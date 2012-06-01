/*
	Driver_ST7920.cpp
	Driver_ST7920 Class for dot-matrix printing on liquid crystal display driven by ST7920, namely 12864
	Created on: 2012-03-04
	Updated on: 2012-05-14

	library for Arduino for Dot Matrix Display, support driver by 74HC595 and 74HC138, ST7920, HD47780
	Author: Weihong Guan
	Blog: http://aguegu.net
	E-mail: weihong.guan@gmail.com
	Code license: Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0)
	http://creativecommons.org/licenses/by-nc-sa/3.0/

	source host: https://github.com/aguegu/dot-matrix
 */

#include "Driver_ST7920_Basic.h"

ST7920_Basic::ST7920_Basic(uint8_t pin_rs, uint8_t pin_en, uint8_t pin_d4,
		uint8_t pin_d5, uint8_t pin_d6, uint8_t pin_d7) :
		_pin_rs(pin_rs), _pin_en(pin_en)
{
	_pin_d[0] = pin_d4;
	_pin_d[1] = pin_d5;
	_pin_d[2] = pin_d6;
	_pin_d[3] = pin_d7;

	this->initPin();
}

void ST7920_Basic::initPin()
{
	pinMode(_pin_rs, OUTPUT);
	pinMode(_pin_en, OUTPUT);

	for (byte i = 0; i < 4; i++)
		pinMode(_pin_d[i], OUTPUT);

	digitalWrite(_pin_en, LOW);
}

void ST7920_Basic::init()
{
	delayMicroseconds(50000);

	this->setDB2(0x20, true);
	this->setFunctionMode(false, false);
	this->setDisplayMode(true, false, false);
	this->clear();
	this->setEntryMode(true);

	this->setFunctionMode(false, true, true);
}

void ST7920_Basic::clear()
{
	this->writeCmd(0x01);
	delayMicroseconds(2000);
}

void ST7920_Basic::home()
{
	this->writeCmd(0x02);
}

void ST7920_Basic::setEntryMode(bool right)
{
	byte cmd = 0x04;
	if (right)
		cmd |= 0x02;
	this->writeCmd(cmd);
}

void ST7920_Basic::setDisplayMode(bool display, bool cursor, bool blink)
{
	byte cmd = 0x08;
	if (display)
		cmd |= 0x04;
	if (cursor)
		cmd |= 0x02;
	if (blink)
		cmd |= 0x01;
	this->writeCmd(cmd);
}

void ST7920_Basic::moveCursor(bool right)
{
	byte cmd = 0x10;
	if (right)
		cmd |= 0x04;
	this->writeCmd(cmd);
}

void ST7920_Basic::moveDisplay(bool right)
{
	byte cmd = 0x18;
	if (right)
		cmd |= 0x04;
	this->writeCmd(cmd);
}

void ST7920_Basic::setFunctionMode(bool interface8, bool re, bool graphic)
{
	byte cmd = 0x20;
	if (interface8)
		cmd |= 0x10;
	if (re)
		cmd |= 0x04;
	if (re && graphic)
		cmd |= 0x02;
	this->writeCmd(cmd);
}

void ST7920_Basic::setCgRam(byte value)
{
	this->writeData(0x40 | value);
}

void ST7920_Basic::setDdRam(byte address)
{
	this->writeCmd(0x80 | address);
}

/////////////////////////////////////

void ST7920_Basic::writeCmd(byte c)
{
	digitalWrite(_pin_rs, LOW);
	setDB2(c, true);
	setDB2(c, false);
}

void ST7920_Basic::writeData(byte c)
{
	digitalWrite(_pin_rs, HIGH);
	setDB2(c, true);
	setDB2(c, false);
}

void ST7920_Basic::writeDataRev(byte c)
{
	digitalWrite(_pin_rs, HIGH);

	for (byte i = 0; i < 4; i++)
		digitalWrite(_pin_d[3 - i], bit_is_set(c, i));

	this->pulseEn();

	c >>= 4;

	for (byte i = 0; i < 4; i++)
		digitalWrite(_pin_d[3 - i], bit_is_set(c, i));

	this->pulseEn();
}

void ST7920_Basic::setDB2(byte c, bool high)
{
	if (high)
		c >>= 4;

	for (byte i = 0; i < 4; i++)
		digitalWrite(_pin_d[i], bit_is_set(c, i));

	this->pulseEn();
}

void ST7920_Basic::pulseEn()
{
	digitalWrite(_pin_en, HIGH);
	digitalWrite(_pin_en, LOW);
	delayMicroseconds(100);
}

void ST7920_Basic::printWord(char *p)
{
	while (*p)
	{
		this->writeData(*p);
		p++;
	}
}

ST7920_Basic::~ST7920_Basic()
{

}

