/*
 DotMatrix.h
 DotMatrix Class for modeling on the Dot Matrix, providing methods like dot control, and serial output
 library for Arduino to drive LED Dot Matrix Display dirven by 74HC595(column) and 74HC138(row)

 Created on: 2012-1-16
 Updated on: 2012-2-26
 Author: Weihong Guan
 Blog: http://aguegu.net
 E-mail: weihong.guan@gmail.com
 Code license: Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0)
 http://creativecommons.org/licenses/by-nc-sa/3.0/

 source hosting: http://code.google.com/p/aguegu-arduino-library/
 */

#include "DotMatrix.h"

DotMatrix::DotMatrix(byte colCount, byte rowCount)
{
	_colCount = colCount;
	_rowCount = rowCount;

	_bytesPerRow = _colCount / 8;
	_bytesLength = _bytesPerRow * _rowCount;

	_pScreen = (byte *) malloc(sizeof(byte) * _bytesLength);
}

DotMatrix::~DotMatrix()
{
	free(_pScreen);
}

void DotMatrix::clear(byte c)
{
	memset(_pScreen, c, _bytesLength);
}

void DotMatrix::reverseDot(byte col, byte row)
{
	if (getDot(col, row))
		setDot(col, row, false);
	else
		setDot(col, row, true);
}

void DotMatrix::setDot(byte col, byte row, boolean b)
{
	word i = getIndex(col, row);

	bitWrite(_pScreen[i], (col & 0x07), b);
}

void DotMatrix::setLine(byte cA, byte rA, byte cB, byte rB, bool on)
{
	byte cMin, cMax, rMin, rMax;

	cMin = min(cA, cB);
	cMin = max(cMin, 0);

	cMax = max(cA, cB);
	cMax = min(cMax, this->_colCount - 1);

	rMin = min(rA, rB);
	rMin = max(rMin, 0);

	rMax = max(rA, rB);
	rMax = min(rMax, this->_rowCount - 1);

	if (cMax - cMin >= rMax - rMin)
	{
		for (byte c = cMin; c <= cMax; c++)
		{
			int d = 32767;
			for (byte r = rMin; r <= rMax; r++)
			{
				int k = abs((c - cA) * (rA - rB) - (r - rA) * (cA - cB));
				if (d > k)
					d = k;
			}

			for (byte r = rMin; r <= rMax; r++)
			{
				if (abs((c - cA) * (rA - rB) - (r - rA) * (cA - cB)) == d)
					this->setDot(c, r, on);
			}
		}
	}
	else
	{
		for (byte r = rMin; r <= rMax; r++)
		{
			int d = 32767;
			for (byte c = cMin; c <= cMax; c++)
			{
				int k = abs((c - cA) * (rA - rB) - (r - rA) * (cA - cB));
				if (d > k)
					d = k;
			}

			for (byte c = cMin; c <= cMax; c++)
			{
				if (abs((c - cA) * (rA - rB) - (r - rA) * (cA - cB)) == d)
					this->setDot(c, r, on);
			}
		}
	}
}

void DotMatrix::setRect(byte cA, byte rA, byte cB, byte rB, bool on)
{
	byte cMin, cMax, rMin, rMax;

	cMin = min(cA, cB);
	cMin = max(cMin, 0);

	cMax = max(cA, cB);
	cMax = min(cMax, this->_colCount - 1);

	rMin = min(rA, rB);
	rMin = max(rMin, 0);

	rMax = max(rA, rB);
	rMax = min(rMax, this->_rowCount - 1);

	for (uint16_t c = cMin; c <= cMax; c++)
		for (uint16_t r = rMin; r <= rMax; r++)
		{
			this->setDot(c, r, on);
		}
}

word DotMatrix::getIndex(byte col, byte row) const
{
	word index = row * _bytesPerRow + (col >> 3);
	if (index < _bytesLength)
		return (index);
	else
		return 0;
}

boolean DotMatrix::getDot(byte col, byte row) const
{
	boolean b = false;

	word i = getIndex(col, row);
	b = bitRead(_pScreen[i], (col & 0x07));

	return b;
}

byte * DotMatrix::output() const
{
	return _pScreen;
}

byte DotMatrix::countCol() const
{
	return _colCount;
}

byte DotMatrix::countRow() const
{
	return _rowCount;
}

byte DotMatrix::countBytePerRow() const
{
	return _bytesPerRow;
}

word DotMatrix::countBytes() const
{
	return _bytesLength;
}

void DotMatrix::setByte(word index, byte value)
{
	if (index >= _bytesLength)
		return;
	_pScreen[index] = value;
}

void DotMatrix::move(Direction d, boolean recycle)
{
	byte pTemp[_bytesPerRow];
	switch (d)
	{
	case Left:
		for (byte r = 0; r < _rowCount; r++)
		{
			word index = r * _bytesPerRow;
			boolean b0 = bitRead(_pScreen[index], 0);
			for (byte i = 1; i < _bytesPerRow; i++)
			{
				boolean b = bitRead(_pScreen[index + 1], 0);
				_pScreen[index] >>= 1;
				bitWrite(_pScreen[index], 7, b);
				index++;
			}

			_pScreen[index] >>= 1;

			if (recycle)
				bitWrite(_pScreen[index], 7, b0);
		}
		break;
	case Right:
		for (byte r = 0; r < _rowCount; r++)
		{
			word index = r * _bytesPerRow + _bytesPerRow - 1;
			boolean b0 = bitRead(_pScreen[index], 7);
			for (byte i = 1; i < _bytesPerRow; i++)
			{
				boolean b = bitRead(_pScreen[index - 1], 7);
				_pScreen[index] <<= 1;
				bitWrite(_pScreen[index], 0, b);
				index--;
			}

			_pScreen[index] <<= 1;

			if (recycle)
				bitWrite(_pScreen[index], 0, b0);
		}
		break;
	case Up:
		for (word i = 0; i < _bytesPerRow; i++)
			pTemp[i] = _pScreen[i];

		for (byte r = 0; r < _rowCount - 1; r++)
		{
			word index = r * _bytesPerRow;
			for (byte i = 0; i < _bytesPerRow; i++)
			{
				_pScreen[index] = _pScreen[index + _bytesPerRow];
				index++;
			}
		}

		for (word index = _bytesPerRow * (_rowCount - 1), i = 0;
				i < _bytesPerRow; i++)
			_pScreen[index++] = recycle ? pTemp[i] : 0x00;

		break;
	case Down:
		for (word i = 0, index = (_rowCount - 1) * _bytesPerRow;
				i < _bytesPerRow; i++)
			pTemp[i] = _pScreen[index++];

		for (byte r = _rowCount - 1; r > 0; r--)
		{
			word index = r * _bytesPerRow;
			for (byte i = 0; i < _bytesPerRow; i++)
			{
				_pScreen[index] = _pScreen[index - _bytesPerRow];
				index++;
			}
		}

		for (word i = 0; i < _bytesPerRow; i++)
			_pScreen[i] = recycle ? pTemp[i] : 0x00;

		break;
	}
}
