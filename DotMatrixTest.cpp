#include "DotMatrixTest.h"

void setup()
{
	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);
	pinMode(7, OUTPUT);
	pinMode(8, OUTPUT);
	pinMode(9, OUTPUT);

	digitalWrite(5, LOW);
//	digitalWrite(8, LOW);

}

void loop()
{
	static byte i = 0;
	digitalWrite(8, i % 24);
	digitalWrite(9, HIGH);
	digitalWrite(7, HIGH);
	digitalWrite(7, LOW);

	digitalWrite(6, HIGH);
	digitalWrite(6, LOW);
	delay(500);

	i++;

	if (i == 24)
	{
		i = 0;
		delay(1500);
	}

}
