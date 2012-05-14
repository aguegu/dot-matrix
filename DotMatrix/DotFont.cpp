/*
 DotFont.cpp
 DotFont Class for printing characters on DotMatrix
 Created on: 2012-01-22
 Updated on: 2012-05-14

 library for Arduino for Dot Matrix Display, support driver by 74HC595 and 74HC138, ST7920, HD47780
 Author: Weihong Guan
 Blog: http://aguegu.net
 E-mail: weihong.guan@gmail.com
 Code license: Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0)
 http://creativecommons.org/licenses/by-nc-sa/3.0/

 source host: https://github.com/aguegu/dot-matrix
 */

#include "DotFont.h"

byte DotFont::getWidth() const
{
	return _unitWidth;
}

byte DotFont::getHeight() const
{
	return _unitHeight;
}

boolean DotFont::getVertical() const
{
	return _vertical;
}

byte DotFont::getMaxCol() const
{
	return _dm.countCol() - 1;
}

byte DotFont::getMaxRow() const
{
	return _dm.countRow() - 1;
}

DotFont::DotFont(DotMatrix & dm) :
		_dm(dm)
{
	_col = _row = _index = 0;
	_vertical = true;
}

DotFont::~DotFont()
{
	// TODO Auto-generated destructor stub
}

void DotFont::setPattern(const uint8_t * pattern, const uint8_t * pattern_state)
{
	_pattern = pattern;
	_unitWidth = pgm_read_byte_near(pattern_state);
	_unitHeight = pgm_read_byte_near(pattern_state + 1);
	_patternIndent = pgm_read_byte_near(pattern_state + 2);
	_patternLength = pgm_read_byte_near(pattern_state + 3);
}

void DotFont::setChar(char chr)
{
	_index = (chr - _patternIndent) % _patternLength;
}

void DotFont::setVertical(boolean vertical)
{
	_vertical = vertical;
}

void DotFont::postAt(byte col, byte row)
{
	_col = col;
	_row = row;
}

void DotFont::clear(bool on) const
{
	if (_vertical)
		_dm.setRect(_col, _row, _col + _unitWidth, _row + _unitHeight, on);
	else
		_dm.setRect(_row, _dm.countRow() - _col - 1, _row + _unitHeight,
				_dm.countRow() - _col - 1 - _unitWidth, on);
}

void DotFont::print() const
{
	_vertical ? showV():showH();
}

void DotFont::showH() const
{
	for (byte c = 0; c < _unitWidth; c++)
	{
		for (byte r = 0; r < _unitHeight; r++)
		{
			if (boolean b = bitRead(pgm_read_byte_near(_pattern + _unitWidth * _index + c), r))
				_dm.setDot(_row + r, _dm.countRow() - _col - 1 - c, b);
		}
	}

}

void DotFont::showV() const
{
	for (byte c = 0; c < _unitWidth; c++)
	{
		for (byte r = 0; r < _unitHeight; r++)
		{
			if (boolean b = bitRead(pgm_read_byte_near(_pattern + _unitWidth * _index + c), r))
				_dm.setDot(_col + c, _row + r, b);
		}
	}
}

byte DotFont::calcFontRealWidth() const
{
	byte i = _unitWidth - 1;

	while (pgm_read_byte_near(_pattern + _unitWidth * _index + i) == 0 && i)
		i--;
	return i + 1;
}

