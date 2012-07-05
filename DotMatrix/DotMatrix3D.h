/*
 * DotMatrix3D.h
 *
 *  Created on: 2012-5-29
 *      Author: gmb-gwh
 */

#ifndef DOTMATRIX3D_H_
#define DOTMATRIX3D_H_

#include "DotMatrix.h"

class DotMatrix3D: public DotMatrix
{
public:
	DotMatrix3D(byte block_count);
	virtual ~DotMatrix3D();
	void setDot(byte x, byte y, byte z, bool on = true);

	enum Direction3D
	{
		Z_NEGA,
		Z_POSI,
		Y_NEGA,
		Y_POSI,
		X_NEGA,
		X_POSI,
	};

	void setMoveDirection(Direction3D direction);

private:

	byte _block_count;

	static const byte BLOCK_EDGE_LENGTH = 8;
	static const byte BLOCK_COLUMN_COUNT = 64;

	byte convertCol(byte x, byte y);
};

#endif /* DOTMATRIX3D_H_ */
