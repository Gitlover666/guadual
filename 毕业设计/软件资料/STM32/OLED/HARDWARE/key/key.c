#include "key.h"

void KEY_Init(void)
{
 
		 GPIO_InitTypeDef  GPIO_InitStructure;
			
		 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);	 //使能端口时钟
			
		 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 
		 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		 //上拉输入
		 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
		 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化
						
		 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 
		 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		 //上拉输入
		 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
		 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化

}







