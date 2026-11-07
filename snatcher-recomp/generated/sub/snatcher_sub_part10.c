/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_sub_at_00601C(M68kStepContext *ctx){
  { uint32_t target=(0x0000D7EAu)&0xFFFFFFu; ctx->charge=12;
    g_cpu.PC=target; }
}
void snatcher_sub_at_00D80A(M68kStepContext *ctx){
  g_cpu.D[4] = (g_cpu.D[4] & 0xFFFF0000u) | (uint32_t)((uint16_t)((uint16_t)g_cpu.D[0]));
  { uint16_t _fv = (uint16_t)((uint16_t)g_cpu.D[0]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 15)        g_cpu.SR |= (1u<<3); }
}
void snatcher_sub_at_00E422(M68kStepContext *ctx){
  uint16_t _00E422r = (uint16_t)((uint16_t)((uint16_t)g_cpu.D[0]) - (uint16_t)0x2000u);
  { uint16_t _fa = (uint16_t)((uint16_t)((uint16_t)g_cpu.D[0])), _fb = (uint16_t)((uint16_t)0x2000u), _fr = (uint16_t)(_00E422r);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fr)                   g_cpu.SR |= (1u<<2);
    if (_fr >> 15)              g_cpu.SR |= (1u<<3);
    if ((uint32_t)_fb > (uint32_t)_fa) { g_cpu.SR |= (1u<<0); }
    if (((_fa^_fb) & 0x00008000u) && ((_fa^_fr) & 0x00008000u)) g_cpu.SR |= (1u<<1); }
}
void snatcher_sub_at_00E4F2(M68kStepContext *ctx){
  m68k_write32(g_cpu.A[3], (uint32_t)((uint32_t)g_cpu.D[1])); g_cpu.A[3] += 4;
  { uint32_t _fv = (uint32_t)((uint32_t)g_cpu.D[1]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 31)        g_cpu.SR |= (1u<<3); }
}
void snatcher_sub_at_00E9E2(M68kStepContext *ctx){
  g_cpu.D[7] = (g_cpu.D[7] & 0xFFFFFF00u) | (uint32_t)((uint8_t)(0x02u));
  { uint8_t _fv = (uint8_t)(0x02u);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_sub_at_00F276(M68kStepContext *ctx){
  g_cpu.D[7] = 0x00000028u;
  { uint32_t _fv = (uint32_t)((uint32_t)0x00000028u);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 31)        g_cpu.SR |= (1u<<3); }
}
