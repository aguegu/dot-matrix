/*
 * Driver_ST7920.cpp
 *
 *  Created on: 2012-6-1
 *      Author: agu
 */

#include "Driver_ST7920.h"

ST7920::ST7920(DotMatrix & dm, uint8_t pin_rs, uint8_t pin_en, uint8_t pin_d4, uint8_t pin_d5, uint8_t pin_d6, uint8_t pin_d7)
	:ST7920_Basic(pin_rs, pin_en, pin_d4, pin_d5, pin_d6, pin_d7), _dm(dm)
{
	// TODO Auto-generated constructor stub
	this->init();
}

ST7920::~ST7920()
{
	// TODO Auto-generated destructor stub
}

void ST7920::putDM()
{
	byte *p = _dm.output();

	for (byte r = 0; r < 0x20; r++)
	{
		this->setDdRam(r); // y
		this->setDdRam(0x00); // x
		for (byte i = _dm.countBytePerRow(); i; i--)
			this->writeDataRev(*(p++));
	}

	for (byte r = 0; r < 0x20; r++)
	{
		this->setDdRam(r); // y
		this->setDdRam(0x08); // x
		for (byte i =  _dm.countBytePerRow(); i; i--)
			this->writeDataRev(*(p++));
	}
}
