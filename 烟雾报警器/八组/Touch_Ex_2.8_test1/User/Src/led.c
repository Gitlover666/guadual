# include "led.h"
# include "stm32f10x.h"

void LED_Init(void)
{
	//定义一个结构体
	GPIO_InitTypeDef GPIO_InitStructre;
	//开启时钟A、B、E
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOA, ENABLE);	 //使能PB,PE端口时钟
	//初始化配置相关gpio口，通用推挽输出
	GPIO_InitStructre.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructre.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6;
	GPIO_InitStructre.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructre);
	
	GPIO_InitStructre.GPIO_Pin = GPIO_Pin_5;
	GPIO_Init(GPIOB, &GPIO_InitStructre);
	GPIO_InitStructre.GPIO_Pin = GPIO_Pin_5;
	GPIO_Init(GPIOE, &GPIO_InitStructre);
	GPIO_SetBits(GPIOA,GPIO_Pin_5|GPIO_Pin_6);
	GPIO_SetBits(GPIOB,GPIO_Pin_5);
	GPIO_SetBits(GPIOE,GPIO_Pin_5);

}

