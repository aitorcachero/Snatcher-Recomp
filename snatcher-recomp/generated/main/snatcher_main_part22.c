/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_main_at_FF07DC(M68kStepContext *ctx){
  m68k_write16(0x00A12006u, (uint16_t)(0x08E2u));
  { uint16_t _fv = (uint16_t)(0x08E2u);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 15)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF085C(M68kStepContext *ctx){
  m68k_write32((uint32_t)(int32_t)(int16_t)0xE0EC, (uint32_t)(0xFFFFBC00u));
  { uint32_t _fv = (uint32_t)(0xFFFFBC00u);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 31)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF0B44(M68kStepContext *ctx){
  { uint32_t target=(0x00FF428Au)&0xFFFFFFu; ctx->charge=18;
    g_cpu.A[7]-=4; m68k_write32(g_cpu.A[7],0xFF0B48u);
    g_cpu.PC=target; }
}
void snatcher_main_at_FF155A(M68kStepContext *ctx){
  if(!m68k_step_supervisor(ctx))return;
  ctx->charge=20;
  m68k_step_set_sr(ctx,(uint16_t)(g_cpu.SR|0x0700u));
}
void snatcher_main_at_FF16FA(M68kStepContext *ctx){
  uint16_t _tFF16FA = m68k_read16((uint32_t)(int32_t)(int16_t)0xE058);
  m68k_write16((uint32_t)(int32_t)(int16_t)0xE058, (uint16_t)(0));
  g_cpu.SR = (g_cpu.SR & ~0x0Fu) | (1u<<2);
}
void snatcher_main_at_FF42EC(M68kStepContext *ctx){
  uint8_t _tFF42EC = m68k_read8(0x00FF7F24);
  uint8_t _FF42ECr = 0;
  { uint32_t _bn = 3u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF42EC) & (1u<<_bn)) ? (1u<<2) : 0u);
    _FF42ECr = (uint8_t)((uint8_t)(_tFF42EC) & ~(uint8_t)(1u<<_bn)); }
  m68k_write8(0x00FF7F24u, (uint8_t)(_FF42ECr));
}
void snatcher_main_at_FF437E(M68kStepContext *ctx){
  uint8_t _tsFF437E = m68k_read8((uint32_t)(g_cpu.A[1] + (int32_t)4));
  g_cpu.D[6] = (g_cpu.D[6] & 0xFFFFFF00u) | (uint32_t)((uint8_t)(_tsFF437E));
  { uint8_t _fv = (uint8_t)(_tsFF437E);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF4412(M68kStepContext *ctx){
  { uint32_t target=(0xFFFF4372u)&0xFFFFFFu; ctx->charge=20;
    g_cpu.A[7]-=4; m68k_write32(g_cpu.A[7],0xFF4418u);
    g_cpu.PC=target; }
}
void snatcher_main_at_FF44B2(M68kStepContext *ctx){
  g_cpu.D[0] = 0x00000001u;
  { uint32_t _fv = (uint32_t)((uint32_t)0x00000001u);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 31)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF5258(M68kStepContext *ctx){
  uint8_t _tFF5258 = m68k_read8(0x00FF7F2E);
  uint8_t _FF5258r = 0;
  { uint32_t _bn = 0u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF5258) & (1u<<_bn)) ? (1u<<2) : 0u);
    _FF5258r = (uint8_t)((uint8_t)(_tFF5258) | (uint8_t)(1u<<_bn)); }
  m68k_write8(0x00FF7F2Eu, (uint8_t)(_FF5258r));
}
void snatcher_main_at_FF52E0(M68kStepContext *ctx){
  if(!(g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF52ECu;}else ctx->charge=12;
}
void snatcher_main_at_FF5488(M68kStepContext *ctx){
  m68k_write8(0x00FF7F30u, (uint8_t)((uint8_t)g_cpu.D[5]));
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[5]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF5A40(M68kStepContext *ctx){
  if(!(g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF5A3Cu;}else ctx->charge=12;
}
void snatcher_main_at_FF5ABC(M68kStepContext *ctx){
  uint8_t _tFF5ABC = m68k_read8(0x00FF7F24);
  { uint32_t _bn = 6u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF5ABC) & (1u<<_bn)) ? (1u<<2) : 0u); }
}
void snatcher_main_at_FF5CC6(M68kStepContext *ctx){
  m68k_write8(g_cpu.A[3], (uint8_t)((uint8_t)g_cpu.D[4]));
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[4]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
