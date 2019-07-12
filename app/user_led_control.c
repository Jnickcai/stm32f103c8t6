/* Standard includes. */
#include <stdio.h>
/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
/* Library includes. */
#include "stm32f10x_it.h"
/*user Library*/
#include "user_led.h"
#include "user_led_control.h"

/* AppTaskCreate ��ջ */
//static StackType_t AppTaskCreate_Stack[128];
/* LED ��ջ */
//static StackType_t const OPEN_LED_Task_Stack[128];
//static StackType_t const CLOSE_LED_Task_Stack[128];

 /* AppTaskCreate TCB */
//static StaticTask_t AppTaskCreate_TCB;
/* AppTaskCreate TCB */

void open_led(){
	while(1){
	 user_led_on();
	 vTaskDelay(500); /* ��ʱ500 tick��������500ms */
	 user_led_off();
	 vTaskDelay(500); /* ��ʱ500 tick��������500ms */
	}
}


void close_led(){
	while(1){
	 //user_led_off();
	 vTaskDelay(500); /* ��ʱ500 tick��������500ms */
	}
}