/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_main_at_FF07B0(M68kStepContext *ctx){
  g_cpu.D[0] = (g_cpu.D[0] & 0xFFFF0000u) | (uint32_t)((uint16_t)(0x001Fu));
  { uint16_t _fv = (uint16_t)(0x001Fu);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 15)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF0830(M68kStepContext *ctx){
  ctx->charge=18; g_cpu.A[7]-=4; m68k_write32(g_cpu.A[7],0xFF0832u); g_cpu.PC=0xFF0898u;
}
void snatcher_main_at_FF08B8(M68kStepContext *ctx){
  g_cpu.D[0] = (g_cpu.D[0] & 0xFFFF0000u) | (uint32_t)((uint16_t)(0x005Fu));
  { uint16_t _fv = (uint16_t)(0x005Fu);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 15)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF151E(M68kStepContext *ctx){
  m68k_write8(0x00A1000Du, (uint8_t)((uint8_t)g_cpu.D[7]));
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[7]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF1688(M68kStepContext *ctx){
  ctx->charge=16; g_cpu.PC=m68k_read32(g_cpu.A[7])&0xFFFFFFu; g_cpu.A[7]+=4;
}
void snatcher_main_at_FF42BA(M68kStepContext *ctx){
  g_cpu.A[5] = 0x00A11100u;
}
void snatcher_main_at_FF4354(M68kStepContext *ctx){
  { uint32_t target=(0x00FF59CCu)&0xFFFFFFu; ctx->charge=18;
    g_cpu.A[7]-=4; m68k_write32(g_cpu.A[7],0xFF4358u);
    g_cpu.PC=target; }
}
void snatcher_main_at_FF43DE(M68kStepContext *ctx){
  { uint32_t target=(0xFFFF4E08u)&0xFFFFFFu; ctx->charge=20;
    g_cpu.A[7]-=4; m68k_write32(g_cpu.A[7],0xFF43E4u);
    g_cpu.PC=target; }
}
void snatcher_main_at_FF447C(M68kStepContext *ctx){
  uint8_t _tFF447C = m68k_read8((uint32_t)(g_cpu.A[1] + (int32_t)34));
  { uint32_t _bn = 5u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF447C) & (1u<<_bn)) ? (1u<<2) : 0u); }
}
void snatcher_main_at_FF4502(M68kStepContext *ctx){
  { uint32_t target=(0xFFFF48BCu)&0xFFFFFFu; ctx->charge=20;
    g_cpu.A[7]-=4; m68k_write32(g_cpu.A[7],0xFF4508u);
    g_cpu.PC=target; }
}
void snatcher_main_at_FF52AE(M68kStepContext *ctx){
  g_cpu.D[2] = 0x00000000u;
  { uint32_t _fv = (uint32_t)((uint32_t)0x00000000u);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 31)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF544E(M68kStepContext *ctx){
  g_cpu.A[1] = 0x00FF7A00u;
}
void snatcher_main_at_FF5A10(M68kStepContext *ctx){
  if((g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF5A24u;}else ctx->charge=12;
}
void snatcher_main_at_FF5A88(M68kStepContext *ctx){
  if(!(g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF5A84u;}else ctx->charge=12;
}
void snatcher_main_at_FF5C1A(M68kStepContext *ctx){
  uint8_t _FF5C1Ar = (uint8_t)((uint8_t)g_cpu.D[5]) & (uint8_t)0xC0u;
  { uint8_t _fv = (uint8_t)(_FF5C1Ar);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
  g_cpu.D[5] = (g_cpu.D[5] & 0xFFFFFF00u) | (uint32_t)((uint8_t)(_FF5C1Ar));
}
