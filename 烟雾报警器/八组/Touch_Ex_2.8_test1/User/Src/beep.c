# include "beep.h"
# include "stm32f10x.h"

void BEEP_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructre;
	//����ʱ��B
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PB,PE�˿�ʱ��
	//��ʼ���������gpio�ڣ�ͨ���������
	GPIO_InitStructre.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructre.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructre.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructre);
}

