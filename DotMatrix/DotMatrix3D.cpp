/*
 * DotMatrix3D.cpp
 *
 *  Created on: 2012-5-29
 *      Author: gmb-gwh
 */

#include "DotMatrix3D.h"

DotMatrix3D::DotMatrix3D(byte block_count) :
		DotMatrix(block_count * BLOCK_COLUMN_COUNT, BLOCK_EDGE_LENGTH)
{

}

DotMatrix3D::~DotMatrix3D()
{
	// TODO Auto-generated destructor stub
}

void DotMatrix3D::setDot(byte x, byte y, byte z, bool on)
{
	if (y >= BLOCK_EDGE_LENGTH || z >= BLOCK_EDGE_LENGTH)
		return;

	byte col = this->convertCol(x, z);

	//DotMatrix::setDot(block_id * BLOCK_COLUMN_COUNT + col_x + col_y * BLOCK_EDGE_LENGTH, on);
	this->DotMatrix::setDot(col, y, on);
}

byte DotMatrix3D::convertCol(byte x, byte z)
{
	return ((x << 3) + z);
}

void DotMatrix3D::setMoveDirection(Direction3D d)
{
	switch (d)
	{
	case Z_NEGA:
		_funMoveDirection = &DotMatrix3D::moveBitInByteNega;
		break;
	case Z_POSI:
		_funMoveDirection = &DotMatrix3D::moveBitInBytePosi;
		break;
	case Y_NEGA:
		_funMoveDirection = &DotMatrix3D::moveBitInRowNega;
		break;
	case Y_POSI:
		_funMoveDirection = &DotMatrix3D::moveBitInRowPosi;
		break;
	case X_NEGA:
		_funMoveDirection = &DotMatrix3D::moveByteInColNega;
		break;
	case X_POSI:
		_funMoveDirection = &DotMatrix3D::moveByteInColPosi;
		break;
	}
}


