#include "DotMatrixTest.h"

#include "Driver_HD44780_Basic.h"

HD44780_Basic lcd(8, 9, 10, 11, 12, 13);

void setup()
{
	lcd.init();
	lcd.printf("hello, world.");
	lcd.printf(0x10, " hello, world.");
	lcd.putCache();
}

void loop()
{
	static int value = 0x00;
	lcd.setCache();
	lcd.printf(0x04, "hello, world.");
	lcd.printf(0x10, "%d", value++);
	lcd.putCache();
	delay(100);
}
