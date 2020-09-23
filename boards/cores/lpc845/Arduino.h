/*
  Arduino.h - Main include file for the Arduino SDK

  Copyright (c) 2014 ChrisMicro.  All right reserved.

*/

#ifndef Arduino_h
#define Arduino_h

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "arduino/lpc_drivers.h"

typedef bool boolean;
typedef uint8_t byte;
typedef uint16_t word;

#include "arduino/binary.h"
#include "arduino/itoa.h"

#define LED_BUILTIN 0
#define BUTTON_BUILTIN 16

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

#include "arduino/wiring_constants.h"

#define clockCyclesPerMicrosecond() ( SystemCoreClock / 1000000L )
#define clockCyclesToMicroseconds(a) ( ((a) * 1000L) / (SystemCoreClock / 1000L) )
#define microsecondsToClockCycles(a) ( (a) * (SystemCoreClock / 1000000L) )

void yield( void ) ;

/* system functions */
int main( void );
void init( void );

/* sketch */
void setup( void ) ;
void loop( void ) ;

void delay(uint32_t milliSeconds);
void Serial_begin(uint32_t baudRate);
void Serial_print(char * string);
void Serial_println(char * string);
void Serial_printnumber(uint32_t number);
uint32_t millis();
uint16_t analogRead(uint8_t channel );
void analogWrite(uint8_t analogOutPin, uint16_t value);
int32_t map(int32_t x, int32_t in_min, int32_t in_max, int32_t out_min, int32_t out_max);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#include "arduino/wiring.h"
#include "arduino/wiring_digital.h"
//#include "arduino/wiring_analog.h"
//#include "arduino/wiring_shift.h"


// undefine stdlib's abs if encountered
#ifdef abs
#undef abs
#endif // abs

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define abs(x) ((x)>0?(x):-(x))
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define round(x)     ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))
#define radians(deg) ((deg)*DEG_TO_RAD)
#define degrees(rad) ((rad)*RAD_TO_DEG)
#define sq(x) ((x)*(x))

#define interrupts() __enable_irq()
#define noInterrupts() __disable_irq()

#define lowByte(w) ((uint8_t) ((w) & 0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

#define bit(b) (1UL << (b))

#endif // Arduino_h
