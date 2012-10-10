/*
 * DotPattern.cpp
 *
 *  Created on: 2012-7-1
 *      Author: Agu
 */

#include "DotPattern.h"

DotPattern::DotPattern(DotMatrix & dm) :
		_dm(dm)
{

}

DotPattern::~DotPattern()
{

}

void DotPattern::print()
{
	word index = 0;
	byte row = _row;
	for (byte r = _row_count; r--;)
	{
		for (byte col = _col, c = _byte_in_row; c--;)
		{
			byte k = DotMatrix::reverseByte(pgm_read_byte_near(_pattern + index++));
			_dm.putByte(col, row, k);
			col += 8;
		}
		row++;
	}
}

void DotPattern::postAt(byte col, byte row)
{
	_col = col;
	_row = row;
	this->print();
}

void DotPattern::setPattern(const uint8_t * pattern, int length,
		byte byte_in_row)
{
	_pattern = pattern;
	_length = length;
	_byte_in_row = byte_in_row;
	_row_count = _length / byte_in_row;
}
