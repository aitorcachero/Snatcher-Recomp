/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_main_at_FF07D8(M68kStepContext *ctx){
  { uint32_t target=((uint32_t)(int32_t)(int16_t)0x0368)&0xFFFFFFu; ctx->charge=18;
    g_cpu.A[7]-=4; m68k_write32(g_cpu.A[7],0xFF07DCu);
    g_cpu.PC=target; }
}
void snatcher_main_at_FF0856(M68kStepContext *ctx){
  uint16_t _tFF0856 = m68k_read16(0xFFFF7010);
  m68k_write16(0xFFFF7010u, (uint16_t)(0));
  g_cpu.SR = (g_cpu.SR & ~0x0Fu) | (1u<<2);
}
void snatcher_main_at_FF0B42(M68kStepContext *ctx){
  if(!(g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF0B48u;}else ctx->charge=8;
}
void snatcher_main_at_FF1558(M68kStepContext *ctx){
  ctx->charge=14;
  g_cpu.A[7] -= 2; m68k_write16(g_cpu.A[7], (uint16_t)(g_cpu.SR));
}
void snatcher_main_at_FF16F8(M68kStepContext *ctx){
  if((g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF1704u;}else ctx->charge=8;
}
void snatcher_main_at_FF42E8(M68kStepContext *ctx){
  if((g_cpu.SR & (1u<<0))){ctx->charge=10;g_cpu.PC=0xFF42F8u;}else ctx->charge=12;
}
void snatcher_main_at_FF437A(M68kStepContext *ctx){
  if((g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF43B0u;}else ctx->charge=12;
}
void snatcher_main_at_FF440E(M68kStepContext *ctx){
  if((g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF4418u;}else ctx->charge=12;
}
void snatcher_main_at_FF44AC(M68kStepContext *ctx){
  g_cpu.A[1] = 0x00FF7A00u;
}
void snatcher_main_at_FF4530(M68kStepContext *ctx){
  ctx->charge=16; g_cpu.PC=m68k_read32(g_cpu.A[7])&0xFFFFFFu; g_cpu.A[7]+=4;
}
void snatcher_main_at_FF52D8(M68kStepContext *ctx){
  uint8_t _tFF52D8 = m68k_read8(0x00FF7F20);
  uint8_t _FF52D8r = (uint8_t)((uint8_t)(_tFF52D8) - (uint8_t)0x20u);
  { uint8_t _fa = (uint8_t)((uint8_t)(_tFF52D8)), _fb = (uint8_t)((uint8_t)0x20u), _fr = (uint8_t)(_FF52D8r);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fr)                   g_cpu.SR |= (1u<<2);
    if (_fr >> 7)              g_cpu.SR |= (1u<<3);
    if ((uint32_t)_fb > (uint32_t)_fa) { g_cpu.SR |= (1u<<0); }
    if (((_fa^_fb) & 0x00000080u) && ((_fa^_fr) & 0x00000080u)) g_cpu.SR |= (1u<<1); }
}
void snatcher_main_at_FF5480(M68kStepContext *ctx){
  m68k_write8(0x00FF7F28u, (uint8_t)(0x00u));
  { uint8_t _fv = (uint8_t)(0x00u);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF5A3C(M68kStepContext *ctx){
  uint8_t _tFF5A3C = m68k_read8(g_cpu.A[2]);
  { uint32_t _bn = 7u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF5A3C) & (1u<<_bn)) ? (1u<<2) : 0u); }
}
void snatcher_main_at_FF5AB8(M68kStepContext *ctx){
  if((g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF5AE8u;}else ctx->charge=12;
}
void snatcher_main_at_FF5CC2(M68kStepContext *ctx){
  if(!(g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF5CBEu;}else ctx->charge=12;
}
