/* Kernbauer Version: 2.16 Konfiguration: RH850 Erzeugungsgangnummer: 145 Zweig: 1 */

/*****************************************************************************
| Project Name: MICROSAR OS
|    File Name: osek.h
|
|  General code: @Version: 9.00.00@
|  Module version: $vv$=2.20
|
|  Description: contains osek prototypes and defines
|
|-----------------------------------------------------------------------------
|               C O P Y R I G H T
|-----------------------------------------------------------------------------
| Copyright (c) 2000-2015 Vector Informatik GmbH          All rights reserved.
|****************************************************************************/

/* CovComment 0:  file: osek.h */











/* MISRA RULE 19.15 VIOLATION: The QAC-Tool states a violation of rule 19.15 with 
 * message 0883 below. Anyhow, there is a double include prevention and therefore,
 * the message is considered to be wrong. */
/* double include preventer */
#ifndef _OSEK_H      /* PRQA S 0883 EOF */ /* see MISRA comment above */
#define _OSEK_H

/*lint -save Messages inhibited in this file, will be re-enabled at the end of file */
/*lint -e539 Did not expect positive indentation */

#if defined __cplusplus
extern "C"
{
#endif

/* Vector release management */
#if defined USE_QUOTE_INCLUDES
 #include "vrm.h"
#else
 #include <vrm.h>
#endif
/* KB begin vrmReleaseNumber (overwritten) */
/* Source release number */
#define osdVrmMajRelNum 1
#define osdVrmMinRelNum 1
/* KB end vrmReleaseNumber */
#if defined USE_QUOTE_INCLUDES
 #include "vrm.h"
#else
 #include <vrm.h>
#endif

/* autosar conformant information publishing */
#define OS_VENDOR_ID 30        /*Autosar/HIS vendor ID Vector-Informatik*/
#define OS_MODULE_ID 0x01

#define OS_AR_RELEASE_MAJOR_VERSION 4
#define OS_AR_RELEASE_MINOR_VERSION 0
#define OS_AR_RELEASE_REVISION_VERSION 3
/* KB begin vrmReleaseNumber (overwritten) */
/* Source release number */
#define osdVrmMajRelNum 1
#define osdVrmMinRelNum 1
/* KB end vrmReleaseNumber */
#define OS_SW_MAJOR_VERSION osdVrmMajRelNumRef
#define OS_SW_MINOR_VERSION osdVrmMinRelNumRef
/* KB begin AutosarPatchVersion (default) */
#define OS_SW_PATCH_VERSION 0
/* KB end AutosarPatchVersion */

/* KB begin osekDefaultConstants (default) */
/* defines for all conformance classes */
#define BCC1   1U
#define BCC2   2U
#define ECC1   3U
#define ECC2   4U

/* and for all scalability classes */
#define SC1    1U
#define SC2    2U
#define SC3    3U
#define SC4    4U

#define STANDARD_STATUS 0U
#define EXTENDED_STATUS 1U

#define osdFALSE 0U
#define osdTRUE  1U

#define osdNULL ((osqPROM1 osqPROM2 void osqPROM3 *)0)

/* state of tasks */
#define PRE_READY       0
#define RUNNING         1
#define WAITING         2
#define READY           3
#define SUSPENDED       4
#define WAIT_SEMAPHORE  5

/* return codes for protection hook */
#ifndef OS_SUPPRESS_PROTHOOK_OLD_RET_VALS
#define PRO_KILLTASKISR           1U
#define PRO_KILLAPPL              2U
#define PRO_KILLAPPL_RESTART      3U
#endif /*OS_SUPPRESS_PROTHOOK_OLD_RET_VALS*/
#define PRO_TERMINATETASKISR      1U
#define PRO_TERMINATEAPPL         2U
#define PRO_TERMINATEAPPL_RESTART 3U
#define PRO_SHUTDOWN              4U
#define PRO_IGNORE                5U

/* KB end osekDefaultConstants */

/* OS type definitions */
/* KB begin osTypeDefinitions (default) */
typedef unsigned char  osuint8;
typedef unsigned short osuint16;
typedef unsigned long  osuint32;
typedef signed   char  osint8;
typedef signed   short osint16;
typedef signed   long  osint32;
/* KB end osTypeDefinitions */

/* Boolean definition */
/* KB begin osekBooleanDef (overwritten) */
#ifndef osbool
 #define osbool osuint8
#endif
/* KB end osekBooleanDef */

/* Type for boolean arrays */
/* KB begin osekBooleanArrayBaseTypeDef (default) */
typedef osbool osBoolArrayBaseType;
/* KB end osekBooleanArrayBaseTypeDef */


/* Are we in a PRQA/QAC/MISRA-check? */
#ifdef PRQA_PTRDIFF_T
 /* YES: Perform some adaptations to the OS */
 /* First the general adaptations: */
 #pragma PRQA_NO_RETURN osAbortSystem
 #pragma PRQA_NO_RETURN osAssertFailed
 #pragma PRQA_NO_RETURN osSysShutdownOS

 /* Then possible plattform specific adaptations: */
 /* KB begin osekHWosPrqaAdaptation (default) */
 /* no platform specific adaptations for PRQA/QAC */
 /* KB end osekHWosPrqaAdaptation */
#endif

/* Known Compilers */
/* KB begin osekCompilerDefines (overwritten) */
/* KB end osekCompilerDefines */


   #if defined USE_QUOTE_INCLUDES
    #include "tcb.h"  /* include before */
   #else
    #include <tcb.h>  /* include before */
   #endif



/* KB begin osekStartOfHModule (overwritten) */
/* KB end osekStartOfHModule */

/* KB begin osekHwMemoryQualifierDefines (overwritten) */

/* define to nothing in the default case */

/* osqROM0 osqROM1 const osqROM2 osVersionVariantCodingType osqROM3 oskVersionVariant; */
#define osqROM0
#define osqROM1
#define osqROM2
#define osqROM3

/* extern osqPROM1 const osqPROM2 char osqPROM3 * osqROM1 const osqROM2 osqROM3 oskTcbTaskName[osdNumberOfAllTasks]; */
#define osqPROM1
#define osqPROM2
#define osqPROM3

/* osqRAM1 volatile osqRAM2 TickType osqRAM3 osSystemCounter; */
/* osqRAM1 osqRAM2 osDispatcherLockType osqRAM3 osLockDispatcher; */
#define osqRAM0
#define osqRAM1 
#define osqRAM2 
#define osqRAM3 

/* osqPRAM1 char osqPRAM2 * osqPRAM3 osActiveTaskModule; */
#define osqPRAM1
#define osqPRAM2
#define osqPRAM3

/* osqBOOL1 volatile osqBOOL2 osbool osqBOOL3 osStartDispatcher; */
#define osqBOOL1 
#define osqBOOL2 
#define osqBOOL3 

/* osqTcbRAM1 volatile osqTcbRAM2 TickType osqTcbRAM3 osCounter[5]; */
/* extern osqTcbRAM1 osqTcbRAM2 osQEntryCountType osqTcbRAM3 osQReadyTaskHead[osdNumberOfPriorities]; */
#define osqTcbRAM1 
#define osqTcbRAM2 
#define osqTcbRAM3 

/* extern (osqPTcbRAM1 osqPTcbRAM2 TaskType osqPTcbRAM3 *) osqROM1 const osqROM2 osqROM3 oskQActivationQueues[osdNumberOfPriorities]; */
#define osqPTcbRAM1 
#define osqPTcbRAM2 
#define osqPTcbRAM3 

/* osqStack1 osqStack2 osStackDataType osqStack3 osTaskStack1[80]; */
#define osqStack1
#define osqStack2
#define osqStack3

/* osqFunc1 void osqFunc2 Function1(void); */
#define osqFunc1
#define osqFunc2 

#define osqScRAM0 
#define osqScRAM1 
#define osqScRAM2 
#define osqScRAM3 
#define osqScPRAM1
#define osqScPRAM2
#define osqScPRAM3

/* qualifiers for inline functions (one qualifier for each function) */
#define osqInlineGetHighPrioBit inline
/* KB end osekHwMemoryQualifierDefines */

/* include hardware specific header files before OSEK Typedefinitions */
/* KB begin osekHWincludeHwHeaderPreTypes (overwritten) */
/* KB end osekHWincludeHwHeaderPreTypes */

#if defined USE_QUOTE_INCLUDES
 #include "osekcov.h"
 #include "osekasrt.h" /* posix types must be defined      */
 #include "osekerr.h"  /* definitions of all error numbers */
#else
 #include <osekcov.h>
 #include <osekasrt.h> /* posix types must be defined      */
 #include <osekerr.h>  /* definitions of all error numbers */
#endif

/* KB begin osekTypedDefaultConstants (default) */
#define INVALID_ISR           ((ISRType)(0xFFFFFFFFUL))
#define INVALID_TASK          ((TaskType)(0xFFFFFFFFUL))
#define INVALID_OSAPPLICATION ((ApplicationType)0xFFU)
#define INVALID_SCHEDULETABLE ((ScheduleTableType)(0xFFFFFFFFUL))
#define INVALID_PROCESS       (((osProcessType)(0xFFFFFFFFUL)))

/* TR:SASR40:6011 Start */
#define APPLICATION_ACCESSIBLE ((ApplicationStateType)1)
#define APPLICATION_RESTARTING ((ApplicationStateType)2)
#define APPLICATION_TERMINATED ((ApplicationStateType)3)
/* TR:SASR40:6011 End */

/* idle definition for task */
#define osdNoActiveTask       INVALID_TASK
/* idle definition for prio */
#define osdNoActivePrio       ((osPrioType)(0xFFFFFFFFUL))
/* idle definition for resource list */
#define osdNoResource         ((ResourceType)(0xFFFFFFFFUL))

/* idle definition for semaphore list */
#define osdNoSemaphore   ((osSemaphoreType)(0xFFFFFFFFUL))

/* KB end osekTypedDefaultConstants */
/* access rights */
#define NO_ACCESS 0U
#define ACCESS 1U


/* Schedule Table status confirms to AS 3.0 */

#define SCHEDULETABLE_STOPPED                 0U
#define SCHEDULETABLE_NEXT                    1U
#define SCHEDULETABLE_WAITING                 2U
#define SCHEDULETABLE_RUNNING                 3U
#define SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS 4U

/* values for AccessType */
#define oskAccess_None 0x0U
#define oskAccess_Read 0x1U
#define oskAccess_Write 0x2U
#define oskAccess_Execute 0x4U
#define oskAccess_Stack 0x8U

/* macros for AccessType */
#define OSMEMORY_IS_READABLE(x) (((x) & oskAccess_Read)? 1 : 0)
#define OSMEMORY_IS_WRITEABLE(x) (((x) & oskAccess_Write)? 1 : 0)
#define OSMEMORY_IS_EXECUTABLE(x) (((x) & oskAccess_Execute)? 1 : 0)
#define OSMEMORY_IS_STACKSPACE(x) (((x) & oskAccess_Stack)? 1 : 0)

/* values for RestartType */
#define RESTART    1
#define NO_RESTART 2

/* SCHEDULETABLE AUTOSTART TYPE */
#define osdScheduleTableAutostartNO                  0U
#define osdScheduleTableAutostartABSOLUT             1U
#define osdScheduleTableAutostartRELATIVE            2U
#define osdScheduleTableAutostartSYNCHRON            3U

/* ALARM AUTOSTART TYPE */
#define osdAlarmAutostartNO                          0U
#define osdAlarmAutostartABSOLUTE                    1U
#define osdAlarmAutostartRELATIVE                    2U

#define OSINVALIDAPPMODE                             0U

/* KB begin osekHwTASKmacro (overwritten) */
/* OSEK-conform task-function-macro */
#define TASK(x) void x##func(void)
/* KB end osekHwTASKmacro */
/* KB begin osekHWISRmacro (default) */
/* OSEK-conform interrupt-function-macro */
#define ISR(x) void x##func(void)
/* KB end osekHWISRmacro */
/* KB begin osekHWAlrmCallbckmacro (default) */
/* OSEK-conform function-macro for alarm callbacks */
#define ALARMCALLBACK(x) void x(void)
/* KB end osekHWAlrmCallbckmacro */
/* Default application mode is generated (OSEK 2.2) */


/* implementation specific constants */
/* KB begin osekConstants (overwritten) */
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
/* KB end osekConstants */



/* KB begin osekTickTypeDef (default) */
typedef osuint32             TickType;
typedef osint32              osTickTimeDiffType;
/* KB end osekTickTypeDef */

/* KB begin osekAditionalTypeDef (default) */

    
/* implementation specific types (OSEK types) */
/* KB begin osekTypes (overwritten) */
/*
    !!! Max priorities: Min(2^(sizeof(osPrioType)*8), 2^(sizeof(osPrioOffsetType)*8) * sizeof(osPrioFlagType)*8)
*/
typedef osuint16      osPrioType;         /* has to be unsigned (invalid is higher than others) */
typedef osuint8       osPrioOffsetType;

typedef osuint32      osStdFlagType; /* Standard-Flag-Type e.g. for AutoStartFlagField of alarms */

typedef osStdFlagType osPrioFlagType;

typedef osStdFlagType osResAccessMaskType;

typedef osuint32            osIntLevelType;      /* also used for level mask */
typedef osuint8             osTaskPreemptionType;
typedef osuint8             osTaskFlagType;
typedef osuint16            osQEntryCountType;
typedef osuint8             osActivationCountType;
typedef osuint32            osStackDataType;  
typedef osuint16            osStackSizeType;      /* maximum stacksize is 64k */
typedef osuint16            osTaskIndexType;  
typedef osuint16            osResourceIndexType;  

typedef osuint16            osTIPType;
typedef osTIPType           osAlarmIndexType; 
typedef osAlarmIndexType    AlarmType;
typedef osAlarmIndexType     *osAlarmIndexRefType;
typedef osTIPType           ScheduleTableType;
/* KB end osekTypes */

/* Autosar types */
/* KB begin atosTypes (overwritten) */
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


typedef double                   osTimeComputationType;/* used in macros for conversion between time and ticks to avoid usage of basic type */
/* KB end atosTypes */

/* KB begin applicationTypeDef (overwritten) */
#ifndef _MSC_VER
typedef osuint8                          ApplicationType;
#endif
/* KB end applicationTypeDef */

/* KB begin osekOSEKTypes (overwritten) */
typedef osTaskIndexType     TaskType;
typedef osResourceIndexType ResourceType;
typedef osuint16            osSemaphoreType;

typedef osuint8             osRTSizeType; /* typedef for library */
typedef osuint16            osSystemTimerReloadValueType;
typedef osuint32            EventMaskType;
#define osdEventMaskTypeSize    4
#define osdMaxAllowedTimeStamp  0xffffffffffffffffU
/* KB end osekOSEKTypes */
/* KB begin osekDispatcherLockType (default) */
typedef osuint8               osDispatcherLockType;
/* KB end osekDispatcherLockType */

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

/* Schedule Table related */
typedef TickType osSTOffsetType;
typedef TickType GlobalTimeTickType;
typedef osuint16 osSTIndexType;

typedef osuint8               ApplicationStateType;    /* TR:SASR40:6010 */
typedef ApplicationStateType *ApplicationStateRefType; /* TR:SASR40:6012 */




/* KB end osekAditionalTypeDef */

/* KB begin osekDefaultTypes (default) */
/* KB begin osekHWosTaskFctType (overwritten) */
typedef void                (*osTaskFctType)(void);
typedef void                (*osIsrFctType)(void);
/* KB end osekHWosTaskFctType */

typedef osuint16              osStackUsageType;
typedef osuint8               osTaskStateType;
/* KB begin osekHWosStackPtrType (overwritten) */
typedef void       *        osStackPtrType;
typedef void const *        osStackPtrToConstType;

typedef struct {
   osStackPtrType start;
   osStackPtrType end;
} osStackType;
/* KB end osekHWosStackPtrType */
typedef osuint8               osResCounterType;
/* KB end osekDefaultTypes */




/* KB begin osekOSEKdeclarations (default) */
#define DeclareTask(TaskId)     osqRAM0 extern osqRAM1 osqRAM2 TaskType osqRAM3 osNotUsed1##TaskId
#define DeclareResource(ResId)  osqRAM0 extern osqRAM1 osqRAM2 TaskType osqRAM3 osNotUsed2##ResId
#define DeclareEvent(Event)     osqRAM0 extern osqRAM1 osqRAM2 TaskType osqRAM3 osNotUsed3##Event
#define DeclareAlarm(AlarmId)   osqRAM0 extern osqRAM1 osqRAM2 TaskType osqRAM3 osNotUsed4##AlarmId
/* KB end osekOSEKdeclarations */    /* DeclareTask, DeclareAlarm,... */

/* structure for AlarmBase */
typedef struct
{
   TickType maxallowedvalue;/* Maximum possible allowed count value (for example */
                            /* in ticks or angle degrees) */
   TickType ticksperbase;   /* Number of ticks required to reach a counter-specific */
                            /* (significant) unit. */
   TickType mincycle;       /* Minimum allowed number of ticks for a cyclic alarm */
                            /* (only for systems with Extended Status). */
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





#if (osdClearTIPAbsIdx != -1)
 osqFunc1 void osqFunc2 osClearTimerInterruptPointAbs(CounterType CounterID);
#endif
#if (osdClearTIPRelIdx != -1)
 osqFunc1 void osqFunc2 osClearTimerInterruptPointRel(CounterType CounterID);
#endif
#if (osdSetTIPAbsMaxGtSemiCountIdx != -1)
 osqFunc1 osbool osqFunc2 osSetTIPAbsMaxGtSemiCount(CounterType CounterID, TickType timeToSet);
#endif
#if (osdSetTIPRelMaxGtSemiCountIdx != -1)
 osqFunc1 osbool osqFunc2 osSetTIPRelMaxGtSemiCount(CounterType CounterID, TickType timeToSet);
#endif
#if (osdSetTIPAbsMaxLeSemiCountIdx != -1)
 osqFunc1 osbool osqFunc2 osSetTIPAbsMaxLeSemiCount(CounterType CounterID, TickType timeToSet);
#endif
#if (osdSetTIPRelMaxLeSemiCountIdx != -1)
 osqFunc1 osbool osqFunc2 osSetTIPRelMaxLeSemiCount(CounterType CounterID, TickType timeToSet);
#endif
#if (osdGetCurrentTimeHighResHybridIdx != -1)
 osqFunc1 TickType osqFunc2 osGetCurrentTimeHiResHybrid(CounterType CounterID);
#endif
#if (osdGetCurrentTimeHighResMonoIdx != -1)
 osqFunc1 TickType osqFunc2 osGetCurrentTimeHiResMono(CounterType CounterID);
#endif
#if (osdGetCurrentTimeStdIdx != -1)
 osqFunc1 TickType osqFunc2 osGetCurrentTimeStd(CounterType CounterID);
#endif
#if (osdHandleCounterInterruptStdIdx != -1)
 osqFunc1 void osqFunc2 osHandleCounterInterruptStd(CounterType CounterID);
#endif
#if (osdHandleCounterInterruptHiResIdx != -1)
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



/* KB begin osHWCtrlVarStruct (default) */
typedef struct
{
   TaskType   ossHighReadyTaskIndex; /* ready task with highest priority */
   osPrioType ossHighReadyTaskPrio;  /* Priority of ready task with highest priority */
   osbool ossStartDispatcher;
#if (CC==BCC2) || (CC==ECC2)
   #if (osdNumberOfPriorities > 0)
      osQEntryCountType ossQReadyTaskHead[osdNumberOfPriorities];
      osQEntryCountType ossQReadyTaskTail[osdNumberOfPriorities];
   #else
      osQEntryCountType ossQReadyTaskHead[1];
      osQEntryCountType ossQReadyTaskTail[1];
   #endif
#else
   #if (osdNumberOfPriorities > 0)
      TaskType ossQReadyTask[osdNumberOfPriorities];
   #else
      TaskType ossQReadyTask[1];
   #endif
#endif
#if (osdRTSize > 1)
   osPrioFlagType ossQReadyPrios[osdRTSize];
#else
   osPrioFlagType ossQReadyPrios;
#endif
}osCtrlVarsLockNeededType;

typedef struct
{
   /* KB begin osekHwSctxCtrlVarsCandidates (default) */
   osuint8 ossIntNestingDepth;
   TaskType ossActiveTaskIndex;    /* indicates the currently running task */
   ISRType ossActiveISRID;     /* Id of the currently running (cat2) ISR */
   osuint8 ossIntSaveDisableCounter;
   osuint8 ossIntSaveDisableCounterGlobal;
   #if (STATUS_LEVEL == EXTENDED_STATUS)
   volatile osuint8 ossIntAPIStatus;
   #endif
   #if (osdNumberOfApplications > 0)
   ApplicationType ossActiveApplicationID;
   #endif
   
   /* KB begin osekHwAdditionalSctxCtrlVarsCandidates (overwritten) */
   volatile osuint8 ossCallDispatcher;
   /* KB end osekHwAdditionalSctxCtrlVarsCandidates */
   /* KB end osekHwSctxCtrlVarsCandidates */
   
   osPrioType ossActiveTaskPrio;     /* Priority of actually active task */
   osIntLevelType ossSavedIntLevel;
   osIntLevelType ossSavedIntLevelNested;
   osbool ossStarted;
  
   /* KB begin osCtrlVarStructVariablesForGlobalDisable (overwritten) */
   osuint32 ossSavedIntDisFlag;
   osuint32 ossSavedIntDisFlagNested;
   /* KB end osCtrlVarStructVariablesForGlobalDisable */

#if (osdFullPreempt || osdMixedPreempt)
   volatile osDispatcherLockType ossLockDispatcher;
#endif
#if osdExceptionDetails
   osint16 ossISRUnhandledException_Number;
#endif
#if ((osdSC == SC3) || (osdSC == SC4))
   osuint16 ossCurrentContext;
   osuint32 ossIsInUserMode;
   osuint8  ossInSystemFct;
#endif
#if (osdNumberOfApplications > 0)
   volatile osbool ossInApplHook;
#endif /* (osdNumberOfApplications > 0) */

#if STATUS_LEVEL == EXTENDED_STATUS
   osResCounterType ossResGlobalOccupationCounter;
  #if (osdNumberOfInterruptResources > 0)
   osIntLevelType ossInitialIntLevel;
  #endif
#endif
#if (osdParameterAccessMacros && osdErrorHook)
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

#if (osdErrorHook!=0)
   #if osdORTIDebug 
      StatusType ossLastErrorCode;
   #endif
   volatile osuint16 ossLastError;
   osbool ossErrorFlag;
#endif
   /* KB begin osCtrlVarsNoLockNeededAdditionalHWVariables (overwritten) */
   #if osdExceptionDetails
   osuint32 ossUnhandledExceptionDetail;
   #endif
   /* KB end osCtrlVarsNoLockNeededAdditionalHWVariables */
}osCtrlVarsNoLockNeededType;

typedef struct
{ 
   volatile osCtrlVarsLockNeededType    LockIsNeeded;
   osCtrlVarsNoLockNeededType  LockIsNotNeeded;
} osCtrlVarType;

#define ptrToCcb (&osOwnCcb->LockIsNeeded)
/* KB end osHWCtrlVarStruct */

/* KB begin osOwnCcbDefine (overwritten) */
#define osOwnCcb (osConfigBlock.CcbAddress[osSysGetCoreID()])

#define osdCounterInternalMaximumValue(x) (oskCounterInternalMaximumValue[x])

/* KB end osOwnCcbDefine */

/* KB begin osekHWConfigBlock (default) */
typedef struct {

   /* Frame */
   osuint8  aucMagicNumber[4];   /* 130 42 12 196  = 0x82 2A 0C C4 */
   osuint16 uiLength;
   osuint16 uiHardwareID;        /* Hardware Identification */
   osuint8  ucMajorVersion;
   osuint8  ucMinorVersion;
   osuint16 uiConfigVersion;     /* Version number of configuration block format*/
   osuint16 uiUserConfigVersion; /* Version number of configuration assigned by user*/

   /* cargo --------------------------------------------------------------- */

   /* start address of config block */
   const void*                      uiStartAddressConfigBlock;
   /* start addresses of sub-containers (fixed number) */
   const void*                      uiStartAddressSubCont0;                /* Sub-container 0 */
   const osTaskFctType*             uiStartAddressTaskStartAddress;        /* Sub-container 1 */
   const osuint8*                   uiStartAddressTaskPreemptive;          /* Sub-container 2 */
   const osuint8*                   uiStartAddressTaskTrusted;             /* Sub-container 3 */
   const osStackPtrType*            uiStartAddressTaskStackStartAddress;   /* Sub-container 4 */
   const osStackPtrType*            uiStartAddressTaskStackEndAddress;     /* Sub-container 5 */
   const osuint8*                   uiStartAddressTaskToAppl;              /* Sub-container 6 */
   const osuint8*                   uiStartAddressIsrTrusted;              /* Sub-container 7 */
   const osuint8*                   uiStartAddressIsrToAppl;               /* Sub-container 8 */
   const osuint8*                   StartAddressApplTrusted;               /* Sub-container 9 */
   const osuint8*                   StartAddressTrustedFunctions;          /* Sub-container 10 */
   const osuint8*                   StartAddressNonTrustedFunctions;       /* Sub-container 11 */
   const osIsrFctType*              StartAddresscat2IsrStartAddress;       /* Sub-container 12 */
   const osuint8*                   StartAddressIsrNestable;               /* Sub-container 13 */
   const CoreIdType*                StartAddressProcessToCore;             /* Sub-container 14 */
   const CoreIdType*                StartAddressAlarmToCore;               /* Sub-container 15 */
   const CoreIdType*                StartAddressResourceToCore;            /* Sub-container 16 */
   const CoreIdType*                StartAddressCounterToCore;             /* Sub-container 17 */
   const CoreIdType*                StartAddressScheduleTableToCore;       /* Sub-container 18 */
   const CoreIdType*                StartAddressApplicationToCore;         /* Sub-container 19 */
   const CoreIdType*                StartAddressTrustedFunctionToCore;     /* Sub-container 20 */
   const CoreIdType*                StartAddressNonTrustedFunctionToCore;  /* Sub-container 21 */
   osCtrlVarType* const *           StartAddressCcbAddress;                /* Sub-container 22 */
   const osuint8*                   StartAddressPeripheralRegions;         /* Sub-container 23 */
/* KB begin osekHWConfigBlockStartAddrSpecific (overwritten) */
   const osStackType*               StartAddressCat2IsrStacks;             /* Sub-container 24 */
   const osuint16* const            StartAddrISRChannel;                   /* Sub-container 25 */
   const osuint16* const            StartAddrISRPrioLevel;                 /* Sub-container 26 */
   const osuint8* const             StartAddrIsrToCore;                    /* Sub-container 27 */
/* KB end osekHWConfigBlockStartAddrSpecific */  

   /* Sub-Container 0 */
   osuint16 uiNumberOfTasks;               /* = osdNumberOfAllTasks            */
   osuint16 uiNumberOfCat2ISRs;            /* = osdNumberOfCat2ISRs            */
   osuint16 uiNumberOfTrustedFunctions;    /* = osdNumberOfTrustedFunctions    */
   osuint16 uiNumberOfNonTrustedFunctions; /* = osdNumberOfNonTrustedFunctions */
   osuint16 uiNumberOfApplications;        /* = osdNumberOfApplications        */
   osuint16 uiNumberOfPeripheralRegions;   /* = osdNumberOfPeripheralRegions   */
   osuint8  ucStackUsageMeasurement;       /* = osdStackUsageMeasurement       */
   osuint16 NumberOfAlarms;                /* = osdNumberOfAlarms              */
   osuint16 NumberOfAllResources;          /* = osdNumberOfAllResources        */
   osuint16 NumberOfAvailableCores;        /* = osdNumberOfAvailableCores      */
   osuint16 NumberOfCounters;              /* = osdNumberOfCounters            */
   osuint16 NumberOfProcesses;             /* = osdNumberOfProcesses           */
   osuint16 NumberOfScheduleTables;        /* = osdNumberOfScheduleTables      */

   /* KB begin osekHWConfigBlockSubCont0Specific (overwritten) */
      osStackType SystemStack[osdNumberOfAvailableCores];
   /* KB end osekHWConfigBlockSubCont0Specific */ 

   /* Sub-Container 1 */
   osTaskFctType              aulTaskStartAddress[osdNumberOfAllTasks+1];
   /* Sub-Container 2 */
   osuint8                    aucTaskPreemptive[osdNumberOfAllTasks+1];
   /* Sub-Container 3 */
   osuint8                    aucTaskTrusted[osdNumberOfAllTasks+1];
   /* Sub-Container 4 */
   osStackPtrType             aulTaskStackStartAddress[osdNumberOfAllTasks+1]; /* TR:SPMF07:0003 */
   /* Sub-Container 5 */
   const osStackPtrType       aulTaskStackEndAddress[osdNumberOfAllTasks+1]; /* TR:SPMF08:0004 */
   /* Sub-Container 6 */
   osuint8                    acTaskToAppl[osdNumberOfAllTasks+1]; 
   /* Sub-Container 7 */
   osuint8                    aucIsrTrusted[osdNumberOfCat2ISRs+1];
   /* Sub-Container 8 */
   osuint8                    acIsrToAppl[osdNumberOfCat2ISRs+1];
   /* Sub-Container 9 */
   osuint8                    applTrusted[osdNumberOfApplications+1];
   /* Sub-Container 10 */
   osuint8                    trustedFunctions[1];
   /* Sub-Container 11 */
   osuint8                    nonTrustedFunctions[1];
   /* Sub-Container 12 */
   osIsrFctType               cat2IsrStartAddress[osdNumberOfCat2ISRs+1];
   /* Sub-Container 13 */
   osuint8                    IsrNestable[osdNumberOfCat2ISRs+1];
   /* Sub-Container 14 */
   CoreIdType                 ProcessToCore[osdNumberOfProcesses+1];
   /* Sub-Container 15 */
   CoreIdType                 AlarmToCore[osdNumberOfAlarms+1];
   /* Sub-Container 16 */
   CoreIdType                 ResourceToCore[osdNumberOfAllResources+1];
   /* Sub-Container 17 */
   CoreIdType                 CounterToCore[osdNumberOfCounters+1];
   /* Sub-Container 18 */
   CoreIdType                 ScheduleTableToCore[osdNumberOfScheduleTables+1];
   /* Sub-Container 19 */
   CoreIdType                 ApplicationToCore[osdNumberOfApplications+1];
   /* Sub-Container 20 */
   CoreIdType                 TrustedFunctionToCore[osdNumberOfTrustedFunctions+1];
   /* Sub-Container 21 */
   CoreIdType                 NonTrustedFunctionToCore[1];
   /* Sub-Container 22 */
   osCtrlVarType* const       CcbAddress[osdNumberOfAvailableCores+1];
   /* Sub-Container 23 */
   osuint8                    peripheralRegions[1];
/* KB begin osekHWConfigBlockSubContainersSpecific (overwritten) */
   /* Sub-Container 24 */
   osStackType                osCat2IsrStacks[osdNumberOfCat2ISRs+1];
   /* Sub-Container 25 */   
   const osuint16             osIsrChannel[osdNumberOfAllISRs+1];
   /* Sub-Container 26 */   
   const osuint16             osIsrPrioLevel[osdNumberOfAllISRs+1];
   /* Sub-Container 27 */   
   const osuint8              osIsrToCore[osdNumberOfAllISRs+1];
/* KB end osekHWConfigBlockSubContainersSpecific */

   /* Frame End ---------------------------------------------------------- */
   osuint32 uiCheckSum;

} tsConfigBlock;
/* KB end osekHWConfigBlock */
/* KB begin osekHWexternConfigBlock (default) */
/* MISRA RULE 8.8 not violated: the external declaration is defined more than once in the vector testsuite.
                                it is declared only once in the OS code
 */ 
extern const tsConfigBlock osConfigBlock; /* PRQA S 3451 */ 
/* KB end osekHWexternConfigBlock */


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
 #if (osdTestMacros == 1)
  #if defined USE_QUOTE_INCLUDES
   #include "testmac1.h"
  #else
   #include <testmac1.h>
  #endif
 #endif
 #if (osdTestMacros == 3)
  #if defined USE_QUOTE_INCLUDES
   #include "testmac3.h"
  #else
   #include <testmac3.h>
  #endif
 #endif
 #if (osdTestMacros == 4)
  #if defined USE_QUOTE_INCLUDES
   #include "testmac4.h"
  #else
   #include <testmac4.h>
  #endif
 #endif
#endif /*osdTestMacros*/

/* KB begin osekHWVariableSectionStartHeader (overwritten) */
/* KB end osekHWVariableSectionStartHeader */

/* KB begin osekHWDefineNegateTick (default) */
/* KB end osekHWDefineNegateTick */

/* KB begin osekHWDefineDummyRead (overwritten) */
#define osdDummyRead(x)   if((x)!=0){__asm("NOP");}
/* KB end osekHWDefineDummyRead */

osqRAM0 extern osqRAM1 volatile osqRAM2 AppModeType osqRAM3 osActiveAppMode;


/* KB begin osekHWVariableSectionEndHeader (overwritten) */
/* KB end osekHWVariableSectionEndHeader */

/* KB begin osekOsAbortSystemPrototype (default) */
osqFunc1 void osqFunc2 osAbortSystem(osuint16 uiError);
/* KB end osekOsAbortSystemPrototype */
/* KB begin osekOsUnrecoverableErrorPrototype (default) */
osqFunc1 void osqFunc2 osUnrecoverableError(StatusType StdErrorCode, osuint16 osOsekErrorCode);
/* KB end osekOsUnrecoverableErrorPrototype */

/* necessary for task/ISR-kill and to handle a missing TerminateTask in SC3/4 */
#if (osdKillTaskIsrPossible || (osdSC == SC3) || (osdSC == SC4))
 #if (osdNumberOfAllResources > 0)
 #if (!defined(osdGetResourceNotUsed)) || (!defined(osdReleaseResourceNotUsed))
  osqFunc1 void osqFunc2 osSysKillResourceList(ResourceType ResId);
 #endif
 #endif
#endif




/* fullfills [SR:001] of $\AutosarOS\general\Generation5\_doc\12_SystemRequirements\RequirementsSpec_MicrosarOS.doc */
/* OSEK-Prototypes */
/* system services */

#ifndef osdActivateTaskNotUsed
#if ((osdSC== SC3) || (osdSC== SC4))

#define ActivateTask(x) (osPsysActivateTask(x))

#else
#define ActivateTask(x) (osActivateTask(x))
#endif
#endif

#ifndef osdTerminateTaskNotUsed
#if ((osdSC== SC3) || (osdSC== SC4))
#define TerminateTask() osPsysTerminateTask()
#else
#define TerminateTask() osTerminateTask()
#endif
#endif

#ifndef osdChainTaskNotUsed
#if ((osdSC== SC3) || (osdSC== SC4))
#define ChainTask(x) (osPsysChainTask(x))
#else
#define ChainTask(x) (osChainTask(x))
#endif
#endif

#ifndef osdScheduleNotUsed
#if ((osdSC== SC3) || (osdSC== SC4))
#define Schedule() osPsysSchedule()
#else
#define Schedule() osSchedule()
#endif
#endif

#ifndef osdGetTaskIDNotUsed
#if ((osdSC== SC3) || (osdSC== SC4))
#define GetTaskID(x) (osPsysGetTaskID(x))
#else
#define GetTaskID(x) (osGetTaskID(x))
#endif
#endif

#ifndef osdGetTaskStateNotUsed
#if ((osdSC== SC3) || (osdSC== SC4))
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


/* interrupt handling */
/* KB begin osekOsAssertFailedPrototype (default) */
osqFunc1 void osqFunc2 osAssertFailed(void);
/* KB end osekOsAssertFailedPrototype */
/* KB begin osekHwOsekGlobalPrototypes (overwritten) */

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

#if (osdNumberOfPrioLevels == 8)
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

/* KB end osekHwOsekGlobalPrototypes */ 

/* KB begin osekHwRTEInterruptMacros (default) */
#define osRTEDisableLevel()   osDisableLevel()
#define osRTEEnableLevel()    osEnableLevel()

 #define osRTEDisableGlobal()  osDisableGlobal()
 #define osRTEEnableGlobal()   osEnableGlobal()
/* KB end osekHwRTEInterruptMacros */

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

#if ((osdSC== SC3) || (osdSC== SC4))
/* KB begin osekHwPsysWrapperPrototypes (default) */
#if (((osdNumberOfAllTasks > 0) && !defined(osdActivateTaskNotUsed)))
/* MISRA RULE 8.10 VIOLATION: osPsysActivateTask might be only called in the same file 
 * in some configuration. Conditional compiling of the function would increase
 * the code complexity to unacceptable level (1505) */
StatusType osPsysActivateTask(TaskType Param0taskIndex);/* PRQA S 1505 */
#endif

#if (((osdNumberOfAllTasks > 0) && !defined(osdChainTaskNotUsed)))
StatusType osPsysChainTask(TaskType Param0taskIndex);
#endif

#if (((osdNumberOfAllTasks > 0) && !defined(osdGetTaskIDNotUsed)))
StatusType osPsysGetTaskID(TaskRefType Param0TaskId);
#endif

#if (((osdNumberOfAllTasks > 0) && !defined(osdGetTaskStateNotUsed)))
StatusType osPsysGetTaskState(TaskType Param0TaskId, TaskStateRefType Param1State);
#endif

#if ((((osdNumberOfAllResources - osdNumberOfInternalResources) > 0) && !defined(osdGetResourceNotUsed)))
StatusType osPsysGetResource(ResourceType Param0ResId);
#endif

#if ((((osdNumberOfAllResources - osdNumberOfInternalResources) > 0) && !defined(osdReleaseResourceNotUsed)))
StatusType osPsysReleaseResource(ResourceType Param0ResId);
#endif

#if ((((CC == ECC1) || (CC == ECC2)) && (osdNumberOfExtendedTasks > 0) && !defined(osdSetEventNotUsed)))
/* MISRA RULE 8.10 VIOLATION: osPsysSetEvent might be only called in the same file 
 * in some configuration. Conditional compiling of the function would increase
 * the code complexity to unacceptable level (1505) */
StatusType osPsysSetEvent(TaskType Param0taskIndex, EventMaskType Param1setMask);/* PRQA S 1505 */
#endif

#if ((((CC == ECC1) || (CC == ECC2)) && (osdNumberOfExtendedTasks > 0) && !defined(osdClearEventNotUsed)))
StatusType osPsysClearEvent(EventMaskType Param0Mask);
#endif

#if ((((CC == ECC1) || (CC == ECC2)) && (osdNumberOfExtendedTasks > 0) && !defined(osdGetEventNotUsed)))
StatusType osPsysGetEvent(TaskType Param0taskIndex, EventMaskRefType Param1Event);
#endif

#if ((((CC == ECC1) || (CC == ECC2)) && (osdNumberOfExtendedTasks > 0) && !defined(osdWaitEventNotUsed)))
StatusType osPsysWaitEvent(EventMaskType Param0Mask);
#endif

#if (((osdNumberOfAlarms > 0) && !defined(osdGetAlarmBaseNotUsed)))
StatusType osPsysGetAlarmBase(AlarmType Param0AlarmId, AlarmBaseRefType Param1Info);
#endif

#if (((osdNumberOfAlarms > 0) && !defined(osdGetAlarmNotUsed)))
StatusType osPsysGetAlarm(AlarmType Param0alarmID, TickRefType Param1diffTickTime);
#endif

#if (((osdNumberOfAlarms > 0) && !defined(osdSetRelAlarmNotUsed)))
StatusType osPsysSetRelAlarm(AlarmType Param0alarmID, TickType Param1deltaTicks, TickType Param2cycle);
#endif

#if (((osdNumberOfAlarms > 0) && !defined(osdSetAbsAlarmNotUsed)))
StatusType osPsysSetAbsAlarm(AlarmType Param0alarmID, TickType Param1start, TickType Param2cycle);
#endif

#if (((osdNumberOfAlarms > 0) && !defined(osdCancelAlarmNotUsed)))
StatusType osPsysCancelAlarm(AlarmType Param0alarmID);
#endif

/* MISRA RULE 14.1 VIOLATION: osPsysShutdownOS might not be called in some
 * configuration. Conditional compiling of the function would increase
 * the code complexity to unacceptable level (1503) */
void osPsysShutdownOS(StatusType Param0Error);/* PRQA S 1503 */

#if (((osdNumberOfScheduleTables > 0) && !defined(osdStartScheduleTableRelNotUsed)))
StatusType osPsysStartScheduleTableRel(ScheduleTableType Param0ScheduleTableID, TickType Param1Offset);
#endif

#if (((osdNumberOfScheduleTables > 0) && !defined(osdStartScheduleTableAbsNotUsed)))
StatusType osPsysStartScheduleTableAbs(ScheduleTableType Param0ScheduleTableID, TickType Param1Offset);
#endif

#if (((osdNumberOfScheduleTables > 0) && !defined(osdNextScheduleTableNotUsed)))
StatusType osPsysNextScheduleTable(ScheduleTableType Param0ScheduleTableID_current, ScheduleTableType Param1ScheduleTableID_next);
#endif

#if (((osdNumberOfScheduleTables > 0) && !defined(osdStopScheduleTableNotUsed)))
StatusType osPsysStopScheduleTable(ScheduleTableType Param0ScheduleTableID);
#endif


#if (((osdNumberOfScheduleTables > 0) && !defined(osdGetScheduleTableStatusNotUsed)))
StatusType osPsysGetScheduleTableStatus(ScheduleTableType Param0ScheduleTableID, ScheduleTableStatusRefType Param1ScheduleStatus);
#endif

#if (((osdNumberOfSWCounters > 0) && !defined(osdIncrementCounterNotUsed)))
StatusType osPsysIncrementCounter(CounterType Param0CounterID);
#endif

#if ((!defined(osdGetCounterValueNotUsed)))
StatusType osPsysGetCounterValue(CounterType Param0CounterID, TickRefType Param1Value);
#endif


#if ((!defined(osdGetElapsedValueNotUsed)))
StatusType osPsysGetElapsedValue(CounterType Param0CounterID, TickRefType Param1Value, TickRefType Param2ElapsedValue);
#endif

#if (((osdNumberOfApplications > 0) && !defined(osdTerminateApplicationNotUsed)))
StatusType osPsysTerminateApplication(ApplicationType Param0Application, RestartType Param1RestartOption);
#endif

#if ((((osdSC == SC3) || (osdSC == SC4)) && !defined(osdGetApplicationStateNotUsed)))
StatusType osPsysGetApplicationState(ApplicationType Param0Application, ApplicationStateRefType Param1Value);
#endif

#if ((!defined(osdCallTrustedFunctionNotUsed)))
StatusType osPsysCallTrustedFunction(TrustedFunctionIndexType Param0FunctionIndex, TrustedFunctionParameterRefType Param1FunctionParams);
#endif


#if ((!defined(osdCheckISRMemoryAccessNotUsed)))
AccessType osPsysCheckISRMemoryAccess(ISRType Param0ISRID, MemoryStartAddressType Param1Address, MemorySizeType Param2Size);
#endif

#if ((!defined(osdCheckTaskMemoryAccessNotUsed)))
AccessType osPsysCheckTaskMemoryAccess(TaskType Param0TaskID, MemoryStartAddressType Param1Address, MemorySizeType Param2Size);
#endif

#if ((!defined(osdCheckObjectAccessNotUsed)))
ObjectAccessType osPsysCheckObjectAccess(ApplicationType Param0ApplID, ObjectTypeType Param1ObjectType, ObjectIDType Param2ObjectID);
#endif

#if ((!defined(osdCheckObjectOwnershipNotUsed)))
/* Param0ObjectType is assembled from the index 'Param0' and its name,
 * 'ObjectType'. Having the characters '0' and 'O' is thus not avoidable.
 * This is no MISRA error (4153).
 */
ApplicationType osPsysCheckObjectOwnership(ObjectTypeType Param0ObjectType, ObjectIDType Param1ObjectID); /* PRQA S 4153 */
#endif

#if (((osdTimingProtectionUsed) && (osdTimingMeasurement) && !defined(osdosGetTaskMaxExecutionTimeNotUsed)))
StatusType osPsysosGetTaskMaxExecutionTime(TaskType Param0TaskID, osTPTimeRefType Param1MaxTime);
#endif

#if (((osdTimingProtectionUsed) && (osdTimingMeasurement) && !defined(osdosGetISRMaxExecutionTimeNotUsed)))
StatusType osPsysosGetISRMaxExecutionTime(ISRType Param0ISRID, osTPTimeRefType Param1MaxTime);
#endif

#if (((osdTimingProtectionUsed) && (osdTimingMeasurement) && !defined(osdosGetTaskMaxBlockingTimeNotUsed)))
StatusType osPsysosGetTaskMaxBlockingTime(TaskType Param0TaskID, BlockTypeType Param1BlockType, ResourceType Param2ResourceID, osTPTimeRefType Param3MaxTime);
#endif

#if (((osdTimingProtectionUsed) && (osdTimingMeasurement) && !defined(osdosGetISRMaxBlockingTimeNotUsed)))
StatusType osPsysosGetISRMaxBlockingTime(ISRType Param0ISRID, BlockTypeType Param1BlockType, ResourceType Param2ResourceID, osTPTimeRefType Param3MaxTime);
#endif

#if (((osdTimingProtectionUsed) && (osdTimingMeasurement) && !defined(osdosGetTaskMinInterArrivalTimeNotUsed)))
StatusType osPsysosGetTaskMinInterArrivalTime(TaskType Param0TaskID, osTPTimeStampRefType Param1MinTime);
#endif

#if (((osdTimingProtectionUsed) && (osdTimingMeasurement) && !defined(osdosGetISRMinInterArrivalTimeNotUsed)))
StatusType osPsysosGetISRMinInterArrivalTime(ISRType Param0ISRID, osTPTimeStampRefType Param1MinTime);
#endif

#if (((osdNumberOfAllTasks > 0) && !defined(osdTerminateTaskNotUsed)))
StatusType osPsysTerminateTask(void);
#endif

#if (((osdNumberOfAllTasks > 0) && !defined(osdScheduleNotUsed)))
StatusType osPsysSchedule(void);
#endif

#if (!defined(osdGetActiveApplicationModeNotUsed))
AppModeType osPsysGetActiveApplicationMode(void);
#endif

#if (!defined(osdGetISRIDNotUsed))
ISRType osPsysGetISRID(void);
#endif

#if ((!defined(osdDisableAllInterruptsNotUsed)))
void osPsysDisableAllInterrupts(void);
#endif

#if ((!defined(osdEnableAllInterruptsNotUsed)))
void osPsysEnableAllInterrupts(void);
#endif

#if ((!defined(osdSuspendAllInterruptsNotUsed)))
void osPsysSuspendAllInterrupts(void);
#endif

#if ((!defined(osdResumeAllInterruptsNotUsed)))
void osPsysResumeAllInterrupts(void);
#endif

#if ((!defined(osdSuspendOSInterruptsNotUsed)))
void osPsysSuspendOSInterrupts(void);
#endif

#if ((!defined(osdResumeOSInterruptsNotUsed)))
void osPsysResumeOSInterrupts(void);
#endif

#if ((((osdSC == SC3) || (osdSC == SC4)) && !defined(osdAllowAccessNotUsed)))
StatusType osPsysAllowAccess(void);
#endif

void osPsysCallApplStartupHook(ApplicationType Param0applID);

void osPsysCallApplErrorHook(StatusType Param0ErrorCode, ApplicationType Param1applID);

void osPsysCallApplShutdownHook(StatusType Param0Error, ApplicationType Param1applID);


/* KB end osekHwPsysWrapperPrototypes */
#endif /* ((osdSC== SC3) || (osdSC== SC4)) */

#define osdIntAPIDisableAll 0x80U

#if (STATUS_LEVEL == EXTENDED_STATUS)
   #define osSetIntAPIStatus(x) (osOwnCcb->LockIsNotNeeded.ossIntAPIStatus = (x))
   #define osIncIntAPIStatus() (osOwnCcb->LockIsNotNeeded.ossIntAPIStatus++)
   #define osDecIntAPIStatus() (osOwnCcb->LockIsNotNeeded.ossIntAPIStatus--)
#else
   #define osSetIntAPIStatus(x)
   #define osIncIntAPIStatus()
   #define osDecIntAPIStatus()
#endif


#ifndef osdEnableAllInterruptsNotUsed
   #if ((osdSC == SC2) ||  (osdSC == SC1))
      #define EnableAllInterrupts() (osEnableAllInterrupts())
   #else
      #define EnableAllInterrupts() (osPsysEnableAllInterrupts())
   #endif
#endif

#ifndef osdDisableAllInterruptsNotUsed
   #if ((osdSC == SC2) || (osdSC == SC1))
      #define DisableAllInterrupts() (osDisableAllInterrupts())
   #else
      #define DisableAllInterrupts() (osPsysDisableAllInterrupts())
   #endif
#endif

#ifndef osdResumeOSInterruptsNotUsed
   #if ((osdSC== SC2) || (osdSC== SC1))
      #define ResumeOSInterrupts() (osResumeOSInterrupts())
   #else
      #define ResumeOSInterrupts() (osPsysResumeOSInterrupts())
   #endif
#endif

#ifndef osdSuspendOSInterruptsNotUsed
   #if ((osdSC == SC2) || (osdSC == SC1))
      #define SuspendOSInterrupts() (osSuspendOSInterrupts())
   #else
      #define SuspendOSInterrupts() (osPsysSuspendOSInterrupts())
   #endif
#endif

#ifndef osdResumeAllInterruptsNotUsed
   #if ((osdSC== SC2) || (osdSC== SC1))
      #define ResumeAllInterrupts() (osResumeAllInterrupts())
   #else
      #define ResumeAllInterrupts() (osPsysResumeAllInterrupts())
   #endif
#endif

#ifndef osdSuspendAllInterruptsNotUsed
   #if ((osdSC == SC2) || (osdSC == SC1))
      #define SuspendAllInterrupts() (osSuspendAllInterrupts())
   #else
      #define SuspendAllInterrupts() (osPsysSuspendAllInterrupts())
   #endif
#endif


/* resource management */

#ifndef osdGetResourceNotUsed
#if ((osdSC== SC3) || (osdSC== SC4))
#define GetResource(x) (osPsysGetResource(x))
#else
#define GetResource(x) (osGetResource(x))
#endif
#endif


#ifndef osdReleaseResourceNotUsed
#if ((osdSC== SC3) || (osdSC== SC4))
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

/* KB begin osekSemaphores (default) */
/* semaphores for OSEK */

#ifndef osdGetSemaphoreNotUsed
#if ((osdSC== SC3) || (osdSC== SC4))
#define GetSemaphore(x) (osPsysGetSemaphore(x))
#else
#define GetSemaphore(x) (osGetSemaphore(x))
#endif
#endif

#ifndef osdReleaseSemaphoreNotUsed
#if ((osdSC== SC3) || (osdSC== SC4))
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

/* KB end osekSemaphores */

/* event control */
#if (CC == ECC1) || (CC == ECC2)

#ifndef osdSetEventNotUsed
#if ((osdSC== SC3) || (osdSC== SC4))
#define SetEvent(x, y) (osPsysSetEvent((x), (y)))
#else
#define SetEvent(x, y) (osSetEvent((x), (y)))
#endif
#endif

#ifndef osdGetEventNotUsed
#if ((osdSC== SC3) || (osdSC== SC4))
#define GetEvent(x, y) (osPsysGetEvent((x), (y)))
#else
#define GetEvent(x, y) (osGetEvent((x), (y)))
#endif
#endif

#ifndef osdClearEventNotUsed
#if ((osdSC== SC3) || (osdSC== SC4))
#define ClearEvent(x) (osPsysClearEvent(x))
#else
#define ClearEvent(x) (osClearEvent(x))
#endif
#endif

#ifndef osdWaitEventNotUsed
#if ((osdSC== SC3) || (osdSC== SC4))
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

#else /*CC...*/

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

#endif /*CC...*/


/* alarms        */
#ifndef osdGetAlarmBaseNotUsed
#if ((osdSC== SC3) || (osdSC== SC4))
#define GetAlarmBase(x, y) (osPsysGetAlarmBase((x), (y)))
#else
#define GetAlarmBase(x, y) (osGetAlarmBase((x), (y)))
#endif
#endif

#ifndef osdSetRelAlarmNotUsed
#if (osdNumberOfAlarms > 0)
/* KB begin osekHwSetRelAlarmDefine2 (default) */
#if ((osdSC== SC3) || (osdSC== SC4))
#define SetRelAlarm(x, y, z) (osPsysSetRelAlarm((x), (y), (z)))
#else
#define SetRelAlarm(x, y, z) (osSetRelAlarm((x), (y), (z)))
#endif
/* KB end osekHwSetRelAlarmDefine2 */
#else
#if ((osdSC== SC3) || (osdSC== SC4))
#define SetRelAlarm(x, y, z) (osPsysSetRelAlarm(x))
#else
#define SetRelAlarm(x, y, z) (osSetRelAlarm(x))
#endif
#endif
#endif

#ifndef osdSetAbsAlarmNotUsed
#if (osdNumberOfAlarms > 0)
/* KB begin osekHwSetAbsAlarmDefine2 (default) */
#if ((osdSC== SC3) || (osdSC== SC4))
#define SetAbsAlarm(x, y, z) (osPsysSetAbsAlarm((x), (y), (z)))
#else
#define SetAbsAlarm(x, y, z) (osSetAbsAlarm((x), (y), (z)))
#endif
/* KB end osekHwSetAbsAlarmDefine2 */
#else
#if ((osdSC== SC3) || (osdSC== SC4))
#define SetAbsAlarm(x, y, z) (osPsysSetAbsAlarm(x))
#else
#define SetAbsAlarm(x, y, z) (osSetAbsAlarm(x))
#endif
#endif
#endif

#ifndef osdCancelAlarmNotUsed
#if ((osdSC== SC3) || (osdSC== SC4))
#define CancelAlarm(x) (osPsysCancelAlarm(x))
#else
#define CancelAlarm(x) (osCancelAlarm(x))
#endif
#endif
 
#if (osdNumberOfAlarmIncrementCounter > 0) || !defined(osdIncrementCounterNotUsed)
/* TR:SPMF09:0011 Start */
#if ((osdSC== SC3) || (osdSC== SC4))
#define IncrementCounter(x) (osPsysIncrementCounter(x))
#else
#define IncrementCounter(x) (osIncrementCounter(x))
#endif
/* TR:SPMF09:0011 End */
#endif


#ifndef osdGetCounterValueNotUsed
 /* TR:SASR30:0383 Start */
 #if ((osdSC == SC3) || (osdSC == SC4))
  #define GetCounterValue(x, y) (osPsysGetCounterValue((x), (y)))
 #else
  #define GetCounterValue(x, y) (osGetCounterValue((x), (y)))
 #endif
 /* TR:SASR30:0383 End */
#endif

#ifndef osdGetElapsedValueNotUsed
 #define GetElapsedCounterValue(x,y,z) GetElapsedValue((x),(y),(z)) /* compatibility ASR3/ASR4 */
 /* TR:SASR30:0392 Start */
 #if ((osdSC == SC3) || (osdSC == SC4))
  #define GetElapsedValue(x, y, z) (osPsysGetElapsedValue((x), (y), (z)))
 #else
  #define GetElapsedValue(x, y, z) (osGetElapsedValue((x), (y), (z)))
 #endif
 /* TR:SASR30:0392 End */
#endif


#ifndef osdGetAlarmNotUsed
#if ((osdSC== SC3) || (osdSC== SC4))
#define GetAlarm(x, y) (osPsysGetAlarm((x), (y)))
#else
#define GetAlarm(x, y) (osGetAlarm((x), (y)))
#endif
#endif

#ifndef osdStartScheduleTableRelNotUsed
#if ((osdSC== SC3) || (osdSC== SC4))
#define StartScheduleTableRel(x, y) osPsysStartScheduleTableRel((x), (y))
#else
#define StartScheduleTableRel(x, y) osStartScheduleTableRel((x), (y))
#endif
#endif

#ifndef osdStartScheduleTableAbsNotUsed
#if ((osdSC== SC3) || (osdSC== SC4))
#define StartScheduleTableAbs(x, y) osPsysStartScheduleTableAbs((x), (y))
#else
#define StartScheduleTableAbs(x, y) osStartScheduleTableAbs((x), (y))
#endif
#endif

#ifndef osdStopScheduleTableNotUsed
#if ((osdSC== SC3) || (osdSC== SC4))
#define StopScheduleTable(x) osPsysStopScheduleTable((x))
#else
#define StopScheduleTable(x) osStopScheduleTable((x))
#endif
#endif

#ifndef osdNextScheduleTableNotUsed
#if ((osdSC== SC3) || (osdSC== SC4))
#define NextScheduleTable(x, y) osPsysNextScheduleTable((x), (y))
#else
#define NextScheduleTable(x, y) osNextScheduleTable((x), (y))
#endif
#endif

#ifndef osdGetScheduleTableStatusNotUsed
#if ((osdSC== SC3) || (osdSC== SC4))
#define GetScheduleTableStatus(x, y) osPsysGetScheduleTableStatus((x), (y))
#else
#define GetScheduleTableStatus(x, y) osGetScheduleTableStatus((x), (y))
#endif
#endif



#ifndef osdGetAlarmBaseNotUsed
osqFunc1 StatusType osqFunc2 osGetAlarmBase(AlarmType AlarmId, AlarmBaseRefType Info);
#endif

#ifndef osdSetRelAlarmNotUsed
/* KB begin osekHWosSetRelAlarmPrototype (default) */
#if (osdNumberOfAlarms > 0)
osqFunc1 StatusType osqFunc2 osSetRelAlarm(AlarmType alarmID, 
                                           TickType deltaTicks,
                                           TickType cycle);
#endif
/* KB end osekHWosSetRelAlarmPrototype */
#endif

#ifndef osdSetAbsAlarmNotUsed
/* KB begin osekHWosSetAbsAlarmPrototype (default) */
#if (osdNumberOfAlarms > 0)
osqFunc1 StatusType osqFunc2 osSetAbsAlarm(AlarmType alarmID, 
                                           TickType start,
                                           TickType cycle);
#endif
/* KB end osekHWosSetAbsAlarmPrototype */
#endif

#ifndef osdCancelAlarmNotUsed
osqFunc1 StatusType osqFunc2 osCancelAlarm(AlarmType alarmID);
#endif

/* fullfills [SR:315] of $\AutosarOS\general\Generation5\_doc\12_SystemRequirements\RequirementsSpec_MicrosarOS.doc */
#if (osdNumberOfAlarmIncrementCounter > 0) || !defined(osdIncrementCounterNotUsed)
osqFunc1 StatusType osqFunc2 osIncrementCounter(CounterType CounterID);
#endif

#ifndef osdGetCounterValueNotUsed
osqFunc1 StatusType osqFunc2 osGetCounterValue(CounterType CounterID, TickRefType Value); /* TR:SASR30:5108 */
#endif

#ifndef osdGetElapsedValueNotUsed
osqFunc1 StatusType osqFunc2 osGetElapsedValue(CounterType CounterID, TickRefType Value, TickRefType ElapsedValue); /* TR:SASR30:5109 */
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




/* TR:SPMF20:0013 Start */
/* definitions for static alarms */
/* these macros should be used as parameters for SetRelAlarm/SetAbsAlarm in case of static alarms */
#define OS_STATIC_ALARM_TIME 0
#define OS_STATIC_CYCLE_TIME 0
/* TR:SPMF20:0013 End */

/* Operating system execution control */
osqFunc1 void osqFunc2 osErrorHook(StatusType ErrorCode);
osqFunc1 void osqFunc2 osShutdownOS(StatusType Error);
#if ((osdSC== SC3) || (osdSC== SC4))
#define ShutdownOS(x) (osPsysShutdownOS(x))
#else
#define ShutdownOS(x) (osShutdownOS(x))
#endif

osqFunc1 void osqFunc2 osStartOSasm(void); /* TR:SPMF05:0001 */

/* Definition of StartOS(). */
/* Error-Checking is done is osStartOSc */
/* TR:SPMF05:0001 Start */
#define StartOS(x)                              \
   osActiveAppMode=(x);                         \
   osStartOSasm()
/* TR:SPMF05:0001 End */

/* fullfills [SR:006] of $\AutosarOS\general\Generation5\_doc\12_SystemRequirements\RequirementsSpec_MicrosarOS.doc */
osqFunc1 void osqFunc2 osInitialize(void); /* TR:SPMF05:0001 */


osqFunc1 ApplicationType osqFunc2 osGetApplicationID(void);
/* KB begin osekGetApplicationIDDef (overwritten) */
#define GetApplicationID()   (osGetApplicationID())
/* KB end osekGetApplicationIDDef */

osqFunc1 AppModeType osqFunc2 osGetActiveApplicationMode(void);
/* KB begin osekGetActiveApplicationModeDef (overwritten) */
#define GetActiveApplicationMode()   (osGetActiveApplicationMode())
/* KB end osekGetActiveApplicationModeDef */

osqFunc1 ISRType osqFunc2 osGetISRID(void);
/* KB begin osekGetISRIDDef (overwritten) */
#define GetISRID()   (osGetISRID())
/* KB end osekGetISRIDDef */

/* KB begin osekCallBackSectionStart (overwritten) */
/* KB end osekCallBackSectionStart */

/* hook routines */
osqFunc1 void osqFunc2 ErrorHook (StatusType Error);
osqFunc1 void osqFunc2 StartupHook (void);
osqFunc1 void osqFunc2 ShutdownHook (StatusType Error);

#if osdPreTaskHook
osqFunc1 void osqFunc2 PreTaskHook (void);
#endif
#if osdPostTaskHook
osqFunc1 void osqFunc2 PostTaskHook (void);
#endif

#if ((osdSC == SC2) || (osdSC == SC3) || (osdSC == SC4))
ProtectionReturnType ProtectionHook(StatusType Fatalerror);
#endif

/* KB begin osekCallBackSectionEnd (default) */
/* KB end osekCallBackSectionEnd */

#if osdStackCheck
 #if osdStackUsageMeasurement
  osqFunc1 osStackUsageType osqFunc2 osGetStackUsage(TaskType taskId); /* TR:SPMF08:0007 */
  /* KB begin osekStackUsagePrototypes (overwritten) */
  osqFunc1 osStackUsageType osqFunc2 osGetISRStackUsage(ISRType isrId);
  osqFunc1 osStackUsageType osqFunc2 osGetSystemStackUsage(void);
  /* KB end osekStackUsagePrototypes */
 #endif
#endif


#if !defined osdProvideTimeStamp
#define osdProvideTimeStamp 0
#endif

/* KB begin osekHWosVersionVariant (default) */
/* TR:SPMF29:0001 Start */
/* structure for version and variant coding */
typedef struct
{
   osuint8 ucMagicNumber1;     /* magic number (e.g. for identification in hex files) */
   osuint8 ucMagicNumber2;     /* defined as osuint8 for independancy of byte order   */
   osuint8 ucMagicNumber3;     /*                                                     */
   osuint8 ucMagicNumber4;     /*                                                     */
   osuint8 ucSysVersionMaj;    /* version of operating system, Major                  */
   osuint8 ucSysVersionMin;    /* version of operating system, Minor                  */
   osuint8 ucGenVersionMaj;    /* version of code generator                           */
   osuint8 ucGenVersionMin;    /* version of code generator                           */
   osuint8 ucSysVariant1;      /* general variant coding 1                            */
   osuint8 ucSysVariant2;      /* general variant coding 2                            */
   osuint8 ucOrtiVariant;      /* ORTI version and variant       TR:SPMF14:0011  TR:SPMF29:0003      */ 
   /* KB begin osekTypeSpecVersionVariant (overwritten) */
   osuint8 ucSpecVariant; /* typedef of implementation specific variant coding */
   /* KB end osekTypeSpecVersionVariant */
} osVersionVariantCodingType;
/* TR:SPMF29:0001 End */

/* KB begin osekConstSectionHeaderStart (default) */
/* KB end osekConstSectionHeaderStart */
osqROM0 extern osqROM1 const osqROM2 osVersionVariantCodingType osqROM3 oskVersionVariant;
/* KB begin osekConstSectionHeaderEnd (default) */
/* KB end osekConstSectionHeaderEnd */
/* KB end osekHWosVersionVariant */

/* setup defines for filling up the variant coding structure */
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


/* TR:SPMF12:0005 Start */
#if osdEnableAssertions
   #define osdVariantAssertionsEnabled 1U
#else
   #define osdVariantAssertionsEnabled 0U
#endif
/* TR:SPMF12:0005 End */
#if (osdSC== SC1)
   #define osdVariantSC 0U
#elif (osdSC== SC2)
   #define osdVariantSC 1U
#elif (osdSC== SC3)
   #define osdVariantSC 2U
#elif (osdSC== SC4)
   #define osdVariantSC 3U
#else
#error wrong scalability class
#endif

#if (osdNumberOfScheduleTables>0)
   #define osdVariantFeaturesUsed_ST 1U
#else 
   #define osdVariantFeaturesUsed_ST 0U
#endif
#if (osdNumberOfHiResSchedTabs>0)
   #define osdVariantFeaturesUsed_HRST 1U
#else 
   #define osdVariantFeaturesUsed_HRST 0U
#endif
   #define osdVariantFeaturesUsed_Sync 0U
#if (osdTimingProtectionUsed)
   #define osdVariantFeaturesUsed_TP   1U
#else 
   #define osdVariantFeaturesUsed_TP   0U
#endif

#if osdORTIEnabled
/* osdORTIStdVersion is decimal coded, osdVariantORTIVersion shall be BCD coded */
#define osdVariantORTIVersion ((((osdORTIStdVersion)/100)<<4)|(((osdORTIStdVersion)%100)/10))
#define osdVariantORTIDebug osdORTIDebug
#else
#define osdVariantORTIVersion 0
#define osdVariantORTIDebug   0
#endif /* osdORTIEnabled */

/* KB begin osekDefineSpecVersionVariant (overwritten) */
/* Derivative */
#define osdVariantCompiler    0
#define osdVariantDerivative  0

#if ((defined(__NoFloat__)) || (defined(__SoftwareFloat__)))
   #define osdVariantFPUSupport 0
#else
   #define osdVariantFPUSupport 1
#endif

/* terminate application is not supported in SafeContext */
#ifndef osdTerminateApplicationNotUsed
#define osdTerminateApplicationNotUsed
#endif
/* KB end osekDefineSpecVersionVariant */



/* KB begin osekSpecificHeaderInclude (overwritten) */
#if defined USE_QUOTE_INCLUDES
 #include "osDerivatives.h"
#else
 #include <osDerivatives.h>
#endif
/* KB end osekSpecificHeaderInclude */


 #if defined USE_QUOTE_INCLUDES
  #include "tcbpost.h"
 #else
  #include <tcbpost.h>
 #endif


/* include hardware specific header files after OSEK Typedefinitions */
/* KB begin osekHWincludeHwHeaderPostTypes (overwritten) */
#if defined USE_QUOTE_INCLUDES
#include "osekasm.h"
#else
#include <osekasm.h>
#endif

#if (osdStackCheck == 1)
   #if (osdSC == SC3) || (osdSC == SC4)
      #if (osdMPUSupportInSVMode == 0)
         #define osdSoftwareStackCheck
      #endif
   #else
      #define osdSoftwareStackCheck
   #endif
#endif 
/* KB end osekHWincludeHwHeaderPostTypes */

/* KB begin osekEndOfHModule (overwritten) */
/* KB end osekEndOfHModule */

#if defined __cplusplus
} /* ENDOF extern "C" */
#endif

/*lint -restore re-enable messages*/

#endif/* double include preventer */

/* END OF HEADER osek.h */

