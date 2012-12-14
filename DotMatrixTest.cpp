#include "DotMatrixTest.h"
#include "DotMatrix.h"
#include "DotPattern.h"
#include "Driver_PCD8544.h"

#include "Pattern.h"

Driver_PCD8544 lcd(A5, A4, A3, A2, A1);
DotMatrix dm = lcd.getDM();
DotPattern dp(dm);

void setup()
{
	pinMode(A0, OUTPUT);
	digitalWrite(A0, HIGH);

	lcd.init();

	dm.clear();

	byte p[72];
	memcpy_P(p, PATTERN_CHAR, 72);
	dp.setPattern(p, 72, 3);
	dp.postAt(1, 0);

	memcpy_P(p, PATTERN_CHAR+72, 72);
	dp.setPattern(p, 72, 3);
	dp.postAt(8, 42);

}

void loop()
{
	lcd.putDM();
	dm.setMoveDirection(DotMatrix::BIT_IN_COL_NEGA);
	dm.move(true);
	dm.setMoveDirection(DotMatrix::BIT_IN_ROW_NEGA);
	dm.move(true);
	//delay(200);
}
