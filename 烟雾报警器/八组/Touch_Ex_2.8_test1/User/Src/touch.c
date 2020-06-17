#include "touch.h"
#include "systick.h"
#include "lcd_gui.h"
#include <stdlib.h>

TOUCH_TYPE_DEF TOUCH_LCD;

/**************************** ������Ӳ���ܽų�ʼ������ ****************************
��  �ܣ��Ѵ�������Ӧ�ĹܽŽ��г�ʼ��
��  ������
����ֵ����
Ӳ�����ӷ�ʽ��
XTP2046    LCD��     MCU
CLK       CLK        PB1       �������
CS        T_CS       PB2       �������
DIN       MOSI       PF9       �������
DOUT      MISO       PF8       ��������
PEN       T_PEN      PF10      ��������
***********************************************************************************/
void Touch_Gpio_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOF,ENABLE);
	
	/* PB2 -- T_CS -- CS  PB1 -- CLK -- DCLK */  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 |GPIO_Pin_2;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	/* PF9 -- MOSI -- DIN */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_Init(GPIOF,&GPIO_InitStructure);
	
	/* PF8 -- MISO -- DOUT PF10 -- T_PEN -- PEN */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOF,&GPIO_InitStructure);	
}

/**************************** ���������ݴ��亯�� ****************************
��  �ܣ�MCU�������ݵ���������������Ӵ�������������ȡ���
��  ������Ҫ���͵�����
����ֵ����ȡ��������
***************************************************************************/
u16 Touch_Get_ADC(u8 common)
{
	u8 i;
	u16 data = 0;
	            
	GPIO_ResetBits(GPIOB,GPIO_Pin_2);     //����Ƭѡ
	
	/* ���Ϳ����ֽ� */
	for(i = 0; i < 8; i++)
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_1); //����ʱ���ߣ�׼������
		if(common & 0x80)
		{
			GPIO_SetBits(GPIOF,GPIO_Pin_9); //����MOSI�����ߣ����1
		}
		else
		{   
			GPIO_ResetBits(GPIOF,GPIO_Pin_9); //����MOSI�����ߣ����0
		}
		Delay_us(1);  
		GPIO_SetBits(GPIOB,GPIO_Pin_1);      //ʱ�Ӳ��������أ���������
		Delay_us(1);
		common <<= 1;
	}
	
	/* ����һ������ʱ�� */
	GPIO_ResetBits(GPIOB,GPIO_Pin_1);	
	Delay_us(1);	
	GPIO_SetBits(GPIOB,GPIO_Pin_1);
	Delay_us(1);
	GPIO_ResetBits(GPIOB,GPIO_Pin_1);

	/* ������ */
	for(i = 0; i < 12; i++)
	{
		data <<= 1;          
		GPIO_ResetBits(GPIOB,GPIO_Pin_1);   //����ʱ���ߣ�׼������
		Delay_us(1);          
		GPIO_SetBits(GPIOB,GPIO_Pin_1);     //ʱ�Ӳ��������أ���������
		if( GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_8) )
		{
			data |= 1;
		}
		Delay_us(1);
	}
	
	/* ����״̬ */            
	GPIO_ResetBits(GPIOB,GPIO_Pin_1);    //����ʱ����             
	GPIO_SetBits(GPIOB,GPIO_Pin_2);     //����Ƭѡ              
	GPIO_ResetBits(GPIOF,GPIO_Pin_9);   //����������

	return data;
}

/**************************** �����������ȡ���� ****************************
��  �ܣ���ȡ������ADCת�����������
��  ������
����ֵ����ȡ��������X��Y������ֵ
***************************************************************************/
TOUCH_TYPE_DEF Touch_Get_XY(void)
{
	TOUCH_TYPE_DEF touch;
	u16 buff[10],temp;
	u8 i,j;
	
	/* ��ȡX������ADֵ */
	for(i = 0; i < 10; i++)
	{
		buff[i] = Touch_Get_ADC(0xD0);    //��ȡX��ADֵ
	}
	
	/* �������� */
	for(i = 0; i < 10; i++)
	{
		for(j = i + 1; j < 9; j++)
		{
			if(buff[i] < buff[j])
			{
				temp = buff[i];
				buff[i] = buff[j];
				buff[j] = temp;
			}
		}
	}
	temp = 0;
	for(i = 1; i < 9; i++)   //ȥ����ߺ����
	{
		temp += buff[i];
	}
	/* ��ƽ���� */
	touch.x = temp / 8;     
	
	/* ��ȡY������ADֵ */
	for(i = 0; i < 10; i++)
	{
		buff[i] = Touch_Get_ADC(0x90);    //��ȡY��ADֵ
	}
	
	/* �������� */
	for(i = 0; i < 10; i++)
	{
		for(j = i + 1; j < 9; j++)
		{
			if(buff[i] < buff[j])
			{
				temp = buff[i];
				buff[i] = buff[j];
				buff[j] = temp;
			}
		}
	}
	temp = 0;
	for(i = 1; i < 9; i++)
	{
		temp += buff[i];
	}
	 /* ��ƽ���� */
	touch.y = temp / 8;  
	
	return touch;
}


/**************************** ��������ʼ��У׼���� ****************************
��  �ܣ������Kx��Bx��Ky��By��ֵ
��  ������
����ֵ����
У׼��ʽ���ĵ�У׼
*****************************************************************************/
void Touch_Adj_Init(void)
{
	float f1,f2;
	TOUCH_TYPE_DEF touch[4];

RE_ADJUST:
	//��һ����
	TP_draw_adjust_point(20, 20, 0xf800);         //��һ��ʮ��
	while( GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_10) )      
	{
		/* �ȴ������������� */
	}
	Delay_ms(10);                                 //��ʱȥ��
	touch[0]=Touch_Get_XY( );                     //��ȡ��������XY��ֵ
	while( !(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_10)) )   
	{
		/* �ȴ��ͷŴ����� */
	}	
	TP_draw_adjust_point(20 ,20,0x2744);           //�����һ��ʮ��
	
	//�ڶ�����
	TP_draw_adjust_point((240 - 20),20, 0xf800);       //��һ��ʮ��
	while( GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_10) )      
	{
		/* �ȴ������������� */
	}
	Delay_ms(10);                     //��ʱȥ��
	touch[1]=Touch_Get_XY( );                //��ȡ��������XY��ֵ
	while( !(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_10)) )  
	{
		/* �ȴ��ͷŴ����� */
	}	
	TP_draw_adjust_point((240- 20), 20, 0x2744);         //����ڶ���ʮ��
	
	//��������
	TP_draw_adjust_point(20, (320 - 20), 0xf800);         //��һ��ʮ��
	while( GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_10) )      
	{
		/* �ȴ������������� */
	}
	Delay_ms(10);                       //��ʱȥ��
	touch[2]=Touch_Get_XY( );                  //��ȡ��������XY��ֵ
	while( !(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_10)) )  
	{
		/* �ȴ��ͷŴ����� */
	}	
	TP_draw_adjust_point(20,(320 - 20), 0x2744);           //���������ʮ��
	
	//���ĸ���
	TP_draw_adjust_point((240- 20), (320 - 20), 0xf800);     //��һ��ʮ��
	while( GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_10) )      
	{
		/* �ȴ������������� */
	}
	Delay_ms(10);                         //��ʱȥ��
	touch[3]=Touch_Get_XY( );                    //��ȡ��������XY��ֵ
	while( !(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_10)) )  
	{
		/* �ȴ��ͷŴ����� */
	}	
	TP_draw_adjust_point((240- 20), (320 - 20), 0x2744);     //������ĸ�ʮ��
	
	//�� 1 2���ľ����ƽ��
	f1=(touch[1].x-touch[0].x)*(touch[1].x-touch[0].x) +
	   (touch[1].y-touch[0].y)*(touch[1].y-touch[0].y);
	
	//��3 4���ľ����ƽ��
	f2=(touch[3].x-touch[2].x)*(touch[3].x-touch[2].x) +
	   (touch[3].y-touch[2].y)*(touch[3].y-touch[2].y);
	
	if(f1 / f2 > 1.1 || f1 / f2 < 0.9)
	{
		goto RE_ADJUST;
	}
	
	//�� 1 3���ľ����ƽ��
	f1=(touch[2].x-touch[0].x)*(touch[2].x-touch[0].x) +
	   (touch[2].y-touch[0].y)*(touch[2].y-touch[0].y);
	
	//��2 4���ľ����ƽ��
	f2=(touch[3].x-touch[1].x)*(touch[3].x-touch[1].x) +
	   (touch[3].y-touch[1].y)*(touch[3].y-touch[1].y);
	
	if(f1 / f2 > 1.1 || f1 / f2 < 0.9)
	{
		goto RE_ADJUST;
	}
	
	//�� 1 4���ľ����ƽ��
	f1 = (touch[3].x-touch[0].x)*(touch[3].x-touch[0].x) +
	     (touch[3].y-touch[0].y)*(touch[3].y-touch[0].y);
	
	//��2 3���ľ����ƽ��
	f2 = (touch[2].x-touch[1].x)*(touch[2].x-touch[1].x) +
	     (touch[2].y-touch[1].y)*(touch[2].y-touch[1].y);
	
	if(f1 / f2 > 1.1 || f1 / f2 < 0.9)
	{
		goto RE_ADJUST;
	}
	
	//��x����ı���ϵ����ƫ����
	TOUCH_LCD.kx =(float)((240 - 20) - 20) / (touch[3].x - touch[0].x);
	TOUCH_LCD.offset_x = 20 - TOUCH_LCD.kx * touch[0].x;
	//��y����ı���ϵ����ƫ����
	TOUCH_LCD.ky = (float)((320 - 20) - 20) / (touch[3].y - touch[0].y);
	TOUCH_LCD.offset_y = 20 - TOUCH_LCD.ky * touch[0].y;

}

/**************************** ����������ת����LCD���꺯�� ****************************
��  �ܣ��Ѵ������������LCDҺ������ʵ�������������
��  ������
����ֵ����
���㹫ʽ��Lcd���� = f(����ϵ��) * Toch���� + offset(ƫ����
************************************************************************************/
TOUCH_TYPE_DEF Touch_Lcd(void)
{
	TOUCH_TYPE_DEF a1,a2;
	
	a1 = Touch_Get_XY( );                              //��ȡ������ADת��ֵ
		a1.x=TOUCH_LCD.kx *a1.x +TOUCH_LCD.offset_x;
		a1.y=TOUCH_LCD.ky *a1.y +TOUCH_LCD.offset_y;
	
	a2 = Touch_Get_XY( );                              //��ȡ������ADת��ֵ
		a2.x=TOUCH_LCD.kx *a2.x +TOUCH_LCD.offset_x; 
		a2.y=TOUCH_LCD.ky *a2.y +TOUCH_LCD.offset_y;
	
	if(abs(a1.x-a2.x)<5 &&abs(a1.y-a2.y)<5)
	{
		a1.x=(a1.x+a2.x)/2;
		a1.y=(a1.y+a2.y)/2;
	}
	else
	{
		a1.x=0xffff;
		a1.y=0xffff;
	}
	
	return a1;
}

/**************************** ����������ɨ�躯�� ****************************
��  �ܣ���ȡ����������ֵ
��  ������
����ֵ�����ش�������ʵʱ�������꣬û�д���touchkey.xΪ0xFFFF
***************************************************************************/
TOUCH_TYPE_DEF Touch_Scanf(void)
{
	static u8 Touch_Sta = 1;
	
	TOUCH_TYPE_DEF touch_key[2];
	TOUCH_TYPE_DEF touchkey = {0xffff,0xffff};
	
	if( (Touch_Sta == 1)&&(!(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_10))) )            //�����Ⲣ�Ҵ������а���
	{
		
		Delay_ms(5);                                     //��ʱȥ��
		if( !(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_10)) )
		{
			
			touch_key[0] = Touch_Lcd();
			touch_key[1] = Touch_Lcd();
			
			/* ��ƽ��ֵ */
			if( (abs(touch_key[0].x -touch_key[1].x)<5) &&
			    (abs(touch_key[0].y -touch_key[1].y)<5) )       //ʶ��������Ч
			{
				touchkey.x = (touch_key[0].x +touch_key[1].x)/2;
				touchkey.y = (touch_key[0].y +touch_key[1].y)/2;    
				
				Touch_Sta=0;                                     //������ʶ��

			}
			else
			{
				touch_key[0].x = 0xffff;
				touch_key[0].y = 0xffff;
			}
		}
	}
	else if( GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_10) )
	{
		Touch_Sta = 1;                                           //����ʶ��
	}
	
	return touchkey;
}


/**************************** ��������ʼ������ ****************************
��  �ܣ���ʼ��������
��  ������
����ֵ����
***************************************************************************/
void Touch_Init(void)
{
	Touch_Gpio_Init();         //������Ӳ����ʼ��
	Touch_Adj_Init();          //������У׼
}

/**************************** ���������ܰ�����⺯�� ****************************
��  �ܣ�ͨ�������ȡʵ�ʵİ�������
��  ������
����ֵ�����ⰴ��ֵ���޴�������ʱ����0
***************************************************************************/
u8 Touch_Get_Mainkeynum(void)
{
	TOUCH_TYPE_DEF Touch;
	u16 x,y;
	u8 rekey = 0;
	
	
	Touch = Touch_Scanf();       //��ȡ����λ�õľ�������
	
	if(Touch.x != 0xffff)        //�жϴ������Ƿ��в���
	{
		/* ��ȡ��������ֵ */
		x = Touch.x;
		y = Touch.y;
		
		/* �жϴ������Ƿ��ڿ���LED�ƹ���ͼƬ��Χ�� */
		if(x >= 45 && x <= 195 && y >= 5 && y <= 155)
		{
			rekey = 1;          //������������LED����ͼ���ڣ�����1
		}
		/* �жϴ������Ƿ��ڿ���BEEP����ͼƬ��Χ�� */
		else if(x >= 45 && x <= 195 && y >= 165 && y <= 320)
		{
			rekey = 2;          //������������BEEP����ͼ���ڣ�����1
		}
		
		/* �������������� */
		Touch.x = 0;
		Touch.y = 0;
	}
	return rekey;
}







