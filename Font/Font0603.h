/*
 * NumFont0603.h
 *
 *  Created on: 2012-3-3
 *      Author: Agu
 */

#ifndef FONT_0603_H_
#define FONT_0603_H_

#include <avr/pgmspace.h>

#ifdef PROGMEM
  #undef PROGMEM
  #define PROGMEM __attribute__((section(".progmem.data")))
#endif

extern const uint8_t PROGMEM FONT_0603_STATE[];
extern const uint8_t PROGMEM FONT_0603[];
//extern const uint8_t PROGMEM BAR[];



#endif /* NUMFONT0603_H_ */
