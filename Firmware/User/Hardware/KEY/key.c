#include "stm32f10x_lib.h"
#include "key.h"

/******************************** �������� *********************************/
u8 Key0,Key1,WK_UP;	//������̼�����

//�������м���������IO��	KEY0=PA13��KEY1=PA15��WK_UP=PA0
void Key_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	//���� KEY0 PA13��KEY1 PA15	Ϊ��������ģʽ
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//��������ģʽ 0Ϊ����ֵ
  	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//����WK_UP PA0  Ϊ��������ģʽ
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	//��������ģʽ 1Ϊ����ֵ
  	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//�ر�JTAG����
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);			
}

u8 Key_Scan(void)
{
	Key0=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_13);	//��ȡKEY0״̬
	Key1=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15);	//��ȡKEY1״̬
	WK_UP=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0);	//��ȡWK_UP״̬	
	if(Key0==0||Key1==0||WK_UP==1)	//�а�������ʱ
	{
		DelayMs(10);//ȥ����
		
		//��ȡKEY0״̬
		Key0=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_13);
		if(Key0==0)
		{
			while(!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_13));//�ȴ������ɿ�
			return 1;
		}	
		//��ȡKEY1״̬
		Key1=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15);
		if(Key1==0)
		{
			while(!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15));//�ȴ������ɿ�
			return 2;
		}
		//��ȡWK_UP״̬
		WK_UP=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0);
		if(WK_UP==1)
		{
			while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0));//�ȴ������ɿ�
			return 3;
		}
	} 
	return 0;//�ް�������
}
