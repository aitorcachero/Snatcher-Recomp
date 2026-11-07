/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_main_at_FF07EA(M68kStepContext *ctx){
  uint8_t _tFF07EA = m68k_read8(g_cpu.A[0]);
  { uint32_t _bn = 2u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF07EA) & (1u<<_bn)) ? (1u<<2) : 0u); }
}
void snatcher_main_at_FF086A(M68kStepContext *ctx){
  { uint32_t target=(0x00FF1706u)&0xFFFFFFu; ctx->charge=18;
    g_cpu.A[7]-=4; m68k_write32(g_cpu.A[7],0xFF086Eu);
    g_cpu.PC=target; }
}
void snatcher_main_at_FF0B4C(M68kStepContext *ctx){
  ctx->charge=20; m68k_step_rte(ctx);
}
void snatcher_main_at_FF1562(M68kStepContext *ctx){
  uint8_t _tsFF1562 = m68k_read8(g_cpu.A[5]);
  m68k_write8((uint32_t)(g_cpu.A[6] + (int32_t)6), (uint8_t)(_tsFF1562));
  { uint8_t _fv = (uint8_t)(_tsFF1562);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF1704(M68kStepContext *ctx){
  ctx->charge=16; g_cpu.PC=m68k_read32(g_cpu.A[7])&0xFFFFFFu; g_cpu.A[7]+=4;
}
void snatcher_main_at_FF42F8(M68kStepContext *ctx){
  uint8_t _tFF42F8 = m68k_read8(0x00FF7F24);
  { uint32_t _bn = 3u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF42F8) & (1u<<_bn)) ? (1u<<2) : 0u); }
}
void snatcher_main_at_FF4386(M68kStepContext *ctx){
  if((g_cpu.SR & (1u<<0))){ctx->charge=10;g_cpu.PC=0xFF439Eu;}else ctx->charge=12;
}
void snatcher_main_at_FF441C(M68kStepContext *ctx){
  if((g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF4426u;}else ctx->charge=12;
}
void snatcher_main_at_FF44B8(M68kStepContext *ctx){
  m68k_write8((uint32_t)(g_cpu.A[1] + (int32_t)177), (uint8_t)((uint8_t)g_cpu.D[0]));
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[0]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF5266(M68kStepContext *ctx){
  if((g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF52FCu;}else ctx->charge=12;
}
void snatcher_main_at_FF52EC(M68kStepContext *ctx){
  { uint32_t _mbase = g_cpu.A[7];
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
    g_cpu.A[7] = m68k_read32(_mbase); _mbase += 4;
    g_cpu.A[7] = _mbase; }
}
void snatcher_main_at_FF5494(M68kStepContext *ctx){
  m68k_write8((uint32_t)(g_cpu.A[1] + (int32_t)0), (uint8_t)((uint8_t)g_cpu.D[5]));
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[5]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF5A48(M68kStepContext *ctx){
  uint8_t _FF5A48r = (uint8_t)((uint8_t)((uint8_t)g_cpu.D[4]) + (uint8_t)4u);
  { uint8_t _fa = (uint8_t)((uint8_t)((uint8_t)g_cpu.D[4])), _fb = (uint8_t)((uint8_t)4u), _fr = (uint8_t)(_FF5A48r);
    g_cpu.SR &= ~(0x1Fu);
    if (!_fr)                        g_cpu.SR |= (1u<<2);
    if (_fr >> 7)                   g_cpu.SR |= (1u<<3);
    if ((uint64_t)_fa + (uint64_t)_fb > 0x000000FFu) { g_cpu.SR |= (1u<<0); g_cpu.SR |= (1u<<4); }
    if (!((_fa^_fb) & 0x00000080u) && ((_fa^_fr) & 0x00000080u)) g_cpu.SR |= (1u<<1); }
  g_cpu.D[4] = (g_cpu.D[4] & 0xFFFFFF00u) | (uint32_t)((uint8_t)(_FF5A48r));
}
void snatcher_main_at_FF5AC8(M68kStepContext *ctx){
  ctx->charge=10; g_cpu.PC=0xFF5B10u;
}
void snatcher_main_at_FF5CCC(M68kStepContext *ctx){
  if(!(g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF5CC8u;}else ctx->charge=12;
}
