/* Standard includes. */
#include <stdio.h>
/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"

#include "user_io_control.h"
#include "xprintf.h"
#include "user_app_common.h"
xTaskHandle IO_TASK_PCB;//IO�߳̾��
SemaphoreHandle_t serial_sem = NULL;//���ڿ��л�����
extern const sys_base_event_t fs_file_operate_ok;
extern const sys_base_event_t io_operate_ok;
static EventBits_t r_event;//�¼�����ֵ
static char buff[20];
void io_out(){
	xprintf_s("io test success\n");
	xprintf_s("��������ɹ�\n");
}
void io_in(){
	xprintf_s("enter any continue...\n");
	xgets(buff,20);
}

void io_test(){
		//�ȴ��¼�
		r_event = xEventGroupWaitBits(sys_base_event_group,//�¼�����
											fs_file_operate_ok,//�ȴ����¼�
											pdFALSE,//true �ȵ�������¼�λ
											pdTRUE,//true�߼���ȴ�
											portMAX_DELAY);//�ȴ�ʱ��	
		if(r_event & fs_file_operate_ok == fs_file_operate_ok){//fs�Ѿ�����
			io_out();
			io_in();
			//�¼���λ
			xEventGroupSetBits(sys_base_event_group,io_operate_ok);
			vTaskDelete(NULL);
		}
}