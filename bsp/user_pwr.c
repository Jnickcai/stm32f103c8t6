#include "user_pwr.h"
#include "stm32f10x_pwr.h"
#include "stm32f10x_rcc.h"
/*stm32����������Ŀɱ�̵�Դ������Ҫ��˯�ߡ�������ͣ������ʡ��ģʽ
����DEBGUGģʽ������ϵͳʱ�ӵ�
���⻹��ADC���������ϸ������
*/

uchar user_pwr_mode_matrix[PWR_MODE_MAX];//��־stm32��ǰ״̬�ģ�ĳ����1���ڸ�ģʽ��

USER_RETURN_VALUE user_set_rtc_backup(FunctionalState NewState){
	 PWR_BackupAccessCmd(NewState);
	 return 0;
}

//�˳�����ģʽ�ķ���
//PA0������
//rtc�����ж�������
//�������Ź���λ
//��λ����

//����ģʽ,PA0�������˳�����ģʽ
USER_RETURN_VALUE user_standby_mode(){
	GPIO_InitTypeDef  GPIO_InitStructure;  		  
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);//GPIOA����ʱ�Ӵ�
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0;	 //PA.0
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPD;//��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);	//��ʼ��IO
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);//ʹ��PWRʱ��
  PWR_WakeUpPinCmd(ENABLE);//˯�߻�������ʹ��
	PWR_EnterSTANDBYMode();
}
//ͣ��ģʽ
USER_RETURN_VALUE user_stop_mode(){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);//ʹ��PWRʱ��
	PWR_EnterSTOPMode(PWR_Regulator_LowPower,PWR_STOPEntry_WFI);//��һ�ж϶��ɻ��ѣ��͹���ģʽ
}
void reboot(){
		__set_FAULTMASK(1); // �ر�һ���ж�
    NVIC_SystemReset(); // ��λ
}
//��ȡ��ǰ�ĵ�Դ����״̬
//��״̬����ĵ�ǰ״̬��λ
USER_RETURN_VALUE user_get_current_status(uchar *matrix){
	 return 0;
}