#include "systick.h"

/********************************************************************
  ��̬ȫ�ֱ���˵����
        fac_us---us��ʱ������
        fac_ms---ms��ʱ������,��ucos��,����ÿ�����ĵ�ms��
*********************************************************************/
static u8  fac_us = 0; 
static u16 fac_ms = 0; 


/********************************************************************
* Function��   delay_init()
* Description: ��ʼ���ӳٺ���;
* Input��  SYSCLK:ϵͳʱ��;SYSTICK��ʱ�ӹ̶�ΪHCLKʱ�ӵ�1/8
* Output�� ��
* Return : ��
* Author:  XYD
* Others:  �ú����趨ϵͳ�δ�ʱ�ӵ�ʱ��Դ��ȷ��us��ms�ı�����
* date of completion:  2015-09-26
* date of last modify: 2015-09-26
*********************************************************************/
void Delay_Init(u8 SYSCLK)
{

    SysTick->CTRL &= ~ ( 1 << 2 ); /* SYSTICKʹ���ⲿʱ��Դ */
    fac_us = SYSCLK / 8;


    fac_ms = ( u16 ) fac_us * 1000; /* ��ucos��,����ÿ��ms��Ҫ��systickʱ���� */

}


/********************************************************************
*  Function   : delay_us ()
*  Description: ��ʱnus����;
*  Input      : nusΪҪ��ʱ��us��.
*  Output     : ��
*  Author     : XYD
*  Others     : 
* date of completion:  2015-09-26
* date of last modify: 2015-09-26
*********************************************************************/
void Delay_us(u32 nus)
{
    u32 temp;
    SysTick->LOAD = nus * fac_us;               /* ʱ����� */
    SysTick->VAL = 0x00;                        /* ��ռ����� */
    SysTick->CTRL = 0x01 ;                      /* ��ʼ���� */

    do
    {
        temp = SysTick->CTRL;
    }
	while ( ( temp & 0x01 ) && ! ( temp & ( 1 << 16 ) ) ); /* �ȴ�ʱ�䵽�� */
    SysTick->CTRL = 0x00;                        /* �رռ����� */
    SysTick->VAL = 0X00;                         /* ��ռ����� */
}


/********************************************************************
*  Function   : delay_ms()
*  Description: ��ʱnms����;
*  Input      : nmsΪҪ��ʱ��ms��.
*  Output     : ��
*  Author     : XYD
*  Others     :  1.ע��nms�ķ�Χ��
*                SysTick->LOADΪ24λ�Ĵ���,
                 ����,�����ʱΪ:nms<=0xffffff*8*1000/SYSCLK ��
                 SYSCLK��λΪHz,nms��λΪms����72M������,nms<=1864
* date of completion:  2015-09-26
* date of last modify: 2015-09-26
*********************************************************************/
void Delay_ms (u16 nms)
{
    u32 temp;
    SysTick->LOAD = ( u32 ) nms * fac_ms;        /* ʱ�����(SysTick->LOADΪ24bit) */
    SysTick->VAL = 0x00;                         /* ��ռ����� */
    SysTick->CTRL = 0x01 ;                       /* ��ʼ���� */

    do
    {
        temp = SysTick->CTRL;
    }
	while ( (temp & 0x01) && ! (temp & ( 1 << 16)) ); /* �ȴ�ʱ�䵽�� */

    SysTick->CTRL = 0x00;                        /* �رռ����� */
    SysTick->VAL = 0X00;                         /* ��ռ����� */
}








