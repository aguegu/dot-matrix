/*
 * hfont_12x8.h
 *
 *  Created on: Jan 29, 2013
 *      Author: agu
 */

#ifndef HFONT_12X7_H_
#define HFONT_12X7_H_

#include <avr/pgmspace.h>

#ifdef PROGMEM
  #undef PROGMEM
  #define PROGMEM __attribute__((section(".progmem.data")))
#endif

extern const uint8_t PROGMEM HFONT_12X7[] ;

#endif /* HFONT_12X7_H_ */
