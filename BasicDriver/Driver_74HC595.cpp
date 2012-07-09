/*
 * Driver_74HC595.cpp
 *
 *  Created on: 2012-7-9
 *      Author: Agu
 */

#include "Driver_74HC595.h"

Driver_74HC595::Driver_74HC595(uint8_t pin_DS, uint8_t pin_SH, uint8_t pin_ST,
		uint8_t pin_OE) :
		_pin_DS(pin_DS), _pin_SH(pin_SH), _pin_ST(pin_ST), _pin_OE(pin_OE)
{
	pinMode(_pin_DS, OUTPUT);
	pinMode(_pin_SH, OUTPUT);
	pinMode(_pin_ST, OUTPUT);
	pinMode(_pin_OE, OUTPUT);
}

Driver_74HC595::~Driver_74HC595()
{
	// TODO Auto-generated destructor stub
}

void Driver_74HC595::shiftSendFromLSB(byte c) const
{
	byte i = BIT_IN_BYTE;

	while (i--)
	{
		pinWrite(_pin_DS, c & 0x01);
		pinClear(_pin_SH);
		pinSet(_pin_SH);
		c >>= 1;
	}
}

void Driver_74HC595::shiftSendFromMSB(byte c) const
{
	byte i = BIT_IN_BYTE;

	while (i--)
	{
		pinWrite(_pin_DS, c & 0x80);
		pinClear(_pin_SH);
		pinSet(_pin_SH);
		c <<= 1;
	}
}

void Driver_74HC595::shiftSendFromLSB(byte * p, byte length) const
{
	for (byte i = length; i; i--)
		this->shiftSendFromLSB(~*(p++));
}

void Driver_74HC595::shiftSendFromMSB(byte * p, byte length) const
{
	for (byte i = length; i; i--)
		this->shiftSendFromMSB(~*(p++));
}

void Driver_74HC595::shiftLatch() const
{
	pinClear(_pin_ST);
	pinSet(_pin_ST);
}

void Driver_74HC595::setOE(bool on) const
{
	pinWrite(_pin_OE, on);
}
