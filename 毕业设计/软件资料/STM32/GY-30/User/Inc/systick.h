#ifndef __SYSTICK_H__
#define __SYSTICK_H__


#include "stm32f10x.h"

void Delay_Init(u8 SYSCLK);
void Delay_us (u32 nus);
void Delay_ms (u16 nms);

#endif

