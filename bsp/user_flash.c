#include "user_flash.h"
#include "stm32f10x_flash.h"
/*��Ϊ������ֲ��fatfs��Ҫdiskio��֧�֣�����������Ҫ��flash�����������棬ʵ����Щ
diskio�ĺ������������ܽ�һ����ֲfatfs*/
//ʵ�����¼����������rtc��ȡʱ�亯��������ʹ��fatfs��
DSTATUS flash_initialize(BYTE pdrv){
	
	return RES_OK;
}

DSTATUS flash_status(BYTE pdrv){
	
	return RES_OK;
}

DRESULT flash_read(BYTE pdrv, BYTE* buff, DWORD sector, UINT count){
	
	return RES_OK;
}

DRESULT flash_write(BYTE pdrv, const BYTE* buff, DWORD sector, UINT count){
	
	return RES_OK;
}

DRESULT flash_ioctl(BYTE pdrv, BYTE cmd, void* buff){
	
	return RES_OK;
}

const struct flash_driver flash_driver={
	flash_initialize,
	flash_status,
	flash_read,
	flash_write,
	flash_ioctl,
};