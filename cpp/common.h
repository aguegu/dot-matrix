#ifndef COMMON_H
#define COMMON_H

#ifdef __cplusplus
extern "C"{
#endif

typedef unsigned char boolean;
typedef unsigned char byte;
typedef unsigned short word;

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;

#ifdef abs
#undef abs
#endif

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define abs(x) ((x)>0?(x):-(x))
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define round(x)     ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))
#define radians(deg) ((deg)*DEG_TO_RAD)
#define degrees(rad) ((rad)*RAD_TO_DEG)
#define sq(x) ((x)*(x))

#define lowByte(w) ((uint8_t) ((w) & 0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))
#define makeWord(h, l) (((h) << 8) + (l))


#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

#define readLowBitInByte(value, bit) ((value) & _BV(bit))
#define setLowBitInByte(value, bit) ((value) |= _BV(bit))
#define clearLowbitInByte(value, bit) ((value) &= ~_BV(bit))
#define writeLowBitInByte(value, bit, bitvalue) (bitvalue ? setLowBitInByte(value, bit) : clearLowbitInByte(value, bit))

#define readHighBitInByte(value, bit) ((value) & (0x80 >> (bit)))
#define setHighBitInByte(value, bit) ((value) |= (0x80 >> (bit)))
#define clearHighBitInByte(value, bit) ((value) &= ~(0x80 >> (bit)))
#define writeHighBitInByte(value, bit, bitvalue) (bitvalue ? setHighBitInByte(value, bit) : clearHighBitInByte(value, bit))

#define _BV(bit) (1 << (bit))

#define pgm_read_byte_near(x) (*(x))


#ifdef __cplusplus
}
#endif

#endif
