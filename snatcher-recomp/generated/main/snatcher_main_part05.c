/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_main_at_FF0790(M68kStepContext *ctx){
  m68k_write16(0x00A11100u, (uint16_t)(0x0100u));
  { uint16_t _fv = (uint16_t)(0x0100u);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 15)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF0814(M68kStepContext *ctx){
  if(!(0)){ uint16_t low=(uint16_t)(g_cpu.D[0]-1u);
    g_cpu.D[0]=(g_cpu.D[0]&0xFFFF0000u)|low;
    if(low!=0xFFFFu){ctx->charge=10;g_cpu.PC=0xFF0812u;}else ctx->charge=14;
  }else ctx->charge=12;
}
void snatcher_main_at_FF08A2(M68kStepContext *ctx){
  if(!(0)){ uint16_t low=(uint16_t)(g_cpu.D[0]-1u);
    g_cpu.D[0]=(g_cpu.D[0]&0xFFFF0000u)|low;
    if(low!=0xFFFFu){ctx->charge=10;g_cpu.PC=0xFF08A0u;}else ctx->charge=14;
  }else ctx->charge=12;
}
void snatcher_main_at_FF0C6E(M68kStepContext *ctx){
  g_cpu.A[6] = 0x00A10005u;
}
void snatcher_main_at_FF157E(M68kStepContext *ctx){
  { uint8_t _sv = (uint8_t)g_cpu.D[1];
    uint8_t _FF157Er = (1 > 0 && 1 < 8) ? (_sv >> 1) : (1 == 0 ? _sv : (uint8_t)0);
    uint32_t _c = (1 <= 8) ? ((_sv >> (1 - 1)) & 1u) : 0u;
    g_cpu.D[1] = (g_cpu.D[1] & 0xFFFFFF00u) | (uint32_t)((uint8_t)_FF157Er);
    g_cpu.SR &= ~(0x1Fu);
    if (!_FF157Er) g_cpu.SR |= (1u<<2);
    if ((uint32_t)_FF157Er >> 7) g_cpu.SR |= (1u<<3);
    if (_c) { g_cpu.SR |= (1u<<0); g_cpu.SR |= (1u<<4); }
  }
}
void snatcher_main_at_FF4296(M68kStepContext *ctx){
  uint8_t _tFF4296 = m68k_read8(0x00FF7F2E);
  { uint32_t _bn = 0u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF4296) & (1u<<_bn)) ? (1u<<2) : 0u); }
}
void snatcher_main_at_FF433E(M68kStepContext *ctx){
  uint8_t _FF433Er = (uint8_t)((uint8_t)((uint8_t)g_cpu.D[3]) - (uint8_t)0x3u);
  { uint8_t _fa = (uint8_t)((uint8_t)((uint8_t)g_cpu.D[3])), _fb = (uint8_t)((uint8_t)0x3u), _fr = (uint8_t)(_FF433Er);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fr)                   g_cpu.SR |= (1u<<2);
    if (_fr >> 7)              g_cpu.SR |= (1u<<3);
    if ((uint32_t)_fb > (uint32_t)_fa) { g_cpu.SR |= (1u<<0); }
    if (((_fa^_fb) & 0x00000080u) && ((_fa^_fr) & 0x00000080u)) g_cpu.SR |= (1u<<1); }
}
void snatcher_main_at_FF43BC(M68kStepContext *ctx){
  if((g_cpu.SR & (1u<<0))){ctx->charge=10;g_cpu.PC=0xFF4330u;}else ctx->charge=12;
}
void snatcher_main_at_FF445A(M68kStepContext *ctx){
  uint8_t _tFF445A = m68k_read8(0x00FF7F2A);
  uint8_t _FF445Ar = 0;
  { uint32_t _bn = 2u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF445A) & (1u<<_bn)) ? (1u<<2) : 0u);
    _FF445Ar = (uint8_t)((uint8_t)(_tFF445A) & ~(uint8_t)(1u<<_bn)); }
  m68k_write8(0x00FF7F2Au, (uint8_t)(_FF445Ar));
}
void snatcher_main_at_FF44EA(M68kStepContext *ctx){
  uint8_t _tsFF44EA = m68k_read8(g_cpu.A[0]); g_cpu.A[0] += 1;
  g_cpu.D[6] = (g_cpu.D[6] & 0xFFFFFF00u) | (uint32_t)((uint8_t)(_tsFF44EA));
  { uint8_t _fv = (uint8_t)(_tsFF44EA);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF5298(M68kStepContext *ctx){
  g_cpu.A[0] += (uint32_t)(int32_t)(int16_t)((uint16_t)g_cpu.D[6]);
}
void snatcher_main_at_FF539E(M68kStepContext *ctx){
  uint8_t _tFF539E = m68k_read8(0x00FF7F2E);
  uint8_t _FF539Er = 0;
  { uint32_t _bn = 0u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF539E) & (1u<<_bn)) ? (1u<<2) : 0u);
    _FF539Er = (uint8_t)((uint8_t)(_tFF539E) & ~(uint8_t)(1u<<_bn)); }
  m68k_write8(0x00FF7F2Eu, (uint8_t)(_FF539Er));
}
void snatcher_main_at_FF59EC(M68kStepContext *ctx){
  uint8_t _tFF59EC = m68k_read8(0x00FF7F24);
  { uint32_t _bn = 0u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF59EC) & (1u<<_bn)) ? (1u<<2) : 0u); }
}
void snatcher_main_at_FF5A74(M68kStepContext *ctx){
  m68k_write8((uint32_t)(g_cpu.A[3] + (int32_t)1), (uint8_t)((uint8_t)g_cpu.D[5]));
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[5]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF5B02(M68kStepContext *ctx){
  m68k_write8(g_cpu.A[2], (uint8_t)((uint8_t)g_cpu.D[4]));
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[4]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
