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
#include "user_pwr.h"
#include "user_pwr_control.h"
xTaskHandle PWR_MODE_SWITCH;//��Դģʽ�л�
xTaskHandle PWR_MODE_SEND_MSG;//��Դģʽ������Ϣ
//����ʹ����Ϣ���У���ȡ��Ϣ�Ž������ģʽ
QueueHandle_t IntMsg_Q = NULL;
extern SemaphoreHandle_t serial_sem;
void pwr_mode_switch(){
	  int rcv_Q = -1;
	  IntMsg_Q = xQueueCreate(IntMsg_Q_MAX_LEN,sizeof( int ));
		while(1){
			xQueueReceive(IntMsg_Q,&rcv_Q,portMAX_DELAY);//���޵ȴ�
			//��ȡ���ڻ�����
			while(xSemaphoreTake(serial_sem,10) != pdTRUE );
			printf("�յ�%d",rcv_Q);
			//post
			xSemaphoreGive(serial_sem);
			if(rcv_Q == enter_standby_msg){
				while(xSemaphoreTake(serial_sem,10) != pdTRUE );
				printf("�����������ģʽ...\n");
				//post
				xSemaphoreGive(serial_sem);
				user_standby_mode();
		}
	}
}

void pwr_mode_send_msg(){
	  int msg = -1;
		while(1){
			  vTaskDelay(portMAX_DELAY);//��ʱportMAX_DELAY��ʱ����������ʱ
			  while(xSemaphoreTake(serial_sem,10) != pdTRUE );
				printf("���ʹ�����Ϣ...\n");
				xSemaphoreGive(serial_sem);
				msg = enter_standby_msg;
				if(xQueueSend(IntMsg_Q,(void *)&msg,0) == pdPASS)
					vTaskDelete(NULL);//������ɣ�ɾ���Լ�
				else{
					while(xSemaphoreTake(serial_sem,10) != pdTRUE );
					printf("��Ϣ����ʧ��...\n");
					xSemaphoreGive(serial_sem);
				}
		}
}


