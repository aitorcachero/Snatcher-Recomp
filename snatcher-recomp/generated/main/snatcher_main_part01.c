/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_main_at_FF0204(M68kStepContext *ctx){
  { uint32_t target=((uint32_t)(int32_t)(int16_t)0x0364)&0xFFFFFFu; ctx->charge=18;
    g_cpu.A[7]-=4; m68k_write32(g_cpu.A[7],0xFF0208u);
    g_cpu.PC=target; }
}
void snatcher_main_at_FF0808(M68kStepContext *ctx){
  g_cpu.D[1] = 0x00000000u;
  { uint32_t _fv = (uint32_t)((uint32_t)0x00000000u);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 31)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF0896(M68kStepContext *ctx){
  ctx->charge=10; g_cpu.PC=0xFF0896u;
}
void snatcher_main_at_FF0C5A(M68kStepContext *ctx){
  { uint32_t target=(0x00FF1516u)&0xFFFFFFu; ctx->charge=18;
    g_cpu.A[7]-=4; m68k_write32(g_cpu.A[7],0xFF0C5Eu);
    g_cpu.PC=target; }
}
void snatcher_main_at_FF1576(M68kStepContext *ctx){
  uint8_t _tsFF1576 = m68k_read8(g_cpu.A[6]);
  g_cpu.D[2] = (g_cpu.D[2] & 0xFFFFFF00u) | (uint32_t)((uint8_t)(_tsFF1576));
  { uint8_t _fv = (uint8_t)(_tsFF1576);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF1724(M68kStepContext *ctx){
  uint16_t _tsFF1724 = m68k_read16(g_cpu.A[0]); g_cpu.A[0] += 2;
  m68k_write16(g_cpu.A[1], (uint16_t)(_tsFF1724)); g_cpu.A[1] += 2;
  { uint16_t _fv = (uint16_t)(_tsFF1724);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 15)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF432C(M68kStepContext *ctx){
  g_cpu.A[3] = (uint32_t)(g_cpu.A[2]);
}
void snatcher_main_at_FF43AC(M68kStepContext *ctx){
  m68k_write32((uint32_t)(g_cpu.A[1] + (int32_t)108), (uint32_t)(g_cpu.A[0]));
  { uint32_t _fv = (uint32_t)(g_cpu.A[0]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 31)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF4444(M68kStepContext *ctx){
  { uint32_t target=(0xFFFF43E0u)&0xFFFFFFu; ctx->charge=20;
    g_cpu.A[7]-=4; m68k_write32(g_cpu.A[7],0xFF444Au);
    g_cpu.PC=target; }
}
void snatcher_main_at_FF44DC(M68kStepContext *ctx){
  if((g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF44E6u;}else ctx->charge=12;
}
void snatcher_main_at_FF528A(M68kStepContext *ctx){
  if(!(g_cpu.SR & (1u<<0))){ctx->charge=10;g_cpu.PC=0xFF52C0u;}else ctx->charge=12;
}
void snatcher_main_at_FF538C(M68kStepContext *ctx){
  uint32_t _tFF538C = m68k_read32((uint32_t)(0x00FF538E + m68k_brief_index_value(0x601Au, g_cpu.D[6], g_cpu.A[6]) + (26)));
  g_cpu.A[6] = (uint32_t)(_tFF538C);
}
void snatcher_main_at_FF59DC(M68kStepContext *ctx){
  if((g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF59ECu;}else ctx->charge=12;
}
void snatcher_main_at_FF5A66(M68kStepContext *ctx){
  if(!(g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF5A62u;}else ctx->charge=12;
}
void snatcher_main_at_FF5AF4(M68kStepContext *ctx){
  g_cpu.D[4] = 0x00000028u;
  { uint32_t _fv = (uint32_t)((uint32_t)0x00000028u);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 31)        g_cpu.SR |= (1u<<3); }
}
