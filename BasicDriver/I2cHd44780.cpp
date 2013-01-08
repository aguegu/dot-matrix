/*
 * I2cHd44780.cpp
 *
 *  Created on: Jan 8, 2013
 *      Author: agu
 */

#include "I2cHd44780.h"

const uint8_t PROGMEM HD44780_BAR[] =
{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 00000000
		0x1f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 11000000
		0x00, 0x00, 0x00, 0x1f, 0x1f, 0x00, 0x00, 0x00, // 00011000
		0x1f, 0x1f, 0x00, 0x1f, 0x1f, 0x00, 0x00, 0x00, // 11011000
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x1f, // 00000011
		0x1f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x1f, // 11000011
		0x00, 0x00, 0x00, 0x1f, 0x1f, 0x00, 0x1f, 0x1f, // 00011011
		0x1f, 0x1f, 0x00, 0x1f, 0x1f, 0x00, 0x1f, 0x1f, // 11011011
		};

const uint8_t PROGMEM HD44780_ROW_ADDRESS_16[] =
{ 0x00, 0x40, 0x10, 0x50 };
const uint8_t PROGMEM HD44780_ROW_ADDRESS_20[] =
{ 0x00, 0x40, 0x14, 0x54 };

I2cHd44780::I2cHd44780(byte address, byte row_count, byte col_count) :
		_address(address), _row_count(row_count), _col_count(col_count)
{
	_cache_length = _row_count * _col_count + 1;
	_cache = (char *) malloc(sizeof(char) * _cache_length);

	_backlight = true;

	this->setCache();

	twi.init();
}

I2cHd44780::~I2cHd44780()
{
	free(_cache);
}

void I2cHd44780::initHardware() const
{
	delayMicroseconds(40000);
//
	twi.writeTo(_address, 0x30 | 0x04);
	twi.writeTo(_address, 0x30);
	//this->setDT(0x30, true);
	delayMicroseconds(4500);

	//this->setDT(0x30, true);
	twi.writeTo(_address, 0x30 | 0x04);
	twi.writeTo(_address, 0x30);
	delayMicroseconds(150);

	twi.writeTo(_address, 0x30 | 0x04);
	twi.writeTo(_address, 0x30);

	twi.writeTo(_address, 0x20 | 0x04);
	twi.writeTo(_address, 0x20);

	this->configureFunction();
	this->configureDisplay(false, false, false);

	this->clear();
	this->configureInput();
	this->rst();
}

void I2cHd44780::transmit(bool isData, byte c) const
{
	byte val = 0;
	bitWrite(val, PIN_BL, _backlight);
	bitWrite(val, PIN_RS, isData);

	val |= c & 0xf0;

	bitSet(val, PIN_EN);
	twi.writeTo(_address, val);

	bitClear(val, PIN_EN);
	twi.writeTo(_address, val);

	val &= 0x0f;
	val |= c << 4;

	bitSet(val, PIN_EN);
	twi.writeTo(_address, val);

	bitClear(val, PIN_EN);
	twi.writeTo(_address, val);
}

void I2cHd44780::clear() const // 0x01
{
	this->transmit(false, 0x01);
	delayMicroseconds(2000);
}

void I2cHd44780::rst() const // 0x02
{
	this->transmit(false, 0x02);
	delayMicroseconds(2000);
}

void I2cHd44780::configureInput(bool ac, bool screen_move) const // 0x04
{
	byte cmd = 0x04;

	if (ac)
		cmd |= 0x02;
	if (screen_move)
		cmd |= 0x01;

	this->transmit(false, cmd);
}

void I2cHd44780::configureDisplay(bool display_on, bool cursor,
		bool blink) const // 0x08
{
	byte cmd = 0x08;
	if (display_on)
		cmd |= 0x04;
	if (cursor)
		cmd |= 0x02;
	if (blink)
		cmd |= 0x01;
	this->transmit(false, cmd);
}

void I2cHd44780::moveCursor(bool right) const // 0x10
{
	byte cmd = 0x10;
	if (right)
		cmd |= 0x04;
	this->transmit(false, cmd);
}

void I2cHd44780::moveScreen(bool right) const // 0x11
{
	byte cmd = 0x11;
	if (right)
		cmd |= 0x04;
	this->transmit(false, cmd);
}

void I2cHd44780::configureFunction(bool interface8, bool doubleline,
		bool font5x10) const // 0x20
{
	byte cmd = 0x20;
	if (interface8)
		cmd |= 0x10;
	if (doubleline)
		cmd |= 0x08;
	if (font5x10)
		cmd |= 0x04;
	this->transmit(false, cmd);
}

void I2cHd44780::setCGRam(byte *pFont, byte length) const // 0x40
{
	this->configureInput(true, false);
	this->transmit(false, 0x40);

	for (byte i = 0; i < length; i++)
	{
		this->transmit(true, pFont[i]);
	}
}

void I2cHd44780::setCursor(byte address) const // 0x80
{
	this->transmit(false, address | 0x80);
}

////////////////////
void I2cHd44780::putString(byte address, char *p, byte length) const
{
	char *pp = p;

	this->setCursor(address);

	while (length--)
	{
		this->transmit(true, *pp++);
	}
}

void I2cHd44780::putChar(byte address, char c) const
{
	this->putString(address, &c, 1);
}

void I2cHd44780::init()
{
	this->initHardware();

	byte *bar = (byte*) malloc(64);
	memcpy_P(bar, HD44780_BAR, 64);
	this->setCGRam(bar, 64);
	free(bar);

	this->configureDisplay(true, true, true);
}

void I2cHd44780::putCache() const
{
	for (byte r = 0; r < _row_count; r++)
		this->putString(
				pgm_read_byte_near((_col_count<=16?HD44780_ROW_ADDRESS_16:HD44780_ROW_ADDRESS_20) + r),
				_cache + _col_count * r, _col_count);
}

void I2cHd44780::printf(byte index, const char *__fmt, ...)
{
	if (index >= _cache_length)
		return;

	va_list ap;
	va_start(ap, __fmt);
	vsnprintf(_cache + index, _cache_length - index, __fmt, ap);
	va_end(ap);
}

void I2cHd44780::printf(const char *__fmt, ...)
{
	va_list ap;
	va_start(ap, __fmt);
	vsnprintf(_cache, _cache_length, __fmt, ap);
	va_end(ap);
}

void I2cHd44780::setCache(byte value)
{
	memset(_cache, value, _cache_length);
}

void I2cHd44780::setCache(byte index, byte value)
{
	if (index >= _cache_length)
		return;

	_cache[index] = value;
}

//////////////////////

void I2cHd44780::setBackLight(bool on)
{
	_backlight = on;
	twi.writeTo(_address, _backlight ? 0x08 : 0x00);
}
