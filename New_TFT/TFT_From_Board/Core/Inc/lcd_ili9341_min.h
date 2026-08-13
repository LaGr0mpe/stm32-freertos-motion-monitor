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
#include "stdbool.h"
////////////////////////////////////////////////////////////////////////////////

typedef enum {
    LCD_STATE_READY = 0,
    LCD_STATE_BUSY,
    LCD_STATE_ERROR
} LCD_State_t;

typedef struct
{
    const uint16_t *data;
    uint16_t width;
    uint16_t height;
} LCD_Image_t;
////////////////////////////////////////////////////////////////////////////////

void LCD_Init(void);
bool LCD_IsReady();
LCD_State_t LCD_GetState(void);
void LCD_FillRGB565(uint16_t color);
bool LCD_FillRGB565_DMA(uint16_t color);
bool LCD_FillRect_RGB565_DMA(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color);
bool LCD_DrawImage_RGB565_DMA(uint16_t x, uint16_t y, const LCD_Image_t *image);

#endif


