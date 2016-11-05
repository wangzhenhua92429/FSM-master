#include "stm32f10x_lib.h"
#include "sys_config.h"

/*******************************************************************************
* 
*            RCC����
* 
*******************************************************************************/
void RCC_Configuration(void)
{   
	ErrorStatus HSEStartUpStatus;

	//��λRCC�ⲿ�豸�Ĵ�����Ĭ��ֵ
	RCC_DeInit();  
	//���ⲿ���پ���
  	RCC_HSEConfig(RCC_HSE_ON); 
	//�ȴ��ⲿ����ʱ��׼����
  	HSEStartUpStatus = RCC_WaitForHSEStartUp(); 
	//�ⲿ����ʱ���Ѿ�׼���
  	if(HSEStartUpStatus == SUCCESS)  
  	{
    	FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		FLASH_SetLatency(FLASH_Latency_2);
  
   		//����AHB(HCLK)ʱ��=SYSCLK
    	RCC_HCLKConfig(RCC_SYSCLK_Div1);
		//����APB2(PCLK2)��=AHBʱ��
    	RCC_PCLK2Config(RCC_HCLK_Div1); 
		//����APB1(PCLK1)��=AHB 1/2ʱ��
    	RCC_PCLK1Config(RCC_HCLK_Div2);  	
		//����ADCʱ��=PCLK2 1/4
    	RCC_ADCCLKConfig(RCC_PCLK2_Div4); 
		//����PLLʱ�� == �ⲿ���پ���ʱ��*9
    	RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9); 
		//����ADCʱ��= PCLK2/4
    	RCC_ADCCLKConfig(RCC_PCLK2_Div4);
		//ʹ��PLLʱ��
    	RCC_PLLCmd(ENABLE);  

   		//�ȴ�PLLʱ�Ӿ���
    	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
    
		//����ϵͳʱ�� = PLLʱ��
    	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK); 
		//���PLLʱ���Ƿ���Ϊϵͳʱ��
    	while(RCC_GetSYSCLKSource() != 0x08);
  	}
}

/*******************************************************************************
* 
*            NVIC����
* 
*******************************************************************************/
void NVIC_Configuration(void)
{
	#ifdef  VECT_TAB_RAM  
  		/* Set the Vector Table base location at 0x20000000 */ 
  		NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 
	#else  /* VECT_TAB_FLASH  */
  		/* Set the Vector Table base location at 0x08000000 */ 
  		NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
	#endif
}
