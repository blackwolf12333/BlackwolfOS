#include "kprintf.h"
#include "monitor.h"
#include "stdarg.h"

void kprintf(const char *format, ...) {
	va_list args;
	va_start(args, format);
	
	int i = 0;
   while (*format) {
		if(*format == '%') {
			if(*(format+1) == '%') {
				format++;
			} else {
				if(*(format+1) == 'd') {
					u32int arg = va_arg(args, int);
					vga.monitor_write_dec(arg);
				} else if(*(format+1) == 's') {
					char *str = va_arg(args, char*);
					vga.monitor_write(str);
				} else if(*(format+1) == 'c') {
					char c = va_arg(args, int);
					vga.monitor_put(c, BLACK, WHITE);
				} //TODO: add other types...
				format+=2;
			}
		} else {
			vga.monitor_put(*format++, BLACK, WHITE);
		}
   }
	
	va_end(args);
}

void va_kprintf(const char *format, va_list args) {
	while (*format) {
		if(*format == '%') {
			if(*(format+1) == '%') {
				format++;
			} else {
				if(*(format+1) == 'd') {
					u32int arg = va_arg(args, int);
					vga.monitor_write_dec(arg);
				} else if(*(format+1) == 's') {
					char *str = va_arg(args, char*);
					vga.monitor_write(str);
				} else if(*(format+1) == 'c') {
					char c = va_arg(args, int);
					vga.monitor_put(c, BLACK, WHITE);
				} //TODO: add other types...
				format+=2;
			}
		} else {
			vga.monitor_put(*format++, BLACK, WHITE);
		}
   }
}
