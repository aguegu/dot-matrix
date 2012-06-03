#include "DotMatrixTest.h"

#include "Driver_HD44780.h"
#include "DotMatrix.h"

DotMatrix dm(16, 6);
HD44780 lcd(dm, 8, 9, 10, 11, 12, 13);

void setup()
{
	lcd.printf("Hello, World.");
	lcd.putCache();

	dm.clear();
	dm.setDot(0,0);
	dm.setDot(dm.countCol()-1, dm.countRow() - 1);
	lcd.convertDotMatrixToCache();
	lcd.putCache();

}

void loop()
{

}
