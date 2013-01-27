// monitor.h -- Defines the interface for monitor.h

#ifndef MONITOR_H
#define MONITOR_H

#include "common.h"

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHT_GRAY 7
#define DARK_GRAY 8
#define LIGHT_BLUE 9
#define LIGHT_GREEN 10
#define LIGHT_CYAN 11
#define LIGHT_RED 12
#define LIGHT_MAGENTA 13
#define LIGHT_BROWN 14
#define WHITE 15

typedef struct monitor {
	u16int *video_memory;
	u16int cursor_x;
	u16int cursor_y;
	void (*monitor_put) (char c, u8int backColour, u8int foreColour);
	void (*monitor_clear)();
	void (*monitor_write)(char *c);
	void (*monitor_write_colorful)(char *c, u8int backColour, u8int foreColour);
	void (*monitor_set_cursor)(u16int x, u16int y);
} monitor;

monitor vga;

void initialize_monitor_vga();

#endif // MONITOR_H
