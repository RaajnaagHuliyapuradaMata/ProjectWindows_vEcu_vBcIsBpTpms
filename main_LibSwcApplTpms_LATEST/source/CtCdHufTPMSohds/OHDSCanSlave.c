

#include "OHDSCanSlave.h"
#include "OHDSCanSlave_Hw.h"
#include "OHDS_Dem.h"
#include "E2E_P02.h"
#include "OHDSCanSlave_ApIf.h"
#include "OHDSCanSlave_Cbk.h"
#include "SchM_OHDSCanSlave.h"
#if(OHDSCANSLAVE_DEV_ERROR_DETECT == STD_ON)
  #include "Det.h"
#endif

#define OHDSCANSLAVE_STATE_UNINITIALIZED                    (0x00u)
#define OHDSCANSLAVE_STATE_INITIALIZED                      (0x01u)
#define OHDSCANSLAVE_STATE_SYNC_RECEIVED                    (0x02u)
#define OHDSCANSLAVE_STATE_FUP_RECEIVED                     (0x03u)

#define OHDSCANSLAVE_MAXUINT32                              (0xFFFFFFFFu)

#define OHDSCANSLAVE_MAXUINT16                              (0xFFFFu)

#define OHDSCANSLAVE_MAXUINT8                               (0xFFu)

#define OHDSCANSLAVE_OPERATINGHOURS_SNA                     (0xFFFFFFFFu)
#define OHDSCANSLAVE_OPERATINGHOURS_UINT16_SNA              (0xFFFFu)
#define OHDSCANSLAVE_OPERATINGHOURS_MSB_SNA                 (0xFFu)

#define OHDSCANSLAVE_STATUS_SNA                             (0xFFu)

#define OHDSCANSLAVE_STATUS_INIT                            (0x02u)

#define OHDSCANSLAVE_NS_MAXVALUE                            (999999999u)

#define OHDSCANSLAVE_SYNC_TIMEOUT                           (5500000u)

#define OHDSCANSLAVE_SYNCLOSTSTATE_FALSE_DEBOUNCE_TIMEOUT   (11000000u)

#define OHDSCANSLAVE_MAXUPDATE_OFFSET                       (4000000000u/OHDSCANSLAVE_TIMER_NS_PER_TICK)

#define OHDSCANSLAVE_MAX_INTERSYNCFUP_TIME                  (450000000u)

#define OHDSCANSLAVE_TIME_DOMAIN                            (0u)

#if !defined(OHDSCANSLAVE_DEV_ERROR_DETECT) || ( (OHDSCANSLAVE_DEV_ERROR_DETECT != STD_OFF) && (OHDSCANSLAVE_DEV_ERROR_DETECT != STD_ON) )
#error "OHDSCANSLAVE_DEV_ERROR_DETECT must be defined to STD_ON or STD_OFF."
#endif

#if !defined(OHDSCANSLAVE_VERSION_INFO_API) || ( (OHDSCANSLAVE_VERSION_INFO_API != STD_OFF) && (OHDSCANSLAVE_VERSION_INFO_API != STD_ON) )
#error "OHDSCANSLAVE_VERSION_INFO_API must be defined to STD_ON or STD_OFF."
#endif

#if !defined(OHDSCANSLAVE_E2E_AR322SUPPORT) || ( (OHDSCANSLAVE_E2E_AR322SUPPORT != STD_OFF) && (OHDSCANSLAVE_E2E_AR322SUPPORT != STD_ON) )
#error "OHDSCANSLAVE_E2E_AR322SUPPORT must be defined to STD_ON or STD_OFF"
#endif

#if !defined(OHDSCANSLAVE_TIMER_MAX) || ( (OHDSCANSLAVE_TIMER_MAX > 0xFFFFFFFFu) || (OHDSCANSLAVE_TIMER_MAX < 4u) )
#error "OHDSCANSLAVE_TIMER_MAX must be between defined 0x04 and 0xFFFFFFFF. Max. 32bit timer supported."
#endif

#if !defined(OHDSCANSLAVE_TIMER_NS_PER_TICK) || ( (OHDSCANSLAVE_TIMER_NS_PER_TICK < 1u) || (OHDSCANSLAVE_TIMER_NS_PER_TICK > 50000u) )
#error "OHDSCANSLAVE_TIMER_NS_PER_TICK must be defined between 1 and 50000."
#endif

#if !defined(OHDSCANSLAVE_CYCLETIME) || ((OHDSCANSLAVE_CYCLETIME > 50000u) || (OHDSCANSLAVE_CYCLETIME < 100u))
#error "OHDSCANSLAVE_CYCLETIME must be defined between 0.1ms and 50ms."
#endif

#if((1000000u % OHDSCANSLAVE_CYCLETIME) != 0u)
#error "OHDSCANSLAVE_CYCLETIME must be a multiple(integer) of 1 second."
#endif

#if !defined(OHDSCANSLAVE_SW_MAJOR_VERSION) || !defined(OHDSCANSLAVE_SW_MINOR_VERSION) || !defined(OHDSCANSLAVE_SW_PATCH_VERSION) || ( ( OHDSCANSLAVE_SW_MAJOR_VERSION != 0x02u ) || ( OHDSCANSLAVE_SW_MINOR_VERSION != 0x01u ) || ( OHDSCANSLAVE_SW_PATCH_VERSION != 0x01u ) )
# error "OHDSCanSlave.c and OHDSCanSlave.h are not consistent."
#endif
#if !defined(OHDSCANSLAVE_CONFIG_VERSION) || ( OHDSCANSLAVE_CONFIG_VERSION != 0x010201u )
# error "OHDSCanSlave_Config.h file has an incorrect version."
#endif

#if(OHDSCANSLAVE_DEV_ERROR_DETECT == STD_ON)
#define OHDSCanSlave_ReportError(apiID, errorID) Det_ReportError( OHDSCANSLAVE_REPORTERROR_MODULEID ,0u , apiID, errorID)
#else
#define OHDSCanSlave_ReportError(apiID, errorID)
#endif

#define OHDSCanSlave_SetStatusBit_SyncLost()               (OHDSCanSlave_StatusByte |= (uint8) (0x02u))
#define OHDSCanSlave_ClearStatusBit_SyncLost()             (OHDSCanSlave_StatusByte &= (uint8) ~(0x02u))
#define OHDSCanSlave_SetStatusBit_Sync()                   (OHDSCanSlave_StatusByte |= (uint8) (0x01u))
#define OHDSCanSlave_ClearStatusBit_Sync()                 (OHDSCanSlave_StatusByte &= (uint8) ~(0x01u))
#define OHDSCanSlave_GetStatusBit_Sync()                   (OHDSCanSlave_StatusByte & ((uint8) 0x01u))
#define OHDSCanSlave_UpdateStatusBit_SGW(val)              (OHDSCanSlave_StatusByte = (uint8)(((uint8)(OHDSCanSlave_StatusByte & ((uint8) ~(0x08u)))) | ((uint8)(((val) & 0x01u) << 3u))))
#define OHDSCanSlave_UpdateStatusBits_US0_SignalBits(val)  (OHDSCanSlave_StatusByte = (uint8)(((uint8)(OHDSCanSlave_StatusByte & ((uint8) ~(0xf0u)))) | ((uint8)(((val) & 0x0fu) << 4u))))

#define OHDSCanSlave_EnterCritical(area)     SchM_Enter_OHDSCanSlave(area)
#define OHDSCanSlave_LeaveCritical(area)     SchM_Exit_OHDSCanSlave(area)

typedef uint8 OHDSCanSlave_CanSyncMsg[OHDSCANSLAVE_CANSIGNAL_MSGLENGTH];
typedef uint8 OHDSCanSlave_CanFUPMsg[OHDSCANSLAVE_CANSIGNAL_MSGLENGTH];

#define OHDS_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"

STATIC VAR(OHDSCanSlave_CanSyncMsg, OHDS_VAR_NOINIT)  OHDSCanSlave_SyncMsg;
STATIC VAR(OHDSCanSlave_CanFUPMsg, OHDS_VAR_NOINIT)   OHDSCanSlave_FupMsg;

STATIC VAR(E2E_P02ReceiverStateType, OHDS_VAR_NOINIT) OHDSCanSlave_E2EReceiverStateSync;
STATIC VAR(E2E_P02ReceiverStateType, OHDS_VAR_NOINIT) OHDSCanSlave_E2EReceiverStateFup;

#define OHDS_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"

#define OHDS_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

STATIC CONST(E2E_P02ConfigType, OHDS_CONST)           OHDSCanSlave_E2EConfigSync =
{
  ((OHDSCANSLAVE_CANSIGNAL_MSGLENGTH - 1u) * 8u)
  , OHDSCanSlave_Sync_DataID
  , 0x0u
#if(OHDSCANSLAVE_E2E_AR322SUPPORT == STD_ON)
  , 0x00u
  , 0x00u
#endif
};

STATIC CONST(E2E_P02ConfigType, OHDS_CONST)           OHDSCanSlave_E2EConfigFup =
{
  ((OHDSCANSLAVE_CANSIGNAL_MSGLENGTH - 1u) * 8u)
  , OHDSCanSlave_Fup_DataID
  , 0x0u
#if(OHDSCANSLAVE_E2E_AR322SUPPORT == STD_ON)
  , 0x00u
  , 0x00u
#endif
};

#define OHDS_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define OHDS_START_SEC_VAR_ZERO_INIT_8BIT
#include "MemMap.h"

STATIC VAR(uint8, OHDS_VAR_ZERO_INIT)                 OHDSCanSlave_State = OHDSCANSLAVE_STATE_UNINITIALIZED;

#define OHDS_STOP_SEC_VAR_ZERO_INIT_8BIT
#include "MemMap.h"

#define OHDS_START_SEC_VAR_NOINIT_8BIT
#include "MemMap.h"

STATIC VAR(uint8, OHDS_VAR_NOINIT)                    OHDSCanSlave_StatusByte;

VAR(uint8, OHDS_VAR_NOINIT)                           OHDSCanSlave_StatusByte_t2s;

VAR(uint8, OHDS_VAR_NOINIT)                           OHDSCanSlave_OperatingHours_High_t2s;

STATIC VAR(uint8, OHDS_VAR_NOINIT)                    OHDSCanSlave_OperatingHours_High;

STATIC VAR(boolean, OHDS_VAR_NOINIT)                  OHDSCanSlave_SyncLostState;

#define OHDS_STOP_SEC_VAR_NOINIT_8BIT
#include "MemMap.h"

#define OHDS_START_SEC_VAR_NOINIT_32BIT
#include "MemMap.h"

STATIC VAR(uint32, OHDS_VAR_NOINIT)                   OHDSCanSlave_OperatingHours_Low;

STATIC VAR(uint32, OHDS_VAR_NOINIT)                   OHDSCanSlave_Timer_LastUpdate;

STATIC VAR(uint32, OHDS_VAR_NOINIT)                   OHDSCanSlave_Timer_LastUpdateCall;

STATIC VAR(uint32, OHDS_VAR_NOINIT)                   OHDSCanSlave_Timer_UpdateError;

STATIC VAR(uint32, OHDS_VAR_NOINIT)                   OHDSCanSlave_Timer_LastSync;

STATIC VAR(uint32, OHDS_VAR_NOINIT)                   OHDSCanSlave_Timer_SyncOffset;

VAR(uint32, OHDS_VAR_NOINIT)                          OHDSCanSlave_OperatingHours_Low_t2s;

VAR(uint32, OHDS_VAR_NOINIT)                          OHDSCanSlave_OperatingHours_t2s_us;

STATIC VAR(uint32, OHDS_VAR_NOINIT)                   OHDSCanSlave_TimeoutValue;

STATIC VAR(uint32, OHDS_VAR_NOINIT)                   OHDSCanSlave_SyncLostState_TimeoutValue;

#define OHDS_STOP_SEC_VAR_NOINIT_32BIT
#include "MemMap.h"

#define OHDS_START_SEC_CODE
#include "MemMap.h"

STATIC FUNC(void, OHDS_CODE) OHDSCanSlave_UpdateOperatingHoursCounter( P2VAR(uint32, AUTOMATIC, OHDS_APPL_VAR) valueLow,
                                                                       P2VAR(uint8, AUTOMATIC, OHDS_APPL_VAR) valueMsb,
                                                                       P2VAR(uint32, AUTOMATIC, OHDS_APPL_VAR) microSeconds,
                                                                       P2VAR(uint8, AUTOMATIC, OHDS_APPL_VAR) status );
STATIC FUNC(void, OHDS_CODE) OHDSCanSlave_MemCpy( P2CONST(uint8, AUTOMATIC, OHDS_APPL_VAR) src,
                                                  P2VAR(uint8, AUTOMATIC, OHDS_APPL_VAR) dest,
                                                  uint8 cnt );
STATIC FUNC(Std_ReturnType, OHDS_CODE) OHDSCanSlave_HandleFUP( void );
STATIC FUNC(void, OHDS_CODE) OHDSCanSlave_UpdateSyncOffset( void );
STATIC FUNC(void, OHDS_CODE) OHDSCanSlave_Multiply( P2VAR(uint32, AUTOMATIC, OHDS_APPL_VAR) resultLow,
                                                    P2VAR(uint8, AUTOMATIC, OHDS_APPL_VAR) resultHigh,
                                                    uint32 a, uint16 b);

#if(OHDSCANSLAVE_VERSION_INFO_API == STD_ON)

FUNC(void, OHDS_CODE) OHDSCanSlave_GetVersionInfo( P2VAR(Std_VersionInfoType, AUTOMATIC, OHDS_APPL_VAR) versionInfo ){
  if(versionInfo != NULL_PTR){
    versionInfo->vendorID         = OHDSCANSLAVE_VENDOR_ID;
    versionInfo->moduleID         = OHDSCANSLAVE_MODULE_ID;
    versionInfo->instanceID       = 0u;
    versionInfo->sw_major_version = OHDSCANSLAVE_SW_MAJOR_VERSION;
    versionInfo->sw_minor_version = OHDSCANSLAVE_SW_MINOR_VERSION;
    versionInfo->sw_patch_version = OHDSCANSLAVE_SW_PATCH_VERSION;
  }
}
#endif

FUNC(void, OHDS_CODE) OHDSCanSlave_InitMemory( void ){
  OHDSCanSlave_State = OHDSCANSLAVE_STATE_UNINITIALIZED;
}

FUNC(void, OHDS_CODE) OHDSCanSlave_Init( void ){

  OHDSCanSlave_State = OHDSCANSLAVE_STATE_UNINITIALIZED;

  OHDSCanSlave_OperatingHours_Low = 0u;
  OHDSCanSlave_OperatingHours_High = 0u;
  OHDSCanSlave_StatusByte = OHDSCANSLAVE_STATUS_INIT;
  OHDSCanSlave_SyncLostState = TRUE;
  OHDSCanSlave_Timer_UpdateError = 0u;
  OHDSCanSlave_TimeoutValue = 0u;
  OHDSCanSlave_SyncLostState_TimeoutValue = 0u;
  OHDSCanSlave_Timer_LastSync = 0u;
  OHDSCanSlave_Timer_SyncOffset = 0u;

  OHDSCanSlave_E2EReceiverStateSync.LastValidCounter = 0u;
  OHDSCanSlave_E2EReceiverStateSync.LostData = 0u;
  OHDSCanSlave_E2EReceiverStateSync.MaxDeltaCounter = 0u;
  OHDSCanSlave_E2EReceiverStateSync.WaitForFirstData = TRUE;
  OHDSCanSlave_E2EReceiverStateSync.NewDataAvailable = FALSE;
  OHDSCanSlave_E2EReceiverStateSync.Status = E2E_P02STATUS_NONEWDATA;

#if(OHDSCANSLAVE_E2E_AR322SUPPORT == STD_ON)
  OHDSCanSlave_E2EReceiverStateSync.NoNewOrRepeatedDataCounter = 0x00u;
  OHDSCanSlave_E2EReceiverStateSync.SyncCounter = 0x00u;
#endif

  OHDSCanSlave_E2EReceiverStateFup.LastValidCounter = 0u;
  OHDSCanSlave_E2EReceiverStateFup.LostData = 0u;
  OHDSCanSlave_E2EReceiverStateFup.MaxDeltaCounter = 0u;
  OHDSCanSlave_E2EReceiverStateFup.WaitForFirstData = TRUE;
  OHDSCanSlave_E2EReceiverStateFup.NewDataAvailable = FALSE;
  OHDSCanSlave_E2EReceiverStateFup.Status = E2E_P02STATUS_NONEWDATA;

#if(OHDSCANSLAVE_E2E_AR322SUPPORT == STD_ON)
  OHDSCanSlave_E2EReceiverStateFup.NoNewOrRepeatedDataCounter = 0x00u;
  OHDSCanSlave_E2EReceiverStateFup.SyncCounter = 0x00u;
#endif

  OHDSCanSlave_OperatingHours_t2s_us = 0u;
  OHDSCanSlave_OperatingHours_Low_t2s = 0u;
  OHDSCanSlave_OperatingHours_High_t2s = 0u;
  OHDSCanSlave_StatusByte_t2s = OHDSCANSLAVE_STATUS_INIT;

  if( OHDSCanSlave_StartTimer() != E_OK ){
    OHDSCanSlave_Timer_LastUpdate = 0u;
    OHDSCanSlave_Timer_LastUpdateCall = 0u;
    OHDSCanSlave_ReportError(OHDSCANSLAVE_INIT_SID, OHDSCANSLAVE_E_TIMERINIT);
  }
  else{

    OHDSCanSlave_Timer_LastUpdate = OHDSCanSlave_GetTimerValue();
    OHDSCanSlave_Timer_LastUpdateCall = OHDSCanSlave_Timer_LastUpdate;
    OHDSCanSlave_State = OHDSCANSLAVE_STATE_INITIALIZED;
  }
}

FUNC(void, OHDS_CODE) OHDSCanSlave_MainFunction( void ){
  if( OHDSCanSlave_State == OHDSCANSLAVE_STATE_UNINITIALIZED ){
    OHDSCanSlave_ReportError( OHDSCANSLAVE_MAINFUNCTION_SID, OHDSCANSLAVE_E_UNINIT);
  }
  else{
    VAR(Std_ReturnType,AUTOMATIC) syncPerformed = E_NOT_OK;

    if( OHDSCanSlave_State == OHDSCANSLAVE_STATE_SYNC_RECEIVED ){
      OHDSCanSlave_UpdateSyncOffset();
    }
    else if( OHDSCanSlave_State == OHDSCANSLAVE_STATE_FUP_RECEIVED ){

      OHDSCanSlave_E2EReceiverStateSync.NewDataAvailable = TRUE;
      if( E2E_P02Check(&OHDSCanSlave_E2EConfigSync, &OHDSCanSlave_E2EReceiverStateSync, &OHDSCanSlave_SyncMsg[1]) == E2E_E_OK ){
        if( OHDSCanSlave_E2EReceiverStateSync.Status != E2E_P02STATUS_WRONGCRC ){
          syncPerformed = OHDSCanSlave_HandleFUP();
        }
      }

      OHDSCanSlave_State = OHDSCANSLAVE_STATE_INITIALIZED;
    }
    else{  }

    if( syncPerformed == E_OK ){

      OHDSCanSlave_SetStatusBit_Sync();
      OHDSCanSlave_TimeoutValue = OHDSCANSLAVE_SYNC_TIMEOUT;

      if( OHDSCanSlave_SyncLostState != FALSE ){

        OHDSCanSlave_SyncLostState = FALSE;
        OHDSCanSlave_SyncLostState_TimeoutValue = OHDSCANSLAVE_SYNCLOSTSTATE_FALSE_DEBOUNCE_TIMEOUT + OHDSCANSLAVE_CYCLETIME;
      }
    }
    else{

      OHDSCanSlave_UpdateOperatingHoursCounter(NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR);

      if( OHDSCANSLAVE_CYCLETIME >= OHDSCanSlave_TimeoutValue  ){
        OHDSCanSlave_TimeoutValue = 0u;
        OHDSCanSlave_SetStatusBit_SyncLost();

        OHDSCanSlave_SyncLostState = TRUE;
        OHDSCanSlave_SyncLostState_TimeoutValue = 0u;
      }
      else{
        OHDSCanSlave_TimeoutValue -= OHDSCANSLAVE_CYCLETIME;
      }
    }

    if( OHDSCanSlave_SyncLostState_TimeoutValue > 0u ){

      if( OHDSCANSLAVE_CYCLETIME >= OHDSCanSlave_SyncLostState_TimeoutValue ){

        OHDSCanSlave_SyncLostState_TimeoutValue = 0u;
        OHDSCanSlave_ClearStatusBit_SyncLost();
      }
      else{

        OHDSCanSlave_SyncLostState_TimeoutValue -= OHDSCANSLAVE_CYCLETIME;
      }
    }
  }
}

FUNC(void, OHDS_CODE) OHDSCanSlave_RxIndication(PduIdType RxPduId, P2CONST(PduInfoType, AUTOMATIC, OHDS_APPL_VAR) PduInfoPtr){
  if( OHDSCanSlave_State == OHDSCANSLAVE_STATE_UNINITIALIZED  ){

  }
  else{
    if( (RxPduId != 0u) || (PduInfoPtr == NULL_PTR) ){
       OHDSCanSlave_ReportError(OHDSCANSLAVE_RXINDICATION_SID, OHDSCANSLAVE_E_PARAM);
    }
    else{
      if( PduInfoPtr->SduLength >= OHDSCANSLAVE_CANSIGNAL_MSGLENGTH ){
        if( OHDSCanSlave_CanSignal_IsSyncMsg(PduInfoPtr->SduDataPtr) ){
          if( OHDSCanSlave_GetCanSignal_TimeDomain(PduInfoPtr->SduDataPtr) == OHDSCANSLAVE_TIME_DOMAIN ){

            OHDSCanSlave_UpdateOperatingHoursCounter(&OHDSCanSlave_OperatingHours_Low_t2s, &OHDSCanSlave_OperatingHours_High_t2s,
                                                     &OHDSCanSlave_OperatingHours_t2s_us, &OHDSCanSlave_StatusByte_t2s);

            OHDSCanSlave_EnterCritical(OHDSCANSLAVE_EXCLUSIVE_AREA_0);

            OHDSCanSlave_Timer_SyncOffset = 0u;

            OHDSCanSlave_Timer_LastSync = OHDSCanSlave_GetTimerValue();

            OHDSCanSlave_MemCpy(PduInfoPtr->SduDataPtr, OHDSCanSlave_SyncMsg, OHDSCANSLAVE_CANSIGNAL_MSGLENGTH);
            OHDSCanSlave_State = OHDSCANSLAVE_STATE_SYNC_RECEIVED;

            OHDSCanSlave_LeaveCritical(OHDSCANSLAVE_EXCLUSIVE_AREA_0);
          }
        }
        else if( OHDSCanSlave_CanSignal_IsFupMsg(PduInfoPtr->SduDataPtr) ){
          if( OHDSCanSlave_State == OHDSCANSLAVE_STATE_SYNC_RECEIVED ){
            if( OHDSCanSlave_GetCanSignal_TimeDomain(PduInfoPtr->SduDataPtr) == OHDSCANSLAVE_TIME_DOMAIN ){

              OHDSCanSlave_EnterCritical(OHDSCANSLAVE_EXCLUSIVE_AREA_0);

              OHDSCanSlave_MemCpy(PduInfoPtr->SduDataPtr, OHDSCanSlave_FupMsg, OHDSCANSLAVE_CANSIGNAL_MSGLENGTH);

              OHDSCanSlave_State = OHDSCANSLAVE_STATE_FUP_RECEIVED;

              OHDSCanSlave_LeaveCritical(OHDSCANSLAVE_EXCLUSIVE_AREA_0);
            }
          }
        }
        else{  }
      }
    }
  }
}

FUNC(void, OHDS_CODE) OHDSCanSlave_TxConfirmation(PduIdType TxPduId){

  OHDSCanSlave_ReportError(OHDSCANSLAVE_TXCONFIRMATION_SID, OHDSCANSLAVE_E_NOTSUPPORTED);
}

STATIC FUNC(void, OHDS_CODE) OHDSCanSlave_MemCpy( P2CONST(uint8, AUTOMATIC, OHDS_APPL_VAR) src,
                                                  P2VAR(uint8, AUTOMATIC, OHDS_APPL_VAR) dest,
                                                  uint8 cnt ){
  for( ;cnt > 0u; cnt-- ){
    dest[cnt-1u] = src[cnt-1u];
  }
}

STATIC FUNC(Std_ReturnType, OHDS_CODE) OHDSCanSlave_HandleFUP( void ){
  VAR(Std_ReturnType, AUTOMATIC) retVal = E_NOT_OK;

  if( OHDSCanSlave_GetCanSignal_SQC(OHDSCanSlave_FupMsg) == OHDSCanSlave_GetCanSignal_SQC(OHDSCanSlave_SyncMsg) ){

    if( OHDSCanSlave_GetCanSignal_NS(OHDSCanSlave_FupMsg) > OHDSCANSLAVE_NS_MAXVALUE ){
    }
    else{

      OHDSCanSlave_E2EReceiverStateFup.NewDataAvailable = TRUE;
      if( E2E_P02Check(&OHDSCanSlave_E2EConfigFup, &OHDSCanSlave_E2EReceiverStateFup, &OHDSCanSlave_FupMsg[1]) == E2E_E_OK ){
        if( OHDSCanSlave_E2EReceiverStateFup.Status != E2E_P02STATUS_WRONGCRC ){

          VAR(uint32, AUTOMATIC) syncOffsetMS;

          OHDSCanSlave_UpdateSyncOffset();

          OHDSCanSlave_EnterCritical(OHDSCANSLAVE_EXCLUSIVE_AREA_0);

          OHDSCanSlave_Timer_UpdateError = OHDSCanSlave_Timer_SyncOffset;
          OHDSCanSlave_Timer_UpdateError += OHDSCanSlave_GetCanSignal_NS(OHDSCanSlave_FupMsg);

          syncOffsetMS = (OHDSCanSlave_Timer_UpdateError / 1000000u);
          syncOffsetMS += OHDSCanSlave_GetCanSignal_OVS(OHDSCanSlave_FupMsg) * 1000u;

          OHDSCanSlave_Timer_UpdateError = (OHDSCanSlave_Timer_UpdateError % 1000000u);

          OHDSCanSlave_Multiply(&OHDSCanSlave_OperatingHours_Low, &OHDSCanSlave_OperatingHours_High, OHDSCanSlave_GetCanSignal_SEC(OHDSCanSlave_SyncMsg), 1000u);

          if( (OHDSCANSLAVE_MAXUINT32 - syncOffsetMS) >= OHDSCanSlave_OperatingHours_Low  ){
            OHDSCanSlave_OperatingHours_Low += syncOffsetMS;
          }
          else{

            OHDSCanSlave_OperatingHours_High++;

            OHDSCanSlave_OperatingHours_Low = syncOffsetMS - ((OHDSCANSLAVE_MAXUINT32 - OHDSCanSlave_OperatingHours_Low) + 1u );
          }

          OHDSCanSlave_Timer_LastUpdate = OHDSCanSlave_GetTimerValue();
          OHDSCanSlave_Timer_LastUpdateCall = OHDSCanSlave_Timer_LastUpdate;

          OHDSCanSlave_UpdateStatusBit_SGW(OHDSCanSlave_GetCanSignal_SGW(OHDSCanSlave_FupMsg));

          OHDSCanSlave_UpdateStatusBits_US0_SignalBits(OHDSCanSlave_GetCanData_US0_SignalBits(OHDSCanSlave_SyncMsg));

          OHDSCanSlave_LeaveCritical(OHDSCANSLAVE_EXCLUSIVE_AREA_0);

          retVal = E_OK;
        }
      }
    }
  }
  return retVal;
}

STATIC FUNC(void, OHDS_CODE) OHDSCanSlave_UpdateSyncOffset( void ){
  VAR(uint32, AUTOMATIC) timerValue;
  VAR(uint32, AUTOMATIC) deltaTNS;

  OHDSCanSlave_EnterCritical(OHDSCANSLAVE_EXCLUSIVE_AREA_0);

  timerValue = OHDSCanSlave_GetTimerValue();
  if(timerValue < OHDSCanSlave_Timer_LastSync){
    deltaTNS = OHDSCANSLAVE_TIMER_MAX - OHDSCanSlave_Timer_LastSync;

    deltaTNS += timerValue + 1u;
  }
  else{
    deltaTNS = timerValue - OHDSCanSlave_Timer_LastSync;
  }

  deltaTNS *= OHDSCANSLAVE_TIMER_NS_PER_TICK;

  if( (OHDSCANSLAVE_MAX_INTERSYNCFUP_TIME - deltaTNS) >= OHDSCanSlave_Timer_SyncOffset ){
    OHDSCanSlave_Timer_SyncOffset += deltaTNS;
  }
  else{
    OHDSCanSlave_Timer_SyncOffset = 0u;
    OHDSCanSlave_State = OHDSCANSLAVE_STATE_INITIALIZED;
  }

  OHDSCanSlave_Timer_LastSync = timerValue;

  OHDSCanSlave_LeaveCritical(OHDSCANSLAVE_EXCLUSIVE_AREA_0);
}

STATIC FUNC(void, OHDS_CODE) OHDSCanSlave_UpdateOperatingHoursCounter( P2VAR(uint32, AUTOMATIC, OHDS_APPL_VAR) valueLow,
                                                                       P2VAR(uint8, AUTOMATIC, OHDS_APPL_VAR) valueMsb,
                                                                       P2VAR(uint32, AUTOMATIC, OHDS_APPL_VAR) microSeconds,
                                                                       P2VAR(uint8, AUTOMATIC, OHDS_APPL_VAR) status ){
  VAR(boolean, AUTOMATIC) performUpdate = FALSE;
  VAR(uint32, AUTOMATIC) timerValue;

  VAR(uint32, AUTOMATIC) tmpOHCounterLow = 0u;
  VAR(uint8, AUTOMATIC) tmpOHCounterHigh = 0u;
  VAR(uint32, AUTOMATIC) tmpNanoSeconds = 0u;

  OHDSCanSlave_EnterCritical(OHDSCANSLAVE_EXCLUSIVE_AREA_0);

  timerValue = OHDSCanSlave_GetTimerValue();

  if( timerValue < OHDSCanSlave_Timer_LastUpdateCall  ){
    tmpNanoSeconds = OHDSCANSLAVE_TIMER_MAX - OHDSCanSlave_Timer_LastUpdate;

    tmpNanoSeconds += timerValue + 1u;

    performUpdate = TRUE;
  }
  else{
    tmpNanoSeconds = timerValue - OHDSCanSlave_Timer_LastUpdate;
  }

  OHDSCanSlave_Timer_LastUpdateCall = timerValue;

  if( tmpNanoSeconds >= OHDSCANSLAVE_MAXUPDATE_OFFSET ){
    performUpdate = TRUE;
  }

  if( (performUpdate == TRUE) || (valueLow != NULL_PTR) ){

    tmpNanoSeconds *= OHDSCANSLAVE_TIMER_NS_PER_TICK;

    tmpNanoSeconds += OHDSCanSlave_Timer_UpdateError;

    tmpOHCounterLow = tmpNanoSeconds / 1000000u;

    tmpNanoSeconds = tmpNanoSeconds % 1000000u;

    if( (OHDSCANSLAVE_MAXUINT32 - tmpOHCounterLow) >= OHDSCanSlave_OperatingHours_Low ){
      tmpOHCounterLow += OHDSCanSlave_OperatingHours_Low;
      tmpOHCounterHigh = OHDSCanSlave_OperatingHours_High;
    }
    else{
      if( OHDSCanSlave_OperatingHours_High == OHDSCANSLAVE_MAXUINT8 ){
        tmpOHCounterHigh = 0x00u;
      }
      else{
        tmpOHCounterHigh = OHDSCanSlave_OperatingHours_High + 1u;
      }

      tmpOHCounterLow = tmpOHCounterLow - ((OHDSCANSLAVE_MAXUINT32 - OHDSCanSlave_OperatingHours_Low) + 1u);
    }

    if( performUpdate == TRUE ){

      OHDSCanSlave_Timer_LastUpdate = timerValue;

      OHDSCanSlave_OperatingHours_Low = tmpOHCounterLow;
      OHDSCanSlave_OperatingHours_High = tmpOHCounterHigh;
      OHDSCanSlave_Timer_UpdateError = tmpNanoSeconds;
    }

    if( valueLow != NULL_PTR ){
      *valueLow = tmpOHCounterLow;

      if( valueMsb != NULL_PTR ){
        *valueMsb = tmpOHCounterHigh;
      }
      if( microSeconds != NULL_PTR ){
        *microSeconds = tmpNanoSeconds / 1000u;
      }
      if( status != NULL_PTR ){
        *status = OHDSCanSlave_StatusByte;
      }
    }
  }
  OHDSCanSlave_LeaveCritical(OHDSCANSLAVE_EXCLUSIVE_AREA_0);
}

FUNC(Std_ReturnType, OHDS_CODE) OHDSCanSlave_GetOperatingHoursUint16( P2VAR(uint16, AUTOMATIC, OHDS_APPL_VAR) value,
                                                                      P2VAR(uint8, AUTOMATIC, OHDS_APPL_VAR) status ){
  VAR(Std_ReturnType, AUTOMATIC) retValue = E_OK;

  if( OHDSCanSlave_State == OHDSCANSLAVE_STATE_UNINITIALIZED ){
    retValue = E_NOT_OK;
    OHDSCanSlave_ReportError(OHDSCANSLAVE_GETOHUINT16_SID, OHDSCANSLAVE_E_UNINIT);

    if(value != NULL_PTR ){
      *value = OHDSCANSLAVE_OPERATINGHOURS_UINT16_SNA;
    }
    if(status != NULL_PTR){
      *status  = OHDSCANSLAVE_STATUS_SNA;
    }
  }
  else{

    if(value != NULL_PTR){
      VAR(uint32, AUTOMATIC) tmpOHLow;
      OHDSCanSlave_UpdateOperatingHoursCounter(&tmpOHLow, NULL_PTR, NULL_PTR, status);

      *value =  (uint16)tmpOHLow;
    }
  }

  return retValue;
}

FUNC(Std_ReturnType, OHDS_CODE) OHDSCanSlave_GetOperatingHours( P2VAR(uint32, AUTOMATIC, OHDS_APPL_VAR) value,
                                                                P2VAR(uint8, AUTOMATIC, OHDS_APPL_VAR) valueMsb,
                                                                P2VAR(uint8, AUTOMATIC, OHDS_APPL_VAR) status ){
  VAR(Std_ReturnType, AUTOMATIC) retValue = E_OK;

  if( OHDSCanSlave_State == OHDSCANSLAVE_STATE_UNINITIALIZED ){
    retValue = E_NOT_OK;
    OHDSCanSlave_ReportError(OHDSCANSLAVE_GETOH_SID, OHDSCANSLAVE_E_UNINIT);

    if((value != NULL_PTR) && (valueMsb != NULL_PTR)){
      *value = OHDSCANSLAVE_OPERATINGHOURS_SNA;
      *valueMsb = OHDSCANSLAVE_OPERATINGHOURS_MSB_SNA;
    }
    if(status != NULL_PTR){
      *status  = OHDSCANSLAVE_STATUS_SNA;
    }
  }
  else{
    if((value != NULL_PTR) && (valueMsb != NULL_PTR)){
      OHDSCanSlave_UpdateOperatingHoursCounter(value, valueMsb, NULL_PTR, status );
    }
  }

  return retValue;
}

FUNC(Std_ReturnType, OHDS_CODE) OHDS_Dem_GetOperatingHours( P2VAR(uint32, AUTOMATIC, OHDS_APPL_VAR) value,
                                                            P2VAR(uint8, AUTOMATIC, OHDS_APPL_VAR) status ){
  VAR(Std_ReturnType, AUTOMATIC) retValue = E_OK;

  if( OHDSCanSlave_State == OHDSCANSLAVE_STATE_UNINITIALIZED ){
    retValue = E_NOT_OK;
    OHDSCanSlave_ReportError(OHDSCANSLAVE_DEM_GETOH_SID, OHDSCANSLAVE_E_UNINIT);

    if(value != NULL_PTR){
      *value = OHDSCANSLAVE_OPERATINGHOURS_SNA;
    }
    if(status != NULL_PTR){
      *status  = OHDSCANSLAVE_STATUS_SNA;
    }
  }
  else{

    if(value != NULL_PTR){
      OHDSCanSlave_UpdateOperatingHoursCounter(value, NULL_PTR, NULL_PTR, status);
    }
  }

  return retValue;
}

#if(OHDSCANSLAVE_VERSION_INFO_API == STD_ON)

FUNC(void, OHDS_CODE) OHDS_Dem_GetVersionInfo( P2VAR(Std_VersionInfoType, AUTOMATIC, OHDS_APPL_VAR) versionInfo ){
  OHDSCanSlave_GetVersionInfo(versionInfo);
}
#endif

STATIC FUNC(void, OHDS_CODE) OHDSCanSlave_Multiply( P2VAR(uint32, AUTOMATIC, OHDS_APPL_VAR) resultLow,
                                                    P2VAR(uint8, AUTOMATIC, OHDS_APPL_VAR) resultHigh,
                                                    uint32 a, uint16 b){
  VAR(uint32, AUTOMATIC) alb, ahb, tmpResult;

  alb = (a & 0xFFFFu) * b;
  ahb = (a >> 16u) * b;

  tmpResult = ahb + (alb >> 16u);

  *resultHigh = (uint8)(tmpResult >> 16u);
  *resultLow  = ((tmpResult & 0xFFFFu) << 16u) + (alb & 0xFFFFu);
}

#define OHDS_STOP_SEC_CODE
#include "MemMap.h"

