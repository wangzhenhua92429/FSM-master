#include "stm32f10x_lib.h"
#include "pwd.h"



void PWD_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;//��ʱ����ʼ���ṹ
	TIM_ICInitTypeDef TIM_ICInitStructure;         //ͨ�������ʼ���ṹ
	GPIO_InitTypeDef GPIO_InitStructure;

	//�������뷽ʽ
	GPIO_InitStructure.GPIO_Pin = /* GPIO_Pin_0 | */GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6; 
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	//�����ʼ��
  	TIM_TimeBaseStructure.TIM_Period = 65535;     //����
  	TIM_TimeBaseStructure.TIM_Prescaler = 720;       //ʱ�ӷ�Ƶ
  	TIM_TimeBaseStructure.TIM_ClockDivision = 0;   //ʱ�ӷָ�
  	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//ģʽ
  	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);//������ʼ��
  	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	//��׽��ʼ��  
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;//�½���
 	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;//�ܽ���Ĵ�����Ӧ��ϵ
  	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;//��Ƶ��
  	TIM_ICInitStructure.TIM_ICFilter = 0x4;        //�˲����ã������������������϶������ȶ�0x0��0xF
 	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;//ͨ��ѡ��	
//  TIM_ICInit(TIM2, &TIM_ICInitStructure);        //��ʼ��	
  	TIM_ICInit(TIM4, &TIM_ICInitStructure);        //��ʼ��				 
 	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;//ͨ��ѡ��
  	TIM_ICInit(TIM2, &TIM_ICInitStructure);        //��ʼ��
 	TIM_ICInitStructure.TIM_Channel = TIM_Channel_3;//ͨ��ѡ��
  	TIM_ICInit(TIM2, &TIM_ICInitStructure);        //��ʼ��
 	TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;//ͨ��ѡ��
  	TIM_ICInit(TIM2, &TIM_ICInitStructure);        //��ʼ��
  
  	TIM_SelectInputTrigger(TIM2, TIM_TS_TI1FP1);   //ѡ��ʱ�Ӵ���Դ				   
  	TIM_SelectSlaveMode(TIM2, TIM_SlaveMode_Reset);//������ʽ					  
  	TIM_SelectMasterSlaveMode(TIM2, TIM_MasterSlaveMode_Enable); //������ʱ���ı�������
  	TIM_ITConfig(TIM2, /*TIM_IT_CC1|*/TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4, ENABLE);        //���ж�
 
	TIM_SelectInputTrigger(TIM4, TIM_TS_TI1F_ED);   //ѡ��ʱ�Ӵ���Դ				   
  	TIM_SelectSlaveMode(TIM4, TIM_SlaveMode_Reset);//������ʽ					  
  	TIM_SelectMasterSlaveMode(TIM4, TIM_MasterSlaveMode_Enable); //������ʱ���ı�������
  	TIM_ITConfig(TIM4, TIM_IT_CC1, ENABLE);        //���ж�

  	TIM_Cmd(TIM2, ENABLE);		  //����TIM2
	TIM_Cmd(TIM4, ENABLE);
}

