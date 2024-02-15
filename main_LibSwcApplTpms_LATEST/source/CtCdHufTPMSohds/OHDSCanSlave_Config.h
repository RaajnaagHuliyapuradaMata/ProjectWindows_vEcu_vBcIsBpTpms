/**************************************************************************************************
   Project Name: Operating Hours Distribution Service (OHDS) - CAN Slave
      File Name: _OHDSCanSlave_Config.h

    Description: Configuration header for the CAN slave. This file has to be adapted by the 
	             integrator.

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
   2013-12-09   1.0.0    vislki  Initial creation
   2014-01-23   1.1.0    vislki  Changed resolution of OHDSCANSLAVE_CYCLETIME
                                 Added development error support
   2014-03-11            viseml  Code Inspection
   2014-03-21   1.2.0    viseml  New configuration switch OHDSCANSLAVE_E2E_AR322SUPPORT
   2014-07-30            viseml  Code Inspection
   2014-09-22   1.2.1    viseml  ISS010 - Description of parameters improved
**************************************************************************************************/
#ifndef OHDSCANSLAVE_CONFIG_H
#define OHDSCANSLAVE_CONFIG_H

/**************************************************************************************************
* Include files
**************************************************************************************************/
#include "ComStack_Types.h"

/**************************************************************************************************
* Version
**************************************************************************************************/

/* Version of config file */
#define OHDSCANSLAVE_CONFIG_VERSION         (0x010201u)

/**************************************************************************************************
* Global defines
**************************************************************************************************/
/* Cycle time of MainFunction in us */
#define OHDSCANSLAVE_CYCLETIME               (10000u)

/* Maximum value of timer 
   Example: a 16-Bit timer has the max value of (2^16)-1 = 0xFFFF
*/
#define OHDSCANSLAVE_TIMER_MAX               (0xFFFFFFFFu)

/* Nanoseconds per Timer tick 
   Example: Timer Frequency: 40 Mhz, Prescaler: 16 => Tick time: 400ns
*/
#define OHDSCANSLAVE_TIMER_NS_PER_TICK       (125u) // 8Mhz Clock

/* The data ID used for E2E check of SYNC message (16 bytes) 
   These IDs are specified in the ECU Extract. This parameter must not be changed by the integrator
   except the specification in ECU Extract has been changed. */ 
#define OHDSCanSlave_Sync_DataID {225u,102u,230u,107u,235u,112u,240u,117u,245u,122u,250u,127u,4u,132u,9u,137u}

/* The data ID used for E2E check of FUP message (16 bytes) 
   These IDs are specified in the ECU Extract. This parameter must not be changed by the integrator
   except the specification in ECU Extract has been changed. */ 
#define OHDSCanSlave_Fup_DataID {143u,78u,13u,199u,134u,69u,4u,190u,125u,60u,246u,181u,116u,51u,237u,172u}
 
/* Provides the Autosar Get Version Info API */
#define OHDSCANSLAVE_VERSION_INFO_API        (STD_ON)
 
/* Development error detection */
#define OHDSCANSLAVE_DEV_ERROR_DETECT        (STD_ON) 

/* E2E Library Version 
   STD_ON  for E2E Library as specified in AR Version 3.2.2 / 4.1.1
   STD_OFF for E2E Library as specified in AR Version 3.2.1 and 3.2.0
*/
#define OHDSCANSLAVE_E2E_AR322SUPPORT       (STD_ON)

/**************************************************************************************************
* Global data types and structures
**************************************************************************************************/

/**************************************************************************************************
* Prototypes of export functions
**************************************************************************************************/

/***** end of header file ************************************************************************/
#endif /* ifndef OHDSCANSLAVE_CONFIG_H */
