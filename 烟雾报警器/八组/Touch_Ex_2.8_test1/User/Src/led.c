# include "led.h"
# include "stm32f10x.h"

void LED_Init(void)
{
	//����һ���ṹ��
	GPIO_InitTypeDef GPIO_InitStructre;
	//����ʱ��A��B��E
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOA, ENABLE);	 //ʹ��PB,PE�˿�ʱ��
	//��ʼ���������gpio�ڣ�ͨ���������
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

