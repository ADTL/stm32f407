/**
 * @file
 * Header file for Siemens S65 Display C library
 * Model: LPH8836
 * Controller: HD66773 132 x 176 dot Graphics Controller 
 * 	Driver for TFT 260,000-color Displays HITACHI
 * @version 1.0.0
 */

#ifndef _lcd_h_
#define _lcd_h_

#include <stdint.h>
#include <stdbool.h>
// ------------------------------ type definitions ----------------------------
/**
 * Type for a color value for both, 8 and 16 bit mode.
 * 
 * In 16 bit mode the color format is RRRRRGGGGGGBBBBB (5-6-5)
 * (bits per component, msb to lsb).
 * You have to be aware of the current bit mode to know which type of color a
 * lcd_color_t variable contains.
 */
typedef uint16_t lcd_color_t;

/**
 * Fuction pointer type for callback functions that manipulate a color value
 * of an image a particular bit mode.
 * The transparency color value is useful to substitute transparent pixels with
 * another color, but still draw the image in blockwise mode. pTransparencyColor
 * is set to NULL is non-transparent mode. The callback is called befor the
 * pixel value is compares to the transparent color (i.e. befor it might be skipped).
 * 
 * Used by lcd_drawImage().
 * @see lcd_drawImage_P()
 */
typedef void (*lcd_image_manipulation_fp_t)(lcd_color_t *p_color, const lcd_color_t *p_transparency_color,
					    uint8_t x, uint8_t y);

/** Type for error codes. */
typedef uint8_t lcd_error_t;

/** Struct for image header data. */
typedef struct {
	uint8_t header_size;				/**< Size in bytes of the image header. */
	uint16_t image_size;				/**< Total image size in byte including header data. */ 
	uint8_t width;					/**< The image's width in pixel. */
	uint8_t height;					/**< The image's height in pixel. */
	uint8_t n_bits_per_pixel;			/**< Number of Bits per pixel. */
	bool b_transparency;				/**< Transparency mode. */
	lcd_color_t transparent_color;	/**< The image's transparent color, if transparency mode is set. */
} lcd_image_header_t;

// ---------------------------- constants --------------------------------------

/** Error code constants. */
enum {
    LCD_NO_ERROR = 0,
    LCD_ERROR_MEMMORY_ALLOCATION,			/**< Memmory allocation via malloc() failed. */
    LCD_ERROR_FONT_CHAR_UNAVAILABLE,		/**< Character is not contained by font. */
    LCD_ERROR_FONT_UNSUPPORTED_FORMAT,		/**< Font format is unknown or unsupported. */
    LCD_ERROR_IMAGE_UNSUPPORTED_FORMAT,		/**< Image format is unknown or unsupported. */
    LCD_ERROR_DIMENSIONS_EXCEEDED,			/**< A drawing operation exceeded the display's dimensions. */
    LCD_ERROR								/**< General unspecified error. */
};

/**
 * Display orientation constants.
 *
 * At the moment only used for screen filling operations.
 */
enum {
	LCD_ORIENTATION_WIDE_Y,			/**< The longer side of the display is the Y-axis (phone-like). */
	LCD_ORIENTATION_WIDE_X			/**< The longer side of the display is the X-axis. */
};

/** Backlight constants */
#define BACKLIGHT_ON 0xff
#define BACKLIGHT_OFF 0x00

/** @name Display dimensions */
//@{
#define LCD_HEIGHT 176			       /**< Display height in pixels. */
#define LCD_WIDTH 132			       /**< Display width in pixels. */
#define LCD_RIGHT (LCD_WIDTH - 1)	       /**< The rightmost pixel index. */
#define LCD_BOTTOM (LCD_HEIGHT - 1)	       /**< The bottommost pixel index. */
#define LCD_PIXELS (LCD_HEIGHT * LCD_WIDTH)    /**< Number of display pixels. */
//@}

/** @name Color values */
//@{
#define LCD_COLOR16_WHITE			0xFFFF
#define LCD_COLOR16_BLACK			0
#define LCD_COLOR16_RED				LCD_COLOR16_RGB(255, 0, 0)
#define LCD_COLOR16_GREEN			LCD_COLOR16_RGB(0, 255, 0)
#define LCD_COLOR16_BLUE			LCD_COLOR16_RGB(0, 0, 255)
#define LCD_COLOR16_GRAY			LCD_COLOR16_RGB(128, 128, 128)
//@}

// ------------------------- preprocessor macros -------------------------------

/** @name LCD_COLOR[16]_RGB() */
//@{
/** Gets a 16 bit color value from RGB components in range [0, 255]. */
#define LCD_COLOR16_RGB(r, g, b)		(((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3))
//@}

/** @name LCD_COLOR[16]() */
//@{
/** Gets a 16 bit color value from 8/16 bit color components. */
#define LCD_COLOR16(r, g, b)			(((uint16_t) r << 11) | ((uint16_t) g << 5) | b)
//@}

/** @name LCD_COLOR[16]_GET_[R/G/B]() */
//@{
/** Gets the R/G/B component of a 16 bit color value. */
#define LCD_COLOR16_GET_R(color)		((color & 0xF800) >> 11)
#define LCD_COLOR16_GET_G(color)		((color & 0x07E0) >>  5)
#define LCD_COLOR16_GET_B(color)		 (color & 0x001F)
//@}


/** @name LCD_LIMIT_[R/G/B/][16]() */
//@{
/** Limits the R/G/B component of a 16 bit color value to its maximum. */
#define LCD_LIMIT_R16(r)				((r > 31) ? 31 : r)
#define LCD_LIMIT_G16(g)				((g > 63) ? 63 : g)
#define LCD_LIMIT_B16(b)				((b > 31) ? 31 : b)
//@}

// ------------------------------ prototypes ----------------------------------


// ----------------------------------------------------------------------------
/** @name						Display control		 						  */
// ----------------------------------------------------------------------------
//@{
/** Initializes the display by sending a command sequence. */
void lcd_init();

/** Set the brightness of the LCD backlight. */
void lcd_set_backlight(uint8_t brightness);

/** Sets the scrolling offset for full screen scrolling. */
void lcd_set_scrolling(uint8_t scroll_offset);

/** Sets the scrolling offset for partial screen scrolling. */
void lcd_set_partial_scrolling(uint8_t start_offset, uint8_t size, uint8_t scroll_offset);
//@}

// -----------------------------------------------------------------------------
/** @name					Basic drawing functions 						  */
// -----------------------------------------------------------------------------
//@{

/** Draws a filled rectangle in a given bit mode. */
void lcd_fill_rectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, lcd_color_t color);

/** Fills the whole screen in a given bit mode. */
void lcd_fill_screen(lcd_color_t color);

/** Sets a pixel in 16 bit mode. */
void lcd_set_pixel16(uint8_t x, uint8_t y, lcd_color_t color16);

/** Draws a rectangle with border and filling in a given bit mode. */
void lcd_draw_rectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, lcd_color_t frame_color,
	                   const lcd_color_t *p_background_color, uint8_t frame_width);

/** Draws a line in a given bit mode. */
void lcd_draw_line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, lcd_color_t color);

//@}
// -----------------------------------------------------------------------------
/** @name					Font drawing functions 							  */
// -----------------------------------------------------------------------------
//@{

/** Draws a character. */
lcd_error_t lcd_draw_char(unsigned char char_index, uint8_t x, uint8_t y, lcd_color_t char_color,
			 const lcd_color_t *p_background_color, const uint8_t * p_font);

/** Draws text from a character string. */
lcd_error_t lcd_draw_text(const char *text, uint8_t x, uint8_t y, lcd_color_t text_color,
			  const lcd_color_t *p_background_color, const uint8_t * p_font,
			  int8_t char_spacing);

/** Draws text horizontally centered from a character string. */
lcd_error_t lcd_draw_centered_text(const char * text, uint8_t y, lcd_color_t text_color,
				 const lcd_color_t * p_background_color, const uint8_t * p_font,
				 int8_t char_spacing);

/** Gets the height of a font in program memmory. */
uint8_t lcd_get_font_height(const uint8_t * p_font);

/** Gets the width in pixels of a string for a given font and character spacing. */
uint16_t lcd_get_text_width(const char * text, const uint8_t * p_font, int8_t char_spacing);

//@}


// -----------------------------------------------------------------------------
/** @name					Image drawing functions 						  */
// -----------------------------------------------------------------------------
//@{

/**
 * Draws an image located in program memmory and optionally performs pixel
 * manipulation on it.
 */
lcd_error_t lcd_draw_image(const uint8_t * image_p, uint8_t x, uint8_t y, bool b_enable_transparency,
							lcd_image_manipulation_fp_t fp);

/** Gets the height of an image in program memmory. */
uint8_t lcd_get_image_height(const uint8_t * image_p);

/** Reads an image's header data into a lcd_imageHeader_t header struct. */
lcd_error_t lcd_read_image_header(lcd_image_header_t *p_header, const uint8_t * image_p);

//@}

// -----------------------------------------------------------------------------
/** @name					Miscellaneous functions 						  */
// -----------------------------------------------------------------------------
//@{

/** Extracts RGB color components depending on a bit mode. */
void lcd_get_color_components(lcd_color_t color, uint8_t *p_red, uint8_t *p_green,
							uint8_t *p_blue);

/** Gets a color value from RGB components depending on a bit mode. */
lcd_color_t lcd_get_color(uint8_t r, uint8_t g, uint8_t b);

//@}

#endif
