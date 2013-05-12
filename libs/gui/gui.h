#ifndef _GUI_H_
#define _GUI_H_

#include "gui_elements.h"

/* Draw button */
void gui_draw_button(const char * text, uint8_t x, uint8_t y, lcd_color_t text_color,
		     const lcd_color_t * p_background_color, lcd_color_t border_color, const uint8_t * p_font);

/* GUI Element */
#include "gui_element.h"
/* GUI Frame */
#include "gui_frame.h"

#endif
