#ifndef __ILI9341_H__
#define __ILI9341_H__

#include <stm32f10x.h>
#include "systick.h"
#include <stm32f10x_conf.h>  

void LCD_ILI9341_CMD(u16 common);
void LCD_ILI9341_Parameter(u16 data);
void LCD_Clear(u16 SX, u16 EX, u16 SY, u16 EY, u16 Color);
void LCD_Init(void);



#endif

