/*
 * Driver_74HC595_SPI.cpp
 *
 *  Created on: 2012-7-16
 *      Author: Agu
 */

#include "Driver_74HC595_SPI.h"

Driver_74HC595_SPI::Driver_74HC595_SPI(SPIClass & spi, uint8_t pin_ST, uint8_t pin_OE)
: _spi(spi), _pin_ST(pin_ST), _pin_OE(pin_OE)
{
	pinMode(pin_ST, OUTPUT);
	pinMode(pin_OE, OUTPUT);

	_spi.setBitOrder(LSBFIRST);
	_spi.setDataMode(SPI_MODE2);
	_spi.begin();
}

Driver_74HC595_SPI::~Driver_74HC595_SPI()
{

}

void Driver_74HC595_SPI::shiftSendFromLSB(byte *p, byte length) const
{
	_spi.setBitOrder(LSBFIRST);
	while(length--)
		_spi.transfer(~*(p++));
}

void Driver_74HC595_SPI::shiftSendFromMSB(byte *p, byte length) const
{
	_spi.setBitOrder(MSBFIRST);
	while(length--)
		_spi.transfer(~*(p++));
}

void Driver_74HC595_SPI::shiftLatch() const
{
	pinSet(_pin_ST);
	pinClear(_pin_ST);
}

void Driver_74HC595_SPI::setOE(bool on) const
{
	pinWrite(_pin_OE, on);
}
