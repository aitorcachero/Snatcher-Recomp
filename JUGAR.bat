@echo off
title MegaCD-Recomp — Hub Sega Mega-CD / Mega Drive PC
cd /d "%~dp0"
cls
echo ================================================================
echo       MegaCD-Recomp — Hub Sega Mega-CD / Genesis PC (x64)
echo       4K UHD - 144Hz - 16:9 Widescreen - Raton Justifier Lightgun
echo ================================================================
echo.
echo   [1] Snatcher (Modo Estandar)
echo   [2] Snatcher (Modo Raton Justifier Lightgun)
echo   [3] Snatcher (Modo 4K UHD 16:9 Panoramico)
echo.
echo   [0] Salir
echo.
echo ================================================================
set /p opt="Selecciona una opcion (1-3): "

if "%opt%"=="1" (
    start "" "JUGAR_SNATCHER.bat"
    exit /b
)
if "%opt%"=="2" (
    start "" "JUGAR_SNATCHER_RATON_JUSTIFIER.bat"
    exit /b
)
if "%opt%"=="3" (
    start "" "JUGAR_SNATCHER_4K_16_9.bat"
    exit /b
)
if "%opt%"=="0" exit /b

echo Opcion no valida.
pause
goto :eof
