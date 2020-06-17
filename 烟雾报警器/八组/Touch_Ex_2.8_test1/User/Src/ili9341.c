#include "ili9341.h"

/**************************** LCD��Ӧ�ܽų�ʼ������ ****************************
��  �ܣ���LCDҺ������Ӧ�ĹܽŽ��г�ʼ��
��  ������
����ֵ����
Ӳ�����ӷ�ʽ��
�����ߣ�
DB0---PD14	DB1---PD15	DB2---PD0	DB3---PD1
DB4---PE7	DB5---PE8	DB6---PE9	DB7---PE10
DB8---PE11	DB9---PE12	DB10---PE13	DB11---PE14
DB12---PE15	DB13---PD8	DB14---PD9	DB15---PD10
�����ߣ�
WR---PD5	RD---PD4	CS---PG12	RS(D/C)---PG0	BL--PB0
*******************************************************************************/
void LCD_Port_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;  //����GPIO�˿ڽṹ�����
	
	/* ʹ��LCDӲ���ܽ�ʱ�� */
	RCC_APB2PeriphClockCmd((RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOG 
	                      | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOF),ENABLE);
	
	/* ����LCDӲ���ܽ�ģʽ */
	/* DB0~DB15�����ߣ��������  ʱ��50M */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_8 | GPIO_Pin_9 |
	                              GPIO_Pin_10 |GPIO_Pin_14 | GPIO_Pin_15;         
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |
	                              GPIO_Pin_11 |GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15; 
	GPIO_Init(GPIOE,&GPIO_InitStructure);
		
	/* �����ߣ��������  ʱ��50M ����Ϊ�ߵ�ƽ */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 ; 
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	GPIO_SetBits(GPIOD,GPIO_Pin_4 | GPIO_Pin_5);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 ; 
	GPIO_Init(GPIOG,&GPIO_InitStructure);
	GPIO_SetBits(GPIOG,GPIO_Pin_12);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 
	GPIO_Init(GPIOG,&GPIO_InitStructure);
	GPIO_SetBits(GPIOG,GPIO_Pin_0);
	
	/* LCD���� */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ; 
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOB, GPIO_Pin_0);         //�رձ��⣬��LCD��ʼ������ٴ�  
}

/**************************** LCD��ʾ������д����� ****************************
��  �ܣ�MUC����Ӧ�Ŀ�������͵���ʾ������
��  ������Ҫ���������
����ֵ����
���ͷ�ʽ��
GPIO_SetBits()    --- �������ݡ�1��
GPIO_ResetBits()  --- �������ݡ�0��
********************************************************************************/
void LCD_ILI9341_CMD(u16 common)
{
	GPIO_ResetBits(GPIOG, GPIO_Pin_12);  //CS����
	GPIO_ResetBits(GPIOG, GPIO_Pin_0);   //D/C����
	GPIO_ResetBits(GPIOD, GPIO_Pin_5);   //WR����
	/* ������͵��������� */
	if(common & 0x01)   GPIO_SetBits(GPIOD,GPIO_Pin_14); else GPIO_ResetBits(GPIOD, GPIO_Pin_14);
	if(common & 0x02)   GPIO_SetBits(GPIOD,GPIO_Pin_15); else GPIO_ResetBits(GPIOD, GPIO_Pin_15);
	if(common & 0x04)   GPIO_SetBits(GPIOD,GPIO_Pin_0);  else GPIO_ResetBits(GPIOD, GPIO_Pin_0);
	if(common & 0x08)   GPIO_SetBits(GPIOD,GPIO_Pin_1);  else GPIO_ResetBits(GPIOD, GPIO_Pin_1);
	if(common & 0x10)   GPIO_SetBits(GPIOE,GPIO_Pin_7);  else GPIO_ResetBits(GPIOE, GPIO_Pin_7);
	if(common & 0x20)   GPIO_SetBits(GPIOE,GPIO_Pin_8);  else GPIO_ResetBits(GPIOE, GPIO_Pin_8);
	if(common & 0x40)   GPIO_SetBits(GPIOE,GPIO_Pin_9);  else GPIO_ResetBits(GPIOE, GPIO_Pin_9);
	if(common & 0x80)   GPIO_SetBits(GPIOE,GPIO_Pin_10); else GPIO_ResetBits(GPIOE, GPIO_Pin_10);
	if(common & 0x0100) GPIO_SetBits(GPIOE,GPIO_Pin_11); else GPIO_ResetBits(GPIOE, GPIO_Pin_11);
	if(common & 0x0200) GPIO_SetBits(GPIOE,GPIO_Pin_12); else GPIO_ResetBits(GPIOE, GPIO_Pin_12);
	if(common & 0x0400) GPIO_SetBits(GPIOE,GPIO_Pin_13); else GPIO_ResetBits(GPIOE, GPIO_Pin_13);
	if(common & 0x0800) GPIO_SetBits(GPIOE,GPIO_Pin_14); else GPIO_ResetBits(GPIOE, GPIO_Pin_14);
	if(common & 0x1000) GPIO_SetBits(GPIOE,GPIO_Pin_15); else GPIO_ResetBits(GPIOE, GPIO_Pin_15);
	if(common & 0x2000) GPIO_SetBits(GPIOD,GPIO_Pin_8);  else GPIO_ResetBits(GPIOD, GPIO_Pin_8);
	if(common & 0x4000) GPIO_SetBits(GPIOD,GPIO_Pin_9);  else GPIO_ResetBits(GPIOD, GPIO_Pin_9);
	if(common & 0x8000) GPIO_SetBits(GPIOD,GPIO_Pin_10); else GPIO_ResetBits(GPIOD, GPIO_Pin_10);
	GPIO_SetBits(GPIOD,GPIO_Pin_5);       //WR����
	GPIO_SetBits(GPIOG,GPIO_Pin_12);      //����CS
}

/**************************** LCD��ʾ������д���ݺ��� ****************************
��  �ܣ�MUC����Ӧ����ʾ���ݻ���Ʋ������͵���ʾ������
��  ������Ҫ���͵���ʾ���ݻ���Ʋ���
����ֵ����
���ͷ�ʽ��
GPIO_SetBits()    --- �������ݡ�1��
GPIO_ResetBits()  --- �������ݡ�0��
********************************************************************************/
void LCD_ILI9341_Parameter(u16 data)
{
	GPIO_ResetBits(GPIOG, GPIO_Pin_12);  //CS����
	GPIO_SetBits(GPIOG, GPIO_Pin_0);     //D/C����
	GPIO_ResetBits(GPIOD, GPIO_Pin_5);   //WR����
	/* �����ݷ��͵��������� */
	if(data & 0x01)   GPIO_SetBits(GPIOD,GPIO_Pin_14); else GPIO_ResetBits(GPIOD, GPIO_Pin_14);
	if(data & 0x02)   GPIO_SetBits(GPIOD,GPIO_Pin_15); else GPIO_ResetBits(GPIOD, GPIO_Pin_15);
	if(data & 0x04)   GPIO_SetBits(GPIOD,GPIO_Pin_0);  else GPIO_ResetBits(GPIOD, GPIO_Pin_0);
	if(data & 0x08)   GPIO_SetBits(GPIOD,GPIO_Pin_1);  else GPIO_ResetBits(GPIOD, GPIO_Pin_1);
	if(data & 0x10)   GPIO_SetBits(GPIOE,GPIO_Pin_7);  else GPIO_ResetBits(GPIOE, GPIO_Pin_7);
	if(data & 0x20)   GPIO_SetBits(GPIOE,GPIO_Pin_8);  else GPIO_ResetBits(GPIOE, GPIO_Pin_8);
	if(data & 0x40)   GPIO_SetBits(GPIOE,GPIO_Pin_9);  else GPIO_ResetBits(GPIOE, GPIO_Pin_9);
	if(data & 0x80)   GPIO_SetBits(GPIOE,GPIO_Pin_10); else GPIO_ResetBits(GPIOE, GPIO_Pin_10);
	if(data & 0x0100) GPIO_SetBits(GPIOE,GPIO_Pin_11); else GPIO_ResetBits(GPIOE, GPIO_Pin_11);
	if(data & 0x0200) GPIO_SetBits(GPIOE,GPIO_Pin_12); else GPIO_ResetBits(GPIOE, GPIO_Pin_12);
	if(data & 0x0400) GPIO_SetBits(GPIOE,GPIO_Pin_13); else GPIO_ResetBits(GPIOE, GPIO_Pin_13);
	if(data & 0x0800) GPIO_SetBits(GPIOE,GPIO_Pin_14); else GPIO_ResetBits(GPIOE, GPIO_Pin_14);
	if(data & 0x1000) GPIO_SetBits(GPIOE,GPIO_Pin_15); else GPIO_ResetBits(GPIOE, GPIO_Pin_15);
	if(data & 0x2000) GPIO_SetBits(GPIOD,GPIO_Pin_8);  else GPIO_ResetBits(GPIOD, GPIO_Pin_8);
	if(data & 0x4000) GPIO_SetBits(GPIOD,GPIO_Pin_9);  else GPIO_ResetBits(GPIOD, GPIO_Pin_9);
	if(data & 0x8000) GPIO_SetBits(GPIOD,GPIO_Pin_10); else GPIO_ResetBits(GPIOD, GPIO_Pin_10);
	GPIO_SetBits(GPIOD,GPIO_Pin_5);       //WR����
	GPIO_SetBits(GPIOG,GPIO_Pin_12);      //����CS
}

/********************** ����˯�ߺ��� *******************************************/
void LCD_EnterSleep_ILI9341(void)
{
	LCD_ILI9341_CMD(0x28); // Display off
	Delay_ms(20);
	LCD_ILI9341_CMD(0x10); // Enter Sleep mode
}

/********************** �˳�˯�ߺ��� *******************************************/
void LCD_ExitSleep_ILI9341(void)
{
	LCD_ILI9341_CMD(0x11); // Sleep out
	Delay_ms(120);
	LCD_ILI9341_CMD(0x29); // Display on
}

/**************************** LCDҺ������������ ****************************
��  �ܣ�����LCDҺ����ʾ������Ļ��ɫ
��  ����SX��EX��X�����ʼ����ͽ�������
		SY��EY��Y�����ʼ����ͽ�������
		Color�� ��Ļ��ɫ
����ֵ����
***************************************************************************/
void LCD_Clear(u16 SX, u16 EX, u16 SY, u16 EY, u16 Color)
{
	u32 i;
	
	LCD_ILI9341_CMD(0x2A);                      //����0x2A�������X������
	LCD_ILI9341_Parameter((SX & 0xff00) >> 8);  //����X����ʼ����ĸ�8λ
	LCD_ILI9341_Parameter((SX & 0x00ff));       //����X����ʼ����ĵ�8λ
	LCD_ILI9341_Parameter((EX & 0xff00) >> 8);  //����X���������ĸ�8λ
	LCD_ILI9341_Parameter((EX & 0x00ff));       //����X���������ĵ�8λ
	
	LCD_ILI9341_CMD(0x2B);                      //����0x2B�������Y������
	LCD_ILI9341_Parameter((SY & 0xff00) >> 8);  //����Y����ʼ����ĸ�8λ
	LCD_ILI9341_Parameter((SY & 0x00ff));       //����Y����ʼ����ĵ�8λ
	LCD_ILI9341_Parameter((EY & 0xff00) >> 8);  //����Y���������ĸ�8λ
	LCD_ILI9341_Parameter((EY & 0x00ff));       //����Y���������ĵ�8λ
	
	LCD_ILI9341_CMD(0x2C);                      //����0x2A�������LCD��ʾ��ɫ
	for(i = 0; i < (EX - SX + 1) * (EY - SY + 1); i++)  //ѭ�����������ÿһ�����ص�
	{
		LCD_ILI9341_Parameter(Color);
	}
}

/**************************** LCDҺ������ʼ������ ****************************
��  �ܣ���LCDҺ�������г�ʼ������
��  ������
����ֵ����
��ʼ��������Һ���������ṩ���û���Ҫ��ʵ��ʹ�÷�ʽ�޸Ĳ��ֲ���
*****************************************************************************/
void LCD_Init(void)
{
	LCD_Port_Init();     //��ʼ������
	
	// VCI=2.8V
	//************* Reset LCD Driver ****************//
	//��λ�źŽӵ����ǵ�Ƭ���ĸ�λ����
	Delay_ms(120); // Delay 120 ms
	//************* Start Initial Sequence **********//
	LCD_ILI9341_CMD(0xCF);
	LCD_ILI9341_Parameter (0x00);
	LCD_ILI9341_Parameter (0x83);
	LCD_ILI9341_Parameter (0X30);
	LCD_ILI9341_CMD(0xED);
	LCD_ILI9341_Parameter (0x64);
	LCD_ILI9341_Parameter (0x03);
	LCD_ILI9341_Parameter (0X12);
	LCD_ILI9341_Parameter (0X81);
	LCD_ILI9341_CMD(0xE8);
	LCD_ILI9341_Parameter (0x85);
	LCD_ILI9341_Parameter (0x01);
	LCD_ILI9341_Parameter (0x79);
	LCD_ILI9341_CMD(0xCB);
	LCD_ILI9341_Parameter (0x39);
	LCD_ILI9341_Parameter (0x2C);
	LCD_ILI9341_Parameter (0x00);
	LCD_ILI9341_Parameter (0x34);
	LCD_ILI9341_Parameter (0x02);
	LCD_ILI9341_CMD(0xF7);
	LCD_ILI9341_Parameter (0x20);

	LCD_ILI9341_CMD(0xEA);
	LCD_ILI9341_Parameter (0x00);
	LCD_ILI9341_Parameter (0x00);
	LCD_ILI9341_CMD(0xC0); //Power control
	LCD_ILI9341_Parameter (0x1D); //VRH[5:0]
	LCD_ILI9341_CMD(0xC1); //Power control
	LCD_ILI9341_Parameter (0x11); //SAP[2:0];BT[3:0]
	LCD_ILI9341_CMD(0xC5); //VCM control
	LCD_ILI9341_Parameter (0x33);
	LCD_ILI9341_Parameter (0x34);
	LCD_ILI9341_CMD(0xC7); //VCM control2
	LCD_ILI9341_Parameter (0Xbe);
	LCD_ILI9341_CMD(0x36); // Memory Access Control
	LCD_ILI9341_Parameter (0x08);
	LCD_ILI9341_CMD(0xB1);
	LCD_ILI9341_Parameter (0x00);
	LCD_ILI9341_Parameter (0x1B);
	LCD_ILI9341_CMD(0xB6); // Display Function Control
	LCD_ILI9341_Parameter (0x0A);
	LCD_ILI9341_Parameter (0xA2);
	LCD_ILI9341_CMD(0xF2); // 3Gamma Function Disable
	LCD_ILI9341_Parameter (0x00);
	LCD_ILI9341_CMD(0x26); //Gamma curve selected
	LCD_ILI9341_Parameter (0x01);
	LCD_ILI9341_CMD(0xE0); //Set Gamma
	LCD_ILI9341_Parameter (0x0F);
	LCD_ILI9341_Parameter (0x23);
	LCD_ILI9341_Parameter (0x1F);

	LCD_ILI9341_Parameter (0x09);
	LCD_ILI9341_Parameter (0x0f);
	LCD_ILI9341_Parameter (0x08);
	LCD_ILI9341_Parameter (0x4B);
	LCD_ILI9341_Parameter (0Xf2);
	LCD_ILI9341_Parameter (0x38);
	LCD_ILI9341_Parameter (0x09);
	LCD_ILI9341_Parameter (0x13);
	LCD_ILI9341_Parameter (0x03);
	LCD_ILI9341_Parameter (0x12);
	LCD_ILI9341_Parameter (0x07);
	LCD_ILI9341_Parameter (0x04);
	LCD_ILI9341_CMD(0XE1); //Set Gamma
	LCD_ILI9341_Parameter (0x00);
	LCD_ILI9341_Parameter (0x1d);
	LCD_ILI9341_Parameter (0x20);
	LCD_ILI9341_Parameter (0x02);
	LCD_ILI9341_Parameter (0x11);
	LCD_ILI9341_Parameter (0x07);
	LCD_ILI9341_Parameter (0x34);
	LCD_ILI9341_Parameter (0x81);
	LCD_ILI9341_Parameter (0x46);
	LCD_ILI9341_Parameter (0x06);
	LCD_ILI9341_Parameter (0x0e);
	LCD_ILI9341_Parameter (0x0c);
	LCD_ILI9341_Parameter (0x32);
	LCD_ILI9341_Parameter (0x38);
	LCD_ILI9341_Parameter (0x0F);
	
	/* ���û�����ʵ������������� */
	LCD_ILI9341_CMD(0x3A);          //����������ɫλ������
	LCD_ILI9341_Parameter(0x55);    //��LCD��ʾ����������Ϊ16BPP
	LCD_ILI9341_CMD(0x36);          //����������ʾ������ɨ�跽��
	LCD_ILI9341_Parameter(0x08);    //ɨ�跽��Ϊ���ϵ��£�������
	LCD_ExitSleep_ILI9341();        //�˳�˯��״̬
	LCD_Clear(0,239,0,319,0x2744);  //LCDҺ��������
	GPIO_SetBits(GPIOB,GPIO_Pin_0); //����Һ���������
}






