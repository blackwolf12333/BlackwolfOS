// main.c -- Defines the C-code kernel entry point, calls initialisation routines.
#include "monitor.h"
#include "text_gui.h"
#include "descriptor_tables.h"

int main(struct multiboot *mboot_ptr)
{
	// All our initialisation calls will go in here.
	initialize_monitor_vga();
	//initialize_text_gui();

	init_descriptor_tables();
	asm volatile("int $0x3");
	
	return 0xDEADBABA;
}
