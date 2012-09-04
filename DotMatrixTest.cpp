#include "DotMatrixTest.h"

#include "Driver_Dual595.h"
#include "DotMatrix.h"

DotMatrix dm(24, 24);
Driver_Dual595 dmd(dm, 9, 8, 7, 6, 5);

void setup()
{
	dm.clear(0x00);
	for (byte i = 0; i < dm.countBytes(); i++)
		dm.setByte(i, i);
}

void loop()
{
	dmd.display();
	//delay(200);
}
