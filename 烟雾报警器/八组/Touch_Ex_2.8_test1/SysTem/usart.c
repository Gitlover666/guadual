#include "usart.h"

/**************************** USART_1ģ���ʼ������ ****************************
��  �ܣ���USART_1ģ����г�ʼ������
��  �����������ݴ��䲨����
����ֵ����
Ӳ�����ӣ�
USART1_RX --- PA10��USART1_TX --- PA9
*********************************************************************************/
void USART_1_Init(u32 Boand)
{
	GPIO_InitTypeDef GPIO_InitStruct;//GPIO��
	USART_InitTypeDef USART_InitStruct;//����
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	//����10Ϊ����
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	//����9Ϊ���
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;//����Ϊ���ùܽ�
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//��ʼ�����ڣ�ͨ��Э���Լ������ʣ�
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStruct.USART_BaudRate = Boand;
	
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART1,&USART_InitStruct);
	
	USART_Cmd(USART1,ENABLE);
}

/**************************** USART_1�����ַ������� ****************************
��  �ܣ�USART_1ģ�鷢��һ���ַ�������
��  ������Ҫ���͵��ַ�������
����ֵ����
*********************************************************************************/
void Usart_Send_Str(char *Str)
{
	while( *Str != '\0' )
	{
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == 0)
		{
			/* �ȴ�������� */
		}
		USART_SendData(USART1,*Str);
		Str++;
		
	}
}

/**************************** USART_1�����ַ����� ****************************
��  �ܣ�USART_1ģ�����һ���ַ�����
��  ������
����ֵ�����ؽ��յ����ַ�����
*********************************************************************************/
char Usart_Rec_Byte(void)
{
	char Temp = 0;
	
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == 0)
	{
		/* �ȴ�������� */
	}
	USART_SendData(USART1,Temp);
	
	return Temp;
}

/**************************** USART_1��ӡ���� ****************************
ʹ�ô��ڴ�ӡ�������裺
1.����stdio.hͷ�ļ�
2.��ħ�����е�Targetѡ��й�ѡ"Use Micro LIB"ѡ��
3.�ú���ϵͳ�Զ����ã�����Ҫ��Ϊʹ��
**************************************************************************/
int fputc(int ch, FILE *stream)
{
	USART_SendData(USART1,ch);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == 0)
	{
		/* �ȴ�������� */
	}
	return ch;
}


