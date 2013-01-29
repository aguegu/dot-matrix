/*
 * A3D8_Master_SPI.cpp
 *
 *  Created on: 2012-7-27
 *      Author: Agu
 */

#include "DotMatrixTest.h"
#include "dot-matrix.h"
#include "dot-pattern.h"
#include "pin_op.h"

#include "hfont_12x7.h"

DotMatrix dm(48, 12);
DotPattern dp(dm);
byte p[12];

void transfer(byte * data, byte length)
{
	pinClear(2);

	SPDR = 0xf2;
	loop_until_bit_is_set(SPSR, SPIF);
	delayMicroseconds(0x30);

	while (length--)
	{
		SPDR = *data++;
		loop_until_bit_is_set(SPSR, SPIF);
		delayMicroseconds(0x30);
	}

	pinSet(2);
}

void setup()
{
	delay(1000);

	pinMode(SS, OUTPUT);
	pinMode(MOSI, OUTPUT);
	pinMode(MISO, INPUT);
	pinMode(SCK, OUTPUT);

	digitalWrite(SS, HIGH);
	pinMode(9, OUTPUT);
	digitalWrite(9, LOW);

	// Speed
	sbi(SPSR, SPI2X);
	cbi(SPCR, SPR1);
	sbi(SPCR, SPR0);

	sbi(SPCR, MSTR);
	sbi(SPCR, SPE);

	pinMode(2, OUTPUT);

}

void loop()
{
	static byte t = 0;

	dm.clear();
	for (byte i = 0; i < 6; i++)
	{
		memcpy_P(p, HFONT_12X7 + 12 * ((i + t) % 10), 12);
		dp.setPattern(p, 12, 1);
		dp.postAt(8 * i, 0);
	}

	transfer(dm.output(), dm.countBytes());
	delay(80);

	t++;
}

