#include "DotMatrixTest.h"
#include "DotMatrix3D.h"
#include "Driver_3D8.h"

DotMatrix3D dm(8, 8, 8);
Driver_3D8 cube(dm, A3, 8, 9, 10, 3, 4, 5, 11);

void setup()
{
	TCCR2B = (TCCR2B & 0xf8) | 0x02;

	dm.clear(0xff);
	//dm.DotMatrix::setDot(0, 0, true);
	cube.setBrightness(0xff);
	cube.setMode(0x02);

	for(byte i=0; i<8; i++)
		dm.setDot(i, i, 0, true);
}

void loop()
{

	dm.setDot(random(8), random(8), 7, true);

	cube.display(0x04);
	dm.move(DotMatrix::Up, false);

}
