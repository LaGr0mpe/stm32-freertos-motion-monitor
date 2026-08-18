/*
 * lcd_ili9341_min.h
 *
 *  Created on: 16 July 2026
 *      Author: ilya.voloshin
 */



#ifndef LCD_ILI9341_MIN_H
#define LCD_ILI9341_MIN_H

#include "main.h"
#include "stdint.h"
#include "stdbool.h"
#include "stdlib.h"
////////////////////////////////////////////////////////////////////////////////

typedef enum {
    LCD_STATE_READY = 0,
    LCD_STATE_BUSY,
    LCD_STATE_ERROR
} LCD_State_t;

typedef enum
{
    LCD_IMAGE_RGB565,
    LCD_IMAGE_ARGB8888
} LCD_ImageFormat_t;

typedef struct
{
    const void *data;
    LCD_ImageFormat_t format;
    uint16_t width;
    uint16_t height;
} LCD_Image_t;

typedef struct
{
    uint8_t width;
    uint8_t height;
    uint8_t advance;
    const uint8_t *bitmap;
} LCD_Glyph_t;
////////////////////////////////////////////////////////////////////////////////

void LCD_Init(void);
bool LCD_IsReady();
LCD_State_t LCD_GetState(void);

bool LCD_FillRGB565_DMA(uint16_t color);
bool LCD_FillRect_RGB565_DMA(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color);
bool LCD_DrawImage_DMA(uint16_t x, uint16_t y, const LCD_Image_t *image);
bool LCD_DrawImagePart_DMA(uint16_t x_dist, uint16_t y_dist, uint16_t x_src, uint16_t y_src, uint16_t width, uint16_t height, const LCD_Image_t *image);
bool LCD_DrawPixel_RGB565(uint16_t x, uint16_t y, uint16_t color);
bool LCD_DrawLine_RGB565(uint16_t x_1, uint16_t y_1, uint16_t x_2, uint16_t y_2, uint16_t color);
bool LCD_Print(uint16_t x, uint16_t y, const char *text, const LCD_Glyph_t * const *font, uint16_t color);


#endif


