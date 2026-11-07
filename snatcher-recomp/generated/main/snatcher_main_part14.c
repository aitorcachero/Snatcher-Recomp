/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_main_at_FF07BA(M68kStepContext *ctx){
  g_cpu.D[0] = (g_cpu.D[0] & 0xFFFFFF00u) | (uint32_t)((uint8_t)(0xF1u));
  { uint8_t _fv = (uint8_t)(0xF1u);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF0838(M68kStepContext *ctx){
  uint8_t _tFF0838 = m68k_read8(0x00A1201F);
  uint8_t _FF0838r = (uint8_t)((uint8_t)(_tFF0838) - (uint8_t)0xFFu);
  { uint8_t _fa = (uint8_t)((uint8_t)(_tFF0838)), _fb = (uint8_t)((uint8_t)0xFFu), _fr = (uint8_t)(_FF0838r);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fr)                   g_cpu.SR |= (1u<<2);
    if (_fr >> 7)              g_cpu.SR |= (1u<<3);
    if ((uint32_t)_fb > (uint32_t)_fa) { g_cpu.SR |= (1u<<0); }
    if (((_fa^_fb) & 0x00000080u) && ((_fa^_fr) & 0x00000080u)) g_cpu.SR |= (1u<<1); }
}
void snatcher_main_at_FF08C2(M68kStepContext *ctx){
  g_cpu.D[0] = (g_cpu.D[0] & 0xFFFF0000u) | (uint32_t)((uint16_t)(0x007Fu));
  { uint16_t _fv = (uint16_t)(0x007Fu);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 15)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF152E(M68kStepContext *ctx){
  m68k_write8(0x00A1000Bu, (uint8_t)((uint8_t)g_cpu.D[7]));
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[7]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF16D6(M68kStepContext *ctx){
  uint8_t _tFF16D6 = m68k_read8(0x00A1200E);
  uint8_t _FF16D6r = 0;
  { uint32_t _bn = 6u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF16D6) & (1u<<_bn)) ? (1u<<2) : 0u);
    _FF16D6r = (uint8_t)((uint8_t)(_tFF16D6) & ~(uint8_t)(1u<<_bn)); }
  m68k_write8(0x00A1200Eu, (uint8_t)(_FF16D6r));
}
void snatcher_main_at_FF42CA(M68kStepContext *ctx){
  if((g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF42F8u;}else ctx->charge=12;
}
void snatcher_main_at_FF4360(M68kStepContext *ctx){
  if((g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF43B0u;}else ctx->charge=12;
}
void snatcher_main_at_FF43EE(M68kStepContext *ctx){
  uint8_t _tFF43EE = m68k_read8(0x00FF7F30);
  uint8_t _FF43EEr = (uint8_t)((uint8_t)(_tFF43EE) - (uint8_t)1u);
  { uint8_t _fa = (uint8_t)((uint8_t)(_tFF43EE)), _fb = (uint8_t)((uint8_t)1u), _fr = (uint8_t)(_FF43EEr);
    g_cpu.SR &= ~(0x1Fu);
    if (!_fr)                   g_cpu.SR |= (1u<<2);
    if (_fr >> 7)              g_cpu.SR |= (1u<<3);
    if ((uint32_t)_fb > (uint32_t)_fa) { g_cpu.SR |= (1u<<0); g_cpu.SR |= (1u<<4); }
    if (((_fa^_fb) & 0x00000080u) && ((_fa^_fr) & 0x00000080u)) g_cpu.SR |= (1u<<1); }
  m68k_write8(0x00FF7F30u, (uint8_t)(_FF43EEr));
}
void snatcher_main_at_FF448C(M68kStepContext *ctx){
  ctx->charge=16; g_cpu.PC=m68k_read32(g_cpu.A[7])&0xFFFFFFu; g_cpu.A[7]+=4;
}
void snatcher_main_at_FF4514(M68kStepContext *ctx){
  ctx->charge=10; g_cpu.PC=0xFF44E8u;
}
void snatcher_main_at_FF52BC(M68kStepContext *ctx){
  ctx->charge=10; g_cpu.PC=0xFF52C8u;
}
void snatcher_main_at_FF545C(M68kStepContext *ctx){
  g_cpu.A[1] += (uint32_t)(0x00000080u);
}
void snatcher_main_at_FF5A20(M68kStepContext *ctx){
  ctx->charge=10; g_cpu.PC=0xFF5A90u;
}
void snatcher_main_at_FF5A98(M68kStepContext *ctx){
  if((g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF5AE8u;}else ctx->charge=12;
}
void snatcher_main_at_FF5CA4(M68kStepContext *ctx){
  if(!(g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF5CACu;}else ctx->charge=12;
}
