#include "stm32f10x_lib.h"
#include "delay.h"

/*******************************************************************************
* 
*           SysTick�ӳ�Ms����
* 
*******************************************************************************/
void DelayMs(u32 nms)
{
  	u32 CountNum;
	FlagStatus Status;		
	SysTick_CounterCmd(SysTick_Counter_Disable);	//ֹͣ����	
	//�ر�SysTick�ж�
	SysTick_ITConfig(DISABLE);
	//ϵͳĬ��SysTick��8��Ƶ��HCLK/8����ǰϵͳʱ��72M�Ļ� 72/8 = 9MHZ
  	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	CountNum=nms*9000;	//ʱ��Ϊ9MHz
	SysTick_SetReload(CountNum);	//װ�ؼ���ֵ
	SysTick_CounterCmd(SysTick_Counter_Clear);	//��ռ�����
	SysTick_CounterCmd(SysTick_Counter_Enable);	//��ʼ����
	do
	{
		Status=SysTick_GetFlagStatus(SysTick_FLAG_COUNT);
	}
	while(Status==RESET);	//�ȴ��������
	SysTick_CounterCmd(SysTick_Counter_Disable);	//ֹͣ����
	SysTick_CounterCmd(SysTick_Counter_Clear);	//��ռ�����
}


