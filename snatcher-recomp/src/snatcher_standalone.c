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
extern void snatcher_justifier_update_mouse(int window_x, int window_y, int win_w, int win_h);
extern void snatcher_justifier_button_down(int button);
extern void snatcher_justifier_button_up(int button);

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
    uint16_t mask = 0;
    if (k[SDL_SCANCODE_UP])     mask |= GPAD_UP;
    if (k[SDL_SCANCODE_DOWN])   mask |= GPAD_DOWN;
    if (k[SDL_SCANCODE_LEFT])   mask |= GPAD_LEFT;
    if (k[SDL_SCANCODE_RIGHT])  mask |= GPAD_RIGHT;
    if (k[SDL_SCANCODE_Z] || k[SDL_SCANCODE_SPACE]) mask |= GPAD_A;
    if (k[SDL_SCANCODE_X])      mask |= GPAD_B;
    if (k[SDL_SCANCODE_C])      mask |= GPAD_C;
    if (k[SDL_SCANCODE_RETURN]) mask |= GPAD_START;
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
    OPENFILENAMEA ofn;
    memset(&ofn, 0, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrTitle = title;
    ofn.lpstrFilter = filter;
    ofn.lpstrFile = out_path;
    ofn.nMaxFile = (DWORD)max_len;
    ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
    return GetOpenFileNameA(&ofn);
}
extern uint8_t g_ram[0x10000];

int main(int argc, char **argv) {
    log_debug("=== Snatcher Recomp Starting ===");
    char bios_path[MAX_PATH] = { 0 };
    char disc_path[MAX_PATH] = { 0 };
    char backup_path[MAX_PATH] = { 0 };
    char settings_path[MAX_PATH] = { 0 };
    int max_frames = 0;

    for (int i = 1; i < argc; ++i) {
        if (i + 1 < argc && !strcmp(argv[i], "--bios"))     strncpy(bios_path, argv[++i], sizeof(bios_path) - 1);
        else if (i + 1 < argc && !strcmp(argv[i], "--disc")) strncpy(disc_path, argv[++i], sizeof(disc_path) - 1);
        else if (i + 1 < argc && !strcmp(argv[i], "--backup")) strncpy(backup_path, argv[++i], sizeof(backup_path) - 1);
        else if (i + 1 < argc && !strcmp(argv[i], "--settings")) strncpy(settings_path, argv[++i], sizeof(settings_path) - 1);
        else if (i + 1 < argc && !strcmp(argv[i], "--max-frames")) max_frames = atoi(argv[++i]);
    }

    // 1. Deteccion automatica de la imagen de disco de Snatcher
    log_debug("Step 1: checking disc...");
    if (disc_path[0] == '\0') {
        const char *disc_candidates[] = {
            "disc/snatcher.sgcd",
            "snatcher-recomp/disc/snatcher.sgcd",
            "../disc/snatcher.sgcd",
            "../../disc/snatcher.sgcd",
            "../../../disc/snatcher.sgcd",
            "../../snatcher-recomp/disc/snatcher.sgcd",
            "../../../snatcher-recomp/disc/snatcher.sgcd",
            "G:/Proyectos/sega megadrive/snatcher-recomp/disc/snatcher.sgcd",
            "G:/Proyectos/sega megadrive/disc/snatcher.sgcd",
            "disc/SNATCHER.CUE",
            "snatcher-recomp/disc/SNATCHER.CUE",
            "../disc/SNATCHER.CUE",
            "../../disc/SNATCHER.CUE",
            "../../../disc/SNATCHER.CUE",
            "snatcher.sgcd",
            NULL
        };
        for (int i = 0; disc_candidates[i] != NULL; i++) {
            if (file_exists_and_size(disc_candidates[i], NULL)) {
                strncpy(disc_path, disc_candidates[i], sizeof(disc_path) - 1);
                break;
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

    // Si no se encuentra, abrir selector de archivos
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

    snprintf(buf, sizeof(buf), "BIOS path resolved: [%s]", bios_path);
    log_debug(buf);

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
        audio_set_master_volume(100);
    }

    // 7. Creacion de la ventana de juego
    log_debug("Step 7: Creating SDL window...");
    int win_w = 1280;
    int win_h = 720;
    SDL_Window *window = SDL_CreateWindow(
        "Snatcher (Mega-CD) — Native PC Port [Español]",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        win_w, win_h,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI
    );
    if (!window) {
        snprintf(buf, sizeof(buf), "SDL_CreateWindow failed: %s", SDL_GetError());
        log_debug(buf);
        MessageBoxA(NULL, buf, "Error Ventana", MB_ICONERROR);
        return 2;
    }
    log_debug("SDL window created OK.");

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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

    SegaCDPresentation *presentation = segacd_presentation_create(window, renderer, settings_path, 0);
    if (!presentation) {
        log_debug("segacd_presentation_create failed!");
    } else {
        log_debug("Presentation created OK.");
    }

    // Mando de juego
    SDL_GameController *pad = NULL;
    for (int i = 0; i < SDL_NumJoysticks(); ++i) {
        if (SDL_IsGameController(i)) {
            pad = SDL_GameControllerOpen(i);
            break;
        }
    }

    // Modo Panorámico
    widescreen = segacd_widescreen_create(&machine, segacd_standalone_program());
    if (widescreen) {
        segacd_widescreen_prepare(widescreen, 426); // Relación 16:9 (320*16/9 ≈ 426)
    }

    snatcher_justifier_set_resolution(win_w, win_h);

    // 8. Bucle principal de juego
    int quit = 0;
    uint64_t freq = SDL_GetPerformanceFrequency();
    uint64_t target = SDL_GetPerformanceCounter();

    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
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
                snatcher_justifier_update_mouse(event.motion.x, event.motion.y, win_w, win_h);
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                snatcher_justifier_button_down(event.button.button);
            } else if (event.type == SDL_MOUSEBUTTONUP) {
                snatcher_justifier_button_up(event.button.button);
            }

            if (presentation && segacd_presentation_handle_event(presentation, &event)) {
                continue;
            }
        }

        // Lectura de mandos
        uint16_t buttons = keyboard_pad() | controller_pad(pad);
        segacd_machine_pad(&machine, 0, buttons);

        // Ejecutar un fotograma nativo de Mega-CD
        M68kStepResult res = segacd_machine_run_frame(&machine);
        if (max_frames > 0 && machine.frames >= (uint64_t)max_frames) {
            quit = 1;
        }
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

        // Renderizado del fotograma
        if (presentation) {
            unsigned frame_w = 320, frame_h = 224, pitch = GVDP_MAX_WIDTH * sizeof(uint32_t);
            const uint32_t *pixels = widescreen ?
                segacd_widescreen_frame(widescreen, &frame_w, &frame_h, &pitch) :
                &machine.pixels[0][0];

            if (pixels) {
                segacd_presentation_present(presentation, pixels, (int)frame_w, (int)frame_h, (int)pitch);
            }
        }

        // Sincronizacion de refresco (60 Hz NTSC)
        target += freq / 60;
        uint64_t now = SDL_GetPerformanceCounter();
        if (now < target) {
            SDL_Delay((Uint32)((target - now) * 1000 / freq));
        } else {
            target = now;
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
