/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_main_at_FF07F0(M68kStepContext *ctx){
  ctx->charge=10; g_cpu.PC=0xFF07EAu;
}
void snatcher_main_at_FF0872(M68kStepContext *ctx){
  uint16_t _tsFF0872 = m68k_read16(0x00FFEF02);
  g_cpu.D[0] = (g_cpu.D[0] & 0xFFFF0000u) | (uint32_t)((uint16_t)(_tsFF0872));
  { uint16_t _fv = (uint16_t)(_tsFF0872);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 15)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF0BC0(M68kStepContext *ctx){
  uint8_t _tFF0BC0 = m68k_read8(0x00A12003);
  { uint32_t _bn = 1u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF0BC0) & (1u<<_bn)) ? (1u<<2) : 0u); }
}
void snatcher_main_at_FF1568(M68kStepContext *ctx){
  g_cpu.D[1] = 0x00000008u;
  { uint32_t _fv = (uint32_t)((uint32_t)0x00000008u);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 31)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF170A(M68kStepContext *ctx){
  g_cpu.D[0] = 0x0000000Eu;
  { uint32_t _fv = (uint32_t)((uint32_t)0x0000000Eu);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 31)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF4304(M68kStepContext *ctx){
  uint8_t _tFF4304 = m68k_read8(0x00FF7F24);
  uint8_t _FF4304r = 0;
  { uint32_t _bn = 3u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF4304) & (1u<<_bn)) ? (1u<<2) : 0u);
    _FF4304r = (uint8_t)((uint8_t)(_tFF4304) | (uint8_t)(1u<<_bn)); }
  m68k_write8(0x00FF7F24u, (uint8_t)(_FF4304r));
}
void snatcher_main_at_FF438E(M68kStepContext *ctx){
  uint32_t _tFF438E = m68k_read32((uint32_t)(g_cpu.A[1] + (int32_t)108));
  g_cpu.A[0] = (uint32_t)(_tFF438E);
}
void snatcher_main_at_FF4426(M68kStepContext *ctx){
  uint8_t _tFF4426 = m68k_read8((uint32_t)(g_cpu.A[1] + (int32_t)45));
  { uint8_t _fv = (uint8_t)(_tFF4426);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF44C0(M68kStepContext *ctx){
  m68k_write8((uint32_t)(g_cpu.A[1] + (int32_t)433), (uint8_t)((uint8_t)g_cpu.D[0]));
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[0]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF526E(M68kStepContext *ctx){
  uint8_t _FF526Er = (uint8_t)((uint8_t)((uint8_t)g_cpu.D[0]) - (uint8_t)0xF1u);
  { uint8_t _fa = (uint8_t)((uint8_t)((uint8_t)g_cpu.D[0])), _fb = (uint8_t)((uint8_t)0xF1u), _fr = (uint8_t)(_FF526Er);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fr)                   g_cpu.SR |= (1u<<2);
    if (_fr >> 7)              g_cpu.SR |= (1u<<3);
    if ((uint32_t)_fb > (uint32_t)_fa) { g_cpu.SR |= (1u<<0); }
    if (((_fa^_fb) & 0x00000080u) && ((_fa^_fr) & 0x00000080u)) g_cpu.SR |= (1u<<1); }
}
void snatcher_main_at_FF52F8(M68kStepContext *ctx){
  if(!(g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF5304u;}else ctx->charge=12;
}
void snatcher_main_at_FF549C(M68kStepContext *ctx){
  g_cpu.A[1] += (uint32_t)(0x00000080u);
}
void snatcher_main_at_FF5A4E(M68kStepContext *ctx){
  if(!(g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF5A4Au;}else ctx->charge=12;
}
void snatcher_main_at_FF5AD4(M68kStepContext *ctx){
  if((g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF5AE8u;}else ctx->charge=12;
}
void snatcher_main_at_FF5CD4(M68kStepContext *ctx){
  ctx->charge=16; g_cpu.PC=m68k_read32(g_cpu.A[7])&0xFFFFFFu; g_cpu.A[7]+=4;
}
