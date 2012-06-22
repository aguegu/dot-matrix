/*
 * Driver595138Basic.cpp
 *
 *  Created on: 2012-6-4
 *      Author: agu
 */

#include "Driver_595_138_Basic.h"

Driver_595_138_Basic::Driver_595_138_Basic(uint8_t pin_C_IN, uint8_t pin_C_SH,
			uint8_t pin_R_A2, uint8_t pin_R_A1, uint8_t pin_R_A0)
	:_pin_595_DS(pin_C_IN), _pin_595_SH(pin_C_SH),
	 _pin_138_A2(pin_R_A2), _pin_138_A1(pin_R_A1), _pin_138_A0(pin_R_A0)
{
	pinMode(_pin_595_DS, OUTPUT);
	pinMode(_pin_595_SH, OUTPUT);

	pinMode(_pin_138_A2, OUTPUT);
	pinMode(_pin_138_A1, OUTPUT);
	pinMode(_pin_138_A0, OUTPUT);
}

Driver_595_138_Basic::~Driver_595_138_Basic()
{

}

void Driver_595_138_Basic::setRow(byte r) const
{
	pinWrite(_pin_138_A0, r & 0x01);
	pinWrite(_pin_138_A1, r & 0x02);
	pinWrite(_pin_138_A2, r & 0x04);
}

void Driver_595_138_Basic::setColFromLSB(byte * p, byte length) const
{
	for (byte i = length; i ; i--)
		this->shiftSendFromLSB(~*(p++));
}

void Driver_595_138_Basic::setColFromMSB(byte * p, byte length) const
{
	for (byte i = length; i ; i--)
		this->shiftSendFromMSB(~*(p++));
}

void Driver_595_138_Basic::shiftSendFromLSB(byte c) const
{
	byte i=8;

	while(i--)
	{
		pinWrite(_pin_595_DS, c & 0x01);
		pinClear(_pin_595_SH);
		pinSet(_pin_595_SH);
		c >>= 1;
	}
}

void Driver_595_138_Basic::shiftSendFromMSB(byte c) const
{
	byte i=8;

	while(i--)
	{
		pinWrite(_pin_595_DS, c & 0x80);
		pinClear(_pin_595_SH);
		pinSet(_pin_595_SH);
		c <<= 1;
	}
}


