#include <windows.h>
#include <stdio.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // 1. Configuracion de variables de entorno optimas para MegaCD-Recomp
    SetEnvironmentVariableA("SEGACD_RENDER_THREAD", "1");
    SetEnvironmentVariableA("SEGACD_PRESENT_THREAD", "1");
    SetEnvironmentVariableA("SEGACD_VSYNC", "1");
    SetEnvironmentVariableA("SEGACD_HIGH_REFRESH", "144");
    SetEnvironmentVariableA("SEGACD_ASPECT_RATIO", "16:9");
    SetEnvironmentVariableA("SEGACD_MOUSE_JUSTIFIER", "1");

    char curDir[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, curDir);

    const char* candidate_paths[] = {
        "snatcher-recomp\\build-release\\Release\\Snatcher_Recompiled.exe",
        "snatcher-recomp\\build-release\\Snatcher_Recompiled.exe",
        "snatcher-recomp\\Snatcher_Recompiled.exe",
        "build-release\\Release\\Snatcher_Recompiled.exe",
        "build-release\\Snatcher_Recompiled.exe",
        "Release\\Snatcher_Recompiled.exe",
        "Snatcher_Recompiled.exe",
        NULL
    };

    char gameExe[MAX_PATH] = { 0 };
    char gameDir[MAX_PATH] = { 0 };

    for (int i = 0; candidate_paths[i] != NULL; i++) {
        snprintf(gameExe, sizeof(gameExe), "%s\\%s", curDir, candidate_paths[i]);
        if (GetFileAttributesA(gameExe) != INVALID_FILE_ATTRIBUTES) {
            // Se encontró el ejecutable, fijar directorio de trabajo
            char* lastSlash = strrchr(gameExe, '\\');
            if (lastSlash) {
                size_t dirLen = (size_t)(lastSlash - gameExe);
                strncpy(gameDir, gameExe, dirLen);
                gameDir[dirLen] = '\0';
            }
            break;
        }
        gameExe[0] = '\0';
    }

    if (gameExe[0] == '\0') {
        MessageBoxA(NULL,
            "No se encontro el binario recompiled 'Snatcher_Recompiled.exe'.\n"
            "Verifica que el proyecto ha sido generado en 'snatcher-recomp/'.",
            "MegaCD-Recomp — Snatcher", MB_ICONERROR);
        return 1;
    }

    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi = { 0 };
    if (!CreateProcessA(gameExe, lpCmdLine && lpCmdLine[0] ? lpCmdLine : NULL, NULL, NULL, FALSE, 0, NULL, curDir, &si, &pi)) {
        MessageBoxA(NULL, "No se pudo iniciar el proceso del juego.", "Error de ejecucion", MB_ICONERROR);
        return 1;
    }

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return 0;
}
