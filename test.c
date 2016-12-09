#include "device\cpu.h"
#include "device\ins.h"

#include <stdio.h>

int main() {
    printf("%x", FILTER(ubit8_t, 0x00, 0x38));
    return 0;
}