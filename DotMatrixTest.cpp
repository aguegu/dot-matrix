#include "DotMatrixTest.h"

void setup()
{
	for (byte i=0; i<20;i++)
	{	pinMode(i, OUTPUT);
		digitalWrite(i, HIGH);
	}
	digitalWrite(5,LOW);
}

void loop()
{

}
