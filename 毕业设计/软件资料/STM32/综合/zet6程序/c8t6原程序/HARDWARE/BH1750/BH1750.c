#include "BH1750.h"
#include "delay.h"
#include "sys.h"
#include "stm32f10x.h"
#include "stdint.h"

u8 BUF[8];
u16 temp2=0;
static u32 lux=0;

/****��BH1750����д����****/
void Single_Write_BH1750(unsigned char Reg_Address)
{
    IIC_Start1();
    IIC_Send_Byte(0x46);  //����������ַ0100 0110   ���һλ0����ʾд
    //IIC_Wait_Ack1();
    IIC_Send_Byte(Reg_Address);
    //IIC_Wait_Ack1();
    IIC_Stop1();
}


/****BH1750��ʼ��****/
void BH1750_Init(void)
{
    IIC_Config();
    Single_Write_BH1750(0x01);

}


/****��BH1750���ζ�Lux****/
/****
ģʽѡ��H-Resolution Mode,�ֱ���1lux
���ζ�Opecode��0010 0000 ����0x20
������ַ��0100011��ADDR��GND
****/
void BH1750_ReadOneTime(void)
{
    IIC_Start1();
    IIC_Send_Byte(0x46);  //����������ַ0100 0110   ���һλ0����ʾд
    IIC_Wait_Ack1();
    IIC_Send_Byte(0x20);   //����One time H-Resolution Mode��Opecode 0010 0000���ֱ���Ϊ1lux
    IIC_Wait_Ack1();
    IIC_Stop1();
    delay_ms(200);
    IIC_Start1();
    IIC_Send_Byte(0x47);  //
    IIC_Wait_Ack1();
    BUF[0]=IIC_Read_Byte(1);
    //IIC_Ack();        //����Ӧ��
    //temp1=temp<<8;
    BUF[1]=IIC_Read_Byte(0);
    //IIC_NAck();        //������Ӧ��
    IIC_Stop1();
// 	temp2=BUF[0];
// 	temp2=(temp2<<8)+BUF[1];
// 	lux=(float)temp2/1.2;    //lux��float��

    //return lux;
    //delay_ms(200);
}

/****����һ��****/
/****��BH1750������Lux****/
/****
ģʽѡ��H-Resolution Mode,�ֱ���1lux
������Opecode��0001 0000
������ַ��0100011��ADDR��GND
****/
u16  BH1750_ReadContinuous1(void)
{
    u16 temp=0,temp1=0;


    IIC_Start1();
    IIC_Send_Byte(0x46);  //����������ַ0100 0110   ���һλ0����ʾд
    IIC_Wait_Ack1();
    IIC_Send_Byte(0x10);  //����Continuous H-Resolution Mode��Opecode 0001 0000���ֱ���Ϊ1lux
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

/****��������****/
void  BH1750_ReadContinuous2(void)
{
    IIC_Start1();
    IIC_Send_Byte(0x46);  //����������ַ0100 0110   ���һλ0����ʾд
    IIC_Wait_Ack1();
    IIC_Send_Byte(0x10);  //����Continuous H-Resolution Mode��Opecode 0001 0000���ֱ���Ϊ1lux
    IIC_Wait_Ack1();
    IIC_Stop1();
    delay_ms(200);
    IIC_Start1();
    IIC_Send_Byte(0x47);  //�˴�����ʧ��д����IIC_Read_Byte,�뵱Ȼ����Ϊ���һλ��1����Ӧ����IIC_Read_Byte���ر�ע�⣡����
    IIC_Wait_Ack1();

    BUF[0]=IIC_Read_Byte(1);
    BUF[1]=IIC_Read_Byte(0);

    IIC_Stop1();

}

/****������****/
/****
���ú���BH1750_Multiple_Read()���ж�
����Conversion(void)��������ת��
****/
void BH1750_Multiple_Read(void)
{
    IIC_Start1();
    IIC_Send_Byte(0x47);  //�˴�����ʧ��д����IIC_Read_Byte,�뵱Ȼ����Ϊ���һλ��1����Ӧ����IIC_Read_Byte���ر�ע�⣡����

    BUF[0]=IIC_Read_Byte(1);
    BUF[1]=IIC_Read_Byte(0);
    IIC_Stop1();                          //ֹͣ�ź�
    delay_us(5);
    delay_ms(200);
}


void Conversion(void)
{
    temp2=BUF[0];
    temp2=(temp2<<8)+BUF[1];
    lux=(float)temp2/1.2;    //lux��float��

}

void IIC_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10|GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;  //�������

    GPIO_Init(GPIOB,&GPIO_InitStructure);
    GPIO_SetBits(GPIOB,GPIO_Pin_10|GPIO_Pin_11);   //�����������ͷ�����
}

/***���߳�ʼ��:�����������ͷ����ߣ����������ź�ǰ��Ҫ�ȳ�ʼ������
         �����߼�⵽���߿��вſ�ʼ���������ź�****/

void IIC_Start1(void)
{
    SDA_OUT()       //����SDA��Ϊ���
    //�ڿ�ʼ���ݴ���ǰ������SDA��SCL������
    IIC_SDA=1;    //������ʼ�����������źţ��ͷ�����
    delay_us(2);
    IIC_SCL=1;
    delay_us(5);   //Tsu;STA����ʼ�����Ľ���ʱ�����4.7us��
    IIC_SDA=0;    //SDA�ɸ߱�Ϊ�ͱ�ʾ��ʼ�ź�
    delay_us(4);   //��ʼ�����ı���ʱ�����4us
    IIC_SCL=0;    //ǯסIIC���ߣ�׼�����ͻ��߽�������
    delay_us(2);
}

/***ֹͣ�ź�***/
void IIC_Stop1(void)
{
    SDA_OUT()       //����SDA��Ϊ���
    IIC_SDA=0;   //����ֹͣ�źŵ������ź�
    delay_us(2);
    IIC_SCL=1;   //����ֹͣ�źŵ�ʱ���ź�
    delay_us(5);  //ֹͣ�źŵĽ���ʱ�����4us
    IIC_SDA=1;   //����ֹͣ�ź�
    delay_us(4);    //
}

/****�ȴ�Ӧ���źŵ���****/
/*����������Ӧ���ź�
����ֵ��1 ����Ӧ��ʧ��
         0  ����Ӧ��ɹ�
ע��;�˺����ķ���ֵ����������������Ӱ��
*/
u8 IIC_Wait_Ack1(void)
{
    u8 ucErrorTime=0;
    SDA_IN();     //SDA���ó�����
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

/****����AckӦ��****/
/****
       ����������Ӧ���źţ�����Ӧ��
****/
void IIC_Ack(void)
{
    IIC_SCL=0;
    SDA_OUT();
    IIC_SDA=0;   //������Ӧ��
    delay_us(2);
    IIC_SCL=1;
    delay_us(4);        //SCL�ߵ�ƽ���ڴ���4us
    IIC_SCL=0;         //��ʱ���ߣ�ǯסIIC�����Ա��������
    delay_us(2);
}
/****������AckӦ��****/
/****
       ����������Ӧ���źţ�������Ӧ��
****/
void IIC_NAck(void)
{
    IIC_SCL=0;
    SDA_OUT();
    IIC_SDA=1;   //��������Ӧ��
    delay_us(2);
    IIC_SCL=1;
    delay_us(4);        //SCL�ߵ�ƽ���ڴ���4us
    IIC_SCL=0;         //��ʱ���ߣ�ǯסIIC�����Ա��������
    delay_us(2);
}


/****����һ���ֽ�****/
/****
����:������c���ͳ�ȥ�������ǵ�ַ��Ҳ���������ݣ��������ȴ�Ӧ��
****/
void IIC_Send_Byte(unsigned char c)  //Ҫ���͵����ݳ���Ϊ8λ
{
    u8 i;
    SDA_OUT();

    for(i=0; i<8; i++)
    {
        if((c<<i)&0x80)   //�жϷ���λ
				IIC_SDA=1;   
        else IIC_SDA=0;

        delay_us(2);
        IIC_SCL=1;     //����SCL��֪ͨ��������ʼ��������λ
        delay_us(4);   //��֤SCL�ߵ�ƽ���ڴ���4us
        IIC_SCL=0;    //����SCL������SDA������һλ���ݡ���Ϊֻ����SCL=0ʱ������SDA��״̬�����仯
        delay_us(2);
    }
    IIC_SCL=0;      //����SCL��Ϊ�´����ݴ�������׼��
    delay_us(2);
}

/***����һ���ֽ�***/
/***
����:�������մ��������������ݣ�ackΪ1ʱ������Ack(����Ӧ��);ackΪ0ʱ������NAck(������Ӧ��)
ע�⣺IIC��д����ʱ����λ��ǰ����λ�ں�
***/
u8 IIC_Read_Byte(unsigned char ack)
{
    unsigned char i,receive=0;
    SDA_IN();
    for(i=0; i<8; i++)
    {
        IIC_SCL=0;    //��SCLΪ�ͣ�׼����������λ
        delay_us(5);  //ʱ�ӵ͵�ƽ���ڴ���4.7us
        IIC_SCL=1;   //��SCLΪ�ߣ�ʹSDA��������Ч
        delay_us(2);
        receive=receive<<1;
        if(READ_SDA) receive=receive+1;    //��ȡSDA���ѽ��յ�����λ����receve�У����˴�д��IIC_SDA==1����ʧ�ܣ�˼��ԭ��
        delay_us(2);
    }
    if(!ack) IIC_NAck();   //����NAck
    else IIC_Ack();    //����Ack
    return receive;

}



