#ifndef USER_RCC_CONTROL_H
#define USER_RCC_CONTROL_H

void show_sys_clock();
typedef enum{
	SYS_INIT_OK = (0x01<<0),
	DEBUG_SERIAL_IDLE = (0x01<<1),
}sys_base_event_t;//ö������

extern xTaskHandle RCC_SYS_CLOCK;//��ӡϵͳʱ���߳̾��
extern EventGroupHandle_t sys_base_event_group;//�����¼���
extern sys_base_event_t sys_init_ok;//ö��
extern sys_base_event_t debug_serial_idle;//ö��

#endif