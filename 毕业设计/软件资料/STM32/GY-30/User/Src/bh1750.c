#include "bh1750.h"
#include "systick.h"

/************* BH1750写指令函数 ****************/
void BH1750_Write_Com(u8 Dev_Adder, u8 Common)
{
	IIC_Start();               //产生一个起始信号
	IIC_Write_Byte(Dev_Adder); //发送控制字节
	if( IIC_Get_ACK() )        //检测应答
	{
		goto WR_End;             
	}
	IIC_Write_Byte(Common);    //发送控制命令
	if( IIC_Get_ACK() )        //检测应答
	{
		goto WR_End;
	}
WR_End:
	IIC_Stop();                //产生结束信号
}

/************* BH1750读数据函数 ****************/
u16 BH1750_Read_Date(u8 Dev_Adder)
{
	u8 Buff[2] = {0};
	u16 Data = 0;
	
	IIC_Start();                      //产生一个起始信号
	IIC_Write_Byte(Dev_Adder | 0x01); //发送控制字节
	if( IIC_Get_ACK() )               //检测应答
	{
		goto WR_End;             
	}
	/* 读取光强数据 */
	Buff[0] = IIC_Read_Byte();        //读取光强数据高8位
	IIC_Send_ACK();                   //发送一个应答信号
	Buff[1] = IIC_Read_Byte();        //读取光强数据低8位
	IIC_Send_NoACK();                 //发送一个非应答信号
WR_End:
	IIC_Stop();                       //产生结束信号	
	Delay_ms(5);
	
	/* 合并光强数据 */
	Data = Buff[0];
	Data = (Data << 8) | Buff[1];     //合成数据
	
	return Data;
}

/************* BH1750初始化函数 ****************/
void BH1750_Init(void)
{
	IIC_GPIO_Init();
	BH1750_Write_Com(SlaveAdder,0x01);    //开电源
	BH1750_Write_Com(SlaveAdder,0x10);    //连续高分辨率测量模式
	Delay_ms(180);                        //等待启动测量
}

























