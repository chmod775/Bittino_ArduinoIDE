/*
 * Copyright 2017-2018 NXP
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Peripherals v1.0
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/*******************************************************************************
 * Included files
 ******************************************************************************/
#include "drivers/fsl_common.h"
#include "drivers/fsl_gpio.h"
#include "peripherals.h"

/*******************************************************************************
 * BOARD_InitBootPeripherals function
 ******************************************************************************/
void BOARD_InitBootPeripherals(void)
{
  BOARD_InitPeripherals();
}

void BOARD_InitPeripherals(void)
{
  GPIO_PortInit(GPIO, 0);
}