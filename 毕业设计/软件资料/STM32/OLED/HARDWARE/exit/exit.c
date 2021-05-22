#include "exit.h"
#include "key.h"
#include "delay.h"
#include "led.h"
#include "stdio.h"
#include "usart.h"
u16 lm=0;
char  canbuf1[20];
void exit0_init(void)
{
			EXTI_InitTypeDef   EXTI_InitStructure;
			NVIC_InitTypeDef   NVIC_InitStructure;
	
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//ʹ�ܸ��ù���ʱ��
			KEY_Init();
			
			EXTI_InitStructure.EXTI_Line=EXTI_Line0;
			EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;//�ж�
////			EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;//����  ������
			EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising;
//			EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising_Falling;//����  ������
			EXTI_InitStructure.EXTI_LineCmd=ENABLE;
			EXTI_Init(&EXTI_InitStructure);
	
			NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//�����ȼ�3
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
			NVIC_Init(&NVIC_InitStructure); 
			
}

void EXTI0_IRQHandler(void)
{

	lm++;
	if(lm>999999){lm=0;}
	sprintf(canbuf1,"%d  ", lm); 
	SendString2(canbuf1);
	
//	delay_ms(10);//����
//	if(KEY1==0)	 	 //WK_UP����
//	{				 
//		
//	}
	EXTI_ClearITPendingBit(EXTI_Line0); //���LINE0�ϵ��жϱ�־λ  
}


