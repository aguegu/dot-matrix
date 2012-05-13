/*
 * Lcd1602String.cpp
 *
 *  Created on: 2012-3-3
 *      Author: Agu
 */

#include "Lcd1602String.h"
#include "string.h"

Lcd1602String::Lcd1602String(Lcd1602 & lcd, byte row_count, byte col_count):_lcd(lcd)
{
	_col_count = col_count;
	_row_count = row_count;
	_length = _col_count * _row_count + 1;
	_lcd = lcd;

	_lcd.init();
	byte *bar = (byte*)malloc(64);
	memcpy_P(bar, BAR, 64);
	_lcd.setCGRam(bar, 64);
	free(bar);

	_lcd.setDisplayMode(true, false, false);

	_font_width = pgm_read_byte_near(&FONT_NUM_WIDTH);

	_pScreen = (char *) malloc(sizeof(char) * _length);
	memset(_pScreen, 0x20, _length);
}

void Lcd1602String::print()
{
	for (byte r=0; r<_row_count; r++)
		_lcd.putString(pgm_read_byte_near(ROW_INDEX+r), _pScreen + _col_count * r, _col_count);
}

void Lcd1602String::write(char *p, byte length)
{
	memcpy(_pScreen, p, min(_length, length));
}

void Lcd1602String::printf(const char *__fmt, ...)
{
	va_list ap;
	va_start(ap, __fmt);
	vsnprintf(_pScreen, _length, __fmt, ap);
	//this->printf(0, __fmt, ap);
	va_end(ap);
}

void Lcd1602String::printf(byte index, const char *__fmt, ...)
{
	if (index >= _length) return;

	va_list ap;
	va_start(ap, __fmt);
	vsnprintf(_pScreen + index, _length - index, __fmt, ap);
	va_end(ap);
}

void Lcd1602String::putChar(byte index, char c)
{
	_pScreen[index] = c;
}

void Lcd1602String::putChar(byte row, byte col, char c)
{
	this->putChar(row*_col_count+col, c);
}

void Lcd1602String::putNumChar(byte row, byte col, byte c)
{
	this->putChar(row*_col_count+col, c + 0x30);
}

void Lcd1602String::putBar(byte bar, byte col, byte row)
{
	for (byte r = row; r<_row_count; r++)
	{
		this->putChar(r, col, bar & 0x07);
		bar >>= 3;
	}
}

void Lcd1602String::putNumber(byte num, byte col, byte row)
{
	byte index = num * _font_width;
	for (byte i=0; i<_font_width; i++)
		this->putBar(pgm_read_byte_near(FONT_NUM + index + i), col+i, row);
}

void Lcd1602String::clear()
{
	memset(_pScreen, 0, _length);
}

Lcd1602String::~Lcd1602String()
{
	free(_pScreen);
}

