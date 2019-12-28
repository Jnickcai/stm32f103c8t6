#ifndef USER_PWR_H
#define USER_PWR_H
#include "user_common.h"
#include "stm32f10x.h"
#define PWR_MODE_MAX	2
typedef enum{
	//user_pwr_sleep = 0,
	user_pwr_standby = 0,
	user_pwr__stop,
}user_pwr_mode;
extern uchar user_pwr_mode_matrix[PWR_MODE_MAX];//��־stm32��ǰ״̬�ģ�ĳ����1���ڸ�ģʽ��
//ʹ�ܻ���ʹ��rtc�ͱ��ݼĴ����ķ���
USER_RETURN_VALUE user_set_rtc_backup(FunctionalState NewState);
//˯��ģʽ
//USER_RETURN_VALUE user_sleep_mode();
//����ģʽ
USER_RETURN_VALUE user_standby_mode();
//ͣ��ģʽ
USER_RETURN_VALUE user_stop_mode();
void reboot();
//��ȡ��ǰ�ĵ�Դ����״̬
USER_RETURN_VALUE user_get_current_status(uchar *matrix);

#endif