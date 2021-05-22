#ifndef __IIC_H__
#define __IIC_H__


#include <stm32f10x.h> 

/* SCL --- PB10  SDA --- PB11 */
#define SCL_H()   (GPIO_SetBits(GPIOB,GPIO_Pin_10))
#define SCL_L()   (GPIO_ResetBits(GPIOB,GPIO_Pin_10))

#define SDA_H()   (GPIO_SetBits(GPIOB,GPIO_Pin_11))
#define SDA_L()   (GPIO_ResetBits(GPIOB,GPIO_Pin_11))

#define READ_SDA() ((GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)) && 1)


void IIC_GPIO_Init(void);
void IIC_Start(void);
void IIC_Stop(void);
void IIC_Send_ACK(void);
void IIC_Send_NoACK(void);
u8 IIC_Get_ACK(void);
void IIC_Write_Byte(u8 Data);
u8 IIC_Read_Byte(void);


#endif













