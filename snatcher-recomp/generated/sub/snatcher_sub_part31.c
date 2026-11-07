/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_sub_at_00D7EE(M68kStepContext *ctx){
  uint8_t _00D7EEr = (uint8_t)((uint8_t)g_cpu.D[0]) | (uint8_t)0x0u;
  { uint8_t _fv = (uint8_t)(_00D7EEr);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
  g_cpu.D[0] = (g_cpu.D[0] & 0xFFFFFF00u) | (uint32_t)((uint8_t)(_00D7EEr));
}
void snatcher_sub_at_00E050(M68kStepContext *ctx){
  uint8_t _t00E050 = m68k_read8(0x0007F802);
  uint8_t _00E050r = 0;
  { uint32_t _bn = (uint32_t)g_cpu.D[5] & 7u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_t00E050) & (1u<<_bn)) ? (1u<<2) : 0u);
    _00E050r = (uint8_t)((uint8_t)(_t00E050) & ~(uint8_t)(1u<<_bn)); }
  m68k_write8(0x0007F802u, (uint8_t)(_00E050r));
}
void snatcher_sub_at_00E4C2(M68kStepContext *ctx){
  uint16_t _00E4C2r = (uint16_t)((uint16_t)((uint16_t)g_cpu.D[2]) - (uint16_t)0x11u);
  { uint16_t _fa = (uint16_t)((uint16_t)((uint16_t)g_cpu.D[2])), _fb = (uint16_t)((uint16_t)0x11u), _fr = (uint16_t)(_00E4C2r);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fr)                   g_cpu.SR |= (1u<<2);
    if (_fr >> 15)              g_cpu.SR |= (1u<<3);
    if ((uint32_t)_fb > (uint32_t)_fa) { g_cpu.SR |= (1u<<0); }
    if (((_fa^_fb) & 0x00008000u) && ((_fa^_fr) & 0x00008000u)) g_cpu.SR |= (1u<<1); }
}
void snatcher_sub_at_00E9BE(M68kStepContext *ctx){
  ctx->charge=18; g_cpu.A[7]-=4; m68k_write32(g_cpu.A[7],0x00E9C2u); g_cpu.PC=0x00F272u;
}
void snatcher_sub_at_00EEBA(M68kStepContext *ctx){
  uint8_t _t00EEBA = m68k_read8((uint32_t)(int32_t)(int16_t)0x2C34);
  uint8_t _00EEBAr = 0;
  { uint32_t _bn = (uint32_t)g_cpu.D[1] & 7u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_t00EEBA) & (1u<<_bn)) ? (1u<<2) : 0u);
    _00EEBAr = (uint8_t)((uint8_t)(_t00EEBA) & ~(uint8_t)(1u<<_bn)); }
  m68k_write8((uint32_t)(int32_t)(int16_t)0x2C34, (uint8_t)(_00EEBAr));
}
