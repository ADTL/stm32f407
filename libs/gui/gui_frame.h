#ifndef _GUI_FRAME_H_
#define _GUI_FRAME_H_

#include "gui_element.h"
#include "lcd.h"

/* Frame element options */
typedef struct {
    lcd_color_t color;
} gui_frame_options_t;

/* Drawing frame */
void gui_frame_draw(gui_element_t * element);

#endif
