#include "gpio.h"

/**************************** LED�Ƴ�ʼ������ ****************************
��  �ܣ���ʼ��LED�ƶ�Ӧ��Ӳ�������˿�
��  ������
����ֵ����
Ӳ�����ӷ�ʽ��
LED1(D3) --- PB5 --- ������� ---- �͵�ƽ�����ߵ�ƽ��
LED2(D4) --- PE5 --- ������� ---- �͵�ƽ�����ߵ�ƽ��
LED3(D5) --- PA5 --- ������� ---- �͵�ƽ�����ߵ�ƽ��
LED4(D6) --- PA6 --- ������� ---- �͵�ƽ�����ߵ�ƽ��
***************************************************************************/
void Led_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;   /* ����һ���ṹ�����ͱ��� */
	
	/* ����GPIO�˿�ģ���ʱ�� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOE |
	                       RCC_APB2Periph_GPIOA,ENABLE);  //ʹ��GPIOB��GPIOE��GPIOBAʱ��
	
	/* LED1(D3) --- PB5 */
	/* ����GPIO�˿ڹ���ģʽ */
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_5;             //ʹ�ö˿ڱ��5
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;       //����ٶ�50M
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;       //�����������
	/* ��ʼ��GPIO�˿� */
	GPIO_Init(GPIOB, &GPIO_InitStructure);                  //��ʼ��GPIOB��
	/* ��ʼ�����״̬ */
	GPIO_SetBits(GPIOB,GPIO_Pin_5);                        //GPIOB.5��ʼ������ߵ�ƽ
	
	/* LED2(D4) --- PE5 */
	/* ��ʼ��GPIO�˿� */
	GPIO_Init(GPIOE, &GPIO_InitStructure);                  //��ʼ��GPIOE��
	/* ��ʼ�����״̬ */
	GPIO_SetBits(GPIOE,GPIO_Pin_5);                         //GPIOE.5��ʼ������ߵ�ƽ
	
	/* LED3(D5) --- PA5 LED4(D6) --- PA6 */
	/* ����GPIO�˿ڹ���ģʽ */
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_5 | GPIO_Pin_6; //ʹ�ö˿ڱ��5��6
	/* ��ʼ��GPIO�˿� */
	GPIO_Init(GPIOA, &GPIO_InitStructure);                   //��ʼ��GPIOB��
	/* ��ʼ�����״̬ */
	GPIO_SetBits(GPIOA,(GPIO_Pin_5 | GPIO_Pin_6));           //GPIOA.5��GPIOA.6��ʼ������ߵ�ƽ      	
}

/**************************** ��������ʼ������ ****************************
��  �ܣ���ʼ����������Ӧ��Ӳ�������˿�
��  ������
����ֵ����
Ӳ�����ӷ�ʽ��
Beep --- PB8 --- ������� ---- �ߵ�ƽ�죬�͵�ƽ����
***************************************************************************/
void Beep_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;   /* ����һ���ṹ�����ͱ��� */
	
	/* ����GPIO�˿�ģ���ʱ�� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);    //ʹ��GPIOBʱ��
	
	/* ����GPIO�˿ڹ���ģʽ */
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_8;             //ʹ�ö˿ڱ��8
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;       //����ٶ�50M
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;       //�����������
	
	/* ��ʼ��GPIO�˿� */
	GPIO_Init(GPIOB, &GPIO_InitStructure);                  //��ʼ��GPIOB��
	
	/* ��ʼ�����״̬ */
	GPIO_ResetBits(GPIOB,GPIO_Pin_8);                       //GPIOB.8��ʼ������͵�ƽ
}

/**************************** ������ʼ������ ****************************
��  �ܣ���ʼ��������Ӧ��Ӳ�������˿�
��  ������
����ֵ����
Ӳ�����ӷ�ʽ��
UP��     --- PA0 --- �������� --- �������»�ȡ�͵�ƽ
RIGHT��  --- PE4 --- �������� --- �������»�ȡ�͵�ƽ
DOWN��   --- PE3 --- �������� --- �������»�ȡ�͵�ƽ
LEFT��   --- PE2 --- �������� --- �������»�ȡ�ߵ�ƽ
***************************************************************************/
void Key_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;   /* ����һ���ṹ�����ͱ��� */
	
	/* ����GPIO�˿�ģ���ʱ�� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOE,ENABLE);    //ʹ��GPIOA��GPIOEʱ��
	
	/* UP��(PA0) */
	/* ����GPIO�˿ڹ���ģʽ */
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0;             //ʹ�ö˿ڱ��0
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;          //��������ģʽ 
	/* ��ʼ��GPIO�˿� */
	GPIO_Init(GPIOA, &GPIO_InitStructure);                  //��ʼ��GPIOA��
	
	/* RIGHT��(PE4)��DOWN��(PE3) */
	/* ����GPIO�˿ڹ���ģʽ */
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_4 |GPIO_Pin_3; //ʹ�ö˿ڱ��4�Ͷ˿�3
	/* ��ʼ��GPIO�˿� */
	GPIO_Init(GPIOE, &GPIO_InitStructure);                  //��ʼ��GPIOE��
	
	/* LEFT��(PE2) */
	/* ����GPIO�˿ڹ���ģʽ */
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2;             //ʹ�ö˿ڱ��2
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPD;          //��������ģʽ 
	/* ��ʼ��GPIO�˿� */
	GPIO_Init(GPIOE, &GPIO_InitStructure);                  //��ʼ��GPIOE��
}

/**************************** ������ʼ������ ****************************
��  �ܣ��԰�������ɨ��
��  ������
����ֵ��������Ч�İ���ֵ
����������ʽ���Ա�����
ͨ���������������3��5����������״ֵ̬��Ȼ��Ա��ж��⼸������״ֵ̬�Ƿ�һ�£�
���һ�£���֤������ֵ��Ч
*************************************************************************/
u8 Key_Scan(void)
{
	u8 Key_Val = 0xff;                     //������Чֵ�������
	static u8 Key_Sta = 1;                 //���ּ���־��1��������������0����ֹ��������
	static u8 Key_1,Key_2,Key_3,time = 0;  //������ȡ�����Լ�����ֵ�������
	
	/* ����ֵ���� */
	Key_3 = Key_2;
	Key_2 = Key_1;
	time++;
	
	/* �ж��Ƿ�������ʶ�����а������� */
	if((Key_Sta == 1 ) &&  ( (!(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0))) || (!(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4))
		 || (!(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3))) || (GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2))) ))
	{
		if( (!(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0))) )          //UP��������
		{
			Key_1 = UP;           //���水��ֵ
		}
		else if( (!(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4))) )     //RIGHT��������
		{
			Key_1 = RIGHT;         //���水��ֵ
		}
		else if( (!(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3))) )     //DOWN��������
		{
			Key_1 = DOWN;         //���水��ֵ
		}
		else if( (GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)) )        //LEFT��������
		{
			Key_1 = LEFT;         //���水��ֵ
		}
		if(time == 3)             //�ж϶�ȡ�����Ƿ�ﵽ3��
		{
			time = 0;             //��ȡ��������
			if( (Key_1 == Key_2) && (Key_2 == Key_3) )    //�ж�3�ζ����İ���ֵ�Ƿ�һ��
			{
				Key_Val = Key_1;  //���水����Чֵ
				Key_Sta = 0;      //��������ʶ��
			}
		}
	}
	/* ����û�а��� */
	else if( GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) || GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)
		 ||  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3) || (!(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2))) )
	{
		Key_Sta = 1;           //������ʶ��
		time = 0;              //��ȡ��������
	}
	
	return 	Key_Val;           //������Ч����ֵ
}















