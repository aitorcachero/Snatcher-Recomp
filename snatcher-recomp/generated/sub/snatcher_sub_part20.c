/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_sub_at_00D490(M68kStepContext *ctx){
  uint8_t _00D490r = (uint8_t)((uint8_t)g_cpu.D[0]) | (uint8_t)0xCu;
  { uint8_t _fv = (uint8_t)(_00D490r);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
  g_cpu.D[0] = (g_cpu.D[0] & 0xFFFFFF00u) | (uint32_t)((uint8_t)(_00D490r));
}
void snatcher_sub_at_00D844(M68kStepContext *ctx){
  g_cpu.A[6] = (uint32_t)(int32_t)(int16_t)((uint16_t)g_cpu.D[2]);
}
void snatcher_sub_at_00E442(M68kStepContext *ctx){
  ctx->charge=18; g_cpu.A[7]-=4; m68k_write32(g_cpu.A[7],0x00E446u); g_cpu.PC=0x00E4A0u;
}
void snatcher_sub_at_00E99C(M68kStepContext *ctx){
  m68k_write8((uint32_t)(g_cpu.A[1] + (int32_t)11), (uint8_t)((uint8_t)g_cpu.D[7]));
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[7]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_sub_at_00EA04(M68kStepContext *ctx){
  ctx->charge=18; g_cpu.A[7]-=4; m68k_write32(g_cpu.A[7],0x00EA08u); g_cpu.PC=0x00E058u;
}
void snatcher_sub_at_00F560(M68kStepContext *ctx){
  uint16_t _t00F560 = m68k_read16(0x00FF8032);
  uint16_t _00F560r = (uint16_t)(_t00F560) & (uint16_t)0xFFF7u;
  { uint16_t _fv = (uint16_t)(_00F560r);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 15)        g_cpu.SR |= (1u<<3); }
  m68k_write16(0x00FF8032u, (uint16_t)(_00F560r));
}
