#ifndef __USART_H
#define __USART_H
#include "sys.h"

void USART1_init(u32 baudrate);
void SendString(char * buf1);
void USART2_init(u32 baudrate);	
void SendString2(char * buf1);


#endif





