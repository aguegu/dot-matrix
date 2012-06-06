/*
	Driver_595_138.h
	Driver_595_138 Class for dot-matrix printing on matrix driven by 74HC595 and 74HC138
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

#ifndef DRIVER_595_138_H_
#define DRIVER_595_138_H_

#include "Driver_595_138_Basic.h"
#include "DotMatrix.h"

class Driver_595_138:public Driver_595_138_Basic
{
public:

	Driver_595_138(DotMatrix & dm, uint8_t pin_C_IN, uint8_t pin_C_OE, uint8_t pin_C_ST, uint8_t pin_C_SH, uint8_t pin_R_OE, uint8_t pin_R_A2, uint8_t pin_R_A1, uint8_t pin_R_A0, uint16_t speed = 0x400);
	virtual ~Driver_595_138();
	void display(byte times = 1) const;
	void setSpeed(uint16_t scan_span = 0x400);

protected:

	const uint8_t _pin_595_OE;
	const uint8_t _pin_595_ST;
	const uint8_t _pin_138_OE;

	const DotMatrix & _dm;

	byte _row_count;
	byte _bytes_per_row;
	uint16_t _scan_span;

	void setSize();
};

#endif /* DRIVER_595_138_H_ */
