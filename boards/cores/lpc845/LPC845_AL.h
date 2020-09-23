#ifndef _LPC845_AL_H_
#define _LPC845_AL_H_                               /**< Symbol preventing repeated inclusion */

#include "LPC845.h"
#include "drivers/fsl_swm_connections.h"
#include "drivers/fsl_clock.h"

/* USARTs array */
extern const USART_Type *USARTS_ARRAY[];
extern const IRQn_Type IRQ_USARTS_ARRAY[5];

extern const swm_select_movable_t SWM_USARTS_ARRAY[5][5];

extern const clock_select_t CLOCK_USARTS_ARRAY[5][5];

/* IOCON BittinoPin array */
extern const unsigned short IOCON_INDEX_BP_ARRAY[];

/* SWM BittinoPin array */
extern const swm_port_pin_type_t SWM_PORTPIN_BP_ARRAY[];

/* SWM Fixed BittinoPin array */
extern const swm_select_fixed_pin_t SWM_FIXED_A_BP_ARRAY[];

extern const swm_select_fixed_pin_t SWM_FIXED_B_BT_ARRAY[];

#endif