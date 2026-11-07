/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_sub_at_00D7EA(M68kStepContext *ctx){
  uint8_t _00D7EAr = (uint8_t)((uint8_t)g_cpu.D[0]) | (uint8_t)0x0u;
  { uint8_t _fv = (uint8_t)(_00D7EAr);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
  g_cpu.D[0] = (g_cpu.D[0] & 0xFFFFFF00u) | (uint32_t)((uint8_t)(_00D7EAr));
}
void snatcher_sub_at_00E04E(M68kStepContext *ctx){
  uint16_t _00E04Er = (uint16_t)((uint16_t)((uint16_t)g_cpu.D[5]) + (uint16_t)1u);
  { uint16_t _fa = (uint16_t)((uint16_t)((uint16_t)g_cpu.D[5])), _fb = (uint16_t)((uint16_t)1u), _fr = (uint16_t)(_00E04Er);
    g_cpu.SR &= ~(0x1Fu);
    if (!_fr)                        g_cpu.SR |= (1u<<2);
    if (_fr >> 15)                   g_cpu.SR |= (1u<<3);
    if ((uint64_t)_fa + (uint64_t)_fb > 0x0000FFFFu) { g_cpu.SR |= (1u<<0); g_cpu.SR |= (1u<<4); }
    if (!((_fa^_fb) & 0x00008000u) && ((_fa^_fr) & 0x00008000u)) g_cpu.SR |= (1u<<1); }
  g_cpu.D[5] = (g_cpu.D[5] & 0xFFFF0000u) | (uint32_t)((uint16_t)(_00E04Er));
}
void snatcher_sub_at_00E4C0(M68kStepContext *ctx){
  g_cpu.D[2] = (g_cpu.D[2] & 0xFFFF0000u) | (uint32_t)((uint16_t)((uint16_t)g_cpu.D[1]));
  { uint16_t _fv = (uint16_t)((uint16_t)g_cpu.D[1]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 15)        g_cpu.SR |= (1u<<3); }
}
void snatcher_sub_at_00E9BA(M68kStepContext *ctx){
  m68k_write8((uint32_t)(g_cpu.A[1] + (int32_t)11), (uint8_t)((uint8_t)g_cpu.D[7]));
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[7]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_sub_at_00EEB6(M68kStepContext *ctx){
  uint8_t _00EEB6r = (uint8_t)(g_cpu.A[5]) | (uint8_t)0x0u;
  { uint8_t _fv = (uint8_t)(_00EEB6r);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
  g_cpu.A[5] = (uint32_t)(_00EEB6r);
}
