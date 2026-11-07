@echo off
cd /d "%~dp0"
title Snatcher (Mega-CD) — Recompilacion Nativa PC

:: Configuración de entorno
set SEGACD_RENDER_THREAD=1
set SEGACD_PRESENT_THREAD=1
set SEGACD_VSYNC=1
set SEGACD_HIGH_REFRESH=144
set SEGACD_ASPECT_RATIO=16:9
set SEGACD_MOUSE_JUSTIFIER=1

:: 1. Lanzador nativo en la raíz
if exist "Snatcher.exe" (
    start "" "Snatcher.exe"
    exit /b
)

:: 2. Lanzador en snatcher-recomp
if exist "snatcher-recomp\Snatcher.exe" (
    cd /d "%~dp0snatcher-recomp"
    start "" "Snatcher.exe"
    exit /b
)

:: 3. Binario directo recompiled
if exist "snatcher-recomp\build-release\Release\Snatcher_Recompiled.exe" (
    cd /d "%~dp0snatcher-recomp\build-release\Release"
    start "" "Snatcher_Recompiled.exe"
    exit /b
)
if exist "snatcher-recomp\Snatcher_Recompiled.exe" (
    cd /d "%~dp0snatcher-recomp"
    start "" "Snatcher_Recompiled.exe"
    exit /b
)

exit /b
