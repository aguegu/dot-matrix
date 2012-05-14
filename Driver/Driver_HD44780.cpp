/*
	Driver_HD44780.cpp
	Driver_HD44780 Class for dot-matrix printing on liquid crystal display driven by HD47780, namely 1602/1604
	Created on: 2012-02-29
	Updated on: 2012-05-14

	library for Arduino for Dot Matrix Display, support driver by 74HC595 and 74HC138, ST7920, HD47780
	Author: Weihong Guan
	Blog: http://aguegu.net
	E-mail: weihong.guan@gmail.com
	Code license: Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0)
	http://creativecommons.org/licenses/by-nc-sa/3.0/

	source host: https://github.com/aguegu/dot-matrix
 */

#include "Driver_HD44780.h"

const uint8_t PROGMEM HD44780_BAR[] =
{
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x1f,0x1f,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x1f,0x1f,0x00,0x00,0x00,
	0x1f,0x1f,0x00,0x1f,0x1f,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x1f,0x1f,
	0x1f,0x1f,0x00,0x00,0x00,0x00,0x1f,0x1f,
	0x00,0x00,0x00,0x1f,0x1f,0x00,0x1f,0x1f,
	0x1f,0x1f,0x00,0x1f,0x1f,0x00,0x1f,0x1f,
};

const uint8_t PROGMEM HD44780_ROW_ADDRESS[] =
{
	0x00, 0x40, 0x10, 0x50
};

HD44780::HD44780(DotMatrix dm, uint8_t pin_rs, uint8_t pin_en, uint8_t pin_d4, uint8_t pin_d5, uint8_t pin_d6, uint8_t pin_d7)
	:_dm(dm), _pin_rs(pin_rs), _pin_en(pin_en)
{
	_pin_dt[0] = pin_d4;
	_pin_dt[1] = pin_d5;
	_pin_dt[2] = pin_d6;
	_pin_dt[3] = pin_d7;

	pinMode(_pin_rs, OUTPUT);
	pinMode(_pin_en, OUTPUT);

	for (byte i = 0; i < 4; i++)
		pinMode(_pin_dt[i], OUTPUT);
}

void HD44780::initHardware() const
{
	delayMicroseconds(50000);
	digitalWrite(_pin_rs, LOW);
	digitalWrite(_pin_en, LOW);

	this->setDT(0x30, true);
	delayMicroseconds(4500);

	this->setDT(0x30, true);
	delayMicroseconds(4500);

	this->setDT(0x30, true);
	delayMicroseconds(150);

	this->setDT(0x20, true);

	this->setFunctionMode();
	this->setDisplayMode(false, false, false);

	this->clear();
	this->setInputMode();
	this->rst();
}

void HD44780::setDT(byte c, bool b) const
{
	if (b) c >>= 4;

	for (byte i = 0; i < 4; i++)
		digitalWrite(_pin_dt[i], bit_is_set(c, i));

	this->pulseEn();
}

void HD44780::setData(byte c) const
{
	this->setDT(c, true);
	this->setDT(c, false);
}

void HD44780::pulseEn(void) const
{
	digitalWrite(_pin_en, LOW);
	delayMicroseconds(1);
	digitalWrite(_pin_en, HIGH);
	delayMicroseconds(1);
	digitalWrite(_pin_en, LOW);
	delayMicroseconds(100);
}

void HD44780::writeCmd(byte command) const
{
	digitalWrite(_pin_rs, LOW);
	this->setData(command);
}

void HD44780::writeData(byte data) const
{
	digitalWrite(_pin_rs, HIGH);
	this->setData(data);
}

////////////////////////////////////////////

void HD44780::clear() const	// 0x01
{
	this->writeCmd(0x01);
	delayMicroseconds(2000);
}

void HD44780::rst()	const	// 0x02
{
	this->writeCmd(0x02);
	delayMicroseconds(2000);
}

void HD44780::setInputMode(bool ac, bool screen_move) const	// 0x04
{
	byte cmd = 0x04;

	if (ac) cmd |= 0x02;
	if (screen_move) cmd |= 0x01;

	this->writeCmd(cmd);
}

void HD44780::setDisplayMode(bool display_on, bool cursor, bool blink) const	// 0x08
{
	byte cmd = 0x08;
	if (display_on)	cmd |= 0x04;
	if (cursor) cmd |= 0x02;
	if (blink) cmd |= 0x01;
	this->writeCmd(cmd);
}

void HD44780::moveCursor(bool right) const	// 0x10
{
	byte cmd = 0x10;
	if (right) cmd |= 0x04;
	this->writeCmd(cmd);
}

void HD44780::moveScreen(bool right) const	// 0x11
{
	byte cmd = 0x11;
	if (right) cmd |= 0x04;
	this->writeCmd(cmd);
}


void HD44780::setFunctionMode(bool interface8, bool doubleline, bool font5x10) const	// 0x20
{
	 byte cmd = 0x20;
	 if (interface8) cmd |= 0x10;
	 if (doubleline) cmd |= 0x08;
	 if (font5x10)	cmd |= 0x04;
	 this->writeCmd(cmd);
}

void HD44780::setCGRam(byte *pFont, byte length) const
{
	byte i;

	this->setInputMode(1,0);
	this->writeCmd(0x40);

	for(i=0;i<length;i++)
	{
		this->writeData(pFont[i]);
	}
}

void HD44780::setCursor(byte address) const	// 0x80
{
	this->writeCmd(address | 0x80);
}

////////////////////
void HD44780::putString(byte address, char *p, byte length) const
{
	byte i;

	this->setCursor(address);

	for (i=0; i<length;i++)
	{
		this->writeData(p[i]);
	}
}

void HD44780::putChar(byte address, char c) const
{
	this->putString(address, &c, 1);
}

void HD44780::init()
{
	this->initHardware();

	byte *bar = (byte*)malloc(64);
	memcpy_P(bar, HD44780_BAR, 64);
	this->setCGRam(bar, 64);
	free(bar);

	this->setDisplayMode(true, false, false);

	_row_count = _dm.countCol();
	_col_count = _dm.countRow() / 3;

	_cache_length = _row_count * _col_count + 1;
	_cache = (char *)malloc(sizeof(char) * _cache_length);
}


void HD44780::printCache()
{
	for (byte r=0; r<_row_count; r++)
		this->putString(pgm_read_byte_near(HD44780_ROW_ADDRESS+r), _cache + _col_count * r, _col_count);
}

void HD44780::printf(byte index, const char *__fmt, ...)
{
	if (index >= _cache_length) return;

	va_list ap;
	va_start(ap, __fmt);
	vsnprintf(_cache + index, _cache_length - index, __fmt, ap);
	va_end(ap);
}

void HD44780::printf(const char *__fmt, ...)
{
	va_list ap;
	va_start(ap, __fmt);
	vsnprintf(_cache, _cache_length, __fmt, ap);
	va_end(ap);
}

void HD44780::printDotMatrix()
{
	//byte *p = _dm.output();
	for(byte c=0; c<_col_count; c++)
	{
		for (byte r=0; r<_row_count; r++)
		{
			bitWrite(*(_cache + _col_count * (r/3) + c), r % 3, _dm.getDot(c, r));
		}
	}
}

//////////////////////
HD44780::~HD44780()
{
	free(_cache);
}

