#include "cpu.h"
#include "ins.h"

boolean_t calc_pf(ubit64_t mask, ubit64_t n) {
    boolean_t result = TRUE;
    ubit64_t bit_ptr = 1;
    while(mask & bit_ptr) {
        result ^= !!(n & bit_ptr);
        bit_ptr <<= 1;
    }
    return result;
}

void ins_aaa(cpu_t cpu) {
    if((cpu.rg.al & 0x0f > 0x09) || GETBIT(cpu.rg.eflags, CPU_EFLAGS_AF)) {
        cpu.rg.al += 0x06;
        cpu.rg.ah += 0x01;
        SETBIT(cpu.rg.eflags, CPU_EFLAGS_AF);
        SETBIT(cpu.rg.eflags, CPU_EFLAGS_CF);
    }
    else {
        CLRBIT(cpu.rg.eflags, CPU_EFLAGS_AF);
        CLRBIT(cpu.rg.eflags, CPU_EFLAGS_CF);
    }

    cpu.rg.al &= 0x0f;
}

void ins_aad(cpu_t cpu) {
    ubit8_t tempAL = cpu.rg.al;
    ubit8_t tempAH = cpu.rg.ah;
    cpu.rg.al = FILTER(ubit8_t, UBIT8_MAX, 
        (tempAL + (tempAH * cpu.cur_ins.opcode[1])) & 0xff);
    cpu.rg.ah = 0x00;

    ALTBIT(cpu.rg.eflags, CPU_EFLAGS_SF, GETNBIT(cpu.rg.al, 8));
    ALTBIT(cpu.rg.eflags, CPU_EFLAGS_ZF, !!!cpu.rg.al);
    ALTBIT(cpu.rg.eflags, CPU_EFLAGS_PF, calc_pf(UBIT8_MAX, cpu.rg.al));
}

void ins_aam(cpu_t cpu) {
    ubit8_t tempAL = cpu.rg.al;
    cpu.rg.ah = tempAL / cpu.cur_ins.opcode[1];
    cpu.rg.al = tempAL % cpu.cur_ins.opcode[1];

    ALTBIT(cpu.rg.eflags, CPU_EFLAGS_SF, GETNBIT(cpu.rg.al, 8));
    ALTBIT(cpu.rg.eflags, CPU_EFLAGS_ZF, !!!cpu.rg.al);
    ALTBIT(cpu.rg.eflags, CPU_EFLAGS_PF, calc_pf(UBIT8_MAX, cpu.rg.al));
}

void ins_aas(cpu_t cpu) {
    if((cpu.rg.al & 0x0f) > 0x09 || GETBIT(cpu.rg.eflags, CPU_EFLAGS_AF)) {
        cpu.rg.al -= 0x06;
        cpu.rg.ah -= 0x01;
        SETBIT(cpu.rg.eflags, CPU_EFLAGS_CF);
        SETBIT(cpu.rg.eflags, CPU_EFLAGS_AF);
    }
    else {
        CLRBIT(cpu.rg.eflags, CPU_EFLAGS_CF);
        CLRBIT(cpu.rg.eflags, CPU_EFLAGS_AF);
    }

    cpu.rg.al &= 0x0f;
}

void ins_adc_al_i8(cpu_t cpu) {
    ubit8_t op1 = cpu.rg.al;
    ubit8_t op2 = (ubit8_t)cpu.cur_ins.immediate;

    cpu.rg.al = op1 + op2 + GETBIT(cpu.rg.eflags, CPU_EFLAGS_CF) ? 0x01 : 0x00;

    ALTBIT(cpu.rg.eflags, CPU_EFLAGS_OF,
        ((GETNBIT(op1, 8) != GETNBIT(cpu.rg.al, 8)) && (GETNBIT(op2, 8) != GETNBIT(cpu.rg.al, 8))));
    ALTBIT(cpu.rg.eflags, CPU_EFLAGS_SF, GETNBIT(cpu.rg.al, 8));
    ALTBIT(cpu.rg.eflags, CPU_EFLAGS_ZF, !!!cpu.rg.al);
    ALTBIT(cpu.rg.eflags, CPU_EFLAGS_AF, !!((op1 ^ op2 ^ cpu.rg.eflags) & 0x10));
    ALTBIT(cpu.rg.eflags, CPU_EFLAGS_CF, 
        ((GETBIT(cpu.rg.eflags, CPU_EFLAGS_CF) && op2 == UBIT8_MAX) ? 
            TRUE : ((cpu.rg.al < op1) || (cpu.rg.al < op2))));
    ALTBIT(cpu.rg.eflags, CPU_EFLAGS_PF, calc_pf(UBIT8_MAX, cpu.rg.al));
}

void ins_adc_ax_i16(cpu_t cpu) {
    ubit16_t op1 = cpu.rg.ax;
    ubit16_t op2 = (ubit16_t)cpu.cur_ins.immediate;

    cpu.rg.ax = op1 + op2 + GETBIT(cpu.rg.eflags, CPU_EFLAGS_CF) ? 0x01 : 0x00;

    ALTBIT(cpu.rg.eflags, CPU_EFLAGS_OF,
        ((GETNBIT(op1, 16) != GETNBIT(cpu.rg.ax, 16)) && (GETNBIT(op2, 16) != GETNBIT(cpu.rg.ax, 16))));
    ALTBIT(cpu.rg.eflags, CPU_EFLAGS_SF, GETNBIT(cpu.rg.ax, 16));
    ALTBIT(cpu.rg.eflags, CPU_EFLAGS_ZF, !!!(cpu.rg.ax));
}
