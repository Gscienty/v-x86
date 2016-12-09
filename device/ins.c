#include "cpu.h"
#include "ins.h"
#include "ram.h"

boolean_t calc_pf(ubit64_t mask, ubit64_t n) {
    boolean_t result = TRUE;
    ubit64_t bit_ptr = 1;
    while(mask & bit_ptr) {
        result ^= !!(n & bit_ptr);
        bit_ptr <<= 1;
    }
    return result;
}

var_addr modrm_reg_addr(cpu_t cpu, modrm_t regt) {
    switch(regt) {
        case MOD_RM_R8:
            switch(FILTER(ubit8_t, cpu.cur_ins.modrm, 0x38)) {
                case 0x00 : return VARADDR(cpu.rg.al);
                case 0x08 : return VARADDR(cpu.rg.cl);
                case 0x10 : return VARADDR(cpu.rg.dl);
                case 0x18 : return VARADDR(cpu.rg.bl);
                case 0x20 : return VARADDR(cpu.rg.ah);
                case 0x28 : return VARADDR(cpu.rg.ch);
                case 0x30 : return VARADDR(cpu.rg.dh);
                case 0x38 : return VARADDR(cpu.rg.bh); 
            }
        case MOD_RM_R16:
            switch(FILTER(ubit8_t, cpu.cur_ins.modrm, 0x38)) {
                case 0x00 : return VARADDR(cpu.rg.ax);
                case 0x08 : return VARADDR(cpu.rg.cx);
                case 0x10 : return VARADDR(cpu.rg.dx);
                case 0x18 : return VARADDR(cpu.rg.bx);
                case 0x20 : return VARADDR(cpu.rg.sp);
                case 0x28 : return VARADDR(cpu.rg.bp);
                case 0x30 : return VARADDR(cpu.rg.si);
                case 0x38 : return VARADDR(cpu.rg.di);
            }
        case MOD_RM_R32:
            switch(FILTER(ubit8_t, cpu.cur_ins.modrm, 0x38)) {
                case 0x00 : return VARADDR(cpu.rg.eax);
                case 0x08 : return VARADDR(cpu.rg.ecx);
                case 0x10 : return VARADDR(cpu.rg.edi);
                case 0x18 : return VARADDR(cpu.rg.ebx);
                case 0x20 : return VARADDR(cpu.rg.esp);
                case 0x28 : return VARADDR(cpu.rg.ebp);
                case 0x30 : return VARADDR(cpu.rg.esi);
                case 0x38 : return VARADDR(cpu.rg.edi);
            }
    }
}


var_addr modrm_rm_addr16(cpu_t cpu, ram_t ram, modrm_t regt) {
    switch(FILTER(ubit8_t, cpu.cur_ins.modrm, 0xc7)) {
        case 0x00:
            switch(FILTER(ubit8_t, cpu.cur_ins.modrm, 0x07)) {
                case 0x00 : return (var_addr)RAM_GETADDR(ram, cpu.rg.bx + cpu.rg.si);
                case 0x01 : return (var_addr)RAM_GETADDR(ram, cpu.rg.bx + cpu.rg.di);
                case 0x02 : return (var_addr)RAM_GETADDR(ram, cpu.rg.bp + cpu.rg.si);
                case 0x03 : return (var_addr)RAM_GETADDR(ram, cpu.rg.bp + cpu.rg.di);
                case 0x04 : return (var_addr)RAM_GETADDR(ram, cpu.rg.si);
                case 0x05 : return (var_addr)RAM_GETADDR(ram, cpu.rg.di);
                case 0x06 : return VARADDR(cpu.cur_ins.displacement);
                case 0x07 : return (var_addr)RAM_GETADDR(ram, cpu.rg.bx);
            }
        case 0xc0:
            switch(regt) {
                case MOD_RM_RM8  : return VARADDR(cpu.rg.al);
                case MOD_RM_RM16 : return VARADDR(cpu.rg.ax);
                case MOD_RM_RM32 : return VARADDR(cpu.rg.eax);
            }
        case 0xc1:
            switch(regt) {
                case MOD_RM_RM8  : return VARADDR(cpu.rg.cl);
                case MOD_RM_RM16 : return VARADDR(cpu.rg.cx);
                case MOD_RM_RM32 : return VARADDR(cpu.rg.ecx);
            }
        case 0xc2:
            switch(regt) {
                case MOD_RM_RM8  : return VARADDR(cpu.rg.dl);
                case MOD_RM_RM16 : return VARADDR(cpu.rg.dx);
                case MOD_RM_RM32 : return VARADDR(cpu.rg.edx);
            }
        case 0xc3:
            switch(regt) {
                case MOD_RM_RM8  : return VARADDR(cpu.rg.bl);
                case MOD_RM_RM16 : return VARADDR(cpu.rg.bx);
                case MOD_RM_RM32 : return VARADDR(cpu.rg.ebx);
            }
        case 0xc4:
            switch(regt) {
                case MOD_RM_RM8  : return VARADDR(cpu.rg.ah);
                case MOD_RM_RM16 : return VARADDR(cpu.rg.sp);
                case MOD_RM_RM32 : return VARADDR(cpu.rg.esp);
            }
        case 0xc5:
            switch(regt) {
                case MOD_RM_RM8  : return VARADDR(cpu.rg.ch);
                case MOD_RM_RM16 : return VARADDR(cpu.rg.bp);
                case MOD_RM_RM32 : return VARADDR(cpu.rg.ebp);
            }
        case 0xc6:
            switch(regt) {
                case MOD_RM_RM8  : return VARADDR(cpu.rg.dh);
                case MOD_RM_RM16 : return VARADDR(cpu.rg.si);
                case MOD_RM_RM32 : return VARADDR(cpu.rg.esi);
            }
        case 0xc7:
            switch(regt) {
                case MOD_RM_RM8  : return VARADDR(cpu.rg.bh);
                case MOD_RM_RM16 : return VARADDR(cpu.rg.di);
                case MOD_RM_RM32 : return VARADDR(cpu.rg.edi);
            }
    }
}

var_addr modrm_rm_addr32(cpu_t cpu, modrm_t regt) {
    switch(FILTER(ubit8_t, cpu.cur_ins.modrm, 0xc7)) {
        case 0xc0: 
            switch(regt) {
                case MOD_RM_RM8  : return VARADDR(cpu.rg.al);
                case MOD_RM_RM16 : return VARADDR(cpu.rg.ax);
                case MOD_RM_RM32 : return VARADDR(cpu.rg.eax);
            }
        case 0xc1:
            switch(regt) {
                case MOD_RM_RM8  : return VARADDR(cpu.rg.cl);
                case MOD_RM_RM16 : return VARADDR(cpu.rg.cx);
                case MOD_RM_RM32 : return VARADDR(cpu.rg.ecx);
            }
        case 0xc2:
            switch(regt) {
                case MOD_RM_RM8  : return VARADDR(cpu.rg.dl);
                case MOD_RM_RM16 : return VARADDR(cpu.rg.dx);
                case MOD_RM_RM32 : return VARADDR(cpu.rg.edx);
            }
        case 0xc3:
            switch(regt) {
                case MOD_RM_RM8  : return VARADDR(cpu.rg.bl);
                case MOD_RM_RM16 : return VARADDR(cpu.rg.bx);
                case MOD_RM_RM32 : return VARADDR(cpu.rg.ebx);
            }
        case 0xc4:
            switch(regt) {
                case MOD_RM_RM8  : return VARADDR(cpu.rg.ah);
                case MOD_RM_RM16 : return VARADDR(cpu.rg.sp);
                case MOD_RM_RM32 : return VARADDR(cpu.rg.esp);
            }
        case 0xc5:
            switch(regt) {
                case MOD_RM_RM8  : return VARADDR(cpu.rg.ch);
                case MOD_RM_RM16 : return VARADDR(cpu.rg.bp);
                case MOD_RM_RM32 : return VARADDR(cpu.rg.ebp);
            }
        case 0xc6:
            switch(regt) {
                case MOD_RM_RM8  : return VARADDR(cpu.rg.dh);
                case MOD_RM_RM16 : return VARADDR(cpu.rg.si);
                case MOD_RM_RM32 : return VARADDR(cpu.rg.esi);
            }
        case 0xc7:
            switch(regt) {
                case MOD_RM_RM8  : return VARADDR(cpu.rg.bh);
                case MOD_RM_RM16 : return VARADDR(cpu.rg.di);
                case MOD_RM_RM32 : return VARADDR(cpu.rg.edi);
            }
    }
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
    ALTBIT(cpu.rg.eflags, CPU_EFLAGS_AF, !!((op1 ^ op2 ^ cpu.rg.al) & 0x10));
    ALTBIT(cpu.rg.eflags, CPU_EFLAGS_CF, 
        ((GETBIT(cpu.rg.eflags, CPU_EFLAGS_CF) && op2 == UBIT8_MAX) ? 
            TRUE : (cpu.rg.al < op1 || cpu.rg.al < op2)));
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
    ALTBIT(cpu.rg.eflags, CPU_EFLAGS_AF, !!((op1 ^ op2 ^ cpu.rg.ax) & 0x10));
    ALTBIT(cpu.rg.eflags, CPU_EFLAGS_CF,
        ((GETBIT(cpu.rg.eflags, CPU_EFLAGS_CF) && op2 == UBIT16_MAX) ?
            TRUE : (cpu.rg.ax < op1 || cpu.rg.ax < op2)));
    ALTBIT(cpu.rg.eflags, CPU_EFLAGS_PF, calc_pf(UBIT16_MAX, cpu.rg.ax));
}

void ins_adc_eax_i32(cpu_t cpu) {
    ubit32_t op1 = cpu.rg.eax;
    ubit32_t op2 = (ubit32_t)cpu.cur_ins.immediate;

    cpu.rg.eax = op1 + op2 + GETBIT(cpu.rg.eflags, CPU_EFLAGS_CF) ? 0x01 : 0x00;

    ALTBIT(cpu.rg.eflags, CPU_EFLAGS_OF,
        ((GETNBIT(op1, 32) != GETNBIT(cpu.rg.eax, 32)) && (GETNBIT(op2, 32) != GETNBIT(cpu.rg.eax, 32))));
    ALTBIT(cpu.rg.eflags, CPU_EFLAGS_SF, GETNBIT(cpu.rg.eax, 32));
    ALTBIT(cpu.rg.eflags, CPU_EFLAGS_ZF, !!!(cpu.rg.eax));
    ALTBIT(cpu.rg.eflags, CPU_EFLAGS_AF, !!((op1 ^ op2 ^ cpu.rg.eax) & 0x10));
    ALTBIT(cpu.rg.eflags, CPU_EFLAGS_CF, 
        ((GETBIT(cpu.rg.eflags, CPU_EFLAGS_CF) && op2 == UBIT32_MAX) ?
            TRUE : (cpu.rg.eax < op1 || cpu.rg.eax < op2)));
    ALTBIT(cpu.rg.eflags, CPU_EFLAGS_PF, calc_pf(UBIT32_MAX, cpu.rg.eax));
}
