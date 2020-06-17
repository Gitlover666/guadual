#include "usart.h"

/**************************** USART_1模块初始化函数 ****************************
功  能：对USART_1模块进行初始化设置
参  数：串口数据传输波特率
返回值：无
硬件连接：
USART1_RX --- PA10；USART1_TX --- PA9
*********************************************************************************/
void USART_1_Init(u32 Boand)
{
	GPIO_InitTypeDef GPIO_InitStruct;//GPIO口
	USART_InitTypeDef USART_InitStruct;//串口
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	//设置10为输入
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	//设置9为输出
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;//配置为复用管脚
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//初始化串口（通信协议以及波特率）
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStruct.USART_BaudRate = Boand;
	
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART1,&USART_InitStruct);
	
	USART_Cmd(USART1,ENABLE);
}

/**************************** USART_1发送字符串函数 ****************************
功  能：USART_1模块发送一个字符串数据
参  数：需要发送的字符串数据
返回值：无
*********************************************************************************/
void Usart_Send_Str(char *Str)
{
	while( *Str != '\0' )
	{
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == 0)
		{
			/* 等待发送完成 */
		}
		USART_SendData(USART1,*Str);
		Str++;
		
	}
}

/**************************** USART_1接收字符函数 ****************************
功  能：USART_1模块接收一个字符数据
参  数：无
返回值：返回接收到的字符数据
*********************************************************************************/
char Usart_Rec_Byte(void)
{
	char Temp = 0;
	
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == 0)
	{
		/* 等待接收完成 */
	}
	USART_SendData(USART1,Temp);
	
	return Temp;
}

/**************************** USART_1打印函数 ****************************
使用串口打印函数步骤：
1.包含stdio.h头文件
2.在魔术棒中的Target选项卡中勾选"Use Micro LIB"选项
3.该函数系统自动调用，不需要人为使用
**************************************************************************/
int fputc(int ch, FILE *stream)
{
	USART_SendData(USART1,ch);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == 0)
	{
		/* 等待发送完成 */
	}
	return ch;
}


