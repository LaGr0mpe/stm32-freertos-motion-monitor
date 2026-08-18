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

// "
static const uint8_t Letter_quot_data[8] =
{
		0b00110110,
		0b00110110,
		0b00010010,
		0b00100100,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000
};

const LCD_Glyph_t Letter_quot =
{
	.bitmap = Letter_quot_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// #
static const uint8_t Letter_hashtag_data[8] =
{
		0b00010010,
		0b00010010,
		0b11111111,
		0b00100100,
		0b00100100,
		0b11111111,
		0b01001000,
		0b01001000
};

const LCD_Glyph_t Letter_hashtag =
{
	.bitmap = Letter_hashtag_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// $
static const uint8_t Letter_dollar_data[8] =
{
		0b00011000,
		0b00111100,
		0b01100110,
		0b01100000,
		0b00111110,
		0b10000011,
		0b01111110,
		0b00011000
};

const LCD_Glyph_t Letter_dollar =
{
	.bitmap = Letter_dollar_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// %
static const uint8_t Letter_percent_data[8] =
{
		0b00100001,
		0b01010011,
		0b00100110,
		0b00001100,
		0b00011000,
		0b00110010,
		0b01100101,
		0b01000010
};

const LCD_Glyph_t Letter_percent =
{
	.bitmap = Letter_percent_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// &
static const uint8_t Letter_and_data[8] =
{
		0b00110000,
		0b01001000,
		0b01001000,
		0b00110010,
		0b00110100,
		0b01001000,
		0b01001100,
		0b00110010
};

const LCD_Glyph_t Letter_and =
{
	.bitmap = Letter_and_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// '
static const uint8_t Letter_apostrophe_data[8] =
{
		0b00000000,
		0b00011000,
		0b00011000,
		0b00001000,
		0b00010000,
		0b00000000,
		0b00000000,
		0b00000000
};

const LCD_Glyph_t Letter_apostrophe =
{
	.bitmap = Letter_apostrophe_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// (
static const uint8_t Letter_op_bracket_data[8] =
{
		0b00001000,
		0b00010000,
		0b00100000,
		0b00100000,
		0b00100000,
		0b00100000,
		0b00010000,
		0b00001000
};

const LCD_Glyph_t Letter_op_bracket =
{
	.bitmap = Letter_op_bracket_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// )
static const uint8_t Letter_cl_bracket_data[8] =
{
		0b00010000,
		0b00001000,
		0b00000100,
		0b00000100,
		0b00000100,
		0b00000100,
		0b00001000,
		0b00010000
};

const LCD_Glyph_t Letter_cl_bracket =
{
	.bitmap = Letter_cl_bracket_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// star
static const uint8_t Letter_star_data[8] =
{
		0b00000000,
		0b01010100,
		0b00111000,
		0b01111100,
		0b00111000,
		0b01010100,
		0b00000000,
		0b00000000
};

const LCD_Glyph_t Letter_star =
{
	.bitmap = Letter_star_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// +
static const uint8_t Letter_plus_data[8] =
{
		0b00000000,
		0b00000000,
		0b00010000,
		0b00010000,
		0b01111100,
		0b00010000,
		0b00010000,
		0b00000000
};

const LCD_Glyph_t Letter_plus =
{
	.bitmap = Letter_plus_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// ,
static const uint8_t Letter_comma_data[8] =
{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00011000,
		0b00011000,
		0b00001000,
		0b00010000
};

const LCD_Glyph_t Letter_comma =
{
	.bitmap = Letter_comma_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// -
static const uint8_t Letter_minus_data[8] =
{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00111100,
		0b00111100,
		0b00000000,
		0b00000000,
		0b00000000
};

const LCD_Glyph_t Letter_minnus =
{
	.bitmap = Letter_minus_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// .
static const uint8_t Letter_dot_data[8] =
{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00011000,
		0b00011000,
		0b00000000
};

const LCD_Glyph_t Letter_dot =
{
	.bitmap = Letter_dot_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// /
static const uint8_t Letter_slash_data[8] =
{
		0b00000001,
		0b00000011,
		0b00000110,
		0b00001100,
		0b00011000,
		0b00110000,
		0b01100000,
		0b11000000
};

const LCD_Glyph_t Letter_slash =
{
	.bitmap = Letter_slash_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// 0
static const uint8_t Letter_null_data[8] =
{
		0b00011000,
		0b00100100,
		0b00100100,
		0b00100100,
		0b00100100,
		0b00100100,
		0b00100100,
		0b00011000
};

const LCD_Glyph_t Letter_null =
{
	.bitmap = Letter_null_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// 1
static const uint8_t Letter_one_data[8] =
{
		0b00011000,
		0b00011000,
		0b00111000,
		0b01011000,
		0b00011000,
		0b00011000,
		0b01111110,
		0b01111110
};

const LCD_Glyph_t Letter_one =
{
	.bitmap = Letter_one_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// 2
static const uint8_t Letter_two_data[8] =
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

const LCD_Glyph_t Letter_two =
{
	.bitmap = Letter_two_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// 3
static const uint8_t Letter_three_data[8] =
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

const LCD_Glyph_t Letter_three =
{
	.bitmap = Letter_three_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// 4
static const uint8_t Letter_four_data[8] =
{
		0b00001000,
		0b00011000,
		0b00101000,
		0b01111110,
		0b00001000,
		0b00001000,
		0b00001000,
		0b00001000
};

const LCD_Glyph_t Letter_four =
{
	.bitmap = Letter_four_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// 5
static const uint8_t Letter_five_data[8] =
{
		0b00111100,
		0b00100000,
		0b00100000,
		0b00111100,
		0b00000110,
		0b01000010,
		0b01000110,
		0b00111100
};

const LCD_Glyph_t Letter_five =
{
	.bitmap = Letter_five_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// 6
static const uint8_t Letter_six_data[8] =
{
		0b00011100,
		0b00100010,
		0b00100000,
		0b00101100,
		0b00110010,
		0b00110010,
		0b00110010,
		0b00011100
};

const LCD_Glyph_t Letter_six =
{
	.bitmap = Letter_six_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// 7
static const uint8_t Letter_seven_data[8] =
{
		0b01111110,
		0b01000010,
		0b00000100,
		0b00111110,
		0b00000100,
		0b00001100,
		0b00001000,
		0b00001000
};

const LCD_Glyph_t Letter_seven =
{
	.bitmap = Letter_seven_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// 8
static const uint8_t Letter_eight_data[8] =
{
		0b00000000,
		0b00011000,
		0b00100100,
		0b00100100,
		0b00011000,
		0b00100100,
		0b00100100,
		0b00011000
};

const LCD_Glyph_t Letter_eight =
{
	.bitmap = Letter_eight_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// 9
static const uint8_t Letter_nine_data[8] =
{
		0b00011100,
		0b00100110,
		0b00100110,
		0b00100110,
		0b00011010,
		0b00000010,
		0b00100010,
		0b00011100
};

const LCD_Glyph_t Letter_nine =
{
	.bitmap = Letter_nine_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// :
static const uint8_t Letter_colon_data[8] =
{
		0b00000000,
		0b00011000,
		0b00011000,
		0b00000000,
		0b00000000,
		0b00011000,
		0b00011000,
		0b00000000
};

const LCD_Glyph_t Letter_colon =
{
	.bitmap = Letter_colon_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// ;
static const uint8_t Letter_semicolon_data[8] =
{
		0b00000000,
		0b00011000,
		0b00011000,
		0b00000000,
		0b00011000,
		0b00011000,
		0b00001000,
		0b00010000
};

const LCD_Glyph_t Letter_semicolon =
{
	.bitmap = Letter_semicolon_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// <
static const uint8_t Letter_smaller_data[8] =
{
		0b00000011,
		0b00001110,
		0b00111000,
		0b11100000,
		0b11100000,
		0b00111000,
		0b00001110,
		0b00000011
};

const LCD_Glyph_t Letter_smaller =
{
	.bitmap = Letter_smaller_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// =
static const uint8_t Letter_equal_data[8] =
{
		0b00000000,
		0b01111110,
		0b01111110,
		0b00000000,
		0b01111110,
		0b01111110,
		0b00000000,
		0b00000000
};

const LCD_Glyph_t Letter_equal =
{
	.bitmap = Letter_equal_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// >
static const uint8_t Letter_bigger_data[8] =
{
		0b11000000,
		0b01110000,
		0b00011100,
		0b00000111,
		0b00000111,
		0b00011100,
		0b01110000,
		0b11000000
};

const LCD_Glyph_t Letter_bigger =
{
	.bitmap = Letter_bigger_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// ?
static const uint8_t Letter_question_data[8] =
{
		0b00011000,
		0b00100100,
		0b00100010,
		0b00000010,
		0b00000100,
		0b00001000,
		0b00000000,
		0b00001000
};

const LCD_Glyph_t Letter_question =
{
	.bitmap = Letter_question_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// @
static const uint8_t Letter_dog_data[8] =
{
		0b00111100,
		0b01000010,
		0b10011001,
		0b10100101,
		0b10100101,
		0b10011110,
		0b01000000,
		0b00111110
};

const LCD_Glyph_t Letter_dog =
{
	.bitmap = Letter_dog_data,
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

// B
static const uint8_t Letter_Big_B_data[8] =
{
		0b01111100,
		0b01100011,
		0b01100011,
		0b01111100,
		0b01111100,
		0b01100011,
		0b01100011,
		0b01111100
};

const LCD_Glyph_t Letter_Big_B =
{
	.bitmap = Letter_Big_B_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// C
static const uint8_t Letter_Big_C_data[8] =
{
		0b00011100,
		0b00100010,
		0b01000000,
		0b01000000,
		0b01000000,
		0b01000000,
		0b00100010,
		0b00011100
};

const LCD_Glyph_t Letter_Big_C =
{
	.bitmap = Letter_Big_C_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// D
static const uint8_t Letter_Big_D_data[8] =
{
		0b01111100,
		0b01100110,
		0b01100011,
		0b01100011,
		0b01100011,
		0b01100011,
		0b01100110,
		0b01111100
};

const LCD_Glyph_t Letter_Big_D =
{
	.bitmap = Letter_Big_D_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// E
static const uint8_t Letter_Big_E_data[8] =
{
		0b01111110,
		0b01100000,
		0b01100000,
		0b01111000,
		0b01111000,
		0b01100000,
		0b01100000,
		0b01111110
};

const LCD_Glyph_t Letter_Big_E =
{
	.bitmap = Letter_Big_E_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// F
static const uint8_t Letter_Big_F_data[8] =
{
		0b01111110,
		0b01111110,
		0b01100000,
		0b01111000,
		0b01111000,
		0b01100000,
		0b01100000,
		0b01100000
};

const LCD_Glyph_t Letter_Big_F =
{
	.bitmap = Letter_Big_F_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// G
static const uint8_t Letter_Big_G_data[8] =
{
		0b00011100,
		0b00100010,
		0b01000001,
		0b01000000,
		0b01001111,
		0b01000001,
		0b00100011,
		0b00011101
};

const LCD_Glyph_t Letter_Big_G =
{
	.bitmap = Letter_Big_G_data,
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

// I
static const uint8_t Letter_Big_I_data[8] =
{
		0b01111110,
		0b01111110,
		0b00011000,
		0b00011000,
		0b00011000,
		0b00011000,
		0b01111110,
		0b01111110
};

const LCD_Glyph_t Letter_Big_I =
{
	.bitmap = Letter_Big_I_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// J
static const uint8_t Letter_Big_J_data[8] =
{
		0b00011110,
		0b00011110,
		0b00001100,
		0b00001100,
		0b01101100,
		0b01101100,
		0b00111100,
		0b00011000
};

const LCD_Glyph_t Letter_Big_J =
{
	.bitmap = Letter_Big_J_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// K
static const uint8_t Letter_Big_K_data[8] =
{
		0b01100110,
		0b01101100,
		0b01101000,
		0b01110000,
		0b01110000,
		0b01101000,
		0b01101100,
		0b01100110
};

const LCD_Glyph_t Letter_Big_K =
{
	.bitmap = Letter_Big_K_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// L
static const uint8_t Letter_Big_L_data[8] =
{
		0b01100000,
		0b01100000,
		0b01100000,
		0b01100000,
		0b01100000,
		0b01100110,
		0b01111110,
		0b01111110
};

const LCD_Glyph_t Letter_Big_L =
{
	.bitmap = Letter_Big_L_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// M
static const uint8_t Letter_Big_M_data[8] =
{
		0b11000011,
		0b11100111,
		0b11111111,
		0b11011011,
		0b11000011,
		0b11000011,
		0b11000011,
		0b11000011
};

const LCD_Glyph_t Letter_Big_M =
{
	.bitmap = Letter_Big_M_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// N
static const uint8_t Letter_Big_N_data[8] =
{
		0b11000011,
		0b11100011,
		0b11110011,
		0b11111011,
		0b11011111,
		0b11001111,
		0b11000111,
		0b11000011
};

const LCD_Glyph_t Letter_Big_N =
{
	.bitmap = Letter_Big_N_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// O
static const uint8_t Letter_Big_O_data[8] =
{
		0b00111100,
		0b01000010,
		0b01000010,
		0b01000010,
		0b01000010,
		0b01000010,
		0b01000010,
		0b00111100
};

const LCD_Glyph_t Letter_Big_O =
{
	.bitmap = Letter_Big_O_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// P
static const uint8_t Letter_Big_P_data[8] =
{
		0b01111110,
		0b01100011,
		0b01100011,
		0b01100011,
		0b01111100,
		0b01100000,
		0b01100000,
		0b01100000
};

const LCD_Glyph_t Letter_Big_P =
{
	.bitmap = Letter_Big_P_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// Q
static const uint8_t Letter_Big_Q_data[8] =
{
		0b00111100,
		0b01000010,
		0b11000011,
		0b11000011,
		0b11000011,
		0b11000111,
		0b01100110,
		0b00111101
};

const LCD_Glyph_t Letter_Big_Q =
{
	.bitmap = Letter_Big_Q_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// R
static const uint8_t Letter_Big_R_data[8] =
{
		0b01111110,
		0b01100011,
		0b01100011,
		0b01111110,
		0b01100100,
		0b01100110,
		0b01100110,
		0b01100011
};

const LCD_Glyph_t Letter_Big_R =
{
	.bitmap = Letter_Big_R_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// S
static const uint8_t Letter_Big_S_data[8] =
{
		0b00011000,
		0b01100100,
		0b01100110,
		0b00110000,
		0b00010000,
		0b11001100,
		0b01001100,
		0b00111000
};

const LCD_Glyph_t Letter_Big_S =
{
	.bitmap = Letter_Big_S_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// T
static const uint8_t Letter_Big_T_data[8] =
{
		0b11111111,
		0b11111111,
		0b10011001,
		0b00011000,
		0b00011000,
		0b00011000,
		0b00011000,
		0b00011000
};

const LCD_Glyph_t Letter_Big_T =
{
	.bitmap = Letter_Big_T_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// U
static const uint8_t Letter_Big_U_data[8] =
{
		0b11000011,
		0b11000011,
		0b11000011,
		0b11000011,
		0b11000011,
		0b11000011,
		0b01100110,
		0b00111110
};

const LCD_Glyph_t Letter_Big_U =
{
	.bitmap = Letter_Big_U_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// V
static const uint8_t Letter_Big_V_data[8] =
{
		0b10000001,
		0b10000001,
		0b11000011,
		0b01000010,
		0b01100110,
		0b00100100,
		0b00111100,
		0b00011000
};

const LCD_Glyph_t Letter_Big_V =
{
	.bitmap = Letter_Big_V_data,
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

// X
static const uint8_t Letter_Big_X_data[8] =
{
		0b11000011,
		0b01100110,
		0b00111100,
		0b00011000,
		0b00011000,
		0b00111100,
		0b01100110,
		0b11000011
};

const LCD_Glyph_t Letter_Big_X =
{
	.bitmap = Letter_Big_X_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// Y
static const uint8_t Letter_Big_Y_data[8] =
{
		0b11000011,
		0b01100110,
		0b00111100,
		0b00011000,
		0b00011000,
		0b00011000,
		0b00011000,
		0b00011000
};

const LCD_Glyph_t Letter_Big_Y =
{
	.bitmap = Letter_Big_Y_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// Z
static const uint8_t Letter_Big_Z_data[8] =
{
		0b11111111,
		0b11111111,
		0b00001110,
		0b00011100,
		0b00111000,
		0b01110000,
		0b11111111,
		0b11111111
};

const LCD_Glyph_t Letter_Big_Z =
{
	.bitmap = Letter_Big_Z_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// [
static const uint8_t Letter_op_sq_bracket_data[8] =
{
		0b00111100,
		0b00100000,
		0b00100000,
		0b00100000,
		0b00100000,
		0b00100000,
		0b00100000,
		0b00111100
};

const LCD_Glyph_t Letter_op_sq_bracket =
{
	.bitmap = Letter_op_sq_bracket_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// \ //
static const uint8_t Letter_rev_slash_data[8] =
{
		0b11000000,
		0b01100000,
		0b00110000,
		0b00011000,
		0b00001100,
		0b00000110,
		0b00000011,
		0b00000001
};

const LCD_Glyph_t Letter_rev_slash =
{
	.bitmap = Letter_rev_slash_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// ]
static const uint8_t Letter_cl_sq_bracket_data[8] =
{
		0b00111100,
		0b00000100,
		0b00000100,
		0b00000100,
		0b00000100,
		0b00000100,
		0b00000100,
		0b00111100
};

const LCD_Glyph_t Letter_cl_sq_braket =
{
	.bitmap = Letter_cl_sq_bracket_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

//
static const uint8_t Letter__data[8] =
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

const LCD_Glyph_t Letter_ =
{
	.bitmap = Letter__data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// ^
static const uint8_t Letter_caret_data[8] =
{
		0b00010000,
		0b00101000,
		0b01000100,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000
};

const LCD_Glyph_t Letter_caret =
{
	.bitmap = Letter_caret_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

//  —
static const uint8_t Letter_dash_data[8] =
{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b01111110,
		0b01111110
};

const LCD_Glyph_t Letter_dash =
{
	.bitmap = Letter_dash_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// `
static const uint8_t Letter_backquote_data[8] =
{
		0b00011000,
		0b00011000,
		0b00000100,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000
};

const LCD_Glyph_t Letter_backquote =
{
	.bitmap = Letter_backquote_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// a
static const uint8_t Letter_a_data[8] =
{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00011010,
		0b00100110,
		0b00100010,
		0b00100110,
		0b00011010
};

const LCD_Glyph_t Letter_a =
{
	.bitmap = Letter_a_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

//
static const uint8_t Letter_b_data[8] =
{
		0b00000000,
		0b00100000,
		0b00100000,
		0b00100000,
		0b00111000,
		0b00100100,
		0b00100100,
		0b00111000
};

const LCD_Glyph_t Letter_b =
{
	.bitmap = Letter_b_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

//
static const uint8_t Letter_c_data[8] =
{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00011000,
		0b00100100,
		0b00100000,
		0b00100100,
		0b00011000
};

const LCD_Glyph_t Letter_c =
{
	.bitmap = Letter_c_data,
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

//
static const uint8_t Letter_f_data[8] =
{
		0b00000000,
		0b00011000,
		0b00100100,
		0b00100000,
		0b01111000,
		0b00100000,
		0b00100000,
		0b00100000
};

const LCD_Glyph_t Letter_f =
{
	.bitmap = Letter_f_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// g
static const uint8_t Letter_g_data[8] =
{
		0b00000000,
		0b00110100,
		0b01001100,
		0b01001100,
		0b00110100,
		0b00000100,
		0b01000100,
		0b00111000
};

const LCD_Glyph_t Letter_g =
{
	.bitmap = Letter_g_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

//
static const uint8_t Letter_h_data[8] =
{
		0b00000000,
		0b00100000,
		0b00100000,
		0b00101000,
		0b00110100,
		0b00100100,
		0b00100100,
		0b00100100
};

const LCD_Glyph_t Letter_h =
{
	.bitmap = Letter_h_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// i
static const uint8_t Letter_i_data[8] =
{
		0b00000000,
		0b00010000,
		0b00000000,
		0b00010000,
		0b00010000,
		0b00010000,
		0b00010100,
		0b00001000
};

const LCD_Glyph_t Letter_i =
{
	.bitmap = Letter_i_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

//
static const uint8_t Letter_j_data[8] =
{
		0b00000100,
		0b00000000,
		0b00000100,
		0b00000100,
		0b00000100,
		0b00100100,
		0b00100100,
		0b00011000
};

const LCD_Glyph_t Letter_j =
{
	.bitmap = Letter_j_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

//
static const uint8_t Letter_k_data[8] =
{
		0b00100000,
		0b00100000,
		0b00100100,
		0b00101000,
		0b00110000,
		0b00110000,
		0b00101000,
		0b00100100
};

const LCD_Glyph_t Letter_k =
{
	.bitmap = Letter_k_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// l
static const uint8_t Letter_l_data[8] =
{
		0b00000000,
		0b00010000,
		0b00010000,
		0b00010000,
		0b00010000,
		0b00010100,
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

// m
static const uint8_t Letter_m_data[8] =
{
		0b00000000,
		0b00000000,
		0b01010100,
		0b01101010,
		0b01001010,
		0b01001010,
		0b01001010,
		0b01001010
};

const LCD_Glyph_t Letter_m =
{
	.bitmap = Letter_m_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// n
static const uint8_t Letter_n_data[8] =
{
		0b00000000,
		0b00000000,
		0b00100100,
		0b00110010,
		0b00100010,
		0b00100010,
		0b00100010,
		0b00100010
};

const LCD_Glyph_t Letter_n =
{
	.bitmap = Letter_n_data,
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

//
static const uint8_t Letter_p_data[8] =
{
		0b00000000,
		0b00011000,
		0b00100100,
		0b00100100,
		0b00111000,
		0b00100000,
		0b00100000,
		0b00100000
};

const LCD_Glyph_t Letter_p =
{
	.bitmap = Letter_p_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// q
static const uint8_t Letter_q_data[8] =
{
		0b00000000,
		0b00011000,
		0b00100100,
		0b00100100,
		0b00011000,
		0b00001010,
		0b00001100,
		0b00001000
};

const LCD_Glyph_t Letter_q =
{
	.bitmap = Letter_q_data,
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

// s
static const uint8_t Letter_s_data[8] =
{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000100,
		0b00001010,
		0b00001000,
		0b00101000,
		0b00010000
};

const LCD_Glyph_t Letter_s =
{
	.bitmap = Letter_s_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// t
static const uint8_t Letter_t_data[8] =
{
		0b00000000,
		0b00010000,
		0b00010000,
		0b00010000,
		0b00111100,
		0b00010000,
		0b00010100,
		0b00001000
};

const LCD_Glyph_t Letter_t =
{
	.bitmap = Letter_t_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// u
static const uint8_t Letter_u_data[8] =
{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00100010,
		0b00100010,
		0b00100010,
		0b00100110,
		0b00011010
};

const LCD_Glyph_t Letter_u =
{
	.bitmap = Letter_u_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// v
static const uint8_t Letter_v_data[8] =
{
		0b00000000,
		0b00000000,
		0b00000000,
		0b01000100,
		0b01000100,
		0b00101000,
		0b00101000,
		0b00010000
};

const LCD_Glyph_t Letter_v =
{
	.bitmap = Letter_v_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// w
static const uint8_t Letter_w_data[8] =
{
		0b00000000,
		0b00000000,
		0b00000000,
		0b10000010,
		0b10000010,
		0b01010100,
		0b01010100,
		0b00101000
};

const LCD_Glyph_t Letter_w =
{
	.bitmap = Letter_w_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

//
static const uint8_t Letter_x_data[8] =
{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00100010,
		0b00010100,
		0b00001000,
		0b00010100,
		0b00100010
};

const LCD_Glyph_t Letter_x =
{
	.bitmap = Letter_x_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// y
static const uint8_t Letter_y_data[8] =
{
		0b00100100,
		0b00100100,
		0b00011000,
		0b00001000,
		0b00001100,
		0b00011000,
		0b00101000,
		0b00110000
};

const LCD_Glyph_t Letter_y =
{
	.bitmap = Letter_y_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

//
static const uint8_t Letter_z_data[8] =
{
		0b00000000,
		0b00000000,
		0b00000000,
		0b01111100,
		0b00001000,
		0b00010000,
		0b00100000,
		0b01111100
};

const LCD_Glyph_t Letter_z =
{
	.bitmap = Letter_z_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// {
static const uint8_t Letter_op_curl_bracket_data[8] =
{
		0b00011000,
		0b00110000,
		0b00100000,
		0b11000000,
		0b11000000,
		0b00100000,
		0b00110000,
		0b00011000
};

const LCD_Glyph_t Letter_op_curl_bracket =
{
	.bitmap = Letter_op_curl_bracket_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// |
static const uint8_t Letter_pipe_data[8] =
{
		0b00010000,
		0b00010000,
		0b00010000,
		0b00010000,
		0b00010000,
		0b00010000,
		0b00010000,
		0b00010000
};

const LCD_Glyph_t Letter_pipe =
{
	.bitmap = Letter_pipe_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// }
static const uint8_t Letter_cl_curl_bracket_data[8] =
{
		0b00011000,
		0b00001100,
		0b00000100,
		0b00000011,
		0b00000011,
		0b00000100,
		0b00001100,
		0b00011000
};

const LCD_Glyph_t Letter_cl_curl_bracket =
{
	.bitmap = Letter_cl_curl_bracket_data,
	.width = 8,
	.height = 8,
	.advance = 10
};

// ~
static const uint8_t Letter_tilde_data[8] =
{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00110010,
		0b01001100,
		0b00000000,
		0b00000000,
		0b00000000
};

const LCD_Glyph_t Letter_tilde =
{
	.bitmap = Letter_tilde_data,
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

const LCD_Glyph_t * const Font_Default[FONT_TABLE_SIZE] =
{
    [' '] = &Letter_space,
    ['!'] = &Letter_Exclam,
    ['"'] = &Letter_quot,
    ['#'] = &Letter_hashtag,
    ['$'] = &Letter_dollar,
    ['%'] = &Letter_percent,
    ['&'] = &Letter_and,
    ['\''] = &Letter_apostrophe,
    ['('] = &Letter_op_bracket,
    [')'] = &Letter_cl_bracket,
    ['*'] = &Letter_star,
    ['+'] = &Letter_plus,
    [','] = &Letter_comma,
    ['-'] = &Letter_minnus,
    ['.'] = &Letter_dot,
    ['/'] = &Letter_slash,

    ['0'] = &Letter_null,
    ['1'] = &Letter_one,
    ['2'] = &Letter_two,
    ['3'] = &Letter_three,
    ['4'] = &Letter_four,
    ['5'] = &Letter_five,
    ['6'] = &Letter_six,
    ['7'] = &Letter_seven,
    ['8'] = &Letter_eight,
    ['9'] = &Letter_nine,

    [':'] = &Letter_colon,
    [';'] = &Letter_semicolon,
    ['<'] = &Letter_smaller,
    ['='] = &Letter_equal,
    ['>'] = &Letter_bigger,
    ['?'] = &Letter_question,
    ['@'] = &Letter_dog,

    ['A'] = &Letter_Big_A,
    ['B'] = &Letter_Big_B,
    ['C'] = &Letter_Big_C,
    ['D'] = &Letter_Big_D,
    ['E'] = &Letter_Big_E,
    ['F'] = &Letter_Big_F,
    ['G'] = &Letter_Big_G,
    ['H'] = &Letter_Big_H,
    ['I'] = &Letter_Big_I,
    ['J'] = &Letter_Big_J,
    ['K'] = &Letter_Big_K,
    ['L'] = &Letter_Big_L,
    ['M'] = &Letter_Big_M,
    ['N'] = &Letter_Big_N,
    ['O'] = &Letter_Big_O,
    ['P'] = &Letter_Big_P,
    ['Q'] = &Letter_Big_Q,
    ['R'] = &Letter_Big_R,
    ['S'] = &Letter_Big_S,
    ['T'] = &Letter_Big_T,
    ['U'] = &Letter_Big_U,
    ['V'] = &Letter_Big_V,
    ['W'] = &Letter_Big_W,
    ['X'] = &Letter_Big_X,
    ['Y'] = &Letter_Big_Y,
    ['Z'] = &Letter_Big_Z,

    ['['] = &Letter_op_sq_bracket,
    ['\\'] = &Letter_rev_slash,
    [']'] = &Letter_cl_sq_braket,
    ['^'] = &Letter_caret,
    ['_'] = &Letter_dash,
    ['`'] = &Letter_backquote,

    ['a'] = &Letter_a,
    ['b'] = &Letter_b,
    ['c'] = &Letter_c,
    ['d'] = &Letter_d,
    ['e'] = &Letter_e,
    ['f'] = &Letter_f,
    ['g'] = &Letter_g,
    ['h'] = &Letter_h,
    ['i'] = &Letter_i,
    ['j'] = &Letter_j,
    ['k'] = &Letter_k,
    ['l'] = &Letter_l,
    ['m'] = &Letter_m,
    ['n'] = &Letter_n,
    ['o'] = &Letter_o,
    ['p'] = &Letter_p,
    ['q'] = &Letter_q,
    ['r'] = &Letter_r,
    ['s'] = &Letter_s,
    ['t'] = &Letter_t,
    ['u'] = &Letter_u,
    ['v'] = &Letter_v,
    ['w'] = &Letter_w,
    ['x'] = &Letter_x,
    ['y'] = &Letter_y,
    ['z'] = &Letter_z,

    ['{'] = &Letter_op_curl_bracket,
    ['|'] = &Letter_pipe,
    ['}'] = &Letter_cl_curl_bracket,
    ['~'] = &Letter_tilde
};

