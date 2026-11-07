/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_main_at_FF07A4(M68kStepContext *ctx){
  uint16_t _tFF07A4 = m68k_read16(0x00236440);
  m68k_write16(0x00236440u, (uint16_t)(0));
  g_cpu.SR = (g_cpu.SR & ~0x0Fu) | (1u<<2);
}
void snatcher_main_at_FF0828(M68kStepContext *ctx){
  if((g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF0824u;}else ctx->charge=8;
}
void snatcher_main_at_FF08B2(M68kStepContext *ctx){
  ctx->charge=10; g_cpu.PC=0xFF08A0u;
}
void snatcher_main_at_FF1516(M68kStepContext *ctx){
  g_cpu.D[7] = 0x00000040u;
  { uint32_t _fv = (uint32_t)((uint32_t)0x00000040u);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 31)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF1678(M68kStepContext *ctx){
  m68k_write8(0x00A10005u, (uint8_t)(0x10u));
  { uint8_t _fv = (uint8_t)(0x10u);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF42AE(M68kStepContext *ctx){
  uint8_t _tFF42AE = m68k_read8(0x00FF7F2E);
  uint8_t _FF42AEr = 0;
  { uint32_t _bn = 1u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF42AE) & (1u<<_bn)) ? (1u<<2) : 0u);
    _FF42AEr = (uint8_t)((uint8_t)(_tFF42AE) | (uint8_t)(1u<<_bn)); }
  m68k_write8(0x00FF7F2Eu, (uint8_t)(_FF42AEr));
}
void snatcher_main_at_FF434C(M68kStepContext *ctx){
  if((g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF435Cu;}else ctx->charge=12;
}
void snatcher_main_at_FF43D2(M68kStepContext *ctx){
  uint8_t _tFF43D2 = m68k_read8(0x00FF7F2A);
  uint8_t _FF43D2r = 0;
  { uint32_t _bn = 6u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF43D2) & (1u<<_bn)) ? (1u<<2) : 0u);
    _FF43D2r = (uint8_t)((uint8_t)(_tFF43D2) & ~(uint8_t)(1u<<_bn)); }
  m68k_write8(0x00FF7F2Au, (uint8_t)(_FF43D2r));
}
void snatcher_main_at_FF4470(M68kStepContext *ctx){
  { uint32_t target=(0xFFFF4468u)&0xFFFFFFu; ctx->charge=20;
    g_cpu.A[7]-=4; m68k_write32(g_cpu.A[7],0xFF4476u);
    g_cpu.PC=target; }
}
void snatcher_main_at_FF44F6(M68kStepContext *ctx){
  if((g_cpu.SR & (1u<<0))){ctx->charge=10;g_cpu.PC=0xFF4516u;}else ctx->charge=12;
}
void snatcher_main_at_FF52A4(M68kStepContext *ctx){
  if((g_cpu.SR & (1u<<0))){ctx->charge=10;g_cpu.PC=0xFF52ECu;}else ctx->charge=12;
}
void snatcher_main_at_FF5442(M68kStepContext *ctx){
  g_cpu.D[6] = (g_cpu.D[6] & 0xFFFF0000u) | (uint32_t)((uint16_t)(0x0005u));
  { uint16_t _fv = (uint16_t)(0x0005u);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 15)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF5A04(M68kStepContext *ctx){
  ctx->charge=10; g_cpu.PC=0xFF5A90u;
}
void snatcher_main_at_FF5A82(M68kStepContext *ctx){
  m68k_write8(g_cpu.A[3], (uint8_t)((uint8_t)g_cpu.D[4]));
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[4]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF5B10(M68kStepContext *ctx){
  ctx->charge=16; g_cpu.PC=m68k_read32(g_cpu.A[7])&0xFFFFFFu; g_cpu.A[7]+=4;
}
