

#include "OHDSCanSlave_Hw.h"

#define OHDS_START_SEC_CODE
#include "MemMap.h"

FUNC(Std_ReturnType, OHDS_CODE) OHDSCanSlave_StartTimer( void ){
  Gpt_StartTimer((Gpt_ChannelType) OHDSCANSLAVE_TIMER_CHANNEL, (Gpt_ValueType) 0);

  return E_OK;
}

FUNC(uint32, OHDS_CODE) OHDSCanSlave_GetTimerValue( void ){
  Gpt_ValueType ticks;

  ticks = Gpt_GetTimeElapsed((Gpt_ChannelType) OHDSCANSLAVE_TIMER_CHANNEL);

  return ticks;
}

#define OHDS_STOP_SEC_CODE
#include "MemMap.h"
