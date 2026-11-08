/* =============================================================================
 * SNATCHER (Mega-CD) — Widescreen, EPX/Scale2x HD Text, CRT & TV Color Canvas
 * ============================================================================= */
#include "../../segagenesisrecomp/runner/cd/sonic_cd_widescreen.h"
#include <stdlib.h>
#include <string.h>

#define MAX_WS_WIDTH  1024
#define MAX_WS_HEIGHT 480

struct SegaCDWidescreen {
    SegaCDMachine *machine;
    const SegaCDNativeProgram *program;
    unsigned width;
    unsigned height;
    uint32_t canvas[MAX_WS_HEIGHT][MAX_WS_WIDTH];
    uint32_t epx_temp[448][512];
    uint64_t expanded_frames;
    uint64_t original_frames;
    uint64_t scene_rejections;
    SegaCDWidescreenState state;
    int color_mode;    // 0: Raw original, 1: As on a TV (CRT phosphor response & warm gamma)
    int filter_mode;   // 0: Sharp, 1: Smooth, 2: CRT Scanlines, 3: EPX Scale2x (Texto HD)
};

SegaCDWidescreen *segacd_widescreen_create(SegaCDMachine *machine,
                                          const SegaCDNativeProgram *program) {
    SegaCDWidescreen *ws = (SegaCDWidescreen *)calloc(1, sizeof(SegaCDWidescreen));
    if (!ws) return NULL;
    ws->machine = machine;
    ws->program = program;
    ws->width = 320;
    ws->height = 224;
    ws->state = SEGACD_WIDESCREEN_NATIVE;
    ws->color_mode = 0;
    ws->filter_mode = 0;
    return ws;
}

int segacd_widescreen_destroy(SegaCDWidescreen *ws) {
    if (ws) {
        free(ws);
    }
    return 1;
}

int segacd_widescreen_prepare(SegaCDWidescreen *ws, unsigned width) {
    if (!ws) return 0;
    if (width > MAX_WS_WIDTH) width = MAX_WS_WIDTH;
    if (width < 320) width = 320;
    ws->width = width;
    ws->state = (width > 320) ? SEGACD_WIDESCREEN_ACTIVE : SEGACD_WIDESCREEN_NATIVE;
    return 1;
}

void segacd_widescreen_set_effects(SegaCDWidescreen *ws, int color_mode, int filter_mode) {
    if (ws) {
        ws->color_mode = color_mode;
        ws->filter_mode = filter_mode;
    }
}

SegaCDWidescreenState segacd_widescreen_state(const SegaCDWidescreen *ws) {
    return ws ? ws->state : SEGACD_WIDESCREEN_UNAVAILABLE;
}

static inline uint32_t apply_tv_color(uint32_t c) {
    uint32_t r = (c >> 16) & 0xFF;
    uint32_t g = (c >> 8) & 0xFF;
    uint32_t b = c & 0xFF;

    // Simulación de fósforo de TV Trinitron/CRT: calidez sutil y contraste de negros profundos
    uint32_t nr = (r * 230 + g * 20 + b * 6) >> 8;
    uint32_t ng = (r * 10 + g * 235 + b * 11) >> 8;
    uint32_t nb = (r * 5 + g * 15 + b * 236) >> 8;
    if (nr > 255) nr = 255;
    if (ng > 255) ng = 255;
    if (nb > 255) nb = 255;
    return (0xFF000000 | (nr << 16) | (ng << 8) | nb);
}

static inline uint32_t apply_scanline(uint32_t c) {
    // Atenuar levemente líneas alternas (80% luminancia) para dar textura de tubo CRT
    uint32_t r = ((c >> 16) & 0xFF) * 204 >> 8;
    uint32_t g = ((c >> 8) & 0xFF) * 204 >> 8;
    uint32_t b = (c & 0xFF) * 204 >> 8;
    return (0xFF000000 | (r << 16) | (g << 8) | b);
}

const uint32_t *segacd_widescreen_frame(SegaCDWidescreen *ws, unsigned *width,
                                       unsigned *height, unsigned *pitch) {
    if (!ws || !ws->machine) return NULL;
    
    unsigned game_w = ws->machine->width ? ws->machine->width : 256;
    unsigned game_h = ws->machine->height ? ws->machine->height : 224;

    int is_wide = (ws->width > 320 && ws->state == SEGACD_WIDESCREEN_ACTIVE);

    // ── MODO 3: FILTRO EPX / Scale2x (MEJORA Y SUAVIZADO HD DE TIPOGRAFÍAS Y TEXTOS) ──
    if (ws->filter_mode == 3) {
        // Paso 1: Aplicar Scale2x / EPX sobre la matriz original de 256x224 píxeles del juego.
        // Esto redondea los trazos diagonales y esquinas de las fuentes sin añadir borrosidad.
        for (unsigned y = 0; y < 224; y++) {
            unsigned y_up = (y > 0) ? y - 1 : y;
            unsigned y_dn = (y < 223) ? y + 1 : y;
            for (unsigned x = 0; x < 256; x++) {
                unsigned x_lf = (x > 0) ? x - 1 : x;
                unsigned x_rt = (x < 255) ? x + 1 : x;

                uint32_t P = ws->machine->pixels[y][x];
                uint32_t A = ws->machine->pixels[y_up][x];
                uint32_t C = ws->machine->pixels[y][x_lf];
                uint32_t B = ws->machine->pixels[y][x_rt];
                uint32_t D = ws->machine->pixels[y_dn][x];

                uint32_t p1 = P, p2 = P, p3 = P, p4 = P;
                if (C == A && C != D && A != B) p1 = A;
                if (A == B && A != C && B != D) p2 = B;
                if (D == C && D != B && C != A) p3 = C;
                if (B == D && B != A && D != C) p4 = D;

                if (ws->color_mode) {
                    p1 = apply_tv_color(p1);
                    p2 = apply_tv_color(p2);
                    p3 = apply_tv_color(p3);
                    p4 = apply_tv_color(p4);
                }

                ws->epx_temp[2 * y    ][2 * x    ] = p1;
                ws->epx_temp[2 * y    ][2 * x + 1] = p2;
                ws->epx_temp[2 * y + 1][2 * x    ] = p3;
                ws->epx_temp[2 * y + 1][2 * x + 1] = p4;
            }
        }

        // Paso 2: Escalar la imagen EPX al lienzo final en alta resolución:
        // En 16:9 panorámico: 796x448 (448 * 16 / 9 = 796.444).
        // En 4:3 clásico: 512x448 exacto.
        unsigned out_w = is_wide ? 796 : 512;
        unsigned out_h = 448;

        if (is_wide) {
            for (unsigned y = 0; y < out_h; y++) {
                for (unsigned x = 0; x < out_w; x++) {
                    unsigned src_x = (x * 512) / out_w;
                    if (src_x >= 512) src_x = 511;
                    ws->canvas[y][x] = ws->epx_temp[y][src_x];
                }
            }
        } else {
            for (unsigned y = 0; y < out_h; y++) {
                memcpy(&ws->canvas[y][0], &ws->epx_temp[y][0], 512 * sizeof(uint32_t));
            }
        }

        ws->expanded_frames++;
        if (width) *width = out_w;
        if (height) *height = out_h;
        if (pitch) *pitch = MAX_WS_WIDTH * sizeof(uint32_t);
        return &ws->canvas[0][0];
    }

    // ── MODOS ESTÁNDAR (0: Sharp, 1: Smooth, 2: CRT Scanlines) ──
    unsigned canvas_w = is_wide ? ws->width : game_w;
    if (canvas_w > MAX_WS_WIDTH) canvas_w = MAX_WS_WIDTH;
    if (canvas_w < game_w) canvas_w = game_w;
    unsigned canvas_h = game_h;

    // Si no está en panorámico y no hay efectos (modo Raw puro 4:3), devolver buffer nativo sin copia
    if (!is_wide && !ws->color_mode && ws->filter_mode != 2) {
        if (width) *width = game_w;
        if (height) *height = game_h;
        if (pitch) *pitch = sizeof(uint32_t) * GVDP_MAX_WIDTH;
        ws->original_frames++;
        return &ws->machine->pixels[0][0];
    }

    int crt_scanlines = (ws->filter_mode == 2);
    for (unsigned y = 0; y < canvas_h && y < 240; y++) {
        int is_scanline = crt_scanlines && (y % 2 != 0);
        for (unsigned x = 0; x < canvas_w; x++) {
            unsigned src_x = (x * game_w) / canvas_w;
            if (src_x >= game_w) src_x = game_w - 1;
            uint32_t px = ws->machine->pixels[y][src_x];
            if (ws->color_mode) {
                px = apply_tv_color(px);
            }
            if (is_scanline) {
                px = apply_scanline(px);
            }
            ws->canvas[y][x] = px;
        }
    }

    ws->expanded_frames++;
    if (width) *width = canvas_w;
    if (height) *height = canvas_h;
    if (pitch) *pitch = MAX_WS_WIDTH * sizeof(uint32_t);

    return &ws->canvas[0][0];
}

void segacd_widescreen_stats(const SegaCDWidescreen *ws, uint64_t *expanded_frames,
                             uint64_t *original_frames, uint64_t *scene_rejections) {
    if (!ws) return;
    if (expanded_frames) *expanded_frames = ws->expanded_frames;
    if (original_frames) *original_frames = ws->original_frames;
    if (scene_rejections) *scene_rejections = ws->scene_rejections;
}
