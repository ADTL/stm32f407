#include "lcd_internal.h" 
/**
 * @file
 * Implements line drawing functions.
 */
void lcd_draw_line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, lcd_color_t color) {
    int dy = y2 - y1;
    int dx = x2 - x1;
    int stepx, stepy;
    
    if (dy < 0) {
	dy = -dy;
	stepy = -1;
    }
    else
	stepy = 1;
    
    if (dx < 0) {
	dx = -dx;
	stepx = -1;
    }
    else
	stepx = 1;
    
    dy <<= 1;
    dx <<= 1;
    
    lcd_set_pixel16(x1, y1, color);
    
    if (dx > dy) {
	int fraction = dy - (dx >> 1);
	while (x1 != x2) {
	    if (fraction >= 0) {
		y1 += stepy;
		fraction -= dx;
	    }
	    x1 += stepx;
	    fraction += dy;
	    
	    lcd_set_pixel16(x1, y1, color);
	}
    }
    else {
	int fraction = dx - (dy >> 1);
	while (y1 != y2) {
	    if (fraction >= 0) {
		x1 += stepx;
		fraction -= dy;
	    }
	    y1 += stepy;
	    fraction += dx;
	    
	    lcd_set_pixel16(x1, y1, color);
	}
    }
}