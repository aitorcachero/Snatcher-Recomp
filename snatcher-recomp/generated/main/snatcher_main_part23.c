/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_main_at_FF07E4(M68kStepContext *ctx){
  g_cpu.A[0] = 0x00A12003u;
}
void snatcher_main_at_FF0864(M68kStepContext *ctx){
  uint16_t _tFF0864 = m68k_read16(0x00A1200E);
  m68k_write16(0x00A1200Eu, (uint16_t)(0));
  g_cpu.SR = (g_cpu.SR & ~0x0Fu) | (1u<<2);
}
void snatcher_main_at_FF0B48(M68kStepContext *ctx){
  { uint32_t _mbase = g_cpu.A[7];
    g_cpu.D[0] = m68k_read32(_mbase); _mbase += 4;
    g_cpu.D[1] = m68k_read32(_mbase); _mbase += 4;
    g_cpu.D[2] = m68k_read32(_mbase); _mbase += 4;
    g_cpu.D[3] = m68k_read32(_mbase); _mbase += 4;
    g_cpu.D[4] = m68k_read32(_mbase); _mbase += 4;
    g_cpu.D[5] = m68k_read32(_mbase); _mbase += 4;
    g_cpu.D[6] = m68k_read32(_mbase); _mbase += 4;
    g_cpu.D[7] = m68k_read32(_mbase); _mbase += 4;
    g_cpu.A[0] = m68k_read32(_mbase); _mbase += 4;
    g_cpu.A[1] = m68k_read32(_mbase); _mbase += 4;
    g_cpu.A[2] = m68k_read32(_mbase); _mbase += 4;
    g_cpu.A[3] = m68k_read32(_mbase); _mbase += 4;
    g_cpu.A[4] = m68k_read32(_mbase); _mbase += 4;
    g_cpu.A[5] = m68k_read32(_mbase); _mbase += 4;
    g_cpu.A[6] = m68k_read32(_mbase); _mbase += 4;
    g_cpu.A[7] = _mbase; }
}
void snatcher_main_at_FF155E(M68kStepContext *ctx){
  g_cpu.A[5] = 0x00FF1586u;
}
void snatcher_main_at_FF16FE(M68kStepContext *ctx){
  uint8_t _tFF16FE = m68k_read8((uint32_t)(int32_t)(int16_t)0xE0E0);
  uint8_t _FF16FEr = 0;
  { uint32_t _bn = 0u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF16FE) & (1u<<_bn)) ? (1u<<2) : 0u);
    _FF16FEr = (uint8_t)((uint8_t)(_tFF16FE) | (uint8_t)(1u<<_bn)); }
  m68k_write8((uint32_t)(int32_t)(int16_t)0xE0E0, (uint8_t)(_FF16FEr));
}
void snatcher_main_at_FF42F4(M68kStepContext *ctx){
  ctx->charge=10; g_cpu.PC=0xFF4314u;
}
void snatcher_main_at_FF4382(M68kStepContext *ctx){
  uint8_t _tFF4382 = m68k_read8((uint32_t)(g_cpu.A[1] + (int32_t)5));
  uint8_t _FF4382r = (uint8_t)((uint8_t)(_tFF4382) + (uint8_t)g_cpu.D[6]);
  { uint8_t _fa = (uint8_t)((uint8_t)(_tFF4382)), _fb = (uint8_t)((uint8_t)g_cpu.D[6]), _fr = (uint8_t)(_FF4382r);
    g_cpu.SR &= ~(0x1Fu);
    if (!_fr)                        g_cpu.SR |= (1u<<2);
    if (_fr >> 7)                   g_cpu.SR |= (1u<<3);
    if ((uint64_t)_fa + (uint64_t)_fb > 0x000000FFu) { g_cpu.SR |= (1u<<0); g_cpu.SR |= (1u<<4); }
    if (!((_fa^_fb) & 0x00000080u) && ((_fa^_fr) & 0x00000080u)) g_cpu.SR |= (1u<<1); }
  m68k_write8((uint32_t)(g_cpu.A[1] + (int32_t)5), (uint8_t)(_FF4382r));
}
void snatcher_main_at_FF4418(M68kStepContext *ctx){
  uint8_t _tFF4418 = m68k_read8((uint32_t)(g_cpu.A[1] + (int32_t)44));
  { uint8_t _fv = (uint8_t)(_tFF4418);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF44B4(M68kStepContext *ctx){
  m68k_write8((uint32_t)(g_cpu.A[1] + (int32_t)49), (uint8_t)((uint8_t)g_cpu.D[0]));
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[0]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF5260(M68kStepContext *ctx){
  uint32_t _FF5260r = (uint32_t)((uint32_t)g_cpu.D[0]) & (uint32_t)0xFFu;
  { uint32_t _fv = (uint32_t)(_FF5260r);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 31)        g_cpu.SR |= (1u<<3); }
  g_cpu.D[0] = (uint32_t)(uint32_t)(_FF5260r);
}
void snatcher_main_at_FF52E4(M68kStepContext *ctx){
  m68k_write8(0x00FF7F20u, (uint8_t)(0x00u));
  { uint8_t _fv = (uint8_t)(0x00u);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF548E(M68kStepContext *ctx){
  g_cpu.A[1] = 0x00FF7D00u;
}
void snatcher_main_at_FF5A44(M68kStepContext *ctx){
  m68k_write8((uint32_t)(g_cpu.A[3] + (int32_t)1), (uint8_t)((uint8_t)g_cpu.D[5]));
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[5]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF5AC4(M68kStepContext *ctx){
  if(!(g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF5AE8u;}else ctx->charge=12;
}
void snatcher_main_at_FF5CC8(M68kStepContext *ctx){
  uint8_t _tFF5CC8 = m68k_read8(g_cpu.A[2]);
  { uint32_t _bn = 7u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF5CC8) & (1u<<_bn)) ? (1u<<2) : 0u); }
}
