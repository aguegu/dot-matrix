#include "DotMatrixTest.h"

#include "DotMatrix.h"
#include "Driver_ST7920.h"
#include "DotFont.h"
#include "DotString.h"

#include "Font0703.h"
#include "Font0705.h"
#include "Font0503.h"

DotMatrix dm(128, 64);
ST7920 dmd(dm, 8, 9, 10, 11, 12, 13);

void setup()
{
	dm.clear();

	DotFont df(dm);
	df.setPattern(FONT_0703, FONT_0703_STATE);
	for (byte i = 0; i < 8; i++)
	{
		DotString ds(df, 32, true);
		ds.printf("Hello,%d", 2012 + i);
		ds.print(8 * i, 8 * i);
	}

	df.setPattern(FONT_0705, FONT_0705_STATE);
	for (byte i = 0; i < 8; i++)
	{
		DotString ds(df, 32, true);
		ds.printf("%d", i);
		ds.print(120, 8 * i);
	}

	df.setPattern(FONT_0503, FONT_0503_STATE);
	for (byte i = 0; i < 8; i++)
	{
		DotString ds(df, 32, true);
		ds.printf("%d", i);
		ds.print(116, 8 * i + 2);
	}


	dmd.init();
	dmd.clear();
	dmd.putImage();
}

void loop()
{

}
