/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_sub_at_00D4CC(M68kStepContext *ctx){
  g_cpu.A[2] -= 1; uint8_t _t00D4CC = m68k_read8(g_cpu.A[2]);
  uint8_t _00D4CCr = (uint8_t)((uint8_t)g_cpu.D[7] - (uint8_t)(_t00D4CC));
  { uint8_t _fa = (uint8_t)((uint8_t)((uint8_t)g_cpu.D[7])), _fb = (uint8_t)((uint8_t)(_t00D4CC)), _fr = (uint8_t)(_00D4CCr);
    g_cpu.SR &= ~(0x1Fu);
    if (!_fr)                   g_cpu.SR |= (1u<<2);
    if (_fr >> 7)              g_cpu.SR |= (1u<<3);
    if ((uint32_t)_fb > (uint32_t)_fa) { g_cpu.SR |= (1u<<0); g_cpu.SR |= (1u<<4); }
    if (((_fa^_fb) & 0x00000080u) && ((_fa^_fr) & 0x00000080u)) g_cpu.SR |= (1u<<1); }
  g_cpu.D[7] = (g_cpu.D[7] & 0xFFFFFF00u) | (uint32_t)((uint8_t)_00D4CCr);
}
void snatcher_sub_at_00E046(M68kStepContext *ctx){
  uint16_t _00E046r = (uint16_t)((uint16_t)g_cpu.D[5] + (uint16_t)((uint16_t)g_cpu.D[5]));
  { uint16_t _fa = (uint16_t)((uint16_t)((uint16_t)g_cpu.D[5])), _fb = (uint16_t)((uint16_t)((uint16_t)g_cpu.D[5])), _fr = (uint16_t)(_00E046r);
    g_cpu.SR &= ~(0x1Fu);
    if (!_fr)                        g_cpu.SR |= (1u<<2);
    if (_fr >> 15)                   g_cpu.SR |= (1u<<3);
    if ((uint64_t)_fa + (uint64_t)_fb > 0x0000FFFFu) { g_cpu.SR |= (1u<<0); g_cpu.SR |= (1u<<4); }
    if (!((_fa^_fb) & 0x00008000u) && ((_fa^_fr) & 0x00008000u)) g_cpu.SR |= (1u<<1); }
  g_cpu.D[5] = (g_cpu.D[5] & 0xFFFF0000u) | (uint32_t)((uint16_t)_00E046r);
}
void snatcher_sub_at_00E4B4(M68kStepContext *ctx){
  m68k_write32(0x0007F820u, (uint32_t)((uint32_t)g_cpu.D[1]));
  { uint32_t _fv = (uint32_t)((uint32_t)g_cpu.D[1]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 31)        g_cpu.SR |= (1u<<3); }
}
void snatcher_sub_at_00E9B6(M68kStepContext *ctx){
  g_cpu.D[7] = (g_cpu.D[7] & 0xFFFF0000u) | (uint32_t)((uint16_t)((uint16_t)g_cpu.D[6]));
  { uint16_t _fv = (uint16_t)((uint16_t)g_cpu.D[6]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 15)        g_cpu.SR |= (1u<<3); }
}
void snatcher_sub_at_00EA1E(M68kStepContext *ctx){
  { uint32_t _mbase = g_cpu.A[7];
    g_cpu.D[5] = m68k_read32(_mbase); _mbase += 4;
    g_cpu.D[6] = m68k_read32(_mbase); _mbase += 4;
    g_cpu.D[7] = m68k_read32(_mbase); _mbase += 4;
    g_cpu.A[7] = _mbase; }
}
