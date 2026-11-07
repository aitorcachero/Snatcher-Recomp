/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_sub_at_00601E(M68kStepContext *ctx){
  uint8_t _00601Er = (uint8_t)((uint8_t)g_cpu.D[0]) | (uint8_t)0xEAu;
  { uint8_t _fv = (uint8_t)(_00601Er);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
  g_cpu.D[0] = (g_cpu.D[0] & 0xFFFFFF00u) | (uint32_t)((uint8_t)(_00601Er));
}
void snatcher_sub_at_00D80C(M68kStepContext *ctx){
  g_cpu.A[6] = (uint32_t)(int32_t)(int16_t)((uint16_t)g_cpu.D[2]);
}
void snatcher_sub_at_00E426(M68kStepContext *ctx){
  if(!(g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0x00E430u;}else ctx->charge=8;
}
void snatcher_sub_at_00E4F4(M68kStepContext *ctx){
  m68k_write8(0x0007F80Fu, (uint8_t)(0x01u));
  { uint8_t _fv = (uint8_t)(0x01u);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_sub_at_00E9E6(M68kStepContext *ctx){
  ctx->charge=18; g_cpu.A[7]-=4; m68k_write32(g_cpu.A[7],0x00E9EAu); g_cpu.PC=0x00E058u;
}
void snatcher_sub_at_00F278(M68kStepContext *ctx){
  if(!(0)){ uint16_t low=(uint16_t)(g_cpu.D[7]-1u);
    g_cpu.D[7]=(g_cpu.D[7]&0xFFFF0000u)|low;
    if(low!=0xFFFFu){ctx->charge=10;g_cpu.PC=0x00F278u;}else ctx->charge=14;
  }else ctx->charge=12;
}
