#include "user_rcc.h"
#include "stm32f10x_rcc.h"
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
