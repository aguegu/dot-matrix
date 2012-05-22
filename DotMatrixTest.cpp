#include "DotMatrixTest.h"
#include "Driver_HD44780_WithoutDotMatrix.h"

HD44780_WithoutDotMatrix lcd(8, 9, 10, 11, 12, 13);
char s[] = "Hello, World.";
uint32_t num = 0;

void setup()
{
	lcd.init();
	lcd.printBigNumber(0, 1);
	lcd.putCache();
}

void loop()
{
	for (byte i = 0; i<10; i++)
	{
	lcd.printBigNumber(0, i);
	lcd.putCache();
	delay(1000);
	}
}
