/**************************************************************************************************

名称           引脚                       通信协议
esp8266        PA9(T) PA10(R)            机智云串口通信协议Gagent
DHT11          PB9                       串口通信
OLED           PB6(SCL)  PB7(SDA)        IIC
GY-30          PB10(T) PB11(R)           IIC

*****************************************************************************************************/
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "dht11.h"
#include "timer.h"
#include "usart3.h"
#include "beep.h"
#include "oled.h"
#include "BH1750.h"
#include "gizwits_product.h"


//extern void Picture(u8 i);

/* 用户区当前设备状态结构体*/
dataPoint_t currentDataPoint;
#define Temp_Q 32 //温度上限（单位：C）
#define Humi_alarm 90 //湿度上限（单位：%）
//协议初始化
void Gizwits_Init(void)
{
    TIM3_Int_Init(9,7199);//1MS系统定时
//  usart3_init(9600);//WIFI初始化
    uart_init(9600);//这里的波特率只能是9600
    memset((uint8_t*)&currentDataPoint, 0, sizeof(dataPoint_t));//设备状态结构体初始化
    gizwitsInit();//缓冲区初始化
}
//数据采集
void userHandle(void)
{   
    static u16 GQ_Data;//这个光强传感器的参数当使用extern是会出现数据不能正常显示的问题。
    static u8 temp, hum;
//	static u8 temp_num = 0;
//  static u8 humi_num = 0;
//  static u8 GQ_Data_num = 0;
    if(timeuser > 1000)//每1秒上报一次数据
    {
        timeuser=0;//在.h文件里面已经声明过
        //在oled和app上显示温湿度值
        DHT11_Read_Data(&temp,&hum);//读取 DHT11 传感器
        OLED_ShowNum(48,0,temp/10%10,1,16);//x,y，第三位是数据位，长度，字体大小
				OLED_ShowNum(56,0,temp%10,1,16);
        OLED_ShowNum(48,2,hum/10%10,1,16);
				OLED_ShowNum(56,2,hum%10,1,16);//x,y，第三位是数据位，长度，字体大小
        currentDataPoint.valueTemp = temp ;//温度数据
        currentDataPoint.valueShidu = hum;//湿度数据
        //在oled和app上显示光强数值
        GQ_Data = BH1750_ReadContinuous1();	//读取GY-30传感器
        OLED_ShowNum(48,4,GQ_Data/10000%10,1,16);
				OLED_ShowNum(56,4,GQ_Data/1000%10,1,16);
				OLED_ShowNum(64,4,GQ_Data/100%10,1,16);
				OLED_ShowNum(72,4,GQ_Data/10%10,1,16);
				OLED_ShowNum(80,4,GQ_Data%10,1,16);
        currentDataPoint.valueGQ = GQ_Data;//光强数值
		
        //判断温湿度以及光强是否超出给定值，若超出蜂鸣器响，led亮
        if((temp>=currentDataPoint.valueTemp_AlarmScope||hum>=currentDataPoint.valueShidu_AlarmScope||GQ_Data>=currentDataPoint.valueGQ_AlarmScope)&&(currentDataPoint.valueTemp_AlarmScope!=0&&currentDataPoint.valueShidu_AlarmScope!=0&&currentDataPoint.valueGQ_AlarmScope!=0))//温度>报警值
        {

            if(1 == currentDataPoint.valueLED1)//如果led1发送数据则响，开启警报，自动模式
            {

                currentDataPoint.valueTemp_Q=1;//温度达上限报警
                BEEP = 1;
                LED0 = 0;
                delay_ms(1000);delay_ms(1000);delay_ms(1000);
								//当满足条件关闭蜂鸣器和led。
                currentDataPoint.valueLED = currentDataPoint.valueBEEP = 0;
                currentDataPoint.valueTemp_Q=0;
                BEEP = 0;
                LED0 = 1;
								delay_ms(1000);delay_ms(1000);delay_ms(1000);

            }
        }
    }
}

//主函数
int main(void)
{
    delay_init();	    	 //延时函数初始化
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
    LED_Init();			    //LED端口初始化
    DHT11_Init();
    BEEP_Init();            //蜂鸣器初始化
    OLED_Init();			//初始化OLED
    BH1750_Init();
    Gizwits_Init();         //协议初始化
    //OLED显示“温度”
    OLED_ShowCHinese(0,0,0);  //x,y,第三位是汉字库的次序
    OLED_ShowCHinese(16,0,1);
    OLED_ShowCHinese(32,0,10);
    OLED_ShowCHinese(72,0,8);
    //湿度
    OLED_ShowCHinese(0,2,2);
    OLED_ShowCHinese(16,2,3);
    OLED_ShowCHinese(32,2,10);
    OLED_ShowCHinese(72,2,9);
    //光强
    OLED_ShowCHinese(0,4,4);
    OLED_ShowCHinese(16,4,6);
    OLED_ShowCHinese(32,4,10);
    OLED_ShowString(96,4,"lx",16);//这里lx是光强的单位
    while(1)
    {
        userHandle();//用户采集
        gizwitsHandle((dataPoint_t *)&currentDataPoint);//协议处理
    }
}




