/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_sub_at_006006(M68kStepContext *ctx){
  uint8_t _006006r = (uint8_t)((uint8_t)g_cpu.D[0]) | (uint8_t)0xC4u;
  { uint8_t _fv = (uint8_t)(_006006r);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
  g_cpu.D[0] = (g_cpu.D[0] & 0xFFFFFF00u) | (uint32_t)((uint8_t)(_006006r));
}
void snatcher_sub_at_00D7FA(M68kStepContext *ctx){
  { uint32_t _x = (g_cpu.SR >> 4) & 1u;
    uint8_t _00D7FAr = (uint8_t)(0 - (uint8_t)((uint8_t)g_cpu.D[0]) - (uint8_t)_x);
  { uint8_t _fa = (uint8_t)(0), _fb = (uint8_t)((uint8_t)g_cpu.D[0]), _fr = (uint8_t)(_00D7FAr);
    g_cpu.SR &= ~(0x1Fu);
    if (!_fr)                   g_cpu.SR |= (1u<<2);
    if (_fr >> 7)              g_cpu.SR |= (1u<<3);
    if ((uint32_t)_fb > (uint32_t)_fa) { g_cpu.SR |= (1u<<0); g_cpu.SR |= (1u<<4); }
    if (((_fa^_fb) & 0x00000080u) && ((_fa^_fr) & 0x00000080u)) g_cpu.SR |= (1u<<1); }
  g_cpu.D[0] = (g_cpu.D[0] & 0xFFFFFF00u) | (uint32_t)((uint8_t)(_00D7FAr));
  }
}
void snatcher_sub_at_00E060(M68kStepContext *ctx){
  ctx->charge=18; g_cpu.A[7]-=4; m68k_write32(g_cpu.A[7],0x00E064u); g_cpu.PC=0x00F272u;
}
void snatcher_sub_at_00E4CE(M68kStepContext *ctx){
  m68k_write32(0x0007F824u, (uint32_t)((uint32_t)g_cpu.D[2]));
  { uint32_t _fv = (uint32_t)((uint32_t)g_cpu.D[2]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 31)        g_cpu.SR |= (1u<<3); }
}
void snatcher_sub_at_00E9CC(M68kStepContext *ctx){
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[1]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_sub_at_00EEC6(M68kStepContext *ctx){
  uint16_t _00EEC6r = (uint16_t)((uint16_t)g_cpu.D[5] + (uint16_t)((uint16_t)g_cpu.D[5]));
  { uint16_t _fa = (uint16_t)((uint16_t)((uint16_t)g_cpu.D[5])), _fb = (uint16_t)((uint16_t)((uint16_t)g_cpu.D[5])), _fr = (uint16_t)(_00EEC6r);
    g_cpu.SR &= ~(0x1Fu);
    if (!_fr)                        g_cpu.SR |= (1u<<2);
    if (_fr >> 15)                   g_cpu.SR |= (1u<<3);
    if ((uint64_t)_fa + (uint64_t)_fb > 0x0000FFFFu) { g_cpu.SR |= (1u<<0); g_cpu.SR |= (1u<<4); }
    if (!((_fa^_fb) & 0x00008000u) && ((_fa^_fr) & 0x00008000u)) g_cpu.SR |= (1u<<1); }
  g_cpu.D[5] = (g_cpu.D[5] & 0xFFFF0000u) | (uint32_t)((uint16_t)_00EEC6r);
}
