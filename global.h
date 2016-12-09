#ifndef _GLOBAL_
#define _GLOBAL_

typedef unsigned char ubit1_t;
typedef unsigned char ubit4_t;
typedef unsigned char ubit8_t;
typedef unsigned short ubit16_t;
typedef unsigned int ubit32_t;
typedef unsigned long ubit64_t;
typedef signed char bit8_t;
typedef signed short bit16_t;
typedef signed int bit32_t;
typedef signed long bit64_t; 

typedef ubit1_t boolean_t;

#if 1
typedef ubit64_t var_addr;
typedef ubit64_t func_addr;
#endif

#define GET_VARADDR(a) ((var_addr)(&(a)))
#define GET_FUNCADDR(a) ((func_addr)(a))

#define GETBIT(a, b) (!!((a) & (b)))
#define GETNBIT(a, b) (GETBIT((a), (1 << ((b) - 1))))
#define SETBIT(a, b) ((a) |= (b))
#define CLRBIT(a, b) ((a) &= ~(b))
#define ALTBIT(a, b, f) ((f) ? SETBIT((a), (b)) : CLRBIT((a), (b)))

#define TRUE  0x01
#define FALSE 0x00

#define UBIT1_MAX  0x01
#define UBIT4_MAX  0x0f
#define UBIT8_MAX  0xff
#define UBIT16_MAX 0xffff
#define UBIT24_MAX 0x00ffffff
#define UBIT32_MAX 0xffffffff
#define UBIT48_MAX 0x0000ffffffffffff
#define UBIT64_MAX 0xffffffffffffffff

#if 1
#define UBIT_MAX UBIT64_MAX
#define BIT_SIZE 64
#endif

#define FILTER(t, m, n) ((t)(n) & m)

#define EXEC_FUNC(func) ((func_addr) ? ((*(void (*)(void))(func))()) : 0);

#endif