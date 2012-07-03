/*
 * ControllerA3D8.h
 *
 *  Created on: 2012-7-3
 *      Author: Agu
 */

#ifndef CONTROLLER_A3D8_BASIC_H_
#define CONTROLLER_A3D8_BASIC_H_

#include "Arduino.h"

class Controller_A3D8_Basic
{
public:

	enum InputMode
	{
		XYZ = 0x00, YZX = 0x01, ZXY = 0x02, OLD = 0x03
	};

	Controller_A3D8_Basic(HardwareSerial & sp, unsigned long baud_rate = 57600,
			byte length = 64);
	virtual ~Controller_A3D8_Basic();
	void sendGlobal(byte c);
	void sendColumn(byte col, byte value);
	void sendBatch(const byte *p, byte length);
	void sendMode(InputMode mode);
	void sendBrightness(byte brightness);
	void sendBgLed(byte bg_led_configure);

private:
	HardwareSerial & _sp;

protected:
	const byte _length;



};

#endif /* CONTROLLERA3D8_H_ */
