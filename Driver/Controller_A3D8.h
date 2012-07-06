/*
 * Controller_A3D8.h
 *
 *  Created on: 2012-7-3
 *	Author: Weihong Guan
 *	Blog: http://aguegu.net
 *	E-mail: weihong.guan@gmail.com
 *
 *	Code license: Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0)
 *	http://creativecommons.org/licenses/by-nc-sa/3.0/
 *	source host: https://github.com/aguegu/dot-matrix
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
	void putDMrevZ();
	void putReverseDM();

private:
	DotMatrix & _dm;
};

#endif /* CONTROLLER_A3D8_H_ */
