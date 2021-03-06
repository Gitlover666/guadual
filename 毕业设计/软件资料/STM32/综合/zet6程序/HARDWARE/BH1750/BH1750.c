#include "BH1750.h"
#include "delay.h"
#include "IIC.h"
#include "sys.h"
#include "stm32f10x.h"
#include <stdint.h>


u8 BUF[8];
u16 temp2=0;
static u32 lux=0;



/****向BH1750单次写命令****/
void Single_Write_BH1750(unsigned char Reg_Address)
{
	IIC_Start1();
	IIC_Send_Byte(0x46);  //发送器件地址0100 0110   最后一位0，表示写
	//IIC_Wait_Ack1();
	IIC_Send_Byte(Reg_Address);  
	//IIC_Wait_Ack1();
	IIC_Stop1();
}


/****BH1750初始化****/
void BH1750_Init(void)
{
	IIC_Config();
  Single_Write_BH1750(0x01);
	
}


/****从BH1750单次读Lux****/
/****
模式选择：H-Resolution Mode,分辨率1lux
单次读Opecode：0010 0000 ，即0x20
器件地址：0100011，ADDR接GND
****/
void BH1750_ReadOneTime(void)
{
	

	IIC_Start1();
	IIC_Send_Byte(0x46);  //发送器件地址0100 0110   最后一位0，表示写
	IIC_Wait_Ack1();
	IIC_Send_Byte(0x20);   //发送One time H-Resolution Mode的Opecode 0010 0000，分辨率为1lux
	IIC_Wait_Ack1();
	IIC_Stop1();
	delay_ms(200);
	IIC_Start1();
	IIC_Send_Byte(0x47);  //
	IIC_Wait_Ack1();
	BUF[0]=IIC_Read_Byte(1);
	//IIC_Ack();        //主机应答
	//temp1=temp<<8;
	BUF[1]=IIC_Read_Byte(0);
	//IIC_NAck();        //主机不应答	
	IIC_Stop1();
	
	
// 	temp2=BUF[0];
// 	temp2=(temp2<<8)+BUF[1];
// 	lux=(float)temp2/1.2;    //lux是float型
	
	//return lux;
	//delay_ms(200);
}

/****方法一：****/
/****从BH1750连续读Lux****/
/****
模式选择：H-Resolution Mode,分辨率1lux
连续读Opecode：0001 0000
器件地址：0100011，ADDR接GND
****/
u16  BH1750_ReadContinuous1(void)
{
	u16 temp=0,temp1=0;


	IIC_Start1();
  IIC_Send_Byte(0x46);  //发送器件地址0100 0110   最后一位0，表示写
	IIC_Wait_Ack1();
	IIC_Send_Byte(0x10);  //发送Continuous H-Resolution Mode的Opecode 0001 0000，分辨率为1lux
	IIC_Wait_Ack1();
	IIC_Stop1();
	delay_ms(200);
	IIC_Start1();
  IIC_Send_Byte(0x47);  //此处严重失误，写成了IIC_Read_Byte,想当然的认为最后一位是1，就应该用IIC_Read_Byte，特别注意！！！
	IIC_Wait_Ack1();
	
	
// 	BUF[0]=IIC_Read_Byte(1);
// 	BUF[1]=IIC_Read_Byte(0);	
	
	
	temp=IIC_Read_Byte(1);
	temp1=IIC_Read_Byte(0);


	IIC_Stop1();
	
	temp2=temp1+(temp<<8);
//	lux=temp2/1.2;    
  lux=temp2;
	return lux;


}


/****方法二：****/


void  BH1750_ReadContinuous2(void)
{
	//u16 temp=0,temp1=0;


	IIC_Start1();
  IIC_Send_Byte(0x46);  //发送器件地址0100 0110   最后一位0，表示写
	IIC_Wait_Ack1();
	IIC_Send_Byte(0x10);  //发送Continuous H-Resolution Mode的Opecode 0001 0000，分辨率为1lux
	IIC_Wait_Ack1();
	IIC_Stop1();
	delay_ms(200);
	IIC_Start1();
  IIC_Send_Byte(0x47);  //此处严重失误，写成了IIC_Read_Byte,想当然的认为最后一位是1，就应该用IIC_Read_Byte，特别注意！！！
	IIC_Wait_Ack1();
	
	
	BUF[0]=IIC_Read_Byte(1);
	BUF[1]=IIC_Read_Byte(0);	
	
	
// 	temp=IIC_Read_Byte(1);
// 	temp1=IIC_Read_Byte(0);

	IIC_Stop1();
	
// 	temp2=temp1+(temp<<8);
// 	lux=(float)temp2/1.2;    //lux是float型


}






/****方法三****/
/****
利用函数BH1750_Multiple_Read()进行读
利用Conversion(void)函数进行转换
****/
void BH1750_Multiple_Read(void)
{
	IIC_Start1();
  IIC_Send_Byte(0x47);  //此处严重失误，写成了IIC_Read_Byte,想当然的认为最后一位是1，就应该用IIC_Read_Byte，特别注意！！！

	BUF[0]=IIC_Read_Byte(1); 
	BUF[1]=IIC_Read_Byte(0); 	
	IIC_Stop1();                          //停止信号  
	delay_us(5);
	delay_ms(200);
}

void Conversion(void)
{
	temp2=BUF[0];
	temp2=(temp2<<8)+BUF[1];
	lux=(float)temp2/1.2;    //lux是float型
	
}





