/**************************************************************************************************
   Project Name: Operating Hours Distribution Service (OHDS) - CAN Slave
      File Name: _OHDSCanSlave_Compiler_Cfg.h

    Description: Compiler abstraction for OHDS CAN slave component. This file must be included in
                 or the content must be copied to the Compiler_Cfg.h
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
   visart       Andreas Reifert           Vector Informatik GmbH
  -------------------------------------------------------------------------------------------------
                 R E V I S I O N   H I S T O R Y
  -------------------------------------------------------------------------------------------------
   Date         Rev.     Author  Description
   ----------   -------  ------  ------------------------------------------------------------------
   2013-12-09   1.0.0    vislki  Creation
   2014-02-07   1.0.1    vislki	 Removed unnecessary defines
   2014-03-05   1.0.2    vislki  Renamed Compiler_Cfg defines
   2014-03-11            viseml  Code Inspection
   2014-07-25   2.0.0    visart  Added ZERO_INIT for internal state
   2014-07-29            viseml  Code Inspection
**************************************************************************************************/
#ifndef OHDSCANSLAVE_COMPILER_CFG_H
#define OHDSCANSLAVE_COMPILER_CFG_H

/**************************************************************************************************
* Global defines
**************************************************************************************************/

/* Package Merger: Start Section CompilerCfgModuleList */

/**********************************************************************************************************************
 *  OHDSCANSLAVE START 
 *********************************************************************************************************************/

#define OHDS_CODE
#define OHDS_CONST
#define OHDS_VAR_NOINIT
#define OHDS_VAR_ZERO_INIT
#define OHDS_APPL_VAR

/**********************************************************************************************************************
 *  OHDSCANSLAVE END 
 *********************************************************************************************************************/

/* Package Merger: Stop Section CompilerCfgModuleList */

/***** end of header file ************************************************************************/
#endif /* ifndef OHDSCANSLAVE_COMPILER_CFG_H */
