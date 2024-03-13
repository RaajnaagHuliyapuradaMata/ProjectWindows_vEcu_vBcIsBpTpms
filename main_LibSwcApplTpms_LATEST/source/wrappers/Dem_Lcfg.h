

#if !defined(DEM_LCFG_H)
#define DEM_LCFG_H

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

#define Dem_DEM_IND_SC8_RELEVANT             0
#define Dem_DEM_IND_MALFLAMP                 1
#define Dem_DEM_IND_ECUFAILURE               2

typedef P2VAR(uint8, TYPEDEF, DEM_APPL_DATA) Dem_ApplBufferPtrType;
typedef P2FUNC(Std_ReturnType, DEM_APPL_CODE, Dem_GetCurrentOdometerFPtrType) (P2VAR(uint32, AUTOMATIC, DEM_VAR_NOINIT) );
typedef P2FUNC(Std_ReturnType, DEM_APPL_CODE, Dem_GetExternalTesterStatusFPtrType) (P2VAR(boolean, AUTOMATIC, DEM_VAR_NOINIT) );
typedef P2FUNC(Std_ReturnType, DEM_APPL_CODE, Dem_OnControlDTCFPtrType) (boolean );
typedef VAR(uint8, TYPEDEF) Dem_Mem_PrimaryIndexType;
typedef VAR(uint8, TYPEDEF) Dem_Mem_MirrorIndexType;
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
typedef VAR(uint8, TYPEDEF) Dem_DataRecordSizeType;

#define DEM_START_SEC_VAR_SAVED_ZONE0_UNSPECIFIED

#include "MemMap.h"

extern VAR(Dem_NvAdminDataType, DEM_APPL_DATA) Dem_Cfg_NvAdminData;
extern VAR(Dem_NvStatusDataType, DEM_APPL_DATA) Dem_Cfg_NvEventStatusData;
extern VAR(Dem_NvPrimaryEntryType, DEM_APPL_DATA) Dem_Cfg_NvPrimaryEntry_1;
extern VAR(Dem_NvPrimaryEntryType, DEM_APPL_DATA) Dem_Cfg_NvPrimaryEntry_2;
extern VAR(Dem_NvPrimaryEntryType, DEM_APPL_DATA) Dem_Cfg_NvPrimaryEntry_3;
extern VAR(Dem_NvPrimaryEntryType, DEM_APPL_DATA) Dem_Cfg_NvPrimaryEntry_4;
extern VAR(Dem_NvPrimaryEntryType, DEM_APPL_DATA) Dem_Cfg_NvPrimaryEntry_5;
extern VAR(Dem_NvPrimaryEntryType, DEM_APPL_DATA) Dem_Cfg_NvPrimaryEntry_6;
extern VAR(Dem_NvPrimaryEntryType, DEM_APPL_DATA) Dem_Cfg_NvPrimaryEntry_7;
extern VAR(Dem_NvPrimaryEntryType, DEM_APPL_DATA) Dem_Cfg_NvPrimaryEntry_8;
extern VAR(Dem_NvPrimaryEntryType, DEM_APPL_DATA) Dem_Cfg_NvPrimaryEntry_9;
extern VAR(Dem_NvPrimaryEntryType, DEM_APPL_DATA) Dem_Cfg_NvPrimaryEntry_10;
extern VAR(Dem_NvMirrorMemoryType, DEM_APPL_DATA) Dem_Cfg_NvMirrorMemory;
extern VAR(uint8, DEM_APPL_DATA) Dem_PreFFBuffer[DEM_PRESTORE_FF_BUFFER_SIZE];

#define DEM_STOP_SEC_VAR_SAVED_ZONE0_UNSPECIFIED

#include "MemMap.h"

#define DEM_START_SEC_VAR_FAST_8BIT

#include "MemMap.h"

extern VAR(uint8, DEM_VAR_NOINIT_FAST) Dem_StatusTestFailedTOC[];
extern VAR(uint8, DEM_VAR_NOINIT_FAST) Dem_StatusConfirmedDTC[];
extern VAR(uint8, DEM_VAR_NOINIT_FAST) Dem_StatusTestNotCompletedTOC[];
extern VAR(Dem_DtcInternalStatusType, DEM_VAR_NOINIT_FAST) Dem_DtcInternalStatus[];
extern VAR(sint8, DEM_VAR_NOINIT_FAST) Dem_DtcFaultDetectionCounter[];
extern VAR(uint8, DEM_VAR_NOINIT_FAST) Dem_Mem_PrimaryEntryStatus[];
extern VAR(Dem_Mem_PrimaryIndexType, DEM_VAR_NOINIT_FAST) Dem_Mem_PrimaryChronology[];

#define DEM_STOP_SEC_VAR_FAST_8BIT

#include "MemMap.h"

#define DEM_START_SEC_VAR_NOINIT_8BIT

#include "MemMap.h"

extern VAR(Dem_OperationCycleStateType, DEM_VAR_NOINIT) Dem_OperationCycleState[];
#define DEM_STOP_SEC_VAR_NOINIT_8BIT

#include "MemMap.h"

#define DEM_START_SEC_VAR_NOINIT_16BIT

#include "MemMap.h"

extern VAR(Dem_EventIdType, DEM_VAR_NOINIT) Dem_IndicatorCounter[][2];
#define DEM_STOP_SEC_VAR_NOINIT_16BIT

#include "MemMap.h"

#define DEM_START_SEC_VAR_NOINIT_UNSPECIFIED

#include "MemMap.h"

extern VAR(uint32, DEM_VAR_NOINIT) Dem_EnableConditionState;
extern VAR(Dem_AQElementType, DEM_VAR_NOINIT) Dem_ActionQueue[];
extern VAR(Dem_TimeBasedDebounceTimerType, DEM_VAR_NOINIT) Dem_DebounceTimer;
extern VAR(Dem_TimeBasedDebounceTimerType, DEM_VAR_NOINIT) Dem_DebounceTimerSlots[];

#define DEM_STOP_SEC_VAR_NOINIT_UNSPECIFIED

#include "MemMap.h"

#define DEM_START_SEC_CONST_LCFG

#include "MemMap.h"

extern CONST(Dem_DemConfigurationType, DEM_CONST) Dem_DemConfiguration;

extern CONST(Dem_NvMBlockIdType, DEM_CONST) Dem_Cfg_NvAdminBlock;
extern CONST(Dem_NvMBlockIdType, DEM_CONST) Dem_Cfg_NvEventStatusBlock;
extern CONST(Dem_NvMBlockIdType, DEM_CONST) Dem_Cfg_NvPrimaryBlocks[];
extern CONST(Dem_NvMBlockIdType, DEM_CONST) Dem_Cfg_NvMirrorBlocks[];

extern CONST(Dem_NvPrimaryEntryType, DEM_CONST) Dem_Cfg_NvPrimaryEntry_Zero;

extern CONST(Dem_DTCGroupMappingType, DEM_CONST) Dem_DTCGroupTable[];
extern CONST(uint8, DEM_CONST) Dem_LinkTimeProperty[];
extern CONST(uint8, DEM_CONST) Dem_InitMonitorIndexTable[];
extern CONST(Dem_InitMonitorFPtrType, DEM_CONST) Dem_InitMonitorFPtrTable[];
extern CONST(Dem_TriggerDTCFunctionType, DEM_CONST) Dem_TriggerDTCFunctionTable[];
extern CONST(uint8, DEM_CONST) Dem_TriggerDTCIndexTable[];
extern CONST(uint8, DEM_CONST) Dem_TriggerDTCCountTable[];
extern CONST(Dem_TriggerFunctionType, DEM_CONST) Dem_TriggerFunctionTable[];
extern CONST(uint8, DEM_CONST) Dem_IndicatorCountTable[];
extern CONST(uint8, DEM_CONST) Dem_IndicatorIndexTable[];
extern CONST(Dem_IndicatorIdType, DEM_CONST) Dem_IndicatorIdTable[];
extern CONST(Dem_IndicatorStatusType, DEM_CONST) Dem_IndicatorStatusTable[];
extern CONST(Dem_DTCGroupKindType, DEM_CONST) Dem_EventGroupTable[];
extern CONST(Dem_DIDLookupTableType, DEM_CONST) Dem_DIDLookupTable[];
extern CONST(Dem_GetExtDataRecordFPtrType, DEM_CONST) Dem_GetExtDataRecordListTable[];

extern CONST(uint8, DEM_CONST) Dem_StatusAvailabilityMask;
extern CONST(uint16, DEM_CONST) Dem_MaxSizeOfSnapshotRecord;
extern CONST(uint16, DEM_CONST) Dem_MaxSizeOfExtdataRecord;
extern CONST(uint16, DEM_CONST) Dem_NumberOfOperationCycles;
extern CONST(uint16, DEM_CONST) Dem_NumberOfIndicators;
extern CONST(Dem_EventIdType, DEM_CONST) Dem_Cfg_MaxEventId;
extern CONST(Dem_Mem_PrimaryIndexType, DEM_CONST) Dem_Cfg_NumPrimaryEntries;
extern CONST(Dem_Mem_MirrorIndexType, DEM_CONST) Dem_Cfg_NumMirrorEntries;
extern CONST(uint16, DEM_CONST) Dem_Cfg_MirrorEntrySize;
extern CONST(uint16, DEM_CONST) Dem_Cfg_MirrorUserDataSize;
extern CONST(uint16, DEM_CONST) Dem_SizeofPreFFBuffer;
extern CONST(uint8, DEM_CONST) Dem_SnapshotsPerDTC;
extern CONST(uint8, DEM_CONST) Dem_FirstOverwritableSnapshot;
extern CONST(uint8, DEM_CONST) Dem_ReportErrorBufferSize;
extern CONST(uint16, DEM_CONST) Dem_ActionQueueCount;
extern CONST(uint8, DEM_CONST) Dem_DTCGroupMappingCount;
extern CONST(uint8, DEM_CONST) Dem_SizeofEventIdType;
extern CONST(uint16, DEM_CONST) Dem_NumberOfDebounceTimerSlots;

extern CONSTP2VAR(uint32, DEM_CONST, DEM_APPL_DATA) Dem_Cfg_AdminActiveVersionPtr;
extern CONSTP2VAR(uint16, DEM_CONST, DEM_APPL_DATA) Dem_Cfg_AdminCycleCounterPtr;
extern CONSTP2VAR(uint8, DEM_CONST, DEM_VAR_NOINIT) Dem_Cfg_AdminCycleStatePtr;

extern volatile CONSTP2VAR(uint8, DEM_CONST, DEM_APPL_DATA) Dem_StatusTestFailedPtr;
extern volatile CONSTP2VAR(uint8, DEM_CONST, DEM_VAR_NOINIT_FAST) Dem_StatusTestFailedTOCPtr;
extern volatile CONSTP2VAR(uint8, DEM_CONST, DEM_VAR_NOINIT_FAST) Dem_StatusConfirmedDTCPtr;
extern volatile CONSTP2VAR(uint8, DEM_CONST, DEM_APPL_DATA) Dem_StatusTestNotCompletedSLCPtr;
extern volatile CONSTP2VAR(uint8, DEM_CONST, DEM_APPL_DATA) Dem_StatusTestFailedSLCPtr;
extern volatile CONSTP2VAR(uint8, DEM_CONST, DEM_VAR_NOINIT_FAST) Dem_StatusTestNotCompletedTOCPtr;

extern CONSTP2VAR(sint8, DEM_CONST, DEM_VAR_NOINIT_FAST) Dem_FaultDetectionCounterPtr;
extern CONSTP2VAR(Dem_EventIdType, DEM_CONST, DEM_APPL_DATA) Dem_FirstFailedEventIdPtr;
extern CONSTP2VAR(Dem_EventIdType, DEM_CONST, DEM_APPL_DATA) Dem_FirstConfirmedEventIdPtr;
extern CONSTP2VAR(Dem_EventIdType, DEM_CONST, DEM_APPL_DATA) Dem_MostRecentFailedEventIdPtr;
extern CONSTP2VAR(Dem_EventIdType, DEM_CONST, DEM_APPL_DATA) Dem_MostRecentConfmdEventIdPtr;
extern CONSTP2VAR(Dem_NvPrimaryEntryType, DEM_CONST, DEM_APPL_DATA) Dem_Cfg_PrimaryStackPtr[];

extern CONSTP2VAR(Dem_EventIdType, DEM_CONST, DEM_APPL_DATA) Dem_Cfg_MirrorEventIdPtr;
extern CONSTP2VAR(uint8, DEM_CONST, DEM_APPL_DATA) Dem_Cfg_MirrorDataPtr;
extern CONSTP2VAR(Dem_Mem_MirrorIndexType, DEM_CONST, DEM_APPL_DATA) Dem_Cfg_MirrorWriteIndexPtr;

extern CONSTP2VAR(uint16, DEM_CONST, DEM_APPL_DATA) Dem_HirOdometerPtr;
extern CONSTP2VAR(uint8, DEM_CONST, DEM_APPL_DATA) Dem_HirReadCountPtr;

#define DEM_STOP_SEC_CONST_LCFG

#include "MemMap.h"

#define DEM_START_SEC_CODE

#include "MemMap.h"

extern FUNC(Dem_EventIdType, DEM_CODE) Dem_Cfg_GetMaxEventId(void);
extern FUNC(uint8, DEM_CODE) DemCfg_GetDTCTranslationFormat(void);
extern FUNC(Dem_GetCurrentOdometerFPtrType, DEM_CODE) DemCfg_GetCurrentOdometerFPtr(void);
extern FUNC(Dem_GetExternalTesterStatusFPtrType, DEM_CODE) DemCfg_GetExternalTesterStatusFPtr(void);
extern FUNC(Dem_OnControlDTCFPtrType, DEM_CODE) DemCfg_GetOnControlDTCFPtr(void);
extern FUNC(uint16, DEM_CODE) DemCfg_GetMaxCountOfOperationCycle(void);
extern FUNC(uint8, DEM_CODE) DemCfg_GetCountOfSnapshotsPerDTC(void);
extern FUNC(uint16, DEM_CODE) DemCfg_GetMaxSnapshotRecordSize(void);
extern FUNC(uint8, DEM_CODE) DemCfg_Get1stOverwrtSnapshotIndex(void);

#define DemCfg_GetCountOfGlobalSsDIDs(EventId) 0
#define DemCfg_GetFirstGlobalSsRecord(EventId) 0
extern FUNC(uint16, DEM_CODE) DemCfg_GetMaxExtdataRecordSize(void);
extern FUNC(Dem_Mem_PrimaryIndexType, DEM_CODE) Dem_Cfg_GetNumPrimaryEntries(void);
extern FUNC(uint32, DEM_CODE) DemCfg_GetEnableConditionInitValue(void);

extern FUNC(Dem_DTCGroupKindType, DEM_CODE) Dem_MapGroupNumberToGroupKind(Dem_DTCType DTCGroupNumber);
extern FUNC(Dem_DTCType, DEM_CODE) DemCfg_GetDTCnumber(Dem_EventIdType EventId);

extern FUNC(Dem_InitMonitorFPtrType, DEM_CODE) DemCfg_GetInitMonitorFPtr(Dem_EventIdType EventId);

#define DemCfg_GetFirstTriggerOnDTC(EventId) (Dem_TriggerDTCIndexTable[Dem_LinkTimeProperty[EventId]])

#define DemCfg_GetCountOfTriggerOnDTC(EventId) (Dem_TriggerDTCCountTable[Dem_LinkTimeProperty[EventId]])

#define DemCfg_GetFirstTriggerOnEvent(EventId) 0

#define DemCfg_GetCountOfTriggerOnEvent(EventId) 0

#define DemCfg_GetEventPriority(EventId)     (Dem_EventPriorityTable[Dem_PostBuildProperty[EventId]])

#define DemCfg_GetDTCSeverity(EventId)       0

#define DemCfg_GetAgingCycleId(EventId)      0

#define DemCfg_GetOperationCycleId(EventId)  (Dem_OperationCycleTable[Dem_PostBuildProperty[EventId]])

#define DemCfg_GetNumberOfAgingCycles(EventId) (Dem_AgingCountTable[Dem_PostBuildProperty[EventId]])

#define DemCfg_GetEnableConditionMask(EventId) (Dem_EnableConditionTable[Dem_PostBuildProperty[EventId]])

#define DemCfg_GetCountOfIndicatorIds(EventId) (Dem_IndicatorCountTable[Dem_LinkTimeProperty[EventId]])

#define DemCfg_GetIndicatorIndex(EventId)    (Dem_IndicatorIndexTable[Dem_LinkTimeProperty[EventId]])

#define DemCfg_GetIndicatorId(IndIdIdx)      (Dem_IndicatorIdTable[IndIdIdx])

#define DemCfg_GetIndicatorStatusType(IndIdIdx) (Dem_IndicatorStatusTable[IndIdIdx])
extern FUNC(Dem_EventIdPtrType, DEM_CODE) DemCfg_GetIndicatorCounterPtr(Dem_IndicatorIdType IndicatorId, Dem_IndicatorStatusType IndicatorBehavior);

#define DemCfg_GetViewId(EventId)            255

#define DemCfg_GetFunctionalUnit(EventId)    (Dem_FunctionalUnitTable[Dem_PostBuildProperty[EventId]])

#define DemCfg_GetDtcSupportWarningIndicator(EventId) FALSE

#define DemCfg_GetDtcSuppressFlag(EventId)   FALSE
extern FUNC(boolean, DEM_CODE) DemCfg_GetIsAgingAllowed(Dem_EventIdType EventId);
extern FUNC(boolean, DEM_CODE) DemCfg_IsOccurrence(Dem_EventIdType EventId);

#define DemCfg_GetIsPredebJumpPreFailed(EventId) 1

#define DemCfg_GetIsPredebJumpPrePassed(EventId) 0
extern FUNC(uint8, DEM_CODE) DemCfg_GetPredebStepsizePreFailed(Dem_EventIdType EventId);
extern FUNC(uint8, DEM_CODE) DemCfg_GetPredebStepsizePrePassed(Dem_EventIdType EventId);
extern FUNC(uint8, DEM_CODE) DemCfg_GetIsEventTimeBasedDebounce(Dem_EventIdType EventId);

#define DemCfg_GetTimeBasedDebValueFailed(EventId) (Dem_DebounceFailedTimeTable[Dem_DebounceIndexTable[Dem_PostBuildProperty[EventId]]])

#define DemCfg_GetTimeBasedDebValuePassed(EventId) (Dem_DebouncePassedTimeTable[Dem_DebounceIndexTable[Dem_PostBuildProperty[EventId]]])

#define DemCfg_GetTimeBasedDebounceTableIdx(EventId) (Dem_EventIdToTimeBasedDebIdxTable[EventId])

#define DemCfg_GetEventIdFromTimeBasedDebounceTableIdx(TimeBasedIdx) (Dem_TimeBasedDebIdxToEventIdTable[TimeBasedIdx])

#define DemCfg_GetDTCKind(EventId)           (Dem_DtcKindTable[Dem_PostBuildProperty[EventId]])

#define DemCfg_GetDTCOrigin(EventId)         (Dem_EventDestinationTable[Dem_PostBuildProperty[EventId]])

#define DemCfg_GetDTCGroupKind(EventId)      (Dem_EventGroupTable[Dem_LinkTimeProperty[EventId]])

#define DemCfg_GetFirstSnapshot(EventId)     0

#define DemCfg_GetCountOfSnapshotDIDs(EventId) 0

#define DemCfg_GetSnapshotDID(SsRecIdx)      0

#define DemCfg_GetSnapshotDIDAddr(SsRecIdx)  0

#define DemCfg_GetSnapshotDIDDataSize(SsRecIdx) 0

#define DemCfg_GetFirstSnapshotRecNumber(EventId) 0

#define DemCfg_GetCountOfSnapshotRecNumbers(EventId) 0

#define DemCfg_GetSnapshotRecordNumber(ssRecordIndex) 255

#define DemCfg_GetSnapshotRecordDIDsSize(ssRecordIndex) 0

#define DemCfg_GetSnapshotRecordNumberOfDIDs(ssRecordIndex) 0

#define DemCfg_GetSnapshotRecordDIDIndex(ssRecordIndex) 0

#define DemCfg_PrestoreFFBufStartOffset(EventId) 0

#define DemCfg_PrestoreFFBufSize(EventId)    0

#define DemCfg_PrestoreFFBufEndOffset(EventId) 0

#define DemCfg_GetFirstExtendedRecord(EventId) (Dem_EventRecordIndexTable[Dem_PostBuildProperty[EventId]])

#define DemCfg_GetCountOfCurrentExtendedRecord(EventId) (Dem_EventRecordSizeTable[Dem_PostBuildProperty[EventId]])

#define DemCfg_GetExtendedRecordNumber(ExtRecIdx) (Dem_RecordIdTable[ExtRecIdx])

#define DemCfg_GetExtendedRecordNumberDataSize(ExtRecIdx) (Dem_RecordSizeTable[ExtRecIdx])

#define DemCfg_GetMirExtendedRecordNumberDataSize(ExtRecIdx) (Dem_RecordSizeMirTable[ExtRecIdx])

#define DemCfg_GetExtendedRecordFuncRef(ExtRecIdx) (Dem_RecordFuncTable[ExtRecIdx])

#define DemCfg_GetEventIdentityVariant(EventId) 0

#define DEM_STOP_SEC_CODE

#include "MemMap.h"

#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 268053767
      #error "The magic number of the generated file <C:\_TSS\DAG\MFA2\Target\Appl\GenData\Dem_Lcfg.h> is different. Please check time and date of generated files!"
  #endif
#else
#define MAGIC_NUMBER 268053767
#endif
#endif

#endif
