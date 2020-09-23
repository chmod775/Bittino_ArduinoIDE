#include "al_uart.h"

AL_USART *USARTS_Instances[5] = { NULL, NULL, NULL, NULL, NULL };

void USART0_IRQHandler(void) { if (USARTS_Instances[0] != NULL) USARTS_Instances[0]->IRQHandler(); }
void USART1_IRQHandler(void) { if (USARTS_Instances[1] != NULL) USARTS_Instances[1]->IRQHandler(); }
void USART2_IRQHandler(void) { if (USARTS_Instances[2] != NULL) USARTS_Instances[2]->IRQHandler(); }
void USART3_IRQHandler(void) { if (USARTS_Instances[3] != NULL) USARTS_Instances[3]->IRQHandler(); }
void USART4_IRQHandler(void) { if (USARTS_Instances[4] != NULL) USARTS_Instances[4]->IRQHandler(); }
