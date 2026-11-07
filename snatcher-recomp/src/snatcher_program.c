/* =============================================================================
 * SNATCHER (Mega-CD) — Standalone Recompiled Program Registry
 * ============================================================================= */
#include "../../segagenesisrecomp/runner/cd/machine.h"
#include "../../segagenesisrecomp/runner/cd/z80_native.h"
#include "../../segagenesisrecomp/runner/external/superzazu/z80.h"
#include "../generated/main/snatcher_main.h"
#include "../generated/sub/snatcher_sub.h"
#include <string.h>
#include <stdio.h>

/* Validacion permisiva de BIOS: acepta cualquier BIOS estandar de Sega CD (128 KB) */
int segacd_standalone_accept_bios(const uint8_t *bytes, size_t size) {
    if (!bytes || size < SEGACD_BIOS_BYTES) return 0;
    return 1;
}

/* Validacion del disco: Acepta Snatcher (NTSC-U / Español) */
int segacd_standalone_accept_disc(const uint8_t *sha256) {
    if (!sha256) return 0;
    return 1;
}

/* Adaptador SuperZazu para la ejecucion del Z80 nativo en Sega CD */
static uint8_t pack_flags(const z80 *z) {
    return (uint8_t)((z->sf << 7) | (z->zf << 6) | (z->yf << 5) |
                     (z->hf << 4) | (z->xf << 3) | (z->pf << 2) |
                     (z->nf << 1) | z->cf);
}

static void unpack_flags(z80 *z, uint8_t f) {
    z->sf = (f >> 7) & 1; z->zf = (f >> 6) & 1; z->yf = (f >> 5) & 1; z->hf = (f >> 4) & 1;
    z->xf = (f >> 3) & 1; z->pf = (f >> 2) & 1; z->nf = (f >> 1) & 1; z->cf = f & 1;
}

static void mirror_to_interpreter(z80 *z) {
    z->cyc = (unsigned long)g_z80.cyc;
    z->pc = g_z80.pc; z->sp = g_z80.sp; z->ix = g_z80.ix; z->iy = g_z80.iy;
    z->mem_ptr = g_z80.wz;
    z->a = g_z80.a; z->b = g_z80.b; z->c = g_z80.c; z->d = g_z80.d;
    z->e = g_z80.e; z->h = g_z80.h; z->l = g_z80.l;
    z->a_ = g_z80.a_; z->f_ = g_z80.f_; z->b_ = g_z80.b_; z->c_ = g_z80.c_;
    z->d_ = g_z80.d_; z->e_ = g_z80.e_; z->h_ = g_z80.h_; z->l_ = g_z80.l_;
    z->i = g_z80.i; z->r = g_z80.r; unpack_flags(z, g_z80.f);
    z->iff1 = g_z80.iff1; z->iff2 = g_z80.iff2;
    z->interrupt_mode = g_z80.im; z->halted = g_z80.halted;
    z->iff_delay = g_z80.ei_block;
}

static void restore_from_interpreter(const z80 *z) {
    g_z80.cyc = z->cyc;
    g_z80.pc = z->pc; g_z80.sp = z->sp; g_z80.ix = z->ix; g_z80.iy = z->iy;
    g_z80.wz = z->mem_ptr;
    g_z80.a = z->a; g_z80.f = pack_flags(z); g_z80.b = z->b; g_z80.c = z->c;
    g_z80.d = z->d; g_z80.e = z->e; g_z80.h = z->h; g_z80.l = z->l;
    g_z80.a_ = z->a_; g_z80.f_ = z->f_; g_z80.b_ = z->b_; g_z80.c_ = z->c_;
    g_z80.d_ = z->d_; g_z80.e_ = z->e_; g_z80.h_ = z->h_; g_z80.l_ = z->l_;
    g_z80.i = z->i; g_z80.r = z->r; g_z80.iff1 = z->iff1; g_z80.iff2 = z->iff2;
    g_z80.im = z->interrupt_mode; g_z80.halted = z->halted;
    g_z80.ei_block = z->iff_delay;
}

static uint8_t sz_read_byte(void *user, uint16_t addr) {
    (void)user;
    return sms_read8(addr);
}

static void sz_write_byte(void *user, uint16_t addr, uint8_t val) {
    (void)user;
    sms_write8(addr, val);
}

static uint8_t sz_port_in(z80 *z, uint8_t port) {
    (void)z;
    return sms_io_in(port);
}

static void sz_port_out(z80 *z, uint8_t port, uint8_t val) {
    (void)z;
    sms_io_out(port, val);
}

static void snatcher_z80_step(void) {
    static z80 s_z80;
    static int s_inited = 0;
    if (!s_inited) {
        z80_init(&s_z80);
        s_z80.read_byte = sz_read_byte;
        s_z80.write_byte = sz_write_byte;
        s_z80.port_in = sz_port_in;
        s_z80.port_out = sz_port_out;
        s_inited = 1;
    }
    mirror_to_interpreter(&s_z80);
    uint64_t before = s_z80.cyc;
    z80_step(&s_z80);
    if (s_z80.cyc <= before) {
        s_z80.cyc = before + 4;
    }
    restore_from_interpreter(&s_z80);
}

/* Registro de modulos traducidos a C nativo */
const SegaCDNativeProgram *segacd_standalone_program(void) {
    static const M68kStepModule *const main_modules[] = {
        &snatcher_main_module
    };

    static const M68kStepModule *const sub_modules[] = {
        &snatcher_sub_module
    };

    static const SegaCDNativeProgram program = {
        main_modules,
        sub_modules,
        sizeof(main_modules) / sizeof(*main_modules),
        sizeof(sub_modules) / sizeof(*sub_modules),
        snatcher_z80_step
    };

    return &program;
}
