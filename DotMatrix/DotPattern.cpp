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
	for (byte r = 0; r < _row_count; r++)
	{
		for (byte c = 0; c < _byte_in_row * 8; c++)
		{
			byte k = DotMatrix::reverseByte(pgm_read_byte_near(_pattern + r * _byte_in_row + (c >> 3)));
			if (boolean b = bitRead(k, c & 0x07))
				_dm.setDot(_col+c, _row+r, b);
		}
	}
}

void DotPattern::postAt(byte col, byte row)
{
	_col = col;
	_row = row;
}

void DotPattern::setPattern(const uint8_t * pattern, int length,
		byte byte_in_row)
{
	_pattern = pattern;
	_length = length;
	_byte_in_row = byte_in_row;
	_row_count = _length / byte_in_row;
}
