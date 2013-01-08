#include "DotMatrixTest.h"
#include "I2cHd44780.h"

I2cHd44780 lcd(0x27);

void setup()
{
	lcd.init();
	lcd.setBackLight(false);
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
