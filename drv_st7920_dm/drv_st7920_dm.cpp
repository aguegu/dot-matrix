/*
 drv_st7920_dm.cpp
 DrvSt7920Dm Class, for DotMatrix printing on liquid crystal display driven by ST7920, namely 12864
 Created on: 2012-06-01

 library for Arduino for Dot Matrix Display, support driver by 74HC595 and 74HC138, ST7920, HD47780
 Author: Weihong Guan
 Blog: http://aguegu.net
 E-mail: weihong.guan@gmail.com
 Code license: Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0)
 http://creativecommons.org/licenses/by-nc-sa/3.0/

 source host: https://github.com/aguegu/dot-matrix
 */

#include "drv_st7920_dm.h"

DrvSt7920Dm::DrvSt7920Dm(uint8_t pin_rs, uint8_t pin_en, uint8_t pin_d4, uint8_t pin_d5,
		uint8_t pin_d6, uint8_t pin_d7) :
		DrvSt7920(pin_rs, pin_en, pin_d4, pin_d5, pin_d6, pin_d7), _dm(128,
				64)
{
	this->init();
}

DrvSt7920Dm::~DrvSt7920Dm()
{

}

void DrvSt7920Dm::putDM()
{
	byte *p = _dm.output();

	for (byte r = 0; r < 0x20; r++)
	{
		this->setDdRam(r); // y
		this->setDdRam(0x00); // x
		for (byte i = _dm.countBytePerRow(); i--;)
			this->writeData(*(p++));
	}

	for (byte r = 0; r < 0x20; r++)
	{
		this->setDdRam(r); // y
		this->setDdRam(0x08); // x
		for (byte i = _dm.countBytePerRow(); i--;)
			this->writeData(*(p++));
	}
}

DotMatrix & DrvSt7920Dm::getDotMatrix()
{
	return _dm;
}
