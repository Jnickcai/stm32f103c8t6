#ifndef USER_FLASH_H
#define USER_FLASH_H

#include "user_common.h"
/*@brief
stm32�ڲ���rom��2����
flash 64K~256K����
��Ϣ��(ϵͳ�洢��2K Byte �û�ѡ���ֽ� 16 Byte

�ڲ�ram��1������sram��

��ϵ��boot��3�ַ�ʽ��
ϵͳ�洢��boot
flash�洢��boot
sram�洢��boot
һ�㶼�ǰѳ������ص�flash���档
*/

/*@brief
��������ֲfs
128K��flashһ����128���飬ÿ������1K�����������sector(����)
��ȥ���ص�flash�еĴ����ֻ�����ݣ�ʣ�µ�flash��С���������ǿ��Բ����ķ�Χ��
*/

/* Results of Disk Functions */
typedef enum {
	RES_OK = 0,		/* 0: Successful */
	RES_ERROR,		/* 1: R/W Error */
	RES_WRPRT,		/* 2: Write Protected */
	RES_NOTRDY,		/* 3: Not Ready */
	RES_PARERR		/* 4: Invalid Parameter */
} DRESULT;
typedef BYTE DSTATUS;
struct flash_driver{
	DSTATUS (*initialize)(BYTE pdrv);
	DSTATUS (*status)(BYTE pdrv);
	DRESULT (*read)(BYTE pdrv, BYTE* buff, DWORD sector, UINT count);
	DRESULT (*write)(BYTE pdrv, const BYTE* buff, DWORD sector, UINT count);
	DRESULT (*ioctl)(BYTE pdrv, BYTE cmd, void* buff);
};

extern const struct flash_driver flash_driver;
#endif