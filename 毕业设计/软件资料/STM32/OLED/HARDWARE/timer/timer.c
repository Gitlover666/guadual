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

//		GPIO_PinRemapConfig(GPIO_Remap_TIM4, DISABLE); //不用重映射

	
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
		

		TIM_ARRPreloadConfig(TIM4, ENABLE);			 // 使能TIM1重载寄存器ARR
			
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

	
//		TIM_ICInitStructure.TIM_Channel=TIM_Channel_4;//通道
//		TIM_ICInitStructure.TIM_ICFilter=0x00;  //不滤波 滤波器
//		TIM_ICInitStructure.TIM_ICPolarity=      //捕获极性
//		TIM_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1;    //分频系数
//		TIM_ICInitStructure.TIM_ICSelection=     //映射关系
//		TIM_ICInit(TIM2,&TIM_ICInitStructure);



}


void TIM3_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能
	
	//定时器TIM3初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器


	TIM_Cmd(TIM3, ENABLE);  //使能TIMx					 
}
//定时器3中断服务程序
void TIM3_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
		{
			LED3=!LED3;
			
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx更新中断标志 
		
		}
}
























