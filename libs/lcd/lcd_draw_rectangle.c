/**
 * @file
 * Implements lcd_drawRectangle().
 */


#include <stdlib.h>
#include "lcd.h"


/**
 * @param [in] x1, y1, x2, y2		The rectangle's coordinates
 * 
 * @param [in] frame_color			Color for the rectangle's border (according to mode)
 * 
 * @param [in] p_background_color		Pointer to a color for the rectangle's filling
 * 									(according to mode), can be NULL for rectangles
 * 									without filling.
 * 
 * @param [in] frame_width			Width of the rectangle's border
 */ 
void lcd_draw_rectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, lcd_color_t frame_color,
	                   const lcd_color_t *p_background_color, uint8_t frame_width) {
    if (frame_width > 0) {
	lcd_fill_rectangle(x1, y1, x2, y1 + frame_width - 1, frame_color); // Line top
	lcd_fill_rectangle(x1, y2 - frame_width + 1, x2, y2, frame_color); // Line bottom
	lcd_fill_rectangle(x1, y1, x1 + frame_width - 1, y2, frame_color); // Line left
	lcd_fill_rectangle(x2 - frame_width + 1, y1, x2, y2, frame_color); // Line right
	
	// Filling
	if (p_background_color != NULL)
	    lcd_fill_rectangle(x1 + frame_width, y1 + frame_width, x2 - frame_width,
			       y2 - frame_width, * p_background_color);
    }
}