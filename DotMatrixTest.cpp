#include "DotMatrixTest.h"
#include "DotMatrix.h"
#include "DotFont.h"
#include "DotString.h"
#include "Driver_HD44780.h"

#include "Font0603.h"

DotMatrix dm(16, 6);

HD44780 lcd(dm, 8, 9, 10, 11, 12, 13);
char s[] = "Hello, World.";
uint32_t num = 0;

void setup()
{
	dm.clear(0x00);
	lcd.init();

	DotFont df(dm);
	df.setPattern(FONT_0603, FONT_0603_STATE);

	DotString ds(df,8);
	ds.printf("%4d", 1);
	ds.postAt(0,0);

	lcd.convertDotMatrixToCache();
	lcd.putCache();
}

void loop()
{

}
