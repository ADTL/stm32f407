#include "spi-setup.h"
#include "lcd_internal.h"

/**
 * @details
 * The scrolling area is offset by scrollOffset pixels. Pixels get shifted to the
 * opposite end (modulo-like).
 * 
 * @param [in] start_offset		The pixel row index where to start the scrolling
 * 
 * @param [in] size				The width in pixels of the scrolling area
 *
 * @param [in] scroll_offset		The number of pixels to offset the scrolling area
 */
void lcd_set_partial_scrolling(uint8_t start_offset, uint8_t size, uint8_t scroll_offset) {
    SELECT();                  // select display
    
    lcd_serv_cmd(0x14);
    lcd_serv_data(start_offset + size, start_offset);
    lcd_serv_cmd(0x11);
    lcd_serv_data(0x00, scroll_offset);
    
    DESELECT();                     // deselect display
}

/**
 * @details
 * The scrolling area is offset by scrollOffset pixels. Pixels get shifted to the
 * opposite end (modulo-like).
 * 
* @param [in] scroll_offset		The number of pixels to offset the scrolling area
 */
void lcd_set_scrolling(uint8_t scroll_offset) {
    lcd_set_partial_scrolling(0, LCD_HEIGHT, scroll_offset);
}
