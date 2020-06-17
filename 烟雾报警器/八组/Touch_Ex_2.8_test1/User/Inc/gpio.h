#ifndef __GPIO_H__
#define __GPIO_H__

#include <stm32f10x.h>
#include <stm32f10x_conf.h>  

/* ����ֵ�궨�� */
#define UP      1
#define RIGHT   2
#define DOWN    3
#define LEFT    4
#define NULL    0    /* û�а������� */

void Led_Init(void);
void Beep_Init(void);
void Key_Init(void);
u8 Key_Scan(void);


#endif















