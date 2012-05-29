/*
 * DotMatrix3D.cpp
 *
 *  Created on: 2012-5-29
 *      Author: gmb-gwh
 */

#include "DotMatrix3D.h"

DotMatrix3D::DotMatrix3D(byte x_count, byte y_count, byte z_count): DotMatrix(x_count * y_count, z_count)
{
	_x_count = x_count;
	_y_count = y_count;
	_z_count = z_count;

	_x_block_count = _x_count / BLOCK_EDGE_LENGTH;
	_y_block_count = _y_count / BLOCK_EDGE_LENGTH;

	_block_count = _x_block_count * _y_block_count;
}

DotMatrix3D::~DotMatrix3D()
{
	// TODO Auto-generated destructor stub
}

void DotMatrix3D::setDot(byte x, byte y, byte z, bool on)
{
	if (x >= _x_count || y >= _y_count || z >= _z_count) return;

	byte col = this->convertCol(x, y);

	//DotMatrix::setDot(block_id * BLOCK_COLUMN_COUNT + col_x + col_y * BLOCK_EDGE_LENGTH, on);
	DotMatrix::setDot(col, z, on);
}

byte DotMatrix3D::convertCol(byte x, byte y)
{
	byte block_x_id = x >> 3; 	//	x / BLOCK_EDGE_LENGTH;
	byte block_y_id = y >> 3; 	//	y / BLOCK_EDGE_LENGTH;

	byte block_id = block_x_id * _y_block_count + block_y_id;

	byte col_x = x & 0x3f; 	//	x % BLOCK_EDGE_LENGTH;
	byte col_y = y & 0x3f;	//	y % BLOCK_EDGE_LENGTH;

	return((block_id << 6) + (col_y << 3) + col_x);
}
