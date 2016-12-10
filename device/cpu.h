#ifndef _CPU_
#define _CPU_

#include "..\global.h"

typedef ubit8_t ins_prefix_t;
typedef ubit8_t ins_opcode_t;
typedef ubit8_t ins_modrm_t;
typedef ubit8_t ins_sib_t;
typedef ubit32_t ins_displacement_t;
typedef ubit32_t ins_immediate_t;

#define INS_PREFIX_LOCK  0xf0
#define INS_PREFIX_REPNE 0xf2
#define INS_PREFIX_REP   0xf3
#define INS_PREFIX_REPE  0xf3

#define INS_PREFIX_SEG_CS 0x2e
#define INS_PREFIX_SEG_SS 0x36
#define INS_PREFIX_SEG_DS 0x3e
#define INS_PREFIX_SEG_ES 0x26
#define INS_PREFIX_SEG_FS 0x64
#define INS_PREFIX_SEG_GS 0x65

#define INS_PREFIX_OPSIZE 0x66

#define INS_PREFIX_ADDRSIZE 0x67


#define CPU_EFLAGS_CF      0x00000001
#define CPU_EFLAGS_PF      0x00000004
#define CPU_EFLAGS_AF      0x00000010
#define CPU_EFLAGS_ZF      0x00000040
#define CPU_EFLAGS_SF      0x00000080
#define CPU_EFLAGS_TF      0x00000100
#define CPU_EFLAGS_IF      0x00000200
#define CPU_EFLAGS_DF      0x00000400
#define CPU_EFLAGS_OF      0x00000800
#define CPU_EFLAGS_IOPLL   0x00001000
#define CPU_EFLAGS_IOPLH   0x00002000
#define CPU_EFLAGS_IOPL    0x00003000
#define CPU_EFLAGS_NT      0x00004000
#define CPU_EFLAGS_RF      0x00010000
#define CPU_EFLAGS_VM      0x00020000
#define CPU_EFLAGS_RESEVED 0xfffc802a


#define INS_EXCEPT_DE 0x00000000
#define INS_EXCEPT_DB 0x00000001
#define INS_EXCEPT_BP 0x00000002
#define INS_EXCEPT_OF 0x00000004
#define INS_EXCEPT_BR 0x00000008
#define INS_EXCEPT_UD 0x00000010
#define INS_EXCEPT_NM 0x00000020
#define INS_EXCEPT_DF 0x00000040
#define INS_EXCEPT_TS 0x00000080
#define INS_EXCEPT_NP 0x00000100
#define INS_EXCEPT_SS 0x00000200
#define INS_EXCEPT_GP 0x00000400
#define INS_EXCEPT_PF 0x00000800
#define INS_EXCEPT_MF 0x00001000
#define INS_EXCEPT_AC 0x00002000
#define INS_EXCEPT_MC 0x00004000

typedef struct {
    ins_prefix_t prefix;
    ins_opcode_t opcode[2];
    ins_modrm_t modrm;
    ins_sib_t sib;
    ins_displacement_t displacement;
    ins_immediate_t immediate;
} ins_format_t;

typedef struct {
    ubit16_t selector;

    ubit32_t base;
    ubit32_t limit;
    
    union {
        ubit4_t dpl;
        ubit4_t cpl;
    };

    union {
        struct {
            boolean_t accessable;
            boolean_t executable;
            union {
                struct {
                    boolean_t size32;
                    boolean_t conform;
                    boolean_t readable;
                } code;
                struct {
                    boolean_t size32;
                    boolean_t expdown;
                    boolean_t writeable;
                } data;
            };
        } seg;
        struct {
            ubit4_t type;
        } sys;
    };
} cpu_sreg_t;


typedef struct {
    union {
        union { struct { ubit8_t al; ubit8_t ah; }; ubit16_t ax; };
        ubit32_t eax;
    };

    union {
        union { struct { ubit8_t bl; ubit8_t bh; }; ubit16_t bx; };
        ubit32_t ebx;
    };

    union {
        union { struct { ubit8_t cl; ubit8_t ch; }; ubit16_t cx; };
        ubit32_t ecx;
    };

    union {
        union { struct { ubit8_t dl; ubit8_t dh; }; ubit16_t dx; };
        ubit32_t edx;
    };

    union {
        ubit16_t sp;
        ubit32_t esp;
    };

    union {
        ubit16_t bp;
        ubit32_t ebp;
    };

    union {
        ubit16_t si;
        ubit32_t esi;
    };

    union {
        ubit16_t di;
        ubit32_t edi;
    };
    
    union {
        ubit16_t ip;
        ubit32_t eip;
    };

    union {
        ubit16_t flags;
        ubit32_t eflags;
    };

    cpu_sreg_t cs, ss, es, ds, fs, gs;
    cpu_sreg_t gdtr, idtr, ldtr, tr;
} cpu_rg_t;

typedef struct {
    cpu_rg_t rg;
    ins_format_t cur_ins;
    boolean_t is_addr32;
} cpu_t;

extern struct {
    func_addr ins_map[0x100];
} ins_op;

void init_ins_op();

#endif