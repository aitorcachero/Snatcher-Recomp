/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_sub_at_006000(M68kStepContext *ctx){
  /* NOP */
}
void snatcher_sub_at_00D7F2(M68kStepContext *ctx){
  { uint32_t _x = (g_cpu.SR >> 4) & 1u;
    uint8_t _00D7F2r = (uint8_t)(0 - (uint8_t)((uint8_t)g_cpu.D[0]) - (uint8_t)_x);
  { uint8_t _fa = (uint8_t)(0), _fb = (uint8_t)((uint8_t)g_cpu.D[0]), _fr = (uint8_t)(_00D7F2r);
    g_cpu.SR &= ~(0x1Fu);
    if (!_fr)                   g_cpu.SR |= (1u<<2);
    if (_fr >> 7)              g_cpu.SR |= (1u<<3);
    if ((uint32_t)_fb > (uint32_t)_fa) { g_cpu.SR |= (1u<<0); g_cpu.SR |= (1u<<4); }
    if (((_fa^_fb) & 0x00000080u) && ((_fa^_fr) & 0x00000080u)) g_cpu.SR |= (1u<<1); }
  g_cpu.D[0] = (g_cpu.D[0] & 0xFFFFFF00u) | (uint32_t)((uint8_t)(_00D7F2r));
  }
}
void snatcher_sub_at_00E056(M68kStepContext *ctx){
  ctx->charge=16; g_cpu.PC=m68k_read32(g_cpu.A[7])&0xFFFFFFu; g_cpu.A[7]+=4;
}
void snatcher_sub_at_00E4C6(M68kStepContext *ctx){
  if((g_cpu.SR & (1u<<0))){ctx->charge=10;g_cpu.PC=0x00E4D6u;}else ctx->charge=8;
}
void snatcher_sub_at_00E9C2(M68kStepContext *ctx){
  g_cpu.D[7] = (g_cpu.D[7] & 0xFFFFFF00u) | (uint32_t)((uint8_t)((uint8_t)g_cpu.D[6]));
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[6]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_sub_at_00EEBE(M68kStepContext *ctx){
  { uint32_t _x = (g_cpu.SR >> 4) & 1u;
    uint8_t _00EEBEr = (uint8_t)(0 - (uint8_t)((uint8_t)g_cpu.D[4]) - (uint8_t)_x);
  { uint8_t _fa = (uint8_t)(0), _fb = (uint8_t)((uint8_t)g_cpu.D[4]), _fr = (uint8_t)(_00EEBEr);
    g_cpu.SR &= ~(0x1Fu);
    if (!_fr)                   g_cpu.SR |= (1u<<2);
    if (_fr >> 7)              g_cpu.SR |= (1u<<3);
    if ((uint32_t)_fb > (uint32_t)_fa) { g_cpu.SR |= (1u<<0); g_cpu.SR |= (1u<<4); }
    if (((_fa^_fb) & 0x00000080u) && ((_fa^_fr) & 0x00000080u)) g_cpu.SR |= (1u<<1); }
  g_cpu.D[4] = (g_cpu.D[4] & 0xFFFFFF00u) | (uint32_t)((uint8_t)(_00EEBEr));
  }
}
