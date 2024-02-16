/* -----------------------------------------------------------------------------
  Filename:    Dem_Lcfg.h
  Description: Toolversion: 19.00.32.01.50.01.22.00.00.00
               
               Serial Number: CBD1500122
               Customer Info: Huf Electronics Bretten GmbH
                              Package: MSR Daimler SLP10
                              Micro: R7F7010133AFP
                              Compiler: Green Hills 6.1.4
               
               
               Generator Fwk   : GENy 
               Generator Module: Dem
               
               Configuration   : C:\_TSS\DAG\MFA2\Target\Config\ECUC\HufTPMS_G6_F1L.ecuc.vdsxml
               
               ECU: 
                       TargetSystem: Hw_Rh850Cpu
                       Compiler:     GreenHills
                       Derivates:    F1L
               
               Channel "HMI":
                       Databasefile: 
                       Bussystem:    CAN
                       Manufacturer: DaimlerChrysler
                       Node:         CanStateManagerConfiguration

 ----------------------------------------------------------------------------- */
/* -----------------------------------------------------------------------------
  C O P Y R I G H T
 -------------------------------------------------------------------------------
  Copyright (c) 2001-2015 by Vector Informatik GmbH. All rights reserved.
 
  This software is copyright protected and proprietary to Vector Informatik 
  GmbH.
  
  Vector Informatik GmbH grants to you only those rights as set out in the 
  license conditions.
  
  All other rights remain with Vector Informatik GmbH.
 -------------------------------------------------------------------------------
 ----------------------------------------------------------------------------- */

#if !defined(DEM_LCFG_H)
#define DEM_LCFG_H

/* -----------------------------------------------------------------------------
    &&&~ Dem Parameters
 ----------------------------------------------------------------------------- */

/* START of Checksum include for
  - Diag_AsrDemLinktimeCRC */
#define DEM_MAX_NUMBER_EVENT_ENTRY           10
#define DEM_NUMBER_OF_VIEWS                  0
#define DEM_NUMBER_OF_EVENTS                 68
#define DEM_STATUS_AVAILABILITY_MASK         0x39u
#define DEM_NUMBER_OF_OPERATION_CYCLES       4
#define DEM_NUMBER_OF_INDICATORS             3
#define DEM_MAX_EXTDATA_RECORD_SIZE          24
#define DEM_MAX_SNAPSHOT_RECORD_SIZE         1
#define DEM_BSW_ERROR_BUFFER_SIZE            4
#define DEM_ADD_ERROR_BUFFER_SIZE            1
#define DEM_SNAPSHOTS_PER_DTC                0
#define DEM_FIRST_SNAPSHOT_TO_OVERWRITE      0
#define DEM_PRESTORE_FF_BUFFER_SIZE          1
#define DEM_MAX_NUMBER_EVENT_ENTRY_MIR       10
#define DEM_MAX_EXTDATA_MIR_RECORD_SIZE      15
/* END of Checksum include for
  - Diag_AsrDemLinktimeCRC */


/* -----------------------------------------------------------------------------
    &&&~ Dem_Indicators
 ----------------------------------------------------------------------------- */

/* START of Checksum exclude for
  - Diag_AsrDemLinktimeCRC */
#define Dem_DEM_IND_SC8_RELEVANT             0
#define Dem_DEM_IND_MALFLAMP                 1
#define Dem_DEM_IND_ECUFAILURE               2
/* END of Checksum exclude for
  - Diag_AsrDemLinktimeCRC */


/* -----------------------------------------------------------------------------
    &&&~ Dem configuration type definitions
 ----------------------------------------------------------------------------- */

/* START of Checksum include for
  - Diag_AsrDemLinktimeCRC */
typedef P2VAR(uint8, TYPEDEF, DEM_APPL_DATA) Dem_ApplBufferPtrType; /* PRQA S 0850 */ /* MD_MSR_19.8 */
typedef P2FUNC(Std_ReturnType, DEM_APPL_CODE, Dem_GetCurrentOdometerFPtrType) (P2VAR(uint32, AUTOMATIC, DEM_VAR_NOINIT) /* Odometer */); /* PRQA S 0850 */ /* MD_MSR_19.8 */
typedef P2FUNC(Std_ReturnType, DEM_APPL_CODE, Dem_GetExternalTesterStatusFPtrType) (P2VAR(boolean, AUTOMATIC, DEM_VAR_NOINIT) /* testerPresent */); /* PRQA S 0850 */ /* MD_MSR_19.8 */
typedef P2FUNC(Std_ReturnType, DEM_APPL_CODE, Dem_OnControlDTCFPtrType) (boolean /* newStatus */); /* PRQA S 0850 */ /* MD_MSR_19.8 */
typedef VAR(uint8, TYPEDEF) Dem_Mem_PrimaryIndexType; /* PRQA S 0850 */ /* MD_MSR_19.8 */
typedef VAR(uint8, TYPEDEF) Dem_Mem_MirrorIndexType; /* PRQA S 0850 */ /* MD_MSR_19.8 */
typedef struct Dem_NvAdminDataTypeTag
{
  uint32 activeVersion;
  uint16 cycleCounter[DEM_NUMBER_OF_OPERATION_CYCLES];
} Dem_NvAdminDataType;
typedef struct Dem_NvStatusDataTypeTag
{
  uint8 statusTestFailed[(DEM_NUMBER_OF_EVENTS / 8) + 1];
  uint8 statusTestNotCompletedSLC[(DEM_NUMBER_OF_EVENTS / 8) + 1];
  uint8 statusTestFailedSLC[(DEM_NUMBER_OF_EVENTS / 8) + 1];
  Dem_EventIdType firstFailedEvent;
  Dem_EventIdType firstConfirmedEvent;
  Dem_EventIdType mostRecentFailedEvent;
  Dem_EventIdType mostRecentConfirmedEvent;
} Dem_NvStatusDataType;
typedef VAR(uint8, TYPEDEF) Dem_NvPrimaryEntryType[2 + 4 + 2 + DEM_MAX_EXTDATA_RECORD_SIZE + (DEM_SNAPSHOTS_PER_DTC*DEM_MAX_SNAPSHOT_RECORD_SIZE) + 1];
typedef struct Dem_NvMirrorMemoryTypeTag
{
  Dem_EventIdType eventId[DEM_MAX_NUMBER_EVENT_ENTRY_MIR];
  uint8 eventData[DEM_MAX_NUMBER_EVENT_ENTRY_MIR][1+DEM_MAX_EXTDATA_MIR_RECORD_SIZE+1];
  uint16 hirOdometer;
  uint8 hirReadCount;
  Dem_Mem_MirrorIndexType writeIndex;
} Dem_NvMirrorMemoryType;
typedef struct Dem_DemConfigurationTypeTag
{
  uint8 DTCTranslationFormat;
  Dem_GetCurrentOdometerFPtrType GetCurrentOdometerFPtr;
  Dem_GetExternalTesterStatusFPtrType GetExternalTesterStatusFPtr;
  Dem_OnControlDTCFPtrType OnControlDTCFPtr;
} Dem_DemConfigurationType;
typedef struct Dem_DIDLookupTableTypeTag
{
  uint16 did;
  Dem_GetDataValueByDataIdentifierType pFunc;
} Dem_DIDLookupTableType;
typedef VAR(uint8, TYPEDEF) Dem_DataRecordSizeType; /* PRQA S 0850 */ /* MD_MSR_19.8 */
/* END of Checksum include for
  - Diag_AsrDemLinktimeCRC */


/* -----------------------------------------------------------------------------
    &&&~ Global Data Prototypes
 ----------------------------------------------------------------------------- */

/* START of Checksum include for
  - Diag_AsrDemLinktimeCRC */
/* -----------------------------------------------------------------------------
    &&&~ RAM buffers of NVRAM stored data
 ----------------------------------------------------------------------------- */

#define DEM_START_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"

extern VAR(Dem_NvAdminDataType, DEM_APPL_DATA) Dem_Cfg_NvAdminData; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern VAR(Dem_NvStatusDataType, DEM_APPL_DATA) Dem_Cfg_NvEventStatusData; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern VAR(Dem_NvPrimaryEntryType, DEM_APPL_DATA) Dem_Cfg_NvPrimaryEntry_1; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern VAR(Dem_NvPrimaryEntryType, DEM_APPL_DATA) Dem_Cfg_NvPrimaryEntry_2; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern VAR(Dem_NvPrimaryEntryType, DEM_APPL_DATA) Dem_Cfg_NvPrimaryEntry_3; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern VAR(Dem_NvPrimaryEntryType, DEM_APPL_DATA) Dem_Cfg_NvPrimaryEntry_4; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern VAR(Dem_NvPrimaryEntryType, DEM_APPL_DATA) Dem_Cfg_NvPrimaryEntry_5; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern VAR(Dem_NvPrimaryEntryType, DEM_APPL_DATA) Dem_Cfg_NvPrimaryEntry_6; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern VAR(Dem_NvPrimaryEntryType, DEM_APPL_DATA) Dem_Cfg_NvPrimaryEntry_7; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern VAR(Dem_NvPrimaryEntryType, DEM_APPL_DATA) Dem_Cfg_NvPrimaryEntry_8; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern VAR(Dem_NvPrimaryEntryType, DEM_APPL_DATA) Dem_Cfg_NvPrimaryEntry_9; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern VAR(Dem_NvPrimaryEntryType, DEM_APPL_DATA) Dem_Cfg_NvPrimaryEntry_10; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern VAR(Dem_NvMirrorMemoryType, DEM_APPL_DATA) Dem_Cfg_NvMirrorMemory; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern VAR(uint8, DEM_APPL_DATA) Dem_PreFFBuffer[DEM_PRESTORE_FF_BUFFER_SIZE]; /* PRQA S 0850 */ /* MD_MSR_19.8 */

#define DEM_STOP_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"




/* -----------------------------------------------------------------------------
    &&&~ RAM buffers for internal data
 ----------------------------------------------------------------------------- */

#define DEM_START_SEC_VAR_FAST_8BIT
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"

extern VAR(uint8, DEM_VAR_NOINIT_FAST) Dem_StatusTestFailedTOC[]; /* PRQA S 0850, 3684 */ /* MD_MSR_19.8, MD_DEM_8.12 */
extern VAR(uint8, DEM_VAR_NOINIT_FAST) Dem_StatusConfirmedDTC[]; /* PRQA S 0850, 3684 */ /* MD_MSR_19.8, MD_DEM_8.12 */
extern VAR(uint8, DEM_VAR_NOINIT_FAST) Dem_StatusTestNotCompletedTOC[]; /* PRQA S 0850, 3684 */ /* MD_MSR_19.8, MD_DEM_8.12 */
extern VAR(Dem_DtcInternalStatusType, DEM_VAR_NOINIT_FAST) Dem_DtcInternalStatus[]; /* PRQA S 0850, 3684 */ /* MD_MSR_19.8, MD_DEM_8.12 */
extern VAR(sint8, DEM_VAR_NOINIT_FAST) Dem_DtcFaultDetectionCounter[]; /* PRQA S 0850, 3684 */ /* MD_MSR_19.8, MD_DEM_8.12 */
extern VAR(uint8, DEM_VAR_NOINIT_FAST) Dem_Mem_PrimaryEntryStatus[]; /* PRQA S 0850, 3684 */ /* MD_MSR_19.8, MD_DEM_8.12 */
extern VAR(Dem_Mem_PrimaryIndexType, DEM_VAR_NOINIT_FAST) Dem_Mem_PrimaryChronology[]; /* PRQA S 0850, 3684 */ /* MD_MSR_19.8, MD_DEM_8.12 */

#define DEM_STOP_SEC_VAR_FAST_8BIT
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"


#define DEM_START_SEC_VAR_NOINIT_8BIT
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"

extern VAR(Dem_OperationCycleStateType, DEM_VAR_NOINIT) Dem_OperationCycleState[]; /* PRQA S 0850, 3684 */ /* MD_MSR_19.8, MD_DEM_8.12 */
#define DEM_STOP_SEC_VAR_NOINIT_8BIT
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"


#define DEM_START_SEC_VAR_NOINIT_16BIT
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"

extern VAR(Dem_EventIdType, DEM_VAR_NOINIT) Dem_IndicatorCounter[][2]; /* PRQA S 0850, 3684 */ /* MD_MSR_19.8, MD_DEM_8.12 */
#define DEM_STOP_SEC_VAR_NOINIT_16BIT
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"



#define DEM_START_SEC_VAR_NOINIT_UNSPECIFIED
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"

extern VAR(uint32, DEM_VAR_NOINIT) Dem_EnableConditionState; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern VAR(Dem_AQElementType, DEM_VAR_NOINIT) Dem_ActionQueue[]; /* PRQA S 0850, 3684 */ /* MD_MSR_19.8, MD_DEM_8.12 */
extern VAR(Dem_TimeBasedDebounceTimerType, DEM_VAR_NOINIT) Dem_DebounceTimer; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern VAR(Dem_TimeBasedDebounceTimerType, DEM_VAR_NOINIT) Dem_DebounceTimerSlots[]; /* PRQA S 0850, 3684 */ /* MD_MSR_19.8, MD_DEM_8.12 */

#define DEM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"




/* -----------------------------------------------------------------------------
    &&&~ Precompile/Linktime specific config data
 ----------------------------------------------------------------------------- */

#define DEM_START_SEC_CONST_LCFG
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"

extern CONST(Dem_DemConfigurationType, DEM_CONST) Dem_DemConfiguration; /* PRQA S 0850 */ /* MD_MSR_19.8 */

extern CONST(Dem_NvMBlockIdType, DEM_CONST) Dem_Cfg_NvAdminBlock; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern CONST(Dem_NvMBlockIdType, DEM_CONST) Dem_Cfg_NvEventStatusBlock; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern CONST(Dem_NvMBlockIdType, DEM_CONST) Dem_Cfg_NvPrimaryBlocks[]; /* PRQA S 0850, 3684 */ /* MD_MSR_19.8, MD_DEM_8.12 */
extern CONST(Dem_NvMBlockIdType, DEM_CONST) Dem_Cfg_NvMirrorBlocks[]; /* PRQA S 0850, 3684 */ /* MD_MSR_19.8, MD_DEM_8.12 */

extern CONST(Dem_NvPrimaryEntryType, DEM_CONST) Dem_Cfg_NvPrimaryEntry_Zero; /* PRQA S 0850 */ /* MD_MSR_19.8 */

extern CONST(Dem_DTCGroupMappingType, DEM_CONST) Dem_DTCGroupTable[]; /* PRQA S 0850, 3684 */ /* MD_MSR_19.8, MD_DEM_8.12 */
extern CONST(uint8, DEM_CONST) Dem_LinkTimeProperty[]; /* PRQA S 0850, 3684 */ /* MD_MSR_19.8, MD_DEM_8.12 */
extern CONST(uint8, DEM_CONST) Dem_InitMonitorIndexTable[]; /* PRQA S 0850, 3684 */ /* MD_MSR_19.8, MD_DEM_8.12 */
extern CONST(Dem_InitMonitorFPtrType, DEM_CONST) Dem_InitMonitorFPtrTable[]; /* PRQA S 0850, 3684 */ /* MD_MSR_19.8, MD_DEM_8.12 */
extern CONST(Dem_TriggerDTCFunctionType, DEM_CONST) Dem_TriggerDTCFunctionTable[]; /* PRQA S 0850, 3684 */ /* MD_MSR_19.8, MD_DEM_8.12 */
extern CONST(uint8, DEM_CONST) Dem_TriggerDTCIndexTable[]; /* PRQA S 0850, 3684 */ /* MD_MSR_19.8, MD_DEM_8.12 */
extern CONST(uint8, DEM_CONST) Dem_TriggerDTCCountTable[]; /* PRQA S 0850, 3684 */ /* MD_MSR_19.8, MD_DEM_8.12 */
extern CONST(Dem_TriggerFunctionType, DEM_CONST) Dem_TriggerFunctionTable[]; /* PRQA S 0850, 3684 */ /* MD_MSR_19.8, MD_DEM_8.12 */
extern CONST(uint8, DEM_CONST) Dem_IndicatorCountTable[]; /* PRQA S 0850, 3684 */ /* MD_MSR_19.8, MD_DEM_8.12 */
extern CONST(uint8, DEM_CONST) Dem_IndicatorIndexTable[]; /* PRQA S 0850, 3684 */ /* MD_MSR_19.8, MD_DEM_8.12 */
extern CONST(Dem_IndicatorIdType, DEM_CONST) Dem_IndicatorIdTable[]; /* PRQA S 0850, 3684 */ /* MD_MSR_19.8, MD_DEM_8.12 */
extern CONST(Dem_IndicatorStatusType, DEM_CONST) Dem_IndicatorStatusTable[]; /* PRQA S 0850, 3684 */ /* MD_MSR_19.8, MD_DEM_8.12 */
extern CONST(Dem_DTCGroupKindType, DEM_CONST) Dem_EventGroupTable[]; /* PRQA S 0850, 3684 */ /* MD_MSR_19.8, MD_DEM_8.12 */
extern CONST(Dem_DIDLookupTableType, DEM_CONST) Dem_DIDLookupTable[]; /* PRQA S 0850, 3684 */ /* MD_MSR_19.8, MD_DEM_8.12 */
extern CONST(Dem_GetExtDataRecordFPtrType, DEM_CONST) Dem_GetExtDataRecordListTable[]; /* PRQA S 0850, 3684 */ /* MD_MSR_19.8, MD_DEM_8.12 */


extern CONST(uint8, DEM_CONST) Dem_StatusAvailabilityMask; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern CONST(uint16, DEM_CONST) Dem_MaxSizeOfSnapshotRecord; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern CONST(uint16, DEM_CONST) Dem_MaxSizeOfExtdataRecord; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern CONST(uint16, DEM_CONST) Dem_NumberOfOperationCycles; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern CONST(uint16, DEM_CONST) Dem_NumberOfIndicators; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern CONST(Dem_EventIdType, DEM_CONST) Dem_Cfg_MaxEventId; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern CONST(Dem_Mem_PrimaryIndexType, DEM_CONST) Dem_Cfg_NumPrimaryEntries; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern CONST(Dem_Mem_MirrorIndexType, DEM_CONST) Dem_Cfg_NumMirrorEntries; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern CONST(uint16, DEM_CONST) Dem_Cfg_MirrorEntrySize; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern CONST(uint16, DEM_CONST) Dem_Cfg_MirrorUserDataSize; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern CONST(uint16, DEM_CONST) Dem_SizeofPreFFBuffer; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern CONST(uint8, DEM_CONST) Dem_SnapshotsPerDTC; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern CONST(uint8, DEM_CONST) Dem_FirstOverwritableSnapshot; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern CONST(uint8, DEM_CONST) Dem_ReportErrorBufferSize; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern CONST(uint16, DEM_CONST) Dem_ActionQueueCount; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern CONST(uint8, DEM_CONST) Dem_DTCGroupMappingCount; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern CONST(uint8, DEM_CONST) Dem_SizeofEventIdType; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern CONST(uint16, DEM_CONST) Dem_NumberOfDebounceTimerSlots; /* PRQA S 0850 */ /* MD_MSR_19.8 */

extern CONSTP2VAR(uint32, DEM_CONST, DEM_APPL_DATA) Dem_Cfg_AdminActiveVersionPtr; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern CONSTP2VAR(uint16, DEM_CONST, DEM_APPL_DATA) Dem_Cfg_AdminCycleCounterPtr; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern CONSTP2VAR(uint8, DEM_CONST, DEM_VAR_NOINIT) Dem_Cfg_AdminCycleStatePtr; /* PRQA S 0850 */ /* MD_MSR_19.8 */

extern volatile CONSTP2VAR(uint8, DEM_CONST, DEM_APPL_DATA) Dem_StatusTestFailedPtr; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern volatile CONSTP2VAR(uint8, DEM_CONST, DEM_VAR_NOINIT_FAST) Dem_StatusTestFailedTOCPtr; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern volatile CONSTP2VAR(uint8, DEM_CONST, DEM_VAR_NOINIT_FAST) Dem_StatusConfirmedDTCPtr; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern volatile CONSTP2VAR(uint8, DEM_CONST, DEM_APPL_DATA) Dem_StatusTestNotCompletedSLCPtr; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern volatile CONSTP2VAR(uint8, DEM_CONST, DEM_APPL_DATA) Dem_StatusTestFailedSLCPtr; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern volatile CONSTP2VAR(uint8, DEM_CONST, DEM_VAR_NOINIT_FAST) Dem_StatusTestNotCompletedTOCPtr; /* PRQA S 0850 */ /* MD_MSR_19.8 */

extern CONSTP2VAR(sint8, DEM_CONST, DEM_VAR_NOINIT_FAST) Dem_FaultDetectionCounterPtr; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern CONSTP2VAR(Dem_EventIdType, DEM_CONST, DEM_APPL_DATA) Dem_FirstFailedEventIdPtr; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern CONSTP2VAR(Dem_EventIdType, DEM_CONST, DEM_APPL_DATA) Dem_FirstConfirmedEventIdPtr; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern CONSTP2VAR(Dem_EventIdType, DEM_CONST, DEM_APPL_DATA) Dem_MostRecentFailedEventIdPtr; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern CONSTP2VAR(Dem_EventIdType, DEM_CONST, DEM_APPL_DATA) Dem_MostRecentConfmdEventIdPtr; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern CONSTP2VAR(Dem_NvPrimaryEntryType, DEM_CONST, DEM_APPL_DATA) Dem_Cfg_PrimaryStackPtr[]; /* PRQA S 0850, 3684 */ /* MD_MSR_19.8, MD_DEM_8.12 */

extern CONSTP2VAR(Dem_EventIdType, DEM_CONST, DEM_APPL_DATA) Dem_Cfg_MirrorEventIdPtr; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern CONSTP2VAR(uint8, DEM_CONST, DEM_APPL_DATA) Dem_Cfg_MirrorDataPtr; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern CONSTP2VAR(Dem_Mem_MirrorIndexType, DEM_CONST, DEM_APPL_DATA) Dem_Cfg_MirrorWriteIndexPtr; /* PRQA S 0850 */ /* MD_MSR_19.8 */

extern CONSTP2VAR(uint16, DEM_CONST, DEM_APPL_DATA) Dem_HirOdometerPtr; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern CONSTP2VAR(uint8, DEM_CONST, DEM_APPL_DATA) Dem_HirReadCountPtr; /* PRQA S 0850 */ /* MD_MSR_19.8 */



#define DEM_STOP_SEC_CONST_LCFG
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"




/* END of Checksum include for
  - Diag_AsrDemLinktimeCRC */


/* -----------------------------------------------------------------------------
    &&&~ Global Function Prototypes
 ----------------------------------------------------------------------------- */

/* START of Checksum include for
  - Diag_AsrDemLinktimeCRC */
#define DEM_START_SEC_CODE
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"

/* -----------------------------------------------------------------------------
    &&&~ Access function to global configuration data
 ----------------------------------------------------------------------------- */

extern FUNC(Dem_EventIdType, DEM_CODE) Dem_Cfg_GetMaxEventId(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern FUNC(uint8, DEM_CODE) DemCfg_GetDTCTranslationFormat(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern FUNC(Dem_GetCurrentOdometerFPtrType, DEM_CODE) DemCfg_GetCurrentOdometerFPtr(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern FUNC(Dem_GetExternalTesterStatusFPtrType, DEM_CODE) DemCfg_GetExternalTesterStatusFPtr(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern FUNC(Dem_OnControlDTCFPtrType, DEM_CODE) DemCfg_GetOnControlDTCFPtr(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern FUNC(uint16, DEM_CODE) DemCfg_GetMaxCountOfOperationCycle(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern FUNC(uint8, DEM_CODE) DemCfg_GetCountOfSnapshotsPerDTC(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern FUNC(uint16, DEM_CODE) DemCfg_GetMaxSnapshotRecordSize(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern FUNC(uint8, DEM_CODE) DemCfg_Get1stOverwrtSnapshotIndex(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */
/* No longer used, kept for compatibility */
#define DemCfg_GetCountOfGlobalSsDIDs(EventId) 0
#define DemCfg_GetFirstGlobalSsRecord(EventId) 0
extern FUNC(uint16, DEM_CODE) DemCfg_GetMaxExtdataRecordSize(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern FUNC(Dem_Mem_PrimaryIndexType, DEM_CODE) Dem_Cfg_GetNumPrimaryEntries(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern FUNC(uint32, DEM_CODE) DemCfg_GetEnableConditionInitValue(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */


extern FUNC(Dem_DTCGroupKindType, DEM_CODE) Dem_MapGroupNumberToGroupKind(Dem_DTCType DTCGroupNumber); /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern FUNC(Dem_DTCType, DEM_CODE) DemCfg_GetDTCnumber(Dem_EventIdType EventId); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/* -----------------------------------------------------------------------------
    &&&~ Access functions to the event specific configurable data
 ----------------------------------------------------------------------------- */

extern FUNC(Dem_InitMonitorFPtrType, DEM_CODE) DemCfg_GetInitMonitorFPtr(Dem_EventIdType EventId); /* PRQA S 0850 */ /* MD_MSR_19.8 */
/* Map EventId to the first Index into the list of TriggerOnDTCStatusChanged callbacks. */
#define DemCfg_GetFirstTriggerOnDTC(EventId) (Dem_TriggerDTCIndexTable[Dem_LinkTimeProperty[EventId]])
/* Map EventId to the number of corresponding TriggerOnDTCStatusChanged callbacks. */
#define DemCfg_GetCountOfTriggerOnDTC(EventId) (Dem_TriggerDTCCountTable[Dem_LinkTimeProperty[EventId]])
/* Map EventId to the first Index into the list of TriggerOnEventStatusChanged callbacks. */
#define DemCfg_GetFirstTriggerOnEvent(EventId) 0
/* Map EventId to number of TriggerOnEventStatusChanged callbacks. */
#define DemCfg_GetCountOfTriggerOnEvent(EventId) 0
/* Map EventId to priority. */
#define DemCfg_GetEventPriority(EventId)     (Dem_EventPriorityTable[Dem_PostBuildProperty[EventId]])
/* Map EventId to severity. */
#define DemCfg_GetDTCSeverity(EventId)       0
/* Map EventId to its healing cycle. See Dem_Types.h for operation cycle IDs. */
#define DemCfg_GetAgingCycleId(EventId)      0
/* Map EventId to its operation cycle. See Dem_Types.h for healing cycle IDs. */
#define DemCfg_GetOperationCycleId(EventId)  (Dem_OperationCycleTable[Dem_PostBuildProperty[EventId]])
/* Maps EventId to <Number of Healing Cycles> - 1 */
#define DemCfg_GetNumberOfAgingCycles(EventId) (Dem_AgingCountTable[Dem_PostBuildProperty[EventId]])
/* Map EventId to relevant enable conditions. Set bit means enable condition must be active for the Event. */
#define DemCfg_GetEnableConditionMask(EventId) (Dem_EnableConditionTable[Dem_PostBuildProperty[EventId]])
/* Map EventId to the number of relevant indicators. */
#define DemCfg_GetCountOfIndicatorIds(EventId) (Dem_IndicatorCountTable[Dem_LinkTimeProperty[EventId]])
/* Map EventId to index in Dem_IndicatorIdTable and Dem_IndicatorStatusTable. */
#define DemCfg_GetIndicatorIndex(EventId)    (Dem_IndicatorIndexTable[Dem_LinkTimeProperty[EventId]])
/* Map IndIdIdx to IndicatorId. */
#define DemCfg_GetIndicatorId(IndIdIdx)      (Dem_IndicatorIdTable[IndIdIdx])
/* Map IndIdIdx to indicator status. */
#define DemCfg_GetIndicatorStatusType(IndIdIdx) (Dem_IndicatorStatusTable[IndIdIdx])
extern FUNC(Dem_EventIdPtrType, DEM_CODE) DemCfg_GetIndicatorCounterPtr(Dem_IndicatorIdType IndicatorId, Dem_IndicatorStatusType IndicatorBehavior); /* PRQA S 0850 */ /* MD_MSR_19.8 */
/* Map EventId to a ViewID. */
#define DemCfg_GetViewId(EventId)            255
/* Map EventId to functional unit. */
#define DemCfg_GetFunctionalUnit(EventId)    (Dem_FunctionalUnitTable[Dem_PostBuildProperty[EventId]])
/* Map EventId to flag value. */
#define DemCfg_GetDtcSupportWarningIndicator(EventId) FALSE
/* Map EventId to flag value. */
#define DemCfg_GetDtcSuppressFlag(EventId)   FALSE
extern FUNC(boolean, DEM_CODE) DemCfg_GetIsAgingAllowed(Dem_EventIdType EventId); /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern FUNC(boolean, DEM_CODE) DemCfg_IsOccurrence(Dem_EventIdType EventId); /* PRQA S 0850 */ /* MD_MSR_19.8 */
/* Test if EventId uses Jump-Up-to-Zero, used for counter based debouncing. */
#define DemCfg_GetIsPredebJumpPreFailed(EventId) 1
/* Test if EventId uses Jump-Down-to-Zero, used for counter based debouncing. */
#define DemCfg_GetIsPredebJumpPrePassed(EventId) 0
extern FUNC(uint8, DEM_CODE) DemCfg_GetPredebStepsizePreFailed(Dem_EventIdType EventId); /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern FUNC(uint8, DEM_CODE) DemCfg_GetPredebStepsizePrePassed(Dem_EventIdType EventId); /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern FUNC(uint8, DEM_CODE) DemCfg_GetIsEventTimeBasedDebounce(Dem_EventIdType EventId); /* PRQA S 0850 */ /* MD_MSR_19.8 */
/* Map EventId to 'prefailed' qualification time. Used for timer based debouncing. */
#define DemCfg_GetTimeBasedDebValueFailed(EventId) (Dem_DebounceFailedTimeTable[Dem_DebounceIndexTable[Dem_PostBuildProperty[EventId]]])
/* Map EventId to 'prepassed' qualification time. Used for timer based debouncing. */
#define DemCfg_GetTimeBasedDebValuePassed(EventId) (Dem_DebouncePassedTimeTable[Dem_DebounceIndexTable[Dem_PostBuildProperty[EventId]]])
/* Map time slot index to EventId. Used for timer based debouncing. */
#define DemCfg_GetTimeBasedDebounceTableIdx(EventId) (Dem_EventIdToTimeBasedDebIdxTable[EventId])
/* Map EventId to time slot index. Used for timer based debouncing. */
#define DemCfg_GetEventIdFromTimeBasedDebounceTableIdx(TimeBasedIdx) (Dem_TimeBasedDebIdxToEventIdTable[TimeBasedIdx])
/* Map EventId to DTC kind. Dem_DTCKindType is defined in dem_types.h */
#define DemCfg_GetDTCKind(EventId)           (Dem_DtcKindTable[Dem_PostBuildProperty[EventId]])
/* Map EventId to supported origin (bitcoded). Primary == 0x02, Mirror == 0x04, Permanent == 0x08, Secondary == 0x10. */
#define DemCfg_GetDTCOrigin(EventId)         (Dem_EventDestinationTable[Dem_PostBuildProperty[EventId]])
/* Map EventId to DTC group index. Internal event == 0x00, OBD == 0x01, P == 0x02, C == 0x04, B == 0x08, U == 0x10, ALL == 0xFF */
#define DemCfg_GetDTCGroupKind(EventId)      (Dem_EventGroupTable[Dem_LinkTimeProperty[EventId]])
/* Map EventId to the Index of the first DID of its snapshot records. */
#define DemCfg_GetFirstSnapshot(EventId)     0
/* Map EventId to the total number of DIDs across all of its snapshot records. */
#define DemCfg_GetCountOfSnapshotDIDs(EventId) 0
/* Map SsRecIdx to the DID number. Get first SsRecIdx either per Event using DemCfg_GetFirstSnapshot(EventId) or per Snapshot by DemCfg_GetSnapshotRecordDIDIndex(ssRecordIndex) */
#define DemCfg_GetSnapshotDID(SsRecIdx)      0
/* Map SsRecIdx to a list of DID numbers. Get first SsRecIdx either per Event using DemCfg_GetFirstSnapshot(EventId) or per Snapshot by DemCfg_GetSnapshotRecordDIDIndex(ssRecordIndex) */
#define DemCfg_GetSnapshotDIDAddr(SsRecIdx)  0
/* Map SsRecIdx to the size of the DID (in byte). Get first SsRecIdx either per Event using DemCfg_GetFirstSnapshot(EventId) or per Snapshot by DemCfg_GetSnapshotRecordDIDIndex(ssRecordIndex) */
#define DemCfg_GetSnapshotDIDDataSize(SsRecIdx) 0
/* Map EventId to first Index into snapshot table. */
#define DemCfg_GetFirstSnapshotRecNumber(EventId) 0
/* Map EventId to number of snapshot records. */
#define DemCfg_GetCountOfSnapshotRecNumbers(EventId) 0
/* Map ssRecordIndex to number of the snapshot record. The first valid ssRecordIndex is DemCfg_GetFirstSnapshotRecNumber(EvenId). */
#define DemCfg_GetSnapshotRecordNumber(ssRecordIndex) 255
/* Map ssRecordIndex to the size of the snapshot record (in byte). The first valid ssRecordIndex is DemCfg_GetFirstSnapshotRecNumber(EvenId). */
#define DemCfg_GetSnapshotRecordDIDsSize(ssRecordIndex) 0
/* Map ssRecordIndex to the number of DIDs in the snapshot record. The first valid ssRecordIndex is DemCfg_GetFirstSnapshotRecNumber(EvenId). */
#define DemCfg_GetSnapshotRecordNumberOfDIDs(ssRecordIndex) 0
/* Map ssRecordIndex to first Index into DID table. The first valid ssRecordIndex is DemCfg_GetFirstSnapshotRecNumber(EvenId). */
#define DemCfg_GetSnapshotRecordDIDIndex(ssRecordIndex) 0
/* Map EventId to the offset into the prestored snapshot buffer. */
#define DemCfg_PrestoreFFBufStartOffset(EventId) 0
/* Map EventId to size of its prestored snapshot data. */
#define DemCfg_PrestoreFFBufSize(EventId)    0
/* Map EventId to the end offset into the prestored snapshot buffer. */
#define DemCfg_PrestoreFFBufEndOffset(EventId) 0
/* Map EventId to Index of first Extended Data Record. Index is valid in Dem_Record* tables. */
#define DemCfg_GetFirstExtendedRecord(EventId) (Dem_EventRecordIndexTable[Dem_PostBuildProperty[EventId]])
/* Map EventId to number of Extended Data Records. */
#define DemCfg_GetCountOfCurrentExtendedRecord(EventId) (Dem_EventRecordSizeTable[Dem_PostBuildProperty[EventId]])
/* Map ExtRecIdx to RecordId of an Extended Data Record. (First) valid ExtRecIdx per EventId is returned by DemCfg_GetFirstExtendedRecord. */
#define DemCfg_GetExtendedRecordNumber(ExtRecIdx) (Dem_RecordIdTable[ExtRecIdx])
/* Map ExtRecIdx to size [byte] of an Extended Data Record. (First) valid ExtRecIdx per EventId is returned by DemCfg_GetFirstExtendedRecord. */
#define DemCfg_GetExtendedRecordNumberDataSize(ExtRecIdx) (Dem_RecordSizeTable[ExtRecIdx])
/* Map ExtRecIdx to size [byte] of an Extended Data Record, in MirrorMemory. (First) valid ExtRecIdx per EventId is returned by DemCfg_GetFirstExtendedRecord. */
#define DemCfg_GetMirExtendedRecordNumberDataSize(ExtRecIdx) (Dem_RecordSizeMirTable[ExtRecIdx])
/* Map ExtRecIdx to function pointer used to get the data. (First) valid ExtRecIdx per EventId is returned by DemCfg_GetFirstExtendedRecord. */
#define DemCfg_GetExtendedRecordFuncRef(ExtRecIdx) (Dem_RecordFuncTable[ExtRecIdx])
/* Map EventId to valid identity mask. Can be multiple identity (only one bit set) or VSG mode (multiple bits set). */
#define DemCfg_GetEventIdentityVariant(EventId) 0



#define DEM_STOP_SEC_CODE
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"


/* END of Checksum include for
  - Diag_AsrDemLinktimeCRC */


/* -----------------------------------------------------------------------------
    &&&~ Justification of MISRA deviations
 ----------------------------------------------------------------------------- */

/* START of Checksum exclude for
  - Diag_AsrDemLinktimeCRC */
/* MD_DEM_8.12:
    Reason:     Prevent compiler optimization based on known array size.
    Risk:       None. The static code is not allowed to access this array directly.
    Prevention: Code inspection. */
/* END of Checksum exclude for
  - Diag_AsrDemLinktimeCRC */



/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 268053767
      #error "The magic number of the generated file <C:\_TSS\DAG\MFA2\Target\Appl\GenData\Dem_Lcfg.h> is different. Please check time and date of generated files!"
  #endif
#else
  #define MAGIC_NUMBER 268053767
#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

#endif /* DEM_LCFG_H */
