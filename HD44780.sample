#include "DotMatrixTest.h"

#include "D"
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
