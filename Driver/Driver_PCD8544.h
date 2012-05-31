/*
 *	Driver_PCD8544.h
 *	Driver_PCD8544 Class for dot-matrix printing on liquid crystal display driven by PCD8544, namely Nokia 8544
 *	Created on: 2012-05-30
 *
 *	library for Arduino for Dot Matrix Display, support driver by 74HC595 and 74HC138, ST7920, HD47780
 *	Author: Weihong Guan
 *	Blog: http://aguegu.net
 *	E-mail: weihong.guan@gmail.com
 *
 *	Code license: Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0)
 *	http://creativecommons.org/licenses/by-nc-sa/3.0/
 *	source host: https://github.com/aguegu/dot-matrix
 */

#ifndef DRIVER_PCD8544_H_
#define DRIVER_PCD8544_H_

#include "Arduino.h"
#include "DotMatrix.h"
#include "Driver_PCD8544_WithoutDotMatrix.h"

#define COMMAND	false
#define DATA	true

class Driver_PCD8544:public Driver_PCD8544_WithoutDotMatrix
{

public:

	Driver_PCD8544(DotMatrix & dm, uint8_t pin_sce, uint8_t pin_rst, uint8_t pin_dc, uint8_t pin_din, uint8_t pin_sclk);
	virtual ~Driver_PCD8544();
private:
	const DotMatrix & _dm;


};

#endif /* DRIVER_PCD8544_H_ */
