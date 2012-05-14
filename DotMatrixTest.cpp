#include "DotMatrixTest.h"
#include "DotMatrix.h"
#include "DotFont.h"
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

	byte j=0;
	for (byte i = 0; i < 4; i++)
	{
		df.setChar('2' + i);
		df.postAt(j, 0);
		df.print();
		j+= df.calcFontRealWidth() + 1;
	}

	lcd.convertDotMatrixToCache();
	lcd.putCache();
}

void loop()
{

}
