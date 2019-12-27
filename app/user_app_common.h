#ifndef USER_APP_COMMON_H
#define USER_APP_COMMON_H
/*@brief
���APP��Ҫ�õ�ȫ��OS����
**********/

#include "user_common.h"
#include "user_led_control.h"
#include "user_usart_control.h"
#include "user_pwr_control.h"
#include "user_crc_control.h"
#include "user_rcc_control.h"
#include "user_flash_control.h"
#include "user_fs_control.h"
//#inlucde "user_io_control.h"
extern xTaskHandle IO_TASK_PCB;//IO�߳̾��
extern SemaphoreHandle_t serial_sem;//������Դ������
void io_test();
extern void xprintf_s(const char*	fmt,...);
typedef enum{
	SYS_INIT_OK = (0x01<<0),
	FLASH_INIT_OK = (0x01<<1),
	FS_MOUNT_OK = (0x01<<2),
	FS_FILE_OPERATE_OK = (0x01<<3),
}sys_base_event_t;//ö������


#endif