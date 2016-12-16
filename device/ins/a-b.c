#include "..\ins.h"

void ins_aaa(cpu_t *cpu) {
    if((cpu->rg.al & 0x0f > 0x09) || GETBIT(cpu->rg.eflags, CPU_EFLAGS_AF)) {
        cpu->rg.al += 0x06;
        cpu->rg.ah += 0x01;
        SETBIT(cpu->rg.eflags, CPU_EFLAGS_AF);
        SETBIT(cpu->rg.eflags, CPU_EFLAGS_CF);
    }
    else {
        CLRBIT(cpu->rg.eflags, CPU_EFLAGS_AF);
        CLRBIT(cpu->rg.eflags, CPU_EFLAGS_CF);
    }

    cpu->rg.al &= 0x0f;
}

void ins_aad(cpu_t *cpu) {
    ubit8_t tempAL = cpu->rg.al;
    ubit8_t tempAH = cpu->rg.ah;
    cpu->rg.al = FILTER(ubit8_t, tempAL + (tempAH * cpu->cur_ins.opcode[1]), UBIT8_MAX);
    cpu->rg.ah = 0x00;

    ALTBIT(cpu->rg.eflags, CPU_EFLAGS_SF, GETNBIT(cpu->rg.al, 8));
    ALTBIT(cpu->rg.eflags, CPU_EFLAGS_ZF, !GETBIT(cpu->rg.al, 0xff));
    ALTBIT(cpu->rg.eflags, CPU_EFLAGS_PF, calc_pf(UBIT8_MAX, cpu->rg.al));
}

void ins_aam(cpu_t *cpu) {
    ubit8_t tempAL = cpu->rg.al;
    cpu->rg.ah = tempAL / cpu->cur_ins.opcode[1];
    cpu->rg.al = tempAL % cpu->cur_ins.opcode[1];

    ALTBIT(cpu->rg.eflags, CPU_EFLAGS_SF, GETNBIT(cpu->rg.al, 8));
    ALTBIT(cpu->rg.eflags, CPU_EFLAGS_ZF, !GETBIT(cpu->rg.al, UBIT8_MAX));
    ALTBIT(cpu->rg.eflags, CPU_EFLAGS_PF, calc_pf(UBIT8_MAX, cpu->rg.al));
}

void ins_aas(cpu_t *cpu) {
    if((cpu->rg.al & 0x0f) > 0x09 || GETBIT(cpu->rg.eflags, CPU_EFLAGS_AF)) {
        cpu->rg.al -= 0x06;
        cpu->rg.ah -= 0x01;
        SETBIT(cpu->rg.eflags, CPU_EFLAGS_CF);
        SETBIT(cpu->rg.eflags, CPU_EFLAGS_AF);
    }
    else {
        CLRBIT(cpu->rg.eflags, CPU_EFLAGS_CF);
        CLRBIT(cpu->rg.eflags, CPU_EFLAGS_AF);
    }

    cpu->rg.al &= 0x0f;
}

#define INC_ADD(dst, size, dc)\
    dst = op1 + op2 + (dc && GETBIT(cpu->rg.eflags, CPU_EFLAGS_CF) ? 0x01 : 0x00); \
    ALTBIT(cpu->rg.eflags, CPU_EFLAGS_OF, ((GETNBIT(op1, size) != GETNBIT(dst, size)) && (GETNBIT(op2, size) != GETNBIT(dst, size))));\
    ALTBIT(cpu->rg.eflags, CPU_EFLAGS_SF, GETNBIT(dst, size));\
    ALTBIT(cpu->rg.eflags, CPU_EFLAGS_ZF, !GETBIT(dst, UBIT8_MAX));\
    ALTBIT(cpu->rg.eflags, CPU_EFLAGS_AF, GETBIT((op1 ^ op2 ^ dst), 0x10));\
    ALTBIT(cpu->rg.eflags, CPU_EFLAGS_CF, \
        ((GETBIT(cpu->rg.eflags, CPU_EFLAGS_CF) && op2 == UBIT8_MAX) ?\ 
            TRUE : (dst < op1 || dst < op2)));\
    ALTBIT(cpu->rg.eflags, CPU_EFLAGS_PF, calc_pf(UBIT8_MAX, dst));

#define INS_ADD_AZ_IZ(t, r, dc)\
    t op1 = r;\
    t op2 = (t)cpu->cur_ins.immediate;\
    INC_ADD(r, sizeof(t) << 3, dc);

void ins_adc_al_imm8  (cpu_t *cpu) { INS_ADD_AZ_IZ(ubit8_t , cpu->rg.al , TRUE ) }
void ins_adc_ax_imm16 (cpu_t *cpu) { INS_ADD_AZ_IZ(ubit16_t, cpu->rg.ax , TRUE ) }
void ins_adc_eax_imm32(cpu_t *cpu) { INS_ADD_AZ_IZ(ubit32_t, cpu->rg.eax, TRUE ) }
void ins_add_al_imm8  (cpu_t *cpu) { INS_ADD_AZ_IZ(ubit8_t , cpu->rg.al , FALSE) }
void ins_add_ax_imm16 (cpu_t *cpu) { INS_ADD_AZ_IZ(ubit16_t, cpu->rg.ax , FALSE) }
void ins_add_eax_imm32(cpu_t *cpu) { INS_ADD_AZ_IZ(ubit32_t, cpu->rg.eax, FALSE) }

#define INS_ADD_RMX_IMMY(t1, t2, t1s, t2f, dc)\
    t1 *dst_addr = GET_MODRM_RM_ADDR(cpu, ram, t1, t1s);\
    t1 op1 = *dst_addr;\
    t2 op2 = FILTER(t2, cpu->cur_ins.immediate, t2f);\
    INC_ADD((*dst_addr), sizeof(t1) << 3, dc);

void ins_adc_rm8_imm8  (cpu_t *cpu, ram_t *ram) { INS_ADD_RMX_IMMY(ubit8_t , ubit8_t , MOD_RM_RM8 , UBIT8_MAX , TRUE ) }
void ins_adc_rm16_imm16(cpu_t *cpu, ram_t *ram) { INS_ADD_RMX_IMMY(ubit16_t, ubit16_t, MOD_RM_RM16, UBIT16_MAX, TRUE ) }
void ins_adc_rm32_imm32(cpu_t *cpu, ram_t *ram) { INS_ADD_RMX_IMMY(ubit32_t, ubit32_t, MOD_RM_RM32, UBIT32_MAX, TRUE ) }
void ins_adc_rm16_imm8 (cpu_t *cpu, ram_t *ram) { INS_ADD_RMX_IMMY(ubit16_t, ubit8_t , MOD_RM_RM16, UBIT8_MAX , TRUE ) }
void ins_adc_rm32_imm8 (cpu_t *cpu, ram_t *ram) { INS_ADD_RMX_IMMY(ubit32_t, ubit8_t , MOD_RM_RM32, UBIT8_MAX , TRUE ) }
void ins_add_rm8_imm8  (cpu_t *cpu, ram_t *ram) { INS_ADD_RMX_IMMY(ubit8_t , ubit8_t , MOD_RM_RM8 , UBIT8_MAX , FALSE) }
void ins_add_rm16_imm16(cpu_t *cpu, ram_t *ram) { INS_ADD_RMX_IMMY(ubit16_t, ubit16_t, MOD_RM_RM16, UBIT16_MAX, FALSE) }
void ins_add_rm32_imm32(cpu_t *cpu, ram_t *ram) { INS_ADD_RMX_IMMY(ubit32_t, ubit32_t, MOD_RM_RM32, UBIT32_MAX, FALSE) }
void ins_add_rm16_imm8 (cpu_t *cpu, ram_t *ram) { INS_ADD_RMX_IMMY(ubit16_t, ubit8_t , MOD_RM_RM16, UBIT8_MAX , FALSE) }
void ins_add_rm32_imm8 (cpu_t *cpu, ram_t *ram) { INS_ADD_RMX_IMMY(ubit32_t, ubit8_t , MOD_RM_RM32, UBIT8_MAX , FALSE) }

#define INS_ADD_RMX_RX(t, rms, rs, dc)\
    t *dst_addr = GET_MODRM_RM_ADDR(cpu, ram, t, rms);\
    t op1 = *dst_addr;\
    t op2 = *(t *)modrm_reg_addr(cpu, rs);\
    INC_ADD((*dst_addr), sizeof(t) << 3, dc);

void ins_adc_rm8_r8  (cpu_t *cpu, ram_t *ram) { INS_ADD_RMX_RX(ubit8_t , MOD_RM_RM8 , MOD_RM_R8 , TRUE ) }
void ins_adc_rm16_r16(cpu_t *cpu, ram_t *ram) { INS_ADD_RMX_RX(ubit16_t, MOD_RM_RM16, MOD_RM_R16, TRUE ) }
void ins_adc_rm32_r32(cpu_t *cpu, ram_t *ram) { INS_ADD_RMX_RX(ubit32_t, MOD_RM_RM32, MOD_RM_R32, TRUE ) }
void ins_add_rm8_r8  (cpu_t *cpu, ram_t *ram) { INS_ADD_RMX_RX(ubit8_t , MOD_RM_RM8 , MOD_RM_R8 , FALSE) }
void ins_add_rm16_r16(cpu_t *cpu, ram_t *ram) { INS_ADD_RMX_RX(ubit16_t, MOD_RM_RM16, MOD_RM_R16, FALSE) }
void ins_add_rm32_r32(cpu_t *cpu, ram_t *ram) { INS_ADD_RMX_RX(ubit32_t, MOD_RM_RM32, MOD_RM_R32, FALSE) }

#define INS_ADD_RX_RMX(t, rs, rms, dc)\
    t *dst_addr = (t *)modrm_reg_addr(cpu, rs);\
    t op1 = *dst_addr;\
    t op2 = *GET_MODRM_RM_ADDR(cpu, ram, t, rms);\
    INC_ADD((*dst_addr), sizeof(t) << 3, dc);

void ins_adc_r8_rm8  (cpu_t *cpu, ram_t *ram) { INS_ADD_RX_RMX(ubit8_t , MOD_RM_R8 , MOD_RM_RM8 , TRUE) }
void ins_adc_r16_rm16(cpu_t *cpu, ram_t *ram) { INS_ADD_RX_RMX(ubit16_t, MOD_RM_R16, MOD_RM_RM16, TRUE) }
void ins_adc_r32_rm32(cpu_t *cpu, ram_t *ram) { INS_ADD_RX_RMX(ubit32_t, MOD_RM_R32, MOD_RM_RM32, TRUE) }
void ins_add_r8_rm8  (cpu_t *cpu, ram_t *ram) { INS_ADD_RX_RMX(ubit8_t , MOD_RM_R8 , MOD_RM_RM8 , FALSE) }
void ins_add_r16_rm16(cpu_t *cpu, ram_t *ram) { INS_ADD_RX_RMX(ubit16_t, MOD_RM_R16, MOD_RM_RM16, FALSE) }
void ins_add_r32_rm32(cpu_t *cpu, ram_t *ram) { INS_ADD_RX_RMX(ubit32_t, MOD_RM_R32, MOD_RM_RM32, FALSE) }



#define INC_AND(dst, size)\
    dst = op1 & op2; \
    CLRBIT(cpu->rg.eflags, CPU_EFLAGS_OF);\
    CLRBIT(cpu->rg.eflags, CPU_EFLAGS_CF);\
    ALTBIT(cpu->rg.eflags, CPU_EFLAGS_SF, GETNBIT(dst, size));\
    ALTBIT(cpu->rg.eflags, CPU_EFLAGS_ZF, !GETBIT(dst, UBIT8_MAX));\
    ALTBIT(cpu->rg.eflags, CPU_EFLAGS_PF, calc_pf(UBIT8_MAX, dst));

#define INS_AND_AZ_IZ(t, r)\
    t op1 = r;\
    t op2 = (t)cpu->cur_ins.immediate;\
    INC_AND(r, sizeof(t) << 3);

void ins_and_al_imm8  (cpu_t *cpu) { INS_AND_AZ_IZ(ubit8_t , cpu->rg.al ) }
void ins_and_ax_imm16 (cpu_t *cpu) { INS_AND_AZ_IZ(ubit16_t, cpu->rg.ax ) }
void ins_and_eax_imm32(cpu_t *cpu) { INS_AND_AZ_IZ(ubit32_t, cpu->rg.eax) }

#define INS_AND_RMX_IMMY(t1, t2, t1s, t2f)\
    t1 *dst_addr = GET_MODRM_RM_ADDR(cpu, ram, t1, t1s);\
    t1 op1 = *dst_addr;\
    t2 op2 = FILTER(t2, cpu->cur_ins.immediate, t2f);\
    INC_AND((*dst_addr), sizeof(t1) << 3);

void ins_and_rm8_imm8  (cpu_t *cpu, ram_t *ram) { INS_AND_RMX_IMMY(ubit8_t , ubit8_t , MOD_RM_RM8 , UBIT8_MAX ) }
void ins_and_rm16_imm16(cpu_t *cpu, ram_t *ram) { INS_AND_RMX_IMMY(ubit16_t, ubit16_t, MOD_RM_RM16, UBIT16_MAX) }
void ins_and_rm32_imm32(cpu_t *cpu, ram_t *ram) { INS_AND_RMX_IMMY(ubit32_t, ubit32_t, MOD_RM_RM32, UBIT32_MAX) }
void ins_and_rm16_imm8 (cpu_t *cpu, ram_t *ram) { INS_AND_RMX_IMMY(ubit16_t, ubit8_t , MOD_RM_RM16, UBIT8_MAX ) }
void ins_and_rm32_imm8 (cpu_t *cpu, ram_t *ram) { INS_AND_RMX_IMMY(ubit32_t, ubit8_t , MOD_RM_RM32, UBIT8_MAX ) }

#define INS_AND_RMX_RX(t, rms, rs)\
    t *dst_addr = GET_MODRM_RM_ADDR(cpu, ram, t, rms);\
    t op1 = *dst_addr;\
    t op2 = *(t *)modrm_reg_addr(cpu, rs);\
    INC_AND((*dst_addr), sizeof(t) << 3);

void ins_and_rm8_r8  (cpu_t *cpu, ram_t *ram) { INS_AND_RMX_RX(ubit8_t , MOD_RM_RM8 , MOD_RM_R8 ) }
void ins_and_rm16_r16(cpu_t *cpu, ram_t *ram) { INS_AND_RMX_RX(ubit16_t, MOD_RM_RM16, MOD_RM_R16) }
void ins_and_rm32_r32(cpu_t *cpu, ram_t *ram) { INS_AND_RMX_RX(ubit32_t, MOD_RM_RM32, MOD_RM_R32) }

#define INS_AND_RX_RMX(t, rs, rms)\
    t *dst_addr = (t *)modrm_reg_addr(cpu, rs);\
    t op1 = *dst_addr;\
    t op2 = *GET_MODRM_RM_ADDR(cpu, ram, t, rms);\
    INC_AND((*dst_addr), sizeof(t) << 3);

void ins_and_r8_rm8  (cpu_t *cpu, ram_t *ram) { INS_AND_RX_RMX(ubit8_t , MOD_RM_R8 , MOD_RM_RM8 ) }
void ins_and_r16_rm16(cpu_t *cpu, ram_t *ram) { INS_AND_RX_RMX(ubit16_t, MOD_RM_R16, MOD_RM_RM16) }
void ins_and_r32_rm32(cpu_t *cpu, ram_t *ram) { INS_AND_RX_RMX(ubit32_t, MOD_RM_R32, MOD_RM_RM32) }

void ins_arpl(cpu_t * cpu, ram_t* ram) {
    ubit16_t *dst_addr = GET_MODRM_RM_ADDR(cpu, ram, ubit16_t, MOD_RM_RM16);
    ubit16_t op1 = *dst_addr;
    ubit16_t op2 = *(ubit16_t *)modrm_reg_addr(cpu, MOD_RM_R16);

    if(op1 < op2) {
        SETBIT(cpu->rg.eflags, CPU_EFLAGS_ZF);
        *dst_addr = op2;
    }
    else {
        CLRBIT(cpu->rg.eflags, CPU_EFLAGS_ZF);
    }
}

void ins_bound16(cpu_t *cpu, ram_t *ram) {
    ubit16_t ai = *(ubit16_t *)modrm_reg_addr(cpu, MOD_RM_R16);
    ubit16_t *lb = GET_MODRM_RM_ADDR(cpu, ram, ubit16_t, MOD_RM_RM16);
    ubit16_t *ub = RAM_GETADDR((*ram), ((var_addr)lb + 2 - ram->base));

    if(ai < *lb || ai > *ub) { /*INS_EXCEPT_BR*/ }
}
void ins_bound32(cpu_t *cpu, ram_t *ram) {
    ubit32_t ai = *(ubit32_t *)modrm_reg_addr(cpu, MOD_RM_R32);
    ubit32_t *lb = GET_MODRM_RM_ADDR(cpu, ram, ubit32_t, MOD_RM_RM32);
    ubit32_t *ub = RAM_GETADDR((*ram), ((var_addr)lb + 4 - ram->base));

    if(ai < lb || ai > ub) { /*INS_EXCEPT_BR*/ }
}


void ins_bsf16(cpu_t *cpu, ram_t *ram) {
    ubit16_t *dst = (ubit16_t *)modrm_reg_addr(cpu, MOD_RM_R16);
    ubit16_t src = *(ubit16_t *)GET_MODRM_RM_ADDR(cpu, ram, ubit16_t, MOD_RM_RM16);

    if(src == 0) {
        SETBIT(cpu->rg.eflags, CPU_EFLAGS_ZF);
    }
    else {
        CLRBIT(cpu->rg.eflags, CPU_EFLAGS_ZF);
        ubit8_t temp = 1;
        while(!GETNBIT(src, temp)) {
            temp += 1;
            *dst = temp - 1;
        }
    }
}
void ins_bsf32(cpu_t *cpu, ram_t *ram) {
    ubit32_t *dst = (ubit32_t *)modrm_reg_addr(cpu, MOD_RM_R32);
    ubit32_t src = *(ubit32_t *)GET_MODRM_RM_ADDR(cpu, ram, ubit32_t, MOD_RM_RM32);

    if(src == 0) {
        SETBIT(cpu->rg.eflags, CPU_EFLAGS_ZF);
    }
    else {
        CLRBIT(cpu->rg.eflags, CPU_EFLAGS_ZF);
        ubit8_t temp = 1;
        while(!GETNBIT(src, temp)) {
            temp += 1;
            *dst = temp - 1;
        }
    }
}
void ins_bsr16(cpu_t *cpu, ram_t *ram) {
    ubit16_t *dst = (ubit16_t *)modrm_reg_addr(cpu, MOD_RM_R16);
    ubit16_t src = *(ubit16_t *)GET_MODRM_RM_ADDR(cpu, ram, ubit16_t, MOD_RM_RM16);

    if(src == 0) {
        SETBIT(cpu->rg.eflags, CPU_EFLAGS_ZF);
    }
    else {
        CLRBIT(cpu->rg.eflags, CPU_EFLAGS_ZF);
        ubit8_t temp = 16;
        while(!GETNBIT(src, temp)) {
            temp -= 1;
            *dst = temp - 1;
        }
    }
}
void ins_bsr32(cpu_t *cpu, ram_t *ram) {
    ubit32_t *dst = (ubit32_t *)modrm_reg_addr(cpu, MOD_RM_R32);
    ubit32_t src = *(ubit32_t *)GET_MODRM_RM_ADDR(cpu, ram, ubit32_t, MOD_RM_RM32);

    if(src == 0) {
        SETBIT(cpu->rg.eflags, CPU_EFLAGS_ZF);
    }
    else {
        CLRBIT(cpu->rg.eflags, CPU_EFLAGS_ZF);
        ubit8_t temp = 32;
        while(!GETNBIT(src, temp)) {
            temp -= 1;
            *dst = temp - 1;
        }
    }
}

void ins_bswap(cpu_t *cpu) {
    ubit8_t *dst = (ubit8_t *)modrm_reg_addr(cpu, MOD_RM_R32);
    ubit32_t temp = *(ubit32_t *)dst;

    *((ubit8_t *)((ubit8_t *)dst + 0)) = *((ubit8_t *)((ubit8_t *)&temp + 3));
    *((ubit8_t *)((ubit8_t *)dst + 1)) = *((ubit8_t *)((ubit8_t *)&temp + 2));
    *((ubit8_t *)((ubit8_t *)dst + 2)) = *((ubit8_t *)((ubit8_t *)&temp + 1));
    *((ubit8_t *)((ubit8_t *)dst + 3)) = *((ubit8_t *)((ubit8_t *)&temp + 0));
}

#define INS_BTX_RX(t, s, r, c, z, a) \
    t *base = GET_MODRM_RM_ADDR(cpu, ram, t, s);\
    t offset = *(t *)modrm_reg_addr(cpu, r) % (sizeof(t) << 3);\
    ALTBIT(cpu->rg.eflags, CPU_EFLAGS_CF, GETNBIT((*base), offset + 1));\
    if(c) { ALTBIT((*base), (1 << offset), (a || (z && !GETNBIT((*base), offset + 1)))); }

void ins_bt16_r (cpu_t *cpu, ram_t *ram) { INS_BTX_RX(ubit16_t, MOD_RM_RM16, MOD_RM_R16, FALSE, TRUE , FALSE) }
void ins_bt32_r (cpu_t *cpu, ram_t *ram) { INS_BTX_RX(ubit32_t, MOD_RM_RM32, MOD_RM_R32, FALSE, TRUE , FALSE) }
void ins_btc16_r(cpu_t *cpu, ram_t *ram) { INS_BTX_RX(ubit16_t, MOD_RM_RM16, MOD_RM_R16, TRUE , TRUE , FALSE) }
void ins_btc32_r(cpu_t *cpu, ram_t *ram) { INS_BTX_RX(ubit32_t, MOD_RM_RM32, MOD_RM_R32, TRUE , TRUE , FALSE) }
void ins_btr16_r(cpu_t *cpu, ram_t *ram) { INS_BTX_RX(ubit16_t, MOD_RM_RM16, MOD_RM_R16, TRUE , FALSE, FALSE) }
void ins_btr32_r(cpu_t *cpu, ram_t *ram) { INS_BTX_RX(ubit32_t, MOD_RM_RM32, MOD_RM_R32, TRUE , FALSE, FALSE) }
void ins_bts16_r(cpu_t *cpu, ram_t *ram) { INS_BTX_RX(ubit16_t, MOD_RM_RM16, MOD_RM_R16, TRUE , TRUE , TRUE ) }
void ins_bts32_r(cpu_t *cpu, ram_t *ram) { INS_BTX_RX(ubit32_t, MOD_RM_RM32, MOD_RM_R32, TRUE , TRUE , TRUE ) }

#define INS_BTX_IMMX(t, s, r, c, z, a) \
    t *base = GET_MODRM_RM_ADDR(cpu, ram, t, s);\
    ubit8_t offset = FILTER(ubit8_t, cpu->cur_ins.immediate, UBIT8_MAX) % (sizeof(t) << 3);\
    ALTBIT(cpu->rg.eflags, CPU_EFLAGS_CF, GETNBIT((*base), offset + 1));\
    if(c) { ALTBIT((*base), (1 << offset), (a || (z && !GETNBIT((*base), offset + 1)))); }

void ins_bt16_imm (cpu_t *cpu, ram_t *ram) { INS_BTX_IMMX(ubit16_t, MOD_RM_RM16, MOD_RM_R16, FALSE, TRUE , FALSE) }
void ins_bt32_imm (cpu_t *cpu, ram_t *ram) { INS_BTX_IMMX(ubit32_t, MOD_RM_RM32, MOD_RM_R32, FALSE, TRUE , FALSE) }
void ins_btc16_imm(cpu_t *cpu, ram_t *ram) { INS_BTX_IMMX(ubit16_t, MOD_RM_RM16, MOD_RM_R16, TRUE , TRUE , FALSE) }
void ins_btc32_imm(cpu_t *cpu, ram_t *ram) { INS_BTX_IMMX(ubit32_t, MOD_RM_RM32, MOD_RM_R32, TRUE , TRUE , FALSE) }
void ins_btr16_imm(cpu_t *cpu, ram_t *ram) { INS_BTX_IMMX(ubit16_t, MOD_RM_RM16, MOD_RM_R16, TRUE , FALSE, FALSE) }
void ins_btr32_imm(cpu_t *cpu, ram_t *ram) { INS_BTX_IMMX(ubit32_t, MOD_RM_RM32, MOD_RM_R32, TRUE , FALSE, FALSE) }
void ins_bts16_imm(cpu_t *cpu, ram_t *ram) { INS_BTX_IMMX(ubit16_t, MOD_RM_RM16, MOD_RM_R16, TRUE , TRUE , TRUE ) }
void ins_bts32_imm(cpu_t *cpu, ram_t *ram) { INS_BTX_IMMX(ubit32_t, MOD_RM_RM32, MOD_RM_R32, TRUE , TRUE , TRUE ) }

