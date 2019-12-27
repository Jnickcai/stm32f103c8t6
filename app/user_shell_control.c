/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"
/*user Library*/
#include "user_shell_control.h"
#include "nr_micro_shell.h"
#include "xprintf.h"
#include "user_app_common.h"
xTaskHandle Shell_Test_Task_TCB;
extern const sys_base_event_t io_operate_ok;
extern void do_action();
static EventBits_t r_event;//�¼�����ֵ
//����ɨ�裬����������ַ��򴫵ݸ�shell
//����shell�����ǵ��ٵģ�����ÿ�η������ַ���������󣬿����Ե�Ƭ����ɨ��
void shell_test(){
			//�ȴ��¼�
		r_event = xEventGroupWaitBits(sys_base_event_group,//�¼�����
											io_operate_ok,//�ȴ����¼�
											pdFALSE,//true �ȵ�������¼�λ
											pdTRUE,//true�߼���ȴ�
											portMAX_DELAY);//�ȴ�ʱ��	
		if(r_event & io_operate_ok == io_operate_ok){//io�Ѿ�����
			shell_init();
			do_action();
			while(1){
				//�ַ����ݸ�shell
				shell(xgetc());
				//����Ƭ��
				vTaskDelay(50);//����50ms
    }
	}
}