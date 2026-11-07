/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_sub_at_00D496(M68kStepContext *ctx){
  uint32_t _00D496r = (uint32_t)((uint32_t)g_cpu.D[0]) | (uint32_t)0x800001u;
  { uint32_t _fv = (uint32_t)(_00D496r);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 31)        g_cpu.SR |= (1u<<3); }
  g_cpu.D[0] = (uint32_t)(uint32_t)(_00D496r);
}
void snatcher_sub_at_00DDB8(M68kStepContext *ctx){
  m68k_write16(0x0007F87Au, (uint16_t)(0x0000u));
  { uint16_t _fv = (uint16_t)(0x0000u);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 15)        g_cpu.SR |= (1u<<3); }
}
void snatcher_sub_at_00E492(M68kStepContext *ctx){
  { uint32_t _mbase = g_cpu.A[7];
    g_cpu.A[0] = m68k_read32(_mbase); _mbase += 4;
    g_cpu.A[7] = _mbase; }
}
void snatcher_sub_at_00E9A4(M68kStepContext *ctx){
  g_cpu.D[7] = (g_cpu.D[7] & 0xFFFFFF00u) | (uint32_t)((uint8_t)((uint8_t)g_cpu.D[6]));
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[6]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_sub_at_00EA0A(M68kStepContext *ctx){
  { uint16_t _sv = (uint16_t)g_cpu.D[7];
    uint16_t _00EA0Ar = (8 > 0 && 8 < 16) ? (_sv >> 8) : (8 == 0 ? _sv : (uint16_t)0);
    uint32_t _c = (8 <= 16) ? ((_sv >> (8 - 1)) & 1u) : 0u;
    g_cpu.D[7] = (g_cpu.D[7] & 0xFFFF0000u) | (uint32_t)((uint16_t)_00EA0Ar);
    g_cpu.SR &= ~(0x1Fu);
    if (!_00EA0Ar) g_cpu.SR |= (1u<<2);
    if ((uint32_t)_00EA0Ar >> 15) g_cpu.SR |= (1u<<3);
    if (_c) { g_cpu.SR |= (1u<<0); g_cpu.SR |= (1u<<4); }
  }
}
void snatcher_sub_at_00F56A(M68kStepContext *ctx){
  m68k_write8(0x00FF802Fu, (uint8_t)(0x02u));
  { uint8_t _fv = (uint8_t)(0x02u);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
