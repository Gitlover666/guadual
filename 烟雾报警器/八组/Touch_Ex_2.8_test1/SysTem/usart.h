#ifndef __USART_H__
#define __USART_H__

#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "stdio.h"

void USART_1_Init(u32 Boand);
void Usart_Send_Str(char *Str);
char Usart_Rec_Byte(void);

#endif

