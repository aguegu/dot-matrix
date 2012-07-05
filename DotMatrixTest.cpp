#include "DotMatrixTest.h"

#include "DotMatrix3D.h"
#include "Controller_A3D8.h"

#define BYTE_LENGTH 64

extern HardwareSerial Serial;

DotMatrix3D dm(1);
Controller_A3D8 cube(dm, Serial);

byte * cache;

const uint8_t PROGMEM PATTERN_LOVE[] =
{ 0x00, 0x81, 0x81, 0xFF, // I
		0x38, 0xFC, 0xFE, 0x3F, //heart
		0x00, 0xFF, 0xFF, 0x01, // U
		};

const uint8_t PROGMEM PATTERN_ARROW[] =
{ 0x08, 0x14, 0x22, 0x77, 0x14, 0x14, 0x14, 0x14, 0x14, 0x1c, };

void setup()
{
	delay(0x200);

	cache = new byte(BYTE_LENGTH);
	Serial.begin(57600);
	cube.sendMode(Controller_A3D8_Basic::XYZ);
	cube.sendBrightness(0xff);

	dm.clear(0x00);

	for (byte i = 0; i < 4; i++)
		dm.setDot(0, 0, i);

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

	cube.sendGlobal(0xff);
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

void animationFlowZPosi()
{
	dm.setMoveDirection(DotMatrix3D::Z_POSI);
	dm.move(false);
	for (byte i = 0; i < random(4); i++)
	{
		byte x = random(8);
		byte y = random(8);
		dm.setDot(x, y, 0);
	}
	cube.putDM();
}

void animationMoveSide()
{
	static byte k = 0;

	if (k == 0 || k == 72)
		dm.clear(0x01);

	byte index;

	for (word i = dm.countBytes(); i;)
	{
		i--;
		byte temp = dm.getByte(i) & 0x81;
		dm.setByte(i, ((dm.getByte(i) & 0x7e) << 1) | temp);
	}

	if (bitRead(dm.orValue(),0) == true)
	{
		do
		{
			index = random(64);
		} while (dm.getByte(index) != 0x01);
		dm.setByte(index, 0x02);
	}

	k < 72 ? cube.putDM() : cube.putDMrevZ();

	if (++k == 144)
		k = 0;
}

void animationMoveSideQuick()
{
	static byte k = 0;
	static bool b = true;

	if (k == 0)
	{
		for (byte i = 0; i < BYTE_LENGTH; i++)
		{
			cache[i] = _BV(random(8));
		}
	}

	if (b)
		for (byte i = 0; i < BYTE_LENGTH; i++)
		{
			byte temp = dm.getByte(i);
			if (dm.getByte(i) < cache[i])
				dm.setByte(i, temp << 1);
		}
	else
	{
		for (byte i = 0; i < BYTE_LENGTH; i++)
		{
			byte temp = dm.getByte(i);
			if (dm.getByte(i) < 0x80)
				dm.setByte(i, temp << 1);
		}
	}

	cube.putDM();
	k++;
	if (k == 8 || k == 16)
		b = !b;
	if (k == 16)
		k = 0;

}

void animationWave2D()
{
	static byte k = 0;
	static bool b = false;

	dm.setMoveDirection(DotMatrix3D::Y_POSI);
	dm.move(false);

	dm.setByte(k, 0xff);
	cube.putDM();

	if (k == 7 || k == 0)
		b = !b;

	b ? k++ : k--;
}

void animationWave3D()
{
	static byte k = 0;
	static bool b = false;

	for (byte i = 0; i < 8; i++)
		cache[i] = dm.getByte(i);

	dm.setMoveDirection(DotMatrix3D::Y_POSI);
	dm.move(false);

	for (byte i = 0; i < 8; i++)
		dm.setByte(i, cache[i]);

	for (byte i = 7; i; i--)
		dm.setByte(i, dm.getByte(i - 1));

	dm.setByte(0x00, _BV(k));
	if (k == 7 || k == 0)
		b = !b;

	cube.putDM();
	b ? k++ : k--;
}

void animationWaveShake()
{
	static byte k = 0;
	static bool b = false;

	dm.setMoveDirection(DotMatrix3D::X_POSI);
	dm.move(false);
	dm.setLine(0, k, 7, 7 - k);

	cube.putDM();

	if (k == 7 || k == 0)
		b = !b;

	cube.putDM();
	b ? k++ : k--;
}

void animationWaveRotate()
{
	static byte k = 0;

	dm.setMoveDirection(DotMatrix3D::X_POSI);
	dm.move(false);

	byte temp = k % 7;
	cache[0] = 0;
	cache[1] = temp;
	cache[2] = 7;
	cache[3] = 7 - temp;

	byte i = k / 7;

	dm.setLine(cache[i % 4], cache[(i + 1) % 4], cache[(i + 2) % 4],
			cache[(i + 3) % 4]);

	cube.putDM();

	if (++k == 28)
		k = 0;

	cube.putDM();

}

void animationDance()
{
	static char x = 4, y = 4;

	dm.setMoveDirection(DotMatrix3D::Z_POSI);
	dm.move();

	char vx = random(3) - 1;
	char vy = random(3) - 1;

	x += vx;
	y += vy;

	if (x >= 8 || x < 0)
	{
		x -= vx + vx;
	}

	if (y >= 8 || y < 0)
	{
		y -= vy + vy;
	}

	dm.setDot(x, y, 0);
	cube.putDM();
}

void animationRotateArrow()
{
	static byte k = 0;
	dm.rotate(0, false, false);
	if (k < 10)
		dm.setByte(0, pgm_read_byte_near(PATTERN_ARROW+k));
	cube.putDM();
	if (++k == 28)
		k = 0;
}

void animationRotateLove()
{
	static byte k = 0;

	if (k % 56 == 0)
	{
		for (byte i = 0; i < 4; i++)
		{
			byte value = DotMatrix::reverseByte(
					pgm_read_byte_near(PATTERN_LOVE+(k/56)*4+i));
			dm.setByte(0x20 + i, value);
			dm.setByte(0x27 - i, value);
			dm.setByte(0x18 + i, value);
			dm.setByte(0x1f - i, value);
		}
	}

	dm.rotateSync(true, true);

	cube.putDM();

	if (++k == 28 * 6)
		k = 0;

}

void animationOneByOne()
{
	static bool b = true;
	byte col, row;

	if (b)
	{
		if (dm.andValue() != 0xff)
		{
			do
			{
				col = random(64);
				row = random(8);
			} while (dm.getDot(col, row) == true);
			dm.DotMatrix::setDot(col, row, true);
		}
		else
			b = false;
	}
	else
	{
		if (dm.orValue())
		{
			do
			{
				col = random(64);
				row = random(8);
			} while (dm.getDot(col, row) == false);
			dm.DotMatrix::setDot(col, row, false);
		}
		else
			b = true;
	}

	cube.putDM();
}

void callAnimation(void (*p)(), uint16_t span, uint16_t times, byte init_value,
		Controller_A3D8_Basic::InputMode mode)
{
	cube.sendMode(mode);
	dm.clear(init_value);
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
	callAnimation(animationFlash, 0xF0, 0x08, 0x00, Controller_A3D8_Basic::XYZ);
	callAnimation(animationBreathe, 0x08, 0xff * 4, 0xff,
			Controller_A3D8_Basic::XYZ);
	callAnimationInModes(animationFacetScan, 0x40, 0x08, 0x00);
	callAnimationInModes(animationBlockScan, 0x40, 0x08, 0x00);
	callAnimationInModes(animationFlowZPosi, 0x40, 0x40, 0x00);
	callAnimationInModes(animationMoveSide, 0x30, 144, 0x00);
	callAnimationInModes(animationMoveSideQuick, 0x40, 0x10, 0x01);
	callAnimationInModes(animationWave2D, 0x40, 14 * 4, 0x00);
	callAnimation(animationWave3D, 0x40, 14 * 8, 0x00,
			Controller_A3D8_Basic::ZXY);

	callAnimation(animationWaveRotate, 0x20, 14 * 8, 0x00,
			Controller_A3D8_Basic::XYZ);
	callAnimation(animationWaveRotate, 0x20, 14 * 8, 0x00,
			Controller_A3D8_Basic::YZX);

	callAnimation(animationDance, 0x20, 0x80, 0x00, Controller_A3D8_Basic::ZXY);

	callAnimation(animationRotateArrow, 0x20, 28 * 3, 0x00,
			Controller_A3D8_Basic::YZX);

	callAnimation(animationRotateArrow, 0x30, 28 * 3, 0x00,
			Controller_A3D8_Basic::ZXY);

	callAnimation(animationRotateLove, 0x30, 28 * 6, 0x00,
			Controller_A3D8_Basic::ZXY);

	callAnimation(animationOneByOne, 0x10, 0x400, 0x00,
			Controller_A3D8_Basic::XYZ);
}

