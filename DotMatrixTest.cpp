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
	dm.setMoveDirection(DotMatrix::BIT_IN_COL_NEGA);
	dp.setPattern(PATTERN_CHAR,72,3);
	dp.postAt(0, 0);
	dp.print();

	dp.setPattern(PATTERN_CHAR+72,72,3);
		dp.postAt(8, 42);
		dp.print();
}

void loop()
{
	lcd.putDM();
//	dm.setMoveDirection(DotMatrix::BIT_IN_COL_NEGA);
//	dm.move(true);
//	dm.setMoveDirection(DotMatrix::BIT_IN_ROW_NEGA);
//	dm.move(true);
	delay(200);
}
