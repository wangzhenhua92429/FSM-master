#include "stm32f10x_lib.h"
#include "exti_key.h"
#include "key.h"
#include "led.h"

/*****************�ⲿ�ж�0������*********************/
void EXTI0_IRQHandler(void)
{
	DelayMs(10);
	//��ȡWK_UP״̬
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==1)
	{
		//DS0��DS1��ȡ��
		DS0_Convs();
		DS1_Convs();
	}
	//�������жϹ���λ
	EXTI_ClearITPendingBit(EXTI_Line0);
}


/*****************�ⲿ�ж�10��15������*********************/
void EXTI15_10_IRQHandler(void)
{
	DelayMs(10);
	//Key0���� DS0ȡ��
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_13)==0)
		DS0_Convs();
	//Key1���� DS1ȡ��
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)==0)
		DS1_Convs();
	
	//�������жϹ���λ
	EXTI_ClearITPendingBit(EXTI_Line13);
	EXTI_ClearITPendingBit(EXTI_Line15);	
}

/**********************�����ⲿ�жϳ�ʼ������**********************/
void EXTIKey_Init(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/********************���ü�����Ӧ��IO��***********************/
	//���� KEY0 PA13��KEY1 PA15	Ϊ��������ģʽ
	//����WK_UP PA0  Ϊ��������ģʽ
	Key_Init();

	/***************************�����ⲿ�ж����ȼ�*******************************
	*					�������ȼ���KEY0=KEY1>WK_UP
	****************************************************************************/
	//�����ж����ȼ���2
  	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  
  
  	//����EXTI0���ȼ�  WK_UP
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQChannel; //�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =  2;  //ǿռ���ȼ�
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;//�����ȼ�
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  //ͨ���ж�ʹ��
  	NVIC_Init(&NVIC_InitStructure);//��ʼ���ж�
	//����EXTI13 EXTI15���ȼ�	   KEY0  KEY1
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQChannel; //�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =  2;  //ǿռ���ȼ�
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//�����ȼ�
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  //ͨ���ж�ʹ��
  	NVIC_Init(&NVIC_InitStructure);//��ʼ���ж�

	/*********************�����ⲿ�ж�****************************
	*  EXTI0	PA0		WK_UP 	�����ش���
	*  EXTI13 	PA13 	KEY0 	�½��ش���
	*  EXTI13	PA15	KEY1	�½��ش���
	*************************************************************/
	//�����ⲿ�ж��� ��EXTI0 ���ӵ�PA0	WK_UP
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
	//�����ⲿ�ж��� ��EXTI13 ���ӵ�PA13 KEY0
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource13);
	//�����ⲿ�ж��� ��EXTI15 ���ӵ�PA15 KEY1
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource15);
	
	//����EXTI0 �����ش����ж�
	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	//����EXTI13��EXTI15 �½��ش����ж�
	EXTI_InitStructure.EXTI_Line=EXTI_Line13|EXTI_Line15;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);	
}
