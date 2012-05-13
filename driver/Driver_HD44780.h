/*
 * Driver_HD44780.h
 *
 *  Created on: 2012-2-29
 *      Author: Agu
 */

#ifndef DRIVER_HD44780_H_
#define DRIVER_HD44780_H_

#include "Arduino.h"
#include "DotMatrix.h"

#ifdef PROGMEM
  #undef PROGMEM
  #define PROGMEM __attribute__((section(".progmem.data")))
#endif

extern const uint8_t PROGMEM HD44780_BAR[];

class HD44780
{
public:
	HD44780(DotMatrix dm, uint8_t pin_rs, uint8_t pin_en, uint8_t pin_d4, uint8_t pin_d5, uint8_t pin_d6, uint8_t pin_d7);
	virtual ~HD44780();
	void init();
	void clear();
	void rst();
	void setCursor(byte address);
	void moveCursor(bool right);
	void moveScreen(bool right);

	void setDisplayMode(bool display_on = true, bool cursor = true, bool blink = true);
	void setCGRam(byte *pFont, byte length);

	void putString(byte address, char *p, byte length);
	void putChar(byte address, char c);

private:

	DotMatrix & _dm;

	const uint8_t _pin_rs;
	const uint8_t _pin_en;
	uint8_t _pin_dt[4];

	void initHardware();

	void setDT(byte c, bool b);
	void pulseEn(void);
	void setData(byte c);

	void writeCmd(byte);
	void writeData(byte);

	void setInputMode(bool ac = true, bool screen_move = false);
	void setFunctionMode(bool interface8 = false, bool doubleline = true, bool font5x10 = false);
};
#endif /* Driver_HD44780.h */
