/* =============================================================================
 * SNATCHER (Mega-CD) — Widescreen & Presentation Canvas Handler
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

SegaCDWidescreenState segacd_widescreen_state(const SegaCDWidescreen *ws) {
    return ws ? ws->state : SEGACD_WIDESCREEN_UNAVAILABLE;
}

const uint32_t *segacd_widescreen_frame(SegaCDWidescreen *ws, unsigned *width,
                                       unsigned *height, unsigned *pitch) {
    if (!ws || !ws->machine) return NULL;
    
    unsigned game_w = ws->machine->width ? ws->machine->width : 256;
    unsigned game_h = ws->machine->height ? ws->machine->height : 224;

    // Si está en modo nativo 4:3 o ancho no expandido, devolver el buffer nativo exacto
    if (ws->width <= game_w || ws->state == SEGACD_WIDESCREEN_NATIVE) {
        if (width) *width = game_w;
        if (height) *height = game_h;
        if (pitch) *pitch = sizeof(uint32_t) * GVDP_MAX_WIDTH;
        ws->original_frames++;
        return &ws->machine->pixels[0][0];
    }

    // Modo Panorámico Widescreen (16:9):
    // Con resolución vertical de 224 píxeles, la relación 16:9 exacta es 398 píxeles (224 * 16 / 9 ≈ 398).
    // Para el formato panorámico 16:9, escalamos horizontalmente los 256 píxeles del juego
    // a lo largo de todo el ancho del lienzo (398 píxeles) para llenar completamente la pantalla sin barras negras laterales.
    unsigned canvas_w = ws->width > 0 ? ws->width : 398;
    if (canvas_w > GVDP_MAX_WIDTH) canvas_w = GVDP_MAX_WIDTH;
    if (canvas_w < game_w) canvas_w = game_w;

    unsigned canvas_h = game_h;

    for (unsigned y = 0; y < canvas_h && y < 240; y++) {
        for (unsigned x = 0; x < canvas_w; x++) {
            unsigned src_x = (x * game_w) / canvas_w;
            if (src_x >= game_w) src_x = game_w - 1;
            ws->canvas[y][x] = ws->machine->pixels[y][src_x];
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
