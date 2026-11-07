/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_main_at_FF07CC(M68kStepContext *ctx){
  uint32_t _tFF07CC = m68k_read32(g_cpu.A[0]);
  m68k_write32(g_cpu.A[0], (uint32_t)(0)); g_cpu.A[0] += 4;
  g_cpu.SR = (g_cpu.SR & ~0x0Fu) | (1u<<2);
}
void snatcher_main_at_FF084E(M68kStepContext *ctx){
  ctx->charge=18; g_cpu.A[7]-=4; m68k_write32(g_cpu.A[7],0xFF0850u); g_cpu.PC=0xFF08B4u;
}
void snatcher_main_at_FF0B32(M68kStepContext *ctx){
  { uint32_t target=(0x00FF1678u)&0xFFFFFFu; ctx->charge=18;
    g_cpu.A[7]-=4; m68k_write32(g_cpu.A[7],0xFF0B36u);
    g_cpu.PC=target; }
}
void snatcher_main_at_FF1546(M68kStepContext *ctx){
  m68k_write8(0x00A10005u, (uint8_t)(0x30u));
  { uint8_t _fv = (uint8_t)(0x30u);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF16E6(M68kStepContext *ctx){
  m68k_write8(0x00A12016u, (uint8_t)((uint8_t)g_cpu.D[0]));
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[0]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF42DC(M68kStepContext *ctx){
  uint16_t _FF42DCr = (uint16_t)((uint16_t)g_cpu.D[3]) & (uint16_t)0xFFu;
  { uint16_t _fv = (uint16_t)(_FF42DCr);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 15)        g_cpu.SR |= (1u<<3); }
  g_cpu.D[3] = (g_cpu.D[3] & 0xFFFF0000u) | (uint32_t)((uint16_t)(_FF42DCr));
}
void snatcher_main_at_FF4372(M68kStepContext *ctx){
  g_cpu.D[6] = (g_cpu.D[6] & 0xFFFFFF00u) | (uint32_t)((uint8_t)((uint8_t)g_cpu.D[3]));
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[3]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF4402(M68kStepContext *ctx){
  uint8_t _tFF4402 = m68k_read8((uint32_t)(g_cpu.A[1] + (int32_t)30));
  uint8_t _FF4402r = (uint8_t)((uint8_t)(_tFF4402) - (uint8_t)1u);
  { uint8_t _fa = (uint8_t)((uint8_t)(_tFF4402)), _fb = (uint8_t)((uint8_t)1u), _fr = (uint8_t)(_FF4402r);
    g_cpu.SR &= ~(0x1Fu);
    if (!_fr)                   g_cpu.SR |= (1u<<2);
    if (_fr >> 7)              g_cpu.SR |= (1u<<3);
    if ((uint32_t)_fb > (uint32_t)_fa) { g_cpu.SR |= (1u<<0); g_cpu.SR |= (1u<<4); }
    if (((_fa^_fb) & 0x00000080u) && ((_fa^_fr) & 0x00000080u)) g_cpu.SR |= (1u<<1); }
  m68k_write8((uint32_t)(g_cpu.A[1] + (int32_t)30), (uint8_t)(_FF4402r));
}
void snatcher_main_at_FF449C(M68kStepContext *ctx){
  uint16_t _tFF449C = m68k_read16(0x00FF7F5E);
  uint16_t _FF449Cr = (uint16_t)((uint16_t)(_tFF449C) - (uint16_t)0xFFFFu);
  { uint16_t _fa = (uint16_t)((uint16_t)(_tFF449C)), _fb = (uint16_t)((uint16_t)0xFFFFu), _fr = (uint16_t)(_FF449Cr);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fr)                   g_cpu.SR |= (1u<<2);
    if (_fr >> 15)              g_cpu.SR |= (1u<<3);
    if ((uint32_t)_fb > (uint32_t)_fa) { g_cpu.SR |= (1u<<0); }
    if (((_fa^_fb) & 0x00008000u) && ((_fa^_fr) & 0x00008000u)) g_cpu.SR |= (1u<<1); }
}
void snatcher_main_at_FF4522(M68kStepContext *ctx){
  { uint32_t target=(0xFFFF4662u)&0xFFFFFFu; ctx->charge=20;
    g_cpu.A[7]-=4; m68k_write32(g_cpu.A[7],0xFF4528u);
    g_cpu.PC=target; }
}
void snatcher_main_at_FF52CE(M68kStepContext *ctx){
  g_cpu.A[0] += (uint32_t)((uint32_t)g_cpu.D[2]);
}
void snatcher_main_at_FF5470(M68kStepContext *ctx){
  m68k_write8((uint32_t)(g_cpu.A[1] + (int32_t)50), (uint8_t)(0x01u));
  { uint8_t _fv = (uint8_t)(0x01u);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF5A32(M68kStepContext *ctx){
  uint8_t _tFF5A32 = m68k_read8(g_cpu.A[2]);
  { uint32_t _bn = 7u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF5A32) & (1u<<_bn)) ? (1u<<2) : 0u); }
}
void snatcher_main_at_FF5AA8(M68kStepContext *ctx){
  if((g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF5ACCu;}else ctx->charge=12;
}
void snatcher_main_at_FF5CB4(M68kStepContext *ctx){
  uint8_t _tsFF5CB4 = m68k_read8(0x00FF7F2D);
  g_cpu.D[4] = (g_cpu.D[4] & 0xFFFFFF00u) | (uint32_t)((uint8_t)(_tsFF5CB4));
  { uint8_t _fv = (uint8_t)(_tsFF5CB4);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
