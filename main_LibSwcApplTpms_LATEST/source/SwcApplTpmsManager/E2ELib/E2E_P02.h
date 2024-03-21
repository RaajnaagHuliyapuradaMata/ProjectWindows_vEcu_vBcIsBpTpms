
#if(!defined E2E_P02_H)
#define E2E_P02_H

#include <E2E.h>

#if(defined E2EP02_VENDOR_ID)
#error E2EP02_VENDOR_ID is already defined
#endif

#define E2EP02_VENDOR_ID         1U

#if(defined E2EP02_AR_RELEASE_MAJOR_VERSION)
#error E2EP02_AR_RELEASE_MAJOR_VERSION already defined
#endif

#define E2EP02_AR_RELEASE_MAJOR_VERSION  4U

#if(defined E2EP02_AR_RELEASE_MINOR_VERSION)
#error E2EP02_AR_RELEASE_MINOR_VERSION already defined
#endif

#define E2EP02_AR_RELEASE_MINOR_VERSION  0U

#if(defined E2EP02_AR_RELEASE_REVISION_VERSION)
#error E2EP02_AR_RELEASE_REVISION_VERSION already defined
#endif

#define E2EP02_AR_RELEASE_REVISION_VERSION  3U

#if(defined E2EP02_AR_MAJOR_VERSION)
#error E2EP02_AR_MAJOR_VERSION already defined
#endif

#define E2EP02_AR_MAJOR_VERSION  2U

#if(defined E2EP02_AR_MINOR_VERSION)
#error E2EP02_AR_MINOR_VERSION already defined
#endif

#define E2EP02_AR_MINOR_VERSION  0U

#if(defined E2EP02_AR_PATCH_VERSION)
#error E2EP02_AR_PATCH_VERSION already defined
#endif

#define E2EP02_AR_PATCH_VERSION  0U

#if(defined E2EP02_SW_MAJOR_VERSION)
#error E2EP02_SW_MAJOR_VERSION already defined
#endif

#define E2EP02_SW_MAJOR_VERSION  2U

#if(defined E2EP02_SW_MINOR_VERSION)
#error E2EP02_SW_MINOR_VERSION already defined
#endif

#define E2EP02_SW_MINOR_VERSION  1U

#if(defined E2EP02_SW_PATCH_VERSION)
#error E2EP02_SW_PATCH_VERSION already defined
#endif

#define E2EP02_SW_PATCH_VERSION  4U

typedef struct{
   uint16 DataLength;

   uint8  DataIDList[16];

   uint8  MaxDeltaCounterInit;

   uint8  MaxNoNewOrRepeatedData;

   uint8  SyncCounterInit;

} E2E_P02ConfigType;

typedef struct{
   uint8 Counter;

} E2E_P02SenderStateType;

typedef enum {
   E2E_P02STATUS_OK = 0x0U,

   E2E_P02STATUS_NONEWDATA = 0x1U,

   E2E_P02STATUS_WRONGCRC = 0x2U,

   E2E_P02STATUS_SYNC = 0x3U,

   E2E_P02STATUS_INITIAL = 0x4U,

   E2E_P02STATUS_REPEATED = 0x8U,

   E2E_P02STATUS_OKSOMELOST = 0x20U,

   E2E_P02STATUS_WRONGSEQUENCE = 0x40U

} E2E_P02ReceiverStatusType;

typedef struct{
   E2E_P02ReceiverStatusType Status;

   uint8   LastValidCounter;

   uint8   MaxDeltaCounter;

   boolean WaitForFirstData;

   boolean NewDataAvailable;

   uint8   LostData;

   uint8   NoNewOrRepeatedDataCounter;

   uint8   SyncCounter;

} E2E_P02ReceiverStateType;

#define E2E_START_SEC_CODE
#include <MemMap.h>

extern FUNC(Std_ReturnType, E2E_CODE) E2E_P02Protect
(
   P2CONST(E2E_P02ConfigType, AUTOMATIC, E2E_APPL_CONST) Config,
   P2VAR(E2E_P02SenderStateType, AUTOMATIC, E2E_APPL_DATA) State,
   P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) Data
);

extern FUNC(Std_ReturnType, E2E_CODE) E2E_P02Check
(
   P2CONST(E2E_P02ConfigType, AUTOMATIC, E2E_APPL_CONST) Config,
   P2VAR(E2E_P02ReceiverStateType, AUTOMATIC, E2E_APPL_DATA) State,
   P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) Data
);

#define E2E_STOP_SEC_CODE
#include <MemMap.h>

#endif

