#ifndef _GUI_ELEMENTS_H_
#define _GUI_ELEMENTS_H_

#include "lcd.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
/* Drawing rounded box */
void gui_elements_draw_rounded_box(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, const lcd_color_t * p_background_color,
				   lcd_color_t color_border);

#endif