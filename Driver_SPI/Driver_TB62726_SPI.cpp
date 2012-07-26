/*
 * Driver_TB62726_SPI.cpp
 *
 *  Created on: 2012-7-16
 *      Author: Agu
 */

#include "Driver_TB62726_SPI.h"

Driver_TB62726_SPI::Driver_TB62726_SPI(SPIClass & spi, uint8_t pin_latch,
		uint8_t pin_oe, uint8_t pin_rext) :
		Driver_74HC595_SPI(spi, pin_latch, pin_oe), _pin_rext(pin_rext)
{

}

void Driver_TB62726_SPI::setBrightness(byte brg)
{
	analogWrite(_pin_rext, brg);
}

Driver_TB62726_SPI::~Driver_TB62726_SPI()
{

}

void Driver_TB62726_SPI::shiftSendCoupleFromLSB(byte *p, byte length)
{
	for (byte i = length >> 1; i--;)
	{
		_spi.setBitOrder(LSBFIRST);
		_spi.transfer(*(p++));
		_spi.setBitOrder(MSBFIRST);
		_spi.transfer(*(p++));
	}
}
