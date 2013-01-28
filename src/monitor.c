// monitor.c -- implements a simple VGA driver
#include "monitor.h"

// function prototypes
static void monitor_put(char c, u8int backColour, u8int foreColour);
static void monitor_clear();
static void monitor_write(char *c);
static void monitor_write_colorful(char *c, u8int backColour, u8int foreColour);
static void monitor_set_cursor(u16int x, u16int y);
static void monitor_write_hex(u32int n);
static void monitor_write_dec(u32int n);

void initialize_monitor_vga() {
	vga.data.video_memory = (u16int *)0xB8000;
	vga.data.cursor_x = 0;
	vga.data.cursor_y = 0;
	vga.data.width = 80;
	vga.data.height = 25;
	vga.monitor_put = monitor_put;
	vga.monitor_clear = monitor_clear;
	vga.monitor_write = monitor_write;
	vga.monitor_write_colorful = monitor_write_colorful;
	vga.monitor_set_cursor = monitor_set_cursor;
	vga.monitor_write_hex = monitor_write_hex;
	vga.monitor_write_dec = monitor_write_dec;
	vga.monitor_clear();
}

// Updates the hardware cursor.
static void move_cursor()
{
   // The screen is 80 characters wide...
   u16int cursorLocation = vga.data.cursor_y * 80 + vga.data.cursor_x;
   outb(0x3D4, 14);                  // Tell the VGA board we are setting the high cursor byte.
   outb(0x3D5, cursorLocation >> 8); // Send the high cursor byte.
   outb(0x3D4, 15);                  // Tell the VGA board we are setting the low cursor byte.
   outb(0x3D5, cursorLocation);      // Send the low cursor byte.
}

// Scrolls the text on the screen up by one line.
static void scroll()
{

   // Get a space character with the default colour attributes.
   u8int attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
   u16int blank = 0x20 /* space */ | (attributeByte << 8);

   // Row 25 is the end, this means we need to scroll up
   if(vga.data.cursor_y > vga.data.height)
   {
       // Move the current text chunk that makes up the screen
       // back in the buffer by a line
		 u16int width = vga.data.width;
		 u16int height = vga.data.height;
       int i;
       for (i = 0; i < (height-1)*width; i++)
       {
           vga.data.video_memory[i] = vga.data.video_memory[i+width];
       }

       // The last line should now be blank. Do this by writing
       // 80 spaces to it.
       for (i = (height-1)*width; i < height*width; i++)
       {
           vga.data.video_memory[i] = blank;
       }
       // The cursor should now be on the last line.
       vga.data.cursor_y = height-1;
   }
}

/*u16int getPositionOfLastCharacter() {
	u16int *location;
	u16int bits=8;
	u16int x;
	for(x = 0; x < vga.data.width; x++) {
		location = vga.data.video_memory + (vga.data.cursor_y*80 + x);
		char loc = location >> bits;
		vga.monitor_put(loc, RED, RED);
		if(loc == '\n') {
			return x;
		} else {
			continue;
		}
	}
	return 0;
}*/

// Writes a single character out to the screen.
static void monitor_put(char c, u8int backColour, u8int foreColour)
{
   // The attribute byte is made up of two nibbles - the lower being the
   // foreground colour, and the upper the background colour.
   u8int  attributeByte = (backColour << 4) | (foreColour & 0x0F);
   // The attribute byte is the top 8 bits of the word we have to send to the
   // VGA board.
   u16int attribute = attributeByte << 8;
   u16int *location;

   // Handle a backspace, by moving the cursor back one space
   if (c == 0x08) {
		if(vga.data.cursor_x > 0) {
			vga.data.cursor_x--;
			vga.monitor_put(' ', backColour, foreColour);
			vga.data.cursor_x--;
		} else if(vga.data.cursor_x == 0) {
			vga.data.cursor_y--;
			vga.data.cursor_x = 0;//getPositionOfLastCharacter();
		}
	}

   // Handle a tab by increasing the cursor's X, but only to a point
   // where it is divisible by 8.
   else if (c == 0x09) {
       vga.data.cursor_x = (vga.data.cursor_x+8) & ~(8-1);
   }

   // Handle carriage return
   else if (c == '\r')
   {
       vga.data.cursor_x = 0;
   }

   // Handle newline by moving cursor back to left and increasing the row
   else if (c == '\n')
   {
		u8int  attributeByte2 = (BLACK << 4) | (BLACK & 0x0F);
		u16int attribute2 = attributeByte2 << 8;
		location = vga.data.video_memory + (vga.data.cursor_y*80 + vga.data.cursor_x);
		*location = ' ' | attribute2;
		vga.data.cursor_x = 0;
		vga.data.cursor_y++;
   }
   // Handle any other printable character.
   else if(c >= ' ')
   {
       location = vga.data.video_memory + (vga.data.cursor_y*vga.data.width + vga.data.cursor_x);
       *location = c | attribute;
       vga.data.cursor_x++;
   }

   // Check if we need to insert a new line because we have reached the end
   // of the screen.
   if (vga.data.cursor_x >= vga.data.width)
   {
       vga.data.cursor_x = 0;
       vga.data.cursor_y ++;
   }

   // Scroll the screen if needed.
   scroll();
   // Move the hardware cursor.
   move_cursor();
}

// Clears the screen, by copying lots of spaces to the framebuffer.
static void monitor_clear()
{
   // Make an attribute byte for the default colours
   u8int attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
   u16int blank = 0x20 /* space */ | (attributeByte << 8);

   int i;
   for (i = 0; i < 80*25; i++)
   {
       vga.data.video_memory[i] = blank;
   }

   // Move the hardware cursor back to the start.
   vga.data.cursor_x = 0;
   vga.data.cursor_y = 0;
   move_cursor();
}

// Outputs a null-terminated ASCII string to the monitor.
static void monitor_write(char *c)
{
   int i = 0;
   while (c[i])
   {
       vga.monitor_put(c[i++], 0, 15);
   }
}

static void monitor_write_colorful(char *c, u8int backColour, u8int foreColour) {
	int i = 0;
   while (c[i])
   {
       vga.monitor_put(c[i++], backColour, foreColour);
   }
}

static void monitor_set_cursor(u16int x, u16int y) {
	vga.data.cursor_x = x;
	vga.data.cursor_y = y;
	move_cursor();
}

static void monitor_write_hex(u32int n)
{
    s32int tmp;

    monitor_write("0x");

    char noZeroes = 1;

    int i;
    for (i = 28; i > 0; i -= 4)
    {
        tmp = (n >> i) & 0xF;
        if (tmp == 0 && noZeroes != 0)
        {
            continue;
        }
    
        if (tmp >= 0xA)
        {
            noZeroes = 0;
            monitor_put (tmp-0xA+'a', BLACK, WHITE);
        }
        else
        {
            noZeroes = 0;
            monitor_put(tmp+'0', BLACK, WHITE);
        }
    }
  
    tmp = n & 0xF;
    if (tmp >= 0xA)
    {
        monitor_put (tmp-0xA+'a', BLACK, WHITE);
    }
    else
    {
        monitor_put (tmp+'0', BLACK, WHITE);
    }

}

static void monitor_write_dec(u32int n)
{

    if (n == 0)
    {
        monitor_put('0', BLACK, WHITE);
        return;
    }

    s32int acc = n;
    char c[32];
    int i = 0;
    while (acc > 0)
    {
        c[i] = '0' + acc%10;
        acc /= 10;
        i++;
    }
    c[i] = 0;

    char c2[32];
    c2[i--] = 0;
    int j = 0;
    while(i >= 0)
    {
        c2[i--] = c[j++];
    }
    monitor_write(c2);

}
