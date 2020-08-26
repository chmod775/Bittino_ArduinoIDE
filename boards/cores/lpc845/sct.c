/**************************************************************************/
/*!
    @file     sct.c
    @author   ChrisMicro
    @author   unknown others
    @brief    state configurable timer functions

    @section LICENSE see below for my code contribution

*/
/**************************************************************************/
#include "LPC8xx.h"
#include "sct.h"

void sct_fsm_init (void);

void init_sct(uint8_t channel)
{
	// set pre-scalar, SCT clock = 1 MHz, clear counter
    //LPC_SCT->CTRL_L |= (((SystemCoreClock/1000000-1) << 5) | (1<<3));

	// connect SCT OUTP_0 to IO-PIN
	LPC_SWM->PINASSIGN6 &=0x00FFFFFF;
	//LPC_SWM->PINASSIGN6 |=3<<24; // SCT OUTP_0 at P0.3
	LPC_SWM->PINASSIGN6 |=channel<<24; // SCT OUTP_0 at P0.3

	LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 8); // enable the SCT clock
	sct_fsm_init(); // Initialize SCT
#if 0
	LPC_SCT->EVEN = (1 << 0);    // enable EVENT0 interrupt
	NVIC_EnableIRQ(SCT_IRQn); // enable SCT interrupt
#endif
	LPC_SCT->CTRL_L &= ~(1<<2); // start the SCT by clearing bit 2 in CTRL
}

void setPwm(uint8_t channel,uint16_t value)
{
	LPC_SCT->MATCHREL[1].L=value;
}

volatile uint16_t value=100;
void SCT_IRQHandler(void)
{
	uint32_t status = LPC_SCT->EVFLAG;

	//LPC_GPIO_PORT->NOT0 = 1 << 3;

	LPC_SCT->MATCHREL[1].L=value++;
	if(value>800)value=100;

	// Acknowledge interrupts
	LPC_SCT->EVFLAG = status;
  return;
}

/*
 * from LPC800 SCT Cookbook and Tutorial
 * http://www.lpcware.com/content/nxpfile/lpc80-sct-cookbook-and-tutorial-code-examples
 */

/* Generated by fzmparser version 2.4 --- DO NOT EDIT! */
/* Uses following resources: */
/* 2 events, 1+0 states, 0 inputs, 1 outputs, 2+0 match regs, 0+0 capture regs */

#define MATCH_PERIOD 1024
#define MATCH_DUTY 256 // 10% duty cycle

void sct_fsm_init (void)
{
	LPC_SCT->CONFIG = (LPC_SCT->CONFIG & ~0x00060001) | 0x00000000; /* SPLIT */

	/* MATCH/CAPTURE registers */
	LPC_SCT->REGMODE_L = 0x0000;         /* L: 2x MATCH, 0x CAPTURE, 3 unused */
	LPC_SCT->REGMODE_H = 0x0000;             /* H: 0x MATCH, 0x CAPTURE, 5 unused */
	LPC_SCT->MATCH_L[0] = MATCH_PERIOD;           // initial default value MATCH0
	LPC_SCT->MATCHREL_L[0] = MATCH_PERIOD;
	LPC_SCT->MATCH_L[1] = MATCH_DUTY;             // initial default value
	LPC_SCT->MATCHREL_L[1] = MATCH_DUTY;

	/* OUTPUT registers */
	LPC_SCT->OUT[0].SET = 0x00000001;
	LPC_SCT->OUT[0].CLR = 0x00000002;
	  /* Unused outputs must not be affected by any event */
	LPC_SCT->OUT[1].SET = 0;
	LPC_SCT->OUT[1].CLR = 0;
	LPC_SCT->OUT[2].SET = 0;
	LPC_SCT->OUT[2].CLR = 0;
	LPC_SCT->OUT[3].SET = 0;
	LPC_SCT->OUT[3].CLR = 0;

	/* Conflict resolution register */

	/* EVENT registers */
	LPC_SCT->EVENT[0].CTRL = 0x00005000;     /* L: --> state L_ENTRY */
	LPC_SCT->EVENT[0].STATE = 0x00000001;
	LPC_SCT->EVENT[1].CTRL = 0x00005001;     /* L: --> state L_ENTRY */
	LPC_SCT->EVENT[1].STATE = 0x00000001;
	  /* Unused events must not have any effect */
	LPC_SCT->EVENT[2].STATE = 0;
	LPC_SCT->EVENT[3].STATE = 0;
	LPC_SCT->EVENT[4].STATE = 0;
	LPC_SCT->EVENT[5].STATE = 0;

	/* STATE registers */
	LPC_SCT->STATE_L = 0;
	LPC_SCT->STATE_H = 0; /* implicit value */

	/* state names assignment: */
	  /* State L 0: L_ENTRY */

	/* CORE registers */
	LPC_SCT->START_L = 0x0000;
	LPC_SCT->STOP_L =  0x0000;
	LPC_SCT->HALT_L =  0x0000;
	LPC_SCT->LIMIT_L = 0x0001;
	LPC_SCT->START_H = 0x0000;
	LPC_SCT->STOP_H =  0x0000;
	LPC_SCT->HALT_H =  0x0000;
	LPC_SCT->LIMIT_H = 0x0000;
	LPC_SCT->EVEN =    0x00000000;

}

/***********************************************************************************

    Software License Agreement (BSD License)

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

***********************************************************************************/


