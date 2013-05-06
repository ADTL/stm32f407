/*
    created with FontEditor written by H. Reddmann
    HaReddmann at t-online dot de

    File Name           : droid_12x13.h
    Date                : 18.03.2010
    Font size in bytes  : 0x063A, 1594
    Font width          : 10
    Font height         : 13
    Font first char     : 0x21
    Font last char      : 0xFF
    Font bits per pixel : 1
    Font is compressed  : false

    The font data are defined as

    struct _FONT_ {
     // common shared fields
       uint16_t   font_Size_in_Bytes_over_all_included_Size_it_self;
       uint8_t    font_Width_in_Pixel_for_fixed_drawing;
       uint8_t    font_Height_in_Pixel_for_all_Characters;
       uint8_t    font_Bits_per_Pixels;
                    // if MSB are set then font is a compressed font
       uint8_t    font_First_Char;
       uint8_t    font_Last_Char;
       uint8_t    font_Char_Widths[font_Last_Char - font_First_Char +1];
                    // for each character the separate width in pixels,
                    // characters < 128 have an implicit virtual right empty row
                    // characters with font_Char_Widths[] == 0 are undefined

     // if compressed font then additional fields
       uint8_t    font_Byte_Padding;
                    // each Char in the table are aligned in size to this value
       uint8_t    font_RLE_Table[3];
                    // Run Length Encoding Table for Decompression
       uint8_t    font_Char_Size_in_Bytes[font_Last_Char - font_First_Char +1];
                    // for each char the size in (bytes / font_Byte_Padding) are stored,
                    // this get us the table to seek to the right beginning of each char
                    // in the font_data[]. Withhelp of font_Byte_Padding we ensure that
                    // one byte is suitable to store character sizes greater 255

     // for compressed and uncompressed fonts
       uint8_t    font_data[];
                    // bit field of all characters
    }
*/

#ifndef droid_12x13_H
#define droid_12x13_H

static uint8_t font[] = {
    0x06, 0x3A, 0x0A, 0x0D, 0x01, 0x21, 0xFF,
    0x01, 0x03, 0x07, 0x05, 0x08, 0x06, 0x01, 0x02, 0x02, 0x05, 0x05, 0x02, 0x03, 0x01, 0x04, 0x05, 
    0x03, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x01, 0x02, 0x04, 0x04, 0x04, 0x04, 0x08, 
    0x07, 0x05, 0x06, 0x06, 0x04, 0x04, 0x06, 0x06, 0x03, 0x02, 0x06, 0x04, 0x07, 0x05, 0x07, 0x04, 
    0x07, 0x05, 0x04, 0x05, 0x06, 0x07, 0x09, 0x06, 0x05, 0x06, 0x02, 0x04, 0x02, 0x07, 0x05, 0x02, 
    0x05, 0x05, 0x04, 0x05, 0x05, 0x04, 0x05, 0x05, 0x01, 0x01, 0x04, 0x01, 0x09, 0x05, 0x05, 0x05, 
    0x05, 0x03, 0x04, 0x03, 0x05, 0x05, 0x07, 0x05, 0x05, 0x04, 0x03, 0x01, 0x03, 0x04, 0x00, 0x00, 
    0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x03, 0x09, 0x00, 0x06, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x09, 0x00, 0x04, 0x07, 0x00, 
    0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 
    0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x07, 
    0x07, 0x07, 0x07, 0x07, 0x07, 0x08, 0x07, 0x05, 0x05, 0x05, 0x05, 0x03, 0x03, 0x03, 0x03, 0x07, 
    0x07, 0x08, 0x08, 0x08, 0x08, 0x08, 0x05, 0x08, 0x07, 0x07, 0x08, 0x07, 0x07, 0x05, 0x05, 0x05, 
    0x05, 0x05, 0x05, 0x05, 0x05, 0x09, 0x04, 0x05, 0x05, 0x05, 0x05, 0x02, 0x02, 0x03, 0x03, 0x05, 
    0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 
    0x7C, 0x83, 0x03, 0x00, 0x00, 0x0E, 0x00, 0x08, 0x20, 0x07, 0x3C, 0xE0, 0x1C, 0xF0, 0x80, 0x13, 
    0x40, 0x00, 0x18, 0x81, 0x24, 0xF8, 0x0F, 0x92, 0x40, 0x0C, 0x18, 0x80, 0x04, 0x60, 0x0C, 0x60, 
    0x00, 0x03, 0x18, 0x03, 0x90, 0x00, 0x0C, 0x80, 0x01, 0x4B, 0x90, 0x08, 0x32, 0x81, 0x19, 0x80, 
    0x04, 0x07, 0x80, 0x1F, 0x0C, 0x8C, 0x81, 0xC1, 0x0F, 0x08, 0x00, 0x05, 0x78, 0x00, 0x14, 0x80, 
    0x00, 0x40, 0x00, 0x08, 0xC0, 0x07, 0x20, 0x00, 0x04, 0x00, 0x10, 0x80, 0x01, 0x04, 0x80, 0x00, 
    0x10, 0x00, 0x0C, 0x80, 0x01, 0x0C, 0x60, 0x00, 0x03, 0xC0, 0x0F, 0x04, 0x82, 0x40, 0x10, 0x08, 
    0xFC, 0x80, 0x00, 0x08, 0x00, 0xFF, 0x40, 0x10, 0x04, 0x83, 0x50, 0x10, 0x09, 0x1C, 0x41, 0x20, 
    0x48, 0x04, 0x89, 0x20, 0x11, 0xD8, 0x01, 0x18, 0xC0, 0x02, 0x44, 0xC0, 0x3F, 0x00, 0x01, 0x4F, 
    0x20, 0x11, 0x24, 0x82, 0x44, 0x10, 0x07, 0xF8, 0x80, 0x22, 0x48, 0x04, 0x89, 0x00, 0x0E, 0x04, 
    0x80, 0x60, 0x10, 0x03, 0x1A, 0xC0, 0x00, 0xB0, 0x03, 0x89, 0x20, 0x11, 0x24, 0x02, 0x3B, 0xE0, 
    0x00, 0x22, 0x41, 0x24, 0x88, 0x02, 0x3E, 0x80, 0x19, 0x00, 0x08, 0xC6, 0x00, 0x01, 0x50, 0x00, 
    0x0A, 0x20, 0x02, 0x28, 0x00, 0x05, 0xA0, 0x00, 0x14, 0x40, 0x04, 0x50, 0x00, 0x0A, 0x80, 0x00, 
    0x01, 0x20, 0x1A, 0x24, 0x00, 0x03, 0xC0, 0x07, 0x04, 0x41, 0x4E, 0x28, 0x0A, 0x45, 0xA1, 0x2F, 
    0x08, 0x01, 0x1E, 0x00, 0x0C, 0x60, 0x80, 0x0B, 0x08, 0x01, 0x2E, 0x00, 0x06, 0x00, 0x83, 0x7F, 
    0x90, 0x08, 0x12, 0x41, 0x22, 0xB0, 0x03, 0x3C, 0x40, 0x08, 0x04, 0x82, 0x40, 0x10, 0x08, 0x02, 
    0xC1, 0x3F, 0x08, 0x04, 0x81, 0x20, 0x10, 0x08, 0x01, 0x1E, 0xF0, 0x0F, 0x12, 0x41, 0x22, 0x48, 
    0x04, 0xFF, 0x20, 0x01, 0x24, 0x80, 0x04, 0xC0, 0x03, 0x84, 0x40, 0x20, 0x88, 0x04, 0x91, 0x20, 
    0x1E, 0xFC, 0x03, 0x04, 0x80, 0x00, 0x10, 0x00, 0x02, 0xF8, 0x07, 0x81, 0xE0, 0x1F, 0x04, 0x02, 
    0x00, 0xF1, 0x1F, 0xFE, 0x01, 0x02, 0xA0, 0x00, 0x22, 0x20, 0x08, 0x00, 0x82, 0x7F, 0x00, 0x08, 
    0x00, 0x01, 0x20, 0xF8, 0x07, 0x06, 0x00, 0x03, 0x80, 0x01, 0x0C, 0x60, 0x00, 0xFE, 0xC1, 0x3F, 
    0x30, 0x00, 0x18, 0x00, 0x0C, 0xFC, 0x03, 0x1E, 0x20, 0x04, 0x02, 0x41, 0x20, 0x08, 0x04, 0x42, 
    0x80, 0x07, 0xFC, 0x83, 0x08, 0x10, 0x01, 0x1C, 0x00, 0x0F, 0x10, 0x02, 0x81, 0x20, 0x10, 0x04, 
    0x06, 0x21, 0xC1, 0x03, 0xFE, 0x41, 0x04, 0x88, 0x00, 0x31, 0xC0, 0x19, 0x18, 0x82, 0x44, 0x10, 
    0x09, 0xC2, 0x40, 0x00, 0x08, 0x00, 0xFF, 0x20, 0x00, 0x04, 0x80, 0x3F, 0x00, 0x08, 0x00, 0x01, 
    0x20, 0x00, 0x04, 0x7F, 0x60, 0x00, 0x70, 0x00, 0x30, 0x00, 0x08, 0xC0, 0x00, 0x07, 0x18, 0x00, 
    0x07, 0x00, 0x07, 0x00, 0x03, 0x1C, 0x70, 0x00, 0x70, 0x00, 0x30, 0xC0, 0x01, 0x07, 0x60, 0x18, 
    0x90, 0x00, 0x0C, 0x80, 0x01, 0x48, 0xC0, 0x30, 0x18, 0x00, 0x0C, 0x00, 0x1E, 0x30, 0x80, 0x01, 
    0x10, 0x0C, 0x42, 0x41, 0x24, 0x48, 0x04, 0x85, 0x60, 0x10, 0xFC, 0x8F, 0x00, 0x31, 0x00, 0x18, 
    0x00, 0x0C, 0x00, 0x06, 0x01, 0xE2, 0x7F, 0x20, 0x00, 0x02, 0x20, 0x00, 0x02, 0x80, 0x00, 0x20, 
    0x00, 0x08, 0x00, 0x40, 0x00, 0x08, 0x00, 0x01, 0x20, 0x00, 0x24, 0x00, 0x08, 0x00, 0x60, 0x80, 
    0x12, 0x50, 0x02, 0x4A, 0x80, 0x0F, 0xFE, 0x01, 0x21, 0x20, 0x04, 0x84, 0x00, 0x0F, 0xE0, 0x01, 
    0x42, 0x40, 0x08, 0x08, 0x01, 0x1E, 0x20, 0x04, 0x84, 0x80, 0x10, 0xFC, 0x03, 0x3C, 0x40, 0x09, 
    0x28, 0x01, 0x25, 0xC0, 0x04, 0x04, 0xE0, 0x1F, 0x14, 0x80, 0x00, 0x80, 0x31, 0xC8, 0x09, 0x29, 
    0xE1, 0x24, 0x04, 0xE3, 0x1F, 0x10, 0x00, 0x02, 0x40, 0x00, 0xF0, 0x41, 0x3F, 0xE8, 0x3F, 0xFF, 
    0x00, 0x02, 0xA0, 0x00, 0x62, 0xF0, 0x0F, 0xF8, 0x01, 0x01, 0x20, 0x00, 0x04, 0x00, 0x1F, 0x10, 
    0x00, 0x02, 0x40, 0x00, 0xF0, 0x01, 0x3F, 0x20, 0x00, 0x04, 0x80, 0x00, 0xE0, 0x03, 0x3C, 0x40, 
    0x08, 0x08, 0x01, 0x21, 0xC0, 0x03, 0xFC, 0x87, 0x10, 0x10, 0x02, 0x42, 0x80, 0x07, 0xF0, 0x00, 
    0x21, 0x20, 0x04, 0x84, 0x80, 0xFF, 0xF0, 0x03, 0x02, 0x40, 0x00, 0x10, 0x01, 0x25, 0x20, 0x05, 
    0x44, 0x80, 0x00, 0xF8, 0x01, 0x42, 0xC0, 0x07, 0x00, 0x01, 0x20, 0x00, 0x04, 0xFC, 0x80, 0x01, 
    0xC0, 0x01, 0x40, 0x00, 0x07, 0x18, 0x00, 0x0F, 0x00, 0x06, 0x30, 0x80, 0x01, 0xC0, 0x00, 0x60, 
    0xC0, 0x03, 0x88, 0x01, 0x0A, 0x80, 0x00, 0x28, 0x80, 0x18, 0x30, 0x10, 0x38, 0x02, 0x38, 0xE0, 
    0x00, 0x03, 0x20, 0x06, 0xA4, 0x80, 0x12, 0x30, 0x02, 0x08, 0xE0, 0x1E, 0x02, 0xC4, 0xFF, 0x09, 
    0x10, 0xDE, 0x01, 0x04, 0x40, 0x00, 0x04, 0x00, 0x01, 0x10, 0x00, 0x80, 0x00, 0x0C, 0x00, 0xC0, 
    0x10, 0x25, 0xC2, 0x48, 0x14, 0x06, 0x20, 0x00, 0x0A, 0x20, 0x02, 0x00, 0x80, 0x07, 0x08, 0x81, 
    0x40, 0x10, 0x08, 0xFE, 0x41, 0x22, 0x48, 0x04, 0x89, 0x00, 0x00, 0x04, 0xA3, 0x50, 0x98, 0x89, 
    0x0A, 0xC1, 0x20, 0x40, 0x84, 0x94, 0xA0, 0x14, 0x12, 0x01, 0x3C, 0x40, 0x08, 0x08, 0x01, 0x21, 
    0xC0, 0x03, 0x94, 0x80, 0x12, 0x50, 0x02, 0x4C, 0x40, 0x0C, 0x49, 0x41, 0x25, 0x64, 0x04, 0x01, 
    0xC0, 0x00, 0x21, 0x00, 0x78, 0x84, 0x00, 0x0C, 0x40, 0x00, 0x00, 0x00, 0xEC, 0x03, 0x00, 0x08, 
    0x80, 0x02, 0x20, 0x00, 0xF8, 0x0F, 0x20, 0x00, 0x04, 0x80, 0x80, 0x0F, 0x00, 0x06, 0x20, 0xC1, 
    0x22, 0x00, 0x04, 0x30, 0x80, 0x41, 0x2C, 0x50, 0x04, 0xB0, 0x00, 0x18, 0x00, 0x0C, 0x80, 0x01, 
    0x0C, 0x60, 0x81, 0x22, 0x88, 0x05, 0xC0, 0x00, 0x60, 0x00, 0x0C, 0x60, 0x20, 0x0B, 0x12, 0x81, 
    0x2C, 0x00, 0x06, 0x00, 0x03, 0x60, 0x08, 0x83, 0x58, 0xA0, 0x08, 0x64, 0x41, 0x30, 0x00, 0x18, 
    0x00, 0x03, 0x18, 0xE4, 0x02, 0x42, 0x90, 0x0B, 0x80, 0x01, 0xC0, 0x00, 0x18, 0xC0, 0x40, 0x16, 
    0x34, 0x02, 0x59, 0x00, 0x0C, 0x00, 0x06, 0xC0, 0x00, 0x06, 0xB0, 0x80, 0x11, 0xF0, 0x0F, 0x12, 
    0x41, 0x22, 0x48, 0x04, 0x00, 0x80, 0x07, 0x08, 0x81, 0x40, 0x12, 0x58, 0x02, 0x45, 0x20, 0x00, 
    0x00, 0xFF, 0x28, 0x11, 0x26, 0x82, 0x44, 0x00, 0x00, 0xFE, 0x41, 0x22, 0x4C, 0x44, 0x89, 0x00, 
    0x00, 0xF8, 0x43, 0x49, 0x24, 0x09, 0x25, 0x01, 0x00, 0xF8, 0x47, 0x89, 0x20, 0x11, 0x25, 0x22, 
    0x41, 0xE8, 0x0F, 0x04, 0x81, 0x20, 0xF4, 0x47, 0x82, 0x50, 0x10, 0xF9, 0x43, 0x41, 0x14, 0x08, 
    0xFE, 0x51, 0x20, 0x40, 0x00, 0xFF, 0x20, 0x11, 0x24, 0x82, 0x40, 0x20, 0x04, 0x78, 0x00, 0x00, 
    0xF8, 0xC7, 0x02, 0x88, 0x01, 0xC2, 0x20, 0x20, 0xF0, 0x0F, 0x00, 0x00, 0x0F, 0x10, 0x42, 0x81, 
    0x30, 0x10, 0x04, 0x02, 0x21, 0xC0, 0x03, 0x00, 0x00, 0x0F, 0x10, 0x02, 0x81, 0x30, 0x10, 0x05, 
    0x02, 0x21, 0xC0, 0x03, 0x00, 0x00, 0x0F, 0x10, 0x42, 0x81, 0x20, 0x10, 0x04, 0x22, 0x21, 0xC0, 
    0x03, 0x00, 0x00, 0x0F, 0x16, 0x42, 0x81, 0x30, 0x10, 0x06, 0x22, 0x21, 0xC0, 0x03, 0x00, 0x00, 
    0x0F, 0x10, 0x42, 0x81, 0x20, 0x10, 0x05, 0x02, 0x21, 0xC0, 0x03, 0x88, 0x00, 0x0A, 0x80, 0x00, 
    0x28, 0x80, 0x08, 0x00, 0x00, 0x1E, 0x20, 0x0C, 0x42, 0x41, 0x26, 0x28, 0x04, 0x43, 0x80, 0x07, 
    0x00, 0x80, 0x3F, 0x00, 0x88, 0x00, 0x21, 0x20, 0x00, 0x04, 0x7F, 0x00, 0x00, 0xFC, 0x01, 0x40, 
    0x00, 0x08, 0x01, 0x11, 0x20, 0xF8, 0x03, 0x00, 0xE0, 0x0F, 0x00, 0x42, 0x40, 0x04, 0x08, 0x01, 
    0x01, 0x20, 0xF8, 0x03, 0x00, 0xE0, 0x0F, 0x00, 0x22, 0x40, 0x00, 0x88, 0x00, 0xC1, 0x1F, 0x08, 
    0x00, 0x06, 0x00, 0x01, 0xC2, 0x23, 0x04, 0x60, 0x00, 0x02, 0x00, 0x00, 0xF8, 0x07, 0x22, 0x40, 
    0x04, 0x70, 0x00, 0xFF, 0x11, 0x00, 0x12, 0x81, 0x25, 0x00, 0x03, 0x64, 0x80, 0x12, 0x52, 0x82, 
    0x4A, 0x80, 0x0F, 0xC8, 0x00, 0x25, 0xA8, 0x84, 0x94, 0x00, 0x1F, 0x90, 0x81, 0x4A, 0x48, 0x09, 
    0x29, 0x41, 0x3E, 0x20, 0x83, 0x95, 0x90, 0x12, 0x54, 0x42, 0x7C, 0x40, 0x06, 0x28, 0x41, 0x25, 
    0xA0, 0x04, 0xF9, 0x80, 0x0C, 0x52, 0xA2, 0x4A, 0x48, 0x09, 0xF0, 0x01, 0x19, 0xA0, 0x04, 0x94, 
    0x80, 0x12, 0xE0, 0x01, 0x4A, 0x40, 0x09, 0x28, 0x01, 0x26, 0xC0, 0x23, 0x84, 0x85, 0x50, 0x10, 
    0x02, 0x3C, 0x48, 0x09, 0x2A, 0x01, 0x25, 0xC0, 0x04, 0x78, 0x80, 0x12, 0x54, 0x42, 0x4A, 0x80, 
    0x09, 0xF0, 0x40, 0x25, 0xA4, 0x04, 0x95, 0x00, 0x13, 0xE0, 0x81, 0x4A, 0x40, 0x09, 0x2A, 0x01, 
    0x26, 0x04, 0x00, 0xFD, 0xA0, 0x1F, 0x02, 0x80, 0x00, 0xC8, 0x0F, 0x02, 0x40, 0x00, 0xE0, 0x07, 
    0x01, 0x50, 0x0E, 0x24, 0x42, 0x45, 0xC0, 0x08, 0xF0, 0x00, 0x3F, 0x2C, 0x80, 0x04, 0xA0, 0x00, 
    0xE2, 0x03, 0x3C, 0x40, 0x08, 0x09, 0x41, 0x21, 0xC0, 0x03, 0x78, 0x80, 0x10, 0x14, 0x42, 0x42, 
    0x80, 0x07, 0xF0, 0x40, 0x21, 0x24, 0x84, 0x84, 0x20, 0x0F, 0xE0, 0xC1, 0x42, 0x48, 0x08, 0x0A, 
    0x21, 0x1E, 0xC0, 0x03, 0x85, 0x80, 0x10, 0x14, 0x02, 0x3C, 0x00, 0x01, 0x20, 0x00, 0x15, 0x80, 
    0x00, 0x10, 0x00, 0x1F, 0x10, 0x03, 0x5A, 0xC0, 0x08, 0xF8, 0x00, 0x1F, 0x04, 0x04, 0x81, 0x00, 
    0x10, 0xF0, 0x03, 0x3E, 0x00, 0x08, 0x02, 0x21, 0x20, 0xE0, 0x07, 0x7C, 0x20, 0x10, 0x02, 0x42, 
    0x40, 0xD0, 0x0F, 0xF8, 0x40, 0x20, 0x00, 0x04, 0x81, 0x80, 0x1F, 0x30, 0x10, 0x38, 0x12, 0x38, 
    0xE1, 0x00, 0x03, 0xF8, 0x3F, 0x84, 0x80, 0x10, 0x10, 0x02, 0x3C, 0xD0, 0x40, 0xE0, 0x08, 0xE0, 
    0x80, 0x03, 0x0D, 0x00
};

#endif
