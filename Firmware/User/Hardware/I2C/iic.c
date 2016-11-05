#include "stm32f10x_lib.h"
#include "iic.h"
/**********************************************************************/
/*IIC����		         				                              */
/*																	  */
/**********************************************************************/
void I2C_Config()
{
	GPIO_InitTypeDef GPIO_InitStructure;

	 I2C_InitTypeDef I2C_InitStructure;
	 
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
	/* Configure IO connected to IIC*********************/
	 GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10 | GPIO_Pin_11;
  	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
 	 GPIO_Init(GPIOB, &GPIO_InitStructure);

	 I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
 	 I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
 	 I2C_InitStructure.I2C_OwnAddress1 = I2C2_SLAVE_ADDRESS7;
 	 I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
 	 I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
 	 I2C_InitStructure.I2C_ClockSpeed = 200000;
	 
	 I2C_Cmd(I2C2, ENABLE);   

	 I2C_Init(I2C2, &I2C_InitStructure);
}
/**********************************************************************/
/*IICдһ���ֽ�	         				                              */
/*																	  */
/**********************************************************************/
void I2C_WriteByte(unsigned char id,unsigned char write_address,unsigned char byte)
{
	I2C_GenerateSTART(I2C2,ENABLE);
	//������ʼ����
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));
	//�ȴ�ACK
	I2C_Send7bitAddress(I2C2,id,I2C_Direction_Transmitter);
	//���豸�����豸��ַ
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	//�ȴ�ACK
	I2C_SendData(I2C2, write_address);
	//�Ĵ�����ַ
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	//�ȴ�ACK
	I2C_SendData(I2C2, byte);
	//��������
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	//�������
	I2C_GenerateSTOP(I2C2, ENABLE);
	//���������ź�
}
/**********************************************************************/
/*IIC������	         				                              	  */
/*																	  */
/**********************************************************************/
unsigned char I2C_ReadByte(unsigned char  id, unsigned char read_address)
{  
	unsigned char temp; 	

	while(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY));
  	//�ȴ�I2C
  	I2C_GenerateSTART(I2C2, ENABLE);
  	//������ʼ�ź�
  	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));
    //EV5
  	I2C_Send7bitAddress(I2C2, id, I2C_Direction_Transmitter);
	//���͵�ַ
  	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
  	//EV6
  	I2C_Cmd(I2C2, ENABLE);
 	//�������ÿ������EV6
  	I2C_SendData(I2C2, read_address);  
	//���Ͷ��õ�ַ
  	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
  	//EV8 
  	I2C_GenerateSTART(I2C2, ENABLE);
	//���·���
  	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));
  	//EV5
  	I2C_Send7bitAddress(I2C2, id, I2C_Direction_Receiver);
  	//���Ͷ���ַ
  	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
  	//EV6  
    I2C_AcknowledgeConfig(I2C2, DISABLE);
    I2C_GenerateSTOP(I2C2, ENABLE);
	//�ر�Ӧ���ֹͣ��������
    while(!(I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED)));
	      
    temp = I2C_ReceiveData(I2C2);
   
  	I2C_AcknowledgeConfig(I2C2, ENABLE);

	return temp;
}

