/*
 * DriverDual595.cpp
 *
 *  Created on: 2012-9-4
 *      Author: agu
 */

#include "Driver_Dual595.h"

Driver_Dual595::Driver_Dual595(uint8_t pin_col, uint8_t pin_row, uint8_t pin_sh, uint8_t pin_st, uint8_t pin_oe)
	:_pin_col(pin_col), _pin_row(pin_row), _pin_sh(pin_sh), _pin_st(pin_st), _pin_oe(pin_oe)
{
	pinMode(_pin_col, OUTPUT);
	pinMode(_pin_row, OUTPUT);
	pinMode(_pin_sh, OUTPUT);
	pinMode(_pin_st, OUTPUT);
	pinMode(_pin_oe, OUTPUT);

	pinWrite(_pin_oe, LOW);

}

Driver_Dual595::~Driver_Dual595()
{

}

