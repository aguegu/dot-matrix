/*
 *	Driver_HD44780_Basic.h
 *	Driver_HD44780_Basic Class, arduino driver for liquid crystal display driven by HD47780, namely 1602/1604
 *	Created on: 2012-06-01
 *
 *	library for Arduino for Dot Matrix Display, support driver by 74HC595 and 74HC138, ST7920, HD47780
 *	Author: Weihong Guan
 *	Blog: http://aguegu.net
 *	E-mail: weihong.guan@gmail.com
 *
 *	Code license: Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0)
 *	http://creativecommons.org/licenses/by-nc-sa/3.0/
 *	source host: https://github.com/aguegu/dot-matrix
 */

#ifndef DRIVER_HD44780_BASIC_H_
#define DRIVER_HD44780_BASIC_H_

#include "Arduino.h"
#include "pinWrite.h"

#ifdef PROGMEM
  #undef PROGMEM
  #define PROGMEM __attribute__((section(".progmem.data")))
#endif

class HD44780_Basic
{
public:
	HD44780_Basic(uint8_t pin_rs, uint8_t pin_en, uint8_t pin_d4, uint8_t pin_d5, uint8_t pin_d6, uint8_t pin_d7,
			byte row_count = 2, byte col_count = 16);
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

protected:

	const byte _row_count;
	const byte _col_count;
	byte _cache_length;
	char * _cache;

private:

	const uint8_t _pin_rs;
	const uint8_t _pin_en;
	uint8_t _pin_dt[4];


	void initHardware() const;

	void setDT(byte c, bool b) const;
	inline void pulseEn(void) const;
	void setData(byte c) const;

	void writeCmd(byte) const;
	void writeData(byte) const;

	void configureInput(bool ac = true, bool screen_move = false) const;
	void configureFunction(bool interface8 = false, bool doubleline = true, bool font5x10 = false) const;
};

#endif /* DRIVER_HD44780_BASIC_H_ */
