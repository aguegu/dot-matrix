/*
 * ControllerA3D8.cpp
 *
 *  Created on: 2012-7-3
 *      Author: Agu
 */

#include "Controller_A3D8.h"

Controller_A3D8::Controller_A3D8(DotMatrix3D & dm, HardwareSerial & sp,
		unsigned long baud_rate) :
		Controller_A3D8_Basic(sp, baud_rate, dm.countBytes()), _dm(dm)
{

}

Controller_A3D8::~Controller_A3D8()
{

}

void Controller_A3D8::putDM()
{
	this->sendBatch(_dm.output(), _length);
}

void Controller_A3D8::putDMrevZ()
{
	_sp.write(0xf2);
	byte *p = _dm.output();
	for (byte i = _length; i--;)
		_sp.write(DotMatrix::reverseByte(*p++));
}
