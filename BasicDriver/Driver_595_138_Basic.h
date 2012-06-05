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
	Driver_595_138_Basic(uint8_t pin_C_IN, uint8_t pin_C_SH,
			uint8_t pin_R_A2, uint8_t pin_R_A1, uint8_t pin_R_A0);
	virtual ~Driver_595_138_Basic();

protected:

	const uint8_t _pin_595_DS;
	const uint8_t _pin_595_SH;

	const uint8_t _pin_138_A2;
	const uint8_t _pin_138_A1;
	const uint8_t _pin_138_A0;

	void setRow(byte r) const;

	void setColFromLSB(byte *p, byte length) const;
	void setColFromMSB(byte *p, byte length) const;

	void shiftSendFromLSB(byte c) const;
	void shiftSendFromMSB(byte c) const;
};

#endif /* DRIVER_595_138_BASIC_H_ */
