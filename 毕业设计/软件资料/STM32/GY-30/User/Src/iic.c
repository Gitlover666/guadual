#include "iic.h"
#include "systick.h"

/************ IIC管脚初始化函数 ******************/
void IIC_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/* 使能GPIO端口时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	/* IIC空闲状态 */
	SCL_H();
	SDA_H();
}

/************ IIC起始信号函数 ******************/
void IIC_Start(void)
{
	SCL_L();     //拉低SCL，允许SDA改变
	SDA_H();     //拉高SDA，为下降沿做准备
	SCL_H();     //拉高SCL
	Delay_us(5); //延时，拉高SCL后至少4.7us才能拉低SDA  
	SDA_L();     //拉低SDA，下降沿产生起始信号
	Delay_us(4); //起始信号保存时间为4us
	SCL_L();
}

/************ IIC结束信号函数 ******************/
void IIC_Stop(void)
{
	SCL_L();      //拉低SCL，允许SDA改变
	SDA_L();      //拉低SDA，为上升沿做准备
	SCL_H();      //拉高SCL
	Delay_us(4);  //延时，拉高SCL后至少4us才能拉高SDA  
	SDA_H();      //拉高SDA，上升沿产生结束信号
	Delay_us(5);  //结束后只要保存4.7us才能下一个开始
}

/************ IIC发送应答函数 ******************/
void IIC_Send_ACK(void)
{
	SCL_L();      //拉低SCL，允许SDA改变
	SDA_L();      //拉低SDA，产生应答信号
	Delay_us(5);  //延时，保证SCL低电平脉冲宽度4.7us
	SCL_H();      //拉高SCL，SCL高电平期间，SDA低电平表示应答信号
	Delay_us(4);  //延时，保证SCL高电平脉冲宽度4us
	SCL_L();
}

/************ IIC发送应答函数 ******************/
void IIC_Send_NoACK(void)
{
	SCL_L();      //拉低SCL，允许SDA改变
	SDA_H();      //拉高SDA，产生非应答信号
	Delay_us(5);  //延时，保证SCL低电平脉冲宽度4.7us
	SCL_H();      //拉高SCL，SCL高电平期间，SDA低电平表示应答信号
	Delay_us(4);  //延时，保证SCL高电平脉冲宽度4us
	SCL_L();
}

/************ IIC检测应答函数 *****************
1：检测到非应答信号，0：检测到应答信号
**********************************************/
u8 IIC_Get_ACK(void)
{
	u8 ErrorTimer = 0;
	
	/* 释放总线 */
	SCL_L();      //拉低SCL，允许SDA改变
	SDA_H();
	Delay_us(5);  //延时，保证SCL低电平脉冲宽度4.7us
	
	SCL_H();      
	while( READ_SDA() )
	{
		ErrorTimer++;
		if(ErrorTimer >= 250)
		{
			IIC_Stop();
			return 1; //检测到非应答信号，返回1
		}
	}
	Delay_us(4);  //延时，保证SCL高电平脉冲宽度4us
	SCL_L();
	return 0;     //检测到应答信号，返回0
}

/************ IIC写字节函数 ******************/
void IIC_Write_Byte(u8 Data)
{
	u8 i;
	
	for(i = 0; i < 8; i++)
	{
		SCL_L();          //拉低SCL，允许SDA改变
		if(Data & 0x80)   //判断需要发送的数据位是0还是1，先发高位
		{
			SDA_H();        //拉高SDA表示数据“1”
		}
		else
		{
			SDA_L();        //拉低SDA表示数据“0”
		}
		Delay_us(5);      //延时，保证SCL低电平脉冲宽度4.7us
		SCL_H();          //拉高SCL，传输数据
		Delay_us(4);      //延时，保证SCL高电平脉冲宽度4us
		Data <<= 1;       //把数据的次高位移成最高位
	}
}

/************ IIC读字节函数 ******************/
u8 IIC_Read_Byte(void)
{
	u8 Date = 0;
	u8 i;
	
	/* 释放总线 */
	SCL_L();
	SDA_H();
	
	for(i = 0; i < 8; i++)
	{
		Date <<= 1;       //读取8位数据只需要移动7次，所以需要空移一次
		SCL_L();          //拉低SCL，允许SDA改变
		Delay_us(5);      //延时，保证SCL低电平脉冲宽度4.7us
		SCL_H();          //拉高SCL，传输数据
		if( READ_SDA() )
		{
			Date |= 0x01;
		}
		
	}
	
	return Date;
}














