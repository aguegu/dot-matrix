/*
 * Driver_3D8_SPI.h
 *
 *  Created on: 2012-7-26
 *      Author: Agu
 */

#ifndef DRIVER_3D8_SPI_H_
#define DRIVER_3D8_SPI_H_

#include "DotMatrix.h"
#include "Driver_62726_138_SPI.h"

class Driver_3D8_SPI:public Driver_62726_138_SPI
{
public:
	Driver_3D8_SPI(DotMatrix & dm, SPIClass & spi,
			uint8_t pin_latch, uint8_t pin_en, uint8_t pin_rext, uint8_t pin_a2,
			uint8_t pin_a1, uint8_t pin_a0, uint16_t scan_speed = 0x600);

	virtual ~Driver_3D8_SPI();
	enum ScanMode
	{
		XYZ = 0x00, YZX = 0x01, ZXY = 0x02, OLD = 0x03
	};

	void display(byte times = 0x01) const;

	void setMode(ScanMode mode = XYZ);

private:

	void (Driver_3D8_SPI::*_setCol)(byte row) const;

	void setColxyz(byte row) const;
	void setColzxy(byte row) const;
	void setColyzx(byte row) const;
};

#endif /* DRIVER_3D8__SPI_H_ */
