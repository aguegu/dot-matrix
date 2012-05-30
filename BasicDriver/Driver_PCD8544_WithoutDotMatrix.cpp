/*
 * Driver_PCD8544.cpp
 *
 *  Created on: 2012-5-30
 *      Author: gmb-gwh
 */

#include "Driver_PCD8544_WithoutDotMatrix.h"

Driver_PCD8544_WithoutDotMatrix::Driver_PCD8544_WithoutDotMatrix()
{
	// TODO Auto-generated constructor stub
	_pin_sce = 2;
	_pin_rst = 3;
	_pin_dc = 4;
	_pin_din = 5;
	_pin_sclk = 6;

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

	this->send(0x21, COMMAND);
	this->send(0x80 | 0x48, COMMAND);
	this->send(0x04 | 0x02, COMMAND);
	this->send(0x10, COMMAND);

	this->send(0x20, COMMAND);
	this->send(0x0c, COMMAND);


	this->setRamX(0);
	this->setRamY(0);

	for(byte r=0; r<6; r++)
	{
		for (byte c=0; c<84; c++)
		{
			this->send(0xcc, DATA);
		}
	}
}

void Driver_PCD8544_WithoutDotMatrix::setRamX(byte x)
{
	this->send(0x80 | x, COMMAND);
}

void Driver_PCD8544_WithoutDotMatrix::setRamY(byte y)
{
	this->send(0x40 | y, COMMAND);
}
