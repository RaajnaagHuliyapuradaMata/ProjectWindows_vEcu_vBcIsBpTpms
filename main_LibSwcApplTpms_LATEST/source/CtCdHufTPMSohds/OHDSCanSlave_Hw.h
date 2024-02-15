/**************************************************************************************************
   Project Name: Operating Hours Distribution Service (OHDS) - CAN Slave
      File Name: _OHDSCanSlave_Hw.h

    Description: Header file of OHDS Hardware Abstraction Layer
                 This file must be adapted by the integrator to the project specific environment

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
  -------------------------------------------------------------------------------------------------
                 R E V I S I O N   H I S T O R Y
  -------------------------------------------------------------------------------------------------
   Date         Rev.     Author  Description
   ----------   -------  ------  ------------------------------------------------------------------
   2013-12-09   1.0.0    vislki  Creation
   2014-03-05   1.0.1    vislki  Renamed Compiler_Cfg and MemMap defines
   2014-03-11            viseml  Code Inspection
**************************************************************************************************/
#ifndef OHDSCANSLAVE_HW_H
#define OHDSCANSLAVE_HW_H

/**************************************************************************************************
* Include files
**************************************************************************************************/
#include "OHDSCanSlave_Config.h"
#include "Gpt.h"

/**************************************************************************************************
* Version
**************************************************************************************************/


/**************************************************************************************************
* Global defines
**************************************************************************************************/
#define OHDSCANSLAVE_TIMER_CHANNEL   (uint8)0x01//(OHDS_GPTChannel)

/**************************************************************************************************
* Global data types and structures
**************************************************************************************************/


/**************************************************************************************************
* Prototypes of export functions
**************************************************************************************************/

#define OHDS_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
/**************************************************************************************************
   Function name    : OHDSCanSlave_GetTimerValue
   ------------------------------------------------------------------------------------------------
   Description      : This function returns the value of a free running timer. The unit of the return
                      value is ticks. The  duration  of  one  tick  must  be  configured  in  the
                      OHDSCanSlave config  file.  If  the  timer  is counting downwards, the value
                      must be transformed.
   ------------------------------------------------------------------------------------------------
   Called by        : OHDSCanSlave
   ------------------------------------------------------------------------------------------------
   Parameter        : -
   ------------------------------------------------------------------------------------------------
   Returncode       : value: uint32
   ------------------------------------------------------------------------------------------------
   Misc             : -
**************************************************************************************************/
FUNC(uint32, OHDS_CODE) OHDSCanSlave_GetTimerValue( void );

/**************************************************************************************************
   Function name    : OHDSCanSlave_StartTimer
   ------------------------------------------------------------------------------------------------
   Description      : This  function  can  be  used  to  start  the  free  running  timer.  If  the
                      timer  is  shared,  the implementation of this function can consist of a
                      single "return E_OK;" statement.
   ------------------------------------------------------------------------------------------------
   Called by        : OHDSCanSlave_Init
   ------------------------------------------------------------------------------------------------
   Parameter        : -
   ------------------------------------------------------------------------------------------------
   Returncode       : E_OK: Success
                      E_NOT_OK: Failure
   ------------------------------------------------------------------------------------------------
   Misc             : -
**************************************************************************************************/
FUNC(Std_ReturnType, OHDS_CODE) OHDSCanSlave_StartTimer( void );

#define OHDS_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/***** end of header file ************************************************************************/
#endif /* ifndef OHDSCANSLAVE_HW_H */
