/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_sub_at_006010(M68kStepContext *ctx){
  { uint32_t target=(0x0000E046u)&0xFFFFFFu; ctx->charge=12;
    g_cpu.PC=target; }
}
void snatcher_sub_at_00D800(M68kStepContext *ctx){
  if(!(g_cpu.SR & ((1u<<0)|(1u<<2)))){ctx->charge=10;g_cpu.PC=0x00D844u;}else ctx->charge=8;
}
void snatcher_sub_at_00E338(M68kStepContext *ctx){
  ctx->charge=10; g_cpu.PC=0x00E492u;
}
void snatcher_sub_at_00E4DE(M68kStepContext *ctx){
  m68k_write32(0x0007F824u, (uint32_t)(0x00000000u));
  { uint32_t _fv = (uint32_t)(0x00000000u);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 31)        g_cpu.SR |= (1u<<3); }
}
void snatcher_sub_at_00E9D2(M68kStepContext *ctx){
  uint8_t _ts00E9D2 = m68k_read8(0x0007F812);
  g_cpu.D[5] = (g_cpu.D[5] & 0xFFFFFF00u) | (uint32_t)((uint8_t)(_ts00E9D2));
  { uint8_t _fv = (uint8_t)(_ts00E9D2);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_sub_at_00EED0(M68kStepContext *ctx){
  uint8_t _t00EED0 = m68k_read8(0x0007F802);
  uint8_t _00EED0r = 0;
  { uint32_t _bn = (uint32_t)g_cpu.D[5] & 7u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_t00EED0) & (1u<<_bn)) ? (1u<<2) : 0u);
    _00EED0r = (uint8_t)((uint8_t)(_t00EED0) & ~(uint8_t)(1u<<_bn)); }
  m68k_write8(0x0007F802u, (uint8_t)(_00EED0r));
}
