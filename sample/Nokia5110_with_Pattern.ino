#include "DotMatrixTest.h"
#include "DotMatrix.h"
#include "DotPattern.h"
#include "Driver_PCD8544.h"

#include "Pattern.h"

DotMatrix dm(48, 84);
Driver_PCD8544 lcd(dm, 2, 3, 4, 5, 6);
DotPattern dp(dm);

void setup()
{
	pinMode(7, OUTPUT);
	digitalWrite(7, HIGH);

	lcd.init();

	dm.clear();

	dp.setPattern(PATTERN_CHAR,288,6);
	dp.postAt(8,1);
	dp.print();

}

void loop()
{
	lcd.putDM();
	delay(1000);
}
