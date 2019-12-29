#include "user_usart.h"	
#include "stdarg.h"	 	 
#include "stdio.h"	 	 
#include "string.h"

//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
//#pragma import(__use_no_semihosting)   
/*
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
*/

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
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //��������
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);				   //��ʼ��GPIOA

	 //��4����Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��NVIC�Ĵ���
	
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
	NVIC_InitTypeDef NVIC_InitStructure;	
	//ʹ�� USART2 ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//�򿪴���ʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);   //��PA�˿�ʱ��

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
	 //Usart2 NVIC ����
	
	
	/*!!!!!!!!!!!!**attetion!!!****!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
	
	
	//���������ж����ˣ�����һֱ�޷������жϣ�����������
	
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
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
	NVIC_InitTypeDef NVIC_InitStructure;
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
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	  //��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//��������
	GPIO_Init(GPIOB, &GPIO_InitStructure);                    //��ʼ��GPIOB
	 //Usart2 NVIC ����
	
	
	/*!!!!!!!!!!!!**attetion!!!****!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
	
	
	//���������ж����ˣ�����һֱ�޷������жϣ�����������
	
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ��� 
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


#if defined(UART4)&&(ZET6==1)
//����4��ʼ��
void UART4_Config(int boaud_rate)   //��ʼ�� ����USART4
{
	GPIO_InitTypeDef GPIO_InitStructure;	   //���ڶ˿����ýṹ�����
	USART_InitTypeDef USART_InitStructure;	   //���ڲ������ýṹ�����
	NVIC_InitTypeDef NVIC_InitStructure;
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
	 //��4����Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
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


#endif
#if defined(UART5)&&(ZET6==1)
//����5��ʼ��
void UART5_Config(int boaud_rate)   //��ʼ�� ����UART5
{
	GPIO_InitTypeDef GPIO_InitStructure;		//���ڶ˿����ýṹ�����
	USART_InitTypeDef USART_InitStructure;		//���ڲ������ýṹ�����
	NVIC_InitTypeDef NVIC_InitStructure;
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
	   //��4����Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	//����UART5����
	USART_InitStructure.USART_BaudRate = boaud_rate;	                    //���������ã�2400
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	    //����λ�����ã�8λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 	        //ֹͣλ���ã�1λ
	USART_InitStructure.USART_Parity = USART_Parity_No ;            //�Ƿ���żУ�飺��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//Ӳ��������ģʽ���ã�û��ʹ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //�����뷢�Ͷ�ʹ��
	USART_Init(UART5, &USART_InitStructure);                       //��ʼ��UART5

	//�򿪷����жϺͽ����ж�(�����Ҫ�ж�)
	//USART_ITConfig(UART5, USART_IT_TXE, ENABLE);  // ʹ��ָ����UART5�����ж�
  	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE); // ʹ��ָ����UART5�����ж�

	//ʹ�� UART5�� �������
	USART_Cmd(UART5, ENABLE);                             // UART5ʹ��

	//�����������1���ֽ��޷���ȷ���ͳ�ȥ������ */
    USART_ClearFlag(UART5, USART_FLAG_TC);                //�崮��5���ͱ�־
}


#endif
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


#ifdef USART1

static volatile struct{
	uint16_t	tri, twi, tct;
	uint16_t	rri, rwi, rct;
	uint8_t		tbuf[USART1_TXB];
	uint8_t		rbuf[USART1_RXB];
} Fifo1;

static int u1_putc(uchar c){
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
static uchar u1_getc(){
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
const volatile Usart_Obj_st usart1_obj={
	u1_putc,
	u1_getc,
};
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


#endif
#ifdef USART2

static volatile struct{
	uint16_t	tri, twi, tct;
	uint16_t	rri, rwi, rct;
	uint8_t		tbuf[USART2_TXB];
	uint8_t		rbuf[USART2_RXB];
} Fifo2;

static int u2_putc(uchar c){
	int i;
	/* Wait for tx fifo is not full */
	while (Fifo2.tct >= USART2_TXB) ;

	i = Fifo2.twi;		/* Put a byte into Tx fifo */
	Fifo2.tbuf[i] = c;
	Fifo2.twi = ++i % USART2_TXB;
	__disable_irq();
	Fifo2.tct++;
	USART_ITConfig(USART2, USART_IT_TXE, ENABLE);//ʹ�ܷ����ж�
	__enable_irq();
	return 0;
}
static uchar u2_getc(){
	uchar d;
	int i;

	/* Wait while rx fifo is empty */
	while (!Fifo2.rct);

	i = Fifo2.rri;			/* Get a byte from rx fifo */
	d = Fifo2.rbuf[i];
	Fifo2.rri = ++i % USART2_RXB;
	__disable_irq();
	Fifo2.rct--;
	__enable_irq();

	return d;
}
const volatile Usart_Obj_st usart2_obj={
	u2_putc,
	u2_getc,
};
void USART2_IRQHandler(){
	uchar d;
	uint i=0;
	if(USART_GetITStatus(USART2, USART_IT_RXNE) == SET){  //�����ж�
		d = (uchar)USART_ReceiveData(USART2);//��ȡ16bit��1��
		i = Fifo2.rct;
		if (i < USART2_RXB) {	/* Store it into the rx fifo if not full */
			Fifo2.rct = ++i;
			i = Fifo2.rwi;
			Fifo2.rbuf[i] = d;
			Fifo2.rwi = ++i % USART2_RXB;
		}
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);//��������жϱ�־
	}
	
	if(USART_GetITStatus(USART2, USART_IT_TXE) == SET){  //�����ж�,Ҫ��ʹ���˷����ж�
		i = Fifo2.tct;
		if (i--) {	/* There is any data in the tx fifo */
			Fifo2.tct = (uint16_t)i;
			i = Fifo2.tri;
			user_Usart_SendByte(USART2,Fifo2.tbuf[i]);
			Fifo2.tri = ++i % USART2_TXB;
		} else {	/* No data in the tx fifo */
			USART_ITConfig(USART2, USART_IT_TXE, DISABLE);//ʧ�ܷ����ж�
			USART_ClearITPendingBit(USART2,USART_IT_TXE);//��������жϱ�־
		}
	}
}
#endif
#ifdef USART3
static volatile struct{
	uint16_t	tri, twi, tct;
	uint16_t	rri, rwi, rct;
	uint8_t		tbuf[USART3_TXB];
	uint8_t		rbuf[USART3_RXB];
} Fifo3;

static int u3_putc(uchar c){
	int i;
	/* Wait for tx fifo is not full */
	while (Fifo3.tct >= USART3_TXB) ;

	i = Fifo3.twi;		/* Put a byte into Tx fifo */
	Fifo3.tbuf[i] = c;
	Fifo3.twi = ++i % USART3_TXB;
	__disable_irq();
	Fifo3.tct++;
	USART_ITConfig(USART3, USART_IT_TXE, ENABLE);//ʹ�ܷ����ж�
	__enable_irq();
	return 0;
}
static uchar u3_getc(){
	uchar d;
	int i;

	/* Wait while rx fifo is empty */
	while (!Fifo3.rct);

	i = Fifo3.rri;			/* Get a byte from rx fifo */
	d = Fifo3.rbuf[i];
	Fifo3.rri = ++i % USART3_RXB;
	__disable_irq();
	Fifo3.rct--;
	__enable_irq();

	return d;
}
const volatile Usart_Obj_st usart3_obj={
	u3_putc,
	u3_getc,
};
void USART3_IRQHandler(){
	uchar d;
	uint i=0;
	if(USART_GetITStatus(USART3, USART_IT_RXNE) == SET){  //�����ж�
		d = (uchar)USART_ReceiveData(USART3);//��ȡ16bit��1��
		i = Fifo3.rct;
		if (i < USART3_RXB) {	/* Store it into the rx fifo if not full */
			Fifo3.rct = ++i;
			i = Fifo3.rwi;
			Fifo3.rbuf[i] = d;
			Fifo3.rwi = ++i % USART3_RXB;
		}
		USART_ClearITPendingBit(USART3,USART_IT_RXNE);//��������жϱ�־
	}
	
	if(USART_GetITStatus(USART3, USART_IT_TXE) == SET){  //�����ж�,Ҫ��ʹ���˷����ж�
		i = Fifo3.tct;
		if (i--) {	/* There is any data in the tx fifo */
			Fifo3.tct = (uint16_t)i;
			i = Fifo3.tri;
			user_Usart_SendByte(USART3,Fifo3.tbuf[i]);
			Fifo3.tri = ++i % USART3_TXB;
		} else {	/* No data in the tx fifo */
			USART_ITConfig(USART3, USART_IT_TXE, DISABLE);//ʧ�ܷ����ж�
			USART_ClearITPendingBit(USART3,USART_IT_TXE);//��������жϱ�־
		}
	}
}

#endif
//uart4 5 �Ĵ�����Щ���⣬������������
#if defined(UART4)&&(ZET6==1)
static volatile struct{
	uint16_t	tri, twi, tct;
	uint16_t	rri, rwi, rct;
	uint8_t		tbuf[UART4_TXB];
	uint8_t		rbuf[UART4_RXB];
} Fifo4;

static int u4_putc(uchar c){
	int i;
	/* Wait for tx fifo is not full */
	while (Fifo4.tct >= UART4_TXB) ;

	i = Fifo4.twi;		/* Put a byte into Tx fifo */
	Fifo4.tbuf[i] = c;
	Fifo4.twi = ++i % UART4_TXB;
	__disable_irq();
	Fifo4.tct++;
	USART_ITConfig(UART4, USART_IT_TXE, ENABLE);//ʹ�ܷ����ж�
	__enable_irq();
	return 0;
}
static uchar u4_getc(){
	uchar d;
	int i;

	/* Wait while rx fifo is empty */
	while (!Fifo4.rct);

	i = Fifo4.rri;			/* Get a byte from rx fifo */
	d = Fifo4.rbuf[i];
	Fifo4.rri = ++i % UART4_RXB;
	__disable_irq();
	Fifo1.rct--;
	__enable_irq();

	return d;
}
const volatile Usart_Obj_st usart4_obj={
	u4_putc,
	u4_getc,
};

void UART4_IRQHandler(){
	uchar d;
	uint i=0;
	if(USART_GetITStatus(UART4, USART_IT_RXNE) == SET){  //�����ж�
		d = (uchar)USART_ReceiveData(UART4);//��ȡ16bit��1��
		i = Fifo4.rct;
		if (i < UART4_RXB) {	/* Store it into the rx fifo if not full */
			Fifo4.rct = ++i;
			i = Fifo4.rwi;
			Fifo4.rbuf[i] = d;
			Fifo4.rwi = ++i % UART4_RXB;
		}
		USART_ClearITPendingBit(UART4,USART_IT_RXNE);//��������жϱ�־
	}
	
	if(USART_GetITStatus(UART4, USART_IT_TXE) == SET){  //�����ж�,Ҫ��ʹ���˷����ж�
		i = Fifo4.tct;
		if (i--) {	/* There is any data in the tx fifo */
			Fifo1.tct = (uint16_t)i;
			i = Fifo4.tri;
			user_Usart_SendByte(UART4,Fifo4.tbuf[i]);
			Fifo4.tri = ++i % UART4_TXB;
		} else {	/* No data in the tx fifo */
			USART_ITConfig(UART4, USART_IT_TXE, DISABLE);//ʧ�ܷ����ж�
			USART_ClearITPendingBit(UART4,USART_IT_TXE);//��������жϱ�־
		}
	}
}

#endif

#if defined(UART5)&&(ZET6==1)
static volatile struct{
	uint16_t	tri, twi, tct;
	uint16_t	rri, rwi, rct;
	uint8_t		tbuf[UART5_TXB];
	uint8_t		rbuf[UART5_RXB];
} Fifo5;

static int u5_putc(uchar c){
	int i;
	/* Wait for tx fifo is not full */
	while (Fifo5.tct >= UART5_TXB) ;

	i = Fifo5.twi;		/* Put a byte into Tx fifo */
	Fifo5.tbuf[i] = c;
	Fifo5.twi = ++i % UART5_TXB;
	__disable_irq();
	Fifo5.tct++;
	USART_ITConfig(UART5, USART_IT_TXE, ENABLE);//ʹ�ܷ����ж�
	__enable_irq();
	return 0;
}
static uchar u5_getc(){
	uchar d;
	int i;

	/* Wait while rx fifo is empty */
	while (!Fifo5.rct);

	i = Fifo5.rri;			/* Get a byte from rx fifo */
	d = Fifo5.rbuf[i];
	Fifo5.rri = ++i % UART5_RXB;
	__disable_irq();
	Fifo1.rct--;
	__enable_irq();

	return d;
}
const volatile Usart_Obj_st usart5_obj={
	u5_putc,
	u5_getc,
};

void UART5_IRQHandler(){
	uchar d;
	uint i=0;
	if(USART_GetITStatus(UART5, USART_IT_RXNE) == SET){  //�����ж�
		d = (uchar)USART_ReceiveData(UART5);//��ȡ16bit��1��
		i = Fifo5.rct;
		if (i < UART5_RXB) {	/* Store it into the rx fifo if not full */
			Fifo5.rct = ++i;
			i = Fifo5.rwi;
			Fifo5.rbuf[i] = d;
			Fifo5.rwi = ++i % UART5_RXB;
		}
		USART_ClearITPendingBit(UART5,USART_IT_RXNE);//��������жϱ�־
	}
	
	if(USART_GetITStatus(UART5, USART_IT_TXE) == SET){  //�����ж�,Ҫ��ʹ���˷����ж�
		i = Fifo5.tct;
		if (i--) {	/* There is any data in the tx fifo */
			Fifo1.tct = (uint16_t)i;
			i = Fifo5.tri;
			user_Usart_SendByte(UART5,Fifo5.tbuf[i]);
			Fifo5.tri = ++i % UART5_TXB;
		} else {	/* No data in the tx fifo */
			USART_ITConfig(UART5, USART_IT_TXE, DISABLE);//ʧ�ܷ����ж�
			USART_ClearITPendingBit(UART5,USART_IT_TXE);//��������жϱ�־
		}
	}
}

#endif




