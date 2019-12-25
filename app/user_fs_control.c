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
#include "user_fs_control.h"
#include "ff.h"
#include "user_app_common.h"
extern const sys_base_event_t fs_mount_ok;
extern const sys_base_event_t flash_init_ok;
static EventBits_t r_event;//�¼�����ֵ
FATFS *fs,fatfs;//fs�������
#define work_buff_len 	512
void *work=NULL;
int clust_size = 0;
extern SemaphoreHandle_t serial_sem;
//fatfs�ļ�ϵͳʹ��:1)mount	\
2) mkfs	\
3)�ļ�����
//��������fs����ǰ�����������flash����\
Ϊ�ˣ����ǵȵ���flash��������¼����Ż�ִ��fs_init����ع����
void fs_init(){
		//�ȴ��¼�
		r_event = xEventGroupWaitBits(sys_base_event_group,//�¼�����
											flash_init_ok,//�ȴ����¼�
											pdFALSE,//true �ȵ�������¼�λ
											pdTRUE,//true�߼���ȴ�
											portMAX_DELAY);//�ȴ�ʱ��	
		if(r_event & flash_init_ok == flash_init_ok){//flash���������
			configASSERT((clust_size = xPortGetFreeHeapSize())>=work_buff_len);
			printf("      %d       ",clust_size);
			work = pvPortMalloc(work_buff_len);//fs ��ʽ�������е���ʱ������
			fs = &fatfs;
			r_event = f_mkfs("1:", 0, work, work_buff_len);
			configASSERT(!r_event);
			printf("      %d       ",r_event);
			r_event = f_mount(fs, "1:", 1);
			configASSERT(!r_event);
			r_event = f_getfree("1:",&clust_size,&fs);
			configASSERT(!r_event);
			while(xSemaphoreTake(serial_sem,10) != pdTRUE );
			printf("fs mount success,size:%d clust\n",clust_size);
			xSemaphoreGive(serial_sem);
		}
		//fs��ʼ����ɣ��¼���λ
		xEventGroupSetBits(sys_base_event_group,fs_mount_ok);
}
xTaskHandle FS_TEST_TASK_PCB;//��ӡϵͳFLASH�߳̾��

/***attention!!!!**/

/*****
freertos�������ջ��С�����Ծ�����Ҫ�������ջ���涨��ϴ���������������ջ���������
*********/
FIL fp;
char buffer[20];
int count=0;
void fs_test(){
  	fs_init();
	//�ȴ��¼�
		r_event = xEventGroupWaitBits(sys_base_event_group,//�¼�����
											fs_mount_ok,//�ȴ����¼�
											pdFALSE,//true �ȵ�������¼�λ
											pdTRUE,//true�߼���ȴ�
											portMAX_DELAY);//�ȴ�ʱ��	
		if(r_event & fs_mount_ok == fs_mount_ok){//fs�Ѿ�����
			r_event = f_open(&fp, "1:hello.txt", FA_CREATE_NEW | FA_WRITE);
			configASSERT(!r_event);
			f_write(&fp, "Hello, World!\r\n", 15, &count);
			configASSERT(count == 15);
			f_close(&fp);
			r_event = f_open(&fp, "1:hello.txt", FA_READ);
			configASSERT(!r_event);
			f_read(&fp,buffer,15,&count);
			f_close(&fp);
			while(xSemaphoreTake(serial_sem,10) != pdTRUE );
			printf("read text:%s\n",buffer);
			xSemaphoreGive(serial_sem);
			vPortFree(work);
			f_unmount("1:");
			while(1);
			//������ɣ�ɾ������  ɾ������������NULL  ������ɾ���Լ������Ϊʲô����
			//vTaskDelete(NULL);
		}
}