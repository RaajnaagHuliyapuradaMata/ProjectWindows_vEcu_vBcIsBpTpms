/**
 * \file
 *
 * \brief AUTOSAR E2E
 *
 * This file contains the implementation of the AUTOSAR
 * module E2E.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*==================[inclusions]=============================================*/

#include <E2E.h>          /* E2E library */

/*==================[macros]=================================================*/

/*==================[type definitions]=======================================*/

/*==================[internal function declarations]=========================*/

/*==================[internal constants]=====================================*/

/*==================[internal data]==========================================*/

/*==================[external function definition]=========================*/

#define E2E_START_SEC_CODE
#include <MemMap.h>

FUNC(void, E2E_CODE) E2E_GetVersionInfo
(
   P2VAR(Std_VersionInfoType, AUTOMATIC, E2E_APPL_DATA) VersionInfo
)
{
   if (NULL_PTR != VersionInfo)
   {
      uint32 i;

      /* Initialize complete struct with zeros.
       * This ensures compatibility with ASR 3.2 which additionally
       * contains the parameter instanceId which must be set to 0.
       */
      for (i=0U; i<(uint32)(sizeof(Std_VersionInfoType)); i++)
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

/*==================[internal function definition]===========================*/

/*==================[end of file]============================================*/
