/*
 * Lcd1602String.h
 *
 *  Created on: 2012-3-3
 *      Author: Agu
 */

#ifndef LCD1602STRING_H_
#define LCD1602STRING_H_

#include "arduino.h"
#include "Lcd1602.h"
#include "LcdFont.h"


class Lcd1602String
{
public:
	Lcd1602String(Lcd1602 & lcd, byte row_count = 2, byte col_count = 16);
	virtual ~Lcd1602String();
	void print();
	void write(char *p, byte length);
	void putChar(byte index, char c);
	void putChar(byte row, byte col, char c);
	void putBar(byte bar, byte col, byte row = 0);
	void putNumber(byte num, byte col, byte row = 0);
	void putNumChar(byte row, byte col, byte c);
	void printf(const char *__fmt, ...);
	void printf(byte index, const char *__fmt, ...);

	void clear();

private:
	char * _pScreen;
	Lcd1602 & _lcd;
	byte _col_count;
	byte _row_count;
	byte _length;
	byte _font_width;

};

#endif /* LCD1602STRING_H_ */
