/*
 * 	Driver3D8.cpp
 *
 *	A3D8 (3D8S) 8x8x8 cubic led display driver
 *
 *  Created on: 2012-6-14
 *	Author: Weihong Guan
 *	Blog: http://aguegu.net
 *	E-mail: weihong.guan@gmail.com
 *
 *	Code license: Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0)
 *	http://creativecommons.org/licenses/by-nc-sa/3.0/
 *	source host: https://github.com/aguegu/dot-matrix
 */

#include "Driver_3D8.h"

Driver_3D8::Driver_3D8(DotMatrix & dm, uint8_t pin_din, uint8_t pin_clk,
		uint8_t pin_latch, uint8_t pin_en, uint8_t pin_rext, uint8_t pin_a2,
		uint8_t pin_a1, uint8_t pin_a0, uint16_t scan_speed) :
		Driver_1818_138(dm, pin_din, pin_clk, pin_latch, pin_en, pin_rext,
				pin_a2, pin_a1, pin_a0, 255, scan_speed)

{

	this->setMode();
}

Driver_3D8::~Driver_3D8()
{

}

void Driver_3D8::setMode(ScanMode mode)
{
	switch (mode)
	{
	case ZXY:
		_setCol = &Driver_3D8::setColzxy;
		break;
	case YZX:
		_setCol = &Driver_3D8::setColyzx;
		break;
	default:
		_setCol = &Driver_3D8::setColxyz;
		break;
	}
}

void Driver_3D8::setColxyz(byte row) const
{
	byte * p = _dm.output();
	p += _byte_per_row * row;

	chip_col.shiftSendFromLSB(p, _byte_per_row);
}

void Driver_3D8::display(byte times) const
{
	while (times--)
	{
		for (byte r = 0; r < _row_count; r++)
		{
			(this->*_setCol)(r);

			chip_col.setOE(true);
			chip_col.shiftLatch();
			chip_row.setValue(r);
			chip_col.setOE(false);

			delayMicroseconds(_scan_span);
		}
	}
}

void Driver_3D8::setColzxy(byte row) const
{
	byte * p = _dm.output();
	for (byte j = 0; j < _word_per_row; j++)
	{
		for (byte i = 8; i--;)
		{
			chip_col.setDS(bitRead(*(p++), row));
			chip_col.shiftClock();
		}

		p += _byte_per_row;

		for (byte i = 8; i--;)
		{
			chip_col.setDS(bitRead(*(--p), row));
			chip_col.shiftClock();
		}
		p += _byte_per_row;
	}
}

void Driver_3D8::setColyzx(byte row) const
{
	byte *p = _dm.output() + row;
	for (byte j = 0; j < _byte_per_row; j++) // z
	{
		for (byte i = 8; i--;)
		{
			if (j & 0x01)
				p -= _byte_per_row;
			chip_col.setDS(bitRead(*p, j));
			chip_col.shiftClock();
			if (!(j & 0x01))
				p += _byte_per_row;
		}
	}

}

