

#if ! defined __TCBPOST_H__
#define __TCBPOST_H__
#if defined USE_QUOTE_INCLUDES
 #include "vrm.h"
#else
 #include <vrm.h>
#endif

#define osdVrmGenMajRelNum 1
#define osdVrmGenMinRelNum 1
#if defined USE_QUOTE_INCLUDES
 #include "vrm.h"
#else
 #include <vrm.h>
#endif

#define SystemTimer ((CounterType) 0)
#define osdTimerOSTMID SystemTimer
#define osClearTimerInterruptPoint(cnt)
#define osHandleCounterInterrupt(cnt) osHandleCounterInterruptStd(cnt)
#define osSetTimerInterruptPoint(cnt, time) osdFALSE
#define osInsertMinHeap(newItem, h, cnt) osInsertMinHeapStd((newItem), (h), (cnt))
#define osGetCurrentTime(cnt) osCounter[cnt]

#if(osdNumberOfAlarms + osdNumberOfScheduleTables>0)
   extern osqTcbRAM1 volatile osqTcbRAM2 TickType osqTcbRAM3 osAlarmTime[osdNumberOfAlarms + osdNumberOfScheduleTables];
#else
   extern osqTcbRAM1 volatile osqTcbRAM2 TickType osqTcbRAM3 osAlarmTime[1];
#endif
#if(osdNumberOfAlarms > 0)
      extern osqTcbRAM1 volatile osqTcbRAM2 osuint8 osqTcbRAM3 osAlarmActivated[osdNumberOfAlarms];
#else
      extern osqTcbRAM1 volatile osqTcbRAM2 osuint8 osqTcbRAM3 osAlarmActivated[1];
#endif

   extern osqTcbRAM1 osqTcbRAM2 osHeapElementType osqTcbRAM3 osSystemTimerHeap[10];

#if(osdNumberOfAlarms > 0)
   extern osqTcbRAM1 volatile osqTcbRAM2 TickType osqTcbRAM3 osAlarmCycleTime[osdNumberOfAlarms];
#else
   extern osqTcbRAM1 volatile osqTcbRAM2 TickType osqTcbRAM3 osAlarmCycleTime[1];
#endif

#if(osdNumberOfCounters > 0)
   extern osqROM0 osqROM1 const osqROM2 osHeapType osqROM3 oskAlarmHeaps[1];
   extern osqROM0 osqROM1 const osqROM2 osAlarmIndexType osqROM3 oskAlarmHeapSize[1];
#endif

#if(osdNumberOfAlarms > 0)
      extern osqROM0 osqROM1 const osqROM2 TickType osqROM3 oskStaticAlarmTime[osdNumberOfAlarms];
      extern osqROM0 osqROM1 const osqROM2 TickType osqROM3 oskStaticAlarmCycleTime[osdNumberOfAlarms];
#else
      osqROM0 extern osqROM1 const osqROM2 TickType osqROM3 oskStaticAlarmTime[1];
      osqROM0 extern osqROM1 const osqROM2 TickType osqROM3 oskStaticAlarmCycleTime[1];
#endif

#if(osdNumberOfAlarms > 0)
      osqROM0 extern osqROM1 const osqROM2 TaskType osqROM3 oskAlarmTask[osdNumberOfAlarms];
      #if(osdNumberOfAlarmSetEvent > 0)
         osqROM0 extern osqROM1 const osqROM2 EventMaskType osqROM3 oskAlarmEvent[osdNumberOfAlarms];
      #else
         osqROM0 extern osqROM1 const osqROM2 EventMaskType osqROM3 oskAlarmEvent[1];
      #endif
      osqROM0 extern osqROM1 const osqROM2 osuint8 osqROM3 oskAlarmAction[osdNumberOfAlarms];
      #if(osdNumberOfAlarmCallback > 0)
         osqROM0 extern osqROM1 const osqROM2 osAlarmCallbackType osqROM3 oskAlarmCallback[osdNumberOfAlarms];
      #else
         osqROM0 extern osAlarmCallbackType osqROM1 const osqROM2 osqROM3 oskAlarmCallback[1];
      #endif
      #if(osdNumberOfAlarmIncrementCounter > 0)
         osqROM0 extern osqROM1 const osqROM2 CounterType osqROM3 oskAlarmIncrementCounterID[osdNumberOfAlarms];
      #else
         osqROM0 extern osqROM1 const osqROM2 CounterType osqROM3 oskAlarmIncrementCounterID[1];
      #endif
#else
      osqROM0 extern osqROM1 const osqROM2 TaskType osqROM3 oskAlarmTask[1];
      osqROM0 extern osqROM1 const osqROM2 EventMaskType osqROM3 oskAlarmEvent[1];
      osqROM0 extern osqROM1 const osqROM2 osuint8 osqROM3 oskAlarmAction[1];
      osqROM0 extern osAlarmCallbackType osqROM1 const osqROM2 osqROM3 oskAlarmCallback[1];
      osqROM0 extern osqROM1 const osqROM2 CounterType osqROM3 oskAlarmIncrementCounterID[1];
#endif

#if(osdNumberOfScheduleTables > 0)
extern osqROM0 osqROM1 const osqROM2 CounterType osqROM3 oskCounterOfST[osdNumberOfScheduleTables];
extern osqROM0 osqROM1 const osqROM2 TickType osqROM3 oskSTMaxAllowed[osdNumberOfScheduleTables];
extern osqROM0 osqROM1 const osqROM2 TickType osqROM3 oskScheduleTableInitialOffset[osdNumberOfScheduleTables];
extern osqROM0 osqROM1 const osqROM2 TickType osqROM3 oskAutostartScheduleTableOffset[osdNumberOfScheduleTables];
extern osqROM0 osqROM1 const osqROM2 TickType osqROM3 oskPrecision[osdNumberOfScheduleTables];
extern osqROM0 osqROM1 const osqROM2 osSTIndexType osqROM3 oskSTStartIndex[osdNumberOfScheduleTables];
extern osqROM0 osqROM1 const osqROM2 osuint8 osqROM3 oskScheduleTableAutoStart      [osdNumberOfScheduleTables];
extern osqROM0 osqROM1 const osqROM2 osuint8 osqROM3 oskScheduleTableAutoStartType  [osdNumberOfScheduleTables];
osqRAM0 extern osqRAM1 volatile osqRAM2 osSTIndexType           osqRAM3 osSTCurrentIndex[osdNumberOfScheduleTables];
osqRAM0 extern osqRAM1 volatile osqRAM2 ScheduleTableStatusType osqRAM3 osSTState[osdNumberOfScheduleTables];
osqRAM0 extern osqRAM1 volatile osqRAM2 ScheduleTableType       osqRAM3 osSTNextTable[osdNumberOfScheduleTables];
#else
extern osqROM0 osqROM1 const osqROM2 CounterType    osqROM3 oskCounterOfST                 [1];
extern osqROM0 osqROM1 const osqROM2 TickType       osqROM3 oskSTMaxAllowed                [1];
extern osqROM0 osqROM1 const osqROM2 osSTOffsetType osqROM3 oskScheduleTableInitialOffset  [1];
extern osqROM0 osqROM1 const osqROM2 TickType       osqROM3 oskAutostartScheduleTableOffset[1];
extern osqROM0 osqROM1 const osqROM2 TickType       osqROM3 oskPrecision                   [1];
extern osqROM0 osqROM1 const osqROM2 osSTIndexType  osqROM3 oskSTStartIndex                [1];
extern osqROM0 osqROM1 const osqROM2 osuint8        osqROM3 oskScheduleTableAutoStart      [1];
extern osqROM0 osqROM1 const osqROM2 osuint8        osqROM3 oskScheduleTableAutoStartType  [1];
osqRAM0 extern osqRAM1 volatile osqRAM2 osSTIndexType           osqRAM3 osSTCurrentIndex[1];
osqRAM0 extern osqRAM1 volatile osqRAM2 ScheduleTableStatusType osqRAM3 osSTState[1];
osqRAM0 extern osqRAM1 volatile osqRAM2 ScheduleTableType       osqRAM3 osSTNextTable[1];
#endif

#define OS_MS2TICKS_SystemTimer(x) ((TickType)((((osTimeComputationType)(x)) * 1.00000)+0.5))
#define OS_TICKS2MS_SystemTimer(x) ((PhysicalTimeType)((((osTimeComputationType)(x)) * 1.00000)+0.5))
#define OS_NS2TICKS_SystemTimer(x) ((TickType)((((osTimeComputationType)(x)) * 1.00000e-006)+0.5))
#define OS_TICKS2NS_SystemTimer(x) ((PhysicalTimeType)((((osTimeComputationType)(x)) * 1.00000e+006)+0.5))
#define OS_SEC2TICKS_SystemTimer(x) ((TickType)((((osTimeComputationType)(x)) * 1000.00)+0.5))
#define OS_TICKS2SEC_SystemTimer(x) ((PhysicalTimeType)((((osTimeComputationType)(x)) * 0.00100000)+0.5))
#define OS_US2TICKS_SystemTimer(x) ((TickType)((((osTimeComputationType)(x)) * 0.00100000)+0.5))
#define OS_TICKS2US_SystemTimer(x) ((PhysicalTimeType)((((osTimeComputationType)(x)) * 1000.00)+0.5))

extern osqTcbRAM1 volatile osqTcbRAM2 TickType osqTcbRAM3 osCounter[1];

osqROM0 extern osqROM1 const osqROM2 TickType osqROM3 oskCounterMaxAllowedValue[1];

osqROM0 extern osqROM1 const osqROM2 TickType osqROM3 oskCounterInternalMaximumValue[1];

osqROM0 extern osqROM1 const osqROM2 TickType osqROM3 oskCounterHalfrange[1];

osqROM0 extern osqROM1 const osqROM2 TickType osqROM3 oskCounterTicksPerBase[1];

osqROM0 extern osqROM1 const osqROM2 TickType osqROM3 oskCounterMinCycle[1];

osqROM0 extern osqROM1 const osqROM2 TickType osqROM3 oskCounterReloadValue[1];

osqROM0 extern osqROM1 const osqROM2 CoreIdType osqROM3 oskCounterCoreId[1];

osqROM0 extern osqROM1 const osqROM2 TickType osqROM3 oskCounterHiResMaxHardwareValueHalf[1];

osqROM0 extern osqROM1 const osqROM2 TickType osqROM3 oskHiResTimerBitMask[1];

osqROM0 extern osqROM1 const osqROM2 TickType osqROM3 oskHWTimerSemiCount[1];

osqROM0 extern osqROM1 const osqROM2 TickType osqROM3 oskMinTimeBetweenTimerIrqs[1];

extern osqTcbRAM1 volatile osqTcbRAM2 TickType osqTcbRAM3 osLastHighResTimerIrq[1];

extern osqTcbRAM1 volatile osqTcbRAM2 TickType osqTcbRAM3 osNextAllowedTimerInt[1];

osqROM0 extern osqROM1 const osqROM2 osuint8 osqROM3 oskAlarmCounterRef[9];

#define osReleaseHiResTimerISR(counterId)

#define osTriggerHiResTimerISR(counterId)

#define osGetHWTimerCounterValue(counterId) 0

#define osSetHWTimerDeltaValue(counterId,timeToSet)

#define osSetHWTimerCompareValue(counterId,timeToSet)
osqROM0 extern osqPTcbRAM1 volatile osqPTcbRAM2 TaskType osqPTcbRAM3 * osqROM1 const osqROM2 osqROM3 oskQActivationQueues[osdNumberOfPriorities];
osqROM0 extern osqROM1 const osqROM2 osQEntryCountType osqROM3 oskQMaxActivations[osdNumberOfPriorities];
#if((CC == BCC2) || (CC == ECC2))
   #if(osdNumberOfAllTasks > 0)
      extern volatile osqTcbRAM1 osqTcbRAM2 osActivationCountType osqTcbRAM3 osTcbActivationCount[osdNumberOfAllTasks];
   #else
      extern volatile osqTcbRAM1 osqTcbRAM2 osActivationCountType osqTcbRAM3 osTcbActivationCount[1];
   #endif
#endif

extern osqTcbRAM1 osqTcbRAM2 osCtrlVarType osqTcbRAM3 osCtrlVarsCore0;
   extern osqTcbRAM1 volatile osqTcbRAM2 EventMaskType osqTcbRAM3 osTcbWaitEventMask[osdNumberOfExtendedTasks];

#if((osdSC == SC3) || (osdSC == SC4))
   extern osqTcbRAM1 volatile osqTcbRAM2 ApplicationStateType osqTcbRAM3 osApplicationState [osdNumberOfApplications];
#endif

#if(osdNumberOfAllTasks > 0)
  osqROM0 extern osqROM1 const osqROM2 osTaskFlagType osqROM3 oskTcbTaskFlags[osdNumberOfAllTasks];
#if(osdNumberOfExtendedTasks > 0) || osdLib
   extern osqTcbRAM1 volatile osqTcbRAM2 EventMaskType osqTcbRAM3 osTcbSetEventMask[osdNumberOfExtendedTasks];
#endif
#else
   #if STATUS_LEVEL == EXTENDED_STATUS
      osqROM0 extern osqROM1 const osqROM2 osTaskFlagType osqROM3 oskTcbTaskFlags[1];
   #endif
#if(osdNumberOfExtendedTasks > 0) || osdLib
      extern osqTcbRAM1 volatile osqTcbRAM2 EventMaskType osqTcbRAM3 osTcbSetEventMask[1];
#endif
#endif

#if(osdNumberOfAllTasks > 0)
   extern osqTcbRAM1 volatile osqTcbRAM2 osTaskStateType osqTcbRAM3 osTcbTaskState[osdNumberOfAllTasks];
   #if osdORTIDebug
    extern osqTcbRAM1 osqTcbRAM2 osPrioType osqTcbRAM3 osTcbActualPrio[osdNumberOfAllTasks];
    extern osqTcbRAM1 osqTcbRAM2 osuint8 osqTcbRAM3 osTcbORTIServiceId[osdNumberOfAllTasks];
   #endif
   #if STATUS_LEVEL == EXTENDED_STATUS
    #if(osdNumberOfInternalResources > 0) || (osdNumberOfInterruptResources > 0)
     extern osqTcbRAM1 osqTcbRAM2 osuint8 osqTcbRAM3 osTcbResourceCounter[osdNumberOfAllTasks];
    #endif
   #endif

#else
   extern osqTcbRAM1 volatile osqTcbRAM2 osTaskStateType osqTcbRAM3 osTcbTaskState[1];
   #if osdORTIDebug
   extern osqTcbRAM1 osqTcbRAM2 osPrioType osqTcbRAM3 osTcbActualPrio[1];
   extern osqTcbRAM1 osqTcbRAM2 osuint8 osqTcbRAM3 osTcbORTIServiceId[1];
   #endif

   #if STATUS_LEVEL == EXTENDED_STATUS
   #if(osdNumberOfInternalResources > 0) || (osdNumberOfInterruptResources > 0)
   extern osqTcbRAM1 osqTcbRAM2 osuint8 osqTcbRAM3 osTcbResourceCounter[1];
   #endif
   #endif
#endif

#if(osdNumberOfAllResources > 0)
   #if((!defined(osdGetResourceNotUsed)) || (!defined(osdReleaseResourceNotUsed)))
      extern osqTcbRAM1 osqTcbRAM2 osPrioType osqTcbRAM3 osResSavedPrio[osdNumberOfAllResources];
   #endif
   #if STATUS_LEVEL == EXTENDED_STATUS && ((!defined(osdGetResourceNotUsed)) || (!defined(osdReleaseResourceNotUsed)))
      extern osqTcbRAM1 osqTcbRAM2 osResCounterType osqTcbRAM3 osResOccupationCounter[osdNumberOfAllResources];
   #endif
   #if((STATUS_LEVEL == EXTENDED_STATUS) && osdEnableAssertions && ((!defined(osdGetResourceNotUsed)) || (!defined(osdReleaseResourceNotUsed)))) || osdORTIDebug
      extern osqTcbRAM1 osqTcbRAM2 TaskType osqTcbRAM3 osResActualTask[osdNumberOfAllResources];
   #endif

   #if(!defined(osdGetResourceNotUsed)) || (!defined(osdReleaseResourceNotUsed))
      extern osqROM0 osqROM1 const osqROM2 osPrioType osqROM3 oskResCeilingPrio[osdNumberOfAllResources];
   #endif
#else
   #if((!defined(osdGetResourceNotUsed)) || (!defined(osdReleaseResourceNotUsed)))
      extern osqTcbRAM1 osqTcbRAM2 osPrioType osqTcbRAM3 osResSavedPrio[1];
   #endif
   #if STATUS_LEVEL == EXTENDED_STATUS && ((!defined(osdGetResourceNotUsed)) || (!defined(osdReleaseResourceNotUsed)))
      extern osqTcbRAM1 osqTcbRAM2 osResCounterType osqTcbRAM3 osResOccupationCounter[1];
   #endif
   #if((STATUS_LEVEL == EXTENDED_STATUS) && osdEnableAssertions && ((!defined(osdGetResourceNotUsed)) || (!defined(osdReleaseResourceNotUsed)))) || osdORTIDebug
      extern osqTcbRAM1 osqTcbRAM2 TaskType osqTcbRAM3 osResActualTask[1];
   #endif

   #if(!defined(osdGetResourceNotUsed)) || (!defined(osdReleaseResourceNotUsed))
   extern osqROM0 osqROM1 const osqROM2 osPrioType osqROM3 oskResCeilingPrio[1];
   #endif
#endif
#if(!defined(osdGetResourceNotUsed)) || (!defined(osdReleaseResourceNotUsed))
 #if(osdNumberOfTaskResources > 0)
   #if(osdRTSize > 1)
      extern osqROM0 osqROM1 const osqROM2 osPrioOffsetType osqROM3 oskResCeilingPrioOffset[osdNumberOfTaskResources];
   #endif
   extern osqROM0 osqROM1 const osqROM2 osPrioFlagType osqROM3 oskResCeilingPrioMask[osdNumberOfTaskResources];
 #else
   #if(osdRTSize > 1)
      extern osqROM0 osqROM1 const osqROM2 osPrioOffsetType osqROM3 oskResCeilingPrioOffset[1];
   #endif
   extern osqROM0 osqROM1 const osqROM2 osPrioFlagType osqROM3 oskResCeilingPrioMask[1];
 #endif
#endif

#if(osdNumberOfInternalResources > 0)
   extern osqROM0 osqROM1 const osqROM2 osPrioType osqROM3 oskResInternalCeilingPrio[osdNumberOfAllTasks];
   extern osqROM0 osqROM1 const osqROM2 osPrioFlagType osqROM3 oskResInternalCeilingPrioMask[osdNumberOfAllTasks];
   #if(osdRTSize > 1)
      extern osqROM0 osqROM1 const osqROM2 osPrioOffsetType osqROM3 oskResInternalCeilingPrioOffset[osdNumberOfAllTasks];
   #endif
#endif
#if(osdNumberOfSemaphores > 0)
   extern osqTcbRAM1 osqTcbRAM2 osuint8 osqTcbRAM3 osSemaphoreState[osdNumberOfSemaphores];
   #if(osdNumberOfExtendedTasks == 0) && osdLib
   extern osqTcbRAM1 volatile osqTcbRAM2 osSemaphoreType osqTcbRAM3 osTcbWaitForSemaphore[1];
   #else
   extern osqTcbRAM1 volatile osqTcbRAM2 osSemaphoreType osqTcbRAM3 osTcbWaitForSemaphore[osdNumberOfExtendedTasks];
   #endif
   #if(osdKillTaskIsrPossible || (osdSC== SC3) || (osdSC== SC4))
      extern osqTcbRAM1 volatile osqTcbRAM2 TaskType osqTcbRAM3 osSemaOwner[osdNumberOfSemaphores];
   #endif
#endif

#if osdLib
#define osrRTSize                     oskRTSize
#define osrNumberOfPriorities         oskNumberOfPriorities
#define osrNumberOfAppModes           oskNumberOfAppModes
#define osrNumberOfAllTasks           oskNumberOfAllTasks
#define osrNumberOfAllResources       oskNumberOfAllResources
#define osrNumberOfTaskResources      oskNumberOfTaskResources
#define osrNumberOfInterruptResources oskNumberOfInterruptResources
#define osrNumberOfInternalResources  oskNumberOfInternalResources
#define osrNumberOfExtendedTasks      oskNumberOfExtendedTasks
#define osrNumberOfAlarms             oskNumberOfAlarms
#define osrNumberOfScheduleTables     oskNumberOfScheduleTables
#define osrNumberOfSemaphores         oskNumberOfSemaphores
#define osrSystemTimer                oskSystemTimer
#define osrNumberOfCounters           oskNumberOfCounters

   extern const osRTSizeType               oskRTSize;
   extern const osAppModeIndexType         oskNumberOfAppModes;
   extern const osTaskIndexType            oskNumberOfAllTasks;
   extern const osTaskIndexType            oskNumberOfExtendedTasks;
   extern const osPrioType                 oskNumberOfPriorities;
   extern const osResourceIndexType        oskNumberOfAllResources;
   extern const osResourceIndexType        oskNumberOfTaskResources;
   extern const osResourceIndexType        oskNumberOfInterruptResources;
   extern const osResourceIndexType        oskNumberOfInternalResources;

   extern const osAlarmIndexType           oskNumberOfAlarms;

   extern const ScheduleTableType          oskNumberOfScheduleTables;
   extern const osSemaphoreType            oskNumberOfSemaphores;
   extern const CounterType                oskSystemTimer;
   extern const CounterType                oskNumberOfCounters;

   extern const TickType oskMaxAllowedValue;
   extern const TickType oskTicksPerBase;
   extern const TickType oskMinCycle;
   extern const osuint8 oskAlarmAutoStart[];

   extern const osuint8 oskTcbAutoStart[];

   extern const osVersionVariantCodingType oskLibVersionVariant;

#else
#define osrRTSize                      osdRTSize
#define osrNumberOfPriorities          osdNumberOfPriorities
#define osrNumberOfAppModes            osdNumberOfAppModes
#define osrNumberOfAllTasks            osdNumberOfAllTasks
#define osrNumberOfAllResources        osdNumberOfAllResources
#define osrNumberOfTaskResources       osdNumberOfTaskResources
#define osrNumberOfInterruptResources  osdNumberOfInterruptResources
#define osrNumberOfInternalResources   osdNumberOfInternalResources
#define osrNumberOfExtendedTasks       osdNumberOfExtendedTasks
#define osrNumberOfAlarms              osdNumberOfAlarms
#define osrNumberOfScheduleTables      osdNumberOfScheduleTables
#define osrNumberOfSemaphores          osdNumberOfSemaphores
#define osrNumberOfCounters            osdNumberOfCounters

#endif

osqROM0 extern osStackPtrType osqROM1 const osqROM2 osqROM3  oskSystemStackTop;

#if(osdKillTaskIsrPossible || (osdSC == SC3) || (osdSC == SC4))
#if(osdNumberOfCat2ISRs > 0)
   extern osqTcbRAM1 osqTcbRAM2 osResourceIndexType osqTcbRAM3 osIcbLockedResource[osdNumberOfCat2ISRs];
#else
   extern osqTcbRAM1 osqTcbRAM2 osResourceIndexType osqTcbRAM3 osIcbLockedResource[1];
#endif
#endif

#define HufTPMS_Task2 ((TaskType)0)
#define HufTPMS_Task3 ((TaskType)1)
#define HufTPMS_Task4 ((TaskType)2)
#define SchM_SyncTask_1 ((TaskType)3)
#define SchM_SyncTask_2 ((TaskType)4)
#define SchM_AsyncTask_1 ((TaskType)5)
#define SchM_AsyncTask_2 ((TaskType)6)
#define HufTPMS_Task1 ((TaskType)7)

void HufTPMS_Task2func(void);
void HufTPMS_Task3func(void);
void HufTPMS_Task4func(void);
void SchM_SyncTask_1func(void);
void SchM_SyncTask_2func(void);
void SchM_AsyncTask_1func(void);
void SchM_AsyncTask_2func(void);
void HufTPMS_Task1func(void);

osqROM0 extern osqROM1 const osqROM2 osTaskFlagType osqROM3 oskTcbTaskFlags[osdNumberOfAllTasks];
osqROM0 extern osqROM1 const osqROM2 osPrioFlagType osqROM3 oskTcbReadyPrioMask[osdNumberOfAllTasks];
#if(osdRTSize > 1)
osqROM0 extern osqROM1 const osqROM2 osPrioOffsetType osqROM3 oskTcbReadyPrioOffset[osdNumberOfAllTasks];
#endif
osqROM0 extern osqROM1 const osqROM2 osPrioType osqROM3 oskTcbHomePrio[osdNumberOfAllTasks];
#if(CC == BCC2) || (CC == ECC2)
osqROM0 extern osqROM1 const osqROM2 osActivationCountType osqROM3 oskTcbAllowedActivations[osdNumberOfAllTasks];
#endif

#define osdIsrADC0_SG1_CAT2_ISRCat 2
#define osdIsrCanIsrGlobalStatusCat 2
#define osdIsrCanIsrRxFifoCat 2
#define osdIsrCanIsrStatus_0Cat 2
#define osdIsrCanIsrTx_0Cat 2
#define osdIsrCanIsrWakeup_0Cat 2
#define osdIsrIsrIntP11Cat 2
#define osdIsrosOstmInterrupt_c0Cat 2
#define osdIsrOsIsrCat 1
#define osdIsrosTrapDispatcher_c0Cat 1

#define ADC0_SG1_CAT2_ISR ((ISRType)0)
#define CanIsrGlobalStatus ((ISRType)1)
#define CanIsrRxFifo ((ISRType)2)
#define CanIsrStatus_0 ((ISRType)3)
#define CanIsrTx_0 ((ISRType)4)
#define CanIsrWakeup_0 ((ISRType)5)
#define IsrIntP11 ((ISRType)6)
#define osOstmInterrupt_c0 ((ISRType)7)

#if((osdSC== SC3) || (osdSC== SC4))
#endif

void ADC0_SG1_CAT2_ISRfunc(void);
void CanIsrGlobalStatusfunc(void);
void CanIsrRxFifofunc(void);
void CanIsrStatus_0func(void);
void CanIsrTx_0func(void);
void CanIsrWakeup_0func(void);
void IsrIntP11func(void);
void osOstmInterruptfunc(void);
void _usr_init(void);
void osTrapDispatcher_c0(void);

void ADC0_SG1_CAT2_ISR_CAT2(void);
void CanIsrGlobalStatus_CAT2(void);
void CanIsrRxFifo_CAT2(void);
void CanIsrStatus_0_CAT2(void);
void CanIsrTx_0_CAT2(void);
void CanIsrWakeup_0_CAT2(void);
void IsrIntP11_CAT2(void);
void osOstmInterrupt_c0_CAT2(void);

#if(osdNumberOfAlarms > 0)
 osqROM0 extern osqROM1 const osqROM2 osuint8 osqROM3 oskAlarmAutoStart[osdNumberOfAlarms];
#endif

#if(osdNumberOfAlarms > 0)
extern osqROM0 osqROM1 const osqROM2 osuint8 osqROM3 oskAlarmAutoStartType  [osdNumberOfAlarms];
#endif

#if(osdNumberOfAllTasks > 0)
 osqROM0 extern osqROM1 const osqROM2 osuint8 osqROM3 oskTcbAutoStart[osdNumberOfAllTasks];
#endif

#define osdNumberOfAppModes 1
#define OsAppMode 1

#define Rte_Ev_Cyclic_HufTPMS_Task4_0_1s ((EventMaskType)(0x00000001))
#define Rte_Ev_Cyclic_HufTPMS_Task4_0_200ms ((EventMaskType)(0x00000002))
#define Rte_Ev_OnRx_HufTPMS_Task3_CpApHufTPMSmgr_PP_EnvData_DE_tEnvData ((EventMaskType)(0x00000001))
#define Rte_Ev_Run_CpApHufTPMSdia_RCtApHufTPMSdia_PN14SupBatStat ((EventMaskType)(0x00000002))
#define Rte_Ev_Run_CpApHufTPMSdia_RCtApHufTPMSdia_RdEvcCfgBit010C ((EventMaskType)(0x00000004))
#define Rte_Ev_Run_CpApHufTPMSdia_RCtApHufTPMSdia_RdEvcCfgBit0132 ((EventMaskType)(0x00000008))
#define Rte_Ev_Run_CpApHufTPMSdia_RCtApHufTPMSdia_RdTesterPresent ((EventMaskType)(0x00000001))
#define Rte_Ev_Run_CpApHufTPMSdia_RCtApHufTPMSdia_ReceiveTelData ((EventMaskType)(0x00000010))
#define Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_GenInternalClock ((EventMaskType)(0x00000004))
#define Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdDateTm ((EventMaskType)(0x00000002))
#define Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdEngCtrl ((EventMaskType)(0x00000004))
#define Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdEnvPressure ((EventMaskType)(0x00000008))
#define Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdEnvTemperature ((EventMaskType)(0x00000010))
#define Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdGrBac ((EventMaskType)(0x00000020))
#define Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdIgnStat ((EventMaskType)(0x00000040))
#define Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdOdo ((EventMaskType)(0x00000080))
#define Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdPN14EOLDispRq ((EventMaskType)(0x00000100))
#define Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdSupPN14BatStat ((EventMaskType)(0x00000200))
#define Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdTpmActvRq ((EventMaskType)(0x00000400))
#define Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdVehSpeed ((EventMaskType)(0x00000800))
#define Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdWhlPlsCnt ((EventMaskType)(0x00001000))
#define Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_ReceiveTelData ((EventMaskType)(0x00000020))
#define Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_ReceiveWAState ((EventMaskType)(0x00000040))
#define Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_ReceiveWarnOut ((EventMaskType)(0x00000080))
#define Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutEngCtrl ((EventMaskType)(0x00002000))
#define Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutEnvPressure ((EventMaskType)(0x00004000))
#define Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutIcBasicInfo ((EventMaskType)(0x00008000))
#define Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutIcDateTime ((EventMaskType)(0x00010000))
#define Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutIcSettings ((EventMaskType)(0x00020000))
#define Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutIgnStat ((EventMaskType)(0x00040000))
#define Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutPN14EOLDispRq ((EventMaskType)(0x00080000))
#define Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutSupPN14BatStat ((EventMaskType)(0x00100000))
#define Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutWhlPlsCnt ((EventMaskType)(0x00200000))
#define Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_WrDisplayMsg ((EventMaskType)(0x00000100))
#define Rte_Ev_Run_CpCdHufTPMSrfd_RCtCdHufTPMSrfd_ChkRfStruct ((EventMaskType)(0x00400000))
#define SchM_AsyncEvent_1 ((EventMaskType)(0x00000001))
#define SchM_AsyncEvent_2 ((EventMaskType)(0x00000001))
#define SchM_SyncEvent_1 ((EventMaskType)(0x00000001))
#define SchM_SyncEvent_2 ((EventMaskType)(0x00000001))

#define Rte_Al_TE_CpApHufTPMSmgr_RCtApHufTPMSmgr_GenInternalClock ((AlarmType)0)
#define Rte_Al_TE_CpApHufTPMSmgr_RCtApHufTPMSmgr_WrDisplayMsg ((AlarmType)1)
#define Rte_Al_TE_CpCdHufTPMSrfd_RCtCdHufTPMSrfd_ChkRfStruct ((AlarmType)2)
#define Rte_Al_TE_HufTPMS_Task4_0_1s ((AlarmType)3)
#define Rte_Al_TE_HufTPMS_Task4_0_200ms ((AlarmType)4)
#define SchM_Alarm_Async_1 ((AlarmType)5)
#define SchM_Alarm_Async_2 ((AlarmType)6)
#define SchM_Alarm_Sync_1 ((AlarmType)7)
#define SchM_Alarm_Sync_2 ((AlarmType)8)

#if(osdNumberOfAlarmActivateTask > 0) || (osdNumberOfAlarmSetEvent > 0)

osqROM0 extern osqROM1 const osqROM2 TaskType osqROM3 oskAlarmTask[osdNumberOfAlarms];
#endif

#if osdNumberOfAlarmSetEvent > 0

osqROM0 extern osqROM1 const osqROM2 EventMaskType osqROM3 oskAlarmEvent[osdNumberOfAlarms];
#endif

#if osdNumberOfAlarmCallback > 0

osqROM0 extern osAlarmCallbackType osqROM1 const osqROM2 osqROM3 oskAlarmCallback[osdNumberOfAlarms];
#endif

#if osdNumberOfAlarmIncrementCounter > 0

osqROM0 extern osqROM1 const osqROM2 CounterType osqROM3 oskAlarmIncrementCounterID[osdNumberOfAlarms];
#endif

#pragma ghs startdata

extern osuint32 osExceptionVectorTable_c0[];
extern osuint32 osEIINTVectorTable_c0[];
#pragma ghs enddata

#if(osdKillTaskIsrPossible || (osdSC== SC3) || (osdSC== SC4))
#if(osdNumberOfAllTasks > 0)
   extern osqTcbRAM1 osqTcbRAM2 osResourceIndexType osqTcbRAM3 osTcbLockedResource[osdNumberOfAllTasks];
#else
   extern osqTcbRAM1 osqTcbRAM2 osResourceIndexType osqTcbRAM3 osTcbLockedResource[1];
#endif
#endif

#define RES_SCHEDULER ((ResourceType)0)

#if(STATUS_LEVEL == EXTENDED_STATUS) && osdEnableAssertions
 #if((!defined(osdGetResourceNotUsed)) || (!defined(osdReleaseResourceNotUsed)))
osqROM0 extern osqROM1 const osqROM2 osResAccessMaskType osqROM3 oskResAccessMask[osdNumberOfAllResources][1];

 #endif
#endif

#if(osdKillTaskIsrPossible || (osdSC == SC3) || (osdSC == SC4))
#if(osdNumberOfAllResources > 0)
   extern osqTcbRAM1 osqTcbRAM2 osResourceIndexType osqTcbRAM3 osResNextLockedResource[osdNumberOfAllResources];
#else
   extern osqTcbRAM1 osqTcbRAM2 osResourceIndexType osqTcbRAM3 osResNextLockedResource[1];
#endif
#endif

#if((osdSC== SC3) || (osdSC== SC4))
#endif

#define OSMAXALLOWEDVALUE_SystemTimer 0x7fffffffUL

#define OSMINCYCLE_SystemTimer 1

#define OSTICKSPERBASE_SystemTimer 40000

#define OSSECONDSPERTICK_SystemTimer 0.00100000

#endif
