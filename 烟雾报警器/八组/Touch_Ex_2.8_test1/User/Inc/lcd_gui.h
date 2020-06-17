#ifndef __LCD_GUI_H__
#define __LCD_GUI_H__

/* ��Ҫ����ʹ�õľ���������ͺ��Լ�����оƬ������ͬ��ͷ�ļ� */
#include "ili9341.h"
#include <stm32f10x.h>
//������ɫֵ�궨��
#define COLOR_WHITE 0xFFFF
#define COLOR_RED   0xF800
#define COLOR_BLACK 0x0000
#define COLOR_GREEN 0x07E0
#define COLOR_BLUE  0x001F

/* ����LCD_GUI���� */
void LCD_Draw_Point(u16 xpos, u16 ypos, u16 Color);                                //���㺯��  
void LCD_SetDrawBlock(u32 SX,u32 SY,u32 EX,u32 EY);                                //�������ص�����
void Draw_Big_Point(u16 x,u16 y,u16 color);                                        //����㺯����2*2�㣩                    
void LCD_Dis_8x16Ascill(u16 Xpos,u16 Ypos,char str,u16 Pcolor,u16 Bcolor);         //8*16�ַ���ʾ����
void LCD_Dis_8x16string(u16 xpos,u16 ypos,const char *str,u16 pcolor,u16 bcolor);  //8*16�ַ�����ʾ����
void Show_Font(u16 x, u16 y, u8 *dzk, u8 size, u16 pcolor, u16 bcolor);            //��ʾ�����С���ֺ���
void Show_Picture(u32 x,u32 y,u32 Pic_x,u32 Pic_y,const unsigned char * p);        //��ʾ�����СͼƬ����

void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2, u16 pcolor);                     //���ߺ���
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2,u16 pcolor);                 //������
void Draw_Circle(u16 x,u16 y,u8 r,u16 pcolor);                                     //��Բ����
void TP_draw_adjust_point(u16 x,u16 y,u16 color);                                  //��ʮ�ֺ���

u16 RGB(u8 R, u8 G, u8 B);                                                         //RGB��ɫת������

/* ����8*16�ַ���16*16���ֵ�������ʾ */ 
void LCD_Dis_Ascill_Sf(u16 Xpos, u16 Ypos, char Str, u16 Pcolor, u16 Bcolor, u16 Size);  
void LCD_Dis_Str_Sf(u16 Xpos, u16 Ypos, const unsigned char *Str, u16 Pcolor, u16 Bcolor, u16 Size);
void LCD_Dis_Hz_Sf(u16 Xpos, u16 Ypos, const unsigned char *Str, u16 Pcolor, u16 Bcolor, u16 Size);
void LCD_Dis_String(u16 Xpos,u16 Ypos, const unsigned char *Str, u16 Pcolor, u16 Bcolor, u16 Size); 

#endif
