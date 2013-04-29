/**
 * @file
 * Header file for all library-internal functionalities.
 */


#ifndef _lcd_internal_h_
#define _lcd_internal_h_

#include "stm32f4xx_gpio.h"
#include "lcd.h"
#include "lcd_io.h"

// ------------------------- defines -------------------------------------------
/* wait to end transmit and send cs pulse */
#define lcd_cs_pulse() DESELECT();SELECT()
/* Index register block prefix */
#define LCD_WRITE_INDEX_REG 0x74
/* Current register block prefix */
#define LCD_WRITE_SEL_REG 0x76
/* Display control pins */

// ------------------------- internal prototypes -------------------------------

/* Setup display backligth */
void lcd_backlight_setup(void);
/* Starts blockwise drawing of the display's content. Sets the LCD's current window
 * and Display pins (CS, RS). */
void lcd_start_blockwise_drawing(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t orientation);
/* Send 8 bit data to lcd */
void (*lcd_write_8)(unsigned char);
/* Send 16 bit data to lcd */
void (*lcd_write_16)(unsigned short);
/* Send service index command */
void lcd_serv_cmd(char cmd);
/* Send service data to current index */
void lcd_serv_data(char dat1,char dat2);
/* Delay in ms for another command */
void lcd_delay_ms(int delay);

#endif
