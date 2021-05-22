#ifndef __USART_H__
#define __USART_H__


#include <stm32f10x.h> 
#include <stdio.h>

void Usart1_Init(u32 Pclk, u32 Bound);
void USART_Send_Str(u8 *dat);

#endif
