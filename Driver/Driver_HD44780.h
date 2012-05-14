/*
	Driver_HD44780.h
	Driver_HD44780 Class for dot-matrix printing on liquid crystal display driven by HD47780, namely 1602/1604
	Created on: 2012-02-29
	Updated on: 2012-05-14

	library for Arduino for Dot Matrix Display, support driver by 74HC595 and 74HC138, ST7920, HD47780
	Author: Weihong Guan
	Blog: http://aguegu.net
	E-mail: weihong.guan@gmail.com
	Code license: Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0)
	http://creativecommons.org/licenses/by-nc-sa/3.0/

	source host: https://github.com/aguegu/dot-matrix
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
	void putCache() const;

	void printf(const char *__fmt, ...);
	void printf(byte index, const char *__fmt, ...);
	void convertDotMatrixToCache();

private:

	const DotMatrix & _dm;
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
#endif /* Driver_HD44780.h */
