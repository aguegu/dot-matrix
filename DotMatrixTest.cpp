#include "DotMatrixTest.h"
#include "DotMatrix.h"
#include "Driver_1818_138.h"

DotMatrix dm(64, 8);
Driver_1818_138 cube(dm, A3, 8, 9, 10, 3, 4, 5, 11);

void setup()
{
	dm.clear(0x00);
	dm.setDot(0, random(8), true);
}

void loop()
{
	dm.move(DotMatrix::Right, false);

	cube.display(0x04);
}
