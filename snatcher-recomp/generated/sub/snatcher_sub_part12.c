/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_sub_at_006022(M68kStepContext *ctx){
  { uint32_t target=(0x0000D4C0u)&0xFFFFFFu; ctx->charge=12;
    g_cpu.PC=target; }
}
void snatcher_sub_at_00D80E(M68kStepContext *ctx){
  g_cpu.A[4] = (uint32_t)(0);
  g_cpu.SR = (g_cpu.SR & ~0x0Fu) | (1u<<2);
}
void snatcher_sub_at_00E428(M68kStepContext *ctx){
  uint16_t _ts00E428 = m68k_read16(g_cpu.A[3]); g_cpu.A[3] += 2;
  g_cpu.D[0] = (g_cpu.D[0] & 0xFFFF0000u) | (uint32_t)((uint16_t)(_ts00E428));
  { uint16_t _fv = (uint16_t)(_ts00E428);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 15)        g_cpu.SR |= (1u<<3); }
}
void snatcher_sub_at_00E4FC(M68kStepContext *ctx){
  ctx->charge=16; g_cpu.PC=m68k_read32(g_cpu.A[7])&0xFFFFFFu; g_cpu.A[7]+=4;
}
void snatcher_sub_at_00E9EA(M68kStepContext *ctx){
  g_cpu.D[7] = (g_cpu.D[7] & 0xFFFF0000u) | (uint32_t)((uint16_t)((uint16_t)g_cpu.D[6]));
  { uint16_t _fv = (uint16_t)((uint16_t)g_cpu.D[6]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 15)        g_cpu.SR |= (1u<<3); }
}
void snatcher_sub_at_00F27C(M68kStepContext *ctx){
  { uint32_t _mbase = g_cpu.A[7];
    g_cpu.D[7] = m68k_read32(_mbase); _mbase += 4;
    g_cpu.A[7] = _mbase; }
}
