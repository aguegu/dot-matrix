/*
 * Driver_62726_138_SPI.h
 *
 *  Created on: 2012-7-26
 *      Author: Agu
 */

#ifndef DRIVER_62726_138_SPI_H_
#define DRIVER_62726_138_SPI_H_

#include "DotMatrix.h"
#include "SPI.h"
#include "Driver_TB62726_SPI.h"
#include "Driver_74HC138.h"

class Driver_62726_138_SPI
{
public:
	Driver_62726_138_SPI(DotMatrix & dm, SPIClass & spi, uint8_t pin_latch, uint8_t pin_en, uint8_t pin_rext,
			uint8_t pin_a2, uint8_t pin_a1, uint8_t pin_a0, uint8_t pin_oe, uint16_t scan_speed = 0x600);

	virtual ~Driver_62726_138_SPI();

	void setSpeed(uint16_t scan_span);
	void setSize();
	void setBrightness(byte brg = 0xff);

	void display(byte times = 0x01) const;

protected:

	const DotMatrix & _dm;
	Driver_TB62726_SPI chip_col;
	Driver_74HC138 chip_row;

	word _scan_span;

	byte _row_count;
	byte _word_per_row;
	byte _byte_per_row;

	void setCol(byte row) const;

};

#endif /* DRIVER_62726_138_SPI_H_ */
