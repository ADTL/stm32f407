#include "spi-setup.h"
#include "lcd_internal.h"
/**
 * @details
 * Befor calling lcd_setPixel16() the bitmode has to be set manually to 16 bit
 * (if not already set). It is not set implicitly to avoid extensive SPI traffic
 * when setting many pixels blockwise.
 *
 * @param [in] x, y		The pixel's coordinates
 *
 * @param [in] color16	The 16 bit color value to set the pixel to
 * 
 * @see lcd_setPixel8() 
 */
void lcd_set_pixel16(uint8_t x, uint8_t y, lcd_color_t color16) {
    unsigned int i;

    SELECT();                  // select display

    lcd_serv_cmd(0x16);
    lcd_serv_data(0x83, 0x00);
    lcd_serv_cmd(0x17);
    lcd_serv_data(0xAF, 0x00);
    lcd_serv_cmd(0x21);
    lcd_serv_data(y, x);
    lcd_serv_cmd(0x22);
    lcd_serv_data(color16 >> 8, color16);

    DESELECT();                // deselect display
}