/*
 * drvdm_tb62726x74hc138_spi.h
 *
 *  Created on: 2012-7-26
 *      Author: Agu
 */

#ifndef DRV_DM_TB62726_X_74HC595_SPI_H_
#define DRV_DM_TB62726_X_74HC595_SPI_H_

#include "dot-matrix.h"
#include "drv_tb62726x74hc138_spi.h"

class DrvDmTb6276X74hc138Spi: public DrvTb62726X74hc138Spi
{
public:
	DrvDmTb6276X74hc138Spi(DotMatrix & dm, SPIClass & spi, uint8_t pin_latch,
			uint8_t pin_en, uint8_t pin_rext, uint8_t pin_a2, uint8_t pin_a1,
			uint8_t pin_a0, uint16_t scan_speed = 0x600);

	virtual ~DrvDmTb6276X74hc138Spi();
	enum ScanMode
	{
		XYZ = 0x00, YZX = 0x01, ZXY = 0x02, OLD = 0x03
	};

	void display(byte times = 0x01) const;

	void setMode(ScanMode mode = XYZ);

private:

	void (DrvDmTb6276X74hc138Spi::*_setCol)(byte row) const;

	void setColxyz(byte row) const;
	void setColzxy(byte row) const;
	void setColyzx(byte row) const;
};

#endif /* DRV_DM_TB62726_X_74HC595_SPI_H_ */
