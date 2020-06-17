# include "beep.h"
# include "stm32f10x.h"

void BEEP_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructre;
	//开启时钟B
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PB,PE端口时钟
	//初始化配置相关gpio口，通用推挽输出
	GPIO_InitStructre.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructre.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructre.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructre);
}

