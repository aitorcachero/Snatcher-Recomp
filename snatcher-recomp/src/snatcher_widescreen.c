/* =============================================================================
 * SNATCHER (Mega-CD) — Widescreen, CRT Scanlines & TV Color Canvas Handler
 * ============================================================================= */
#include "../../segagenesisrecomp/runner/cd/sonic_cd_widescreen.h"
#include <stdlib.h>
#include <string.h>

struct SegaCDWidescreen {
    SegaCDMachine *machine;
    const SegaCDNativeProgram *program;
    unsigned width;
    unsigned height;
    uint32_t canvas[240][GVDP_MAX_WIDTH];
    uint64_t expanded_frames;
    uint64_t original_frames;
    uint64_t scene_rejections;
    SegaCDWidescreenState state;
    int color_mode;    // 0: Raw original, 1: As on a TV (CRT phosphor response & warm gamma)
    int crt_scanlines; // 0: Off, 1: CRT scanlines
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
    ws->crt_scanlines = 0;
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
    if (width > GVDP_MAX_WIDTH) width = GVDP_MAX_WIDTH;
    if (width < 320) width = 320;
    ws->width = width;
    ws->state = (width > 320) ? SEGACD_WIDESCREEN_ACTIVE : SEGACD_WIDESCREEN_NATIVE;
    return 1;
}

void segacd_widescreen_set_effects(SegaCDWidescreen *ws, int color_mode, int crt_scanlines) {
    if (ws) {
        ws->color_mode = color_mode;
        ws->crt_scanlines = crt_scanlines;
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
    unsigned canvas_w = is_wide ? ws->width : game_w;
    if (canvas_w > GVDP_MAX_WIDTH) canvas_w = GVDP_MAX_WIDTH;
    if (canvas_w < game_w) canvas_w = game_w;

    unsigned canvas_h = game_h;

    // Si no está en panorámico y no hay efectos (modo Raw puro 4:3), devolver buffer nativo sin copia
    if (!is_wide && !ws->color_mode && !ws->crt_scanlines) {
        if (width) *width = game_w;
        if (height) *height = game_h;
        if (pitch) *pitch = sizeof(uint32_t) * GVDP_MAX_WIDTH;
        ws->original_frames++;
        return &ws->machine->pixels[0][0];
    }

    // Procesar fotograma con escalado horizontal 16:9, colores CRT y/o scanlines
    for (unsigned y = 0; y < canvas_h && y < 240; y++) {
        int is_scanline = ws->crt_scanlines && (y % 2 != 0);
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
    if (pitch) *pitch = sizeof(uint32_t) * GVDP_MAX_WIDTH;

    return &ws->canvas[0][0];
}

void segacd_widescreen_stats(const SegaCDWidescreen *ws, uint64_t *expanded_frames,
                             uint64_t *original_frames, uint64_t *scene_rejections) {
    if (!ws) return;
    if (expanded_frames) *expanded_frames = ws->expanded_frames;
    if (original_frames) *original_frames = ws->original_frames;
    if (scene_rejections) *scene_rejections = ws->scene_rejections;
}
