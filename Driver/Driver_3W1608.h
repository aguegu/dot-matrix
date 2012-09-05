/*
 * Driver_3W1608.h
 *
 *  Created on: 2012-8-31
 *      Author: agu
 */

#ifndef DRIVER_3W1608_H_
#define DRIVER_3W1608_H_

#include "Arduino.h"
#include "Driver_74HC595_SPI.h"
#include "DotMatrix.h"

class Driver_3W1608
{
public:
	Driver_3W1608();
	virtual ~Driver_3W1608();
	void display(byte times = 1);
	void setScanSpan(uint16_t scan_span = 0x800);
	DotMatrix & getDotMatrix();
private:
	DotMatrix _dm;
	Driver_74HC595_SPI chip;
	uint16_t _scan_span;
};

#endif /* DRIVER_3W1608_H_ */
