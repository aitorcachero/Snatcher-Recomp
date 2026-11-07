/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_sub_at_00602A(M68kStepContext *ctx){
  uint8_t _00602Ar = (uint8_t)((uint8_t)g_cpu.D[1]) | (uint8_t)0xEEu;
  { uint8_t _fv = (uint8_t)(_00602Ar);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
  g_cpu.D[1] = (g_cpu.D[1] & 0xFFFFFF00u) | (uint32_t)((uint8_t)(_00602Ar));
}
void snatcher_sub_at_00D814(M68kStepContext *ctx){
  g_cpu.A[6] = (uint32_t)(int32_t)(int16_t)((uint16_t)g_cpu.D[2]);
}
void snatcher_sub_at_00E430(M68kStepContext *ctx){
  uint16_t _00E430r = (uint16_t)((uint16_t)((uint16_t)g_cpu.D[0]) - (uint16_t)0x4000u);
  { uint16_t _fa = (uint16_t)((uint16_t)((uint16_t)g_cpu.D[0])), _fb = (uint16_t)((uint16_t)0x4000u), _fr = (uint16_t)(_00E430r);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fr)                   g_cpu.SR |= (1u<<2);
    if (_fr >> 15)              g_cpu.SR |= (1u<<3);
    if ((uint32_t)_fb > (uint32_t)_fa) { g_cpu.SR |= (1u<<0); }
    if (((_fa^_fb) & 0x00008000u) && ((_fa^_fr) & 0x00008000u)) g_cpu.SR |= (1u<<1); }
}
void snatcher_sub_at_00E990(M68kStepContext *ctx){
  uint16_t _00E990r = (uint16_t)((uint16_t)g_cpu.D[5] + (uint16_t)((uint16_t)g_cpu.D[5]));
  { uint16_t _fa = (uint16_t)((uint16_t)((uint16_t)g_cpu.D[5])), _fb = (uint16_t)((uint16_t)((uint16_t)g_cpu.D[5])), _fr = (uint16_t)(_00E990r);
    g_cpu.SR &= ~(0x1Fu);
    if (!_fr)                        g_cpu.SR |= (1u<<2);
    if (_fr >> 15)                   g_cpu.SR |= (1u<<3);
    if ((uint64_t)_fa + (uint64_t)_fb > 0x0000FFFFu) { g_cpu.SR |= (1u<<0); g_cpu.SR |= (1u<<4); }
    if (!((_fa^_fb) & 0x00008000u) && ((_fa^_fr) & 0x00008000u)) g_cpu.SR |= (1u<<1); }
  g_cpu.D[5] = (g_cpu.D[5] & 0xFFFF0000u) | (uint32_t)((uint16_t)_00E990r);
}
void snatcher_sub_at_00E9F2(M68kStepContext *ctx){
  ctx->charge=18; g_cpu.A[7]-=4; m68k_write32(g_cpu.A[7],0x00E9F6u); g_cpu.PC=0x00F272u;
}
void snatcher_sub_at_00F32A(M68kStepContext *ctx){
  if(!(g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0x00F326u;}else ctx->charge=8;
}
