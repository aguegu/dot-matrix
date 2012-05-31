/*
 * Driver_PCD8544.h
 *
 *  Created on: 2012-5-30
 *      Author: gmb-gwh
 */

#ifndef DRIVER_PCD8544_WITHOUT_DOTMATRIX_H_
#define DRIVER_PCD8544_WITHOUT_DOTMATRIX_H_

#include "Arduino.h"

#define COMMAND	false
#define DATA	true

class Driver_PCD8544_WithoutDotMatrix
{

public:

	Driver_PCD8544_WithoutDotMatrix
		(uint8_t pin_sce, uint8_t pin_rst, uint8_t pin_dc, uint8_t pin_din, uint8_t pin_sclk);
	virtual ~Driver_PCD8544_WithoutDotMatrix();
	void init();
	void setRamAddress(byte x, byte y);

	void configureFunction(byte tc = 0x03, byte bias = 0x00, byte vop = 0x50);
	void configureDisplay(bool display_on = true, bool reverse = false);


private:

	const uint8_t _pin_sce;
	const uint8_t _pin_rst;
	const uint8_t _pin_dc;
	const uint8_t _pin_din;
	const uint8_t _pin_sclk;

	const static byte BYTES_PER_COLUMN = 6;
	const static byte CLOLUMN_COUNT = 84;

	void send(byte c, bool b);

};

#endif /* DRIVER_PCD8544_H_ */
