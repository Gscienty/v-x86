#include "port.h"

void port_add_read  (port_t *port, ubit16_t offset, func_addr in_func ) { port->infunc[offset]  = in_func;  }
void port_add_write (port_t *port, ubit16_t offset, func_addr out_func) { port->outfunc[offset] = out_func; }
void port_exec_read (port_t *port, ubit16_t offset, void *params) { 
    ((void (*)(port_t *, void *))(port->infunc[offset]))(port, params);
}
void port_exec_write(port_t *port, ubit16_t offset, void *params) {
    ((void (*)(port_t *, void *))(port->outfunc[offset]))(port, params);
}
