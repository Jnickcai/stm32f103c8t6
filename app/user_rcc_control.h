#ifndef USER_RCC_CONTROL_H
#define USER_RCC_CONTROL_H

void show_sys_clock();

extern xTaskHandle RCC_SYS_CLOCK;//��ӡϵͳʱ���߳̾��
extern EventGroupHandle_t sys_base_event_group;//�����¼���


#endif