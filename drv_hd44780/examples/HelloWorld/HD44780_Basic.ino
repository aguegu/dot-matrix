#include "drv_hd44780.h"

DrvHd44780 lcd(7, 6, 5, 4, 3, 2);

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
