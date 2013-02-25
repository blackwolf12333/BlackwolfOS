#ifndef KPRINTF_H
#define KPRINTF_H

#include "stdarg.h"

void kprintf(const char *format, ...);
void va_kprintf(const char *format, va_list args);

#endif
