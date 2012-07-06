/*
 * ControllerA3D8.cpp
 *
 *  Created on: 2012-7-3
 *	Author: Weihong Guan
 *	Blog: http://aguegu.net
 *	E-mail: weihong.guan@gmail.com
 *
 *	Code license: Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0)
 *	http://creativecommons.org/licenses/by-nc-sa/3.0/
 *	source host: https://github.com/aguegu/dot-matrix
 *
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

void Controller_A3D8::putReverseDM()
{
	_sp.write(0xf2);
	byte *p = _dm.output();
	for (byte i = _length; i--;)
		_sp.write(~(*p++));
}
