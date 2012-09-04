#include "DotMatrixTest.h"

#include "DotMatrix.h"
#include "Driver_3W1608.h"
#include "DotFont.h"
#include "DotString.h"

#include "Font0703.h"

DotMatrix dm(16,8);
Driver_3W1608 dmd(dm);

void setup()
{
	dm.clear();
	DotFont df(dm);
	df.setPattern(FONT_0703, FONT_0703_STATE);
	DotString ds(df, 8, true);
	ds.printf("boxz");
	ds.postAt(0,1);
}

void loop()
{
	dmd.display();
}
