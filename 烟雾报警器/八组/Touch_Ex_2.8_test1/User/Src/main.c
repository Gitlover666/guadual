/* ����������LED�ƺͷ����� */

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
int num1;    //����Ũ����ֵ
int num2;    //�������
int num3[4] = {1};    //�������
int num4[4] = {1};  

int j;
int x = 0;
char buf[20];     //��������ת����ɺ���ַ���
int adc_value=0;
int adc_value1=0;
TOUCH_TYPE_DEF Touch;
char flag = 0;
int LCD_Beep = 0;


void myadc_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	ADC_InitTypeDef ADC_InitStruct;
	//����GPIOA��ADC1��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1|RCC_APB2Periph_GPIOA,ENABLE);
	//RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1|RCC_APB2Periph_GPIOA,ENABLE);
	//��ʼ��PA4Ϊģ������
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;  //ģ������ģʽ
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_3;
	GPIO_Init(GPIOA,&GPIO_InitStruct);    //д�����üĴ���
	//��ADC���з�Ƶ
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //6��Ƶ  ADC����ʱ��12M
	//����ADC
	ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;  //����ת��
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;//�����Ҷ���
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//���ⲿ����
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;//��������ģʽ
	ADC_InitStruct.ADC_NbrOfChannel = 1;   //ת������
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;  //����Ҫɨ�跽ʽ
	ADC_Init(ADC1,&ADC_InitStruct);
	ADC_Cmd(ADC1,ENABLE);   //��ADC�ϵ�
	//��У׼
	ADC_ResetCalibration(ADC1);
	//�ȴ�У׼�Ĵ�����λ���
	while(ADC_GetResetCalibrationStatus(ADC1));
	ADC_StartCalibration(ADC1);
	//�ȴ�У׼�Ĵ���У׼���
	while(ADC_GetCalibrationStatus(ADC1));
}

u16 myADC_get(void)
{
	//���ù���ת������,ת��4��ͨ��--PA4
	ADC_RegularChannelConfig(ADC1,ADC_Channel_4,1,
	ADC_SampleTime_239Cycles5);
	//���������ADC��ʼת��
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	//�ȴ�ת�����
	while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));
	
	return ADC_GetConversionValue(ADC1);
}

u16 myADC_get1(void)
{
	//���ù���ת������,ת��3��ͨ��--PA3
	ADC_RegularChannelConfig(ADC1,ADC_Channel_3,1,
	ADC_SampleTime_239Cycles5);
	//���������ADC��ʼת��
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	//�ȴ�ת�����
	while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));
	
	return ADC_GetConversionValue(ADC1);
}


int TOUCH_Sz(void)
{		
		x++;
		Show_Picture(0,0,240,320,gImage_bj); 
	
		LCD_Dis_String(30,60,"����Ũ��",COLOR_WHITE,COLOR_BLACK,1);
		
		LCD_Dis_String(30,120,"�������",COLOR_WHITE,COLOR_BLACK,1);

		LCD_Dis_String(160,270,"����",COLOR_WHITE,COLOR_BLACK,2);
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
			
			Touch = Touch_Scanf();   //��ȡ��������
			if(Touch.x!=0xFFFF)
			{
				if(Touch.x<230&&Touch.x>160&&Touch.y<300&&Touch.y>260)
				{	
					GPIO_SetBits(GPIOB,GPIO_Pin_8);
					Delay_ms(100);
					GPIO_ResetBits(GPIOB,GPIO_Pin_8);
					break;
				}

			if(Touch.x<152&&Touch.x>120&&Touch.y<76&&Touch.y>60)  //���Ӽ�
			{
//				return 2;
				return flag = 2;
			}
			if(Touch.x<152&&Touch.x>120&&Touch.y<136&&Touch.y>120)  //���Ӽ�
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
			//�ж��Ƿ���������λ��
//			if(num1 < 1000)
//			{
//				LCD_Clear(144,152,60,75,COLOR_BLACK);  //LCDҺ��������
//			}
//			sprintf(buf,"%d",num2);
//			LCD_Dis_String(120,120,(const unsigned char *)buf,COLOR_WHITE,COLOR_BLACK,1);
//			if(num2 < 100)
//			{
//				LCD_Clear(136,148,120,135,COLOR_BLACK);  //LCDҺ��������
//			}
		
}
		
}
//	return 0;
    return flag = 0;
	}

int TOUCH_fh(void)
{		
//		LCD_Clear(0,239,0,319,0x2744);  //LCDҺ��������
	  Show_Picture(0,0,240,320,gImage_bj); 
		LCD_Dis_String(55,20,"�༶���٢޵�����һ",COLOR_WHITE,COLOR_BLACK,1);
		LCD_Dis_String(55,41,"���飺�Թ���",COLOR_WHITE,COLOR_BLACK,1);
	  LCD_Dis_String(103,62,"������",COLOR_WHITE,COLOR_BLACK,1);
	  LCD_Dis_String(103,83,"�ź��",COLOR_WHITE,COLOR_BLACK,1);
	  LCD_Dis_String(103,104,"������",COLOR_WHITE,COLOR_BLACK,1);
	  LCD_Dis_String(160,270,"����",COLOR_WHITE,COLOR_BLACK,2);
		LCD_Dis_String(55,170,"����Ũ�ȣ�",COLOR_WHITE,COLOR_BLACK,1);
	  LCD_Dis_String(55,191,"������룺",COLOR_WHITE,COLOR_BLACK,1);
		while(1)
	  {
		
			Touch = Touch_Scanf();   //��ȡ��������
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
		//�������Ũ�ȷ���������������ֵ������pe5��Ҳ���ǵڶ����ƣ��������������������С����ֵ����
		//ͼ��ͷ�����������֮�䲻ͣ�л�����be5��Ҳ���ǵ�һ���ƣ�������߶����㣬��ƶ�����ͼ���л�Ϊ��һ����
		adc_value = myADC_get();
		sprintf(buf,"%4d",adc_value);
		LCD_Dis_String(137,170,buf,0xf800,0xFFFF,1);  //��ʾ���
		if(adc_value > (num3[3]+num3[2]*10+num3[1]*100+num3[0]*1000))//�ڶ�����
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
			LCD_Dis_String(137,191,buf,0xf800,0xFFFF,1);  //��ʾ���
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
			Touch = Touch_Scanf();   //��ȡ��������
			if(pos==5|pos<0)
			{
				pos = 0;
			}
			if(Touch.x!=0xFFFF)
			{
//			if(Touch.x<230&&Touch.x>160&&Touch.y<300&&Touch.y>260)
//				{		 
//					return 1;         //��������ʼ��
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
			else if(Touch.x<80&&Touch.x>0&&Touch.y<320&&Touch.y>280)  //��
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
			else if(Touch.x<240&&Touch.x>160&&Touch.y<320&&Touch.y>280)  //���ټ�
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
			Touch = Touch_Scanf();   //��ȡ��������
			if(pos1==5|pos1<0)
			{
				pos1 = 0;
			}
			if(Touch.x!=0xFFFF)
			{
//			if(Touch.x<230&&Touch.x>160&&Touch.y<300&&Touch.y>260)
//				{		 
//					return 1;         //��������ʼ��
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
			else if(Touch.x<80&&Touch.x>0&&Touch.y<320&&Touch.y>280)  //��
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
			else if(Touch.x<240&&Touch.x>160&&Touch.y<320&&Touch.y>280)  //���ټ�
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
	
	/* Ӳ����ʼ�� */
	Led_Init();               //LED�Ƴ�ʼ��
	Beep_Init();              //��������ʼ
	LCD_Init();               //Һ������ʼ��
	Touch_Init();             //��������ʼ��                    
	myadc_Init();   					//adc��ʼ��
	while(1)
	{
			if(flag == 0)//��������ҳ��
			{
				 TOUCH_fh();
			}
			if(flag == 1)//���뷵��ҳ��
			{
				TOUCH_Sz();
			}	
			if(flag == 2)//�������ҳ��
			{
				TOUCH_JP();
			}
			if(flag == 3)//�������ҳ��1
			{
				TOUCH_JP1();
			}
	}
}
	















