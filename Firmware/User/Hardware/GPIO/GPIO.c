#include "stm32f10x_lib.h"
#include "GPIO.h"

void GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = LED;  // ѡ�����н�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  //���ó�����ʽ���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //���ģʽ�� I/O����ٶ� 50M HZ
	GPIO_Init(GPIO_LED, &GPIO_InitStructure);  //��ʼ��IO��
	
	//�ر�JTAG����
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);			
}
