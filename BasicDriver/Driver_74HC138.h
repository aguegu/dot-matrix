/*
 * Driver_74HC138.h
 *
 *  Created on: 2012-7-9
 *      Author: Agu
 */

#ifndef DRIVER_74HC138_H_
#define DRIVER_74HC138_H_

#include "Arduino.h"
#include "PinWrite.h"

class Driver_74HC138
{
public:
	Driver_74HC138(uint8_t pin_A2, uint8_t pin_A1, uint8_t pin_A0,
			uint8_t pin_OE);
	virtual ~Driver_74HC138();
	void setValue(byte r) const;
	void setOE(bool on) const;
private:
	const uint8_t _pin_A2;
	const uint8_t _pin_A1;
	const uint8_t _pin_A0;
	const uint8_t _pin_OE;
};

#endif /* DRIVER_74HC138_H_ */
