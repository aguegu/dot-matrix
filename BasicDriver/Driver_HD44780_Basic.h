/*
 * Driver_HD44780_Basic.h
 *
 *  Created on: 2012-6-1
 *      Author: agu
 */

#ifndef DRIVER_HD44780_BASIC_H_
#define DRIVER_HD44780_BASIC_H_

#include "Arduino.h"

#ifdef PROGMEM
  #undef PROGMEM
  #define PROGMEM __attribute__((section(".progmem.data")))
#endif

class HD44780_Basic
{
public:
	HD44780_Basic(uint8_t pin_rs, uint8_t pin_en,
			uint8_t pin_d4, uint8_t pin_d5, uint8_t pin_d6, uint8_t pin_d7,
			byte col_count, byte row_count);
	virtual ~HD44780_Basic();

	void init();
	void clear() const;
	void rst() const;

	void setCursor(byte address) const;
	void moveCursor(bool right) const;
	void moveScreen(bool right) const;

	void configureDisplay(bool display_on = true, bool cursor = true, bool blink = true) const;
	void setCGRam(byte *pFont, byte length) const;

	void putString(byte address, char *p, byte length) const;
	void putChar(byte address, char c) const;
	void putCache() const;

	void setCache(byte value = 0x00);
	void setCache(byte index, byte value);
	void printf(const char *__fmt, ...);
	void printf(byte index, const char *__fmt, ...);

private:

	char * _cache;

	const uint8_t _pin_rs;
	const uint8_t _pin_en;
	uint8_t _pin_dt[4];

	byte _row_count;
	byte _col_count;
	byte _cache_length;

	void initHardware() const;

	void setDT(byte c, bool b) const;
	void pulseEn(void) const;
	void setData(byte c) const;

	void writeCmd(byte) const;
	void writeData(byte) const;

	void setInputMode(bool ac = true, bool screen_move = false) const;
	void setFunctionMode(bool interface8 = false, bool doubleline = true, bool font5x10 = false) const;
};

#endif /* DRIVER_HD44780_BASIC_H_ */
