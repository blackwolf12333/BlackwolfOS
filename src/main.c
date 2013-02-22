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

int createlist(char *lnode, ...);
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
	
	// initialize the keyboard
	//init_keyboard();
	int length = createlist("test", "apple", "lolgek", NULL);
	kprintf("%d\n", length);
	list_node *ptr = &liststart;
	while(ptr) {
		kprintf("%s ", ptr->data);
		ptr = ptr->next;
	}
	
	return 0xDEADBABA;
}

int createlist(char *lnode, ...) {
	int i = 1;
	va_list args;
	va_start(args, lnode);
	
	start_list(&liststart, lnode);
	list_node *ptr = &liststart;
	char *arg = va_arg(args, char*);
	while(arg) {
		i++;
		add_to_list(&ptr, arg);
		ptr = ptr->next;
	}
	
	va_end(args);
	kprintf("\tfinished creating list\n");
	return i;
}
