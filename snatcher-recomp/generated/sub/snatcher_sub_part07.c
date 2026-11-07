/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_sub_at_006012(M68kStepContext *ctx){
  uint8_t _006012r = (uint8_t)((uint8_t)g_cpu.D[0]) | (uint8_t)0x46u;
  { uint8_t _fv = (uint8_t)(_006012r);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
  g_cpu.D[0] = (g_cpu.D[0] & 0xFFFFFF00u) | (uint32_t)((uint8_t)(_006012r));
}
void snatcher_sub_at_00D802(M68kStepContext *ctx){
  g_cpu.D[6] = (g_cpu.D[6] & 0xFFFF0000u) | (uint32_t)((uint16_t)((uint16_t)g_cpu.D[0]));
  { uint16_t _fv = (uint16_t)((uint16_t)g_cpu.D[0]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 15)        g_cpu.SR |= (1u<<3); }
}
void snatcher_sub_at_00E41A(M68kStepContext *ctx){
  uint16_t _ts00E41A = m68k_read16(g_cpu.A[3]); g_cpu.A[3] += 2;
  g_cpu.D[0] = (g_cpu.D[0] & 0xFFFF0000u) | (uint32_t)((uint16_t)(_ts00E41A));
  { uint16_t _fv = (uint16_t)(_ts00E41A);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 15)        g_cpu.SR |= (1u<<3); }
}
void snatcher_sub_at_00E4E8(M68kStepContext *ctx){
  g_cpu.A[3] = (uint32_t)(0x0007F828u);
}
void snatcher_sub_at_00E9D8(M68kStepContext *ctx){
  uint8_t _00E9D8r = (uint8_t)((uint8_t)g_cpu.D[5]) & (uint8_t)0x3u;
  { uint8_t _fv = (uint8_t)(_00E9D8r);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
  g_cpu.D[5] = (g_cpu.D[5] & 0xFFFFFF00u) | (uint32_t)((uint8_t)(_00E9D8r));
}
void snatcher_sub_at_00EED6(M68kStepContext *ctx){
  uint8_t _ts00EED6 = m68k_read8(0x0007F807);
  m68k_write8((uint32_t)(g_cpu.A[0] + m68k_brief_index_value(0x3014u, g_cpu.D[3], g_cpu.A[3]) + (20)), (uint8_t)(_ts00EED6));
  { uint8_t _fv = (uint8_t)(_ts00EED6);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
