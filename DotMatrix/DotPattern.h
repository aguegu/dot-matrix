/*
 * DotPattern.h
 *
 *  Created on: 2012-7-1
 *      Author: Agu
 */

#ifndef DOTPATTERN_H_
#define DOTPATTERN_H_

#include "Arduino.h"
#include "DotMatrix.h"

class DotPattern
{
public:
	DotPattern(DotMatrix & dm);
	virtual ~DotPattern();
	void setPattern(const uint8_t * pattern, int length, byte byte_in_row);
	void postAt(byte col, byte row);

private:
	DotMatrix & _dm;
	byte _byte_in_row;
	byte _row_count;
	byte _col;
	byte _row;
	int _length;
	const uint8_t *_pattern;
	void print();
};

#endif /* DOTPATTERN_H_ */
