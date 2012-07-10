/*
 * Driver_TB62726.h
 *
 *  Created on: 2012-7-10
 *      Author: Agu
 */

#ifndef DRIVER_TB62726_H_
#define DRIVER_TB62726_H_

#include "Driver_74HC595.h"

class Driver_TB62726:public Driver_74HC595
{
public:
	Driver_TB62726();
	virtual ~Driver_TB62726();
};

#endif /* DRIVER_TB62726_H_ */
