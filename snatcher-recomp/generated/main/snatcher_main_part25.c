/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_main_at_FF07EE(M68kStepContext *ctx){
  if((g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF07F2u;}else ctx->charge=8;
}
void snatcher_main_at_FF086E(M68kStepContext *ctx){
  ctx->charge=18; g_cpu.A[7]-=4; m68k_write32(g_cpu.A[7],0xFF0872u); g_cpu.PC=0xFF0C5Au;
}
void snatcher_main_at_FF0BB8(M68kStepContext *ctx){
  uint8_t _tFF0BB8 = m68k_read8(0x00A12003);
  uint8_t _FF0BB8r = 0;
  { uint32_t _bn = 1u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF0BB8) & (1u<<_bn)) ? (1u<<2) : 0u);
    _FF0BB8r = (uint8_t)((uint8_t)(_tFF0BB8) | (uint8_t)(1u<<_bn)); }
  m68k_write8(0x00A12003u, (uint8_t)(_FF0BB8r));
}
void snatcher_main_at_FF1566(M68kStepContext *ctx){
  g_cpu.D[7] = 0x00000000u;
  { uint32_t _fv = (uint32_t)((uint32_t)0x00000000u);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 31)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF1706(M68kStepContext *ctx){
  g_cpu.A[0] = 0x00FF1784u;
}
void snatcher_main_at_FF4300(M68kStepContext *ctx){
  if(!(g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF43DEu;}else ctx->charge=12;
}
void snatcher_main_at_FF438A(M68kStepContext *ctx){
  uint8_t _tFF438A = m68k_read8((uint32_t)(g_cpu.A[1] + (int32_t)36));
  m68k_write8((uint32_t)(g_cpu.A[1] + (int32_t)36), (uint8_t)(0));
  g_cpu.SR = (g_cpu.SR & ~0x0Fu) | (1u<<2);
}
void snatcher_main_at_FF4420(M68kStepContext *ctx){
  { uint32_t target=(0xFFFF43ACu)&0xFFFFFFu; ctx->charge=20;
    g_cpu.A[7]-=4; m68k_write32(g_cpu.A[7],0xFF4426u);
    g_cpu.PC=target; }
}
void snatcher_main_at_FF44BC(M68kStepContext *ctx){
  m68k_write8((uint32_t)(g_cpu.A[1] + (int32_t)305), (uint8_t)((uint8_t)g_cpu.D[0]));
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[0]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF526A(M68kStepContext *ctx){
  { uint32_t _mbase = g_cpu.A[7];
    _mbase -= 4; m68k_write32(_mbase, g_cpu.A[7]);
    _mbase -= 4; m68k_write32(_mbase, g_cpu.A[6]);
    _mbase -= 4; m68k_write32(_mbase, g_cpu.A[5]);
    _mbase -= 4; m68k_write32(_mbase, g_cpu.A[4]);
    _mbase -= 4; m68k_write32(_mbase, g_cpu.A[3]);
    _mbase -= 4; m68k_write32(_mbase, g_cpu.A[2]);
    _mbase -= 4; m68k_write32(_mbase, g_cpu.A[1]);
    _mbase -= 4; m68k_write32(_mbase, g_cpu.A[0]);
    _mbase -= 4; m68k_write32(_mbase, g_cpu.D[7]);
    _mbase -= 4; m68k_write32(_mbase, g_cpu.D[6]);
    _mbase -= 4; m68k_write32(_mbase, g_cpu.D[5]);
    _mbase -= 4; m68k_write32(_mbase, g_cpu.D[4]);
    _mbase -= 4; m68k_write32(_mbase, g_cpu.D[3]);
    _mbase -= 4; m68k_write32(_mbase, g_cpu.D[2]);
    _mbase -= 4; m68k_write32(_mbase, g_cpu.D[1]);
    g_cpu.A[7] = _mbase; }
}
void snatcher_main_at_FF52F0(M68kStepContext *ctx){
  uint8_t _tFF52F0 = m68k_read8(0x00FF7F2A);
  { uint32_t _bn = 2u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF52F0) & (1u<<_bn)) ? (1u<<2) : 0u); }
}
void snatcher_main_at_FF5498(M68kStepContext *ctx){
  m68k_write8((uint32_t)(g_cpu.A[1] + (int32_t)1), (uint8_t)((uint8_t)g_cpu.D[5]));
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[5]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF5A4A(M68kStepContext *ctx){
  uint8_t _tFF5A4A = m68k_read8(g_cpu.A[2]);
  { uint32_t _bn = 7u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF5A4A) & (1u<<_bn)) ? (1u<<2) : 0u); }
}
void snatcher_main_at_FF5ACC(M68kStepContext *ctx){
  uint8_t _tFF5ACC = m68k_read8(0x00FF7F24);
  { uint32_t _bn = 1u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF5ACC) & (1u<<_bn)) ? (1u<<2) : 0u); }
}
void snatcher_main_at_FF5CD0(M68kStepContext *ctx){
  m68k_write8((uint32_t)(g_cpu.A[3] + (int32_t)1), (uint8_t)((uint8_t)g_cpu.D[5]));
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[5]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
