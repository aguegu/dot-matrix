#include "DotMatrixTest.h"
#include "DotMatrix3D.h"
#include "Driver_1818_138.h"

DotMatrix3D dm(8, 8, 8);
Driver_1818_138 cube(dm, A3, 8, 9, 10, 3, 4, 5, 11);

void setup()
{
	dm.clear(0x00);
	//dm.DotMatrix::setDot(0, 0, true);
	cube.setBrightness(0x20);

	for(byte i=0; i<8; i++)
		dm.setDot(i, i, i, true);
}

void loop()
{
	dm.setDot(random(8), random(8), 7, true);

	cube.display(0x04);
	dm.move(DotMatrix::Up, false);
}
