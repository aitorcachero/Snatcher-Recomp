/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_sub_at_00602E(M68kStepContext *ctx){
  { uint32_t target=(0x0000F326u)&0xFFFFFFu; ctx->charge=12;
    g_cpu.PC=target; }
}
void snatcher_sub_at_00D816(M68kStepContext *ctx){
  uint8_t _t00D816 = m68k_read8(g_cpu.A[4]);
  uint8_t _00D816r = (uint8_t)(_t00D816) & (uint8_t)0x42u;
  { uint8_t _fv = (uint8_t)(_00D816r);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
  m68k_write8(g_cpu.A[4], (uint8_t)(_00D816r)); g_cpu.A[4] += 1;
}
void snatcher_sub_at_00E434(M68kStepContext *ctx){
  if((g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0x00E43Eu;}else ctx->charge=8;
}
void snatcher_sub_at_00E992(M68kStepContext *ctx){
  g_cpu.D[7] = (g_cpu.D[7] & 0xFFFFFF00u) | (uint32_t)((uint8_t)((uint8_t)g_cpu.D[5]));
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[5]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_sub_at_00E9F6(M68kStepContext *ctx){
  g_cpu.D[7] = (g_cpu.D[7] & 0xFFFFFF00u) | (uint32_t)((uint8_t)((uint8_t)g_cpu.D[6]));
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[6]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_sub_at_00F32C(M68kStepContext *ctx){
  ctx->charge=10; g_cpu.PC=0x00F552u;
}
