#include "..\ins.h"

void ins_halt(cpu_t *cpu) {
    cpu->halt = TRUE;
}

#define INS_IDIV_RM(t1, t2, ut, rm, br, sr1, sr2, max, min) \
    t1 dst = (t1)br;\
    t2 src = *GET_MODRM_RM_ADDR(cpu, ram, t2, rm);\
    if(src == 0) { /*except DE*/ }\
    t2 temp = dst / src;\
    if((ut)temp > max || (ut)temp < min) { /*except DE*/ }\
    else {\
        sr1 = (ut)temp;\
        sr2 = (ut)(dst % src);\
    }


void ins_idiv_rm8 (cpu_t *cpu, ram_t *ram) { 
    INS_IDIV_RM(bit16_t, bit8_t, ubit8_t, MOD_RM_RM8, cpu->rg.ax, cpu->rg.al, cpu->rg.ah, 0x7f, 0x80) 
}
void ins_idiv_rm16(cpu_t *cpu, ram_t *ram) { 
    INS_IDIV_RM(bit32_t, bit16_t, ubit16_t, MOD_RM_RM16, (((ubit32_t)cpu->rg.dx << 16) | cpu->rg.ax), cpu->rg.ax, cpu->rg.dx, 0x7fff, 0x8000) 
}
void ins_idiv_rm32(cpu_t *cpu, ram_t *ram) { 
    INS_IDIV_RM(bit64_t, bit32_t, ubit32_t, MOD_RM_RM8, (((ubit64_t)cpu->rg.edx << 32) | cpu->rg.eax), cpu->rg.eax, cpu->rg.edx, 0x7fffffff, 0x80000000) 
}

void ins_imul_rm8 (cpu_t *cpu, ram_t *ram) {
    cpu->rg.ax = (bit16_t)((bit8_t)cpu->rg.al * *GET_MODRM_RM_ADDR(cpu, ram, bit8_t, MOD_RM_RM16));
    if(cpu->rg.ah == 0x00 || cpu->rg.ah == 0xff) {
        CLRBIT(cpu->rg.eflags, CPU_EFLAGS_CF); CLRBIT(cpu->rg.eflags, CPU_EFLAGS_OF);
    }
    else {
        SETBIT(cpu->rg.eflags, CPU_EFLAGS_CF); CLRBIT(cpu->rg.eflags, CPU_EFLAGS_OF);
    }
}

void ins_imul_rm16(cpu_t *cpu, ram_t *ram) {
    ubit32_t temp = (bit32_t)((bit16_t)cpu->rg.ax * *GET_MODRM_RM_ADDR(cpu, ram, bit16_t, MOD_RM_RM16));
    cpu->rg.dx = (ubit16_t)((temp & 0xffff0000) >> 16);
    cpu->rg.ax = (ubit16_t)(temp & 0x0000ffff);
    if(cpu->rg.dx == 0x0000 || cpu->rg.dx == 0xffff) {
        CLRBIT(cpu->rg.eflags, CPU_EFLAGS_CF); CLRBIT(cpu->rg.eflags, CPU_EFLAGS_OF);
    }
    else {
        SETBIT(cpu->rg.eflags, CPU_EFLAGS_CF); CLRBIT(cpu->rg.eflags, CPU_EFLAGS_OF);
    }
}

void ins_imul_rm32(cpu_t *cpu, ram_t *ram) {
    ubit64_t temp = (bit64_t)((bit32_t)cpu->rg.ax * *GET_MODRM_RM_ADDR(cpu, ram, bit32_t, MOD_RM_RM32));
    cpu->rg.dx = (ubit32_t)((temp & 0xffffffff00000000) >> 16);
    cpu->rg.ax = (ubit32_t)(temp & 0x00000000ffffffff);
    if(cpu->rg.dx == 0x00000000 || cpu->rg.dx == 0xffffffff) {
        CLRBIT(cpu->rg.eflags, CPU_EFLAGS_CF); CLRBIT(cpu->rg.eflags, CPU_EFLAGS_OF);
    }
    else {
        SETBIT(cpu->rg.eflags, CPU_EFLAGS_CF); CLRBIT(cpu->rg.eflags, CPU_EFLAGS_OF);
    }
}

#define INS_IMUL_R_RMX(t1, t2, r, rm)\
    t1 *rg = (t1 *)modrm_reg_addr(cpu, r);\
    t1 rmg = *GET_MODRM_RM_ADDR(cpu, ram, t1, rmg);\
    t2 temp = (t2)*rg * (t2)rmg;\
    *rg = *(t1 *)&temp;\
    if(temp != *rg) { SETBIT(cpu->rg.eflags, CPU_EFLAGS_CF); SETBIT(cpu->rg.eflags, CPU_EFLAGS_OF); } \
    else { CLRBIT(cpu->rg.eflags, CPU_EFLAGS_CF); CLRBIT(cpu->rg.eflags, CPU_EFLAGS_OF); }

void ins_imul_r_rm16(cpu_t *cpu, ram_t *ram) { INS_IMUL_R_RMX(bit16_t, bit32_t, MOD_RM_R16, MOD_RM_RM16) }
void ins_imul_r_rm32(cpu_t *cpu, ram_t *ram) { INS_IMUL_R_RMX(bit32_t, bit64_t, MOD_RM_R32, MOD_RM_RM32) }

#define INS_IMUL_R_RMX_IMMY(ddmt, rrmt, immt, r, rm)\
    ddmt temp = *(immt *)&cpu->cur_ins.immediate * *GET_MODRM_RM_ADDR(cpu, ram, rrmt, rm);\
    rrmt *dst = (rrmt *)modrm_reg_addr(cpu, r);\
    *dst = *(rrmt *)&temp;\
    if(*dst != temp) { SETBIT(cpu->rg.eflags, CPU_EFLAGS_CF); SETBIT(cpu->rg.eflags, CPU_EFLAGS_OF); }\
    else { CLRBIT(cpu->rg.eflags, CPU_EFLAGS_CF); CLRBIT(cpu->rg.eflags, CPU_EFLAGS_OF); }

void ins_imul_r_rm16_imm8 (cpu_t *cpu, ram_t *ram) { INS_IMUL_R_RMX_IMMY(bit32_t, bit16_t, bit8_t , MOD_RM_R16, MOD_RM_RM16) }
void ins_imul_r_rm32_imm8 (cpu_t *cpu, ram_t *ram) { INS_IMUL_R_RMX_IMMY(bit64_t, bit32_t, bit8_t , MOD_RM_R32, MOD_RM_RM32) }
void ins_imul_r_rm16_imm16(cpu_t *cpu, ram_t *ram) { INS_IMUL_R_RMX_IMMY(bit32_t, bit16_t, bit16_t, MOD_RM_R16, MOD_RM_RM16) }
void ins_imul_r_rm32_imm32(cpu_t *cpu, ram_t *ram) { INS_IMUL_R_RMX_IMMY(bit64_t, bit32_t, bit32_t, MOD_RM_R32, MOD_RM_RM32) }

#define INS_IMUL_RX_IMMY(t1, t2, r)\
    t1 *rg = (t1 *)modrm_reg_addr(cpu, r);\
    t1 src = *(t1 *)&cpu->cur_ins.immediate;\
    t2 temp = (t2)*rg * (t2)src;\
    *rg = *(t1 *)&temp;\
    if(temp != *rg) { SETBIT(cpu->rg.eflags, CPU_EFLAGS_CF); SETBIT(cpu->rg.eflags, CPU_EFLAGS_OF); } \
    else { CLRBIT(cpu->rg.eflags, CPU_EFLAGS_CF); CLRBIT(cpu->rg.eflags, CPU_EFLAGS_OF); }

void ins_imul_r16_imm8 (cpu_t *cpu, ram_t *ram){ INS_IMUL_RX_IMMY(bit16_t, bit8_t , MOD_RM_R16) }
void ins_imul_r32_imm8 (cpu_t *cpu, ram_t *ram){ INS_IMUL_RX_IMMY(bit32_t, bit8_t , MOD_RM_R32) }
void ins_imul_r16_imm16(cpu_t *cpu, ram_t *ram){ INS_IMUL_RX_IMMY(bit16_t, bit16_t, MOD_RM_R16) }
void ins_imul_r32_imm32(cpu_t *cpu, ram_t *ram){ INS_IMUL_RX_IMMY(bit32_t, bit32_t, MOD_RM_R32) }

#define INS_IN_A_X(rg, portIdr, t)\
    port_exec_read(port, (ubit16_t)*(t *)&portIdr, NULL);\
    rg = port->IObit8;

void ins_in_al_imm8 (cpu_t *cpu, ram_t *ram, port_t *port) { INS_IN_A_X(cpu->rg.al , cpu->cur_ins.immediate, ubit8_t ) }
void ins_in_ax_imm8 (cpu_t *cpu, ram_t *ram, port_t *port) { INS_IN_A_X(cpu->rg.ax , cpu->cur_ins.immediate, ubit8_t ) }
void ins_in_eax_imm8(cpu_t *cpu, ram_t *ram, port_t *port) { INS_IN_A_X(cpu->rg.eax, cpu->cur_ins.immediate, ubit8_t ) }
void ins_in_al_dx   (cpu_t *cpu, ram_t *ram, port_t *port) { INS_IN_A_X(cpu->rg.al , cpu->rg.dx            , ubit16_t) }
void ins_in_ax_dx   (cpu_t *cpu, ram_t *ram, port_t *port) { INS_IN_A_X(cpu->rg.ax , cpu->rg.dx            , ubit16_t) }
void ins_in_eax_dx  (cpu_t *cpu, ram_t *ram, port_t *port) { INS_IN_A_X(cpu->rg.eax, cpu->rg.dx            , ubit16_t) }

#define INS_INC_RMX(rmt, rm, l, rmtm)\
    rmt *dst = GET_MODRM_RM_ADDR(cpu, ram, rmt, rm);\
    rmt temp = *dst;\
    *dst += 1;\
    ALTBIT(cpu->rg.eflags, CPU_EFLAGS_OF, (GETNBIT(temp, l) != GETNBIT(*dst, l)));\
    ALTBIT(cpu->rg.eflags, CPU_EFLAGS_SF, GETNBIT(*dst, l));\
    ALTBIT(cpu->rg.eflags, CPU_EFLAGS_ZF, !!*dst);\
    ALTBIT(cpu->rg.eflags, CPU_EFLAGS_AF, GETBIT((temp ^ 0x01 ^ *dst) , 0x10));\
    ALTBIT(cpu->rg.eflags, CPU_EFLAGS_PF, calc_pf(rmtm, *dst));

#define INS_INC_RX(rmt, rm, l, rmtm)\
    rmt *dst = (rmt *)modrm_reg_addr(cpu, rm);\
    rmt temp = *dst;\
    *dst += 1;\
    ALTBIT(cpu->rg.eflags, CPU_EFLAGS_OF, (GETNBIT(temp, l) != GETNBIT(*dst, l)));\
    ALTBIT(cpu->rg.eflags, CPU_EFLAGS_SF, GETNBIT(*dst, l));\
    ALTBIT(cpu->rg.eflags, CPU_EFLAGS_ZF, !!*dst);\
    ALTBIT(cpu->rg.eflags, CPU_EFLAGS_AF, GETBIT((temp ^ 0x01 ^ *dst) , 0x10));\
    ALTBIT(cpu->rg.eflags, CPU_EFLAGS_PF, calc_pf(rmtm, *dst));

void ins_inc_rm8 (cpu_t *cpu, ram_t *ram) { INS_INC_RMX(ubit8_t , MOD_RM_RM8 , 8 , UBIT8_MAX ) }
void ins_inc_rm16(cpu_t *cpu, ram_t *ram) { INS_INC_RMX(ubit16_t, MOD_RM_RM16, 16, UBIT16_MAX) }
void ins_inc_rm32(cpu_t *cpu, ram_t *ram) { INS_INC_RMX(ubit32_t, MOD_RM_RM32, 32, UBIT32_MAX) }
void ins_inc_r16 (cpu_t *cpu, ram_t *ram) { INS_INC_RX (ubit16_t, MOD_RM_R16 , 16, UBIT16_MAX) }
void ins_inc_r32 (cpu_t *cpu, ram_t *ram) { INS_INC_RX (ubit32_t, MOD_RM_R32 , 32, UBIT32_MAX) }

