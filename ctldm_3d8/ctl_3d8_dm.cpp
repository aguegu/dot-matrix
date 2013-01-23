/*
 * ctl_3d8_dm.cpp
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

#include "ctl_3d8_dm.h"

Ctl3D8Dm::Ctl3D8Dm(DotMatrix3d8 & dm, HardwareSerial & sp,
		unsigned long baud_rate) :
		Ctl3D8(sp, baud_rate, dm.countBytes()), _dm(dm)
{

}

Ctl3D8Dm::~Ctl3D8Dm()
{

}

void Ctl3D8Dm::putDM()
{
	this->sendBatch(_dm.output(), _length);
}

void Ctl3D8Dm::putDMrevZ()
{
	_sp.write(0xf2);
	byte *p = _dm.output();
	for (byte i = _length; i--;)
		_sp.write(reverseByte(*p++));
}

void Ctl3D8Dm::putReverseDM()
{
	_sp.write(0xf2);
	byte *p = _dm.output();
	for (byte i = _length; i--;)
		_sp.write(~(*p++));
}
