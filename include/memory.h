#ifndef MEMORY_H
#define MEMORY_H

#include "types.h"

void memcpy(void *dest, const u8int *src, u32int len);
void memset(void *dest, u8int val, u32int len);

#endif
