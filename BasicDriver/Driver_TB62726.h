/*
 * Driver_TB62726.h
 *
 *  Created on: 2012-7-10
 *      Author: Agu
 */

#ifndef DRIVER_TB62726_H_
#define DRIVER_TB62726_H_

#include "Driver_74HC595.h"

class Driver_TB62726:public Driver_74HC595
{
public:
	Driver_TB62726(uint8_t pin_din, uint8_t pin_clk, uint8_t pin_latch, uint8_t pin_oe, uint8_t pin_rext);
	virtual ~Driver_TB62726();
	void setBrightness(byte brg);
	void shiftSendFromLSB(byte *p, byte length) const;
	void shiftSendFromMSB(byte *p, byte length) const;
private:
	const uint8_t _pin_rext;
};

#endif /* DRIVER_TB62726_H_ */
