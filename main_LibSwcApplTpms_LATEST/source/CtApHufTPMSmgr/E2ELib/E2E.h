
#if(!defined E2E_H)
#define E2E_H



#include <Std_Types.h>          
#include <Platform_Types.h>     





#if(defined E2E_E_INPUTERR_NULL) 
#error E2E_E_INPUTERR_NULL is already defined
#endif


#define E2E_E_INPUTERR_NULL 0x13U

#if(defined E2E_E_INPUTERR_WRONG) 
#error E2E_E_INPUTERR_WRONG is already defined
#endif


#define E2E_E_INPUTERR_WRONG 0x17U

#if(defined E2E_E_INTERR) 
#error E2E_E_INTERR is already defined
#endif


#define E2E_E_INTERR 0x19U

#if(defined E2E_E_OK) 
#error E2E_E_OK is already defined
#endif


#define E2E_E_OK 0U

#if(defined E2E_E_INVALID) 
#error E2E_E_INVALID is already defined
#endif


#define E2E_E_INVALID 0xFFU



#if(defined E2E_VENDOR_ID) 
#error E2E_VENDOR_ID is already defined
#endif

#define E2E_VENDOR_ID         1U



#if(defined E2E_MODULE_ID) 
#error E2E_MODULE_ID already defined
#endif

#define E2E_MODULE_ID         207U



#if(defined E2E_AR_RELEASE_MAJOR_VERSION) 
#error E2E_AR_RELEASE_MAJOR_VERSION already defined
#endif

#define E2E_AR_RELEASE_MAJOR_VERSION  4U

#if(defined E2E_AR_RELEASE_MINOR_VERSION) 
#error E2E_AR_RELEASE_MINOR_VERSION already defined
#endif

#define E2E_AR_RELEASE_MINOR_VERSION  0U

#if(defined E2E_AR_RELEASE_REVISION_VERSION) 
#error E2E_AR_RELEASE_REVISION_VERSION already defined
#endif

#define E2E_AR_RELEASE_REVISION_VERSION  3U



#if(defined E2E_AR_MAJOR_VERSION) 
#error E2E_AR_MAJOR_VERSION already defined
#endif

#define E2E_AR_MAJOR_VERSION  2U

#if(defined E2E_AR_MINOR_VERSION) 
#error E2E_AR_MINOR_VERSION already defined
#endif

#define E2E_AR_MINOR_VERSION  0U

#if(defined E2E_AR_PATCH_VERSION) 
#error E2E_AR_PATCH_VERSION already defined
#endif

#define E2E_AR_PATCH_VERSION  0U



#if(defined E2E_SW_MAJOR_VERSION) 
#error E2E_SW_MAJOR_VERSION already defined
#endif

#define E2E_SW_MAJOR_VERSION  2U

#if(defined E2E_SW_MINOR_VERSION) 
#error E2E_SW_MINOR_VERSION already defined
#endif

#define E2E_SW_MINOR_VERSION  0U

#if(defined E2E_SW_PATCH_VERSION) 
#error E2E_SW_PATCH_VERSION already defined
#endif

#define E2E_SW_PATCH_VERSION  1U











#define E2E_START_SEC_CODE
#include <MemMap.h>


extern FUNC(void, E2E_CODE) E2E_GetVersionInfo
(
   P2VAR(Std_VersionInfoType, AUTOMATIC, E2E_APPL_DATA) VersionInfo
);

#define E2E_STOP_SEC_CODE
#include <MemMap.h>

#endif 

