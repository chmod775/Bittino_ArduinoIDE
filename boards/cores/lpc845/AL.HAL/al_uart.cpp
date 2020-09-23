#include "al_uart.h"

AL_USART *USARTS_Instances[5] = { NULL, NULL, NULL, NULL, NULL };

void USART0_IRQHandler(void) { if (USARTS_Instances[0] != NULL) USARTS_Instances[0]->IRQHandler(); }
void USART1_IRQHandler(void) { if (USARTS_Instances[1] != NULL) USARTS_Instances[1]->IRQHandler(); }
void USART2_IRQHandler(void) { if (USARTS_Instances[2] != NULL) USARTS_Instances[2]->IRQHandler(); }
void USART3_IRQHandler(void) { if (USARTS_Instances[3] != NULL) USARTS_Instances[3]->IRQHandler(); }
void USART4_IRQHandler(void) { if (USARTS_Instances[4] != NULL) USARTS_Instances[4]->IRQHandler(); }

AL_USART::AL_USART(uint8_t ID, uint8_t txPin, uint8_t rxPin, uint8_t rtsPin, uint8_t ctsPin, uint8_t sclkPin)
{
  if (ID > FSL_FEATURE_SOC_USART_COUNT) return;

  CLOCK_Select(CLOCK_USARTS_ARRAY[ID][1]); // From_MainClk

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
  usart = (USART_Type *)(USARTS_ARRAY[ID]);
}

void AL_USART::Setup(uint32_t baudrate, uint32_t bufferSize, uint8_t *txBuffer, uint8_t *rxBuffer)
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
  USART_Init(this->usart, &config, _USART_CLK_FREQ);
}


int32_t AL_USART::Send(uint8_t *data, uint32_t nBytes) {
  return USART_WriteBlocking(USART0, data, nBytes == 0 ? bufferSize : nBytes);
}
int32_t AL_USART::SendString(char *str) {
  //strcpy((char *)this->txBuffer, str);
  return Send((uint8_t *)str, strlen(str) - 1);
}

int32_t AL_USART::Receive(uint32_t nBytes) {
  //return USART_WriteBlocking(usart, data, nBytes == 0 ? bufferSize : nBytes);
  
}

void AL_USART::IRQHandler(void) {

}
