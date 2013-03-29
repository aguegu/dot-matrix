/*
 * ReverseByte.h
 *
 *  Created on: Dec 12, 2012
 *      Author: agu
 */

#ifndef REVERSE_BYTE_H

#define REVERSE_BYTE_H

#include "Arduino.h"

#ifdef PROGMEM
  #undef PROGMEM
  #define PROGMEM __attribute__((section(".progmem.data")))
#endif

#ifdef __cplusplus
extern "C"{
#endif

extern const uint8_t PROGMEM REVERSE[];

byte reverseByte(byte c);

#ifdef __cplusplus
}
#endif

#endif



