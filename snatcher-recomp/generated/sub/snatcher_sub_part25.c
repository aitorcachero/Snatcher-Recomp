/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_sub_at_00D4C0(M68kStepContext *ctx){
  uint8_t _00D4C0r = (uint8_t)((uint8_t)g_cpu.D[0]) | (uint8_t)0xCu;
  { uint8_t _fv = (uint8_t)(_00D4C0r);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
  g_cpu.D[0] = (g_cpu.D[0] & 0xFFFFFF00u) | (uint32_t)((uint8_t)(_00D4C0r));
}
void snatcher_sub_at_00DDCA(M68kStepContext *ctx){
  m68k_write16(g_cpu.A[3], (uint16_t)(0xFFFFu)); g_cpu.A[3] += 2;
  { uint16_t _fv = (uint16_t)(0xFFFFu);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 15)        g_cpu.SR |= (1u<<3); }
}
void snatcher_sub_at_00E4A6(M68kStepContext *ctx){
  uint32_t _ts00E4A6 = m68k_read32(0x0007F820);
  g_cpu.D[0] = (uint32_t)(uint32_t)(_ts00E4A6);
  { uint32_t _fv = (uint32_t)(_ts00E4A6);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 31)        g_cpu.SR |= (1u<<3); }
}
void snatcher_sub_at_00E9AE(M68kStepContext *ctx){
  g_cpu.D[7] = (g_cpu.D[7] & 0xFFFFFF00u) | (uint32_t)((uint8_t)((uint8_t)g_cpu.D[5]));
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[5]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_sub_at_00EA14(M68kStepContext *ctx){
  g_cpu.D[7] = (g_cpu.D[7] & 0xFFFFFF00u) | (uint32_t)((uint8_t)((uint8_t)g_cpu.D[6]));
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[6]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
