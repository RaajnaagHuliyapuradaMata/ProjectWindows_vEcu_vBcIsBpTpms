/**************************************************************************************************
   Project Name: Operating Hours Distribution Service (OHDS) - CAN Slave
      File Name: _OHDSCanSlave_MemMap.h

    Description: Memory abstraction for OHDS CAN slave component. This file must be included in
                 or the content must be copied to the MemMap.h
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
   2014-03-05   1.0.2    vislki  Renamed MemMap defines
   2014-03-11            viseml  Code Inspection
   2014-07-25   2.0.0    visart  Added ZERO_INIT for internal state
   2014-07-29            viseml  Code Inspection
**************************************************************************************************/


/**************************************************************************************************
* Global defines
**************************************************************************************************/

/* Package Merger: Start Section MemMapModuleList */

/**********************************************************************************************************************
 *  OHDSCANSLAVE START 
 *********************************************************************************************************************/

/*******  CODE sections **********************************************************************************************/

#ifdef OHDS_START_SEC_CODE
# undef OHDS_START_SEC_CODE
# define START_SEC_CODE                            /* mapped to default code section */
#endif
#ifdef OHDS_STOP_SEC_CODE
# undef OHDS_STOP_SEC_CODE
# define STOP_SEC_CODE                             /* default code stop section */
#endif

/*******  CONST sections  ********************************************************************************************/

/* CONST sections */
#ifdef OHDS_START_SEC_CONST_UNSPECIFIED
# undef OHDS_START_SEC_CONST_UNSPECIFIED
# define START_SEC_CONST_UNSPECIFIED
#endif
#ifdef OHDS_STOP_SEC_CONST_UNSPECIFIED
# undef OHDS_STOP_SEC_CONST_UNSPECIFIED
# define STOP_SEC_CONST
#endif


/*******  VAR sections  **********************************************************************************************/

/* VAR NOINIT sections */
#ifdef OHDS_START_SEC_VAR_NOINIT_8BIT
# undef OHDS_START_SEC_VAR_NOINIT_8BIT
# define START_SEC_VAR_NOINIT_8BIT
#endif
#ifdef OHDS_STOP_SEC_VAR_NOINIT_8BIT
# undef OHDS_STOP_SEC_VAR_NOINIT_8BIT
# define STOP_SEC_VAR
#endif

#ifdef OHDS_START_SEC_VAR_NOINIT_16BIT
# undef OHDS_START_SEC_VAR_NOINIT_16BIT
# define START_SEC_VAR_NOINIT_16BIT
#endif
#ifdef OHDS_STOP_SEC_VAR_NOINIT_16BIT
# undef OHDS_STOP_SEC_VAR_NOINIT_16BIT
# define STOP_SEC_VAR
#endif

#ifdef OHDS_START_SEC_VAR_NOINIT_32BIT
# undef OHDS_START_SEC_VAR_NOINIT_32BIT
# define START_SEC_VAR_NOINIT_32BIT
#endif
#ifdef OHDS_STOP_SEC_VAR_NOINIT_32BIT
# undef OHDS_STOP_SEC_VAR_NOINIT_32BIT
# define STOP_SEC_VAR
#endif

#ifdef OHDS_START_SEC_VAR_NOINIT_UNSPECIFIED
# undef OHDS_START_SEC_VAR_NOINIT_UNSPECIFIED
# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#ifdef OHDS_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef OHDS_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# define STOP_SEC_VAR
#endif

/* VAR ZERO_INIT sections */
#ifdef OHDS_START_SEC_VAR_ZERO_INIT_8BIT
# undef OHDS_START_SEC_VAR_ZERO_INIT_8BIT
# define START_SEC_VAR_ZERO_INIT_8BIT
#endif
#ifdef OHDS_STOP_SEC_VAR_ZERO_INIT_8BIT
# undef OHDS_STOP_SEC_VAR_ZERO_INIT_8BIT
# define STOP_SEC_VAR
#endif


/**********************************************************************************************************************
 *  OHDSCANSLAVE END
 *********************************************************************************************************************/

/* Package Merger: Stop Section MemMapModuleList */

/***** end of header file ************************************************************************/

