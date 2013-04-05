/*
 * Record3d8.h
 *
 *  Created on: Mar 29, 2013
 *      Author: agu
 */

#ifndef RECORD3D8_H_
#define RECORD3D8_H_

#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <locale.h>
#include <cursesw.h>
#include "common.h"

class Record3d8
{
	public:
		Record3d8(byte length = 64);
		virtual ~Record3d8();

		enum InputMode
		{
			XYZ = 0x00, YZX = 0x01, ZXY = 0x02
		};

		void sendGlobal(byte c);
		void sendColumn(byte col, byte value);
		void sendBatch(const byte *p, byte length);
		void sendMode(InputMode mode = XYZ);
		void sendBrightness(byte brightness);
		void sendBgLed(byte bg_led_configure);
		void sendDelay(word span);
		byte * output();
		void display();
		void init();
		void terminate();

	private:
		const byte _length;
		byte *_p;
		static const unsigned char c_on[5];
		static const unsigned char c_off[5];
};

#endif /* RECORD3D8_H_ */
