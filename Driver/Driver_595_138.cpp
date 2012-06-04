/*
	Driver_595_138.cpp
	Driver_595_138 Class for dot-matrix printing on matrix driven by 74HC595 and 74HC138
	Created on: 2012-01-15
	Updated on: 2012-05-14

	library for Arduino for Dot Matrix Display, support driver by 74HC595 and 74HC138, ST7920, HD47780
	Author: Weihong Guan
	Blog: http://aguegu.net
	E-mail: weihong.guan@gmail.com
	Code license: Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0)
	http://creativecommons.org/licenses/by-nc-sa/3.0/

	source host: https://github.com/aguegu/dot-matrix
 */

#include "Driver_595_138.h"

Driver_595_138::Driver_595_138(DotMatrix & dm, uint8_t pin_C_IN,
		uint8_t pin_C_OE, uint8_t pin_C_ST, uint8_t pin_C_SH, uint8_t pin_R_OE,
		uint8_t pin_R_A2, uint8_t pin_R_A1, uint8_t pin_R_A0, uint16_t speed)
	:Driver_595_138_Basic(pin_C_IN, pin_C_OE, pin_C_ST, pin_C_SH,
			pin_R_OE, pin_R_A2, pin_R_A1, pin_R_A0, speed), _dm(dm)
{
	this->setSize(_dm.countBytes(), _dm.countRow());
}


void Driver_595_138::display(byte times)
{
	Driver_595_138_Basic::display(_dm.output(), times);
}

Driver_595_138::~Driver_595_138()
{

}

