#include "keyboard.h"
#include "isr.h"
#include "monitor.h"
#include "common.h"
#include "arrays.h"
#include "charmap.h"
#include "kprintf.h"

char kbdus[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   50,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   50,				/* Right shift */
  '*',
    29,	/* Alt */
  ' ',	/* Space bar */
    53,	/* Caps lock */
    31,	/* 59 - F1 key ... > */
    32,   33,   34,   35,   36,   37,   38,   39,
    40,	/* < ... F10 */
    51,	/* 69 - Num lock*/
    52,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    41,	/* F11 Key */
    42,	/* F12 Key */
    0,	/* All other keys are undefined */
};

u8int alt_pressed = 0;
u8int shift_pressed = 0;

static void keyboard_callback(registers_t regs) {
	u8int scancode = inb(0x60);
	if(scancode & 0x80) {
		// TODO handle the release of a key
		if(kbdus[scancode] == 29) {
			alt_pressed = 0;
		} else if(kbdus[scancode] == 50) {
			shift_pressed = 0;
		}
	} else {
		if(kbdus[scancode] == 29) {
			alt_pressed = 1;
		} else if(kbdus[scancode] == 50) {
			shift_pressed = 1;
		} else {
			char c = kbdus[scancode];
			if(shift_pressed == 1) {
				int indexofc = indexOf(alfa, c);
				if(indexofc >= 0) {
					c = alfa[indexofc+26];
				} else if(indexofc == -1) {
					kprintf("org: %c", c);
					indexofc = indexOf(numeric, c);
					if(indexofc >= 0) {
						c = numeric[c+10];
					}
				}
			}
			vga.monitor_put(c, BLACK, WHITE);	
		}
	}
}

void init_keyboard() {
	register_interrupt_handler(IRQ1, &keyboard_callback);
}
