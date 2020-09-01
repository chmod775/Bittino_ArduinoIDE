/**************************************************************************/
/*!
    @file     arduino.c
    @author   ChrisMicro
    @author   others ( marked in code )
    @brief    arduino compatible functions for LPC810

    @section LICENSE see below for my code contribution

*/
/**************************************************************************/
#include "Arduino.h"

const uint8_t pin_map[] = {0, 17, 4, 13, 18, 23, 14, 21, 0, 7, 25, 1, 24, 16, 11, 10, 0};

void pinMode(uint8_t pin, uint8_t mode)
{
	gpio_pin_config_t config =
	{
		kGPIO_DigitalInput,
		0,
	};

	if (mode == OUTPUT)
		config.pinDirection = kGPIO_DigitalOutput;

	GPIO_PinInit(GPIO, 0, pin_map[pin], &config);
}

void digitalWrite(uint8_t pin, uint8_t value)
{
	GPIO_PinWrite(GPIO, 0, pin_map[pin], value);
}

void digitalToggle(uint8_t pin)
{
	digitalWrite(pin, !digitalRead(pin));
}

int digitalRead(uint8_t pin)
{
	return GPIO_PinRead(GPIO, 0, pin_map[pin]);
}

/*
 * from wiring.c
 * https://code.google.com/p/arduino/source/browse/trunk/hardware/arduino/cores/arduino/wiring.c
 *
 *   wiring.c - Partial implementation of the Wiring API for the ATmega8.
 * Part of Arduino - http://www.arduino.cc/
 *
 * Copyright (c) 2005-2006 David A. Mellis
 */

void delay(unsigned long ms)
{
  for(int i=0;i<100000;i++) {
    __asm("nop");
  }
}
// https://code.google.com/p/arduino/source/browse/trunk/hardware/arduino/cores/arduino/WMath.cpp
int32_t map(int32_t x, int32_t in_min, int32_t in_max, int32_t out_min, int32_t out_max)
{
  int32_t value=(x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  return value;
}

/*
 * The syntax for real Arduinos would be
 * Serial.begin(9600);
 *
 * Because the LPC810 software is not written in c++,
 * we can not use the "."
 * We use "_" instead which results in a slitly incompatile library.
 *
 */
void Serial_begin(uint32_t baudRate)
{
	uart0Init(baudRate);
}
/*
 * Serial_print can only print text, not numbers
 * due to the lack auf c++
 */
void Serial_print(char * string)
{
	printf("%s",string);
}
void Serial_println(char * string)
{
	printf("%s\n\r",string);
}
void Serial_printnumber(uint32_t number)
{
	printf("%d ",number);
}

uint16_t analogRead(uint8_t channel )
{
	static uint8_t initFlags=0;

	uint16_t value=0;

	if((initFlags&(1<<channel))==0)
	{
		init_adc(channel);
		initFlags|=1<<channel;
	}

	return 	read_adc(channel);
}
// value 0..255
void analogWrite(uint8_t analogOutPin, uint16_t value)
{
	static uint8_t initFlags=0;

	if((initFlags&(1<<analogOutPin))==0)
	{
		init_sct(analogOutPin);
		initFlags|=1<<analogOutPin;
	}
	setPwm(analogOutPin,value*4); // scale value to 1023 for Arduino Uno compatibility
}
/******************************************************************************

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:
	1. Redistributions of source code must retain the above copyright
	notice, this list of conditions and the following disclaimer.
	2. Redistributions in binary form must reproduce the above copyright
	notice, this list of conditions and the following disclaimer in the
	documentation and/or other materials provided with the distribution.
	3. Neither the name of the copyright holders nor the
	names of its contributors may be used to endorse or promote products
	derived from this software without specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
	EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
	DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
	DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
	LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
	ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*************************************************************************/
