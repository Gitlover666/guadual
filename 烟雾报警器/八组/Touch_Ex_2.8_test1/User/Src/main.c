/* 触摸屏控制LED灯和蜂鸣器 */

#include "gpio.h"
#include "lcd_gui.h"
#include "pic.h"
#include "touch.h"
#include "ili9341.h"
#include "stdio.h"
# include "led.h"
# include "beep.h"
# include "stdio.h"
#include "systick.h"

int pos=0;
int pos1=0;
char ledflag=0;
char beepflag=0;
int num1;    //烟雾浓度阈值
int num2;    //火焰距离
int num3[4] = {1};    //火焰距离
int num4[4] = {1};  

int j;
int x = 0;
char buf[20];     //保存数字转换完成后的字符串
int adc_value=0;
int adc_value1=0;
TOUCH_TYPE_DEF Touch;
char flag = 0;
int LCD_Beep = 0;


void myadc_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	ADC_InitTypeDef ADC_InitStruct;
	//开启GPIOA和ADC1的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1|RCC_APB2Periph_GPIOA,ENABLE);
	//RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1|RCC_APB2Periph_GPIOA,ENABLE);
	//初始化PA4为模拟输入
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;  //模拟输入模式
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_3;
	GPIO_Init(GPIOA,&GPIO_InitStruct);    //写入配置寄存器
	//对ADC进行分频
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //6分频  ADC工作时钟12M
	//配置ADC
	ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;  //单次转换
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;//数据右对其
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//无外部触发
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;//独立工作模式
	ADC_InitStruct.ADC_NbrOfChannel = 1;   //转换数量
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;  //不需要扫描方式
	ADC_Init(ADC1,&ADC_InitStruct);
	ADC_Cmd(ADC1,ENABLE);   //给ADC上电
	//自校准
	ADC_ResetCalibration(ADC1);
	//等待校准寄存器复位完成
	while(ADC_GetResetCalibrationStatus(ADC1));
	ADC_StartCalibration(ADC1);
	//等待校准寄存器校准完成
	while(ADC_GetCalibrationStatus(ADC1));
}

u16 myADC_get(void)
{
	//配置规则转换序列,转换4号通道--PA4
	ADC_RegularChannelConfig(ADC1,ADC_Channel_4,1,
	ADC_SampleTime_239Cycles5);
	//软件触发，ADC开始转换
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	//等待转换完成
	while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));
	
	return ADC_GetConversionValue(ADC1);
}

u16 myADC_get1(void)
{
	//配置规则转换序列,转换3号通道--PA3
	ADC_RegularChannelConfig(ADC1,ADC_Channel_3,1,
	ADC_SampleTime_239Cycles5);
	//软件触发，ADC开始转换
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	//等待转换完成
	while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));
	
	return ADC_GetConversionValue(ADC1);
}


int TOUCH_Sz(void)
{		
		x++;
		Show_Picture(0,0,240,320,gImage_bj); 
	
		LCD_Dis_String(30,60,"烟雾浓度",COLOR_WHITE,COLOR_BLACK,1);
		
		LCD_Dis_String(30,120,"火焰距离",COLOR_WHITE,COLOR_BLACK,1);

		LCD_Dis_String(160,270,"返回",COLOR_WHITE,COLOR_BLACK,2);
		if(x == 1)
		{
		sprintf(buf,"%d",num3[0]);
	  LCD_Dis_String(120,60,(const unsigned char *)buf,COLOR_WHITE,COLOR_BLACK,1);
	
		sprintf(buf,"%d",num4[0]);
	  LCD_Dis_String(120,120,(const unsigned char *)buf,COLOR_WHITE,COLOR_BLACK,1);
		}
		if(x == 2)
		{
			sprintf(buf,"%d",num4[0]);
			LCD_Dis_String(120,120,(const unsigned char *)buf,COLOR_WHITE,COLOR_BLACK,1);
		}
		for(j=0;j<pos;j++)
		{
		sprintf(buf,"%d",num3[j]);
		LCD_Dis_String(120+j*8,60,(const unsigned char *)buf,COLOR_WHITE,COLOR_BLACK,1);
		}
		for(j=0;j<pos1;j++)
		{
			sprintf(buf,"%d",num4[j]);
			LCD_Dis_String(120+j*8,120,(const unsigned char *)buf,COLOR_WHITE,COLOR_BLACK,1);
		}
		while(1)
		{
			
			Touch = Touch_Scanf();   //获取触摸坐标
			if(Touch.x!=0xFFFF)
			{
				if(Touch.x<230&&Touch.x>160&&Touch.y<300&&Touch.y>260)
				{	
					GPIO_SetBits(GPIOB,GPIO_Pin_8);
					Delay_ms(100);
					GPIO_ResetBits(GPIOB,GPIO_Pin_8);
					break;
				}

			if(Touch.x<152&&Touch.x>120&&Touch.y<76&&Touch.y>60)  //增加键
			{
//				return 2;
				return flag = 2;
			}
			if(Touch.x<152&&Touch.x>120&&Touch.y<136&&Touch.y>120)  //增加键
			{
//				return 2;
				return flag = 3;
			}
			
//		for(j=0;j<=pos;j++)
//		{
//		sprintf(buf,"%d",num3[j]);
//		LCD_Dis_String(120+j*8,60,(const unsigned char *)buf,COLOR_WHITE,COLOR_BLACK,1);
//		}
//		for(j=0;j<=pos1;j++)
//		{
//			sprintf(buf,"%d",num4[j]);
//			LCD_Dis_String(120+j*8,120,(const unsigned char *)buf,COLOR_WHITE,COLOR_BLACK,1);
//		}
//			sprintf(buf,"%d",num1);
//			LCD_Dis_String(120,60,(const unsigned char *)buf,COLOR_WHITE,COLOR_BLACK,1);
			//判断是否少于三四位数
//			if(num1 < 1000)
//			{
//				LCD_Clear(144,152,60,75,COLOR_BLACK);  //LCD液晶屏清屏
//			}
//			sprintf(buf,"%d",num2);
//			LCD_Dis_String(120,120,(const unsigned char *)buf,COLOR_WHITE,COLOR_BLACK,1);
//			if(num2 < 100)
//			{
//				LCD_Clear(136,148,120,135,COLOR_BLACK);  //LCD液晶屏清屏
//			}
		
}
		
}
//	return 0;
    return flag = 0;
	}

int TOUCH_fh(void)
{		
//		LCD_Clear(0,239,0,319,0x2744);  //LCD液晶屏清屏
	  Show_Picture(0,0,240,320,gImage_bj); 
		LCD_Dis_String(55,20,"班级：①⑥电气本一",COLOR_WHITE,COLOR_BLACK,1);
		LCD_Dis_String(55,41,"八组：赵国承",COLOR_WHITE,COLOR_BLACK,1);
	  LCD_Dis_String(103,62,"赵鹏飞",COLOR_WHITE,COLOR_BLACK,1);
	  LCD_Dis_String(103,83,"张洪达",COLOR_WHITE,COLOR_BLACK,1);
	  LCD_Dis_String(103,104,"王凤毅",COLOR_WHITE,COLOR_BLACK,1);
	  LCD_Dis_String(160,270,"设置",COLOR_WHITE,COLOR_BLACK,2);
		LCD_Dis_String(55,170,"烟雾浓度：",COLOR_WHITE,COLOR_BLACK,1);
	  LCD_Dis_String(55,191,"火焰距离：",COLOR_WHITE,COLOR_BLACK,1);
		while(1)
	  {
		
			Touch = Touch_Scanf();   //获取触摸坐标
			if(Touch.x!=0xFFFF)
			{
			if(Touch.x<230&&Touch.x>160&&Touch.y<300&&Touch.y>260)
				{		 
					GPIO_SetBits(GPIOB,GPIO_Pin_8);
					Delay_ms(100);
					GPIO_ResetBits(GPIOB,GPIO_Pin_8);
					return flag = 1;
				}	
			}		
		//如果烟雾浓度符合条件（大于阈值），亮pe5，也就是第二个灯，如果火焰距离符合条件（小于阈值），
		//图标和蜂鸣器在两者之间不停切换，亮be5，也就是第一个灯，如果两者都满足，则灯都亮，图标切换为另一个。
		adc_value = myADC_get();
		sprintf(buf,"%4d",adc_value);
		LCD_Dis_String(137,170,buf,0xf800,0xFFFF,1);  //显示结果
		if(adc_value > (num3[3]+num3[2]*10+num3[1]*100+num3[0]*1000))//第二个灯
			{
				GPIO_SetBits(GPIOB,GPIO_Pin_8);
				GPIO_ResetBits(GPIOE,GPIO_Pin_5);
				Show_Picture(30,250,50,50,gImage_hz); 
			}
			else
			{
				GPIO_ResetBits(GPIOB,GPIO_Pin_8);
				GPIO_SetBits(GPIOE,GPIO_Pin_5);
				Show_Picture(30,250,50,50,gImage_zc); 
			}
			adc_value1 = myADC_get1();
			sprintf(buf,"%4d",adc_value1);
			LCD_Dis_String(137,191,buf,0xf800,0xFFFF,1);  //显示结果
		if(adc_value1 <= (num4[3]+num4[2]*10+num4[1]*100+num4[0]*1000))
			{
				GPIO_SetBits(GPIOB,GPIO_Pin_8);
				GPIO_ResetBits(GPIOB,GPIO_Pin_5);
				Show_Picture(30,250,50,50,gImage_hz); 
			}
			else
			{
				GPIO_ResetBits(GPIOB,GPIO_Pin_8);
				GPIO_SetBits(GPIOB,GPIO_Pin_5);
				Show_Picture(30,250,50,50,gImage_zc); 
			}
		}
		
}

int TOUCH_JP(void)
{
	int i;
	Show_Picture(0,0,240,320,gImage_bj);
	Show_Picture(0,160,240,160,gImage_jianpan);
	LCD_Clear(100,132,60,76,COLOR_BLACK);
	for(i=0;i<pos;i++)
		{	
			sprintf(buf,"%d",num3[i]);
//			LCD_Dis_String(124-i*8,60,(const unsigned char *)buf,COLOR_WHITE,COLOR_BLACK,1);
			LCD_Dis_String(100+i*8,60,(const unsigned char *)buf,COLOR_WHITE,COLOR_BLACK,1);
		}
	while(1)
	  {
			Touch = Touch_Scanf();   //获取触摸坐标
			if(pos==5|pos<0)
			{
				pos = 0;
			}
			if(Touch.x!=0xFFFF)
			{
//			if(Touch.x<230&&Touch.x>160&&Touch.y<300&&Touch.y>260)
//				{		 
//					return 1;         //触摸屏初始化
//				}	
			if(Touch.x<80&&Touch.x>0&&Touch.y<200&&Touch.y>160)  //1
			{
				Show_Picture(0,160,10,10,gImage_ysj);
				Delay_ms(100);
				Show_Picture(0,160,10,10,gImage_xs);
				num3[pos] = 1;
				pos++;
			}
			else if(Touch.x<160&&Touch.x>80&&Touch.y<200&&Touch.y>160)  //2
			{
				Show_Picture(80,160,10,10,gImage_ysj);
				Delay_ms(100);
				Show_Picture(80,160,10,10,gImage_xs);
				num3[pos] = 2;
				pos++;	 
			}
			else if(Touch.x<240&&Touch.x>160&&Touch.y<200&&Touch.y>160)  //3
			{
        Show_Picture(160,160,10,10,gImage_ysj);
				Delay_ms(100);
				Show_Picture(160,160,10,10,gImage_xs);
				num3[pos] = 3;
				pos++;
			}
			else if(Touch.x<80&&Touch.x>0&&Touch.y<240&&Touch.y>200)  //4
			{
        Show_Picture(0,200,10,10,gImage_ysj);
				Delay_ms(100);
				Show_Picture(0,200,10,10,gImage_xs);
				num3[pos] = 4;
				pos++;	
			}
			else if(Touch.x<160&&Touch.x>80&&Touch.y<240&&Touch.y>200)  //5
			{
				Show_Picture(80,200,10,10,gImage_ysj);
				Delay_ms(100);
				Show_Picture(80,200,10,10,gImage_xs);
				num3[pos] = 5;
				pos++;
			}
			else if(Touch.x<240&&Touch.x>160&&Touch.y<240&&Touch.y>200)  //6
			{
				Show_Picture(160,200,10,10,gImage_ysj);
				Delay_ms(100);
				Show_Picture(160,200,10,10,gImage_xs);
				num3[pos] = 6;
				pos++;
			}
			else if(Touch.x<80&&Touch.x>0&&Touch.y<280&&Touch.y>240)  //7
			{
				Show_Picture(0,240,10,10,gImage_ysj);
				Delay_ms(100);
				Show_Picture(0,240,10,10,gImage_xs);
				num3[pos] = 7;
				pos++;
			}
			else if(Touch.x<160&&Touch.x>80&&Touch.y<280&&Touch.y>240)  //8
			{
				Show_Picture(80,240,10,10,gImage_ysj);
				Delay_ms(100);
				Show_Picture(80,240,10,10,gImage_xs);
				num3[pos] = 8;
				pos++;
			}
			else if(Touch.x<240&&Touch.x>160&&Touch.y<280&&Touch.y>240)  //9
			{
				Show_Picture(160,240,10,10,gImage_ysj);
				Delay_ms(100);
				Show_Picture(160,240,10,10,gImage_xs);
				num3[pos] = 9;
				pos++;
			}
			else if(Touch.x<80&&Touch.x>0&&Touch.y<320&&Touch.y>280)  //减
			{
				Show_Picture(0,280,10,10,gImage_ysj);
				Delay_ms(100);
				Show_Picture(0,280,10,10,gImage_xs);
				pos--;
				num3[pos] = 0;
				
//				LCD_Clear(100,100+pos*8,60,76,COLOR_BLACK);				
					
			}
			else if(Touch.x<160&&Touch.x>80&&Touch.y<320&&Touch.y>280)  //0
			{
				Show_Picture(80,280,10,10,gImage_ysj);
				Delay_ms(100);
				Show_Picture(80,280,10,10,gImage_xs);
				num3[pos] = 0;
				pos++;
			
			}
			else if(Touch.x<240&&Touch.x>160&&Touch.y<320&&Touch.y>280)  //减少键
			{
					Show_Picture(160,280,10,10,gImage_ysj);
				  Delay_ms(100);
				  Show_Picture(160,280,10,10,gImage_xs);
				  GPIO_SetBits(GPIOB,GPIO_Pin_8);
					Delay_ms(100);
					GPIO_ResetBits(GPIOB,GPIO_Pin_8);
				 break;
			}
		
			for(i=0;i<pos;i++)
			{	
				sprintf(buf,"%d",num3[i]);
//			LCD_Dis_String(124-i*8,60,(const unsigned char *)buf,COLOR_WHITE,COLOR_BLACK,1);
				LCD_Dis_String(100+i*8,60,(const unsigned char *)buf,COLOR_WHITE,COLOR_BLACK,1);
			}
			LCD_Clear(100,132,60,76,COLOR_BLACK);
			for(i=0;i<pos;i++)
			{	
				if(num3[i]>-1)
				{
					sprintf(buf,"%d",num3[i]);
//				LCD_Dis_String(124-(4-pos)*8)+8*i,60,(const unsigned char *)buf,COLOR_WHITE,COLOR_BLACK,1);
					LCD_Dis_String(132-pos*8+8*i,60,(const unsigned char *)buf,COLOR_WHITE,COLOR_BLACK,1);
					
				}
				
			}
			}		

		}
//		return 3;
		return flag = 1;

}

int TOUCH_JP1(void)
{
	int i;
	Show_Picture(0,0,240,320,gImage_bj);
	Show_Picture(0,160,240,160,gImage_jianpan);
	LCD_Clear(100,132,60,76,COLOR_BLACK);
	 for(i=0;i<pos1;i++)
		{	
				sprintf(buf,"%d",num4[i]);
//			LCD_Dis_String(124-i*8,60,(const unsigned char *)buf,COLOR_WHITE,COLOR_BLACK,1);
				LCD_Dis_String(100+i*8,60,(const unsigned char *)buf,COLOR_WHITE,COLOR_BLACK,1);
		}

	while(1)
	  {
			Touch = Touch_Scanf();   //获取触摸坐标
			if(pos1==5|pos1<0)
			{
				pos1 = 0;
			}
			if(Touch.x!=0xFFFF)
			{
//			if(Touch.x<230&&Touch.x>160&&Touch.y<300&&Touch.y>260)
//				{		 
//					return 1;         //触摸屏初始化
//				}	
			if(Touch.x<80&&Touch.x>0&&Touch.y<200&&Touch.y>160)  //1
			{
				Show_Picture(0,160,10,10,gImage_ysj);
				Delay_ms(100);
				Show_Picture(0,160,10,10,gImage_xs);
				num4[pos1] = 1;
				pos1++;
			}
			else if(Touch.x<160&&Touch.x>80&&Touch.y<200&&Touch.y>160)  //2
			{
				Show_Picture(80,160,10,10,gImage_ysj);
				Delay_ms(100);
				Show_Picture(80,160,10,10,gImage_xs);
				num4[pos1] = 2;
				pos1++;	 
			}
			else if(Touch.x<240&&Touch.x>160&&Touch.y<200&&Touch.y>160)  //3
			{
				Show_Picture(160,160,10,10,gImage_ysj);
				Delay_ms(100);
				Show_Picture(160,160,10,10,gImage_xs);
				num4[pos1] = 3;
				pos1++;
			}
			else if(Touch.x<80&&Touch.x>0&&Touch.y<240&&Touch.y>200)  //4
			{
				Show_Picture(0,200,10,10,gImage_ysj);
				Delay_ms(100);
				Show_Picture(0,200,10,10,gImage_xs);
				num4[pos1] = 4;
				pos1++;	
			}
			else if(Touch.x<160&&Touch.x>80&&Touch.y<240&&Touch.y>200)  //5
			{
				Show_Picture(80,200,10,10,gImage_ysj);
				Delay_ms(100);
				Show_Picture(80,200,10,10,gImage_xs);
				num4[pos1] = 5;
				pos1++;
			}
			else if(Touch.x<240&&Touch.x>160&&Touch.y<240&&Touch.y>200)  //6
			{
				Show_Picture(160,200,10,10,gImage_ysj);
				Delay_ms(100);
				Show_Picture(160,200,10,10,gImage_xs);
				num4[pos1] = 6;
				pos1++;
			}
			else if(Touch.x<80&&Touch.x>0&&Touch.y<280&&Touch.y>240)  //7
			{
				Show_Picture(0,240,10,10,gImage_ysj);
				Delay_ms(100);
				Show_Picture(0,240,10,10,gImage_xs);
				num4[pos1] = 7;
				pos1++;
			}
			else if(Touch.x<160&&Touch.x>80&&Touch.y<280&&Touch.y>240)  //8
			{
				Show_Picture(80,240,10,10,gImage_ysj);
				Delay_ms(100);
				Show_Picture(80,240,10,10,gImage_xs);
				num4[pos1] = 8;
				pos1++;
			}
			else if(Touch.x<240&&Touch.x>160&&Touch.y<280&&Touch.y>240)  //9
			{
				Show_Picture(160,240,10,10,gImage_ysj);
				Delay_ms(100);
				Show_Picture(160,240,10,10,gImage_xs);
				num4[pos1] = 9;
				pos1++;
			}
			else if(Touch.x<80&&Touch.x>0&&Touch.y<320&&Touch.y>280)  //减
			{
				Show_Picture(0,280,10,10,gImage_ysj);
				Delay_ms(100);
				Show_Picture(0,280,10,10,gImage_xs);
				pos1--;
				num4[pos1] = 0;
						
					
			}
			else if(Touch.x<160&&Touch.x>80&&Touch.y<320&&Touch.y>280)  //0
			{
				Show_Picture(80,280,10,10,gImage_ysj);
				Delay_ms(100);
				Show_Picture(80,280,10,10,gImage_xs);
				num4[pos1] = 0;
				pos1++;
			
			}
			else if(Touch.x<240&&Touch.x>160&&Touch.y<320&&Touch.y>280)  //减少键
			{
				  Show_Picture(160,280,10,10,gImage_ysj);
				  Delay_ms(100);
				  Show_Picture(160,280,10,10,gImage_xs);
					GPIO_SetBits(GPIOB,GPIO_Pin_8);
					Delay_ms(100);
					GPIO_ResetBits(GPIOB,GPIO_Pin_8);
				 break;
			}
		
			for(i=0;i<pos1;i++)
			{	
				sprintf(buf,"%d",num4[i]);
//			LCD_Dis_String(124-i*8,60,(const unsigned char *)buf,COLOR_WHITE,COLOR_BLACK,1);
				LCD_Dis_String(100+i*8,60,(const unsigned char *)buf,COLOR_WHITE,COLOR_BLACK,1);
			}
			LCD_Clear(100,132,60,76,COLOR_BLACK);
			for(i=0;i<pos1;i++)
			{	
				if(num4[i]>-1)
				{
					sprintf(buf,"%d",num4[i]);
//				LCD_Dis_String(124-(4-pos)*8)+8*i,60,(const unsigned char *)buf,COLOR_WHITE,COLOR_BLACK,1);
					LCD_Dis_String(132-pos1*8+8*i,60,(const unsigned char *)buf,COLOR_WHITE,COLOR_BLACK,1);
				}
				
			}
			}		

		}
//		return 3;
		return flag = 1;
	
}

int main(void)
{
	
	/* 硬件初始化 */
	Led_Init();               //LED灯初始化
	Beep_Init();              //蜂鸣器初始
	LCD_Init();               //液晶屏初始化
	Touch_Init();             //触摸屏初始化                    
	myadc_Init();   					//adc初始化
	while(1)
	{
			if(flag == 0)//进入设置页面
			{
				 TOUCH_fh();
			}
			if(flag == 1)//进入返回页面
			{
				TOUCH_Sz();
			}	
			if(flag == 2)//进入键盘页面
			{
				TOUCH_JP();
			}
			if(flag == 3)//进入键盘页面1
			{
				TOUCH_JP1();
			}
	}
}
	















