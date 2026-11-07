/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_sub_at_006030(M68kStepContext *ctx){
  uint8_t _006030r = (uint8_t)((uint8_t)g_cpu.D[0]) | (uint8_t)0x26u;
  { uint8_t _fv = (uint8_t)(_006030r);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
  g_cpu.D[0] = (g_cpu.D[0] & 0xFFFFFF00u) | (uint32_t)((uint8_t)(_006030r));
}
void snatcher_sub_at_00D81A(M68kStepContext *ctx){
  g_cpu.D[6] = (g_cpu.D[6] & 0xFFFF0000u) | (uint32_t)((uint16_t)((uint16_t)g_cpu.D[0]));
  { uint16_t _fv = (uint16_t)((uint16_t)g_cpu.D[0]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 15)        g_cpu.SR |= (1u<<3); }
}
void snatcher_sub_at_00E436(M68kStepContext *ctx){
  uint16_t _00E436r = (uint16_t)((uint16_t)((uint16_t)g_cpu.D[0]) - (uint16_t)0x6000u);
  { uint16_t _fa = (uint16_t)((uint16_t)((uint16_t)g_cpu.D[0])), _fb = (uint16_t)((uint16_t)0x6000u), _fr = (uint16_t)(_00E436r);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fr)                   g_cpu.SR |= (1u<<2);
    if (_fr >> 15)              g_cpu.SR |= (1u<<3);
    if ((uint32_t)_fb > (uint32_t)_fa) { g_cpu.SR |= (1u<<0); }
    if (((_fa^_fb) & 0x00008000u) && ((_fa^_fr) & 0x00008000u)) g_cpu.SR |= (1u<<1); }
}
void snatcher_sub_at_00E994(M68kStepContext *ctx){
  ctx->charge=18; g_cpu.A[7]-=4; m68k_write32(g_cpu.A[7],0x00E998u); g_cpu.PC=0x00E058u;
}
void snatcher_sub_at_00E9F8(M68kStepContext *ctx){
  m68k_write8((uint32_t)(g_cpu.A[1] + (int32_t)9), (uint8_t)((uint8_t)g_cpu.D[7]));
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[7]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_sub_at_00F552(M68kStepContext *ctx){
  ctx->charge=14;
  g_cpu.A[7] -= 2; m68k_write16(g_cpu.A[7], (uint16_t)(g_cpu.SR));
}
