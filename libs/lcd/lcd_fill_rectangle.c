#include "stm32f4xx_gpio.h"
#include "spi-setup.h"
#include "lcd_internal.h"

/**
 * @param [in] x1, y1, x2, y2		The coordinates of the display area to fill
 * 
 * @param [in] color				The color value to fill with, according to mode
 */
void lcd_fill_rectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, lcd_color_t color) {
    const uint16_t number_of_pixels = (x2 - x1 + 1) * (y2 - y1 + 1);
    uint16_t i;
    
    SELECT();                  // select display

    lcd_serv_cmd(0x05);
    lcd_serv_data(0x00, 0x30);
    lcd_serv_cmd(0x16);
    lcd_serv_data(x2, x1);
    lcd_serv_cmd(0x17);
    lcd_serv_data(y2, y1);
    lcd_serv_cmd(0x21);
    lcd_serv_data(y1, x1);
    lcd_serv_cmd(0x22);
    lcd_write_8(LCD_WRITE_SEL_REG);

    // start data transmission
    for (i = 0; i < number_of_pixels; i++) lcd_write_16(color);

    DESELECT();                     // deselect display
}
/* LCD fill screen */
void lcd_fill_screen(lcd_color_t color) {
    lcd_fill_rectangle(0, 0, LCD_RIGHT, LCD_BOTTOM, color);
}
