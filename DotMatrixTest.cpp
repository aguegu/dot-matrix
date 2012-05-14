#include "DotMatrixTest.h"
#include "DotMatrix.h"
#include "Driver_HD44780.h"

DotMatrix dm(16, 6);
HD44780 lcd(dm, 8, 9, 10, 11, 12, 13);
char s[] = "Hello, World.";
uint32_t num=0;

void setup()
{
	dm.clear(0x00);
	lcd.init();

	//dm.setDot(0,0,true);

	lcd.convertDotMatrixToCache();
	//lcd.printf("%d", dm.countRow());
	lcd.putCache();
}


void loop()
{


}
