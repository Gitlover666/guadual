#include "iic.h"
#include "systick.h"

/************ IIC�ܽų�ʼ������ ******************/
void IIC_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/* ʹ��GPIO�˿�ʱ�� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	/* IIC����״̬ */
	SCL_H();
	SDA_H();
}

/************ IIC��ʼ�źź��� ******************/
void IIC_Start(void)
{
	SCL_L();     //����SCL������SDA�ı�
	SDA_H();     //����SDA��Ϊ�½�����׼��
	SCL_H();     //����SCL
	Delay_us(5); //��ʱ������SCL������4.7us��������SDA  
	SDA_L();     //����SDA���½��ز�����ʼ�ź�
	Delay_us(4); //��ʼ�źű���ʱ��Ϊ4us
	SCL_L();
}

/************ IIC�����źź��� ******************/
void IIC_Stop(void)
{
	SCL_L();      //����SCL������SDA�ı�
	SDA_L();      //����SDA��Ϊ��������׼��
	SCL_H();      //����SCL
	Delay_us(4);  //��ʱ������SCL������4us��������SDA  
	SDA_H();      //����SDA�������ز��������ź�
	Delay_us(5);  //������ֻҪ����4.7us������һ����ʼ
}

/************ IIC����Ӧ���� ******************/
void IIC_Send_ACK(void)
{
	SCL_L();      //����SCL������SDA�ı�
	SDA_L();      //����SDA������Ӧ���ź�
	Delay_us(5);  //��ʱ����֤SCL�͵�ƽ������4.7us
	SCL_H();      //����SCL��SCL�ߵ�ƽ�ڼ䣬SDA�͵�ƽ��ʾӦ���ź�
	Delay_us(4);  //��ʱ����֤SCL�ߵ�ƽ������4us
	SCL_L();
}

/************ IIC����Ӧ���� ******************/
void IIC_Send_NoACK(void)
{
	SCL_L();      //����SCL������SDA�ı�
	SDA_H();      //����SDA��������Ӧ���ź�
	Delay_us(5);  //��ʱ����֤SCL�͵�ƽ������4.7us
	SCL_H();      //����SCL��SCL�ߵ�ƽ�ڼ䣬SDA�͵�ƽ��ʾӦ���ź�
	Delay_us(4);  //��ʱ����֤SCL�ߵ�ƽ������4us
	SCL_L();
}

/************ IIC���Ӧ���� *****************
1����⵽��Ӧ���źţ�0����⵽Ӧ���ź�
**********************************************/
u8 IIC_Get_ACK(void)
{
	u8 ErrorTimer = 0;
	
	/* �ͷ����� */
	SCL_L();      //����SCL������SDA�ı�
	SDA_H();
	Delay_us(5);  //��ʱ����֤SCL�͵�ƽ������4.7us
	
	SCL_H();      
	while( READ_SDA() )
	{
		ErrorTimer++;
		if(ErrorTimer >= 250)
		{
			IIC_Stop();
			return 1; //��⵽��Ӧ���źţ�����1
		}
	}
	Delay_us(4);  //��ʱ����֤SCL�ߵ�ƽ������4us
	SCL_L();
	return 0;     //��⵽Ӧ���źţ�����0
}

/************ IICд�ֽں��� ******************/
void IIC_Write_Byte(u8 Data)
{
	u8 i;
	
	for(i = 0; i < 8; i++)
	{
		SCL_L();          //����SCL������SDA�ı�
		if(Data & 0x80)   //�ж���Ҫ���͵�����λ��0����1���ȷ���λ
		{
			SDA_H();        //����SDA��ʾ���ݡ�1��
		}
		else
		{
			SDA_L();        //����SDA��ʾ���ݡ�0��
		}
		Delay_us(5);      //��ʱ����֤SCL�͵�ƽ������4.7us
		SCL_H();          //����SCL����������
		Delay_us(4);      //��ʱ����֤SCL�ߵ�ƽ������4us
		Data <<= 1;       //�����ݵĴθ�λ�Ƴ����λ
	}
}

/************ IIC���ֽں��� ******************/
u8 IIC_Read_Byte(void)
{
	u8 Date = 0;
	u8 i;
	
	/* �ͷ����� */
	SCL_L();
	SDA_H();
	
	for(i = 0; i < 8; i++)
	{
		Date <<= 1;       //��ȡ8λ����ֻ��Ҫ�ƶ�7�Σ�������Ҫ����һ��
		SCL_L();          //����SCL������SDA�ı�
		Delay_us(5);      //��ʱ����֤SCL�͵�ƽ������4.7us
		SCL_H();          //����SCL����������
		if( READ_SDA() )
		{
			Date |= 0x01;
		}
		
	}
	
	return Date;
}














