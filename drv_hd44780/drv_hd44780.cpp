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

#include "drv_hd44780.h"

const uint8_t PROGMEM HD44780_BAR[] =
{
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// 00000000
	0x1f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 11000000
	0x00, 0x00, 0x00, 0x1f, 0x1f, 0x00, 0x00, 0x00, // 00011000
	0x1f, 0x1f, 0x00, 0x1f, 0x1f, 0x00, 0x00, 0x00, // 11011000
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x1f,	// 00000011
	0x1f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x1f, // 11000011
	0x00, 0x00, 0x00, 0x1f, 0x1f, 0x00, 0x1f, 0x1f, // 00011011
	0x1f, 0x1f, 0x00, 0x1f, 0x1f, 0x00, 0x1f, 0x1f, // 11011011
};

const uint8_t PROGMEM HD44780_ROW_ADDRESS_16[] =
{ 0x00, 0x40, 0x10, 0x50 };
const uint8_t PROGMEM HD44780_ROW_ADDRESS_20[] =
{ 0x00, 0x40, 0x14, 0x54 };

DrvHd44780::DrvHd44780(uint8_t pin_rs, uint8_t pin_en, uint8_t pin_d4,
		uint8_t pin_d5, uint8_t pin_d6, uint8_t pin_d7, byte row_count,
		byte col_count) :
		_pin_rs(pin_rs), _pin_en(pin_en), _row_count(row_count), _col_count(
				col_count)
{
	_cache_length = _row_count * _col_count + 1;
	_cache = (char *) malloc(sizeof(char) * _cache_length);

	_pin_dt[0] = pin_d4;
	_pin_dt[1] = pin_d5;
	_pin_dt[2] = pin_d6;
	_pin_dt[3] = pin_d7;

	pinMode(_pin_rs, OUTPUT);
	pinMode(_pin_en, OUTPUT);

	for (byte i = 0; i < 4; i++)
		pinMode(_pin_dt[i], OUTPUT);

	this->setCache();
}

DrvHd44780::~DrvHd44780()
{
	free(_cache);
}

void DrvHd44780::initHardware() const
{
	delayMicroseconds(40000);

	pinClear(_pin_rs);
	pinClear(_pin_en);

	this->setDT(0x30, true);
	delayMicroseconds(4500);

	this->setDT(0x30, true);
	delayMicroseconds(150);

	this->setDT(0x30, true);
	this->setDT(0x20, true);

	this->configureFunction();
	this->configureDisplay(false, false, false);

	this->clear();
	this->configureInput();
	this->rst();
}

void DrvHd44780::setDT(byte c, bool b) const
{
	if (b)
		c >>= 4;

	for (byte i = 0; i < 4; i++)
		pinWrite(_pin_dt[i], bit_is_set(c, i));

	this->pulseEn();
}

void DrvHd44780::setData(byte c) const
{
	this->setDT(c, true);
	this->setDT(c, false);
}

void DrvHd44780::pulseEn(void) const
{
	pinSet(_pin_en);
	pinClear(_pin_en);
	delayMicroseconds(100);
}

void DrvHd44780::writeCmd(byte command) const
{
	pinClear(_pin_rs);
	this->setData(command);
}

void DrvHd44780::writeData(byte data) const
{
	pinSet(_pin_rs);
	this->setData(data);
}

////////////////////////////////////////////

void DrvHd44780::clear() const // 0x01
{
	this->writeCmd(0x01);
	delayMicroseconds(2000);
}

void DrvHd44780::rst() const // 0x02
{
	this->writeCmd(0x02);
	delayMicroseconds(2000);
}

void DrvHd44780::configureInput(bool ac, bool screen_move) const // 0x04
{
	byte cmd = 0x04;

	if (ac)
		cmd |= 0x02;
	if (screen_move)
		cmd |= 0x01;

	this->writeCmd(cmd);
}

void DrvHd44780::configureDisplay(bool display_on, bool cursor,
		bool blink) const // 0x08
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

void DrvHd44780::moveCursor(bool right) const // 0x10
{
	byte cmd = 0x10;
	if (right)
		cmd |= 0x04;
	this->writeCmd(cmd);
}

void DrvHd44780::moveScreen(bool right) const // 0x11
{
	byte cmd = 0x11;
	if (right)
		cmd |= 0x04;
	this->writeCmd(cmd);
}

void DrvHd44780::configureFunction(bool interface8, bool doubleline,
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

void DrvHd44780::setCGRam(byte *pFont, byte length) const
{
	this->configureInput(true, false);
	this->writeCmd(0x40);

	for (byte i = 0; i < length; i++)
	{
		this->writeData(pFont[i]);
	}
}

void DrvHd44780::setCursor(byte address) const // 0x80
{
	this->writeCmd(address | 0x80);
}

////////////////////
void DrvHd44780::putString(byte address, char *p, byte length) const
{
	char *pp = p;

	this->setCursor(address);

	while (length--)
	{
		this->writeData(*pp++);
	}
}

void DrvHd44780::putChar(byte address, char c) const
{
	this->putString(address, &c, 1);
}

void DrvHd44780::init()
{
	this->initHardware();

	byte *bar = (byte*) malloc(64);
	memcpy_P(bar, HD44780_BAR, 64);
	this->setCGRam(bar, 64);
	free(bar);

	this->configureDisplay(true, false, false);
}

void DrvHd44780::putCache() const
{
	for (byte r = 0; r < _row_count; r++)
		this->putString(
				pgm_read_byte_near((_col_count<=16?HD44780_ROW_ADDRESS_16:HD44780_ROW_ADDRESS_20) + r),
				_cache + _col_count * r, _col_count);
}

void DrvHd44780::printf(byte index, const char *__fmt, ...)
{
	if (index >= _cache_length)
		return;

	va_list ap;
	va_start(ap, __fmt);
	vsnprintf(_cache + index, _cache_length - index, __fmt, ap);
	va_end(ap);
}

void DrvHd44780::printf(const char *__fmt, ...)
{
	va_list ap;
	va_start(ap, __fmt);
	vsnprintf(_cache, _cache_length, __fmt, ap);
	va_end(ap);
}

void DrvHd44780::setCache(byte value)
{
	memset(_cache, value, _cache_length);
}

void DrvHd44780::setCache(byte index, byte value)
{
	if (index >= _cache_length)
		return;

	_cache[index] = value;
}

//////////////////////

