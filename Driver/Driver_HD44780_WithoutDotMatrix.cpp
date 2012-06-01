/*
 *	Driver_HD44780_WithoutDotMatrix.cpp
 *	Driver_HD44780 Class for dot-matrix printing on liquid crystal display driven by HD47780, namely 1602/1604
 *	Created on: 2012-02-29
 *	Updated on: 2012-05-14
 *
 *	library for Arduino for Dot Matrix Display, support driver by 74HC595 and 74HC138, ST7920, HD47780
 *	Author: Weihong Guan
 *	Blog: http://aguegu.net
 *	E-mail: weihong.guan@gmail.com
 *
 *	Code license: Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0)
 *	http://creativecommons.org/licenses/by-nc-sa/3.0/
 *	source host: https://github.com/aguegu/dot-matrix
 */

#include "Driver_HD44780_WithoutDotMatrix.h"

const uint8_t PROGMEM HD44780_NUMBER_FONT[] =
{
	0x07, 0x01, 0x07, 0x07, 0x04, 0x07,		// 0
	0x00, 0x07, 0x00, 0x00, 0x07, 0x00,		// 1
	0x01, 0x01, 0x07, 0x07, 0x05, 0x05,		// 2
	0x05, 0x05, 0x07, 0x04, 0x04, 0x07,		// 3
	0x07, 0x00, 0x07, 0x03, 0x02, 0x07,		// 4
	0x07, 0x05, 0x05, 0x04, 0x04, 0x07,		// 5
	0x07, 0x05, 0x05, 0x07, 0x04, 0x07,		// 6
	0x01, 0x01, 0x07, 0x00, 0x00, 0x07,		// 7
	0x07, 0x05, 0x07, 0x07, 0x04, 0x07,		// 8
	0x07, 0x01, 0x07, 0x05, 0x05, 0x07,		// 9
};

HD44780_WithoutDotMatrix::HD44780_WithoutDotMatrix(uint8_t pin_rs, uint8_t pin_en,
		uint8_t pin_d4, uint8_t pin_d5, uint8_t pin_d6, uint8_t pin_d7,
		byte col_count, byte row_count)
		: HD44780_Basic(pin_rs, pin_en, pin_d4, pin_d5, pin_d6, pin_d7, col_count, row_count)
{
	this->init();
}

HD44780_WithoutDotMatrix::~HD44780_WithoutDotMatrix()
{

}


void HD44780_WithoutDotMatrix::printBigNumber(byte address, byte num)
{
	byte indent = num * 6;
	for(byte i=0; i<3; i++)
	{
		this->setCache(address + i, pgm_read_byte_near(HD44780_NUMBER_FONT+ indent + i));
		this->setCache(address + _col_count + i, pgm_read_byte_near(HD44780_NUMBER_FONT+ indent + i + 3));
	}
}



