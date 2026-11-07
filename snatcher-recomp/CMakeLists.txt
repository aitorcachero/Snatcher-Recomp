cmake_minimum_required(VERSION 3.20)
project(SnatcherRecomp LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(ENGINE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../segagenesisrecomp")
set(RECOMP_UI_ROOT "${ENGINE_ROOT}/runner/external/recomp-ui")

# Includes
include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/generated/main"
    "${CMAKE_CURRENT_SOURCE_DIR}/generated/sub"
    "${ENGINE_ROOT}/runner"
    "${ENGINE_ROOT}/runner/include"
    "${ENGINE_ROOT}/runner/cd"
    "${ENGINE_ROOT}/runner/video"
    "${ENGINE_ROOT}/runner/audio"
    "${ENGINE_ROOT}/runner/external/ymfm/src"
    "${ENGINE_ROOT}/runner/external/superzazu"
    "${ENGINE_ROOT}/external/m68k-recomp-core/runtime"
    "${ENGINE_ROOT}/external/m68k-recomp-core/common"
    "${ENGINE_ROOT}/recompiler/src"
    "${ENGINE_ROOT}/external/z80-recomp-core/include"
    "${ENGINE_ROOT}/runner/external/SDL2/SDL2-2.28.5/include"
    "${RECOMP_UI_ROOT}/src"
    "${RECOMP_UI_ROOT}/src/common"
)

# Generated sources
file(GLOB MAIN_GEN_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/generated/main/*.c")
file(GLOB SUB_GEN_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/generated/sub/*.c")

set(SNATCHER_SOURCES
    src/snatcher_program.c
    src/snatcher_justifier_mouse.c
    src/snatcher_widescreen.c
    src/snatcher_cue.c
    src/snatcher_standalone.c
    ${MAIN_GEN_SOURCES}
    ${SUB_GEN_SOURCES}
    ${ENGINE_ROOT}/runner/cd/machine.c
    ${ENGINE_ROOT}/runner/cd/segacd.c
    ${ENGINE_ROOT}/runner/cd/rf5c164.c
    ${ENGINE_ROOT}/runner/cd/cdd.c
    ${ENGINE_ROOT}/runner/cd/cdc.c
    ${ENGINE_ROOT}/runner/cd/sector.c
    ${ENGINE_ROOT}/runner/cd/stamp.c
    ${ENGINE_ROOT}/runner/cd/dma.c
    ${ENGINE_ROOT}/runner/cd/fader.c
    ${ENGINE_ROOT}/runner/cd/cdda.c
    ${ENGINE_ROOT}/runner/cd/disc_image.c
    ${ENGINE_ROOT}/runner/cd/z80_native.c
    ${ENGINE_ROOT}/runner/external/superzazu/z80.c
    ${ENGINE_ROOT}/runner/cd/m68k_floor.c
    ${ENGINE_ROOT}/external/m68k-recomp-core/common/m68k_decoder.c
    ${ENGINE_ROOT}/external/m68k-recomp-core/common/m68k_timing.c
    ${ENGINE_ROOT}/external/m68k-recomp-core/common/m68k_validator.c
    ${ENGINE_ROOT}/recompiler/src/rom_parser.c
    ${ENGINE_ROOT}/runner/cd/segacd_coordinator.c
    ${ENGINE_ROOT}/runner/cd/backup.c
    ${ENGINE_ROOT}/runner/cd/audio_mix.c
    ${ENGINE_ROOT}/runner/cd/audio_native.c
    ${ENGINE_ROOT}/runner/cd/debug.c
    ${ENGINE_ROOT}/runner/cd/presentation.c
    ${ENGINE_ROOT}/runner/cd/presentation_ui.c
    ${RECOMP_UI_ROOT}/src/common/recomp_runtime_ui.c
    ${RECOMP_UI_ROOT}/src/common/recomp_runtime_settings.c
    ${ENGINE_ROOT}/runner/video/genesis_bus.c
    ${ENGINE_ROOT}/runner/video/genesis_vdp.c
    ${ENGINE_ROOT}/runner/audio.c
    ${ENGINE_ROOT}/runner/audio/sn76489.c
    ${ENGINE_ROOT}/runner/audio/ym2612_ymfm.cpp
    ${ENGINE_ROOT}/runner/external/ymfm/src/ymfm_opn.cpp
    ${ENGINE_ROOT}/runner/external/ymfm/src/ymfm_ssg.cpp
    ${ENGINE_ROOT}/runner/external/ymfm/src/ymfm_adpcm.cpp
    ${ENGINE_ROOT}/runner/external/ymfm/src/ymfm_pcm.cpp
    ${ENGINE_ROOT}/external/m68k-recomp-core/runtime/m68k_step.c
)

add_executable(Snatcher_Recompiled ${SNATCHER_SOURCES})

target_compile_definitions(Snatcher_Recompiled PRIVATE
    _CRT_SECURE_NO_WARNINGS
    SNATCHER_RECOMP=1
    SEGACD_SKIP_PAYLOAD_HASH=1
)

set(SDL2_LIB_DIR "${ENGINE_ROOT}/runner/external/SDL2/SDL2-2.28.5/lib/x64")
target_link_libraries(Snatcher_Recompiled PRIVATE
    "${SDL2_LIB_DIR}/SDL2.lib"
    "${SDL2_LIB_DIR}/SDL2main.lib"
    ws2_32
)

set_target_properties(Snatcher_Recompiled PROPERTIES
    WIN32_EXECUTABLE TRUE
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build-release"
)

add_custom_command(TARGET Snatcher_Recompiled POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL2_LIB_DIR}/SDL2.dll"
        "$<TARGET_FILE_DIR:Snatcher_Recompiled>/SDL2.dll"
    VERBATIM
)
