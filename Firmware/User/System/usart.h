#ifndef __USART_H
#define __USART_H
#include "stm32f10x_lib.h"

/******************************** �궨�� *********************************/ 
#define TxBufferSize   (countof(TxBuffer))
#define countof(a)   (sizeof(a) / sizeof(*(a)))

/******************************** ���� *********************************/
void USART1_Configuration(void);
void USART1_PutString(u8* BUF,u8 LEN);

#endif
