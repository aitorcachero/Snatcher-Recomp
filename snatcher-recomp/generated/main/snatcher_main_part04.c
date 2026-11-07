/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_main_at_FF0788(M68kStepContext *ctx){
  m68k_write16(0x00C00004u, (uint16_t)(0x8104u));
  { uint16_t _fv = (uint16_t)(0x8104u);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 15)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF0812(M68kStepContext *ctx){
  uint16_t _tFF0812 = m68k_read16(g_cpu.A[0]);
  m68k_write16(g_cpu.A[0], (uint16_t)(0)); g_cpu.A[0] += 2;
  g_cpu.SR = (g_cpu.SR & ~0x0Fu) | (1u<<2);
}
void snatcher_main_at_FF08A0(M68kStepContext *ctx){
  uint32_t _tFF08A0 = m68k_read32(g_cpu.A[0]);
  m68k_write32(g_cpu.A[0], (uint32_t)(0)); g_cpu.A[0] += 4;
  g_cpu.SR = (g_cpu.SR & ~0x0Fu) | (1u<<2);
}
void snatcher_main_at_FF0C68(M68kStepContext *ctx){
  m68k_write8(0x00A12012u, (uint8_t)((uint8_t)g_cpu.D[7]));
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[7]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF157C(M68kStepContext *ctx){
  uint8_t _FF157Cr = (uint8_t)g_cpu.D[7] | (uint8_t)((uint8_t)g_cpu.D[1]);
  g_cpu.D[7] = (g_cpu.D[7] & 0xFFFFFF00u) | (uint32_t)((uint8_t)_FF157Cr);
  { uint8_t _fv = (uint8_t)(_FF157Cr);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF4292(M68kStepContext *ctx){
  if(!(g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF4400u;}else ctx->charge=12;
}
void snatcher_main_at_FF4336(M68kStepContext *ctx){
  uint8_t _tsFF4336 = m68k_read8((uint32_t)(g_cpu.A[6] + m68k_brief_index_value(0x3000u, g_cpu.D[3], g_cpu.A[3]) + (0)));
  m68k_write8(0x00FF7F2Du, (uint8_t)(_tsFF4336));
  { uint8_t _fv = (uint8_t)(_tsFF4336);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF43B8(M68kStepContext *ctx){
  uint8_t _FF43B8r = (uint8_t)((uint8_t)((uint8_t)g_cpu.D[3]) - (uint8_t)0x6u);
  { uint8_t _fa = (uint8_t)((uint8_t)((uint8_t)g_cpu.D[3])), _fb = (uint8_t)((uint8_t)0x6u), _fr = (uint8_t)(_FF43B8r);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fr)                   g_cpu.SR |= (1u<<2);
    if (_fr >> 7)              g_cpu.SR |= (1u<<3);
    if ((uint32_t)_fb > (uint32_t)_fa) { g_cpu.SR |= (1u<<0); }
    if (((_fa^_fb) & 0x00000080u) && ((_fa^_fr) & 0x00000080u)) g_cpu.SR |= (1u<<1); }
}
void snatcher_main_at_FF4454(M68kStepContext *ctx){
  { uint32_t target=(0xFFFF4412u)&0xFFFFFFu; ctx->charge=20;
    g_cpu.A[7]-=4; m68k_write32(g_cpu.A[7],0xFF445Au);
    g_cpu.PC=target; }
}
void snatcher_main_at_FF44E8(M68kStepContext *ctx){
  g_cpu.D[6] = 0x00000000u;
  { uint32_t _fv = (uint32_t)((uint32_t)0x00000000u);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 31)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF5292(M68kStepContext *ctx){
  g_cpu.A[0] = 0xFFFF6142u;
}
void snatcher_main_at_FF539A(M68kStepContext *ctx){
  { uint32_t _mbase = g_cpu.A[7];
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
    g_cpu.A[7] = m68k_read32(_mbase); _mbase += 4;
    g_cpu.A[7] = _mbase; }
}
void snatcher_main_at_FF59E8(M68kStepContext *ctx){
  ctx->charge=10; g_cpu.PC=0xFF5A24u;
}
void snatcher_main_at_FF5A70(M68kStepContext *ctx){
  if(!(g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF5A6Cu;}else ctx->charge=12;
}
void snatcher_main_at_FF5AFE(M68kStepContext *ctx){
  if(!(g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF5AFAu;}else ctx->charge=12;
}
