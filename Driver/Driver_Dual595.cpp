/*
 * DriverDual595.cpp
 *
 *  Created on: 2012-9-4
 *      Author: agu
 */

#include "Driver_Dual595.h"

Driver_Dual595::Driver_Dual595(DotMatrix dm, uint8_t pin_col, uint8_t pin_row, uint8_t pin_sh,
		uint8_t pin_st, uint8_t pin_oe) :
		_dm(dm), _pin_col(pin_col), _pin_row(pin_row), _pin_sh(pin_sh), _pin_st(pin_st), _pin_oe(
				pin_oe)
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
		for (byte c = 0; c < 24; c++)
		{
			//pinWrite(_pin_col, !((*p) & _BV(c%8)));
			pinWrite(_pin_col, bitRead((*p),4));
			//pinWrite(_pin_col, HIGH);
			pinWrite(_pin_row, c!=r);	// row on when it is LOW
			this->shiftClock();
		}
		this->shiftLatch();
		delay(0x100);
	}


}
