/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_main_at_FF07D2(M68kStepContext *ctx){
  g_cpu.A[1] = 0xFFFF06C8u;
}
void snatcher_main_at_FF0852(M68kStepContext *ctx){
  uint16_t _tFF0852 = m68k_read16((uint32_t)(int32_t)(int16_t)0xE058);
  m68k_write16((uint32_t)(int32_t)(int16_t)0xE058, (uint16_t)(0));
  g_cpu.SR = (g_cpu.SR & ~0x0Fu) | (1u<<2);
}
void snatcher_main_at_FF0B3A(M68kStepContext *ctx){
  uint8_t _tFF0B3A = m68k_read8(0x00A1200F);
  { uint32_t _bn = 4u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF0B3A) & (1u<<_bn)) ? (1u<<2) : 0u); }
}
void snatcher_main_at_FF1556(M68kStepContext *ctx){
  ctx->charge=16; g_cpu.PC=m68k_read32(g_cpu.A[7])&0xFFFFFFu; g_cpu.A[7]+=4;
}
void snatcher_main_at_FF16F4(M68kStepContext *ctx){
  uint16_t _tFF16F4 = m68k_read16((uint32_t)(int32_t)(int16_t)0xE058);
  { uint16_t _fv = (uint16_t)(_tFF16F4);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 15)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF42E4(M68kStepContext *ctx){
  uint16_t _FF42E4r = (uint16_t)((uint16_t)((uint16_t)g_cpu.D[3]) - (uint16_t)0x15u);
  { uint16_t _fa = (uint16_t)((uint16_t)((uint16_t)g_cpu.D[3])), _fb = (uint16_t)((uint16_t)0x15u), _fr = (uint16_t)(_FF42E4r);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fr)                   g_cpu.SR |= (1u<<2);
    if (_fr >> 15)              g_cpu.SR |= (1u<<3);
    if ((uint32_t)_fb > (uint32_t)_fa) { g_cpu.SR |= (1u<<0); }
    if (((_fa^_fb) & 0x00008000u) && ((_fa^_fr) & 0x00008000u)) g_cpu.SR |= (1u<<1); }
}
void snatcher_main_at_FF4378(M68kStepContext *ctx){
  uint8_t _FF4378r = (uint8_t)((uint8_t)g_cpu.D[6]) ^ (uint8_t)g_cpu.D[0];
  { uint8_t _fv = (uint8_t)(_FF4378r);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
  g_cpu.D[6] = (g_cpu.D[6] & 0xFFFFFF00u) | (uint32_t)((uint8_t)(_FF4378r));
}
void snatcher_main_at_FF440A(M68kStepContext *ctx){
  uint8_t _tFF440A = m68k_read8((uint32_t)(g_cpu.A[1] + (int32_t)22));
  { uint8_t _fv = (uint8_t)(_tFF440A);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF44A8(M68kStepContext *ctx){
  { uint32_t _mbase = g_cpu.A[7];
    _mbase -= 4; m68k_write32(_mbase, g_cpu.A[1]);
    g_cpu.A[7] = _mbase; }
}
void snatcher_main_at_FF452C(M68kStepContext *ctx){
  ctx->charge=10; g_cpu.PC=0xFF44E8u;
}
void snatcher_main_at_FF52D2(M68kStepContext *ctx){
  uint8_t _tFF52D2 = m68k_read8(0x00FF7F20);
  uint8_t _FF52D2r = (uint8_t)((uint8_t)(_tFF52D2) + (uint8_t)1u);
  { uint8_t _fa = (uint8_t)((uint8_t)(_tFF52D2)), _fb = (uint8_t)((uint8_t)1u), _fr = (uint8_t)(_FF52D2r);
    g_cpu.SR &= ~(0x1Fu);
    if (!_fr)                        g_cpu.SR |= (1u<<2);
    if (_fr >> 7)                   g_cpu.SR |= (1u<<3);
    if ((uint64_t)_fa + (uint64_t)_fb > 0x000000FFu) { g_cpu.SR |= (1u<<0); g_cpu.SR |= (1u<<4); }
    if (!((_fa^_fb) & 0x00000080u) && ((_fa^_fr) & 0x00000080u)) g_cpu.SR |= (1u<<1); }
  m68k_write8(0x00FF7F20u, (uint8_t)(_FF52D2r));
}
void snatcher_main_at_FF547C(M68kStepContext *ctx){
  if(!(0)){ uint16_t low=(uint16_t)(g_cpu.D[6]-1u);
    g_cpu.D[6]=(g_cpu.D[6]&0xFFFF0000u)|low;
    if(low!=0xFFFFu){ctx->charge=10;g_cpu.PC=0xFF5470u;}else ctx->charge=14;
  }else ctx->charge=12;
}
void snatcher_main_at_FF5A3A(M68kStepContext *ctx){
  m68k_write8(g_cpu.A[3], (uint8_t)((uint8_t)g_cpu.D[4]));
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[4]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF5AB0(M68kStepContext *ctx){
  uint8_t _tFF5AB0 = m68k_read8(0x00FF7F24);
  { uint32_t _bn = 0u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF5AB0) & (1u<<_bn)) ? (1u<<2) : 0u); }
}
void snatcher_main_at_FF5CBE(M68kStepContext *ctx){
  uint8_t _tFF5CBE = m68k_read8(g_cpu.A[2]);
  { uint32_t _bn = 7u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF5CBE) & (1u<<_bn)) ? (1u<<2) : 0u); }
}
