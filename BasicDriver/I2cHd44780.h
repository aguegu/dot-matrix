/*
 * I2cHd44780.h
 *
 *  Created on: Jan 8, 2013
 *      Author: agu
 */

#ifndef I2CHD44780_H_
#define I2CHD44780_H_

#include "Arduino.h"
#include "Twi.h"

#define PIN_RS	0
#define PIN_RW	1
#define PIN_EN	2
#define PIN_BL	3	// backlight, background LED


class I2cHd44780
{
public:
	I2cHd44780(byte address, byte row_count = 2, byte col_count = 16);
	virtual ~I2cHd44780();

	void init();
	void clear() const;
	void rst() const;

	void setCursor(byte address) const;
	void moveCursor(bool right) const;
	void moveScreen(bool right) const;

	void configureDisplay(bool display_on = true, bool cursor = true,
			bool blink = true) const;
	void setCGRam(byte *pFont, byte length) const;

	void putString(byte address, char *p, byte length) const;
	void putChar(byte address, char c) const;
	void putCache() const;

	void setCache(byte value = 0x00);
	void setCache(byte index, byte value);
	void printf(const char *__fmt, ...);
	void printf(byte index, const char *__fmt, ...);

private:

	const byte _address;
	bool _backlight;

	void initHardware() const;
	void transmit(bool isData, byte val) const;

	void configureInput(bool ac = true, bool screen_move = false) const;
	void configureFunction(bool interface8 = false, bool doubleline = true,
			bool font5x10 = false) const;

protected:

	const byte _row_count;
	const byte _col_count;
	byte _cache_length;
	char * _cache;
};

#endif /* I2CHD44780_H_ */
