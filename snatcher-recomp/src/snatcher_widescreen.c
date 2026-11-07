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
    
    // Si la anchura es estándar (320), devuelve el framebuffer nativo directamente
    if (ws->width == 320) {
        if (width) *width = 320;
        if (height) *height = 224;
        if (pitch) *pitch = sizeof(uint32_t) * GVDP_MAX_WIDTH;
        ws->original_frames++;
        return &ws->machine->pixels[0][0];
    }

    // Modo Panorámico Widescreen (16:9 / 21:9):
    // Centra la imagen de 320x224 en el canvas panorámico con marco de relleno
    unsigned canvas_w = ws->width;
    unsigned canvas_h = 224;
    unsigned offset_x = (canvas_w - 320) / 2;

    for (unsigned y = 0; y < canvas_h; y++) {
        // Relleno de fondo cinemático izquierdo
        for (unsigned x = 0; x < offset_x; x++) {
            ws->canvas[y][x] = 0xFF080808; // Color negro/gris cinemático
        }
        // Copia de los píxeles nativos del VDP centrados
        memcpy(&ws->canvas[y][offset_x], &ws->machine->pixels[y][0], 320 * sizeof(uint32_t));
        // Relleno de fondo cinemático derecho
        for (unsigned x = offset_x + 320; x < canvas_w; x++) {
            ws->canvas[y][x] = 0xFF080808;
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
