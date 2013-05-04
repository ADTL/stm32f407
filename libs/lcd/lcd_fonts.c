#include "lcd_internal.h"
#include "spi-setup.h"
#include <stdlib.h>

// Constants

/** Size of the font header. */
#define LCD_FONT_HEADER_SIZE 7

/** Struct for font header data. */
typedef struct {
	uint16_t size;				/**< The total font size. */
	uint8_t maximal_width;		/**< The maximum width of a single character. */
	uint8_t height;				/**< The font's height. */
	uint8_t n_bits_per_pixel;		/**< Bit depth for pixel data, only 1 bit supported
									 at the moment. */
	uint8_t first_char;			/**< The first character of the characte range defindes
									 by the font. */
	uint8_t last_char;			/**< The last character of the characte range defindes
									 by the font. */
	uint8_t n_chars;				/**< Number of characters in the font (= lastChar - firstChar). */
	uint8_t space_width;			/**< The width for the space character (needed, if it's not
									 part of the font). */
} lcd_font_header_t;

// ---------------------------- Global variables -------------------------------
/** Pointer into program memmory to the currently loaded font. */
const uint8_t * lcd_p_font = NULL;

/** Pointer into program memmory to the offset where the current font's pixel
 * data starts. */
const uint8_t * lcd_p_font_data = NULL;

/** Header of the currently loaded font */
lcd_font_header_t lcd_font_header;

// ------------------------ internal functions ---------------------------------

uint8_t lcd_get_char_width(unsigned char c, const uint8_t * p_font) {
    return *(p_font + LCD_FONT_HEADER_SIZE + c - lcd_font_header.first_char);
}

// -----------------------------------------------------------------------------

/** @param [in] p_font		Pointer to the font array in program memmory to load */
lcd_error_t lcd_load_font(const uint8_t * p_font) {
    uint8_t byte;
    
    // Read font header
    lcd_font_header.size = (uint16_t) * p_font;
    lcd_font_header.maximal_width = *(p_font + 2);
    lcd_font_header.height = *(p_font + 3);
    
    byte = *(p_font + 4);
    if (byte & 0x80)
	// Font is compressed (not supported)
	return LCD_ERROR_FONT_UNSUPPORTED_FORMAT;
    
    lcd_font_header.n_bits_per_pixel = byte;
    
    lcd_font_header.first_char = *(p_font + 5);
    lcd_font_header.last_char = *(p_font + 6);
    lcd_font_header.n_chars = lcd_font_header.last_char - lcd_font_header.first_char + 1;
    lcd_font_header.space_width = lcd_font_header.height * 4 / 10;
    
    // Set pointer to font
    lcd_p_font = p_font;
    
    // Set pointer to pixel data
    lcd_p_font_data = p_font + LCD_FONT_HEADER_SIZE + lcd_font_header.n_chars;
    
    return LCD_NO_ERROR;
}

/**
 * @param [in] c					The character to draw
 *
 * @param [in] x, y					The coordinates to draw the character at
 *
 * @param [in] char_color			The color to draw the character with
 *
 * @param [in] p_background_color		Pointer to a background color for the character,
 * 									can be NULL to draw a transparent
 *
 * @param [in] p_font				Pointer to a font array in program memmory to use
 *
 * @return							An error code, > 0 on failure and LCD_NO_ERROR
 * 									(= 0) on success.
 */
lcd_error_t lcd_draw_char(unsigned char c, uint8_t x, uint8_t y, lcd_color_t char_color,
			 const lcd_color_t *p_background_color, const uint8_t * p_font) {
    uint8_t char_offset = c - lcd_font_header.first_char;
    uint8_t bit, byte;
    uint8_t offset_x = 0, offset_y = 0;
    uint16_t bit_offset = 0, last_bit;
    uint8_t char_width = lcd_get_char_width(c, p_font);
    uint16_t i;
    
    // Load font, if necessary
    if (p_font != lcd_p_font)
	lcd_load_font(p_font);
    
    // Check if character exists in font
    if ((c < lcd_font_header.first_char) || (c > lcd_font_header.last_char) || (char_width == 0)) {
	return LCD_ERROR_FONT_CHAR_UNAVAILABLE;
    }
    
    // Find offset within pixel data block by adding all character sizes
    for (i = 0; i < char_offset; i++) {
	bit_offset += lcd_get_char_width(lcd_font_header.first_char + i, p_font)
	    * lcd_font_header.height * lcd_font_header.n_bits_per_pixel;
    }
	    
    last_bit = bit_offset + char_width * lcd_font_header.height;
    
    // Read first byte from program memmory
    byte = lcd_p_font_data[bit_offset / 8];
    
    // Draw character
    if (p_background_color == NULL) {
	// Transparent mode, draw pixel by pixel
	
	for (i = bit_offset; i < last_bit; i++) {
	    bit = i % 8;
	    
	    // Read new byte from program memmory if necessary
	    if (bit == 0)
		byte = lcd_p_font_data[i / 8];
	    
	    if (byte & (1 << bit))
		lcd_set_pixel16(x + offset_x, y + offset_y, char_color);
	    
	    offset_y++;
	    if (offset_y == lcd_font_header.height) {
		offset_y = 0;
		offset_x++;
	    }
	}
    } else {
	// Non-transparent mode, draw blockwise
	lcd_start_blockwise_drawing(x, y, x + char_width - 1, y + lcd_font_header.height - 1,
				    LCD_ORIENTATION_WIDE_Y);
	lcd_serv_cmd(0x22);
	lcd_write_8(LCD_WRITE_SEL_REG);
	for (i = bit_offset; i < last_bit; i++) {
	    
	    bit = i % 8;
	    
	    // Read new byte from program memmory if necessary
	    if (bit == 0)
		byte = lcd_p_font_data[i / 8];
	    
	    if (byte & (1 << bit))
		lcd_write_16(char_color);
	    else
		lcd_write_16(*p_background_color);
	}
	
	DESELECT();                     // deselect display
    }
    
    return LCD_NO_ERROR;
}

/**
 * @param [in] text					The character string to draw
 *
 * @param [in] x, y					The coordinates to draw the text at
 *
 * @param [in] text_color			The color to draw the text with
 *
 * @param [in] p_background_color		Pointer to a background color for the text,
 * 									can be NULL to draw a transparent
 *
 * @param [in] p_font				Pointer to a font array in program memmory to use
 *
 * @param [in] char_spacing			A spacing value to offset every character with,
 * 									has no effect if set to 0
 * 
 * @return							An error code, > 0 on failure and LCD_NO_ERROR
 * 									(= 0) on success.
 */
/** Draws text from a character string. */
lcd_error_t lcd_draw_text(const char * text, uint8_t x, uint8_t y, lcd_color_t text_color,
			  const lcd_color_t * p_background_color, const uint8_t * p_font,
			  int8_t char_spacing) {
    uint8_t c;
    uint8_t old_x, char_width;
    uint16_t length = 0;
    uint16_t i;
    const uint8_t * p_text = text;
    /* calculate string length */
    while (*p_text++ != '\0') length++;
    
    if (text == NULL)
	return LCD_ERROR;
    // Load font, if necessary
    if (p_font != lcd_p_font)
	lcd_load_font(p_font);
    
    for (i = 0; i < length; i++) {
	c = (uint8_t) text[i];
	
	if (c == 0x20) {
	    if (p_background_color != NULL)
		lcd_fill_rectangle(x, y, x + lcd_font_header.space_width,
				   y + lcd_font_header.height - 1, * p_background_color);
	    x += lcd_font_header.space_width;
	    continue;
	}
	
	char_width = lcd_get_char_width(c, p_font);
	
	if (char_width == 0) {
	    continue;
	}
	
	lcd_draw_char(c, x, y, text_color, p_background_color, p_font);
	
	x += char_width;
	
	if (x >= LCD_WIDTH)
	    break;
	
	old_x = x;
	x += char_spacing + 1;
	
	if ((p_background_color != NULL) && (i != length - 1))
	    lcd_fill_rectangle(old_x, y, x, y + lcd_font_header.height - 1,
			       *p_background_color);
    }
    
    return LCD_NO_ERROR;
}

/**
 * @param [in] text					The character string to draw
 *
 * @param [in] x, y					The coordinates to draw the text at
 *
 * @param [in] text_color			The color to draw the text with
 *
 * @param [in] p_background_color		Pointer to a background color for the text,
 * 									can be NULL to draw a transparent
 *
 * @param [in] p_font				Pointer to a font array in program memmory to use
 *
 * @param [in] char_spacing			A spacing value to offset every character with,
 * 									has no effect if set to 0
 * 
 * @return							An error code, > 0 on failure and LCD_NO_ERROR
 * 									(= 0) on success.
 */
lcd_error_t lcd_draw_vert_text(const char * text, uint8_t x, uint8_t y, lcd_color_t text_color,
			  const lcd_color_t * p_background_color, const uint8_t * p_font,
			  int8_t char_spacing) {
    uint8_t c;
    uint8_t old_y, char_height;
    uint16_t length = 0;
    uint16_t i;
    const uint8_t * p_text = text;
    /* calculate string length */
    while (*p_text++ != '\0') length++;
    
    if (text == NULL)
	return LCD_ERROR;
    // Load font, if necessary
    if (p_font != lcd_p_font)
	lcd_load_font(p_font);
    
    for (i = 0; i < length; i++) {
	c = (uint8_t) text[i];
	
	if (c == 0x20) {
	    if (p_background_color != NULL)
		lcd_fill_rectangle(x, y, x + lcd_font_header.space_width,
				   y + lcd_font_header.height - 1, * p_background_color);
	    x += lcd_font_header.space_width;
	    continue;
	}
	
	char_height = lcd_get_font_height(p_font);
	
	lcd_draw_char(c, x, y, text_color, p_background_color, p_font);
	
	y += char_height;
	
	if (y >= LCD_HEIGHT)
	    break;
	
	old_y = y;
	y += char_spacing;
	
	if ((p_background_color != NULL) && (i != length - 1))
	    lcd_fill_rectangle(x, old_y, x, y,
			       *p_background_color);
    }
    
    return LCD_NO_ERROR;
}

/**
 * @param [in] p_font		Pointer to a font array in program memmory
 *
 * @return					The font's height (i.e. the height of the biggest character)
 * 
 * @see lcd_getTextWidth()
 */
uint8_t lcd_get_font_height(const uint8_t * p_font) {
    // Load font, if necessary
    if (p_font != lcd_p_font)
	lcd_load_font(p_font);
    
    return lcd_font_header.height;
}

uint8_t lcd_get_font_width(const uint8_t * p_font) {
    // Load font, if necessary
    if (p_font != lcd_p_font)
	lcd_load_font(p_font);
    
    return lcd_font_header.maximal_width;
}

/**
 * @param [in] text			Character string of the text
 * 
 * @param [in] p_font		Pointer to a font array in program memmory
 *
 * @param [in] char_spacing	An additional character spacing to take into account
 * 							for calculation.
 * 
 * @return					The width in pixels of the text if drawn to screen.
 *
 * @see lcd_getFontHeight, lcd_drawText()
 */
uint16_t lcd_get_text_width(const char * text, const uint8_t * p_font, int8_t char_spacing) {
    uint8_t length = 0;
    uint16_t text_width = 0;
    uint8_t i;
    const uint8_t * p_text = text;
    /* calculate string length */
    while (*p_text++) length++;
    // Load font, if necessary
    if (p_font != lcd_p_font)
	lcd_load_font(p_font);
    
    for (i = 0; i < length; i++) {
	if (text[i] == 0x20) {
	    text_width += lcd_font_header.space_width;
	} else if ((text[i] < lcd_font_header.first_char) ||
	    (text[i] > lcd_font_header.last_char))
		continue;
	else
	    text_width += lcd_get_char_width(text[i], p_font) + char_spacing + 1;
    }
    
    return text_width - char_spacing - 1;
}

/**
 * @param [in] text					A character string to draw
 *
 * @param [in] y					The Y-coordinate to draw the text at
 *
 * @param [in] text_color			The color to draw the text with
 *
 * @param [in] p_background_color		Pointer to a background color for the text,
 * 									can be NULL to draw a transparent
 *
 * @param [in] p_font				Pointer to a font array in program memmory to use
 *
 * @param [in] char_spacing			A spacing value to offset every character with,
 * 									has no effect if set to 0
 *
 * @return							An error code, > 0 on failure and LCD_NO_ERROR
 * 									(= 0) on success.
 */
lcd_error_t lcd_draw_centered_text(const char * text, uint8_t y, lcd_color_t text_color,
				 const lcd_color_t * p_background_color, const uint8_t * p_font,
				 int8_t char_spacing) {
    
    uint8_t x = (LCD_WIDTH - lcd_get_text_width(text, p_font, char_spacing)) / 2 + 1;
    
    return lcd_draw_text(text, x, y, text_color, p_background_color, p_font, char_spacing);
}

uint16_t lcd_strlen(const char * text) {
    uint16_t length = 0;
    /* calculate string length */
    while (*text++ != '\0') length++;
    
    return length;
}
