/*
 *	Driver_HD44780_WithoutDotMatrix.h
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

#ifndef DRIVER_HD44780_WITHOUT_DOTMATRIX_H_
#define DRIVER_HD44780_WITHOUT_DOTMATRIX_H_

#include "Driver_HD44780_Basic.h"

#ifdef PROGMEM
  #undef PROGMEM
  #define PROGMEM __attribute__((section(".progmem.data")))
#endif

class HD44780_WithoutDotMatrix:public HD44780_Basic
{
public:

	HD44780_WithoutDotMatrix(uint8_t pin_rs, uint8_t pin_en, uint8_t pin_d4, uint8_t pin_d5, uint8_t pin_d6, uint8_t pin_d7, byte col_count = 16, byte row_count = 2);
	virtual ~HD44780_WithoutDotMatrix();

	void printBigNumber(byte address, byte num);
};
#endif /* Driver_HD44780.h */
