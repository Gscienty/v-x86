#include "..\ins.h"

#define I_J(cond, t) if(cond) { \
    cpu->rg.eip += *(t *)&cpu->cur_ins.immediate; \
    if(!cpu->is_operand32) { cpu->rg.eip &= 0x0000ffff; }\
}
#define C_F(f) GETBIT(cpu->rg.eflags, f)
#define F_S CPU_EFLAGS_SF
#define F_O CPU_EFLAGS_OF
#define F_C CPU_EFLAGS_CF
#define F_Z CPU_EFLAGS_ZF

void ins_ja   (cpu_t *cpu) { I_J( !C_F(F_C) && !C_F(F_Z)           , bit8_t) }
void ins_jae  (cpu_t *cpu) { I_J( !C_F(F_C)                        , bit8_t) }
void ins_jb   (cpu_t *cpu) { I_J(  C_F(F_C)                        , bit8_t) }
void ins_jbe  (cpu_t *cpu) { I_J(  C_F(F_C) ||  C_F(F_Z)           , bit8_t) }
void ins_jc   (cpu_t *cpu) { I_J(  C_F(F_C)                        , bit8_t) }
void ins_jcxz (cpu_t *cpu) { I_J(!!cpu->rg.cx                      , bit8_t) }
void ins_jecxz(cpu_t *cpu) { I_J(!!cpu->rg.ecx                     , bit8_t) }
void ins_je   (cpu_t *cpu) { I_J(  C_F(F_Z)                        , bit8_t) }
void ins_jg   (cpu_t *cpu) { I_J( !C_F(F_Z) && C_F(F_S) == C_F(F_O), bit8_t) }
void ins_jge  (cpu_t *cpu) { I_J(  C_F(F_S) == C_F(F_O)            , bit8_t) }
void ins_jl   (cpu_t *cpu) { I_J(  C_F(F_S) != C_F(F_O)            , bit8_t) }
void ins_jle  (cpu_t *cpu) { I_J(  C_F(F_Z) && C_F(F_S) != C_F(F_O), bit8_t) }
void ins_jna  (cpu_t *cpu) { I_J(  C_F(F_C) || C_F(F_Z)            , bit8_t) }
void ins_jnae (cpu_t *cpu) { I_J(  C_F(F_C)                        , bit8_t) }