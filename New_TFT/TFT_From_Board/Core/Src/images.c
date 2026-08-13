/*
 * images.c
 *
 *  Created on: 13 Aug 2026
 *      Author: ilya.voloshin
 */
#include <stdint.h>
#include "images.h"
#include "colors.h"

const uint16_t test_image_data[8 * 8] =
{
		WHITE_Color, WHITE_Color, BLACK_Color, WHITE_Color, WHITE_Color, BLACK_Color, BLUE_Color,  BLUE_Color,
		WHITE_Color, BLACK_Color, BLACK_Color, BLACK_Color, BLACK_Color, BLACK_Color, BLACK_Color,  BLUE_Color,
		BLACK_Color, BLACK_Color, BLACK_Color, BLACK_Color, BLACK_Color, BLACK_Color, BLACK_Color,  BLACK_Color,
		WHITE_Color, BLACK_Color, BLACK_Color, GREEN_Color, GREEN_Color, BLACK_Color, BLACK_Color,  WHITE_Color,
		WHITE_Color, BLACK_Color, BLACK_Color, GREEN_Color, GREEN_Color, BLACK_Color, BLACK_Color,  WHITE_Color,
		BLACK_Color, BLACK_Color, BLACK_Color, BLACK_Color, BLACK_Color, BLACK_Color, BLACK_Color,  BLACK_Color,
		RED_Color,   BLACK_Color, BLACK_Color, BLACK_Color, BLACK_Color, BLACK_Color, BLACK_Color,  YELLOW_Color,
		RED_Color,   RED_Color,   BLACK_Color, WHITE_Color, WHITE_Color, BLACK_Color, YELLOW_Color, YELLOW_Color
};

const LCD_Image_t test_image =
{
    .data = test_image_data,
    .width = 8,
    .height = 8
};

const uint16_t cross_data[8 * 8] =
{
    CYAN_Color,  BLACK_Color, BLACK_Color, BLACK_Color, BLACK_Color, BLACK_Color, BLACK_Color, CYAN_Color,
    BLACK_Color, CYAN_Color,  BLACK_Color, BLACK_Color, BLACK_Color, BLACK_Color, CYAN_Color,  BLACK_Color,
    BLACK_Color, BLACK_Color, CYAN_Color,  BLACK_Color, BLACK_Color, CYAN_Color,  BLACK_Color, BLACK_Color,
    BLACK_Color, BLACK_Color, BLACK_Color, CYAN_Color,  CYAN_Color,  BLACK_Color, BLACK_Color, BLACK_Color,
    BLACK_Color, BLACK_Color, BLACK_Color, CYAN_Color,  CYAN_Color,  BLACK_Color, BLACK_Color, BLACK_Color,
    BLACK_Color, BLACK_Color, CYAN_Color,  BLACK_Color, BLACK_Color, CYAN_Color,  BLACK_Color, BLACK_Color,
    BLACK_Color, CYAN_Color,  BLACK_Color, BLACK_Color, BLACK_Color, BLACK_Color, CYAN_Color,  BLACK_Color,
    CYAN_Color,  BLACK_Color, BLACK_Color, BLACK_Color, BLACK_Color, BLACK_Color, BLACK_Color, CYAN_Color
};

const LCD_Image_t cross =
{
    .data = cross_data,
    .width = 8,
    .height = 8
};

const uint16_t chess_data[8 * 8] =
{
    WHITE_Color, BLACK_Color, WHITE_Color, BLACK_Color, WHITE_Color, BLACK_Color, WHITE_Color, BLACK_Color,
    BLACK_Color, WHITE_Color, BLACK_Color, WHITE_Color, BLACK_Color, WHITE_Color, BLACK_Color, WHITE_Color,

    WHITE_Color, BLACK_Color, WHITE_Color, BLACK_Color, WHITE_Color, BLACK_Color, WHITE_Color, BLACK_Color,
    BLACK_Color, WHITE_Color, BLACK_Color, WHITE_Color, BLACK_Color, WHITE_Color, BLACK_Color, WHITE_Color,

    WHITE_Color, BLACK_Color, WHITE_Color, BLACK_Color, WHITE_Color, BLACK_Color, WHITE_Color, BLACK_Color,
    BLACK_Color, WHITE_Color, BLACK_Color, WHITE_Color, BLACK_Color, WHITE_Color, BLACK_Color, WHITE_Color,

    WHITE_Color, BLACK_Color, WHITE_Color, BLACK_Color, WHITE_Color, BLACK_Color, WHITE_Color, BLACK_Color,
    BLACK_Color, WHITE_Color, BLACK_Color, WHITE_Color, BLACK_Color, WHITE_Color, BLACK_Color, WHITE_Color
};

const LCD_Image_t chess =
{
    .data = chess_data,
    .width = 8,
    .height = 8
};

static uint16_t img_big_test_pixels[120 * 120];

void Image_GenerateBigTest(void)
{
    for (uint16_t y = 0; y < 120; y++)
    {
        for (uint16_t x = 0; x < 120; x++)
        {
            uint16_t color = BLACK_Color;

            /* Outer border */
            if (x == 0 || x == 119 || y == 0 || y == 119)
            {
                color = ORANGE_Color;
            }

            /* Inner border */
            else if (x == 4 || x == 115 || y == 4 || y == 115)
            {
                color = WHITE_Color;
            }

            /* Vertical & horizontal center */
            else if ((x >= 58 && x <= 61) ||
                     (y >= 58 && y <= 61))
            {
                color = GREEN_Color;
            }

            /* Main diagonal */
            else if ((x == y) ||
                     (x == y + 1) ||
                     (y == x + 1))
            {
                color = BLUE_Color;
            }

            /* Second diagonal */
            else if ((x + y == 119) ||
                     (x + y == 118) ||
                     (x + y == 120))
            {
                color = BLUE_Color;
            }

            /* Red square in the center */
            if (x >= 50 && x <= 69 &&
                y >= 50 && y <= 69)
            {
                color = RED_Color;
            }

            img_big_test_pixels[y * 120 + x] = color;
        }
    }
}

const LCD_Image_t img_big_test =
{
    .data = img_big_test_pixels,
    .width = 120,
    .height = 120
};



