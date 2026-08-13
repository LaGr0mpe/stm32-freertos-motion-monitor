/*
 * images.h
 *
 *  Created on: 13 Aug 2026
 *      Author: ilya.voloshin
 */

#ifndef INC_IMAGES_H_
#define INC_IMAGES_H_

#include "lcd_ili9341_min.h"

extern void Image_GenerateBigTest(void);

extern const LCD_Image_t test_image;
extern const LCD_Image_t cross;
extern const LCD_Image_t chess;
extern const LCD_Image_t img_big_test;

#endif /* INC_IMAGES_H_ */
