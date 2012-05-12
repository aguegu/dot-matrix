/*
	DotString.cpp
	DotString Class is an array of DotFont0704 and provides a display method to DotMatrix
	library for Arduino to drive LED Dot Matrix Display dirven by 74HC595(column) and 74HC138(row)

	Created on: 2012-1-25
	Updated on: 2012-2-26
	Author: Weihong Guan
	Blog: http://aguegu.net
	E-mail: weihong.guan@gmail.com
	Code license: Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0)
	http://creativecommons.org/licenses/by-nc-sa/3.0/

	source hosting: http://code.google.com/p/aguegu-arduino-library/
 */
#include "DotString.h"
#include "DotFont.h"

DotString::DotString(DotFont & df, byte length, bool smart_width): _df(df)
{
	_length = length;
	_smart_width = smart_width;
	_p = (char *)malloc(sizeof(char)*_length);
}

DotString::~DotString()
{
	free(_p);
}

void DotString::printf(const char *__fmt, ...)
{
	va_list ap;
	va_start(ap, __fmt);
	vsnprintf(_p, _length, __fmt, ap);
	va_end(ap);
}

void DotString::print(byte col, byte row)
{
	byte cursor = col;
	char *p = _p;

	while(*p)
	{
		_df.setChar(*(p++));
		_df.postAt(cursor , row);
		_df.print();
		cursor += _smart_width? _df.calcFontRealWidth()+1: _df.getWidth() + 1;

	}
}
