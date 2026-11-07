/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_sub_at_00D494(M68kStepContext *ctx){
  { uint32_t _bn = (uint32_t)g_cpu.D[0] & 31u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)((uint32_t)g_cpu.D[0]) & (1u<<_bn)) ? (1u<<2) : 0u); }
}
void snatcher_sub_at_00E446(M68kStepContext *ctx){
  ctx->charge=10; g_cpu.PC=0x00E492u;
}
void snatcher_sub_at_00E9A0(M68kStepContext *ctx){
  ctx->charge=18; g_cpu.A[7]-=4; m68k_write32(g_cpu.A[7],0x00E9A4u); g_cpu.PC=0x00F272u;
}
void snatcher_sub_at_00EA08(M68kStepContext *ctx){
  g_cpu.D[7] = (g_cpu.D[7] & 0xFFFF0000u) | (uint32_t)((uint16_t)((uint16_t)g_cpu.D[6]));
  { uint16_t _fv = (uint16_t)((uint16_t)g_cpu.D[6]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 15)        g_cpu.SR |= (1u<<3); }
}
void snatcher_sub_at_00F568(M68kStepContext *ctx){
  if(!m68k_step_supervisor(ctx))return;
  ctx->charge=16;
  uint16_t _step00F568 = m68k_read16(g_cpu.A[7]); g_cpu.A[7] += 2;
  m68k_step_set_sr(ctx,(uint16_t)(_step00F568));
}
