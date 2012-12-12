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

#define bitReadInByteRev(value, bit) ((value) & (0x80 >> (bit)))
#define bitSetInByteRev(value, bit) ((value) |= (0x80 >> (bit)))
#define bitClearInByteRev(value, bit) ((value) &= ~(0x80 >> (bit)))
#define bitWriteInByteRev(value, bit, bitvalue) (bitvalue ? bitSetInByteRev(value, bit) : bitClearInByteRev(value, bit))

#endif

