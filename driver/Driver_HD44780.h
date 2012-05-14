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
	void clear() const;
	void rst() const;

	void setCursor(byte address) const;
	void moveCursor(bool right) const;
	void moveScreen(bool right) const;

	void setDisplayMode(bool display_on = true, bool cursor = true, bool blink = true) const;
	void setCGRam(byte *pFont, byte length) const;

	void putString(byte address, char *p, byte length) const;
	void putChar(byte address, char c) const;

	void printCache();
	void printf(const char *__fmt, ...);
	void printf(byte index, const char *__fmt, ...);
	void printDotMatrix();

private:

	const DotMatrix & _dm;
	byte _row_count;
	byte _col_count;
	byte _cache_length;
	char * _cache;

	const uint8_t _pin_rs;
	const uint8_t _pin_en;
	uint8_t _pin_dt[4];

	void initHardware() const;

	void setDT(byte c, bool b) const;
	void pulseEn(void) const;
	void setData(byte c) const;

	void writeCmd(byte) const;
	void writeData(byte) const;

	void setInputMode(bool ac = true, bool screen_move = false) const;
	void setFunctionMode(bool interface8 = false, bool doubleline = true, bool font5x10 = false) const;
};
#endif /* Driver_HD44780.h */
