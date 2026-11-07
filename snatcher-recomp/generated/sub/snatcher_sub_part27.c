/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_sub_at_00D4C6(M68kStepContext *ctx){
  uint32_t _00D4C6r = (uint32_t)((uint32_t)g_cpu.D[0]) | (uint32_t)0x800001u;
  { uint32_t _fv = (uint32_t)(_00D4C6r);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 31)        g_cpu.SR |= (1u<<3); }
  g_cpu.D[0] = (uint32_t)(uint32_t)(_00D4C6r);
}
void snatcher_sub_at_00DDD2(M68kStepContext *ctx){
  ctx->charge=16; g_cpu.PC=m68k_read32(g_cpu.A[7])&0xFFFFFFu; g_cpu.A[7]+=4;
}
void snatcher_sub_at_00E4AE(M68kStepContext *ctx){
  uint32_t _00E4AEr = (uint32_t)((uint32_t)((uint32_t)g_cpu.D[1]) + (uint32_t)0x10u);
  { uint32_t _fa = (uint32_t)((uint32_t)((uint32_t)g_cpu.D[1])), _fb = (uint32_t)((uint32_t)0x10u), _fr = (uint32_t)(_00E4AEr);
    g_cpu.SR &= ~(0x1Fu);
    if (!_fr)                        g_cpu.SR |= (1u<<2);
    if (_fr >> 31)                   g_cpu.SR |= (1u<<3);
    if ((uint64_t)_fa + (uint64_t)_fb > 0xFFFFFFFFu) { g_cpu.SR |= (1u<<0); g_cpu.SR |= (1u<<4); }
    if (!((_fa^_fb) & 0x80000000u) && ((_fa^_fr) & 0x80000000u)) g_cpu.SR |= (1u<<1); }
  g_cpu.D[1] = (uint32_t)(uint32_t)(_00E4AEr);
}
void snatcher_sub_at_00E9B2(M68kStepContext *ctx){
  ctx->charge=18; g_cpu.A[7]-=4; m68k_write32(g_cpu.A[7],0x00E9B6u); g_cpu.PC=0x00E058u;
}
void snatcher_sub_at_00EA1A(M68kStepContext *ctx){
  ctx->charge=18; g_cpu.A[7]-=4; m68k_write32(g_cpu.A[7],0x00EA1Eu); g_cpu.PC=0x00F272u;
}
