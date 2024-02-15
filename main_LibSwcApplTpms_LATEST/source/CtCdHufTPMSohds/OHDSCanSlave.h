/**************************************************************************************************
   Project Name: Operating Hours Distribution Service (OHDS) - CAN Slave
      File Name: OHDSCanSlave.h

    Description: Implementation header of the OHDS CAN Slave component

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
   2014-01-14   1.0.1    vislki  No Changes here
   2014-01-21   1.0.2    vislki  No Changes here
   2014-01-30   1.1.0    vislki  Moved signal access layer to header file
   2014-02-19   1.1.1    vislki  No Changes here
   2014-03-05            vislki  Renamed Compiler_Cfg and MemMap defines
   2014-03-11   1.2.0    viseml  OHDSCanSlave_GetVersionInfo added
   2014-03-11            viseml  Code Inspection
   2014-03-13            vislki  Incorporated findings from code inspection
   2014-07-18   2.0.0    visart  New frame format
   2014-07-21            visart  Added further signal access macros
   2014-07-25            visart  Added OHDSCanSlave_InitMemory
   2014-07-29            viseml  Code Inspection
   2014-09-23  2.1.0     viseml  New component version
   2015-04-29  2.1.1     viseml  New component version
**************************************************************************************************/
#ifndef OHDSCANSLAVE_H
#define OHDSCANSLAVE_H

/**************************************************************************************************
* Include files
**************************************************************************************************/
#include "OHDSCanSlave_Config.h"

/**************************************************************************************************
* Version
**************************************************************************************************/
#define OHDSCANSLAVE_VENDOR_ID            (0x001Eu)   /* Vector */
#define OHDSCANSLAVE_MODULE_ID            (255u)      /* CDD */
#define OHDSCANSLAVE_SW_MAJOR_VERSION     (0x02u)
#define OHDSCANSLAVE_SW_MINOR_VERSION     (0x01u)
#define OHDSCANSLAVE_SW_PATCH_VERSION     (0x01u)

/**************************************************************************************************
* Global defines
**************************************************************************************************/
/* Error ID's for reporting */
#define OHDSCANSLAVE_E_UNINIT              (0x01u)
#define OHDSCANSLAVE_E_PARAM               (0x02u)
#define OHDSCANSLAVE_E_NOTSUPPORTED        (0x03u)
#define OHDSCANSLAVE_E_TIMERINIT           (0x04u)

/* API ID's for error reporting */
#define OHDSCANSLAVE_MAINFUNCTION_SID      (0x01u)
#define OHDSCANSLAVE_RXINDICATION_SID      (0x02u)
#define OHDSCANSLAVE_GETOHUINT16_SID       (0x03u)
#define OHDSCANSLAVE_GETOH_SID             (0x04u)
#define OHDSCANSLAVE_DEM_GETOH_SID         (0x05u)
#define OHDSCANSLAVE_TXCONFIRMATION_SID    (0x06u)
#define OHDSCANSLAVE_INIT_SID              (0x07u)
#define OHDSCANSLAVE_INITMEMORY_SID        (0x08u)

/* Module ID OHDS for Det_ReportError API */
#define OHDSCANSLAVE_REPORTERROR_MODULEID  (25110u)
/**************************************************************************************************
* Global data types and structures
**************************************************************************************************/

/**************************************************************************************************
 * Signal Access Layer
 **************************************************************************************************/
/* PRQA S 3453 OHDSCANSLAVE_SIGNALACCESS */ /* MD_OHDSCANSLAVE_19.7_FUNCTION_LIKE_MACRO */

/* Required message length */
#define OHDSCANSLAVE_CANSIGNAL_MSGLENGTH                       8u
/* Message type (Multiplexer value in 1st byte) */
#define OHDSCanSlave_GetCanSignal_Type(bufferPtr)              ((uint8)(bufferPtr)[0])
#define OHDSCanSlave_CanSignal_IsSyncMsg(bufferPtr)            (OHDSCanSlave_GetCanSignal_Type(bufferPtr) == 0x20u)
#define OHDSCanSlave_CanSignal_IsFupMsg(bufferPtr)             (OHDSCanSlave_GetCanSignal_Type(bufferPtr) == 0x28u)
/* Sequence counter */
#define OHDSCanSlave_GetCanSignal_SQC(bufferPtr)               ((bufferPtr)[2] & 0x0fu)
/* Sync message: Time Domain */
#define OHDSCanSlave_GetCanSignal_TimeDomain(bufferPtr)        ((uint8)(((bufferPtr)[2] & 0xf0u) >> 4u))

/* Get the second signal from Sync message (big endian) */
#define OHDSCanSlave_GetCanSignal_SEC(bufferPtr)   (((uint32)((uint32)((bufferPtr)[4] & 0x1Fu) << 24u) & 0xff000000u) | \
                                                    ((uint32)((uint32) (bufferPtr)[5]          << 16u) &   0xff0000u) | \
                                                    ((uint32)((uint32) (bufferPtr)[6]          <<  8u) &     0xff00u) | \
                                                    ((uint32)          (bufferPtr)[7]))

/* Get the nano second signal from FUP message (big endian) */
#define OHDSCanSlave_GetCanSignal_NS(bufferPtr)    (((uint32)((uint32) (bufferPtr)[4]          << 24u) & 0xff000000u) | \
                                                    ((uint32)((uint32) (bufferPtr)[5]          << 16u) &   0xff0000u) | \
                                                    ((uint32)((uint32) (bufferPtr)[6]          <<  8u) &     0xff00u) | \
                                                    ((uint32)          (bufferPtr)[7]))

/* Get the status signal bits from SYNC message US0 byte */
#define OHDSCanSlave_GetCanData_US0_SignalBits(bufferPtr)  ((uint8)(((bufferPtr)[3] & 0xf0u) >> 4u))

/* Get the OVS signal from FUP message */
#define OHDSCanSlave_GetCanSignal_OVS(bufferPtr)   ((uint8)((bufferPtr)[3] & 0x03u))

/* Get the SGW signal from FUP message */
#define OHDSCanSlave_GetCanSignal_SGW(bufferPtr)   ((uint8)(((bufferPtr)[3] & 0x04u) >> 2u))

/* PRQA L:OHDSCANSLAVE_SIGNALACCESS */

/**************************************************************************************************
* Prototypes of export functions
**************************************************************************************************/

#define OHDS_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**************************************************************************************************
   Function name    : OHDSCanSlave_InitMemory
   ------------------------------------------------------------------------------------------------
   Description      : Initializes the CDD internal states
   ------------------------------------------------------------------------------------------------
   Called by        : EcuM
   ------------------------------------------------------------------------------------------------
   Parameter        : -
   ------------------------------------------------------------------------------------------------
   Returncode       : -
   ------------------------------------------------------------------------------------------------
   Misc             : -
**************************************************************************************************/
FUNC(void, OHDS_CODE) OHDSCanSlave_InitMemory( void );

/**************************************************************************************************
   Function name    : OHDSCanSlave_Init
   ------------------------------------------------------------------------------------------------
   Description      : Initializes the CDD internal states and starts the timer
   ------------------------------------------------------------------------------------------------
   Called by        : EcuM
   ------------------------------------------------------------------------------------------------
   Parameter        : -
   ------------------------------------------------------------------------------------------------
   Returncode       : -
   ------------------------------------------------------------------------------------------------
   Misc             : -
**************************************************************************************************/
FUNC(void, OHDS_CODE) OHDSCanSlave_Init( void );

/**************************************************************************************************
   Function name    : OHDSCanSlave_MainFunction
   ------------------------------------------------------------------------------------------------
   Description      : Executes state machine of component
   ------------------------------------------------------------------------------------------------
   Called by        : SchM
   ------------------------------------------------------------------------------------------------
   Parameter        : -
   ------------------------------------------------------------------------------------------------
   Returncode       : -
   ------------------------------------------------------------------------------------------------
   Misc             : -
**************************************************************************************************/
FUNC(void, OHDS_CODE) OHDSCanSlave_MainFunction( void );

#if (OHDSCANSLAVE_VERSION_INFO_API == STD_ON)
/**************************************************************************************************
   Function name    : OHDSCanSlave_GetVersionInfo
   ------------------------------------------------------------------------------------------------
   Description      : This function returns module information in a standardized format. 
   ------------------------------------------------------------------------------------------------
   Called by        : Application
   ------------------------------------------------------------------------------------------------
   Parameter        : versionInfo: Std_VersionInfoType*
   ------------------------------------------------------------------------------------------------
   Returncode       : -
   ------------------------------------------------------------------------------------------------
   Misc             : -
**************************************************************************************************/
FUNC(void, OHDS_CODE) OHDSCanSlave_GetVersionInfo( P2VAR(Std_VersionInfoType, AUTOMATIC, OHDS_APPL_VAR) versionInfo );

#endif /* OHDSCANSLAVE_VERSION_INFO_API */

#define OHDS_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/***** end of header file ************************************************************************/
#endif /* ifndef OHDSCANSLAVE_H */
