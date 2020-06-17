#include "lcd_gui.h"
#include <string.h>
#include "font.h"
#include "dzk.h"

/**************************** LCD�����ص㺯�� ****************************
��  �ܣ���LCDҺ�����ϻ�һ�����ص�
��  ����Xpos��X������
		Ypos��Y������
		Color�����ص���ɫ
����ֵ����
*************************************************************************/
void LCD_Draw_Point(u16 xpos, u16 ypos, u16 Color)
{
	/* �����п������� */
	LCD_ILI9341_CMD(0x2a);                         //�����е�ַ��������
	LCD_ILI9341_Parameter((xpos & 0xff00) >> 8);   //������ʼ�����ݵĸ�8λ
	LCD_ILI9341_Parameter(xpos & 0xff);            //������ʼ�����ݵĵ�8λ
	LCD_ILI9341_Parameter((xpos & 0xff00) >> 8);   //���ͽ��������ݵĸ�8λ
	LCD_ILI9341_Parameter(xpos & 0xff);            //���ͽ��������ݵĵ�8λ
	
	/* ����ҳ�������� */
	LCD_ILI9341_CMD(0x2b);                         //����ҳ��ַ��������
	LCD_ILI9341_Parameter((ypos & 0xff00) >> 8);   //������ʼҳ���ݵĸ�8λ
	LCD_ILI9341_Parameter(ypos & 0xff);            //������ʼҳ���ݵĵ�8λ
	LCD_ILI9341_Parameter((ypos & 0xff00) >> 8);   //���ͽ���ҳ���ݵĸ�8λ
	LCD_ILI9341_Parameter(ypos & 0xff);            //���ͽ���ҳ���ݵĵ�8λ
	
	LCD_ILI9341_CMD(0x2c);                         //дGRAM��������
	LCD_ILI9341_Parameter(Color);
}

/********************************** LCD�������ط�Χ���꺯�� **********************************
��  �ܣ����ý�Ҫ��ʾͼ��Ŀ�����������ʾ����ͼ��
��  ����SX   ��ʼx����
		SY   ��ʼY����
        EX   ����X����
        EY   ����Y����
����ֵ����
*********************************************************************************************/
void LCD_SetDrawBlock(u32 SX,u32 SY,u32 EX,u32 EY)
{
	/* �����п������� */
	LCD_ILI9341_CMD(0x2a);                         //�����е�ַ��������
	LCD_ILI9341_Parameter((SX & 0xff00) >> 8);   //������ʼ�����ݵĸ�8λ
	LCD_ILI9341_Parameter(SX & 0xff);            //������ʼ�����ݵĵ�8λ
	LCD_ILI9341_Parameter((EX & 0xff00) >> 8);   //���ͽ��������ݵĸ�8λ
	LCD_ILI9341_Parameter(EX & 0xff);            //���ͽ��������ݵĵ�8λ
	
	/* ����ҳ�������� */
	LCD_ILI9341_CMD(0x2b);                         //����ҳ��ַ��������
	LCD_ILI9341_Parameter((SY & 0xff00) >> 8);   //������ʼҳ���ݵĸ�8λ
	LCD_ILI9341_Parameter(SY & 0xff);            //������ʼҳ���ݵĵ�8λ
	LCD_ILI9341_Parameter((EY & 0xff00) >> 8);   //���ͽ���ҳ���ݵĸ�8λ
	LCD_ILI9341_Parameter(EY & 0xff);            //���ͽ���ҳ���ݵĵ�8λ
}


/**************************** LCD�ַ���ʾ���� ****************************
��  �ܣ���LCDҺ������ʾһ��8X16��С���ַ�
��  ����Xpos��  X������
		Ypos��  Y������
		Pcolor��������ɫ
		Bcolor��������ɫ
		str��   ��Ҫ��ʾ������
����ֵ����
**************************************************************************/
void LCD_Dis_8x16Ascill(u16 Xpos, u16 Ypos, char str, u16 Pcolor, u16 Bcolor)
{
	u8 buff[16];    //�����ʾ�ַ�����ģ
	u8 x,y;
	
	str = str - 32;  //�õ�Ascill��ֵ��ƫ����
	
	/* ������Ҫ��ʾ��ASCILL��ģ�����ݿ�����buff����ȥ */
	memcpy((char *)buff, &ascill[str * 16], 16);  //����Ҫ��ʾ����ģ��ֵ��buff����
	
	/* �����ַ����������� */	
	LCD_SetDrawBlock(Xpos,Ypos,(Xpos + 8 - 1),(Ypos + 16 - 1));
	
	/* ����������ɫ����*/
	LCD_ILI9341_CMD(0x2c);
	
	/* ��ʾ�ַ� */
	for(y = 0; y < 16; y++)
	{
		for(x = 0; x < 8; x++)
		{
			if(buff[y] & (0x80 >> x))             //�ж���Ҫ��ʾ�����ص��Ƿ�Ϊ��ʾ����
			{
				LCD_ILI9341_Parameter(Pcolor);    //��ʾ������ɫ
			}
			else
			{
				LCD_ILI9341_Parameter(Bcolor);   //��ʾ��Ļ��ɫ
			}
		}
	}
}

/**************************** LCD�ַ�����ʾ���� ****************************
��  �ܣ���LCDҺ������ʾһ��8X16��С���ַ���
��  ����xpos��x������
		ypos��y������
		*str�� ��ʾ���ַ���
		pcolor���ַ���ɫ
		bcolor��������ɫ
����ֵ����
**********************************************************************************/
void LCD_Dis_8x16string(u16 xpos,u16 ypos,const char *str,u16 pcolor,u16 bcolor)
{
	while(*str!='\0')
	{
		LCD_Dis_8x16Ascill(xpos,ypos,*str,pcolor,bcolor);
		xpos = xpos + 8;  //ƫ��Ҫ��ʾ��X����
		str = str + 1;    //ƫ���ַ��ĵ�ַ
	}
}

/**************************** LCD������ʾ���� ****************************
��  �ܣ���LCDҺ������ʾһ��ָ����С�ĺ���
��  ����Xpos��  X������
		Ypos��  Y������
		dzk��   ������ģ
		size��  �����С
		Pcolor��������ɫ
		Bcolor��������ɫ
����ֵ����
**************************************************************************/
void Show_Font(u16 Xpos, u16 Ypos,u8 *dzk,u8 size,u16 Pcolor, u16 Bcolor)
{
	u8 csize = 0;
	u8 i,j,temp;
	u16 x0 = Xpos;
	
	/* ������Ҫ��ʾ�ĺ��ֵ���ģ���ֽ��� */
	csize = (size / 8 + ((size % 8)?1:0)) * size;
	
	/* ���ú��ֵ��������� */	
	LCD_SetDrawBlock(Xpos,Ypos,(Xpos + size - 1),(Ypos + size - 1));
	
	/* ����������ɫ����*/
	LCD_ILI9341_CMD(0x2c);
	
	/* ��ʾ���� */
	for(i = 0; i < csize; i++)     //ѭ����ʾ���ֵ������ֽ���
	{
		temp = dzk[i];             //ȡ��1���ֽڵ�����
		for(j = 0; j < 8; j++)     //һ���ֽ�8λ
		{
			if(temp & 0x80)        //�ж�����㻹�Ǳ�����
			{
				LCD_ILI9341_Parameter(Pcolor);    //��ʾ������ɫ
			}
			else
			{  
				LCD_ILI9341_Parameter(Bcolor);   //��ʾ��Ļ��ɫ
			}
			temp <<= 1;    //���ֽڵĴθ�λ�Ƴ����λ
			Xpos++;        //X���������
			if((Xpos - x0) == size)  //�ж�X���Ƿ�д��
			{
				Xpos = x0;           //X��ָ�صڶ��е����ֽ�
				Ypos++;              //Y���1
				break;
			}
		}
	}
}

/********************************* LCD���ߺ��� *********************************
��  �ܣ���LCDҺ��������һ��ָ�����ȵ���
��  ����*x1,y1:�������
		*x2,y2:�յ����� 
		*pcolor��������ɫ
����ֵ����
**********************************************************************************/
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2, u16 pcolor)
{
	u16 i; 
	int xerr = 0,yerr = 0;
	int delta_x,delta_y,distance;  //delta_x��delta_y������������
	int incx,incy;                 //�����־λ
	int uRow,uCol; 
	delta_x = x2-x1;                //������������(�����յ�����֮��ľ���) 
	delta_y = y2-y1; 
	uRow = x1; 
	uCol = y1; 
	if(delta_x > 0)           //���õ����������»���
		incx = 1;             
	else if(delta_x == 0)
		incx = 0;             //���� 
	else 
	{
		incx = -1;            //���õ����������ϻ���
		delta_x = -delta_x;   //����ȡ��
	} 
	if(delta_y > 0)           //���õ���������ǰ����
		incy=1; 
	else if(delta_y == 0)
		incy=0;                //ˮƽ�� 
	else
	{
		incy=-1;               //���õ������������
		delta_y = -delta_y;    //����ȡ��
	} 
	if( delta_x > delta_y)
		distance = delta_x;       //ѡȡ��������������(ѡȡ����һ���㿪ʼ��) 
	else 
		distance = delta_y; 
	
	for(i = 0;i <= distance+1; i++ )      //������� 
	{  
		LCD_Draw_Point(uRow,uCol,pcolor);   //���� 
		xerr += delta_x ;                   //���㻭����               
		yerr += delta_y ; 
		if(xerr > distance)                 //x�ửһ�����
		{ 
			xerr -= distance; 
			uRow += incx;                     //���Ʒ���
		} 
		if(yerr > distance) 
		{ 
			yerr -= distance; 
			uCol += incy; 
		} 
	}  
}  

/********************************* LCD�����κ��� *********************************
��  �ܣ���LCDҺ��������һ��ָ����С�ľ���ͼ��
��  ����*x1,y1:�����������
		*x2,y2:���ζԽ����� 
		*pcolor��������ɫ
����ֵ����
**********************************************************************************/
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2,u16 pcolor)
{
	LCD_DrawLine(x1,y1,x2,y1,pcolor);
	LCD_DrawLine(x1,y1,x1,y2,pcolor);
	LCD_DrawLine(x1,y2,x2,y2,pcolor);
	LCD_DrawLine(x2,y1,x2,y2,pcolor);
}

/********************************** LCD��Բ���� **********************************
��  �ܣ���LCDҺ��������һ��ָ����С��Բ��ͼ��
��  ����*x,y��Բ������
		*r��  Բ�İ뾶
		*pcolor��������ɫ
����ֵ����
**********************************************************************************/
void Draw_Circle(u16 x,u16 y,u8 r,u16 pcolor)
{
	int a,b;
	int di;
	a = 0;
	b = r;	  
	di = 3 - (r << 1);             //�ж��¸���λ�õı�־
	while(a <= b)
	{
		LCD_Draw_Point(x+a,y-b,pcolor);             //5
 		LCD_Draw_Point(x+b,y-a,pcolor);             //0           
		LCD_Draw_Point(x+b,y+a,pcolor);             //4               
		LCD_Draw_Point(x+a,y+b,pcolor);             //6 
		LCD_Draw_Point(x-a,y+b,pcolor);             //1       
 		LCD_Draw_Point(x-b,y+a,pcolor);             
		LCD_Draw_Point(x-a,y-b,pcolor);             //2             
  		LCD_Draw_Point(x-b,y-a,pcolor);             //7     	         
		a++;
		//ʹ��Bresenham�㷨��Բ     
		if(di<0)
		{
			di += 4 * a + 6;	
		}			
		else
		{
			di += 10 + 4 * (a-b);   
			b--;
		} 						    
	}
} 

/********************************** LCDͼƬ��ʾ���� **********************************
��  �ܣ���LCDҺ������ʾһ��ָ����С��ͼƬ
��  ����*x,y:        ͼƬ��ʼ����
		*High,Width��ͼƬ�ĸ߶ȺͿ�� 
		*bmp[]��     ��Ҫ��ʾ��ͼƬ����������
����ֵ����
**************************************************************************************/
void Show_Picture(u32 x,u32 y,u32 Width, u32 High,const unsigned char * p)
{ 
	u32 i,j;  

    /* ����ͼƬ���������� */	
	LCD_SetDrawBlock(x,y,(x + Width - 1),(y + High - 1));
	
	/* ����������ɫ����*/
	LCD_ILI9341_CMD(0x2c);
	
	/* ѭ������ͼ�ε�ÿһ�����ص� */
	for(j = 0; j < High; j++)
	{ 
		for(i = 0; i < Width; i++)
		{ 
			LCD_ILI9341_Parameter((*p<<8)+*(p+1));   //����LCD��������16λ�ģ�������Ҫ��2��8λ���غϳ�16λ����
			p = p + 2;
		}
	}

}

/********************************** RGB��ɫת������ **********************************
��  �ܣ���ָ����8-8-8��ɫ�� ת 5-6-5��ɫ��
��  ����R G B���졢�̡��� 24bit 8-8-8��ʽ��ɫ��
����ֵ��16bit 5-6-5  ��ɫ��
**************************************************************************************/
u16 RGB(u8 R, u8 G, u8 B)
{
	u16 color;
	color = ((R>>3)<<11) | ((G>>2)<<5) | (B>>3);
	
	return (color);
}

/********************************** LCD��ʮ�ֺ��� **********************************
��  �ܣ���LCDҺ��������һ������Ϊ10��ʮ��ͼ��
��  ����*x.y��  ������  
		*color: ��ɫ
����ֵ����
************************************************************************************/
void TP_draw_adjust_point(u16 x,u16 y,u16 color)
{
	u8 i;
	
	/* ����ʮ�ֵ��������� */
	LCD_Draw_Point(x,y,color);
	
	/* ʮ�ֳ��ȴ�СΪ10 */
	for(i=1; i<10; i++)
	{
		LCD_Draw_Point(x-i,y,color);
		LCD_Draw_Point(x  ,y-i,color);
		LCD_Draw_Point(x+i,y,color);
		LCD_Draw_Point(x  ,y+i,color);
	}
}

/******************************** LCD����2*2��С���㺯�� ********************************
��  �ܣ���LCDҺ��������һ��2X2��С�����ص�
��  ����*x.y��  ������  
		*color: ��ɫ
����ֵ����
****************************************************************************************/
void Draw_Big_Point(u16 x,u16 y,u16 color)
{	    
	LCD_Draw_Point(x,y,color);
	LCD_Draw_Point(x+1,y,color);
	LCD_Draw_Point(x,y+1,color);
	LCD_Draw_Point(x+1,y+1,color);	 	  	
}

/********************************** LCD������ʾ�ַ����� **********************************
��  �ܣ���LCDҺ�����Ŵ���ʾһ����8X16��СΪ�������ַ�
��  ����Xpos��X����
		Ypos��Y����
		Str�� ��Ҫ��ʾ���ַ�
		Pcolor��������ɫ
		Bcolor��������ɫ
		size: ���ű���
����ֵ����
************************************************************************************/
void LCD_Dis_Ascill_Sf(u16 Xpos, u16 Ypos, char Str, u16 Pcolor, u16 Bcolor, u16 Size)
{
	u8 buff[16];                                  //�����Ҫ��ʾ���ַ���ģ
	u8 x,y;
	
	Str = Str - 32;                                //�õ�Ascill��ֵ��ƫ����
	memcpy((char *)buff,&ascill[Str * 16], 16);    //����Ҫ��ʾ����ģ������ȡ����ʾ���� 
	
	/* �����ַ����������� */	
	LCD_SetDrawBlock(Xpos,Ypos,(Xpos + 8 * Size - 1),(Ypos + 16 * Size - 1));
	
	/* ����������ɫ����*/
	LCD_ILI9341_CMD(0x2c);
	
	/* ��ʾ�ַ� */
	for(y = 0; y < 16 * Size; y++)                 //ѭ��д���ַ���Ԫ�أ� ���г��ϷŴ���
	{
		for(x = 0; x < (8 * Size); x++)
		{
			
			if( buff[y / Size] & (0x80 >> x / Size) )
			{  
//				LCD_Draw_Point(x+Xpos,y+Ypos,Pcolor);
				LCD_ILI9341_Parameter(Pcolor);                //��ʾ������ɫ
			}
			else
			{
				LCD_ILI9341_Parameter(Bcolor);                //��ʾ������ɫ
			}
		}
	}
}

/************************************** LCD������ʾ�ַ������� **************************************
��  �ܣ���LCDҺ�����Ŵ���ʾһ����8X16��СΪ�������ַ���
��  ����Xpos��X����
		Ypos��Y����
		*Str�� ASCII�ַ���
		Pcolor��������ɫ
		Bcolor��������ɫ
		Size: ���ű���
����ֵ����
**************************************************************************************************/
void LCD_Dis_Str_Sf(u16 Xpos, u16 Ypos, const unsigned char *Str, u16 Pcolor, u16 Bcolor, u16 Size)
{
	u8 i = 0;
	
	while(Str[i] != '\0' )
	{
		LCD_Dis_Ascill_Sf(Xpos + (i * (8 * Size)), Ypos, Str[i], Pcolor, Bcolor, Size);
		i++;
	}
}

/************************************** LCD������ʾ���ֺ��� **************************************
��  �ܣ���LCDҺ�����Ŵ���ʾһ����16X16��СΪ�����ĺ���
��  ����Xpos��X����
		Ypos��Y����
		*Str�� ��Ҫ��ʾ������
		Pcolor��������ɫ
		Bcolor��������ɫ
		Size: ���ű���
����ֵ����
************************************************************************************************/
void LCD_Dis_Hz_Sf(u16 Xpos, u16 Ypos, const unsigned char *Str, u16 Pcolor, u16 Bcolor, u16 Size)
{
	u8 buff[32];                        //�����Ҫ��ʾ���ַ���ģ
	u8 x,y;
	u16 tmp;
	
	memcpy((char *)buff,Str, 32);       //����Ҫ��ʾ����ģ������ȡ����ʾ���� 
	
	/* ���ú��ֵ��������� */	
	//LCD_SetDrawBlock(Xpos,Ypos,Xpos+16*Size-1,Ypos+16*Size-1);
	
	/* ����������ɫ����*/
	//LCD_ILI9341_CMD(0x2c);
	
	for(y = 0; y < 16*Size; y++)        //ѭ��д���ַ���Ԫ��
	{
		tmp = ((u16)buff[(y/Size)*2] << 8) | buff[(y/Size)*2+1]; // �ϲ�������ģ
		
		for(x = 0; x < 16*Size; x++)
		{
			if(tmp & (0x8000 >> x/Size))
			{
				LCD_Draw_Point(x+Xpos,y+Ypos,Pcolor);
				//LCD_ILI9341_Parameter(Pcolor);                   //��ʾ������ɫ
			}
			else
			{
				//LCD_ILI9341_Parameter(Bcolor);                    //��ʾ������ɫ
			}
		}
	}
}

/************************************** LCD������ʾ���� **************************************
��  �ܣ���LCDҺ�����Ŵ�����ʾһ����16X16��СΪ�����ĺ��ֻ�����8X16��СΪ�������ַ�
��  ����Xpos��X����
		Ypos��Y����
		*Str�� ��Ҫ��ʾ������
		Pcolor��������ɫ
		Bcolor��������ɫ
		Size: ���ű���
����ֵ����
��ע:��ʾû��ȡģ�ĺ��֣���������ʾ�������ģ�����º��ֵķ�����
1��ȡģ16x16����(���롢���С���λ��ǰ)
2����ȡģ�õĺõ�����ճ����dzk.h�ļ���DZK[]�������
3����Hz_Index[]����������ȡģ���ݵĶ�Ӧ����
4������dzk.h�ļ���GB16_NUM�궨�����ֵ��������ֵ����Hz_Index[]���ܵĺ��ָ���
************************************************************************************************/
void LCD_Dis_String(u16 Xpos,u16 Ypos, const unsigned char *Str, u16 Pcolor, u16 Bcolor, u16 Size)
{
	u32 i;

	while (*Str != '\0')
	{
		if(*Str >= ' ' && *Str <= '~')                 //ascii�ַ�
		{
			if( Xpos > (239 - (8 * Size)) )            //�ж��Ƿ�һ�еľ�ͷ
			{
				Xpos = 0;                              //X�����¿�ʼ
				Ypos += 16 * Size;                     //Y�ỻ��
			}
			/* ��ʾһ���ַ� */
			LCD_Dis_Ascill_Sf(Xpos, Ypos, *Str, Pcolor, Bcolor, Size);    
			Xpos += 8 * Size;                         //X�����ƫ��һ���ַ���λ��
			Str++;                                    //��ʾ���ݵ���  
		}
		
		else if(*Str >= 0xA1 && *Str <= 0xFE)         //����
		{
			if(Xpos > (239 - (16 * Size)))            //�ж��Ƿ�һ�еľ�ͷ
			{
				Xpos = 0;                             //X�����¿�ʼ
				Ypos += 16 * Size;                    //Y�ỻ��
			}
			/* ������ʾ */
			for (i = 0; i < GB16_NUM; i++)            //ѭ�����Һ����б��е����к���
			{
				if ( (*Str == Hz_Index[i*2]) && (*(Str+1) == Hz_Index[i*2+1]) )     //�ҵ����ֵ���ģλ��
				{
					LCD_Dis_Hz_Sf(Xpos, Ypos, &DZK[32*(i)], Pcolor, Bcolor, Size);  //��ʾһ������
					break;
				}
			}
			Xpos += 16 * Size;                          //X�����ƫ��һ�����ֵ�λ��
			Str += 2;                                   //��ʾ���ݵ�����һ������ռ2���ֽ�
		}
		else
		{
			break;
		}
	}
}




































