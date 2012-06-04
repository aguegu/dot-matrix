/*
	Created on: 2012-01-25
	Updated on: 2012-06-03
	Author: Weihong Guan
	Blog: http://aguegu.net
	E-mail: weihong.guan@gmail.com
	Code license: Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0)
	http://creativecommons.org/licenses/by-nc-sa/3.0/
 */

#include "DotMatrixTest.h"
#include "Driver_595_138.h"
#include "DotMatrix.h"
#include "DotFont.h"
#include "DotString.h"
#include "Font0703.h"

DotMatrix dm(24*1, 7);
Driver_595_138 dmd(dm, 11, 10, 9, 8, 7, 6, 5, 4);


DotFont df(dm);
DotString ds(df, dm.countCol(), true);


extern HardwareSerial Serial;
byte index = 0;

void setup()
{
	dm.clear(0x00);

	df.setPattern(FONT_0703, FONT_0703_STATE);
	ds.printf("Hello.");
	ds.postAt(0,0);

	dmd.setSpeed(0x800);
	Serial.begin(9600);
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

			ds.setChar(index, cData);
			index++;

			if (cData == 0x0A)
			{
				dm.clear();
				ds.setChar(index-1, 0);
				ds.postAt(0,0);
				Serial.println(ds.getString());
				index = 0;
			}
		}
	}
}


