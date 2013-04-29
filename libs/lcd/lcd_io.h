/* write a byte */
#define lcd_wr_8(func) lcd_write_8 = (void(*)(unsigned char))(func)
extern void (*lcd_write_8)(unsigned char);
/* write a word */
#define lcd_wr_16(func) lcd_write_16 = (void(*)(unsigned short))(func)
extern void (*lcd_write_16)(unsigned short);

