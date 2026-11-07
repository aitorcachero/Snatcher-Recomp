/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_sub_at_00D48E(M68kStepContext *ctx){
  { uint32_t _bn = (uint32_t)g_cpu.D[4] & 31u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)((uint32_t)g_cpu.D[2]) & (1u<<_bn)) ? (1u<<2) : 0u); }
}
void snatcher_sub_at_00E43E(M68kStepContext *ctx){
  ctx->charge=18; g_cpu.A[7]-=4; m68k_write32(g_cpu.A[7],0x00E442u); g_cpu.PC=0x00DDB8u;
}
void snatcher_sub_at_00E99A(M68kStepContext *ctx){
  { uint16_t _sv = (uint16_t)g_cpu.D[7];
    uint16_t _00E99Ar = (8 > 0 && 8 < 16) ? (_sv >> 8) : (8 == 0 ? _sv : (uint16_t)0);
    uint32_t _c = (8 <= 16) ? ((_sv >> (8 - 1)) & 1u) : 0u;
    g_cpu.D[7] = (g_cpu.D[7] & 0xFFFF0000u) | (uint32_t)((uint16_t)_00E99Ar);
    g_cpu.SR &= ~(0x1Fu);
    if (!_00E99Ar) g_cpu.SR |= (1u<<2);
    if ((uint32_t)_00E99Ar >> 15) g_cpu.SR |= (1u<<3);
    if (_c) { g_cpu.SR |= (1u<<0); g_cpu.SR |= (1u<<4); }
  }
}
void snatcher_sub_at_00EA00(M68kStepContext *ctx){
  g_cpu.D[7] = (g_cpu.D[7] & 0xFFFFFF00u) | (uint32_t)((uint8_t)(0x03u));
  { uint8_t _fv = (uint8_t)(0x03u);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_sub_at_00F558(M68kStepContext *ctx){
  m68k_write16(0x00FF8030u, (uint16_t)(0x0000u));
  { uint16_t _fv = (uint16_t)(0x0000u);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 15)        g_cpu.SR |= (1u<<3); }
}
