#include "DotMatrixTest.h"

#include "Driver_HD44780.h"
#include "DotMatrix.h"
#include "Font0603.h"
#include "DotFont.h"
#include "DotString.h"

HD44780 lcd(13, 12, 11, 10, 9, 8, 4, 0x14);

DotMatrix dm = lcd.getDotMatrix();
DotFont df(dm);

void setup()
{
	lcd.init();
	df.setPattern(FONT_0603, FONT_0603_STATE);

	dm.clear();

	DotString ds(df, 8);
	ds.printf("%4d", 2360);
	ds.postAt(0x05, 0);
	lcd.convertDotMatrixToCache();

	lcd.printf(0x28, "THR.%d%% SPD.%3d km/h", 47, 107);
	lcd.printf(0x3c, "CLD.%d%% TMP.%2d/%2d %cC", 62, 90, 58, 0xdf);
	lcd.printf(0x00, "RPM.");
	lcd.putCache();
}

void loop()
{
//	static int i = 0;
//
//	dm.clear();
//
//	DotString ds(df, 8);
//	ds.printf("%4d", i);
//	ds.postAt(0, 3);
//	lcd.convertDotMatrixToCache();
//	//lcd.putCache();
//	i++;
//
//	delay(100);
}
