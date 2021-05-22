#include "usart.h"

/* 串口1对应管脚 *
RXD ---> PA10
TXD ---> PA9
******************/

/************* 串口初始化函数 ******************
Pclk：串口1模块时钟
Bound：串口波特率
************************************************/
void Usart1_Init(u32 Pclk, u32 Bound)
{
	float USARTDIV;  //波特率计算值
	u16 Mantissa;    //整数部分
	u16 Fraction;    //小数部分
	
	/* 使能串口模块时钟 */
	RCC->APB2ENR |= 1 << 14;  //使能串口1时钟
	
	/* 设置串口管脚功能 */
	/* STM32外设模块有自己的功能模式
	模块的功能模式参考STM32中文参考手册_V10.pdf
	第110页，外设的GPIO设置
	TXD：推挽复用输出
	RXD：浮空输入或上拉输入*/
	RCC->APB2ENR |= 1 << 2;   //使能GPIOA时钟
	GPIOA->CRH &= 0xfffff00f; //把CRH寄存器4~11位清零
	GPIOA->CRH |= 0x000004b0; //PA9设置为复用推挽，速度50M，PA10设置位浮空输入
	
	/* 设置串口比特率 */
	USARTDIV = (float)(Pclk * 1000000 /(16. * Bound));  //计算波特率值
	Mantissa = USARTDIV;                      //获取整数部分     
	Fraction = (USARTDIV - Mantissa) * 16;    //获取小数部分
	USART1->BRR = (Mantissa << 4) | Fraction; //把波特率计算值写入波特率寄存器
	
	/* 串口模块设置 */
	USART1->CR1 |= 1 << 13;   //使能串口模块
	USART1->CR1 &= ~(1 << 12);//数据长度位8位，不包含校验位
	USART1->CR1 &= ~(1 << 10);//不使用数据校验
	USART1->CR1 |= 1 << 3;    //发送使能
	USART1->CR1 |= 1 << 2;    //接收使能
	
	USART1->CR2 &= ~(3 << 12);//停止位长度为1位停止位
}

/***************** 串口发送字符函数 **************************/
void USART_Send_Str(u8 *dat)
{
	while( *dat != '\0')
	{
		USART1->DR = *dat;
		while(!(USART1->SR & (1 << 7)));       //发送完成
		dat++;
	}
}

/*fputc是printf最底层的调用函数*/
int fputc(int data, FILE* file)
{
	 USART1->DR = data;  //发送数据
	 while(!(USART1->SR & (1<<7))); /*等待发送串口的数据*/
	 return data;
}











