/*
 * Driver_TB62726_SPI.h
 *
 *  Created on: 2012-7-16
 *      Author: Agu
 */

#ifndef DRIVER_TB62726_SPI_H_
#define DRIVER_TB62726_SPI_H_

#include "Driver_74HC595_SPI.h"

class Driver_TB62726_SPI:public Driver_74HC595_SPI
{
public:
	Driver_TB62726_SPI(SPIClass & spi, uint8_t pin_latch, uint8_t pin_oe, uint8_t pin_rext);
	virtual ~Driver_TB62726_SPI();


};

#endif /* DRIVER_TB62726_SPI_H_ */
