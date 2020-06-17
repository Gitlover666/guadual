#include "gpio.h"

/**************************** LED灯初始化函数 ****************************
功  能：初始化LED灯对应的硬件驱动端口
参  数：无
返回值：无
硬件连接方式：
LED1(D3) --- PB5 --- 推挽输出 ---- 低电平亮，高电平灭
LED2(D4) --- PE5 --- 推挽输出 ---- 低电平亮，高电平灭
LED3(D5) --- PA5 --- 推挽输出 ---- 低电平亮，高电平灭
LED4(D6) --- PA6 --- 推挽输出 ---- 低电平亮，高电平灭
***************************************************************************/
void Led_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;   /* 定义一个结构体类型变量 */
	
	/* 开启GPIO端口模块的时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOE |
	                       RCC_APB2Periph_GPIOA,ENABLE);  //使能GPIOB、GPIOE、GPIOBA时钟
	
	/* LED1(D3) --- PB5 */
	/* 设置GPIO端口工作模式 */
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_5;             //使用端口编号5
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;       //输出速度50M
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;       //推挽输出功能
	/* 初始化GPIO端口 */
	GPIO_Init(GPIOB, &GPIO_InitStructure);                  //初始化GPIOB组
	/* 初始化输出状态 */
	GPIO_SetBits(GPIOB,GPIO_Pin_5);                        //GPIOB.5初始化输出高电平
	
	/* LED2(D4) --- PE5 */
	/* 初始化GPIO端口 */
	GPIO_Init(GPIOE, &GPIO_InitStructure);                  //初始化GPIOE组
	/* 初始化输出状态 */
	GPIO_SetBits(GPIOE,GPIO_Pin_5);                         //GPIOE.5初始化输出高电平
	
	/* LED3(D5) --- PA5 LED4(D6) --- PA6 */
	/* 设置GPIO端口工作模式 */
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_5 | GPIO_Pin_6; //使用端口编号5和6
	/* 初始化GPIO端口 */
	GPIO_Init(GPIOA, &GPIO_InitStructure);                   //初始化GPIOB组
	/* 初始化输出状态 */
	GPIO_SetBits(GPIOA,(GPIO_Pin_5 | GPIO_Pin_6));           //GPIOA.5和GPIOA.6初始化输出高电平      	
}

/**************************** 蜂鸣器初始化函数 ****************************
功  能：初始化蜂鸣器对应的硬件驱动端口
参  数：无
返回值：无
硬件连接方式：
Beep --- PB8 --- 推挽输出 ---- 高电平响，低电平不响
***************************************************************************/
void Beep_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;   /* 定义一个结构体类型变量 */
	
	/* 开启GPIO端口模块的时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);    //使能GPIOB时钟
	
	/* 设置GPIO端口工作模式 */
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_8;             //使用端口编号8
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;       //输出速度50M
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;       //推挽输出功能
	
	/* 初始化GPIO端口 */
	GPIO_Init(GPIOB, &GPIO_InitStructure);                  //初始化GPIOB组
	
	/* 初始化输出状态 */
	GPIO_ResetBits(GPIOB,GPIO_Pin_8);                       //GPIOB.8初始化输出低电平
}

/**************************** 按键初始化函数 ****************************
功  能：初始化按键对应的硬件驱动端口
参  数：无
返回值：无
硬件连接方式：
UP键     --- PA0 --- 上拉输入 --- 按键按下获取低电平
RIGHT键  --- PE4 --- 上拉输入 --- 按键按下获取低电平
DOWN键   --- PE3 --- 上拉输入 --- 按键按下获取低电平
LEFT键   --- PE2 --- 下拉输入 --- 按键按下获取高电平
***************************************************************************/
void Key_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;   /* 定义一个结构体类型变量 */
	
	/* 开启GPIO端口模块的时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOE,ENABLE);    //使能GPIOA、GPIOE时钟
	
	/* UP键(PA0) */
	/* 设置GPIO端口工作模式 */
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0;             //使用端口编号0
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;          //上拉输入模式 
	/* 初始化GPIO端口 */
	GPIO_Init(GPIOA, &GPIO_InitStructure);                  //初始化GPIOA组
	
	/* RIGHT键(PE4)、DOWN键(PE3) */
	/* 设置GPIO端口工作模式 */
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_4 |GPIO_Pin_3; //使用端口编号4和端口3
	/* 初始化GPIO端口 */
	GPIO_Init(GPIOE, &GPIO_InitStructure);                  //初始化GPIOE组
	
	/* LEFT键(PE2) */
	/* 设置GPIO端口工作模式 */
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2;             //使用端口编号2
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPD;          //下拉输入模式 
	/* 初始化GPIO端口 */
	GPIO_Init(GPIOE, &GPIO_InitStructure);                  //初始化GPIOE组
}

/**************************** 按键初始化函数 ****************************
功  能：对按键进行扫描
参  数：无
返回值：返回有效的按键值
按键消抖方式：对比消抖
通过连续读出多个（3～5个）按键的状态值，然后对比判断这几个按键状态值是否一致，
如果一致，则证明按键值有效
*************************************************************************/
u8 Key_Scan(void)
{
	u8 Key_Val = 0xff;                     //按键有效值保存变量
	static u8 Key_Sta = 1;                 //松手检测标志，1：允许按键操作，0：禁止按键操作
	static u8 Key_1,Key_2,Key_3,time = 0;  //按键读取次数以及按键值保存变量
	
	/* 按键值传递 */
	Key_3 = Key_2;
	Key_2 = Key_1;
	time++;
	
	/* 判断是否允许按键识别并且有按键按下 */
	if((Key_Sta == 1 ) &&  ( (!(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0))) || (!(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4))
		 || (!(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3))) || (GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2))) ))
	{
		if( (!(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0))) )          //UP键被按下
		{
			Key_1 = UP;           //保存按键值
		}
		else if( (!(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4))) )     //RIGHT键被按下
		{
			Key_1 = RIGHT;         //保存按键值
		}
		else if( (!(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3))) )     //DOWN键被按下
		{
			Key_1 = DOWN;         //保存按键值
		}
		else if( (GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)) )        //LEFT键被按下
		{
			Key_1 = LEFT;         //保存按键值
		}
		if(time == 3)             //判断读取次数是否达到3次
		{
			time = 0;             //读取次数清零
			if( (Key_1 == Key_2) && (Key_2 == Key_3) )    //判断3次读出的按键值是否一致
			{
				Key_Val = Key_1;  //保存按键有效值
				Key_Sta = 0;      //不允许按键识别
			}
		}
	}
	/* 按键没有按下 */
	else if( GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) || GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)
		 ||  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3) || (!(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2))) )
	{
		Key_Sta = 1;           //允许按键识别
		time = 0;              //读取次数清零
	}
	
	return 	Key_Val;           //返回有效按键值
}















