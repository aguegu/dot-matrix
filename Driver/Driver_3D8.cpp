/*
 * Driver3D8.cpp
 *
 *  Created on: 2012-6-14
 *      Author: agu
 */

#include "Driver_3D8.h"


Driver_3D8::~Driver_3D8()
{

}


Driver_3D8::Driver_3D8(DotMatrix & dm, uint8_t pin_62726_DS,
		uint8_t pin_62726_OE, uint8_t pin_62726_ST, uint8_t pin_62726_SH,
		uint8_t pin_138_A2, uint8_t pin_138_A1, uint8_t pin_138_A0,
		uint8_t pin_brightness, uint16_t scan_speed) :
		Driver_595_138_Basic(pin_62726_DS, pin_62726_SH, pin_138_A2, pin_138_A1,
				pin_138_A0), _dm(dm), _pin_62726_OE(pin_62726_OE), _pin_62726_ST(
				pin_62726_ST), _pin_brightness(pin_brightness)

{
	pinMode(_pin_62726_OE, OUTPUT);
	pinMode(_pin_62726_ST, OUTPUT);

	pinMode(_pin_brightness, OUTPUT);

	this->setMode();

	this->setBrightness();
	this->setSpeed(scan_speed);
	this->setSize();
}

void Driver_3D8::setMode(byte mode)
{
	switch(mode)
	{
	case 1:
		_setCol = &Driver_3D8::setColzxy;
		break;
	case 2:
		_setCol = &Driver_3D8::setColyzx;
		break;
	default:
		_setCol = &Driver_3D8::setColxyz;
		break;

	}
}

void Driver_3D8::setSpeed(uint16_t scan_span)
{
	_scan_span = scan_span;
}

void Driver_3D8::setSize()
{
	_row_count = _dm.countRow();
	_byte_per_row = _dm.countBytePerRow();
	_word_per_row = _byte_per_row / 2;
}

void Driver_3D8::setBrightness(byte brg)
{
	analogWrite(_pin_brightness, brg);
}

void Driver_3D8::setColxyz(byte row) const
{
	byte * p = _dm.output();
	p += _byte_per_row * row;

	for (byte i = 0; i < _word_per_row; i++)
	{
		this->shiftSendFromLSB(*p++);
		this->shiftSendFromMSB(*p++);
	}
}

void Driver_3D8::display(byte times) const
{
	while (times--)
	{
		for (byte r = 0; r < _row_count; r++)
		{
			//this->setColxyz(r);
			(this->*_setCol)(r);

			pinSet(_pin_62726_OE);

			pinSet(_pin_62726_ST);
			pinClear(_pin_62726_ST);
			this->setRow(r);

			pinClear(_pin_62726_OE);

			delayMicroseconds(_scan_span);
		}
	}
}

void Driver_3D8::setColzxy(byte row) const
{
	byte *p = _dm.output() + row;
	for (byte j = 0; j < 8; j++) // z
	{
		for (byte i = 0; i < 8; i++) // y
		{
			if (j&0x01)	p-=8;
			pinWrite(_pin_595_DS, bitRead(*p, j));

			pinClear(_pin_595_SH);
			pinSet(_pin_595_SH);
			if (!(j&0x01)) p+=8;
			//byte * p = _dm.output() + 8*((j&0x01)?(7-i):i)+ row;
		}
	}
}

void Driver_3D8::setColyzx(byte row) const
{
	//word length = _dm.countBytes();
	byte * p = _dm.output();
	for (byte j = 0; j < 4; j++)
	{
		for (byte i = 0; i < 8; i++) // x
		{
			pinWrite(_pin_595_DS, bitRead(*(p++), row));
			pinClear(_pin_595_SH);
			pinSet(_pin_595_SH);
		}

		p += 8;

		for (byte i = 0; i < 8; i++)
		{
			digitalWrite(_pin_595_DS, bitRead(*(--p), row));
			digitalWrite(_pin_595_SH, LOW);
			digitalWrite(_pin_595_SH, HIGH);
		}
		p += 8;
	}
}


