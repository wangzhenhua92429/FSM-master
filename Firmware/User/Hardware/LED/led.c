#include "stm32f10x_lib.h"
#include "led.h"

//DS0��DS1��ʼ�� DS0��PA8	DS1��PD2
void LED_Init(void)
{
  	GPIO_InitTypeDef GPIO_InitStructure;
	//������ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Pin = DS0 ;
	//Ϊ�����PWM������˹ܽŲ��ø�������ķ�ʽ
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
 
  	GPIO_InitStructure.GPIO_Pin = DS1 ;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  	GPIO_Init(GPIO_DS1, &GPIO_InitStructure);

	//�ر�DS0 DS1
	DS0_OFF();
	DS1_OFF();
}

/**************************************************************
*					���ض��˿����ȡ��
*  ���������GPIOX��GPIOA��D����GPIO_PIN��GPIO_Pin_0~15��
**************************************************************/
void GPIO_OutputBitToggle(GPIO_TypeDef* GPIOX,u16 GPIO_PIN)
{
	u8 ReadValu;
	ReadValu=GPIO_ReadOutputDataBit(GPIOX,GPIO_PIN);
	if(ReadValu==0x01)
		GPIO_ResetBits(GPIOX,GPIO_PIN);
	else if(ReadValu==0x00)
		GPIO_SetBits(GPIOX,GPIO_PIN);	
}

/**********************DS0��������****************************/
//DS0��
void DS0_ON(void)
{
	GPIO_ResetBits(GPIO_DS0,DS0);
}

//DS0�ر�
void DS0_OFF(void)
{
	GPIO_SetBits(GPIO_DS0,DS0);
}

//DS0ȡ��
void DS0_Convs(void)
{
	GPIO_OutputBitToggle(GPIO_DS0,DS0);	
}

/**********************DS1��������****************************/
//DS1��
void DS1_ON(void)
{
	GPIO_ResetBits(GPIO_DS1,DS1);
} 

//DS1�ر�
void DS1_OFF(void)
{
	GPIO_SetBits(GPIO_DS1,DS1);
}

//DS1ȡ��
void DS1_Convs(void)
{
	GPIO_OutputBitToggle(GPIO_DS1,DS1);	
}
