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
#include "user_flash_control.h"
#include "user_flash.h"
#include "user_app_common.h"
extern EventGroupHandle_t sys_base_event_group;//�����ⲿ���¼���
xTaskHandle FLASH_SIZE_TASK_PCB;//��ӡϵͳFLASH�߳̾��
static EventBits_t r_event;//�¼�����ֵ
static unsigned short flash_size_value=0;

void flash_read_write_test(){
	char *buff = pvPortMalloc(1024);
	flash_driver.initialize(0);
	flash_driver.write(0,"test",0,1);
	flash_driver.read(0,buff,0,1);
	printf("%s",buff);
	vPortFree(buff);
}
void flash_test(){
	  flash_size_value = flash_size();
		while(1){
			//�ȴ����ڿ����¼�
			r_event = xEventGroupWaitBits(sys_base_event_group,//�¼�����
											debug_serial_idle,//�ȴ����¼�
											pdTRUE,//true �ȵ�������¼�λ
											pdTRUE,//true�߼���ȴ�
											portMAX_DELAY);//�ȴ�ʱ��
			if((r_event &debug_serial_idle)==debug_serial_idle){//���ȵ����¼����Ƿ�Ϊ��Ҫ���¼�
				printf("FLASH:%uKB\n",flash_size_value);
				//��־���ڿ����¼�(�ͷ��¼�)
				xEventGroupSetBits(sys_base_event_group,debug_serial_idle);
				flash_read_write_test();
				//������ɣ�ɾ������
				vTaskDelete(FLASH_SIZE_TASK_PCB);
			}
		}
}

