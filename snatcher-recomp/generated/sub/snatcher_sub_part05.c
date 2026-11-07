/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_sub_at_00600C(M68kStepContext *ctx){
  uint8_t _00600Cr = (uint8_t)((uint8_t)g_cpu.D[0]) | (uint8_t)0x8Eu;
  { uint8_t _fv = (uint8_t)(_00600Cr);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
  g_cpu.D[0] = (g_cpu.D[0] & 0xFFFFFF00u) | (uint32_t)((uint8_t)(_00600Cr));
}
void snatcher_sub_at_00D7FE(M68kStepContext *ctx){
  uint16_t _t00D7FE = m68k_read16(g_cpu.A[2]);
  uint16_t _00D7FEr = (uint16_t)(~(uint16_t)(_t00D7FE));
  { uint16_t _fv = (uint16_t)(_00D7FEr);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 15)        g_cpu.SR |= (1u<<3); }
  m68k_write16(g_cpu.A[2], (uint16_t)(_00D7FEr)); g_cpu.A[2] += 2;
}
void snatcher_sub_at_00E332(M68kStepContext *ctx){
  uint8_t _t00E332 = m68k_read8(0x0007F843);
  uint8_t _00E332r = (uint8_t)((uint8_t)(_t00E332) + (uint8_t)1u);
  { uint8_t _fa = (uint8_t)((uint8_t)(_t00E332)), _fb = (uint8_t)((uint8_t)1u), _fr = (uint8_t)(_00E332r);
    g_cpu.SR &= ~(0x1Fu);
    if (!_fr)                        g_cpu.SR |= (1u<<2);
    if (_fr >> 7)                   g_cpu.SR |= (1u<<3);
    if ((uint64_t)_fa + (uint64_t)_fb > 0x000000FFu) { g_cpu.SR |= (1u<<0); g_cpu.SR |= (1u<<4); }
    if (!((_fa^_fb) & 0x00000080u) && ((_fa^_fr) & 0x00000080u)) g_cpu.SR |= (1u<<1); }
  m68k_write8(0x0007F843u, (uint8_t)(_00E332r));
}
void snatcher_sub_at_00E4D6(M68kStepContext *ctx){
  m68k_write8(0x0007F80Eu, (uint8_t)(0x00u));
  { uint8_t _fv = (uint8_t)(0x00u);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_sub_at_00E9D0(M68kStepContext *ctx){
  g_cpu.D[5] = 0x00000000u;
  { uint32_t _fv = (uint32_t)((uint32_t)0x00000000u);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 31)        g_cpu.SR |= (1u<<3); }
}
void snatcher_sub_at_00EECE(M68kStepContext *ctx){
  uint16_t _00EECEr = (uint16_t)((uint16_t)((uint16_t)g_cpu.D[5]) + (uint16_t)1u);
  { uint16_t _fa = (uint16_t)((uint16_t)((uint16_t)g_cpu.D[5])), _fb = (uint16_t)((uint16_t)1u), _fr = (uint16_t)(_00EECEr);
    g_cpu.SR &= ~(0x1Fu);
    if (!_fr)                        g_cpu.SR |= (1u<<2);
    if (_fr >> 15)                   g_cpu.SR |= (1u<<3);
    if ((uint64_t)_fa + (uint64_t)_fb > 0x0000FFFFu) { g_cpu.SR |= (1u<<0); g_cpu.SR |= (1u<<4); }
    if (!((_fa^_fb) & 0x00008000u) && ((_fa^_fr) & 0x00008000u)) g_cpu.SR |= (1u<<1); }
  g_cpu.D[5] = (g_cpu.D[5] & 0xFFFF0000u) | (uint32_t)((uint16_t)(_00EECEr));
}
