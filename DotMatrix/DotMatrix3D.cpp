/*
 * DotMatrix3D.cpp
 *
 *  Created on: 2012-5-29
 *      Author: gmb-gwh
 */

#include "DotMatrix3D.h"

DotMatrix3D::DotMatrix3D(byte block_count): DotMatrix(block_count * BLOCK_COLUMN_COUNT, BLOCK_EDGE_LENGTH)
{

}

DotMatrix3D::~DotMatrix3D()
{
	// TODO Auto-generated destructor stub
}

void DotMatrix3D::setDot(byte x, byte y, byte z, bool on)
{
	if (y >= BLOCK_EDGE_LENGTH || z >= BLOCK_EDGE_LENGTH) return;

	byte col = this->convertCol(x, z);

	//DotMatrix::setDot(block_id * BLOCK_COLUMN_COUNT + col_x + col_y * BLOCK_EDGE_LENGTH, on);
	this->DotMatrix::setDot(col, y, on);
}

byte DotMatrix3D::convertCol(byte x, byte z)
{
	return((x<<3)+z);
}
