/* Standard includes. */
#include <stdio.h>
/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"
/* Library includes. */
#include "stm32f10x_it.h"
//bsp includes
#include "user_rcc_control.h"
#include "user_rcc.h"
#include "user_app_common.h"
//ʹ��freertos���¼���\
�ȴ���ϵͳ��������¼��󣬴�ӡ���ϵͳ��ǰ��ʱ��\
Ϊ�˱������߳����ô�ӡ���ڣ�ʹ�õȴ����ڿ��е��¼�

EventGroupHandle_t sys_base_event_group;
xTaskHandle RCC_SYS_CLOCK;//��ӡϵͳʱ���߳̾��
extern const sys_base_event_t sys_init_ok;//ö��

static unsigned int user_sys_clock = 0;
static EventBits_t r_event;//�¼�����ֵ
//xEventGroupClearBits() ����¼�λ
//
void show_sys_clock(){
		user_sys_clock = user_Get_Sys_Clock();
		//�ȴ��¼�
		r_event = xEventGroupWaitBits(sys_base_event_group,//�¼�����
											sys_init_ok,//�ȴ����¼�
											pdFALSE,//true �ȵ�������¼�λ
											pdTRUE,//true�߼���ȴ�
											portMAX_DELAY);//�ȴ�ʱ��
		
		if(r_event & sys_init_ok == sys_init_ok){							
			xprintf_s("System Clock:%uMHZ\n",user_sys_clock/1000000);
			//��־���ڿ����¼�
			//xEventGroupSetBits(sys_base_event_group,sys_init_ok);								
			//!!!!!attention!!!!!!
			/*
			ʹ��ʱӦ�������˶����¼��������ö����¼���
		  �����ԭ��δ֪���Ƚ�һ��̽��֮������ٲ���	*/
			//freertos�ĵȴ��¼�����������ԭ�Ӳ��������������task�ȴ�һ���¼�������¼������ˣ���ô���task\
				�����յ�֪ͨ���������ȵ��¼��Ĳ��������������ȴ���֤
			//ʵ���ˣ�freertos���¼�������������������ʵġ�
			vTaskDelete(NULL);//������ɣ�ɾ������
		}
}
