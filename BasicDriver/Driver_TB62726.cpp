/*
 * Driver_TB62726.cpp
 *
 *  Created on: 2012-7-10
 *      Author: Agu
 */

#include "Driver_TB62726.h"

Driver_TB62726::Driver_TB62726(uint8_t pin_din, uint8_t pin_clk,
		uint8_t pin_latch, uint8_t pin_oe, uint8_t pin_rext) :
		Driver_74HC595(pin_din, pin_clk, pin_latch, pin_oe), _pin_rext(pin_rext)
{

}

Driver_TB62726::~Driver_TB62726()
{

}

void Driver_TB62726::setBrightness(byte brg)
{
	analogWrite(_pin_rext, brg);
}

void Driver_TB62726::shiftSendFromLSB(byte *p, byte length) const
{
	for (byte i = length >> 1; i; i--)
	{
		this->Driver_74HC595::shiftSendFromLSB(*(p++));
		this->Driver_74HC595::shiftSendFromMSB(*(p++));
	}
}

void Driver_TB62726::shiftSendFromMSB(byte *p, byte length) const
{
	for (byte i = length >> 1; i; i--)
	{
		this->Driver_74HC595::shiftSendFromMSB(*(p++));
		this->Driver_74HC595::shiftSendFromLSB(*(p++));
	}
}
