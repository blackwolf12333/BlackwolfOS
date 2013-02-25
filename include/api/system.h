#ifndef API_SYSTEM_H
#define API_SYSTEM_H

#ifndef KPRINTF_H
#include "kprintf.h"
#endif

#define NULL (void*)0

#define new(object, ret) ret = kmalloc_a(object)

typedef struct {
    char stdout;
    void (*printf)(const char *format, ...);
} system;

static inline void printf(const char *format, ...) {
	va_list args;
	va_start(args, format);
	
	va_kprintf(format, args);
	
	va_end(args);
}

#endif
