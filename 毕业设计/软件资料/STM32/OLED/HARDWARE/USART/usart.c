#include "usart.h"
/*
//TXD  -->  PA9  (UART1-TXD)
//RXD  -->  PA10 (UART1-RXD)
------------------------------
*/

u8 TxBuffer[258];
u8 TxCounter=0;
u8 count=0; 

void USART1_init(u32 baudrate)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure; 
	/* ʹ�� UART1 ģ���ʱ��  ʹ�� UART1��Ӧ�����Ŷ˿�PA��ʱ��*/
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);

		//����UART1 �ķ�������
	
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;// Ϊ������� 
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);    

	 // ����UART1 �Ľ�������
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//�������� 
  	GPIO_Init(GPIOA, &GPIO_InitStructure);
	  
		
		USART_InitStructure.USART_BaudRate = baudrate;//	  1.������Ϊ���ó���ָ�������� baudrate;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;//	  2. 8λ����			  USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;//	  3.һ��ֹͣλ			  USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No ;//	  4. ����żЧ��			  USART_Parity_No ;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//	  5.��ʹ��Ӳ��������	  USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//	  6.ʹ�ܷ��ͺͽ��չ���	  USART_Mode_Rx | USART_Mode_Tx;
	//Ӧ�����õ�UART1
		USART_Init(USART1, &USART_InitStructure); 
		USART_ITConfig(USART1, USART_IT_TXE, DISABLE);  
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);        
		USART_ClearFlag(USART1,USART_FLAG_TC);

   /* Enable the USART1 Interrupt */
     NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
		 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 7;
     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
     NVIC_Init(&NVIC_InitStructure);
	//����UART1
	
		USART_Cmd(USART1, ENABLE);
		USART_ITConfig(USART1, USART_IT_TXE, ENABLE); // ʹ�ܻ���ʧ��ָ���� USART �ж�

}

void USART1_IRQHandler(void)
{

	if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)
		{   
			USART_SendData(USART1, TxBuffer[TxCounter++]); 
			if(TxCounter == count) 
			{
				USART_ITConfig(USART1, USART_IT_TXE, DISABLE);// ȫ���������
			}
			USART_ClearITPendingBit(USART1, USART_IT_TXE); //��� USART1 ���жϴ�����λ
		}
	else if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {
			USART_ClearITPendingBit(USART1, USART_IT_RXNE);
  }
	USART_ClearITPendingBit(USART1,USART_IT_ORE);
//	USART_SendData(USART1,8);
}

void SendString(char * buf1)
{  u8 i=0;
   while (1)
   {  if (buf1[i]!=0)
     {  USART_SendData(USART1, buf1[i]);  //����һ��byte������
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET){}; //�ȴ����ͽ���
        i++;
     }
     else return;
   }
//	  USART_SendData(USART1,'\n');
}

void USART2_init(u32 bound)
{
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART2��GPIOAʱ��
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	//USART2_TX   GPIOA.2
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.2
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.2
   
  //USART2_RX	  GPIOA.3��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA3
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.3 

  //Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//��ռ���ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART2, &USART_InitStructure); //��ʼ������2
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ���2

}

void USART2_IRQHandler(void)                	//����2�жϷ������
{
//	u8 Res,i; 
//	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
//		{
//			
//			Res =USART_ReceiveData(USART2);	//��ȡ���յ�������	
//			for(i=0;i<30;i++)
//			{
////				table[i]=Res;	
//				Res=0;
//			}
//		//	USART_SendData(USART1,Res);	
//		}
////	USART_ClearITPendingBit(USART2,USART_IT_RXNE);
}

void SendString2(char * buf1)
{  u8 i=0;
   while (1)
   {  if (buf1[i]!=0)
     {  USART_SendData(USART2, buf1[i]);  //����һ��byte������
        while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET){}; //�ȴ����ͽ���
        i++;
     }
     else return;
   }
//	  USART_SendData(USART2,'\n');
}


