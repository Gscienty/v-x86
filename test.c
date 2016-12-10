#include "device\cpu.h"
#include "device\ins.h"

#include <stdio.h>

ubit8_t memory[256];

int main() {
    cpu_t cpu;
    ram_t ram;
    ram.base = (var_addr)memory;
    ram.size = 32;
    memory[0] = 0x01;
    cpu.is_addr32 = TRUE;
    cpu.rg.eflags = 0x00;
    cpu.rg.ecx = 0x00000000;
    cpu.cur_ins.modrm = 0x01;

    cpu.rg.al = 0x02;
    
    ins_adc_r8_rm8(&cpu, &ram);
    
    printf("%x %x\n", cpu.rg.al, cpu.rg.ah);
    printf("%d", GETBIT(cpu.rg.eflags, CPU_EFLAGS_CF));
}