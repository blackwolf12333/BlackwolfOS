# Makefile for JamesM's kernel tutorials.
# The C and C++ rules are already setup by default.
# The only one that needs changing is the assembler 
# rule, as we use nasm instead of GNU as.

SOURCES=boot.o main.o common.o monitor.o text_gui.o isr.o descriptor_tables.o gdt.o interrupt.o timer.o keyboard.o kprintf.o arrays.o system.o ../api/linked_list.o kheap.o paging.o memory.o string.o

CFLAGS=-nostdlib -nostdinc -fno-builtin -fno-stack-protector -I../include -I../include/api
LDFLAGS=-Tlink.ld
ASFLAGS=-felf

all: $(SOURCES) link

clean:
	-rm *.o kernel

link:
	ld $(LDFLAGS) -o kernel $(SOURCES)

.s.o:
	nasm $(ASFLAGS) $<
