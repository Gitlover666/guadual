#include "BH1750.h"
#include "delay.h"
#include "sys.h"
#include "stm32f10x.h"
#include "stdint.h"

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
    IIC_Send_Byte(0x47);
    IIC_Wait_Ack1();
    temp=IIC_Read_Byte(1);
    temp1=IIC_Read_Byte(0);
    IIC_Stop1();
    temp2=temp1+(temp<<8);
    lux=temp2;
    return lux;
}

/****方法二：****/
void  BH1750_ReadContinuous2(void)
{
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

    IIC_Stop1();

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

void IIC_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10|GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;  //推挽输出

    GPIO_Init(GPIOB,&GPIO_InitStructure);
    GPIO_SetBits(GPIOB,GPIO_Pin_10|GPIO_Pin_11);   //将总线拉高释放总线
}

/***总线初始化:将总线拉高释放总线，发送启动信号前，要先初始化总线
         即总线检测到总线空闲才开始发送启动信号****/

void IIC_Start1(void)
{
    SDA_OUT()       //设置SDA线为输出
    //在开始数据传输前，先让SDA和SCL都拉高
    IIC_SDA=1;    //发送起始条件的数据信号，释放总线
    delay_us(2);
    IIC_SCL=1;
    delay_us(5);   //Tsu;STA：起始条件的建立时间大于4.7us。
    IIC_SDA=0;    //SDA由高变为低表示开始信号
    delay_us(4);   //起始条件的保持时间大于4us
    IIC_SCL=0;    //钳住IIC总线，准备发送或者接收数据
    delay_us(2);
}

/***停止信号***/
void IIC_Stop1(void)
{
    SDA_OUT()       //设置SDA线为输出
    IIC_SDA=0;   //发送停止信号的数据信号
    delay_us(2);
    IIC_SCL=1;   //发送停止信号的时钟信号
    delay_us(5);  //停止信号的建立时间大于4us
    IIC_SDA=1;   //发送停止信号
    delay_us(4);    //
}

/****等待应答信号到来****/
/*从器件进行应答信号
返回值：1 接收应答失败
         0  接收应答成功
注意;此函数的返回值不会对下面的语句才生影响
*/
u8 IIC_Wait_Ack1(void)
{
    u8 ucErrorTime=0;
    SDA_IN();     //SDA设置成输入
    IIC_SDA=1;
    delay_us(2);
    IIC_SCL=1;
    delay_us(2);
    while(READ_SDA)
    {
        ucErrorTime++;
        if(ucErrorTime>=250)
        {
            IIC_Stop1();
            return 1;
        }
    }
    IIC_SCL=0;
    return 0;
}

/****产生Ack应答****/
/****
       主器件进行应答信号，产生应答
****/
void IIC_Ack(void)
{
    IIC_SCL=0;
    SDA_OUT();
    IIC_SDA=0;   //主器件应答
    delay_us(2);
    IIC_SCL=1;
    delay_us(4);        //SCL高电平周期大于4us
    IIC_SCL=0;         //清时钟线，钳住IIC总线以便继续接收
    delay_us(2);
}
/****不产生Ack应答****/
/****
       主器件进行应答信号，不产生应答
****/
void IIC_NAck(void)
{
    IIC_SCL=0;
    SDA_OUT();
    IIC_SDA=1;   //主器件不应答
    delay_us(2);
    IIC_SCL=1;
    delay_us(4);        //SCL高电平周期大于4us
    IIC_SCL=0;         //清时钟线，钳住IIC总线以便继续接收
    delay_us(2);
}


/****发送一个字节****/
/****
功能:将数据c发送出去，可以是地址，也可以是数据，发送完后等待应答，
****/
void IIC_Send_Byte(unsigned char c)  //要传送的数据长度为8位
{
    u8 i;
    SDA_OUT();

    for(i=0; i<8; i++)
    {
        if((c<<i)&0x80)   //判断发送位
				IIC_SDA=1;   
        else IIC_SDA=0;

        delay_us(2);
        IIC_SCL=1;     //拉高SCL，通知被控器开始接收数据位
        delay_us(4);   //保证SCL高电平周期大于4us
        IIC_SCL=0;    //拉低SCL，允许SDA传输下一位数据。因为只有在SCL=0时才允许SDA的状态发生变化
        delay_us(2);
    }
    IIC_SCL=0;      //拉低SCL，为下次数据传输做好准备
    delay_us(2);
}

/***接收一个字节***/
/***
功能:用来接收从器件传来的数据，ack为1时，发送Ack(产生应答);ack为0时，发送NAck(不产生应答)
注意：IIC读写数据时，高位在前，低位在后
***/
u8 IIC_Read_Byte(unsigned char ack)
{
    unsigned char i,receive=0;
    SDA_IN();
    for(i=0; i<8; i++)
    {
        IIC_SCL=0;    //置SCL为低，准备接收数据位
        delay_us(5);  //时钟低电平周期大于4.7us
        IIC_SCL=1;   //置SCL为高，使SDA上数据有效
        delay_us(2);
        receive=receive<<1;
        if(READ_SDA) receive=receive+1;    //读取SDA，把接收的数据位放入receve中，若此处写成IIC_SDA==1，会失败，思考原因？
        delay_us(2);
    }
    if(!ack) IIC_NAck();   //发送NAck
    else IIC_Ack();    //发送Ack
    return receive;

}



