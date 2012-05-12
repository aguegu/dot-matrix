#include "DotMatrixTest.h"

#include "DotMatrix.h"
#include "Driver_ST7920.h"

DotMatrix dm(128, 64);
ST7920 dmd(dm, 8, 9, 10, 11, 12, 13);
//DotString ds(dm);

char s0[] = "Agu's Mill";

void setup()
{
	dm.clear();

	for(byte i=0; i< 64; i++)
		dm.setDot(i,i);

	dmd.init();
	dmd.clear();
	//dmd.putImage();

}

void loop()
{
	dm.move(DotMatrix::Down, true);
	dmd.putImage();
	//delay(0);

}
