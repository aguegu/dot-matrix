/*
	Driver_ST7920.h
	Driver_ST7920 Class, for DotMatrix printing on liquid crystal display driven by ST7920, namely 12864
	Created on: 2012-06-01

	library for Arduino for Dot Matrix Display, support driver by 74HC595 and 74HC138, ST7920, HD47780
	Author: Weihong Guan
	Blog: http://aguegu.net
	E-mail: weihong.guan@gmail.com
	Code license: Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0)
	http://creativecommons.org/licenses/by-nc-sa/3.0/

	source host: https://github.com/aguegu/dot-matrix
 */

#ifndef DRIVER_ST7920_H_
#define DRIVER_ST7920_H_

#include "Driver_ST7920_Basic.h"
#include "DotMatrix.h"

class ST7920:public ST7920_Basic
{
public:

	ST7920(DotMatrix & dm, uint8_t pin_rs, uint8_t pin_en, uint8_t pin_d4, uint8_t pin_d5, uint8_t pin_d6, uint8_t pin_d7);
	virtual ~ST7920();
	void putDM();

private:

	const DotMatrix & _dm;
};

#endif /* DRIVER_ST7920_H_ */
