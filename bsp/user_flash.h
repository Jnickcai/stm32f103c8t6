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

/*����ֲfatfs��ʱ������һ�����⣬fatfs֧�ֵ���Сsector��128������ӵ�е�sector������
��ˣ���ʹ��fatfsʱ������ʹ������߼�����sector����1����
�����ʹ��fatfs����ʹ������sector��
��˶�������ĺ꣬����sector������
*/
#define USE_FAT_FS 1
#if USE_FAT_FS==0
#define FLASH_START_ADDR  0x8000000 //����flash����ʼ��ַ
#define FLASH_SECTOR_SIZE 1024 //����flash��������С
#define USER_START_SECTOR	64 //�����û���������ʼ����,�ʹ��볤���й�
#define FLASH_SECTOR_MAX_NUMBER (128) //������������
#define FLASH_SECTOR_NUMBER  (FLASH_SECTOR_MAX_NUMBER-USER_START_SECTOR) //�û�������������
#define FLASH_BLOCK_SIZE 2 //����1��block=2��sector

#elif USE_FAT_FS==1
#define FLASH_START_ADDR  0x8000000 //����flash����ʼ��ַ
#define FLASH_SECTOR_SIZE 512 //����flash��������С
#define USER_START_SECTOR	64 //�����û���������ʼ����,�ʹ��볤���й�
#define FLASH_SECTOR_MAX_NUMBER (256) //������������ -2�Ƕ������
#define FLASH_SECTOR_NUMBER  (FLASH_SECTOR_MAX_NUMBER-USER_START_SECTOR) //�û�������������
#define FLASH_BLOCK_SIZE 2 //����1��block=2��sector
#endif
/* Results of Disk Functions */
typedef enum {
	RES_OK = 0,		/* 0: Successful */
	RES_ERROR,		/* 1: R/W Error */
	RES_WRPRT,		/* 2: Write Protected */
	RES_NOTRDY,		/* 3: Not Ready */
	RES_PARERR		/* 4: Invalid Parameter */
} DRESULT;
typedef BYTE DSTATUS;

/* Disk Status Bits (DSTATUS) */

#define STA_NOINIT		0x01	/* Drive not initialized */
#define STA_NODISK		0x02	/* No medium in the drive */
#define STA_PROTECT		0x04	/* Write protected */

//repeat from diskio.h
/* Generic command (Used by FatFs) */
#define CTRL_SYNC			0	/* Complete pending write process (needed at _FS_READONLY == 0) */
#define GET_SECTOR_COUNT	1	/* Get media size (needed at _USE_MKFS == 1) */
#define GET_SECTOR_SIZE		2	/* Get sector size (needed at _MAX_SS != _MIN_SS) */
#define GET_BLOCK_SIZE		3	/* Get erase block size (needed at _USE_MKFS == 1) */
#define CTRL_TRIM			4	/* Inform device that the data on the block of sectors is no longer used (needed at _USE_TRIM == 1) */

struct flash_driver{
	DSTATUS (*initialize)(BYTE pdrv);
	DSTATUS (*status)(BYTE pdrv);
	DRESULT (*read)(BYTE pdrv, BYTE* buff, DWORD sector, UINT count);
	DRESULT (*write)(BYTE pdrv, const BYTE* buff, DWORD sector, UINT count);
	DRESULT (*ioctl)(BYTE pdrv, BYTE cmd, void* buff);
};
/*@brief:
����flash��С����λ��KB
*/
unsigned short flash_size(void);
extern const struct flash_driver flash_driver;
#endif