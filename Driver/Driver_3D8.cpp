/*
 * Driver3D8.cpp
 *
 *  Created on: 2012-6-14
 *      Author: agu
 */

#include "Driver_3D8.h"

Driver_3D8::Driver_3D8(DotMatrix & dm, uint8_t pin_62726_DS,
		uint8_t pin_62726_OE, uint8_t pin_62726_ST, uint8_t pin_62726_SH,
		uint8_t pin_138_A2, uint8_t pin_138_A1, uint8_t pin_138_A0,
		uint8_t pin_brightness, uint16_t scan_speed)
:Driver_1818_138(dm, pin_62726_DS, pin_62726_OE, pin_62726_ST, pin_62726_SH,
		pin_138_A2, pin_138_A1, pin_138_A0, pin_brightness, scan_speed)

{
	this->setMode();
}

Driver_3D8::~Driver_3D8()
{

}

void Driver_3D8::setMode(byte mode)
{
	switch (mode)
	{
	case 1:
		_setCol = &Driver_3D8::setColzxy;
		break;
	case 2:
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
	byte *p = _dm.output() + row;
	for (byte j = 0; j < _byte_per_row; j++) // z
	{
		for (byte i = 8; i--; )
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

void Driver_3D8::setColyzx(byte row) const
{
	byte * p = _dm.output();
	for (byte j = 0; j < _word_per_row; j++)
	{
		for (byte i = 8; i--; )
		{
			chip_col.setDS(bitRead(*(p++), row));
			chip_col.shiftClock();
		}

		p += _byte_per_row;

		for (byte i = 8; i--; )
		{
			chip_col.setDS(bitRead(*(--p), row));
			chip_col.shiftClock();
		}
		p += _byte_per_row;
	}
}

