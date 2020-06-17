#ifndef __LCD_GUI_H__
#define __LCD_GUI_H__

/* 需要根据使用的具体控制器型号以及主控芯片包含不同的头文件 */
#include "ili9341.h"
#include <stm32f10x.h>
//常用颜色值宏定义
#define COLOR_WHITE 0xFFFF
#define COLOR_RED   0xF800
#define COLOR_BLACK 0x0000
#define COLOR_GREEN 0x07E0
#define COLOR_BLUE  0x001F

/* 常用LCD_GUI函数 */
void LCD_Draw_Point(u16 xpos, u16 ypos, u16 Color);                                //画点函数  
void LCD_SetDrawBlock(u32 SX,u32 SY,u32 EX,u32 EY);                                //设置像素点坐标
void Draw_Big_Point(u16 x,u16 y,u16 color);                                        //画大点函数（2*2点）                    
void LCD_Dis_8x16Ascill(u16 Xpos,u16 Ypos,char str,u16 Pcolor,u16 Bcolor);         //8*16字符显示函数
void LCD_Dis_8x16string(u16 xpos,u16 ypos,const char *str,u16 pcolor,u16 bcolor);  //8*16字符串显示函数
void Show_Font(u16 x, u16 y, u8 *dzk, u8 size, u16 pcolor, u16 bcolor);            //显示任意大小汉字函数
void Show_Picture(u32 x,u32 y,u32 Pic_x,u32 Pic_y,const unsigned char * p);        //显示任意大小图片函数

void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2, u16 pcolor);                     //画线函数
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2,u16 pcolor);                 //画矩形
void Draw_Circle(u16 x,u16 y,u8 r,u16 pcolor);                                     //画圆函数
void TP_draw_adjust_point(u16 x,u16 y,u16 color);                                  //画十字函数

u16 RGB(u8 R, u8 G, u8 B);                                                         //RGB颜色转换函数

/* 基于8*16字符和16*16汉字的缩放显示 */ 
void LCD_Dis_Ascill_Sf(u16 Xpos, u16 Ypos, char Str, u16 Pcolor, u16 Bcolor, u16 Size);  
void LCD_Dis_Str_Sf(u16 Xpos, u16 Ypos, const unsigned char *Str, u16 Pcolor, u16 Bcolor, u16 Size);
void LCD_Dis_Hz_Sf(u16 Xpos, u16 Ypos, const unsigned char *Str, u16 Pcolor, u16 Bcolor, u16 Size);
void LCD_Dis_String(u16 Xpos,u16 Ypos, const unsigned char *Str, u16 Pcolor, u16 Bcolor, u16 Size); 

#endif
