/*
 * Driver_TB62726_SPI.h
 *
 *  Created on: 2012-7-16
 *      Author: Agu
 */

#ifndef DRIVER_TB62726_SPI_H_
#define DRIVER_TB62726_SPI_H_

#include "Arduino.h"
#include "Driver_74HC595_SPI.h"

class Driver_TB62726_SPI: public Driver_74HC595_SPI
{
public:

	Driver_TB62726_SPI(SPIClass & spi, uint8_t pin_latch, uint8_t pin_oe, uint8_t pin_rext);
	virtual ~Driver_TB62726_SPI();

	void setBrightness(byte brg);
	void shiftSendCoupleFromLSB(byte *p, byte length);

private:

	const uint8_t _pin_rext;
};

#endif /* DRIVER_TB62726_SPI_H_ */
