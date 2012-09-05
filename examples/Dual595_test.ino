#include "DotMatrixTest.h"

#include "Driver_Dual595.h"
#include "DotMatrix.h"
#include "DotFont.h"
#include "DotString.h"

#include "Font0703.h"

Driver_Dual595 dmd(9, 8, 7, 6, 5);
DotMatrix dm = dmd.getDotMatrix();

void setup()
{
	dm.clear(0x00);
	DotFont df(dm);
	df.setPattern(FONT_0703, FONT_0703_STATE);
	DotString ds(df, 16, true);
	ds.printf("aGuegu.net");
	dm.setRect(0, 0, 47, 11);
	dm.setRect(1, 1, 46, 10, false);

	ds.postAt(4, 3);
}

void loop()
{
	dmd.display();
}
