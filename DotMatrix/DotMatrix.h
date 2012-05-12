/*
	DotMatrix.cpp
	DotMatrix Class for modeling on the Dot Matrix, providing methods like dot control, and serial output
	library for Arduino to drive LED Dot Matrix Display dirven by 74HC595(column) and 74HC138(row)

	Created on: 2012-1-16
	Updated on: 2012-2-26
	Author: Weihong Guan
	Blog: http://aguegu.net
	E-mail: weihong.guan@gmail.com
	Code license: Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0)
	http://creativecommons.org/licenses/by-nc-sa/3.0/

	source hosting: http://code.google.com/p/aguegu-arduino-library/
 */

#ifndef DOTMATRIX_H_
#define DOTMATRIX_H_

#include "Arduino.h"

class DotMatrix
{
public:
	DotMatrix(byte colCount, byte rowCount);
	virtual ~DotMatrix();

	void clear(byte c = 0x00);
	void setByte(word index, byte value);

	void reverseDot(byte col, byte row);
	void setDot(byte col, byte row, boolean b = true);
	boolean getDot(byte col, byte row) const;

	void setLine(byte cA, byte rA, byte cB, byte rB, bool on = true);
	void setRect(byte cA, byte rA, byte cB, byte rB, bool on = true);

	enum Direction
	{
		Left, Right, Up, Down
	};

	void move(Direction d, boolean recycle = false);

	byte * output() const;
	byte countCol() const;
	byte countRow() const;
	word countBytes() const;
	byte countBytePerRow() const;

private:
	byte _colCount;
	byte _rowCount;
	byte _bytesPerRow;
	word _bytesLength;

	byte * _pScreen;

	word getIndex(byte col, byte row) const;
};

#endif /* DOTMATRIX_H_ */
