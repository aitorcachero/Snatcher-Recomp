/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_main_at_FF0200(M68kStepContext *ctx){
  g_cpu.A[1] = 0x00FF020Cu;
}
void snatcher_main_at_FF0806(M68kStepContext *ctx){
  if((g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF080Au;}else ctx->charge=8;
}
void snatcher_main_at_FF0892(M68kStepContext *ctx){
  if(!(g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF0BB8u;}else ctx->charge=12;
}
void snatcher_main_at_FF0BE0(M68kStepContext *ctx){
  ctx->charge=10; g_cpu.PC=0xFF0B2Cu;
}
void snatcher_main_at_FF1574(M68kStepContext *ctx){
  /* NOP */
}
void snatcher_main_at_FF1722(M68kStepContext *ctx){
  uint32_t _tsFF1722 = m68k_read32(g_cpu.A[0]); g_cpu.A[0] += 4;
  m68k_write32(g_cpu.A[1], (uint32_t)(_tsFF1722)); g_cpu.A[1] += 4;
  { uint32_t _fv = (uint32_t)(_tsFF1722);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 31)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF4326(M68kStepContext *ctx){
  g_cpu.A[2] = 0x00A04000u;
}
void snatcher_main_at_FF43A8(M68kStepContext *ctx){
  { uint32_t target=(0x00FF4402u)&0xFFFFFFu; ctx->charge=18;
    g_cpu.A[7]-=4; m68k_write32(g_cpu.A[7],0xFF43ACu);
    g_cpu.PC=target; }
}
void snatcher_main_at_FF4440(M68kStepContext *ctx){
  if((g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF444Au;}else ctx->charge=12;
}
void snatcher_main_at_FF44D8(M68kStepContext *ctx){
  uint8_t _tFF44D8 = m68k_read8((uint32_t)(g_cpu.A[1] + (int32_t)49));
  { uint8_t _fv = (uint8_t)(_tFF44D8);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF5286(M68kStepContext *ctx){
  uint8_t _FF5286r = (uint8_t)((uint8_t)((uint8_t)g_cpu.D[0]) - (uint8_t)0x3Fu);
  { uint8_t _fa = (uint8_t)((uint8_t)((uint8_t)g_cpu.D[0])), _fb = (uint8_t)((uint8_t)0x3Fu), _fr = (uint8_t)(_FF5286r);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fr)                   g_cpu.SR |= (1u<<2);
    if (_fr >> 7)              g_cpu.SR |= (1u<<3);
    if ((uint32_t)_fb > (uint32_t)_fa) { g_cpu.SR |= (1u<<0); }
    if (((_fa^_fb) & 0x00000080u) && ((_fa^_fr) & 0x00000080u)) g_cpu.SR |= (1u<<1); }
}
void snatcher_main_at_FF538A(M68kStepContext *ctx){
  { uint8_t _sv = (uint8_t)g_cpu.D[6];
    uint8_t _FF538Ar = (2 > 0 && 2 < 8) ? (_sv << 2) : (2 == 0 ? _sv : (uint8_t)0);
    uint32_t _c = (2 > 0 && 2 <= 8) ? ((_sv >> (8 - 2)) & 1u) : 0u;
    g_cpu.D[6] = (g_cpu.D[6] & 0xFFFFFF00u) | (uint32_t)((uint8_t)_FF538Ar);
    g_cpu.SR &= ~(0x1Fu);
    if (!_FF538Ar) g_cpu.SR |= (1u<<2);
    if ((uint32_t)_FF538Ar >> 7) g_cpu.SR |= (1u<<3);
    if (_c) { g_cpu.SR |= (1u<<0); g_cpu.SR |= (1u<<4); }
  }
}
void snatcher_main_at_FF59D8(M68kStepContext *ctx){
  uint8_t _FF59D8r = (uint8_t)((uint8_t)((uint8_t)g_cpu.D[3]) - (uint8_t)0x4u);
  { uint8_t _fa = (uint8_t)((uint8_t)((uint8_t)g_cpu.D[3])), _fb = (uint8_t)((uint8_t)0x4u), _fr = (uint8_t)(_FF59D8r);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fr)                   g_cpu.SR |= (1u<<2);
    if (_fr >> 7)              g_cpu.SR |= (1u<<3);
    if ((uint32_t)_fb > (uint32_t)_fa) { g_cpu.SR |= (1u<<0); }
    if (((_fa^_fb) & 0x00000080u) && ((_fa^_fr) & 0x00000080u)) g_cpu.SR |= (1u<<1); }
}
void snatcher_main_at_FF5A62(M68kStepContext *ctx){
  uint8_t _tFF5A62 = m68k_read8(g_cpu.A[2]);
  { uint32_t _bn = 7u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF5A62) & (1u<<_bn)) ? (1u<<2) : 0u); }
}
void snatcher_main_at_FF5AF0(M68kStepContext *ctx){
  ctx->charge=10; g_cpu.PC=0xFF5B10u;
}
