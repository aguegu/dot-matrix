/*
 *  A3D8_master.ino
 *
 *	animation with the support of dot-matrix library
 *	master animation sample on arduino managing 3D8S 8x8x8 led cubic display
 *  The onboard arduino uno does both animation calc and led driving
 *
 *  Created on: 2012-7-11
 *	Author: Weihong Guan
 *	Blog: http://aguegu.net
 *	E-mail: weihong.guan@gmail.com
 *
 *	Code license: Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0)
 *	http://creativecommons.org/licenses/by-nc-sa/3.0/
 *	source host: https://github.com/aguegu/dot-matrix
 *
 */

#include "Driver_74HC595_SPI.h"

Driver_74HC595_SPI chip(SPI, 8, 9);

#define SECTION_COUNT 4
#define BW 0x20

byte led_count = SECTION_COUNT * 8;
word cache_count = SECTION_COUNT * BW;

byte *cache = (byte *) malloc(sizeof(byte) * cache_count);

void setBW(byte *p, byte index, byte bw)
{
	for (byte i = 0; i < BW && i < bw; i++)
	{
		p[i * SECTION_COUNT + index / 8] |= _BV(index % 8);
	}
}

void setup()
{
	chip.setOE(false);
	memset(cache, 0x00, cache_count);

//	setBW(cache, 31, 0x0f);
//	setBW(cache, 30, 0x01);

	for (byte i = 0; i < led_count; i++)
	{
		setBW(cache, i, 0);
	}
}

void loop()
{
	static word indent = 0;
	chip.shiftSend(cache + indent, 4);
	chip.shiftLatch();

	delay(0x80);

	indent += SECTION_COUNT;
	if (indent == cache_count)
		indent = 0x00;
}
