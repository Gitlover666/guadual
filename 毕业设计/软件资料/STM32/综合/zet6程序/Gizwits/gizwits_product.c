#include <stdio.h>
#include <string.h>
//#include "hal_key.h"
#include "gizwits_product.h"
#include "common.h"
#include "usart3.h"
#include "led.h"
#include "beep.h"
#include "usart.h"

//定义变量
static uint32_t timerMsCount;
uint8_t aRxBuffer;
uint16_t  timeuser = 0;
/** User area the current device state structure*/
extern dataPoint_t currentDataPoint;

/**@} */
/**@name Gizwits User Interface
* @{
*/

/**
* @brief Event handling interface

* Description:

* 1. Users can customize the changes in WiFi module status

* 2. Users can add data points in the function of event processing logic, such as calling the relevant hardware peripherals operating interface

* @param [in] info: event queue
* @param [in] data: protocol data
* @param [in] len: protocol data length
* @return NULL
* @ref gizwits_protocol.h
*/
//在这里控制蜂鸣器等
int8_t gizwitsEventProcess(eventInfo_t *info, uint8_t *gizdata, uint32_t len)
{
    uint8_t i = 0;
    dataPoint_t *dataPointPtr = (dataPoint_t *)gizdata;
    moduleStatusInfo_t *wifiData = (moduleStatusInfo_t *)gizdata;
    protocolTime_t *ptime = (protocolTime_t *)gizdata;

#if MODULE_TYPE
    gprsInfo_t *gprsInfoData = (gprsInfo_t *)gizdata;
#else
    moduleInfo_t *ptModuleInfo = (moduleInfo_t *)gizdata;
#endif

    if((NULL == info) || (NULL == gizdata))
    {
        return -1;
    }

    for(i=0; i<info->num; i++)
    {
        switch(info->event[i])
        {
        case EVENT_LED:
            currentDataPoint.valueLED = dataPointPtr->valueLED;
            GIZWITS_LOG("Evt: EVENT_LED %d \n", currentDataPoint.valueLED);
            if(0x01 == currentDataPoint.valueLED)
            {
                if(0 == currentDataPoint.valueLED1)
                    LED0 = 0;//user handle
            }
            else
            {
                if(0 == currentDataPoint.valueLED1)
                    LED0 = 1;//user handle
            }
            break;
        case EVENT_BEEP:
            currentDataPoint.valueBEEP = dataPointPtr->valueBEEP;
            GIZWITS_LOG("Evt: EVENT_BEEP %d \n", currentDataPoint.valueBEEP);
            if(0x01 == currentDataPoint.valueBEEP)
            {
                if(0 == currentDataPoint.valueLED1)
                    BEEP = 1;//user handle
            }
            else
            {
                if(0 == currentDataPoint.valueLED1)
                    BEEP = 0;//user handle
            }
            break;
        case EVENT_LED1:
            currentDataPoint.valueLED1 = dataPointPtr->valueLED1;
            GIZWITS_LOG("Evt: EVENT_LED1 %d \n", currentDataPoint.valueLED1);
            if(0x01 == currentDataPoint.valueLED1)
            {
                LED1 = 0;//user handle
								
            }
            else
            {
                LED1 = 1;//user handle
								
            }
            break;
        case EVENT_Temp_AlarmScope:

            currentDataPoint.valueTemp_AlarmScope = dataPointPtr->valueTemp_AlarmScope;
            GIZWITS_LOG("Evt:EVENT_Temp_AlarmScope %d\n",currentDataPoint.valueTemp_AlarmScope);
            //user handle
            break;
        case EVENT_Shidu_AlarmScope:

            currentDataPoint.valueShidu_AlarmScope = dataPointPtr->valueShidu_AlarmScope;
            GIZWITS_LOG("Evt:EVENT_Shidu_AlarmScope %d\n",currentDataPoint.valueShidu_AlarmScope);
            //user handle
            break;
        case EVENT_GQ_AlarmScope:
            currentDataPoint.valueGQ_AlarmScope = dataPointPtr->valueGQ_AlarmScope;
            GIZWITS_LOG("Evt:EVENT_GQ_AlarmScope %d\n",currentDataPoint.valueGQ_AlarmScope);
            //user handle
            break;


        case WIFI_SOFTAP:
            break;
        case WIFI_AIRLINK:
            break;
        case WIFI_STATION:
            break;
        case WIFI_CON_ROUTER:

            break;
        case WIFI_DISCON_ROUTER:

            break;
        case WIFI_CON_M2M:

            break;
        case WIFI_DISCON_M2M:
            break;
        case WIFI_RSSI:
            GIZWITS_LOG("RSSI %d\n", wifiData->rssi);
            break;
        case TRANSPARENT_DATA:
            GIZWITS_LOG("TRANSPARENT_DATA \n");
            //user handle , Fetch data from [data] , size is [len]
            break;
        case WIFI_NTP:
            GIZWITS_LOG("WIFI_NTP : [%d-%d-%d %02d:%02d:%02d][%d] \n",ptime->year,ptime->month,ptime->day,ptime->hour,ptime->minute,ptime->second,ptime->ntp);
            break;
        case MODULE_INFO:
            GIZWITS_LOG("MODULE INFO ...\n");
#if MODULE_TYPE
            GIZWITS_LOG("GPRS MODULE ...\n");
            //Format By gprsInfo_t
#else
            GIZWITS_LOG("WIF MODULE ...\n");
            //Format By moduleInfo_t
            GIZWITS_LOG("moduleType : [%d] \n",ptModuleInfo->moduleType);
#endif
            break;
        default:
            break;
        }
    }

    return 0;
}


/**
* Data point initialization function

* In the function to complete the initial user-related data
* @param none
* @return none
* @note The developer can add a data point state initialization value within this function
*/
void userInit(void)
{
    memset((uint8_t*)&currentDataPoint, 0, sizeof(dataPoint_t));

}


/**
* @brief Millisecond timing maintenance function, milliseconds increment, overflow to zero

* @param none
* @return none
*/
void gizTimerMs(void)
{
    timerMsCount++;
    timeuser++;
}

/**
* @brief Read millisecond count

* @param none
* @return millisecond count
*/
uint32_t gizGetTimerCount(void)
{
    return timerMsCount;
}

/**
* @brief MCU reset function

* @param none
* @return none
*/
void mcuRestart(void)
{
    __set_FAULTMASK(1);
    NVIC_SystemReset();
}



/**
* @brief Serial port write operation, send data to WiFi module
*
* @param buf      : buf address
* @param len      : buf length
*
* @return : Return effective data length;-1，return failure
*/
//这里也很重要，发送给云服务器
int32_t uartWrite(uint8_t *buf, uint32_t len)
{
//		uint8_t crc[1] = {0x55};
    uint32_t i = 0;

    if(NULL == buf)
    {
        return -1;
    }

    for(i=0; i<len; i++)
    {
        USART_SendData(USART1,buf[i]);
        while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET); //循环发送,直到发送完毕
        if(i >=2 && buf[i] == 0xFF)
        {
            USART_SendData(USART1,0x55);
            while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET); //循环发送,直到发送完毕
        }
    }

#ifdef PROTOCOL_DEBUG
    GIZWITS_LOG("MCU2WiFi[%4d:%4d]: ", gizGetTimerCount(), len);
    for(i=0; i<len; i++)
    {
        GIZWITS_LOG("%02x ", buf[i]);

        if(i >=2 && buf[i] == 0xFF)
        {
            GIZWITS_LOG("%02x ", 0x55);
        }
    }
    GIZWITS_LOG("\n");
#endif

    return len;
}
