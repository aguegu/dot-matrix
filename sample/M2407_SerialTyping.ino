/*
	Created on: 2012-1-25
	Updated on: 2012-2-26
	Author: Weihong Guan
	Blog: http://aguegu.net
	E-mail: weihong.guan@gmail.com
	Code license: Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0)
	http://creativecommons.org/licenses/by-nc-sa/3.0/
 */

#include "DotMatrixTest.h"
#include "Driver_595_138.h"
#include "DotMatrix.h"
#include "DotString.h"

DotMatrix dm(24*1, 7);
Driver_595_138 dmd(dm, 11, 10, 9, 8, 7, 6, 5, 4);
DotString ds(dm);

extern HardwareSerial Serial;
byte index = 0;
char * s;

void setup()
{
	s = (char *) malloc(sizeof(char) * dm.countCol());
	dmd.setSpeed(0x200);

	Serial.begin(9600);
	dm.clear(false);
	dm.setDot(0,0,true);
	dm.setByte(0, 0xf0);
}

void loop()
{
	dmd.display(0x08);
}

void serialEvent()
{
	while (Serial.available())
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
