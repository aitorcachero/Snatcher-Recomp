/* =============================================================================
 * SNATCHER (Mega-CD) — Modern Setup & Configuration Launcher
 * Estilo visual moderno inspirado en Sega Rally Revo / Recomp Modern UI
 * Configurado para ejecutarse a Pantalla Completa con Escalado Adaptativo
 * ============================================================================= */

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_syswm.h>
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

#include <windows.h>
#include <commdlg.h>
#include <stdio.h>
#include <string.h>
#include <string>

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
    int color_mode;       // 0: Raw original, 1: As on a TV
} SnatcherLauncherConfig;

static UINT_PTR CALLBACK BrowseHookProc(HWND hdlg, UINT uiMsg, WPARAM wParam, LPARAM lParam) {
    if (uiMsg == WM_INITDIALOG) {
        HWND hParent = GetParent(hdlg);
        HWND target = hParent ? hParent : hdlg;
        SetWindowPos(target, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
        BringWindowToTop(target);
        SetForegroundWindow(target);
        SetActiveWindow(target);
    }
    return 0;
}

static bool prompt_browse_disc(SDL_Window *window, char *out_path, size_t max_len) {
    HWND hwnd = NULL;
    if (window) {
        SDL_SysWMinfo wmInfo;
        SDL_VERSION(&wmInfo.version);
        if (SDL_GetWindowWMInfo(window, &wmInfo)) {
            hwnd = wmInfo.info.win.window;
        }
    }
    if (!hwnd) {
        hwnd = GetActiveWindow();
        if (!hwnd) hwnd = GetForegroundWindow();
    }

    // Deshabilitar la ventana principal para bloquear toda interacción mientras el diálogo esté abierto
    if (hwnd) {
        EnableWindow(hwnd, FALSE);
    }

    char file_buf[MAX_PATH] = { 0 };
    if (out_path && out_path[0]) {
        strncpy(file_buf, out_path, sizeof(file_buf) - 1);
    }

    OPENFILENAMEA ofn;
    memset(&ofn, 0, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrTitle = "Selecciona la imagen de Snatcher (.sgcd, .cue, .bin)";
    ofn.lpstrFilter = "Imagenes Sega CD (*.sgcd;*.cue;*.bin)\0*.sgcd;*.cue;*.bin\0Todos los archivos (*.*)\0*.*\0";
    ofn.lpstrFile = file_buf;
    ofn.nMaxFile = (DWORD)sizeof(file_buf);
    ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_EXPLORER | OFN_NOCHANGEDIR | OFN_ENABLEHOOK | OFN_ENABLESIZING;
    ofn.lpfnHook = BrowseHookProc;

    BOOL ok = GetOpenFileNameA(&ofn);

    // Reactivar la ventana principal y devolverle el foco
    if (hwnd) {
        EnableWindow(hwnd, TRUE);
        SetForegroundWindow(hwnd);
        SetActiveWindow(hwnd);
    }

    if (ok && file_buf[0]) {
        strncpy(out_path, file_buf, max_len - 1);
        out_path[max_len - 1] = '\0';
        return true;
    }
    return false;
}

static GLuint load_texture_from_bmp(const char *path, int *out_w, int *out_h) {
    SDL_Surface *surface = SDL_LoadBMP(path);
    if (!surface) return 0;

    GLuint tex_id = 0;
    glGenTextures(1, &tex_id);
    glBindTexture(GL_TEXTURE_2D, tex_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    GLenum format = GL_BGR;
    if (surface->format->BytesPerPixel == 4) {
        format = GL_BGRA;
    }
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, format, GL_UNSIGNED_BYTE, surface->pixels);

    if (out_w) *out_w = surface->w;
    if (out_h) *out_h = surface->h;

    SDL_FreeSurface(surface);
    return tex_id;
}

extern "C" int run_snatcher_modern_launcher(char *disc_path_io, size_t disc_path_cap, SnatcherLauncherConfig *cfg_out) {
    // 1. Inicializar configuración inicial desde settings.toml si existe
    int fullscreen = 1;
    int window_scale = 3;
    int widescreen = 1;
    int linear_filter = 3; // 0: Sharp, 1: Smooth, 2: CRT Scanlines, 3: EPX Scale2x (Texto HD)
    int volume = 100;
    int mouse_enabled = 1;
    int refresh_rate = 0; // 0: Auto (adapta a los hercios del monitor)
    int vsync = 1; // 1: VSync activado
    int integer_scaling = 0; // 0: Off, 1: On
    int color_mode = 1; // 1: As on a TV (cálido CRT)

    FILE *fset = fopen("settings.toml", "r");
    if (fset) {
        char line[256];
        while (fgets(line, sizeof(line), fset)) {
            int v = 0;
            if (sscanf(line, "fullscreen = %d", &v) == 1) fullscreen = v;
            else if (sscanf(line, "window_scale = %d", &v) == 1) window_scale = v;
            else if (sscanf(line, "widescreen = %d", &v) == 1) widescreen = v;
            else if (sscanf(line, "view_mode = %d", &v) == 1) widescreen = (v != 0);
            else if (sscanf(line, "vsync = %d", &v) == 1) vsync = v;
            else if (sscanf(line, "filter = %d", &v) == 1) linear_filter = v;
            else if (sscanf(line, "linear_filter = %d", &v) == 1) {
                if (linear_filter < 2) linear_filter = v;
            }
            else if (sscanf(line, "integer_scaling = %d", &v) == 1) integer_scaling = v;
            else if (sscanf(line, "color_mode = %d", &v) == 1) color_mode = v;
            else if (sscanf(line, "volume = %d", &v) == 1) volume = v;
            else if (sscanf(line, "mouse_enabled = %d", &v) == 1) mouse_enabled = v;
            else if (sscanf(line, "refresh_rate = %d", &v) == 1) refresh_rate = v;
        }
        fclose(fset);
    }

    // 2. Obtener resolución del escritorio y crear ventana en PANTALLA COMPLETA
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_DisplayMode dm;
    if (SDL_GetDesktopDisplayMode(0, &dm) != 0) {
        dm.w = 1920;
        dm.h = 1080;
    }

    int win_w = dm.w;
    int win_h = dm.h;

    SDL_Window *window = SDL_CreateWindow(
        "Snatcher — Modern PC Launcher",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        win_w, win_h,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_ALLOW_HIGHDPI
    );
    if (!window) {
        // Respaldo sin fullscreen si fallara el modo exclusivo
        window = SDL_CreateWindow(
            "Snatcher — Modern PC Launcher",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            1280, 720,
            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI
        );
    }
    if (!window) return 2;

    SDL_GetWindowSize(window, &win_w, &win_h);

    int detected_hz = (dm.refresh_rate > 0) ? dm.refresh_rate : 60;
    int disp_idx = SDL_GetWindowDisplayIndex(window);
    if (disp_idx >= 0 && SDL_GetCurrentDisplayMode(disp_idx, &dm) == 0 && dm.refresh_rate > 0) {
        detected_hz = dm.refresh_rate;
    }

    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1); // Activar VSync

    SDL_Cursor *cursor_hand = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
    SDL_Cursor *cursor_arrow = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);

    // Factor de escalado de interfaz relativo a 1080p
    float scale = (float)win_h / 1080.0f;
    if (scale < 0.80f) scale = 0.80f;
    if (scale > 2.50f) scale = 2.50f;

    // 3. Inicializar Dear ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
    io.IniFilename = NULL; // No generar imgui.ini

    // Cargar tipografía moderna con escalado de alta definición
    ImFont *font_title = NULL;
    ImFont *font_large = NULL;
    ImFont *font_bold = NULL;
    ImFont *font_regular = NULL;
    ImFont *font_small = NULL;

    const char *bold_candidates[] = {
        "assets/fonts/LatoLatin-Bold.ttf",
        "snatcher-recomp/assets/fonts/LatoLatin-Bold.ttf",
        "release_pkg/Snatcher-Recomp-v1.0.1-Windows-x64/assets/fonts/LatoLatin-Bold.ttf",
        "release_pkg/Snatcher-Recomp-v1.0.0-Windows-x64/assets/fonts/LatoLatin-Bold.ttf",
        "../assets/fonts/LatoLatin-Bold.ttf",
        NULL
    };
    const char *reg_candidates[] = {
        "assets/fonts/LatoLatin-Regular.ttf",
        "snatcher-recomp/assets/fonts/LatoLatin-Regular.ttf",
        "release_pkg/Snatcher-Recomp-v1.0.1-Windows-x64/assets/fonts/LatoLatin-Regular.ttf",
        "release_pkg/Snatcher-Recomp-v1.0.0-Windows-x64/assets/fonts/LatoLatin-Regular.ttf",
        "../assets/fonts/LatoLatin-Regular.ttf",
        NULL
    };

    const char *found_bold = NULL;
    for (int i = 0; bold_candidates[i]; i++) {
        if (GetFileAttributesA(bold_candidates[i]) != INVALID_FILE_ATTRIBUTES) {
            found_bold = bold_candidates[i];
            break;
        }
    }

    const char *found_reg = NULL;
    for (int i = 0; reg_candidates[i]; i++) {
        if (GetFileAttributesA(reg_candidates[i]) != INVALID_FILE_ATTRIBUTES) {
            found_reg = reg_candidates[i];
            break;
        }
    }

    if (found_bold) {
        font_title = io.Fonts->AddFontFromFileTTF(found_bold, 40.0f * scale);
        font_large = io.Fonts->AddFontFromFileTTF(found_bold, 28.0f * scale);
        font_bold  = io.Fonts->AddFontFromFileTTF(found_bold, 22.0f * scale);
    }
    if (found_reg) {
        font_regular = io.Fonts->AddFontFromFileTTF(found_reg, 19.0f * scale);
        font_small   = io.Fonts->AddFontFromFileTTF(found_reg, 15.0f * scale);
    }
    if (!font_regular) {
        io.Fonts->AddFontDefault();
    }

    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init("#version 330");

    // 4. Cargar textura del póster vertical de Snatcher
    int poster_w = 0, poster_h = 0;
    const char *poster_candidates[] = {
        "assets/img/snatcher_poster.bmp",
        "snatcher-recomp/assets/img/snatcher_poster.bmp",
        "release_pkg/Snatcher-Recomp-v1.0.1-Windows-x64/assets/img/snatcher_poster.bmp",
        "release_pkg/Snatcher-Recomp-v1.0.0-Windows-x64/assets/img/snatcher_poster.bmp",
        "../assets/img/snatcher_poster.bmp",
        NULL
    };
    GLuint poster_tex = 0;
    for (int i = 0; poster_candidates[i]; i++) {
        if (GetFileAttributesA(poster_candidates[i]) != INVALID_FILE_ATTRIBUTES) {
            poster_tex = load_texture_from_bmp(poster_candidates[i], &poster_w, &poster_h);
            if (poster_tex) break;
        }
    }

    // 5. Estilo visual: Paleta moderna Dark Slate + Vibrant Orange (Estilo Sega Rally Revo)
    ImGuiStyle &style = ImGui::GetStyle();
    style.WindowRounding    = 0.0f;
    style.FrameRounding     = 6.0f * scale;
    style.ItemSpacing       = ImVec2(12.0f * scale, 12.0f * scale);
    style.ItemInnerSpacing  = ImVec2(10.0f * scale, 8.0f * scale);
    style.ScrollbarRounding = 4.0f * scale;
    style.GrabRounding      = 5.0f * scale;
    style.FramePadding      = ImVec2(12.0f * scale, 8.0f * scale);

    ImVec4 *colors = style.Colors;
    colors[ImGuiCol_WindowBg]             = ImVec4(0.047f, 0.071f, 0.122f, 1.00f); // #0C121F Deep Navy
    colors[ImGuiCol_ChildBg]              = ImVec4(0.063f, 0.094f, 0.157f, 1.00f); // #101828 Slate Card
    colors[ImGuiCol_Border]               = ImVec4(0.141f, 0.200f, 0.314f, 1.00f);
    colors[ImGuiCol_FrameBg]              = ImVec4(0.090f, 0.133f, 0.220f, 1.00f);
    colors[ImGuiCol_FrameBgHovered]       = ImVec4(0.125f, 0.180f, 0.290f, 1.00f);
    colors[ImGuiCol_FrameBgActive]        = ImVec4(0.160f, 0.224f, 0.353f, 1.00f);
    colors[ImGuiCol_TitleBg]              = ImVec4(0.047f, 0.071f, 0.122f, 1.00f);
    colors[ImGuiCol_TitleBgActive]        = ImVec4(0.047f, 0.071f, 0.122f, 1.00f);
    colors[ImGuiCol_CheckMark]            = ImVec4(1.000f, 0.463f, 0.000f, 1.00f); // Vibrant Orange
    colors[ImGuiCol_SliderGrab]           = ImVec4(1.000f, 0.463f, 0.000f, 1.00f);
    colors[ImGuiCol_SliderGrabActive]     = ImVec4(1.000f, 0.600f, 0.200f, 1.00f);
    colors[ImGuiCol_Button]               = ImVec4(0.094f, 0.141f, 0.231f, 1.00f);
    colors[ImGuiCol_ButtonHovered]        = ImVec4(0.137f, 0.200f, 0.322f, 1.00f);
    colors[ImGuiCol_ButtonActive]         = ImVec4(0.180f, 0.259f, 0.412f, 1.00f);
    colors[ImGuiCol_Header]               = ImVec4(1.000f, 0.463f, 0.000f, 0.25f);
    colors[ImGuiCol_HeaderHovered]        = ImVec4(1.000f, 0.463f, 0.000f, 0.40f);
    colors[ImGuiCol_HeaderActive]         = ImVec4(1.000f, 0.463f, 0.000f, 0.60f);
    colors[ImGuiCol_Text]                 = ImVec4(0.950f, 0.960f, 0.980f, 1.00f);
    colors[ImGuiCol_TextDisabled]         = ImVec4(0.500f, 0.580f, 0.680f, 1.00f);

    // Bucle interactivo del lanzador
    int active_tab = 0; // 0: Play, 1: Picture, 2: Controls, 3: Audio
    int active_preset = (widescreen && window_scale == 3) ? 0 : ((widescreen && window_scale == 2) ? 1 : ((!widescreen) ? 2 : 3));
    bool running = true;
    int result_action = 0; // 0: Launch, 1: Quit

    char current_disc[MAX_PATH] = { 0 };
    if (disc_path_io && disc_path_io[0]) {
        strncpy(current_disc, disc_path_io, sizeof(current_disc) - 1);
    }

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT) {
                running = false;
                result_action = 1; // Quit
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                    running = false;
                    result_action = 1; // Quit con Esc
                } else if (event.key.keysym.scancode == SDL_SCANCODE_RETURN || event.key.keysym.scancode == SDL_SCANCODE_KP_ENTER) {
                    running = false;
                    result_action = 0; // Play con Enter
                } else if (event.key.keysym.scancode == SDL_SCANCODE_F11 ||
                           (event.key.keysym.scancode == SDL_SCANCODE_RETURN && (event.key.keysym.mod & KMOD_ALT))) {
                    Uint32 wflags = SDL_GetWindowFlags(window);
                    if (wflags & SDL_WINDOW_FULLSCREEN_DESKTOP) {
                        SDL_SetWindowFullscreen(window, 0);
                        SDL_SetWindowSize(window, (int)(1280 * scale), (int)(720 * scale));
                        SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
                    } else {
                        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
                    }
                }
            } else if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED) {
                win_w = event.window.data1;
                win_h = event.window.data2;
            }
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        if (io.DisplaySize.x > 0 && io.DisplaySize.y > 0) {
            win_w = (int)io.DisplaySize.x;
            win_h = (int)io.DisplaySize.y;
        }

        // Ventana principal que cubre todo el lienzo de pantalla completa
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2((float)win_w, (float)win_h));
        ImGui::Begin("LauncherMain", NULL,
                     ImGuiWindowFlags_NoTitleBar |
                     ImGuiWindowFlags_NoResize |
                     ImGuiWindowFlags_NoMove |
                     ImGuiWindowFlags_NoScrollbar |
                     ImGuiWindowFlags_NoBringToFrontOnFocus);

        ImDrawList *draw = ImGui::GetWindowDrawList();

        // ── Columna Izquierda: Póster de Snatcher (proporcional, ~32% ancho) ──
        float left_w = (float)win_w * 0.32f;
        if (left_w < 380.0f * scale) left_w = 380.0f * scale;
        if (left_w > 640.0f * scale) left_w = 640.0f * scale;

        ImGui::BeginChild("LeftBanner", ImVec2(left_w, (float)win_h), false, ImGuiWindowFlags_NoScrollbar);
        if (poster_tex && poster_w > 0 && poster_h > 0) {
            // Ajuste de aspecto perfecto sin deformar la imagen
            float target_aspect = left_w / (float)win_h;
            float img_aspect = (float)poster_w / (float)poster_h;
            ImVec2 uv0(0.0f, 0.0f);
            ImVec2 uv1(1.0f, 1.0f);
            if (img_aspect > target_aspect) {
                float f = target_aspect / img_aspect;
                float crop = (1.0f - f) * 0.5f;
                uv0.x = crop;
                uv1.x = 1.0f - crop;
            } else {
                float f = img_aspect / target_aspect;
                float crop = (1.0f - f) * 0.5f;
                uv0.y = crop;
                uv1.y = 1.0f - crop;
            }
            ImGui::Image((ImTextureID)(intptr_t)poster_tex, ImVec2(left_w, (float)win_h), uv0, uv1);
        } else {
            // Fondo de degradado elegante si no hay póster cargado
            draw->AddRectFilledMultiColor(ImVec2(0, 0), ImVec2(left_w, (float)win_h),
                                          IM_COL32(14, 24, 45, 255), IM_COL32(20, 38, 70, 255),
                                          IM_COL32(10, 15, 28, 255), IM_COL32(5, 8, 16, 255));
        }

        // Overlay inferior con degradado y tipografía nítida
        float overlay_h = 160.0f * scale;
        draw->AddRectFilledMultiColor(ImVec2(0, win_h - overlay_h), ImVec2(left_w, (float)win_h),
                                      IM_COL32(12, 19, 32, 0), IM_COL32(12, 19, 32, 0),
                                      IM_COL32(12, 19, 32, 250), IM_COL32(12, 19, 32, 250));

        if (font_large) ImGui::PushFont(font_large);
        draw->AddText(ImVec2(28.0f * scale, win_h - 130.0f * scale), IM_COL32(255, 255, 255, 255), "SNATCHER");
        if (font_large) ImGui::PopFont();

        if (font_bold) ImGui::PushFont(font_bold);
        draw->AddText(ImVec2(28.0f * scale, win_h - 85.0f * scale), IM_COL32(255, 130, 0, 255), "Sega Mega-CD — NTSC-U [Español]");
        if (font_bold) ImGui::PopFont();

        if (font_regular) ImGui::PushFont(font_regular);
        draw->AddText(ImVec2(28.0f * scale, win_h - 50.0f * scale), IM_COL32(148, 163, 184, 230), "PC Native Recompilation v1.0.5 • EPX Texto HD • Auto / 60 / 144 / 240 / 360 Hz");
        if (font_regular) ImGui::PopFont();

        ImGui::EndChild();

        // ── Columna Derecha: Interfaz de Configuración Amplia ───────────────
        ImGui::SameLine();
        float pad_x = 36.0f * scale;
        ImGui::SetCursorPosX(left_w + pad_x);
        float right_w = (float)win_w - left_w - pad_x * 1.5f;
        ImGui::BeginChild("RightPanel", ImVec2(right_w, (float)win_h), false, ImGuiWindowFlags_NoScrollbar);

        // Decoración superior: Rayas diagonales naranja estilo Racing / Cyberpunk
        float right_top_x = right_w - (110.0f * scale);
        draw->AddTriangleFilled(ImVec2(left_w + pad_x + right_top_x + 24 * scale, 0),
                                ImVec2(left_w + pad_x + right_top_x + 48 * scale, 0),
                                ImVec2(left_w + pad_x + right_top_x + 12 * scale, 60 * scale), IM_COL32(255, 115, 0, 230));
        draw->AddTriangleFilled(ImVec2(left_w + pad_x + right_top_x + 48 * scale, 0),
                                ImVec2(left_w + pad_x + right_top_x + 12 * scale, 60 * scale),
                                ImVec2(left_w + pad_x + right_top_x - 12 * scale, 60 * scale), IM_COL32(255, 115, 0, 230));
        draw->AddTriangleFilled(ImVec2(left_w + pad_x + right_top_x + 60 * scale, 0),
                                ImVec2(left_w + pad_x + right_top_x + 84 * scale, 0),
                                ImVec2(left_w + pad_x + right_top_x + 48 * scale, 60 * scale), IM_COL32(255, 140, 0, 230));
        draw->AddTriangleFilled(ImVec2(left_w + pad_x + right_top_x + 84 * scale, 0),
                                ImVec2(left_w + pad_x + right_top_x + 48 * scale, 60 * scale),
                                ImVec2(left_w + pad_x + right_top_x + 24 * scale, 60 * scale), IM_COL32(255, 140, 0, 230));

        ImGui::Dummy(ImVec2(0, 14.0f * scale));

        // Título principal en alta resolución
        if (font_title) ImGui::PushFont(font_title);
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "Snatcher");
        if (font_title) ImGui::PopFont();

        if (font_regular) ImGui::PushFont(font_regular);
        ImGui::TextColored(ImVec4(0.65f, 0.72f, 0.82f, 1.0f), "Listo. Pulsa Jugar o la tecla Intro (Enter).");
        if (font_regular) ImGui::PopFont();

        ImGui::Dummy(ImVec2(0, 10.0f * scale));

        // ── Pestañas de Navegación Estilo Revo (Play, Picture, Controls, Audio) ──
        const char *tabs[] = { "Play", "Picture", "Controls", "Audio" };
        if (font_large) ImGui::PushFont(font_large);
        for (int t = 0; t < 4; t++) {
            if (t > 0) ImGui::SameLine(0, 24.0f * scale);
            bool is_selected = (active_tab == t);
            if (is_selected) {
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.50f, 0.05f, 1.0f));
            } else {
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.70f, 0.76f, 0.85f, 1.0f));
            }

            if (ImGui::Button(tabs[t], ImVec2(0, 36.0f * scale))) {
                active_tab = t;
            }
            ImGui::PopStyleColor();

            // Línea naranja brillante debajo de la pestaña activa
            if (is_selected) {
                ImVec2 bmin = ImGui::GetItemRectMin();
                ImVec2 bmax = ImGui::GetItemRectMax();
                draw->AddLine(ImVec2(bmin.x, bmax.y + 2), ImVec2(bmax.x, bmax.y + 2), IM_COL32(255, 120, 0, 255), 3.0f * scale);
            }
        }
        if (font_large) ImGui::PopFont();

        // Línea divisoria suave horizontal
        ImVec2 sep_pos = ImGui::GetCursorScreenPos();
        draw->AddLine(ImVec2(sep_pos.x, sep_pos.y + 8 * scale), ImVec2(sep_pos.x + right_w - 40.0f * scale, sep_pos.y + 8 * scale), IM_COL32(36, 51, 80, 255), 1.5f);
        ImGui::Dummy(ImVec2(0, 18.0f * scale));

        // ── CONTENIDO: TAB 0: PLAY (JUGAR) ──────────────────────────────────
        if (active_tab == 0) {
            // Fila de Archivo de Juego / Disco
            if (font_bold) ImGui::PushFont(font_bold);
            ImGui::TextColored(ImVec4(0.78f, 0.84f, 0.92f, 1.0f), "Disco del juego (Mega-CD):");
            if (font_bold) ImGui::PopFont();

            if (font_regular) ImGui::PushFont(font_regular);
            float input_w = right_w - 180.0f * scale;
            if (input_w < 300.0f) input_w = 300.0f;
            ImGui::PushItemWidth(input_w);
            ImGui::InputText("##disc_path", current_disc, sizeof(current_disc), ImGuiInputTextFlags_ReadOnly);
            ImGui::PopItemWidth();

            ImGui::SameLine();
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.12f, 0.18f, 0.30f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.0f, 0.46f, 0.0f, 0.8f));
            ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);
            if (ImGui::Button("Examinar...", ImVec2(120.0f * scale, 0))) {
                char picked[MAX_PATH] = { 0 };
                if (prompt_browse_disc(window, picked, sizeof(picked))) {
                    strncpy(current_disc, picked, sizeof(current_disc) - 1);
                }
            }
            ImGui::PopStyleVar();
            ImGui::PopStyleColor(2);

            if (current_disc[0] != '\0') {
                ImGui::TextColored(ImVec4(0.20f, 0.88f, 0.45f, 1.0f), "Disco detectado: Snatcher (Mega-CD Español) - NTSC-U [OK]");
            } else {
                ImGui::TextColored(ImVec4(1.0f, 0.45f, 0.20f, 1.0f), "Aviso: Copia tu imagen a la carpeta disc/ o pulsa Examinar.");
            }
            if (font_regular) ImGui::PopFont();

            ImGui::Dummy(ImVec2(0, 16.0f * scale));

            // Presets "Look" (Moderna, Steam Deck, Original 1994, Personalizado)
            if (font_bold) ImGui::PushFont(font_bold);
            ImGui::TextColored(ImVec4(0.90f, 0.93f, 0.98f, 1.0f), "Aspecto (Look):");
            if (font_bold) ImGui::PopFont();

            struct PresetCard {
                const char *badge;
                const char *title;
                const char *sub1;
                const char *sub2;
            } cards[4] = {
                { "Recomendado", "Moderna", "1920x1080 (16:9)", "Texto HD EPX, Auto Hz" },
                { NULL, "Steam Deck", "1280x800 (16:9)", "Texto HD EPX, 60 Hz" },
                { NULL, "Original 1994", "1280x960 (4:3)", "60 Hz, Píxel Nítido / Retro" },
                { NULL, "Personalizado", "Ajustable", "Configura en Picture o Play" }
            };

            float card_w = 210.0f * scale;
            float card_h = 135.0f * scale;

            for (int i = 0; i < 4; i++) {
                if (i > 0) ImGui::SameLine(0, 16.0f * scale);
                bool sel = (active_preset == i);

                ImGui::PushID(i);
                ImVec2 p_min = ImGui::GetCursorScreenPos();
                ImVec2 p_max = ImVec2(p_min.x + card_w, p_min.y + card_h);

                bool clicked = ImGui::InvisibleButton("##card_btn", ImVec2(card_w, card_h));
                bool card_hovered = ImGui::IsItemHovered();
                if (card_hovered) {
                    ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
                }

                ImU32 bg_col = sel ? IM_COL32(20, 34, 58, 255) : (card_hovered ? IM_COL32(22, 32, 52, 255) : IM_COL32(15, 23, 38, 255));
                ImU32 border_col = sel ? IM_COL32(255, 115, 0, 255) : (card_hovered ? IM_COL32(255, 150, 40, 255) : IM_COL32(40, 58, 90, 255));

                draw->AddRectFilled(p_min, p_max, bg_col, 8.0f * scale);
                draw->AddRect(p_min, p_max, border_col, 8.0f * scale, 0, sel ? 2.5f * scale : (card_hovered ? 2.0f * scale : 1.0f));

                if (cards[i].badge) {
                    if (font_small) ImGui::PushFont(font_small);
                    draw->AddText(ImVec2(p_min.x + 14.0f * scale, p_min.y + 12.0f * scale), IM_COL32(255, 120, 0, 255), cards[i].badge);
                    if (font_small) ImGui::PopFont();
                }

                float text_y = cards[i].badge ? 38.0f * scale : 20.0f * scale;
                if (font_bold) ImGui::PushFont(font_bold);
                draw->AddText(ImVec2(p_min.x + 14.0f * scale, p_min.y + text_y), IM_COL32(255, 255, 255, 255), cards[i].title);
                if (font_bold) ImGui::PopFont();

                if (font_regular) ImGui::PushFont(font_regular);
                draw->AddText(ImVec2(p_min.x + 14.0f * scale, p_min.y + text_y + 30.0f * scale), IM_COL32(148, 163, 184, 255), cards[i].sub1);
                if (font_regular) ImGui::PopFont();

                if (font_small) ImGui::PushFont(font_small);
                draw->AddText(ImVec2(p_min.x + 14.0f * scale, p_min.y + text_y + 54.0f * scale), IM_COL32(100, 116, 139, 255), cards[i].sub2);
                if (font_small) ImGui::PopFont();

                if (clicked) {
                    active_preset = i;
                    if (i == 0) { // Modern
                        fullscreen = 1; window_scale = 3; widescreen = 1; linear_filter = 3; vsync = 1; refresh_rate = 0; integer_scaling = 0; color_mode = 1;
                    } else if (i == 1) { // Steam Deck
                        fullscreen = 1; window_scale = 2; widescreen = 1; linear_filter = 3; vsync = 1; refresh_rate = 60; integer_scaling = 0; color_mode = 1;
                    } else if (i == 2) { // Original 1994
                        fullscreen = 0; window_scale = 3; widescreen = 0; linear_filter = 0; vsync = 1; refresh_rate = 60; integer_scaling = 1; color_mode = 1;
                    }
                }
                ImGui::PopID();
            }

            ImGui::Dummy(ImVec2(0, 18.0f * scale));

            // Mejoras / Opciones de Juego
            if (font_bold) ImGui::PushFont(font_bold);
            ImGui::TextColored(ImVec4(0.90f, 0.93f, 0.98f, 1.0f), "Mejoras y Opciones:");
            if (font_bold) ImGui::PopFont();

            // Hack Panorámico 16:9
            if (font_regular) ImGui::PushFont(font_regular);
            ImGui::TextColored(ImVec4(0.75f, 0.80f, 0.90f, 1.0f), "Hack Panorámico 16:9:");
            ImGui::SameLine(280.0f * scale);
            if (widescreen) {
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.45f, 0.0f, 0.95f));
                ImGui::Button("Activado (recomendado)##ws_on", ImVec2(0, 36.0f * scale));
                ImGui::PopStyleColor();
                ImGui::SameLine();
                if (ImGui::Button("Desactivado##ws_off", ImVec2(0, 36.0f * scale))) { widescreen = 0; active_preset = 3; }
            } else {
                if (ImGui::Button("Activado##ws_on", ImVec2(0, 36.0f * scale))) { widescreen = 1; active_preset = 3; }
                ImGui::SameLine();
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.20f, 0.28f, 0.42f, 0.95f));
                ImGui::Button("Desactivado##ws_off", ImVec2(0, 36.0f * scale));
                ImGui::PopStyleColor();
            }
            ImGui::TextColored(ImVec4(0.55f, 0.63f, 0.74f, 1.0f), "Centra la imagen en 16:9 con relleno cinemático simétrico sin deformar píxeles.");

            ImGui::Dummy(ImVec2(0, 6.0f * scale));

            // Ratón Konami Justifier
            ImGui::TextColored(ImVec4(0.75f, 0.80f, 0.90f, 1.0f), "Ratón Konami Justifier:");
            ImGui::SameLine(280.0f * scale);
            if (mouse_enabled) {
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.45f, 0.0f, 0.95f));
                ImGui::Button("Activado (recomendado)##m_on", ImVec2(0, 36.0f * scale));
                ImGui::PopStyleColor();
                ImGui::SameLine();
                if (ImGui::Button("Desactivado##m_off", ImVec2(0, 36.0f * scale))) mouse_enabled = 0;
            } else {
                if (ImGui::Button("Activado##m_on", ImVec2(0, 36.0f * scale))) mouse_enabled = 1;
                ImGui::SameLine();
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.20f, 0.28f, 0.42f, 0.95f));
                ImGui::Button("Desactivado##m_off", ImVec2(0, 36.0f * scale));
                ImGui::PopStyleColor();
            }
            ImGui::TextColored(ImVec4(0.55f, 0.63f, 0.74f, 1.0f), "Apunta y dispara con el ratón de tu PC durante las secuencias de tiroteo de Snatcher.");

            ImGui::Dummy(ImVec2(0, 6.0f * scale));

            // Frecuencia de Refresco / Tasa de Hz (60, 144, 240, 360)
            ImGui::TextColored(ImVec4(0.75f, 0.80f, 0.90f, 1.0f), "Tasa de Refresco (Hz):");
            ImGui::SameLine(280.0f * scale);
            int hz_options[] = { 60, 144, 240, 360, 0 };
            for (int h = 0; h < 5; h++) {
                if (h > 0) ImGui::SameLine(0, 8.0f * scale);
                bool is_cur = (refresh_rate == hz_options[h]);
                char hlabel[48];
                if (hz_options[h] == 0) {
                    snprintf(hlabel, sizeof(hlabel), "Auto (%d Hz)##hz_play_auto", detected_hz);
                } else {
                    snprintf(hlabel, sizeof(hlabel), "%d Hz##hz_play_%d", hz_options[h], hz_options[h]);
                }
                float btn_w = (hz_options[h] == 0) ? 140.0f * scale : 75.0f * scale;
                if (is_cur) {
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.45f, 0.0f, 0.95f));
                    ImGui::Button(hlabel, ImVec2(btn_w, 36.0f * scale));
                    ImGui::PopStyleColor();
                } else {
                    if (ImGui::Button(hlabel, ImVec2(btn_w, 36.0f * scale))) {
                        refresh_rate = hz_options[h];
                        active_preset = 3;
                    }
                }
            }
            ImGui::TextColored(ImVec4(0.55f, 0.63f, 0.74f, 1.0f), "Sincronización nativa de pantalla y ratón: 60Hz estándar, 144/240/360Hz gaming, o Auto (%d Hz de tu monitor).", detected_hz);
            if (font_regular) ImGui::PopFont();
        }

        // ── CONTENIDO: TAB 1: PICTURE (PANTALLA) ────────────────────────────
        else if (active_tab == 1) {
            if (font_large) ImGui::PushFont(font_large);
            ImGui::TextColored(ImVec4(0.90f, 0.93f, 0.98f, 1.0f), "Ajustes de Pantalla (Display & Motion)");
            if (font_large) ImGui::PopFont();
            ImGui::Dummy(ImVec2(0, 6.0f * scale));

            if (font_regular) ImGui::PushFont(font_regular);

            // ── Bloque 1: DISPLAY ──
            if (font_bold) ImGui::PushFont(font_bold);
            ImGui::TextColored(ImVec4(1.0f, 0.50f, 0.05f, 1.0f), "Display");
            if (font_bold) ImGui::PopFont();

            // 1. Fullscreen
            ImGui::Text("Fullscreen (Pantalla completa):");
            ImGui::SameLine(320.0f * scale);
            if (fullscreen) {
                if (ImGui::Button("Off##fs_off", ImVec2(75.0f * scale, 30.0f * scale))) { fullscreen = 0; active_preset = 3; }
                ImGui::SameLine();
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.45f, 0.0f, 0.95f));
                ImGui::Button("On##fs_on", ImVec2(75.0f * scale, 30.0f * scale));
                ImGui::PopStyleColor();
            } else {
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.20f, 0.28f, 0.42f, 0.95f));
                ImGui::Button("Off##fs_off", ImVec2(75.0f * scale, 30.0f * scale));
                ImGui::PopStyleColor();
                ImGui::SameLine();
                if (ImGui::Button("On##fs_on", ImVec2(75.0f * scale, 30.0f * scale))) { fullscreen = 1; active_preset = 3; }
            }

            // 2. VSync
            ImGui::Text("VSync (Sincronización vertical):");
            ImGui::SameLine(320.0f * scale);
            if (vsync) {
                if (ImGui::Button("Off##vs_off", ImVec2(75.0f * scale, 30.0f * scale))) { vsync = 0; active_preset = 3; }
                ImGui::SameLine();
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.45f, 0.0f, 0.95f));
                ImGui::Button("On##vs_on", ImVec2(75.0f * scale, 30.0f * scale));
                ImGui::PopStyleColor();
            } else {
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.20f, 0.28f, 0.42f, 0.95f));
                ImGui::Button("Off##vs_off", ImVec2(75.0f * scale, 30.0f * scale));
                ImGui::PopStyleColor();
                ImGui::SameLine();
                if (ImGui::Button("On##vs_on", ImVec2(75.0f * scale, 30.0f * scale))) { vsync = 1; active_preset = 3; }
            }

            // 3. Aspect
            ImGui::Text("Aspect (Relación de aspecto):");
            ImGui::SameLine(320.0f * scale);
            if (widescreen) {
                if (ImGui::Button("4:3 TV##asp_43", ImVec2(90.0f * scale, 30.0f * scale))) { widescreen = 0; active_preset = 3; }
                ImGui::SameLine();
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.45f, 0.0f, 0.95f));
                ImGui::Button("16:9##asp_169", ImVec2(90.0f * scale, 30.0f * scale));
                ImGui::PopStyleColor();
            } else {
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.20f, 0.28f, 0.42f, 0.95f));
                ImGui::Button("4:3 TV##asp_43", ImVec2(90.0f * scale, 30.0f * scale));
                ImGui::PopStyleColor();
                ImGui::SameLine();
                if (ImGui::Button("16:9##asp_169", ImVec2(90.0f * scale, 30.0f * scale))) { widescreen = 1; active_preset = 3; }
            }

            // 4. Filter
            ImGui::Text("Filter (Filtro gráfico):");
            ImGui::SameLine(320.0f * scale);
            const char *filter_labels[] = { "Sharp (Nítido)", "Smooth (Suave)", "CRT Scanlines", "EPX (Texto HD)" };
            for (int f = 0; f < 4; f++) {
                if (f > 0) ImGui::SameLine();
                bool f_cur = (linear_filter == f);
                float f_w = (f == 3) ? 145.0f * scale : ((f == 2) ? 135.0f * scale : 115.0f * scale);
                if (f_cur) {
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.45f, 0.0f, 0.95f));
                    ImGui::Button(filter_labels[f], ImVec2(f_w, 30.0f * scale));
                    ImGui::PopStyleColor();
                } else {
                    if (ImGui::Button(filter_labels[f], ImVec2(f_w, 30.0f * scale))) {
                        linear_filter = f;
                        active_preset = 3;
                    }
                }
            }

            if (font_small) ImGui::PushFont(font_small);
            if (linear_filter == 3) {
                ImGui::TextColored(ImVec4(0.40f, 0.85f, 0.45f, 1.0f), "Filtro EPX / Scale2x activo: Suavizado inteligente para textos y pixel art en alta resolución sin borrosidad.");
            } else if (linear_filter == 2) {
                ImGui::TextColored(ImVec4(0.85f, 0.75f, 0.40f, 1.0f), "Filtro CRT Scanlines activo: Lineas de barrido analogicas simulando un monitor de tubo clasico.");
            } else if (linear_filter == 1) {
                ImGui::TextColored(ImVec4(0.65f, 0.75f, 0.90f, 1.0f), "Filtro Smooth activo: Interpolacion bilineal suave general.");
            } else {
                ImGui::TextColored(ImVec4(0.65f, 0.75f, 0.90f, 1.0f), "Filtro Sharp activo: Pixeles nitidos retro clasicos 1:1 sin suavizado.");
            }
            if (font_small) ImGui::PopFont();

            // 5. Integer Scaling
            ImGui::Text("Integer scaling (Escalado entero):");
            ImGui::SameLine(320.0f * scale);
            if (integer_scaling) {
                if (ImGui::Button("Off##is_off", ImVec2(75.0f * scale, 30.0f * scale))) { integer_scaling = 0; active_preset = 3; }
                ImGui::SameLine();
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.45f, 0.0f, 0.95f));
                ImGui::Button("On##is_on", ImVec2(75.0f * scale, 30.0f * scale));
                ImGui::PopStyleColor();
            } else {
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.20f, 0.28f, 0.42f, 0.95f));
                ImGui::Button("Off##is_off", ImVec2(75.0f * scale, 30.0f * scale));
                ImGui::PopStyleColor();
                ImGui::SameLine();
                if (ImGui::Button("On##is_on", ImVec2(75.0f * scale, 30.0f * scale))) { integer_scaling = 1; active_preset = 3; }
            }

            // 6. Colours
            ImGui::Text("Colours (Paleta de color):");
            ImGui::SameLine(320.0f * scale);
            if (color_mode) {
                if (ImGui::Button("Raw (Original)##col_raw", ImVec2(130.0f * scale, 30.0f * scale))) { color_mode = 0; active_preset = 3; }
                ImGui::SameLine();
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.45f, 0.0f, 0.95f));
                ImGui::Button("As on a TV (Cálido)##col_tv", ImVec2(165.0f * scale, 30.0f * scale));
                ImGui::PopStyleColor();
            } else {
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.20f, 0.28f, 0.42f, 0.95f));
                ImGui::Button("Raw (Original)##col_raw", ImVec2(130.0f * scale, 30.0f * scale));
                ImGui::PopStyleColor();
                ImGui::SameLine();
                if (ImGui::Button("As on a TV (Cálido)##col_tv", ImVec2(165.0f * scale, 30.0f * scale))) { color_mode = 1; active_preset = 3; }
            }

            // 7. Escala de ventana / Resolución interna
            ImGui::Text("Internal Resolution / Scale:");
            ImGui::SameLine(320.0f * scale);
            const char *scales[] = { "1x (256x224)", "2x (720p)", "3x (1080p)", "4x (1440p 2K)", "5x (2160p 4K)" };
            int cur_scale_idx = window_scale - 1;
            if (cur_scale_idx < 0) cur_scale_idx = 0;
            if (cur_scale_idx > 4) cur_scale_idx = 4;
            ImGui::PushItemWidth(200.0f * scale);
            if (ImGui::Combo("##win_scale", &cur_scale_idx, scales, 5)) {
                window_scale = cur_scale_idx + 1;
                active_preset = 3;
            }
            ImGui::PopItemWidth();

            ImGui::Dummy(ImVec2(0, 8.0f * scale));

            // ── Bloque 2: MOTION ──
            if (font_bold) ImGui::PushFont(font_bold);
            ImGui::TextColored(ImVec4(1.0f, 0.50f, 0.05f, 1.0f), "Motion");
            if (font_bold) ImGui::PopFont();

            // Refresh Rate (Hz) con opción AUTO
            ImGui::Text("Refresh Rate / High Frame Rate:");
            ImGui::SameLine(320.0f * scale);
            int hz_opts_pic[] = { 60, 144, 240, 360, 0 };
            for (int h = 0; h < 5; h++) {
                if (h > 0) ImGui::SameLine();
                bool is_c = (refresh_rate == hz_opts_pic[h]);
                char h_lbl[48];
                if (hz_opts_pic[h] == 0) {
                    snprintf(h_lbl, sizeof(h_lbl), "Auto (%d Hz)##hz_pic_auto", detected_hz);
                } else {
                    snprintf(h_lbl, sizeof(h_lbl), "%d Hz##hz_pic_%d", hz_opts_pic[h], hz_opts_pic[h]);
                }
                float b_w = (hz_opts_pic[h] == 0) ? 140.0f * scale : 75.0f * scale;
                if (is_c) {
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.45f, 0.0f, 0.95f));
                    ImGui::Button(h_lbl, ImVec2(b_w, 30.0f * scale));
                    ImGui::PopStyleColor();
                } else {
                    if (ImGui::Button(h_lbl, ImVec2(b_w, 30.0f * scale))) {
                        refresh_rate = hz_opts_pic[h];
                        active_preset = 3;
                    }
                }
            }
            ImGui::TextColored(ImVec4(0.55f, 0.63f, 0.74f, 1.0f), "La opción Auto sincroniza fotogramas y ratón a la frecuencia nativa detectada de tu monitor (%d Hz).", detected_hz);

            if (font_regular) ImGui::PopFont();
        }

        // ── CONTENIDO: TAB 2: CONTROLS (CONTROLES) ──────────────────────────
        else if (active_tab == 2) {
            if (font_large) ImGui::PushFont(font_large);
            ImGui::TextColored(ImVec4(0.90f, 0.93f, 0.98f, 1.0f), "Mapeo de Mandos y Teclado");
            if (font_large) ImGui::PopFont();
            ImGui::Dummy(ImVec2(0, 8.0f * scale));

            if (font_regular) ImGui::PushFont(font_regular);
            // Detección de mando
            int num_pads = SDL_NumJoysticks();
            if (num_pads > 0) {
                ImGui::TextColored(ImVec4(0.20f, 0.88f, 0.45f, 1.0f), "Mando detectado: %s", SDL_JoystickNameForIndex(0));
            } else {
                ImGui::TextColored(ImVec4(0.70f, 0.76f, 0.85f, 1.0f), "Teclado activo (Conecta cualquier mando Xbox, PlayStation o Switch en cualquier momento).");
            }

            ImGui::Dummy(ImVec2(0, 10.0f * scale));

            // Tabla visual de controles con fuentes claras y legibles
            if (ImGui::BeginTable("KeymapTable", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
                ImGui::TableSetupColumn("Acción", ImGuiTableColumnFlags_WidthFixed, 220.0f * scale);
                ImGui::TableSetupColumn("Teclado", ImGuiTableColumnFlags_WidthFixed, 320.0f * scale);
                ImGui::TableSetupColumn("Gamepad (Xbox / PlayStation / Switch)", ImGuiTableColumnFlags_WidthStretch);
                ImGui::TableHeadersRow();

                const char *actions[][3] = {
                    { "Cruceta / Movimiento", "Flechas de dirección / W A S D", "D-Pad y Stick Izquierdo" },
                    { "Botón A", "Z  /  Espacio", "Botón X (PlayStation Cuadrado)" },
                    { "Botón B", "X", "Botón A (PlayStation Cruz)" },
                    { "Botón C", "C", "Botón B (PlayStation Círculo)" },
                    { "Start / Pausa", "Enter / Intro", "Botón Start / Options" },
                    { "Pistola Justifier", "Ratón (Clic Izq: Disparar, Der: Escudo)", "Gatillos RT / LT" },
                    { "Salir del Juego", "Escape (Esc)", "Botón Back / Select o Guide" }
                };

                for (int r = 0; r < 7; r++) {
                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0);
                    if (r == 6) {
                        ImGui::TextColored(ImVec4(1.0f, 0.45f, 0.0f, 1.0f), "%s", actions[r][0]);
                    } else {
                        ImGui::Text("%s", actions[r][0]);
                    }
                    ImGui::TableSetColumnIndex(1);
                    if (r == 6) {
                        ImGui::TextColored(ImVec4(1.0f, 0.45f, 0.0f, 1.0f), "%s", actions[r][1]);
                    } else {
                        ImGui::Text("%s", actions[r][1]);
                    }
                    ImGui::TableSetColumnIndex(2);
                    ImGui::Text("%s", actions[r][2]);
                }
                ImGui::EndTable();
            }

            ImGui::Dummy(ImVec2(0, 10.0f * scale));
            ImGui::TextColored(ImVec4(0.55f, 0.63f, 0.74f, 1.0f), "Tip: Pulsa la tecla Escape (Esc) en cualquier momento del juego para salir instantáneamente.");
            if (font_regular) ImGui::PopFont();
        }

        // ── CONTENIDO: TAB 3: AUDIO ─────────────────────────────────────────
        else if (active_tab == 3) {
            if (font_large) ImGui::PushFont(font_large);
            ImGui::TextColored(ImVec4(0.90f, 0.93f, 0.98f, 1.0f), "Ajustes de Sonido");
            if (font_large) ImGui::PopFont();
            ImGui::Dummy(ImVec2(0, 12.0f * scale));

            if (font_regular) ImGui::PushFont(font_regular);
            ImGui::Text("Volumen Maestro:");
            ImGui::PushItemWidth(450.0f * scale);
            ImGui::SliderInt("##vol_slider", &volume, 0, 100, "%d%%");
            ImGui::PopItemWidth();

            ImGui::Dummy(ImVec2(0, 14.0f * scale));
            ImGui::TextColored(ImVec4(0.70f, 0.76f, 0.85f, 1.0f), "Salida de audio: 48.000 Hz / 16-bit Estéreo (Sega CD PCM + CDDA + FM YM2612).");
            ImGui::TextColored(ImVec4(0.55f, 0.63f, 0.74f, 1.0f), "Mezcla de sonido por hardware nativo x64 de ultra baja latencia.");
            if (font_regular) ImGui::PopFont();
        }

        // ── BARRA INFERIOR / FOOTER (PLAY + EXIT) ───────────────────────────
        ImGui::SetCursorPosY((float)win_h - 110.0f * scale);
        if (font_small) ImGui::PushFont(font_small);
        ImGui::TextColored(ImVec4(0.55f, 0.63f, 0.74f, 1.0f), "Los ajustes se guardan automáticamente al pulsar Jugar. Puedes pulsar Alt+Enter o F11 para alternar ventana.");
        if (font_small) ImGui::PopFont();

        ImGui::SetCursorPosY((float)win_h - 85.0f * scale);

        // Botón Jugar (Play) gigante naranja estilo Revo
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.000f, 0.463f, 0.000f, 1.00f)); // #FF7600
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.000f, 0.580f, 0.150f, 1.00f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.850f, 0.380f, 0.000f, 1.00f));
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 6.0f * scale);

        if (font_large) ImGui::PushFont(font_large);
        if (ImGui::Button("  JUGAR (Play)  ", ImVec2(240.0f * scale, 56.0f * scale))) {
            running = false;
            result_action = 0; // Launch
        }
        if (font_large) ImGui::PopFont();

        ImGui::PopStyleVar();
        ImGui::PopStyleColor(4);

        ImGui::SameLine(0, 20.0f * scale);

        // Botón Salir (Quit)
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.12f, 0.16f, 0.25f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.18f, 0.24f, 0.36f, 1.0f));
        if (font_bold) ImGui::PushFont(font_bold);
        if (ImGui::Button("Salir", ImVec2(130.0f * scale, 56.0f * scale))) {
            running = false;
            result_action = 1; // Quit
        }
        if (font_bold) ImGui::PopFont();
        ImGui::PopStyleColor(2);

        ImGui::EndChild();
        ImGui::End();

        // Actualizar cursor del ratón: mano interactiva sobre cualquier opción o botón
        bool is_hovering = ImGui::IsAnyItemHovered() || ImGui::IsAnyItemActive() || (ImGui::GetMouseCursor() == ImGuiMouseCursor_Hand);
        if (is_hovering) {
            SDL_SetCursor(cursor_hand);
        } else {
            SDL_SetCursor(cursor_arrow);
        }

        // Renderizado OpenGL3
        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(0.047f, 0.071f, 0.122f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }

    // 6. Limpieza y guardado
    if (poster_tex) {
        glDeleteTextures(1, &poster_tex);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);

    if (cursor_hand) SDL_FreeCursor(cursor_hand);
    if (cursor_arrow) SDL_FreeCursor(cursor_arrow);

    // Guardar ajustes seleccionados en settings.toml
    fset = fopen("settings.toml", "w");
    if (fset) {
        fprintf(fset, "# Snatcher Mega-CD Recomp - Settings\n");
        fprintf(fset, "fullscreen = %d\n", fullscreen);
        fprintf(fset, "window_scale = %d\n", window_scale);
        fprintf(fset, "widescreen = %d\n", widescreen);
        fprintf(fset, "view_mode = %d\n", widescreen ? 1 : 0);
        fprintf(fset, "vsync = %d\n", vsync);
        fprintf(fset, "filter = %d\n", linear_filter);
        fprintf(fset, "linear_filter = %d\n", (linear_filter == 1 || linear_filter == 3) ? 1 : 0);
        fprintf(fset, "integer_scaling = %d\n", integer_scaling);
        fprintf(fset, "color_mode = %d\n", color_mode);
        fprintf(fset, "volume = %d\n", volume);
        fprintf(fset, "mouse_enabled = %d\n", mouse_enabled);
        fprintf(fset, "refresh_rate = %d\n", refresh_rate);
        fclose(fset);
    }

    if (current_disc[0] != '\0' && disc_path_io && disc_path_cap > 0) {
        strncpy(disc_path_io, current_disc, disc_path_cap - 1);
        disc_path_io[disc_path_cap - 1] = '\0';
    }

    if (cfg_out) {
        cfg_out->fullscreen = fullscreen;
        cfg_out->window_scale = window_scale;
        cfg_out->widescreen = widescreen;
        cfg_out->linear_filter = linear_filter;
        cfg_out->volume = volume;
        cfg_out->mouse_enabled = mouse_enabled;
        cfg_out->refresh_rate = refresh_rate;
        cfg_out->vsync = vsync;
        cfg_out->integer_scaling = integer_scaling;
        cfg_out->color_mode = color_mode;
    }

    return result_action;
}
