/*
 * Driver595138Basic.cpp
 *
 *  Created on: 2012-6-4
 *      Author: agu
 */

#include "Driver_595_138_Basic.h"

Driver_595_138_Basic::Driver_595_138_Basic(uint8_t pin_C_IN, uint8_t pin_C_OE,
		uint8_t pin_C_ST, uint8_t pin_C_SH, uint8_t pin_R_OE, uint8_t pin_R_A2,
		uint8_t pin_R_A1, uint8_t pin_R_A0) :
		_pin_595_DS(pin_C_IN), _pin_595_OE(pin_C_OE), _pin_595_ST(pin_C_ST), _pin_595_SH(
				pin_C_SH), _pin_138_OE(pin_R_OE), _pin_138_A2(pin_R_A2), _pin_138_A1(
				pin_R_A1), _pin_138_A0(pin_R_A0)

{
	pinMode(_pin_595_DS, OUTPUT);
	pinMode(_pin_595_OE, OUTPUT);
	pinMode(_pin_595_ST, OUTPUT);
	pinMode(_pin_595_SH, OUTPUT);

	pinMode(_pin_138_OE, OUTPUT);
	pinMode(_pin_138_A2, OUTPUT);
	pinMode(_pin_138_A1, OUTPUT);
	pinMode(_pin_138_A0, OUTPUT);
}

Driver_595_138_Basic::~Driver_595_138_Basic()
{

}

void Driver_595_138_Basic::setRow(byte r)
{
	digitalWrite(_pin_138_A0, r & 0x01);
	digitalWrite(_pin_138_A1, r & 0x02);
	digitalWrite(_pin_138_A2, r & 0x04);
}

void Driver_595_138_Basic::setCol(byte * p, byte length)
{
	for (byte i = length; i ; i--)
		this->shiftSend(~*(p++));

		//shiftOut(_pin_595_DS, _pin_595_SH, LSBFIRST, ~*(p++));
}

void Driver_595_138_Basic::shiftSend(byte c)
{
	for (byte i=0; i<8; i++)
	{
		digitalWrite(_pin_595_DS, bitRead(c, i));

		digitalWrite(_pin_595_SH, LOW);
		digitalWrite(_pin_595_SH, HIGH);
	}
}


