#include "DotMatrixTest.h"

#include "Driver_HD44780_Basic.h"

HD44780_Basic lcd(13, 12, 11, 10, 9, 8);

void setup()
{
	lcd.init();
}

void loop()
{
	static word val = 0;
	lcd.printf("Hello, world.");
	lcd.printf(0x18, "%8d", val);
	lcd.putCache();

	val++;
	delay(500);
}
