/*
 *	Basic animation sample on arduino managing 3D8S 8x8x8 led cubic display
 *	by connecting the serial port on 3D8S board (P2)
 *
 *	P2.1 -> VCC (5V)
 *	P2.2 -> #1 (TX)
 *	P2.3 -> #0 (RX)
 *	P2.4 -> GND (0V)
 *
 *	Disconnection would be needed when upload the sketch to arduino.
 *
 *	Author: Weihong Guan
 *	Blog: http://aguegu.net
 *	E-mail: weihong.guan@gmail.com
 *
 *	Code license: Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0)
 *	http://creativecommons.org/licenses/by-nc-sa/3.0/
 *	source host: https://github.com/aguegu/dot-matrix
 */

#include "DotMatrixTest.h"
#include "Controller_A3D8_Basic.h"

extern HardwareSerial Serial;

const byte length = 64;
byte * pScreen;

Controller_A3D8_Basic cube(Serial);

void setup()
{
	//pScreen = (byte *) malloc(sizeof(byte) * length);
	pScreen = new byte(length);
	Serial.begin(57600);
	cube.sendMode(Controller_A3D8_Basic::XYZ);
	cube.sendBrightness(0xff);
}

void animationBgLed()
{
	static byte value = 0x00;
	cube.sendGlobal(0x00);
	cube.sendBgLed(value++);
	if (value == 4) value = 0;
}

void animationFlash()
{
	static byte value = 0xff;
	cube.sendGlobal(value);
	value = ~value;
}

void animationBreathe()
{
	static byte brightness = 0xff;
	static bool increase = false;

	cube.sendBrightness(increase ? ++brightness : --brightness);

	if (brightness == 0xff)
		increase = false;

	if (brightness == 0x00)
		increase = true;
}

void animationFacetScan()
{
	static byte value = 0x01;
	cube.sendGlobal(value);
	value <<= 1;
	if (value == 0x00)
		value = 0x01;
}

void animationBlockScan()
{
	static byte value = 0x00;
	value = (value << 1) + 0x01;
	cube.sendGlobal(value);
	if (value == 0xff)
		value = 0x00;
}
void animationRiseZ()
{
	for (byte i = 0; i < length; i++)
		pScreen[i] <<= 1;

	for (byte i = 0; i < random(4); i++)
	{
		byte x = random(8);
		byte y = random(8);
		pScreen[8 * y + x] |= 0x01;
	}
	cube.sendBatch(pScreen, length);
}

void callAnimation(void (*p)(), uint16_t span, uint16_t times, byte init_value,
		Controller_A3D8_Basic::InputMode mode)
{
	cube.sendMode(mode);
	cube.sendGlobal(init_value);
	while (times--)
	{
		(*p)();
		delay(span);
	}
}

void callAnimationInModes(void (*p)(), uint16_t span, uint16_t times,
		byte init_value)
{
	for (byte i = 0; i < 3; i++)
		callAnimation(p, span, times, init_value,
				(Controller_A3D8_Basic::InputMode) i);
}

void loop()
{
	callAnimation(animationBgLed, 0x400, 0x08, 0x00, Controller_A3D8_Basic::XYZ);
	callAnimation(animationFlash, 0xF0, 0x08, 0x00, Controller_A3D8_Basic::XYZ);
	callAnimation(animationBreathe, 0x08, 0xff * 4, 0xff, Controller_A3D8_Basic::XYZ);
	callAnimationInModes(animationFacetScan, 0x80, 0x08, 0x00);
	callAnimationInModes(animationBlockScan, 0x80, 0x08, 0x00);
	callAnimationInModes(animationRiseZ,0x40, 0x60, 0x00);
}

