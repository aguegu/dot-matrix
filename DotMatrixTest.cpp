#include "DotMatrixTest.h"
#include "Driver_PCD8544_WithoutDotMatrix.h"

Driver_PCD8544_WithoutDotMatrix lcd;



void setup()
{
	lcd.init();
	pinMode(2, OUTPUT);
	digitalWrite(2, HIGH);
}

void loop()
{

}
