/*
 * DriverDual595.h
 *
 *  Created on: 2012-9-4
 *      Author: agu
 */

#ifndef DRIVERDUAL595_H_
#define DRIVERDUAL595_H_

#include "Arduino.h"
#include "PinWrite.h"
#include "DotMatrix.h"

class Driver_Dual595
{
public:
	Driver_Dual595(DotMatrix & dm, uint8_t pin_col, uint8_t pin_row, uint8_t pin_sh, uint8_t pin_st, uint8_t pin_oe);
	virtual ~Driver_Dual595();

	void display() const;
private:

	DotMatrix & _dm;

	const uint8_t _pin_col;
	const uint8_t _pin_row;
	const uint8_t _pin_sh;
	const uint8_t _pin_st;
	const uint8_t _pin_oe;

	inline void shiftLatch() const;
	inline void shiftClock() const;
};

#endif /* DRIVERDUAL595_H_ */
