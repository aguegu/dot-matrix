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

void DotPattern::setPattern(const uint8_t * pattern, int length, byte byte_in_row)
{
	_pattern = pattern;
	_length = length;
	_byte_in_row = byte_in_row;
	_row_count = length / byte_in_row;
}
