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
		:Driver_595_138_Basic(pin_62726_DS, pin_62726_SH, pin_138_A2, pin_138_A1, pin_138_A0),
		 _dm(dm), _pin_62726_OE(pin_62726_OE), _pin_62726_ST(pin_62726_ST), _pin_brightness(pin_brightness)

{
	pinMode(_pin_62726_OE, OUTPUT);
	pinMode(_pin_62726_ST, OUTPUT);

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

void Driver_1818_138::setCol(byte *p) const
{
	for (byte i = 0; i < _word_per_row; i++)
	{
		this->shiftSendFromLSB(*p++);
		this->shiftSendFromMSB(*p++);
	}
}

void Driver_1818_138::display(byte times) const
{
	while (times--)
	{
		byte * p = _dm.output();
		for (byte r = 0; r < _row_count; r++)
		{
			this->setCol(p);
			p += _byte_per_row;

			digitalWrite(_pin_62726_OE, HIGH);

			digitalWrite(_pin_62726_ST, HIGH);
			digitalWrite(_pin_62726_ST, LOW);
			this->setRow(r);

			digitalWrite(_pin_62726_OE, LOW);

			delayMicroseconds(_scan_span);
		}
	}
}
