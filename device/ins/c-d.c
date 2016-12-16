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

#define I_C(cond, t, r, rm) if(cond) { *(t *)modrm_reg_addr(cpu, r) = *GET_MODRM_RM_ADDR(cpu, ram, t, rm); }

void ins_cmova16  (cpu_t *cpu, ram_t *ram) { I_C(!C_F(F_C) && !C_F(F_Z)            , ubit16_t, R16, RM16) }
void ins_cmova32  (cpu_t *cpu, ram_t *ram) { I_C(!C_F(F_C) && !C_F(F_Z)            , ubit32_t, R32, RM32) }
void ins_cmovae16 (cpu_t *cpu, ram_t *ram) { I_C(!C_F(F_C)                         , ubit16_t, R16, RM16) }
void ins_cmovae32 (cpu_t *cpu, ram_t *ram) { I_C(!C_F(F_C)                         , ubit32_t, R32, RM32) }
void ins_cmovb16  (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_C)                         , ubit16_t, R16, RM16) }
void ins_cmovb32  (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_C)                         , ubit32_t, R32, RM32) }
void ins_cmovbe16 (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_C) ||  C_F(F_Z)            , ubit16_t, R16, RM16) }
void ins_cmovbe32 (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_C) ||  C_F(F_Z)            , ubit32_t, R32, RM32) }
void ins_cmovc16  (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_C)                         , ubit16_t, R16, RM16) }
void ins_cmovc32  (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_C)                         , ubit32_t, R32, RM32) }
void ins_cmove16  (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_Z)                         , ubit16_t, R16, RM16) }
void ins_cmove32  (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_Z)                         , ubit32_t, R32, RM32) }
void ins_cmovg16  (cpu_t *cpu, ram_t *ram) { I_C(!C_F(F_Z) &&  C_F(F_S) == C_F(F_O), ubit16_t, R16, RM16) }
void ins_cmovg32  (cpu_t *cpu, ram_t *ram) { I_C(!C_F(F_Z) &&  C_F(F_S) == C_F(F_O), ubit32_t, R32, RM32) }
void ins_cmovge16 (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_S) ==  C_F(F_O)            , ubit16_t, R16, RM16) }
void ins_cmovge32 (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_S) ==  C_F(F_O)            , ubit32_t, R32, RM32) }
void ins_cmovl16  (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_S) !=  C_F(F_O)            , ubit16_t, R16, RM16) }
void ins_cmovl32  (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_S) !=  C_F(F_O)            , ubit32_t, R32, RM32) }
void ins_cmovle16 (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_Z) &&  C_F(F_S) != C_F(F_O), ubit16_t, R16, RM16) }
void ins_cmovle32 (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_Z) &&  C_F(F_S) != C_F(F_O), ubit32_t, R32, RM32) }
void ins_cmovna16 (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_C) ||  C_F(F_Z)            , ubit16_t, R16, RM16) }
void ins_cmovna32 (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_C) ||  C_F(F_Z)            , ubit32_t, R32, RM32) }
void ins_cmovnae16(cpu_t *cpu, ram_t *ram) { I_C( C_F(F_C)                         , ubit16_t, R16, RM16) }
void ins_cmovnae32(cpu_t *cpu, ram_t *ram) { I_C( C_F(F_C)                         , ubit32_t, R32, RM32) }
void ins_cmovnb16 (cpu_t *cpu, ram_t *ram) { I_C(!C_F(F_C)                         , ubit16_t, R16, RM16) }
void ins_cmovnb32 (cpu_t *cpu, ram_t *ram) { I_C(!C_F(F_C)                         , ubit32_t, R32, RM32) }
void ins_cmovnbe16(cpu_t *cpu, ram_t *ram) { I_C(!C_F(F_C) && !C_F(F_Z)            , ubit16_t, R16, RM16) }
void ins_cmovnbe32(cpu_t *cpu, ram_t *ram) { I_C(!C_F(F_C) && !C_F(F_Z)            , ubit32_t, R32, RM32) }
void ins_cmovnc16 (cpu_t *cpu, ram_t *ram) { I_C(!C_F(F_C)                         , ubit16_t, R16, RM16) }
void ins_cmovnc32 (cpu_t *cpu, ram_t *ram) { I_C(!C_F(F_C)                         , ubit32_t, R32, RM32) }
void ins_cmovne16 (cpu_t *cpu, ram_t *ram) { I_C(!C_F(F_Z)                         , ubit16_t, R16, RM16) }
void ins_cmovne32 (cpu_t *cpu, ram_t *ram) { I_C(!C_F(F_Z)                         , ubit32_t, R32, RM32) }
void ins_cmovng16 (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_Z) ||  C_F(F_S) != C_F(F_O), ubit16_t, R16, RM16) }
void ins_cmovng32 (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_Z) ||  C_F(F_S) != C_F(F_O), ubit32_t, R32, RM32) }
void ins_cmovnge16(cpu_t *cpu, ram_t *ram) { I_C( C_F(F_S) !=  C_F(F_O)            , ubit16_t, R16, RM16) }
void ins_cmovnge32(cpu_t *cpu, ram_t *ram) { I_C( C_F(F_S) !=  C_F(F_O)            , ubit32_t, R32, RM32) }
void ins_cmovnl16 (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_S) ==  C_F(F_O)            , ubit16_t, R16, RM16) }
void ins_cmovnl32 (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_S) ==  C_F(F_O)            , ubit32_t, R32, RM32) }
void ins_cmovnle16(cpu_t *cpu, ram_t *ram) { I_C(!C_F(F_Z) &&  C_F(F_S) == C_F(F_O), ubit16_t, R16, RM16) }
void ins_cmovnle32(cpu_t *cpu, ram_t *ram) { I_C(!C_F(F_Z) &&  C_F(F_S) == C_F(F_O), ubit32_t, R32, RM32) }
void ins_cmovnp16 (cpu_t *cpu, ram_t *ram) { I_C(!C_F(F_P)                         , ubit16_t, R16, RM16) }
void ins_cmovnp32 (cpu_t *cpu, ram_t *ram) { I_C(!C_F(F_P)                         , ubit32_t, R32, RM32) }
void ins_cmovns16 (cpu_t *cpu, ram_t *ram) { I_C(!C_F(F_S)                         , ubit16_t, R16, RM16) }
void ins_cmovns32 (cpu_t *cpu, ram_t *ram) { I_C(!C_F(F_S)                         , ubit32_t, R32, RM32) }
void ins_cmovnz16 (cpu_t *cpu, ram_t *ram) { I_C(!C_F(F_Z)                         , ubit16_t, R16, RM16) }
void ins_cmovnz32 (cpu_t *cpu, ram_t *ram) { I_C(!C_F(F_Z)                         , ubit32_t, R32, RM32) }
void ins_cmovo16  (cpu_t *cpu, ram_t *ram) { I_C(!C_F(F_O)                         , ubit16_t, R16, RM16) }
void ins_cmovo32  (cpu_t *cpu, ram_t *ram) { I_C(!C_F(F_O)                         , ubit32_t, R32, RM32) }
void ins_cmovp16  (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_P)                         , ubit16_t, R16, RM16) }
void ins_cmovp32  (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_P)                         , ubit32_t, R32, RM32) }
void ins_cmovpe16 (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_P)                         , ubit16_t, R16, RM16) }
void ins_cmovpe32 (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_P)                         , ubit32_t, R32, RM32) }
void ins_cmovpo16 (cpu_t *cpu, ram_t *ram) { I_C(!C_F(F_P)                         , ubit16_t, R16, RM16) }
void ins_cmovpo32 (cpu_t *cpu, ram_t *ram) { I_C(!C_F(F_P)                         , ubit32_t, R32, RM32) }
void ins_cmovs16  (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_S)                         , ubit16_t, R16, RM16) }
void ins_cmovs32  (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_S)                         , ubit32_t, R32, RM32) }
void ins_cmovz16  (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_Z)                         , ubit16_t, R16, RM16) }
void ins_cmovz32  (cpu_t *cpu, ram_t *ram) { I_C( C_F(F_Z)                         , ubit32_t, R32, RM32) }

#define INS_CMP(p1, p2, t, m) \
    t op1 = p1;\
    t op2 = p2;\
    t temp = op1 - op2;\
    ALTBIT(cpu->rg.eflags, CPU_EFLAGS_CF, op1 < op2);\
    ALTBIT(cpu->rg.eflags, CPU_EFLAGS_OF, GETNBIT(op1, sizeof(t) << 3) != GETNBIT(op2, sizeof(t) << 3) && GETNBIT(temp, sizeof(t) << 3) == GETNBIT(op2, sizeof(t) << 3));\
    ALTBIT(cpu->rg.eflags, CPU_EFLAGS_SF, GETNBIT(temp, sizeof(t) << 3));\
    ALTBIT(cpu->rg.eflags, CPU_EFLAGS_AF, GETBIT((op1 ^ op2 ^ temp), 0x10));\
    ALTBIT(cpu->rg.eflags, CPU_EFLAGS_ZF, !!temp);\
    ALTBIT(cpu->rg.eflags, CPU_EFLAGS_PF, calc_pf(m, temp));

#define CMP_RM_IMM(t, t2, rm, m) INS_CMP(*(t *)GET_MODRM_RM_ADDR(cpu, ram, t, rm), (t)*(t2 *)&cpu->cur_ins.immediate, t, m)
#define CMP_RM_R(t, rm, r, m) INS_CMP(*(t *)GET_MODRM_RM_ADDR(cpu, ram, t, rm), *(t *)modrm_reg_addr(cpu, r), t, m);
#define CMP_R_RM(t, rm, r, m) INS_CMP(*(t *)modrm_reg_addr(cpu, r), *GET_MODRM_RM_ADDR(cpu, ram, t, rm), t, m);

void ins_cmp_al_imm8   (cpu_t *cpu) { INS_CMP(cpu->rg.al , *(bit8_t *)&cpu->cur_ins.immediate  , bit8_t , UBIT8_MAX ) }
void ins_cmp_ax_imm16  (cpu_t *cpu) { INS_CMP(cpu->rg.ax , *(ubit16_t *)&cpu->cur_ins.immediate, bit16_t, UBIT16_MAX) }
void ins_cmp_eax_imm32 (cpu_t *cpu) { INS_CMP(cpu->rg.eax, *(ubit32_t *)&cpu->cur_ins.immediate, bit32_t, UBIT32_MAX) }
void ins_cmp_rm8_imm8  (cpu_t *cpu, ram_t *ram) { CMP_RM_IMM(bit8_t , bit8_t , MOD_RM_RM8 , UBIT8_MAX  ) }
void ins_cmp_rm16_imm16(cpu_t *cpu, ram_t *ram) { CMP_RM_IMM(bit16_t, bit16_t, MOD_RM_RM16, UBIT16_MAX ) }
void ins_cmp_rm32_imm32(cpu_t *cpu, ram_t *ram) { CMP_RM_IMM(bit32_t, bit32_t, MOD_RM_RM32, UBIT32_MAX ) }
void ins_cmp_rm16_imm8 (cpu_t *cpu, ram_t *ram) { CMP_RM_IMM(bit16_t, bit8_t , MOD_RM_RM16, UBIT16_MAX ) }
void ins_cmp_rm32_imm8 (cpu_t *cpu, ram_t *ram) { CMP_RM_IMM(bit32_t, bit8_t , MOD_RM_RM32, UBIT32_MAX ) }
void ins_cmp_rm8_r8    (cpu_t *cpu, ram_t *ram) { CMP_RM_R(bit8_t , MOD_RM_RM8 , MOD_RM_R8 , UBIT8_MAX ) }
void ins_cmp_rm16_r16  (cpu_t *cpu, ram_t *ram) { CMP_RM_R(bit16_t, MOD_RM_RM16, MOD_RM_R16, UBIT16_MAX) }
void ins_cmp_rm32_r32  (cpu_t *cpu, ram_t *ram) { CMP_RM_R(bit32_t, MOD_RM_RM32, MOD_RM_R32, UBIT32_MAX) }
void ins_cmp_r8_rm8    (cpu_t *cpu, ram_t *ram) { CMP_R_RM(bit8_t , MOD_RM_RM8 , MOD_RM_R8 , UBIT8_MAX ) }
void ins_cmp_r16_rm16  (cpu_t *cpu, ram_t *ram) { CMP_R_RM(bit16_t, MOD_RM_RM16, MOD_RM_R16, UBIT16_MAX) }
void ins_cmp_r32_rm32  (cpu_t *cpu, ram_t *ram) { CMP_R_RM(bit32_t, MOD_RM_RM32, MOD_RM_R32, UBIT32_MAX) }

#define INS_CMPS_M(t, m) \ 
    if(cpu->is_addr32) {\
        INS_CMP(*(t *)RAM_SEG_GETADDR((*ram), cpu->rg.ds.base, cpu->rg.esi), *(t *)RAM_SEG_GETADDR((*ram), cpu->rg.es.base, cpu->rg.edi), t, m)\
        cpu->rg.esi += GETBIT(cpu->rg.eflags, CPU_EFLAGS_DF) ? -sizeof(t) : sizeof(t);\
        cpu->rg.edi += GETBIT(cpu->rg.eflags, CPU_EFLAGS_DF) ? -sizeof(t) : sizeof(t);\
    }\
    else {\
        INS_CMP(*(t *)RAM_SEG_GETADDR((*ram), cpu->rg.ds.base, cpu->rg.si), *(t *)(cpu->rg.es.base, cpu->rg.di), t, m)\
        cpu->rg.si += GETBIT(cpu->rg.eflags, CPU_EFLAGS_DF) ? -sizeof(t) : sizeof(t);\
        cpu->rg.di += GETBIT(cpu->rg.eflags, CPU_EFLAGS_DF) ? -sizeof(t) : sizeof(t);\
    }

void ins_cmps_m8 (cpu_t *cpu, ram_t *ram) { INS_CMPS_M(ubit8_t , UBIT8_MAX ) }
void ins_cmps_m16(cpu_t *cpu, ram_t *ram) { INS_CMPS_M(ubit16_t, UBIT16_MAX) }
void ins_cmps_m32(cpu_t *cpu, ram_t *ram) { INS_CMPS_M(ubit32_t, UBIT32_MAX) }
void ins_cmpsb   (cpu_t *cpu, ram_t *ram) { INS_CMPS_M(ubit8_t , UBIT8_MAX ) }
void ins_cmpsw   (cpu_t *cpu, ram_t *ram) { INS_CMPS_M(ubit16_t, UBIT16_MAX) }
void ins_cmpsd   (cpu_t *cpu, ram_t *ram) { INS_CMPS_M(ubit32_t, UBIT32_MAX) }

#define INS_CMPXCHG(t, rm, r, rgt) \
    t *rm_addr = GET_MODRM_RM_ADDR(cpu, ram, t, rm);\
    if(*rm_addr == rgt) {\
        SETBIT(cpu->rg.eflags, CPU_EFLAGS_ZF);\
        *rm_addr = *(t *)modrm_reg_addr(cpu, r);\
    }\
    else {\
        CLRBIT(cpu->rg.eflags, CPU_EFLAGS_ZF);\
        rgt = *rm_addr;\
    }

void ins_cmpxchg8 (cpu_t *cpu, ram_t *ram) { INS_CMPXCHG(ubit8_t , MOD_RM_RM8 , MOD_RM_R8 , cpu->rg.al ) }
void ins_cmpxchg16(cpu_t *cpu, ram_t *ram) { INS_CMPXCHG(ubit16_t, MOD_RM_RM16, MOD_RM_R16, cpu->rg.ax ) }
void ins_cmpxchg32(cpu_t *cpu, ram_t *ram) { INS_CMPXCHG(ubit32_t, MOD_RM_RM32, MOD_RM_R32, cpu->rg.eax) }

void ins_cmpxchg8b(cpu_t *cpu, ram_t *ram) {
    ubit32_t *dest_l = (ubit32_t *)GET_MODRM_RM_ADDR(cpu, ram, ubit32_t, MOD_RM_RM32);
    ubit32_t *dest_h = (ubit32_t *)RAM_GETADDR((*ram), ((var_addr)dest_l - ram->base + 4));

    if(*dest_h == cpu->rg.edx && *dest_l == cpu->rg.eax) {
        SETBIT(cpu->rg.eflags, CPU_EFLAGS_ZF);
        *dest_l = cpu->rg.ebx;
        *dest_h = cpu->rg.ecx;
    }
    else {
        CLRBIT(cpu->rg.eflags, CPU_EFLAGS_ZF);
        cpu->rg.eax = *dest_l;
        cpu->rg.edx = *dest_h;
    }
}

void ins_cwd(cpu_t *cpu) { cpu->rg.dx  = GETNBIT(cpu->rg.ax , 16) ? 0xffff     : 0x0000    ; }
void ins_cdq(cpu_t *cpu) { cpu->rg.edx = GETNBIT(cpu->rg.eax, 32) ? 0xffffffff : 0x00000000; }

#define INS_DAX(f) \
    if((cpu->rg.al & 0x0f) > 0x09 || GETBIT(cpu->rg.eflags, CPU_EFLAGS_AF)) {\
        ubit8_t origin_AL = cpu->rg.al;\
        cpu->rg.al += f ? 0x06 : -0x06;\
        ALTBIT(cpu->rg.eflags, CPU_EFLAGS_CF,\ 
            GETBIT(cpu->rg.eflags, CPU_EFLAGS_CF) || (!f && cpu->rg.al < origin_AL) || (f ? cpu->rg.al : origin_AL) < 0x06);\
        SETBIT(cpu->rg.eflags, CPU_EFLAGS_AF);\
    }\
    else { SETBIT(cpu->rg.eflags, CPU_EFLAGS_AF); }\
    if((cpu->rg.al & 0xf0) > 0x90 || GETBIT(cpu->rg.eflags, CPU_EFLAGS_CF)) {\
        cpu->rg.al += f ? 0x60 : -0x60;\
        SETBIT(cpu->rg.eflags, CPU_EFLAGS_CF);\
    }\
    else { CLRBIT(cpu->rg.eflags, CPU_EFLAGS_CF); }

void ins_daa(cpu_t *cpu) { INS_DAX(TRUE ) }
void ins_das(cpu_t *cpu) { INS_DAX(FALSE) }

#define INS_DEC_RMX(t, rm, m)\
    ubit8_t size = sizeof(t) << 3;\
    t *dst = GET_MODRM_RM_ADDR(cpu, ram, t, rm);\
    t origin_dst = *dst;\
    *dst -= 0x01;\
    ALTBIT(cpu->rg.eflags, CPU_EFLAGS_SF, GETNBIT(*dst, size));\
    ALTBIT(cpu->rg.eflags, CPU_EFLAGS_ZF, !GETBIT(*dst, m));\
    ALTBIT(cpu->rg.eflags, CPU_EFLAGS_OF, GETNBIT(origin_dst, size) && !GETNBIT(*dst, size));\
    ALTBIT(cpu->rg.eflags, CPU_EFLAGS_AF, GETNBIT(origin_dst, size) && !GETNBIT(*dst, size));\
    ALTBIT(cpu->rg.eflags, CPU_EFLAGS_AF, GETBIT((origin_dst ^ 0x01 ^ *dst), 0x10));\
    ALTBIT(cpu->rg.eflags, CPU_EFLAGS_PF, calc_pf(m, *dst));\

void ins_dec_rm8 (cpu_t *cpu, ram_t *ram) { INS_DEC_RMX(ubit8_t , MOD_RM_RM8 , UBIT8_MAX ) }
void ins_dec_rm16(cpu_t *cpu, ram_t *ram) { INS_DEC_RMX(ubit16_t, MOD_RM_RM16, UBIT16_MAX) }
void ins_dec_rm32(cpu_t *cpu, ram_t *ram) { INS_DEC_RMX(ubit32_t, MOD_RM_RM32, UBIT32_MAX) }

#define INS_DEC_RX(t, r, m)\
    ubit8_t size = sizeof(t) << 3;\
    t *dst = (t *)modrm_reg_addr(cpu, r);\
    t origin_dst = *dst;\
    *dst -= 0x01;\
    ALTBIT(cpu->rg.eflags, CPU_EFLAGS_SF, GETNBIT(*dst, size));\
    ALTBIT(cpu->rg.eflags, CPU_EFLAGS_ZF, !GETBIT(*dst, m));\
    ALTBIT(cpu->rg.eflags, CPU_EFLAGS_OF, GETNBIT(origin_dst, size) && !GETNBIT(*dst, size));\
    ALTBIT(cpu->rg.eflags, CPU_EFLAGS_AF, GETNBIT(origin_dst, size) && !GETNBIT(*dst, size));\
    ALTBIT(cpu->rg.eflags, CPU_EFLAGS_AF, GETBIT((origin_dst ^ 0x01 ^ *dst), 0x10));\
    ALTBIT(cpu->rg.eflags, CPU_EFLAGS_PF, calc_pf(m, *dst));\

void ins_dec_r16(cpu_t *cpu) { INS_DEC_RX(ubit16_t, MOD_RM_R16, UBIT16_MAX) }
void ins_dec_r32(cpu_t *cpu) { INS_DEC_RX(ubit32_t, MOD_RM_R32, UBIT32_MAX) }

#define INS_DIV_RM(t1, t2, rm, br, sr1, sr2, max) \
    t1 dst = br;\
    t2 src = *GET_MODRM_RM_ADDR(cpu, ram, t2, rm);\
    if(src == 0) { /*except DE*/ }\
    t2 temp = dst / src;\
    if(temp > max) { /*except DE*/ }\
    else {\
        sr1 = temp;\
        sr2 = dst % src;\
    }

void ins_div_rm8 (cpu_t *cpu, ram_t *ram) { INS_DIV_RM(ubit16_t, ubit8_t , MOD_RM_RM8 , cpu->rg.ax, cpu->rg.al, cpu->rg.ah, UBIT8_MAX) }
void ins_div_rm16(cpu_t *cpu, ram_t *ram) { INS_DIV_RM(ubit32_t, ubit16_t, MOD_RM_RM16, ((ubit32_t)cpu->rg.dx << 16) | ((ubit32_t)cpu->rg.ax), cpu->rg.ax, cpu->rg.dx, UBIT16_MAX) }
void ins_div_rm32(cpu_t *cpu, ram_t *ram) { INS_DIV_RM(ubit64_t, ubit32_t, MOD_RM_RM32, ((ubit64_t)cpu->rg.edx << 32) | ((ubit32_t)cpu->rg.eax), cpu->rg.eax, cpu->rg.edx, UBIT32_MAX) }