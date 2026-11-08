/* =============================================================================
 * SNATCHER (Mega-CD) — Standalone Native PC Runner & Launcher
 * ============================================================================= */
#include "../../segagenesisrecomp/runner/cd/machine.h"
#include "../../segagenesisrecomp/runner/cd/audio_native.h"
#include "../../segagenesisrecomp/runner/cd/backup.h"
#include "../../segagenesisrecomp/runner/cd/debug.h"
#include "../../segagenesisrecomp/runner/cd/disc_image.h"
#include "../../segagenesisrecomp/runner/cd/presentation.h"
#include "../../segagenesisrecomp/runner/cd/sonic_cd_widescreen.h"
#include "../../segagenesisrecomp/runner/cd/m68k_floor.h"
#include "../../segagenesisrecomp/runner/audio.h"
#include "snatcher_cue.h"
#include "recomp_launcher.h"
#include "../../segagenesisrecomp/runner/external/recomp-ui/src/common/keybinds.h"
#include <SDL2/SDL.h>
#include <windows.h>
#include <commdlg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern const SegaCDNativeProgram *segacd_standalone_program(void);
extern int segacd_standalone_accept_bios(const uint8_t *bytes, size_t size);
extern int segacd_standalone_accept_disc(const uint8_t *sha256);

// Hook para raton Konami Justifier
extern void snatcher_justifier_set_resolution(int width, int height);
extern void snatcher_justifier_update_mouse(int window_x, int window_y, int win_w, int win_h, int is_widescreen);
extern void snatcher_justifier_button_down(int button);
extern void snatcher_justifier_button_up(int button);

typedef struct {
    int fullscreen;
    int window_scale;
    int widescreen;
    int linear_filter;    // 0: Sharp, 1: Smooth, 2: CRT Scanlines
    int volume;
    int mouse_enabled;
    int refresh_rate;     // 0: Auto (monitor Hz), 60, 144, 240, 360
    int vsync;            // 0: Off, 1: On
    int integer_scaling;  // 0: Off, 1: On
    int color_mode;       // 0: Raw original, 1: As on a TV (CRT phosphor warm gamma)
} SnatcherLauncherConfig;

extern void segacd_widescreen_set_effects(SegaCDWidescreen *ws, int color_mode, int crt_scanlines);

// Lanzador moderno estilo Revo
extern int run_snatcher_modern_launcher(char *disc_path_io, size_t disc_path_cap, SnatcherLauncherConfig *cfg_out);

static SegaCDMachine machine;
static SegaCDWidescreen *widescreen = NULL;static void log_debug(const char *msg) {
    FILE *f = fopen("snatcher_debug.log", "a");
    if (f) {
        fprintf(f, "%s\n", msg);
        fclose(f);
    }
}

static void dump_frame_bmp(const char *filename, const uint32_t *pixels, int w, int h, int pitch) {
    FILE *f = fopen(filename, "wb");
    if (!f) return;
    uint16_t bfType = 0x4D42;
    uint32_t bfSize = 54 + w * h * 4;
    uint32_t bfReserved = 0;
    uint32_t bfOffBits = 54;
    fwrite(&bfType, 2, 1, f);
    fwrite(&bfSize, 4, 1, f);
    fwrite(&bfReserved, 4, 1, f);
    fwrite(&bfOffBits, 4, 1, f);

    uint32_t biSize = 40;
    int32_t biWidth = w;
    int32_t biHeight = -h; // top-down
    uint16_t biPlanes = 1;
    uint16_t biBitCount = 32;
    uint32_t biCompression = 0;
    uint32_t biSizeImage = w * h * 4;
    int32_t biXPelsPerMeter = 2835;
    int32_t biYPelsPerMeter = 2835;
    uint32_t biClrUsed = 0;
    uint32_t biClrImportant = 0;
    fwrite(&biSize, 4, 1, f);
    fwrite(&biWidth, 4, 1, f);
    fwrite(&biHeight, 4, 1, f);
    fwrite(&biPlanes, 2, 1, f);
    fwrite(&biBitCount, 2, 1, f);
    fwrite(&biCompression, 4, 1, f);
    fwrite(&biSizeImage, 4, 1, f);
    fwrite(&biXPelsPerMeter, 4, 1, f);
    fwrite(&biYPelsPerMeter, 4, 1, f);
    fwrite(&biClrUsed, 4, 1, f);
    fwrite(&biClrImportant, 4, 1, f);

    const uint8_t *src = (const uint8_t *)pixels;
    for (int y = 0; y < h; y++) {
        fwrite(src + y * pitch, 4, w, f);
    }
    fclose(f);
}
static int media_read(void *image, int32_t lba, uint8_t raw[2352]) {
    int ok = segacd_image_read((SegaCDImage *)image, lba, raw);
    static int read_count = 0;
    if (read_count < 30 || !ok) {
        char msg[256];
        snprintf(msg, sizeof(msg), "media_read: lba=%d ok=%d", lba, ok);
        log_debug(msg);
        read_count++;
    }
    return ok;
}

static uint16_t keyboard_pad(void) {
    const Uint8 *k = SDL_GetKeyboardState(NULL);
    const KeyBinds *kb = recompui_keybinds_get();
    uint16_t mask = 0;
    if (kb) {
        if (kb->p1.up    != SDL_SCANCODE_UNKNOWN && k[kb->p1.up])    mask |= GPAD_UP;
        if (kb->p1.down  != SDL_SCANCODE_UNKNOWN && k[kb->p1.down])  mask |= GPAD_DOWN;
        if (kb->p1.left  != SDL_SCANCODE_UNKNOWN && k[kb->p1.left])  mask |= GPAD_LEFT;
        if (kb->p1.right != SDL_SCANCODE_UNKNOWN && k[kb->p1.right]) mask |= GPAD_RIGHT;
        if (kb->p1.a     != SDL_SCANCODE_UNKNOWN && k[kb->p1.a])     mask |= GPAD_A;
        if (kb->p1.b     != SDL_SCANCODE_UNKNOWN && k[kb->p1.b])     mask |= GPAD_B;
        if (kb->p1.x     != SDL_SCANCODE_UNKNOWN && k[kb->p1.x])     mask |= GPAD_C;
        if (kb->p1.y     != SDL_SCANCODE_UNKNOWN && k[kb->p1.y])     mask |= GPAD_A;
        if (kb->p1.start != SDL_SCANCODE_UNKNOWN && k[kb->p1.start]) mask |= GPAD_START;
    }
    // Sane fallback defaults: Arrows, WASD, Z/X/C/Space/Enter
    if (k[SDL_SCANCODE_UP] || k[SDL_SCANCODE_W])     mask |= GPAD_UP;
    if (k[SDL_SCANCODE_DOWN] || k[SDL_SCANCODE_S])   mask |= GPAD_DOWN;
    if (k[SDL_SCANCODE_LEFT] || k[SDL_SCANCODE_A])   mask |= GPAD_LEFT;
    if (k[SDL_SCANCODE_RIGHT] || k[SDL_SCANCODE_D])  mask |= GPAD_RIGHT;
    if (k[SDL_SCANCODE_Z] || k[SDL_SCANCODE_J] || k[SDL_SCANCODE_SPACE]) mask |= GPAD_A;
    if (k[SDL_SCANCODE_X] || k[SDL_SCANCODE_K])      mask |= GPAD_B;
    if (k[SDL_SCANCODE_C] || k[SDL_SCANCODE_L])      mask |= GPAD_C;
    if (k[SDL_SCANCODE_RETURN])                      mask |= GPAD_START;
    return mask;
}

static uint16_t controller_pad(SDL_GameController *pad) {
    if (!pad) return 0;
    uint16_t mask = 0;
#define BUTTON(sdl, gen) if (SDL_GameControllerGetButton(pad, sdl)) mask |= gen
    BUTTON(SDL_CONTROLLER_BUTTON_DPAD_UP, GPAD_UP);
    BUTTON(SDL_CONTROLLER_BUTTON_DPAD_DOWN, GPAD_DOWN);
    BUTTON(SDL_CONTROLLER_BUTTON_DPAD_LEFT, GPAD_LEFT);
    BUTTON(SDL_CONTROLLER_BUTTON_DPAD_RIGHT, GPAD_RIGHT);
    BUTTON(SDL_CONTROLLER_BUTTON_X, GPAD_A);
    BUTTON(SDL_CONTROLLER_BUTTON_A, GPAD_B);
    BUTTON(SDL_CONTROLLER_BUTTON_B, GPAD_C);
    BUTTON(SDL_CONTROLLER_BUTTON_START, GPAD_START);
#undef BUTTON
    Sint16 x = SDL_GameControllerGetAxis(pad, SDL_CONTROLLER_AXIS_LEFTX);
    Sint16 y = SDL_GameControllerGetAxis(pad, SDL_CONTROLLER_AXIS_LEFTY);
    if (x < -16000) mask |= GPAD_LEFT;
    if (x > 16000) mask |= GPAD_RIGHT;
    if (y < -16000) mask |= GPAD_UP;
    if (y > 16000) mask |= GPAD_DOWN;
    return mask;
}

static int file_exists_and_size(const char *path, size_t *out_size) {
    FILE *f = fopen(path, "rb");
    if (!f) return 0;
    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    fclose(f);
    if (sz < 0) return 0;
    if (out_size) *out_size = (size_t)sz;
    return 1;
}

static int prompt_select_file(const char *title, const char *filter, char *out_path, size_t max_len) {
    HWND hwnd = GetActiveWindow();
    if (!hwnd) hwnd = GetForegroundWindow();
    if (hwnd) EnableWindow(hwnd, FALSE);

    OPENFILENAMEA ofn;
    memset(&ofn, 0, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrTitle = title;
    ofn.lpstrFilter = filter;
    ofn.lpstrFile = out_path;
    ofn.nMaxFile = (DWORD)max_len;
    ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_EXPLORER | OFN_NOCHANGEDIR;
    BOOL ret = GetOpenFileNameA(&ofn);

    if (hwnd) {
        EnableWindow(hwnd, TRUE);
        SetForegroundWindow(hwnd);
        SetActiveWindow(hwnd);
    }
    return ret;
}
extern uint8_t g_ram[0x10000];

static int is_file_ext(const char *path, const char *ext) {
    size_t len = strlen(path);
    size_t elen = strlen(ext);
    if (len < elen) return 0;
    return _stricmp(path + len - elen, ext) == 0;
}

static int prepare_disc_image(const char *input_path, char *out_disc_path, size_t out_max) {
    if (!input_path || input_path[0] == '\0') return 0;

    // Si ya es un .sgcd existente, usarlo directamente
    if (is_file_ext(input_path, ".sgcd")) {
        if (file_exists_and_size(input_path, NULL)) {
            strncpy(out_disc_path, input_path, out_max - 1);
            return 1;
        }
        return 0;
    }

    // Si es un .bin
    char cue_file[MAX_PATH] = { 0 };
    if (is_file_ext(input_path, ".bin")) {
        if (!ensure_snatcher_cue_exists(input_path, cue_file, sizeof(cue_file))) {
            return 0;
        }
        input_path = cue_file;
    }

    // Si es un .cue
    if (is_file_ext(input_path, ".cue")) {
        char target_sgcd[MAX_PATH] = { 0 };
        if (strstr(input_path, "disc") != NULL) {
            strncpy(target_sgcd, "disc/snatcher.sgcd", sizeof(target_sgcd) - 1);
        } else {
            strncpy(target_sgcd, input_path, sizeof(target_sgcd) - 1);
            char *dot = strrchr(target_sgcd, '.');
            if (dot) strcpy(dot, ".sgcd");
        }

        // Si ya existe el .sgcd y tiene tamano suficiente (> 10 MB)
        size_t sz = 0;
        if (file_exists_and_size(target_sgcd, &sz) && sz > 10 * 1024 * 1024) {
            strncpy(out_disc_path, target_sgcd, out_max - 1);
            return 1;
        }

        // Convertir CUE a SGCD
        char log_buf[1024];
        snprintf(log_buf, sizeof(log_buf), "Converting CUE to SGCD: [%s] -> [%s]...", input_path, target_sgcd);
        log_debug(log_buf);

        char err[512] = { 0 };
        CreateDirectoryA("disc", NULL);
        if (!convert_cue_to_sgcd(input_path, target_sgcd, err, sizeof(err))) {
            log_debug(err);
            MessageBoxA(NULL, err, "Error al procesar CUE de Snatcher", MB_ICONERROR);
            return 0;
        }

        log_debug("Conversion to SGCD completed successfully.");
        strncpy(out_disc_path, target_sgcd, out_max - 1);
        return 1;
    }

    return 0;
}

static int run_snatcher_launcher(char *disc_path_io, size_t disc_path_cap, SnatcherLauncherConfig *cfg_out) {
    RecompLauncherCSettings ls;
    memset(&ls, 0, sizeof(ls));
    ls.output_method    = 0;   // SDL
    ls.window_scale     = 3;   // 3x scale (1280x720 en 16:9)
    ls.fullscreen       = 0;
    ls.linear_filter    = 1;
    ls.widescreen       = 1;   // 16:9 por defecto
    ls.widescreen_cells = 426;
    ls.enable_audio     = 1;
    ls.audio_freq       = 48000;
    ls.volume           = 100;
    ls.mouse_enabled    = 1;
    ls.player_src[0]    = 1;   // Teclado + raton
    ls.deadzone[0]      = 10;
    ls.pad_mode[0]      = 1;   // 6 botones

    // Cargar ajustes previos si existen en settings.toml
    FILE *fset = fopen("settings.toml", "r");
    if (fset) {
        char line[256];
        while (fgets(line, sizeof(line), fset)) {
            int v = 0;
            if (sscanf(line, "fullscreen = %d", &v) == 1) ls.fullscreen = v;
            else if (sscanf(line, "window_scale = %d", &v) == 1) ls.window_scale = v;
            else if (sscanf(line, "widescreen = %d", &v) == 1) ls.widescreen = v;
            else if (sscanf(line, "view_mode = %d", &v) == 1) ls.widescreen = (v != 0);
            else if (sscanf(line, "linear_filter = %d", &v) == 1) ls.linear_filter = v;
            else if (sscanf(line, "volume = %d", &v) == 1) ls.volume = v;
            else if (sscanf(line, "vsync = %d", &v) == 1) { if (cfg_out) cfg_out->vsync = v; }
            else if (sscanf(line, "integer_scaling = %d", &v) == 1) { if (cfg_out) cfg_out->integer_scaling = v; }
            else if (sscanf(line, "color_mode = %d", &v) == 1) { if (cfg_out) cfg_out->color_mode = v; }
            else if (sscanf(line, "refresh_rate = %d", &v) == 1) { if (cfg_out) cfg_out->refresh_rate = v; }
        }
        fclose(fset);
    }

    RecompLauncherCGameInfo gi;
    memset(&gi, 0, sizeof(gi));
    gi.name                 = "SNATCHER";
    gi.region               = "Sega Mega-CD (Español)";
    gi.platform             = "SEGA MEGA-CD";
    gi.theme                = "genesis";
    gi.rom_noun             = "Disco";
    gi.widescreen_supported = 1;
    gi.aspect_mask          = 3; // 4:3 y 16:9
    gi.pad_mode_supported   = 1;
    gi.pad_mode_selectable  = 1;
    gi.num_players          = 1;
    gi.sram_path            = "saves/snatcher.bram";
    gi.keybinds_path        = "keybinds.ini";
    gi.config_path          = "settings.toml";

    recomp_launcher_set_preserve_sdl(1);

    const char *assets_dir = "assets";
    if (!file_exists_and_size("assets/fonts/LatoLatin-Regular.ttf", NULL)) {
        if (file_exists_and_size("snatcher-recomp/assets/fonts/LatoLatin-Regular.ttf", NULL)) {
            assets_dir = "snatcher-recomp/assets";
        }
    }

    char picked[MAX_PATH] = { 0 };
    int lr = recomp_launcher_run_window(
        "Snatcher (Sega Mega-CD) — Launcher & Ajustes",
        &ls,
        &gi,
        assets_dir,
        (disc_path_io && disc_path_io[0]) ? disc_path_io : "",
        picked,
        sizeof(picked)
    );

    // Guardar configuracion seleccionada en settings.toml
    fset = fopen("settings.toml", "w");
    if (fset) {
        fprintf(fset, "# Snatcher Mega-CD Recomp - Settings\n");
        fprintf(fset, "fullscreen = %d\n", ls.fullscreen);
        fprintf(fset, "window_scale = %d\n", ls.window_scale);
        fprintf(fset, "widescreen = %d\n", ls.widescreen);
        fprintf(fset, "view_mode = %d\n", ls.widescreen ? 1 : 0);
        fprintf(fset, "linear_filter = %d\n", ls.linear_filter);
        fprintf(fset, "volume = %d\n", ls.volume);
        fclose(fset);
    }

    if (picked[0] != '\0' && disc_path_io && disc_path_cap > 0) {
        strncpy(disc_path_io, picked, disc_path_cap - 1);
        disc_path_io[disc_path_cap - 1] = '\0';
    }

    if (cfg_out) {
        cfg_out->fullscreen = ls.fullscreen;
        cfg_out->window_scale = ls.window_scale;
        cfg_out->widescreen = ls.widescreen;
        cfg_out->linear_filter = ls.linear_filter;
        cfg_out->volume = ls.volume;
        cfg_out->mouse_enabled = ls.mouse_enabled;
    }

    return lr;
}

int main(int argc, char **argv) {
    log_debug("=== Snatcher Recomp Starting ===");
    recompui_keybinds_init(NULL);
    char bios_path[MAX_PATH] = { 0 };
    char disc_path[MAX_PATH] = { 0 };
    char backup_path[MAX_PATH] = { 0 };
    char settings_path[MAX_PATH] = { 0 };
    int max_frames = 0;
    int no_launcher = 0;

    for (int i = 1; i < argc; ++i) {
        if (i + 1 < argc && !strcmp(argv[i], "--bios"))     strncpy(bios_path, argv[++i], sizeof(bios_path) - 1);
        else if (i + 1 < argc && !strcmp(argv[i], "--disc")) strncpy(disc_path, argv[++i], sizeof(disc_path) - 1);
        else if (i + 1 < argc && !strcmp(argv[i], "--backup")) strncpy(backup_path, argv[++i], sizeof(backup_path) - 1);
        else if (i + 1 < argc && !strcmp(argv[i], "--settings")) strncpy(settings_path, argv[++i], sizeof(settings_path) - 1);
        else if (i + 1 < argc && !strcmp(argv[i], "--max-frames")) max_frames = atoi(argv[++i]);
        else if (!strcmp(argv[i], "--no-launcher")) no_launcher = 1;
    }

    // 1. Deteccion automatica de la imagen de disco de Snatcher
    log_debug("Step 1: checking disc...");
    if (disc_path[0] != '\0') {
        char prepared[MAX_PATH] = { 0 };
        if (prepare_disc_image(disc_path, prepared, sizeof(prepared))) {
            strncpy(disc_path, prepared, sizeof(disc_path) - 1);
        }
    }

    if (disc_path[0] == '\0') {
        // 1a. Buscar .sgcd existentes
        const char *sgcd_candidates[] = {
            "disc/snatcher.sgcd",
            "snatcher.sgcd",
            "snatcher-recomp/disc/snatcher.sgcd",
            "../disc/snatcher.sgcd",
            "../../disc/snatcher.sgcd",
            "../../../disc/snatcher.sgcd",
            NULL
        };
        for (int i = 0; sgcd_candidates[i] != NULL; i++) {
            if (file_exists_and_size(sgcd_candidates[i], NULL)) {
                strncpy(disc_path, sgcd_candidates[i], sizeof(disc_path) - 1);
                break;
            }
        }
    }

    if (disc_path[0] == '\0') {
        // 1b. Buscar cualquier .sgcd en carpeta disc/
        WIN32_FIND_DATAA ffd;
        HANDLE hFind = FindFirstFileA("disc\\*.sgcd", &ffd);
        if (hFind != INVALID_HANDLE_VALUE) {
            snprintf(disc_path, sizeof(disc_path), "disc\\%s", ffd.cFileName);
            FindClose(hFind);
        }
    }

    if (disc_path[0] == '\0') {
        // 1c. Buscar archivos .cue candidatos
        const char *cue_candidates[] = {
            "disc/SNATCHER.CUE",
            "disc/snatcher.cue",
            "SNATCHER.CUE",
            "snatcher.cue",
            "snatcher-recomp/disc/SNATCHER.CUE",
            "snatcher-recomp/disc/snatcher.cue",
            "../disc/SNATCHER.CUE",
            "../disc/snatcher.cue",
            "../../disc/SNATCHER.CUE",
            "../../disc/snatcher.cue",
            "../../../disc/SNATCHER.CUE",
            NULL
        };
        for (int i = 0; cue_candidates[i] != NULL; i++) {
            if (file_exists_and_size(cue_candidates[i], NULL)) {
                char prepared[MAX_PATH] = { 0 };
                if (prepare_disc_image(cue_candidates[i], prepared, sizeof(prepared))) {
                    strncpy(disc_path, prepared, sizeof(disc_path) - 1);
                    break;
                }
            }
        }
    }

    if (disc_path[0] == '\0') {
        // 1d. Buscar cualquier .cue en disc/
        WIN32_FIND_DATAA ffd;
        HANDLE hFind = FindFirstFileA("disc\\*.cue", &ffd);
        if (hFind != INVALID_HANDLE_VALUE) {
            char found_cue[MAX_PATH];
            snprintf(found_cue, sizeof(found_cue), "disc\\%s", ffd.cFileName);
            FindClose(hFind);
            char prepared[MAX_PATH] = { 0 };
            if (prepare_disc_image(found_cue, prepared, sizeof(prepared))) {
                strncpy(disc_path, prepared, sizeof(disc_path) - 1);
            }
        }
    }

    if (disc_path[0] == '\0') {
        // 1e. Buscar SNATCHER.BIN en disc/ (si el usuario solo coloco el .bin)
        const char *bin_candidates[] = {
            "disc/SNATCHER.BIN",
            "disc/snatcher.bin",
            "SNATCHER.BIN",
            "snatcher.bin",
            NULL
        };
        for (int i = 0; bin_candidates[i] != NULL; i++) {
            if (file_exists_and_size(bin_candidates[i], NULL)) {
                char prepared[MAX_PATH] = { 0 };
                if (prepare_disc_image(bin_candidates[i], prepared, sizeof(prepared))) {
                    strncpy(disc_path, prepared, sizeof(disc_path) - 1);
                    break;
                }
            }
        }
    }

    char buf[1024];
    snprintf(buf, sizeof(buf), "Disc path resolved: [%s]", disc_path);
    log_debug(buf);

    // 2. Deteccion automatica de BIOS de Sega CD (128 KB)
    log_debug("Step 2: checking BIOS...");
    if (bios_path[0] == '\0') {
        const char *bios_candidates[] = {
            "bios/us_scd1_9210.bin",
            "bios/bios_CD_U.bin",
            "bios/segacd_bios.bin",
            "bios/mcd2_us.bin",
            "bios/bios.bin",
            "bios/bios/bios_CD_U.bin",
            "bios/bios/Sega CD (U) - Model 1 v1.10 (1992).bin",
            "snatcher-recomp/bios/us_scd1_9210.bin",
            "snatcher-recomp/bios/bios_CD_U.bin",
            "snatcher-recomp/bios/segacd_bios.bin",
            "snatcher-recomp/bios/mcd2_us.bin",
            "snatcher-recomp/bios/bios.bin",
            "../bios/us_scd1_9210.bin",
            "../bios/bios_CD_U.bin",
            "../bios/segacd_bios.bin",
            "../../bios/us_scd1_9210.bin",
            "../../bios/bios_CD_U.bin",
            "../../bios/segacd_bios.bin",
            "../../bios/bios/bios_CD_U.bin",
            "../../bios/bios/Sega CD (U) - Model 1 v1.10 (1992).bin",
            "../../../bios/us_scd1_9210.bin",
            "../../../bios/bios_CD_U.bin",
            "../../../bios/segacd_bios.bin",
            "../../../bios/bios/bios_CD_U.bin",
            "../../../bios/bios/Sega CD (U) - Model 1 v1.10 (1992).bin",
            "G:/Proyectos/sega megadrive/bios/us_scd1_9210.bin",
            "G:/Proyectos/sega megadrive/bios/bios_CD_U.bin",
            "G:/Proyectos/sega megadrive/bios/segacd_bios.bin",
            "G:/Proyectos/sega megadrive/bios/bios/bios_CD_U.bin",
            "G:/Proyectos/sega megadrive/bios/bios/Sega CD (U) - Model 1 v1.10 (1992).bin",
            NULL
        };
        for (int i = 0; bios_candidates[i] != NULL; i++) {
            size_t sz = 0;
            if (file_exists_and_size(bios_candidates[i], &sz) && sz == SEGACD_BIOS_BYTES) {
                strncpy(bios_path, bios_candidates[i], sizeof(bios_path) - 1);
                break;
            }
        }
    }

    // Si aun no se encuentra, busca cualquier .bin de 128KB en bios/
    if (bios_path[0] == '\0') {
        WIN32_FIND_DATAA ffd;
        HANDLE hFind = FindFirstFileA("bios\\*.bin", &ffd);
        if (hFind != INVALID_HANDLE_VALUE) {
            do {
                if (ffd.nFileSizeLow == SEGACD_BIOS_BYTES) {
                    snprintf(bios_path, sizeof(bios_path), "bios\\%s", ffd.cFileName);
                    break;
                }
            } while (FindNextFileA(hFind, &ffd));
            FindClose(hFind);
        }
    }

    snprintf(buf, sizeof(buf), "BIOS auto-check: [%s]", bios_path);
    log_debug(buf);

    // 2b. Launcher moderno con configuracion de resolución, controles, audio y mejoras
    SnatcherLauncherConfig launcher_cfg = {
        .fullscreen = 1,
        .window_scale = 3,
        .widescreen = 1,
        .linear_filter = 3, // EPX Texto HD por defecto
        .volume = 100,
        .mouse_enabled = 1,
        .refresh_rate = 0, // Auto: adapta a los hercios del monitor
        .vsync = 1,
        .integer_scaling = 0,
        .color_mode = 1 // Colores como en TV por defecto
    };

    if (!no_launcher && max_frames == 0) {
        log_debug("Step 2b: Showing Recomp Launcher UI...");
        int lr = run_snatcher_modern_launcher(disc_path, sizeof(disc_path), &launcher_cfg);
        if (lr == 1) { // RECOMP_LAUNCHER_RESULT_QUIT
            log_debug("Launcher closed by user.");
            return 0;
        }
        if (disc_path[0] != '\0') {
            char prepared[MAX_PATH] = { 0 };
            if (prepare_disc_image(disc_path, prepared, sizeof(prepared))) {
                strncpy(disc_path, prepared, sizeof(disc_path) - 1);
            }
        }
    }

    if (disc_path[0] == '\0') {
        char picked[MAX_PATH] = { 0 };
        if (prompt_select_file("Selecciona la imagen de Snatcher (.sgcd, .cue, .bin)",
                               "Imagenes Sega CD (*.sgcd;*.cue;*.bin)\0*.sgcd;*.cue;*.bin\0Todos (*.*)\0*.*\0",
                               picked, sizeof(picked))) {
            char prepared[MAX_PATH] = { 0 };
            if (prepare_disc_image(picked, prepared, sizeof(prepared))) {
                strncpy(disc_path, prepared, sizeof(disc_path) - 1);
            }
        }
    }

    if (disc_path[0] == '\0') {
        log_debug("ERROR: Disc path is empty!");
        MessageBoxA(NULL,
            "MegaCD-Recomp requiere la imagen de disco de Snatcher.\n\n"
            "Por favor, copia tus archivos SNATCHER.CUE y SNATCHER.BIN\n"
            "dentro de la carpeta 'disc/' o selecciónalos en el lanzador.",
            "MegaCD-Recomp — Imagen de disco requerida", MB_ICONWARNING);
        return 1;
    }

    // Comprobar BIOS después del launcher si aún no se tiene
    if (bios_path[0] == '\0') {
        char picked[MAX_PATH] = { 0 };
        if (prompt_select_file("Selecciona el archivo BIOS de Sega CD (128 KB)",
                               "Archivos BIOS (*.bin;*.rom)\0*.bin;*.rom\0Todos (*.*)\0*.*\0",
                               picked, sizeof(picked))) {
            size_t sz = 0;
            if (file_exists_and_size(picked, &sz) && sz == SEGACD_BIOS_BYTES) {
                CreateDirectoryA("bios", NULL);
                CopyFileA(picked, "bios\\segacd_bios.bin", FALSE);
                strncpy(bios_path, picked, sizeof(bios_path) - 1);
            }
        }
    }

    if (bios_path[0] == '\0') {
        log_debug("ERROR: BIOS path is empty!");
        MessageBoxA(NULL,
            "MegaCD-Recomp requiere el archivo de BIOS de Sega CD (128 KB).\n\n"
            "Por favor, copia tu archivo de BIOS (ej: bios_CD_U.bin o us_scd1_9210.bin)\n"
            "dentro de la carpeta 'bios/' o 'snatcher-recomp/bios/' y vuelve a iniciar el juego.",
            "MegaCD-Recomp — Archivo de BIOS requerido", MB_ICONWARNING);
        return 1;
    }

    // 3. Inicializacion de SDL
    log_debug("Step 3: Initializing SDL...");
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) != 0) {
        snprintf(buf, sizeof(buf), "SDL_Init failed: %s", SDL_GetError());
        log_debug(buf);
        MessageBoxA(NULL, buf, "Error SDL2", MB_ICONERROR);
        return 2;
    }
    log_debug("SDL initialized successfully.");

    // Rutas de guardado y configuracion
    if (backup_path[0] == '\0') {
        CreateDirectoryA("saves", NULL);
        strncpy(backup_path, "saves/snatcher.bram", sizeof(backup_path) - 1);
    }
    if (settings_path[0] == '\0') {
        strncpy(settings_path, "settings.toml", sizeof(settings_path) - 1);
    }

    // 4. Carga de BIOS
    log_debug("Step 4: Reading BIOS file...");
    static uint8_t bios[SEGACD_BIOS_BYTES];
    FILE *fb = fopen(bios_path, "rb");
    if (!fb || fread(bios, 1, SEGACD_BIOS_BYTES, fb) != SEGACD_BIOS_BYTES) {
        if (fb) fclose(fb);
        log_debug("Failed to read 131072 bytes from BIOS file");
        MessageBoxA(NULL, "No se pudo leer el archivo de BIOS especificado.", "Error de lectura", MB_ICONERROR);
        SDL_Quit();
        return 2;
    }
    fclose(fb);
    log_debug("BIOS loaded OK.");

    // 5. Carga de la imagen de disco
    log_debug("Step 5: Opening disc image...");
    char disc_err[512] = { 0 };
    SegaCDImage *image = segacd_image_open(disc_path, disc_err, sizeof(disc_err));
    if (!image) {
        snprintf(buf, sizeof(buf), "segacd_image_open failed: %s", disc_err);
        log_debug(buf);
        MessageBoxA(NULL, buf, "Error de disco", MB_ICONERROR);
        SDL_Quit();
        return 2;
    }
    log_debug("Disc image opened OK.");

    // 6. Inicializacion de la maquina nativa Sega CD
    log_debug("Step 6: Initializing SegaCD machine...");
    if (!segacd_machine_init(&machine, bios, sizeof(bios), segacd_standalone_program())) {
        log_debug("segacd_machine_init failed!");
        MessageBoxA(NULL, "Fallo al inicializar los modulos nativos del juego.", "Error interno", MB_ICONERROR);
        segacd_image_close(image);
        SDL_Quit();
        return 2;
    }
    log_debug("Machine initialized OK.");

    // Activar interprete floor de respaldo para codigo transitorio / BIOS no compilada
    segacd_coordinator_floor(&machine.coordinator, segacd_m68k_floor_step);

    // Carga de Backup RAM
    segacd_backup_load(backup_path, machine.devices.backup);

    // Montaje del lector CDD
    segacd_cdd_mount(&machine.devices.drive, segacd_image_toc(image));
    segacd_coordinator_media(&machine.coordinator, media_read, image, NULL, NULL);

    // Inicializacion de audio nativo x64
    SegaCDNativeAudio *audio = segacd_native_audio_create(1);
    if (audio) {
        segacd_native_audio_attach_io(audio, &machine.coordinator.io);
        machine.audio_write = segacd_native_audio_write;
        machine.audio_user = audio;
        audio_set_master_volume(launcher_cfg.volume);
    }

    // 7. Creacion de la ventana de juego
    log_debug("Step 7: Creating SDL window...");
    int scale = launcher_cfg.window_scale > 0 ? launcher_cfg.window_scale : 3;
    // Para altura vertical 224, la relación 16:9 exacta es 398 (224*16/9 ≈ 398)
    int base_w = launcher_cfg.widescreen ? 398 : 298;
    int base_h = 224;
    int win_w = base_w * scale;
    int win_h = base_h * scale;

    Uint32 win_flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI;
    if (launcher_cfg.fullscreen) {
        win_flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    }

    SDL_Window *window = SDL_CreateWindow(
        "Snatcher (Mega-CD) — Native PC Port [Español]",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        win_w, win_h,
        win_flags
    );
    if (!window) {
        snprintf(buf, sizeof(buf), "SDL_CreateWindow failed: %s", SDL_GetError());
        log_debug(buf);
        MessageBoxA(NULL, buf, "Error Ventana", MB_ICONERROR);
        return 2;
    }
    log_debug("SDL window created OK.");

    int monitor_hz = 60;
    SDL_DisplayMode dm;
    int display_idx = SDL_GetWindowDisplayIndex(window);
    if (display_idx < 0) display_idx = 0;
    if (SDL_GetCurrentDisplayMode(display_idx, &dm) == 0 && dm.refresh_rate > 0) {
        monitor_hz = dm.refresh_rate;
    }

    int target_hz = launcher_cfg.refresh_rate;
    if (target_hz <= 0) {
        target_hz = monitor_hz;
    }
    snprintf(buf, sizeof(buf), "Selected display refresh rate: %d Hz (Monitor native: %d Hz, %s)",
             target_hz, monitor_hz, launcher_cfg.refresh_rate <= 0 ? "Auto" : "Manual");
    log_debug(buf);

    Uint32 rend_flags = SDL_RENDERER_ACCELERATED;
    if (launcher_cfg.vsync) {
        rend_flags |= SDL_RENDERER_PRESENTVSYNC;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, rend_flags);
    if (!renderer) {
        log_debug("Accelerated renderer failed, falling back to software...");
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    }
    if (!renderer) {
        snprintf(buf, sizeof(buf), "SDL_CreateRenderer failed: %s", SDL_GetError());
        log_debug(buf);
        MessageBoxA(NULL, buf, "Error Renderer", MB_ICONERROR);
        return 2;
    }
    log_debug("Renderer created OK.");

    SDL_RenderSetIntegerScale(renderer, launcher_cfg.integer_scaling ? SDL_TRUE : SDL_FALSE);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, (launcher_cfg.linear_filter == 1 || launcher_cfg.linear_filter == 3) ? "1" : "0");

    SegaCDPresentation *presentation = segacd_presentation_create(window, renderer, settings_path, 0);
    if (!presentation) {
        log_debug("segacd_presentation_create failed!");
    } else {
        log_debug("Presentation created OK.");
    }
    if (presentation) {
        log_debug("Presentation created OK.");
        SDL_RenderSetIntegerScale(renderer, launcher_cfg.integer_scaling ? SDL_TRUE : SDL_FALSE);
    }

    // Restaurar título y tamaño tras presentation_create
    SDL_SetWindowTitle(window, "Snatcher (Mega-CD) — Native PC Port [Español]");
    if (launcher_cfg.fullscreen) {
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    } else {
        SDL_SetWindowSize(window, win_w, win_h);
        SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    }

    // Mando de juego
    SDL_GameController *pad = NULL;
    for (int i = 0; i < SDL_NumJoysticks(); ++i) {
        if (SDL_IsGameController(i)) {
            pad = SDL_GameControllerOpen(i);
            break;
        }
    }

    // Modo Panorámico Widescreen y Efectos Visuales (Colores TV, Scanlines CRT y EPX Scale2x)
    widescreen = segacd_widescreen_create(&machine, segacd_standalone_program());
    if (widescreen) {
        segacd_widescreen_prepare(widescreen, launcher_cfg.widescreen ? 398 : 256);
        segacd_widescreen_set_effects(widescreen, launcher_cfg.color_mode, launcher_cfg.linear_filter);
    }

    snatcher_justifier_set_resolution(win_w, win_h);

    // 8. Bucle principal de juego con soporte nativo para 60 Hz, 144 Hz, 240 Hz y 360 Hz
    int quit = 0;
    uint64_t freq = SDL_GetPerformanceFrequency();
    uint64_t last_time = SDL_GetPerformanceCounter();
    uint64_t target_render_time = last_time;
    uint64_t render_interval = freq / (uint64_t)target_hz;

    const double time_per_sim_frame = 1.0 / 60.0;
    double accumulator = 0.0;

    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            } else if (event.type == SDL_KEYDOWN) {
                // Tecla Escape (Esc) para salir del juego
                if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                    quit = 1;
                }
            } else if (event.type == SDL_CONTROLLERBUTTONDOWN) {
                // Botón Back o Guide en mando para salir del juego
                if (event.cbutton.button == SDL_CONTROLLER_BUTTON_BACK ||
                    event.cbutton.button == SDL_CONTROLLER_BUTTON_GUIDE) {
                    quit = 1;
                }
            } else if (event.type == SDL_CONTROLLERDEVICEADDED && !pad) {
                pad = SDL_GameControllerOpen(event.cdevice.which);
            } else if (event.type == SDL_CONTROLLERDEVICEREMOVED && pad) {
                if (SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(pad)) == event.cdevice.which) {
                    SDL_GameControllerClose(pad);
                    pad = NULL;
                }
            } else if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED) {
                win_w = event.window.data1;
                win_h = event.window.data2;
                snatcher_justifier_set_resolution(win_w, win_h);
            } else if (event.type == SDL_MOUSEMOTION) {
                if (launcher_cfg.mouse_enabled) {
                    snatcher_justifier_update_mouse(event.motion.x, event.motion.y, win_w, win_h, launcher_cfg.widescreen);
                }
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (launcher_cfg.mouse_enabled) {
                    snatcher_justifier_button_down(event.button.button);
                }
            } else if (event.type == SDL_MOUSEBUTTONUP) {
                if (launcher_cfg.mouse_enabled) {
                    snatcher_justifier_button_up(event.button.button);
                }
            }

            if (presentation && segacd_presentation_handle_event(presentation, &event)) {
                continue;
            }
        }

        int menu_open = presentation && segacd_presentation_is_open(presentation);
        audio_set_playback_enabled(!menu_open);

        // Control de tiempo para la simulación precisa de Mega-CD a 60 Hz
        uint64_t current_time = SDL_GetPerformanceCounter();
        double delta_seconds = (double)(current_time - last_time) / (double)freq;
        last_time = current_time;
        if (delta_seconds > 0.15) delta_seconds = 0.15;
        accumulator += delta_seconds;

        if (!menu_open) {
            // Avanzar fotogramas de la simulación nativa a 60.0 Hz exactos
            while (accumulator >= time_per_sim_frame) {
                int block_input = segacd_presentation_blocks_game_input(presentation);
                uint16_t buttons = block_input ? 0 : (keyboard_pad() | controller_pad(pad));
                segacd_machine_pad(&machine, 0, buttons);

                // Ejecutar un fotograma nativo de Mega-CD
                M68kStepResult res = segacd_machine_run_frame(&machine);
                if (max_frames > 0 && machine.frames >= (uint64_t)max_frames) {
                    quit = 1;
                    break;
                }

                // Enviar buffer de audio nativo hacia SDL2
                if (audio) {
                    segacd_native_audio_finish_frame(audio, machine.frames * 896040u, (uint32_t)machine.frames, 1);
                }

                accumulator -= time_per_sim_frame;

                static uint64_t last_logged_frame = 0;
                static int error_logged = 0;
                if (res != M68K_STEP_OK && !error_logged) {
                    char msg[2048];
                    uint32_t mpc = machine.coordinator.cpu[0].state.regs.PC;
                    uint32_t spc = machine.coordinator.cpu[1].state.regs.PC;
                    uint8_t mbytes[16] = {0};
                    if (mpc >= 0xFF0000u) {
                        for (int b = 0; b < 16; b++) mbytes[b] = g_ram[(mpc + b) & 0xFFFFu];
                    } else if (mpc < sizeof(machine.devices.bios)) {
                        for (int b = 0; b < 16; b++) mbytes[b] = machine.devices.bios[(mpc + b) & 0x1FFFFu];
                    }
                    uint8_t sbytes[16] = {0};
                    for (int b = 0; b < 16; b++) sbytes[b] = machine.devices.prg[(spc + b) & 0x7FFFFu];

                    snprintf(msg, sizeof(msg),
                             "FRAME ERROR at frame %llu: res=%d, last_cpu=%u, last_res=%d, "
                             "MainPC=0x%06X, SubPC=0x%06X, Z80_pc=0x%04X, Z80_res=%d, CDD_status=%d\n"
                             "   Scheduler: waits=%llu, wait_addr=0x%06X, wait_cpu=%u, wait_res=%d\n"
                             "   Main regs: D0=%08X D1=%08X D2=%08X A0=%08X A1=%08X A7=%08X SR=%04X fault=%d faddr=0x%06X\n"
                             "   Sub  regs: D0=%08X D1=%08X D2=%08X A0=%08X A1=%08X A7=%08X SR=%04X fault=%d faddr=0x%06X\n"
                             "   GateArray: mode=0x%02X, flg=[%02X,%02X], cmd0=%04X, stat0=%04X, irq_p=%02X, irq_m=%02X\n"
                             "   Main code at MainPC: %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X\n"
                             "   Sub  code at SubPC:  %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X",
                             (unsigned long long)machine.frames, res,
                             machine.coordinator.last_cpu, machine.coordinator.last_result,
                             mpc, spc, machine.z80.state.pc, machine.z80.result, machine.devices.drive.status,
                             (unsigned long long)machine.coordinator.waits,
                             machine.coordinator.wait_address,
                             machine.coordinator.wait_cpu,
                             machine.coordinator.wait_result,
                             machine.coordinator.cpu[0].state.regs.D[0],
                             machine.coordinator.cpu[0].state.regs.D[1],
                             machine.coordinator.cpu[0].state.regs.D[2],
                             machine.coordinator.cpu[0].state.regs.A[0],
                             machine.coordinator.cpu[0].state.regs.A[1],
                             machine.coordinator.cpu[0].state.regs.A[7],
                             machine.coordinator.cpu[0].state.regs.SR,
                             machine.coordinator.cpu[0].state.fault,
                             machine.coordinator.cpu[0].state.fault_address,
                             machine.coordinator.cpu[1].state.regs.D[0],
                             machine.coordinator.cpu[1].state.regs.D[1],
                             machine.coordinator.cpu[1].state.regs.D[2],
                             machine.coordinator.cpu[1].state.regs.A[0],
                             machine.coordinator.cpu[1].state.regs.A[1],
                             machine.coordinator.cpu[1].state.regs.A[7],
                             machine.coordinator.cpu[1].state.regs.SR,
                             machine.coordinator.cpu[1].state.fault,
                             machine.coordinator.cpu[1].state.fault_address,
                             machine.devices.memory_mode,
                             machine.devices.flags[0], machine.devices.flags[1],
                             machine.devices.command[0], machine.devices.status[0],
                             machine.devices.irq_pending, machine.devices.irq_mask,
                             mbytes[0], mbytes[1], mbytes[2], mbytes[3], mbytes[4], mbytes[5],
                             mbytes[6], mbytes[7], mbytes[8], mbytes[9], mbytes[10], mbytes[11],
                             sbytes[0], sbytes[1], sbytes[2], sbytes[3], sbytes[4], sbytes[5],
                             sbytes[6], sbytes[7], sbytes[8], sbytes[9], sbytes[10], sbytes[11]);
                    log_debug(msg);
                    error_logged = 1;
                } else if (machine.frames - last_logged_frame >= 60) {
                    char msg[512];
                    snprintf(msg, sizeof(msg),
                             "Frame %llu: MainPC=0x%06X, SubPC=0x%06X, SubRun=%d, CDD=%d, mode=0x%02X, flg=[%02X,%02X], cmd0=%04X, stat0=%04X, irq_p=%02X, irq_m=%02X\n"
                             "   Main regs: D0=%08X D1=%08X A0=%08X A1=%08X A7=%08X SR=%04X\n"
                             "   Sub  regs: D0=%08X D1=%08X A0=%08X A1=%08X A7=%08X SR=%04X\n"
                             "   Sub at SubPC: %02X %02X %02X %02X %02X %02X %02X %02X",
                             (unsigned long long)machine.frames,
                             machine.coordinator.cpu[0].state.regs.PC,
                             machine.coordinator.cpu[1].state.regs.PC,
                             segacd_sub_runnable(&machine.devices),
                             machine.devices.drive.status,
                             machine.devices.memory_mode,
                             machine.devices.flags[0],
                             machine.devices.flags[1],
                             machine.devices.command[0],
                             machine.devices.status[0],
                             machine.devices.irq_pending,
                             machine.devices.irq_mask,
                             machine.coordinator.cpu[0].state.regs.D[0],
                             machine.coordinator.cpu[0].state.regs.D[1],
                             machine.coordinator.cpu[0].state.regs.A[0],
                             machine.coordinator.cpu[0].state.regs.A[1],
                             machine.coordinator.cpu[0].state.regs.A[7],
                             machine.coordinator.cpu[0].state.regs.SR,
                             machine.coordinator.cpu[1].state.regs.D[0],
                             machine.coordinator.cpu[1].state.regs.D[1],
                             machine.coordinator.cpu[1].state.regs.A[0],
                             machine.coordinator.cpu[1].state.regs.A[1],
                             machine.coordinator.cpu[1].state.regs.A[7],
                             machine.coordinator.cpu[1].state.regs.SR,
                             machine.devices.prg[machine.coordinator.cpu[1].state.regs.PC & 0x7FFFF],
                             machine.devices.prg[(machine.coordinator.cpu[1].state.regs.PC + 1) & 0x7FFFF],
                             machine.devices.prg[(machine.coordinator.cpu[1].state.regs.PC + 2) & 0x7FFFF],
                             machine.devices.prg[(machine.coordinator.cpu[1].state.regs.PC + 3) & 0x7FFFF],
                             machine.devices.prg[(machine.coordinator.cpu[1].state.regs.PC + 4) & 0x7FFFF],
                             machine.devices.prg[(machine.coordinator.cpu[1].state.regs.PC + 5) & 0x7FFFF],
                             machine.devices.prg[(machine.coordinator.cpu[1].state.regs.PC + 6) & 0x7FFFF],
                             machine.devices.prg[(machine.coordinator.cpu[1].state.regs.PC + 7) & 0x7FFFF]);
                    log_debug(msg);
                    last_logged_frame = machine.frames;
                }
            }
        } else {
            accumulator = 0.0;
        }

        // Renderizado del fotograma actual a la frecuencia nativa seleccionada (60 / 144 / 240 / 360 Hz)
        if (presentation) {
            unsigned game_w = machine.width ? machine.width : 256;
            unsigned game_h = machine.height ? machine.height : 224;
            unsigned frame_w = game_w, frame_h = game_h, pitch = GVDP_MAX_WIDTH * sizeof(uint32_t);
            const uint32_t *pixels = widescreen ?
                segacd_widescreen_frame(widescreen, &frame_w, &frame_h, &pitch) :
                &machine.pixels[0][0];

            if (pixels) {
                segacd_presentation_present(presentation, pixels, (int)frame_w, (int)frame_h, (int)pitch);
            }
        }

        // Sincronizacion de refresco para la tasa de Hz objetivo (60 / 144 / 240 / 360 Hz)
        target_render_time += render_interval;
        uint64_t now = SDL_GetPerformanceCounter();
        if (now < target_render_time) {
            uint64_t diff = target_render_time - now;
            Uint32 ms_to_sleep = (Uint32)(diff * 1000 / freq);
            if (ms_to_sleep > 1) {
                SDL_Delay(ms_to_sleep - 1);
            }
            while (SDL_GetPerformanceCounter() < target_render_time) {
                YieldProcessor();
            }
        } else {
            target_render_time = now;
        }
    }

    // 9. Guardado y limpieza al salir
    segacd_backup_store(backup_path, machine.devices.backup);

    if (widescreen) segacd_widescreen_destroy(widescreen);
    if (presentation) segacd_presentation_destroy(presentation);
    if (pad) SDL_GameControllerClose(pad);
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    if (audio) segacd_native_audio_destroy(audio);
    segacd_machine_close(&machine);
    segacd_image_close(image);
    SDL_Quit();

    return 0;
}
