/************************************************************************************************************
 * (c) HuF Electronics GmbH      Abteilung ENTS4     2015
 ************************************************************************************************************/

/*********************************************************************************************************//**
 * \file tel_statistic.c
 * \brief Manage telegramm statistics information
 *
 *------------------------------------------------------------------------------------------------------------
 * Global Description
 * 
 *
 *
 *
 *
 *------------------------------------------------------------------------------------------------------------
 * Modul Description
 * 
 *
 * Purpose:
 *
 *
 *
 *------------------------------------------------------------------------------------------------------------
 */


/************************************************************************************************************
 *                                             include
 ************************************************************************************************************/
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
#include "filling_detection.h" /*mgr */
#include "filling_detectionX.h" /*FD */

/************************************************************************************************************
 *                                             macro
 ************************************************************************************************************/
//#define AVG_PRESS_ENABLED --> tel_statisticX.h

#define M_MAX 540U // maximal value mute timer
#define MAX_NUM_BLOCKS 1000U
#define T_MAX_PAL 39U// 

#define AKA_OFFSET 0x02U
#define MAX_RAW_IN_VAL_P 0xFFU
#define MAX_RAW_IN_VAL_T 0xB1U

#define MAX_RAW_IN_VAL_AVG_P 0xFFFFU

#define MAX_OUT_VAL_P MAX_RAW_IN_VAL_P - AKA_OFFSET
#define MAX_OUT_VAL_T MAX_RAW_IN_VAL_T - AKA_OFFSET

#define MAX_OUT_VAL_AVG_P MAX_RAW_IN_VAL_AVG_P - AKA_OFFSET

/************************************************************************************************************
 *                                            typedef
 ************************************************************************************************************/

/************************************************************************************************************
 *                                    data (Modulglobal) - ROM
 ************************************************************************************************************/
typedef struct   /* Stat parameterset*/
{
  uint8 ucSensorState;
  uint16 ushMuteCntr;
  uint8 ucTempmissedTimer;
}telStatStruct;

typedef struct   /* Stat parameterset v2*/
{
  uint32 ulTelID;
  uint8 ucLastValidP;
  uint8 ucLastValidT;
  uint32 ulLastTime;
  uint8 ucRxBlocs;
#ifdef AVG_PRESS_ENABLED
  uint16 uiAvgP; //  CRS_1211_130_362 Pressure in sum 0xFFFF=65535/255= 257*0,025=6,425bar max!
  uint8 ucAvgCnt; // Average counter max:0xff = 255 
#endif
}telStatStructV2;

static telStatStruct tTelStatStruct[cMaxLR];
static telStatStructV2 tTelStatStructV2[cTableSize];
static uint8 ucFailureState = FAILURE_MODE_ok;
static uint8 ucSensorMissingField = 0;
static boolean bModuleIsInitialized = FALSE;
static boolean bAutoLearnCycleCompleted = FALSE;
static boolean bSensorHas2BeLearn[cMaxLR] = {TRUE, TRUE, TRUE, TRUE}; // all sensors need 2 be learnt before setting DTC 2 passed
/************************************************************************************************************
 *                                    data (Modulglobal) - RAM
 ************************************************************************************************************/

/************************************************************************************************************
 *                                       data (global) - ROM
 ************************************************************************************************************/

extern FUNC(Std_ReturnType, DEM_CODE) Dem_SetEventStatus(Dem_EventIdType       EventId, Dem_EventStatusType   EventStatus);
extern FUNC(Std_ReturnType, ECUM_API_CODE) EcuM_GetState(P2VAR(EcuM_StateType, AUTOMATIC, ECUM_APPL_DATA) state);
/************************************************************************************************************
 *                                       data (global) - RAM
 ************************************************************************************************************/



/***********************************************************************************************************
 *                                 prototype (local functions - private)
 ***********************************************************************************************************/
 void static UpdateFailureState(void);
 void static IncrementRxBlocksSum(uint8 ucColOfID);
 void static IncrementMissedBlocksSum(uint8 ucColOfID);  
 void static putTelInfo2Table(uint32 ulID, uint8 ucP, uint8 ucT, uint32 ulTime);
 void static ClearSensorStateMissing(uint8);
 void static SetSensorState2Missing(uint8);
 void static ClearLastRecPressTemp(uint8 ucColOfID);
 void static UpdateMissingSensorsDTCs(void);
 void static UpdateDisturbedSensorsDTCs(void);
/************************************************************************************************************
 *                               prototype (external functions - interface)
 ************************************************************************************************************/
extern void Dem_SetEventExData(uint8);


 /************************************************************************************************//**
 * \brief buid statistics based on received wheel electronic telegramm
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] ulTelID current telegramm ID
 * \param [in] ucTelP  current telegramm pressure
 * \param [in] ucTelT  current telegramm temperature
 * \param [out] tTelStatStruct telegramm statistic structure
 * \return none
 *
 *------------------------------------------------------------------------------------------------
 */
 void BuildTelStatistics(uint32 ulTelID, uint8 ucTelP, uint8 ucTelT, uint32 ulTime, boolean bSensorDefect)
 {
   // only learned wheel sensors should be monitored
   if ( !bSensorDefect) // ignore telegramms with invalid contents
   {
     if(ucGetColOfID(&ulTelID) < cMaxLR)
     {
       //increment rx counter
       IncrementRxBlocksSum(ucGetColOfID(&ulTelID)); 
     }
   }
   
   if(!bSensorDefect)//Save telegramm statistic 
   {
    putTelInfo2Table(ulTelID, ucTelP,  ucTelT, ulTime);
   }else
   {
    putTelInfo2Table(ulTelID, (uint8)0x00,  (uint8)0x00, ulTime);
   }
 }


 /************************************************************************************************//**
 * \brief cyclically update timers based telegramm statistics
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] ucCurrentVehSpeed current vehicle speed
 * \param [in] ucMinPalSpeed minimal needed vehicle speed
 * \param [out] tTelStatStruct telegramm statistic structure
 * \return none
 *
 *------------------------------------------------------------------------------------------------
 */
 void UpdateTelStatInfo(uint16 ushCurrentVehSpeed, uint8 ucMinPalSpeed)
 {
  uint8 i, ucWaToErr;
  EcuM_StateType  EcuM_State;            /* EcuM RUN mode state */


  /* check EcuM state */
  (void)EcuM_GetState(&EcuM_State); // At ECUM_RUN State the DCM is supposed to have been already initialised

  if(bModuleIsInitialized && (EcuM_State == ECUM_STATE_APP_RUN))
  {
     /* update tel stat info according to PAL logic document version 1.4 section 9.1.1 */
    for (i=0; i<cMaxLR; i++)
    {
      // increment mute timer if VSpeed>Vmin
      if (ushCurrentVehSpeed > ucMinPalSpeed)
      {
        if (tTelStatStruct[i].ushMuteCntr < M_MAX)
        {
          tTelStatStruct[i].ushMuteCntr++;
        }
      }  
      else if ( (ushCurrentVehSpeed==0) && (tTelStatStruct[i].ushMuteCntr<T_MAX_PAL) )
      {
        tTelStatStruct[i].ushMuteCntr = 0;     // reset timer
      }

      //------------------------- update missed blocks counter---------------------------------------------------/
      if (ushCurrentVehSpeed > ucMinPalSpeed)
      {
        if (tTelStatStruct[i].ucTempmissedTimer < T_MAX_PAL)
        {
          tTelStatStruct[i].ucTempmissedTimer++;
        }
      }  
      else if ( (ushCurrentVehSpeed==0) && (tTelStatStruct[i].ushMuteCntr<T_MAX_PAL) )
      {
        tTelStatStruct[i].ucTempmissedTimer = 0;     // reset timer
      }

      if(tTelStatStruct[i].ucTempmissedTimer==T_MAX_PAL)
      {
        IncrementMissedBlocksSum(i);
        tTelStatStruct[i].ucTempmissedTimer = 0;     // reset timer
      }

      // ----------------------update sensor state------------------------------------------------------/
      // Get current error code
      Rte_Call_PP_GetWaTOErrorCode_OP_GetWaTOErrorCode(&ucWaToErr, i);
      if(bGetBitBetriebszustandBZ(cZO_ERROR) && (ucWaToErr == SensorMissin))
      {
        SetSensorState2Missing(i);
      }
      if( bGetBitBetriebszustandBZ(cER_FINISH) || (bGetBitBetriebszustandBZ(cZO_ERROR)&&(ucWaToErr != SensorMissin)))
      {
        ClearSensorStateMissing(i);
      }
   
      //-------------------------------------------------------------------------------------------------------
      //if( (bGetBitBetriebszustandBZ(cZO_ERROR) && (ucWaToErr == SensorMissin)) || ( (ucGetSensorDTCState(i)==TRUE) &&  (!bGetBitBetriebszustandBZ(cER_FINISH)) && (!bGetBitBetriebszustandBZ(cZO_TIMEOUT)) )) //autolearn detects missing wheel sensor
      if(bGetSensorStateMissing(i))
      {
        if (  (tTelStatStruct[i].ucSensorState == SENSOR_STATE_MISSING) && (ui8GetDAGAutoLearnState() != Autolearn_Learning) )
        {
          ClearLastRecPressTemp(i); // clear received Pressure and Temperature only once see OIL#1152, OIL#1297 
        }
        tTelStatStruct[i].ucSensorState=SENSOR_STATE_MISSING;

        DelWarnOfId(i); // need to find better place for calling this
        PuT(i,-127);  // temperature 4 TVWarn no longer valide

      }
      else if (tTelStatStruct[i].ushMuteCntr < T_MAX_PAL)
      {
        if (tTelStatStruct[i].ucSensorState!=SENSOR_STATE_UNKNOWN)
        {
          // only move to sensor state ok after receiving first RF telegramm
          tTelStatStruct[i].ucSensorState=SENSOR_STATE_OK;
        }  
      }
      else if (tTelStatStruct[i].ushMuteCntr < M_MAX)
      {
        tTelStatStruct[i].ucSensorState=SENSOR_STATE_SUSPICIOUS;
      }
      else if( (bGetBitBetriebszustandBZ(cZO_FINISH) || bGetBitBetriebszustandBZ(cZO_TIMEOUT)) && (tTelStatStruct[i].ushMuteCntr==M_MAX)) //autolocate is over now, but Mute_Counter = M_Max
      {
        tTelStatStruct[i].ucSensorState=SENSOR_STATE_DISTURBED;
        ClearLastRecPressTemp(i);
      }

    //-----------------------------------------------------------------------------------------------
   }

    // update general failure state
    UpdateFailureState();

    
    if( bGetBitBetriebszustandBZ(cER_FINISH) || bGetBitBetriebszustandBZ(cZO_FINISH) || bGetBitBetriebszustandBZ(cZO_TIMEOUT) )
    {
      if( !bAutoLearnCycleCompleted)
      {
        // update missing sensors DTCs, do it once per learn cycle
        bAutoLearnCycleCompleted = TRUE;
        UpdateMissingSensorsDTCs(); 
      }
      else
      {
        //update disturbed sensors DTC only learn cycle
        //UpdateDisturbedSensorsDTCs();
      }
    }
    UpdateDisturbedSensorsDTCs();
  }
 }

  /************************************************************************************************//**
 * \brief init statistic module
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] ucCurrentVehSpeed current vehicle speed
 * \param [in] ucMinPalSpeed minimal needed vehicle speed
 * \param [out] tTelStatStruct telegramm statistic structure
 * \return none
 *
 *------------------------------------------------------------------------------------------------
 */
 void InitTelStatInfo(void)
 {
    uint16 i;

    // reset all timer after power on reset
    for (i=0; i<cMaxLR; i++)
    {
      tTelStatStruct[i].ushMuteCntr=0;
      tTelStatStruct[i].ucSensorState=SENSOR_STATE_UNKNOWN;
      tTelStatStruct[i].ucTempmissedTimer = 0;
    }
      // TPM failure state
      if( (GETucWAHistSensorState()&0x0F) == FAILURE_MODE_noWE) //low nipple
      {
        ucFailureState = FAILURE_MODE_noWE; 
      }
      /*else if ( *Rte_Pim_Pim_FailureStateNoWheelSensors() == FAILURE_MODE_soWE)
      {
        ucFailureState = FAILURE_MODE_soWE;
      }
      else if ( *Rte_Pim_Pim_FailureStateNoWheelSensors() == FAILURE_MODE_RfInterference)
      {
        ucFailureState = FAILURE_MODE_RfInterference;
      }*/
      else
      {
        ucFailureState = FAILURE_MODE_ok;
      }


      ucSensorMissingField = (GETucWAHistSensorState()&0xF0)>>4;


    /* re init struc */
	  for (i=0;i<sizeof(tTelStatStructV2);i++){
		  *((uint8*)&tTelStatStructV2 + i) = 0;
	  }
    /*for (i=0; i<cMaxLR; i++)
    {
      tTelStatStructV2[i].ulTelID = ulGetID(i); // preload history IDs
    }*/

    bAutoLearnCycleCompleted = FALSE;

    bModuleIsInitialized = TRUE;
 }

 void InitTelStatInfoAtModeChange(void)
 {
   uint8 i;
   	
   //rest all telegramms counters only
   for (i=0;i<cTableSize;i++){
		  tTelStatStructV2[i].ucRxBlocs = 0;
	  }

   bAutoLearnCycleCompleted = FALSE;
 }

 void static UpdateFailureState()
 {

  uint8 i;
  uint8 ucCntrMiss, ucCntrDisturb, ucCntrOk;
  ucCntrMiss =0;
  ucCntrDisturb = 0;
  ucCntrOk = 0;

  // reset all timer after power on reset
  for (i=0; i<cMaxLR; i++)
  {
    if(tTelStatStruct[i].ucSensorState==SENSOR_STATE_MISSING)
    {
      ucCntrMiss++;
    }
        
    if(tTelStatStruct[i].ucSensorState==SENSOR_STATE_DISTURBED)
    {
      ucCntrDisturb++;
    }
    
    if(tTelStatStruct[i].ucSensorState==SENSOR_STATE_OK)
    {
      ucCntrOk++;
    }
  }
  
  // DTCs status are updated hier
  if( (ucCntrMiss==0) && (ucCntrDisturb==0) )// OIL#1090 && (ucCntrOk==cMaxLR))
  {
    ucFailureState = FAILURE_MODE_ok;  
  }
  else if (ucCntrMiss == cMaxLR) // Autolearns fails and all wheel sensors are in Sensor_State_XY = MISSING
  {
    ucFailureState=FAILURE_MODE_noWE;
  }
  else if ( (ucCntrMiss > 0 ) || (ucCntrDisturb > 0)) // some sensors mising or disturbed
  {
    if(ucCntrMiss>0) //missing sensors have higher priority than disturbed ones
    {
      ucFailureState=FAILURE_MODE_soWE;
    }
    else
    {
      ucFailureState = FAILURE_MODE_RfInterference;
    }

  }
  PUTucWAHistSensorState((ucFailureState&0x0F) | ((ucSensorMissingField<<4)&0xF0));
 }

  void static UpdateMissingSensorsDTCs(void)
  {
    uint8 i;
    uint8 ucCntrMiss;
    EcuM_StateType  EcuM_State;            /* EcuM RUN mode state */
    ucCntrMiss =0;

    // reset all timer after power on reset
    for (i=0; i<cMaxLR; i++)
    {
      if(tTelStatStruct[i].ucSensorState==SENSOR_STATE_MISSING)
      {
        ucCntrMiss++;
      }
    }

    /* check EcuM state */
    (void)EcuM_GetState(&EcuM_State); // At ECUM_RUN State the DCM is supposed to have been already initialised

    if( EcuM_State == ECUM_STATE_APP_RUN )
    {
      // DTCs status are updated hier
      if( (ucCntrMiss < cMaxLR)  )
      {    
        // to be optimized
        Dem_SetEventStatus( Dem_DTC_0x551c00, DEM_EVENT_STATUS_PASSED);
      }
      else
      {
        Dem_SetEventStatus( Dem_DTC_0x551c00, DEM_EVENT_STATUS_FAILED);
      }
      for (i=0; i<cMaxLR; i++)
      {
        if ( (ucGetSensorState(i) !=  SENSOR_STATE_DISTURBED) && (ucGetSensorState(i) !=  SENSOR_STATE_MISSING) )         
        {
          switch (i)
          {
            case 0: 
              Dem_SetEventStatus( Dem_DTC_0xd16209, DEM_EVENT_STATUS_PASSED);     //set DTC code 
              bSensorHas2BeLearn[i] = FALSE;
              break;
            case 1: 
              Dem_SetEventStatus( Dem_DTC_0xd16309, DEM_EVENT_STATUS_PASSED);     //set DTC code 
              bSensorHas2BeLearn[i] = FALSE;
              break;
            case 2: 
              Dem_SetEventStatus( Dem_DTC_0xd16409, DEM_EVENT_STATUS_PASSED);     //set DTC code 
              bSensorHas2BeLearn[i] = FALSE;
              break;
            case 3: 
              Dem_SetEventStatus( Dem_DTC_0xd16509, DEM_EVENT_STATUS_PASSED );     //set DTC code 
              bSensorHas2BeLearn[i] = FALSE;
              break;
 /* nothing to do */
          }
        }
        else
        {
          switch (i)
          {
            case 0: 
              Dem_SetEventExData( Dem_DTC_0xd16209); /* interface to external data record */
              Dem_SetEventStatus( Dem_DTC_0xd16209, DEM_EVENT_STATUS_FAILED);     //set DTC code 
              break;
            case 1: 
              Dem_SetEventExData( Dem_DTC_0xd16309); /* interface to external data record */
              Dem_SetEventStatus( Dem_DTC_0xd16309, DEM_EVENT_STATUS_FAILED);     //set DTC code 
              break;
            case 2: 
              Dem_SetEventExData( Dem_DTC_0xd16409); /* interface to external data record */
              Dem_SetEventStatus( Dem_DTC_0xd16409, DEM_EVENT_STATUS_FAILED);     //set DTC code 
              break;
            case 3: 
              Dem_SetEventExData( Dem_DTC_0xd16509 ); /* interface to external data record */
              Dem_SetEventStatus( Dem_DTC_0xd16509, DEM_EVENT_STATUS_FAILED);     //set DTC code 
              break;
          }
        }
      }
    }
  }

 void static UpdateDisturbedSensorsDTCs(void)
 {
  uint8 i;
  uint8 ucCntrDisturb, ucCntrUk, ucCntrSpcs, ucCntrMiss;
  EcuM_StateType  EcuM_State;            /* EcuM RUN mode state */
  ucCntrDisturb = 0;
  ucCntrUk = 0;
  ucCntrSpcs = 0;
  ucCntrMiss = 0;


  // reset all timer after power on reset
  for (i=0; i<cMaxLR; i++)
  {     
    if(tTelStatStruct[i].ucSensorState==SENSOR_STATE_DISTURBED)
    {
      ucCntrDisturb++;
    }
    
    if(tTelStatStruct[i].ucSensorState==SENSOR_STATE_UNKNOWN)
    {
      ucCntrUk++;
    }

    if(tTelStatStruct[i].ucSensorState==SENSOR_STATE_SUSPICIOUS)
    {
      ucCntrSpcs++;
    }
    
    if(tTelStatStruct[i].ucSensorState==SENSOR_STATE_MISSING)
    {
      ucCntrMiss++;
    }
  }

  /* check EcuM state */
  (void)EcuM_GetState(&EcuM_State); // At ECUM_RUN State the DCM is supposed to have been already initialised

  if( EcuM_State == ECUM_STATE_APP_RUN )
  {
    for (i=0; i<cMaxLR; i++)
    {
      if ( ucGetSensorState(i) ==  SENSOR_STATE_DISTURBED)
      {
        // set RF interference DTC if needed
        Dem_SetEventStatus( Dem_DTC_0xa27900, DEM_EVENT_STATUS_FAILED); // set RF interference        

        /* hint: DAI do not make DTC according to mounted position, they make localisation with Status Info Diag Service */
        switch (i)
        {
          case 0: 
            Dem_SetEventExData( Dem_DTC_0xd16209 ); /* interface to external data record */
            Dem_SetEventStatus( Dem_DTC_0xd16209, DEM_EVENT_STATUS_FAILED);     //set DTC code 
            break;
          case 1: 
            Dem_SetEventExData( Dem_DTC_0xd16309 ); /* interface to external data record */
            Dem_SetEventStatus( Dem_DTC_0xd16309, DEM_EVENT_STATUS_FAILED);     //set DTC code 
            break;
          case 2: 
            Dem_SetEventExData( Dem_DTC_0xd16409 ); /* interface to external data record */
            Dem_SetEventStatus( Dem_DTC_0xd16409, DEM_EVENT_STATUS_FAILED);     //set DTC code 
            break;
          case 3: 
            Dem_SetEventExData( Dem_DTC_0xd16509 ); /* interface to external data record */
            Dem_SetEventStatus( Dem_DTC_0xd16509, DEM_EVENT_STATUS_FAILED);     //set DTC code 
            break;
          default:
            ;     /* nothing to do */
        }
      }
      else if( (ucGetSensorState(i) ==  SENSOR_STATE_OK) && (bSensorHas2BeLearn[i] == FALSE))
      {
        switch (i)
        {
          case 0: 
            Dem_SetEventStatus( Dem_DTC_0xd16209, DEM_EVENT_STATUS_PASSED);     //set DTC code 
            break;
          case 1: 
            Dem_SetEventStatus( Dem_DTC_0xd16309, DEM_EVENT_STATUS_PASSED);     //set DTC code 
            break;
          case 2: 
            Dem_SetEventStatus( Dem_DTC_0xd16409, DEM_EVENT_STATUS_PASSED);     //set DTC code 
            break;
          case 3: 
          Dem_SetEventStatus( Dem_DTC_0xd16509, DEM_EVENT_STATUS_PASSED );     //set DTC code 
            break;
          default:
            ;     /* nothing to do */
        }
      }
    }
    if ( (ucCntrDisturb == 0) && (ucCntrUk == 0) && (ucCntrSpcs == 0) && (ucCntrMiss < cMaxLR))
    {
      Dem_SetEventStatus( Dem_DTC_0xa27900, DEM_EVENT_STATUS_PASSED); // set RF interference
    }
  } 
 }

 

 void ResetFailureState(void)
 {
   uint8 i;
     
   //*Rte_Pim_Pim_FailureStateNoWheelSensors() = FAILURE_MODE_ok;
   //Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_FailureStateNoWheelSensors_WriteBlock((const NvM_DestPtr *) Rte_Pim_Pim_FailureStateNoWheelSensors()); // write to nvm
   ucFailureState=FAILURE_MODE_ok;
   PUTucWAHistSensorState(ucFailureState);

    for (i=0; i<cMaxLR; i++)
    {
      tTelStatStruct[i].ushMuteCntr = 0;
      tTelStatStruct[i].ucSensorState = SENSOR_STATE_UNKNOWN;

      if(pucGetLearnError ()[i] == SensorMissin)
      {
        pucGetLearnError ()[i] = NoError;
      }

      ClearSensorStateMissing(i);
      bSensorHas2BeLearn[i] = TRUE; // senseor cleared using diagnostic command, means has 2 be learned again

    }
    ClearTPM_StatNoSensors(); //Reset HMI Signal TPM Stat
    ClearTPM_MsgDispRqNoSensors(); 
 }

 uint8 ucGetFailureState(void)
 {
   return ucFailureState;
 }

  uint16 ushGetTelMuteTime(uint8 ucPos)
 {
   if (ucPos<cMaxLR)
   {
      return tTelStatStruct[ucPos].ushMuteCntr;
   }
   else 
   {
     return 0xFFFF;
   }
 }

  uint8 ucGetSensorState(uint8 ucPos)
  {
   if (ucPos<cMaxLR)
   {
      return tTelStatStruct[ucPos].ucSensorState;
   }
   else 
   {
     return 0;// unknow
   }
 }

  // function is called after new IDs have been learnt. 
 void ClearTelStatisticsStruct(uint8 ucPosMask)
 {
   uint8 i;
   for (i=0; i<cMaxLR; i++)
   {
     if (ucPosMask & (1<<i))
     {
       tTelStatStruct[i].ucSensorState=SENSOR_STATE_OK;
       tTelStatStruct[i].ucTempmissedTimer=0;
       tTelStatStruct[i].ushMuteCntr=0;
     }
   }
 }


  void static IncrementRxBlocksSum(uint8 ucColOfID)
  {
     if( ushGetRxBlocksSum(ucColOfID) < MAX_NUM_BLOCKS)
     {
       PutRxBlocksSum((ushGetRxBlocksSum(ucColOfID) + 1), ucColOfID);
       //tTelStatStruct[ucGetColOfID(&ulTelID)].ushRxBlocks++;
     }
     else
     {
       PutRxBlocksSum((MAX_NUM_BLOCKS >> 1), ucColOfID);
       PutMissedBlocksSum((ushGetMissedBlocksSum(ucColOfID) >> 1), ucColOfID);
     }

    //reset mute timer 
    tTelStatStruct[ucColOfID].ushMuteCntr=0;
    if(tTelStatStruct[ucColOfID].ucSensorState != SENSOR_STATE_MISSING)
    {
      tTelStatStruct[ucColOfID].ucSensorState=SENSOR_STATE_OK; // missing sensors have to be successfully learned again before their status can be changed
    }
    tTelStatStruct[ucColOfID].ucTempmissedTimer = 0;
  }

 
  void static IncrementMissedBlocksSum(uint8 ucColOfID)
  {
    if( ushGetMissedBlocksSum(ucColOfID) < MAX_NUM_BLOCKS)
    {
      PutMissedBlocksSum((ushGetMissedBlocksSum(ucColOfID) + 1), ucColOfID);
      //tTelStatStruct[ucGetColOfID(&ulTelID)].ushRxBlocks++;
    }
    else
    {
      PutMissedBlocksSum((MAX_NUM_BLOCKS >> 1), ucColOfID);
      PutRxBlocksSum((ushGetMissedBlocksSum(ucColOfID) >> 1), ucColOfID);
    }
  }


  void static putTelInfo2Table(uint32 ulID, uint8 ucP, uint8 ucT, uint32 ulTime)
  {
    uint8 ucIDPosInRFStatTable, ucRegister, i;
    uint8 ucMinIx ;
		uint16 uiPaverage;

    ucRegister = 0;
    ucIDPosInRFStatTable = cMaxLR; // first 4 position reserved for prelearned IDs

    //---------check whether ID is set in history or not---------------//
    if(ucGetColOfID(&ulID) < cMaxLR) // ER?
    {
      ucIDPosInRFStatTable = ucGetColOfID(&ulID);
      //-------------------clear ID
      for (i=cMaxLR;i<cTableSize;i++)
      {
        if(tTelStatStructV2[i].ulTelID == ulID)
        {
          tTelStatStructV2[i].ulTelID=0;
          tTelStatStructV2[ucIDPosInRFStatTable].ucRxBlocs = tTelStatStructV2[i].ucRxBlocs; // load counter
#ifdef AVG_PRESS_ENABLED
          tTelStatStructV2[ucIDPosInRFStatTable].uiAvgP = tTelStatStructV2[i].uiAvgP; // CRS_1211_130_362restore average pressure
          tTelStatStructV2[ucIDPosInRFStatTable].ucAvgCnt = tTelStatStructV2[i].ucAvgCnt; // restore counter
#endif
        }
      }
    }
    else
    {
      while (ulID != tTelStatStructV2[ucIDPosInRFStatTable].ulTelID)
      { 
        ucIDPosInRFStatTable++;
      
        if (cTableSize == ucIDPosInRFStatTable)
        {
          ucRegister = 1; //ID not found / new ID. Register this ID in the next step.
          break;
        }
      }

      //New ID. Register this ID
      if (1 == ucRegister)
      {
        //Find free place
        ucIDPosInRFStatTable=cMaxLR;
        while (tTelStatStructV2[ucIDPosInRFStatTable].ulTelID != 0)
        {
          ucIDPosInRFStatTable++;
          if (cTableSize == ucIDPosInRFStatTable)
          {
            break;

          }
        }     
      }
    }
  
    //Register the ID in the free place
    if (ucIDPosInRFStatTable < cTableSize)
    {
      tTelStatStructV2[ucIDPosInRFStatTable].ulTelID = ulID;
      if(ucP > 0x00) //no need to update current pressure with invalid one
      {
        tTelStatStructV2[ucIDPosInRFStatTable].ucLastValidP = ucP; //
      }
      if(ucT > 0x00) //no need to update current temperature with invalid one
      {
        tTelStatStructV2[ucIDPosInRFStatTable].ucLastValidT = ucT; //
      }
      tTelStatStructV2[ucIDPosInRFStatTable].ulLastTime = ulTime;
      tTelStatStructV2[ucIDPosInRFStatTable].ucRxBlocs ++;
#ifdef AVG_PRESS_ENABLED
			if(((bGETucCalRequestState(cCAL_MANUAL_ACTIV)) || (bGETucCalRequestState(cCAL_AUTO_ACTIV))) && (bGetBitFahrzeugzustandFZZ( cKFZFAEHRT_20KMH ) == TRUE )) 
			{			
				/* P Mittelwertbildung fortlaufend Achtung, der AKA_OFFSET wird abgezogen!!! und NUR bis 255*/
				
				if((tTelStatStructV2[ucIDPosInRFStatTable].ucAvgCnt) != 0xFF)
				{
					tTelStatStructV2[ucIDPosInRFStatTable].ucAvgCnt ++;	
					uiPaverage=tTelStatStructV2[ucIDPosInRFStatTable].uiAvgP;	 /*CRS_1211_130_362*/
					tTelStatStructV2[ucIDPosInRFStatTable].uiAvgP = uiPaverage + (ucP-AKA_OFFSET);/*CRS_1211_130_362*/
				}
			}
#endif
    }
    else{ // overwrite ID with lowest receive telegramms
      ucMinIx = cMaxLR;
      for( i = ucMinIx; i < cTableSize; i++)
      {

        if (tTelStatStructV2[i].ucRxBlocs < tTelStatStructV2[ucMinIx].ucRxBlocs)
        {
          ucMinIx = i;
        }
      }
      tTelStatStructV2[ucMinIx].ulTelID = ulID;
      if(ucP > 0x00) ////no need to update current pressure with invalid one
      {
        tTelStatStructV2[ucMinIx].ucLastValidP = ucP; //
      }
      if(ucT > 0x00) //no need to update current temperature with invalid one
      {
        tTelStatStructV2[ucMinIx].ucLastValidT = ucT; //
      }
      tTelStatStructV2[ucMinIx].ulLastTime = ulTime;
      tTelStatStructV2[ucMinIx].ucRxBlocs ++;
#ifdef AVG_PRESS_ENABLED
			if(((bGETucCalRequestState(cCAL_MANUAL_ACTIV)) || (bGETucCalRequestState(cCAL_AUTO_ACTIV))) && (bGetBitFahrzeugzustandFZZ( cKFZFAEHRT_20KMH ) == TRUE )) 
			{      
				/* P Mittelwertbildung fortlaufend Achtung, der AKA_OFFSET wird abgezogen!!! UND NUR bis 255*/
				if((tTelStatStructV2[ucIDPosInRFStatTable].ucAvgCnt) != 0xFF)
				{
					tTelStatStructV2[ucIDPosInRFStatTable].ucAvgCnt ++;		
					uiPaverage=tTelStatStructV2[ucIDPosInRFStatTable].uiAvgP;	/*CRS_1211_130_362*/
					tTelStatStructV2[ucIDPosInRFStatTable].uiAvgP = uiPaverage + (ucP-AKA_OFFSET);	/*CRS_1211_130_362*/				
				}
			}
#endif
    }
  }


  uint8 ucGetLastReceivedPress(uint32 ulTelID)
  {
    uint8 i;

    i= cTableSize;// init

    if (ulTelID!=0 && (ucGetSensorState(ucGetColOfID(&ulTelID)) != SENSOR_STATE_DISTURBED)  && (ucGetSensorState(ucGetColOfID(&ulTelID)) != SENSOR_STATE_MISSING))
    {
      for (i=0;i<cTableSize;i++)
      {
        if(tTelStatStructV2[i].ulTelID == ulTelID)
        {
          break; 
        }
      }
    }
    if( (i<cTableSize) && (tTelStatStructV2[i].ucLastValidP>0x00)  )// init
    {
      if(tTelStatStructV2[i].ucLastValidP>0x01)
      {
        //handle overflow, remove AKA offset
        return  (uint8)( (tTelStatStructV2[i].ucLastValidP < MAX_RAW_IN_VAL_P) ? (tTelStatStructV2[i].ucLastValidP-AKA_OFFSET) : MAX_OUT_VAL_P);//AKA offset
      }
      else
      {
        return 0x00; //underflow
      }
    }
    else
    {
      return 0xFF; // invalid pressure, sensor missing
    }
  }

  uint8 ucTelStatGetIDPosInTable(uint32 ulTelID)
  {
    uint8 i;

    for (i=0; i<cTableSize; i++)
    {
      if (tTelStatStructV2[i].ulTelID == ulTelID)
      {
        break;
      }
    }
    return(i);
  }

 
  uint8 ucGetLastReceivedTemp(uint32 ulTelID)
  {
    uint8 i;

    i= cTableSize;// init
        
    if (ulTelID!=0 && (ucGetSensorState(ucGetColOfID(&ulTelID)) != SENSOR_STATE_DISTURBED)  && (ucGetSensorState(ucGetColOfID(&ulTelID)) != SENSOR_STATE_MISSING))
    {
      for (i=0;i<cTableSize;i++)
      {
        if(tTelStatStructV2[i].ulTelID == ulTelID)
        {
          break; 
        }
      }
    }
    if( (i<cTableSize) && (tTelStatStructV2[i].ucLastValidT>0x00) )// init
    {
      if(tTelStatStructV2[i].ucLastValidT>0x01)
      {
        //handle overflow, remove AKA offset
        return  (uint8)( (tTelStatStructV2[i].ucLastValidT < MAX_RAW_IN_VAL_T) ? (tTelStatStructV2[i].ucLastValidT-AKA_OFFSET) : MAX_OUT_VAL_T);//AKA offset
      }
      else
      {
        return 0x00; //underflow
      }
    }
    else
    {
      return 0xFF; // invalid temperature, sensor missing
    }
  }


  uint32 ulTelStatGetLastRxTime(uint32 ulTelID)
  {
    uint8 i;

    for (i=0;i<cTableSize;i++)
    {
      if(tTelStatStructV2[i].ulTelID == ulTelID)
      {
        break; 
      }
    }

    if(i<cTableSize)// init
    {
      return  tTelStatStructV2[i].ulLastTime; //AKA offset
    }
    else
    {
      return 0xFFFFFFFF;
    }
  }

   
  uint8 ucTelStatGetLastRxBlocs(uint32 ulTelID)
  {
    uint8 i;

    for (i=0;i<cTableSize;i++)
    {
      if(tTelStatStructV2[i].ulTelID == ulTelID)
      {
        break; 
      }
    }

    if(i<cTableSize)// init
    {
      return  tTelStatStructV2[i].ucRxBlocs; //AKA offset
    }
    else
    {
      return 0x00;
    }
  }
#ifdef AVG_PRESS_ENABLED
void ClearAvgPress4FD(void) /*CRS_1211_130_335*/
{

uint8 i;

	for (i=0;i<cTableSize;i++)
	{
		tTelStatStructV2[i].uiAvgP = 0;		// /*CRS_1211_130_362*/ clear all average pressure
		tTelStatStructV2[i].ucAvgCnt = 0;	// clear all average counter
	}
}



uint8 ucGetAvgPress4FD(uint32 ulTelID) /*CRS_1211_130_335*/
{
  uint8 i;

  i= cTableSize;// init
  if (ulTelID!=0 && (ucGetSensorState(ucGetColOfID(&ulTelID)) != SENSOR_STATE_DISTURBED)  && (ucGetSensorState(ucGetColOfID(&ulTelID)) != SENSOR_STATE_MISSING))
  {
    for (i=0;i<cTableSize;i++)
    {
      if(tTelStatStructV2[i].ulTelID == ulTelID)
      {
        break; 
      }
    }
  }
  if( (i<cTableSize) && (tTelStatStructV2[i].uiAvgP>0x00)  )// init
  {
    if(tTelStatStructV2[i].uiAvgP>0x01)
    {
      //handle overflow, remove AKA offset
      return  (uint8)( ((tTelStatStructV2[i].uiAvgP < MAX_RAW_IN_VAL_AVG_P) ? (tTelStatStructV2[i].uiAvgP) : MAX_OUT_VAL_AVG_P) /(tTelStatStructV2[i].ucAvgCnt));//CRS_1211_130_362 AKA offset
    }
    else
    {
      return 0x00; //underflow
    }
  }
  else
  {
    return 0xFF; // invalid pressure, sensor missing
  }
}

uint8 ucGetAvgCntr4FD(uint32 ulTelID) /*CRS_1211_130_335*/
{
  uint8 i;

  i= cTableSize;// init
  if (ulTelID!=0 && (ucGetSensorState(ucGetColOfID(&ulTelID)) != SENSOR_STATE_DISTURBED)  && (ucGetSensorState(ucGetColOfID(&ulTelID)) != SENSOR_STATE_MISSING))
  {
    for (i=0;i<cTableSize;i++)
    {
      if(tTelStatStructV2[i].ulTelID == ulTelID)
      {
        break; 
      }
    }
  }
  if( (i<cTableSize) && (tTelStatStructV2[i].uiAvgP>0x00)  )// init
  {
    return tTelStatStructV2[i].ucAvgCnt;
  }
  else
  {
    return 0x00; // invalid pressure, sensor missing
  }
}
#endif /*CRS_1211_130_335*/

boolean bGetSensorStateMissing(uint8 ucColOfID)
{
   return  (boolean)( (ucSensorMissingField>>ucColOfID) & 0x01 );
}

void static SetSensorState2Missing(uint8 ucColOfID)
{
  ucSensorMissingField |= (0x01<<ucColOfID);
}

void static ClearSensorStateMissing(uint8 ucColOfID)
{
  ucSensorMissingField &= ~(0x01<<ucColOfID);
}


void UpdateSensorStateAtClamp15Off(void)
{
  ResetFailureStateSensorDisturbed();
}


 void ResetFailureStateSensorMissing(uint8 ucPos)
 {
   uint8 i, ucCntrMiss, ucCntrDisturb;

   ucCntrMiss = 0; //init
   ucCntrDisturb = 0; //init

   if(ucPos < cMaxLR)
   {
      tTelStatStruct[ucPos].ushMuteCntr = 0;
      tTelStatStruct[ucPos].ucSensorState = SENSOR_STATE_UNKNOWN;

      if(pucGetLearnError ()[ucPos] == SensorMissin)
      {
        pucGetLearnError ()[ucPos] = NoError;
      }

      ClearSensorStateMissing(ucPos);
      bSensorHas2BeLearn[ucPos] = TRUE; // senseor cleared using diagnostic command, means has 2 be learned again

      for (i=0; i<cMaxLR; i++)
      {
        if(tTelStatStruct[i].ucSensorState==SENSOR_STATE_MISSING)
        {
          ucCntrMiss++;
        }
        
        if(tTelStatStruct[i].ucSensorState==SENSOR_STATE_DISTURBED)
        {
          ucCntrDisturb++;
        }
      }
      if(ucCntrMiss > 0)
      {
        ucFailureState = FAILURE_MODE_soWE;
      }
      else if(ucCntrDisturb > 0)
      {
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

 void ResetFailureStateSensorDisturbed(void)
 {
     uint8 i;
    for (i=0; i<cMaxLR; i++)
    {
      if(tTelStatStruct[i].ucSensorState==SENSOR_STATE_DISTURBED)
      {
        tTelStatStruct[i].ushMuteCntr = 0;
        tTelStatStruct[i].ucSensorState = SENSOR_STATE_UNKNOWN;
      }
    }
    if(ucFailureState == FAILURE_MODE_RfInterference)
    {
      ucFailureState = FAILURE_MODE_ok;
    }
  }

 // Clear last received pressure and temperature
 void static ClearLastRecPressTemp(uint8 ucColOfID)
 {

   uint32 ulTelID;
   uint8 i;
   
   if (ucColOfID < cMaxLR)
   {
    ulTelID = ulGetID(ucColOfID);
    
    if(ulTelID != 0)
    {
      for (i=0;i<cTableSize;i++)
      {
        if(tTelStatStructV2[i].ulTelID == ulTelID)
        {
          break; 
        }
      }

      if(i<cTableSize)// init
      {
        tTelStatStructV2[i].ucLastValidP = 0x00; // set to invalid
        tTelStatStructV2[i].ucLastValidT = 0x00; // set to invalid
      }
    }
   }
 }

 boolean bCheckHistIDReception1(void)
 {
   uint8 i;
   boolean bRet = TRUE;

   for (i=0;i<4;i++)
   {
     if(ucTelStatGetLastRxBlocs(ulGetID(i)) < 1)
     {
       bRet = FALSE;
     }
   }
   return bRet;
 }