/*
 * drv_ld1608.cpp
 *
 *  Created on: 2012-8-31
 *      Author: agu
 */

#include "drv_ld1608.h"

DrvLd1608::DrvLd1608() :
		_dm(16, 8), chip(SPI, 9, 8)
{
	this->setScanSpan();
}

DrvLd1608::~DrvLd1608()
{

}

void DrvLd1608::display(byte times)
{
	while (times--)
	{
		byte *p = _dm.output();
		for (byte r = 0; r < 8; r++)
		{
			byte col = _BV(r);
			chip.shiftSendRev(p, 2);
			chip.shiftSend(&col, 1);
			chip.shiftLatch();
			p += 2;

			delayMicroseconds(_scan_span);
		}
	}
}

void DrvLd1608::setScanSpan(uint16_t scan_span)
{
	_scan_span = scan_span;
}

DotMatrix & DrvLd1608::getDotMatrix()
{
	return _dm;
}
