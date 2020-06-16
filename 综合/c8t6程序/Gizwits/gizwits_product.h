#ifndef _GIZWITS_PRODUCT_H
#define _GIZWITS_PRODUCT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stm32f10x.h>
#include "gizwits_protocol.h"

extern uint16_t  timeuser;
/**
* MCU software version
*/
#define SOFTWARE_VERSION "03030000"
/**
* MCU hardware version
*/
#define HARDWARE_VERSION "03010100"

#define MODULE_TYPE 0 //0,WIFI ;1,GPRS

extern dataPoint_t currentDataPoint;

void gizTimerMs(void);
void timerInit(void);
void uartInit(void);
void userInit(void);
void userHandle(void);
void mcuRestart(void);
uint32_t gizGetTimerCount(void);
int32_t uartWrite(uint8_t *buf, uint32_t len);
int8_t gizwitsEventProcess(eventInfo_t *info, uint8_t *data, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif
