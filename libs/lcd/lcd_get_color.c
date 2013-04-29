/**
 * @file
 * Implements lcd_getColorComponents() and lcd_getColor().
 */


#include "lcd.h"


/**
 * @param [in] color					The color valaue to disperse
 * 
 * @param [out] p_red, p_green, p_blue		Pointers to uint8_t variables for the red
 * 										/ green / blue components
 * 
 * @param [in] mode						The bit mode corresponding to the color
 */ 
void lcd_get_color_components(lcd_color_t color, uint8_t *p_red, uint8_t *p_green,
							uint8_t *p_blue) {
		*p_red   = LCD_COLOR16_GET_R(color);
		*p_green = LCD_COLOR16_GET_G(color);
		*p_blue  = LCD_COLOR16_GET_B(color);
}

/**
 * @details
 * Color components are in the range of the given mode, not [0, 255].
 * 
 * @param [in] r, g, b				The color components for 8 or 16 bit pixel data mode
 * 
 * @param [in] mode					The bit mode corresponding to the color components
 * 
 * @return 							The color value
 */
lcd_color_t lcd_get_color(uint8_t r, uint8_t g, uint8_t b) {
    return LCD_COLOR16(r, g, b);
}
