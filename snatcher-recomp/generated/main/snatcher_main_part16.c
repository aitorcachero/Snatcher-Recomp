/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_main_at_FF07C2(M68kStepContext *ctx){
  g_cpu.A[0] = 0x00236400u;
}
void snatcher_main_at_FF0842(M68kStepContext *ctx){
  m68k_write16((uint32_t)(int32_t)(int16_t)0xE044, (uint16_t)(0x0001u));
  { uint16_t _fv = (uint16_t)(0x0001u);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 15)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF0B2C(M68kStepContext *ctx){
  uint16_t _tFF0B2C = m68k_read16((uint32_t)(int32_t)(int16_t)0xE056);
  { uint16_t _fv = (uint16_t)(_tFF0B2C);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 15)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF1536(M68kStepContext *ctx){
  m68k_write8(0x00A1000Bu, (uint8_t)(0x50u));
  { uint8_t _fv = (uint8_t)(0x50u);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF16E0(M68kStepContext *ctx){
  uint8_t _tsFF16E0 = m68k_read8((uint32_t)(int32_t)(int16_t)0xE055);
  g_cpu.D[0] = (g_cpu.D[0] & 0xFFFFFF00u) | (uint32_t)((uint8_t)(_tsFF16E0));
  { uint8_t _fv = (uint8_t)(_tsFF16E0);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF42D2(M68kStepContext *ctx){
  if((g_cpu.SR & (1u<<0))){ctx->charge=10;g_cpu.PC=0xFF42F8u;}else ctx->charge=12;
}
void snatcher_main_at_FF436A(M68kStepContext *ctx){
  if((g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF437Eu;}else ctx->charge=12;
}
void snatcher_main_at_FF43F8(M68kStepContext *ctx){
  uint8_t _tFF43F8 = m68k_read8(0x00FF7F2E);
  uint8_t _FF43F8r = 0;
  { uint32_t _bn = 1u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF43F8) & (1u<<_bn)) ? (1u<<2) : 0u);
    _FF43F8r = (uint8_t)((uint8_t)(_tFF43F8) & ~(uint8_t)(1u<<_bn)); }
  m68k_write8(0x00FF7F2Eu, (uint8_t)(_FF43F8r));
}
void snatcher_main_at_FF4492(M68kStepContext *ctx){
  if((g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF449Cu;}else ctx->charge=12;
}
void snatcher_main_at_FF451A(M68kStepContext *ctx){
  uint8_t _FF451Ar = (uint8_t)((uint8_t)((uint8_t)g_cpu.D[5]) - (uint8_t)0x60u);
  { uint8_t _fa = (uint8_t)((uint8_t)((uint8_t)g_cpu.D[5])), _fb = (uint8_t)((uint8_t)0x60u), _fr = (uint8_t)(_FF451Ar);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fr)                   g_cpu.SR |= (1u<<2);
    if (_fr >> 7)              g_cpu.SR |= (1u<<3);
    if ((uint32_t)_fb > (uint32_t)_fa) { g_cpu.SR |= (1u<<0); }
    if (((_fa^_fb) & 0x00000080u) && ((_fa^_fr) & 0x00000080u)) g_cpu.SR |= (1u<<1); }
}
void snatcher_main_at_FF52C2(M68kStepContext *ctx){
  uint8_t _tsFF52C2 = m68k_read8(0x00FF7F20);
  g_cpu.D[2] = (g_cpu.D[2] & 0xFFFFFF00u) | (uint32_t)((uint8_t)(_tsFF52C2));
  { uint8_t _fv = (uint8_t)(_tsFF52C2);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF5466(M68kStepContext *ctx){
  g_cpu.A[1] = 0x00FF7A00u;
}
void snatcher_main_at_FF5A2A(M68kStepContext *ctx){
  g_cpu.D[5] = (g_cpu.D[5] & 0xFFFFFF00u) | (uint32_t)((uint8_t)(0xFFu));
  { uint8_t _fv = (uint8_t)(0xFFu);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF5AA0(M68kStepContext *ctx){
  if((g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF5AB0u;}else ctx->charge=12;
}
void snatcher_main_at_FF5CAC(M68kStepContext *ctx){
  uint8_t _FF5CACr = (uint8_t)((uint8_t)g_cpu.D[5]) | (uint8_t)0xC0u;
  { uint8_t _fv = (uint8_t)(_FF5CACr);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
  g_cpu.D[5] = (g_cpu.D[5] & 0xFFFFFF00u) | (uint32_t)((uint8_t)(_FF5CACr));
}
