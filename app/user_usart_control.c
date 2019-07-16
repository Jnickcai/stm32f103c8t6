/* Standard includes. */
#include <stdio.h>
/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
/* Library includes. */
#include "stm32f10x_it.h"
//bsp includes
#include "user_usart_control.h"
//ʹ��freertos�ľ�����ʱ����
xTaskHandle USART_HEART_BEAT;//���͸����ڵ�������Ϣ
/* �����ϴ�ʱ�䣬���ú�ϵͳ���Զ�������*/
static portTickType PreviousWakeTime;
void usart_heart_beat(){
	/* ������ʱʱ�䣬��ʱ��ת��tick������ */
 const portTickType TimeIncrement = pdMS_TO_TICKS(5000);
	/* ��ȡ��ǰϵͳʱ�� */
 PreviousWakeTime = xTaskGetTickCount();
		while(1){
			printf("ϵͳ������%lu��\n",PreviousWakeTime/1000);
			vTaskDelayUntil(&PreviousWakeTime,TimeIncrement); /* ��ʱ5000 tick��������5000ms */
		}
}
