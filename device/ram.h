#ifndef _RAM_
#define _RAM_

#include "../global.h"

typedef struct {
    var_addr base;
    ubitm_t size;

    boolean_t flag;
} ram_t;

#define RAM_WARP(r, offset) FILTER(ubit32_t, offset, (r.flag ? UBIT32_MAX : 0xffefffff))
#define RAM_GETADDR(r, offset) ((var_addr)(r.base + RAM_WARP(r, offset)))

#define RAM_SEG_GETADDR(r, seg, offset) (r.base + (RAM_WARP(r, FILTER(ubit16_t, seg, UBIT16_MAX) << 4) + FILTER(ubit16_t, offset, UBIT16_MAX)) % r.size)

#define RAM_SEG_GETUBIT8(r, seg, offset)  (*((ubit8_t *)RAM_SEG_GETADDR(r, seg, offset)))
#define RAM_SEG_GETUBIT16(r, seg, offset) (*((ubit8_t *)RAM_SEG_GETADDR(r, seg, offset)))
#define RAM_SEG_GETUBIT32(r, seg, offset) (*((ubit8_t *)RAM_SEG_GETADDR(r, seg, offset)))

#define RAM_GETUBIT8(r, offset)  (*((ubit8_t *)RAM_GETADDR(r, offset)))
#define RAM_GETUBIT16(r, offset) (*((ubit16_t *)RAM_GETADDR(r, offset)))
#define RAM_GETUBIT32(r, offset) (*((ubit32_t *)RAM_GETADDR(r, offset)))

void ram_read(ram_t, var_addr, ubit32_t, ubit8_t);
void ram_write(ram_t, ubit32_t, var_addr, ubit8_t);



#endif