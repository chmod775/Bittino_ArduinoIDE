#include "al_uart.h"

AL_USART *USARTS_Instances[5] = { NULL, NULL, NULL, NULL, NULL };

#ifdef __cplusplus
 extern "C" {
#endif

void USART0_IRQHandler(void) { if (USARTS_Instances[0] != NULL) USARTS_Instances[0]->IRQHandler(); __DSB(); }
void USART1_IRQHandler(void) { if (USARTS_Instances[1] != NULL) USARTS_Instances[1]->IRQHandler(); __DSB(); }
void USART2_IRQHandler(void) { if (USARTS_Instances[2] != NULL) USARTS_Instances[2]->IRQHandler(); __DSB(); }
void USART3_IRQHandler(void) { if (USARTS_Instances[3] != NULL) USARTS_Instances[3]->IRQHandler(); __DSB(); }
void USART4_IRQHandler(void) { if (USARTS_Instances[4] != NULL) USARTS_Instances[4]->IRQHandler(); __DSB(); }

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

AL_USART::AL_USART(uint8_t ID, uint8_t txPin, uint8_t rxPin, uint8_t rtsPin, uint8_t ctsPin, uint8_t sclkPin)
{
  if (ID > FSL_FEATURE_SOC_USART_COUNT) return;
  this->ID = ID;

  CLOCK_Select(CLOCK_USARTS_ARRAY[ID][1]); // From_MainClk

  if (txPin != 0) {
    IOCON_PinMuxSet(IOCON, IOCON_INDEX_BP_ARRAY[txPin], 0);
    SWM_SetMovablePinSelect(SWM0, SWM_USARTS_ARRAY[ID][0], SWM_PORTPIN_BP_ARRAY[txPin]);
  }

  if (rxPin != 0) {
    IOCON_PinMuxSet(IOCON, IOCON_INDEX_BP_ARRAY[rxPin], 0 | IOCON_MODE_PULLDOWN);
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

void AL_USART::Setup(uint32_t baudrate, uint32_t bufferSize, uint8_t *rxBuffer)
{
  this->bufferSize = bufferSize;

  if (rxBuffer == NULL)
    rxBuffer = (uint8_t *)malloc(sizeof(uint8_t) * bufferSize);
  this->rxBuffer = rxBuffer;

  this->rxBuffer_counter = 0;

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

  /* Enabled USART RxReady interrupt */
  USART_EnableInterrupts(this->usart, kUSART_RxReadyInterruptEnable);
  EnableIRQ(IRQ_USARTS_ARRAY[this->ID]);
}


int32_t AL_USART::Send(uint8_t *data, uint32_t nBytes)
{
  return USART_WriteBlocking(this->usart, data, nBytes == 0 ? bufferSize : nBytes);
}
int32_t AL_USART::SendString(char *str)
{
  return Send((uint8_t *)str, strlen(str));
}

uint8_t *AL_USART::Receive(uint32_t nBytes)
{
  size_t len = nBytes;
  if ((len == 0) || (len > this->bufferSize))
    len = this->bufferSize;
  USART_ReadBlocking(this->usart, this->rxBuffer, len);
  return this->rxBuffer;
}

uint8_t *AL_USART::ReceiveUntil(uint8_t endByte, uint32_t *rxSize, uint8_t stringSafe)
{
  this->statusFlags = AL_USART_STATUS_NONE;
  this->endData = endByte;
  this->rxBuffer_counter = 0;

  // Ugly trick, but working and memory lite. Avoid using entire buffer if string (one more byte necessary for terminator)
  if (stringSafe)
    this->bufferSize--;

  // Wait completition
  while (this->statusFlags == AL_USART_STATUS_NONE)
    asm("nop");

  if (rxSize != NULL)
    *rxSize = this->rxBuffer_counter;

  if (stringSafe)
    this->bufferSize++;

  return this->rxBuffer;
}

char *AL_USART::ReceiveString()
{
  return (char *)ReceiveUntil(0x00);
}
char *AL_USART::ReceiveStringUntil(char endChar)
{
  uint32_t len;
  char *str = (char *)ReceiveUntil((uint8_t)endChar, &len);
  str[len] = 0x00; // Terminate string
  return str;
}

void AL_USART::IRQHandler(void)
{
  if (kUSART_RxReady & USART_GetStatusFlags(this->usart))
  {
    uint8_t data = USART_ReadByte(this->usart);

    if (this->statusFlags == AL_USART_STATUS_NONE)
    {
      this->rxBuffer[this->rxBuffer_counter] = data;
      this->rxBuffer_counter++;

      if (data == this->endData)
        this->statusFlags = AL_USART_STATUS_ENDBYTE_RECEIVED;

      if (this->rxBuffer_counter >= this->bufferSize)
        this->statusFlags = AL_USART_STATUS_BUFFER_FULL;
    }
  }
}
