/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_sub_at_006024(M68kStepContext *ctx){
  uint8_t _006024r = (uint8_t)((uint8_t)g_cpu.D[0]) | (uint8_t)0xC0u;
  { uint8_t _fv = (uint8_t)(_006024r);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
  g_cpu.D[0] = (g_cpu.D[0] & 0xFFFFFF00u) | (uint32_t)((uint8_t)(_006024r));
}
void snatcher_sub_at_00D810(M68kStepContext *ctx){
  g_cpu.A[0] -= 1; uint8_t _ts00D810 = m68k_read8(g_cpu.A[0]);
  g_cpu.D[0] = (g_cpu.D[0] & 0xFFFFFF00u) | (uint32_t)((uint8_t)(_ts00D810));
  { uint8_t _fv = (uint8_t)(_ts00D810);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_sub_at_00E42A(M68kStepContext *ctx){
  uint16_t _00E42Ar = (uint16_t)((uint16_t)((uint16_t)g_cpu.D[0]) - (uint16_t)0xFFFFu);
  { uint16_t _fa = (uint16_t)((uint16_t)((uint16_t)g_cpu.D[0])), _fb = (uint16_t)((uint16_t)0xFFFFu), _fr = (uint16_t)(_00E42Ar);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fr)                   g_cpu.SR |= (1u<<2);
    if (_fr >> 15)              g_cpu.SR |= (1u<<3);
    if ((uint32_t)_fb > (uint32_t)_fa) { g_cpu.SR |= (1u<<0); }
    if (((_fa^_fb) & 0x00008000u) && ((_fa^_fr) & 0x00008000u)) g_cpu.SR |= (1u<<1); }
}
void snatcher_sub_at_00E98A(M68kStepContext *ctx){
  { uint32_t _mbase = g_cpu.A[7];
    _mbase -= 4; m68k_write32(_mbase, g_cpu.D[7]);
    _mbase -= 4; m68k_write32(_mbase, g_cpu.D[6]);
    _mbase -= 4; m68k_write32(_mbase, g_cpu.D[5]);
    g_cpu.A[7] = _mbase; }
}
void snatcher_sub_at_00E9EC(M68kStepContext *ctx){
  { uint16_t _sv = (uint16_t)g_cpu.D[7];
    uint16_t _00E9ECr = (8 > 0 && 8 < 16) ? (_sv >> 8) : (8 == 0 ? _sv : (uint16_t)0);
    uint32_t _c = (8 <= 16) ? ((_sv >> (8 - 1)) & 1u) : 0u;
    g_cpu.D[7] = (g_cpu.D[7] & 0xFFFF0000u) | (uint32_t)((uint16_t)_00E9ECr);
    g_cpu.SR &= ~(0x1Fu);
    if (!_00E9ECr) g_cpu.SR |= (1u<<2);
    if ((uint32_t)_00E9ECr >> 15) g_cpu.SR |= (1u<<3);
    if (_c) { g_cpu.SR |= (1u<<0); g_cpu.SR |= (1u<<4); }
  }
}
void snatcher_sub_at_00F280(M68kStepContext *ctx){
  ctx->charge=16; g_cpu.PC=m68k_read32(g_cpu.A[7])&0xFFFFFFu; g_cpu.A[7]+=4;
}
