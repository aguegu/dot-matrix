#include "DotMatrixTest.h"
#include "DotMatrix.h"
#include "Driver_HD44780.h"

DotMatrix dm(16, 6);
HD44780 lcd(dm, 8, 9, 10, 11, 12, 13);

void setup()
{
	lcd.init();
	lcd.printf("hello, world.");
	lcd.printf(0x10, " hello, world.");

	for (byte i=0; i<8; i++)
		lcd.setCache(i, i);

	lcd.putCache();
}

void loop()
{
/*
	static int value = 0x00;
	lcd.setCache();
	lcd.printf(0x04, "hello, world.");
	lcd.printf(0x10, "%d", value++);
	lcd.putCache();
	delay(100);
*/
}
