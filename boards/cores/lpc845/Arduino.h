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

#include "LPC845.h"
#include "drivers/fsl_acomp.h"
#include "drivers/fsl_adc.h"
#include "drivers/fsl_capt.h"
#include "drivers/fsl_clock.h"
#include "drivers/fsl_common.h"
#include "drivers/fsl_crc.h"
#include "drivers/fsl_ctimer.h"
#include "drivers/fsl_dac.h"
#include "drivers/fsl_dma.h"
#include "drivers/fsl_gpio.h"
#include "drivers/fsl_i2c.h"
#include "drivers/fsl_iap.h"
#include "drivers/fsl_inputmux.h"
#include "drivers/fsl_inputmux_connections.h"
#include "drivers/fsl_iocon.h"
#include "drivers/fsl_mrt.h"
#include "drivers/fsl_pint.h"
#include "drivers/fsl_power.h"
#include "drivers/fsl_reset.h"
#include "drivers/fsl_sctimer.h"
#include "drivers/fsl_spi.h"
#include "drivers/fsl_swm.h"
#include "drivers/fsl_swm_connections.h"
#include "drivers/fsl_syscon.h"
#include "drivers/fsl_syscon_connections.h"
#include "drivers/fsl_usart.h"
#include "drivers/fsl_wkt.h"
#include "drivers/fsl_wwdt.h"


#define INPUT 	0
#define OUTPUT 	1
#define INPUT_PULLUP 	1
#define INPUT_PULLDOWN 	1


#define LOW 	0
#define HIGH 	1

#define LED_BUILTIN 0


#ifdef __cplusplus
extern "C"{
#endif // __cplusplus


void pinMode(uint8_t pin, uint8_t mode);
void digitalWrite(uint8_t pin, uint8_t value);
void digitalToggle(uint8_t Pin);
int digitalRead(uint8_t pin);
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



#endif // Arduino_h
