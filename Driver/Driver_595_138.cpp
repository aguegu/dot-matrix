/*
	Driver_595_138.cpp
	Driver_595_138 Class for dot-matrix printing on matrix driven by 74HC595 and 74HC138
	Created on: 2012-01-15
	Updated on: 2012-06-05

	library for Arduino for Dot Matrix Display, support driver by 74HC595 and 74HC138, ST7920, HD47780
	Author: Weihong Guan
	Blog: http://aguegu.net
	E-mail: weihong.guan@gmail.com
	Code license: Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0)
	http://creativecommons.org/licenses/by-nc-sa/3.0/

	source host: https://github.com/aguegu/dot-matrix
 */

#include "Driver_595_138.h"

Driver_595_138::Driver_595_138(DotMatrix & dm, uint8_t pin_C_IN,
		uint8_t pin_C_OE, uint8_t pin_C_ST, uint8_t pin_C_SH, uint8_t pin_R_OE,
		uint8_t pin_R_A2, uint8_t pin_R_A1, uint8_t pin_R_A0, uint16_t scan_span)
	:Driver_595_138_Basic(pin_C_IN, pin_C_SH, pin_R_A2, pin_R_A1, pin_R_A0),
	 _pin_595_OE(pin_C_OE), _pin_595_ST(pin_C_ST), _pin_138_OE(pin_R_OE), _dm(dm)
{
	this->setSize();
	this->setSpeed(scan_span);

	pinMode(_pin_595_OE, OUTPUT);
	pinMode(_pin_595_ST, OUTPUT);
	pinMode(_pin_138_OE, OUTPUT);
}

Driver_595_138::~Driver_595_138()
{

}

void Driver_595_138::display(byte times) const
{
	while (times--)
	{
		byte *p = _dm.output();
		for (byte r = 0; r < _row_count; r++)
		{
			setColFromLSB(p, _bytes_per_row);

			p += _bytes_per_row;

			digitalWrite(_pin_138_OE, LOW);

			digitalWrite(_pin_595_ST, LOW);
			digitalWrite(_pin_595_ST, HIGH);

			setRow(r);

			digitalWrite(_pin_138_OE, HIGH);

			delayMicroseconds(_scan_span);
		}
	}
}

void Driver_595_138::setSpeed(uint16_t scan_span)
{
	_scan_span = scan_span;
}

void Driver_595_138::setSize()
{
	_row_count = _dm.countRow();
	_bytes_per_row = _dm.countBytePerRow();
}
