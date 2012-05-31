/*
 * Driver_PCD8544.cpp
 *
 *  Created on: 2012-5-30
 *      Author: gmb-gwh
 */

#include "Driver_PCD8544_WithoutDotMatrix.h"

Driver_PCD8544_WithoutDotMatrix::Driver_PCD8544_WithoutDotMatrix
	(uint8_t pin_sce, uint8_t pin_rst, uint8_t pin_dc, uint8_t pin_din, uint8_t pin_sclk)
	:_pin_sce(pin_sce), _pin_rst(pin_rst), _pin_dc(pin_dc), _pin_din(pin_din), _pin_sclk(pin_sclk)
{
	// TODO Auto-generated constructor stub
	pinMode(_pin_sce, OUTPUT);
	pinMode(_pin_rst, OUTPUT);
	pinMode(_pin_dc, OUTPUT);
	pinMode(_pin_din, OUTPUT);
	pinMode(_pin_sclk, OUTPUT);
}

Driver_PCD8544_WithoutDotMatrix::~Driver_PCD8544_WithoutDotMatrix()
{
	// TODO Auto-generated destructor stub
}

void Driver_PCD8544_WithoutDotMatrix::send(byte c, bool b)
{
	digitalWrite(_pin_sce, LOW);

	digitalWrite(_pin_dc, b);

	for(byte i=0; i<8; i++)
	{
		digitalWrite(_pin_din, bitRead(c, 7));
		digitalWrite(_pin_sclk, LOW);
		digitalWrite(_pin_sclk, HIGH);
		c <<= 1;
	}

	digitalWrite(_pin_sce, HIGH);
}

void Driver_PCD8544_WithoutDotMatrix::init()
{
	digitalWrite(_pin_sce, LOW);
	digitalWrite(_pin_rst, LOW);
	delay(50);
	digitalWrite(_pin_rst, HIGH);
	digitalWrite(_pin_sce, HIGH);

	this->configureFunction();
	this->configureDisplay();

	this->setRamAddress(0, 0);

	for(byte r=0; r<6; r++)
	{
		for (byte c=0; c<84; c++)
		{
			this->send(c, DATA);
		}
	}
}

void Driver_PCD8544_WithoutDotMatrix::configureFunction(byte tc, byte bias, byte vop)
{
	this->send(0x20 | 0x03, COMMAND);
	this->send(0x04 | (tc & 0x03), COMMAND);
	this->send(0x10 | (bias & 0x07), COMMAND);
	this->send(0x80 | (vop & 0x7f), COMMAND);
	this->send(0x20 | 0x02, COMMAND);
}

void Driver_PCD8544_WithoutDotMatrix::configureDisplay(bool display_on, bool reverse)
{
	this->send(0x08 | (display_on? 0x04:0x00) | (reverse? 0x01:0x00), COMMAND);
}

void Driver_PCD8544_WithoutDotMatrix::setRamAddress(byte x, byte y)
{
	x %= 84;
	y %= 6;
	this->send(0x80 | x, COMMAND);
	this->send(0x40 | y, COMMAND);
}
