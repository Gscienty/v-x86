#ifndef _INS_
#define _INS_

#include "cpu.h"
#include "ram.h"

typedef ubit8_t modrm_t;

#define MOD_RM_R8  0x01
#define MOD_RM_R16 0x02
#define MOD_RM_R32 0x03

#define MOD_RM_RM8  0x01
#define MOD_RM_RM16 0x02
#define MOD_RM_RM32 0x03

var_addr modrm_reg_addr(cpu_t *, modrm_t);

var_addr sib_addr(cpu_t *, ram_t *, ubit32_t);

var_addr modrm_rm_addr16(cpu_t *, ram_t *, modrm_t);
var_addr modrm_rm_addr32(cpu_t *, ram_t *, modrm_t);

#define GET_MODRM_RM_ADDR(cpu, ram, t, rms) (t *)((cpu->is_addr32 && cpu->cur_ins.prefix == INS_PREFIX_ADDRSIZE) ? modrm_rm_addr16(cpu, ram, rms) : modrm_rm_addr32(cpu, ram, rms))

boolean_t calc_pf(ubit64_t, ubit64_t);

void ins_aaa(cpu_t *);
void ins_aad(cpu_t *);
void ins_aam(cpu_t *);
void ins_aas(cpu_t *);

void ins_adc_al_imm8   (cpu_t *);
void ins_adc_ax_imm16  (cpu_t *);
void ins_adc_eax_imm32 (cpu_t *);
void ins_adc_rm8_imm8  (cpu_t *, ram_t *);
void ins_adc_rm16_imm16(cpu_t *, ram_t *);
void ins_adc_rm32_imm32(cpu_t *, ram_t *);
void ins_adc_rm16_imm8 (cpu_t *, ram_t *);
void ins_adc_rm32_imm8 (cpu_t *, ram_t *);
void ins_adc_rm8_r8    (cpu_t *, ram_t *);
void ins_adc_rm16_r16  (cpu_t *, ram_t *);
void ins_adc_rm32_r32  (cpu_t *, ram_t *);
void ins_adc_r8_rm8    (cpu_t *, ram_t *);
void ins_adc_r16_rm16  (cpu_t *, ram_t *);
void ins_adc_r32_rm32  (cpu_t *, ram_t *);

void ins_add_al_imm8   (cpu_t *);
void ins_add_ax_imm16  (cpu_t *);
void ins_add_eax_imm32 (cpu_t *);
void ins_add_rm8_imm8  (cpu_t *, ram_t *);
void ins_add_rm16_imm16(cpu_t *, ram_t *);
void ins_add_rm32_imm32(cpu_t *, ram_t *);
void ins_add_rm16_imm8 (cpu_t *, ram_t *);
void ins_add_rm32_imm8 (cpu_t *, ram_t *);
void ins_add_rm8_r8    (cpu_t *, ram_t *);
void ins_add_rm16_r16  (cpu_t *, ram_t *);
void ins_add_rm32_r32  (cpu_t *, ram_t *);
void ins_add_r8_rm8    (cpu_t *, ram_t *);
void ins_add_r16_rm16  (cpu_t *, ram_t *);
void ins_add_r32_rm32  (cpu_t *, ram_t *);

void ins_and_al_imm8   (cpu_t *);
void ins_and_ax_imm16  (cpu_t *);
void ins_and_eax_imm32 (cpu_t *);
void ins_and_rm8_imm8  (cpu_t *, ram_t *);
void ins_and_rm16_imm16(cpu_t *, ram_t *);
void ins_and_rm32_imm32(cpu_t *, ram_t *);
void ins_and_rm16_imm8 (cpu_t *, ram_t *);
void ins_and_rm32_imm8 (cpu_t *, ram_t *);
void ins_and_rm8_r8    (cpu_t *, ram_t *);
void ins_and_rm16_r16  (cpu_t *, ram_t *);
void ins_and_rm32_r32  (cpu_t *, ram_t *);
void ins_and_r8_rm8    (cpu_t *, ram_t *);
void ins_and_r16_rm16  (cpu_t *, ram_t *);
void ins_and_r32_rm32  (cpu_t *, ram_t *);

void ins_arpl(cpu_t *, ram_t *);

void ins_bound16(cpu_t *, ram_t *);
void ins_bound32(cpu_t *, ram_t *);

void ins_bsf16(cpu_t *, ram_t *);
void ins_bsf32(cpu_t *, ram_t *);
void ins_bsr16(cpu_t *, ram_t *);
void ins_bsr32(cpu_t *, ram_t *);

void ins_bswap(cpu_t *);

void ins_bt16_r   (cpu_t *, ram_t *);
void ins_bt32_r   (cpu_t *, ram_t *);
void ins_bt16_imm (cpu_t *, ram_t *);
void ins_bt32_imm (cpu_t *, ram_t *);
void ins_btc16_r  (cpu_t *, ram_t *);
void ins_btc32_r  (cpu_t *, ram_t *);
void ins_btc16_imm(cpu_t *, ram_t *);
void ins_btc32_imm(cpu_t *, ram_t *);
void ins_btr16_r  (cpu_t *, ram_t *);
void ins_btr32_r  (cpu_t *, ram_t *);
void ins_btr16_imm(cpu_t *, ram_t *);
void ins_btr32_imm(cpu_t *, ram_t *);
void ins_bts16_r  (cpu_t *, ram_t *);
void ins_bts32_r  (cpu_t *, ram_t *);
void ins_bts16_imm(cpu_t *, ram_t *);
void ins_bts32_imm(cpu_t *, ram_t *);

//call

void ins_cbw (cpu_t *);
void ins_cwde(cpu_t *);

void ins_clc(cpu_t *);
void ins_cld(cpu_t *);
//void ins_cli(cpu_t *); interrupt
//clear ts cr0
void ins_cmc(cpu_t *);

void ins_cmova16  (cpu_t *, ram_t *);
void ins_cmova32  (cpu_t *, ram_t *);
void ins_cmovae16 (cpu_t *, ram_t *);
void ins_cmovae32 (cpu_t *, ram_t *);
void ins_cmovb16  (cpu_t *, ram_t *);
void ins_cmovb32  (cpu_t *, ram_t *);
void ins_cmovbe16 (cpu_t *, ram_t *);
void ins_cmovbe32 (cpu_t *, ram_t *);
void ins_cmovc16  (cpu_t *, ram_t *);
void ins_cmovc32  (cpu_t *, ram_t *);
void ins_cmove16  (cpu_t *, ram_t *);
void ins_cmove32  (cpu_t *, ram_t *);
void ins_cmovg16  (cpu_t *, ram_t *);
void ins_cmovg32  (cpu_t *, ram_t *);
void ins_cmovge16 (cpu_t *, ram_t *);
void ins_cmovge32 (cpu_t *, ram_t *);
void ins_cmovl16  (cpu_t *, ram_t *);
void ins_cmovl32  (cpu_t *, ram_t *);
void ins_cmovle16 (cpu_t *, ram_t *);
void ins_cmovle32 (cpu_t *, ram_t *);
void ins_cmovna16 (cpu_t *, ram_t *);
void ins_cmovna32 (cpu_t *, ram_t *);
void ins_cmovnae16(cpu_t *, ram_t *);
void ins_cmovnae32(cpu_t *, ram_t *);
void ins_cmovnb16 (cpu_t *, ram_t *);
void ins_cmovnb32 (cpu_t *, ram_t *);
void ins_cmovnbe16(cpu_t *, ram_t *);
void ins_cmovnbe32(cpu_t *, ram_t *);
void ins_cmovnc16 (cpu_t *, ram_t *);
void ins_cmovnc32 (cpu_t *, ram_t *);
void ins_cmovne16 (cpu_t *, ram_t *);
void ins_cmovne32 (cpu_t *, ram_t *);
void ins_cmovng16 (cpu_t *, ram_t *);
void ins_cmovng32 (cpu_t *, ram_t *);
void ins_cmovnge16(cpu_t *, ram_t *);
void ins_cmovnge32(cpu_t *, ram_t *);
void ins_cmovnl16 (cpu_t *, ram_t *);
void ins_cmovnl32 (cpu_t *, ram_t *);
void ins_cmovnle16(cpu_t *, ram_t *);
void ins_cmovnle32(cpu_t *, ram_t *);
void ins_cmovno16 (cpu_t *, ram_t *);
void ins_cmovno32 (cpu_t *, ram_t *);
void ins_cmovnp16 (cpu_t *, ram_t *);
void ins_cmovnp32 (cpu_t *, ram_t *);
void ins_cmovns16 (cpu_t *, ram_t *);
void ins_cmovns32 (cpu_t *, ram_t *);
void ins_cmovnz16 (cpu_t *, ram_t *);
void ins_cmovnz32 (cpu_t *, ram_t *);
void ins_cmovo16  (cpu_t *, ram_t *);
void ins_cmovo32  (cpu_t *, ram_t *);
void ins_cmovp16  (cpu_t *, ram_t *);
void ins_cmovp32  (cpu_t *, ram_t *);
void ins_cmovpe16 (cpu_t *, ram_t *);
void ins_cmovpe32 (cpu_t *, ram_t *);
void ins_cmovpo16 (cpu_t *, ram_t *);
void ins_cmovpo32 (cpu_t *, ram_t *);
void ins_cmovs16  (cpu_t *, ram_t *);
void ins_cmovs32  (cpu_t *, ram_t *);
void ins_cmovz16  (cpu_t *, ram_t *);
void ins_cmovz32  (cpu_t *, ram_t *);

void ins_cmp_al_imm8   (cpu_t *);
void ins_cmp_ax_imm16  (cpu_t *);
void ins_cmp_eax_imm32 (cpu_t *);
void ins_cmp_rm8_imm8  (cpu_t *, ram_t *);
void ins_cmp_rm16_imm16(cpu_t *, ram_t *);
void ins_cmp_rm32_imm32(cpu_t *, ram_t *);
void ins_cmp_rm16_imm8 (cpu_t *, ram_t *);
void ins_cmp_rm32_imm8 (cpu_t *, ram_t *);
void ins_cmp_rm8_r8    (cpu_t *, ram_t *);
void ins_cmp_rm16_r16  (cpu_t *, ram_t *);
void ins_cmp_rm32_r32  (cpu_t *, ram_t *);
void ins_cmp_r8_rm8    (cpu_t *, ram_t *);
void ins_cmp_r16_rm16  (cpu_t *, ram_t *);
void ins_cmp_r32_rm32  (cpu_t *, ram_t *);

#endif