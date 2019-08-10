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
//ʹ��freertos���¼���\
�ȴ���ϵͳ��������¼��󣬴�ӡ���ϵͳ��ǰ��ʱ��\
Ϊ�˱������߳����ô�ӡ���ڣ�ʹ�õȴ����ڿ��е��¼�

EventGroupHandle_t sys_base_event_group;
xTaskHandle RCC_SYS_CLOCK;//��ӡϵͳʱ���߳̾��

sys_base_event_t sys_init_ok = SYS_INIT_OK;//ö��
sys_base_event_t debug_serial_idle = DEBUG_SERIAL_IDLE;//ö��

static unsigned int user_sys_clock = 0;
static EventBits_t r_event;//�¼�����ֵ
//xEventGroupClearBits() ����¼�λ
//
void show_sys_clock(){
	while(1){
		user_sys_clock = user_Get_Sys_Clock();
		//�ȴ��¼�
		r_event = xEventGroupWaitBits(sys_base_event_group,//�¼�����
											sys_init_ok|debug_serial_idle,//�ȴ����¼�
											pdTRUE,//true �ȵ�������¼�λ
											pdTRUE,//true�߼���ȴ�
											portMAX_DELAY);//�ȴ�ʱ��
		
		if(r_event & (sys_init_ok|debug_serial_idle) 
										== (sys_init_ok|debug_serial_idle)){
											
			printf("��ǰϵͳʱ��:%uMHZ",user_sys_clock/1000000);
			//��־���ڿ����¼�
			xEventGroupSetBits(sys_base_event_group,sys_init_ok|debug_serial_idle);
											
			//!!!!!attention!!!!!!
			/*�������䣬��Ϊȱ����sys_init_ok| �����¼����幤����������
			ʹ��ʱӦ�������˶����¼��������ö����¼���
		  �����ԭ��δ֪���Ƚ�һ��̽��֮������ٲ���	*/

			vTaskDelete(RCC_SYS_CLOCK);//������ɣ�ɾ������
		}
	}
}
