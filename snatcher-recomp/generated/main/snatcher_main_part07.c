/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_main_at_FF07A0(M68kStepContext *ctx){
  if(!(g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF0798u;}else ctx->charge=8;
}
void snatcher_main_at_FF081E(M68kStepContext *ctx){
  g_cpu.A[0] = 0x00A1200Fu;
}
void snatcher_main_at_FF08A8(M68kStepContext *ctx){
  g_cpu.A[0] = 0xFFFF7000u;
}
void snatcher_main_at_FF0C78(M68kStepContext *ctx){
  m68k_write8(0x00A12013u, (uint8_t)((uint8_t)g_cpu.D[7]));
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[7]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF1582(M68kStepContext *ctx){
  if(!m68k_step_supervisor(ctx))return;
  ctx->charge=16;
  uint16_t _stepFF1582 = m68k_read16(g_cpu.A[7]); g_cpu.A[7] += 2;
  m68k_step_set_sr(ctx,(uint16_t)(_stepFF1582));
}
void snatcher_main_at_FF42A2(M68kStepContext *ctx){
  uint8_t _tFF42A2 = m68k_read8(0x00FF7F2E);
  { uint32_t _bn = 1u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF42A2) & (1u<<_bn)) ? (1u<<2) : 0u); }
}
void snatcher_main_at_FF4346(M68kStepContext *ctx){
  g_cpu.A[3] += 2u;
}
void snatcher_main_at_FF43C6(M68kStepContext *ctx){
  uint8_t _tFF43C6 = m68k_read8(0x00FF7F2A);
  { uint32_t _bn = 6u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF43C6) & (1u<<_bn)) ? (1u<<2) : 0u); }
}
void snatcher_main_at_FF4466(M68kStepContext *ctx){
  if((g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF4470u;}else ctx->charge=12;
}
void snatcher_main_at_FF44F0(M68kStepContext *ctx){
  g_cpu.D[5] = (g_cpu.D[5] & 0xFFFFFF00u) | (uint32_t)((uint8_t)((uint8_t)g_cpu.D[6]));
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[6]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF529C(M68kStepContext *ctx){
  uint8_t _tsFF529C = m68k_read8(g_cpu.A[0]);
  g_cpu.D[2] = (g_cpu.D[2] & 0xFFFFFF00u) | (uint32_t)((uint8_t)(_tsFF529C));
  { uint8_t _fv = (uint8_t)(_tsFF529C);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF543A(M68kStepContext *ctx){
  { uint32_t target=(0xFFFF578Au)&0xFFFFFFu; ctx->charge=20;
    g_cpu.A[7]-=4; m68k_write32(g_cpu.A[7],0xFF5440u);
    g_cpu.PC=target; }
}
void snatcher_main_at_FF59F8(M68kStepContext *ctx){
  uint8_t _tFF59F8 = m68k_read8(0x00FF7F24);
  { uint32_t _bn = 6u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF59F8) & (1u<<_bn)) ? (1u<<2) : 0u); }
}
void snatcher_main_at_FF5A7A(M68kStepContext *ctx){
  uint8_t _tFF5A7A = m68k_read8(g_cpu.A[2]);
  { uint32_t _bn = 7u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF5A7A) & (1u<<_bn)) ? (1u<<2) : 0u); }
}
void snatcher_main_at_FF5B08(M68kStepContext *ctx){
  if(!(g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF5B04u;}else ctx->charge=12;
}
