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
static unsigned short flash_size_value=0;
extern SemaphoreHandle_t serial_sem;
extern const sys_base_event_t flash_init_ok;
void flash_read_write_test(){
	char *buff = pvPortMalloc(512);
	flash_driver.initialize(0);
	flash_driver.write(0,"flash hardware test success",0,1);
	flash_driver.read(0,buff,0,1);
	while(xSemaphoreTake(serial_sem,10) != pdTRUE );
	printf("%s",buff);
	xSemaphoreGive(serial_sem);
	//flash��������ɣ��¼���λ
	xEventGroupSetBits(sys_base_event_group,flash_init_ok);
	vPortFree(buff);
}
void flash_test(){
	  flash_size_value = flash_size();
		while(1){
				while(xSemaphoreTake(serial_sem,10) != pdTRUE );
				printf("FLASH:%uKB\n",flash_size_value);
				xSemaphoreGive(serial_sem);
			  //���flash����
				flash_read_write_test();
				//������ɣ�ɾ������
				vTaskDelete(FLASH_SIZE_TASK_PCB);
			}
}

