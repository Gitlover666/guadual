#include "ili9341.h"

/**************************** LCD对应管脚初始化函数 ****************************
功  能：把LCD液晶屏对应的管脚进行初始化
参  数：无
返回值：无
硬件连接方式：
数据线：
DB0---PD14	DB1---PD15	DB2---PD0	DB3---PD1
DB4---PE7	DB5---PE8	DB6---PE9	DB7---PE10
DB8---PE11	DB9---PE12	DB10---PE13	DB11---PE14
DB12---PE15	DB13---PD8	DB14---PD9	DB15---PD10
控制线：
WR---PD5	RD---PD4	CS---PG12	RS(D/C)---PG0	BL--PB0
*******************************************************************************/
void LCD_Port_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;  //定义GPIO端口结构体变量
	
	/* 使能LCD硬件管脚时钟 */
	RCC_APB2PeriphClockCmd((RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOG 
	                      | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOF),ENABLE);
	
	/* 设置LCD硬件管脚模式 */
	/* DB0~DB15数据线：推挽输出  时钟50M */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_8 | GPIO_Pin_9 |
	                              GPIO_Pin_10 |GPIO_Pin_14 | GPIO_Pin_15;         
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |
	                              GPIO_Pin_11 |GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15; 
	GPIO_Init(GPIOE,&GPIO_InitStructure);
		
	/* 控制线：推挽输出  时钟50M 空闲为高电平 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 ; 
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	GPIO_SetBits(GPIOD,GPIO_Pin_4 | GPIO_Pin_5);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 ; 
	GPIO_Init(GPIOG,&GPIO_InitStructure);
	GPIO_SetBits(GPIOG,GPIO_Pin_12);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 
	GPIO_Init(GPIOG,&GPIO_InitStructure);
	GPIO_SetBits(GPIOG,GPIO_Pin_0);
	
	/* LCD背光 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ; 
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOB, GPIO_Pin_0);         //关闭背光，在LCD初始化完后再打开  
}

/**************************** LCD显示控制器写命令函数 ****************************
功  能：MUC把相应的控制命令发送到显示控制器
参  数：需要输入的命令
返回值：无
发送方式：
GPIO_SetBits()    --- 发送数据“1”
GPIO_ResetBits()  --- 发送数据“0”
********************************************************************************/
void LCD_ILI9341_CMD(u16 common)
{
	GPIO_ResetBits(GPIOG, GPIO_Pin_12);  //CS拉低
	GPIO_ResetBits(GPIOG, GPIO_Pin_0);   //D/C拉低
	GPIO_ResetBits(GPIOD, GPIO_Pin_5);   //WR拉低
	/* 把命令发送到数据总线 */
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
	GPIO_SetBits(GPIOD,GPIO_Pin_5);       //WR拉高
	GPIO_SetBits(GPIOG,GPIO_Pin_12);      //拉高CS
}

/**************************** LCD显示控制器写数据函数 ****************************
功  能：MUC把相应的显示数据或控制参数发送到显示控制器
参  数：需要发送的显示数据或控制参数
返回值：无
发送方式：
GPIO_SetBits()    --- 发送数据“1”
GPIO_ResetBits()  --- 发送数据“0”
********************************************************************************/
void LCD_ILI9341_Parameter(u16 data)
{
	GPIO_ResetBits(GPIOG, GPIO_Pin_12);  //CS拉低
	GPIO_SetBits(GPIOG, GPIO_Pin_0);     //D/C拉高
	GPIO_ResetBits(GPIOD, GPIO_Pin_5);   //WR拉低
	/* 把数据发送到数据总线 */
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
	GPIO_SetBits(GPIOD,GPIO_Pin_5);       //WR拉高
	GPIO_SetBits(GPIOG,GPIO_Pin_12);      //拉高CS
}

/********************** 进入睡眠函数 *******************************************/
void LCD_EnterSleep_ILI9341(void)
{
	LCD_ILI9341_CMD(0x28); // Display off
	Delay_ms(20);
	LCD_ILI9341_CMD(0x10); // Enter Sleep mode
}

/********************** 退出睡眠函数 *******************************************/
void LCD_ExitSleep_ILI9341(void)
{
	LCD_ILI9341_CMD(0x11); // Sleep out
	Delay_ms(120);
	LCD_ILI9341_CMD(0x29); // Display on
}

/**************************** LCD液晶屏清屏函数 ****************************
功  能：设置LCD液晶显示屏的屏幕底色
参  数：SX、EX：X轴的起始坐标和结束坐标
		SY、EY：Y轴的起始坐标和结束坐标
		Color： 屏幕颜色
返回值：无
***************************************************************************/
void LCD_Clear(u16 SX, u16 EX, u16 SY, u16 EY, u16 Color)
{
	u32 i;
	
	LCD_ILI9341_CMD(0x2A);                      //发送0x2A命令，设置X轴坐标
	LCD_ILI9341_Parameter((SX & 0xff00) >> 8);  //发送X轴起始坐标的高8位
	LCD_ILI9341_Parameter((SX & 0x00ff));       //发送X轴起始坐标的低8位
	LCD_ILI9341_Parameter((EX & 0xff00) >> 8);  //发送X轴结束坐标的高8位
	LCD_ILI9341_Parameter((EX & 0x00ff));       //发送X轴结束坐标的低8位
	
	LCD_ILI9341_CMD(0x2B);                      //发送0x2B命令，设置Y轴坐标
	LCD_ILI9341_Parameter((SY & 0xff00) >> 8);  //发送Y轴起始坐标的高8位
	LCD_ILI9341_Parameter((SY & 0x00ff));       //发送Y轴起始坐标的低8位
	LCD_ILI9341_Parameter((EY & 0xff00) >> 8);  //发送Y轴结束坐标的高8位
	LCD_ILI9341_Parameter((EY & 0x00ff));       //发送Y轴结束坐标的低8位
	
	LCD_ILI9341_CMD(0x2C);                      //发送0x2A命令，设置LCD显示颜色
	for(i = 0; i < (EX - SX + 1) * (EY - SY + 1); i++)  //循环清屏区域的每一个像素点
	{
		LCD_ILI9341_Parameter(Color);
	}
}

/**************************** LCD液晶屏初始化函数 ****************************
功  能：把LCD液晶屏进行初始化设置
参  数：无
返回值：无
初始化代码由液晶屏厂家提供，用户需要按实际使用方式修改部分参数
*****************************************************************************/
void LCD_Init(void)
{
	LCD_Port_Init();     //初始化引脚
	
	// VCI=2.8V
	//************* Reset LCD Driver ****************//
	//复位信号接到我们单片机的复位引脚
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
	
	/* 由用户根据实际情况进行设置 */
	LCD_ILI9341_CMD(0x3A);          //发送设置颜色位深命令
	LCD_ILI9341_Parameter(0x55);    //把LCD显示控制器设置为16BPP
	LCD_ILI9341_CMD(0x36);          //发送设置显示控制器扫描方向
	LCD_ILI9341_Parameter(0x08);    //扫描方向为从上到下，从左到右
	LCD_ExitSleep_ILI9341();        //退出睡眠状态
	LCD_Clear(0,239,0,319,0x2744);  //LCD液晶屏清屏
	GPIO_SetBits(GPIOB,GPIO_Pin_0); //开启液晶屏背光灯
}






