#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "exti.h"
#include "beep.h"
#include "dht11.h"
#include "bh1750.h"
/************************************************
 ALIENTEK战舰STM32开发板实验5
 外部中断实验   
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/

 int main(void)
 {		
  static u8 temp, hum;
	static u16 GQ_Data;
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);		//串口初始化为115200
 	LED_Init();		  		//初始化与LED连接的硬件接口
	BEEP_Init();         	//初始化蜂鸣器端口
	KEY_Init();         	//初始化与按键连接的硬件接口
	EXTIX_Init();		 	//外部中断初始化
	DHT11_Init();
	LED0=0;					//点亮LED0
	BH1750_Init();
	while(1)
	{	    
//	  GQ_Data = BH1750_ReadContinuous1();	
		DHT11_Read_Data(&temp,&hum);
		printf("温度=%d               湿度=%d\r\n", temp, hum);
//		printf("湿度=%d\r\n", GQ_Data);
		delay_ms(1000);	  
	}
 }

