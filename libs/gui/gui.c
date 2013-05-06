#include "gui.h"
/* Draw button */
void gui_draw_button(const char * text, uint8_t x, uint8_t y, lcd_color_t text_color,
		     const lcd_color_t * p_background_color, lcd_color_t border_color, const uint8_t * p_font) {
    uint16_t text_height = lcd_strlen(text) * lcd_get_font_height(p_font);
    uint16_t text_width = lcd_get_font_width(p_font);
    /* draw button body */
    gui_elements_draw_rounded_box(x, y, x + text_width + 3, y + text_height + 1, p_background_color, border_color);
    /* draw button text */
    lcd_draw_vert_text(text, x + 3, y + 1, text_color, p_background_color, p_font, 0);
}
