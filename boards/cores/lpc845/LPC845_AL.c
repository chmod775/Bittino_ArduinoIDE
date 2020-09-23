#include "LPC845_AL.h"

/* USARTs array */
USART_Type *USARTS_ARRAY[] = USART_BASE_PTRS;

const swm_select_movable_t SWM_USARTS_ARRAY[5][5] = {
    { kSWM_USART0_TXD,    kSWM_USART0_RXD,    kSWM_USART0_RTS,    kSWM_USART0_CTS,    kSWM_USART0_SCLK },
    { kSWM_USART1_TXD,    kSWM_USART1_RXD,    kSWM_USART1_RTS,    kSWM_USART1_CTS,    kSWM_USART1_SCLK },
    { kSWM_USART2_TXD,    kSWM_USART2_RXD,    kSWM_USART2_RTS,    kSWM_USART2_CTS,    kSWM_USART2_SCLK },
    { kSWM_USART3_TXD,    kSWM_USART3_RXD,    kSWM_MOVABLE_NUM_FUNCS,                  kSWM_MOVABLE_NUM_FUNCS,                  kSWM_USART3_SCLK },
    { kSWM_USART4_TXD,    kSWM_USART4_RXD,    kSWM_MOVABLE_NUM_FUNCS,                  kSWM_MOVABLE_NUM_FUNCS,                  kSWM_USART4_SCLK },
};

const clock_select_t CLOCK_USARTS_ARRAY[5][5] = {
  { kUART0_Clk_From_Fro    ,    kUART0_Clk_From_MainClk,    kUART0_Clk_From_Frg0Clk,    kUART0_Clk_From_Frg1Clk,    kUART0_Clk_From_Fro_Div },
  { kUART1_Clk_From_Fro    ,    kUART1_Clk_From_MainClk,    kUART1_Clk_From_Frg0Clk,    kUART1_Clk_From_Frg1Clk,    kUART1_Clk_From_Fro_Div },
  { kUART2_Clk_From_Fro    ,    kUART2_Clk_From_MainClk,    kUART2_Clk_From_Frg0Clk,    kUART2_Clk_From_Frg1Clk,    kUART2_Clk_From_Fro_Div },
  { kUART3_Clk_From_Fro    ,    kUART3_Clk_From_MainClk,    kUART3_Clk_From_Frg0Clk,    kUART3_Clk_From_Frg1Clk,    kUART3_Clk_From_Fro_Div },
  { kUART4_Clk_From_Fro    ,    kUART4_Clk_From_MainClk,    kUART4_Clk_From_Frg0Clk,    kUART4_Clk_From_Frg1Clk,    kUART4_Clk_From_Fro_Div }
};

/* IOCON BittinoPin array */
const unsigned short IOCON_INDEX_BP_ARRAY[] = {
  IOCON_INDEX_PIO0_0,   // BUILT IN LED

  IOCON_INDEX_PIO0_17,   // PIN 1
  IOCON_INDEX_PIO0_4,   // PIN 2
  IOCON_INDEX_PIO0_13,  // PIN 3
  IOCON_INDEX_PIO0_18,  // PIN 4
  IOCON_INDEX_PIO0_23,  // PIN 5
  IOCON_INDEX_PIO0_14,  // PIN 6
  IOCON_INDEX_PIO0_21,  // PIN 7

  IOCON_INDEX_PIO0_12,  // BUILT IN BUTTON

  IOCON_INDEX_PIO0_7,   // PIN 9
  IOCON_INDEX_PIO0_1,   // PIN 10
  IOCON_INDEX_PIO0_25,  // PIN 11
  IOCON_INDEX_PIO0_24,  // PIN 12
  IOCON_INDEX_PIO0_3,   // PIN 13
  IOCON_INDEX_PIO0_2,   // PIN 14
  IOCON_INDEX_PIO0_28   // PIN 15
};

/* SWM BittinoPin array */
const swm_port_pin_type_t SWM_PORTPIN_BP_ARRAY[] = {
  kSWM_PortPin_P0_0,   // BUILT IN LED

  kSWM_PortPin_P0_17,  // PIN 1
  kSWM_PortPin_P0_4,   // PIN 2
  kSWM_PortPin_P0_13,  // PIN 3
  kSWM_PortPin_P0_18,  // PIN 4
  kSWM_PortPin_P0_23,  // PIN 5
  kSWM_PortPin_P0_14,  // PIN 6
  kSWM_PortPin_P0_21,  // PIN 7

  kSWM_PortPin_P0_12,  // BUILT IN BUTTON

  kSWM_PortPin_P0_7,   // PIN 9
  kSWM_PortPin_P0_1,   // PIN 10
  kSWM_PortPin_P0_25,  // PIN 11
  kSWM_PortPin_P0_24,  // PIN 12
  kSWM_PortPin_P0_3,   // PIN 13
  kSWM_PortPin_P0_2,   // PIN 14
  kSWM_PortPin_P0_28   // PIN 15
};

/* SWM Fixed BittinoPin array */
const swm_select_fixed_pin_t SWM_FIXED_A_BP_ARRAY[] = {
  kSWM_FIXEDPIN_NUM_FUNCS,   // BUILT IN LED

  kSWM_ADC_CHN9,   // PIN 1
  kSWM_ADC_CHN11,   // PIN 2
  kSWM_ADC_CHN10,  // PIN 3
  kSWM_ADC_CHN8,  // PIN 4
  kSWM_ADC_CHN3 ,  // PIN 5
  kSWM_ADC_CHN2,  // PIN 6
  kSWM_ADC_CHN5,  // PIN 7

  kSWM_FIXEDPIN_NUM_FUNCS,  // BUILT IN BUTTON

  kSWM_ADC_CHN0,   // PIN 9
  kSWM_ACMP_INPUT2,   // PIN 10
  kSWM_FIXEDPIN_NUM_FUNCS,  // PIN 11
  kSWM_FIXEDPIN_NUM_FUNCS,  // PIN 12
  kSWM_SWCLK,   // PIN 13
  kSWM_SWDIO,   // PIN 14
  kSWM_FIXEDPIN_NUM_FUNCS   // PIN 15
};

const swm_select_fixed_pin_t SWM_FIXED_B_BT_ARRAY[] = {
  kSWM_FIXEDPIN_NUM_FUNCS,   // BUILT IN LED

  kSWM_DAC_OUT0,   // PIN 1
  kSWM_FIXEDPIN_NUM_FUNCS,   // PIN 2
  kSWM_FIXEDPIN_NUM_FUNCS,  // PIN 3
  kSWM_FIXEDPIN_NUM_FUNCS,  // PIN 4
  kSWM_ACMP_INPUT4,  // PIN 5
  kSWM_ACMP_INPUT3,  // PIN 6
  kSWM_FIXEDPIN_NUM_FUNCS,  // PIN 7

  kSWM_FIXEDPIN_NUM_FUNCS,  // BUILT IN BUTTON

  kSWM_FIXEDPIN_NUM_FUNCS,   // PIN 9
  kSWM_FIXEDPIN_NUM_FUNCS,   // PIN 10
  kSWM_FIXEDPIN_NUM_FUNCS,  // PIN 11
  kSWM_FIXEDPIN_NUM_FUNCS,  // PIN 12
  kSWM_FIXEDPIN_NUM_FUNCS,   // PIN 13
  kSWM_FIXEDPIN_NUM_FUNCS,   // PIN 14
  kSWM_FIXEDPIN_NUM_FUNCS   // PIN 15
};