#include "timer.h"
#include "led.h"
#include "exit.h"
void Timer4_pwmout_init(u16 arr  ,u16 psc)
{
		GPIO_InitTypeDef  GPIO_InitStructure;	
		TIM_TimeBaseInitTypeDef   TIM_TimeBaseInitStructure;
		TIM_OCInitTypeDef   TIM_OCInitStructure;
	
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOB,&GPIO_InitStructure);

//		GPIO_PinRemapConfig(GPIO_Remap_TIM4, DISABLE); //������ӳ��

	
//		TIM_TimeBaseInitStructure.TIM_Period=7200-1;//arr
//		TIM_TimeBaseInitStructure.TIM_Prescaler=0;//psc
		TIM_TimeBaseInitStructure.TIM_Period=arr;//arr
		TIM_TimeBaseInitStructure.TIM_Prescaler=psc;//psc
		TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
		TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;//shuwei0
		TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;
		TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);
		
		
		TIM_OCInitStructure.TIM_Pulse=1000;
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//TIM_OCPolarity_Low;
		TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
		TIM_OC1Init(TIM4, &TIM_OCInitStructure);

		
		TIM_OCInitStructure.TIM_Pulse=500;
		TIM_OC2Init(TIM4, &TIM_OCInitStructure);

		TIM_OCInitStructure.TIM_Pulse=700;
		TIM_OC3Init(TIM4, &TIM_OCInitStructure);
		
		TIM_OCInitStructure.TIM_Pulse=1000;
		TIM_OC4Init(TIM4, &TIM_OCInitStructure);
		

		TIM_ARRPreloadConfig(TIM4, ENABLE);			 // ʹ��TIM1���ؼĴ���ARR
			
		TIM_OC1PreloadConfig(TIM4, ENABLE );  //
		TIM_OC2PreloadConfig(TIM4, ENABLE);  //
		TIM_OC3PreloadConfig(TIM4, ENABLE);  //
		TIM_OC4PreloadConfig(TIM4, ENABLE);  //


		TIM_Cmd(TIM4, ENABLE);  //
		
		TIM_CtrlPWMOutputs(TIM4, ENABLE);
		

}
void TIM2_InPWM_init(u16 arr ,u16 psc)
{
		GPIO_InitTypeDef  GPIO_InitStructure;	
		TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
//		TIM_ICInitTypeDef     TIM_ICInitStructure;
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);	

		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOA,&GPIO_InitStructure);
		
		TIM_TimeBaseInitStructure.TIM_Period=arr;
		TIM_TimeBaseInitStructure.TIM_Prescaler=psc;
		TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
		TIM_TimeBaseInitStructure.TIM_ClockDivision=0;
		TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);

	
//		TIM_ICInitStructure.TIM_Channel=TIM_Channel_4;//ͨ��
//		TIM_ICInitStructure.TIM_ICFilter=0x00;  //���˲� �˲���
//		TIM_ICInitStructure.TIM_ICPolarity=      //������
//		TIM_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1;    //��Ƶϵ��
//		TIM_ICInitStructure.TIM_ICSelection=     //ӳ���ϵ
//		TIM_ICInit(TIM2,&TIM_ICInitStructure);



}


void TIM3_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���


	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx					 
}
//��ʱ��3�жϷ������
void TIM3_IRQHandler(void)   //TIM3�ж�
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
		{
			LED3=!LED3;
			
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx�����жϱ�־ 
		
		}
}
























