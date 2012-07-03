/*
 * Controller_A3D8.h
 *
 *  Created on: 2012-7-3
 *      Author: Agu
 */

#ifndef CONTROLLER_A3D8_H_
#define CONTROLLER_A3D8_H_

#include "Controller_A3D8_Basic.h"
#include "DotMatrix3D.h"

class Controller_A3D8:public Controller_A3D8_Basic
{
public:
	Controller_A3D8(DotMatrix3D & dm, HardwareSerial & sp, unsigned long baud_rate = 57600);
	virtual ~Controller_A3D8();

	void putDM();
private:
	DotMatrix & _dm;
};

#endif /* CONTROLLER_A3D8_H_ */
