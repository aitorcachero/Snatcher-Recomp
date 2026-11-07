/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_main_at_FF07BE(M68kStepContext *ctx){
  { uint32_t target=(0x00FF5258u)&0xFFFFFFu; ctx->charge=18;
    g_cpu.A[7]-=4; m68k_write32(g_cpu.A[7],0xFF07C2u);
    g_cpu.PC=target; }
}
void snatcher_main_at_FF0840(M68kStepContext *ctx){
  if(!(g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF084Eu;}else ctx->charge=8;
}
void snatcher_main_at_FF08C6(M68kStepContext *ctx){
  ctx->charge=10; g_cpu.PC=0xFF08A0u;
}
void snatcher_main_at_FF1534(M68kStepContext *ctx){
  ctx->charge=16; g_cpu.PC=m68k_read32(g_cpu.A[7])&0xFFFFFFu; g_cpu.A[7]+=4;
}
void snatcher_main_at_FF16DE(M68kStepContext *ctx){
  ctx->charge=16; g_cpu.PC=m68k_read32(g_cpu.A[7])&0xFFFFFFu; g_cpu.A[7]+=4;
}
void snatcher_main_at_FF42CE(M68kStepContext *ctx){
  uint16_t _FF42CEr = (uint16_t)((uint16_t)((uint16_t)g_cpu.D[3]) - (uint16_t)0x1500u);
  { uint16_t _fa = (uint16_t)((uint16_t)((uint16_t)g_cpu.D[3])), _fb = (uint16_t)((uint16_t)0x1500u), _fr = (uint16_t)(_FF42CEr);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fr)                   g_cpu.SR |= (1u<<2);
    if (_fr >> 15)              g_cpu.SR |= (1u<<3);
    if ((uint32_t)_fb > (uint32_t)_fa) { g_cpu.SR |= (1u<<0); }
    if (((_fa^_fb) & 0x00008000u) && ((_fa^_fr) & 0x00008000u)) g_cpu.SR |= (1u<<1); }
}
void snatcher_main_at_FF4364(M68kStepContext *ctx){
  uint8_t _tsFF4364 = m68k_read8(0x00FF7F30);
  g_cpu.D[0] = (g_cpu.D[0] & 0xFFFFFF00u) | (uint32_t)((uint8_t)(_tsFF4364));
  { uint8_t _fv = (uint8_t)(_tsFF4364);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF43F4(M68kStepContext *ctx){
  { uint32_t _mbase = g_cpu.A[7];
    g_cpu.D[0] = m68k_read32(_mbase); _mbase += 4;
    g_cpu.D[1] = m68k_read32(_mbase); _mbase += 4;
    g_cpu.D[2] = m68k_read32(_mbase); _mbase += 4;
    g_cpu.D[3] = m68k_read32(_mbase); _mbase += 4;
    g_cpu.D[4] = m68k_read32(_mbase); _mbase += 4;
    g_cpu.D[5] = m68k_read32(_mbase); _mbase += 4;
    g_cpu.D[6] = m68k_read32(_mbase); _mbase += 4;
    g_cpu.D[7] = m68k_read32(_mbase); _mbase += 4;
    g_cpu.A[0] = m68k_read32(_mbase); _mbase += 4;
    g_cpu.A[1] = m68k_read32(_mbase); _mbase += 4;
    g_cpu.A[2] = m68k_read32(_mbase); _mbase += 4;
    g_cpu.A[3] = m68k_read32(_mbase); _mbase += 4;
    g_cpu.A[4] = m68k_read32(_mbase); _mbase += 4;
    g_cpu.A[5] = m68k_read32(_mbase); _mbase += 4;
    g_cpu.A[6] = m68k_read32(_mbase); _mbase += 4;
    g_cpu.A[7] = _mbase; }
}
void snatcher_main_at_FF448E(M68kStepContext *ctx){
  uint8_t _tFF448E = m68k_read8((uint32_t)(g_cpu.A[1] + (int32_t)19));
  { uint8_t _fv = (uint8_t)(_tFF448E);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF4516(M68kStepContext *ctx){
  uint16_t _FF4516r = (uint16_t)((uint16_t)g_cpu.D[5]) & (uint16_t)0x7Fu;
  { uint16_t _fv = (uint16_t)(_FF4516r);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 15)        g_cpu.SR |= (1u<<3); }
  g_cpu.D[5] = (g_cpu.D[5] & 0xFFFF0000u) | (uint32_t)((uint16_t)(_FF4516r));
}
void snatcher_main_at_FF52C0(M68kStepContext *ctx){
  g_cpu.D[2] = 0x00000000u;
  { uint32_t _fv = (uint32_t)((uint32_t)0x00000000u);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 31)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF5462(M68kStepContext *ctx){
  if(!(0)){ uint16_t low=(uint16_t)(g_cpu.D[6]-1u);
    g_cpu.D[6]=(g_cpu.D[6]&0xFFFF0000u)|low;
    if(low!=0xFFFFu){ctx->charge=10;g_cpu.PC=0xFF5454u;}else ctx->charge=14;
  }else ctx->charge=12;
}
void snatcher_main_at_FF5A24(M68kStepContext *ctx){
  uint8_t _tsFF5A24 = m68k_read8(0x00FF7F2D);
  g_cpu.D[4] = (g_cpu.D[4] & 0xFFFFFF00u) | (uint32_t)((uint8_t)(_tsFF5A24));
  { uint8_t _fv = (uint8_t)(_tsFF5A24);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF5A9C(M68kStepContext *ctx){
  uint8_t _FF5A9Cr = (uint8_t)((uint8_t)((uint8_t)g_cpu.D[3]) - (uint8_t)0x4u);
  { uint8_t _fa = (uint8_t)((uint8_t)((uint8_t)g_cpu.D[3])), _fb = (uint8_t)((uint8_t)0x4u), _fr = (uint8_t)(_FF5A9Cr);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fr)                   g_cpu.SR |= (1u<<2);
    if (_fr >> 7)              g_cpu.SR |= (1u<<3);
    if ((uint32_t)_fb > (uint32_t)_fa) { g_cpu.SR |= (1u<<0); }
    if (((_fa^_fb) & 0x00000080u) && ((_fa^_fr) & 0x00000080u)) g_cpu.SR |= (1u<<1); }
}
void snatcher_main_at_FF5CA8(M68kStepContext *ctx){
  ctx->charge=10; g_cpu.PC=0xFF5CB0u;
}
