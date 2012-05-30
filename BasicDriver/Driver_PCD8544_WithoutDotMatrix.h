/*
 * Driver_PCD8544.h
 *
 *  Created on: 2012-5-30
 *      Author: gmb-gwh
 */

#ifndef DRIVER_PCD8544_WITHOUT_DOTMATRIX_H_
#define DRIVER_PCD8544_WITHOUT_DOTMATRIX_H_

#include "Arduino.h"

#define COMMAND	0
#define DATA	1

class Driver_PCD8544_WithoutDotMatrix
{
public:
	Driver_PCD8544_WithoutDotMatrix();
	virtual ~Driver_PCD8544_WithoutDotMatrix();
	void init();
private:

	uint8_t _pin_sce;
	uint8_t _pin_rst;
	uint8_t _pin_dc;
	uint8_t _pin_din;
	uint8_t _pin_sclk;

	void send(byte c, bool b);

};

#endif /* DRIVER_PCD8544_H_ */
