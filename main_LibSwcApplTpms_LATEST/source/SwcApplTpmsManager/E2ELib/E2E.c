

#include <E2E.h>

#define E2E_START_SEC_CODE
#include <MemMap.h>

FUNC(void, E2E_CODE) E2E_GetVersionInfo
(
   P2VAR(Std_VersionInfoType, AUTOMATIC, E2E_APPL_DATA) VersionInfo
)
{
   if(NULL_PTR != VersionInfo)
   {
      uint32 i;

      for(i=0U; i<(uint32)(sizeof(Std_VersionInfoType)); i++)
      {
         ((P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA))
               ((P2VAR(void, AUTOMATIC, E2E_APPL_DATA))VersionInfo))[i] = 0U;
      }

      VersionInfo->vendorID         = E2E_VENDOR_ID;
      VersionInfo->moduleID         = E2E_MODULE_ID;
      VersionInfo->sw_major_version = E2E_SW_MAJOR_VERSION;
      VersionInfo->sw_minor_version = E2E_SW_MINOR_VERSION;
      VersionInfo->sw_patch_version = E2E_SW_PATCH_VERSION;
   }
}

#define E2E_STOP_SEC_CODE
#include <MemMap.h>

