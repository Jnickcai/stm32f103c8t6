#include "user_usart.h"	
#include "stdarg.h"	 	 
#include "stdio.h"	 	 
#include "string.h"

//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

};

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
    USART1->DR = (u8) ch;      
	return ch;
} 

//����1��ʼ��
void USART1_Config(int boaud_rate)		//��ʼ�� ����USART1
{
	GPIO_InitTypeDef     GPIO_InitStructure;   //���ڶ˿����ýṹ�����
	USART_InitTypeDef    USART_InitStructure;  //���ڲ������ýṹ�����
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//��1������GPIO��USART������ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);	 //��GPIOAʱ�Ӻ�GPIOA����ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	//�򿪴��ڸ���ʱ��
	USART_DeInit(USART1);  //��λ����1

	//��2������USART1 Tx�����ͽţ���GPIO����Ϊ���츴��ģʽ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;			   //����1���ͽ�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		   //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	   //����ٶ�50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);				   //��ʼ��GPIOA
														  
	//��3������USART Rx�����սţ���GPIO����Ϊ��������ģʽ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;			   //����1���ս�
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);				   //��ʼ��GPIOA

//	 //��4����Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	
	//��5��������USART1����
	USART_InitStructure.USART_BaudRate             = boaud_rate;							 //���������ã�115200
	USART_InitStructure.USART_WordLength           = USART_WordLength_8b;			 //����λ�����ã�8λ
	USART_InitStructure.USART_StopBits             = USART_StopBits_1;				 //ֹͣλ���ã�1λ
	USART_InitStructure.USART_Parity               = USART_Parity_No;				 //�Ƿ���żУ�飺��
	USART_InitStructure.USART_HardwareFlowControl  = USART_HardwareFlowControl_None; //Ӳ��������ģʽ���ã�û��ʹ��
	USART_InitStructure.USART_Mode                 = USART_Mode_Rx | USART_Mode_Tx;	 //�����뷢�Ͷ�ʹ��
	USART_Init(USART1, &USART_InitStructure);										 //��ʼ��USART1

    //�򿪷����жϺͽ����ж�(�����Ҫ�ж�)
	//  USART_ITConfig(USART1, USART_IT_TXE, ENABLE);  // ʹ��ָ����USART1�����ж� ���˴�ʹ�ܵ��²�ͣ���봮���ж�
  	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); // ʹ��ָ����USART1�����ж� ��

	//��6����ʹ�� USART1�� �������
	 USART_Cmd(USART1, ENABLE);							   //ʹ�� USART1

    //�����������1���ֽ��޷���ȷ���ͳ�ȥ������
    USART_ClearFlag(USART1, USART_FLAG_TC);                //�崮��1���ͱ�־
	
}

//����2��ʼ��
void USART2_Config(int boaud_rate)   //��ʼ�� ����USART2
{
	GPIO_InitTypeDef    GPIO_InitStructure;	   //���ڶ˿����ýṹ�����
	USART_InitTypeDef   USART_InitStructure;   //���ڲ������ýṹ�����

	//ʹ�� USART2 ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//�򿪴��ڸ���ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);   //��PA�˿�ʱ��

	//��USART2 Tx�����ͽţ���GPIO����Ϊ���츴��ģʽ   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				  //ѡ���ĸ�IO�� ��ѡ��PA2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;           //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		  //�趨IO�ڵ�����ٶ�Ϊ50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);    				  //��ʼ��GPIOA

	//��USART2 Rx�����սţ���GPIO����Ϊ��������ģʽ														  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;				  //ѡ���ĸ�IO�� ��ѡ��PA3
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	  //��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);                    //��ʼ��GPIOA
	  
	//����USART2����
	USART_InitStructure.USART_BaudRate = boaud_rate;	                    //���������ã�115200
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	    //����λ�����ã�8λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 	        //ֹͣλ���ã�1λ
	USART_InitStructure.USART_Parity = USART_Parity_No ;            //�Ƿ���żУ�飺��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//Ӳ��������ģʽ���ã�û��ʹ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //�����뷢�Ͷ�ʹ��
	USART_Init(USART2, &USART_InitStructure);                       //��ʼ��USART2
	
	//�򿪷����жϺͽ����ж�(�����Ҫ�ж�)
	//USART_ITConfig(USART2, USART_IT_TXE, ENABLE);  // ʹ��ָ����USART2�����ж�
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); // ʹ��ָ����USART2�����ж�

	//ʹ�� USART2�� �������
	USART_Cmd(USART2, ENABLE);                             // USART2ʹ��

	//�����������1���ֽ��޷���ȷ���ͳ�ȥ������
    USART_ClearFlag(USART2, USART_FLAG_TC);                //�崮��2���ͱ�־
}

//����3��ʼ��
void USART3_Config(int boaud_rate)   //��ʼ�� ����USART3
{
	GPIO_InitTypeDef GPIO_InitStructure;	  //���ڶ˿����ýṹ�����
	USART_InitTypeDef USART_InitStructure;	  //���ڲ������ýṹ�����

	//ʹ�� USART3 ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	//�򿪴��ڸ���ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);   //��PB�˿�ʱ��
  	
	//��USART3 Tx�����ͽţ���GPIO����Ϊ���츴��ģʽ   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;				  //ѡ���ĸ�IO�� ��ѡ��PB10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;           //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		  //�趨IO�ڵ�����ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);    				  //��ʼ��GPIOB
	
	//��USART3 Rx�����սţ���GPIO����Ϊ��������ģʽ														  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;				  //ѡ���ĸ�IO�� ��ѡ��PB11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	  //��������
	GPIO_Init(GPIOB, &GPIO_InitStructure);                    //��ʼ��GPIOA
	  
	//����USART3����
	USART_InitStructure.USART_BaudRate = boaud_rate;	                    //���������ã�115200
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	    //����λ�����ã�8λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 	        //ֹͣλ���ã�1λ
	USART_InitStructure.USART_Parity = USART_Parity_No ;            //�Ƿ���żУ�飺��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//Ӳ��������ģʽ���ã�û��ʹ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //�����뷢�Ͷ�ʹ��
	USART_Init(USART3, &USART_InitStructure);                       //��ʼ��USART3
	
    //�򿪷����жϺͽ����ж�(�����Ҫ�ж�)
	//  USART_ITConfig(USART3, USART_IT_TXE, ENABLE);  // ʹ��ָ����USART3�����ж�
  	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE); // ʹ��ָ����USART3�����ж�

	//ʹ�� USART3�� �������
	USART_Cmd(USART3, ENABLE);                             // USART3ʹ��

	//�����������1���ֽ��޷���ȷ���ͳ�ȥ������
    USART_ClearFlag(USART3, USART_FLAG_TC);                //�崮��3���ͱ�־
}

//����4��ʼ��
void UART4_Config(int boaud_rate)   //��ʼ�� ����USART4
{
	GPIO_InitTypeDef GPIO_InitStructure;	   //���ڶ˿����ýṹ�����
	USART_InitTypeDef USART_InitStructure;	   //���ڲ������ýṹ�����

	//ʹ�� UART4 ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);	//�򿪴��ڸ���ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);   //��PC�˿�ʱ��
	
	//��USART4 Tx�����ͽţ���GPIO����Ϊ���츴��ģʽ   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;				  //ѡ���ĸ�IO�� ��ѡ��PC10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;           //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		  //�趨IO�ڵ�����ٶ�Ϊ50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);    				  //��ʼ��GPIOC

	//��UART4 Rx�����սţ���GPIO����Ϊ��������ģʽ														  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;				  //ѡ���ĸ�IO�� ��ѡ��PC11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	  //��������
	GPIO_Init(GPIOC, &GPIO_InitStructure);                    //��ʼ��GPIOC
	  
	//����UART4����
	USART_InitStructure.USART_BaudRate = boaud_rate;	                    //���������ã�9600
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	    //����λ�����ã�8λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 	        //ֹͣλ���ã�1λ
	USART_InitStructure.USART_Parity = USART_Parity_No ;            //�Ƿ���żУ�飺��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//Ӳ��������ģʽ���ã�û��ʹ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //�����뷢�Ͷ�ʹ��
	USART_Init(UART4, &USART_InitStructure);                       //��ʼ��UART4
	
	//�򿪷����жϺͽ����ж�(�����Ҫ�ж�)
	//USART_ITConfig(UART4, USART_IT_TXE, ENABLE);  // ʹ��ָ����UART4�����ж�
  	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE); // ʹ��ָ����UART4�����ж�

	//ʹ�� UART4�� �������
	USART_Cmd(UART4, ENABLE);                             // UART4ʹ��

	//�����������1���ֽ��޷���ȷ���ͳ�ȥ������
    USART_ClearFlag(UART4, USART_FLAG_TC);                //�崮��4���ͱ�־
}

//����5��ʼ��
void UART5_Config(int boaud_rate)   //��ʼ�� ����UART5
{
	GPIO_InitTypeDef GPIO_InitStructure;		//���ڶ˿����ýṹ�����
	USART_InitTypeDef USART_InitStructure;		//���ڲ������ýṹ�����

	//ʹ�� UART5 ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);	//�򿪴��ڸ���ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);   //��PC�˿�ʱ��
	
	//��UART5 Tx�����ͽţ���GPIO����Ϊ���츴��ģʽ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;				  //ѡ���ĸ�IO�� ��ѡ��PC12
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;           //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		  //�趨IO�ڵ�����ٶ�Ϊ50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);    				  //��ʼ��GPIOC

	//��UART5 Rx�����սţ���GPIO����Ϊ��������ģʽ															  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				  //ѡ���ĸ�IO�� ��ѡ��PD2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	  //��������
	GPIO_Init(GPIOD, &GPIO_InitStructure);                    //��ʼ��GPIOC
	  
	//����UART5����
	USART_InitStructure.USART_BaudRate = boaud_rate;	                    //���������ã�2400
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	    //����λ�����ã�8λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 	        //ֹͣλ���ã�1λ
	USART_InitStructure.USART_Parity = USART_Parity_No ;            //�Ƿ���żУ�飺��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//Ӳ��������ģʽ���ã�û��ʹ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //�����뷢�Ͷ�ʹ��
	USART_Init(UART5, &USART_InitStructure);                       //��ʼ��UART5

	//�򿪷����жϺͽ����ж�(�����Ҫ�ж�)
	//USART_ITConfig(UART5, USART_IT_TXE, ENABLE);  // ʹ��ָ����UART4�����ж�
  	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE); // ʹ��ָ����UART4�����ж�

	//ʹ�� UART5�� �������
	USART_Cmd(UART5, ENABLE);                             // UART5ʹ��

	//�����������1���ֽ��޷���ȷ���ͳ�ȥ������ */
    USART_ClearFlag(UART5, USART_FLAG_TC);                //�崮��5���ͱ�־
}

void user_Usart_SendByte(USART_TypeDef * Usart_Num,uchar SendData)	  //�ô���usart_num����һ���ֽ�����
{	  
	USART_SendData(Usart_Num,SendData);   //�ô��ڷ���һ���ֽ�
	while(USART_GetFlagStatus(Usart_Num, USART_FLAG_TXE) == RESET);  //�ȴ����ڷ������
} 

int user_Usart_Send(USART_TypeDef * Usart_Num,const uchar *str)	  //�ô���usart_num�����ַ���
{	
	int write_counter = 0;
	while(*str!=NULL){
		USART_SendData(Usart_Num,*str);   //�ô��ڷ���һ���ֽ�
		while(USART_GetFlagStatus(Usart_Num, USART_FLAG_TXE) == RESET);  //�ȴ����ڷ������
		write_counter++;
		str++;
	}
	return write_counter;
}

uchar* u_gets(USART_TypeDef * Usart_Num){
	return 0;
}
int u_puts(USART_TypeDef * Usart_Num,uchar *s){
	return 0;
}

#ifdef USART1

static volatile struct{
	uint16_t	tri, twi, tct;
	uint16_t	rri, rwi, rct;
	uint8_t		tbuf[USART1_TXB];
	uint8_t		rbuf[USART1_RXB];
} Fifo1;

int u1_putc(uchar c){
	int i;
	/* Wait for tx fifo is not full */
	while (Fifo1.tct >= USART1_TXB) ;

	i = Fifo1.twi;		/* Put a byte into Tx fifo */
	Fifo1.tbuf[i] = c;
	Fifo1.twi = ++i % USART1_TXB;
	__disable_irq();
	Fifo1.tct++;
	USART_ITConfig(USART1, USART_IT_TXE, ENABLE);//ʹ�ܷ����ж�
	__enable_irq();
	return 0;
}
uchar u1_getc(){
	uchar d;
	int i;

	/* Wait while rx fifo is empty */
	while (!Fifo1.rct);

	i = Fifo1.rri;			/* Get a byte from rx fifo */
	d = Fifo1.rbuf[i];
	Fifo1.rri = ++i % USART1_RXB;
	__disable_irq();
	Fifo1.rct--;
	__enable_irq();

	return d;
}

void USART1_IRQHandler(){
	uchar d;
	uint i=0;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET){  //�����ж�
		d = (uchar)USART_ReceiveData(USART1);//��ȡ16bit��1��
		i = Fifo1.rct;
		if (i < USART1_RXB) {	/* Store it into the rx fifo if not full */
			Fifo1.rct = ++i;
			i = Fifo1.rwi;
			Fifo1.rbuf[i] = d;
			Fifo1.rwi = ++i % USART1_RXB;
		}
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);//��������жϱ�־
	}
	
	if(USART_GetITStatus(USART1, USART_IT_TXE) == SET){  //�����ж�,Ҫ��ʹ���˷����ж�
		i = Fifo1.tct;
		if (i--) {	/* There is any data in the tx fifo */
			Fifo1.tct = (uint16_t)i;
			i = Fifo1.tri;
			user_Usart_SendByte(USART1,Fifo1.tbuf[i]);
			Fifo1.tri = ++i % USART1_TXB;
		} else {	/* No data in the tx fifo */
			USART_ITConfig(USART1, USART_IT_TXE, DISABLE);//ʧ�ܷ����ж�
			USART_ClearITPendingBit(USART1,USART_IT_TXE);//��������жϱ�־
		}
	}
}

const volatile usart_obj usart1_obj={
	u1_putc,
	u1_getc,
	u_gets,
	u_puts,
};

#endif
#ifdef USART2
void USART2_IRQHandler(){
	if(USART_GetITStatus(USART2, USART_IT_RXNE) == RESET){  //�����ж�
		
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);//��������жϱ�־
	}
	
	if(USART_GetITStatus(USART2, USART_IT_TXE) == RESET){  //�����ж�,Ҫ��ʹ���˷����ж�
		
		USART_ClearITPendingBit(USART2,USART_IT_TXE);//��������жϱ�־
	}
}
#endif
#ifdef USART3
void USART3_IRQHandler(){
	if(USART_GetITStatus(USART3, USART_IT_RXNE) == RESET){  //�����ж�
		
		USART_ClearITPendingBit(USART3,USART_IT_RXNE);//��������жϱ�־
	}
	
	if(USART_GetITStatus(USART3, USART_IT_TXE) == RESET){  //�����ж�,Ҫ��ʹ���˷����ж�
		
		USART_ClearITPendingBit(USART3,USART_IT_TXE);//��������жϱ�־
	}
}

#endif
//uart4 5 �Ĵ�����Щ���⣬������������
void USART4_IRQHandler(){
	if(USART_GetITStatus(UART4, USART_IT_RXNE) == RESET){  //�����ж�
		
		USART_ClearITPendingBit(UART4,USART_IT_RXNE);//��������жϱ�־
	}
	
	if(USART_GetITStatus(UART4, USART_IT_TXE) == RESET){  //�����ж�,Ҫ��ʹ���˷����ж�
		
		USART_ClearITPendingBit(UART4,USART_IT_TXE);//��������жϱ�־
	}
}
void USART5_IRQHandler(){
	if(USART_GetITStatus(UART5, USART_IT_RXNE) == RESET){  //�����ж�
		
		USART_ClearITPendingBit(UART5,USART_IT_RXNE);//��������жϱ�־
	}
	
	if(USART_GetITStatus(UART5, USART_IT_TXE) == RESET){  //�����ж�,Ҫ��ʹ���˷����ж�
		
		USART_ClearITPendingBit(UART5,USART_IT_TXE);//��������жϱ�־
	}
}




