/*
 * record_3d8.cpp
 *
 *  Created on: Mar 29, 2013
 *      Author: agu
 */

#include "record_3d8.h"

const unsigned char Record3d8::c_on[5] = { 0xe2, 0x96, 0xa0, 0x20, 0x00 };
const unsigned char Record3d8::c_off[5] = { 0xe2, 0x96, 0xa1, 0x20, 0x00 };

Record3d8::Record3d8(byte length) :
		_length(length)
{
	_p = (byte*) malloc(sizeof(byte) * (length + 8));
	memset(_p, 0x00, _length + 8);
	_p[0] = 0xf2;
}

Record3d8::~Record3d8()
{
	free(_p);
}

void Record3d8::sendGlobal(byte c)
{
	memset(_p + 8, c, _length);
}

void Record3d8::sendColumn(byte col, byte value)
{
	*(_p + 8 + col) = value;
}

void Record3d8::sendBatch(const byte *p, byte length)
{
	memcpy(_p + 8, p, min(_length, length));
}

void Record3d8::sendMode(InputMode mode)
{
	*(_p + 1) = (byte) mode;
}

void Record3d8::sendBrightness(byte brightness)
{
	*(_p + 2) = brightness;
}

void Record3d8::sendBgLed(byte bg_led_configure)
{
	*(_p + 3) = bg_led_configure;
}

void Record3d8::sendDelay(word span)
{
	*(_p + 4) = highByte(span);
	*(_p + 5) = lowByte(span);
}

byte * Record3d8::output()
{
	return _p;
}

void Record3d8::init()
{
	initscr();
	cbreak();
	noecho();	
}

void Record3d8::display()
{
	for (int r = 0; r < 8; r++) {
		move(r, 0);
		for (int c = 0; c < 64; c++) {
			if (c % 8 == 0) printw(" ");
			printw("%s", bitRead(*(_p + 8 + r * 8 + c / 8), c % 8)? c_on: c_off);
		}
	}

	word delay = makeWord(*(_p + 4), *(_p + 5));

	move(8, 0);
	printw("mode: %02x, brightness: 0x%02x, led: %s%s, delay: 0x%04x", _p[1], _p[2], bitRead(_p[3], 0)? c_on:c_off, bitRead(_p[3], 0)? c_on:c_off, delay);

	refresh();
	usleep(delay * 1000);
}

void Record3d8::terminate()
{
	endwin();
}
