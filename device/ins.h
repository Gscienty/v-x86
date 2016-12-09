#ifndef _INS_
#define _INS_

typedef ubit8_t modrm_t;

#define MOD_RM_R8  0x01
#define MOD_RM_R16 0x02
#define MOD_RM_R32 0x03

#define MOD_RM_RM8  0x01
#define MOD_RM_RM16 0x02
#define MOD_RM_RM32 0x03

void ins_aaa(cpu_t);
void ins_aad(cpu_t);
void ins_aam(cpu_t);
void ins_aas(cpu_t);
void ins_adc_al_i8(cpu_t);
void ins_adc_ax_i16(cpu_t);
void ins_adc_eax_i32(cpu_t);

#endif