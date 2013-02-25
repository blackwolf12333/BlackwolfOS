// main.c -- Defines the C-code kernel entry point, calls initialisation routines.
#include "monitor.h"
#include "text_gui.h"
#include "descriptor_tables.h"
#include "timer.h"
#include "keyboard.h"
#include "kprintf.h"
#include "api/linked_list.h"
#include "api/system.h"
#include "stdarg.h"
#include "kheap.h"
#include "paging.h"

list_node liststart;

int main(struct multiboot *mboot_ptr) {
	// All our initialisation calls will go in here.
	init_descriptor_tables();

	initialize_monitor_vga();
	vga.monitor_write("Hello World!\n");
	//initialize_text_gui();
	
	asm volatile("sti");
	// initialize the timer
	init_timer(50);
	
	initialise_paging();
    vga.monitor_write("Hello, paging world!\n");

	return 0xDEADBABA;
}
