#include "stm32f10x.h"
#include "usart.h"
#include "bh1750.h"
#include "systick.h"
#include "string.h"
#include "iic.h"	

int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	Delay_Init(1000);
	Usart1_Init(71, 115200);
	BH1750_Init();
	
	while(1)
	{
		printf("light:");

		Delay_ms(500);
	}
}	

