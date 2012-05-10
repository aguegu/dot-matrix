/*
	Sample of 3 sections of M2407 DotMatrix Display to
	received string (end with "new line") from Arduino Serial Monitor and print it out.

	Created on: 2012-1-25
	Updated on: 2012-2-26
	Author: Weihong Guan
	Blog: http://aguegu.net
	E-mail: weihong.guan@gmail.com
	Code license: Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0)
	http://creativecommons.org/licenses/by-nc-sa/3.0/

	source hosting: http://code.google.com/p/aguegu-arduino-library/
 */

#include "DotMatrixTest.h"
#include "DotMatrixDriver.h"
#include "DotMatrix.h"
#include "DotString.h"

DotMatrix dm(24*1, 7);
DotMatrixDriver dmd(dm, 11, 10, 9, 8, 7, 6, 5, 4);
DotString ds(dm);

extern HardwareSerial Serial;
byte index = 0;
char * s;

void setup()
{
	s = (char *) malloc(sizeof(char) * dm.countCol());
	dmd.setSpeed(0x200);

	Serial.begin(9600);
	dm.clear(true);
}

void loop()
{
	dmd.display(0x08);
}

void serialEvent()
{
	while (Serial.available() > 0)
	{
		if (index < dm.countCol())
		{
			byte cData = Serial.read();

			s[index] = cData;
			index++;

			if (cData == 0x0A)
			{
				s[index-1] = 0;
				ds.printString(s);
				Serial.println(s);
				index = 0;
			}
		}
	}
}

