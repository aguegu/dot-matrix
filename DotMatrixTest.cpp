#include "DotMatrixTest.h"
#include "DotMatrix.h"
#include "Driver_PCD8544.h"

DotMatrix dm(48, 84);
Driver_PCD8544 lcd(dm, 2, 3, 4, 5, 6);

void setup()
{
	pinMode(7, OUTPUT);
	digitalWrite(7, HIGH);

	lcd.init();

	dm.clear();
	dm.setDot(0,0);
	dm.setDot(8,0);
	lcd.putDM();
}

void loop()
{

}
