#ifndef USER_IO_CONTROL_H
#define USER_IO_CONTROL_H
extern SemaphoreHandle_t serial_sem;//������Դ������
extern xTaskHandle IO_TASK_PCB;//IO�߳̾��
void io_test();

#endif