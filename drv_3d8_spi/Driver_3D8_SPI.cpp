/*
 * Driver_3D8_SPI.cpp
 *
 *  Created on: 2012-7-26
 *      Author: Agu
 */

#include "Driver_3D8_SPI.h"

Driver_3D8_SPI::Driver_3D8_SPI(DotMatrix & dm, SPIClass & spi,
		uint8_t pin_latch, uint8_t pin_en, uint8_t pin_rext, uint8_t pin_a2,
		uint8_t pin_a1, uint8_t pin_a0, uint16_t scan_speed) :
		Driver_62726_138_SPI(dm, spi, pin_latch, pin_en, pin_rext,
				pin_a2, pin_a1, pin_a0, 255, scan_speed)
{
	// TODO Auto-generated constructor stub
	this->setMode();
}

Driver_3D8_SPI::~Driver_3D8_SPI()
{
	// TODO Auto-generated destructor stub
}

void Driver_3D8_SPI::setMode(ScanMode mode)
{
	switch (mode)
	{
	case ZXY:
		_setCol = &Driver_3D8_SPI::setColzxy;
		break;
	case YZX:
		_setCol = &Driver_3D8_SPI::setColyzx;
		break;
	default:
		_setCol = &Driver_3D8_SPI::setColxyz;
		break;
	}
}

void Driver_3D8_SPI::setColxyz(byte row) const
{
	byte * p = _dm.output();
	p += _byte_per_row * row;

	chip_col.shiftSendCoupleFromLSB(p, _byte_per_row);
}

void Driver_3D8_SPI::display(byte times) const
{
	while (times--)
	{
		for (byte r = 0; r < _row_count; r++)
		{
			(this->*_setCol)(r);

			chip_col.setOE(true);
			chip_col.shiftLatch();
			chip_row.setValue(r);
			chip_col.setOE(false);

			delayMicroseconds(_scan_span);
		}
	}
}

void Driver_3D8_SPI::setColzxy(byte row) const
{
	byte * p = _dm.output();
	for (byte j = 0; j < _word_per_row; j++)
	{
		byte cache[2];
		byte *p2 = p + _byte_per_row + _byte_per_row;

		for (byte i = 8; i--;)
		{
			cache[0]<<=1;
			if (bitRead(*(p++), row)) cache[0] |= 0x01;

			cache[1]<<=1;
			if (bitRead(*(--p2), row)) cache[1] |= 0x01;
		}
		p += _byte_per_row;
		chip_col.shiftSend(cache, 2);
	}
}

void Driver_3D8_SPI::setColyzx(byte row) const
{
	byte *p = _dm.output() + row;
	for (byte j = 0; j < _byte_per_row; j++) // z
	{
		byte cache;

		for (byte i = 8; i--;)
		{
			cache <<= 1;

			if (j & 0x01)
				p -= _byte_per_row;
			if (bitRead(*p, j)) cache |= 0x01;
			if (!(j & 0x01))
				p += _byte_per_row;
		}

		chip_col.shiftSend(&cache, 1);
	}
}
