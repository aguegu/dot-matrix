/*
 * Driver_62726_138_ISP.cpp
 *
 *  Created on: 2012-7-26
 *      Author: Agu
 */

#include "Driver_62726_138_SPI.h"

Driver_62726_138_SPI::Driver_62726_138_SPI(DotMatrix & dm, SPIClass & spi, uint8_t pin_latch, uint8_t pin_en, uint8_t pin_rext,
		uint8_t pin_a2, uint8_t pin_a1, uint8_t pin_a0, uint8_t pin_oe, uint16_t scan_speed)
:_dm(dm),
	chip_col(spi, pin_latch,pin_en, pin_rext),
	chip_row(pin_a2, pin_a1, pin_a0, pin_oe)
{
	this->setBrightness();
	this->setSpeed(scan_speed);
	this->setSize();

}

Driver_62726_138_SPI::~Driver_62726_138_SPI()
{
	// TODO Auto-generated destructor stub
}

void Driver_62726_138_SPI::setSpeed(uint16_t scan_span)
{
	_scan_span = scan_span;
}

void Driver_62726_138_SPI::setSize()
{
	_row_count = _dm.countRow();
	_byte_per_row = _dm.countBytePerRow();
	_word_per_row = _byte_per_row / 2;
}

void Driver_62726_138_SPI::setBrightness(byte brg)
{
	chip_col.setBrightness(brg);
}

void Driver_62726_138_SPI::setCol(byte row) const
{
	byte * p = _dm.output();
	p += _byte_per_row * row;

	chip_col.shiftSend(p, _byte_per_row);
}

void Driver_62726_138_SPI::display(byte times) const
{
	while (times--)
	{
		for (byte r = 0; r < _row_count; r++)
		{
			this->setCol(r);

			chip_col.setOE(true);
			chip_col.shiftLatch();
			chip_row.setValue(r);
			chip_col.setOE(false);

			delayMicroseconds(_scan_span);
		}
	}
}
