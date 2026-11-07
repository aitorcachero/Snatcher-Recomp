/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_main_at_FF0798(M68kStepContext *ctx){
  uint8_t _tFF0798 = m68k_read8(0x00A11100);
  { uint32_t _bn = 0u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF0798) & (1u<<_bn)) ? (1u<<2) : 0u); }
}
void snatcher_main_at_FF0818(M68kStepContext *ctx){
  m68k_write8(0x00A1201Fu, (uint8_t)((uint8_t)g_cpu.D[1]));
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[1]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF08A6(M68kStepContext *ctx){
  ctx->charge=16; g_cpu.PC=m68k_read32(g_cpu.A[7])&0xFFFFFFu; g_cpu.A[7]+=4;
}
void snatcher_main_at_FF0C74(M68kStepContext *ctx){
  { uint32_t target=(0x00FF1558u)&0xFFFFFFu; ctx->charge=18;
    g_cpu.A[7]-=4; m68k_write32(g_cpu.A[7],0xFF0C78u);
    g_cpu.PC=target; }
}
void snatcher_main_at_FF1580(M68kStepContext *ctx){
  if(!(g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF156Au;}else ctx->charge=8;
}
void snatcher_main_at_FF429E(M68kStepContext *ctx){
  if(!(g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF4400u;}else ctx->charge=12;
}
void snatcher_main_at_FF4342(M68kStepContext *ctx){
  if(!(g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF4348u;}else ctx->charge=12;
}
void snatcher_main_at_FF43C0(M68kStepContext *ctx){
  { uint32_t target=(0xFFFF4D22u)&0xFFFFFFu; ctx->charge=20;
    g_cpu.A[7]-=4; m68k_write32(g_cpu.A[7],0xFF43C6u);
    g_cpu.PC=target; }
}
void snatcher_main_at_FF4462(M68kStepContext *ctx){
  uint8_t _tFF4462 = m68k_read8((uint32_t)(g_cpu.A[1] + (int32_t)6));
  { uint8_t _fv = (uint8_t)(_tFF4462);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF44EC(M68kStepContext *ctx){
  if((g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF44E8u;}else ctx->charge=12;
}
void snatcher_main_at_FF529A(M68kStepContext *ctx){
  g_cpu.A[0] += 3u;
}
void snatcher_main_at_FF53A6(M68kStepContext *ctx){
  ctx->charge=16; g_cpu.PC=m68k_read32(g_cpu.A[7])&0xFFFFFFu; g_cpu.A[7]+=4;
}
void snatcher_main_at_FF59F4(M68kStepContext *ctx){
  if((g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF5A24u;}else ctx->charge=12;
}
void snatcher_main_at_FF5A78(M68kStepContext *ctx){
  uint8_t _FF5A78r = (uint8_t)((uint8_t)((uint8_t)g_cpu.D[4]) + (uint8_t)4u);
  { uint8_t _fa = (uint8_t)((uint8_t)((uint8_t)g_cpu.D[4])), _fb = (uint8_t)((uint8_t)4u), _fr = (uint8_t)(_FF5A78r);
    g_cpu.SR &= ~(0x1Fu);
    if (!_fr)                        g_cpu.SR |= (1u<<2);
    if (_fr >> 7)                   g_cpu.SR |= (1u<<3);
    if ((uint64_t)_fa + (uint64_t)_fb > 0x000000FFu) { g_cpu.SR |= (1u<<0); g_cpu.SR |= (1u<<4); }
    if (!((_fa^_fb) & 0x00000080u) && ((_fa^_fr) & 0x00000080u)) g_cpu.SR |= (1u<<1); }
  g_cpu.D[4] = (g_cpu.D[4] & 0xFFFFFF00u) | (uint32_t)((uint8_t)(_FF5A78r));
}
void snatcher_main_at_FF5B04(M68kStepContext *ctx){
  uint8_t _tFF5B04 = m68k_read8(g_cpu.A[2]);
  { uint32_t _bn = 7u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF5B04) & (1u<<_bn)) ? (1u<<2) : 0u); }
}
