/*
 * Driver595138Basic.h
 *
 *  Created on: 2012-6-4
 *      Author: agu
 */

#ifndef DRIVER_595_138_BASIC_H_
#define DRIVER_595_138_BASIC_H_

#include "Arduino.h"

class Driver_595_138_Basic
{
public:
	Driver_595_138_Basic(uint8_t pin_C_IN, uint8_t pin_C_OE, uint8_t pin_C_ST,
			uint8_t pin_C_SH, uint8_t pin_R_OE, uint8_t pin_R_A2,
			uint8_t pin_R_A1, uint8_t pin_R_A0, uint16_t speed = 0x400);
	virtual ~Driver_595_138_Basic();
	void display(byte *p, byte times = 1);
	void setSpeed(uint16_t speed = 0x400);

protected:

	void setSize(byte length, byte rowCount);

private:

	uint16_t _speed;

	uint8_t _pin_595_DS;
	uint8_t _pin_595_OE;
	uint8_t _pin_595_ST;
	uint8_t _pin_595_SH;

	uint8_t _pin_138_OE;
	uint8_t _pin_138_A2;
	uint8_t _pin_138_A1;
	uint8_t _pin_138_A0;

	byte _length;
	byte _rowCount;
	byte _bytesPerRow;

	void setRow(byte r);
	void setCol(byte *p);
	void shiftSend(byte c);
};

#endif /* DRIVER_595_138_BASIC_H_ */
