#include "usart.h"
/*
//TXD  -->  PA9  (UART1-TXD)
//RXD  -->  PA10 (UART1-RXD)
------------------------------
*/

u8 TxBuffer[258];
u8 TxCounter=0;
u8 count=0; 

void USART1_init(u32 baudrate)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure; 
	/* 使能 UART1 模块的时钟  使能 UART1对应的引脚端口PA的时钟*/
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);

		//配置UART1 的发送引脚
	
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;// 为复用输出 
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);    

	 // 配置UART1 的接收引脚
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入 
  	GPIO_Init(GPIOA, &GPIO_InitStructure);
	  
		
		USART_InitStructure.USART_BaudRate = baudrate;//	  1.波特率为调用程序指定的输入 baudrate;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;//	  2. 8位数据			  USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;//	  3.一个停止位			  USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No ;//	  4. 无奇偶效验			  USART_Parity_No ;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//	  5.不使用硬件流控制	  USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//	  6.使能发送和接收功能	  USART_Mode_Rx | USART_Mode_Tx;
	//应用配置到UART1
		USART_Init(USART1, &USART_InitStructure); 
		USART_ITConfig(USART1, USART_IT_TXE, DISABLE);  
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);        
		USART_ClearFlag(USART1,USART_FLAG_TC);

   /* Enable the USART1 Interrupt */
     NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
		 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 7;
     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
     NVIC_Init(&NVIC_InitStructure);
	//启动UART1
	
		USART_Cmd(USART1, ENABLE);
		USART_ITConfig(USART1, USART_IT_TXE, ENABLE); // 使能或者失能指定的 USART 中断

}

void USART1_IRQHandler(void)
{

	if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)
		{   
			USART_SendData(USART1, TxBuffer[TxCounter++]); 
			if(TxCounter == count) 
			{
				USART_ITConfig(USART1, USART_IT_TXE, DISABLE);// 全部发送完成
			}
			USART_ClearITPendingBit(USART1, USART_IT_TXE); //清除 USART1 的中断待处理位
		}
	else if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {
			USART_ClearITPendingBit(USART1, USART_IT_RXNE);
  }
	USART_ClearITPendingBit(USART1,USART_IT_ORE);
//	USART_SendData(USART1,8);
}

void SendString(char * buf1)
{  u8 i=0;
   while (1)
   {  if (buf1[i]!=0)
     {  USART_SendData(USART1, buf1[i]);  //发送一个byte到串口
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET){}; //等待发送结束
        i++;
     }
     else return;
   }
//	  USART_SendData(USART1,'\n');
}

void USART2_init(u32 bound)
{
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//使能USART2，GPIOA时钟
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	//USART2_TX   GPIOA.2
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.2
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.2
   
  //USART2_RX	  GPIOA.3初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA3
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.3 

  //Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//抢占优先级2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART2, &USART_InitStructure); //初始化串口2
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART2, ENABLE);                    //使能串口2

}

void USART2_IRQHandler(void)                	//串口2中断服务程序
{
//	u8 Res,i; 
//	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
//		{
//			
//			Res =USART_ReceiveData(USART2);	//读取接收到的数据	
//			for(i=0;i<30;i++)
//			{
////				table[i]=Res;	
//				Res=0;
//			}
//		//	USART_SendData(USART1,Res);	
//		}
////	USART_ClearITPendingBit(USART2,USART_IT_RXNE);
}

void SendString2(char * buf1)
{  u8 i=0;
   while (1)
   {  if (buf1[i]!=0)
     {  USART_SendData(USART2, buf1[i]);  //发送一个byte到串口
        while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET){}; //等待发送结束
        i++;
     }
     else return;
   }
//	  USART_SendData(USART2,'\n');
}


