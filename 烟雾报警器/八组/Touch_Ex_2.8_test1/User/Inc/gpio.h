#ifndef __GPIO_H__
#define __GPIO_H__

#include <stm32f10x.h>
#include <stm32f10x_conf.h>  

/* 按键值宏定义 */
#define UP      1
#define RIGHT   2
#define DOWN    3
#define LEFT    4
#define NULL    0    /* 没有按键按下 */

void Led_Init(void);
void Beep_Init(void);
void Key_Init(void);
u8 Key_Scan(void);


#endif















