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
	_z_block_count = _z_count / BLOCK_EDGE_LENGTH;

	_block_count = _x_block_count * _y_block_count * _z_block_count;
}

DotMatrix3D::~DotMatrix3D()
{
	// TODO Auto-generated destructor stub
}


void DotMatrix3D::setDot(byte x, byte y, byte z, bool on)
{
	if (x >= _x_count || y >= _y_count || z >= _z_count) return;

	byte block_id = (y / BLOCK_EDGE_LENGTH) * _x_block_count + (x / BLOCK_EDGE_LENGTH);
	if (block_id >= _block_count) return;

	DotMatrix::setDot(block_id * BLOCK_COLUMN_COUNT + x + y * BLOCK_EDGE_LENGTH, on);
}

