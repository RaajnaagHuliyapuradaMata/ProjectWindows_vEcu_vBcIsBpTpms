

#include "tel_statistic.h"
#include "tel_statisticX.h"
#include "Rte_CtApHufTPMSmgr.h"
#include "WallocX.h"
#include "tss_stdX.h"
#include "state_bzX.h"
#include "state_fzzX.h"
#include "Dem_IntEvtId.h"
#include "USWarnX.h"
#include "DAG_TVWarn.h"
#include "DEM.h"
#include "HMI_handlerX.h"
#include "EcuM_Generated_Types.h"
#include "filling_detection.h"
#include "filling_detectionX.h"

#define M_MAX 540U
 #define MAX_NUM_BLOCKS 1000U
#define T_MAX_PAL 39U

#define AKA_OFFSET 0x02U
#define MAX_RAW_IN_VAL_P 0xFFU
#define MAX_RAW_IN_VAL_T 0xB1U

#define MAX_RAW_IN_VAL_AVG_P 0xFFFFU

#define MAX_OUT_VAL_P MAX_RAW_IN_VAL_P - AKA_OFFSET
#define MAX_OUT_VAL_T MAX_RAW_IN_VAL_T - AKA_OFFSET

#define MAX_OUT_VAL_AVG_P MAX_RAW_IN_VAL_AVG_P - AKA_OFFSET

typedef struct
{
  uint8 ucSensorState;
  uint16 ushMuteCntr;
  uint8 ucTempmissedTimer;
}telStatStruct;

typedef struct
{
  uint32 ulTelID;
  uint8 ucLastValidP;
  uint8 ucLastValidT;
  uint32 ulLastTime;
  uint8 ucRxBlocs;
#ifdef AVG_PRESS_ENABLED
  uint16 uiAvgP;
   uint8 ucAvgCnt;
 #endif
}telStatStructV2;

static telStatStruct tTelStatStruct[cMaxLR];
static telStatStructV2 tTelStatStructV2[cTableSize];
static uint8 ucFailureState = FAILURE_MODE_ok;
static uint8 ucSensorMissingField = 0;
static boolean bModuleIsInitialized = FALSE;
static boolean bAutoLearnCycleCompleted = FALSE;
static boolean bSensorHas2BeLearn[cMaxLR] = {TRUE, TRUE, TRUE, TRUE};

extern FUNC(Std_ReturnType, DEM_CODE) Dem_SetEventStatus(Dem_EventIdType       EventId, Dem_EventStatusType   EventStatus);
extern FUNC(Std_ReturnType, ECUM_API_CODE) EcuM_GetState(P2VAR(EcuM_StateType, AUTOMATIC, ECUM_APPL_DATA) state);

 void static UpdateFailureState(void);
 void static IncrementRxBlocksSum(uint8 ucColOfID);
 void static IncrementMissedBlocksSum(uint8 ucColOfID);
 void static putTelInfo2Table(uint32 ulID, uint8 ucP, uint8 ucT, uint32 ulTime);
 void static ClearSensorStateMissing(uint8);
 void static SetSensorState2Missing(uint8);
 void static ClearLastRecPressTemp(uint8 ucColOfID);
 void static UpdateMissingSensorsDTCs(void);
 void static UpdateDisturbedSensorsDTCs(void);

extern void Dem_SetEventExData(uint8);

 void BuildTelStatistics(uint32 ulTelID, uint8 ucTelP, uint8 ucTelT, uint32 ulTime, boolean bSensorDefect){
   if( !bSensorDefect){
     if(ucGetColOfID(&ulTelID) < cMaxLR){
       IncrementRxBlocksSum(ucGetColOfID(&ulTelID));
     }
   }

   if(!bSensorDefect){
    putTelInfo2Table(ulTelID, ucTelP,  ucTelT, ulTime);
   }else
   {
    putTelInfo2Table(ulTelID, (uint8)0x00,  (uint8)0x00, ulTime);
   }
 }

 void UpdateTelStatInfo(uint16 ushCurrentVehSpeed, uint8 ucMinPalSpeed){
  uint8 i, ucWaToErr;
  EcuM_StateType  EcuM_State;

  (void)EcuM_GetState(&EcuM_State);

  if(bModuleIsInitialized && (EcuM_State == ECUM_STATE_APP_RUN)){

    for(i=0; i<cMaxLR; i++){
      if(ushCurrentVehSpeed > ucMinPalSpeed){
        if(tTelStatStruct[i].ushMuteCntr < M_MAX){
          tTelStatStruct[i].ushMuteCntr++;
        }
      }
      else if( (ushCurrentVehSpeed==0) && (tTelStatStruct[i].ushMuteCntr<T_MAX_PAL) ){
        tTelStatStruct[i].ushMuteCntr = 0;
       }
       if(ushCurrentVehSpeed > ucMinPalSpeed){
        if(tTelStatStruct[i].ucTempmissedTimer < T_MAX_PAL){
          tTelStatStruct[i].ucTempmissedTimer++;
        }
      }
      else if( (ushCurrentVehSpeed==0) && (tTelStatStruct[i].ushMuteCntr<T_MAX_PAL) ){
        tTelStatStruct[i].ucTempmissedTimer = 0;
       }

      if(tTelStatStruct[i].ucTempmissedTimer==T_MAX_PAL){
        IncrementMissedBlocksSum(i);
        tTelStatStruct[i].ucTempmissedTimer = 0;
       }

       Rte_Call_PP_GetWaTOErrorCode_OP_GetWaTOErrorCode(&ucWaToErr, i);
      if(bGetBitBetriebszustandBZ(cZO_ERROR) && (ucWaToErr == SensorMissin)){
        SetSensorState2Missing(i);
      }
      if( bGetBitBetriebszustandBZ(cER_FINISH) || (bGetBitBetriebszustandBZ(cZO_ERROR)&&(ucWaToErr != SensorMissin))){
        ClearSensorStateMissing(i);
      }

        if(bGetSensorStateMissing(i)){
        if(  (tTelStatStruct[i].ucSensorState == SENSOR_STATE_MISSING) && (ui8GetDAGAutoLearnState() != Autolearn_Learning) ){
          ClearLastRecPressTemp(i);
         }
        tTelStatStruct[i].ucSensorState=SENSOR_STATE_MISSING;

        DelWarnOfId(i);
         PuT(i,-127);

      }
      else if(tTelStatStruct[i].ushMuteCntr < T_MAX_PAL){
        if(tTelStatStruct[i].ucSensorState!=SENSOR_STATE_UNKNOWN){
          tTelStatStruct[i].ucSensorState=SENSOR_STATE_OK;
        }
      }
      else if(tTelStatStruct[i].ushMuteCntr < M_MAX){
        tTelStatStruct[i].ucSensorState=SENSOR_STATE_SUSPICIOUS;
      }
      else if( (bGetBitBetriebszustandBZ(cZO_FINISH) || bGetBitBetriebszustandBZ(cZO_TIMEOUT)) && (tTelStatStruct[i].ushMuteCntr==M_MAX)){
        tTelStatStruct[i].ucSensorState=SENSOR_STATE_DISTURBED;
        ClearLastRecPressTemp(i);
      }
    }
     UpdateFailureState();

    if( bGetBitBetriebszustandBZ(cER_FINISH) || bGetBitBetriebszustandBZ(cZO_FINISH) || bGetBitBetriebszustandBZ(cZO_TIMEOUT) ){
      if( !bAutoLearnCycleCompleted){
        bAutoLearnCycleCompleted = TRUE;
        UpdateMissingSensorsDTCs();
      }
      else
      {
       }
    }
    UpdateDisturbedSensorsDTCs();
  }
 }

 void InitTelStatInfo(void){
    uint16 i;
     for(i=0; i<cMaxLR; i++){
      tTelStatStruct[i].ushMuteCntr=0;
      tTelStatStruct[i].ucSensorState=SENSOR_STATE_UNKNOWN;
      tTelStatStruct[i].ucTempmissedTimer = 0;
    }
      if( (GETucWAHistSensorState()&0x0F) == FAILURE_MODE_noWE){
        ucFailureState = FAILURE_MODE_noWE;
      }

      else
      {
        ucFailureState = FAILURE_MODE_ok;
      }

      ucSensorMissingField = (GETucWAHistSensorState()&0xF0)>>4;

     for(i=0;i<sizeof(tTelStatStructV2);i++){
        *((uint8*)&tTelStatStructV2 + i) = 0;
     }

    bAutoLearnCycleCompleted = FALSE;

    bModuleIsInitialized = TRUE;
 }

 void InitTelStatInfoAtModeChange(void){
   uint8 i;
    for(i=0;i<cTableSize;i++){
        tTelStatStructV2[i].ucRxBlocs = 0;
     }

   bAutoLearnCycleCompleted = FALSE;
 }

 void static UpdateFailureState(){

  uint8 i;
  uint8 ucCntrMiss, ucCntrDisturb, ucCntrOk;
  ucCntrMiss =0;
  ucCntrDisturb = 0;
  ucCntrOk = 0;
   for(i=0; i<cMaxLR; i++){
    if(tTelStatStruct[i].ucSensorState==SENSOR_STATE_MISSING){
      ucCntrMiss++;
    }

    if(tTelStatStruct[i].ucSensorState==SENSOR_STATE_DISTURBED){
      ucCntrDisturb++;
    }

    if(tTelStatStruct[i].ucSensorState==SENSOR_STATE_OK){
      ucCntrOk++;
    }
  }
   if( (ucCntrMiss==0) && (ucCntrDisturb==0) ){
    ucFailureState = FAILURE_MODE_ok;
  }
  else if(ucCntrMiss == cMaxLR){
    ucFailureState=FAILURE_MODE_noWE;
  }
  else if( (ucCntrMiss > 0 ) || (ucCntrDisturb > 0)){
    if(ucCntrMiss>0){
      ucFailureState=FAILURE_MODE_soWE;
    }
    else
    {
      ucFailureState = FAILURE_MODE_RfInterference;
    }

  }
  PUTucWAHistSensorState((ucFailureState&0x0F) | ((ucSensorMissingField<<4)&0xF0));
 }

  void static UpdateMissingSensorsDTCs(void){
    uint8 i;
    uint8 ucCntrMiss;
    EcuM_StateType  EcuM_State;
    ucCntrMiss =0;
     for(i=0; i<cMaxLR; i++){
      if(tTelStatStruct[i].ucSensorState==SENSOR_STATE_MISSING){
        ucCntrMiss++;
      }
    }

    (void)EcuM_GetState(&EcuM_State);

    if( EcuM_State == ECUM_STATE_APP_RUN ){
      if( (ucCntrMiss < cMaxLR)  ){
        Dem_SetEventStatus( Dem_DTC_0x551c00, DEM_EVENT_STATUS_PASSED);
      }
      else
      {
        Dem_SetEventStatus( Dem_DTC_0x551c00, DEM_EVENT_STATUS_FAILED);
      }
      for(i=0; i<cMaxLR; i++){
        if( (ucGetSensorState(i) !=  SENSOR_STATE_DISTURBED) && (ucGetSensorState(i) !=  SENSOR_STATE_MISSING) ){
          switch (i){
            case 0:
              Dem_SetEventStatus( Dem_DTC_0xd16209, DEM_EVENT_STATUS_PASSED);
               bSensorHas2BeLearn[i] = FALSE;
              break;
            case 1:
              Dem_SetEventStatus( Dem_DTC_0xd16309, DEM_EVENT_STATUS_PASSED);
               bSensorHas2BeLearn[i] = FALSE;
              break;
            case 2:
              Dem_SetEventStatus( Dem_DTC_0xd16409, DEM_EVENT_STATUS_PASSED);
               bSensorHas2BeLearn[i] = FALSE;
              break;
            case 3:
              Dem_SetEventStatus( Dem_DTC_0xd16509, DEM_EVENT_STATUS_PASSED );
               bSensorHas2BeLearn[i] = FALSE;
              break;

          }
        }
        else
        {
          switch (i){
            case 0:
              Dem_SetEventExData( Dem_DTC_0xd16209);
              Dem_SetEventStatus( Dem_DTC_0xd16209, DEM_EVENT_STATUS_FAILED);
               break;
            case 1:
              Dem_SetEventExData( Dem_DTC_0xd16309);
              Dem_SetEventStatus( Dem_DTC_0xd16309, DEM_EVENT_STATUS_FAILED);
               break;
            case 2:
              Dem_SetEventExData( Dem_DTC_0xd16409);
              Dem_SetEventStatus( Dem_DTC_0xd16409, DEM_EVENT_STATUS_FAILED);
               break;
            case 3:
              Dem_SetEventExData( Dem_DTC_0xd16509 );
              Dem_SetEventStatus( Dem_DTC_0xd16509, DEM_EVENT_STATUS_FAILED);
               break;
          }
        }
      }
    }
  }

 void static UpdateDisturbedSensorsDTCs(void){
  uint8 i;
  uint8 ucCntrDisturb, ucCntrUk, ucCntrSpcs, ucCntrMiss;
  EcuM_StateType  EcuM_State;
  ucCntrDisturb = 0;
  ucCntrUk = 0;
  ucCntrSpcs = 0;
  ucCntrMiss = 0;
   for(i=0; i<cMaxLR; i++){
    if(tTelStatStruct[i].ucSensorState==SENSOR_STATE_DISTURBED){
      ucCntrDisturb++;
    }

    if(tTelStatStruct[i].ucSensorState==SENSOR_STATE_UNKNOWN){
      ucCntrUk++;
    }

    if(tTelStatStruct[i].ucSensorState==SENSOR_STATE_SUSPICIOUS){
      ucCntrSpcs++;
    }

    if(tTelStatStruct[i].ucSensorState==SENSOR_STATE_MISSING){
      ucCntrMiss++;
    }
  }

  (void)EcuM_GetState(&EcuM_State);

  if( EcuM_State == ECUM_STATE_APP_RUN ){
    for(i=0; i<cMaxLR; i++){
      if( ucGetSensorState(i) ==  SENSOR_STATE_DISTURBED){
        Dem_SetEventStatus( Dem_DTC_0xa27900, DEM_EVENT_STATUS_FAILED);

        switch (i){
          case 0:
            Dem_SetEventExData( Dem_DTC_0xd16209 );
            Dem_SetEventStatus( Dem_DTC_0xd16209, DEM_EVENT_STATUS_FAILED);
             break;
          case 1:
            Dem_SetEventExData( Dem_DTC_0xd16309 );
            Dem_SetEventStatus( Dem_DTC_0xd16309, DEM_EVENT_STATUS_FAILED);
             break;
          case 2:
            Dem_SetEventExData( Dem_DTC_0xd16409 );
            Dem_SetEventStatus( Dem_DTC_0xd16409, DEM_EVENT_STATUS_FAILED);
             break;
          case 3:
            Dem_SetEventExData( Dem_DTC_0xd16509 );
            Dem_SetEventStatus( Dem_DTC_0xd16509, DEM_EVENT_STATUS_FAILED);
             break;
          default:
            ;
        }
      }
      else if( (ucGetSensorState(i) ==  SENSOR_STATE_OK) && (bSensorHas2BeLearn[i] == FALSE)){
        switch (i){
          case 0:
            Dem_SetEventStatus( Dem_DTC_0xd16209, DEM_EVENT_STATUS_PASSED);
             break;
          case 1:
            Dem_SetEventStatus( Dem_DTC_0xd16309, DEM_EVENT_STATUS_PASSED);
             break;
          case 2:
            Dem_SetEventStatus( Dem_DTC_0xd16409, DEM_EVENT_STATUS_PASSED);
             break;
          case 3:
          Dem_SetEventStatus( Dem_DTC_0xd16509, DEM_EVENT_STATUS_PASSED );
             break;
          default:
            ;
        }
      }
    }
    if( (ucCntrDisturb == 0) && (ucCntrUk == 0) && (ucCntrSpcs == 0) && (ucCntrMiss < cMaxLR)){
      Dem_SetEventStatus( Dem_DTC_0xa27900, DEM_EVENT_STATUS_PASSED);
     }
  }
 }

 void ResetFailureState(void){
   uint8 i;

   ucFailureState=FAILURE_MODE_ok;
   PUTucWAHistSensorState(ucFailureState);

    for(i=0; i<cMaxLR; i++){
      tTelStatStruct[i].ushMuteCntr = 0;
      tTelStatStruct[i].ucSensorState = SENSOR_STATE_UNKNOWN;

      if(pucGetLearnError ()[i] == SensorMissin){
        pucGetLearnError ()[i] = NoError;
      }

      ClearSensorStateMissing(i);
      bSensorHas2BeLearn[i] = TRUE;

    }
    ClearTPM_StatNoSensors();
    ClearTPM_MsgDispRqNoSensors();
 }

 uint8 ucGetFailureState(void){
   return ucFailureState;
 }

  uint16 ushGetTelMuteTime(uint8 ucPos){
   if(ucPos<cMaxLR){
      return tTelStatStruct[ucPos].ushMuteCntr;
   }
   else
   {
     return 0xFFFF;
   }
 }

  uint8 ucGetSensorState(uint8 ucPos){
   if(ucPos<cMaxLR){
      return tTelStatStruct[ucPos].ucSensorState;
   }
   else
   {
     return 0;
   }
 }

 void ClearTelStatisticsStruct(uint8 ucPosMask){
   uint8 i;
   for(i=0; i<cMaxLR; i++){
     if(ucPosMask & (1<<i)){
       tTelStatStruct[i].ucSensorState=SENSOR_STATE_OK;
       tTelStatStruct[i].ucTempmissedTimer=0;
       tTelStatStruct[i].ushMuteCntr=0;
     }
   }
 }

  void static IncrementRxBlocksSum(uint8 ucColOfID){
     if( ushGetRxBlocksSum(ucColOfID) < MAX_NUM_BLOCKS){
       PutRxBlocksSum((ushGetRxBlocksSum(ucColOfID) + 1), ucColOfID);
     }
     else
     {
       PutRxBlocksSum((MAX_NUM_BLOCKS >> 1), ucColOfID);
       PutMissedBlocksSum((ushGetMissedBlocksSum(ucColOfID) >> 1), ucColOfID);
     }
    tTelStatStruct[ucColOfID].ushMuteCntr=0;
    if(tTelStatStruct[ucColOfID].ucSensorState != SENSOR_STATE_MISSING){
      tTelStatStruct[ucColOfID].ucSensorState=SENSOR_STATE_OK;
    }
    tTelStatStruct[ucColOfID].ucTempmissedTimer = 0;
  }

  void static IncrementMissedBlocksSum(uint8 ucColOfID){
    if( ushGetMissedBlocksSum(ucColOfID) < MAX_NUM_BLOCKS){
      PutMissedBlocksSum((ushGetMissedBlocksSum(ucColOfID) + 1), ucColOfID);
    }
    else
    {
      PutMissedBlocksSum((MAX_NUM_BLOCKS >> 1), ucColOfID);
      PutRxBlocksSum((ushGetMissedBlocksSum(ucColOfID) >> 1), ucColOfID);
    }
  }

  void static putTelInfo2Table(uint32 ulID, uint8 ucP, uint8 ucT, uint32 ulTime){
    uint8 ucIDPosInRFStatTable, ucRegister, i;
    uint8 ucMinIx ;
      uint16 uiPaverage;

    ucRegister = 0;
    ucIDPosInRFStatTable = cMaxLR;

    if(ucGetColOfID(&ulID) < cMaxLR){
      ucIDPosInRFStatTable = ucGetColOfID(&ulID);

      for(i=cMaxLR;i<cTableSize;i++){
        if(tTelStatStructV2[i].ulTelID == ulID){
          tTelStatStructV2[i].ulTelID=0;
          tTelStatStructV2[ucIDPosInRFStatTable].ucRxBlocs = tTelStatStructV2[i].ucRxBlocs;
#ifdef AVG_PRESS_ENABLED
          tTelStatStructV2[ucIDPosInRFStatTable].uiAvgP = tTelStatStructV2[i].uiAvgP;
          tTelStatStructV2[ucIDPosInRFStatTable].ucAvgCnt = tTelStatStructV2[i].ucAvgCnt;
#endif
        }
      }
    }
    else
    {
      while (ulID != tTelStatStructV2[ucIDPosInRFStatTable].ulTelID){
        ucIDPosInRFStatTable++;

        if(cTableSize == ucIDPosInRFStatTable){
          ucRegister = 1;
          break;
        }
      }

      if(1 == ucRegister){
        ucIDPosInRFStatTable=cMaxLR;
        while (tTelStatStructV2[ucIDPosInRFStatTable].ulTelID != 0){
          ucIDPosInRFStatTable++;
          if(cTableSize == ucIDPosInRFStatTable){
            break;

          }
        }
      }
    }

    if(ucIDPosInRFStatTable < cTableSize){
      tTelStatStructV2[ucIDPosInRFStatTable].ulTelID = ulID;
      if(ucP > 0x00){
        tTelStatStructV2[ucIDPosInRFStatTable].ucLastValidP = ucP;
      }
      if(ucT > 0x00){
        tTelStatStructV2[ucIDPosInRFStatTable].ucLastValidT = ucT;
       }
      tTelStatStructV2[ucIDPosInRFStatTable].ulLastTime = ulTime;
      tTelStatStructV2[ucIDPosInRFStatTable].ucRxBlocs ++;
#ifdef AVG_PRESS_ENABLED
         if(((bGETucCalRequestState(cCAL_MANUAL_ACTIV)) || (bGETucCalRequestState(cCAL_AUTO_ACTIV))) && (bGetBitFahrzeugzustandFZZ( cKFZFAEHRT_20KMH ) == TRUE )){

            if((tTelStatStructV2[ucIDPosInRFStatTable].ucAvgCnt) != 0xFF){
               tTelStatStructV2[ucIDPosInRFStatTable].ucAvgCnt ++;
               uiPaverage=tTelStatStructV2[ucIDPosInRFStatTable].uiAvgP;
               tTelStatStructV2[ucIDPosInRFStatTable].uiAvgP = uiPaverage + (ucP-AKA_OFFSET);
            }
         }
#endif
    }
    else{
       ucMinIx = cMaxLR;
      for( i = ucMinIx; i < cTableSize; i++){

        if(tTelStatStructV2[i].ucRxBlocs < tTelStatStructV2[ucMinIx].ucRxBlocs){
          ucMinIx = i;
        }
      }
      tTelStatStructV2[ucMinIx].ulTelID = ulID;
      if(ucP > 0x00){
        tTelStatStructV2[ucMinIx].ucLastValidP = ucP;
       }
      if(ucT > 0x00){
        tTelStatStructV2[ucMinIx].ucLastValidT = ucT;
       }
      tTelStatStructV2[ucMinIx].ulLastTime = ulTime;
      tTelStatStructV2[ucMinIx].ucRxBlocs ++;
#ifdef AVG_PRESS_ENABLED
         if(((bGETucCalRequestState(cCAL_MANUAL_ACTIV)) || (bGETucCalRequestState(cCAL_AUTO_ACTIV))) && (bGetBitFahrzeugzustandFZZ( cKFZFAEHRT_20KMH ) == TRUE )){

            if((tTelStatStructV2[ucIDPosInRFStatTable].ucAvgCnt) != 0xFF){
               tTelStatStructV2[ucIDPosInRFStatTable].ucAvgCnt ++;
               uiPaverage=tTelStatStructV2[ucIDPosInRFStatTable].uiAvgP;
               tTelStatStructV2[ucIDPosInRFStatTable].uiAvgP = uiPaverage + (ucP-AKA_OFFSET);
            }
         }
#endif
    }
  }

  uint8 ucGetLastReceivedPress(uint32 ulTelID){
    uint8 i;

    i= cTableSize;

    if(ulTelID!=0 && (ucGetSensorState(ucGetColOfID(&ulTelID)) != SENSOR_STATE_DISTURBED)  && (ucGetSensorState(ucGetColOfID(&ulTelID)) != SENSOR_STATE_MISSING)){
      for(i=0;i<cTableSize;i++){
        if(tTelStatStructV2[i].ulTelID == ulTelID){
          break;
        }
      }
    }
    if( (i<cTableSize) && (tTelStatStructV2[i].ucLastValidP>0x00)  ){
      if(tTelStatStructV2[i].ucLastValidP>0x01){
        return  (uint8)( (tTelStatStructV2[i].ucLastValidP < MAX_RAW_IN_VAL_P) ? (tTelStatStructV2[i].ucLastValidP-AKA_OFFSET) : MAX_OUT_VAL_P);
       }
      else
      {
        return 0x00;
       }
    }
    else
    {
      return 0xFF;
     }
  }

  uint8 ucTelStatGetIDPosInTable(uint32 ulTelID){
    uint8 i;

    for(i=0; i<cTableSize; i++){
      if(tTelStatStructV2[i].ulTelID == ulTelID){
        break;
      }
    }
    return(i);
  }

  uint8 ucGetLastReceivedTemp(uint32 ulTelID){
    uint8 i;

    i= cTableSize;

    if(ulTelID!=0 && (ucGetSensorState(ucGetColOfID(&ulTelID)) != SENSOR_STATE_DISTURBED)  && (ucGetSensorState(ucGetColOfID(&ulTelID)) != SENSOR_STATE_MISSING)){
      for(i=0;i<cTableSize;i++){
        if(tTelStatStructV2[i].ulTelID == ulTelID){
          break;
        }
      }
    }
    if( (i<cTableSize) && (tTelStatStructV2[i].ucLastValidT>0x00) ){
      if(tTelStatStructV2[i].ucLastValidT>0x01){
        return  (uint8)( (tTelStatStructV2[i].ucLastValidT < MAX_RAW_IN_VAL_T) ? (tTelStatStructV2[i].ucLastValidT-AKA_OFFSET) : MAX_OUT_VAL_T);
       }
      else
      {
        return 0x00;
       }
    }
    else
    {
      return 0xFF;
     }
  }

  uint32 ulTelStatGetLastRxTime(uint32 ulTelID){
    uint8 i;

    for(i=0;i<cTableSize;i++){
      if(tTelStatStructV2[i].ulTelID == ulTelID){
        break;
      }
    }

    if(i<cTableSize){
      return  tTelStatStructV2[i].ulLastTime;
     }
    else
    {
      return 0xFFFFFFFF;
    }
  }

  uint8 ucTelStatGetLastRxBlocs(uint32 ulTelID){
    uint8 i;

    for(i=0;i<cTableSize;i++){
      if(tTelStatStructV2[i].ulTelID == ulTelID){
        break;
      }
    }

    if(i<cTableSize){
      return  tTelStatStructV2[i].ucRxBlocs;
     }
    else
    {
      return 0x00;
    }
  }
#ifdef AVG_PRESS_ENABLED
void ClearAvgPress4FD(void){

uint8 i;

   for(i=0;i<cTableSize;i++){
      tTelStatStructV2[i].uiAvgP = 0;
       tTelStatStructV2[i].ucAvgCnt = 0;
    }
}

uint8 ucGetAvgPress4FD(uint32 ulTelID){
  uint8 i;

  i= cTableSize;
   if(ulTelID!=0 && (ucGetSensorState(ucGetColOfID(&ulTelID)) != SENSOR_STATE_DISTURBED)  && (ucGetSensorState(ucGetColOfID(&ulTelID)) != SENSOR_STATE_MISSING)){
    for(i=0;i<cTableSize;i++){
      if(tTelStatStructV2[i].ulTelID == ulTelID){
        break;
      }
    }
  }
  if( (i<cTableSize) && (tTelStatStructV2[i].uiAvgP>0x00)  ){
    if(tTelStatStructV2[i].uiAvgP>0x01){
      return  (uint8)( ((tTelStatStructV2[i].uiAvgP < MAX_RAW_IN_VAL_AVG_P) ? (tTelStatStructV2[i].uiAvgP) : MAX_OUT_VAL_AVG_P) /(tTelStatStructV2[i].ucAvgCnt));
     }
    else
    {
      return 0x00;
     }
  }
  else
  {
    return 0xFF;
   }
}

uint8 ucGetAvgCntr4FD(uint32 ulTelID){
  uint8 i;

  i= cTableSize;
   if(ulTelID!=0 && (ucGetSensorState(ucGetColOfID(&ulTelID)) != SENSOR_STATE_DISTURBED)  && (ucGetSensorState(ucGetColOfID(&ulTelID)) != SENSOR_STATE_MISSING)){
    for(i=0;i<cTableSize;i++){
      if(tTelStatStructV2[i].ulTelID == ulTelID){
        break;
      }
    }
  }
  if( (i<cTableSize) && (tTelStatStructV2[i].uiAvgP>0x00)  ){
    return tTelStatStructV2[i].ucAvgCnt;
  }
  else
  {
    return 0x00;
   }
}
#endif

boolean bGetSensorStateMissing(uint8 ucColOfID){
   return  (boolean)( (ucSensorMissingField>>ucColOfID) & 0x01 );
}

void static SetSensorState2Missing(uint8 ucColOfID){
  ucSensorMissingField |= (0x01<<ucColOfID);
}

void static ClearSensorStateMissing(uint8 ucColOfID){
  ucSensorMissingField &= ~(0x01<<ucColOfID);
}

void UpdateSensorStateAtClamp15Off(void){
  ResetFailureStateSensorDisturbed();
}

 void ResetFailureStateSensorMissing(uint8 ucPos){
   uint8 i, ucCntrMiss, ucCntrDisturb;

   ucCntrMiss = 0;
    ucCntrDisturb = 0;

   if(ucPos < cMaxLR){
      tTelStatStruct[ucPos].ushMuteCntr = 0;
      tTelStatStruct[ucPos].ucSensorState = SENSOR_STATE_UNKNOWN;

      if(pucGetLearnError ()[ucPos] == SensorMissin){
        pucGetLearnError ()[ucPos] = NoError;
      }

      ClearSensorStateMissing(ucPos);
      bSensorHas2BeLearn[ucPos] = TRUE;

      for(i=0; i<cMaxLR; i++){
        if(tTelStatStruct[i].ucSensorState==SENSOR_STATE_MISSING){
          ucCntrMiss++;
        }

        if(tTelStatStruct[i].ucSensorState==SENSOR_STATE_DISTURBED){
          ucCntrDisturb++;
        }
      }
      if(ucCntrMiss > 0){
        ucFailureState = FAILURE_MODE_soWE;
      }
      else if(ucCntrDisturb > 0){
        ucFailureState = FAILURE_MODE_RfInterference;
      }
      else
      {
        ucFailureState = FAILURE_MODE_ok;
        ClearTPM_MsgDispRqSensorsMissing();
        ClearTPM_StatSensorsMissing();
      }
   }
 }

 void ResetFailureStateSensorDisturbed(void){
     uint8 i;
    for(i=0; i<cMaxLR; i++){
      if(tTelStatStruct[i].ucSensorState==SENSOR_STATE_DISTURBED){
        tTelStatStruct[i].ushMuteCntr = 0;
        tTelStatStruct[i].ucSensorState = SENSOR_STATE_UNKNOWN;
      }
    }
    if(ucFailureState == FAILURE_MODE_RfInterference){
      ucFailureState = FAILURE_MODE_ok;
    }
  }
  void static ClearLastRecPressTemp(uint8 ucColOfID){

   uint32 ulTelID;
   uint8 i;

   if(ucColOfID < cMaxLR){
    ulTelID = ulGetID(ucColOfID);

    if(ulTelID != 0){
      for(i=0;i<cTableSize;i++){
        if(tTelStatStructV2[i].ulTelID == ulTelID){
          break;
        }
      }

      if(i<cTableSize){
        tTelStatStructV2[i].ucLastValidP = 0x00;
         tTelStatStructV2[i].ucLastValidT = 0x00;
       }
    }
   }
 }

 boolean bCheckHistIDReception1(void){
   uint8 i;
   boolean bRet = TRUE;

   for(i=0;i<4;i++){
     if(ucTelStatGetLastRxBlocs(ulGetID(i)) < 1){
       bRet = FALSE;
     }
   }
   return bRet;
 }
