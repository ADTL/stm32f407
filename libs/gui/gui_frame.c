#include "gui_frame.h"

/* Drawing frame */
void gui_frame_draw(gui_element_t * gui_element) {
    if (gui_element->options != NULL) {
	gui_frame_options_t * gui_frame = (gui_frame_options_t *)(gui_element->options);
	
	lcd_fill_rectangle(gui_element->x_pos, gui_element->y_pos, 
			   gui_element->x_pos + gui_element->w_size,
			   gui_element->y_pos + gui_element->h_size, gui_frame->color);
    }
}
