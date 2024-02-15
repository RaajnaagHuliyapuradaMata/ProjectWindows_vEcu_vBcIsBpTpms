/**************************************************************************************************
   Project Name: Operating Hours Distribution Service (OHDS) - CAN Slave
      File Name: OHDSCanSlave_ApIf.h

    Description: Application Interface

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
   2013-12-10   1.0.0    vislki  Creation
   2014-02-07   1.0.1    vislki  Corrected comments
   2014-03-05   1.0.2    vislki  Renamed Compiler_Cfg and MemMap defines
   2014-03-11   1.1.0    viseml  OHDSCanSlave_GetVersionInfo moved to OHDSCanSlave.h
   2014-03-11            viseml  Code Inspection
   2014-07-18   2.0.0    visart  Status byte changed
   2014-07-29            viseml  Code Inspection
**************************************************************************************************/
#ifndef OHDSCANSLAVE_APIF_H
#define OHDSCANSLAVE_APIF_H

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
   Function name    : OHDSCanSlave_GetOperatingHoursUint16
   ------------------------------------------------------------------------------------------------
   Description      : Returns the 16 lower bits of the current operating hours counter
                      (resolution: 1ms)
   ------------------------------------------------------------------------------------------------
   Called by        : SAR
   ------------------------------------------------------------------------------------------------
   Parameter        : value: will contain the actual operating hours counter value if function
                             return E_OK
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
FUNC(Std_ReturnType, OHDS_CODE) OHDSCanSlave_GetOperatingHoursUint16( P2VAR(uint16, AUTOMATIC, OHDS_APPL_VAR) value, 
                                                                      P2VAR(uint8, AUTOMATIC, OHDS_APPL_VAR) status );

/**************************************************************************************************
   Function name    : OHDSCanSlave_GetOperatingHours
   ------------------------------------------------------------------------------------------------
   Description      : Returns the current operating hours counter (resolution: 1ms)
   ------------------------------------------------------------------------------------------------
   Called by        : SAR
   ------------------------------------------------------------------------------------------------
   Parameter        : value: will contain the lower 4 bytes of the actual operating hours counter
                             value if function return E_OK
                      valueMsb: will contain the 5th byte of the actual operating hours counter.
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
   Returncode       : E_OK: If everything worked well. E_NOT_OK: There was any error.
   ------------------------------------------------------------------------------------------------
   Misc             : -
**************************************************************************************************/
FUNC(Std_ReturnType, OHDS_CODE) OHDSCanSlave_GetOperatingHours( P2VAR(uint32, AUTOMATIC, OHDS_APPL_VAR) value, 
                                                                P2VAR(uint8, AUTOMATIC, OHDS_APPL_VAR) valueMsb, 
                                                                P2VAR(uint8, AUTOMATIC, OHDS_APPL_VAR) status );

#define OHDS_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/***** end of header file ************************************************************************/
#endif /* ifndef OHDSCANSLAVE_APIF_H */
