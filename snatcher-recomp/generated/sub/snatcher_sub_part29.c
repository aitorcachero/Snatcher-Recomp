/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_sub_at_00E048(M68kStepContext *ctx){
  uint8_t _t00E048 = m68k_read8(0x0007F802);
  uint8_t _00E048r = 0;
  { uint32_t _bn = (uint32_t)g_cpu.D[5] & 7u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_t00E048) & (1u<<_bn)) ? (1u<<2) : 0u);
    _00E048r = (uint8_t)((uint8_t)(_t00E048) & ~(uint8_t)(1u<<_bn)); }
  m68k_write8(0x0007F802u, (uint8_t)(_00E048r));
}
void snatcher_sub_at_00E4BA(M68kStepContext *ctx){
  uint32_t _ts00E4BA = m68k_read32(0x0007F824);
  g_cpu.D[1] = (uint32_t)(uint32_t)(_ts00E4BA);
  { uint32_t _fv = (uint32_t)(_ts00E4BA);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 31)        g_cpu.SR |= (1u<<3); }
}
void snatcher_sub_at_00E9B8(M68kStepContext *ctx){
  { uint16_t _sv = (uint16_t)g_cpu.D[7];
    uint16_t _00E9B8r = (8 > 0 && 8 < 16) ? (_sv >> 8) : (8 == 0 ? _sv : (uint16_t)0);
    uint32_t _c = (8 <= 16) ? ((_sv >> (8 - 1)) & 1u) : 0u;
    g_cpu.D[7] = (g_cpu.D[7] & 0xFFFF0000u) | (uint32_t)((uint16_t)_00E9B8r);
    g_cpu.SR &= ~(0x1Fu);
    if (!_00E9B8r) g_cpu.SR |= (1u<<2);
    if ((uint32_t)_00E9B8r >> 15) g_cpu.SR |= (1u<<3);
    if (_c) { g_cpu.SR |= (1u<<0); g_cpu.SR |= (1u<<4); }
  }
}
void snatcher_sub_at_00EA22(M68kStepContext *ctx){
  ctx->charge=16; g_cpu.PC=m68k_read32(g_cpu.A[7])&0xFFFFFFu; g_cpu.A[7]+=4;
}
