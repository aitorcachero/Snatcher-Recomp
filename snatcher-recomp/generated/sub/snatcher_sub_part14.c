/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_sub_at_006028(M68kStepContext *ctx){
  { uint32_t target=(0x000150EEu)&0xFFFFFFu; ctx->charge=12;
    g_cpu.PC=target; }
}
void snatcher_sub_at_00D812(M68kStepContext *ctx){
  g_cpu.D[7] = 0x00000000u;
  { uint32_t _fv = (uint32_t)((uint32_t)0x00000000u);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 31)        g_cpu.SR |= (1u<<3); }
}
void snatcher_sub_at_00E42E(M68kStepContext *ctx){
  if((g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0x00E492u;}else ctx->charge=8;
}
void snatcher_sub_at_00E98E(M68kStepContext *ctx){
  g_cpu.D[5] = (uint32_t)(uint32_t)((uint32_t)g_cpu.D[1]);
  { uint32_t _fv = (uint32_t)((uint32_t)g_cpu.D[1]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 31)        g_cpu.SR |= (1u<<3); }
}
void snatcher_sub_at_00E9EE(M68kStepContext *ctx){
  m68k_write8((uint32_t)(g_cpu.A[1] + (int32_t)11), (uint8_t)((uint8_t)g_cpu.D[7]));
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[7]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_sub_at_00F326(M68kStepContext *ctx){
  uint8_t _t00F326 = m68k_read8((uint32_t)(int32_t)(int16_t)0x78AE);
  { uint8_t _fv = (uint8_t)(_t00F326);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
