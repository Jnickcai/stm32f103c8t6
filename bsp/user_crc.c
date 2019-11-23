#include "user_crc.h"
#include "stm32f10x_crc.h"
#include "stm32f10x_rcc.h"
//crc��Ҫ���������ݼĴ�����һ�����ƼĴ���������һ�����ݼĴ�����Ϊ���飬�ֱ���\
ֻ����ֻд\
crc���ɶ���ʽ�ǹ̶���
//crc�Ľ�����Ե�����ֻҪ����գ���ͣ�ĵ������룬��������ٷ���crc�����\
������ľ����������ݵĽ��\
stm32��CRCУ��������ļ�������һ�£��Ǵ�С�˵�����\
�Լ�������û�����
void user_crc_init(){
	//��ʱ��
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC,ENABLE);
	//���CRC�Ĵ���
	CRC_ResetDR();
}
uint32 user_cal_crc_32(uint32 data){
	uint32 ret;
	ret = CRC_CalcCRC(data);
	//���CRC�Ĵ���
	CRC_ResetDR();
	//���ؽ��
	return ret;
}
//���ݿ�ָ�룬���ݿ鳤��
//����CRCУ����
uint32 user_cal_crc(uint32 *ptr,uint32 len){
	uint32 ret;
	ret = CRC_CalcBlockCRC(ptr,len);
	//���CRC�Ĵ���
	CRC_ResetDR();
	//���ؽ��
	return ret;
}