

#include "DotMatrixTest.h"
#include "Driver_595_138.h"
#include "DotMatrix.h"
#include "DotFont.h"
#include "DotString.h"
#include "Font0703.h"

DotMatrix dm(32, 8);
//Driver_595_138 dmd(dm, 10, 11, 13, 12, 7, 6, 5, 4);
Driver_595_138 dmd(dm, 8, 9, 11, 12, 7, 6, 5, 4);
DotFont df(dm);
DotString ds(df, dm.countCol(), true);

extern HardwareSerial Serial;
byte index = 0;

void setup()
{
	pinMode(8, OUTPUT);
	digitalWrite(8, HIGH);

	pinMode(9, OUTPUT);
	digitalWrite(9, LOW);

	dm.clear(0x00);
	dm.setDot(0,0);

	df.setPattern(FONT_0703, FONT_0703_STATE);
	ds.printf("Hi, world.");
	ds.postAt(0,0);

	dmd.setSpeed(0x200);

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
