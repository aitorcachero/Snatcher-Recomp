/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_sub_at_00D4C4(M68kStepContext *ctx){
  { uint32_t _bn = (uint32_t)g_cpu.D[0] & 31u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)((uint32_t)g_cpu.D[0]) & (1u<<_bn)) ? (1u<<2) : 0u); }
}
void snatcher_sub_at_00DDCE(M68kStepContext *ctx){
  if(!(0)){ uint16_t low=(uint16_t)(g_cpu.D[0]-1u);
    g_cpu.D[0]=(g_cpu.D[0]&0xFFFF0000u)|low;
    if(low!=0xFFFFu){ctx->charge=10;g_cpu.PC=0x00DDCAu;}else ctx->charge=14;
  }else ctx->charge=12;
}
void snatcher_sub_at_00E4AC(M68kStepContext *ctx){
  g_cpu.D[1] = (uint32_t)(uint32_t)((uint32_t)g_cpu.D[0]);
  { uint32_t _fv = (uint32_t)((uint32_t)g_cpu.D[0]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 31)        g_cpu.SR |= (1u<<3); }
}
void snatcher_sub_at_00E9B0(M68kStepContext *ctx){
  uint8_t _00E9B0r = (uint8_t)((uint8_t)((uint8_t)g_cpu.D[7]) + (uint8_t)1u);
  { uint8_t _fa = (uint8_t)((uint8_t)((uint8_t)g_cpu.D[7])), _fb = (uint8_t)((uint8_t)1u), _fr = (uint8_t)(_00E9B0r);
    g_cpu.SR &= ~(0x1Fu);
    if (!_fr)                        g_cpu.SR |= (1u<<2);
    if (_fr >> 7)                   g_cpu.SR |= (1u<<3);
    if ((uint64_t)_fa + (uint64_t)_fb > 0x000000FFu) { g_cpu.SR |= (1u<<0); g_cpu.SR |= (1u<<4); }
    if (!((_fa^_fb) & 0x00000080u) && ((_fa^_fr) & 0x00000080u)) g_cpu.SR |= (1u<<1); }
  g_cpu.D[7] = (g_cpu.D[7] & 0xFFFFFF00u) | (uint32_t)((uint8_t)(_00E9B0r));
}
void snatcher_sub_at_00EA16(M68kStepContext *ctx){
  m68k_write8((uint32_t)(g_cpu.A[1] + (int32_t)9), (uint8_t)((uint8_t)g_cpu.D[7]));
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[7]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
