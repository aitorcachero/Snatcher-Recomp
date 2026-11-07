/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_sub_at_00600A(M68kStepContext *ctx){
  { uint32_t target=(0x0000D48Eu)&0xFFFFFFu; ctx->charge=12;
    g_cpu.PC=target; }
}
void snatcher_sub_at_00D7FC(M68kStepContext *ctx){
  g_cpu.A[6] = (uint32_t)(int32_t)(int16_t)((uint16_t)g_cpu.D[2]);
}
void snatcher_sub_at_00E064(M68kStepContext *ctx){
  ctx->charge=16; g_cpu.PC=m68k_read32(g_cpu.A[7])&0xFFFFFFu; g_cpu.A[7]+=4;
}
void snatcher_sub_at_00E4D4(M68kStepContext *ctx){
  ctx->charge=10; g_cpu.PC=0x00E4E8u;
}
void snatcher_sub_at_00E9CE(M68kStepContext *ctx){
  if(!(g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0x00EA1Eu;}else ctx->charge=8;
}
void snatcher_sub_at_00EEC8(M68kStepContext *ctx){
  uint8_t _t00EEC8 = m68k_read8(0x0007F802);
  uint8_t _00EEC8r = 0;
  { uint32_t _bn = (uint32_t)g_cpu.D[5] & 7u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_t00EEC8) & (1u<<_bn)) ? (1u<<2) : 0u);
    _00EEC8r = (uint8_t)((uint8_t)(_t00EEC8) & ~(uint8_t)(1u<<_bn)); }
  m68k_write8(0x0007F802u, (uint8_t)(_00EEC8r));
}
