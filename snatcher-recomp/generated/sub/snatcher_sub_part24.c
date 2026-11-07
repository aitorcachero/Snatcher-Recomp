/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_sub_at_00DDC6(M68kStepContext *ctx){
  g_cpu.D[0] = (g_cpu.D[0] & 0xFFFF0000u) | (uint32_t)((uint16_t)(0x000Cu));
  { uint16_t _fv = (uint16_t)(0x000Cu);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 15)        g_cpu.SR |= (1u<<3); }
}
void snatcher_sub_at_00E4A0(M68kStepContext *ctx){
  g_cpu.A[0] = (uint32_t)(0x0006D000u);
}
void snatcher_sub_at_00E9AA(M68kStepContext *ctx){
  ctx->charge=18; g_cpu.A[7]-=4; m68k_write32(g_cpu.A[7],0x00E9AEu); g_cpu.PC=0x00F272u;
}
void snatcher_sub_at_00EA10(M68kStepContext *ctx){
  ctx->charge=18; g_cpu.A[7]-=4; m68k_write32(g_cpu.A[7],0x00EA14u); g_cpu.PC=0x00F272u;
}
