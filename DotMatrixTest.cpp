#include "DotMatrixTest.h"
#include "DotMatrix3D.h"
#include "Driver_1818_138.h"

DotMatrix3D dm(8, 8, 8);
Driver_1818_138 cube(dm, A3, 8, 9, 10, 3, 4, 5, 11);

void setup()
{
	dm.clear(0x00);
	dm.DotMatrix::setDot(0, 0, true);
	dm.setDot(0, 0, 0, true);
}

void loop()
{
	dm.move(DotMatrix::Right, false);

	cube.display(0x04);
}
