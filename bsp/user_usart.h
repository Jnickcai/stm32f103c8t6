#ifndef USERUSARTH
#define USERUSARTH
#ifdef __cplusplus
extern "C" {
#endif
#include "user_common.h"
#include "stm32f10x_gpio.h"
void USART1_Config(int boaud_rate);
void USART2_Config(int boaud_rate);
void USART3_Config(int boaud_rate);
void USART4_Config(int boaud_rate);
void USART5_Config(int boaud_rate);
void user_Usart_SendByte(USART_TypeDef * Usart_Num,uchar SendData);
//����д����ֽ���,�����ַ�����������û��������
int user_Usart_Send(USART_TypeDef * Usart_Num,const uchar *str);
#ifdef __cplusplus
}
#endif
#endif
