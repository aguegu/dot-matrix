/*
 * Pattern.h
 *
 *  Created on: 2012-7-1
 *      Author: Agu
 */

#ifndef PATTERN_H_
#define PATTERN_H_

#include <avr/pgmspace.h>

#ifdef PROGMEM
  #undef PROGMEM
  #define PROGMEM __attribute__((section(".progmem.data")))
#endif

extern const uint8_t PROGMEM PATTERN_CHAR[] ;

#endif /* PATTERN_H_ */
