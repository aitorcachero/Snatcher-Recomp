/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_main_at_FF07AA(M68kStepContext *ctx){
  g_cpu.A[0] = 0xFFFF7F00u;
}
void snatcher_main_at_FF082A(M68kStepContext *ctx){
  uint8_t _tFF082A = m68k_read8((uint32_t)(g_cpu.A[0] + (int32_t)-1));
  uint8_t _FF082Ar = 0;
  { uint32_t _bn = 0u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF082A) & (1u<<_bn)) ? (1u<<2) : 0u);
    _FF082Ar = (uint8_t)((uint8_t)(_tFF082A) | (uint8_t)(1u<<_bn)); }
  m68k_write8((uint32_t)(g_cpu.A[0] + (int32_t)-1), (uint8_t)(_FF082Ar));
}
void snatcher_main_at_FF08B4(M68kStepContext *ctx){
  g_cpu.A[0] = (uint32_t)(int32_t)(int16_t)0xEB80;
}
void snatcher_main_at_FF1518(M68kStepContext *ctx){
  m68k_write8(0x00A10009u, (uint8_t)((uint8_t)g_cpu.D[7]));
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[7]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF1680(M68kStepContext *ctx){
  m68k_write8(0x00A10005u, (uint8_t)(0x00u));
  { uint8_t _fv = (uint8_t)(0x00u);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF42B6(M68kStepContext *ctx){
  { uint32_t _mbase = g_cpu.A[7];
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
    _mbase -= 4; m68k_write32(_mbase, g_cpu.D[0]);
    g_cpu.A[7] = _mbase; }
}
void snatcher_main_at_FF4350(M68kStepContext *ctx){
  { uint32_t target=(0x00FF5C16u)&0xFFFFFFu; ctx->charge=18;
    g_cpu.A[7]-=4; m68k_write32(g_cpu.A[7],0xFF4354u);
    g_cpu.PC=target; }
}
void snatcher_main_at_FF43DA(M68kStepContext *ctx){
  ctx->charge=10; g_cpu.PC=0xFF43F4u;
}
void snatcher_main_at_FF4476(M68kStepContext *ctx){
  { uint32_t target=(0xFFFF44D2u)&0xFFFFFFu; ctx->charge=20;
    g_cpu.A[7]-=4; m68k_write32(g_cpu.A[7],0xFF447Cu);
    g_cpu.PC=target; }
}
void snatcher_main_at_FF44FA(M68kStepContext *ctx){
  uint8_t _tFF44FA = m68k_read8(0x00FF7F2A);
  uint8_t _FF44FAr = 0;
  { uint32_t _bn = 4u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF44FA) & (1u<<_bn)) ? (1u<<2) : 0u);
    _FF44FAr = (uint8_t)((uint8_t)(_tFF44FA) & ~(uint8_t)(1u<<_bn)); }
  m68k_write8(0x00FF7F2Au, (uint8_t)(_FF44FAr));
}
void snatcher_main_at_FF52A8(M68kStepContext *ctx){
  m68k_write8(0x00FF7F22u, (uint8_t)((uint8_t)g_cpu.D[2]));
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[2]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF5446(M68kStepContext *ctx){
  m68k_write8(0x00FF7F2Fu, (uint8_t)(0x00u));
  { uint8_t _fv = (uint8_t)(0x00u);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF5A08(M68kStepContext *ctx){
  uint8_t _tFF5A08 = m68k_read8(0x00FF7F24);
  { uint32_t _bn = 1u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF5A08) & (1u<<_bn)) ? (1u<<2) : 0u); }
}
void snatcher_main_at_FF5A84(M68kStepContext *ctx){
  uint8_t _tFF5A84 = m68k_read8(g_cpu.A[2]);
  { uint32_t _bn = 7u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF5A84) & (1u<<_bn)) ? (1u<<2) : 0u); }
}
void snatcher_main_at_FF5C16(M68kStepContext *ctx){
  uint8_t _tsFF5C16 = m68k_read8((uint32_t)(g_cpu.A[1] + (int32_t)48));
  g_cpu.D[5] = (g_cpu.D[5] & 0xFFFFFF00u) | (uint32_t)((uint8_t)(_tsFF5C16));
  { uint8_t _fv = (uint8_t)(_tsFF5C16);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
