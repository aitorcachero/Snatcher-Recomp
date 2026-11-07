/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_main_at_FF07F6(M68kStepContext *ctx){
  uint8_t _tFF07F6 = m68k_read8(g_cpu.A[0]);
  { uint32_t _bn = 1u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF07F6) & (1u<<_bn)) ? (1u<<2) : 0u); }
}
void snatcher_main_at_FF087C(M68kStepContext *ctx){
  m68k_write16(0x00FFEF02u, (uint16_t)((uint16_t)g_cpu.D[0]));
  { uint16_t _fv = (uint16_t)((uint16_t)g_cpu.D[0]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 15)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF0BCA(M68kStepContext *ctx){
  uint8_t _tFF0BCA = m68k_read8(0x00A1200E);
  uint8_t _FF0BCAr = 0;
  { uint32_t _bn = 1u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF0BCA) & (1u<<_bn)) ? (1u<<2) : 0u);
    _FF0BCAr = (uint8_t)((uint8_t)(_tFF0BCA) | (uint8_t)(1u<<_bn)); }
  m68k_write8(0x00A1200Eu, (uint8_t)(_FF0BCAr));
}
void snatcher_main_at_FF156C(M68kStepContext *ctx){
  /* NOP */
}
void snatcher_main_at_FF1712(M68kStepContext *ctx){
  if(!(0)){ uint16_t low=(uint16_t)(g_cpu.D[0]-1u);
    g_cpu.D[0]=(g_cpu.D[0]&0xFFFF0000u)|low;
    if(low!=0xFFFFu){ctx->charge=10;g_cpu.PC=0xFF170Cu;}else ctx->charge=14;
  }else ctx->charge=12;
}
void snatcher_main_at_FF4310(M68kStepContext *ctx){
  ctx->charge=10; g_cpu.PC=0xFF43DEu;
}
void snatcher_main_at_FF4396(M68kStepContext *ctx){
  m68k_write32((uint32_t)(g_cpu.A[1] + (int32_t)108), (uint32_t)(g_cpu.A[0]));
  { uint32_t _fv = (uint32_t)(g_cpu.A[0]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 31)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF442E(M68kStepContext *ctx){
  { uint32_t target=(0xFFFF43C6u)&0xFFFFFFu; ctx->charge=20;
    g_cpu.A[7]-=4; m68k_write32(g_cpu.A[7],0xFF4434u);
    g_cpu.PC=target; }
}
void snatcher_main_at_FF44C8(M68kStepContext *ctx){
  m68k_write8((uint32_t)(g_cpu.A[1] + (int32_t)689), (uint8_t)((uint8_t)g_cpu.D[0]));
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[0]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF5276(M68kStepContext *ctx){
  uint8_t _FF5276r = (uint8_t)((uint8_t)((uint8_t)g_cpu.D[0]) - (uint8_t)0x7Bu);
  { uint8_t _fa = (uint8_t)((uint8_t)((uint8_t)g_cpu.D[0])), _fb = (uint8_t)((uint8_t)0x7Bu), _fr = (uint8_t)(_FF5276r);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fr)                   g_cpu.SR |= (1u<<2);
    if (_fr >> 7)              g_cpu.SR |= (1u<<3);
    if ((uint32_t)_fb > (uint32_t)_fa) { g_cpu.SR |= (1u<<0); }
    if (((_fa^_fb) & 0x00000080u) && ((_fa^_fr) & 0x00000080u)) g_cpu.SR |= (1u<<1); }
}
void snatcher_main_at_FF5304(M68kStepContext *ctx){
  ctx->charge=16; g_cpu.PC=m68k_read32(g_cpu.A[7])&0xFFFFFFu; g_cpu.A[7]+=4;
}
void snatcher_main_at_FF54A6(M68kStepContext *ctx){
  m68k_write8((uint32_t)(g_cpu.A[1] + (int32_t)1), (uint8_t)((uint8_t)g_cpu.D[5]));
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[5]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF5A54(M68kStepContext *ctx){
  uint8_t _tFF5A54 = m68k_read8(g_cpu.A[2]);
  { uint32_t _bn = 7u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF5A54) & (1u<<_bn)) ? (1u<<2) : 0u); }
}
void snatcher_main_at_FF5AE0(M68kStepContext *ctx){
  if(!(g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF5AE8u;}else ctx->charge=12;
}
