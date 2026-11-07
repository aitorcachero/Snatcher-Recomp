/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_sub_at_006016(M68kStepContext *ctx){
  { uint32_t target=(0x0000EEB6u)&0xFFFFFFu; ctx->charge=12;
    g_cpu.PC=target; }
}
void snatcher_sub_at_00D804(M68kStepContext *ctx){
  uint8_t _ts00D804 = m68k_read8((uint32_t)(g_cpu.A[0] + m68k_brief_index_value(0x1010u, g_cpu.D[1], g_cpu.A[1]) + (16)));
  g_cpu.D[0] = (g_cpu.D[0] & 0xFFFFFF00u) | (uint32_t)((uint8_t)(_ts00D804));
  { uint8_t _fv = (uint8_t)(_ts00D804);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_sub_at_00E41C(M68kStepContext *ctx){
  uint16_t _00E41Cr = (uint16_t)((uint16_t)((uint16_t)g_cpu.D[0]) - (uint16_t)0xFFFFu);
  { uint16_t _fa = (uint16_t)((uint16_t)((uint16_t)g_cpu.D[0])), _fb = (uint16_t)((uint16_t)0xFFFFu), _fr = (uint16_t)(_00E41Cr);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fr)                   g_cpu.SR |= (1u<<2);
    if (_fr >> 15)              g_cpu.SR |= (1u<<3);
    if ((uint32_t)_fb > (uint32_t)_fa) { g_cpu.SR |= (1u<<0); }
    if (((_fa^_fb) & 0x00008000u) && ((_fa^_fr) & 0x00008000u)) g_cpu.SR |= (1u<<1); }
}
void snatcher_sub_at_00E4EE(M68kStepContext *ctx){
  m68k_write32(g_cpu.A[3], (uint32_t)(g_cpu.A[0])); g_cpu.A[3] += 4;
  { uint32_t _fv = (uint32_t)(g_cpu.A[0]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 31)        g_cpu.SR |= (1u<<3); }
}
void snatcher_sub_at_00E9DC(M68kStepContext *ctx){
  uint8_t _00E9DCr = (uint8_t)((uint8_t)((uint8_t)g_cpu.D[5]) - (uint8_t)0x2u);
  { uint8_t _fa = (uint8_t)((uint8_t)((uint8_t)g_cpu.D[5])), _fb = (uint8_t)((uint8_t)0x2u), _fr = (uint8_t)(_00E9DCr);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fr)                   g_cpu.SR |= (1u<<2);
    if (_fr >> 7)              g_cpu.SR |= (1u<<3);
    if ((uint32_t)_fb > (uint32_t)_fa) { g_cpu.SR |= (1u<<0); }
    if (((_fa^_fb) & 0x00000080u) && ((_fa^_fr) & 0x00000080u)) g_cpu.SR |= (1u<<1); }
}
void snatcher_sub_at_00EEDE(M68kStepContext *ctx){
  ctx->charge=16; g_cpu.PC=m68k_read32(g_cpu.A[7])&0xFFFFFFu; g_cpu.A[7]+=4;
}
