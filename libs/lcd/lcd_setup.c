#include "spi-setup.h"
#include "lcd_internal.h"
#include "xprintf.h"

	const unsigned char ct1[6]= {0x07,0x02,0x04,0x0C,0x0D,0x0E};
	const unsigned char cd1[12]={0x00,0x00, 0x04,0x00, 0x00,0x00, 0x00,0x01, 0x06,0x16, 0x10,0x10};
	const unsigned char ct2[2]= {0x03,0x0E};
	const unsigned char cd2[4]= {0x00,0x0C, 0x2D,0x1F};
	const unsigned char ct3[1]= {0x0D};
	const unsigned char cd3[2]= {0x06,0x16};
	const unsigned char ct4[21]={0x01,0x0F,0x0B,0x11,0x06,0x05,0x14,0x15,0x16,0x17,0x20,0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x3A,0x3B};
	const unsigned char cd4[42]={0x02,0x15, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x30, 0xAF,0x00, 0x00,0x00, 0x83,0x00, 0xAF,0x00,
			0x00,0x00, 0x00,0x00, 0x04,0x00, 0x02,0x07, 0x07,0x00, 0x00,0x05, 0x07,0x03, 0x07,0x07, 0x00, 0x07, 0x12,0x00, 0x00,0x09};
/* Setup LCD */
void lcd_setup(void) {
	char i, j;

	RESET();		// reset display
	DESELECT();		// CS is high during reset release
	DATA();			// RS is not used, set it to high
	lcd_delay_ms(10);
	NORMAL();                    // release reset
	lcd_delay_ms(50);
	SELECT();                      // select display

	// starts at 58.8ms
	lcd_serv_cmd(0x00);
	lcd_serv_data(0x00,0x01);

	// starts at 125ms
	j=0;
	for (i=0; i<6; i++) {
		lcd_serv_cmd(ct1[i]);
		lcd_serv_data(cd1[j],cd1[j+1]);
		j+=2;
	}
	// start at 240ms
	j=0;
	for (i=0; i<2; i++) {
		lcd_serv_cmd(ct2[i]);
		lcd_serv_data(cd2[j],cd2[j+1]);
	    j+=2;
	}
	// start at 355ms
	j=0;
	for (i=0; i<1; i++) {
		lcd_serv_cmd(ct3[i]);
		lcd_serv_data(cd3[j],cd3[j+1]);
	    j+=2;
	}
	// start at 458ms
	j=0;
	for (i=0; i<21; i++) {
		lcd_serv_cmd(ct4[i]);
		lcd_serv_data(cd4[j],cd4[j+1]);
	    j+=2;
	}
	lcd_serv_cmd(0x07);
	lcd_serv_data(0x00, 0x05);
	lcd_serv_cmd(0x07);
	lcd_serv_data(0x00, 0x25);
	lcd_serv_cmd(0x07);
	lcd_serv_data(0x00, 0x27);
	lcd_serv_cmd(0x07);
	lcd_serv_data(0x06, 0x37);
	// ready for first screen
	DESELECT();                   // deselect display

	SPI_Speed(INTERFACE_FAST);
	// setup backlight
	lcd_backlight_setup();

	xputs("LCD enable\n");
}
/* LCD service command */
void lcd_serv_cmd(char cmd) { // indicates command type
	lcd_write_8(LCD_WRITE_INDEX_REG);
	lcd_write_8(0x00);
	lcd_write_8((unsigned char)cmd);
	lcd_cs_pulse();
}
/* LCD service data */
void lcd_serv_data(char dat1,char dat2) { // indicates command data
	lcd_write_8(LCD_WRITE_SEL_REG);
	lcd_write_8((unsigned char)dat1);
	lcd_write_8((unsigned char)dat2);
	lcd_cs_pulse();
}
/* LCD delay in ms */
void lcd_delay_ms(int delay) {
	volatile int counter = delay * 3000;
	while(counter--);
}
