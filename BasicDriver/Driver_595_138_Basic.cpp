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
	digitalWrite(_pin_138_A0, r & 0x01);
	digitalWrite(_pin_138_A1, r & 0x02);
	digitalWrite(_pin_138_A2, r & 0x04);
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

inline void Driver_595_138_Basic::shiftSendFromLSB(byte c) const
{
	for (byte i=0; i<8; i++)
	{
		digitalWrite(_pin_595_DS, c & 0x01);
		c >>= 1;
		digitalWrite(_pin_595_SH, LOW);
		digitalWrite(_pin_595_SH, HIGH);
	}
}

inline void Driver_595_138_Basic::shiftSendFromMSB(byte c) const
{
	for (byte i=0; i<8; i++)
	{
		digitalWrite(_pin_595_DS, c & 0x80);
		c <<= 1;
		digitalWrite(_pin_595_SH, LOW);
		digitalWrite(_pin_595_SH, HIGH);
	}
}


