#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "string.h"
 
/************************************************
 ALIENTEKս��STM32������ʵ��4
 ����ʵ�� 
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/


 int main(void)
 {		
 	u16 t;  
	u16 len;	
	u16 times=0;
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
 	LED_Init();			     //LED�˿ڳ�ʼ��
	KEY_Init();          //��ʼ���밴�����ӵ�Ӳ���ӿ�
 	while(1)
	{
    for(t=0; t<20; t++)
		{
		
//		printf("{\"wz\":\"wenzheng.club\",\"server\":\"106.13.150.28\",\"user\":\"785507435\",\"password\":\"stm32\",\"topic\":\"my_stm\",\"message\":\"%d\"}\r\n", t);
	  printf("{\"wz\":\"wenzheng.club\",\"id\":\"785507435|securemode=3,signmethod=hmacsha1,timestamp=789|\",\"server\":\"a1yPlNVyX6x.iot-as-mqtt.cn-shanghai.aliyuncs.com\",\"user\":\"ESP8266&a1yPlNVyX6x\",\"password\":\"e1d782effd0ef5418c120869e6e1b8f23927d559\",\"topic\":\"/a1yPlNVyX6x/ESP8266/user/set_led\",\"message\":\"%d\"}\r\n", t);
	  delay_ms(1000);
		}
//		if(USART_RX_STA&0x8000)

//		{					   
//			len=USART_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
//			printf("\r\n�����͵���ϢΪ:\r\n\r\n");
//			for(t=0;t<len;t++)
//			{
//				USART_SendData(USART1, USART_RX_BUF[t]);//�򴮿�1��������
//				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
//			}
//			if(memcmp(USART_RX_BUF,"����",4) == 0)
//			{
//				LED1 = 0; 
//				LED0 = 0;
//				delay_ms(1000);

//			}
//			if(memcmp(USART_RX_BUF,"�ص�",4) == 0)
//			{
//				LED1 = 1; 
//				LED0 = 1;
//				delay_ms(1000);

//			}
//			memset(USART_RX_BUF,0,50);
//			printf("\r\n\r\n");//���뻻��
//			USART_RX_STA=0;
//		}else
//		{
//			times++;
//			if(times%5000==0)
//			{
//				printf("\r\nս��STM32������ ����ʵ��\r\n");
//				printf("����ԭ��@ALIENTEK\r\n\r\n");
//			}
//			if(times%200==0)printf("����������,�Իس�������\n");  
//			if(times%30==0)LED0=!LED0;//��˸LED,��ʾϵͳ��������.
//			delay_ms(10);   
//		}

	}	 
 }

