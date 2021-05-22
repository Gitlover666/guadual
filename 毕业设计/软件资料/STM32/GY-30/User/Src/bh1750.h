#ifndef __BH1750_H__
#define __BH1750_H__


#include <stm32f10x.h> 
#include "iic.h"

/*
����������IIC�����еĴӵ�ַ������ADD�ܽŽӷ���ͬ�޸�
ADD�ܽŽӵ�Ϊ0100 0110(0x46),�ӵ�Դʱ��ַΪ1011 1000(0xB8)
*/

#define SlaveAdder 0x46

void BH1750_Write_Com(u8 Dev_Adder, u8 Common);
u16 BH1750_Read_Date(u8 Dev_Adder);
void BH1750_Init(void);

#endif
