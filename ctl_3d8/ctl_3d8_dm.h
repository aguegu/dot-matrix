/*
 *  ctl_3d8_dm.h
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

#include "ctl_3d8.h"
#include "DotMatrix3D.h"
#include "ReverseByte.h"

class Ctl3D8Dm:public Ctl3D8
{
public:
	Ctl3D8Dm(DotMatrix3D & dm, HardwareSerial & sp, unsigned long baud_rate = 57600);
	virtual ~Ctl3D8Dm();

	void putDM();
	void putDMrevZ();
	void putReverseDM();

private:
	DotMatrix & _dm;
};

#endif /* CONTROLLER_A3D8_H_ */
