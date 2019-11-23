#include "user_rcc.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x.h"
#include "stm32f10x_flash.h"
/*
rcc�Ǹ�λ��ʱ�ӿ��� 
stm32�ĸ�λ��Ϊϵͳ��λ �ϵ縴λ ��������λ
��λ������ʱ����

����ʱ��Դ
HSI����ʱ��
HSE����ʱ��
PLLʱ��

AHB 8��Ƶ���ṩ��Systick.Systickһ����Ϊos��ʱ��
RCC_CR�Ĵ���ָʾ�˵�ǰϵͳready��ʱ��Դ���Լ�����ʹ����һ��ʱ��Դ

PA8������Ϊʱ��Դ��������� MCO
*/
extern uint32_t SystemCoreClock;//ϵͳʱ��

uint32 user_Get_Sys_Clock(){
	return SystemCoreClock;
}

//����ϵͳʱ��
void RCC_Configuration(void)
{
	ErrorStatus HSEStartUpStatus;                    //�����ⲿ���پ�������״̬ö�ٱ���

	RCC_DeInit();                                    //��λRCC�ⲿ�豸�Ĵ�����Ĭ��ֵ
	RCC_HSEConfig(RCC_HSE_ON);                       //���ⲿ���پ���
	HSEStartUpStatus = RCC_WaitForHSEStartUp();      //�ȴ��ⲿ����ʱ��׼����
	if(HSEStartUpStatus == SUCCESS)                  //�ⲿ����ʱ���Ѿ�׼���
	{
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable); //����FLASHԤ�����幦�ܣ�����FLASH�Ķ�ȡ�����г����б�����÷�.λ�ã�RCC��ʼ���Ӻ������棬ʱ������֮��
		FLASH_SetLatency(FLASH_Latency_2);                    //flash��������ʱ
			
		RCC_HCLKConfig(RCC_SYSCLK_Div1);               //����AHB(HCLK)ʱ�ӵ���==SYSCLK
		RCC_PCLK2Config(RCC_HCLK_Div1);                //����APB2(PCLK2)��==AHBʱ��
		RCC_PCLK1Config(RCC_HCLK_Div2);                //����APB1(PCLK1)��==AHB1/2ʱ��
			 
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);  //����PLLʱ�� == �ⲿ���پ���ʱ�� * 9 = 72MHz
		RCC_PLLCmd(ENABLE);                                   //ʹ��PLLʱ��
   
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)    //�ȴ�PLLʱ�Ӿ���
		{
		}
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);            //����ϵͳʱ�� = PLLʱ��
		while(RCC_GetSYSCLKSource() != 0x08)                  //���PLLʱ���Ƿ���Ϊϵͳʱ��
		{
		}
	}
}
