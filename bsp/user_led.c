#include "user_led.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

void user_led_init(){
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/* Enable the GPIO_LED Clock */
	LED_RCC_ENABLE();
	GPIO_DeInit(LED_PORT);	 //������GPIOC�Ĵ�������Ϊȱʡֵ		
	GPIO_InitStructure.GPIO_Pin = LED_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //�������
	GPIO_Init(LED_PORT, &GPIO_InitStructure);
	
	GPIO_SetBits(LED_PORT, LED_PIN);    //��PC13�����ø�,��ʼ״̬ΪϨ��ָʾ��
}
void user_led_on(){
	GPIO_ResetBits(LED_PORT , LED_PIN);   //��PC13�����õ�,����ָʾ��
}
void user_led_off(){
	GPIO_SetBits(LED_PORT , LED_PIN);    //��PC13�����ø�,Ϩ��ָʾ��
}