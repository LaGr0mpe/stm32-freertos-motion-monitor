/*
 * images.c
 *
 *  Created on: 13 Aug 2026
 *      Author: ilya.voloshin
 */
#include <stdint.h>
#include "images.h"
#include "colors.h"

const uint16_t test_image[8 * 8] =
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

