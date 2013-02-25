// common.h -- Defines typedefs and some global functions.
#ifndef COMMON_H
#define COMMON_H

#include "types.h"

void outb(u16int port, u8int value);
u8int inb(u16int port);
u16int inw(u16int port);

#define PANIC(msg) panic(msg, __FILE__, __LINE__);
#define ASSERT(b) ((b) ? (void)0 : panic_assert(__FILE__, __LINE__, #b))

extern void panic(char *message, char *file, u32int line);
extern void panic_assert(char *file, u32int line, char *desc);

#endif
