/****

��ģ��IIC�����������IIC�����ĵײ㺯�����緢�����ݡ��������ݡ�Ӧ��λ���͡�
                                                                            ------����ʱ��2018.2.23
���Ծ�����
����ԭʼ�����޸���󣬽��в��ԣ�����printf("\r\n%s",datatemp);���ǲ�����κζ���
�����������̱ȽϺ󣬷����ڽ���IIC_Config()�У��Ƕ�GPIOA���еĳ�ʼ��������GPIOB������Ϊʲô
���û�б����أ�����ʧ������Ǽ�鲻�����ģ���Ϊ���﷨��û�����⣬��Ҫ�Լ������顣
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
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;  //�������

    GPIO_Init(GPIOB,&GPIO_InitStructure);
    GPIO_SetBits(GPIOB,GPIO_Pin_10|GPIO_Pin_11);   //�����������ͷ�����

}

/***���߳�ʼ��:�����������ͷ����ߣ����������ź�ǰ��Ҫ�ȳ�ʼ������
         �����߼�⵽���߿��вſ�ʼ���������ź�****/

// void IIC_Init(void)
// {
// 	IIC_SDA=1;
// 	IIC_SCL=1;
// }

/***��ʼ�ź�***/
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

    //IIC_SCL=0;    //�˾��ǵ���BH1750ʱ�ӣ�2020.03.03

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
        if((c<<i)&0x80)  IIC_SDA=1;   //�жϷ���λ
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
    //IIC_SCL=0;      //�ڴ˴��к��ô�������(�²⣺Ϊ�´����ݴ�������׼���� //ǯסIIC���ߣ�׼�����ͻ��߽�������)
    //delay_us(2);
    return receive;

}


