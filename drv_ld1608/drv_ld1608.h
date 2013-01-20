/*
 * drv_ld1608.h
 *
 *  Created on: 2012-8-31
 *      Author: agu
 */

#ifndef DRV_LD1608_H_
#define DRV_LD1608_H_

#include "Arduino.h"
#include "drv_74hc595_spi.h"
#include "DotMatrix.h"

class DrvLd1608
{
public:
	DrvLd1608();
	virtual ~DrvLd1608();
	void display(byte times = 1);
	void setScanSpan(uint16_t scan_span = 0x800);
	DotMatrix & getDotMatrix();
private:
	DotMatrix _dm;
	Drv74hc595Spi chip;
	uint16_t _scan_span;
};

#endif /* DRV_LD1608_H_ */
