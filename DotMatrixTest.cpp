#include "DotMatrixTest.h"

#include "DotMatrix.h"
#include "Driver_ST7920.h"
#include "DotFont.h"
#include "DotString.h"

#include "Font0703.h"
#include "Font0704.h"
#include "Font0705.h"
#include "Font0503.h"

ST7920 dmd(A5, A4, A3, A2, A1, A0);
DotMatrix dm = dmd.getDotMatrix();

void setup()
{
	dm.clear();

//	for (word i = 0; i < 256; i++)
//	{
//		dm.setByte(i, i);
//	}

	dm.setByte(0, 2U);

	DotFont df(dm);
	df.setPattern(FONT_0703, FONT_0703_STATE);
	df.setVertical(false);

	df.setPattern(FONT_0705, FONT_0705_STATE);
	for (byte i = 0; i < 10; i++)
	{
		DotString ds(df, 32, true);
		ds.printf("%d", i);
		ds.postAt(i * 6, 0);
	}

	df.setPattern(FONT_0503, FONT_0503_STATE);
	for (byte i = 0; i < 10; i++)
	{
		DotString ds(df, 32, true);
		ds.printf("%d", i);
		ds.postAt(i * 6, 8);
	}

	df.setPattern(FONT_0704, FONT_0704_STATE);
	df.setVertical();
	DotString hds(df, 32, true);
	hds.printf("%s", "Lcd12864 driven by dot-matrix");
	hds.postAt(18, 2);

	hds.printf("%s", "library for Arduino.");
	hds.postAt(18, 12);

	hds.printf("%s", "Developed by W.H. Guan");
	hds.postAt(40, 24);

	dm.setRect(32, 40, 108, 56);
	dm.setRect(34, 42, 106, 54, false);

	hds.printf("%s", "aGuegu.net");
	hds.postAt(40, 45);

	dm.setLine(20, 48, 30, 54);
	dm.setLine(16, 54, 30, 54);
	dm.setLine(20, 60, 30, 54);

	dm.setLine(120, 32, 110, 40);
	dm.setLine(126, 40, 110, 40);
	dm.setLine(120, 48, 110, 40);

	dmd.putDM();
}

void loop()
{

}
