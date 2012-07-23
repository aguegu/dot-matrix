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

#include "Driver_74HC595.h"

Driver_74HC595 chip(4, 7, 6, 5);
byte cache[4];

void setup()
{
	chip.setOE(false);

}

void loop()
{
	static byte tmp = 0x01;

	memset(cache, tmp, 4);

	chip.shiftSendRev(cache, 4);
	chip.shiftLatch();

	tmp <<= 1;

	delay(10);

	if (tmp == 0x00) tmp = 0x01;
}
