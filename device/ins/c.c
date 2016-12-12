#include "..\ins.h"

void ins_cbw (cpu_t *cpu) { cpu->rg.ax  = (bit16_t)cpu->rg.al ; }
void ins_cwde(cpu_t *cpu) { cpu->rg.eax = (ubit32_t)cpu->rg.ax; }

//call

void ins_clc(cpu_t *cpu) { CLRBIT(cpu->rg.eflags, CPU_EFLAGS_CF); }
void ins_cld(cpu_t *cpu) { CLRBIT(cpu->rg.eflags, CPU_EFLAGS_DF); }
//cli
//clts
void ins_cmc(cpu_t *cpu) { ALTBIT(cpu->rg.eflags, CPU_EFLAGS_CF, !GETBIT(cpu->rg.eflags, CPU_EFLAGS_CF)); }

#define C_F(f) GETBIT(cpu->rg.eflags, f)
#define F_C CPU_EFLAGS_CF
#define F_Z CPU_EFLAGS_ZF
#define F_S CPU_EFLAGS_SF
#define F_O CPU_EFLAGS_OF
#define F_P CPU_EFLAGS_PF

#define R16  MOD_RM_R16
#define R32  MOD_RM_R32
#define RM16 MOD_RM_RM16
#define RM32 MOD_RM_RM32

#define I_C(cond, t, r, rm) \
    if(cond) { *(t *)modrm_reg_addr(cpu, r) = *GET_MODRM_RM_ADDR(cpu, ram, t, rm); }

void ins_cmova16  (cpu_t *cpu, ram_t *ram) { I_C(!C_F(F_C) && !C_F(F_Z)            , R16, RM16); }
void ins_cmova32  (cpu_t *cpu, ram_t *ram) { I_C(!C_F(F_C) && !C_F(F_Z)            , R32, RM32); }
void ins_cmovae16 (cpu_t *cpu, ram_t *ram) { I_C(!C_F(F_C)                         , R16, RM16); }
void ins_cmovae32 (cpu_t *cpu, ram_t *ram) { I_C(!C_F(F_C)                         , R32, RM32); }
void ins_cmovb16  (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_C)                         , R16, RM16); }
void ins_cmovb32  (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_C)                         , R32, RM32); }
void ins_cmovbe16 (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_C) ||  C_F(F_Z)            , R16, RM16); }
void ins_cmovbe32 (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_C) ||  C_F(F_Z)            , R32, RM32); }
void ins_cmovc16  (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_C)                         , R16, RM16); }
void ins_cmovc32  (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_C)                         , R32, RM32); }
void ins_cmove16  (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_Z)                         , R16, RM16); }
void ins_cmove32  (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_Z)                         , R32, RM32); }
void ins_cmovg16  (cpu_t *cpu, ram_t *ram) { I_C(!C_F(F_Z) &&  C_F(F_S) == C_F(F_O), R16, RM16); }
void ins_cmovg32  (cpu_t *cpu, ram_t *ram) { I_C(!C_F(F_Z) &&  C_F(F_S) == C_F(F_O), R32, RM32); }
void ins_cmovge16 (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_S) ==  C_F(F_O)            , R16, RM16); }
void ins_cmovge32 (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_S) ==  C_F(F_O)            , R32, RM32); }
void ins_cmovl16  (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_S) !=  C_F(F_O)            , R16, RM16); }
void ins_cmovl32  (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_S) !=  C_F(F_O)            , R32, RM32); }
void ins_cmovle16 (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_Z) &&  C_F(F_S) != C_F(F_O), R16, RM16); }
void ins_cmovle32 (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_Z) &&  C_F(F_S) != C_F(F_O), R32, RM32); }
void ins_cmovna16 (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_C) ||  C_F(F_Z)            , R16, RM16); }
void ins_cmovna32 (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_C) ||  C_F(F_Z)            , R32, RM32); }
void ins_cmovnae16(cpu_t *cpu, ram_t *ram) { I_C( C_F(F_C)                         , R16, RM16); }
void ins_cmovnae32(cpu_t *cpu, ram_t *ram) { I_C( C_F(F_C)                         , R32, RM32); }
void ins_cmovnb16 (cpu_t *cpu, ram_t *ram) { I_C(!C_F(F_C)                         , R16, RM16); }
void ins_cmovnb32 (cpu_t *cpu, ram_t *ram) { I_C(!C_F(F_C)                         , R32, RM32); }
void ins_cmovnbe16(cpu_t *cpu, ram_t *ram) { I_C(!C_F(F_C) && !C_F(F_Z)            , R16, RM16); }
void ins_cmovnbe32(cpu_t *cpu, ram_t *ram) { I_C(!C_F(F_C) && !C_F(F_Z)            , R32, RM32); }
void ins_cmovnc16 (cpu_t *cpu, ram_t *ram) { I_C(!C_F(F_C)                         , R16, RM16); }
void ins_cmovnc32 (cpu_t *cpu, ram_t *ram) { I_C(!C_F(F_C)                         , R32, RM32); }
void ins_cmovne16 (cpu_t *cpu, ram_t *ram) { I_C(!C_F(F_Z)                         , R16, RM16); }
void ins_cmovne32 (cpu_t *cpu, ram_t *ram) { I_C(!C_F(F_Z)                         , R32, RM32); }
void ins_cmovng16 (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_Z) ||  C_F(F_S) != C_F(F_O), R16, RM16); }
void ins_cmovng32 (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_Z) ||  C_F(F_S) != C_F(F_O), R32, RM32); }
void ins_cmovnge16(cpu_t *cpu, ram_t *ram) { I_C( C_F(F_S) !=  C_F(F_O)            , R16, RM16); }
void ins_cmovnge32(cpu_t *cpu, ram_t *ram) { I_C( C_F(F_S) !=  C_F(F_O)            , R32, RM32); }
void ins_cmovnl16 (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_S) ==  C_F(F_O)            , R16, RM16); }
void ins_cmovnl32 (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_S) ==  C_F(F_O)            , R32, RM32); }
void ins_cmovnle16(cpu_t *cpu, ram_t *ram) { I_C(!C_F(F_Z) &&  C_F(F_S) == C_F(F_O), R16, RM16); }
void ins_cmovnle32(cpu_t *cpu, ram_t *ram) { I_C(!C_F(F_Z) &&  C_F(F_S) == C_F(F_O), R32, RM32); }
void ins_cmovnp16 (cpu_t *cpu, ram_t *ram) { I_C(!C_F(F_P)                         , R16, RM16); }
void ins_cmovnp32 (cpu_t *cpu, ram_t *ram) { I_C(!C_F(F_P)                         , R32, RM32); }
void ins_cmovns16 (cpu_t *cpu, ram_t *ram) { I_C(!C_F(F_S)                         , R16, RM16); }
void ins_cmovns32 (cpu_t *cpu, ram_t *ram) { I_C(!C_F(F_S)                         , R32, RM32); }
void ins_cmovnz16 (cpu_t *cpu, ram_t *ram) { I_C(!C_F(F_Z)                         , R16, RM16); }
void ins_cmovnz32 (cpu_t *cpu, ram_t *ram) { I_C(!C_F(F_Z)                         , R32, RM32); }
void ins_cmovo16  (cpu_t *cpu, ram_t *ram) { I_C(!C_F(F_O)                         , R16, RM16); }
void ins_cmovo32  (cpu_t *cpu, ram_t *ram) { I_C(!C_F(F_O)                         , R32, RM32); }
void ins_cmovp16  (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_P)                         , R16, RM16); }
void ins_cmovp32  (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_P)                         , R32, RM32); }
void ins_cmovpe16 (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_P)                         , R16, RM16); }
void ins_cmovpe32 (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_P)                         , R32, RM32); }
void ins_cmovpo16 (cpu_t *cpu, ram_t *ram) { I_C(!C_F(F_P)                         , R16, RM16); }
void ins_cmovpo32 (cpu_t *cpu, ram_t *ram) { I_C(!C_F(F_P)                         , R32, RM32); }
void ins_cmovs16  (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_S)                         , R16, RM16); }
void ins_cmovs32  (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_S)                         , R32, RM32); }
void ins_cmovz16  (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_Z)                         , R16, RM16); }
void ins_cmovz32  (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_Z)                         , R32, RM32); }

#define INS_CMP(p1, p2, t, l, m) \
    t op1 = p1;\
    t op2 = p2;\
    t temp = op1 - op2;\
    ALTBIT(cpu->rg.eflags, CPU_EFLAGS_CF, op1 < op2);\
    ALTBIT(cpu->rg.eflags, CPU_EFLAGS_OF, GETNBIT(op1, l) != GETNBIT(op2, l) && GETNBIT(temp, l) == GETNBIT(op2, l));\
    ALTBIT(cpu->rg.eflags, CPU_EFLAGS_SF, GETNBIT(temp, l));\
    ALTBIT(cpu->rg.eflags, CPU_EFLAGS_AF, GETBIT((op1 ^ op2 ^ temp), 0x10));\
    ALTBIT(cpu->rg.eflags, CPU_EFLAGS_AF, GETBIT((op1 ^ op2 ^ temp), 0x10));\
    ALTBIT(cpu->rg.eflags, CPU_EFLAGS_PF, calc_pf(m, temp));

#define CMP_RM_IMM(t, t2, l, rm, m) INS_CMP(*(t *)(GET_MODRM_RM_ADDR(cpu, ram, t, rm), (t)*(t2 *)cpu->cur_ins.immediate, t, l, m))
#define CMP_RM_R(t, l, rm, r, m) INS_CMP(*(t *)GET_MODRM_RM_ADDR(cpu, ram, t, rm), *(t *)modrm_reg_addr(cpu, r), t, l, m);
#define CMP_R_RM(t, l, rm, r, m) INS_CMP(*(t *)modrm_reg_addr(cpu, r), *(t *)GET_MODRM_RM_ADDR(cpu, ram, t, rm), t, l, m);

void ins_cmp_al_imm8   (cpu_t *cpu) { INS_CMP(cpu->rg.al , (ubit8_t )cpu->cur_ins.immediate, ubit8_t , 8 , UBIT8_MAX ) }
void ins_cmp_ax_imm16  (cpu_t *cpu) { INS_CMP(cpu->rg.ax , (ubit16_t)cpu->cur_ins.immediate, ubit16_t, 16, UBIT16_MAX) }
void ins_cmp_eax_imm32 (cpu_t *cpu) { INS_CMP(cpu->rg.eax, (ubit32_t)cpu->cur_ins.immediate, ubit32_t, 32, UBIT32_MAX) }
void ins_cmp_rm8_imm8  (cpu_t *cpu, ram_t *ram) { CMP_RM_IMM(ubit8_t , ubit8_t , 8 , MOD_RM_RM8 , UBIT8_MAX ) }
void ins_cmp_rm16_imm16(cpu_t *cpu, ram_t *ram) { CMP_RM_IMM(ubit16_t, ubit16_t, 16, MOD_RM_RM16, UBIT16_MAX) }
void ins_cmp_rm32_imm32(cpu_t *cpu, ram_t *ram) { CMP_RM_IMM(ubit32_t, ubit32_t, 32, MOD_RM_RM32, UBIT32_MAX) }
void ins_cmp_rm16_imm8 (cpu_t *cpu, ram_t *ram) { CMP_RM_IMM(ubit16_t, bit8_t  , 16, MOD_RM_RM16, UBIT16_MAX) }
void ins_cmp_rm32_imm8 (cpu_t *cpu, ram_t *ram) { CMP_RM_IMM(ubit32_t, bit8_t  , 32, MOD_RM_RM32, UBIT32_MAX) }
void ins_cmp_rm8_r8    (cpu_t *cpu, ram_t *ram) { CMP_RM_R(ubit8_t , 8 , MOD_RM_RM8 , MOD_RM_R8 , UBIT8_MAX ) }
void ins_cmp_rm16_r16  (cpu_t *cpu, ram_t *ram) { CMP_RM_R(ubit16_t, 16, MOD_RM_RM16, MOD_RM_R16, UBIT16_MAX) }
void ins_cmp_rm32_r32  (cpu_t *cpu, ram_t *ram) { CMP_RM_R(ubit32_t, 32, MOD_RM_RM32, MOD_RM_R32, UBIT32_MAX) }
void ins_cmp_r8_rm8    (cpu_t *cpu, ram_t *ram) { CMP_R_RM(ubit8_t , 8 , MOD_RM_RM8 , MOD_RM_R8 , UBIT8_MAX ) }
void ins_cmp_r16_rm16  (cpu_t *cpu, ram_t *ram) { CMP_R_RM(ubit16_t, 16, MOD_RM_RM16, MOD_RM_R16, UBIT16_MAX) }
void ins_cmp_r32_rm32  (cpu_t *cpu, ram_t *ram) { CMP_R_RM(ubit32_t, 32, MOD_RM_RM32, MOD_RM_R32, UBIT32_MAX) }

