/*
 * Driver_ST7920.h
 *
 *  Created on: 2012-3-4
 *      Author: Agu
 */

#ifndef DRIVER_ST7920_H_
#define DRIVER_ST7920_H_

#include "Arduino.h"
#include "DotMatrix.h"

class ST7920
{
public:
	ST7920(DotMatrix & dm, uint8_t pin_rs, uint8_t pin_en, uint8_t pin_d4, uint8_t pin_d5, uint8_t pin_d6, uint8_t pin_d7);
	virtual ~ST7920();

	void init();
	void writeCmd(byte c);
	void writeData(byte c);
	void printWord(char *);
	void clear();
	void home();
	void setEntryMode(bool right = true);
	void setDisplayMode(bool display = true, bool cursor = false, bool blink = false);
	void moveCursor(bool right = true);
	void moveDisplay(bool right = true);
	void setFunctionMode(bool interface8 = false, bool re = false, bool graphic = false);
	void setCgRam(byte value);
	void setDdRam(byte address);	// Set address in Text Mode
	void clearImage(byte c = 0x00);
	void putImage();

private:

	const uint8_t _pin_rs;
	const uint8_t _pin_en;
	uint8_t _pin_d[4];
	DotMatrix & _dm;

	void initPin();
	void pulseEn();
	void setDB2(byte c, bool high);
	void writeDataRev(byte c);
};

#endif /* LCD12864_H_ */
