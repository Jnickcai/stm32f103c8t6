#ifndef USER_USART_CONTROL_H
#define USER_USART_CONTROL_H
extern xTaskHandle USART_HEART_BEAT;//���͸����ڵ�������Ϣ
extern SemaphoreHandle_t serial_sem;//������Դ������
void usart_heart_beat();

#endif