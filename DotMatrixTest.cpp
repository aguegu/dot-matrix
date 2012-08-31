#include "DotMatrixTest.h"

#include "Driver_74HC595.h"

Driver_74HC595 chip(11, 13, 9, 8);
byte pCache[3];

void setup()
{
	pCache[0] = 0xfe;
	pCache[1] = 0xff;
	pCache[2] = 0x01;
}

void loop()
{
	chip.shiftSend(pCache,3);
	chip.shiftLatch();
	delay(0x100);
}
