/*
 * Driver_ST7920.h
 *
 *  Created on: 2012-6-1
 *      Author: agu
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
