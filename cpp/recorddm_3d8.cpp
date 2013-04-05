/*
 * recorddm_3d8.cpp
 *
 *  Created on: Mar 29, 2013
 *      Author: agu
 */

#include "recorddm_3d8.h"

RecordDm3d8::RecordDm3d8(DotMatrix3d8 & dm) :
		Record3d8(dm.countBytes()), _dm(dm)
{

}

RecordDm3d8::~RecordDm3d8()
{

}

void RecordDm3d8::putDM()
{
	this->sendBatch(_dm.output(), _dm.countBytes());
}

void RecordDm3d8::putDMrevZ()
{
	byte *p = _dm.output();
	for (byte i = 0; i < _dm.countBytes(); i++)
		this->sendColumn(i, reverseByte(*p++));
}

void RecordDm3d8::putReverseDM()
{
	byte *p = _dm.output();
	for (byte i = 0; i < _dm.countBytes(); i++)
		this->sendColumn(i, ~(*p++));
}
