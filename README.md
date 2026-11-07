# MegaCD-Recomp — Sega Mega-CD / Mega Drive Static Recompilation Hub

Bienvenido a **MegaCD-Recomp**, el entorno de adaptación nativa a PC (Windows x64) para títulos de **Sega Mega-CD** y **Mega Drive / Genesis** mediante recompilación estática del conjunto de instrucciones Motorola 68000 dual y Zilog Z80.

Cada título traduce los binarios originales de Mega-CD a código C nativo de 64 bits ejecutado sobre un motor de bajo nivel con mejoras de última generación:

- **Resolución 4K UHD / 1080p Nativa:** Escalado interno de renderizado de alta fidelidad con filtros y shaders CRT (*CRT-Royale*, *Scanlines*, *Sharp-Bilinear*).
- **144 Hz High Refresh Presentation:** Desacople de render y presentación en doble hilo (`SEGACD_RENDER_THREAD=1`, `SEGACD_PRESENT_THREAD=1`) con tasa de refresco ultra-fluida.
- **Soporte de Ratón Nativo para Pistola Óptica (Konami Justifier):** Las secuencias de acción y disparo de *Snatcher* se pueden apuntar y disparar directamente con el ratón del PC con precisión de píxel.
- **Widescreen 16:9 / Ultrawide 21:9:** Presentación panorámica adaptativa con marco cinemático ampliado.
- **Cero Tiempos de Carga:** Lectura digital inmediata de las voces PCM (`PCMLD_01.BIN`), scripts y pistas de música CD-DA sin latencias de lente física.
- **Lanzadores Nativos Silenciosos (`.exe`):** Compilados en modo WinMain `-mwindows`, inician instantáneamente sin dejar consolas CMD abiertas en segundo plano.

---

## 🎮 Catálogo de Títulos Integrados

| # | Título | Carpeta | Lanzador Rápido | Región / Idioma |
|---|---|---|---|---|
| **1** | **Snatcher** | [`snatcher-recomp/`](snatcher-recomp/) | [`JUGAR_SNATCHER.bat`](JUGAR_SNATCHER.bat) | NTSC-U / Español (Voces y textos) |

---

## 🚀 Cómo Jugar

### Menú Principal Hub:
Haz doble clic en [`JUGAR.bat`](JUGAR.bat) en la raíz para abrir el selector interactivo y elegir el modo de juego.

### Iniciar Snatcher Directamente:
Puedes hacer doble clic en:
* [`Snatcher.exe`](Snatcher.exe) — Lanzador nativo directo silencioso.
* [`JUGAR_SNATCHER.bat`](JUGAR_SNATCHER.bat) — Lanzador estándar.
* [`JUGAR_SNATCHER_RATON_JUSTIFIER.bat`](JUGAR_SNATCHER_RATON_JUSTIFIER.bat) — Inicia con puntero de ratón asignado a la pistola Justifier.
* [`JUGAR_SNATCHER_4K_16_9.bat`](JUGAR_SNATCHER_4K_16_9.bat) — Inicia con renderizado 4K y formato 16:9.

### Controles:
* **F1** o **Esc**: Abrir menú de configuración en juego (`recomp-ui`).
* **Flechas / D-Pad**: Movimiento / Selección en menús.
* **Z / X / C**: Botones A, B, C de Mega Drive.
* **Enter**: Botón Start.
* **Ratón (Modo Justifier):**
  * Movimiento: Apuntado en pantalla.
  * Clic Izquierdo: Disparar (Trigger).
  * Clic Derecho: Recargar / Escudo.

---

## 📁 Arquitectura del Repositorio

```text
sega megadrive/
├── snatcher-recomp/
│   ├── disc/                   # Imagenes de disco (SNATCHER.BIN / CUE / snatcher.sgcd)
│   ├── extracted/              # 97 binarios y scripts extraidos del juego
│   ├── generated/
│   │   ├── main/               # Codigo C recompilado de la Main 68000 (32 archivos)
│   │   └── sub/                # Codigo C recompilado de la Sub 68000 (SUBCODE.BIN)
│   ├── src/                    # Integracion, adaptador Justifier y Widescreen
│   ├── build-release/          # Ejecutable Snatcher_Recompiled.exe + SDL2.dll
│   ├── Snatcher.exe            # Lanzador nativo silencioso individual
│   ├── game.toml               # Metadatos y opciones de juego
│   ├── settings.toml           # Resolucion, shaders y audio
│   └── keybinds.ini            # Asignacion de teclado y gamepad
├── segagenesisrecomp/          # Motor Sega CD (dual 68K, Z80, YM2612, PCM, ASIC)
├── tools/
│   └── unified_launcher.c      # Codigo fuente C del lanzador nativo Win32
├── Snatcher.exe                # Lanzador nativo silencioso en la raiz
├── JUGAR.bat                   # Menu interactivo del hub
├── JUGAR_SNATCHER.bat          # Lanzador rapido estandar
├── JUGAR_SNATCHER_RATON_JUSTIFIER.bat
├── JUGAR_SNATCHER_4K_16_9.bat
└── README.md                   # Esta documentacion
```

---

## ⚖️ Aviso Legal y Cumplimiento

Este repositorio contiene exclusivamente código fuente generado, scripts de compilación, lanzadores nativos y perfiles de configuración. Las imágenes de disco originales suministradas por el usuario permanecen aisladas en su subcarpeta `disc/`.
