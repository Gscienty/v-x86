#include "ram.h"

#include <string.h>

void ram_read(ram_t ram, var_addr dst, ubit32_t offset, ubit8_t size) {
    if(offset >= ram.size && offset >= 0xfffe0000) {
        offset &= 0x001fffff;
    }

    memcpy((void*) dst, (void*) RAM_GETADDR(ram, offset), size);
}

void ram_write(ram_t ram, ubit32_t offset, var_addr src, ubit8_t size) {
    if(offset >= ram.size && offset >= 0xfffe0000) {
        offset &= 0x001fffff;
    }

    memcpy((void*) RAM_GETADDR(ram, offset), (void*) src, size);
}