#include "DotMatrixTest.h"
#include "Driver_PCD8544_WithoutDotMatrix.h"

Driver_PCD8544_WithoutDotMatrix lcd;



void setup()
{
	pinMode(7, OUTPUT);
	digitalWrite(7, HIGH);

	lcd.init();

}

void loop()
{

}
