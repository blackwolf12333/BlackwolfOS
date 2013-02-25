// common.c -- Defines some global functions.
// From JamesM's kernel development tutorials.

#include "common.h"
#include "monitor.h"

// Write a byte out to the specified port.
void outb(u16int port, u8int value)
{
    asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

u8int inb(u16int port)
{
   u8int ret;
   asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}

u16int inw(u16int port)
{
   u16int ret;
   asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}

extern void panic(char *message, char *file, u32int line)
{
    // We encountered a massive problem and have to stop.
    asm volatile("cli"); // Disable interrupts.

    vga.monitor_write("PANIC(");
    vga.monitor_write(message);
    vga.monitor_write(") at ");
    vga.monitor_write(file);
    vga.monitor_write(":");
    vga.monitor_write_dec(line);
    vga.monitor_write("\n");
    // Halt by going into an infinite loop.
    for(;;);
}

extern void panic_assert(char *file, u32int line, char *desc)
{
    // An assertion failed, and we have to panic.
    asm volatile("cli"); // Disable interrupts.

    vga.monitor_write("ASSERTION-FAILED(");
    vga.monitor_write(desc);
    vga.monitor_write(") at ");
    vga.monitor_write(file);
    vga.monitor_write(":");
    vga.monitor_write_dec(line);
    vga.monitor_write("\n");
    // Halt by going into an infinite loop.
    for(;;);
}
