/****

本模拟IIC软件包包含了IIC操作的底层函数，如发送数据、接收数据、应答位发送。
                                                                            ------更新时间2018.2.23
调试经历：
仿照原始程序修改完后，进行测试，但是printf("\r\n%s",datatemp);就是不输出任何东西
后来，与例程比较后，发现在进行IIC_Config()中，是对GPIOA进行的初始化，不是GPIOB，但是为什么
软件没有报错呢？这种失误软件是检查不出来的，因为其语法并没有问题，需要自己认真检查。
****/
#include "IIC.h"
#include "stm32f10x_gpio.h"
#include "delay.h"

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

// void IIC_Init(void)
// {
// 	IIC_SDA=1;
// 	IIC_SCL=1;
// }

/***起始信号***/
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

    //IIC_SCL=0;    //此句是调试BH1750时加，2020.03.03

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
        if((c<<i)&0x80)  IIC_SDA=1;   //判断发送位
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
    //IIC_SCL=0;      //在此处有何用处？？？(猜测：为下次数据传输做好准备， //钳住IIC总线，准备发送或者接收数据)
    //delay_us(2);
    return receive;

}


