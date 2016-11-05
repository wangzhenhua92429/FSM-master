#ifndef __LED_H
#define __LED_H
#include "stm32f10x_lib.h"

#define GPIO_DS0 GPIOA
#define GPIO_DS1 GPIOD
#define DS0 GPIO_Pin_8
#define DS1 GPIO_Pin_2

void LED_Init(void);
//���ض��˿����ȡ��
void GPIO_OutputBitToggle(GPIO_TypeDef* GPIOX,u16 GPIO_PIN);

//DS0��DS1�Ĵ򿪡��رպ�ȡ��
void DS0_ON(void);
void DS0_OFF(void);
void DS0_Convs(void);
void DS1_ON(void);
void DS1_OFF(void);
void DS1_Convs(void);

#endif
