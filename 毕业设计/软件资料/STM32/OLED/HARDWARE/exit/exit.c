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
	
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟
			KEY_Init();
			
			EXTI_InitStructure.EXTI_Line=EXTI_Line0;
			EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;//中断
////			EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;//上下  跳变沿
			EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising;
//			EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising_Falling;//上下  跳变沿
			EXTI_InitStructure.EXTI_LineCmd=ENABLE;
			EXTI_Init(&EXTI_InitStructure);
	
			NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//子优先级3
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
			NVIC_Init(&NVIC_InitStructure); 
			
}

void EXTI0_IRQHandler(void)
{

	lm++;
	if(lm>999999){lm=0;}
	sprintf(canbuf1,"%d  ", lm); 
	SendString2(canbuf1);
	
//	delay_ms(10);//消抖
//	if(KEY1==0)	 	 //WK_UP按键
//	{				 
//		
//	}
	EXTI_ClearITPendingBit(EXTI_Line0); //清除LINE0上的中断标志位  
}


