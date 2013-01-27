// text_gui.c -- defines a simple textual gui(wip)

#include "text_gui.h"

void init_window() {
	main_window.x = 0;
	main_window.y = 0;
	main_window.dx = 80;
	main_window.dy = 25;
	main_window.content = "Hello GUI world!:D";
	main_window.title = "Main";
}

void create_upper_edge() {
	u16int x;
	for(x = main_window.x; x < main_window.dx; x++) {
		vga.monitor_set_cursor(x, 0);
		vga.monitor_write_colorful(" ", RED, RED);
	}
	vga.monitor_write("\n");
}

void create_left_edge() {
	u16int y;
	for(y = main_window.y; y < main_window.dy; y++) {
		vga.monitor_set_cursor(main_window.x, y);
		vga.monitor_write_colorful(" ", RED, RED);
	}
}

void create_rows() {
	u16int x;
	u16int y;
	for(y = main_window.y+1; y < main_window.dy-1; y++) {
		for(x = main_window.x+1; x < main_window.dx-1; x++) {
			vga.monitor_set_cursor(x, y);
			vga.monitor_write_colorful(" ", LIGHT_RED, LIGHT_RED);
		}
		vga.monitor_write_colorful("\n", RED, RED); // this creates the right edge of the window
	}
}

void create_bottum_edge() {
	u16int x;
	for(x = main_window.x; x < main_window.dx; x++) {
		vga.monitor_set_cursor(x, main_window.dy-1);
		vga.monitor_write_colorful(" ", RED, RED);
	}
}

void write_window_content() {
	int i = 0;
	u16int y = main_window.y+1;
	u16int x = main_window.x+1;
	while(main_window.content[i]) {
		vga.monitor_set_cursor(x++, y);
		vga.monitor_put(main_window.content[i++], LIGHT_RED, BLUE);
	}
}

void write_window_title() {
	int i = 0;
	u16int y = main_window.y;
	u16int x = (main_window.dx / 2) - (strlen(main_window.title) / 2);
	while(main_window.title[i]) {
		vga.monitor_set_cursor(x++, y);
		vga.monitor_put(main_window.title[i++], RED, BLUE);
	}
}

void draw_main_window() {
	u16int x;
	u16int y;
	create_upper_edge();
	create_rows();
	write_window_title();
	write_window_content();
	create_left_edge();
	create_bottum_edge();
}

void initialize_text_gui() {
	init_window();
	draw_main_window();
}
