#ifndef _AL_UART_H_
#define _AL_UART_H_

#include "../Arduino.h"

#define _USART_CLK_SRC  kCLOCK_MainClk
#define _USART_CLK_FREQ CLOCK_GetFreq(_USART_CLK_SRC)

class AL_USART;

extern AL_USART *USARTS_Instances[5];

class AL_USART
{
  private:


  public:
    const uint8_t PIN_NC = 0;

    uint8_t ID;

    USART_Type *usart = NULL;

    uint32_t bufferSize = 0;
    uint8_t *txBuffer = NULL;
    uint8_t *rxBuffer = NULL;

    AL_USART(uint8_t ID, uint8_t txPin, uint8_t rxPin, uint8_t rtsPin = 0, uint8_t ctsPin = 0, uint8_t sclkPin = 0)
    {
      if (ID > FSL_FEATURE_SOC_USART_COUNT) return;

      CLOCK_Select(kUART0_Clk_From_MainClk);//(CLOCK_USARTS_ARRAY[ID][1]); // From_MainClk

      this->usart = (USART_Type *)USARTS_ARRAY[ID];

      if (txPin != 0) {
        IOCON_PinMuxSet(IOCON, IOCON_INDEX_BP_ARRAY[txPin], 0);
        SWM_SetMovablePinSelect(SWM0, SWM_USARTS_ARRAY[ID][0], SWM_PORTPIN_BP_ARRAY[txPin]);
      }

      if (rxPin != 0) {
        IOCON_PinMuxSet(IOCON, IOCON_INDEX_BP_ARRAY[rxPin], 0 | IOCON_MODE_PULLUP);
        SWM_SetMovablePinSelect(SWM0, SWM_USARTS_ARRAY[ID][1], SWM_PORTPIN_BP_ARRAY[rxPin]);
      }

      if (rtsPin != 0) {
        IOCON_PinMuxSet(IOCON, IOCON_INDEX_BP_ARRAY[rtsPin], 0 | IOCON_MODE_PULLUP);
        SWM_SetMovablePinSelect(SWM0, SWM_USARTS_ARRAY[ID][2], SWM_PORTPIN_BP_ARRAY[rtsPin]);
      }

      if (ctsPin != 0) {
        IOCON_PinMuxSet(IOCON, IOCON_INDEX_BP_ARRAY[ctsPin], 0 | IOCON_MODE_PULLUP);
        SWM_SetMovablePinSelect(SWM0, SWM_USARTS_ARRAY[ID][3], SWM_PORTPIN_BP_ARRAY[ctsPin]);
      }

      if (sclkPin != 0) {
        IOCON_PinMuxSet(IOCON, IOCON_INDEX_BP_ARRAY[sclkPin], 0 | IOCON_MODE_PULLUP);
        SWM_SetMovablePinSelect(SWM0, SWM_USARTS_ARRAY[ID][4], SWM_PORTPIN_BP_ARRAY[sclkPin]);
      }

      USARTS_Instances[ID] = this;
    }

    AL_USART *Setup(uint32_t baudrate, uint32_t bufferSize = 32, uint8_t *txBuffer = NULL, uint8_t *rxBuffer = NULL)
    {
      this->bufferSize = bufferSize;

      if (txBuffer == NULL)
        txBuffer = (uint8_t *)malloc(sizeof(uint8_t) * bufferSize);
      this->txBuffer = txBuffer;

      if (rxBuffer == NULL)
        rxBuffer = (uint8_t *)malloc(sizeof(uint8_t) * bufferSize);
      this->rxBuffer = rxBuffer;
      
      usart_config_t config;
      /* Default config by using USART_GetDefaultConfig():
      * config.baudRate_Bps = 9600U;
      * config.parityMode = kUSART_ParityDisabled;
      * config.stopBitCount = kUSART_OneStopBit;
      * config.bitCountPerChar = kUSART_8BitsPerChar;
      * config.loopback = false;
      * config.enableRx = false;
      * config.enableTx = false;
      * config.syncMode = kUSART_SyncModeDisabled;
      */
      USART_GetDefaultConfig(&config);
      config.enableRx     = true;
      config.enableTx     = true;
      config.baudRate_Bps = baudrate;

      /* Initialize the USART with configuration. */
      USART_Init(this->usart, &config, 30000000);
      return this;
    }


    int32_t Send(uint8_t *data, uint32_t nBytes = 0) {
      return USART_WriteBlocking(USART0, data, nBytes == 0 ? bufferSize : nBytes);
    }
    int32_t SendString(char *str) {
      //strcpy((char *)this->txBuffer, str);
      return Send((uint8_t *)str, strlen(str) - 1);
    }

    int32_t Receive(uint32_t nBytes = 0) {
      //return USART_WriteBlocking(usart, data, nBytes == 0 ? bufferSize : nBytes);
      
    }

    void IRQHandler(void) {

    }
};

#endif