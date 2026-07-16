/*
 * lcd_ili9341_min.h
 *
 *  Created on: 16 July 2026
 *      Author: ilya.voloshin
 */



#ifndef LCD_ILI9341_MIN_H
#define LCD_ILI9341_MIN_H

#include "main.h"
#include <stdint.h>

void LCD_Init(void);
void LCD_FillRGB565(uint16_t color);

#endif


