@echo off
cd /d "%~dp0"
title Snatcher (Mega-CD) — Modo Raton Justifier Lightgun

:: Activacion forzada de emulacion de pistola optica por raton
set SEGACD_RENDER_THREAD=1
set SEGACD_PRESENT_THREAD=1
set SEGACD_VSYNC=1
set SEGACD_HIGH_REFRESH=144
set SEGACD_ASPECT_RATIO=16:9
set SEGACD_MOUSE_JUSTIFIER=1
set SEGACD_MOUSE_SENSITIVITY=1.0

if exist "Snatcher.exe" (
    start "" "Snatcher.exe"
    exit /b
)
if exist "snatcher-recomp\Snatcher.exe" (
    cd /d "%~dp0snatcher-recomp"
    start "" "Snatcher.exe"
    exit /b
)
if exist "snatcher-recomp\build-release\Release\Snatcher_Recompiled.exe" (
    cd /d "%~dp0snatcher-recomp\build-release\Release"
    start "" "Snatcher_Recompiled.exe"
    exit /b
)
exit /b
