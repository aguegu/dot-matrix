#include "DotMatrixTest.h"
#include "Driver_PCD8544_WithoutDotMatrix.h"

Driver_PCD8544_WithoutDotMatrix lcd(2, 3, 4, 5, 6);



void setup()
{
	pinMode(7, OUTPUT);
	digitalWrite(7, HIGH);

	lcd.init();
}

void loop()
{

}
