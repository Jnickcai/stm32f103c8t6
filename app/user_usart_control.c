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
#include "user_usart_control.h"
#include "user_rcc_control.h"
#include "user_app_common.h"

//ʹ��freertos�ľ�����ʱ����
xTaskHandle USART_HEART_BEAT;//���͸����ڵ�������Ϣ

/* �����ϴ�ʱ�䣬���ú�ϵͳ���Զ�������*/
static portTickType PreviousWakeTime;
static EventBits_t r_event;//�¼�����ֵ
void usart_heart_beat(){
	/* ������ʱʱ�䣬��ʱ��ת��tick������ */
	const portTickType TimeIncrement = pdMS_TO_TICKS(5000);
	/* ��ȡ��ǰϵͳʱ�� */
  PreviousWakeTime = xTaskGetTickCount();
	while(1){
			vTaskDelayUntil(&PreviousWakeTime,TimeIncrement); /* ��ʱ5000 tick��������5000ms */
			xprintf_s("running time:%lus\n",PreviousWakeTime/1000);
	}
}
