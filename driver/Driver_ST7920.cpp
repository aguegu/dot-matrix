/*
 * Lcd12864.cpp
 *
 *  Created on: 2012-3-4
 *      Author: Agu
 */

#include "Driver_ST7920.h"

ST7920::ST7920(uint8_t pin_rs, uint8_t pin_en, uint8_t pin_d4, uint8_t pin_d5, uint8_t pin_d6, uint8_t pin_d7)
{
	_pin_rs = pin_rs;
	_pin_en = pin_en;

	_pin_d[0] = pin_d4;
	_pin_d[1] = pin_d5;
	_pin_d[2] = pin_d6;
	_pin_d[3] = pin_d7;

	this->initPin();
}

void ST7920::initPin()
{
	pinMode(_pin_rs, OUTPUT);
	pinMode(_pin_en, OUTPUT);

	for (byte i = 0; i < 4; i++)
		pinMode(_pin_d[i], OUTPUT);

	digitalWrite(_pin_en, LOW);
}

void ST7920::init()
{
	delayMicroseconds(50000);

	this->setDB2(0x20, true);
	this->setFunctionMode(false, false);
	this->setDisplayMode(true, false, false);
	this->clear();
	this->setEntryMode(true);
}

void ST7920::clear()
{
	this->writeCmd(0x01);
	delayMicroseconds(2000);
}

void ST7920::home()
{
	this->writeCmd(0x02);
}

void ST7920::setEntryMode(bool right)
{
	byte cmd = 0x04;
	if (right)
		cmd |= 0x02;
	this->writeCmd(cmd);
}

void ST7920::setDisplayMode(bool display, bool cursor, bool blink)
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

void ST7920::moveCursor(bool right)
{
	byte cmd = 0x10;
	if (right)
		cmd |= 0x04;
	this->writeCmd(cmd);
}

void ST7920::moveDisplay(bool right)
{
	byte cmd = 0x18;
	if (right)
		cmd |= 0x04;
	this->writeCmd(cmd);
}

void ST7920::setFunctionMode(bool interface8, bool re, bool graphic)
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

void ST7920::setCgRam(byte value)
{
	this->writeData(0x40 | value);
}

void ST7920::setDdRam(byte address)
{
	this->writeCmd(0x80 | address);
}

/////////////////////////////////////

void ST7920::writeCmd(byte c)
{
	digitalWrite(_pin_rs, LOW);
	setDB(c);
}

void ST7920::writeData(byte c)
{
	digitalWrite(_pin_rs, HIGH);
	setDB(c);
}

void ST7920::setDB2(byte c, bool high)
{
	if (high) c >>= 4;

	for (byte i = 0; i < 4; i++)
		digitalWrite(_pin_d[i], bit_is_set(c, i));

	this->pulseEn();
}

void ST7920::setDB(byte c)
{
	setDB2(c, true);
	setDB2(c, false);
}

void ST7920::pulseEn()
{
	digitalWrite(_pin_en, HIGH);
	digitalWrite(_pin_en, LOW);
	delayMicroseconds(100);
}

void ST7920::printWord(char *p)
{
	while (*p)
	{
		this->writeData(*p);
		p++;
	}
}

void ST7920::clearImage(byte c)
{
	this->setFunctionMode(false, true, false);

	for (byte r = 0; r < 0x20; r++)
	{
		this->setDdRam(r);
		this->setDdRam(0x00);
		for (byte i = 0; i < 0x20; i++)
			this->writeData(i);
	}

	this->setFunctionMode(false, true, true);
}

void ST7920::putImage(byte *p)
{
	//this->setFunctionMode(false, true, false);

	for (byte r = 0; r < 0x20; r++)
	{
		this->setDdRam(r);
		this->setDdRam(0x00);
		for (byte i = 0; i < 0x20; i++)
			this->writeData(*(p++));
	}

	//this->setFunctionMode(false, true, true);
}

ST7920::~ST7920()
{

}

