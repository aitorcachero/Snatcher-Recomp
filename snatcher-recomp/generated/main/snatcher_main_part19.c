/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_main_at_FF07CE(M68kStepContext *ctx){
  if(!(0)){ uint16_t low=(uint16_t)(g_cpu.D[0]-1u);
    g_cpu.D[0]=(g_cpu.D[0]&0xFFFF0000u)|low;
    if(low!=0xFFFFu){ctx->charge=10;g_cpu.PC=0xFF07CCu;}else ctx->charge=14;
  }else ctx->charge=12;
}
void snatcher_main_at_FF0850(M68kStepContext *ctx){
  ctx->charge=18; g_cpu.A[7]-=4; m68k_write32(g_cpu.A[7],0xFF0852u); g_cpu.PC=0xFF08BEu;
}
void snatcher_main_at_FF0B36(M68kStepContext *ctx){
  { uint32_t target=(0x00FF16CCu)&0xFFFFFFu; ctx->charge=18;
    g_cpu.A[7]-=4; m68k_write32(g_cpu.A[7],0xFF0B3Au);
    g_cpu.PC=target; }
}
void snatcher_main_at_FF154E(M68kStepContext *ctx){
  m68k_write8(0x00A1000Bu, (uint8_t)(0x40u));
  { uint8_t _fv = (uint8_t)(0x40u);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF16EC(M68kStepContext *ctx){
  uint8_t _tsFF16EC = m68k_read8((uint32_t)(int32_t)(int16_t)0xE054);
  m68k_write8(0x00A12017u, (uint8_t)(_tsFF16EC));
  { uint8_t _fv = (uint8_t)(_tsFF16EC);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF42E0(M68kStepContext *ctx){
  if((g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF42F8u;}else ctx->charge=12;
}
void snatcher_main_at_FF4374(M68kStepContext *ctx){
  uint8_t _FF4374r = (uint8_t)((uint8_t)g_cpu.D[6]) & (uint8_t)0x1u;
  { uint8_t _fv = (uint8_t)(_FF4374r);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
  g_cpu.D[6] = (g_cpu.D[6] & 0xFFFFFF00u) | (uint32_t)((uint8_t)(_FF4374r));
}
void snatcher_main_at_FF4406(M68kStepContext *ctx){
  if((g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF44E8u;}else ctx->charge=12;
}
void snatcher_main_at_FF44A4(M68kStepContext *ctx){
  if((g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF44D8u;}else ctx->charge=12;
}
void snatcher_main_at_FF4528(M68kStepContext *ctx){
  ctx->charge=10; g_cpu.PC=0xFF4530u;
}
void snatcher_main_at_FF52D0(M68kStepContext *ctx){
  m68k_write8(g_cpu.A[0], (uint8_t)((uint8_t)g_cpu.D[0]));
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[0]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF5476(M68kStepContext *ctx){
  g_cpu.A[1] += (uint32_t)(0x00000080u);
}
void snatcher_main_at_FF5A36(M68kStepContext *ctx){
  if(!(g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF5A32u;}else ctx->charge=12;
}
void snatcher_main_at_FF5AAC(M68kStepContext *ctx){
  ctx->charge=10; g_cpu.PC=0xFF5AE8u;
}
void snatcher_main_at_FF5CBA(M68kStepContext *ctx){
  uint8_t _FF5CBAr = (uint8_t)((uint8_t)((uint8_t)g_cpu.D[4]) + (uint8_t)0xB4u);
  { uint8_t _fa = (uint8_t)((uint8_t)((uint8_t)g_cpu.D[4])), _fb = (uint8_t)((uint8_t)0xB4u), _fr = (uint8_t)(_FF5CBAr);
    g_cpu.SR &= ~(0x1Fu);
    if (!_fr)                        g_cpu.SR |= (1u<<2);
    if (_fr >> 7)                   g_cpu.SR |= (1u<<3);
    if ((uint64_t)_fa + (uint64_t)_fb > 0x000000FFu) { g_cpu.SR |= (1u<<0); g_cpu.SR |= (1u<<4); }
    if (!((_fa^_fb) & 0x00000080u) && ((_fa^_fr) & 0x00000080u)) g_cpu.SR |= (1u<<1); }
  g_cpu.D[4] = (g_cpu.D[4] & 0xFFFFFF00u) | (uint32_t)((uint8_t)(_FF5CBAr));
}
