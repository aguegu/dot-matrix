/*
 *	Driver_PCD8544_WithoutDotMatrix.cpp
 *	Driver_PCD8544 Class for dot-matrix printing on liquid crystal display driven by HD47780, namely 1602/1604
 *	Created on: 2012-05-30
 *
 *	library for Arduino for Dot Matrix Display, support driver by 74HC595 and 74HC138, ST7920, HD47780
 *	Author: Weihong Guan
 *	Blog: http://aguegu.net
 *	E-mail: weihong.guan@gmail.com
 *
 *	Code license: Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0)
 *	http://creativecommons.org/licenses/by-nc-sa/3.0/
 *	source host: https://github.com/aguegu/dot-matrix
 */

#include "Driver_PCD8544_Basic.h"

Driver_PCD8544_Basic::Driver_PCD8544_Basic(uint8_t pin_sce, uint8_t pin_rst,
		uint8_t pin_dc, uint8_t pin_din, uint8_t pin_sclk) :
		_pin_sce(pin_sce), _pin_rst(pin_rst), _pin_dc(pin_dc), _pin_din(
				pin_din), _pin_sclk(pin_sclk)
{
	// TODO Auto-generated constructor stub
	pinMode(_pin_sce, OUTPUT);
	pinMode(_pin_rst, OUTPUT);
	pinMode(_pin_dc, OUTPUT);
	pinMode(_pin_din, OUTPUT);
	pinMode(_pin_sclk, OUTPUT);
}

Driver_PCD8544_Basic::~Driver_PCD8544_Basic()
{
	// TODO Auto-generated destructor stub
}

void Driver_PCD8544_Basic::transmit(byte c, bool b)
{
	pinClear(_pin_sce);

	pinWrite(_pin_dc, b);

	for (byte i = 8; i--;)
	{
		pinWrite(_pin_din, bitRead(c, 7));
		pinClear(_pin_sclk);
		pinSet(_pin_sclk);
		c <<= 1;
	}
	pinSet(_pin_sce);
}

void Driver_PCD8544_Basic::init()
{
	digitalWrite(_pin_sce, LOW);
	digitalWrite(_pin_rst, LOW);
	delay(0x40);
	digitalWrite(_pin_rst, HIGH);
	digitalWrite(_pin_sce, HIGH);

	this->configureHardware();
	this->configureDisplay();
}

void Driver_PCD8544_Basic::configureFunction(bool active,
		bool vertical_addressing, bool extend_command)
{
	this->transmit(
			0x20 | (active ? 0x00 : 0x04) | (vertical_addressing ? 0x02 : 0x00)
					| (extend_command ? 0x01 : 0x00), COMMAND);
}

void Driver_PCD8544_Basic::configureHardware(byte tc, byte bias, byte vop)
{
	this->configureFunction(true, true, true);
	this->transmit(0x04 | (tc & 0x03), COMMAND);
	this->transmit(0x10 | (bias & 0x07), COMMAND);
	this->transmit(0x80 | (vop & 0x7f), COMMAND);
	this->configureFunction(true, true, false);
}

void Driver_PCD8544_Basic::configureDisplay(bool display_on, bool reverse)
{
	this->transmit(
			0x08 | (display_on ? 0x04 : 0x00) | (reverse ? 0x01 : 0x00),
			COMMAND);
}

void Driver_PCD8544_Basic::setRamAddress(byte x, byte y)
{
	x %= CLOLUMN_COUNT;
	y %= BYTES_PER_COLUMN;
	this->transmit(0x80 | x, COMMAND);
	this->transmit(0x40 | y, COMMAND);
}
