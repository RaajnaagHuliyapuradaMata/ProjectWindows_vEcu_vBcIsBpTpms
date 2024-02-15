/**************************************************************************************************
   Project Name: Operating Hours Distribution Service (OHDS) - CAN Slave
      File Name: OHDSCanSlave.c

    Description: Implementation of the OHDS CAN Slave component

  -------------------------------------------------------------------------------------------------
       C O P Y R I G H T
  -------------------------------------------------------------------------------------------------
       Copyright (c) 2014 by Vector Informatik GmbH. All rights reserved.

       This software is copyright protected and proprietary to Vector Informatik GmbH.
       Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
       All other rights remain with Vector Informatik GmbH.


       REMOVAL OF THESE COMMENTS IS A VIOLATION OF THE COPYRIGHT AGREEMENT.

  -------------------------------------------------------------------------------------------------
                 A U T H O R   I D E N T I T Y
  -------------------------------------------------------------------------------------------------
   Initials     Name                      Company
   --------     ---------------------     ---------------------------------------------------------
   vislki       Lothar Kieble             Vector Informatik GmbH
   viseml       Michael Epping            Vector Informatik GmbH
   visart       Andreas Reifert           Vector Informatik GmbH
  -------------------------------------------------------------------------------------------------
                 R E V I S I O N   H I S T O R Y
  -------------------------------------------------------------------------------------------------
   Date         Rev.     Author  Description
   ----------   -------  ------  ------------------------------------------------------------------
   2013-12-09   1.0.0    vislki  Initial creation
   2014-01-14   1.0.1    vislki  Minor changes for MISRA compliance
   2014-01-23   1.1.0    vislki  Moved Sync calculation to MainFunction
   2014-01-27            vislki  Added error handling
   2014-01-27            vislki  Moved signal access layer to header file
   2014-02-10            vislki  Increased accurateness of OH counter extrapolation
   2014-02-19   1.1.1    vislki  Stack size optimization and usage of AUTOSAR macros for
                                 local variables
   2014-03-05            vislki  Renamed Compiler_Cfg and MemMap defines
   2014-03-07            vislki  Reorganized interrupt locks
   2014-03-11            viseml  Code Inspection
   2014-03-13            vislki  Incorporated findings from code inspection
   2014-03-21            viseml  Support for different E2ELib versions, Config checks adapted
   2014-07-18   2.0.0    visart  New frame format
   2014-07-18            visart  Refactoring of constants
   2014-07-18            visart  Added sync lost bit debouncing
   2014-07-21            visart  Moved timer, sync, sync lost handling to MainFunction completely
   2014-07-22            visart  Updated timeout timer handling
   2014-07-24            visart  Extended configuration parameters error handling
   2014-07-25            visart  Added ZERO_INIT for internal state
   2014-07-25            visart  Added OHDSCanSlave_InitMemory
   2014-07-29            viseml  Code Inspection
   2014-09-23   2.1.0    viseml  ISS009
   2015-04-29   2.1.1    viseml  ISS023
**************************************************************************************************/

/**************************************************************************************************
* Include files
**************************************************************************************************/
#include "OHDSCanSlave.h"
#include "OHDSCanSlave_Hw.h"
#include "OHDS_Dem.h"
#include "E2E_P02.h"
#include "OHDSCanSlave_ApIf.h"
#include "OHDSCanSlave_Cbk.h"
#include "SchM_OHDSCanSlave.h"
#if (OHDSCANSLAVE_DEV_ERROR_DETECT == STD_ON)
  #include "Det.h"
#endif
/**************************************************************************************************
* Defines / Constants
**************************************************************************************************/

/* State definitions */
#define OHDSCANSLAVE_STATE_UNINITIALIZED                    (0x00u)  /* Module not initialized yet */    
#define OHDSCANSLAVE_STATE_INITIALIZED                      (0x01u)  /* Module has been initialized */
#define OHDSCANSLAVE_STATE_SYNC_RECEIVED                    (0x02u)  /* Sync message has been received. Wait for FUP */
#define OHDSCANSLAVE_STATE_FUP_RECEIVED                     (0x03u)  /* Sync and FUP message have been received. Perform Sync */  

/* Maximum possible uint32 value */
#define OHDSCANSLAVE_MAXUINT32                              (0xFFFFFFFFu)
/* Maximum possible uint16 value */
#define OHDSCANSLAVE_MAXUINT16                              (0xFFFFu)
/* Maximum possible uint8 value */
#define OHDSCANSLAVE_MAXUINT8                               (0xFFu)

/* Application SNA for operating hours */
#define OHDSCANSLAVE_OPERATINGHOURS_SNA                     (0xFFFFFFFFu)
#define OHDSCANSLAVE_OPERATINGHOURS_UINT16_SNA              (0xFFFFu)
#define OHDSCANSLAVE_OPERATINGHOURS_MSB_SNA                 (0xFFu)
/* Application SNA for status byte */
#define OHDSCANSLAVE_STATUS_SNA                             (0xFFu)
/* Initial value for status byte */
#define OHDSCANSLAVE_STATUS_INIT                            (0x02u)

/* Max allowed value for NS signal in FUP message */
#define OHDSCANSLAVE_NS_MAXVALUE                            (999999999u) /* < 1 second */

/* Timeout value of SYNC message in us */
#define OHDSCANSLAVE_SYNC_TIMEOUT                           (5500000u)

/* Timeout value of debouncing sync lost bit in us */
#define OHDSCANSLAVE_SYNCLOSTSTATE_FALSE_DEBOUNCE_TIMEOUT   (11000000u)

/* The maximum number of hardware ticks which can be collected before updating internal OH */
#define OHDSCANSLAVE_MAXUPDATE_OFFSET                       (4000000000u/OHDSCANSLAVE_TIMER_NS_PER_TICK)
/* The maximum allowed time [ns] between receiving Sync and receiving FUP message */
#define OHDSCANSLAVE_MAX_INTERSYNCFUP_TIME                  (450000000u)

/* Time domain to accept signals for, min. 0, max. 15 */
#define OHDSCANSLAVE_TIME_DOMAIN                            (0u)

/**************************************************************************************************
* Configuration Checks
**************************************************************************************************/
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

#if ((1000000u % OHDSCANSLAVE_CYCLETIME) != 0u)
#error "OHDSCANSLAVE_CYCLETIME must be a multiple(integer) of 1 second."
#endif

/* Version checks */
#if !defined(OHDSCANSLAVE_SW_MAJOR_VERSION) || !defined(OHDSCANSLAVE_SW_MINOR_VERSION) || !defined(OHDSCANSLAVE_SW_PATCH_VERSION) || ( ( OHDSCANSLAVE_SW_MAJOR_VERSION != 0x02u ) || ( OHDSCANSLAVE_SW_MINOR_VERSION != 0x01u ) || ( OHDSCANSLAVE_SW_PATCH_VERSION != 0x01u ) )
# error "OHDSCanSlave.c and OHDSCanSlave.h are not consistent."
#endif
#if !defined(OHDSCANSLAVE_CONFIG_VERSION) || ( OHDSCANSLAVE_CONFIG_VERSION != 0x010201u )
# error "OHDSCanSlave_Config.h file has an incorrect version."
#endif

/**************************************************************************************************
* Macros
**************************************************************************************************/

/* PRQA S 3453 OHDSCANSLAVE_MACRO_C */ /* MD_OHDSCANSLAVE_19.7_FUNCTION_LIKE_MACRO */

/* Error reporting API */
#if (OHDSCANSLAVE_DEV_ERROR_DETECT == STD_ON)
  #define OHDSCanSlave_ReportError(apiID, errorID) Det_ReportError( OHDSCANSLAVE_REPORTERROR_MODULEID ,0u /*Instance*/, apiID, errorID)
#else
  #define OHDSCanSlave_ReportError(apiID, errorID) /* Development error detection not active */
#endif

/* Status byte access */
#define OHDSCanSlave_SetStatusBit_SyncLost()               (OHDSCanSlave_StatusByte |= (uint8) (0x02u))
#define OHDSCanSlave_ClearStatusBit_SyncLost()             (OHDSCanSlave_StatusByte &= (uint8) ~(0x02u))
#define OHDSCanSlave_SetStatusBit_Sync()                   (OHDSCanSlave_StatusByte |= (uint8) (0x01u))
#define OHDSCanSlave_ClearStatusBit_Sync()                 (OHDSCanSlave_StatusByte &= (uint8) ~(0x01u))
#define OHDSCanSlave_GetStatusBit_Sync()                   (OHDSCanSlave_StatusByte & ((uint8) 0x01u))
#define OHDSCanSlave_UpdateStatusBit_SGW(val)              (OHDSCanSlave_StatusByte = (uint8)(((uint8)(OHDSCanSlave_StatusByte & ((uint8) ~(0x08u)))) | ((uint8)(((val) & 0x01u) << 3u))))
#define OHDSCanSlave_UpdateStatusBits_US0_SignalBits(val)  (OHDSCanSlave_StatusByte = (uint8)(((uint8)(OHDSCanSlave_StatusByte & ((uint8) ~(0xf0u)))) | ((uint8)(((val) & 0x0fu) << 4u))))

/* Redefine of enter/leave critical section macros */
#define OHDSCanSlave_EnterCritical(area)     SchM_Enter_OHDSCanSlave(area)
#define OHDSCanSlave_LeaveCritical(area)     SchM_Exit_OHDSCanSlave(area)

/* PRQA L:OHDSCANSLAVE_MACRO_C */

/**************************************************************************************************
* Typedef and Struct definitions
**************************************************************************************************/

typedef uint8 OHDSCanSlave_CanSyncMsg[OHDSCANSLAVE_CANSIGNAL_MSGLENGTH];
typedef uint8 OHDSCanSlave_CanFUPMsg[OHDSCANSLAVE_CANSIGNAL_MSGLENGTH];

/**************************************************************************************************
* Data definitions
**************************************************************************************************/

#define OHDS_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_19.1 */ 

/* Content of received messages*/
STATIC VAR(OHDSCanSlave_CanSyncMsg, OHDS_VAR_NOINIT)  OHDSCanSlave_SyncMsg;
STATIC VAR(OHDSCanSlave_CanFUPMsg, OHDS_VAR_NOINIT)   OHDSCanSlave_FupMsg; 

/* State variables for E2E check */
STATIC VAR(E2E_P02ReceiverStateType, OHDS_VAR_NOINIT) OHDSCanSlave_E2EReceiverStateSync;
STATIC VAR(E2E_P02ReceiverStateType, OHDS_VAR_NOINIT) OHDSCanSlave_E2EReceiverStateFup;

#define OHDS_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_19.1 */ 


#define OHDS_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_19.1 */ 

/* Config variables for E2E check */
/* PRQA S 3218 1 */ /* MD_OHDSCANSLAVE_8.7_STATIC_ACCESS */
STATIC CONST(E2E_P02ConfigType, OHDS_CONST)           OHDSCanSlave_E2EConfigSync = 
{
  ((OHDSCANSLAVE_CANSIGNAL_MSGLENGTH - 1u) * 8u) /* value in bits - 7 bytes are considered (Mux is left out) */
  , OHDSCanSlave_Sync_DataID                     /* DataID */
  , 0x0u                                         /* MaxDeltaCounterInit */
#if (OHDSCANSLAVE_E2E_AR322SUPPORT == STD_ON)
  , 0x00u                                        /* uint8  MaxNoNewOrRepeatedData - Number of consecutively received
                                                                                    valid counter values required */
  , 0x00u                                        /* uint8  SyncCounterInit - Initial maximum allowed gap between two
                                                                             consecutively received valid counter values */
#endif
};
/* PRQA S 3218 1 */ /* MD_OHDSCANSLAVE_8.7_STATIC_ACCESS */
STATIC CONST(E2E_P02ConfigType, OHDS_CONST)           OHDSCanSlave_E2EConfigFup = 
{
  ((OHDSCANSLAVE_CANSIGNAL_MSGLENGTH - 1u) * 8u) /* value in bits - 7 bytes are considered (Mux is left out) */
  , OHDSCanSlave_Fup_DataID                      /* DataID */
  , 0x0u                                         /* MaxDeltaCounterInit */
#if (OHDSCANSLAVE_E2E_AR322SUPPORT == STD_ON)
  , 0x00u                                        /* uint8  MaxNoNewOrRepeatedData - Number of consecutively received
                                                                                    valid counter values required */
  , 0x00u                                        /* uint8  SyncCounterInit - Initial maximum allowed gap between two
                                                                             consecutively received valid counter values */
#endif
};

#define OHDS_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_19.1 */ 

#define OHDS_START_SEC_VAR_ZERO_INIT_8BIT
#include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_19.1 */

/* The state of the component */
STATIC VAR(uint8, OHDS_VAR_ZERO_INIT)                 OHDSCanSlave_State = OHDSCANSLAVE_STATE_UNINITIALIZED;

#define OHDS_STOP_SEC_VAR_ZERO_INIT_8BIT
#include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_19.1 */

#define OHDS_START_SEC_VAR_NOINIT_8BIT
#include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_19.1 */

/* OHDS status byte */
STATIC VAR(uint8, OHDS_VAR_NOINIT)                    OHDSCanSlave_StatusByte;

/* OHDS status byte for DAG test (snapshot) */
/* PRQA S 3408 2 */ /* MD_OHDSCANSLAVE_8.8_EXTERNAL_LINKAGE */
/* PRQA S 1504 1 */ /* MD_OHDSCANSLAVE_8.10_EXTERNAL_LINKAGE */
VAR(uint8, OHDS_VAR_NOINIT)                           OHDSCanSlave_StatusByte_t2s;
/* The 5th byte of the operating hours counter for DAG test (Snapshot) */
/* PRQA S 3408 2 */ /* MD_OHDSCANSLAVE_8.8_EXTERNAL_LINKAGE */
/* PRQA S 1504 1 */ /* MD_OHDSCANSLAVE_8.10_EXTERNAL_LINKAGE */
VAR(uint8, OHDS_VAR_NOINIT)                           OHDSCanSlave_OperatingHours_High_t2s;

/* The 5th byte of the operating hours counter: Resolution: 1ms */
STATIC VAR(uint8, OHDS_VAR_NOINIT)                    OHDSCanSlave_OperatingHours_High;

/* The internal sync lost state */
STATIC VAR(boolean, OHDS_VAR_NOINIT)                  OHDSCanSlave_SyncLostState;

#define OHDS_STOP_SEC_VAR_NOINIT_8BIT
#include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_19.1 */

#define OHDS_START_SEC_VAR_NOINIT_32BIT
#include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_19.1 */

/* The lower bytes of the operating hours counter: Resolution: 1ms */
STATIC VAR(uint32, OHDS_VAR_NOINIT)                   OHDSCanSlave_OperatingHours_Low;
/* Hardware timestamp of the last update of internal operating hours. */
STATIC VAR(uint32, OHDS_VAR_NOINIT)                   OHDSCanSlave_Timer_LastUpdate;
/* Hardware timestamp of the last call of UpdateOperatingHours. Used for 
  timer overflow detection.*/
STATIC VAR(uint32, OHDS_VAR_NOINIT)                   OHDSCanSlave_Timer_LastUpdateCall; 
/* the aggregated error in ns we made during the last update steps */
STATIC VAR(uint32, OHDS_VAR_NOINIT)                   OHDSCanSlave_Timer_UpdateError; 
/* Hardware timestamp of the last received Sync message*/
STATIC VAR(uint32, OHDS_VAR_NOINIT)                   OHDSCanSlave_Timer_LastSync;
/* Time in ns since last received RxIndication of Sync message   */
STATIC VAR(uint32, OHDS_VAR_NOINIT)                   OHDSCanSlave_Timer_SyncOffset;

/* The lower bytes of the operating hours counter for DAG test (Snapshot) */
/* PRQA S 3408 2 */ /* MD_OHDSCANSLAVE_8.8_EXTERNAL_LINKAGE */
/* PRQA S 1504 1 */ /* MD_OHDSCANSLAVE_8.10_EXTERNAL_LINKAGE */
VAR(uint32, OHDS_VAR_NOINIT)                          OHDSCanSlave_OperatingHours_Low_t2s;
/* The ms offset for DAG test (Snapshot) (Resolution: 1us) */
/* PRQA S 3408 2 */ /* MD_OHDSCANSLAVE_8.8_EXTERNAL_LINKAGE */
/* PRQA S 1504 1 */ /* MD_OHDSCANSLAVE_8.10_EXTERNAL_LINKAGE */
VAR(uint32, OHDS_VAR_NOINIT)                          OHDSCanSlave_OperatingHours_t2s_us;

/* Timer used for timeout handling of CAN message. Is loaded with timeout value and decreased in 
every MainFunction call. Value is specified in us */
STATIC VAR(uint32, OHDS_VAR_NOINIT)                   OHDSCanSlave_TimeoutValue;
/* Timer used for Sync Lost bit flank to zero debouncing. Is loaded with timeout value and decreased in 
every MainFunction call. Value is specified in us. */
STATIC VAR(uint32, OHDS_VAR_NOINIT)                   OHDSCanSlave_SyncLostState_TimeoutValue;

#define OHDS_STOP_SEC_VAR_NOINIT_32BIT
#include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_19.1 */


/**************************************************************************************************
* Prototypes for local functions
**************************************************************************************************/
#define OHDS_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

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

/**************************************************************************************************
*  Implementation
**************************************************************************************************/

#if (OHDSCANSLAVE_VERSION_INFO_API == STD_ON)
/**************************************************************************************************
   Function name    : OHDSCanSlave_GetVersionInfo
   ------------------------------------------------------------------------------------------------
   Description      : This function returns module information in a standardized format. 
   ------------------------------------------------------------------------------------------------
   Called by        : Application
   ------------------------------------------------------------------------------------------------
   Parameter        : versionInfo: Std_VersionInfoType*
   ------------------------------------------------------------------------------------------------
   Returncode       : -
   ------------------------------------------------------------------------------------------------
   Misc             : -
**************************************************************************************************/
FUNC(void, OHDS_CODE) OHDSCanSlave_GetVersionInfo( P2VAR(Std_VersionInfoType, AUTOMATIC, OHDS_APPL_VAR) versionInfo )
{
  if (versionInfo != NULL_PTR)
  {
    versionInfo->vendorID         = OHDSCANSLAVE_VENDOR_ID;
    versionInfo->moduleID         = OHDSCANSLAVE_MODULE_ID;
    versionInfo->instanceID       = 0u;
    versionInfo->sw_major_version = OHDSCANSLAVE_SW_MAJOR_VERSION;
    versionInfo->sw_minor_version = OHDSCANSLAVE_SW_MINOR_VERSION;
    versionInfo->sw_patch_version = OHDSCANSLAVE_SW_PATCH_VERSION;
  }
}
#endif /* OHDSCANSLAVE_VERSION_INFO_API */

/**************************************************************************************************
   Function name    : OHDSCanSlave_InitMemory
   ------------------------------------------------------------------------------------------------
   Description      : Initializes the CDD internal states
   ------------------------------------------------------------------------------------------------
   Called by        : EcuM
   ------------------------------------------------------------------------------------------------
   Parameter        : -
   ------------------------------------------------------------------------------------------------
   Returncode       : -
   ------------------------------------------------------------------------------------------------
   Misc             : -
**************************************************************************************************/
FUNC(void, OHDS_CODE) OHDSCanSlave_InitMemory( void )
{
  OHDSCanSlave_State = OHDSCANSLAVE_STATE_UNINITIALIZED;
}

/**************************************************************************************************
   Function name    : OHDSCanSlave_Init
   ------------------------------------------------------------------------------------------------
   Description      : Initializes the CDD internal states and starts the timer
   ------------------------------------------------------------------------------------------------
   Called by        : EcuM
   ------------------------------------------------------------------------------------------------
   Parameter        : -
   ------------------------------------------------------------------------------------------------
   Returncode       : -
   ------------------------------------------------------------------------------------------------
   Misc             : -
**************************************************************************************************/
FUNC(void, OHDS_CODE) OHDSCanSlave_Init( void )
{
  /* Set state to uninitialized to avoid unintended access to variables during
    startup/restart caused by RxIndication */
  OHDSCanSlave_State = OHDSCANSLAVE_STATE_UNINITIALIZED;

  /* Internal variables */
  OHDSCanSlave_OperatingHours_Low = 0u;
  OHDSCanSlave_OperatingHours_High = 0u;
  OHDSCanSlave_StatusByte = OHDSCANSLAVE_STATUS_INIT;
  OHDSCanSlave_SyncLostState = TRUE;
  OHDSCanSlave_Timer_UpdateError = 0u;
  OHDSCanSlave_TimeoutValue = 0u;
  OHDSCanSlave_SyncLostState_TimeoutValue = 0u;
  OHDSCanSlave_Timer_LastSync = 0u;
  OHDSCanSlave_Timer_SyncOffset = 0u;

  /* E2E state structures */
  OHDSCanSlave_E2EReceiverStateSync.LastValidCounter = 0u;
  OHDSCanSlave_E2EReceiverStateSync.LostData = 0u;
  OHDSCanSlave_E2EReceiverStateSync.MaxDeltaCounter = 0u;
  OHDSCanSlave_E2EReceiverStateSync.WaitForFirstData = TRUE;
  OHDSCanSlave_E2EReceiverStateSync.NewDataAvailable = FALSE;
  OHDSCanSlave_E2EReceiverStateSync.Status = E2E_P02STATUS_NONEWDATA;

#if (OHDSCANSLAVE_E2E_AR322SUPPORT == STD_ON)
  OHDSCanSlave_E2EReceiverStateSync.NoNewOrRepeatedDataCounter = 0x00u;
  OHDSCanSlave_E2EReceiverStateSync.SyncCounter = 0x00u;
#endif

  OHDSCanSlave_E2EReceiverStateFup.LastValidCounter = 0u;
  OHDSCanSlave_E2EReceiverStateFup.LostData = 0u;
  OHDSCanSlave_E2EReceiverStateFup.MaxDeltaCounter = 0u;
  OHDSCanSlave_E2EReceiverStateFup.WaitForFirstData = TRUE;
  OHDSCanSlave_E2EReceiverStateFup.NewDataAvailable = FALSE;
  OHDSCanSlave_E2EReceiverStateFup.Status = E2E_P02STATUS_NONEWDATA;

#if (OHDSCANSLAVE_E2E_AR322SUPPORT == STD_ON)
  OHDSCanSlave_E2EReceiverStateFup.NoNewOrRepeatedDataCounter = 0x00u;
  OHDSCanSlave_E2EReceiverStateFup.SyncCounter = 0x00u;
#endif

  /* DAG test vars */
  OHDSCanSlave_OperatingHours_t2s_us = 0u;
  OHDSCanSlave_OperatingHours_Low_t2s = 0u;
  OHDSCanSlave_OperatingHours_High_t2s = 0u;
  OHDSCanSlave_StatusByte_t2s = OHDSCANSLAVE_STATUS_INIT;

  /* Start the HW timer (if not already done by basic software) */
  if( OHDSCanSlave_StartTimer() != E_OK )
  { /* Timer initialization was not successful. Stay in state uninitialized */
    OHDSCanSlave_Timer_LastUpdate = 0u;
    OHDSCanSlave_Timer_LastUpdateCall = 0u;
    OHDSCanSlave_ReportError(OHDSCANSLAVE_INIT_SID, OHDSCANSLAVE_E_TIMERINIT);
  }
  else
  { /* Timer initialization was successful */
    /* Receive the current timer value (in case timer is initialized by basic software) */
    OHDSCanSlave_Timer_LastUpdate = OHDSCanSlave_GetTimerValue();
    OHDSCanSlave_Timer_LastUpdateCall = OHDSCanSlave_Timer_LastUpdate;
    OHDSCanSlave_State = OHDSCANSLAVE_STATE_INITIALIZED;
  }
}

/**************************************************************************************************
   Function name    : OHDSCanSlave_MainFunction
   ------------------------------------------------------------------------------------------------
   Description      : Executes state machine of component
   ------------------------------------------------------------------------------------------------
   Called by        : SchM
   ------------------------------------------------------------------------------------------------
   Parameter        : -
   ------------------------------------------------------------------------------------------------
   Returncode       : -
   ------------------------------------------------------------------------------------------------
   Misc             : -
**************************************************************************************************/
FUNC(void, OHDS_CODE) OHDSCanSlave_MainFunction( void )
{
  if( OHDSCanSlave_State == OHDSCANSLAVE_STATE_UNINITIALIZED )
  { /* Module is not initialized. Report error. */
    OHDSCanSlave_ReportError( OHDSCANSLAVE_MAINFUNCTION_SID, OHDSCANSLAVE_E_UNINIT);
  }
  else
  {
    VAR(Std_ReturnType,AUTOMATIC) syncPerformed = E_NOT_OK;
  
    /* Depending of internal state decide which action to perform */
    if( OHDSCanSlave_State == OHDSCANSLAVE_STATE_SYNC_RECEIVED )
    { /* Update ns counter for sync if sync is active (Just SYNC messages received) */
      OHDSCanSlave_UpdateSyncOffset();
    }
    else if( OHDSCanSlave_State == OHDSCANSLAVE_STATE_FUP_RECEIVED )
    { /* Sync and Fup received. Update OH counter */
      /* CRC check - Is the sync messages accepted? If Crc is ok switch to Sync Received state */
      /* CRC calculation is started with byte 1 - multiplexer byte is left out */
      OHDSCanSlave_E2EReceiverStateSync.NewDataAvailable = TRUE; /* Signalize that there is new data available */
      if( E2E_P02Check(&OHDSCanSlave_E2EConfigSync, &OHDSCanSlave_E2EReceiverStateSync, &OHDSCanSlave_SyncMsg[1]) == E2E_E_OK )
      { /* Check call was OK. Prove whether there was no CRC error */
        if( OHDSCanSlave_E2EReceiverStateSync.Status != E2E_P02STATUS_WRONGCRC )
        { /* CRC check of Sync was ok. HandleFUP. */
          syncPerformed = OHDSCanSlave_HandleFUP();
        }
      }
      /* State transition to IDLE */
      OHDSCanSlave_State = OHDSCANSLAVE_STATE_INITIALIZED;
    }
    else 
    { /* No synchronisation ongoing. */ }

    if( syncPerformed == E_OK )
    {
      /* Sync has been performed within this call */

      /* Set sync bit and reload timeout timer */
      OHDSCanSlave_SetStatusBit_Sync();
      OHDSCanSlave_TimeoutValue = OHDSCANSLAVE_SYNC_TIMEOUT;

      /* Reset sync lost state to FALSE */
      if( OHDSCanSlave_SyncLostState != FALSE )
      {
        /* Clear sync lost state and reload debouncing timer */
        OHDSCanSlave_SyncLostState = FALSE;
        OHDSCanSlave_SyncLostState_TimeoutValue = OHDSCANSLAVE_SYNCLOSTSTATE_FALSE_DEBOUNCE_TIMEOUT + OHDSCANSLAVE_CYCLETIME; /* will be decremented by OHDSCANSLAVE_CYCLETIME in this call below again */
      }
    }
    else
    { /* No sync has been performed within this call */
      /* Update the internal operating hours counter */
      OHDSCanSlave_UpdateOperatingHoursCounter(NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR);

      /* Timeout handling */
      if( OHDSCANSLAVE_CYCLETIME >= OHDSCanSlave_TimeoutValue  )
      { /* Timeout. Set sync lost state, sync lost bit, and stop debouncing. */
        OHDSCanSlave_TimeoutValue = 0u;
        OHDSCanSlave_SetStatusBit_SyncLost();

        OHDSCanSlave_SyncLostState = TRUE;
        OHDSCanSlave_SyncLostState_TimeoutValue = 0u;
      }
      else
      { /* No timeout. Decrease counter. */
        OHDSCanSlave_TimeoutValue -= OHDSCANSLAVE_CYCLETIME;
      }
    }

    /* Sync lost bit handling */
    if( OHDSCanSlave_SyncLostState_TimeoutValue > 0u )
    {
      /* (Edge to zero!) debouncing is in progress */
      if( OHDSCANSLAVE_CYCLETIME >= OHDSCanSlave_SyncLostState_TimeoutValue )
      {
        /* Debouncing timeout. Stop timer, clear sync lost bit. */
        OHDSCanSlave_SyncLostState_TimeoutValue = 0u;
        OHDSCanSlave_ClearStatusBit_SyncLost();
      }
      else
      {
        /* Decreased timer is still positive, i.e., sync lost bit remains set */
        OHDSCanSlave_SyncLostState_TimeoutValue -= OHDSCANSLAVE_CYCLETIME;
      }
    }
  }
}

/**************************************************************************************************
   Function name    : OHDSCanSlave_RxIndication
   ------------------------------------------------------------------------------------------------
   Description      : Indication about received SYNC or FUP message. If received message is a SYNC
                      message data buffer is stored and a timer is started. If a FUP message is
                      received the Operating Hours counter is updated if all checks are successfully
                      passed.
   ------------------------------------------------------------------------------------------------
   Called by        : PduR
   ------------------------------------------------------------------------------------------------
   Parameter        : RxPduId: The pduId of the received PDU
                      PduInfoPtr: Information about the received PDU containing the actual message
                                  buffer.
   ------------------------------------------------------------------------------------------------
   Returncode       : -
   ------------------------------------------------------------------------------------------------
   Misc             : -
**************************************************************************************************/
FUNC(void, OHDS_CODE) OHDSCanSlave_RxIndication(PduIdType RxPduId, P2CONST(PduInfoType, AUTOMATIC, OHDS_APPL_VAR) PduInfoPtr)
{
  if( OHDSCanSlave_State == OHDSCANSLAVE_STATE_UNINITIALIZED  )
  { 
    /* Module has not been initialized. Do not report a development error to avoid unintended Det
    during startup/restart */ 
  }
  else
  { /* Module initialization has been performed. */
    if( (RxPduId != 0u) || (PduInfoPtr == NULL_PTR) ) 
    { /* Received PDU shall always have ID 0. DataPtr shall be not null */
       OHDSCanSlave_ReportError(OHDSCANSLAVE_RXINDICATION_SID, OHDSCANSLAVE_E_PARAM);    
    }
    else 
    { /* SYNC or FUP messages received */
      if( PduInfoPtr->SduLength >= OHDSCANSLAVE_CANSIGNAL_MSGLENGTH )
      { /* DLC check */
        if( OHDSCanSlave_CanSignal_IsSyncMsg(PduInfoPtr->SduDataPtr) )
        { /* Sync message received */
          if( OHDSCanSlave_GetCanSignal_TimeDomain(PduInfoPtr->SduDataPtr) == OHDSCANSLAVE_TIME_DOMAIN )
          { /* Sync message is just valid for configured Time Domain - ISS009 */
                      
            /* Snapshot for DAG test */
            OHDSCanSlave_UpdateOperatingHoursCounter(&OHDSCanSlave_OperatingHours_Low_t2s, &OHDSCanSlave_OperatingHours_High_t2s, 
                                                     &OHDSCanSlave_OperatingHours_t2s_us, &OHDSCanSlave_StatusByte_t2s);
  
            OHDSCanSlave_EnterCritical(OHDSCANSLAVE_EXCLUSIVE_AREA_0);
  
            /* Reset Sync offset */
            OHDSCanSlave_Timer_SyncOffset = 0u;
            /* Store hardware timer value*/
            OHDSCanSlave_Timer_LastSync = OHDSCanSlave_GetTimerValue(); 

            /* Copy the data buffer */
            OHDSCanSlave_MemCpy(PduInfoPtr->SduDataPtr, OHDSCanSlave_SyncMsg, OHDSCANSLAVE_CANSIGNAL_MSGLENGTH);
            OHDSCanSlave_State = OHDSCANSLAVE_STATE_SYNC_RECEIVED;

            OHDSCanSlave_LeaveCritical(OHDSCANSLAVE_EXCLUSIVE_AREA_0);
          }
        }
        else if( OHDSCanSlave_CanSignal_IsFupMsg(PduInfoPtr->SduDataPtr) )
        { /* FUP message received */
          if( OHDSCanSlave_State == OHDSCANSLAVE_STATE_SYNC_RECEIVED )
          { /* FUP expected: accept */
            if( OHDSCanSlave_GetCanSignal_TimeDomain(PduInfoPtr->SduDataPtr) == OHDSCANSLAVE_TIME_DOMAIN )
            { /* FUP message is just valid for configured Time Domain */
              /* Copy the data buffer */
  
              OHDSCanSlave_EnterCritical(OHDSCANSLAVE_EXCLUSIVE_AREA_0);
  
              OHDSCanSlave_MemCpy(PduInfoPtr->SduDataPtr, OHDSCanSlave_FupMsg, OHDSCANSLAVE_CANSIGNAL_MSGLENGTH);
  
              /* Transition to Fup received state */
              OHDSCanSlave_State = OHDSCANSLAVE_STATE_FUP_RECEIVED;
  
              OHDSCanSlave_LeaveCritical(OHDSCANSLAVE_EXCLUSIVE_AREA_0);
            }
          }
        }
        else 
        { /*Message is neither SYNC nor FUP message. */ }
      }
    }
  }
}

/**************************************************************************************************
   Function name    : OHDSCanSlave_TxConfirmation
   ------------------------------------------------------------------------------------------------
   Description      : Confirmation about a sent PDU. This function should not be called by the PduR
                      because the OHDSCanSlave is not allowed to transmit data for now.
   ------------------------------------------------------------------------------------------------
   Called by        : PduR
   ------------------------------------------------------------------------------------------------
   Parameter        : TxPduId: The pduId of the transmitted PDU.
   ------------------------------------------------------------------------------------------------
   Returncode       : -
   ------------------------------------------------------------------------------------------------
   Misc             : -
**************************************************************************************************/
/* PRQA S 3206 1 */ /* Function is dependency of PduR, but unused */
FUNC(void, OHDS_CODE) OHDSCanSlave_TxConfirmation(PduIdType TxPduId)
{
  /* Call is not allowed. Just call DET */
  OHDSCanSlave_ReportError(OHDSCANSLAVE_TXCONFIRMATION_SID, OHDSCANSLAVE_E_NOTSUPPORTED);
}

/**************************************************************************************************
   Function name    : OHDSCanSlave_MemCpy
   ------------------------------------------------------------------------------------------------
   Description      : Copy data from one buffer to another
   ------------------------------------------------------------------------------------------------
   Called by        : OHDSCanSlave_RxIndication
   ------------------------------------------------------------------------------------------------
   Parameter        : src: Pointer to the source data buffer
                      dest: Pointer to the destination data buffer
                      cnt: Number of elements to copy
   ------------------------------------------------------------------------------------------------
   Returncode       : -
   ------------------------------------------------------------------------------------------------
   Misc             : -
**************************************************************************************************/
STATIC FUNC(void, OHDS_CODE) OHDSCanSlave_MemCpy( P2CONST(uint8, AUTOMATIC, OHDS_APPL_VAR) src,
                                                  P2VAR(uint8, AUTOMATIC, OHDS_APPL_VAR) dest, 
                                                  uint8 cnt )
{
  for( ;cnt > 0u; cnt-- )
  {
    dest[cnt-1u] = src[cnt-1u];
  }
}

/**************************************************************************************************
   Function name    : OHDSCanSlave_HandleFUP
   ------------------------------------------------------------------------------------------------
   Description      : Handle a received FUP message.
   ------------------------------------------------------------------------------------------------
   Called by        : OHDSCanSlave_MainFunction
   ------------------------------------------------------------------------------------------------
   Parameter        : -
   ------------------------------------------------------------------------------------------------
   Returncode       : E_OK: If Synchronisation has been performed successfully
                      E_NOT_OK: If Synchronisation has not been performed
   ------------------------------------------------------------------------------------------------
   Misc             : -
**************************************************************************************************/
STATIC FUNC(Std_ReturnType, OHDS_CODE) OHDSCanSlave_HandleFUP( void )
{
  VAR(Std_ReturnType, AUTOMATIC) retVal = E_NOT_OK;
  /* Compare sequence counters of Sync and Fup which each other */
  if( OHDSCanSlave_GetCanSignal_SQC(OHDSCanSlave_FupMsg) == OHDSCanSlave_GetCanSignal_SQC(OHDSCanSlave_SyncMsg) )
  { /* Sequence counter of FUP and SYNC message must fit together.*/   
    /* Check for SNA of FUP message */
    if( OHDSCanSlave_GetCanSignal_NS(OHDSCanSlave_FupMsg) > OHDSCANSLAVE_NS_MAXVALUE )
    { /* FUP signal has been received with SNA. Do not sync. */
    }
    else
    { /* Both signal values are in valid range (SYNC SEC signal is cut off to 29bit). Synchronize. */

      /* CRC check of Fup */
      /* CRC calculation is started with byte 1 - multiplexer byte is left out */
      OHDSCanSlave_E2EReceiverStateFup.NewDataAvailable = TRUE; /* Signalize that there is new data available */ 
      if( E2E_P02Check(&OHDSCanSlave_E2EConfigFup, &OHDSCanSlave_E2EReceiverStateFup, &OHDSCanSlave_FupMsg[1]) == E2E_E_OK )
      { /* Check call was OK. Prove whether there was no CRC error */
        if( OHDSCanSlave_E2EReceiverStateFup.Status != E2E_P02STATUS_WRONGCRC )
        { /* CRC chec was ok. All other errors are ignored */
          /* calculate the new operating hours counter */
          VAR(uint32, AUTOMATIC) syncOffsetMS;    
          /* MS and NS part of the offset */

          OHDSCanSlave_UpdateSyncOffset();

          OHDSCanSlave_EnterCritical(OHDSCANSLAVE_EXCLUSIVE_AREA_0);
          
          OHDSCanSlave_Timer_UpdateError = OHDSCanSlave_Timer_SyncOffset;
          OHDSCanSlave_Timer_UpdateError += OHDSCanSlave_GetCanSignal_NS(OHDSCanSlave_FupMsg);
          /* add OVS to syncOffsetMS (see below), as OHDSCanSlave_Timer_UpdateError shall only contain error < 1ms (see below) */

          /* Consider OVS in milliseconds and milliseconds of nano seconds signal as well */
          syncOffsetMS = (OHDSCanSlave_Timer_UpdateError / 1000000u);
          syncOffsetMS += OHDSCanSlave_GetCanSignal_OVS(OHDSCanSlave_FupMsg) * 1000u;
          /* The recognized error which is < 1ms is also remembered for extrapolation */
          OHDSCanSlave_Timer_UpdateError = (OHDSCanSlave_Timer_UpdateError % 1000000u);
    
          /* syncOffsetMS now contains the offset (measured + FUP) in ms (rounded down). OHDSCanSlave_Timer_UpdateError contains
           the remaining offset in ns */

          /* Multiply the received seconds counter with 1000 to get milliseconds */
          OHDSCanSlave_Multiply(&OHDSCanSlave_OperatingHours_Low, &OHDSCanSlave_OperatingHours_High, OHDSCanSlave_GetCanSignal_SEC(OHDSCanSlave_SyncMsg), 1000u);
    
          if( (OHDSCANSLAVE_MAXUINT32 - syncOffsetMS) >= OHDSCanSlave_OperatingHours_Low  )
          { /* no overflow in operating hours */
            OHDSCanSlave_OperatingHours_Low += syncOffsetMS;
          }
          else 
          { /* overflow in lower part of operating hours */
            /* Because operating hours from the master is much smaller than the local
               counter there could be no overflow of the high byte here.*/
            OHDSCanSlave_OperatingHours_High++;
            /* calculate the rest which is new lower part of the operating hours counter */
            OHDSCanSlave_OperatingHours_Low = syncOffsetMS - ((OHDSCANSLAVE_MAXUINT32 - OHDSCanSlave_OperatingHours_Low) + 1u );
          }
    
          /* update the update hardware timestamp */
          OHDSCanSlave_Timer_LastUpdate = OHDSCanSlave_GetTimerValue();
          OHDSCanSlave_Timer_LastUpdateCall = OHDSCanSlave_Timer_LastUpdate;

          /* Sync lost state is set in MainFunction (together with sync lost bit and debouncing handling outside critical section) */

          /* Set sync status bits */
          /* Sync bit is set in MainFunction (outside critical section) */
          /* Sync lost bit is derived from sync lost state in MainFunction (outside critical section) */
          /* Take over status bit SGW from Fup message */
          OHDSCanSlave_UpdateStatusBit_SGW(OHDSCanSlave_GetCanSignal_SGW(OHDSCanSlave_FupMsg));
          /* Take over status bits RP, TD, TSZ, and USB from Sync message */
          OHDSCanSlave_UpdateStatusBits_US0_SignalBits(OHDSCanSlave_GetCanData_US0_SignalBits(OHDSCanSlave_SyncMsg));
    
          OHDSCanSlave_LeaveCritical(OHDSCANSLAVE_EXCLUSIVE_AREA_0);

          retVal = E_OK;
        }
      }
    }
  }
  return retVal;
}

/**************************************************************************************************
   Function name    : OHDSCanSlave_UpdateSyncOffset
   ------------------------------------------------------------------------------------------------
   Description      : Update the time measured between RxIndication of SYNC message and evaluation
                      of FUP message based on the local hardware timer 
   ------------------------------------------------------------------------------------------------
   Called by        : OHDSCanSlave_MainFunction, OHDSCanSlave_HandleFUP
   ------------------------------------------------------------------------------------------------
   Parameter        : -
   ------------------------------------------------------------------------------------------------
   Returncode       : -
   ------------------------------------------------------------------------------------------------
   Misc             : -
**************************************************************************************************/
STATIC FUNC(void, OHDS_CODE) OHDSCanSlave_UpdateSyncOffset( void )
{
  VAR(uint32, AUTOMATIC) timerValue;
  VAR(uint32, AUTOMATIC) deltaTNS; /* Delta T in ns */

  OHDSCanSlave_EnterCritical(OHDSCANSLAVE_EXCLUSIVE_AREA_0);

  timerValue = OHDSCanSlave_GetTimerValue(); /* ISS023 */
  if(timerValue < OHDSCanSlave_Timer_LastSync)
  { /* overflow detected */
    deltaTNS = OHDSCANSLAVE_TIMER_MAX - OHDSCanSlave_Timer_LastSync;
    /* +1 because at OHDSCANSLAVE_TIMER_MAX to 0 also counts 1 */
    deltaTNS += timerValue + 1u; 
  }
  else
  { /* no overflow occured */
    deltaTNS = timerValue - OHDSCanSlave_Timer_LastSync;
  }
  /* now deltaT contains the delta between two consequtive update calls in ticks.
     Next calculate the delta in ns */
  deltaTNS *= OHDSCANSLAVE_TIMER_NS_PER_TICK;

  /* Overflow check: Time between SYNC and FUP can be a maximum of 2 s*/
  if( (OHDSCANSLAVE_MAX_INTERSYNCFUP_TIME - deltaTNS) >= OHDSCanSlave_Timer_SyncOffset )
  { /* Additional time fits into offset buffer */
    OHDSCanSlave_Timer_SyncOffset += deltaTNS;
  }
  else
  { /* Overflow: Stop waiting for SYNC message */
    OHDSCanSlave_Timer_SyncOffset = 0u;
    OHDSCanSlave_State = OHDSCANSLAVE_STATE_INITIALIZED;
  }
  /* Remember current timer value for next update */
  OHDSCanSlave_Timer_LastSync = timerValue;

  OHDSCanSlave_LeaveCritical(OHDSCANSLAVE_EXCLUSIVE_AREA_0);
}

/**************************************************************************************************
   Function name    : OHDSCanSlave_UpdateOperatingHoursCounter
   ------------------------------------------------------------------------------------------------
   Description      : Update the operating hours based on the local hardware timer if necessary. 
                      An update will be performed either if overflow of the hardware counter is 
                      detected or at least after 4 seconds.

                      It also returns the extrapolated OH counter if the parameters are not null
   ------------------------------------------------------------------------------------------------
   Called by        : OHDSCanSlave
   ------------------------------------------------------------------------------------------------
   Parameter        : valueLow: The lower 4 bytes of the extrapolated OH counter
                      valueMsb: The high byte of the extraplolated OH counter
                      microSeconds: Additional offset to the OH counter in microseconds
                      status: The internal status byte
   ------------------------------------------------------------------------------------------------
   Returncode       : -
   ------------------------------------------------------------------------------------------------
   Misc             : -
**************************************************************************************************/
STATIC FUNC(void, OHDS_CODE) OHDSCanSlave_UpdateOperatingHoursCounter( P2VAR(uint32, AUTOMATIC, OHDS_APPL_VAR) valueLow, 
                                                                       P2VAR(uint8, AUTOMATIC, OHDS_APPL_VAR) valueMsb,
                                                                       P2VAR(uint32, AUTOMATIC, OHDS_APPL_VAR) microSeconds,
                                                                       P2VAR(uint8, AUTOMATIC, OHDS_APPL_VAR) status )
{
  VAR(boolean, AUTOMATIC) performUpdate = FALSE;
  VAR(uint32, AUTOMATIC) timerValue;
  /* PRQA S 3197 3 */ /* Initializer is used for better maintainability  */
  VAR(uint32, AUTOMATIC) tmpOHCounterLow = 0u;
  VAR(uint8, AUTOMATIC) tmpOHCounterHigh = 0u;
  VAR(uint32, AUTOMATIC) tmpNanoSeconds = 0u;

  OHDSCanSlave_EnterCritical(OHDSCANSLAVE_EXCLUSIVE_AREA_0);  

  /* Fetch the current hardware timer value */
  timerValue = OHDSCanSlave_GetTimerValue(); /* ISS023 */

  if( timerValue < OHDSCanSlave_Timer_LastUpdateCall  )
  { /* Detected a timer overflow */
    tmpNanoSeconds = OHDSCANSLAVE_TIMER_MAX - OHDSCanSlave_Timer_LastUpdate;
    /* +1 because at OHDSCANSLAVE_TIMER_MAX to 0 also counts 1 */
    tmpNanoSeconds += timerValue + 1u;
    
    performUpdate = TRUE;
  }
  else
  { /* No overflow: straight calculation of difference */
    tmpNanoSeconds = timerValue - OHDSCanSlave_Timer_LastUpdate;
  }

  /* Store time of this call */
  OHDSCanSlave_Timer_LastUpdateCall = timerValue;

  /* To prevent an overflow of ns counter we do a artificial update after 4 seconds */
  if( tmpNanoSeconds >= OHDSCANSLAVE_MAXUPDATE_OFFSET )
  {
    performUpdate = TRUE;
  }

  /* 1. Calculation of extrapolated time stamp */
  if( (performUpdate == TRUE) || (valueLow != NULL_PTR) )
  { /* The current value of the OH shall be calculated */
    /* now deltaT contains the delta between two consecutive update calls in ticks.
     Next calculate the delta in ns */
    tmpNanoSeconds *= OHDSCANSLAVE_TIMER_NS_PER_TICK;
    /* add the aggregated error from last update steps */
    tmpNanoSeconds += OHDSCanSlave_Timer_UpdateError;
    /* calculate delta T in ms*/
    tmpOHCounterLow = tmpNanoSeconds / 1000000u;
    /* store the remaining error in ns */
    tmpNanoSeconds = tmpNanoSeconds % 1000000u;
    
    /* Now update the actual operating hours counter */
    if( (OHDSCANSLAVE_MAXUINT32 - tmpOHCounterLow) >= OHDSCanSlave_OperatingHours_Low )
    { /* there will be no overflow while adding.*/
      tmpOHCounterLow += OHDSCanSlave_OperatingHours_Low;
      tmpOHCounterHigh = OHDSCanSlave_OperatingHours_High;
    }
    else 
    { /* overflow in lower part of operating hours */
      if( OHDSCanSlave_OperatingHours_High == OHDSCANSLAVE_MAXUINT8 ) 
      { /* overflow in high byte */
        tmpOHCounterHigh = 0x00u;
      }
      else 
      { /* No overflow in high byte. Just increment high byte */
        tmpOHCounterHigh = OHDSCanSlave_OperatingHours_High + 1u; 
      }
      /* calculate the rest which is new lower part of the operating hours counter */
      tmpOHCounterLow = tmpOHCounterLow - ((OHDSCANSLAVE_MAXUINT32 - OHDSCanSlave_OperatingHours_Low) + 1u);
    }

    /* 2. Update internal state variables if necessary */
    if( performUpdate == TRUE )
    {
      /* store current timer value for next overflow detection */
      OHDSCanSlave_Timer_LastUpdate = timerValue;
  
      OHDSCanSlave_OperatingHours_Low = tmpOHCounterLow;
      OHDSCanSlave_OperatingHours_High = tmpOHCounterHigh;
      OHDSCanSlave_Timer_UpdateError = tmpNanoSeconds;
    }

    /* 3. hand the calculated values over to application if necessary */
    if( valueLow != NULL_PTR )
    {
      *valueLow = tmpOHCounterLow;
      /* Msb and microseconds do just make sense if lower bytes are requested */
      if( valueMsb != NULL_PTR )
      {
        *valueMsb = tmpOHCounterHigh;
      }
      if( microSeconds != NULL_PTR )
      {
        *microSeconds = tmpNanoSeconds / 1000u;
      }
      if( status != NULL_PTR )
      {
        *status = OHDSCanSlave_StatusByte;
      }
    }
  }
  OHDSCanSlave_LeaveCritical(OHDSCANSLAVE_EXCLUSIVE_AREA_0);
}

/**************************************************************************************************
   Function name    : OHDSCanSlave_GetOperatingHoursUint16
   ------------------------------------------------------------------------------------------------
   Description      : Returns the 16 lower bits of the current operating hours counter
                      (resolution: 1ms)
   ------------------------------------------------------------------------------------------------
   Called by        : SAR
   ------------------------------------------------------------------------------------------------
   Parameter        : value: will contain the actual operating hours counter value if function
                             return E_OK
                      status: status bits
                              0: SYNC bit
                              1: SYNC lost bit
                              2: CDD implemented
                              3: SGW
                              4: USB
                              5: TSZ
                              6: TD
                              7: RP
   ------------------------------------------------------------------------------------------------
   Returncode       : E_OK: If everything worked well. E_NOT_OK: There was any error.
   ------------------------------------------------------------------------------------------------
   Misc             : -
**************************************************************************************************/
FUNC(Std_ReturnType, OHDS_CODE) OHDSCanSlave_GetOperatingHoursUint16( P2VAR(uint16, AUTOMATIC, OHDS_APPL_VAR) value, 
                                                                      P2VAR(uint8, AUTOMATIC, OHDS_APPL_VAR) status )
{
  VAR(Std_ReturnType, AUTOMATIC) retValue = E_OK;

  if( OHDSCanSlave_State == OHDSCANSLAVE_STATE_UNINITIALIZED )
  { /* CDD is not initialized */
    retValue = E_NOT_OK;
    OHDSCanSlave_ReportError(OHDSCANSLAVE_GETOHUINT16_SID, OHDSCANSLAVE_E_UNINIT);
    /* Return SNA */
    if(value != NULL_PTR )
    { /* if pointer is NULL_PTR no operating hours value is returned */
      *value = OHDSCANSLAVE_OPERATINGHOURS_UINT16_SNA;
    }
    if(status != NULL_PTR)
    { /* if pointer is NULL_PTR no status byte is returned */
      *status  = OHDSCANSLAVE_STATUS_SNA;
    }
  }
  else
  {
    
    if(value != NULL_PTR)
    { /* if pointer is NULL_PTR no operating hours value is returned */
      VAR(uint32, AUTOMATIC) tmpOHLow;
      OHDSCanSlave_UpdateOperatingHoursCounter(&tmpOHLow, NULL_PTR, NULL_PTR, status);
      /* return 2 lower bytes */
      *value =  (uint16)tmpOHLow;
    }
  }

  return retValue;
}


/**************************************************************************************************
   Function name    : OHDSCanSlave_GetOperatingHours
   ------------------------------------------------------------------------------------------------
   Description      : Returns the current operating hours counter (resolution: milliseconds)
   ------------------------------------------------------------------------------------------------
   Called by        : SAR
   ------------------------------------------------------------------------------------------------
   Parameter        : value: will contain the lower 4 bytes of the actual operating hours counter
                             value if function return E_OK
                      valueMsb: will contain the 5th byte of the actual operating hours counter.
                      status: status bits
                              0: SYNC bit
                              1: SYNC lost bit
                              2: CDD implemented
                              3: SGW
                              4: USB
                              5: TSZ
                              6: TD
                              7: RP
   ------------------------------------------------------------------------------------------------
   Returncode       : E_OK: If everything worked well. E_NOT_OK: There was any error.
   ------------------------------------------------------------------------------------------------
   Misc             : -
**************************************************************************************************/
FUNC(Std_ReturnType, OHDS_CODE) OHDSCanSlave_GetOperatingHours( P2VAR(uint32, AUTOMATIC, OHDS_APPL_VAR) value, 
                                                                P2VAR(uint8, AUTOMATIC, OHDS_APPL_VAR) valueMsb, 
                                                                P2VAR(uint8, AUTOMATIC, OHDS_APPL_VAR) status )
{
  VAR(Std_ReturnType, AUTOMATIC) retValue = E_OK;

  if( OHDSCanSlave_State == OHDSCANSLAVE_STATE_UNINITIALIZED )
  { /* CDD is not initialized */
    retValue = E_NOT_OK;
    OHDSCanSlave_ReportError(OHDSCANSLAVE_GETOH_SID, OHDSCANSLAVE_E_UNINIT);
    /* Return SNA */
    if((value != NULL_PTR) && (valueMsb != NULL_PTR))
    { /* if pointer is NULL_PTR no operating hours value is returned */
      *value = OHDSCANSLAVE_OPERATINGHOURS_SNA;
      *valueMsb = OHDSCANSLAVE_OPERATINGHOURS_MSB_SNA;
    }
    if(status != NULL_PTR)
    { /* if pointer is NULL_PTR no status byte is returned */
      *status  = OHDSCANSLAVE_STATUS_SNA;
    }
  }
  else
  {
    if((value != NULL_PTR) && (valueMsb != NULL_PTR))
    { /* if one of the two pointers is a NULL_PTR no operating hours value is returned */
      OHDSCanSlave_UpdateOperatingHoursCounter(value, valueMsb, NULL_PTR, status );
    }
  }

  return retValue;
}

/**************************************************************************************************
   Function name    : OHDS_Dem_GetOperatingHours
   ------------------------------------------------------------------------------------------------
   Description      : Returns the current operating hours counter for the DEM module to store it in
                      DTC environment data (resolution: 1ms)
   ------------------------------------------------------------------------------------------------
   Called by        : SAR
   ------------------------------------------------------------------------------------------------
   Parameter        : value: will contain the lower 4 bytes of the actual operating hours counter
                             value if function return E_OK
                      status: status bits
                              0: SYNC bit
                              1: SYNC lost bit
                              2: CDD implemented
                              3: SGW
                              4: USB
                              5: TSZ
                              6: TD
                              7: RP
   ------------------------------------------------------------------------------------------------
   Returncode       : E_OK: If everything worked well. E_NOT_OK: There was any error.
   ------------------------------------------------------------------------------------------------
   Misc             : -
**************************************************************************************************/
FUNC(Std_ReturnType, OHDS_CODE) OHDS_Dem_GetOperatingHours( P2VAR(uint32, AUTOMATIC, OHDS_APPL_VAR) value, 
                                                            P2VAR(uint8, AUTOMATIC, OHDS_APPL_VAR) status )
{
  VAR(Std_ReturnType, AUTOMATIC) retValue = E_OK;

  if( OHDSCanSlave_State == OHDSCANSLAVE_STATE_UNINITIALIZED )
  { /* CDD is not initialized */
    retValue = E_NOT_OK;
    OHDSCanSlave_ReportError(OHDSCANSLAVE_DEM_GETOH_SID, OHDSCANSLAVE_E_UNINIT);
    /* Return SNA*/
    if(value != NULL_PTR)
    { /* if pointer is NULL_PTR no operating hours value is returned */
      *value = OHDSCANSLAVE_OPERATINGHOURS_SNA;
    }
    if(status != NULL_PTR)
    { /* if pointer is NULL_PTR no status byte is returned */
      *status  = OHDSCANSLAVE_STATUS_SNA;
    }
  }
  else
  {
    
    if(value != NULL_PTR)
    { /* if pointer is NULL_PTR no operating hours value is returned */
      OHDSCanSlave_UpdateOperatingHoursCounter(value, NULL_PTR, NULL_PTR, status);
    }  
  }

  return retValue;
}

#if (OHDSCANSLAVE_VERSION_INFO_API == STD_ON)
/**************************************************************************************************
   Function name    : OHDS_Dem_GetVersionInfo
   ------------------------------------------------------------------------------------------------
   Description      : This function returns module information in a standardized format for the Dem
                      module
   ------------------------------------------------------------------------------------------------
   Called by        : Dem
   ------------------------------------------------------------------------------------------------
   Parameter        : versionInfo: Std_VersionInfoType*
   ------------------------------------------------------------------------------------------------
   Returncode       : -
   ------------------------------------------------------------------------------------------------
   Misc             : -
**************************************************************************************************/
FUNC(void, OHDS_CODE) OHDS_Dem_GetVersionInfo( P2VAR(Std_VersionInfoType, AUTOMATIC, OHDS_APPL_VAR) versionInfo )
{
  OHDSCanSlave_GetVersionInfo(versionInfo);
}
#endif /* OHDSCANSLAVE_VERSION_INFO_API */

/**************************************************************************************************
   Function name    : OHDSCanSlave_Multiply
   ------------------------------------------------------------------------------------------------
   Description      : Multiply two unsigned numbers and catch the overflow
   ------------------------------------------------------------------------------------------------
   Called by        : OHDSCanSlave
   ------------------------------------------------------------------------------------------------
   Parameter        : *resultLow:  low 4 bytes of result,
                      *resultHigh: high 1 byte of result,
                      a: first factor of multiplication,
                      b: second factor of multiplication,
   ------------------------------------------------------------------------------------------------
   Returncode       : -
   ------------------------------------------------------------------------------------------------
   Misc             : -
**************************************************************************************************/
STATIC FUNC(void, OHDS_CODE) OHDSCanSlave_Multiply( P2VAR(uint32, AUTOMATIC, OHDS_APPL_VAR) resultLow, 
                                                    P2VAR(uint8, AUTOMATIC, OHDS_APPL_VAR) resultHigh, 
                                                    uint32 a, uint16 b)
{
  VAR(uint32, AUTOMATIC) alb, ahb, tmpResult;

  /* transform multiplication into factorisation:
     result = (a*b)
            = (aHigh<<16 + aLow)*b
            = aHigh*b<<16 + aLow*b
            = ahb<<16 + alb
   */

  /* cannot overflow since 32bit is sufficient for 16bit*16bit multiplication */
  alb = (a & 0xFFFFu) * b; 
  ahb = (a >> 16u) * b;

  /*  ahb:      aHigh*b       (32bit)
      alb:      aLow*b        (32bit)
      albLow:   LowWord(alb)  (16bit)
      albHigh:  HighWord(alb) (16bit)
   
      resultLow = ahb << 16 + albHigh << 16 + albLow
                = (ahb + albHigh)<<16 + albLow
                = LowWord(tmpResult)<<16 + albLow
   
      resultHigh = HighWord(tmpResult)
                 = tmpResult>>16
  */
  tmpResult = ahb + (alb >> 16u);

  *resultHigh = (uint8)(tmpResult >> 16u);
  *resultLow  = ((tmpResult & 0xFFFFu) << 16u) + (alb & 0xFFFFu);
}

#define OHDS_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* module specific MISRA deviations:

 MD_OHDSCANSLAVE_19.7_FUNCTION_LIKE_MACRO
     Reason:      Function like makro is used because it is faster then function call 
     Risk:        -
     Prevention:  -
 
 MD_OHDSCANSLAVE_8.10_EXTERNAL_LINKAGE
     Reason:      Variable has external linkage because it is intended to be read via XCP
     Risk:        -
     Prevention:  -
 
 MD_OHDSCANSLAVE_8.8_EXTERNAL_LINKAGE
     Reason:      Variable has external linkage because it is intended to be read via XCP. No declaration needed.
     Risk:        -
     Prevention:  -
 
 MD_OHDSCANSLAVE_8.7_STATIC_ACCESS
     Reason:      Constant is defined static and not in function scope because of code cleanage.
     Risk:        -
     Prevention:  -

*/
