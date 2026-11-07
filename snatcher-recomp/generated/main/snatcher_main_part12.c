/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_main_at_FF07B4(M68kStepContext *ctx){
  uint32_t _tFF07B4 = m68k_read32(g_cpu.A[0]);
  m68k_write32(g_cpu.A[0], (uint32_t)(0)); g_cpu.A[0] += 4;
  g_cpu.SR = (g_cpu.SR & ~0x0Fu) | (1u<<2);
}
void snatcher_main_at_FF0832(M68kStepContext *ctx){
  ctx->charge=18; g_cpu.A[7]-=4; m68k_write32(g_cpu.A[7],0xFF0834u); g_cpu.PC=0xFF08A8u;
}
void snatcher_main_at_FF08BC(M68kStepContext *ctx){
  ctx->charge=10; g_cpu.PC=0xFF08A0u;
}
void snatcher_main_at_FF1524(M68kStepContext *ctx){
  uint8_t _tFF1524 = m68k_read8(0x00A12013);
  uint8_t _FF1524r = (uint8_t)((uint8_t)(_tFF1524) - (uint8_t)0x1u);
  { uint8_t _fa = (uint8_t)((uint8_t)(_tFF1524)), _fb = (uint8_t)((uint8_t)0x1u), _fr = (uint8_t)(_FF1524r);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fr)                   g_cpu.SR |= (1u<<2);
    if (_fr >> 7)              g_cpu.SR |= (1u<<3);
    if ((uint32_t)_fb > (uint32_t)_fa) { g_cpu.SR |= (1u<<0); }
    if (((_fa^_fb) & 0x00000080u) && ((_fa^_fr) & 0x00000080u)) g_cpu.SR |= (1u<<1); }
}
void snatcher_main_at_FF16CC(M68kStepContext *ctx){
  uint8_t _tFF16CC = m68k_read8(0x00A1200E);
  uint8_t _FF16CCr = 0;
  { uint32_t _bn = 6u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF16CC) & (1u<<_bn)) ? (1u<<2) : 0u);
    _FF16CCr = (uint8_t)((uint8_t)(_tFF16CC) | (uint8_t)(1u<<_bn)); }
  m68k_write8(0x00A1200Eu, (uint8_t)(_FF16CCr));
}
void snatcher_main_at_FF42C0(M68kStepContext *ctx){
  uint16_t _tsFF42C0 = m68k_read16(0x00FF7F5E);
  g_cpu.D[3] = (g_cpu.D[3] & 0xFFFF0000u) | (uint32_t)((uint16_t)(_tsFF42C0));
  { uint16_t _fv = (uint16_t)(_tsFF42C0);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 15)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF4358(M68kStepContext *ctx){
  uint8_t _tFF4358 = m68k_read8((uint32_t)(g_cpu.A[1] + (int32_t)50));
  m68k_write8((uint32_t)(g_cpu.A[1] + (int32_t)50), (uint8_t)(0));
  g_cpu.SR = (g_cpu.SR & ~0x0Fu) | (1u<<2);
}
void snatcher_main_at_FF43E4(M68kStepContext *ctx){
  uint8_t _tFF43E4 = m68k_read8(0x00FF7F30);
  { uint8_t _fv = (uint8_t)(_tFF43E4);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF4482(M68kStepContext *ctx){
  if((g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF448Eu;}else ctx->charge=12;
}
void snatcher_main_at_FF4508(M68kStepContext *ctx){
  uint8_t _tFF4508 = m68k_read8(0x00FF7F2A);
  { uint32_t _bn = 4u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF4508) & (1u<<_bn)) ? (1u<<2) : 0u); }
}
void snatcher_main_at_FF52B0(M68kStepContext *ctx){
  uint8_t _tsFF52B0 = m68k_read8(0x00FF7F20);
  g_cpu.D[2] = (g_cpu.D[2] & 0xFFFFFF00u) | (uint32_t)((uint8_t)(_tsFF52B0));
  { uint8_t _fv = (uint8_t)(_tsFF52B0);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF5454(M68kStepContext *ctx){
  m68k_write8((uint32_t)(g_cpu.A[1] + (int32_t)0), (uint8_t)((uint8_t)g_cpu.D[5]));
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[5]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF5A14(M68kStepContext *ctx){
  uint8_t _tFF5A14 = m68k_read8(0x00FF7F24);
  { uint32_t _bn = 6u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF5A14) & (1u<<_bn)) ? (1u<<2) : 0u); }
}
void snatcher_main_at_FF5A8C(M68kStepContext *ctx){
  m68k_write8((uint32_t)(g_cpu.A[3] + (int32_t)1), (uint8_t)((uint8_t)g_cpu.D[5]));
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[5]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF5C1E(M68kStepContext *ctx){
  ctx->charge=10; g_cpu.PC=0xFF5C9Cu;
}
