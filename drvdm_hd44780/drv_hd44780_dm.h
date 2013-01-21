/*
	drv_hd44780_dm.h
	Driver_HD44780 Class for dot-matrix printing on liquid crystal display driven by HD47780, namely 1602/1604
	Created on: 2012-02-29
	Updated on: 2012-06-01

	library for Arduino for Dot Matrix Display, support driver by 74HC595 and 74HC138, ST7920, HD47780
	Author: Weihong Guan
	Blog: http://aguegu.net
	E-mail: weihong.guan@gmail.com
	Code license: Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0)
	http://creativecommons.org/licenses/by-nc-sa/3.0/

	source host: https://github.com/aguegu/dot-matrix
 */

#ifndef DRV_HD44780_DM_H_
#define DRV_HD44780_DM_H_

#include "Arduino.h"
#include "dot-matrix.h"
#include "drv_hd44780.h"

class DrvHd44780Dm: public DrvHd44780
{
public:

	DrvHd44780Dm(uint8_t pin_rs, uint8_t pin_en, uint8_t pin_d4, uint8_t pin_d5, uint8_t pin_d6, uint8_t pin_d7, byte row_count = 2, byte col_count = 16);
	virtual ~DrvHd44780Dm();

	void convertDotMatrixToCache();
	DotMatrix & getDotMatrix();

private:
	DotMatrix _dm;
};
#endif /* DRV_HD44780_DM_H_ */
