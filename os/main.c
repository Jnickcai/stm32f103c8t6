/* Standard includes. */
#include <stdio.h>
/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
/* Library includes. */
#include "stm32f10x_it.h"
/*user Library*/
#include "user_usart.h"
#include "user_led.h"

static void hardware_init(){
	USART1_Config(115200);
	user_led_init();
	printf("bsp setup!\n");
}

int main( void ){
	hardware_init();//��ʼ��Ӳ��ƽ̨
	freertos_app_add();//�������	
	vTaskStartScheduler();//��ʼ����
	return 0;
}
