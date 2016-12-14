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
    cpu.rg.ax = 0x0000;
    cpu.rg.bx = 0x7fff;
    cpu.cur_ins.modrm = 0xc3;
    cpu.cur_ins.immediate = 0x0001;

    (&ins_imul_r_rm16_imm16)(&cpu, &ram);

    printf("%d\n", (bit16_t)cpu.rg.ax);
    printf("%d\n", GETBIT(cpu.rg.eflags, CPU_EFLAGS_OF));
}