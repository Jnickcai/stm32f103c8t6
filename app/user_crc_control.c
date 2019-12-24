/* Standard includes. */
#include <stdio.h>
/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
/* Library includes. */
#include "stm32f10x_it.h"
//bsp includes
#include "user_crc.h"
#include "user_crc_control.h"
//����ʹ��freertos���ź�������\
һ������ÿ��3s�ͷ�һ����ֵ�ź���\
���������ȡ��ֵ�ź����󣬼���crc��Ȼ���ӡ
//���ɶ���ʽ0x4C11DB7 \
X32 + X26 + X23 + X22 + X16 + X12 + X11 + X10 + X8 + X7 + X4 + X2 + X +1
xTaskHandle CRC_CAL;//CRC����
xTaskHandle CRC_POST_BINARY_SEM;
unsigned int crc_data[] = {0x0};//����crc������
SemaphoreHandle_t crc_sem = NULL;
unsigned int crc_ret = 0;
extern SemaphoreHandle_t serial_sem;
void crc_cal(){
	//�����Ķ�ֵ�ź�����ʼ״̬Ϊ�գ��������ͷ�
	crc_sem = xSemaphoreCreateBinary();
	while(1){
		//�ȳ��Ի�ȡ�ź���,���ȴ�2000tick
		if(xSemaphoreTake(crc_sem,2000) == pdTRUE ){
			crc_ret = user_cal_crc_32(crc_data[0]);
			//��ȡ���ڻ�����
			while(xSemaphoreTake(serial_sem,10) != pdTRUE );
			printf("����0x%x��CRCУ������:0x%x",crc_data[0],crc_ret);
			//post
			xSemaphoreGive(serial_sem);
			vTaskDelay(1500); /* ��ʱ1500 tick��������1500ms */
		}
	}
}

void crc_post_binary_sem(){
	while(1){
		vTaskDelay(portMAX_DELAY); /* ��ʱportMAX_DELAY tick */
		xSemaphoreGive(crc_sem);
	}
}

