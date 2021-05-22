#ifndef __BH1750_H__
#define __BH1750_H__


#include <stm32f10x.h> 
#include "iic.h"

/*
定义器件在IIC总线中的从地址，根据ADD管脚接法不同修改
ADD管脚接地为0100 0110(0x46),接电源时地址为1011 1000(0xB8)
*/

#define SlaveAdder 0x46

void BH1750_Write_Com(u8 Dev_Adder, u8 Common);
u16 BH1750_Read_Date(u8 Dev_Adder);
void BH1750_Init(void);

#endif
