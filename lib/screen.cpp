#include "screen.h"

#define VRAM_SIZE (MAX_COL*MAX_ROW)
#define DEF_VRAM_BASE 0xb8000

static uint8_t curr_col = 0;
static uint8_t curr_row = 0;

int color = VGA_COLOR_GREEN;

static inline void put(char c) {
    ((uint16_t *) (DEF_VRAM_BASE))[(curr_row * MAX_COL) + curr_col] = (color << 8) | c;
}

static void cons_putc(int c)
{
    switch (c) 
    {
    case '\t':
        do 
        {
            cons_putc(' ');
        } while ((curr_col % 8) != 0);
        break;
    case '\r':
        curr_col = 0;
        break;
    case '\n':
        curr_row += 1;
        if (curr_row >= MAX_ROW) 
        {
            curr_row = 0;
        }
        break;
    case '\b':
        if (curr_col > 0) 
        {
            curr_col -= 1;
            put(' ');
        }
        break;
    default:
        put(c);
        curr_col += 1;
        if (curr_col >= MAX_COL) 
        {
            curr_col = 0;
            curr_row += 1;
            if (curr_row >= MAX_ROW) 
            {
                curr_row = 0;
            }
        }
    };
}

void putchar( int c )
{
    if (c == '\n') 
        cons_putc('\r');
    cons_putc(c);
}

void putchar_cl(int c, int new_color) {
    int tmp = color;
    color = new_color;
    putchar(c);
    color = tmp;
}

void fast_clear_screen() {
    curr_col = 0;
    curr_row = 0;
}

void clear_screen( void )
{
    curr_col = 0;
    curr_row = 0;
    
    int i;
    for (i = 0; i < VRAM_SIZE; i++)
        cons_putc(' ');
    
    curr_col = 0;
    curr_row = 0;
}