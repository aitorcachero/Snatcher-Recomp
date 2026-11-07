/* Generated native MC68000 operations; no input image embedded. */
#include "m68k_step_bind.h"
void snatcher_main_at_FF07B6(M68kStepContext *ctx){
  if(!(0)){ uint16_t low=(uint16_t)(g_cpu.D[0]-1u);
    g_cpu.D[0]=(g_cpu.D[0]&0xFFFF0000u)|low;
    if(low!=0xFFFFu){ctx->charge=10;g_cpu.PC=0xFF07B4u;}else ctx->charge=14;
  }else ctx->charge=12;
}
void snatcher_main_at_FF0834(M68kStepContext *ctx){
  uint16_t _tFF0834 = m68k_read16((uint32_t)(int32_t)(int16_t)0xE030);
  m68k_write16((uint32_t)(int32_t)(int16_t)0xE030, (uint16_t)(0));
  g_cpu.SR = (g_cpu.SR & ~0x0Fu) | (1u<<2);
}
void snatcher_main_at_FF08BE(M68kStepContext *ctx){
  g_cpu.A[0] = (uint32_t)(int32_t)(int16_t)0xED00;
}
void snatcher_main_at_FF152C(M68kStepContext *ctx){
  if((g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF1536u;}else ctx->charge=8;
}
void snatcher_main_at_FF16D4(M68kStepContext *ctx){
  ctx->charge=18; g_cpu.A[7]-=4; m68k_write32(g_cpu.A[7],0xFF16D6u); g_cpu.PC=0xFF16E0u;
}
void snatcher_main_at_FF42C6(M68kStepContext *ctx){
  uint16_t _FF42C6r = (uint16_t)((uint16_t)g_cpu.D[3]) & (uint16_t)0xFF00u;
  { uint16_t _fv = (uint16_t)(_FF42C6r);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 15)        g_cpu.SR |= (1u<<3); }
  g_cpu.D[3] = (g_cpu.D[3] & 0xFFFF0000u) | (uint32_t)((uint16_t)(_FF42C6r));
}
void snatcher_main_at_FF435C(M68kStepContext *ctx){
  uint8_t _tFF435C = m68k_read8((uint32_t)(g_cpu.A[1] + (int32_t)0));
  { uint8_t _fv = (uint8_t)(_tFF435C);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF43EA(M68kStepContext *ctx){
  if((g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF43F4u;}else ctx->charge=12;
}
void snatcher_main_at_FF4486(M68kStepContext *ctx){
  uint8_t _tFF4486 = m68k_read8((uint32_t)(g_cpu.A[1] + (int32_t)34));
  uint8_t _FF4486r = 0;
  { uint32_t _bn = 5u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF4486) & (1u<<_bn)) ? (1u<<2) : 0u);
    _FF4486r = (uint8_t)((uint8_t)(_tFF4486) & ~(uint8_t)(1u<<_bn)); }
  m68k_write8((uint32_t)(g_cpu.A[1] + (int32_t)34), (uint8_t)(_FF4486r));
}
void snatcher_main_at_FF4510(M68kStepContext *ctx){
  if(!(g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF4530u;}else ctx->charge=12;
}
void snatcher_main_at_FF52B6(M68kStepContext *ctx){
  m68k_write8(0x00FF7F23u, (uint8_t)((uint8_t)g_cpu.D[2]));
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[2]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF5458(M68kStepContext *ctx){
  m68k_write8((uint32_t)(g_cpu.A[1] + (int32_t)1), (uint8_t)((uint8_t)g_cpu.D[5]));
  { uint8_t _fv = (uint8_t)((uint8_t)g_cpu.D[5]);
    g_cpu.SR &= ~(0x0Fu);
    if (!_fv)             g_cpu.SR |= (1u<<2);
    if (_fv >> 7)        g_cpu.SR |= (1u<<3); }
}
void snatcher_main_at_FF5A1C(M68kStepContext *ctx){
  if(!(g_cpu.SR & (1u<<2))){ctx->charge=10;g_cpu.PC=0xFF5A24u;}else ctx->charge=12;
}
void snatcher_main_at_FF5A90(M68kStepContext *ctx){
  uint8_t _tFF5A90 = m68k_read8(0x00FF7F24);
  { uint32_t _bn = 7u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF5A90) & (1u<<_bn)) ? (1u<<2) : 0u); }
}
void snatcher_main_at_FF5C9C(M68kStepContext *ctx){
  uint8_t _tFF5C9C = m68k_read8(0x00FF7F2A);
  { uint32_t _bn = 3u;
    g_cpu.SR = (g_cpu.SR & ~(1u<<2)) | (!((uint32_t)(_tFF5C9C) & (1u<<_bn)) ? (1u<<2) : 0u); }
}
