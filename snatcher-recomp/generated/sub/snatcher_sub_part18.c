/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_sub_at_006034(M68kStepContext *ctx){
  { uint32_t target=(0x0000E41Au)&0xFFFFFFu; ctx->charge=12;
    g_cpu.PC=target; }
}
void snatcher_sub_at_00D81C(M68kStepContext *ctx){
  uint8_t _t00D81C = m68k_read8(g_cpu.A[4]);
  uint8_t _00D81Cr = (uint8_t)((uint8_t)(_t00D81C) - (uint8_t)0x44u);
  { uint8_t _fa = (uint8_t)((uint8_t)(_t00D81C)), _fb = (uint8_t)((uint8_t)0x44u), _fr = (uint8_t)(_00D81Cr);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fr)                   g_cpu.SR |= (1u<<2);
    if (_fr >> 7)              g_cpu.SR |= (1u<<3);
    if ((uint32_t)_fb > (uint32_t)_fa) { g_cpu.SR |= (1u<<0); }
    if (((_fa^_fb) & 0x00000080u) && ((_fa^_fr) & 0x00000080u)) g_cpu.SR |= (1u<<1); }
}
void snatcher_sub_at_00E43A(M68kStepContext *ctx){
  if(!(g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0x00E332u;}else ctx->charge=12;
}
void snatcher_sub_at_00E998(M68kStepContext *ctx){
  g_cpu.D[7] = (g_cpu.D[7] & 0xFFFF0000u) | (uint32_t)((uint16_t)((uint16_t)g_cpu.D[6]));
  { uint16_t _fv = (uint16_t)((uint16_t)g_cpu.D[6]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 15)        g_cpu.SR |= (1u<<3); }
}
void snatcher_sub_at_00E9FC(M68kStepContext *ctx){
  ctx->charge=18; g_cpu.A[7]-=4; m68k_write32(g_cpu.A[7],0x00EA00u); g_cpu.PC=0x00F272u;
}
void snatcher_sub_at_00F554(M68kStepContext *ctx){
  if(!m68k_step_supervisor(ctx))return;
  ctx->charge=20;
  m68k_step_set_sr(ctx,(uint16_t)(g_cpu.SR|0x0700u));
}
