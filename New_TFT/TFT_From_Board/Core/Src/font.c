/*
 * font.c
 *
 *  Created on: 17 Aug 2026
 *      Author: ilya.voloshin
 */
#include "font.h"


// !
static const uint8_t Letter_Exclam_data[8] =
{
		0b00011000,
		0b00011000,
		0b00011000,
		0b00011000,
		0b00011000,
		0b00000000,
		0b00011000,
		0b00011000
};

const LCD_Glyph_t Letter_Exclam =
{
	.bitmap = Letter_Exclam_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// 1
static const uint8_t Letter_One_data[8] =
{
		0b00011000,
		0b00011000,
		0b00111000,
		0b01011000,
		0b00011000,
		0b00011000,
		0b00111100,
		0b00111100
};

const LCD_Glyph_t Letter_One =
{
	.bitmap = Letter_One_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// 2
static const uint8_t Letter_Two_data[8] =
{
		0b00111000,
		0b01111100,
		0b11000110,
		0b11000110,
		0b00001100,
		0b00111000,
		0b01100000,
		0b11111111
};

const LCD_Glyph_t Letter_Two =
{
	.bitmap = Letter_Two_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// 3
static const uint8_t Letter_Three_data[8] =
{
		0b01111100,
		0b11000111,
		0b00000011,
		0b00001110,
		0b00001110,
		0b00000011,
		0b11000011,
		0b01111100
};

const LCD_Glyph_t Letter_Three =
{
	.bitmap = Letter_Three_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// A
static const uint8_t Letter_Big_A_data[8] =
{
		0b00111100,
		0b01100110,
		0b11000011,
		0b11000011,
		0b11111111,
		0b11000011,
		0b11000011,
		0b11000011
};

const LCD_Glyph_t Letter_Big_A =
{
	.bitmap = Letter_Big_A_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// H
static const uint8_t Letter_Big_H_data[8] =
{
		0b01100110,
		0b01100110,
		0b01100110,
		0b01111110,
		0b01111110,
		0b01100110,
		0b01100110,
		0b01100110
};

const LCD_Glyph_t Letter_Big_H =
{
	.bitmap = Letter_Big_H_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// W
static const uint8_t Letter_Big_W_data[8] =
{
		0b11000011,
		0b11000011,
		0b11000011,
		0b11000011,
		0b11011011,
		0b11111111,
		0b11100111,
		0b11000011
};

const LCD_Glyph_t Letter_Big_W =
{
	.bitmap = Letter_Big_W_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// d
static const uint8_t Letter_d_data[8] =
{
		0b00000000,
		0b00000000,
		0b00000100,
		0b00000100,
		0b00110100,
		0b01001100,
		0b01001100,
		0b00110100
};

const LCD_Glyph_t Letter_d =
{
	.bitmap = Letter_d_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// e
static const uint8_t Letter_e_data[8] =
{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00011000,
		0b00100100,
		0b00111100,
		0b00100000,
		0b00011100
};

const LCD_Glyph_t Letter_e =
{
	.bitmap = Letter_e_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// l
static const uint8_t Letter_l_data[8] =
{
		0b00000000,
		0b00000000,
		0b00010000,
		0b00010000,
		0b00010000,
		0b00010000,
		0b00011000,
		0b00010000
};

const LCD_Glyph_t Letter_l =
{
	.bitmap = Letter_l_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// o
static const uint8_t Letter_o_data[8] =
{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00011000,
		0b00100100,
		0b00100100,
		0b00100100,
		0b00011000
};

const LCD_Glyph_t Letter_o =
{
	.bitmap = Letter_o_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// r
static const uint8_t Letter_r_data[8] =
{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00101010,
		0b00110100,
		0b00100000,
		0b00100000,
		0b00100000
};

const LCD_Glyph_t Letter_r =
{
	.bitmap = Letter_r_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// space
static const uint8_t Letter_space_data[8] =
{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000
};

const LCD_Glyph_t Letter_space =
{
	.bitmap = Letter_space_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

const LCD_Glyph_t * const Font_Default[128] =
{
	['!'] = &Letter_Exclam,
	['1'] = &Letter_One,
	['2'] = &Letter_Two,
	['3'] = &Letter_Three,
    ['A'] = &Letter_Big_A,
	['H'] = &Letter_Big_H,
	['W'] = &Letter_Big_W,
	['d'] = &Letter_d,
	['e'] = &Letter_e,
	['l'] = &Letter_l,
	['o'] = &Letter_o,
	['r'] = &Letter_r,
	[' '] = &Letter_space


};

