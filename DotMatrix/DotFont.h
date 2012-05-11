/*
	DotFont.h
	DotFont Class for printing characters on DotMatrix
	library for Arduino to drive LED Dot Matrix Display dirven by 74HC595(column) and 74HC138(row)

	Created on: 2012-1-22
	Updated on: 2012-2-26
	Author: Weihong Guan
	Blog: http://aguegu.net
	E-mail: weihong.guan@gmail.com
	Code license: Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0)
	http://creativecommons.org/licenses/by-nc-sa/3.0/

	source hosting: http://code.google.com/p/aguegu-arduino-library/
*/

#ifndef DOTFONT_H_
#define DOTFONT_H_
#include "Arduino.h"
#include "DotMatrix.h"

class DotFont
{
public:

	DotFont(DotMatrix & pDM);
	DotFont(DotMatrix & pDM, byte * pattern, byte unitWidth, byte unitHeight, byte index, byte col, byte row, boolean direction = false);
	virtual ~DotFont();

	//void setDotMatrix(DotMatrix * pDM);
	void show();
	void setPattern(const uint8_t * pattern, const uint8_t * unitWidth, const uint8_t * unitHeight);
	void setIndex(byte index);
	void setDirection(boolean direction = false);
	void moveTo(byte col, byte row);
	void clear(byte col, byte row);
	void fill(byte col, byte row);

	byte calcFontRealWidth();
	byte getWidth();
	byte getHeight();

private:
	void showH();
	void showV();

	DotMatrix & _pDM;
	const uint8_t *_pattern;
	byte _unitWidth;
	byte _unitHeight;
	byte _col;
	byte _row;
	byte _index;
	boolean _direction;
};

#endif /* DOTFONT_H_ */