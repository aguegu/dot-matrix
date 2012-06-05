/*
 * Driver_1818_138.h
 *
 *  Created on: 2012-5-28
 *      Author: Agu
 */

#ifndef DRIVER_1818_138_H_
#define DRIVER_1818_138_H_

#include "Driver_595_138_Basic.h"
#include "DotMatrix.h"

class Driver_1818_138:public Driver_595_138_Basic
{
public:
	Driver_1818_138(DotMatrix & dm,
			uint8_t pin_62726_DS, uint8_t pin_62726_OE, uint8_t pin_62726_ST, uint8_t pin_62726_SH,
			uint8_t pin_138_A0, uint8_t pin_138_A1, uint8_t pin_138_A2, uint8_t pin_brightness, uint16_t scan_speed = 0x400);

	void setSpeed(uint16_t scan_span);
	void setSize(byte length, byte rowCount);

	void display(byte times = 0x01) const;

private:

	const DotMatrix & _dm;

	const uint8_t _pin_62726_OE;
	const uint8_t _pin_62726_ST;

	const uint8_t _pin_brightness;

	word _scan_span;

	byte _length;
	byte _row_count;
	byte _word_per_row;
	byte _byte_per_row;

	void setCol(byte *p) const;
};

#endif /* DRIVER1818138_H_ */
