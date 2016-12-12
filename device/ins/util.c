#include "..\ins.h"

var_addr modrm_reg_addr(cpu_t *cpu, modrm_t regt) {
    switch(regt) {
        case MOD_RM_R8:
            switch(FILTER(ubit8_t, cpu->cur_ins.modrm, 0x38)) {
                case 0x00 : return VARADDR(cpu->rg.al);
                case 0x08 : return VARADDR(cpu->rg.cl);
                case 0x10 : return VARADDR(cpu->rg.dl);
                case 0x18 : return VARADDR(cpu->rg.bl);
                case 0x20 : return VARADDR(cpu->rg.ah);
                case 0x28 : return VARADDR(cpu->rg.ch);
                case 0x30 : return VARADDR(cpu->rg.dh);
                case 0x38 : return VARADDR(cpu->rg.bh); 
            }
        case MOD_RM_R16:
            switch(FILTER(ubit8_t, cpu->cur_ins.modrm, 0x38)) {
                case 0x00 : return VARADDR(cpu->rg.ax);
                case 0x08 : return VARADDR(cpu->rg.cx);
                case 0x10 : return VARADDR(cpu->rg.dx);
                case 0x18 : return VARADDR(cpu->rg.bx);
                case 0x20 : return VARADDR(cpu->rg.sp);
                case 0x28 : return VARADDR(cpu->rg.bp);
                case 0x30 : return VARADDR(cpu->rg.si);
                case 0x38 : return VARADDR(cpu->rg.di);
            }
        case MOD_RM_R32:
            switch(FILTER(ubit8_t, cpu->cur_ins.modrm, 0x38)) {
                case 0x00 : return VARADDR(cpu->rg.eax);
                case 0x08 : return VARADDR(cpu->rg.ecx);
                case 0x10 : return VARADDR(cpu->rg.edi);
                case 0x18 : return VARADDR(cpu->rg.ebx);
                case 0x20 : return VARADDR(cpu->rg.esp);
                case 0x28 : return VARADDR(cpu->rg.ebp);
                case 0x30 : return VARADDR(cpu->rg.esi);
                case 0x38 : return VARADDR(cpu->rg.edi);
            }
    }
}


var_addr modrm_rm_addr16(cpu_t *cpu, ram_t *ram, modrm_t regt) {
    switch(FILTER(ubit8_t, cpu->cur_ins.modrm, 0xc7)) {
        case 0x00 : return RAM_GETADDR((*ram), cpu->rg.bx + cpu->rg.si);
        case 0x01 : return RAM_GETADDR((*ram), cpu->rg.bx + cpu->rg.di);
        case 0x02 : return RAM_GETADDR((*ram), cpu->rg.bp + cpu->rg.si);
        case 0x03 : return RAM_GETADDR((*ram), cpu->rg.bp + cpu->rg.di);
        case 0x04 : return RAM_GETADDR((*ram), cpu->rg.si);
        case 0x05 : return RAM_GETADDR((*ram), cpu->rg.di);
        case 0x06 : return RAM_GETADDR((*ram), FILTER(ubit16_t, cpu->cur_ins.displacement, UBIT16_MAX));
        case 0x07 : return RAM_GETADDR((*ram), cpu->rg.bx);

        case 0x40 : return RAM_GETADDR((*ram), cpu->rg.bx + cpu->rg.si + FILTER(ubit8_t, cpu->cur_ins.displacement, UBIT8_MAX));
        case 0x41 : return RAM_GETADDR((*ram), cpu->rg.bx + cpu->rg.di + FILTER(ubit8_t, cpu->cur_ins.displacement, UBIT8_MAX));
        case 0x42 : return RAM_GETADDR((*ram), cpu->rg.bp + cpu->rg.si + FILTER(ubit8_t, cpu->cur_ins.displacement, UBIT8_MAX));
        case 0x43 : return RAM_GETADDR((*ram), cpu->rg.bp + cpu->rg.di + FILTER(ubit8_t, cpu->cur_ins.displacement, UBIT8_MAX));
        case 0x44 : return RAM_GETADDR((*ram), cpu->rg.si + FILTER(ubit8_t, cpu->cur_ins.displacement, UBIT8_MAX));
        case 0x45 : return RAM_GETADDR((*ram), cpu->rg.di + FILTER(ubit8_t, cpu->cur_ins.displacement, UBIT8_MAX));
        case 0x46 : return RAM_GETADDR((*ram), cpu->rg.bp + FILTER(ubit8_t, cpu->cur_ins.displacement, UBIT8_MAX));
        case 0x47 : return RAM_GETADDR((*ram), cpu->rg.bx + FILTER(ubit8_t, cpu->cur_ins.displacement, UBIT8_MAX));

        case 0x80 : return RAM_GETADDR((*ram), cpu->rg.bx + cpu->rg.si + FILTER(ubit16_t, cpu->cur_ins.displacement, UBIT16_MAX));
        case 0x81 : return RAM_GETADDR((*ram), cpu->rg.bx + cpu->rg.di + FILTER(ubit16_t, cpu->cur_ins.displacement, UBIT16_MAX));
        case 0x82 : return RAM_GETADDR((*ram), cpu->rg.bp + cpu->rg.si + FILTER(ubit16_t, cpu->cur_ins.displacement, UBIT16_MAX));
        case 0x83 : return RAM_GETADDR((*ram), cpu->rg.bp + cpu->rg.di + FILTER(ubit16_t, cpu->cur_ins.displacement, UBIT16_MAX));
        case 0x84 : return RAM_GETADDR((*ram), cpu->rg.si + FILTER(ubit16_t, cpu->cur_ins.displacement, UBIT16_MAX));
        case 0x85 : return RAM_GETADDR((*ram), cpu->rg.di + FILTER(ubit16_t, cpu->cur_ins.displacement, UBIT16_MAX));
        case 0x86 : return RAM_GETADDR((*ram), cpu->rg.bp + FILTER(ubit16_t, cpu->cur_ins.displacement, UBIT16_MAX));
        case 0x87 : return RAM_GETADDR((*ram), cpu->rg.bx + FILTER(ubit16_t, cpu->cur_ins.displacement, UBIT16_MAX));

        case 0xc0: switch(regt) {
                case MOD_RM_RM8  : return VARADDR(cpu->rg.al);
                case MOD_RM_RM16 : return VARADDR(cpu->rg.ax);
                case MOD_RM_RM32 : return VARADDR(cpu->rg.eax);
            }
        case 0xc1: switch(regt) {
                case MOD_RM_RM8  : return VARADDR(cpu->rg.cl);
                case MOD_RM_RM16 : return VARADDR(cpu->rg.cx);
                case MOD_RM_RM32 : return VARADDR(cpu->rg.ecx);
            }
        case 0xc2: switch(regt) {
                case MOD_RM_RM8  : return VARADDR(cpu->rg.dl);
                case MOD_RM_RM16 : return VARADDR(cpu->rg.dx);
                case MOD_RM_RM32 : return VARADDR(cpu->rg.edx);
            }
        case 0xc3: switch(regt) {
                case MOD_RM_RM8  : return VARADDR(cpu->rg.bl);
                case MOD_RM_RM16 : return VARADDR(cpu->rg.bx);
                case MOD_RM_RM32 : return VARADDR(cpu->rg.ebx);
            }
        case 0xc4: switch(regt) {
                case MOD_RM_RM8  : return VARADDR(cpu->rg.ah);
                case MOD_RM_RM16 : return VARADDR(cpu->rg.sp);
                case MOD_RM_RM32 : return VARADDR(cpu->rg.esp);
            }
        case 0xc5: switch(regt) {
                case MOD_RM_RM8  : return VARADDR(cpu->rg.ch);
                case MOD_RM_RM16 : return VARADDR(cpu->rg.bp);
                case MOD_RM_RM32 : return VARADDR(cpu->rg.ebp);
            }
        case 0xc6: switch(regt) {
                case MOD_RM_RM8  : return VARADDR(cpu->rg.dh);
                case MOD_RM_RM16 : return VARADDR(cpu->rg.si);
                case MOD_RM_RM32 : return VARADDR(cpu->rg.esi);
            }
        case 0xc7: switch(regt) {
                case MOD_RM_RM8  : return VARADDR(cpu->rg.bh);
                case MOD_RM_RM16 : return VARADDR(cpu->rg.di);
                case MOD_RM_RM32 : return VARADDR(cpu->rg.edi);
            }
    }
}

#define SIB_LAZY(R) switch(FILTER(ubit8_t, cpu->cur_ins.sib, 0x38)) {\
    case 0x00 : return RAM_GETADDR((*ram), R + (cpu->rg.eax << (FILTER(ubit8_t, cpu->cur_ins.sib, 0xc0) >> 6)));\
    case 0x08 : return RAM_GETADDR((*ram), R + (cpu->rg.ecx << (FILTER(ubit8_t, cpu->cur_ins.sib, 0xc0) >> 6)));\
    case 0x10 : return RAM_GETADDR((*ram), R + (cpu->rg.edx << (FILTER(ubit8_t, cpu->cur_ins.sib, 0xc0) >> 6)));\
    case 0x18 : return RAM_GETADDR((*ram), R + (cpu->rg.ebx << (FILTER(ubit8_t, cpu->cur_ins.sib, 0xc0) >> 6)));\
    case 0x20 : return RAM_GETADDR((*ram), R);\
    case 0x28 : return RAM_GETADDR((*ram), R + (cpu->rg.ebp << (FILTER(ubit8_t, cpu->cur_ins.sib, 0xc0) >> 6)));\
    case 0x30 : return RAM_GETADDR((*ram), R + (cpu->rg.esi << (FILTER(ubit8_t, cpu->cur_ins.sib, 0xc0) >> 6)));\
    case 0x38 : return RAM_GETADDR((*ram), R + (cpu->rg.edi << (FILTER(ubit8_t, cpu->cur_ins.sib, 0xc0) >> 6)));\
}

var_addr sib_addr(cpu_t *cpu, ram_t *ram, ubit32_t offset) {
    switch(FILTER(ubit8_t, cpu->cur_ins.sib, 0x07)) {
        case 0x00 : SIB_LAZY(cpu->rg.eax + offset)
        case 0x01 : SIB_LAZY(cpu->rg.ecx + offset)
        case 0x02 : SIB_LAZY(cpu->rg.edx + offset)
        case 0x03 : SIB_LAZY(cpu->rg.ebx + offset)
        case 0x04 : SIB_LAZY(cpu->rg.esp + offset)
        case 0x05 : SIB_LAZY(((GETBIT(FILTER(ubit8_t, cpu->cur_ins.modrm, 0xc0), UBIT8_MAX)) ? cpu->rg.ebp : 0x00000000) + offset)
        case 0x06 : SIB_LAZY(cpu->rg.esi + offset)
        case 0x07 : SIB_LAZY(cpu->rg.edi + offset)
    }
}

var_addr modrm_rm_addr32(cpu_t *cpu, ram_t *ram, modrm_t regt) {
    switch(FILTER(ubit8_t, cpu->cur_ins.modrm, 0xc7)) {
        case 0x00 : return RAM_GETADDR((*ram), cpu->rg.eax);
        case 0x01 : return RAM_GETADDR((*ram), cpu->rg.ecx);
        case 0x02 : return RAM_GETADDR((*ram), cpu->rg.edx);
        case 0x03 : return RAM_GETADDR((*ram), cpu->rg.ebx);
        case 0x04 : return sib_addr(cpu, ram, 0x00000000);
        case 0x05 : return RAM_GETADDR((*ram), FILTER(ubit32_t, cpu->cur_ins.displacement, UBIT32_MAX));
        case 0x06 : return RAM_GETADDR((*ram), cpu->rg.esi);
        case 0x07 : return RAM_GETADDR((*ram), cpu->rg.edi);

        case 0x40 : return RAM_GETADDR((*ram), cpu->rg.eax + FILTER(ubit8_t, cpu->cur_ins.displacement, UBIT8_MAX));
        case 0x41 : return RAM_GETADDR((*ram), cpu->rg.ecx + FILTER(ubit8_t, cpu->cur_ins.displacement, UBIT8_MAX));
        case 0x42 : return RAM_GETADDR((*ram), cpu->rg.edx + FILTER(ubit8_t, cpu->cur_ins.displacement, UBIT8_MAX));
        case 0x43 : return RAM_GETADDR((*ram), cpu->rg.ebx + FILTER(ubit8_t, cpu->cur_ins.displacement, UBIT8_MAX));
        case 0x44 : return sib_addr(cpu, ram, FILTER(ubit8_t, cpu->cur_ins.displacement, UBIT8_MAX));
        case 0x45 : return RAM_GETADDR((*ram), cpu->rg.ebp + FILTER(ubit8_t, cpu->cur_ins.displacement, UBIT8_MAX));
        case 0x46 : return RAM_GETADDR((*ram), cpu->rg.esi + FILTER(ubit8_t, cpu->cur_ins.displacement, UBIT8_MAX));
        case 0x47 : return RAM_GETADDR((*ram), cpu->rg.edi + FILTER(ubit8_t, cpu->cur_ins.displacement, UBIT8_MAX));

        case 0x80 : return RAM_GETADDR((*ram), cpu->rg.eax + FILTER(ubit32_t, cpu->cur_ins.displacement, UBIT32_MAX));
        case 0x81 : return RAM_GETADDR((*ram), cpu->rg.ecx + FILTER(ubit32_t, cpu->cur_ins.displacement, UBIT32_MAX));
        case 0x82 : return RAM_GETADDR((*ram), cpu->rg.edx + FILTER(ubit32_t, cpu->cur_ins.displacement, UBIT32_MAX));
        case 0x83 : return RAM_GETADDR((*ram), cpu->rg.ebx + FILTER(ubit32_t, cpu->cur_ins.displacement, UBIT32_MAX));
        case 0x84 : return sib_addr(cpu, ram, FILTER(ubit32_t, cpu->cur_ins.displacement, UBIT32_MAX));
        case 0x85 : return RAM_GETADDR((*ram), cpu->rg.ebp + FILTER(ubit32_t, cpu->cur_ins.displacement, UBIT32_MAX));
        case 0x86 : return RAM_GETADDR((*ram), cpu->rg.esi + FILTER(ubit32_t, cpu->cur_ins.displacement, UBIT32_MAX));
        case 0x87 : return RAM_GETADDR((*ram), cpu->rg.edi + FILTER(ubit32_t, cpu->cur_ins.displacement, UBIT32_MAX));

        case 0xc0: switch(regt) {
                case MOD_RM_RM8  : return VARADDR(cpu->rg.al);
                case MOD_RM_RM16 : return VARADDR(cpu->rg.ax);
                case MOD_RM_RM32 : return VARADDR(cpu->rg.eax);
            }
        case 0xc1: switch(regt) {
                case MOD_RM_RM8  : return VARADDR(cpu->rg.cl);
                case MOD_RM_RM16 : return VARADDR(cpu->rg.cx);
                case MOD_RM_RM32 : return VARADDR(cpu->rg.ecx);
            }
        case 0xc2: switch(regt) {
                case MOD_RM_RM8  : return VARADDR(cpu->rg.dl);
                case MOD_RM_RM16 : return VARADDR(cpu->rg.dx);
                case MOD_RM_RM32 : return VARADDR(cpu->rg.edx);
            }
        case 0xc3: switch(regt) {
                case MOD_RM_RM8  : return VARADDR(cpu->rg.bl);
                case MOD_RM_RM16 : return VARADDR(cpu->rg.bx);
                case MOD_RM_RM32 : return VARADDR(cpu->rg.ebx);
            }
        case 0xc4: switch(regt) {
                case MOD_RM_RM8  : return VARADDR(cpu->rg.ah);
                case MOD_RM_RM16 : return VARADDR(cpu->rg.sp);
                case MOD_RM_RM32 : return VARADDR(cpu->rg.esp);
            }
        case 0xc5: switch(regt) {
                case MOD_RM_RM8  : return VARADDR(cpu->rg.ch);
                case MOD_RM_RM16 : return VARADDR(cpu->rg.bp);
                case MOD_RM_RM32 : return VARADDR(cpu->rg.ebp);
            }
        case 0xc6: switch(regt) {
                case MOD_RM_RM8  : return VARADDR(cpu->rg.dh);
                case MOD_RM_RM16 : return VARADDR(cpu->rg.si);
                case MOD_RM_RM32 : return VARADDR(cpu->rg.esi);
            }
        case 0xc7: switch(regt) {
                case MOD_RM_RM8  : return VARADDR(cpu->rg.bh);
                case MOD_RM_RM16 : return VARADDR(cpu->rg.di);
                case MOD_RM_RM32 : return VARADDR(cpu->rg.edi);
            }
    }
}

boolean_t calc_pf(ubit64_t mask, ubit64_t n) {
    boolean_t result = TRUE;
    ubit64_t bit_ptr = 1;
    while(mask & bit_ptr) {
        result ^= GETBIT(n, bit_ptr);
        bit_ptr <<= 1;
    }
    return result;
}