/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_main_at_FF07FC(M68kStepContext *ctx){
  uint8_t _tsFF07FC = m68k_read8(0x00A1201F);
  g_cpu.D[1] = (g_cpu.D[1] & 0xFFFFFF00u) | (uint32_t)((uint8_t)(_tsFF07FC));
  { uint8_t _fv = (uint8_t)(_tsFF07FC);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF0888(M68kStepContext *ctx){
  if(!m68k_step_supervisor(ctx))return;
  ctx->charge=20;
  m68k_step_set_sr(ctx,(uint16_t)(g_cpu.SR&0xF8FFu));
}
void snatcher_main_at_FF0BD8(M68kStepContext *ctx){
  uint16_t _tFF0BD8 = m68k_read16(g_cpu.A[0]);
  uint16_t _FF0BD8r = (uint16_t)(_tFF0BD8) | (uint16_t)0x8100u;
  { uint16_t _fv = (uint16_t)(_FF0BD8r);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 15)        g_cpu.SR |= (1u<<3); }
  m68k_write16(g_cpu.A[0], (uint16_t)(_FF0BD8r));
}
void snatcher_main_at_FF1570(M68kStepContext *ctx){
  /* NOP */
}
void snatcher_main_at_FF171A(M68kStepContext *ctx){
  g_cpu.A[1] = 0x00FFEF00u;
}
void snatcher_main_at_FF431C(M68kStepContext *ctx){
  if(!(g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF43C0u;}else ctx->charge=12;
}
void snatcher_main_at_FF439E(M68kStepContext *ctx){
  m68k_write8((uint32_t)(g_cpu.A[1] + (int32_t)36), (uint8_t)(0x01u));
  { uint8_t _fv = (uint8_t)(0x01u);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF4438(M68kStepContext *ctx){
  if((g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF444Au;}else ctx->charge=12;
}
void snatcher_main_at_FF44D0(M68kStepContext *ctx){
  m68k_write8((uint32_t)(g_cpu.A[1] + (int32_t)1201), (uint8_t)((uint8_t)g_cpu.D[0]));
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[0]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF527E(M68kStepContext *ctx){
  uint8_t _FF527Er = (uint8_t)((uint8_t)((uint8_t)g_cpu.D[0]) - (uint8_t)0x32u);
  { uint8_t _fa = (uint8_t)((uint8_t)((uint8_t)g_cpu.D[0])), _fb = (uint8_t)((uint8_t)0x32u), _fr = (uint8_t)(_FF527Er);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fr)                   g_cpu.SR |= (1u<<2);
    if (_fr >> 7)              g_cpu.SR |= (1u<<3);
    if ((uint32_t)_fb > (uint32_t)_fa) { g_cpu.SR |= (1u<<0); }
    if (((_fa^_fb) & 0x00000080u) && ((_fa^_fr) & 0x00000080u)) g_cpu.SR |= (1u<<1); }
}
void snatcher_main_at_FF5384(M68kStepContext *ctx){
  g_cpu.D[6] = (g_cpu.D[6] & 0xFFFFFF00u) | (uint32_t)((uint8_t)((uint8_t)g_cpu.D[0]));
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[0]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF59CC(M68kStepContext *ctx){
  uint8_t _tFF59CC = m68k_read8(0x00FF7F24);
  { uint32_t _bn = 7u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF59CC) & (1u<<_bn)) ? (1u<<2) : 0u); }
}
void snatcher_main_at_FF5A5C(M68kStepContext *ctx){
  m68k_write8((uint32_t)(g_cpu.A[3] + (int32_t)1), (uint8_t)((uint8_t)g_cpu.D[5]));
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[5]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF5AE8(M68kStepContext *ctx){
  uint8_t _FF5AE8r = (uint8_t)((uint8_t)((uint8_t)g_cpu.D[3]) - (uint8_t)0x6u);
  { uint8_t _fa = (uint8_t)((uint8_t)((uint8_t)g_cpu.D[3])), _fb = (uint8_t)((uint8_t)0x6u), _fr = (uint8_t)(_FF5AE8r);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fr)                   g_cpu.SR |= (1u<<2);
    if (_fr >> 7)              g_cpu.SR |= (1u<<3);
    if ((uint32_t)_fb > (uint32_t)_fa) { g_cpu.SR |= (1u<<0); }
    if (((_fa^_fb) & 0x00000080u) && ((_fa^_fr) & 0x00000080u)) g_cpu.SR |= (1u<<1); }
}
