/*
 * ControllerA3D8.cpp
 *
 *  Created on: 2012-7-3
 *      Author: Agu
 */

#include "Controller_A3D8_Basic.h"

Controller_A3D8_Basic::Controller_A3D8_Basic(HardwareSerial & sp, unsigned long baud_rate,
		byte length) :
		_sp(sp), _length(length)
{
	_sp.begin(baud_rate);
}

Controller_A3D8_Basic::~Controller_A3D8_Basic()
{
	// TODO Auto-generated destructor stub
}

void Controller_A3D8_Basic::sendGlobal(byte c)
{
	_sp.write(0xf0);
	_sp.write(c);
}

void Controller_A3D8_Basic::sendColumn(byte col, byte value)
{
	_sp.write(0xf1);
	_sp.write(col);
	_sp.write(value);
}

void Controller_A3D8_Basic::sendBatch(const byte *p, byte length)
{
	_sp.write(0xf2);
	_sp.write(p, min(_length, length));
}

void Controller_A3D8_Basic::sendMode(InputMode mode)
{
	_sp.write(0xf3);
	_sp.write((byte)mode);
}

void Controller_A3D8_Basic::sendBrightness(byte brightness)
{
	_sp.write(0xf4);
	_sp.write(brightness);
}

void Controller_A3D8_Basic::sendBgLed(byte bg_led_configure)
{
	_sp.write(0xf5);
	_sp.write(bg_led_configure);

}
