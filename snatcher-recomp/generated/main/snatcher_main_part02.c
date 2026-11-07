/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_main_at_FF0208(M68kStepContext *ctx){
  ctx->charge=10; g_cpu.PC=0xFF0784u;
}
void snatcher_main_at_FF080A(M68kStepContext *ctx){
  g_cpu.A[0] = 0x00A12010u;
}
void snatcher_main_at_FF0898(M68kStepContext *ctx){
  g_cpu.A[0] = (uint32_t)(int32_t)(int16_t)0xE000;
}
void snatcher_main_at_FF0C5E(M68kStepContext *ctx){
  g_cpu.A[6] = 0x00A10003u;
}
void snatcher_main_at_FF1578(M68kStepContext *ctx){
  uint8_t _tFF1578 = m68k_read8(g_cpu.A[5]); g_cpu.A[5] += 1;
  uint8_t _FF1578r = (uint8_t)g_cpu.D[2] & (uint8_t)(_tFF1578);
  g_cpu.D[2] = (g_cpu.D[2] & 0xFFFFFF00u) | (uint32_t)((uint8_t)_FF1578r);
  { uint8_t _fv = (uint8_t)(_FF1578r);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF1726(M68kStepContext *ctx){
  ctx->charge=16; g_cpu.PC=m68k_read32(g_cpu.A[7])&0xFFFFFFu; g_cpu.A[7]+=4;
}
void snatcher_main_at_FF432E(M68kStepContext *ctx){
  g_cpu.D[3] = 0x00000000u;
  { uint32_t _fv = (uint32_t)((uint32_t)0x00000000u);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 31)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF43B0(M68kStepContext *ctx){
  g_cpu.A[1] += (uint32_t)(0x00000080u);
}
void snatcher_main_at_FF444A(M68kStepContext *ctx){
  uint8_t _tFF444A = m68k_read8((uint32_t)(g_cpu.A[1] + (int32_t)30));
  uint8_t _FF444Ar = (uint8_t)((uint8_t)(_tFF444A) - (uint8_t)0x1u);
  { uint8_t _fa = (uint8_t)((uint8_t)(_tFF444A)), _fb = (uint8_t)((uint8_t)0x1u), _fr = (uint8_t)(_FF444Ar);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fr)                   g_cpu.SR |= (1u<<2);
    if (_fr >> 7)              g_cpu.SR |= (1u<<3);
    if ((uint32_t)_fb > (uint32_t)_fa) { g_cpu.SR |= (1u<<0); }
    if (((_fa^_fb) & 0x00000080u) && ((_fa^_fr) & 0x00000080u)) g_cpu.SR |= (1u<<1); }
}
void snatcher_main_at_FF44E0(M68kStepContext *ctx){
  { uint32_t target=(0xFFFF451Au)&0xFFFFFFu; ctx->charge=20;
    g_cpu.A[7]-=4; m68k_write32(g_cpu.A[7],0xFF44E6u);
    g_cpu.PC=target; }
}
void snatcher_main_at_FF528E(M68kStepContext *ctx){
  g_cpu.D[6] = (g_cpu.D[6] & 0xFFFF0000u) | (uint32_t)((uint16_t)((uint16_t)g_cpu.D[0]));
  { uint16_t _fv = (uint16_t)((uint16_t)g_cpu.D[0]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 15)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF5390(M68kStepContext *ctx){
  { uint32_t target=(g_cpu.A[6])&0xFFFFFFu; ctx->charge=16;
    g_cpu.A[7]-=4; m68k_write32(g_cpu.A[7],0xFF5392u);
    g_cpu.PC=target; }
}
void snatcher_main_at_FF59E0(M68kStepContext *ctx){
  uint8_t _FF59E0r = (uint8_t)((uint8_t)((uint8_t)g_cpu.D[3]) - (uint8_t)0x5u);
  { uint8_t _fa = (uint8_t)((uint8_t)((uint8_t)g_cpu.D[3])), _fb = (uint8_t)((uint8_t)0x5u), _fr = (uint8_t)(_FF59E0r);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fr)                   g_cpu.SR |= (1u<<2);
    if (_fr >> 7)              g_cpu.SR |= (1u<<3);
    if ((uint32_t)_fb > (uint32_t)_fa) { g_cpu.SR |= (1u<<0); }
    if (((_fa^_fb) & 0x00000080u) && ((_fa^_fr) & 0x00000080u)) g_cpu.SR |= (1u<<1); }
}
void snatcher_main_at_FF5A6A(M68kStepContext *ctx){
  m68k_write8(g_cpu.A[3], (uint8_t)((uint8_t)g_cpu.D[4]));
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[4]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF5AF6(M68kStepContext *ctx){
  uint8_t _tsFF5AF6 = m68k_read8((uint32_t)(0x00FF5AF8 + m68k_brief_index_value(0x301Au, g_cpu.D[3], g_cpu.A[3]) + (26)));
  g_cpu.D[5] = (g_cpu.D[5] & 0xFFFFFF00u) | (uint32_t)((uint8_t)(_tsFF5AF6));
  { uint8_t _fv = (uint8_t)(_tsFF5AF6);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
