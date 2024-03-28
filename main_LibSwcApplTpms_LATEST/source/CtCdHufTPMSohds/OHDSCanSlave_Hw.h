
#ifndef OHDSCANSLAVE_HW_H
#define OHDSCANSLAVE_HW_H

#include "OHDSCanSlave_Config.h"
#include "Gpt.h"

#define OHDSCANSLAVE_TIMER_CHANNEL   (uint8)0x01

#define OHDS_START_SEC_CODE
#include "MemMap.h"

FUNC(uint32, OHDS_CODE) OHDSCanSlave_GetTimerValue(void);

FUNC(Std_ReturnType, OHDS_CODE) OHDSCanSlave_StartTimer(void);

#define OHDS_STOP_SEC_CODE
#include "MemMap.h"
#endif
