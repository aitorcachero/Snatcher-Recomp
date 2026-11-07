/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_main_at_FF07F2(M68kStepContext *ctx){
  uint8_t _tFF07F2 = m68k_read8(g_cpu.A[0]);
  uint8_t _FF07F2r = 0;
  { uint32_t _bn = 1u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF07F2) & (1u<<_bn)) ? (1u<<2) : 0u);
    _FF07F2r = (uint8_t)((uint8_t)(_tFF07F2) | (uint8_t)(1u<<_bn)); }
  m68k_write8(g_cpu.A[0], (uint8_t)(_FF07F2r));
}
void snatcher_main_at_FF0878(M68kStepContext *ctx){
  uint16_t _FF0878r = (uint16_t)((uint16_t)g_cpu.D[0]) | (uint16_t)0x24u;
  { uint16_t _fv = (uint16_t)(_FF0878r);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 15)        g_cpu.SR |= (1u<<3); }
  g_cpu.D[0] = (g_cpu.D[0] & 0xFFFF0000u) | (uint32_t)((uint16_t)(_FF0878r));
}
void snatcher_main_at_FF0BC8(M68kStepContext *ctx){
  if((g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF0BB8u;}else ctx->charge=8;
}
void snatcher_main_at_FF156A(M68kStepContext *ctx){
  uint8_t _tsFF156A = m68k_read8(g_cpu.A[5]); g_cpu.A[5] += 1;
  m68k_write8(g_cpu.A[6], (uint8_t)(_tsFF156A));
  { uint8_t _fv = (uint8_t)(_tsFF156A);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF170C(M68kStepContext *ctx){
  uint16_t _tsFF170C = m68k_read16(g_cpu.A[0]); g_cpu.A[0] += 2;
  m68k_write16(0x00C00004u, (uint16_t)(_tsFF170C));
  { uint16_t _fv = (uint16_t)(_tsFF170C);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 15)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF430C(M68kStepContext *ctx){
  { uint32_t target=(0x00FF543Au)&0xFFFFFFu; ctx->charge=18;
    g_cpu.A[7]-=4; m68k_write32(g_cpu.A[7],0xFF4310u);
    g_cpu.PC=target; }
}
void snatcher_main_at_FF4392(M68kStepContext *ctx){
  { uint32_t target=(0x00FF445Au)&0xFFFFFFu; ctx->charge=18;
    g_cpu.A[7]-=4; m68k_write32(g_cpu.A[7],0xFF4396u);
    g_cpu.PC=target; }
}
void snatcher_main_at_FF442A(M68kStepContext *ctx){
  if((g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF4434u;}else ctx->charge=12;
}
void snatcher_main_at_FF44C4(M68kStepContext *ctx){
  m68k_write8((uint32_t)(g_cpu.A[1] + (int32_t)561), (uint8_t)((uint8_t)g_cpu.D[0]));
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[0]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF5272(M68kStepContext *ctx){
  if(!(g_cpu.SR & (1u<<0))){ctx->charge=10;g_cpu.PC=0xFF5382u;}else ctx->charge=12;
}
void snatcher_main_at_FF52FC(M68kStepContext *ctx){
  uint8_t _tFF52FC = m68k_read8(0x00FF7F2E);
  uint8_t _FF52FCr = 0;
  { uint32_t _bn = 0u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF52FC) & (1u<<_bn)) ? (1u<<2) : 0u);
    _FF52FCr = (uint8_t)((uint8_t)(_tFF52FC) & ~(uint8_t)(1u<<_bn)); }
  m68k_write8(0x00FF7F2Eu, (uint8_t)(_FF52FCr));
}
void snatcher_main_at_FF54A2(M68kStepContext *ctx){
  m68k_write8((uint32_t)(g_cpu.A[1] + (int32_t)0), (uint8_t)((uint8_t)g_cpu.D[5]));
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[5]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF5A52(M68kStepContext *ctx){
  m68k_write8(g_cpu.A[3], (uint8_t)((uint8_t)g_cpu.D[4]));
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[4]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF5AD8(M68kStepContext *ctx){
  uint8_t _tFF5AD8 = m68k_read8(0x00FF7F24);
  { uint32_t _bn = 6u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF5AD8) & (1u<<_bn)) ? (1u<<2) : 0u); }
}
