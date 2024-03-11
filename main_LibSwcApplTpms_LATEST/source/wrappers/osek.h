

#ifndef _OSEK_H
#define _OSEK_H

#if defined __cplusplus
extern "C"
{
#endif

#if defined USE_QUOTE_INCLUDES
 #include "vrm.h"
#else
 #include <vrm.h>
#endif

#define osdVrmMajRelNum 1
#define osdVrmMinRelNum 1

#if defined USE_QUOTE_INCLUDES
 #include "vrm.h"
#else
 #include <vrm.h>
#endif

#define OS_VENDOR_ID 30
#define OS_MODULE_ID 0x01

#define OS_AR_RELEASE_MAJOR_VERSION 4
#define OS_AR_RELEASE_MINOR_VERSION 0
#define OS_AR_RELEASE_REVISION_VERSION 3

#define osdVrmMajRelNum 1
#define osdVrmMinRelNum 1

#define OS_SW_MAJOR_VERSION osdVrmMajRelNumRef
#define OS_SW_MINOR_VERSION osdVrmMinRelNumRef

#define OS_SW_PATCH_VERSION 0

#define BCC1   1U
#define BCC2   2U
#define ECC1   3U
#define ECC2   4U

#define SC1    1U
#define SC2    2U
#define SC3    3U
#define SC4    4U

#define STANDARD_STATUS 0U
#define EXTENDED_STATUS 1U

#define osdFALSE 0U
#define osdTRUE  1U

#define osdNULL ((osqPROM1 osqPROM2 void osqPROM3 *)0)

#define PRE_READY       0
#define RUNNING         1
#define WAITING         2
#define READY           3
#define SUSPENDED       4
#define WAIT_SEMAPHORE  5

#ifndef OS_SUPPRESS_PROTHOOK_OLD_RET_VALS
#define PRO_KILLTASKISR           1U
#define PRO_KILLAPPL              2U
#define PRO_KILLAPPL_RESTART      3U
#endif
#define PRO_TERMINATETASKISR      1U
#define PRO_TERMINATEAPPL         2U
#define PRO_TERMINATEAPPL_RESTART 3U
#define PRO_SHUTDOWN              4U
#define PRO_IGNORE                5U

typedef unsigned char  osuint8;
typedef unsigned short osuint16;
typedef unsigned long  osuint32;
typedef signed   char  osint8;
typedef signed   short osint16;
typedef signed   long  osint32;

#ifndef osbool
 #define osbool osuint8
#endif

typedef osbool osBoolArrayBaseType;

#ifdef PRQA_PTRDIFF_T

 #pragma PRQA_NO_RETURN osAbortSystem
 #pragma PRQA_NO_RETURN osAssertFailed
 #pragma PRQA_NO_RETURN osSysShutdownOS

#endif

   #if defined USE_QUOTE_INCLUDES
    #include "tcb.h"
   #else
    #include <tcb.h>
   #endif

#define osqROM0
#define osqROM1
#define osqROM2
#define osqROM3

#define osqPROM1
#define osqPROM2
#define osqPROM3

#define osqRAM0
#define osqRAM1
#define osqRAM2
#define osqRAM3

#define osqPRAM1
#define osqPRAM2
#define osqPRAM3

#define osqBOOL1
#define osqBOOL2
#define osqBOOL3

#define osqTcbRAM1
#define osqTcbRAM2
#define osqTcbRAM3

#define osqPTcbRAM1
#define osqPTcbRAM2
#define osqPTcbRAM3

#define osqStack1
#define osqStack2
#define osqStack3

#define osqFunc1
#define osqFunc2

#define osqScRAM0
#define osqScRAM1
#define osqScRAM2
#define osqScRAM3
#define osqScPRAM1
#define osqScPRAM2
#define osqScPRAM3

#define osqInlineGetHighPrioBit inline

#if defined USE_QUOTE_INCLUDES
 #include "osekcov.h"
 #include "osekasrt.h"
 #include "osekerr.h"
#else
 #include <osekcov.h>
 #include <osekasrt.h>
 #include <osekerr.h>
#endif

#define INVALID_ISR           ((ISRType)(0xFFFFFFFFUL))
#define INVALID_TASK          ((TaskType)(0xFFFFFFFFUL))
#define INVALID_OSAPPLICATION ((ApplicationType)0xFFU)
#define INVALID_SCHEDULETABLE ((ScheduleTableType)(0xFFFFFFFFUL))
#define INVALID_PROCESS       (((osProcessType)(0xFFFFFFFFUL)))

#define APPLICATION_ACCESSIBLE ((ApplicationStateType)1)
#define APPLICATION_RESTARTING ((ApplicationStateType)2)
#define APPLICATION_TERMINATED ((ApplicationStateType)3)

#define osdNoActiveTask       INVALID_TASK

#define osdNoActivePrio       ((osPrioType)(0xFFFFFFFFUL))

#define osdNoResource         ((ResourceType)(0xFFFFFFFFUL))

#define osdNoSemaphore   ((osSemaphoreType)(0xFFFFFFFFUL))

#define NO_ACCESS 0U
#define ACCESS 1U

#define SCHEDULETABLE_STOPPED                 0U
#define SCHEDULETABLE_NEXT                    1U
#define SCHEDULETABLE_WAITING                 2U
#define SCHEDULETABLE_RUNNING                 3U
#define SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS 4U

#define oskAccess_None 0x0U
#define oskAccess_Read 0x1U
#define oskAccess_Write 0x2U
#define oskAccess_Execute 0x4U
#define oskAccess_Stack 0x8U

#define OSMEMORY_IS_READABLE(x) (((x) & oskAccess_Read)? 1 : 0)
#define OSMEMORY_IS_WRITEABLE(x) (((x) & oskAccess_Write)? 1 : 0)
#define OSMEMORY_IS_EXECUTABLE(x) (((x) & oskAccess_Execute)? 1 : 0)
#define OSMEMORY_IS_STACKSPACE(x) (((x) & oskAccess_Stack)? 1 : 0)

#define RESTART    1
#define NO_RESTART 2

#define osdScheduleTableAutostartNO                  0U
#define osdScheduleTableAutostartABSOLUT             1U
#define osdScheduleTableAutostartRELATIVE            2U
#define osdScheduleTableAutostartSYNCHRON            3U

#define osdAlarmAutostartNO                          0U
#define osdAlarmAutostartABSOLUTE                    1U
#define osdAlarmAutostartRELATIVE                    2U

#define OSINVALIDAPPMODE                             0U

#define TASK(x) void x##func(void)

#define ISR(x) void x##func(void)

#define ALARMCALLBACK(x) void x(void)

#define Os_TPExeSwitchTo(x)      osTPExeSwitchTo(x)
#define Os_TPResumeTimerBlock(x) osTPResumeTimerBlock(x)
#define Os_TPSuspendTimerBlock() osTPSuspendTimerBlock()
#define Os_TPExeSwitchBack(x)    osTPExeSwitchBack(x)
#define Os_TPArrivalAllowed(x)   osTPArrivalAllowed(x)

#define osdPrioBitsPerWord       32
#define osdIntAPIMaxNesting      (osdIntAPIDisableAll-1)

#ifndef OS_CHECK_INTAPISTATUS
#define OS_CHECK_INTAPISTATUS 1
#endif

#ifndef osdRH850_FPU
#define osdRH850_FPU 0
#endif

typedef osuint32             TickType;
typedef osint32              osTickTimeDiffType;

typedef osuint16      osPrioType;
typedef osuint8       osPrioOffsetType;

typedef osuint32      osStdFlagType;

typedef osStdFlagType osPrioFlagType;

typedef osStdFlagType osResAccessMaskType;

typedef osuint32            osIntLevelType;
typedef osuint8             osTaskPreemptionType;
typedef osuint8             osTaskFlagType;
typedef osuint16            osQEntryCountType;
typedef osuint8             osActivationCountType;
typedef osuint32            osStackDataType;
typedef osuint16            osStackSizeType;
typedef osuint16            osTaskIndexType;
typedef osuint16            osResourceIndexType;

typedef osuint16            osTIPType;
typedef osTIPType           osAlarmIndexType;
typedef osAlarmIndexType    AlarmType;
typedef osAlarmIndexType     *osAlarmIndexRefType;
typedef osTIPType           ScheduleTableType;

typedef osuint16                 osProcessType;
typedef osuint16                 ISRType;
typedef osuint8                  ScheduleTableStatusType;
typedef ScheduleTableStatusType* ScheduleTableStatusRefType;
typedef osuint8                  RestartType;
typedef osuint16                 CounterType;
typedef osuint32                 PhysicalTimeType;
#ifdef _MSC_VER
typedef unsigned __int64         osTPTimeStampType;
#else
typedef unsigned long long       osTPTimeStampType;
#endif
typedef osTPTimeStampType*       osTPTimeStampRefType;
typedef osuint32                 osTPTimeType;
typedef osTPTimeType*            osTPTimeRefType;

typedef osuint8                  osMPUAreaType;
typedef osuint8                  osMPUAttributesType;

typedef osuint32                 CoreIdType;

typedef double                   osTimeComputationType;

#ifndef _MSC_VER
typedef osuint8                          ApplicationType;
#endif

typedef osTaskIndexType     TaskType;
typedef osResourceIndexType ResourceType;
typedef osuint16            osSemaphoreType;

typedef osuint8             osRTSizeType;
typedef osuint16            osSystemTimerReloadValueType;
typedef osuint32            EventMaskType;
#define osdEventMaskTypeSize    4
#define osdMaxAllowedTimeStamp  0xffffffffffffffffU

typedef osuint8               osDispatcherLockType;

#ifndef STATUSTYPEDEFINED
#define STATUSTYPEDEFINED
typedef osuint8               StatusType;
#define E_OK 0
#endif

typedef osuint8              TaskStateType;
typedef osuint8              AppModeType;
typedef TaskType            *TaskRefType;
typedef TaskStateType       *TaskStateRefType;
typedef TickType            *TickRefType;
typedef EventMaskType       *EventMaskRefType;
typedef ISRType             *ISRRefType;

typedef TickType osSTOffsetType;
typedef TickType GlobalTimeTickType;
typedef osuint16 osSTIndexType;

typedef osuint8               ApplicationStateType;
typedef ApplicationStateType *ApplicationStateRefType;

typedef void                (*osTaskFctType)(void);
typedef void                (*osIsrFctType)(void);

typedef osuint16              osStackUsageType;
typedef osuint8               osTaskStateType;

typedef void       *        osStackPtrType;
typedef void const *        osStackPtrToConstType;

typedef struct {
   osStackPtrType start;
   osStackPtrType end;
} osStackType;

typedef osuint8               osResCounterType;

#define DeclareTask(TaskId)     osqRAM0 extern osqRAM1 osqRAM2 TaskType osqRAM3 osNotUsed1##TaskId
#define DeclareResource(ResId)  osqRAM0 extern osqRAM1 osqRAM2 TaskType osqRAM3 osNotUsed2##ResId
#define DeclareEvent(Event)     osqRAM0 extern osqRAM1 osqRAM2 TaskType osqRAM3 osNotUsed3##Event
#define DeclareAlarm(AlarmId)   osqRAM0 extern osqRAM1 osqRAM2 TaskType osqRAM3 osNotUsed4##AlarmId

typedef struct
{
   TickType maxallowedvalue;

   TickType ticksperbase;

   TickType mincycle;

} AlarmBaseType;

typedef AlarmBaseType     *AlarmBaseRefType;

typedef osTIPType         osHeapElementType;
typedef osHeapElementType *osHeapElementRefType;
typedef struct
{
   osHeapElementRefType heap;
   osAlarmIndexRefType  count;
} osHeapType;
typedef osHeapType const * osHeapRefType;

typedef osuint16          OSServiceIdType;
typedef void              (*osAlarmCallbackType)(void);
typedef osuint8           BlockTypeType;

#if(osdClearTIPAbsIdx != -1)
 osqFunc1 void osqFunc2 osClearTimerInterruptPointAbs(CounterType CounterID);
#endif
#if(osdClearTIPRelIdx != -1)
 osqFunc1 void osqFunc2 osClearTimerInterruptPointRel(CounterType CounterID);
#endif
#if(osdSetTIPAbsMaxGtSemiCountIdx != -1)
 osqFunc1 osbool osqFunc2 osSetTIPAbsMaxGtSemiCount(CounterType CounterID, TickType timeToSet);
#endif
#if(osdSetTIPRelMaxGtSemiCountIdx != -1)
 osqFunc1 osbool osqFunc2 osSetTIPRelMaxGtSemiCount(CounterType CounterID, TickType timeToSet);
#endif
#if(osdSetTIPAbsMaxLeSemiCountIdx != -1)
 osqFunc1 osbool osqFunc2 osSetTIPAbsMaxLeSemiCount(CounterType CounterID, TickType timeToSet);
#endif
#if(osdSetTIPRelMaxLeSemiCountIdx != -1)
 osqFunc1 osbool osqFunc2 osSetTIPRelMaxLeSemiCount(CounterType CounterID, TickType timeToSet);
#endif
#if(osdGetCurrentTimeHighResHybridIdx != -1)
 osqFunc1 TickType osqFunc2 osGetCurrentTimeHiResHybrid(CounterType CounterID);
#endif
#if(osdGetCurrentTimeHighResMonoIdx != -1)
 osqFunc1 TickType osqFunc2 osGetCurrentTimeHiResMono(CounterType CounterID);
#endif
#if(osdGetCurrentTimeStdIdx != -1)
 osqFunc1 TickType osqFunc2 osGetCurrentTimeStd(CounterType CounterID);
#endif
#if(osdHandleCounterInterruptStdIdx != -1)
 osqFunc1 void osqFunc2 osHandleCounterInterruptStd(CounterType CounterID);
#endif
#if(osdHandleCounterInterruptHiResIdx != -1)
 osqFunc1 void osqFunc2 osHandleCounterInterruptHiRes(CounterType CounterID);
#endif

#define osdCounterId2HiResCounterId(x)    ((x) -  osdNumberOfSWAndSRCounters)
#define osdIsHiResCounter(x)              ((osdNumberOfSWAndSRCounters == 0) || ((x) >= osdNumberOfSWAndSRCounters))
#define osdCounterId2HwCounterId(x)       ((x) -  osdNumberOfSWCounters)
#define osdIsHwCounter(x)                 ((x) >= osdNumberOfSWCounters)

typedef void (*osClearTimerInterruptPointOpType)(CounterType);
typedef osbool (*osSetTimerInterruptPointOpType)(CounterType, TickType);
typedef TickType (*osGetCurrentTimeOpType)(CounterType);
typedef void (*osHandleCounterInterruptsOpType)(CounterType);
typedef osqFunc1 void osqFunc2 (*osInsertMinHeapOpType)(osHeapElementType newItem, osHeapType const * const h, CounterType ctr);

typedef TickType  osHWTimerCompType;

typedef union
{
   TaskType          osTaskType;
   TaskRefType       osTaskRefType;
   ResourceType      osResourceType;
   EventMaskType     osEventMaskType;
   osTIPType         osAlarmType;
   CounterType       osCounterType;
   ScheduleTableType osScheduleTableType;
   ISRType           osISRType;
   osSemaphoreType   osOsSemaphoreType;
} osAPIParam1Type;

typedef union
{
   TaskStateRefType           osTaskStateRefType;
   EventMaskType              osEventMaskType;
   EventMaskRefType           osEventMaskRefType;
   AlarmBaseRefType           osAlarmBaseRefType;
   TickType                   osTickType;
   TickRefType                osTickRefType;
   ScheduleTableType          osScheduleTableType;
   ScheduleTableStatusRefType osScheduleTableStatusRefType;
   BlockTypeType              osBlockType;
} osAPIParam2Type;

typedef union
{
   TickType     osTickType;
   ResourceType osResourceType;
   TickRefType  osTickRefType;
} osAPIParam3Type;

typedef struct
{
   TaskType   ossHighReadyTaskIndex;
   osPrioType ossHighReadyTaskPrio;
   osbool ossStartDispatcher;
#if(CC==BCC2) || (CC==ECC2)
   #if(osdNumberOfPriorities > 0)
      osQEntryCountType ossQReadyTaskHead[osdNumberOfPriorities];
      osQEntryCountType ossQReadyTaskTail[osdNumberOfPriorities];
   #else
      osQEntryCountType ossQReadyTaskHead[1];
      osQEntryCountType ossQReadyTaskTail[1];
   #endif
#else
   #if(osdNumberOfPriorities > 0)
      TaskType ossQReadyTask[osdNumberOfPriorities];
   #else
      TaskType ossQReadyTask[1];
   #endif
#endif
#if(osdRTSize > 1)
   osPrioFlagType ossQReadyPrios[osdRTSize];
#else
   osPrioFlagType ossQReadyPrios;
#endif
}osCtrlVarsLockNeededType;

typedef struct
{

   osuint8 ossIntNestingDepth;
   TaskType ossActiveTaskIndex;
   ISRType ossActiveISRID;
   osuint8 ossIntSaveDisableCounter;
   osuint8 ossIntSaveDisableCounterGlobal;
   #if(STATUS_LEVEL == EXTENDED_STATUS)
   volatile osuint8 ossIntAPIStatus;
   #endif
   #if(osdNumberOfApplications > 0)
   ApplicationType ossActiveApplicationID;
   #endif

   volatile osuint8 ossCallDispatcher;

   osPrioType ossActiveTaskPrio;
   osIntLevelType ossSavedIntLevel;
   osIntLevelType ossSavedIntLevelNested;
   osbool ossStarted;

   osuint32 ossSavedIntDisFlag;
   osuint32 ossSavedIntDisFlagNested;

#if(osdFullPreempt || osdMixedPreempt)
   volatile osDispatcherLockType ossLockDispatcher;
#endif
#if osdExceptionDetails
   osint16 ossISRUnhandledException_Number;
#endif
#if((osdSC == SC3) || (osdSC == SC4))
   osuint16 ossCurrentContext;
   osuint32 ossIsInUserMode;
   osuint8  ossInSystemFct;
#endif
#if(osdNumberOfApplications > 0)
   volatile osbool ossInApplHook;
#endif

#if STATUS_LEVEL == EXTENDED_STATUS
   osResCounterType ossResGlobalOccupationCounter;
  #if(osdNumberOfInterruptResources > 0)
   osIntLevelType ossInitialIntLevel;
  #endif
#endif
#if(osdParameterAccessMacros && osdErrorHook)
   osAPIParam1Type ossAPIParam1;
   osAPIParam2Type ossAPIParam2;
   osAPIParam3Type ossAPIParam3;
   osuint32 * osqPRAM3 ossAPIParam4;
#endif

#if osdStackCheck
   TaskType ossLastActiveTaskIndex;
#endif

#if osdORTIDebug
   volatile osuint8 ossORTICurrentServiceId;
#endif

#if(osdErrorHook!=0)
   #if osdORTIDebug
      StatusType ossLastErrorCode;
   #endif
   volatile osuint16 ossLastError;
   osbool ossErrorFlag;
#endif

   #if osdExceptionDetails
   osuint32 ossUnhandledExceptionDetail;
   #endif

}osCtrlVarsNoLockNeededType;

typedef struct
{
   volatile osCtrlVarsLockNeededType    LockIsNeeded;
   osCtrlVarsNoLockNeededType  LockIsNotNeeded;
} osCtrlVarType;

#define ptrToCcb (&osOwnCcb->LockIsNeeded)

#define osOwnCcb (osConfigBlock.CcbAddress[osSysGetCoreID()])

#define osdCounterInternalMaximumValue(x) (oskCounterInternalMaximumValue[x])

typedef struct {

   osuint8  aucMagicNumber[4];
   osuint16 uiLength;
   osuint16 uiHardwareID;
   osuint8  ucMajorVersion;
   osuint8  ucMinorVersion;
   osuint16 uiConfigVersion;
   osuint16 uiUserConfigVersion;

   const void*                      uiStartAddressConfigBlock;

   const void*                      uiStartAddressSubCont0;
   const osTaskFctType*             uiStartAddressTaskStartAddress;
   const osuint8*                   uiStartAddressTaskPreemptive;
   const osuint8*                   uiStartAddressTaskTrusted;
   const osStackPtrType*            uiStartAddressTaskStackStartAddress;
   const osStackPtrType*            uiStartAddressTaskStackEndAddress;
   const osuint8*                   uiStartAddressTaskToAppl;
   const osuint8*                   uiStartAddressIsrTrusted;
   const osuint8*                   uiStartAddressIsrToAppl;
   const osuint8*                   StartAddressApplTrusted;
   const osuint8*                   StartAddressTrustedFunctions;
   const osuint8*                   StartAddressNonTrustedFunctions;
   const osIsrFctType*              StartAddresscat2IsrStartAddress;
   const osuint8*                   StartAddressIsrNestable;
   const CoreIdType*                StartAddressProcessToCore;
   const CoreIdType*                StartAddressAlarmToCore;
   const CoreIdType*                StartAddressResourceToCore;
   const CoreIdType*                StartAddressCounterToCore;
   const CoreIdType*                StartAddressScheduleTableToCore;
   const CoreIdType*                StartAddressApplicationToCore;
   const CoreIdType*                StartAddressTrustedFunctionToCore;
   const CoreIdType*                StartAddressNonTrustedFunctionToCore;
   osCtrlVarType* const *           StartAddressCcbAddress;
   const osuint8*                   StartAddressPeripheralRegions;

   const osStackType*               StartAddressCat2IsrStacks;
   const osuint16* const            StartAddrISRChannel;
   const osuint16* const            StartAddrISRPrioLevel;
   const osuint8* const             StartAddrIsrToCore;

   osuint16 uiNumberOfTasks;
   osuint16 uiNumberOfCat2ISRs;
   osuint16 uiNumberOfTrustedFunctions;
   osuint16 uiNumberOfNonTrustedFunctions;
   osuint16 uiNumberOfApplications;
   osuint16 uiNumberOfPeripheralRegions;
   osuint8  ucStackUsageMeasurement;
   osuint16 NumberOfAlarms;
   osuint16 NumberOfAllResources;
   osuint16 NumberOfAvailableCores;
   osuint16 NumberOfCounters;
   osuint16 NumberOfProcesses;
   osuint16 NumberOfScheduleTables;

      osStackType SystemStack[osdNumberOfAvailableCores];

   osTaskFctType              aulTaskStartAddress[osdNumberOfAllTasks+1];

   osuint8                    aucTaskPreemptive[osdNumberOfAllTasks+1];

   osuint8                    aucTaskTrusted[osdNumberOfAllTasks+1];

   osStackPtrType             aulTaskStackStartAddress[osdNumberOfAllTasks+1];

   const osStackPtrType       aulTaskStackEndAddress[osdNumberOfAllTasks+1];

   osuint8                    acTaskToAppl[osdNumberOfAllTasks+1];

   osuint8                    aucIsrTrusted[osdNumberOfCat2ISRs+1];

   osuint8                    acIsrToAppl[osdNumberOfCat2ISRs+1];

   osuint8                    applTrusted[osdNumberOfApplications+1];

   osuint8                    trustedFunctions[1];

   osuint8                    nonTrustedFunctions[1];

   osIsrFctType               cat2IsrStartAddress[osdNumberOfCat2ISRs+1];

   osuint8                    IsrNestable[osdNumberOfCat2ISRs+1];

   CoreIdType                 ProcessToCore[osdNumberOfProcesses+1];

   CoreIdType                 AlarmToCore[osdNumberOfAlarms+1];

   CoreIdType                 ResourceToCore[osdNumberOfAllResources+1];

   CoreIdType                 CounterToCore[osdNumberOfCounters+1];

   CoreIdType                 ScheduleTableToCore[osdNumberOfScheduleTables+1];

   CoreIdType                 ApplicationToCore[osdNumberOfApplications+1];

   CoreIdType                 TrustedFunctionToCore[osdNumberOfTrustedFunctions+1];

   CoreIdType                 NonTrustedFunctionToCore[1];

   osCtrlVarType* const       CcbAddress[osdNumberOfAvailableCores+1];

   osuint8                    peripheralRegions[1];

   osStackType                osCat2IsrStacks[osdNumberOfCat2ISRs+1];

   const osuint16             osIsrChannel[osdNumberOfAllISRs+1];

   const osuint16             osIsrPrioLevel[osdNumberOfAllISRs+1];

   const osuint8              osIsrToCore[osdNumberOfAllISRs+1];

   osuint32 uiCheckSum;

} tsConfigBlock;

extern const tsConfigBlock osConfigBlock;

#if osdORTIDebug
 #define osdTestMacros 1
#endif

#ifndef osdTestMacros
 #if defined USE_QUOTE_INCLUDES
  #include "emptymac.h"
 #else
  #include <emptymac.h>
 #endif
#else
 #if(osdTestMacros == 1)
  #if defined USE_QUOTE_INCLUDES
   #include "testmac1.h"
  #else
   #include <testmac1.h>
  #endif
 #endif
 #if(osdTestMacros == 3)
  #if defined USE_QUOTE_INCLUDES
   #include "testmac3.h"
  #else
   #include <testmac3.h>
  #endif
 #endif
 #if(osdTestMacros == 4)
  #if defined USE_QUOTE_INCLUDES
   #include "testmac4.h"
  #else
   #include <testmac4.h>
  #endif
 #endif
#endif

#define osdDummyRead(x)   if((x)!=0){__asm("NOP");}

osqRAM0 extern osqRAM1 volatile osqRAM2 AppModeType osqRAM3 osActiveAppMode;

osqFunc1 void osqFunc2 osAbortSystem(osuint16 uiError);

osqFunc1 void osqFunc2 osUnrecoverableError(StatusType StdErrorCode, osuint16 osOsekErrorCode);

#if(osdKillTaskIsrPossible || (osdSC == SC3) || (osdSC == SC4))
 #if(osdNumberOfAllResources > 0)
 #if(!defined(osdGetResourceNotUsed)) || (!defined(osdReleaseResourceNotUsed))
  osqFunc1 void osqFunc2 osSysKillResourceList(ResourceType ResId);
 #endif
 #endif
#endif

#ifndef osdActivateTaskNotUsed
#if((osdSC== SC3) || (osdSC== SC4))

#define ActivateTask(x) (osPsysActivateTask(x))

#else
#define ActivateTask(x) (osActivateTask(x))
#endif
#endif

#ifndef osdTerminateTaskNotUsed
#if((osdSC== SC3) || (osdSC== SC4))
#define TerminateTask() osPsysTerminateTask()
#else
#define TerminateTask() osTerminateTask()
#endif
#endif

#ifndef osdChainTaskNotUsed
#if((osdSC== SC3) || (osdSC== SC4))
#define ChainTask(x) (osPsysChainTask(x))
#else
#define ChainTask(x) (osChainTask(x))
#endif
#endif

#ifndef osdScheduleNotUsed
#if((osdSC== SC3) || (osdSC== SC4))
#define Schedule() osPsysSchedule()
#else
#define Schedule() osSchedule()
#endif
#endif

#ifndef osdGetTaskIDNotUsed
#if((osdSC== SC3) || (osdSC== SC4))
#define GetTaskID(x) (osPsysGetTaskID(x))
#else
#define GetTaskID(x) (osGetTaskID(x))
#endif
#endif

#ifndef osdGetTaskStateNotUsed
#if((osdSC== SC3) || (osdSC== SC4))
#define GetTaskState(x, y) (osPsysGetTaskState((x), (y)))
#else
#define GetTaskState(x, y) (osGetTaskState((x), (y)))
#endif
#endif

#ifndef osdActivateTaskNotUsed
osqFunc1 StatusType osqFunc2 osActivateTask( TaskType taskIndex);
#endif
#ifndef osdTerminateTaskNotUsed
osqFunc1 StatusType osqFunc2 osTerminateTask ( void );
#endif
#ifndef osdChainTaskNotUsed
osqFunc1 StatusType osqFunc2 osChainTask ( TaskType taskIndex );
#endif
#ifndef osdScheduleNotUsed
osqFunc1 StatusType osqFunc2 osSchedule ( void );
#endif
#ifndef osdGetTaskIDNotUsed
osqFunc1 StatusType osqFunc2 osGetTaskID ( TaskRefType TaskId);
#endif
#ifndef osdGetTaskStateNotUsed
osqFunc1 StatusType osqFunc2 osGetTaskState(TaskType TaskId, TaskStateRefType State);
#endif

osqFunc1 void osqFunc2 osAssertFailed(void);

osqFunc1 void osqFunc2 osInitStacks(void);
osqFunc1 void osqFunc2 osInitINTC(void);
osqFunc1 void osqFunc2 osInitMPU(void);
osqFunc1 osuint16 osqFunc2 osGetConfigBlockVersion(void);

#define ptrToCcb2            (&osOwnCcb->LockIsNotNeeded)

#define osReadICR8(addr)   (*(volatile osuint8*)(addr))
#define osReadICR16(addr)  (*(volatile osuint16*)(addr))

#define osReadIMR8(addr)   (*(volatile osuint8*)(addr))
#define osReadIMR16(addr)  (*(volatile osuint16*)(addr))
#define osReadIMR32(addr)  (*(volatile osuint32*)(addr))

#define osdICRMaskBit    (osuint16)0x0080U
#define osdICRTableBit   (osuint16)0x0040U

#define osdIntMaxIndex   osdNumberOfInterrupts-1

#define osdEIBD0         0xFFFEEB00UL
#define osdEIBD1         0xFFFFB800UL

#define osSetEIBD1(x)    (*((volatile osuint32*)(osdEIBD1 + ((x)*4))))

#define osdIPIR_BASE              0xFFFEEC80UL
#define osdIPIR_CHANNEL(channel)  (osdIPIR_BASE + (4 * (channel)))
#define osdSetIPIR(channel, core) ((*((volatile osuint32*)osdIPIR_CHANNEL(channel))) = (core))

#define osdICRADDR(x)           (((x)<32)?((osdICRBASE0)+((x)*2)):((osdICRBASE1)+((x)*2)))
#define osdICRxLo(x)            (*((volatile osuint8*)(osdICRADDR(x))))
#define osdICRxHi(x)            (*((volatile osuint8*)(osdICRADDR(x)+1)))
#define osdICRx16(x)            (*((volatile osuint16*)(osdICRADDR(x))))

#define osGetICRx8Lo(x)         osdICRxLo(x)
#define osGetICRx8Hi(x)         osdICRxHi(x)
#define osGetICRx16(x)          osdICRx16(x)

#define osWriteICRxLo(x, val)    (osdICRxLo(x)=(val))
#define osWriteICRxHi(x, val)    (osdICRxHi(x)=(val))
#define osWriteICRx16(x, val)    (osdICRx16(x)=(val))

#define osGetPMR()                osAsmGetPMR()
#define osDisableInterrupt(x)     osSetICRxMask(osdICRADDR(x))
#define osEnableInterrupt(x)      osClearICRxMask(osdICRADDR(x))

#define osSysDisableInterruptSource(x)  osDisableInterrupt(x)
#define osSysEnableInterruptSource(x)   osEnableInterrupt(x)

#if(osdNumberOfPrioLevels == 8)
#define osdPMRMask         0xFF
#define osdPMRHiBit        0x100
#else
#define osdPMRMask         0xFFFF
#define osdPMRHiBit        0x10000
#endif

#define osDisableGlobal()        __asm("DI")
#define osEnableGlobal()         __asm("EI")
#define osEnableLevel()          osSetTaskLevel()
#define osDisableLevel()         osSetSystemLevel()

#define osGetInitialLevel()      osGetLevelISPR()
#define osSetLevel(x)            osSetLevelPMR(x)
#define osGetLevel()             osGetLevelPMR()

#define osCheckInterruptsDisabled()  (osCheckIntDisabled())
#define osCheckInterruptsEnabled()   (!osCheckIntDisabled())

#define osSaveDisableGlobal()         ptrToCcb2->ossSavedIntDisFlag=osGetDisableGlobal();
#define osRestoreEnableGlobal()       if(ptrToCcb2->ossSavedIntDisFlag==0){osEnableGlobal();}

#define osSaveDisableLevel()          ptrToCcb2->ossSavedIntLevel=osGetDisableLevel();
#define osRestoreEnableLevel()        osRestoreLevel();

#define osRTEDisableLevel()   osDisableLevel()
#define osRTEEnableLevel()    osEnableLevel()

 #define osRTEDisableGlobal()  osDisableGlobal()
 #define osRTEEnableGlobal()   osEnableGlobal()

#ifndef osdEnableAllInterruptsNotUsed
osqFunc1 void osqFunc2 osEnableAllInterrupts(void);
#endif

#ifndef osdDisableAllInterruptsNotUsed
osqFunc1 void osqFunc2 osDisableAllInterrupts(void);
#endif

#ifndef osdResumeOSInterruptsNotUsed
osqFunc1 void osqFunc2 osResumeOSInterrupts(void);
#endif

#ifndef osdSuspendOSInterruptsNotUsed
osqFunc1 void osqFunc2 osSuspendOSInterrupts(void);
#endif

#ifndef osdResumeAllInterruptsNotUsed
osqFunc1 void osqFunc2 osResumeAllInterrupts(void);
#endif

#ifndef osdSuspendAllInterruptsNotUsed
osqFunc1 void osqFunc2 osSuspendAllInterrupts(void);
#endif

#if((osdSC== SC3) || (osdSC== SC4))

#if(((osdNumberOfAllTasks > 0) && !defined(osdActivateTaskNotUsed)))

StatusType osPsysActivateTask(TaskType Param0taskIndex);
#endif

#if(((osdNumberOfAllTasks > 0) && !defined(osdChainTaskNotUsed)))
StatusType osPsysChainTask(TaskType Param0taskIndex);
#endif

#if(((osdNumberOfAllTasks > 0) && !defined(osdGetTaskIDNotUsed)))
StatusType osPsysGetTaskID(TaskRefType Param0TaskId);
#endif

#if(((osdNumberOfAllTasks > 0) && !defined(osdGetTaskStateNotUsed)))
StatusType osPsysGetTaskState(TaskType Param0TaskId, TaskStateRefType Param1State);
#endif

#if((((osdNumberOfAllResources - osdNumberOfInternalResources) > 0) && !defined(osdGetResourceNotUsed)))
StatusType osPsysGetResource(ResourceType Param0ResId);
#endif

#if((((osdNumberOfAllResources - osdNumberOfInternalResources) > 0) && !defined(osdReleaseResourceNotUsed)))
StatusType osPsysReleaseResource(ResourceType Param0ResId);
#endif

#if((((CC == ECC1) || (CC == ECC2)) && (osdNumberOfExtendedTasks > 0) && !defined(osdSetEventNotUsed)))

StatusType osPsysSetEvent(TaskType Param0taskIndex, EventMaskType Param1setMask);
#endif

#if((((CC == ECC1) || (CC == ECC2)) && (osdNumberOfExtendedTasks > 0) && !defined(osdClearEventNotUsed)))
StatusType osPsysClearEvent(EventMaskType Param0Mask);
#endif

#if((((CC == ECC1) || (CC == ECC2)) && (osdNumberOfExtendedTasks > 0) && !defined(osdGetEventNotUsed)))
StatusType osPsysGetEvent(TaskType Param0taskIndex, EventMaskRefType Param1Event);
#endif

#if((((CC == ECC1) || (CC == ECC2)) && (osdNumberOfExtendedTasks > 0) && !defined(osdWaitEventNotUsed)))
StatusType osPsysWaitEvent(EventMaskType Param0Mask);
#endif

#if(((osdNumberOfAlarms > 0) && !defined(osdGetAlarmBaseNotUsed)))
StatusType osPsysGetAlarmBase(AlarmType Param0AlarmId, AlarmBaseRefType Param1Info);
#endif

#if(((osdNumberOfAlarms > 0) && !defined(osdGetAlarmNotUsed)))
StatusType osPsysGetAlarm(AlarmType Param0alarmID, TickRefType Param1diffTickTime);
#endif

#if(((osdNumberOfAlarms > 0) && !defined(osdSetRelAlarmNotUsed)))
StatusType osPsysSetRelAlarm(AlarmType Param0alarmID, TickType Param1deltaTicks, TickType Param2cycle);
#endif

#if(((osdNumberOfAlarms > 0) && !defined(osdSetAbsAlarmNotUsed)))
StatusType osPsysSetAbsAlarm(AlarmType Param0alarmID, TickType Param1start, TickType Param2cycle);
#endif

#if(((osdNumberOfAlarms > 0) && !defined(osdCancelAlarmNotUsed)))
StatusType osPsysCancelAlarm(AlarmType Param0alarmID);
#endif

void osPsysShutdownOS(StatusType Param0Error);

#if(((osdNumberOfScheduleTables > 0) && !defined(osdStartScheduleTableRelNotUsed)))
StatusType osPsysStartScheduleTableRel(ScheduleTableType Param0ScheduleTableID, TickType Param1Offset);
#endif

#if(((osdNumberOfScheduleTables > 0) && !defined(osdStartScheduleTableAbsNotUsed)))
StatusType osPsysStartScheduleTableAbs(ScheduleTableType Param0ScheduleTableID, TickType Param1Offset);
#endif

#if(((osdNumberOfScheduleTables > 0) && !defined(osdNextScheduleTableNotUsed)))
StatusType osPsysNextScheduleTable(ScheduleTableType Param0ScheduleTableID_current, ScheduleTableType Param1ScheduleTableID_next);
#endif

#if(((osdNumberOfScheduleTables > 0) && !defined(osdStopScheduleTableNotUsed)))
StatusType osPsysStopScheduleTable(ScheduleTableType Param0ScheduleTableID);
#endif

#if(((osdNumberOfScheduleTables > 0) && !defined(osdGetScheduleTableStatusNotUsed)))
StatusType osPsysGetScheduleTableStatus(ScheduleTableType Param0ScheduleTableID, ScheduleTableStatusRefType Param1ScheduleStatus);
#endif

#if(((osdNumberOfSWCounters > 0) && !defined(osdIncrementCounterNotUsed)))
StatusType osPsysIncrementCounter(CounterType Param0CounterID);
#endif

#if((!defined(osdGetCounterValueNotUsed)))
StatusType osPsysGetCounterValue(CounterType Param0CounterID, TickRefType Param1Value);
#endif

#if((!defined(osdGetElapsedValueNotUsed)))
StatusType osPsysGetElapsedValue(CounterType Param0CounterID, TickRefType Param1Value, TickRefType Param2ElapsedValue);
#endif

#if(((osdNumberOfApplications > 0) && !defined(osdTerminateApplicationNotUsed)))
StatusType osPsysTerminateApplication(ApplicationType Param0Application, RestartType Param1RestartOption);
#endif

#if((((osdSC == SC3) || (osdSC == SC4)) && !defined(osdGetApplicationStateNotUsed)))
StatusType osPsysGetApplicationState(ApplicationType Param0Application, ApplicationStateRefType Param1Value);
#endif

#if((!defined(osdCallTrustedFunctionNotUsed)))
StatusType osPsysCallTrustedFunction(TrustedFunctionIndexType Param0FunctionIndex, TrustedFunctionParameterRefType Param1FunctionParams);
#endif

#if((!defined(osdCheckISRMemoryAccessNotUsed)))
AccessType osPsysCheckISRMemoryAccess(ISRType Param0ISRID, MemoryStartAddressType Param1Address, MemorySizeType Param2Size);
#endif

#if((!defined(osdCheckTaskMemoryAccessNotUsed)))
AccessType osPsysCheckTaskMemoryAccess(TaskType Param0TaskID, MemoryStartAddressType Param1Address, MemorySizeType Param2Size);
#endif

#if((!defined(osdCheckObjectAccessNotUsed)))
ObjectAccessType osPsysCheckObjectAccess(ApplicationType Param0ApplID, ObjectTypeType Param1ObjectType, ObjectIDType Param2ObjectID);
#endif

#if((!defined(osdCheckObjectOwnershipNotUsed)))

ApplicationType osPsysCheckObjectOwnership(ObjectTypeType Param0ObjectType, ObjectIDType Param1ObjectID);
#endif

#if(((osdTimingProtectionUsed) && (osdTimingMeasurement) && !defined(osdosGetTaskMaxExecutionTimeNotUsed)))
StatusType osPsysosGetTaskMaxExecutionTime(TaskType Param0TaskID, osTPTimeRefType Param1MaxTime);
#endif

#if(((osdTimingProtectionUsed) && (osdTimingMeasurement) && !defined(osdosGetISRMaxExecutionTimeNotUsed)))
StatusType osPsysosGetISRMaxExecutionTime(ISRType Param0ISRID, osTPTimeRefType Param1MaxTime);
#endif

#if(((osdTimingProtectionUsed) && (osdTimingMeasurement) && !defined(osdosGetTaskMaxBlockingTimeNotUsed)))
StatusType osPsysosGetTaskMaxBlockingTime(TaskType Param0TaskID, BlockTypeType Param1BlockType, ResourceType Param2ResourceID, osTPTimeRefType Param3MaxTime);
#endif

#if(((osdTimingProtectionUsed) && (osdTimingMeasurement) && !defined(osdosGetISRMaxBlockingTimeNotUsed)))
StatusType osPsysosGetISRMaxBlockingTime(ISRType Param0ISRID, BlockTypeType Param1BlockType, ResourceType Param2ResourceID, osTPTimeRefType Param3MaxTime);
#endif

#if(((osdTimingProtectionUsed) && (osdTimingMeasurement) && !defined(osdosGetTaskMinInterArrivalTimeNotUsed)))
StatusType osPsysosGetTaskMinInterArrivalTime(TaskType Param0TaskID, osTPTimeStampRefType Param1MinTime);
#endif

#if(((osdTimingProtectionUsed) && (osdTimingMeasurement) && !defined(osdosGetISRMinInterArrivalTimeNotUsed)))
StatusType osPsysosGetISRMinInterArrivalTime(ISRType Param0ISRID, osTPTimeStampRefType Param1MinTime);
#endif

#if(((osdNumberOfAllTasks > 0) && !defined(osdTerminateTaskNotUsed)))
StatusType osPsysTerminateTask(void);
#endif

#if(((osdNumberOfAllTasks > 0) && !defined(osdScheduleNotUsed)))
StatusType osPsysSchedule(void);
#endif

#if(!defined(osdGetActiveApplicationModeNotUsed))
AppModeType osPsysGetActiveApplicationMode(void);
#endif

#if(!defined(osdGetISRIDNotUsed))
ISRType osPsysGetISRID(void);
#endif

#if((!defined(osdDisableAllInterruptsNotUsed)))
void osPsysDisableAllInterrupts(void);
#endif

#if((!defined(osdEnableAllInterruptsNotUsed)))
void osPsysEnableAllInterrupts(void);
#endif

#if((!defined(osdSuspendAllInterruptsNotUsed)))
void osPsysSuspendAllInterrupts(void);
#endif

#if((!defined(osdResumeAllInterruptsNotUsed)))
void osPsysResumeAllInterrupts(void);
#endif

#if((!defined(osdSuspendOSInterruptsNotUsed)))
void osPsysSuspendOSInterrupts(void);
#endif

#if((!defined(osdResumeOSInterruptsNotUsed)))
void osPsysResumeOSInterrupts(void);
#endif

#if((((osdSC == SC3) || (osdSC == SC4)) && !defined(osdAllowAccessNotUsed)))
StatusType osPsysAllowAccess(void);
#endif

void osPsysCallApplStartupHook(ApplicationType Param0applID);

void osPsysCallApplErrorHook(StatusType Param0ErrorCode, ApplicationType Param1applID);

void osPsysCallApplShutdownHook(StatusType Param0Error, ApplicationType Param1applID);

#endif

#define osdIntAPIDisableAll 0x80U

#if(STATUS_LEVEL == EXTENDED_STATUS)
   #define osSetIntAPIStatus(x) (osOwnCcb->LockIsNotNeeded.ossIntAPIStatus = (x))
   #define osIncIntAPIStatus() (osOwnCcb->LockIsNotNeeded.ossIntAPIStatus++)
   #define osDecIntAPIStatus() (osOwnCcb->LockIsNotNeeded.ossIntAPIStatus--)
#else
   #define osSetIntAPIStatus(x)
   #define osIncIntAPIStatus()
   #define osDecIntAPIStatus()
#endif

#ifndef osdEnableAllInterruptsNotUsed
   #if((osdSC == SC2) ||  (osdSC == SC1))
      #define EnableAllInterrupts() (osEnableAllInterrupts())
   #else
      #define EnableAllInterrupts() (osPsysEnableAllInterrupts())
   #endif
#endif

#ifndef osdDisableAllInterruptsNotUsed
   #if((osdSC == SC2) || (osdSC == SC1))
      #define DisableAllInterrupts() (osDisableAllInterrupts())
   #else
      #define DisableAllInterrupts() (osPsysDisableAllInterrupts())
   #endif
#endif

#ifndef osdResumeOSInterruptsNotUsed
   #if((osdSC== SC2) || (osdSC== SC1))
      #define ResumeOSInterrupts() (osResumeOSInterrupts())
   #else
      #define ResumeOSInterrupts() (osPsysResumeOSInterrupts())
   #endif
#endif

#ifndef osdSuspendOSInterruptsNotUsed
   #if((osdSC == SC2) || (osdSC == SC1))
      #define SuspendOSInterrupts() (osSuspendOSInterrupts())
   #else
      #define SuspendOSInterrupts() (osPsysSuspendOSInterrupts())
   #endif
#endif

#ifndef osdResumeAllInterruptsNotUsed
   #if((osdSC== SC2) || (osdSC== SC1))
      #define ResumeAllInterrupts() (osResumeAllInterrupts())
   #else
      #define ResumeAllInterrupts() (osPsysResumeAllInterrupts())
   #endif
#endif

#ifndef osdSuspendAllInterruptsNotUsed
   #if((osdSC == SC2) || (osdSC == SC1))
      #define SuspendAllInterrupts() (osSuspendAllInterrupts())
   #else
      #define SuspendAllInterrupts() (osPsysSuspendAllInterrupts())
   #endif
#endif

#ifndef osdGetResourceNotUsed
#if((osdSC== SC3) || (osdSC== SC4))
#define GetResource(x) (osPsysGetResource(x))
#else
#define GetResource(x) (osGetResource(x))
#endif
#endif

#ifndef osdReleaseResourceNotUsed
#if((osdSC== SC3) || (osdSC== SC4))
#define ReleaseResource(x) (osPsysReleaseResource(x))
#else
#define ReleaseResource(x) (osReleaseResource(x))
#endif
#endif

#ifndef osdGetResourceNotUsed
osqFunc1 StatusType osqFunc2 osGetResource(ResourceType ResId);
#endif

#ifndef osdReleaseResourceNotUsed
osqFunc1 StatusType osqFunc2 osReleaseResource(ResourceType ResId);
#endif

#ifndef osdGetSemaphoreNotUsed
#if((osdSC== SC3) || (osdSC== SC4))
#define GetSemaphore(x) (osPsysGetSemaphore(x))
#else
#define GetSemaphore(x) (osGetSemaphore(x))
#endif
#endif

#ifndef osdReleaseSemaphoreNotUsed
#if((osdSC== SC3) || (osdSC== SC4))
#define ReleaseSemaphore(x) (osPsysReleaseSemaphore(x))
#else
#define ReleaseSemaphore(x) (osReleaseSemaphore(x))
#endif
#endif

#ifndef osdGetSemaphoreNotUsed
osqFunc1 StatusType osqFunc2 osGetSemaphore(osSemaphoreType SemaId);
#endif
#ifndef osdReleaseSemaphoreNotUsed
osqFunc1 StatusType osqFunc2 osReleaseSemaphore(osSemaphoreType SemaId);
#endif

#if(CC == ECC1) || (CC == ECC2)

#ifndef osdSetEventNotUsed
#if((osdSC== SC3) || (osdSC== SC4))
#define SetEvent(x, y) (osPsysSetEvent((x), (y)))
#else
#define SetEvent(x, y) (osSetEvent((x), (y)))
#endif
#endif

#ifndef osdGetEventNotUsed
#if((osdSC== SC3) || (osdSC== SC4))
#define GetEvent(x, y) (osPsysGetEvent((x), (y)))
#else
#define GetEvent(x, y) (osGetEvent((x), (y)))
#endif
#endif

#ifndef osdClearEventNotUsed
#if((osdSC== SC3) || (osdSC== SC4))
#define ClearEvent(x) (osPsysClearEvent(x))
#else
#define ClearEvent(x) (osClearEvent(x))
#endif
#endif

#ifndef osdWaitEventNotUsed
#if((osdSC== SC3) || (osdSC== SC4))
#define WaitEvent(x) (osPsysWaitEvent(x))
#else
#define WaitEvent(x) (osWaitEvent(x))
#endif
#endif

#ifndef osdSetEventNotUsed
osqFunc1 StatusType osqFunc2 osSetEvent(TaskType taskIndex, EventMaskType setMask);
#endif

#ifndef osdClearEventNotUsed
osqFunc1 StatusType osqFunc2 osClearEvent (EventMaskType Mask );
#endif

#ifndef osdGetEventNotUsed
osqFunc1 StatusType osqFunc2 osGetEvent(TaskType taskIndex, EventMaskRefType Event);
#endif

#ifndef osdWaitEventNotUsed
osqFunc1 StatusType osqFunc2 osWaitEvent(EventMaskType mask);
#endif

#else

#ifndef osdSetEventNotUsed
#define SetEvent(x, y) (Event API used with wrong conformance class)
#endif
#ifndef osdClearEventNotUsed
#define ClearEvent(x) (Event API used with wrong conformance class)
#endif
#ifndef osdGetEventNotUsed
#define GetEvent(x, y) (Event API used with wrong conformance class)
#endif
#ifndef osdWaitEventNotUsed
#define WaitEvent(x)   (Event API used with wrong conformance class)
#endif

#endif

#ifndef osdGetAlarmBaseNotUsed
#if((osdSC== SC3) || (osdSC== SC4))
#define GetAlarmBase(x, y) (osPsysGetAlarmBase((x), (y)))
#else
#define GetAlarmBase(x, y) (osGetAlarmBase((x), (y)))
#endif
#endif

#ifndef osdSetRelAlarmNotUsed
#if(osdNumberOfAlarms > 0)

#if((osdSC== SC3) || (osdSC== SC4))
#define SetRelAlarm(x, y, z) (osPsysSetRelAlarm((x), (y), (z)))
#else
#define SetRelAlarm(x, y, z) (osSetRelAlarm((x), (y), (z)))
#endif

#else
#if((osdSC== SC3) || (osdSC== SC4))
#define SetRelAlarm(x, y, z) (osPsysSetRelAlarm(x))
#else
#define SetRelAlarm(x, y, z) (osSetRelAlarm(x))
#endif
#endif
#endif

#ifndef osdSetAbsAlarmNotUsed
#if(osdNumberOfAlarms > 0)

#if((osdSC== SC3) || (osdSC== SC4))
#define SetAbsAlarm(x, y, z) (osPsysSetAbsAlarm((x), (y), (z)))
#else
#define SetAbsAlarm(x, y, z) (osSetAbsAlarm((x), (y), (z)))
#endif

#else
#if((osdSC== SC3) || (osdSC== SC4))
#define SetAbsAlarm(x, y, z) (osPsysSetAbsAlarm(x))
#else
#define SetAbsAlarm(x, y, z) (osSetAbsAlarm(x))
#endif
#endif
#endif

#ifndef osdCancelAlarmNotUsed
#if((osdSC== SC3) || (osdSC== SC4))
#define CancelAlarm(x) (osPsysCancelAlarm(x))
#else
#define CancelAlarm(x) (osCancelAlarm(x))
#endif
#endif

#if(osdNumberOfAlarmIncrementCounter > 0) || !defined(osdIncrementCounterNotUsed)

#if((osdSC== SC3) || (osdSC== SC4))
#define IncrementCounter(x) (osPsysIncrementCounter(x))
#else
#define IncrementCounter(x) (osIncrementCounter(x))
#endif

#endif

#ifndef osdGetCounterValueNotUsed

 #if((osdSC == SC3) || (osdSC == SC4))
  #define GetCounterValue(x, y) (osPsysGetCounterValue((x), (y)))
 #else
  #define GetCounterValue(x, y) (osGetCounterValue((x), (y)))
 #endif

#endif

#ifndef osdGetElapsedValueNotUsed
 #define GetElapsedCounterValue(x,y,z) GetElapsedValue((x),(y),(z))

 #if((osdSC == SC3) || (osdSC == SC4))
  #define GetElapsedValue(x, y, z) (osPsysGetElapsedValue((x), (y), (z)))
 #else
  #define GetElapsedValue(x, y, z) (osGetElapsedValue((x), (y), (z)))
 #endif

#endif

#ifndef osdGetAlarmNotUsed
#if((osdSC== SC3) || (osdSC== SC4))
#define GetAlarm(x, y) (osPsysGetAlarm((x), (y)))
#else
#define GetAlarm(x, y) (osGetAlarm((x), (y)))
#endif
#endif

#ifndef osdStartScheduleTableRelNotUsed
#if((osdSC== SC3) || (osdSC== SC4))
#define StartScheduleTableRel(x, y) osPsysStartScheduleTableRel((x), (y))
#else
#define StartScheduleTableRel(x, y) osStartScheduleTableRel((x), (y))
#endif
#endif

#ifndef osdStartScheduleTableAbsNotUsed
#if((osdSC== SC3) || (osdSC== SC4))
#define StartScheduleTableAbs(x, y) osPsysStartScheduleTableAbs((x), (y))
#else
#define StartScheduleTableAbs(x, y) osStartScheduleTableAbs((x), (y))
#endif
#endif

#ifndef osdStopScheduleTableNotUsed
#if((osdSC== SC3) || (osdSC== SC4))
#define StopScheduleTable(x) osPsysStopScheduleTable((x))
#else
#define StopScheduleTable(x) osStopScheduleTable((x))
#endif
#endif

#ifndef osdNextScheduleTableNotUsed
#if((osdSC== SC3) || (osdSC== SC4))
#define NextScheduleTable(x, y) osPsysNextScheduleTable((x), (y))
#else
#define NextScheduleTable(x, y) osNextScheduleTable((x), (y))
#endif
#endif

#ifndef osdGetScheduleTableStatusNotUsed
#if((osdSC== SC3) || (osdSC== SC4))
#define GetScheduleTableStatus(x, y) osPsysGetScheduleTableStatus((x), (y))
#else
#define GetScheduleTableStatus(x, y) osGetScheduleTableStatus((x), (y))
#endif
#endif

#ifndef osdGetAlarmBaseNotUsed
osqFunc1 StatusType osqFunc2 osGetAlarmBase(AlarmType AlarmId, AlarmBaseRefType Info);
#endif

#ifndef osdSetRelAlarmNotUsed

#if(osdNumberOfAlarms > 0)
osqFunc1 StatusType osqFunc2 osSetRelAlarm(AlarmType alarmID,
                                           TickType deltaTicks,
                                           TickType cycle);
#endif

#endif

#ifndef osdSetAbsAlarmNotUsed

#if(osdNumberOfAlarms > 0)
osqFunc1 StatusType osqFunc2 osSetAbsAlarm(AlarmType alarmID,
                                           TickType start,
                                           TickType cycle);
#endif

#endif

#ifndef osdCancelAlarmNotUsed
osqFunc1 StatusType osqFunc2 osCancelAlarm(AlarmType alarmID);
#endif

#if(osdNumberOfAlarmIncrementCounter > 0) || !defined(osdIncrementCounterNotUsed)
osqFunc1 StatusType osqFunc2 osIncrementCounter(CounterType CounterID);
#endif

#ifndef osdGetCounterValueNotUsed
osqFunc1 StatusType osqFunc2 osGetCounterValue(CounterType CounterID, TickRefType Value);
#endif

#ifndef osdGetElapsedValueNotUsed
osqFunc1 StatusType osqFunc2 osGetElapsedValue(CounterType CounterID, TickRefType Value, TickRefType ElapsedValue);
#endif

#ifndef osdGetAlarmNotUsed
osqFunc1 StatusType osqFunc2 osGetAlarm(AlarmType alarmID, TickRefType diffTickTime);
#endif

#ifndef osdStartScheduleTableRelNotUsed
osqFunc1 StatusType osqFunc2 osStartScheduleTableRel(ScheduleTableType ScheduleTableID, TickType Offset);
#endif
#ifndef osdStartScheduleTableAbsNotUsed
osqFunc1 StatusType osqFunc2 osStartScheduleTableAbs(ScheduleTableType ScheduleTableID, TickType Tickvalue);
#endif

#ifndef osdNextScheduleTableNotUsed
osqFunc1 StatusType osqFunc2 osNextScheduleTable(ScheduleTableType ScheduleTableID_current, ScheduleTableType ScheduleTableID_next);
#endif
#ifndef osdGetScheduleTableStatusNotUsed
osqFunc1 StatusType osqFunc2 osGetScheduleTableStatus(ScheduleTableType ScheduleTableID, ScheduleTableStatusRefType ScheduleStatus);
#endif
#ifndef osdStopScheduleTableNotUsed
osqFunc1 StatusType osqFunc2 osStopScheduleTable(ScheduleTableType ScheduleTableID);
#endif

#define OS_STATIC_ALARM_TIME 0
#define OS_STATIC_CYCLE_TIME 0

osqFunc1 void osqFunc2 osErrorHook(StatusType ErrorCode);
osqFunc1 void osqFunc2 osShutdownOS(StatusType Error);
#if((osdSC== SC3) || (osdSC== SC4))
#define ShutdownOS(x) (osPsysShutdownOS(x))
#else
#define ShutdownOS(x) (osShutdownOS(x))
#endif

osqFunc1 void osqFunc2 osStartOSasm(void);

#define StartOS(x)                              \
   osActiveAppMode=(x);                         \
   osStartOSasm()

osqFunc1 void osqFunc2 osInitialize(void);

osqFunc1 ApplicationType osqFunc2 osGetApplicationID(void);

#define GetApplicationID()   (osGetApplicationID())

osqFunc1 AppModeType osqFunc2 osGetActiveApplicationMode(void);

#define GetActiveApplicationMode()   (osGetActiveApplicationMode())

osqFunc1 ISRType osqFunc2 osGetISRID(void);

#define GetISRID()   (osGetISRID())

osqFunc1 void osqFunc2 ErrorHook (StatusType Error);
osqFunc1 void osqFunc2 StartupHook (void);
osqFunc1 void osqFunc2 ShutdownHook (StatusType Error);

#if osdPreTaskHook
osqFunc1 void osqFunc2 PreTaskHook (void);
#endif
#if osdPostTaskHook
osqFunc1 void osqFunc2 PostTaskHook (void);
#endif

#if((osdSC == SC2) || (osdSC == SC3) || (osdSC == SC4))
ProtectionReturnType ProtectionHook(StatusType Fatalerror);
#endif

#if osdStackCheck
 #if osdStackUsageMeasurement
  osqFunc1 osStackUsageType osqFunc2 osGetStackUsage(TaskType taskId);

  osqFunc1 osStackUsageType osqFunc2 osGetISRStackUsage(ISRType isrId);
  osqFunc1 osStackUsageType osqFunc2 osGetSystemStackUsage(void);

 #endif
#endif

#if !defined osdProvideTimeStamp
#define osdProvideTimeStamp 0
#endif

typedef struct
{
   osuint8 ucMagicNumber1;
   osuint8 ucMagicNumber2;
   osuint8 ucMagicNumber3;
   osuint8 ucMagicNumber4;
   osuint8 ucSysVersionMaj;
   osuint8 ucSysVersionMin;
   osuint8 ucGenVersionMaj;
   osuint8 ucGenVersionMin;
   osuint8 ucSysVariant1;
   osuint8 ucSysVariant2;
   osuint8 ucOrtiVariant;

   osuint8 ucSpecVariant;

} osVersionVariantCodingType;

osqROM0 extern osqROM1 const osqROM2 osVersionVariantCodingType osqROM3 oskVersionVariant;

#if CC == BCC1
   #define osdVariantCC 0U
#elif CC == BCC2
   #define osdVariantCC 1U
#elif CC == ECC1
   #define osdVariantCC 2U
#elif CC == ECC2
   #define osdVariantCC 3U
#else
#error wrong conformance class
#endif

#if STATUS_LEVEL == EXTENDED_STATUS
   #define osdVariantStatus 1U
#else
   #define osdVariantStatus 0U
#endif

#if osdNonPreempt
   #define osdVariantSchedule 0U
#elif osdFullPreempt
   #define osdVariantSchedule 1U
#elif osdMixedPreempt
   #define osdVariantSchedule 2U
#else
#error wrong scheduling policy
#endif

#if osdStackCheck
   #define osdVariantStackcheck 1U
#else
   #define osdVariantStackcheck 0U
#endif

#if osdEnableAssertions
   #define osdVariantAssertionsEnabled 1U
#else
   #define osdVariantAssertionsEnabled 0U
#endif

#if(osdSC== SC1)
   #define osdVariantSC 0U
#elif(osdSC== SC2)
   #define osdVariantSC 1U
#elif(osdSC== SC3)
   #define osdVariantSC 2U
#elif(osdSC== SC4)
   #define osdVariantSC 3U
#else
#error wrong scalability class
#endif

#if(osdNumberOfScheduleTables>0)
   #define osdVariantFeaturesUsed_ST 1U
#else
   #define osdVariantFeaturesUsed_ST 0U
#endif
#if(osdNumberOfHiResSchedTabs>0)
   #define osdVariantFeaturesUsed_HRST 1U
#else
   #define osdVariantFeaturesUsed_HRST 0U
#endif
   #define osdVariantFeaturesUsed_Sync 0U
#if(osdTimingProtectionUsed)
   #define osdVariantFeaturesUsed_TP   1U
#else
   #define osdVariantFeaturesUsed_TP   0U
#endif

#if osdORTIEnabled

#define osdVariantORTIVersion ((((osdORTIStdVersion)/100)<<4)|(((osdORTIStdVersion)%100)/10))
#define osdVariantORTIDebug osdORTIDebug
#else
#define osdVariantORTIVersion 0
#define osdVariantORTIDebug   0
#endif

#define osdVariantCompiler    0
#define osdVariantDerivative  0

#if((defined(__NoFloat__)) || (defined(__SoftwareFloat__)))
   #define osdVariantFPUSupport 0
#else
   #define osdVariantFPUSupport 1
#endif

#ifndef osdTerminateApplicationNotUsed
#define osdTerminateApplicationNotUsed
#endif

#if defined USE_QUOTE_INCLUDES
 #include "osDerivatives.h"
#else
 #include <osDerivatives.h>
#endif

 #if defined USE_QUOTE_INCLUDES
  #include "tcbpost.h"
 #else
  #include <tcbpost.h>
 #endif

#if defined USE_QUOTE_INCLUDES
#include "osekasm.h"
#else
#include <osekasm.h>
#endif

#if(osdStackCheck == 1)
   #if(osdSC == SC3) || (osdSC == SC4)
      #if(osdMPUSupportInSVMode == 0)
         #define osdSoftwareStackCheck
      #endif
   #else
      #define osdSoftwareStackCheck
   #endif
#endif

#if defined __cplusplus
}
#endif

#endif

