

#include "internal_clock.h"
#include "internal_clockX.h"
#include "state_fzzX.h"
#include "Rte_CtApHufTPMSmgr.h"
#include "WallocX.h"
#include "state_fzzX.h"
#include "Gpt.h"

#define cT_SpecialLearn         (uint16) 300
#define ECU_TIMER_CHANNEL       0U
#define ECU_TIMER_MAX           0xFFFFFFFFU
#define ECU_TIMER_S_PER_TICK    4U
#define ECU_TIMER_FREQ_KHZ      250u

static uint32 ulGlobalTime = 0;
static uint32  ucLastTicks = 0;
static uint32 ucTicksError = 0;

static uint16 ushStanbyTime = cT_STANBY;
 static uint16 ushParkingTime = cT_STANBY;

static uint8 ucOpTimeMethodCurrent;

static boolean bAbsErrorDetected =  FALSE;

extern uint16 uiKl30MFA_Vsys;
extern void TP3(uint8 ucSet);
extern void SetCodNvMBlockNewDataFlag(boolean);

void InternTimersInit(void){
  ulGlobalTime = 0;
  ucLastTicks = 0;
  ucTicksError = 0;
  Gpt_StartTimer((Gpt_ChannelType) ECU_TIMER_CHANNEL, (Gpt_ValueType) 0);

  ushStanbyTime = cT_STANBY;
  ushParkingTime=cT_STANBY;
   ClearBitFahrzeugzustandFZZ(cKFZPARKING_START_AFD );

}

void IncrInternMsTimer(void){
  uint32 ucCurrentTicks, ucDeltaTicks;

  ucCurrentTicks = Gpt_GetTimeElapsed((Gpt_ChannelType) ECU_TIMER_CHANNEL);
   if(ucCurrentTicks < ucLastTicks){
    ucDeltaTicks = (ECU_TIMER_MAX - ucLastTicks) + ucCurrentTicks + 1;
  }
  else{
      ucDeltaTicks = ucCurrentTicks - ucLastTicks;
  }

   ulGlobalTime = ulGlobalTime + ( (ucDeltaTicks + ucTicksError) / ECU_TIMER_FREQ_KHZ );
    ucLastTicks = ucCurrentTicks;
   ucTicksError =  ucDeltaTicks % ECU_TIMER_FREQ_KHZ;
 }

void GetInternMSTime(uint32* ulInternalTime){
  uint32 ucCurrentTicks, ucDeltaTicks;
  ucCurrentTicks = Gpt_GetTimeElapsed((Gpt_ChannelType) ECU_TIMER_CHANNEL);
   if(ucCurrentTicks < ucLastTicks){
    ucDeltaTicks = (ECU_TIMER_MAX - ucLastTicks) + ucCurrentTicks;
  }
  else{
      ucDeltaTicks = ucCurrentTicks - ucLastTicks;
  }

   *ulInternalTime = ulGlobalTime + ((ucDeltaTicks + ucTicksError) / ECU_TIMER_FREQ_KHZ );
}

void UpdateParkingTimer(uint16 ushVSpeed){
  if(ushVSpeed == 0){
    if(ushParkingTime<cT_STANBY){
      ushParkingTime++;

    }
  }
  else{
    ushParkingTime=0;
  }
}

void UpdateStanbyTimer(boolean bIgnState, uint16 ushVSpeed, uint8 ucVmin){
   static uint8 ucVSpeedCnt = 0;

   if( (ushVSpeed > ucVmin) && (ucVSpeedCnt < 20) ){
      ucVSpeedCnt ++;
   }
   else{
      ucVSpeedCnt = 0;
   }
   if((ucVSpeedCnt==20) && (bIgnState==TRUE)){
      ResetStanbyTimer();
   }

   if((bIgnState ==  FALSE) || ((bIgnState==TRUE) && (ushVSpeed == 0))){
      if(ushStanbyTime < cT_STANBY)
         ushStanbyTime++;
   }
}

void ResetStanbyTimer(void){
   ushStanbyTime = 0;
}

void SkipStanbyTimer(void){

   ushStanbyTime = cT_STANBY;

}

uint16 ushGetCurrentECUStanbyTime(void){
   return ushStanbyTime;
}

uint8 ucGetCurrentECUParkingState(void){
  if(ushParkingTime<cT_SpecialLearn){
    return 1;
   }
  else if(ushParkingTime<cT_STANBY){
    return 2;
   }
  else{
    return 3;
   }

}

uint16 ushGetCurrentECUParkingTime(void){

  return ushParkingTime;
}

boolean bStanbyTimerElapsed(void){

   return (ushStanbyTime >= cT_STANBY);

}

uint8  GetOpTimeMethodCurrent(void){
  return ucOpTimeMethodCurrent;
}
 void SetOpTimeMethodTarget(uint8 ucTimeMethod, uint8 ucCstDelay){
  if(ucTimeMethod == OP_TIME_METHOD_CSTDELAY){
    Rte_Pim_Pim_tCodNvMBlock()->aucPalAbsDelayTimeParam[0] = OP_TIME_METHOD_CSTDELAY;
  }
  else if(ucTimeMethod == OP_TIME_METHOD_OHDS){
    Rte_Pim_Pim_tCodNvMBlock()->aucPalAbsDelayTimeParam[0] = OP_TIME_METHOD_OHDS;
  }
  else{
  }
  Rte_Pim_Pim_tCodNvMBlock()->aucPalAbsDelayTimeParam[1] = ucCstDelay;
  SetCodNvMBlockNewDataFlag(TRUE);
  Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCodNvMBlock_SetRamBlockStatus(TRUE);
}
 uint8 GetOpTimeMehodTarget(void){
  return Rte_Pim_Pim_tCodNvMBlock()->aucPalAbsDelayTimeParam[0];
}
 uint8 GetPalAbsConstantDelay(void){
  return Rte_Pim_Pim_tCodNvMBlock()->aucPalAbsDelayTimeParam[1];
}

void GetSystemOperatingTime(uint32* ulOpTime){
  uint8 ucStatus, ucMSB, ucTemp;
  uint32 ulTempOpTime;

  ucTemp = ucOpTimeMethodCurrent;

  if( (GetOpTimeMehodTarget() == OP_TIME_METHOD_CSTDELAY) || (bAbsErrorDetected==TRUE)){
    GetInternMSTime(ulOpTime);
    ucOpTimeMethodCurrent = OP_TIME_METHOD_CSTDELAY;
  }
  else if( GetOpTimeMehodTarget() == OP_TIME_METHOD_OHDS){
    Rte_Call_R_OHDS_GetOperatingHours_GetOperatingHours(&ulTempOpTime, &ucMSB, &ucStatus);
    if((ucStatus & 0x01) == 0x01 ){
      if( bGetBitFahrzeugzustandFZZ(cFAILURE_MONITORING) && bGetFzzCanSignalImplausibleState(cFZZ_TRACTION_SYSTEM_IMPLAU)){
      GetInternMSTime(ulOpTime);
        ucOpTimeMethodCurrent = OP_TIME_METHOD_CSTDELAY;
        bAbsErrorDetected = TRUE;
      }
      else{
        *ulOpTime = ulTempOpTime;
        ucOpTimeMethodCurrent = OP_TIME_METHOD_OHDS;
      }

    }
    else{
      GetInternMSTime(ulOpTime);
      ucOpTimeMethodCurrent = OP_TIME_METHOD_CSTDELAY;
    }

  }
  else{
  }
   if(ucTemp != ucOpTimeMethodCurrent){
      ReNewABSRef();
    }
}

void SetPalAbsTimeInfoSNA(void){

}

