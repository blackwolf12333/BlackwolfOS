#ifndef TEXT_GUI_H
#define TEXT_GUI_H

#include "monitor.h"

typedef struct window_t {
	u16int x;
	u16int y;
	u16int dx;
	u16int dy;
	char *content;
	char *title;
} window;

window main_window;

void initialize_text_gui();

#endif
