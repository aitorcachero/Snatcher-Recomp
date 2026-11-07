/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_sub_at_006018(M68kStepContext *ctx){
  uint8_t _006018r = (uint8_t)((uint8_t)g_cpu.D[0]) | (uint8_t)0xB6u;
  { uint8_t _fv = (uint8_t)(_006018r);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
  g_cpu.D[0] = (g_cpu.D[0] & 0xFFFFFF00u) | (uint32_t)((uint8_t)(_006018r));
}
void snatcher_sub_at_00D808(M68kStepContext *ctx){
  uint8_t _ts00D808 = m68k_read8(g_cpu.A[0]);
  g_cpu.D[0] = (g_cpu.D[0] & 0xFFFFFF00u) | (uint32_t)((uint8_t)(_ts00D808));
  { uint8_t _fv = (uint8_t)(_ts00D808);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_sub_at_00E420(M68kStepContext *ctx){
  if((g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0x00E492u;}else ctx->charge=8;
}
void snatcher_sub_at_00E4F0(M68kStepContext *ctx){
  m68k_write32(g_cpu.A[3], (uint32_t)((uint32_t)g_cpu.D[0])); g_cpu.A[3] += 4;
  { uint32_t _fv = (uint32_t)((uint32_t)g_cpu.D[0]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 31)        g_cpu.SR |= (1u<<3); }
}
void snatcher_sub_at_00E9E0(M68kStepContext *ctx){
  if(!(g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0x00EA1Eu;}else ctx->charge=8;
}
void snatcher_sub_at_00F272(M68kStepContext *ctx){
  { uint32_t _mbase = g_cpu.A[7];
    _mbase -= 4; m68k_write32(_mbase, g_cpu.D[7]);
    g_cpu.A[7] = _mbase; }
}
