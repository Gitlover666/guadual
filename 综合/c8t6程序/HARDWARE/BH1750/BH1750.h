#ifndef __BH1750_H
#define __BH1750_H

#include "sys.h"
//IO��������
#define IIC_SCL    PBout(10) //SCL
#define IIC_SDA    PBout(11) //SDA	 
#define READ_SDA   PBin(11)  //����SDA

//IO�������ã��������뻹���������˫��������
#define SDA_IN()  {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=8<<12;}
#define SDA_OUT() {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=3<<12;}

void IIC_Config(void);
void IIC_Init(void) ;
void IIC_Start1(void);  //��ʼ�ź�
void IIC_Stop1(void);  //ֹͣ�ź�
u8 IIC_Wait_Ack1(void);
void IIC_Ack(void);
void IIC_NAck(void);
void IIC_Send_Byte(unsigned char c);  //Ҫ���͵����ݳ���Ϊ8λ
u8 IIC_Read_Byte(unsigned char ack);
void Single_Write_BH1750(unsigned char Reg_Address);
void BH1750_Init(void);
void BH1750_ReadOneTime(void);
u16 BH1750_ReadContinuous1(void);
void BH1750_ReadContinuous2(void);
void BH1750_Multiple_Read(void);
void Conversion(void);

#endif


