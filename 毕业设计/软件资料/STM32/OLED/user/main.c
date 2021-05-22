#include "stm32f10x.h"
#include "delay.h"
#include "stdio.h"
#include "OLED.h"
int main(void)
{		
	 	u16 led0pwmval=3000;
		u8 dir=1;	
	
		delay_init(72);
//		USART2_init(115200);
//		USART1_init(115200);
//		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置 NVIC 中断分组 2
//		Timer4_pwmout_init(4999,0);
//		TIM3_Init(7199,7199);/* ARR 装载值 ，PSC 预分频值 ，f =(ARR-1)*(PSC-1)/72M ，默认设置所以分母是72m ，*/
//		exit0_init();
//		LED_Init();
		OLED_Init();
		while(1)
		{	
//			Picture(1);
			
			OLED_ShowCHinese(18,0,0);
			OLED_ShowNum(0,0,10,2,16);
		}
}

