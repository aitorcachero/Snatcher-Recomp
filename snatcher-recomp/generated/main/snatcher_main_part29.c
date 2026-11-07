/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_main_at_FF07FA(M68kStepContext *ctx){
  if((g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF07F6u;}else ctx->charge=8;
}
void snatcher_main_at_FF0882(M68kStepContext *ctx){
  m68k_write16(0x00C00004u, (uint16_t)((uint16_t)g_cpu.D[0]));
  { uint16_t _fv = (uint16_t)((uint16_t)g_cpu.D[0]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 15)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF0BD2(M68kStepContext *ctx){
  g_cpu.A[0] = (uint32_t)(0x00A12000u);
}
void snatcher_main_at_FF156E(M68kStepContext *ctx){
  /* NOP */
}
void snatcher_main_at_FF1716(M68kStepContext *ctx){
  g_cpu.A[0] = 0x00FF1784u;
}
void snatcher_main_at_FF4314(M68kStepContext *ctx){
  uint8_t _tFF4314 = m68k_read8(0x00FF7F2A);
  { uint32_t _bn = 6u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF4314) & (1u<<_bn)) ? (1u<<2) : 0u); }
}
void snatcher_main_at_FF439A(M68kStepContext *ctx){
  ctx->charge=10; g_cpu.PC=0xFF43B0u;
}
void snatcher_main_at_FF4434(M68kStepContext *ctx){
  uint8_t _tsFF4434 = m68k_read8((uint32_t)(g_cpu.A[1] + (int32_t)28));
  g_cpu.D[6] = (g_cpu.D[6] & 0xFFFFFF00u) | (uint32_t)((uint8_t)(_tsFF4434));
  { uint8_t _fv = (uint8_t)(_tsFF4434);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF44CC(M68kStepContext *ctx){
  m68k_write8((uint32_t)(g_cpu.A[1] + (int32_t)1073), (uint8_t)((uint8_t)g_cpu.D[0]));
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[0]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF527A(M68kStepContext *ctx){
  if(!(g_cpu.SR & (1u<<0))){ctx->charge=10;g_cpu.PC=0xFF52ECu;}else ctx->charge=12;
}
void snatcher_main_at_FF5382(M68kStepContext *ctx){
  g_cpu.D[6] = 0x00000000u;
  { uint32_t _fv = (uint32_t)((uint32_t)0x00000000u);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 31)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF54AA(M68kStepContext *ctx){
  ctx->charge=16; g_cpu.PC=m68k_read32(g_cpu.A[7])&0xFFFFFFu; g_cpu.A[7]+=4;
}
void snatcher_main_at_FF5A58(M68kStepContext *ctx){
  if(!(g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF5A54u;}else ctx->charge=12;
}
void snatcher_main_at_FF5AE4(M68kStepContext *ctx){
  ctx->charge=10; g_cpu.PC=0xFF5B10u;
}
