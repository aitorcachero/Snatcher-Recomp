/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_main_at_FF0784(M68kStepContext *ctx){
  if(!m68k_step_supervisor(ctx))return;
  ctx->charge=20;
  m68k_step_set_sr(ctx,(uint16_t)(g_cpu.SR|0x0700u));
}
void snatcher_main_at_FF0810(M68kStepContext *ctx){
  g_cpu.D[0] = 0x00000007u;
  { uint32_t _fv = (uint32_t)((uint32_t)0x00000007u);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 31)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF089C(M68kStepContext *ctx){
  g_cpu.D[0] = (g_cpu.D[0] & 0xFFFF0000u) | (uint32_t)((uint16_t)(0x003Fu));
  { uint16_t _fv = (uint16_t)(0x003Fu);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 15)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF0C64(M68kStepContext *ctx){
  { uint32_t target=(0x00FF1558u)&0xFFFFFFu; ctx->charge=18;
    g_cpu.A[7]-=4; m68k_write32(g_cpu.A[7],0xFF0C68u);
    g_cpu.PC=target; }
}
void snatcher_main_at_FF157A(M68kStepContext *ctx){
  if((g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF157Eu;}else ctx->charge=8;
}
void snatcher_main_at_FF428A(M68kStepContext *ctx){
  uint8_t _tFF428A = m68k_read8(0x00FF7F72);
  { uint32_t _bn = 7u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF428A) & (1u<<_bn)) ? (1u<<2) : 0u); }
}
void snatcher_main_at_FF4330(M68kStepContext *ctx){
  g_cpu.A[6] = (uint32_t)(0xFFFF4000u);
}
void snatcher_main_at_FF43B6(M68kStepContext *ctx){
  uint8_t _FF43B6r = (uint8_t)((uint8_t)((uint8_t)g_cpu.D[3]) + (uint8_t)1u);
  { uint8_t _fa = (uint8_t)((uint8_t)((uint8_t)g_cpu.D[3])), _fb = (uint8_t)((uint8_t)1u), _fr = (uint8_t)(_FF43B6r);
    g_cpu.SR &= ~(0x1Fu);
    if (!_fr)                        g_cpu.SR |= (1u<<2);
    if (_fr >> 7)                   g_cpu.SR |= (1u<<3);
    if ((uint64_t)_fa + (uint64_t)_fb > 0x000000FFu) { g_cpu.SR |= (1u<<0); g_cpu.SR |= (1u<<4); }
    if (!((_fa^_fb) & 0x00000080u) && ((_fa^_fr) & 0x00000080u)) g_cpu.SR |= (1u<<1); }
  g_cpu.D[3] = (g_cpu.D[3] & 0xFFFFFF00u) | (uint32_t)((uint8_t)(_FF43B6r));
}
void snatcher_main_at_FF4450(M68kStepContext *ctx){
  if(!(g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF445Au;}else ctx->charge=12;
}
void snatcher_main_at_FF44E6(M68kStepContext *ctx){
  ctx->charge=16; g_cpu.PC=m68k_read32(g_cpu.A[7])&0xFFFFFFu; g_cpu.A[7]+=4;
}
void snatcher_main_at_FF5290(M68kStepContext *ctx){
  { uint16_t _sv = (uint16_t)g_cpu.D[6];
    uint16_t _FF5290r = (3 > 0 && 3 < 16) ? (_sv << 3) : (3 == 0 ? _sv : (uint16_t)0);
    uint32_t _c = (3 > 0 && 3 <= 16) ? (((uint32_t)_sv >> (16 - 3)) & 1u) : 0u;
    uint32_t _v = 0u;
    { uint32_t _top = (uint32_t)_sv >> 12;
      if (_top != 0u && _top != 0xFu) _v = 1u; }
    g_cpu.D[6] = (g_cpu.D[6] & 0xFFFF0000u) | (uint32_t)((uint16_t)_FF5290r);
    g_cpu.SR &= ~(0x1Fu);
    if (!_FF5290r) g_cpu.SR |= (1u<<2);
    if ((uint32_t)_FF5290r >> 15) g_cpu.SR |= (1u<<3);
    if (_c) { g_cpu.SR |= (1u<<0); g_cpu.SR |= (1u<<4); }
    if (_v) g_cpu.SR |= (1u<<1);
  }
}
void snatcher_main_at_FF5392(M68kStepContext *ctx){
  ctx->charge=10; g_cpu.PC=0xFF539Au;
}
void snatcher_main_at_FF59E4(M68kStepContext *ctx){
  if((g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF5A08u;}else ctx->charge=12;
}
void snatcher_main_at_FF5A6C(M68kStepContext *ctx){
  uint8_t _tFF5A6C = m68k_read8(g_cpu.A[2]);
  { uint32_t _bn = 7u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF5A6C) & (1u<<_bn)) ? (1u<<2) : 0u); }
}
void snatcher_main_at_FF5AFA(M68kStepContext *ctx){
  uint8_t _tFF5AFA = m68k_read8(g_cpu.A[2]);
  { uint32_t _bn = 7u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF5AFA) & (1u<<_bn)) ? (1u<<2) : 0u); }
}
