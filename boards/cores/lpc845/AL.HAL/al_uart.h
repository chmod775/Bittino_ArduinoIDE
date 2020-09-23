#ifndef _AL_UART_H_
#define _AL_UART_H_

#include "../Arduino.h"

#define _USART_CLK_SRC  kCLOCK_MainClk
#define _USART_CLK_FREQ CLOCK_GetFreq(_USART_CLK_SRC)

class AL_USART;

extern AL_USART *USARTS_Instances[5];

class AL_USART
{
  public:
    const uint8_t PIN_NC = 0;

    uint8_t ID;

    USART_Type *usart = USART0;

    uint32_t bufferSize;
    uint8_t *txBuffer;
    uint8_t *rxBuffer;

    AL_USART(void) : AL_USART(0, 11, 12) {};
    AL_USART(uint8_t ID, uint8_t txPin, uint8_t rxPin, uint8_t rtsPin = 0, uint8_t ctsPin = 0, uint8_t sclkPin = 0);

    void Setup(uint32_t baudrate, uint32_t bufferSize = 32, uint8_t *txBuffer = NULL, uint8_t *rxBuffer = NULL);


    int32_t Send(uint8_t *data, uint32_t nBytes = 0);
    int32_t SendString(char *str);

    int32_t Receive(uint32_t nBytes = 0);

    void IRQHandler(void);
};

#endif