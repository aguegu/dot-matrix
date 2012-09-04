/*
 * DriverDual595.cpp
 *
 *  Created on: 2012-9-4
 *      Author: agu
 */

#include "Driver_Dual595.h"

Driver_Dual595::Driver_Dual595(uint8_t pin_col, uint8_t pin_row,
		uint8_t pin_sh, uint8_t pin_st, uint8_t pin_oe) :
		_dm(48, 12), _pin_col(pin_col), _pin_row(pin_row), _pin_sh(pin_sh), _pin_st(
				pin_st), _pin_oe(pin_oe)
{
	pinMode(_pin_col, OUTPUT);
	pinMode(_pin_row, OUTPUT);
	pinMode(_pin_sh, OUTPUT);
	pinMode(_pin_st, OUTPUT);
	pinMode(_pin_oe, OUTPUT);

	pinWrite(_pin_oe, LOW);


}

Driver_Dual595::~Driver_Dual595()
{

}

void Driver_Dual595::shiftLatch() const
{
	pinSet(_pin_st);
	pinClear(_pin_st);
}

void Driver_Dual595::shiftClock() const
{
	pinSet(_pin_sh);
	pinClear(_pin_sh);
}

void Driver_Dual595::display() const
{
	byte *p = _dm.output();

	for (byte r = 0; r < 24; r++)
	{
		byte *p2 = p + pgm_read_byte_near(DUAL595_ROW_ADDRESS+r);
		for (byte i = 0, j = 0; i < 3; i++)
		{
			byte tmp = *p2;
			for (byte c = 0; c < 8; c++, j++)
			{
				pinWrite(_pin_col, tmp&0x01);
				pinWrite(_pin_row, j!=r);
				// row on when it is LOW
				this->shiftClock();
				tmp >>= 1;
			}
			p2++;
		}
		this->shiftLatch();
		delayMicroseconds(0x100);
	}
}

DotMatrix & Driver_Dual595::getDotMatrix()
{
	return _dm;
}
