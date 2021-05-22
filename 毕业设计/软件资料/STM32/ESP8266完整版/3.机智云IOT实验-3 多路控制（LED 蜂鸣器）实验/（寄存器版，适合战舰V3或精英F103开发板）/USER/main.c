#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 
#include "key.h"
#include "timer.h" 
#include "usart3.h"
#include "beep.h"
#include "gizwits_product.h" 
/************************************************
 ALIENTEK战舰V3\精英STM32开发板
 机智云-IOT_LED 测试实验
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/

/* 用户区当前设备状态结构体*/
dataPoint_t currentDataPoint;

//协议初始化
void Gizwits_Init(void)
{
	
	TIM3_Int_Init(9,7199);//1MS系统定时
    usart3_init(36,9600);	//WIFI初始化
	memset((uint8_t*)&currentDataPoint, 0, sizeof(dataPoint_t));//设备状态结构体初始化
	gizwitsInit();//缓冲区初始化
}
//数据采集
void userHandle(void)
{

	
}
//主函数
int main(void)
{	
    int key;	
	Stm32_Clock_Init(9);	//系统时钟设置
	uart_init(72,115200); 	//串口初始化为115200
	delay_init(72);	   	 	//延时初始化 
	LED_Init();		  		//初始化与LED连接的硬件接口
 	KEY_Init();             //按键初始化 
    BEEP_Init();            //蜂鸣器初始化	
	Gizwits_Init();         //协议初始化
	printf("--------机智云IOT-多路控制实验----------\r\n");
	printf("KEY1:AirLink连接模式\t KEY_UP:复位\r\n\r\n");
   	while(1)
	{
	    userHandle();//用户采集
         
        gizwitsHandle((dataPoint_t *)&currentDataPoint);//协议处理
 		
	}	
}	 
