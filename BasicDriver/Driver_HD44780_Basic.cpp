/*
 *	Driver_HD44780_Basic.cpp
 *	Driver_HD44780_Basic Class, arduino driver for liquid crystal display driven by HD47780, namely 1602/1604
 *	Created on: 2012-06-01
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

#include "Driver_HD44780_Basic.h"

const uint8_t PROGMEM HD44780_BAR[] =
{
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x1f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x1f, 0x1f, 0x00, 0x00, 0x00,
	0x1f, 0x1f, 0x00, 0x1f, 0x1f, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x1f,
	0x1f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x1f,
	0x00, 0x00, 0x00, 0x1f, 0x1f, 0x00, 0x1f, 0x1f,
	0x1f, 0x1f, 0x00, 0x1f, 0x1f, 0x00, 0x1f, 0x1f,
};

const uint8_t PROGMEM HD44780_ROW_ADDRESS[] = { 0x00, 0x40, 0x10, 0x50 };

HD44780_Basic::HD44780_Basic(uint8_t pin_rs, uint8_t pin_en,
		uint8_t pin_d4, uint8_t pin_d5, uint8_t pin_d6, uint8_t pin_d7,
		byte col_count, byte row_count)
		:  _pin_rs(pin_rs), _pin_en(pin_en)
{
	_pin_dt[0] = pin_d4;
	_pin_dt[1] = pin_d5;
	_pin_dt[2] = pin_d6;
	_pin_dt[3] = pin_d7;

	pinMode(_pin_rs, OUTPUT);
	pinMode(_pin_en, OUTPUT);

	for (byte i = 0; i < 4; i++)
		pinMode(_pin_dt[i], OUTPUT);

	_col_count = col_count;
	_row_count = row_count;

	_cache_length = _row_count * _col_count + 1;
	_cache = (char *) malloc(sizeof(char) * _cache_length);

	this->setCache();
}

HD44780_Basic::~HD44780_Basic()
{
	free(_cache);
}

void HD44780_Basic::initHardware() const
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

	this->configureFunction();
	this->configureDisplay(false, false, false);

	this->clear();
	this->configureInput();
	this->rst();
}

void HD44780_Basic::setDT(byte c, bool b) const
{
	if (b)
		c >>= 4;

	for (byte i = 0; i < 4; i++)
		digitalWrite(_pin_dt[i], bit_is_set(c, i));

	this->pulseEn();
}

void HD44780_Basic::setData(byte c) const
{
	this->setDT(c, true);
	this->setDT(c, false);
}

void HD44780_Basic::pulseEn(void) const
{
	digitalWrite(_pin_en, LOW);
	digitalWrite(_pin_en, HIGH);
	digitalWrite(_pin_en, LOW);
	delayMicroseconds(100);
}

void HD44780_Basic::writeCmd(byte command) const
{
	digitalWrite(_pin_rs, LOW);
	this->setData(command);
}

void HD44780_Basic::writeData(byte data) const
{
	digitalWrite(_pin_rs, HIGH);
	this->setData(data);
}

////////////////////////////////////////////

void HD44780_Basic::clear() const // 0x01
{
	this->writeCmd(0x01);
	delayMicroseconds(2000);
}

void HD44780_Basic::rst() const // 0x02
{
	this->writeCmd(0x02);
	delayMicroseconds(2000);
}

void HD44780_Basic::configureInput(bool ac, bool screen_move) const // 0x04
{
	byte cmd = 0x04;

	if (ac)
		cmd |= 0x02;
	if (screen_move)
		cmd |= 0x01;

	this->writeCmd(cmd);
}

void HD44780_Basic::configureDisplay(bool display_on, bool cursor, bool blink) const // 0x08
{
	byte cmd = 0x08;
	if (display_on)
		cmd |= 0x04;
	if (cursor)
		cmd |= 0x02;
	if (blink)
		cmd |= 0x01;
	this->writeCmd(cmd);
}

void HD44780_Basic::moveCursor(bool right) const // 0x10
{
	byte cmd = 0x10;
	if (right)
		cmd |= 0x04;
	this->writeCmd(cmd);
}

void HD44780_Basic::moveScreen(bool right) const // 0x11
{
	byte cmd = 0x11;
	if (right)
		cmd |= 0x04;
	this->writeCmd(cmd);
}

void HD44780_Basic::configureFunction(bool interface8, bool doubleline,
		bool font5x10) const // 0x20
{
	byte cmd = 0x20;
	if (interface8)
		cmd |= 0x10;
	if (doubleline)
		cmd |= 0x08;
	if (font5x10)
		cmd |= 0x04;
	this->writeCmd(cmd);
}

void HD44780_Basic::setCGRam(byte *pFont, byte length) const
{
	byte i;

	this->configureInput(true, false);
	this->writeCmd(0x40);

	for (i = 0; i < length; i++)
	{
		this->writeData(pFont[i]);
	}
}

void HD44780_Basic::setCursor(byte address) const // 0x80
{
	this->writeCmd(address | 0x80);
}

////////////////////
void HD44780_Basic::putString(byte address, char *p, byte length) const
{
	byte i;

	this->setCursor(address);

	for (i = 0; i < length; i++)
	{
		this->writeData(p[i]);
	}
}

void HD44780_Basic::putChar(byte address, char c) const
{
	this->putString(address, &c, 1);
}

void HD44780_Basic::init()
{
	this->initHardware();

	byte *bar = (byte*) malloc(64);
	memcpy_P(bar, HD44780_BAR, 64);
	this->setCGRam(bar, 64);
	free(bar);

	this->configureDisplay(true, false, false);
}


void HD44780_Basic::putCache() const
{
	for (byte r = 0; r < _row_count; r++)
		this->putString(pgm_read_byte_near(HD44780_ROW_ADDRESS + r),
				_cache + _col_count * r, _col_count);
}

void HD44780_Basic::printf(byte index, const char *__fmt, ...)
{
	if (index >= _cache_length)
		return;

	va_list ap;
	va_start(ap, __fmt);
	vsnprintf(_cache + index, _cache_length - index, __fmt, ap);
	va_end(ap);
}

void HD44780_Basic::printf(const char *__fmt, ...)
{
	va_list ap;
	va_start(ap, __fmt);
	vsnprintf(_cache, _cache_length, __fmt, ap);
	va_end(ap);
}

void HD44780_Basic::setCache(byte value)
{
	memset(_cache, value, _cache_length);
}

void HD44780_Basic::setCache(byte index, byte value)
{
	if (index >= _cache_length) return;

	_cache[index] = value;
}

//////////////////////


