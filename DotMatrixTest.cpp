#include "DotMatrixTest.h"
#include "DotMatrix.h"
#include "DotFont.h"
#include "DotString.h"
#include "Driver_PCD8544.h"

#include "Font0704.h"


DotMatrix dm(48, 84);
Driver_PCD8544 lcd(dm, 2, 3, 4, 5, 6);


void setup()
{
	pinMode(7, OUTPUT);
	digitalWrite(7, HIGH);

	lcd.init();

	dm.clear();

	DotFont df(dm);
	df.setPattern(FONT_0704, FONT_0704_STATE);
	DotString ds(df, 32, true);

	ds.printf("Hello, world.");
	ds.postAt(0,0);

	ds.printf("Font Display");
	ds.postAt(0, 9);

	ds.printf("on Nokia 5110,");
	ds.postAt(0, 18);

	ds.printf("driven by");
	ds.postAt(0, 27);

	ds.printf("Arduino.");
	ds.postAt(0, 36);

	ds.printf("Cool, right?");
	ds.postAt(0, 45);

	ds.printf("aGuegu.net");
	ds.postAt(4, 63);

	ds.printf("%2d-%02d, %d", 5, 31, 2012);
	ds.postAt(8, 72);

	lcd.putDM();
}

void loop()
{

}
