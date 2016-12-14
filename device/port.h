#ifndef _PORT_
#define _PORT
#include "..\global.h"

#define PORT_COUNT 0x10000

typedef struct {
    func_addr  infunc[PORT_COUNT];
    func_addr outfunc[PORT_COUNT];

    union {
        ubit8_t  IObit8;
        ubit16_t IObit16;
        ubit32_t IObit32;
    };
} port_t;

void port_add_read  (port_t *, ubit16_t, func_addr);
void port_add_write (port_t *, ubit16_t, func_addr);
void port_exec_read (port_t *, ubit16_t, void *);
void port_exec_write(port_t *, ubit16_t, void *);
#endif