#ifndef __TOUCH_H__
#define	__TOUCH_H__

#include <stm32f10x.h>

typedef struct
{
	/* 触摸屏坐标值 */
	u16 x;
	u16 y;
	
	/* 触摸屏比例系数、偏移量*/
	float kx;        //比例系数
	float ky;
	s16 offset_x;    //偏移量
	s16 offset_y;
	
}TOUCH_TYPE_DEF;


/* 函数声明 */
void Touch_Gpio_Init(void);
void Touch_Adj_Init(void);
u16 Touch_Get_ADC(u8 common);
TOUCH_TYPE_DEF Touch_Get_XY(void);
TOUCH_TYPE_DEF Touch_Lcd(void);
TOUCH_TYPE_DEF Touch_Scanf(void);
TOUCH_TYPE_DEF Get_Touch_Lcd_XY(void);
void Touch_Init(void);
u8 Touch_Get_Mainkeynum(void);

/* 外部变量声明 */
extern TOUCH_TYPE_DEF TOUCH_LCD;

#endif

