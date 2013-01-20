/*
	drv_74hc595x74hc138.h
	Drv74hc595X74hc138 Class for dot-matrix printing on matrix driven by 74HC595 and 74HC138
	Created on: 2012-01-25
	Updated on: 2012-06-05

	library for Arduino for Dot Matrix Display, support driver by 74HC595 and 74HC138, ST7920, HD47780
	Author: Weihong Guan
	Blog: http://aguegu.net
	E-mail: weihong.guan@gmail.com
	Code license: Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0)
	http://creativecommons.org/licenses/by-nc-sa/3.0/

	source host: https://github.com/aguegu/dot-matrix
 */

#ifndef DRIVER_74HC595_X_74HC138_H_
#define DRIVER_74HC595_X_74HC138_H_

#include "DotMatrix.h"
#include "Arduino.h"
#include "drv_74hc138.h"
#include "drv_74hc595.h"

class Drv74hc595X74hc138
{
public:

	Drv74hc595X74hc138(DotMatrix & dm, uint8_t pin_C_IN, uint8_t pin_C_OE, uint8_t pin_C_ST, uint8_t pin_C_SH, uint8_t pin_R_OE, uint8_t pin_R_A2, uint8_t pin_R_A1, uint8_t pin_R_A0, uint16_t speed = 0x400);
	virtual ~Drv74hc595X74hc138();
	void display(byte times = 1);
	void setSpeed(uint16_t scan_span = 0x400);

protected:

	const DotMatrix & _dm;

	Drv74hc595 chip_col;
	Drv74hc138 chip_row;

	byte _row_count;
	byte _bytes_per_row;
	uint16_t _scan_span;

	void setSize();
};

#endif /* DRIVER_74HC595_X_74HC138_H_ */
