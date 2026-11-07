/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_sub_at_006002(M68kStepContext *ctx){
  /* NOP */
}
void snatcher_sub_at_00D7F4(M68kStepContext *ctx){
  { uint32_t _bn = (uint32_t)g_cpu.D[0] & 31u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)((uint32_t)g_cpu.D[2]) & (1u<<_bn)) ? (1u<<2) : 0u); }
}
void snatcher_sub_at_00E058(M68kStepContext *ctx){
  uint8_t _00E058r = (uint8_t)((uint8_t)((uint8_t)g_cpu.D[7]) + (uint8_t)0xC0u);
  { uint8_t _fa = (uint8_t)((uint8_t)((uint8_t)g_cpu.D[7])), _fb = (uint8_t)((uint8_t)0xC0u), _fr = (uint8_t)(_00E058r);
    g_cpu.SR &= ~(0x1Fu);
    if (!_fr)                        g_cpu.SR |= (1u<<2);
    if (_fr >> 7)                   g_cpu.SR |= (1u<<3);
    if ((uint64_t)_fa + (uint64_t)_fb > 0x000000FFu) { g_cpu.SR |= (1u<<0); g_cpu.SR |= (1u<<4); }
    if (!((_fa^_fb) & 0x00000080u) && ((_fa^_fr) & 0x00000080u)) g_cpu.SR |= (1u<<1); }
  g_cpu.D[7] = (g_cpu.D[7] & 0xFFFFFF00u) | (uint32_t)((uint8_t)(_00E058r));
}
void snatcher_sub_at_00E4C8(M68kStepContext *ctx){
  g_cpu.D[1] = 0x00000010u;
  { uint32_t _fv = (uint32_t)((uint32_t)0x00000010u);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 31)        g_cpu.SR |= (1u<<3); }
}
void snatcher_sub_at_00E9C4(M68kStepContext *ctx){
  m68k_write8((uint32_t)(g_cpu.A[1] + (int32_t)9), (uint8_t)((uint8_t)g_cpu.D[7]));
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[7]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_sub_at_00EEC0(M68kStepContext *ctx){
  ctx->charge=18; g_cpu.A[7]-=4; m68k_write32(g_cpu.A[7],0x00EEC4u); g_cpu.PC=0x00E98Au;
}
