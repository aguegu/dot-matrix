#include "DotMatrixTest.h"
#include "dot-matrix.h"
#include "dot-pattern.h"
#include "drvdm_pcd8544.h"

#include "hpattern.h"

DrvDmPcd8544 lcd(7, 6, 5, 4, 3);
DotMatrix dm = lcd.getDM();
DotPattern dp(dm);

void setup()
{
	pinMode(2, OUTPUT);
	digitalWrite(2, HIGH);	// background led

	lcd.init();

	dm.clear();

	byte p[72];
	memcpy_P(p, H_PATTERN, 72);
	dp.setPattern(p, 72, 3);
	dp.postAt(0, 0);

	memcpy_P(p, H_PATTERN+72, 72);
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
	delay(200);
}
