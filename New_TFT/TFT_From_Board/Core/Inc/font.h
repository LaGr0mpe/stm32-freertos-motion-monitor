/*
 * font.h
 *
 *  Created on: 17 Aug 2026
 *      Author: ilya.voloshin
 */

#ifndef INC_FONT_H_
#define INC_FONT_H_

#include "lcd_ili9341_min.h"
#define FONT_WIDTH  8
#define FONT_HEIGHT 8
#define FONT_TABLE_SIZE 128

extern const LCD_Glyph_t * const Font_Default[FONT_TABLE_SIZE];

#endif /* INC_FONT_H_ */
