/*
 DotMatrix.h
 DotMatrix Class for modeling on the Dot Matrix, providing methods like dot control, draw rectangle, line
 Created on: 2012-01-16
 Updated on: 2012-05-14

 library for Arduino for Dot Matrix Display, support driver by 74HC595 and 74HC138, ST7920, HD47780
 Author: Weihong Guan
 Blog: http://aguegu.net
 E-mail: weihong.guan@gmail.com
 Code license: Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0)
 http://creativecommons.org/licenses/by-nc-sa/3.0/

 source host: https://github.com/aguegu/dot-matrix
 */

#ifndef DOTMATRIX_H_
#define DOTMATRIX_H_

#include "Arduino.h"

class DotMatrix
{
public:
	DotMatrix(byte col_count, byte row_count);
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
		COL_NEGA, COL_POSI, ROW_NEGA, ROW_POSI
	};

	void move(Direction d, boolean recycle = false);

	byte * output() const;
	byte countCol() const;
	byte countRow() const;
	word countBytes() const;
	byte countBytePerRow() const;

private:
	byte _col_count;
	byte _row_count;
	byte _bytes_per_row;
	word _bytes_length;

	byte * _pScreen;

	word getIndex(byte col, byte row) const;
	void moveColNega(bool recycle);
	void moveColPosi(bool recycle);
	void moveRowNega(bool recycle);
	void moveRowPosi(bool recycle);

	void moveColNegaForByte(bool recycle);
	void moveColPosiForByte(bool recycle);

	void moveByteNegaInRow(bool recycle);
	void moveBytePosiInRow(bool recycle);

	void moveNegaInByte(bool recycle);
	void movePosiInByte(bool recycle);
};

#endif /* DOTMATRIX_H_ */
