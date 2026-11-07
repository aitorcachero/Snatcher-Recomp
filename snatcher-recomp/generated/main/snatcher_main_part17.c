/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_main_at_FF07C8(M68kStepContext *ctx){
  g_cpu.D[0] = (g_cpu.D[0] & 0xFFFF0000u) | (uint32_t)((uint16_t)(0x000Du));
  { uint16_t _fv = (uint16_t)(0x000Du);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 15)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF0848(M68kStepContext *ctx){
  m68k_write16((uint32_t)(int32_t)(int16_t)0xE02A, (uint16_t)(0x0001u));
  { uint16_t _fv = (uint16_t)(0x0001u);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 15)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF0B30(M68kStepContext *ctx){
  if((g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF0B3Au;}else ctx->charge=8;
}
void snatcher_main_at_FF153E(M68kStepContext *ctx){
  m68k_write8(0x00A10005u, (uint8_t)(0x10u));
  { uint8_t _fv = (uint8_t)(0x10u);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF16E4(M68kStepContext *ctx){
  { uint8_t _sv = (uint8_t)g_cpu.D[0];
    uint8_t _FF16E4r = (1 > 0 && 1 < 8) ? (_sv << 1) : (1 == 0 ? _sv : (uint8_t)0);
    uint32_t _c = (1 > 0 && 1 <= 8) ? ((_sv >> (8 - 1)) & 1u) : 0u;
    g_cpu.D[0] = (g_cpu.D[0] & 0xFFFFFF00u) | (uint32_t)((uint8_t)_FF16E4r);
    g_cpu.SR &= ~(0x1Fu);
    if (!_FF16E4r) g_cpu.SR |= (1u<<2);
    if ((uint32_t)_FF16E4r >> 7) g_cpu.SR |= (1u<<3);
    if (_c) { g_cpu.SR |= (1u<<0); g_cpu.SR |= (1u<<4); }
  }
}
void snatcher_main_at_FF42D6(M68kStepContext *ctx){
  uint16_t _tsFF42D6 = m68k_read16(0x00FF7F5E);
  g_cpu.D[3] = (g_cpu.D[3] & 0xFFFF0000u) | (uint32_t)((uint16_t)(_tsFF42D6));
  { uint16_t _fv = (uint16_t)(_tsFF42D6);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 15)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF436E(M68kStepContext *ctx){
  uint8_t _FF436Er = (uint8_t)((uint8_t)g_cpu.D[0]) & (uint8_t)0x1u;
  { uint8_t _fv = (uint8_t)(_FF436Er);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
  g_cpu.D[0] = (g_cpu.D[0] & 0xFFFFFF00u) | (uint32_t)((uint8_t)(_FF436Er));
}
void snatcher_main_at_FF4400(M68kStepContext *ctx){
  ctx->charge=16; g_cpu.PC=m68k_read32(g_cpu.A[7])&0xFFFFFFu; g_cpu.A[7]+=4;
}
void snatcher_main_at_FF4496(M68kStepContext *ctx){
  { uint32_t target=(0xFFFF44F4u)&0xFFFFFFu; ctx->charge=20;
    g_cpu.A[7]-=4; m68k_write32(g_cpu.A[7],0xFF449Cu);
    g_cpu.PC=target; }
}
void snatcher_main_at_FF451E(M68kStepContext *ctx){
  if(!(g_cpu.SR & (1u<<0))){ctx->charge=10;g_cpu.PC=0xFF452Cu;}else ctx->charge=12;
}
void snatcher_main_at_FF52C8(M68kStepContext *ctx){
  g_cpu.A[0] = 0x00FF7F00u;
}
void snatcher_main_at_FF546C(M68kStepContext *ctx){
  g_cpu.D[6] = (g_cpu.D[6] & 0xFFFF0000u) | (uint32_t)((uint16_t)(0x0005u));
  { uint16_t _fv = (uint16_t)(0x0005u);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 15)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF5A2E(M68kStepContext *ctx){
  uint8_t _FF5A2Er = (uint8_t)((uint8_t)((uint8_t)g_cpu.D[4]) + (uint8_t)0x80u);
  { uint8_t _fa = (uint8_t)((uint8_t)((uint8_t)g_cpu.D[4])), _fb = (uint8_t)((uint8_t)0x80u), _fr = (uint8_t)(_FF5A2Er);
    g_cpu.SR &= ~(0x1Fu);
    if (!_fr)                        g_cpu.SR |= (1u<<2);
    if (_fr >> 7)                   g_cpu.SR |= (1u<<3);
    if ((uint64_t)_fa + (uint64_t)_fb > 0x000000FFu) { g_cpu.SR |= (1u<<0); g_cpu.SR |= (1u<<4); }
    if (!((_fa^_fb) & 0x00000080u) && ((_fa^_fr) & 0x00000080u)) g_cpu.SR |= (1u<<1); }
  g_cpu.D[4] = (g_cpu.D[4] & 0xFFFFFF00u) | (uint32_t)((uint8_t)(_FF5A2Er));
}
void snatcher_main_at_FF5AA4(M68kStepContext *ctx){
  uint8_t _FF5AA4r = (uint8_t)((uint8_t)((uint8_t)g_cpu.D[3]) - (uint8_t)0x5u);
  { uint8_t _fa = (uint8_t)((uint8_t)((uint8_t)g_cpu.D[3])), _fb = (uint8_t)((uint8_t)0x5u), _fr = (uint8_t)(_FF5AA4r);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fr)                   g_cpu.SR |= (1u<<2);
    if (_fr >> 7)              g_cpu.SR |= (1u<<3);
    if ((uint32_t)_fb > (uint32_t)_fa) { g_cpu.SR |= (1u<<0); }
    if (((_fa^_fb) & 0x00000080u) && ((_fa^_fr) & 0x00000080u)) g_cpu.SR |= (1u<<1); }
}
void snatcher_main_at_FF5CB0(M68kStepContext *ctx){
  m68k_write8((uint32_t)(g_cpu.A[1] + (int32_t)48), (uint8_t)((uint8_t)g_cpu.D[5]));
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[5]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
