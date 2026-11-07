/* =============================================================================
 * SNATCHER (Mega-CD) — Modern Setup & Configuration Launcher
 * Estilo visual moderno inspirado en Sega Rally Revo / Recomp Modern UI
 * ============================================================================= */

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
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
    int linear_filter;
    int volume;
    int mouse_enabled;
} SnatcherLauncherConfig;

static bool prompt_browse_disc(char *out_path, size_t max_len) {
    OPENFILENAMEA ofn;
    memset(&ofn, 0, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrTitle = "Selecciona la imagen de Snatcher (.sgcd, .cue, .bin)";
    ofn.lpstrFilter = "Imagenes Sega CD (*.sgcd;*.cue;*.bin)\0*.sgcd;*.cue;*.bin\0Todos los archivos (*.*)\0*.*\0";
    ofn.lpstrFile = out_path;
    ofn.nMaxFile = (DWORD)max_len;
    ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
    return GetOpenFileNameA(&ofn) != 0;
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
    int fullscreen = 0;
    int window_scale = 3;
    int widescreen = 1;
    int linear_filter = 1;
    int volume = 100;
    int mouse_enabled = 1;

    FILE *fset = fopen("settings.toml", "r");
    if (fset) {
        char line[256];
        while (fgets(line, sizeof(line), fset)) {
            int v = 0;
            if (sscanf(line, "fullscreen = %d", &v) == 1) fullscreen = v;
            else if (sscanf(line, "window_scale = %d", &v) == 1) window_scale = v;
            else if (sscanf(line, "widescreen = %d", &v) == 1) widescreen = v;
            else if (sscanf(line, "linear_filter = %d", &v) == 1) linear_filter = v;
            else if (sscanf(line, "volume = %d", &v) == 1) volume = v;
            else if (sscanf(line, "mouse_enabled = %d", &v) == 1) mouse_enabled = v;
        }
        fclose(fset);
    }

    // 2. Crear ventana SDL2 con contexto OpenGL
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    int win_w = 1020;
    int win_h = 630;
    SDL_Window *window = SDL_CreateWindow(
        "Snatcher — Modern PC Launcher",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        win_w, win_h,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI
    );
    if (!window) return 2;

    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1); // Enable VSync

    // 3. Inicializar Dear ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.IniFilename = NULL; // No guardar imgui.ini

    // Cargar tipografía moderna
    ImFont *font_bold = NULL;
    ImFont *font_regular = NULL;
    const char *bold_candidates[] = {
        "assets/fonts/LatoLatin-Bold.ttf",
        "snatcher-recomp/assets/fonts/LatoLatin-Bold.ttf",
        "release_pkg/Snatcher-Recomp-v1.0.1-Windows-x64/assets/fonts/LatoLatin-Bold.ttf",
        "../assets/fonts/LatoLatin-Bold.ttf",
        NULL
    };
    const char *reg_candidates[] = {
        "assets/fonts/LatoLatin-Regular.ttf",
        "snatcher-recomp/assets/fonts/LatoLatin-Regular.ttf",
        "release_pkg/Snatcher-Recomp-v1.0.1-Windows-x64/assets/fonts/LatoLatin-Regular.ttf",
        "../assets/fonts/LatoLatin-Regular.ttf",
        NULL
    };
    for (int i = 0; bold_candidates[i]; i++) {
        if (GetFileAttributesA(bold_candidates[i]) != INVALID_FILE_ATTRIBUTES) {
            font_bold = io.Fonts->AddFontFromFileTTF(bold_candidates[i], 20.0f);
            break;
        }
    }
    for (int i = 0; reg_candidates[i]; i++) {
        if (GetFileAttributesA(reg_candidates[i]) != INVALID_FILE_ATTRIBUTES) {
            font_regular = io.Fonts->AddFontFromFileTTF(reg_candidates[i], 16.0f);
            break;
        }
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
    style.FrameRounding     = 6.0f;
    style.ItemSpacing       = ImVec2(10.0f, 10.0f);
    style.ItemInnerSpacing  = ImVec2(8.0f, 6.0f);
    style.ScrollbarRounding = 4.0f;
    style.GrabRounding      = 4.0f;

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
                }
            }
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        // Ventana principal que cubre todo el lienzo
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2((float)win_w, (float)win_h));
        ImGui::Begin("LauncherMain", NULL,
                     ImGuiWindowFlags_NoTitleBar |
                     ImGuiWindowFlags_NoResize |
                     ImGuiWindowFlags_NoMove |
                     ImGuiWindowFlags_NoScrollbar |
                     ImGuiWindowFlags_NoBringToFrontOnFocus);

        ImDrawList *draw = ImGui::GetWindowDrawList();

        // ── Columna Izquierda: Póster de Snatcher (330px) ────────────────────
        float left_w = 340.0f;
        ImGui::BeginChild("LeftBanner", ImVec2(left_w, (float)win_h), false, ImGuiWindowFlags_NoScrollbar);
        if (poster_tex) {
            ImGui::Image((ImTextureID)(intptr_t)poster_tex, ImVec2(left_w, (float)win_h));
        } else {
            // Fondo de degradado elegante si no hay póster cargado
            draw->AddRectFilledMultiColor(ImVec2(0, 0), ImVec2(left_w, (float)win_h),
                                          IM_COL32(14, 24, 45, 255), IM_COL32(20, 38, 70, 255),
                                          IM_COL32(10, 15, 28, 255), IM_COL32(5, 8, 16, 255));
        }

        // Overlay inferior con degradado y tipografía
        float overlay_h = 100.0f;
        draw->AddRectFilledMultiColor(ImVec2(0, win_h - overlay_h), ImVec2(left_w, (float)win_h),
                                      IM_COL32(12, 19, 32, 0), IM_COL32(12, 19, 32, 0),
                                      IM_COL32(12, 19, 32, 245), IM_COL32(12, 19, 32, 245));

        draw->AddText(ImVec2(24.0f, win_h - 75.0f), IM_COL32(255, 255, 255, 255), "SNATCHER");
        draw->AddText(ImVec2(24.0f, win_h - 52.0f), IM_COL32(255, 130, 0, 240), "Sega Mega-CD — NTSC-U [Español]");
        draw->AddText(ImVec2(24.0f, win_h - 32.0f), IM_COL32(148, 163, 184, 200), "PC Native Recompilation v1.0.1");

        ImGui::EndChild();

        // ── Columna Derecha: Interfaz de Configuración (~680px) ───────────────
        ImGui::SameLine();
        ImGui::SetCursorPosX(left_w + 24.0f);
        ImGui::BeginChild("RightPanel", ImVec2(win_w - left_w - 32.0f, (float)win_h), false, ImGuiWindowFlags_NoScrollbar);

        // Decoración superior: Rayas diagonales naranja estilo Racing / Cyberpunk
        float right_top_x = win_w - left_w - 90.0f;
        draw->AddTriangleFilled(ImVec2(right_top_x + 20, 0), ImVec2(right_top_x + 38, 0), ImVec2(right_top_x + 10, 48), IM_COL32(255, 115, 0, 230));
        draw->AddTriangleFilled(ImVec2(right_top_x + 38, 0), ImVec2(right_top_x + 10, 48), ImVec2(right_top_x - 8, 48), IM_COL32(255, 115, 0, 230));
        draw->AddTriangleFilled(ImVec2(right_top_x + 48, 0), ImVec2(right_top_x + 66, 0), ImVec2(right_top_x + 38, 48), IM_COL32(255, 140, 0, 230));
        draw->AddTriangleFilled(ImVec2(right_top_x + 66, 0), ImVec2(right_top_x + 38, 48), ImVec2(right_top_x + 20, 48), IM_COL32(255, 140, 0, 230));

        ImGui::Dummy(ImVec2(0, 10.0f));

        // Título del juego
        if (font_bold) ImGui::PushFont(font_bold);
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "Snatcher");
        if (font_bold) ImGui::PopFont();

        ImGui::TextColored(ImVec4(0.58f, 0.64f, 0.72f, 1.0f), "Listo. Pulsa Jugar o Enter.");

        ImGui::Dummy(ImVec2(0, 8.0f));

        // ── Pestañas de Navegación Estilo Revo (Play, Picture, Controls, Audio) ──
        const char *tabs[] = { "Play", "Picture", "Controls", "Audio" };
        for (int t = 0; t < 4; t++) {
            if (t > 0) ImGui::SameLine(0, 18.0f);
            bool is_selected = (active_tab == t);
            if (is_selected) {
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.50f, 0.05f, 1.0f));
            } else {
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.70f, 0.76f, 0.85f, 1.0f));
            }

            if (ImGui::Button(tabs[t], ImVec2(0, 28.0f))) {
                active_tab = t;
            }
            ImGui::PopStyleColor();

            // Línea naranja debajo de la pestaña activa
            if (is_selected) {
                ImVec2 bmin = ImGui::GetItemRectMin();
                ImVec2 bmax = ImGui::GetItemRectMax();
                draw->AddLine(ImVec2(bmin.x, bmax.y + 2), ImVec2(bmax.x, bmax.y + 2), IM_COL32(255, 120, 0, 255), 3.0f);
            }
        }

        // Línea divisoria suave horizontal
        ImVec2 sep_pos = ImGui::GetCursorScreenPos();
        draw->AddLine(ImVec2(sep_pos.x, sep_pos.y + 6), ImVec2(sep_pos.x + win_w - left_w - 60.0f, sep_pos.y + 6), IM_COL32(36, 51, 80, 255), 1.0f);
        ImGui::Dummy(ImVec2(0, 16.0f));

        // ── CONTENIDO: TAB 0: PLAY (JUGAR) ──────────────────────────────────
        if (active_tab == 0) {
            // Fila de Archivo de Juego / Disco
            ImGui::TextColored(ImVec4(0.70f, 0.76f, 0.85f, 1.0f), "Disco del juego (Mega-CD):");
            ImGui::PushItemWidth(win_w - left_w - 180.0f);
            ImGui::InputText("##disc_path", current_disc, sizeof(current_disc), ImGuiInputTextFlags_ReadOnly);
            ImGui::PopItemWidth();

            ImGui::SameLine();
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.12f, 0.18f, 0.30f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.0f, 0.46f, 0.0f, 0.8f));
            ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);
            if (ImGui::Button("Examinar...", ImVec2(90, 0))) {
                char picked[MAX_PATH] = { 0 };
                if (prompt_browse_disc(picked, sizeof(picked))) {
                    strncpy(current_disc, picked, sizeof(current_disc) - 1);
                }
            }
            ImGui::PopStyleVar();
            ImGui::PopStyleColor(2);

            if (current_disc[0] != '\0') {
                ImGui::TextColored(ImVec4(0.20f, 0.85f, 0.45f, 1.0f), "Disco detectado: Snatcher (Mega-CD Español) - NTSC-U [OK]");
            } else {
                ImGui::TextColored(ImVec4(1.0f, 0.40f, 0.20f, 1.0f), "Aviso: Copia tu imagen a la carpeta disc/ o pulsa Examinar.");
            }

            ImGui::Dummy(ImVec2(0, 12.0f));

            // Presets "Look" (Modern, Steam Deck, Original 1994, Custom)
            ImGui::TextColored(ImVec4(0.85f, 0.88f, 0.94f, 1.0f), "Aspecto (Look):");

            struct PresetCard {
                const char *badge;
                const char *title;
                const char *sub1;
                const char *sub2;
            } cards[4] = {
                { "Recomendado", "Moderna", "1920x1080 (16:9)", "Hack Panorámico, Suave" },
                { NULL, "Steam Deck", "1280x800 (16:9)", "Portátil, Optimizado" },
                { NULL, "Original 1994", "1280x960 (4:3)", "Píxel Nítido / Retro" },
                { NULL, "Personalizado", "Ajustable", "Configura en Picture" }
            };

            float card_w = 148.0f;
            float card_h = 100.0f;

            for (int i = 0; i < 4; i++) {
                if (i > 0) ImGui::SameLine(0, 10.0f);
                bool sel = (active_preset == i);

                ImGui::PushID(i);
                ImVec2 p_min = ImGui::GetCursorScreenPos();
                ImVec2 p_max = ImVec2(p_min.x + card_w, p_min.y + card_h);

                ImU32 bg_col = sel ? IM_COL32(20, 32, 54, 255) : IM_COL32(15, 23, 38, 255);
                ImU32 border_col = sel ? IM_COL32(255, 115, 0, 255) : IM_COL32(40, 58, 90, 255);

                draw->AddRectFilled(p_min, p_max, bg_col, 8.0f);
                draw->AddRect(p_min, p_max, border_col, 8.0f, 0, sel ? 2.0f : 1.0f);

                if (cards[i].badge) {
                    draw->AddText(ImVec2(p_min.x + 12.0f, p_min.y + 10.0f), IM_COL32(255, 120, 0, 255), cards[i].badge);
                }

                float text_y = cards[i].badge ? 32.0f : 16.0f;
                draw->AddText(ImVec2(p_min.x + 12.0f, p_min.y + text_y), IM_COL32(255, 255, 255, 255), cards[i].title);
                draw->AddText(ImVec2(p_min.x + 12.0f, p_min.y + text_y + 22.0f), IM_COL32(148, 163, 184, 255), cards[i].sub1);
                draw->AddText(ImVec2(p_min.x + 12.0f, p_min.y + text_y + 40.0f), IM_COL32(100, 116, 139, 255), cards[i].sub2);

                if (ImGui::InvisibleButton("##card_btn", ImVec2(card_w, card_h))) {
                    active_preset = i;
                    if (i == 0) { // Modern
                        window_scale = 3; widescreen = 1; linear_filter = 1;
                    } else if (i == 1) { // Steam Deck
                        window_scale = 2; widescreen = 1; linear_filter = 1;
                    } else if (i == 2) { // Original 1994
                        window_scale = 3; widescreen = 0; linear_filter = 0;
                    }
                }
                ImGui::PopID();
            }

            ImGui::Dummy(ImVec2(0, 14.0f));

            // Mejoras / Opciones de Juego
            ImGui::TextColored(ImVec4(0.85f, 0.88f, 0.94f, 1.0f), "Mejoras y Opciones:");

            // Hack Panorámico 16:9
            ImGui::TextColored(ImVec4(0.70f, 0.76f, 0.85f, 1.0f), "Hack Panorámico 16:9:");
            ImGui::SameLine(220.0f);
            if (widescreen) {
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.45f, 0.0f, 0.9f));
                ImGui::Button("Activado (recomendado)##ws_on");
                ImGui::PopStyleColor();
                ImGui::SameLine();
                if (ImGui::Button("Desactivado##ws_off")) { widescreen = 0; active_preset = 3; }
            } else {
                if (ImGui::Button("Activado##ws_on")) { widescreen = 1; active_preset = 3; }
                ImGui::SameLine();
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.20f, 0.28f, 0.42f, 0.9f));
                ImGui::Button("Desactivado##ws_off");
                ImGui::PopStyleColor();
            }
            ImGui::TextColored(ImVec4(0.50f, 0.58f, 0.68f, 1.0f), "Centra la imagen en 16:9 con relleno cinemático sin deformar píxeles.");

            ImGui::Dummy(ImVec2(0, 4.0f));

            // Ratón Konami Justifier
            ImGui::TextColored(ImVec4(0.70f, 0.76f, 0.85f, 1.0f), "Ratón Konami Justifier:");
            ImGui::SameLine(220.0f);
            if (mouse_enabled) {
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.45f, 0.0f, 0.9f));
                ImGui::Button("Activado (recomendado)##m_on");
                ImGui::PopStyleColor();
                ImGui::SameLine();
                if (ImGui::Button("Desactivado##m_off")) mouse_enabled = 0;
            } else {
                if (ImGui::Button("Activado##m_on")) mouse_enabled = 1;
                ImGui::SameLine();
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.20f, 0.28f, 0.42f, 0.9f));
                ImGui::Button("Desactivado##m_off");
                ImGui::PopStyleColor();
            }
            ImGui::TextColored(ImVec4(0.50f, 0.58f, 0.68f, 1.0f), "Apunta y dispara con el ratón de tu PC durante las secuencias de tiroteo.");
        }

        // ── CONTENIDO: TAB 1: PICTURE (PANTALLA) ────────────────────────────
        else if (active_tab == 1) {
            ImGui::TextColored(ImVec4(0.85f, 0.88f, 0.94f, 1.0f), "Configuración de Pantalla y Gráficos");
            ImGui::Dummy(ImVec2(0, 6.0f));

            // Escala de ventana
            ImGui::Text("Escala de ventana / Resolución:");
            const char *scales[] = { "1x (256x224 Nativo)", "2x (720p)", "3x (1080p)", "4x (1440p 2K)", "5x (2160p 4K)" };
            int cur_scale_idx = window_scale - 1;
            if (cur_scale_idx < 0) cur_scale_idx = 0;
            if (cur_scale_idx > 4) cur_scale_idx = 4;
            if (ImGui::Combo("##win_scale", &cur_scale_idx, scales, 5)) {
                window_scale = cur_scale_idx + 1;
                active_preset = 3;
            }

            ImGui::Dummy(ImVec2(0, 6.0f));

            // Pantalla completa
            ImGui::Text("Modo de visualización:");
            if (ImGui::RadioButton("Modo Ventana", fullscreen == 0)) fullscreen = 0;
            ImGui::SameLine(180.0f);
            if (ImGui::RadioButton("Pantalla Completa (Fullscreen)", fullscreen != 0)) fullscreen = 1;

            ImGui::Dummy(ImVec2(0, 6.0f));

            // Relación de aspecto
            ImGui::Text("Relación de aspecto:");
            if (ImGui::RadioButton("16:9 Panorámico", widescreen == 1)) { widescreen = 1; active_preset = 3; }
            ImGui::SameLine(180.0f);
            if (ImGui::RadioButton("4:3 Clásico Original", widescreen == 0)) { widescreen = 0; active_preset = 3; }

            ImGui::Dummy(ImVec2(0, 6.0f));

            // Filtro bilineal
            ImGui::Text("Filtro de textura:");
            if (ImGui::RadioButton("Bilineal (Suave)", linear_filter == 1)) linear_filter = 1;
            ImGui::SameLine(180.0f);
            if (ImGui::RadioButton("Píxel Nítido (Nearest)", linear_filter == 0)) linear_filter = 0;
        }

        // ── CONTENIDO: TAB 2: CONTROLS (CONTROLES) ──────────────────────────
        else if (active_tab == 2) {
            ImGui::TextColored(ImVec4(0.85f, 0.88f, 0.94f, 1.0f), "Mapeo de Mandos y Teclado");
            ImGui::Dummy(ImVec2(0, 4.0f));

            // Detección de mando
            int num_pads = SDL_NumJoysticks();
            if (num_pads > 0) {
                ImGui::TextColored(ImVec4(0.20f, 0.85f, 0.45f, 1.0f), "Mando detectado: %s", SDL_JoystickNameForIndex(0));
            } else {
                ImGui::TextColored(ImVec4(0.70f, 0.76f, 0.85f, 1.0f), "Teclado activo (Conecta cualquier mando Xbox/PlayStation/Switch en cualquier momento).");
            }

            ImGui::Dummy(ImVec2(0, 8.0f));

            // Tabla visual de controles
            if (ImGui::BeginTable("KeymapTable", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
                ImGui::TableSetupColumn("Acción", ImGuiTableColumnFlags_WidthFixed, 140.0f);
                ImGui::TableSetupColumn("Teclado", ImGuiTableColumnFlags_WidthFixed, 230.0f);
                ImGui::TableSetupColumn("Gamepad", ImGuiTableColumnFlags_WidthStretch);
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

            ImGui::Dummy(ImVec2(0, 8.0f));
            ImGui::TextColored(ImVec4(0.50f, 0.58f, 0.68f, 1.0f), "Tip: Pulsa la tecla Escape (Esc) en cualquier momento del juego para salir instantáneamente.");
        }

        // ── CONTENIDO: TAB 3: AUDIO ─────────────────────────────────────────
        else if (active_tab == 3) {
            ImGui::TextColored(ImVec4(0.85f, 0.88f, 0.94f, 1.0f), "Ajustes de Sonido");
            ImGui::Dummy(ImVec2(0, 8.0f));

            ImGui::Text("Volumen Maestro:");
            ImGui::PushItemWidth(320.0f);
            ImGui::SliderInt("##vol_slider", &volume, 0, 100, "%d%%");
            ImGui::PopItemWidth();

            ImGui::Dummy(ImVec2(0, 8.0f));
            ImGui::TextColored(ImVec4(0.70f, 0.76f, 0.85f, 1.0f), "Salida de audio: 48.000 Hz / 16-bit Estéreo (Sega CD PCM + CDDA + FM YM2612).");
            ImGui::TextColored(ImVec4(0.50f, 0.58f, 0.68f, 1.0f), "Mezcla de sonido por hardware nativo x64 de ultra baja latencia.");
        }

        // ── BARRA INFERIOR / FOOTER (PLAY + EXIT) ───────────────────────────
        ImGui::SetCursorPosY((float)win_h - 75.0f);
        ImGui::TextColored(ImVec4(0.50f, 0.58f, 0.68f, 1.0f), "Los ajustes se guardan automáticamente al pulsar Jugar.");

        ImGui::SetCursorPosY((float)win_h - 55.0f);

        // Botón Jugar (Play) gigante naranja estilo Revo
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.000f, 0.463f, 0.000f, 1.00f)); // #FF7600
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.000f, 0.580f, 0.150f, 1.00f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.850f, 0.380f, 0.000f, 1.00f));
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 4.0f);

        if (font_bold) ImGui::PushFont(font_bold);
        if (ImGui::Button("  JUGAR (Play)  ", ImVec2(180, 42))) {
            running = false;
            result_action = 0; // Launch
        }
        if (font_bold) ImGui::PopFont();

        ImGui::PopStyleVar();
        ImGui::PopStyleColor(4);

        ImGui::SameLine(0, 16.0f);

        // Botón Salir (Quit)
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.12f, 0.16f, 0.25f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.18f, 0.24f, 0.36f, 1.0f));
        if (ImGui::Button("Salir", ImVec2(90, 42))) {
            running = false;
            result_action = 1; // Quit
        }
        ImGui::PopStyleColor(2);

        ImGui::EndChild();
        ImGui::End();

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

    // Guardar ajustes seleccionados en settings.toml
    fset = fopen("settings.toml", "w");
    if (fset) {
        fprintf(fset, "# Snatcher Mega-CD Recomp - Settings\n");
        fprintf(fset, "fullscreen = %d\n", fullscreen);
        fprintf(fset, "window_scale = %d\n", window_scale);
        fprintf(fset, "widescreen = %d\n", widescreen);
        fprintf(fset, "linear_filter = %d\n", linear_filter);
        fprintf(fset, "volume = %d\n", volume);
        fprintf(fset, "mouse_enabled = %d\n", mouse_enabled);
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
    }

    return result_action;
}
