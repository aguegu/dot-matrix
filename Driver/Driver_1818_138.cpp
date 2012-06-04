/*
 * Driver1818138.cpp
 *
 *  Created on: 2012-5-28
 *      Author: Agu
 */

#include "Driver_1818_138.h"

Driver_1818_138::Driver_1818_138(DotMatrix & dm, uint8_t pin_62726_DS,
		uint8_t pin_62726_OE, uint8_t pin_62726_ST, uint8_t pin_62726_SH,
		uint8_t pin_138_A0, uint8_t pin_138_A1, uint8_t pin_138_A2,
		uint8_t pin_brightness, uint16_t scan_speed)
		:_dm(dm),
		_pin_62726_DS(pin_62726_DS), _pin_62726_OE(pin_62726_OE), _pin_62726_ST(pin_62726_ST), _pin_62726_SH(pin_62726_SH),
		_pin_138_A0(pin_138_A0), _pin_138_A1(pin_138_A1), _pin_138_A2(pin_138_A2), _pin_brightness(pin_brightness)
{
	// TODO Auto-generated constructor stub
	pinMode(_pin_62726_DS, OUTPUT);
	pinMode(_pin_62726_OE, OUTPUT);
	pinMode(_pin_62726_SH, OUTPUT);
	pinMode(_pin_62726_ST, OUTPUT);

	pinMode(_pin_138_A0, OUTPUT);
	pinMode(_pin_138_A1, OUTPUT);
	pinMode(_pin_138_A2, OUTPUT);

	pinMode(_pin_brightness, OUTPUT);
	analogWrite(_pin_brightness, 0xff);

	this->setSpeed(scan_speed);
	this->setSize(dm.countBytes(), dm.countRow());
}

void Driver_1818_138::setSpeed(uint16_t scan_span)
{
	_scan_span = scan_span;
}

void Driver_1818_138::setSize(byte length, byte row_count)
{
	_length = length;
	_row_count = row_count;
	_byte_per_row = _length / _row_count;
	_word_per_row = _byte_per_row / 2;


}

void Driver_1818_138::setRow(byte r)
{
	digitalWrite(_pin_138_A0, r & 0x01);
	digitalWrite(_pin_138_A1, r & 0x02);
	digitalWrite(_pin_138_A2, r & 0x04);
}

void Driver_1818_138::setCol(byte *p)
{
	for (byte i = 0; i < _word_per_row; i++)
	{
		for (byte j = 0; j < 8; j++)
		{
			digitalWrite(_pin_62726_DS, bitRead(*p,j));
			digitalWrite(_pin_62726_SH, LOW);
			digitalWrite(_pin_62726_SH, HIGH);
		}
		p++;

		for (byte j = 8; j;)
		{
			digitalWrite(_pin_62726_DS, bitRead(*p,--j));
			digitalWrite(_pin_62726_SH, LOW);
			digitalWrite(_pin_62726_SH, HIGH);
		}
		p++;
	}
}

void Driver_1818_138::display(byte times)
{
	byte * p = _dm.output();

	while(times--)
	for (byte r = 0; r < _row_count; r++)
	{
		this->setCol(p + _byte_per_row * r );
		digitalWrite(_pin_62726_OE, HIGH);

		digitalWrite(_pin_62726_ST, HIGH);
		digitalWrite(_pin_62726_ST, LOW);
		this->setRow(r);
		digitalWrite(_pin_62726_OE, LOW);
		delayMicroseconds(_scan_span);
	}
}
