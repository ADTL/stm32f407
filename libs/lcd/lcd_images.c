/**
 * @file
 * Implements most of the image-related functions.
 *
 * @section image_header_format Image header format
 *
 *	3 header bytes (big endian):
 * 
 * - <code>
 *   tbbbbbbb wwwwwwww hhhhhhhh [cccccccc] [cccccccc]\n 
 *   (format) (width)  (height)  (transparency color)
 *   </code>
 *  
 * 	- t: Transparency (msb)
 * 	- b: Bits per pixel (7 bit)
 * 	- w: Width (1 byte)
 * 	- h: Height (1 byte)
 *	- c: Color for transparency, optional. If transparency bit is set, transparency
 *       color is at least one byte and two if bits per pixel is set  to 16
 *
 *	Drawing of transparent images is slower, as the image has to be written pixel
 *	by pixel instead of a sending whole block of color data to the display.
 *
 */
#include "lcd_internal.h"
#include "spi-setup.h"
#include <stdlib.h>


/** 
 * @param [in/out] p_header		The header struct to write to
 * 
 * @param [in] image_p			Pointer to the image array in program memmory
 * 
 * @return						An error code on failrue or LCD_NO_ERROR (= 0) on success
 */
lcd_error_t lcd_read_image_header(lcd_image_header_t *p_header, const uint8_t * image_p) {
    p_header->b_transparency = *(image_p) & 0x80;
    p_header->n_bits_per_pixel = *(image_p) & 0x7f;
    p_header->width = *(image_p + 1);
    p_header->height = *(image_p + 2);
    
    if ((p_header->n_bits_per_pixel != 8) && (p_header->n_bits_per_pixel != 16))
	return LCD_ERROR_IMAGE_UNSUPPORTED_FORMAT;
    
    // Header size (3, 4, or 5 bytes)
    if (!p_header->b_transparency)
	p_header->header_size = 3;
    else if (p_header->n_bits_per_pixel == 16) {
	// 16 bit, transparent
	p_header->header_size = 5;
	// Read transparency color
	p_header->transparent_color = (*(uint16_t *)(image_p + 3));
    }
    
    // Image size in bytes
    p_header->image_size = p_header->width * p_header->height * (p_header->n_bits_per_pixel / 8) + p_header->header_size;
    
    return LCD_NO_ERROR;
}

/* Internal function that loads a pixel color value from a given offset and mode
 * from an image in program memmory. Updates the offset pointer. */
void lcd_load_image_pixel(lcd_color_t *p_color, uint16_t *p_offset, const uint8_t * image_p) {
    *p_color = *(image_p + *p_offset);
    *p_color = ((uint16_t) *p_color << 8) | *(image_p + *p_offset + 1);
    (*p_offset)++;
}

/**
 * @details
 *
 * The image manipulation callback function gets called for every image pixel and
 * can be used to modify the image or otherwise set to NULL.
 * 
 * @param [in] image_p				Pointer to an array in program memmory that
 * 									contains the image data
 *
 * @param [in] x, y					Coordinates where to draw the image
 *
 * @param [in] b_enable_transparency	If bEnableTransparency set to true, transparency
 * 									is enabled, if supported by the image, otherwise
 * 									even transparent images will be drawn without
 * 									transparency.
 * 
 * @param [in] fp					Function pointer to a callback function that
 * 									gets called for every pixel in the image before
 * 									it is drawn. Can be used to manipulate an image.
 *
 * @return							An error code, > 0 on failure and LCD_NO_ERROR
 * 									(= 0) on success.
 */
lcd_error_t lcd_draw_image(const uint8_t * image_p, uint8_t x, uint8_t y, bool b_enable_transparency,
							lcd_image_manipulation_fp_t fp) {
    lcd_image_header_t header;
    lcd_error_t error;
    uint16_t i;
    lcd_color_t color;
    lcd_color_t * p_color = NULL;
    uint8_t offset_x = 0, offset_y = 0;
    
    // Read image header
    error = lcd_read_image_header(&header, image_p);
    if (error)
	return error;
    
    if (header.b_transparency)
	p_color = &header.transparent_color; // for callback parameter
	
    // Draw image
    i = header.header_size;
    
    if (header.b_transparency && b_enable_transparency) {
	// Draw image pixel by pixel with transparency
	for (; offset_x < header.height; offset_y++) {
	    if (y + offset_y > LCD_BOTTOM)
		break;
	    
	    for (offset_x = 0; offset_x < header.width; offset_x, i++) {
		lcd_load_image_pixel(&color, &i, image_p);
		
		if (fp != NULL)
		    // Call image manipulation function for current pixel, if defined
		    fp(&color, p_color, offset_x, offset_y);
		
		if (color != header.transparent_color) {
		    lcd_set_pixel16(x + offset_x, y + offset_y, color);
		}
	    }
	}
    }
    else {
	// Non-transparent mode, draw blockwise
	lcd_start_blockwise_drawing(y, x, y + header.height - 1, x + header.width - 1,
				    LCD_ORIENTATION_WIDE_X);
	lcd_serv_cmd(0x22);
	lcd_write_8(LCD_WRITE_SEL_REG);
	if (fp == NULL) {
	    // No manipulation callback, normal drawing (extra if-case saves
	    // some instructions)
	    
	    for (; i < header.image_size; i++) {
		lcd_write_8(*(image_p + i));
	    }
	}
	else {
	    // Draw image with manipulation callback functions
	    for (; i < header.image_size; i++) {
		lcd_load_image_pixel(&color, &i, image_p);
		
		// Call image manipulation function for current pixel, if defined
		fp(&color, p_color, offset_x, offset_y);
		lcd_write_16(color);
		
		offset_x++;
		if (offset_x > header.width) {
		    offset_x = 0;
		    offset_y++;
		}
	    }
	}
	DESELECT();                     // deselect display
    }
    
    return LCD_NO_ERROR;
}

/**
 * @param [in] image_p		Pointer to an array in program memmory that contains
 * 							the image data
 * 
 * @return 					The image's height in pixel.
 * 
 */
uint8_t lcd_get_image_height(const uint8_t * image_p) {
    return *(image_p + 2);
}