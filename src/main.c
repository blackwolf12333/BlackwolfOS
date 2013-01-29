// main.c -- Defines the C-code kernel entry point, calls initialisation routines.
#include "monitor.h"
#include "text_gui.h"
#include "descriptor_tables.h"
#include "timer.h"
#include "keyboard.h"
#include "kprintf.h"

void init_vga_graphics_mode() {
	asm volatile("mov 0013, %ax");
	asm volatile("int $10");
}

int main(struct multiboot *mboot_ptr)
{
	// All our initialisation calls will go in here.
	init_descriptor_tables();

	initialize_monitor_vga();
	vga.monitor_write("Hello World!\n");
	//initialize_text_gui();
	
	asm volatile("sti");
	// initialize the timer
	init_timer(50);
	
	// initialize the keyboard
	//init_keyboard();
	kprintf("%s\n", "Test");
	
	init_vga_graphics_mode();
	
	return 0xDEADBABA;
}
