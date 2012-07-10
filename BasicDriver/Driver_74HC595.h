/*
 * Driver_74HC595.h
 *
 *  Created on: 2012-7-9
 *      Author: Agu
 */

#ifndef DRIVER_74HC595_H_
#define DRIVER_74HC595_H_

#include "Arduino.h"
#include "PinWrite.h"

#ifndef BIT_IN_BYTE
#define BIT_IN_BYTE 8
#endif

class Driver_74HC595
{
public:
	Driver_74HC595(uint8_t pin_DS, uint8_t pin_SH, uint8_t pin_ST, uint8_t pin_OE);
	virtual ~Driver_74HC595();

	void shiftSendFromLSB(byte c) const;
	void shiftSendFromMSB(byte c) const;
	void shiftSendFromLSB(byte *p, byte length) const;
	void shiftSendFromMSB(byte *p, byte length) const;
	void shiftLatch() const;
	void setOE(bool on = true) const;
	void setDS(bool high) const;
	void shiftClock() const;

private:
	const uint8_t _pin_DS;
	const uint8_t _pin_SH;
	const uint8_t _pin_ST;
	const uint8_t _pin_OE;
};

#endif /* DRIVER_74HC595_H_ */
