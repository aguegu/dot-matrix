/*
	Driver_595_138.cpp
	Driver_595_138 Class for dot-matrix printing on matrix driven by 74HC595 and 74HC138
	Created on: 2012-01-15
	Updated on: 2012-05-14

	library for Arduino for Dot Matrix Display, support driver by 74HC595 and 74HC138, ST7920, HD47780
	Author: Weihong Guan
	Blog: http://aguegu.net
	E-mail: weihong.guan@gmail.com
	Code license: Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0)
	http://creativecommons.org/licenses/by-nc-sa/3.0/

	source host: https://github.com/aguegu/dot-matrix
 */

#include "Driver_595_138.h"

Driver_595_138::Driver_595_138(DotMatrix & dm, uint8_t pin_C_IN,
		uint8_t pin_C_OE, uint8_t pin_C_ST, uint8_t pin_C_SH, uint8_t pin_R_OE,
		uint8_t pin_R_A2, uint8_t pin_R_A1, uint8_t pin_R_A0, uint16_t speed):_dm(dm)
{
	_pin_595_ST = pin_C_ST;
	_pin_595_SH = pin_C_SH;
	_pin_595_DS = pin_C_IN;
	_pin_595_OE = pin_C_OE;

	_pin_138_OE = pin_R_OE;
	_pin_138_A0 = pin_R_A0;
	_pin_138_A1 = pin_R_A1;
	_pin_138_A2 = pin_R_A2;

	pinMode(_pin_138_A1, OUTPUT);
	pinMode(_pin_138_A2, OUTPUT);
	pinMode(_pin_595_ST, OUTPUT);
	pinMode(_pin_595_SH, OUTPUT);
	pinMode(_pin_595_DS, OUTPUT);
	pinMode(_pin_595_OE, OUTPUT);

	pinMode(_pin_138_OE, OUTPUT);
	pinMode(_pin_138_A0, OUTPUT);

	this->setSpeed(speed);

	this->setSize(_dm.countBytes(), _dm.countRow());
}

void Driver_595_138::setSpeed(uint16_t speed)
{
	_speed = speed;
}

void Driver_595_138::setSize(byte length, byte rowCount)
{
	_length = length;
	_rowCount = rowCount;
	_bytesPerRow = _length / _rowCount;
}

void Driver_595_138::setRow(byte r)
{
	digitalWrite(_pin_138_A0, r & 0x01);
	digitalWrite(_pin_138_A1, r & 0x02);
	digitalWrite(_pin_138_A2, r & 0x04);
}

void Driver_595_138::setCol(byte * p)
{
	for (byte i = _bytesPerRow; i ; i--)
		this->shiftSend(~*(p++));

		//shiftOut(_pin_595_DS, _pin_595_SH, LSBFIRST, ~*(p++));
}

void Driver_595_138::shiftSend(byte c)
{
	for (byte i=0; i<8; i++)
	{
		digitalWrite(_pin_595_DS, bitRead(c, i));

		digitalWrite(_pin_595_SH, LOW);
		digitalWrite(_pin_595_SH, HIGH);
	}
}

void Driver_595_138::display(byte times)
{
	byte* p = _dm.output();

	while (times--)
	{
		for (byte r = 0; r < _rowCount; r++)
		{
			setCol(p + _bytesPerRow * r);
			digitalWrite(_pin_138_OE, LOW);

			digitalWrite(_pin_595_ST, LOW);
			digitalWrite(_pin_595_ST, HIGH);

			setRow(r);
			digitalWrite(_pin_138_OE, HIGH);
			delayMicroseconds(_speed);
		}
	}
}

Driver_595_138::~Driver_595_138()
{

}

