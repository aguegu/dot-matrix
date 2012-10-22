#include "DotMatrixTest.h"

#include "DotMatrix.h"
#include "Driver_ST7920.h"

ST7920 dmd(A5, A4, A3, A2, A1, A0);
DotMatrix dm = dmd.getDotMatrix();

volatile bool completed = false;

void setup()
{
	Serial.begin(115200);
	dm.clear();
	dmd.putDM();
}

void loop()
{
	if (completed)
	{
		dmd.putDM();
		completed = false;
	}
}

void serialEvent()
{
	static int index = 0;
	byte data = Serial.read();

	if (index == 0 && data == 0xf3)
	{
		index = 1;
	}
	else if (index)
	{
		if (index >= 1024)
		{
			index = 0;
			completed = true;
		}
		else
		{
			dm.setByte(index - 1, data);
			index = index + 1;
		}
	}
}
