#include "gui_elements.h"
/* Drawing rounded box
 * Parameters:
 * x1, y1, x2, y2: Coordinates
 * color_background: background color for box or NULL for transparent
 * color_border: box border color
 */
void gui_elements_draw_rounded_box(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, const lcd_color_t * p_background_color,
				   lcd_color_t color_border) {
    uint8_t width = x2 - x1 + 1;
    uint8_t height = y2 - y1 + 1;
    
    if (width >= 5 && height >= 1) {
	lcd_draw_line(x1 + 2, y1, x2 - 2, y1, color_border);
	lcd_draw_line(x1 + 2, y2, x2 - 2, y2, color_border);
    }
    if (height >= 5 && width >= 1) {
	lcd_draw_line(x1, y1 + 2, x1, y2 - 2, color_border);
	lcd_draw_line(x2, y1 + 2, x2, y2 - 2, color_border);
    }
    if (width >= 3 && height >= 3) {
	lcd_set_pixel16(x1 + 1, y1 + 1, color_border);
	lcd_set_pixel16(x2 - 1, y1 + 1, color_border);
	lcd_set_pixel16(x1 + 1, y2 - 1, color_border);
	lcd_set_pixel16(x2 - 1, y2 - 1, color_border);
    }
    if (p_background_color != NULL) {
	if (width >= 3 && height >= 3) {
	    lcd_draw_line(x1 + 1, y1 + 2, x1 + 1, y2 - 2, *p_background_color);
	    lcd_draw_line(x2 - 1, y1 + 2, x2 - 1, y2 - 2, *p_background_color);
	}
	if (width >= 5 && height >= 3) {
	    lcd_fill_rectangle(x1 + 2, y1 + 1, x2 - 2, y2 - 1, *p_background_color);
	}
    }
}
