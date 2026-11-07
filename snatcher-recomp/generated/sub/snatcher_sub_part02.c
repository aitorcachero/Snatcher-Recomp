/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_sub_at_006004(M68kStepContext *ctx){
  { uint32_t target=(0x0000D4C4u)&0xFFFFFFu; ctx->charge=12;
    g_cpu.PC=target; }
}
void snatcher_sub_at_00D7F6(M68kStepContext *ctx){
  uint8_t _00D7F6r = (uint8_t)((uint8_t)(g_cpu.A[0]) - (uint8_t)0x20u);
  { uint8_t _fa = (uint8_t)((uint8_t)(g_cpu.A[0])), _fb = (uint8_t)((uint8_t)0x20u), _fr = (uint8_t)(_00D7F6r);
    g_cpu.SR &= ~(0x1Fu);
    if (!_fr)                   g_cpu.SR |= (1u<<2);
    if (_fr >> 7)              g_cpu.SR |= (1u<<3);
    if ((uint32_t)_fb > (uint32_t)_fa) { g_cpu.SR |= (1u<<0); g_cpu.SR |= (1u<<4); }
    if (((_fa^_fb) & 0x00000080u) && ((_fa^_fr) & 0x00000080u)) g_cpu.SR |= (1u<<1); }
  g_cpu.A[0] = (uint32_t)(_00D7F6r);
}
void snatcher_sub_at_00E05C(M68kStepContext *ctx){
  m68k_write8((uint32_t)(g_cpu.A[1] + (int32_t)15), (uint8_t)((uint8_t)g_cpu.D[7]));
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[7]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_sub_at_00E4CA(M68kStepContext *ctx){
  uint16_t _00E4CAr = (uint16_t)((uint16_t)((uint16_t)g_cpu.D[2]) - (uint16_t)0x10u);
  { uint16_t _fa = (uint16_t)((uint16_t)((uint16_t)g_cpu.D[2])), _fb = (uint16_t)((uint16_t)0x10u), _fr = (uint16_t)(_00E4CAr);
    g_cpu.SR &= ~(0x1Fu);
    if (!_fr)                   g_cpu.SR |= (1u<<2);
    if (_fr >> 15)              g_cpu.SR |= (1u<<3);
    if ((uint32_t)_fb > (uint32_t)_fa) { g_cpu.SR |= (1u<<0); g_cpu.SR |= (1u<<4); }
    if (((_fa^_fb) & 0x00008000u) && ((_fa^_fr) & 0x00008000u)) g_cpu.SR |= (1u<<1); }
  g_cpu.D[2] = (g_cpu.D[2] & 0xFFFF0000u) | (uint32_t)((uint16_t)(_00E4CAr));
}
void snatcher_sub_at_00E9C8(M68kStepContext *ctx){
  ctx->charge=18; g_cpu.A[7]-=4; m68k_write32(g_cpu.A[7],0x00E9CCu); g_cpu.PC=0x00F272u;
}
void snatcher_sub_at_00EEC4(M68kStepContext *ctx){
  g_cpu.D[5] = (uint32_t)(uint32_t)((uint32_t)g_cpu.D[1]);
  { uint32_t _fv = (uint32_t)((uint32_t)g_cpu.D[1]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 31)        g_cpu.SR |= (1u<<3); }
}
