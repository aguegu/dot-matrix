#include "DotMatrixTest.h"
#include "DotMatrix.h"
#include "Driver_HD44780.h"

DotMatrix dm(16, 6);
HD44780 lcd(dm, 8, 9, 10, 11, 12, 13);
char s[] = "Hello, World.";
uint32_t num=0;

void setup()
{
	lcd.init();
	lcd.setDisplayMode(true, false, false);
}


void loop()
{
	lcd.putString(0x40, s, sizeof(s)-1);
	uint32_t t = num;
	for(byte i=0; i<10; i++)
	{
		lcd.putChar(15-i, (t % 10)+0x30);
		t /= 10;
		if (t==0) break;
	}
	num++;
	delay(200);
}
