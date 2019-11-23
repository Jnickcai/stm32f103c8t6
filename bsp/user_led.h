#ifndef USER_LED_H
#define USER_LED_H
#include "user_common.h"
//�����Сϵͳ�Ĳ���LED�ӵ���VCC��PC13������PC13����Ϊ����͵�ƽ���ɵ���LED
#define LED_PORT		(GPIOC)
#define LED_PIN			(GPIO_Pin_13)
#define LED_RCC_ENABLE()	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE)

void user_led_init();
void user_led_on();
void user_led_off();

#endif