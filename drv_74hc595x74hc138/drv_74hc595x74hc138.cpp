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

#include "drv_74hc595x74hc138.h"

Drv74hc595X74hc138::Drv74hc595X74hc138(DotMatrix & dm, uint8_t pin_C_IN,
		uint8_t pin_C_OE, uint8_t pin_C_ST, uint8_t pin_C_SH, uint8_t pin_R_OE,
		uint8_t pin_R_A2, uint8_t pin_R_A1, uint8_t pin_R_A0, uint16_t scan_span)
		:_dm(dm), chip_col(pin_C_IN, pin_C_SH, pin_C_ST, pin_C_OE), chip_row(pin_R_A2, pin_R_A1, pin_R_A0, pin_R_OE)
{
	this->setSize();
	this->setSpeed(scan_span);
}

Drv74hc595X74hc138::~Drv74hc595X74hc138()
{

}

void Drv74hc595X74hc138::display(byte times)
{
	chip_col.setShiftMode();

	while (times--)
	{
		byte *p = _dm.output();
		for (byte r = 0; r < _row_count; r++)
		{
			chip_col.shiftSendRev(p, _bytes_per_row);
			p += _bytes_per_row;

			chip_row.setOE(false);

			chip_col.shiftLatch();

			chip_row.setValue(r);

			chip_row.setOE(true);

			delayMicroseconds(_scan_span);
		}
	}
}

void Drv74hc595X74hc138::setSpeed(uint16_t scan_span)
{
	_scan_span = scan_span;
}

void Drv74hc595X74hc138::setSize()
{
	_row_count = _dm.countRow();
	_bytes_per_row = _dm.countBytePerRow();
}
