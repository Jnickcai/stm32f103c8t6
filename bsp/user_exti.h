#ifndef USER_EXIT_H
#define USER_EXIT_H

#ifdef __cplusplus
extern "C" {
#endif
#include "user_common.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_exti.h"
#include "stm32f10x.h"
	
#define MAX_EXTI_NUM	16
typedef struct{
	int (*init)(GPIO_TypeDef* GPIOx,uint Pin,
uint GPIO_PortSourceGPIOx,uint GPIO_PinSourcex,
uint EXTI_Linex,EXTITrigger_TypeDef Trigger,
uint EXTIx_IRQn,void(*callback)());//�жϷ�����Ĵ���,���û�ʵ�ֲ���ֵ
	void(*start)(uint EXTI_Line);
	void(*stop)(uint EXTI_Line);
	int(*deinit)(GPIO_TypeDef* GPIOx,uint Pin,
uint GPIO_PortSourceGPIOx,uint GPIO_PinSourcex,
uint EXTI_Linex,EXTITrigger_TypeDef Trigger,
uint EXTIx_IRQn);
}Exti_St;

typedef struct{
	void(*init)();
}Event_St;

/*demo:exit_obj.init(GPIOB,GPIO_Pin_9,GPIO_PortSourceGPIOB,GPIO_PinSource9,
EXTI_Line9,EXTI_Trigger_Rising_Falling,EXTI9_5_IRQn,cb);

exit_obj.deint(GPIOB,GPIO_Pin_9,GPIO_PortSourceGPIOB,GPIO_PinSource9,
EXTI_Line9,EXTI_Trigger_Rising_Falling,EXTI9_5_IRQn)
*/
extern const Exti_St exti_obj;

#ifdef __cplusplus
}
#endif
#endif