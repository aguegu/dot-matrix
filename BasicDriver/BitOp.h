/*
 * BitOp.h
 *
 *  Created on: Dec 13, 2012
 *      Author: agu
 */

#ifndef BIT_OP
#define BIT_OP

#define bitReadInByte(value, bit) ((value) & _BV(bit))
#define bitSetInByte(value, bit) ((value) |= _BV(bit))
#define bitClearInByte(value, bit) ((value) &= ~_BV(bit))
#define bitWriteInByte(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

#endif

