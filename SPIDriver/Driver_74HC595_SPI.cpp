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

	this->setShiftSendMode();
	_spi.setDataMode(SPI_MODE0);
	_spi.setClockDivider(SPI_CLOCK_DIV2);
	_spi.begin();
}

Driver_74HC595_SPI::~Driver_74HC595_SPI()
{

}

void Driver_74HC595_SPI::setShiftSendMode(byte mode)
{
	_spi.setBitOrder(mode);
}


void Driver_74HC595_SPI::shiftSend(byte *p, byte length) const
{
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
