#include "stm32f10x_lib.h"
#include "usart.h"

/*******************************************************************************
* 				          USART1����ӦIO������ 
*******************************************************************************/
void USART1_Configuration(void)
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/**************��ӦIO������  ***************
	*		TXD~PA9				RXD~PA10
	*******************************************/
   	//����USART1_Tx(PA9)Ϊ�����������
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);

    //���� USART1_Rx(PA10)Ϊ��������
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

	/***************USART1����***************/
    //������ = 115200
    //���ݳ��� = 8λ
    // һ��ֹͣλ
    //��У��
    //��Ӳ��������
    //������պͷ���
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	//���ô���1
	USART_Init(USART1,&USART_InitStructure);

	//��������1
	USART_Cmd(USART1, ENABLE);
}

/*******************************************************************************
*            �ַ������ͺ��� 
*******************************************************************************/
void USART1_PutString(u8* BUF,u8 LEN)
{
	u8 i;
	for(i=0;i<LEN;i++)
	{
		USART_SendData(USART1,(u8)*BUF++);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	}
}
