/*
 * Driver_74HC138.cpp
 *
 *  Created on: 2012-7-9
 *      Author: Agu
 */

#include "Driver_74HC138.h"

Driver_74HC138::Driver_74HC138(uint8_t pin_A2, uint8_t pin_A1, uint8_t pin_A0,
		uint8_t pin_OE)
:_pin_A2(pin_A2),_pin_A1(pin_A1),_pin_A0(pin_A0),_pin_OE(pin_OE)
{
	pinMode(_pin_A2, OUTPUT);
	pinMode(_pin_A1, OUTPUT);
	pinMode(_pin_A0, OUTPUT);
	pinMode(_pin_OE, OUTPUT);
}

Driver_74HC138::~Driver_74HC138()
{

}

void Driver_74HC138::setValue(byte r) const
{
	pinWrite(_pin_A0, r & 0x01);
	pinWrite(_pin_A1, r & 0x02);
	pinWrite(_pin_A2, r & 0x04);
}

void Driver_74HC138::setOE(bool on) const
{
	pinWrite(_pin_OE, on);
}

