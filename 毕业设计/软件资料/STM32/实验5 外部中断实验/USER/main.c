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
 ALIENTEKս��STM32������ʵ��5
 �ⲿ�ж�ʵ��   
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/

 int main(void)
 {		
  static u8 temp, hum;
	static u16 GQ_Data;
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);		//���ڳ�ʼ��Ϊ115200
 	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
	BEEP_Init();         	//��ʼ���������˿�
	KEY_Init();         	//��ʼ���밴�����ӵ�Ӳ���ӿ�
	EXTIX_Init();		 	//�ⲿ�жϳ�ʼ��
	DHT11_Init();
	LED0=0;					//����LED0
	BH1750_Init();
	while(1)
	{	    
//	  GQ_Data = BH1750_ReadContinuous1();	
		DHT11_Read_Data(&temp,&hum);
		printf("�¶�=%d               ʪ��=%d\r\n", temp, hum);
//		printf("ʪ��=%d\r\n", GQ_Data);
		delay_ms(1000);	  
	}
 }

