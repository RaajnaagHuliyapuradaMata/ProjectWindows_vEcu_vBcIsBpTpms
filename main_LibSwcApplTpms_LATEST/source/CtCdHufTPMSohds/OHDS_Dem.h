/**************************************************************************************************
   Project Name: Operating Hours Distribution Service (OHDS)
      File Name: OHDS_Dem.h

    Description: Interface for DEM

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
   2014-02-07   1.0.1    vislki  Adapted comments of function declarations
   2014-03-05   1.0.2    vislki  Renamed Compiler_Cfg and MemMap defines
   2014-03-11            viseml  Code Inspection
   2014-03-13            vislki  Incorporated findings from code inspection
   2014-07-18   2.0.0    visart  New status bits
   2014-07-29            viseml  Code Inspection
**************************************************************************************************/
#ifndef OHDS_DEM_H
#define OHDS_DEM_H

/**************************************************************************************************
* Include files
**************************************************************************************************/
#include "OHDSCanSlave_Config.h"
/**************************************************************************************************
* Version
**************************************************************************************************/

/**************************************************************************************************
* Global defines
**************************************************************************************************/


/**************************************************************************************************
* Global data types and structures
**************************************************************************************************/


/**************************************************************************************************
* Prototypes of export functions
**************************************************************************************************/
#define OHDS_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**************************************************************************************************
   Function name    : OHDS_Dem_GetOperatingHours
   ------------------------------------------------------------------------------------------------
   Description      : Returns the current operating hours counter for the DEM module to store it in
                      DTC environment data (resolution: 1ms)
   ------------------------------------------------------------------------------------------------
   Called by        : Dem
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
   Returncode       : E_OK: If everything worked well. E_NOT_OK: There was an error.
   ------------------------------------------------------------------------------------------------
   Misc             : -
**************************************************************************************************/
FUNC(Std_ReturnType, OHDS_CODE) OHDS_Dem_GetOperatingHours( P2VAR(uint32, AUTOMATIC, OHDS_APPL_VAR) value, 
                                                            P2VAR(uint8, AUTOMATIC, OHDS_APPL_VAR) status );

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
FUNC(void, OHDS_CODE) OHDS_Dem_GetVersionInfo( P2VAR(Std_VersionInfoType, AUTOMATIC, OHDS_APPL_VAR) versionInfo );

#endif /* OHDSCANSLAVE_VERSION_INFO_API */

#define OHDS_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/***** end of header file ************************************************************************/
#endif /* ifndef OHDS_DEM_H */
