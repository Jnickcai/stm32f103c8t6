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
Ϊ�ˣ����ǵȵ���flash��������¼����Ż�ִ��fs_init����ع�����
void fs_init(){
		//�ȴ��¼�
		r_event = xEventGroupWaitBits(sys_base_event_group,//�¼�����
											flash_init_ok,//�ȴ����¼�
											pdFALSE,//true �ȵ�������¼�λ
											pdTRUE,//true�߼���ȴ�
											portMAX_DELAY);//�ȴ�ʱ��	
		if(r_event & flash_init_ok == flash_init_ok){//flash���������
			work = pvPortMalloc(work_buff_len);//fs ��ʽ�������е���ʱ������
			fs = &fatfs;
			r_event = f_mkfs("0:",FM_FAT,1024,work,work_buff_len);
			//r_event = f_mkfs("",FM_SFD,0,work,work_buff_len);
			configASSERT(!r_event);
			r_event = f_mount(fs,"0:",1);
			configASSERT(!r_event);
			r_event = f_getfree("0:",&clust_size,&fs);
			configASSERT(!r_event);
			while(xSemaphoreTake(serial_sem,10) != pdTRUE );
			printf("fs mount success,size:%d clust\n",clust_size);
			xSemaphoreGive(serial_sem);
		}
		//fs��ʼ����ɣ��¼���λ
		xEventGroupSetBits(sys_base_event_group,fs_mount_ok);
}
xTaskHandle FS_TEST_TASK_PCB;//��ӡϵͳFLASH�߳̾��
void fs_test(){
	  FIL fp;
	  char buffer[20];
	  int read_count=0;
  	fs_init();
	//�ȴ��¼�
		r_event = xEventGroupWaitBits(sys_base_event_group,//�¼�����
											fs_mount_ok,//�ȴ����¼�
											pdFALSE,//true �ȵ�������¼�λ
											pdTRUE,//true�߼���ȴ�
											portMAX_DELAY);//�ȴ�ʱ��	
		if(r_event & fs_mount_ok == fs_mount_ok){//fs�Ѿ�����
			//r_event = f_open(&fp,"0:test.txt",FA_CREATE_NEW|FA_WRITE);
			//configASSERT(!r_event);
			//printf("    %d   ",r_event);
			//f_puts("hello world",&fp);
			//f_sync(&fp);
			//f_lseek(&fp,0);
			//f_read(&fp,buffer,20,&read_count);
			//f_close(&fp);
			while(xSemaphoreTake(serial_sem,10) != pdTRUE );
			printf("read text:%s\n",buffer);
			xSemaphoreGive(serial_sem);
			//������ɣ�ɾ������
			vTaskDelete(FS_TEST_TASK_PCB);
		}
}