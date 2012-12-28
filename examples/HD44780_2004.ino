#include "ObdExamples.h"
#include "Obd.h"
#include "Driver_HD44780_Basic.h"
#include "RemoteTransmitter.h"

Obd obd(Serial);
HD44780_Basic lcd(12, 11, 5, 4, 3, 2, 4);
RemoteTransmitter rt(13, 478);

const uint32_t ADDRESS = 265518UL;

void setup()
{
	lcd.init();
	Serial.begin(38400);
	Serial.setTimeout(3000);

	lcd.printf("OBD Start");

//	char c[] =
//	{ 0x30, 0x31, 0x30, 0x64, 0x0D, 0x34, 0x31, 0x20, 0x30, 0x44, 0x20, 0x30,
//			0x30, 0x20, 0x0d, 0x0d };
//
//	int i;
//	sscanf(c + 11, "%02x", &i);
//	lcd.printf("%d", i);

//	for (byte i = 0; i < sizeof(c); i++)
//	{
//		//lcd.printf(i + i, "%02X", p[i]);
//		lcd.setCache(i, c[i]);
//	}

	lcd.putCache();
}

void loop()
{
	static byte counter = 0;
	static word last_speed = 0;

	word speed = obd.getByte(0x0D);

	lcd.setCache();

	if (obd.err())
	{
		char *p = obd.getOutput();
		for (byte i = 0; i < 64; i++)
			lcd.setCache(i, p[i]);

		rt.sendData(ADDRESS + 80);
		//rt.sendData(ADDRESS + 18);
	}
	else
	{
		lcd.printf(0x10, "SPD:%u km/h", speed);

		uint16_t rpm = obd.getWord(0x0C) / 4;
		lcd.printf("RPM:%u", rpm);

		int16_t throttle = obd.getByte(0x11) * 20 / 51;
		lcd.printf(0x20, "Thr:%u%%", throttle);

		int16_t load = obd.getByte(0x04) * 20 / 51;
		lcd.printf(0x30, "Load:%u%%", load);

		//if (counter > 0)
		{
			if (speed >= 30)
				rt.sendData(ADDRESS + 2); // blue swift
			else if (speed == 0)
				rt.sendData(ADDRESS + 54);
			else
			{
				if (speed > last_speed)
					rt.sendData(ADDRESS + 6);
				else //if (speed < last_speed - 2)
					rt.sendData(ADDRESS + 18);
			}

			//counter = 0;
		}

		last_speed = speed;
	}
	lcd.putCache();

	counter++;

}
