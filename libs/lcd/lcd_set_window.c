/**
 * @file
 * Implements lcd_setWindow() and lcd_startBlockwiseDrawing().
 */
#include "spi-setup.h"
#include "lcd_internal.h"

/*
 * @param [in] x1, y1, x2, y2		Pixel coordinates
 * @param [in] orientation			Direction in which the data will be written to the display,
 * 									either LCD_ORIENTATION_WIDE_Y or LCD_ORIENTATION_WIDE_X
 */
void lcd_set_window(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t orientation) {
    SELECT();                   // select display
    
    lcd_serv_cmd(0x05);
    if (orientation == LCD_ORIENTATION_WIDE_Y) {
	lcd_serv_data(0x00,0x38);
	lcd_serv_cmd(0x16);
	lcd_serv_data(x2, x1);
	lcd_serv_cmd(0x17);
	lcd_serv_data(y2, y1);
    }
    else {
	lcd_serv_data(0x00,0x30);
	lcd_serv_cmd(0x17);
	lcd_serv_data(x2, x1);
	lcd_serv_cmd(0x16);
	lcd_serv_data(y2, y1);
    }
    
    DESELECT();                       // deselect display
}

void lcd_start_blockwise_drawing(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t orientation)
{
    lcd_set_window(x1, y1, x2, y2, orientation);
    
    SELECT();                   // select display
    lcd_serv_cmd(0x21);
    if (orientation == LCD_ORIENTATION_WIDE_Y)
	lcd_serv_data(y1, x1);
    else
	lcd_serv_data(x1, y1);
}