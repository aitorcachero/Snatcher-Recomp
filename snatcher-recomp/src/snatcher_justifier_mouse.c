/* =============================================================================
 * SNATCHER (Mega-CD) — Konami Justifier Lightgun Mouse Support
 * Traduce el movimiento y clics del raton del PC a coordenadas de pistola optica
 * ============================================================================= */
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    bool enabled;
    int mouse_x;
    int mouse_y;
    bool trigger_down;
    bool reload_down;
    int screen_width;
    int screen_height;
} SnatcherJustifierState;

static SnatcherJustifierState g_justifier = {
    .enabled = true,
    .mouse_x = 160,
    .mouse_y = 112,
    .trigger_down = false,
    .reload_down = false,
    .screen_width = 320,
    .screen_height = 224
};

void snatcher_justifier_set_resolution(int width, int height) {
    if (width > 0) g_justifier.screen_width = width;
    if (height > 0) g_justifier.screen_height = height;
}

void snatcher_justifier_update_mouse(int window_x, int window_y, int win_w, int win_h, int is_widescreen) {
    if (win_w <= 0 || win_h <= 0) return;
    int mapped_x;
    if (is_widescreen) {
        // En 16:9 panorámico, la imagen llena todo el ancho de la pantalla
        mapped_x = (window_x * 256) / win_w;
    } else {
        // En 4:3 clásico, la imagen se mantiene en 4:3 centrada con franjas negras a los lados
        int view_w = (win_h * 4) / 3;
        int bar_w = (win_w - view_w) / 2;
        if (bar_w < 0) bar_w = 0;
        if (window_x < bar_w) mapped_x = 0;
        else if (window_x > win_w - bar_w) mapped_x = 255;
        else mapped_x = ((window_x - bar_w) * 256) / (view_w > 0 ? view_w : 1);
    }
    int mapped_y = (window_y * 224) / win_h;

    if (mapped_x < 0) mapped_x = 0;
    if (mapped_x > 255) mapped_x = 255;
    if (mapped_y < 0) mapped_y = 0;
    if (mapped_y > 223) mapped_y = 223;

    g_justifier.mouse_x = mapped_x;
    g_justifier.mouse_y = mapped_y;
}

void snatcher_justifier_button_down(int button) {
    if (button == 1) { // Click Izquierdo = Gatillo / Disparar
        g_justifier.trigger_down = true;
    } else if (button == 3) { // Click Derecho = Recargar / Escudo
        g_justifier.reload_down = true;
    }
}

void snatcher_justifier_button_up(int button) {
    if (button == 1) {
        g_justifier.trigger_down = false;
    } else if (button == 3) {
        g_justifier.reload_down = false;
    }
}

/* Latch de HV Counter del VDP para detección de posición de impacto */
void snatcher_justifier_get_latch(uint8_t *h_counter, uint8_t *v_counter) {
    if (h_counter) {
        // En VDP de Mega Drive, el H-counter cuenta pixels/2
        *h_counter = (uint8_t)(g_justifier.mouse_x / 2);
    }
    if (v_counter) {
        *v_counter = (uint8_t)g_justifier.mouse_y;
    }
}

bool snatcher_justifier_is_trigger_active(void) {
    return g_justifier.trigger_down;
}
