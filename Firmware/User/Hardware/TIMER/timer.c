#include "stm32f10x_lib.h"
#include "timer.h"

//��ʱ��3���жϷ������
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET)
	{
		//DS1״̬��ת
		DS0_Convs();
	}
	//���TIM3 �ĸ��±�־λ
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);	
}

/************************��ʱ��3���ú���**********************************
*						1s���ʱ����㹫ʽ��
*	(1+TIM_Prescaler )/72M)*(1+TIM_Period )=((1+7199)/72M)*(1+9999)=1�� 
*				��ʱ��3Ĭ��Ϊ�ⲿʱ�� APB1��2=72MHz
*							���ϼ���ģʽ
*************************************************************************/
void Timer_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	//��TIM3ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
		
	/*******************����TIM3���ж����ȼ�**********************/
	//2λ��ռ���ȼ�  2λ�����ȼ�
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	// Enable the TIM3 gloabal Interrupt
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	/*******************����TIM3**********************/
	TIM_TimeBaseStructure.TIM_Period = 9999; 
	TIM_TimeBaseStructure.TIM_Prescaler = 7199;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	////���жϣ�����һ�����жϺ����������ж�
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);
	//ʹ��ARR�Ĵ��� ����
	TIM_ARRPreloadConfig(TIM3, ENABLE); 
	//ʹ�ܸ���ʱ���ж�
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);   
	//ʹ��TIM3��ʱ��
	TIM_Cmd(TIM3, ENABLE);

}




