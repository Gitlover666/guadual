#ifndef __BH1750_H
#define __BH1750_H


#include "sys.h"

void Single_Write_BH1750(unsigned char Reg_Address);
void BH1750_Init(void);
void BH1750_ReadOneTime(void);
u16 BH1750_ReadContinuous1(void);
void BH1750_ReadContinuous2(void);
void BH1750_Multiple_Read(void);
void Conversion(void);


#endif


