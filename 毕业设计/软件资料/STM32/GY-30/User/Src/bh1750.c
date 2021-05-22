#include "bh1750.h"
#include "systick.h"

/************* BH1750дָ��� ****************/
void BH1750_Write_Com(u8 Dev_Adder, u8 Common)
{
	IIC_Start();               //����һ����ʼ�ź�
	IIC_Write_Byte(Dev_Adder); //���Ϳ����ֽ�
	if( IIC_Get_ACK() )        //���Ӧ��
	{
		goto WR_End;             
	}
	IIC_Write_Byte(Common);    //���Ϳ�������
	if( IIC_Get_ACK() )        //���Ӧ��
	{
		goto WR_End;
	}
WR_End:
	IIC_Stop();                //���������ź�
}

/************* BH1750�����ݺ��� ****************/
u16 BH1750_Read_Date(u8 Dev_Adder)
{
	u8 Buff[2] = {0};
	u16 Data = 0;
	
	IIC_Start();                      //����һ����ʼ�ź�
	IIC_Write_Byte(Dev_Adder | 0x01); //���Ϳ����ֽ�
	if( IIC_Get_ACK() )               //���Ӧ��
	{
		goto WR_End;             
	}
	/* ��ȡ��ǿ���� */
	Buff[0] = IIC_Read_Byte();        //��ȡ��ǿ���ݸ�8λ
	IIC_Send_ACK();                   //����һ��Ӧ���ź�
	Buff[1] = IIC_Read_Byte();        //��ȡ��ǿ���ݵ�8λ
	IIC_Send_NoACK();                 //����һ����Ӧ���ź�
WR_End:
	IIC_Stop();                       //���������ź�	
	Delay_ms(5);
	
	/* �ϲ���ǿ���� */
	Data = Buff[0];
	Data = (Data << 8) | Buff[1];     //�ϳ�����
	
	return Data;
}

/************* BH1750��ʼ������ ****************/
void BH1750_Init(void)
{
	IIC_GPIO_Init();
	BH1750_Write_Com(SlaveAdder,0x01);    //����Դ
	BH1750_Write_Com(SlaveAdder,0x10);    //�����߷ֱ��ʲ���ģʽ
	Delay_ms(180);                        //�ȴ���������
}

























