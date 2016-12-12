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
    cpu.rg.ecx = 0x00000002;//r
    cpu.rg.eax = 0x00000006;//rm
    cpu.cur_ins.modrm = 0xc8;
    
    ins_btc32_r(&cpu, &ram);
    
    
    printf("%x\n", cpu.rg.eax);
    printf("%d", GETBIT(cpu.rg.eflags, CPU_EFLAGS_CF));
}