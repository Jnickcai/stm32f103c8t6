#ifndef USEER_PWR_CONTROL_H
#define USEER_PWR_CONTROL_H
extern xTaskHandle PWR_MODE_SWITCH;//��Դģʽ�л�
extern xTaskHandle PWR_MODE_SEND_MSG;//��Դģʽ������Ϣ
typedef enum{
	 enter_standby_msg = 0,
}IntMsg;//������Ϣ
#define IntMsg_Q_MAX_LEN	10
extern QueueHandle_t IntMsg_Q;
void pwr_mode_switch();
void pwr_mode_send_msg();

//�ܽᣬע����Ϣ����һ��Ҫ����һ�£������ں˻�assert�����һ�õ����Ե����ݡ�\
ע���޷��������з�����֮�������
#endif