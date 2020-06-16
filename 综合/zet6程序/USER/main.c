/**************************************************************************************************

����           ����                       ͨ��Э��
esp8266        PA9(T) PA10(R)            �����ƴ���ͨ��Э��Gagent
DHT11          PB9                       ����ͨ��
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

/* �û�����ǰ�豸״̬�ṹ��*/
dataPoint_t currentDataPoint;
#define Temp_Q 32 //�¶����ޣ���λ��C��
#define Humi_alarm 90 //ʪ�����ޣ���λ��%��
//Э���ʼ��
void Gizwits_Init(void)
{
    TIM3_Int_Init(9,7199);//1MSϵͳ��ʱ
//  usart3_init(9600);//WIFI��ʼ��
    uart_init(9600);//����Ĳ�����ֻ����9600
    memset((uint8_t*)&currentDataPoint, 0, sizeof(dataPoint_t));//�豸״̬�ṹ���ʼ��
    gizwitsInit();//��������ʼ��
}
//���ݲɼ�
void userHandle(void)
{   
    static u16 GQ_Data;//�����ǿ�������Ĳ�����ʹ��extern�ǻ�������ݲ���������ʾ�����⡣
    static u8 temp, hum;
//	static u8 temp_num = 0;
//  static u8 humi_num = 0;
//  static u8 GQ_Data_num = 0;
    if(timeuser > 1000)//ÿ1���ϱ�һ������
    {
        timeuser=0;//��.h�ļ������Ѿ�������
        //��oled��app����ʾ��ʪ��ֵ
        DHT11_Read_Data(&temp,&hum);//��ȡ DHT11 ������
        OLED_ShowNum(48,0,temp/10%10,1,16);//x,y������λ������λ�����ȣ������С
				OLED_ShowNum(56,0,temp%10,1,16);
        OLED_ShowNum(48,2,hum/10%10,1,16);
				OLED_ShowNum(56,2,hum%10,1,16);//x,y������λ������λ�����ȣ������С
        currentDataPoint.valueTemp = temp ;//�¶�����
        currentDataPoint.valueShidu = hum;//ʪ������
        //��oled��app����ʾ��ǿ��ֵ
        GQ_Data = BH1750_ReadContinuous1();	//��ȡGY-30������
        OLED_ShowNum(48,4,GQ_Data/10000%10,1,16);
				OLED_ShowNum(56,4,GQ_Data/1000%10,1,16);
				OLED_ShowNum(64,4,GQ_Data/100%10,1,16);
				OLED_ShowNum(72,4,GQ_Data/10%10,1,16);
				OLED_ShowNum(80,4,GQ_Data%10,1,16);
        currentDataPoint.valueGQ = GQ_Data;//��ǿ��ֵ
		
        //�ж���ʪ���Լ���ǿ�Ƿ񳬳�����ֵ���������������죬led��
        if((temp>=currentDataPoint.valueTemp_AlarmScope||hum>=currentDataPoint.valueShidu_AlarmScope||GQ_Data>=currentDataPoint.valueGQ_AlarmScope)&&(currentDataPoint.valueTemp_AlarmScope!=0&&currentDataPoint.valueShidu_AlarmScope!=0&&currentDataPoint.valueGQ_AlarmScope!=0))//�¶�>����ֵ
        {

            if(1 == currentDataPoint.valueLED1)//���led1�����������죬�����������Զ�ģʽ
            {

                currentDataPoint.valueTemp_Q=1;//�¶ȴ����ޱ���
                BEEP = 1;
                LED0 = 0;
                delay_ms(1000);delay_ms(1000);delay_ms(1000);
								//�����������رշ�������led��
                currentDataPoint.valueLED = currentDataPoint.valueBEEP = 0;
                currentDataPoint.valueTemp_Q=0;
                BEEP = 0;
                LED0 = 1;
								delay_ms(1000);delay_ms(1000);delay_ms(1000);

            }
        }
    }
}

//������
int main(void)
{
    delay_init();	    	 //��ʱ������ʼ��
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
    LED_Init();			    //LED�˿ڳ�ʼ��
    DHT11_Init();
    BEEP_Init();            //��������ʼ��
    OLED_Init();			//��ʼ��OLED
    BH1750_Init();
    Gizwits_Init();         //Э���ʼ��
    //OLED��ʾ���¶ȡ�
    OLED_ShowCHinese(0,0,0);  //x,y,����λ�Ǻ��ֿ�Ĵ���
    OLED_ShowCHinese(16,0,1);
    OLED_ShowCHinese(32,0,10);
    OLED_ShowCHinese(72,0,8);
    //ʪ��
    OLED_ShowCHinese(0,2,2);
    OLED_ShowCHinese(16,2,3);
    OLED_ShowCHinese(32,2,10);
    OLED_ShowCHinese(72,2,9);
    //��ǿ
    OLED_ShowCHinese(0,4,4);
    OLED_ShowCHinese(16,4,6);
    OLED_ShowCHinese(32,4,10);
    OLED_ShowString(96,4,"lx",16);//����lx�ǹ�ǿ�ĵ�λ
    while(1)
    {
        userHandle();//�û��ɼ�
        gizwitsHandle((dataPoint_t *)&currentDataPoint);//Э�鴦��
    }
}




