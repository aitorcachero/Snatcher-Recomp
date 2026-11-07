/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_main_at_FF0802(M68kStepContext *ctx){
  uint8_t _FF0802r = (uint8_t)((uint8_t)((uint8_t)g_cpu.D[1]) - (uint8_t)0xFFu);
  { uint8_t _fa = (uint8_t)((uint8_t)((uint8_t)g_cpu.D[1])), _fb = (uint8_t)((uint8_t)0xFFu), _fr = (uint8_t)(_FF0802r);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fr)                   g_cpu.SR |= (1u<<2);
    if (_fr >> 7)              g_cpu.SR |= (1u<<3);
    if ((uint32_t)_fb > (uint32_t)_fa) { g_cpu.SR |= (1u<<0); }
    if (((_fa^_fb) & 0x00000080u) && ((_fa^_fr) & 0x00000080u)) g_cpu.SR |= (1u<<1); }
}
void snatcher_main_at_FF088C(M68kStepContext *ctx){
  uint8_t _tFF088C = m68k_read8(0x00A1201F);
  { uint8_t _fv = (uint8_t)(_tFF088C);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF0BDC(M68kStepContext *ctx){
  if(!m68k_step_supervisor(ctx))return;
  ctx->charge=20;
  m68k_step_set_sr(ctx,(uint16_t)(g_cpu.SR&0xF8FFu));
}
void snatcher_main_at_FF1572(M68kStepContext *ctx){
  /* NOP */
}
void snatcher_main_at_FF1720(M68kStepContext *ctx){
  uint32_t _tsFF1720 = m68k_read32(g_cpu.A[0]); g_cpu.A[0] += 4;
  m68k_write32(g_cpu.A[1], (uint32_t)(_tsFF1720)); g_cpu.A[1] += 4;
  { uint32_t _fv = (uint32_t)(_tsFF1720);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 31)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF4320(M68kStepContext *ctx){
  g_cpu.A[1] = 0x00FF7A00u;
}
void snatcher_main_at_FF43A4(M68kStepContext *ctx){
  uint32_t _tFF43A4 = m68k_read32((uint32_t)(g_cpu.A[1] + (int32_t)108));
  g_cpu.A[0] = (uint32_t)(_tFF43A4);
}
void snatcher_main_at_FF443C(M68kStepContext *ctx){
  uint8_t _FF443Cr = (uint8_t)((uint8_t)((uint8_t)g_cpu.D[6]) - (uint8_t)0x7Fu);
  { uint8_t _fa = (uint8_t)((uint8_t)((uint8_t)g_cpu.D[6])), _fb = (uint8_t)((uint8_t)0x7Fu), _fr = (uint8_t)(_FF443Cr);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fr)                   g_cpu.SR |= (1u<<2);
    if (_fr >> 7)              g_cpu.SR |= (1u<<3);
    if ((uint32_t)_fb > (uint32_t)_fa) { g_cpu.SR |= (1u<<0); }
    if (((_fa^_fb) & 0x00000080u) && ((_fa^_fr) & 0x00000080u)) g_cpu.SR |= (1u<<1); }
}
void snatcher_main_at_FF44D4(M68kStepContext *ctx){
  { uint32_t _mbase = g_cpu.A[7];
    g_cpu.A[1] = m68k_read32(_mbase); _mbase += 4;
    g_cpu.A[7] = _mbase; }
}
void snatcher_main_at_FF5282(M68kStepContext *ctx){
  if((g_cpu.SR & (1u<<0))){ctx->charge=10;g_cpu.PC=0xFF52C0u;}else ctx->charge=12;
}
void snatcher_main_at_FF5386(M68kStepContext *ctx){
  uint8_t _FF5386r = (uint8_t)((uint8_t)((uint8_t)g_cpu.D[6]) - (uint8_t)0xF1u);
  { uint8_t _fa = (uint8_t)((uint8_t)((uint8_t)g_cpu.D[6])), _fb = (uint8_t)((uint8_t)0xF1u), _fr = (uint8_t)(_FF5386r);
    g_cpu.SR &= ~(0x1Fu);
    if (!_fr)                   g_cpu.SR |= (1u<<2);
    if (_fr >> 7)              g_cpu.SR |= (1u<<3);
    if ((uint32_t)_fb > (uint32_t)_fa) { g_cpu.SR |= (1u<<0); g_cpu.SR |= (1u<<4); }
    if (((_fa^_fb) & 0x00000080u) && ((_fa^_fr) & 0x00000080u)) g_cpu.SR |= (1u<<1); }
  g_cpu.D[6] = (g_cpu.D[6] & 0xFFFFFF00u) | (uint32_t)((uint8_t)(_FF5386r));
}
void snatcher_main_at_FF59D4(M68kStepContext *ctx){
  if((g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF5A24u;}else ctx->charge=12;
}
void snatcher_main_at_FF5A60(M68kStepContext *ctx){
  uint8_t _FF5A60r = (uint8_t)((uint8_t)((uint8_t)g_cpu.D[4]) + (uint8_t)4u);
  { uint8_t _fa = (uint8_t)((uint8_t)((uint8_t)g_cpu.D[4])), _fb = (uint8_t)((uint8_t)4u), _fr = (uint8_t)(_FF5A60r);
    g_cpu.SR &= ~(0x1Fu);
    if (!_fr)                        g_cpu.SR |= (1u<<2);
    if (_fr >> 7)                   g_cpu.SR |= (1u<<3);
    if ((uint64_t)_fa + (uint64_t)_fb > 0x000000FFu) { g_cpu.SR |= (1u<<0); g_cpu.SR |= (1u<<4); }
    if (!((_fa^_fb) & 0x00000080u) && ((_fa^_fr) & 0x00000080u)) g_cpu.SR |= (1u<<1); }
  g_cpu.D[4] = (g_cpu.D[4] & 0xFFFFFF00u) | (uint32_t)((uint8_t)(_FF5A60r));
}
void snatcher_main_at_FF5AEC(M68kStepContext *ctx){
  if((g_cpu.SR & (1u<<0))){ctx->charge=10;g_cpu.PC=0xFF5AF4u;}else ctx->charge=12;
}
