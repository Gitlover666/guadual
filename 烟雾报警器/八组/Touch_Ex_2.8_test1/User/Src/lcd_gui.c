#include "lcd_gui.h"
#include <string.h>
#include "font.h"
#include "dzk.h"

/**************************** LCD画像素点函数 ****************************
功  能：在LCD液晶屏上画一个像素点
参  数：Xpos：X轴坐标
		Ypos：Y轴坐标
		Color：像素点颜色
返回值：无
*************************************************************************/
void LCD_Draw_Point(u16 xpos, u16 ypos, u16 Color)
{
	/* 发送列控制命令 */
	LCD_ILI9341_CMD(0x2a);                         //发送列地址设置命令
	LCD_ILI9341_Parameter((xpos & 0xff00) >> 8);   //发送起始列数据的高8位
	LCD_ILI9341_Parameter(xpos & 0xff);            //发送起始列数据的低8位
	LCD_ILI9341_Parameter((xpos & 0xff00) >> 8);   //发送结束列数据的高8位
	LCD_ILI9341_Parameter(xpos & 0xff);            //发送结束列数据的低8位
	
	/* 发送页控制命令 */
	LCD_ILI9341_CMD(0x2b);                         //发送页地址设置命令
	LCD_ILI9341_Parameter((ypos & 0xff00) >> 8);   //发送起始页数据的高8位
	LCD_ILI9341_Parameter(ypos & 0xff);            //发送起始页数据的低8位
	LCD_ILI9341_Parameter((ypos & 0xff00) >> 8);   //发送结束页数据的高8位
	LCD_ILI9341_Parameter(ypos & 0xff);            //发送结束页数据的低8位
	
	LCD_ILI9341_CMD(0x2c);                         //写GRAM控制命令
	LCD_ILI9341_Parameter(Color);
}

/********************************** LCD设置像素范围坐标函数 **********************************
功  能：设置将要显示图像的块区域（适用显示矩形图像）
参  数：SX   起始x坐标
		SY   起始Y坐标
        EX   结束X坐标
        EY   结束Y坐标
返回值：无
*********************************************************************************************/
void LCD_SetDrawBlock(u32 SX,u32 SY,u32 EX,u32 EY)
{
	/* 发送列控制命令 */
	LCD_ILI9341_CMD(0x2a);                         //发送列地址设置命令
	LCD_ILI9341_Parameter((SX & 0xff00) >> 8);   //发送起始列数据的高8位
	LCD_ILI9341_Parameter(SX & 0xff);            //发送起始列数据的低8位
	LCD_ILI9341_Parameter((EX & 0xff00) >> 8);   //发送结束列数据的高8位
	LCD_ILI9341_Parameter(EX & 0xff);            //发送结束列数据的低8位
	
	/* 发送页控制命令 */
	LCD_ILI9341_CMD(0x2b);                         //发送页地址设置命令
	LCD_ILI9341_Parameter((SY & 0xff00) >> 8);   //发送起始页数据的高8位
	LCD_ILI9341_Parameter(SY & 0xff);            //发送起始页数据的低8位
	LCD_ILI9341_Parameter((EY & 0xff00) >> 8);   //发送结束页数据的高8位
	LCD_ILI9341_Parameter(EY & 0xff);            //发送结束页数据的低8位
}


/**************************** LCD字符显示函数 ****************************
功  能：在LCD液晶屏显示一个8X16大小的字符
参  数：Xpos：  X轴坐标
		Ypos：  Y轴坐标
		Pcolor：字体颜色
		Bcolor：背景颜色
		str：   需要显示的内容
返回值：无
**************************************************************************/
void LCD_Dis_8x16Ascill(u16 Xpos, u16 Ypos, char str, u16 Pcolor, u16 Bcolor)
{
	u8 buff[16];    //存放显示字符的字模
	u8 x,y;
	
	str = str - 32;  //得到Ascill码值的偏移量
	
	/* 把我们要显示的ASCILL码模的数据拷贝的buff里面去 */
	memcpy((char *)buff, &ascill[str * 16], 16);  //把需要显示的字模赋值到buff数组
	
	/* 设置字符的区域坐标 */	
	LCD_SetDrawBlock(Xpos,Ypos,(Xpos + 8 - 1),(Ypos + 16 - 1));
	
	/* 发送设置颜色命令*/
	LCD_ILI9341_CMD(0x2c);
	
	/* 显示字符 */
	for(y = 0; y < 16; y++)
	{
		for(x = 0; x < 8; x++)
		{
			if(buff[y] & (0x80 >> x))             //判断需要显示的像素点是否为显示对象
			{
				LCD_ILI9341_Parameter(Pcolor);    //显示字体颜色
			}
			else
			{
				LCD_ILI9341_Parameter(Bcolor);   //显示屏幕颜色
			}
		}
	}
}

/**************************** LCD字符串显示函数 ****************************
功  能：在LCD液晶屏显示一组8X16大小的字符串
参  数：xpos：x轴坐标
		ypos：y轴坐标
		*str： 显示的字符串
		pcolor：字符颜色
		bcolor：背景颜色
返回值：无
**********************************************************************************/
void LCD_Dis_8x16string(u16 xpos,u16 ypos,const char *str,u16 pcolor,u16 bcolor)
{
	while(*str!='\0')
	{
		LCD_Dis_8x16Ascill(xpos,ypos,*str,pcolor,bcolor);
		xpos = xpos + 8;  //偏移要显示的X坐标
		str = str + 1;    //偏移字符的地址
	}
}

/**************************** LCD汉字显示函数 ****************************
功  能：在LCD液晶屏显示一个指定大小的汉字
参  数：Xpos：  X轴坐标
		Ypos：  Y轴坐标
		dzk：   汉字字模
		size：  字体大小
		Pcolor：字体颜色
		Bcolor：背景颜色
返回值：无
**************************************************************************/
void Show_Font(u16 Xpos, u16 Ypos,u8 *dzk,u8 size,u16 Pcolor, u16 Bcolor)
{
	u8 csize = 0;
	u8 i,j,temp;
	u16 x0 = Xpos;
	
	/* 计算需要显示的汉字的字模的字节数 */
	csize = (size / 8 + ((size % 8)?1:0)) * size;
	
	/* 设置汉字的区域坐标 */	
	LCD_SetDrawBlock(Xpos,Ypos,(Xpos + size - 1),(Ypos + size - 1));
	
	/* 发送设置颜色命令*/
	LCD_ILI9341_CMD(0x2c);
	
	/* 显示汉字 */
	for(i = 0; i < csize; i++)     //循环显示汉字的所有字节数
	{
		temp = dzk[i];             //取出1个字节的数据
		for(j = 0; j < 8; j++)     //一个字节8位
		{
			if(temp & 0x80)        //判断字体点还是背景点
			{
				LCD_ILI9341_Parameter(Pcolor);    //显示字体颜色
			}
			else
			{  
				LCD_ILI9341_Parameter(Bcolor);   //显示屏幕颜色
			}
			temp <<= 1;    //把字节的次高位移成最高位
			Xpos++;        //X轴坐标递增
			if((Xpos - x0) == size)  //判断X轴是否写完
			{
				Xpos = x0;           //X轴指回第二行的首字节
				Ypos++;              //Y轴加1
				break;
			}
		}
	}
}

/********************************* LCD画线函数 *********************************
功  能：在LCD液晶屏画出一条指定长度的线
参  数：*x1,y1:起点坐标
		*x2,y2:终点坐标 
		*pcolor：画笔颜色
返回值：无
**********************************************************************************/
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2, u16 pcolor)
{
	u16 i; 
	int xerr = 0,yerr = 0;
	int delta_x,delta_y,distance;  //delta_x、delta_y坐标增量变量
	int incx,incy;                 //方向标志位
	int uRow,uCol; 
	delta_x = x2-x1;                //计算坐标增量(计算终点和起点之间的距离) 
	delta_y = y2-y1; 
	uRow = x1; 
	uCol = y1; 
	if(delta_x > 0)           //设置单步方向，向下画线
		incx = 1;             
	else if(delta_x == 0)
		incx = 0;             //竖线 
	else 
	{
		incx = -1;            //设置单步方向，向上画线
		delta_x = -delta_x;   //数据取反
	} 
	if(delta_y > 0)           //设置单步方向，向前画线
		incy=1; 
	else if(delta_y == 0)
		incy=0;                //水平线 
	else
	{
		incy=-1;               //设置单步方向，向后画线
		delta_y = -delta_y;    //数据取反
	} 
	if( delta_x > delta_y)
		distance = delta_x;       //选取基本增量坐标轴(选取从哪一个点开始画) 
	else 
		distance = delta_y; 
	
	for(i = 0;i <= distance+1; i++ )      //画线输出 
	{  
		LCD_Draw_Point(uRow,uCol,pcolor);   //画点 
		xerr += delta_x ;                   //计算画点数               
		yerr += delta_y ; 
		if(xerr > distance)                 //x轴画一点结束
		{ 
			xerr -= distance; 
			uRow += incx;                     //控制方向
		} 
		if(yerr > distance) 
		{ 
			yerr -= distance; 
			uCol += incy; 
		} 
	}  
}  

/********************************* LCD画矩形函数 *********************************
功  能：在LCD液晶屏画出一个指定大小的矩形图案
参  数：*x1,y1:矩形起点坐标
		*x2,y2:矩形对角坐标 
		*pcolor：画笔颜色
返回值：无
**********************************************************************************/
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2,u16 pcolor)
{
	LCD_DrawLine(x1,y1,x2,y1,pcolor);
	LCD_DrawLine(x1,y1,x1,y2,pcolor);
	LCD_DrawLine(x1,y2,x2,y2,pcolor);
	LCD_DrawLine(x2,y1,x2,y2,pcolor);
}

/********************************** LCD画圆函数 **********************************
功  能：在LCD液晶屏画出一个指定大小的圆形图案
参  数：*x,y：圆心坐标
		*r：  圆的半径
		*pcolor：画笔颜色
返回值：无
**********************************************************************************/
void Draw_Circle(u16 x,u16 y,u8 r,u16 pcolor)
{
	int a,b;
	int di;
	a = 0;
	b = r;	  
	di = 3 - (r << 1);             //判断下个点位置的标志
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
		//使用Bresenham算法画圆     
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

/********************************** LCD图片显示函数 **********************************
功  能：在LCD液晶屏显示一幅指定大小的图片
参  数：*x,y:        图片起始坐标
		*High,Width：图片的高度和宽度 
		*bmp[]：     需要显示的图片的数据数组
返回值：无
**************************************************************************************/
void Show_Picture(u32 x,u32 y,u32 Width, u32 High,const unsigned char * p)
{ 
	u32 i,j;  

    /* 设置图片的区域坐标 */	
	LCD_SetDrawBlock(x,y,(x + Width - 1),(y + High - 1));
	
	/* 发送设置颜色命令*/
	LCD_ILI9341_CMD(0x2c);
	
	/* 循环画出图形的每一个像素点 */
	for(j = 0; j < High; j++)
	{ 
		for(i = 0; i < Width; i++)
		{ 
			LCD_ILI9341_Parameter((*p<<8)+*(p+1));   //画点LCD的像素是16位的，所以需要将2个8位像素合成16位像素
			p = p + 2;
		}
	}

}

/********************************** RGB颜色转换函数 **********************************
功  能：把指定的8-8-8颜色码 转 5-6-5颜色码
参  数：R G B：红、绿、蓝 24bit 8-8-8格式颜色码
返回值：16bit 5-6-5  颜色码
**************************************************************************************/
u16 RGB(u8 R, u8 G, u8 B)
{
	u16 color;
	color = ((R>>3)<<11) | ((G>>2)<<5) | (B>>3);
	
	return (color);
}

/********************************** LCD画十字函数 **********************************
功  能：在LCD液晶屏画出一个长度为10的十字图形
参  数：*x.y：  点坐标  
		*color: 颜色
返回值：无
************************************************************************************/
void TP_draw_adjust_point(u16 x,u16 y,u16 color)
{
	u8 i;
	
	/* 设置十字的中心坐标 */
	LCD_Draw_Point(x,y,color);
	
	/* 十字长度大小为10 */
	for(i=1; i<10; i++)
	{
		LCD_Draw_Point(x-i,y,color);
		LCD_Draw_Point(x  ,y-i,color);
		LCD_Draw_Point(x+i,y,color);
		LCD_Draw_Point(x  ,y+i,color);
	}
}

/******************************** LCD画（2*2大小）点函数 ********************************
功  能：在LCD液晶屏画出一个2X2大小的像素点
参  数：*x.y：  点坐标  
		*color: 颜色
返回值：无
****************************************************************************************/
void Draw_Big_Point(u16 x,u16 y,u16 color)
{	    
	LCD_Draw_Point(x,y,color);
	LCD_Draw_Point(x+1,y,color);
	LCD_Draw_Point(x,y+1,color);
	LCD_Draw_Point(x+1,y+1,color);	 	  	
}

/********************************** LCD缩放显示字符函数 **********************************
功  能：在LCD液晶屏放大显示一个以8X16大小为基础的字符
参  数：Xpos：X坐标
		Ypos：Y坐标
		Str： 需要显示的字符
		Pcolor：字体颜色
		Bcolor：背景颜色
		size: 缩放倍数
返回值：无
************************************************************************************/
void LCD_Dis_Ascill_Sf(u16 Xpos, u16 Ypos, char Str, u16 Pcolor, u16 Bcolor, u16 Size)
{
	u8 buff[16];                                  //存放需要显示的字符字模
	u8 x,y;
	
	Str = Str - 32;                                //得到Ascill码值的偏移量
	memcpy((char *)buff,&ascill[Str * 16], 16);    //把需要显示的字模数据提取到显示数组 
	
	/* 设置字符的区域坐标 */	
	LCD_SetDrawBlock(Xpos,Ypos,(Xpos + 8 * Size - 1),(Ypos + 16 * Size - 1));
	
	/* 发送设置颜色命令*/
	LCD_ILI9341_CMD(0x2c);
	
	/* 显示字符 */
	for(y = 0; y < 16 * Size; y++)                 //循环写入字符的元素， 行列乘上放大倍数
	{
		for(x = 0; x < (8 * Size); x++)
		{
			
			if( buff[y / Size] & (0x80 >> x / Size) )
			{  
//				LCD_Draw_Point(x+Xpos,y+Ypos,Pcolor);
				LCD_ILI9341_Parameter(Pcolor);                //显示字体颜色
			}
			else
			{
				LCD_ILI9341_Parameter(Bcolor);                //显示背景颜色
			}
		}
	}
}

/************************************** LCD缩放显示字符串函数 **************************************
功  能：在LCD液晶屏放大显示一个以8X16大小为基础的字符串
参  数：Xpos：X坐标
		Ypos：Y坐标
		*Str： ASCII字符串
		Pcolor：字体颜色
		Bcolor：背景颜色
		Size: 缩放倍数
返回值：无
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

/************************************** LCD缩放显示汉字函数 **************************************
功  能：在LCD液晶屏放大显示一个以16X16大小为基础的汉字
参  数：Xpos：X坐标
		Ypos：Y坐标
		*Str： 需要显示的内容
		Pcolor：字体颜色
		Bcolor：背景颜色
		Size: 缩放倍数
返回值：无
************************************************************************************************/
void LCD_Dis_Hz_Sf(u16 Xpos, u16 Ypos, const unsigned char *Str, u16 Pcolor, u16 Bcolor, u16 Size)
{
	u8 buff[32];                        //存放需要显示的字符字模
	u8 x,y;
	u16 tmp;
	
	memcpy((char *)buff,Str, 32);       //把需要显示的字模数据提取到显示数组 
	
	/* 设置汉字的区域坐标 */	
	//LCD_SetDrawBlock(Xpos,Ypos,Xpos+16*Size-1,Ypos+16*Size-1);
	
	/* 发送设置颜色命令*/
	//LCD_ILI9341_CMD(0x2c);
	
	for(y = 0; y < 16*Size; y++)        //循环写入字符的元素
	{
		tmp = ((u16)buff[(y/Size)*2] << 8) | buff[(y/Size)*2+1]; // 合并两个子模
		
		for(x = 0; x < 16*Size; x++)
		{
			if(tmp & (0x8000 >> x/Size))
			{
				LCD_Draw_Point(x+Xpos,y+Ypos,Pcolor);
				//LCD_ILI9341_Parameter(Pcolor);                   //显示字体颜色
			}
			else
			{
				//LCD_ILI9341_Parameter(Bcolor);                    //显示背景颜色
			}
		}
	}
}

/************************************** LCD缩放显示函数 **************************************
功  能：在LCD液晶屏放大混合显示一个以16X16大小为基础的汉字或者以8X16大小为基础的字符
参  数：Xpos：X坐标
		Ypos：Y坐标
		*Str： 需要显示的内容
		Pcolor：字体颜色
		Bcolor：背景颜色
		Size: 缩放倍数
返回值：无
备注:显示没有取模的汉字，汉字是显示不出来的，添加新汉字的方法：
1、取模16x16汉字(阴码、逐行、高位在前)
2、将取模好的好的数据粘贴到dzk.h文件的DZK[]数组最后
3、在Hz_Index[]数组后面加上取模数据的对应汉字
4、更改dzk.h文件中GB16_NUM宏定义的数值，这个宏的值就是Hz_Index[]中总的汉字个数
************************************************************************************************/
void LCD_Dis_String(u16 Xpos,u16 Ypos, const unsigned char *Str, u16 Pcolor, u16 Bcolor, u16 Size)
{
	u32 i;

	while (*Str != '\0')
	{
		if(*Str >= ' ' && *Str <= '~')                 //ascii字符
		{
			if( Xpos > (239 - (8 * Size)) )            //判断是否到一行的尽头
			{
				Xpos = 0;                              //X轴重新开始
				Ypos += 16 * Size;                     //Y轴换行
			}
			/* 显示一个字符 */
			LCD_Dis_Ascill_Sf(Xpos, Ypos, *Str, Pcolor, Bcolor, Size);    
			Xpos += 8 * Size;                         //X轴递增偏移一个字符的位置
			Str++;                                    //显示内容递增  
		}
		
		else if(*Str >= 0xA1 && *Str <= 0xFE)         //汉字
		{
			if(Xpos > (239 - (16 * Size)))            //判断是否到一行的尽头
			{
				Xpos = 0;                             //X轴重新开始
				Ypos += 16 * Size;                    //Y轴换行
			}
			/* 汉字显示 */
			for (i = 0; i < GB16_NUM; i++)            //循环查找汉字列表中的所有汉字
			{
				if ( (*Str == Hz_Index[i*2]) && (*(Str+1) == Hz_Index[i*2+1]) )     //找到汉字的字模位置
				{
					LCD_Dis_Hz_Sf(Xpos, Ypos, &DZK[32*(i)], Pcolor, Bcolor, Size);  //显示一个汉字
					break;
				}
			}
			Xpos += 16 * Size;                          //X轴递增偏移一个汉字的位置
			Str += 2;                                   //显示内容递增，一个汉字占2个字节
		}
		else
		{
			break;
		}
	}
}




































