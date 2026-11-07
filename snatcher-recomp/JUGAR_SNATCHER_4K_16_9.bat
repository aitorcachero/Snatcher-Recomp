@echo off
cd /d "%~dp0"
title Snatcher (Mega-CD) — Modo 4K Panoramico 16:9

:: Forzar escalado 4K interno y formato panorámico
set SEGACD_RENDER_THREAD=1
set SEGACD_PRESENT_THREAD=1
set SEGACD_VSYNC=1
set SEGACD_HIGH_REFRESH=144
set SEGACD_ASPECT_RATIO=16:9
set SEGACD_INTERNAL_SCALE=4.0
set SEGACD_SHADER=crt_royale

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
