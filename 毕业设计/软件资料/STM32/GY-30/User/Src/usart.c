#include "usart.h"

/* ����1��Ӧ�ܽ� *
RXD ---> PA10
TXD ---> PA9
******************/

/************* ���ڳ�ʼ������ ******************
Pclk������1ģ��ʱ��
Bound�����ڲ�����
************************************************/
void Usart1_Init(u32 Pclk, u32 Bound)
{
	float USARTDIV;  //�����ʼ���ֵ
	u16 Mantissa;    //��������
	u16 Fraction;    //С������
	
	/* ʹ�ܴ���ģ��ʱ�� */
	RCC->APB2ENR |= 1 << 14;  //ʹ�ܴ���1ʱ��
	
	/* ���ô��ڹܽŹ��� */
	/* STM32����ģ�����Լ��Ĺ���ģʽ
	ģ��Ĺ���ģʽ�ο�STM32���Ĳο��ֲ�_V10.pdf
	��110ҳ�������GPIO����
	TXD�����츴�����
	RXD�������������������*/
	RCC->APB2ENR |= 1 << 2;   //ʹ��GPIOAʱ��
	GPIOA->CRH &= 0xfffff00f; //��CRH�Ĵ���4~11λ����
	GPIOA->CRH |= 0x000004b0; //PA9����Ϊ�������죬�ٶ�50M��PA10����λ��������
	
	/* ���ô��ڱ����� */
	USARTDIV = (float)(Pclk * 1000000 /(16. * Bound));  //���㲨����ֵ
	Mantissa = USARTDIV;                      //��ȡ��������     
	Fraction = (USARTDIV - Mantissa) * 16;    //��ȡС������
	USART1->BRR = (Mantissa << 4) | Fraction; //�Ѳ����ʼ���ֵд�벨���ʼĴ���
	
	/* ����ģ������ */
	USART1->CR1 |= 1 << 13;   //ʹ�ܴ���ģ��
	USART1->CR1 &= ~(1 << 12);//���ݳ���λ8λ��������У��λ
	USART1->CR1 &= ~(1 << 10);//��ʹ������У��
	USART1->CR1 |= 1 << 3;    //����ʹ��
	USART1->CR1 |= 1 << 2;    //����ʹ��
	
	USART1->CR2 &= ~(3 << 12);//ֹͣλ����Ϊ1λֹͣλ
}

/***************** ���ڷ����ַ����� **************************/
void USART_Send_Str(u8 *dat)
{
	while( *dat != '\0')
	{
		USART1->DR = *dat;
		while(!(USART1->SR & (1 << 7)));       //�������
		dat++;
	}
}

/*fputc��printf��ײ�ĵ��ú���*/
int fputc(int data, FILE* file)
{
	 USART1->DR = data;  //��������
	 while(!(USART1->SR & (1<<7))); /*�ȴ����ʹ��ڵ�����*/
	 return data;
}











