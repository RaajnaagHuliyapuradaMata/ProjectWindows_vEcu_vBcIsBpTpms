/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2007 - 2013 by Vector Informatik GmbH.                                           All rights reserved.
 *
 *                Please note, that this file contains example configuration used by the 
 *                MICROSAR BSW. This code may influence the behaviour of the MICROSAR BSW
 *                in principle. Therefore, great care must be taken to verify
 *                the correctness of the implementation.
 *
 *                The contents of the originally delivered files are only examples respectively
 *                implementation proposals. With regard to the fact that these functions
 *                are meant for demonstration purposes only, the liability of Vector Informatik
 *                shall be expressly excluded in cases of ordinary negligence, 
 *                to the extent admissible by law or statute.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  _MemMap.h
 *    Component:  -
 *       Module:  -
 *    Generator:  -
 *
 *  Description:  This File is a template for the MemMap.h
 *                This file has to be extended with the memory section defines for all BSW modules
 *                which where used.
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  MISRA VIOLATIONS
 *  -------------------------------------------------------------------------------------------------------------------
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Joachim Kalmbach              Jk            Vector Informatik GmbH
 *  Heike Honert                  Ht            Vector Informatik GmbH
 *  Eugen Stripling               Seu           Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2007-08-01  Jk                    Initial creation
 *  01.01.00  2007-12-14  Jk                    Component specific defines filtering added
 *  01.01.02  2008-11-04  Jk                    Component specific defines filtering added
 *  01.01.03  2008-12-17  Ht                    Improve list of components  (Tp_AsrTpCan,Tp_AsrTpFr,DrvMcu,DrvIcu added)
 *  01.01.04  2009-04-27  Ht                    improve list of components  (Cp_XcpOnCanAsr, Il_AsrIpduM, If_VxFblDcm,
 *                                              If_VxFblVpm_Volvo_ab, DrvFls added)
 *  01.01.05  2009-04-24  Msr                   Renamed J1939_AsrBase as TpJ1939_AsrBase
 *  01.01.06  2009-06-03  Ht                    Improve list of components (Adc, Dio, Gpt, Pwm, Spi, Wdg, Fls, Port, Fim)
 *  01.02.00  2009-08-01  Ht                    Improve list of components (Fee_30_Inst2, Can, ...Sub)
 *                                              Support filtering for RTE
 *  01.02.01  2009-08-18  HH                    replaced C++ comment by C comment
 *  01.02.02  2009-09-02  Lo                    add external Flash driver support
 *  01.02.03  2009-09-12  Lo                    add DrvFls_Mcs12xFslftm01ExtVx
 *                        Ht                    Improve list of components (CanTrcv_30_Tja1040dio,
 *                                                Eth, EthTrcv, EthIf, SoAd, TcpIp, EthSM)
 *  01.03.00  2009-10-30  Ht                    support R8: change EthTrcv to EthTrcv_30_Canoeemu
 *                                              support EthTrcv_30_Dp83848
 *                                              change CanTrcv_30_Xdio to CanTrcv_30___Your_Trcv__
 *                                              change CanTrcv_30_Tja1040dio to CanTrcv_30_Tja1041
 *                                              change name FrTrcv to FrTrcv_30_Tja1080dio
 *                        Lo                    add Cp_AsrXcp
 *                        Ht                    add Cp_XcpOnFrAsr
 *  01.03.01  2010-01-13  Ht                    support SysService_AsrCal
 *  01.03.02  2010-02-15  Ht                    support SysService_SswRcs_Daimler, SysService_Tls, Tp_Http, 
 *                                                      SysService_Dns, SysService_Json, DrvTrans_GenericLindioAsr
 *                        Lo                    add Diag_AsrDem for all OEMs
 *                                              rename internal variables and filter methods
 *  01.04.00  2010-03-04  Ht                    change name FrTrcv_30_Tja1080dio to FrTrcv_30_Tja1080
 *  01.04.01  2010-03-10  Ht                    support DrvTrans_GenericFrAsr, DrvTrans_As8223FrspiAsr, DrvEep and If_AsrIfEa
 *  01.04.02  2010-04-07  Lo                    change IfFee to real components and add If_AsrIfWdV85xNec01Sub
 *  01.04.03  2010-06-11  Ht                    add CanTrcv_30_Tja1043
 *                        Lo                    add Il_AsrIpduMEbBmwSub
 *  01.04.04  2010-08-24  Ht                    add CanTrcv_30_Tle62512G, DrvEep_XAt25128EAsr, Tp_AsrTpFrEbBmwSub
 *  01.05.00  2010-08-24  Ht                    support R10:
 *                                              change LinTrcv_30_Tle7259dio to LinTrcv_30_Tle7259
 *  01.05.01  2010-10-14  Ht                    add VStdLib, SysService_SswScc, SysService_IpBase, SysService_Crypto
 *  01.05.02  2010-10-20  Ht                    support comments for Package Merge Tool
 *  01.05.03  2010-11-03  Ht                    add SysService_E2eLibTttechSub, SysService_E2ePwTttechSub
 *  01.05.04  2010-11-16  Ht                    add SysService_Exi, DrvTrans_Int6400EthAsr, Cdd_AsrCdd_Fiat, Diag_AsrDem_Fiat
 *  01.05.05  2010-12-17  Ht                    add SysService_AsrSchM, DrvEep_XXStubAsr, DrvIcu_Tms570Tinhet01ExtVx
 *                                                  DrvWd_XTle4278gEAsr, DrvWd_XXStubAsr
 *  01.05.06  2011-02-17  Ht                    add DrvEed, SysService_AsrBswM
 *  01.05.07  2011-03-04  Ht                    add DrvTrans_Tja1055CandioAsr
 *                                              rename CanTrcv_30_Tja1040dio to CanTrcv_30_Tja1040
 *                                              add SysService_XmlEngine
 *  01.06.00  2011-03-15  Ht                    support ASR4.0
 *                                              add Ccl_Asr4ComM, Ccl_Asr4SmCan, Nm_Asr4NmIf, Nm_AsrNmDirOsek
 *  01.06.01  2011-04-15  Ht                    add Diag_AsrDcm_<OEM>
 *  01.06.02  2011-06-17  Ht                    correct Diag_AsrDcm_<OEM>
 *                                              add Monitoring_AsrDlt and Monitoring_GenericMeasurement
 *  01.06.03  2011-09-20  Ht                    add DrvTrans_Tja1145CanSpiAsr, DrvTrans_E52013CanspiAsr, DrvFls_XXStubAsr,
 *                                              If_AsrIfFeeV85xNec05Sub, If_AsrIfFeeV85xNec06Sub, If_AsrIfFeeV85xNec07Sub
 *                                              SysService_AsrWdMTttechSub and If_AsrIfWdTttechSub
 *  01.06.04  2011-11-22  Ht                    add If_AsrIfFeeTiSub, 
 *                                              ESCAN00054718: add Cdd_AsrCdd
 *  01.06.05  2011-12-09  Ht                    add Tp_IpV4, Tp_IpV6
 *  01.06.06  2011-12-14  Ht                    add Monitoring_RuntimeMeasurement
 *  01.06.07  2012-01-03  Ht                    add DrvI2c, SysService_Asr4BswM
 *  01.06.08  2012-01-31  Ht                    add DrvTrans_Ar7000EthAsr, DrvTrans_GenericEthmiiAsr
 *  01.06.09  2012-03-06  Ht                    add If_AsrIfFeeMb9df126Fuji01Sub, 
 *                                              Infineon_Tc1767Inf01Sub, Infineon_Tc178xInf01Sub, Infineon_Tc1797Inf01Sub, Infineon_Tc1797Inf02Sub
 *  01.06.10  2012-03-13  Ht                    add Gw_AsrPduRCfg5, Il_AsrComCfg5, Il_AsrIpduMCfg5, Cdd_AsrCddCfg5,
 *                                              Tp_Asr4TpCan, Diag_Asr4Dcm, Diag_Asr4Dem
 *  01.06.11  2012-03-20  Ht                    add Cp_AsrCcp, Cp_XcpOnTcpIpAsr
 *  01.07.00  2012-07-26  Ht                    ESCAN00059365: [AUTOSAR4, compiler warning]: Wrong define name in #undef statement causes re-definition warning
 *                                              add Nm_Asr4NmCan, Nm_Asr4NmFr, Infineon_Xc2000Inf01Sub, Ccl_Asr4ComMCfg5, SysService_Asr4BswMCfg5, SysService_Asr4EcuM, SysService_AsrRamTst,
 *                                                  Ccl_Asr4SmLin 
 *            2012-09-04  Ht                    add support for ASR specification 4.0 R3
 *  01.07.01  2012-10-23  Seu                   add SysService_XmlSecurity
 *  01.07.02  2013-01-10  Seu                   MISRA deviation comments added
 *  01.08.00  2013-03-01  Seu    ESCAN00065501  AR4-325: Add support for Post-build RAM memory section
 *            2013-04-12  Seu    ESCAN00066614  Add the deviation for violation of MISRA rule 19.6
 *  01.09.00  2013-12-10  Seu    ESCAN00072537  Add *_NOCACHE_* memory sections for variables
 *            2013-12-16  Seu                   MISRA compliance: usage of character "'" removed, typos corrected
 *********************************************************************************************************************/

/* PRQA S 0841 MEMMAP_0841_TAG */ /* MD_MSR_19.6 */

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Rte_MemMap.h"
#include "OHDSCanSlave_MemMap.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

 /* PRQA S 0883 1 */ /* MD_MemMap_19.15 */
#undef MEMMAP_VENDOR_ID /* PRQA S 0841 */ /* MD_MSR_19.6 */

#define MEMMAP_VENDOR_ID        (30u)

/* AUTOSAR Software Specification Version Information */

# undef MEMMAP_AR_MAJOR_VERSION /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_AR_MINOR_VERSION /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_AR_PATCH_VERSION /* PRQA S 0841 */ /* MD_MSR_19.6 */

/* AUTOSAR Document version 1.1.0 part of release 3.0.1 */
# define MEMMAP_AR_MAJOR_VERSION       (1u)
# define MEMMAP_AR_MINOR_VERSION       (1u)
# define MEMMAP_AR_PATCH_VERSION       (0u)

/* compatiblity to older versions */
# undef MEM_AR_MAJOR_VERSION /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEM_AR_MINOR_VERSION /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEM_AR_PATCH_VERSION /* PRQA S 0841 */ /* MD_MSR_19.6 */

# define MEM_AR_MAJOR_VERSION          MEMMAP_AR_MAJOR_VERSION
# define MEM_AR_MINOR_VERSION          MEMMAP_AR_MINOR_VERSION
# define MEM_AR_PATCH_VERSION          MEMMAP_AR_PATCH_VERSION


# undef MEMMAP_SW_MAJOR_VERSION /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_SW_MINOR_VERSION /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_SW_PATCH_VERSION /* PRQA S 0841 */ /* MD_MSR_19.6 */

# define MEMMAP_SW_MAJOR_VERSION     (1u)
# define MEMMAP_SW_MINOR_VERSION     (9u)
# define MEMMAP_SW_PATCH_VERSION     (0u)

/* compatiblity to older versions */
# undef MEM_SW_MAJOR_VERSION /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEM_SW_MINOR_VERSION /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEM_SW_PATCH_VERSION /* PRQA S 0841 */ /* MD_MSR_19.6 */

# define MEM_SW_MAJOR_VERSION        MEMMAP_SW_MAJOR_VERSION 
# define MEM_SW_MINOR_VERSION        MEMMAP_SW_MINOR_VERSION 
# define MEM_SW_PATCH_VERSION        MEMMAP_SW_PATCH_VERSION 

#define MEMMAP_ERROR

/* Package Merger: Start Section MemMapModuleList */


//#include "Rte_MemMap.h"
/*TPMS  Dem_Lcfg.c */


/**********************************************************************************************************************
 *  COMM START 
 *********************************************************************************************************************/

/*******  CODE sections **********************************************************************************************/

#if defined( APPL_FBL_INFO_HEADER_START_SEC_CONST )
   #pragma ghs startdata
   #pragma ghs section rodata=".APPLHEADER"
# undef APPL_FBL_INFO_HEADER_START_SEC_CONST
# undef MEMMAP_ERROR
#endif

#if defined( APPL_FBL_INFO_HEADER_STOP_SEC_CONST )
#   pragma ghs section rodata=default
#   pragma ghs enddata
# undef APPL_FBL_INFO_HEADER_STOP_SEC_CONST
# undef MEMMAP_ERROR
#endif

#ifdef COMM_START_SEC_CODE
  #undef COMM_START_SEC_CODE
  #define START_SEC_CODE                            /* mapped to default code section */
#endif
#ifdef COMM_STOP_SEC_CODE
  #undef COMM_STOP_SEC_CODE
  #define STOP_SEC_CODE                             /* default code stop section */
#endif

#ifdef COMM_START_SEC_APPL_CODE
  #undef COMM_START_SEC_APPL_CODE
  #define START_SEC_CODE                            /* mapped to default code section */
#endif
#ifdef COMM_STOP_SEC_APPL_CODE
  #undef COMM_STOP_SEC_APPL_CODE
  #define STOP_SEC_CODE                             /* default code stop section */
#endif

/*******  CONST sections  ********************************************************************************************/

/* CONST sections */


/* ----------------------------------------------------------------------------------------------------------------- */

#if defined( FBLHEADER_START_SEC_CONST ) || \
    defined( FBLHEADER_START_SEC_CONST_EXPORT )
   #pragma ghs startdata
   #pragma ghs section rodata=".FBLHEADER"
# undef FBLHEADER_START_SEC_CONST
# undef FBLHEADER_START_SEC_CONST_EXPORT
# undef MEMMAP_ERROR
#endif

#if defined( FBLHEADER_STOP_SEC_CONST ) || \
    defined( FBLHEADER_STOP_SEC_CONST_EXPORT )
#   pragma ghs section rodata=default
#   pragma ghs enddata
# undef FBLHEADER_STOP_SEC_CONST
# undef FBLHEADER_STOP_SEC_CONST_EXPORT
# undef MEMMAP_ERROR
#endif

/* ----------------------------------------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------------------------------------- */

#if defined( MAGICFLAG_START_SEC_DATA ) || \
    defined( MAGICFLAG_START_SEC_DATA_EXPORT )
#   pragma ghs startdata
#   pragma ghs section bss=".FBLMAGIC"
# undef MAGICFLAG_START_SEC_DATA
# undef MAGICFLAG_START_SEC_DATA_EXPORT
# undef MEMMAP_ERROR
#endif

#if defined( MAGICFLAG_STOP_SEC_DATA ) || \
    defined( MAGICFLAG_STOP_SEC_DATA_EXPORT )
#   pragma ghs section bss=default
#   pragma ghs enddata
# undef MAGICFLAG_STOP_SEC_DATA
# undef MAGICFLAG_STOP_SEC_DATA_EXPORT
# undef MEMMAP_ERROR
#endif

/* ----------------------------------------------------------------------------------------------------------------- */
#ifdef COMM_START_SEC_CONST_8BIT
# undef COMM_START_SEC_CONST_8BIT
# define START_SEC_CONST_8BIT                       /* mapped to default const 8bit section */
#endif
#ifdef COMM_STOP_SEC_CONST_8BIT
# undef COMM_STOP_SEC_CONST_8BIT
# define STOP_SEC_CONST                             /* default const stop section */
#endif

#ifdef COMM_START_SEC_CONST_16BIT
# undef COMM_START_SEC_CONST_16BIT
# define START_SEC_CONST_16BIT
#endif
#ifdef COMM_STOP_SEC_CONST_16BIT
# undef COMM_STOP_SEC_CONST_16BIT
# define STOP_SEC_CONST
#endif

#ifdef COMM_START_SEC_CONST_32BIT
# undef COMM_START_SEC_CONST_32BIT
# define START_SEC_CONST_32BIT
#endif
#ifdef COMM_STOP_SEC_CONST_32BIT
# undef COMM_STOP_SEC_CONST_32BIT
# define STOP_SEC_CONST
#endif

#ifdef COMM_START_SEC_CONST_UNSPECIFIED
# undef COMM_START_SEC_CONST_UNSPECIFIED
# define START_SEC_CONST_UNSPECIFIED
#endif
#ifdef COMM_STOP_SEC_CONST_UNSPECIFIED
# undef COMM_STOP_SEC_CONST_UNSPECIFIED
# define STOP_SEC_CONST
#endif


/*******  VAR sections  **********************************************************************************************/

/* VAR NOINIT sections */

#ifdef COMM_START_SEC_VAR_NOINIT_8BIT
# undef COMM_START_SEC_VAR_NOINIT_8BIT
# define START_SEC_VAR_NOINIT_8BIT
#endif
#ifdef COMM_STOP_SEC_VAR_NOINIT_8BIT
# undef COMM_STOP_SEC_VAR_NOINIT_8BIT
# define STOP_SEC_VAR
#endif

#ifdef COMM_START_SEC_VAR_NOINIT_16BIT
# undef COMM_START_SEC_VAR_NOINIT_16BIT
# define START_SEC_VAR_NOINIT_16BIT
#endif
#ifdef COMM_STOP_SEC_VAR_NOINIT_16BIT
# undef COMM_STOP_SEC_VAR_NOINIT_16BIT
# define STOP_SEC_VAR
#endif

#ifdef COMM_START_SEC_VAR_NOINIT_32BIT
# undef COMM_START_SEC_VAR_NOINIT_32BIT
# define START_SEC_VAR_NOINIT_32BIT
#endif
#ifdef COMM_STOP_SEC_VAR_NOINIT_32BIT
# undef COMM_STOP_SEC_VAR_NOINIT_32BIT
# define STOP_SEC_VAR
#endif

#ifdef COMM_START_SEC_VAR_NOINIT_UNSPECIFIED
# undef COMM_START_SEC_VAR_NOINIT_UNSPECIFIED
# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#ifdef COMM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef COMM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# define STOP_SEC_VAR
#endif


/* VAR ZERO INIT sections */

#ifdef COMM_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
# undef COMM_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
# define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif
#ifdef COMM_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
# undef COMM_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
# define STOP_SEC_VAR
#endif

/* VAR NVRAM sections */

#ifdef COMM_START_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
# undef COMM_START_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
# define START_SEC_VAR_FAST_NOINIT_UNSPECIFIED
#endif
#ifdef COMM_STOP_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
# undef COMM_STOP_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
# define STOP_SEC_VAR
#endif

/* Postbuild CFG CONST sections */

/* Root pointer to postbuild data */
#ifdef COMM_START_SEC_PBCFG_ROOT
# undef COMM_START_SEC_PBCFG_ROOT
# define START_SEC_CONST_PBCFG
#endif
#ifdef COMM_STOP_SEC_PBCFG_ROOT
# undef COMM_STOP_SEC_PBCFG_ROOT
# define STOP_SEC_CONST
#endif
/**********************************************************************************************************************
 *  COMM END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  CanSM START 
 *********************************************************************************************************************/

/*******  CODE sections **********************************************************************************************/

#ifdef CANSM_START_SEC_CODE
# undef CANSM_START_SEC_CODE
# define START_SEC_CODE                                               /* mapped to default code section */
#endif

#ifdef CANSM_STOP_SEC_CODE
# undef CANSM_STOP_SEC_CODE
# define STOP_SEC_CODE                                                /* default code stop section */
#endif

#ifdef CANSM_START_SEC_APPL_CODE
# undef CANSM_START_SEC_APPL_CODE
# define START_SEC_CODE                                               /* mapped to default code section */
#endif

#ifdef CANSM_STOP_SEC_APPL_CODE
# undef CANSM_STOP_SEC_APPL_CODE
# define STOP_SEC_CODE                                                /* default code stop section */
#endif

/*******  CONST sections  ********************************************************************************************/

/* CONST sections */

#ifdef CANSM_START_SEC_CONST_8BIT
# undef CANSM_START_SEC_CONST_8BIT
# define START_SEC_CONST_8BIT
#endif

#ifdef CANSM_STOP_SEC_CONST_8BIT
# undef CANSM_STOP_SEC_CONST_8BIT
# define STOP_SEC_CONST                                               /* default const stop section */
#endif

#ifdef CANSM_START_SEC_CONST_16BIT
# undef CANSM_START_SEC_CONST_16BIT
# define START_SEC_CONST_16BIT
#endif

#ifdef CANSM_STOP_SEC_CONST_16BIT
# undef CANSM_STOP_SEC_CONST_16BIT
# define STOP_SEC_CONST                                               /* default const stop section */
#endif

#ifdef CANSM_START_SEC_CONST_32BIT
# undef CANSM_START_SEC_CONST_32BIT
# define START_SEC_CONST_32BIT
#endif

#ifdef CANSM_STOP_SEC_CONST_32BIT
# undef CANSM_STOP_SEC_CONST_32BIT
# define STOP_SEC_CONST
#endif

/* FAST CONST sections */

/* Postbuild CFG CONST sections */

/* Root pointer to postbuild data */
#ifdef CANSM_START_SEC_PBCFG_ROOT
# undef CANSM_START_SEC_PBCFG_ROOT
# define START_SEC_CONST_PBCFG
#endif
#ifdef CANSM_STOP_SEC_PBCFG_ROOT
# undef CANSM_STOP_SEC_PBCFG_ROOT
# define STOP_SEC_CONST
#endif

/* Root table for postbuild data */

#ifdef CANSM_START_SEC_PBCFG
# undef CANSM_START_SEC_PBCFG
# define START_SEC_CONST_PBCFG
#endif
#ifdef CANSM_STOP_SEC_PBCFG
# undef CANSM_STOP_SEC_PBCFG
# define STOP_SEC_CONST
#endif


/*******  VAR sections  **********************************************************************************************/

/* VAR INIT sections */

#ifdef CANSM_START_SEC_VAR_INIT_8BIT
# undef CANSM_START_SEC_VAR_INIT_8BIT
# define START_SEC_VAR_INIT_8BIT
#endif

#ifdef CANSM_STOP_SEC_VAR_INIT_8BIT
# undef CANSM_STOP_SEC_VAR_INIT_8BIT
# define STOP_SEC_VAR
#endif

/* VAR NOINIT sections */

#ifdef CANSM_START_SEC_VAR_NOINIT_8BIT
# undef CANSM_START_SEC_VAR_NOINIT_8BIT
# define START_SEC_VAR_NOINIT_8BIT
#endif

#ifdef CANSM_STOP_SEC_VAR_NOINIT_8BIT
# undef CANSM_STOP_SEC_VAR_NOINIT_8BIT
# define STOP_SEC_VAR
#endif

#ifdef CANSM_START_SEC_VAR_NOINIT_UNSPECIFIED
# undef CANSM_START_SEC_VAR_NOINIT_UNSPECIFIED
# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif

#ifdef CANSM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef CANSM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# define STOP_SEC_VAR
#endif

/* VAR ZERO INIT sections */

#ifdef CANSM_START_SEC_VAR_ZERO_INIT_8BIT
# undef CANSM_START_SEC_VAR_ZERO_INIT_8BIT
# define START_SEC_VAR_ZERO_INIT_8BIT
#endif

#ifdef CANSM_STOP_SEC_VAR_ZERO_INIT_8BIT
# undef CANSM_STOP_SEC_VAR_ZERO_INIT_8BIT
# define STOP_SEC_VAR
#endif

/* VAR FAST INIT sections */


/* VAR FAST NOINIT sections */


/* VAR FAST ZERO INIT sections */


/**********************************************************************************************************************
 *  CanSM END
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  Cdd_AsrCdd START 
 *********************************************************************************************************************/
/* Copy the memory mapping defines for each of your configured CDDs and replace the prefix _CDD with the MSN of your configured CDD as higher case. */

/*******  CODE sections **********************************************************************************************/

#ifdef _CDD_START_SEC_CODE
# undef _CDD_START_SEC_CODE
# define START_SEC_CODE
#endif
#ifdef _CDD_STOP_SEC_CODE
# undef _CDD_STOP_SEC_CODE
# define STOP_SEC_CODE
#endif

/* Add additional memory mapping defines for each of you configured CDDs here. */

/*******  CONST sections  ********************************************************************************************/

/* CONST sections */

/* FAST CONST sections */

/* Postbuild CFG CONST sections */

/* Root table for postbuild data */

/*******  VAR sections  **********************************************************************************************/

/* VAR INIT sections */

/* VAR NOINIT sections */

/* VAR ZERO INIT sections */

/* VAR FAST INIT sections */

/* VAR FAST NOINIT sections */

/* VAR FAST ZERO INIT sections */

/**********************************************************************************************************************
 *  Cdd_AsrCdd END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  XCP START 
 *********************************************************************************************************************/

/*******  CODE sections **********************************************************************************************/

#ifdef XCP_START_SEC_CODE 
    #undef XCP_START_SEC_CODE 
    #define START_SEC_CODE
#endif

#ifdef XCP_STOP_SEC_CODE 
    #undef XCP_STOP_SEC_CODE 
    #define STOP_SEC_CODE
#endif


/*******  CONST sections  ********************************************************************************************/

/* CONST sections */

#ifdef XCP_START_SEC_CONST_UNSPECIFIED
    #undef XCP_START_SEC_CONST_UNSPECIFIED
    #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef XCP_STOP_SEC_CONST_UNSPECIFIED
    #undef XCP_STOP_SEC_CONST_UNSPECIFIED
    #define STOP_SEC_CONST
#endif

#ifdef XCP_START_SEC_CONST_16BIT 
    #undef XCP_START_SEC_CONST_16BIT 
    #define START_SEC_CONST_16BIT
#endif

#ifdef XCP_STOP_SEC_CONST_16BIT 
    #undef XCP_STOP_SEC_CONST_16BIT 
    #define STOP_SEC_CONST
#endif

#ifdef XCP_START_SEC_CONST_8BIT 
    #undef XCP_START_SEC_CONST_8BIT 
    #define START_SEC_CONST_8BIT
#endif

#ifdef XCP_STOP_SEC_CONST_8BIT 
    #undef XCP_STOP_SEC_CONST_8BIT 
    #define STOP_SEC_CONST
#endif


/*******  VAR sections  **********************************************************************************************/

/* VAR INIT sections */

#ifdef XCP_START_SEC_VAR_NOINIT_UNSPECIFIED 
    #undef XCP_START_SEC_VAR_NOINIT_UNSPECIFIED 
    #define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif

#ifdef XCP_STOP_SEC_VAR_NOINIT_UNSPECIFIED 
    #undef XCP_STOP_SEC_VAR_NOINIT_UNSPECIFIED 
    #define STOP_SEC_VAR
#endif

#ifdef XCP_START_SEC_VAR_NOINIT_8BIT 
    #undef XCP_START_SEC_VAR_NOINIT_8BIT 
    #define START_SEC_VAR_NOINIT_8BIT
#endif

#ifdef XCP_STOP_SEC_VAR_NOINIT_8BIT 
    #undef XCP_STOP_SEC_VAR_NOINIT_8BIT 
    #define STOP_SEC_VAR
#endif


/**********************************************************************************************************************
 *  XCP END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  CANXCP START 
 *********************************************************************************************************************/

/*******  CODE sections **********************************************************************************************/

#ifdef CANXCP_START_SEC_CODE
  #undef CANXCP_START_SEC_CODE
  #define START_SEC_CODE                            /* mapped to default code section */
#endif

#ifdef CANXCP_STOP_SEC_CODE
  #undef CANXCP_STOP_SEC_CODE
  #define STOP_SEC_CODE                             /* default code stop section */
#endif


/*******  CONST sections  ********************************************************************************************/

/* CONST sections */

#ifdef CANXCP_START_SEC_CONST_8BIT
  #undef CANXCP_START_SEC_CONST_8BIT
  #define START_SEC_CONST_8BIT                      /* mapped to const 8 bit section */
#endif

#ifdef CANXCP_STOP_SEC_CONST_8BIT
  #undef CANXCP_STOP_SEC_CONST_8BIT
  #define STOP_SEC_CONST                            /* default const stop section */
#endif

#ifdef CANXCP_START_SEC_CONST_UNSPECIFIED
  #undef CANXCP_START_SEC_CONST_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED               /* mapped to const unspecified bit section */
#endif

#ifdef CANXCP_STOP_SEC_CONST_UNSPECIFIED
  #undef CANXCP_STOP_SEC_CONST_UNSPECIFIED
  #define STOP_SEC_CONST                            /* default const stop section */
#endif


/* Post build config unspecified */

#ifdef CANXCP_START_SEC_PBCFG_ROOT
  #undef CANXCP_START_SEC_PBCFG_ROOT
  #define START_SEC_CONST_PBCFG                     /* mapped to const unspecified section */
#endif

#ifdef CANXCP_STOP_SEC_PBCFG_ROOT
  #undef CANXCP_STOP_SEC_PBCFG_ROOT
  #define STOP_SEC_CONST                            /* default const stop section */
#endif


#ifdef CANXCP_START_SEC_PBCFG
  #undef CANXCP_START_SEC_PBCFG
  #define START_SEC_CONST_PBCFG                     /* mapped to const unspecified section */
#endif

#ifdef CANXCP_STOP_SEC_PBCFG
  #undef CANXCP_STOP_SEC_PBCFG
  #define STOP_SEC_CONST                            /* default const stop section */
#endif


/*******  VAR sections  **********************************************************************************************/

/* VAR INIT sections */

#ifdef CANXCP_START_SEC_VAR_NOINIT_8BIT
  #undef CANXCP_START_SEC_VAR_NOINIT_8BIT
  #define START_SEC_VAR_NOINIT_8BIT                 /* mapped to uninitialized RAM 8bit section */
#endif

#ifdef CANXCP_STOP_SEC_VAR_NOINIT_8BIT
  #undef CANXCP_STOP_SEC_VAR_NOINIT_8BIT
  #define STOP_SEC_VAR                              /* default RAM stop section */
#endif


/* Var noinit unspecified */
#ifdef CANXCP_START_SEC_VAR_NOINIT_UNSPECIFIED
  #undef CANXCP_START_SEC_VAR_NOINIT_UNSPECIFIED
  #define START_SEC_VAR_NOINIT_UNSPECIFIED          /* mapped to uninitialized RAM unspecified section */
#endif

#ifdef CANXCP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
  #undef CANXCP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
  #define STOP_SEC_VAR                              /* default RAM stop section */
#endif


/**********************************************************************************************************************
 *  CANXCP END
 *********************************************************************************************************************/

/* ==== Start sections mapping ==== */
#ifdef DCM_START_SEC_CONST_8BIT
# undef DCM_START_SEC_CONST_8BIT
# define START_SEC_CONST_8BIT                                        /*mapped to default const section */
#endif

#ifdef DCM_START_SEC_CONST_16BIT
# undef DCM_START_SEC_CONST_16BIT
# define START_SEC_CONST_16BIT                                       /*mapped to default const section */
#endif

#ifdef DCM_START_SEC_CONST_32BIT
# undef DCM_START_SEC_CONST_32BIT
# define START_SEC_CONST_32BIT                                       /*mapped to default const section */
#endif

#ifdef DCM_START_SEC_CONST_UNSPECIFIED
# undef DCM_START_SEC_CONST_UNSPECIFIED
# define START_SEC_CONST_UNSPECIFIED                                 /*mapped to default const section */
#endif

#ifdef DCM_START_SEC_CALIB_8BIT
# undef DCM_START_SEC_CALIB_8BIT
# define START_SEC_CONST_8BIT                                        /*mapped to default CALIB section */
#endif

#ifdef DCM_START_SEC_CALIB_16BIT
# undef DCM_START_SEC_CALIB_16BIT
# define START_SEC_CONST_16BIT                                       /*mapped to default CALIB section */
#endif

#ifdef DCM_START_SEC_CALIB_32BIT
# undef DCM_START_SEC_CALIB_32BIT
# define START_SEC_CONST_32BIT                                       /*mapped to default CALIB section */
#endif

#ifdef DCM_START_SEC_CALIB_UNSPECIFIED
# undef DCM_START_SEC_CALIB_UNSPECIFIED
# define START_SEC_CONST_UNSPECIFIED                                 /*mapped to default CALIB section */
#endif

#ifdef DCM_START_SEC_VAR_NOINIT_8BIT
# undef DCM_START_SEC_VAR_NOINIT_8BIT
# define START_SEC_VAR_NOINIT_8BIT                                   /*mapped to default var section*/
#endif

#ifdef DCM_START_SEC_VAR_NOINIT_16BIT
# undef DCM_START_SEC_VAR_NOINIT_16BIT
# define START_SEC_VAR_NOINIT_16BIT                                  /*mapped to default var section*/
#endif

#ifdef DCM_START_SEC_VAR_NOINIT_32BIT
# undef DCM_START_SEC_VAR_NOINIT_32BIT
# define START_SEC_VAR_NOINIT_32BIT                                  /*mapped to default var section*/
#endif

#ifdef DCM_START_SEC_VAR_NOINIT_UNSPECIFIED
# undef DCM_START_SEC_VAR_NOINIT_UNSPECIFIED
# define START_SEC_VAR_NOINIT_UNSPECIFIED                            /*mapped to default var section*/
#endif

#ifdef DCM_START_SEC_CODE
# undef DCM_START_SEC_CODE
# define START_SEC_CODE                                              /*mapped to default code section*/
#endif

#ifdef DCM_APPL_START_SEC_CODE
# undef DCM_APPL_START_SEC_CODE
# define START_SEC_CODE                                              /*default appl code section*/
#endif

/* ==== Stop sections mapping ==== */

#ifdef DCM_STOP_SEC_CONST_8BIT
# undef DCM_STOP_SEC_CONST_8BIT
# define STOP_SEC_CONST                                              /*default const section */
#endif

#ifdef DCM_STOP_SEC_CONST_16BIT
# undef DCM_STOP_SEC_CONST_16BIT
# define STOP_SEC_CONST                                              /*default const section */
#endif

#ifdef DCM_STOP_SEC_CONST_32BIT
# undef DCM_STOP_SEC_CONST_32BIT
# define STOP_SEC_CONST                                              /*default const section */
#endif

#ifdef DCM_STOP_SEC_CONST_UNSPECIFIED
# undef DCM_STOP_SEC_CONST_UNSPECIFIED
# define STOP_SEC_CONST                                              /*default const section */
#endif

#ifdef DCM_STOP_SEC_CALIB_8BIT
# undef DCM_STOP_SEC_CALIB_8BIT
# define STOP_SEC_CONST                                              /*default CALIB section */
#endif

#ifdef DCM_STOP_SEC_CALIB_16BIT
# undef DCM_STOP_SEC_CALIB_16BIT
# define STOP_SEC_CONST                                              /*default CALIB section */
#endif

#ifdef DCM_STOP_SEC_CALIB_32BIT
# undef DCM_STOP_SEC_CALIB_32BIT
# define STOP_SEC_CONST                                              /*default CALIB section */
#endif

#ifdef DCM_STOP_SEC_CALIB_UNSPECIFIED
# undef DCM_STOP_SEC_CALIB_UNSPECIFIED
# define STOP_SEC_CONST                                              /*default CALIB section */
#endif

#ifdef DCM_STOP_SEC_VAR_NOINIT_8BIT
# undef DCM_STOP_SEC_VAR_NOINIT_8BIT
# define STOP_SEC_VAR                                                /*default var section*/
#endif

#ifdef DCM_STOP_SEC_VAR_NOINIT_16BIT
# undef DCM_STOP_SEC_VAR_NOINIT_16BIT
# define STOP_SEC_VAR                                                /*default var section*/
#endif

#ifdef DCM_STOP_SEC_VAR_NOINIT_32BIT
# undef DCM_STOP_SEC_VAR_NOINIT_32BIT
# define STOP_SEC_VAR                                                /*default var section*/
#endif

#ifdef DCM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef DCM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# define STOP_SEC_VAR                                                /*default var section*/
#endif

#ifdef DCM_STOP_SEC_CODE
# undef DCM_STOP_SEC_CODE
# define STOP_SEC_CODE                                               /*default code section*/
#endif

#ifdef DCM_APPL_STOP_SEC_CODE
# undef DCM_APPL_STOP_SEC_CODE
# define STOP_SEC_CODE                                               /*default appl code section*/
#endif

/** DEM ***************************************************************************/
/*---------------------START-MODULE-SPECIFIC-START-SECTIONS-----------------------*/
                                                              /* code section */
#if defined (DEM_START_SEC_CODE)
    #undef DEM_START_SEC_CODE
    #define START_SEC_CODE
#endif
                                                              /* vars initialized by startup code */
#if defined (DEM_START_SEC_VAR_8BIT)
    #undef DEM_START_SEC_VAR_8BIT
    #define START_SEC_VAR_INIT_8BIT
#endif
#if defined (DEM_START_SEC_VAR_32BIT)
    #undef DEM_START_SEC_VAR_32BIT
    #define START_SEC_VAR_INIT_32BIT
#endif
                                                              /* never initialized vars with high number of accesses */
#if defined (DEM_START_SEC_VAR_FAST_8BIT)
    #undef DEM_START_SEC_VAR_FAST_8BIT
    #define START_SEC_VAR_FAST_NOINIT_8BIT
#endif
#if defined (DEM_START_SEC_VAR_FAST_16BIT)
    #undef DEM_START_SEC_VAR_FAST_16BIT
    #define START_SEC_VAR_FAST_NOINIT_16BIT
#endif
#if defined (DEM_START_SEC_VAR_FAST_32BIT)
    #undef DEM_START_SEC_VAR_FAST_32BIT
    #define START_SEC_VAR_FAST_NOINIT_32BIT
#endif
                                                              /* never initialized vars */
#if defined (DEM_START_SEC_VAR_NOINIT_8BIT)
    #undef DEM_START_SEC_VAR_NOINIT_8BIT
    #define START_SEC_VAR_NOINIT_8BIT
#endif
#if defined (DEM_START_SEC_VAR_NOINIT_16BIT)
    #undef DEM_START_SEC_VAR_NOINIT_16BIT
    #define START_SEC_VAR_NOINIT_16BIT
#endif
#if defined (DEM_START_SEC_VAR_NOINIT_UNSPECIFIED)
    #undef DEM_START_SEC_VAR_NOINIT_UNSPECIFIED
    #define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
                                                              /* vars saved in non volatile memory */
#if defined (DEM_START_SEC_VAR_SAVED_ZONE0_UNSPECIFIED)
    #undef DEM_START_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
    #define START_SEC_VAR_FAST_NOINIT_UNSPECIFIED
#endif
                                                              /* global or static constants */
#if defined (DEM_START_SEC_CONST_8BIT)
    #undef DEM_START_SEC_CONST_8BIT
    #define START_SEC_CONST_8BIT
#endif
#if defined (DEM_START_SEC_CONST_32BIT)
    #undef DEM_START_SEC_CONST_32BIT
    #define START_SEC_CONST_32BIT
#endif
#if defined (DEM_START_SEC_CONST_UNSPECIFIED)
    #undef DEM_START_SEC_CONST_UNSPECIFIED
    #define START_SEC_CONST_UNSPECIFIED
#endif
                                                              /* global or static constants (linktime) */
#if defined (DEM_START_SEC_CONST_LCFG)
    #undef DEM_START_SEC_CONST_LCFG
    #define START_SEC_CONST_UNSPECIFIED
#endif
                                                              /* global or static constants (postbuild) */
#if defined (DEM_START_SEC_PBCONST_ROOT)
    #undef DEM_START_SEC_PBCONST_ROOT
    #define START_SEC_CONST_PBCFG
#endif
#if defined (DEM_START_SEC_PBCONST)
    #undef DEM_START_SEC_PBCONST
    #define START_SEC_CONST_PBCFG
#endif
/*---------------------STOP-MODULE-SPECIFIC-START-SECTIONS------------------------*/

/*---------------------START-MODULE-SPECIFIC-STOP-SECTIONS------------------------*/

#if defined (DEM_STOP_SEC_CODE)
    #undef DEM_STOP_SEC_CODE
    #define STOP_SEC_CODE
#endif

#if defined (DEM_STOP_SEC_VAR_8BIT)
    #undef DEM_STOP_SEC_VAR_8BIT
    #define STOP_SEC_VAR
#endif
#if defined (DEM_STOP_SEC_VAR_32BIT)
    #undef DEM_STOP_SEC_VAR_32BIT
    #define STOP_SEC_VAR
#endif


#if defined (DEM_STOP_SEC_VAR_FAST_8BIT)
    #undef DEM_STOP_SEC_VAR_FAST_8BIT
    #define STOP_SEC_VAR
#endif
#if defined (DEM_STOP_SEC_VAR_FAST_16BIT)
    #undef DEM_STOP_SEC_VAR_FAST_16BIT
    #define STOP_SEC_VAR
#endif
#if defined (DEM_STOP_SEC_VAR_FAST_32BIT)
    #undef DEM_STOP_SEC_VAR_FAST_32BIT
    #define STOP_SEC_VAR
#endif

#if defined (DEM_STOP_SEC_VAR_NOINIT_8BIT)
    #undef DEM_STOP_SEC_VAR_NOINIT_8BIT
    #define STOP_SEC_VAR
#endif
#if defined (DEM_STOP_SEC_VAR_NOINIT_16BIT)
    #undef DEM_STOP_SEC_VAR_NOINIT_16BIT
    #define STOP_SEC_VAR
#endif
#if defined (DEM_STOP_SEC_VAR_NOINIT_UNSPECIFIED)
    #undef DEM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
    #define STOP_SEC_VAR
#endif

#if defined (DEM_STOP_SEC_VAR_SAVED_ZONE0_UNSPECIFIED)
    #undef DEM_STOP_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
    #define STOP_SEC_VAR
#endif

#if defined (DEM_STOP_SEC_CONST_8BIT)
    #undef DEM_STOP_SEC_CONST_8BIT
    #define STOP_SEC_CONST
#endif
#if defined (DEM_STOP_SEC_CONST_32BIT)
    #undef DEM_STOP_SEC_CONST_32BIT
    #define STOP_SEC_CONST
#endif
#if defined (DEM_STOP_SEC_CONST_UNSPECIFIED)
    #undef DEM_STOP_SEC_CONST_UNSPECIFIED
    #define STOP_SEC_CONST
#endif

#if defined (DEM_STOP_SEC_CONST_LCFG)
    #undef DEM_STOP_SEC_CONST_LCFG
    #define STOP_SEC_CONST
#endif

#if defined (DEM_STOP_SEC_PBCONST_ROOT)
    #undef DEM_STOP_SEC_PBCONST_ROOT
    #define STOP_SEC_CONST
#endif
#if defined (DEM_STOP_SEC_PBCONST)
    #undef DEM_STOP_SEC_PBCONST
    #define STOP_SEC_CONST
#endif
/*---------------------STOP-MODULE-SPECIFIC-STOP-SECTIONS------------------------*/
/** End of DEM *******************************************************************/



/***********************************************************************************************************************
 *  ADC START
 **********************************************************************************************************************/

#ifdef ADC_START_SEC_CODE_FAST
  #undef ADC_START_SEC_CODE_FAST
    #define START_SEC_CODE
#endif
#ifdef ADC_START_SEC_PUBLIC_CODE
  #undef ADC_START_SEC_PUBLIC_CODE
    #define START_SEC_CODE
#endif
#ifdef ADC_START_SEC_PRIVATE_CODE
  #undef ADC_START_SEC_PRIVATE_CODE
    #define START_SEC_CODE
#endif

#ifdef ADC_START_SEC_APPL_CODE
  #undef ADC_START_SEC_APPL_CODE
    #define START_SEC_CODE
#endif
/**************************************** Stop CODE sections **********************************************************/
#ifdef ADC_STOP_SEC_CODE_FAST
  #undef ADC_STOP_SEC_CODE_FAST
    #define STOP_SEC_CODE
#endif
#ifdef ADC_STOP_SEC_PUBLIC_CODE
  #undef ADC_STOP_SEC_PUBLIC_CODE
    #define STOP_SEC_CODE
#endif
#ifdef ADC_STOP_SEC_PRIVATE_CODE
  #undef ADC_STOP_SEC_PRIVATE_CODE
    #define STOP_SEC_CODE
#endif
#ifdef ADC_STOP_SEC_APPL_CODE
  #undef ADC_STOP_SEC_APPL_CODE
    #define STOP_SEC_CODE
#endif
/**************************************** Start VAR sections **********************************************************/
#ifdef ADC_START_SEC_VAR_1BIT
  #undef ADC_START_SEC_VAR_1BIT
    #define START_SEC_VAR_INIT_UNSPECIFIED
#endif
#ifdef ADC_START_SEC_VAR_NOINIT_1BIT
  #undef ADC_START_SEC_VAR_NOINIT_1BIT
    #define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#ifdef ADC_START_SEC_VAR_FAST_1BIT
  #undef ADC_START_SEC_VAR_FAST_1BIT
    #define START_SEC_VAR_FAST_INIT_UNSPECIFIED
#endif
#ifdef  ADC_START_SEC_VAR_8BIT
  #undef ADC_START_SEC_VAR_8BIT
    #define START_SEC_VAR_INIT_8BIT
#endif
#ifdef ADC_START_SEC_VAR_NOINIT_8BIT
  #undef ADC_START_SEC_VAR_NOINIT_8BIT
    #define START_SEC_VAR_NOINIT_8BIT
#endif
#ifdef ADC_START_SEC_VAR_FAST_8BIT
  #undef  ADC_START_SEC_VAR_FAST_8BIT
    #define START_SEC_VAR_FAST_INIT_8BIT
#endif
#ifdef ADC_START_SEC_VAR_16BIT
  #undef  ADC_START_SEC_VAR_16BIT
    #define START_SEC_VAR_INIT_16BIT
#endif
#ifdef ADC_START_SEC_VAR_NOINIT_16BIT
  #undef  ADC_START_SEC_VAR_NOINIT_16BIT
    #define START_SEC_VAR_NOINIT_16BIT
#endif
#ifdef ADC_START_SEC_VAR_FAST_16BIT
  #undef  ADC_START_SEC_VAR_FAST_16BIT
    #define START_SEC_VAR_FAST_INIT_16BIT
#endif
#ifdef ADC_START_SEC_VAR_NOINIT_32BIT
  #undef  ADC_START_SEC_VAR_NOINIT_32BIT
    #define START_SEC_VAR_NOINIT_32BIT
#endif
#ifdef ADC_START_SEC_VAR_32BIT
  #undef  ADC_START_SEC_VAR_32BIT
    #define START_SEC_VAR_INIT_32BIT
#endif
#ifdef ADC_START_SEC_VAR_FAST_32BIT
  #undef  ADC_START_SEC_VAR_FAST_32BIT
    #define START_SEC_VAR_FAST_INIT_32BIT
#endif
#ifdef ADC_START_SEC_VAR_UNSPECIFIED
  #undef  ADC_START_SEC_VAR_UNSPECIFIED
    #define START_SEC_VAR_INIT_UNSPECIFIED
#endif
#ifdef ADC_START_SEC_VAR_NOINIT_UNSPECIFIED
  #undef  ADC_START_SEC_VAR_NOINIT_UNSPECIFIED
    #define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#ifdef ADC_START_SEC_VAR_FAST_UNSPECIFIED
  #undef  ADC_START_SEC_VAR_FAST_UNSPECIFIED
    #define START_SEC_VAR_FAST_INIT_UNSPECIFIED
#endif
#ifdef ADC_START_SEC_CONFIG_VAR_NOINIT_UNSPECIFIED
  #undef  ADC_START_SEC_CONFIG_VAR_NOINIT_UNSPECIFIED
    #define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
/**************************************** Stop VAR sections ***********************************************************/
#ifdef ADC_STOP_SEC_VAR_1BIT
  #undef ADC_STOP_SEC_VAR_1BIT
    #define STOP_SEC_VAR
#endif
#ifdef ADC_STOP_SEC_VAR_NOINIT_1BIT
  #undef ADC_STOP_SEC_VAR_NOINIT_1BIT
    #define STOP_SEC_VAR
#endif
#ifdef ADC_STOP_SEC_VAR_FAST_1BIT
  #undef ADC_STOP_SEC_VAR_FAST_1BIT
    #define STOP_SEC_VAR
#endif
#ifdef  ADC_STOP_SEC_VAR_8BIT
  #undef ADC_STOP_SEC_VAR_8BIT
    #define STOP_SEC_VAR
#endif
#ifdef ADC_STOP_SEC_VAR_NOINIT_8BIT
  #undef ADC_STOP_SEC_VAR_NOINIT_8BIT
    #define STOP_SEC_VAR
#endif
#ifdef ADC_STOP_SEC_VAR_FAST_8BIT
  #undef ADC_STOP_SEC_VAR_FAST_8BIT
    #define STOP_SEC_VAR
#endif

#ifdef ADC_STOP_SEC_VAR_16BIT
  #undef ADC_STOP_SEC_VAR_16BIT
    #define STOP_SEC_VAR
#endif
#ifdef ADC_STOP_SEC_VAR_NOINIT_16BIT
  #undef ADC_STOP_SEC_VAR_NOINIT_16BIT
    #define STOP_SEC_VAR
#endif
#ifdef  ADC_STOP_SEC_VAR_FAST_16BIT
  #undef ADC_STOP_SEC_VAR_FAST_16BIT
    #define STOP_SEC_VAR
#endif
#ifdef ADC_STOP_SEC_VAR_32BIT
  #undef ADC_STOP_SEC_VAR_32BIT
    #define STOP_SEC_VAR
#endif
#ifdef  ADC_STOP_SEC_VAR_NOINIT_32BIT
  #undef  ADC_STOP_SEC_VAR_NOINIT_32BIT
    #define STOP_SEC_VAR
#endif
#ifdef ADC_STOP_SEC_VAR_FAST_32BIT
  #undef ADC_STOP_SEC_VAR_FAST_32BIT
    #define STOP_SEC_VAR
#endif
#ifdef ADC_STOP_SEC_VAR_UNSPECIFIED
  #undef ADC_STOP_SEC_VAR_UNSPECIFIED
    #define STOP_SEC_VAR
#endif
#ifdef ADC_STOP_SEC_VAR_NOINIT_UNSPECIFIED
  #undef ADC_STOP_SEC_VAR_NOINIT_UNSPECIFIED
    #define STOP_SEC_VAR
#endif
#ifdef ADC_STOP_SEC_VAR_FAST_UNSPECIFIED
  #undef ADC_STOP_SEC_VAR_FAST_UNSPECIFIED
    #define STOP_SEC_VAR
#endif
#ifdef ADC_STOP_SEC_CONFIG_VAR_NOINIT_UNSPECIFIED
  #undef ADC_STOP_SEC_CONFIG_VAR_NOINIT_UNSPECIFIED
    #define STOP_SEC_VAR
#endif
/**************************************** Start CONST sections ********************************************************/
#ifdef  ADC_START_SEC_CONST_1BIT
  #undef ADC_START_SEC_CONST_1BIT
    #define START_SEC_CONST_UNSPECIFIED
#endif
#ifdef ADC_START_SEC_CONST_8BIT
  #undef ADC_START_SEC_CONST_8BIT
    #define START_SEC_CONST_8BIT
#endif
#ifdef ADC_START_SEC_CONST_16BIT
  #undef ADC_START_SEC_CONST_16BIT
    #define START_SEC_CONST_16BIT
#endif
#ifdef  ADC_START_SEC_CONST_32BIT
  #undef ADC_START_SEC_CONST_32BIT
    #define START_SEC_CONST_32BIT
#endif
#ifdef ADC_START_SEC_CONST_UNSPECIFIED
  #undef ADC_START_SEC_CONST_UNSPECIFIED
    #define START_SEC_CONST_UNSPECIFIED
#endif
/**************************************** Stop CONST sections *********************************************************/
#ifdef ADC_STOP_SEC_CONST_1BIT
  #undef ADC_STOP_SEC_CONST_1BIT
    #define STOP_SEC_CONST
#endif
#ifdef  ADC_STOP_SEC_CONST_8BIT
  #undef ADC_STOP_SEC_CONST_8BIT
    #define STOP_SEC_CONST
#endif
#ifdef ADC_STOP_SEC_CONST_16BIT
  #undef ADC_STOP_SEC_CONST_16BIT
    #define STOP_SEC_CONST
#endif
#ifdef ADC_STOP_SEC_CONST_32BIT
  #undef ADC_STOP_SEC_CONST_32BIT
    #define STOP_SEC_CONST
#endif
#ifdef ADC_STOP_SEC_CONST_UNSPECIFIED
  #undef ADC_STOP_SEC_CONST_UNSPECIFIED
    #define STOP_SEC_CONST
#endif
/**************************************** START CONFIG sections *******************************************************/
#ifdef ADC_START_SEC_CONFIG_DATA_UNSPECIFIED
  #undef  ADC_START_SEC_CONFIG_DATA_UNSPECIFIED
    #define START_SEC_CONST_PBCFG
#endif
#ifdef  ADC_START_SEC_DBTOC_DATA_UNSPECIFIED
  #undef ADC_START_SEC_DBTOC_DATA_UNSPECIFIED
    #define START_SEC_CONST_PBCFG
#endif
/**************************************** START CONFIG sections *******************************************************/
#ifdef ADC_STOP_SEC_CONFIG_DATA_UNSPECIFIED
  #undef ADC_STOP_SEC_CONFIG_DATA_UNSPECIFIED
    #define STOP_SEC_CONST
#endif
#ifdef  ADC_STOP_SEC_DBTOC_DATA_UNSPECIFIED
  #undef ADC_STOP_SEC_DBTOC_DATA_UNSPECIFIED
    #define STOP_SEC_CONST
#endif

/*******************************************************************************************************************************
 *  ADC STOP
 ******************************************************************************************************************************/

/* Kernbauer Version: 1.16 Konfiguration: DrvCAN Erzeugungsgangnummer: 1 */


/**********************************************************************************************************************
 *  Can START 
 *********************************************************************************************************************/

#if defined (CAN_REMAP_PB_SECTIONS)
/* for none PB variants the code will be mapped to standard sections, so the generated and static code can ignore the variant handling */
# if defined (CAN_START_SEC_PBCFG)
#  undef CAN_START_SEC_PBCFG                /* PRQA S 0841 */ /* MD_MSR_19.6 */
#  define CAN_START_SEC_CONST_UNSPECIFIED
# endif
# if defined (CAN_STOP_SEC_PBCFG)
#  undef CAN_STOP_SEC_PBCFG                 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#  define CAN_STOP_SEC_CONST_UNSPECIFIED
# endif

# if defined (CAN_START_SEC_VAR_PBCFG)
#  undef CAN_START_SEC_VAR_PBCFG            /* PRQA S 0841 */ /* MD_MSR_19.6 */
#  define CAN_START_SEC_VAR_NOINIT_UNSPECIFIED
# endif
# if defined (CAN_STOP_SEC_VAR_PBCFG)
#  undef CAN_STOP_SEC_VAR_PBCFG             /* PRQA S 0841 */ /* MD_MSR_19.6 */
#  define CAN_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# endif
#endif

/*******  CODE sections **********************************************************************************************/

#ifdef CAN_START_SEC_CODE                             /* CAN code */ /* PRQA S 0883 */ /* Appears only while testing */
# undef CAN_START_SEC_CODE                              /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CODE                               /* mapped to default code section */
#endif
#ifdef CAN_STOP_SEC_CODE
# undef CAN_STOP_SEC_CODE                               /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CODE
#endif

#ifdef CAN_START_SEC_STATIC_CODE                      /* CAN static code */
# undef CAN_START_SEC_STATIC_CODE                       /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CODE                               /* mapped to default code section */
#endif
#ifdef CAN_STOP_SEC_STATIC_CODE
# undef CAN_STOP_SEC_STATIC_CODE                        /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CODE
#endif

#ifdef CAN_START_SEC_CODE_APPL                        /* Appl code (generic precopy)*/
# undef CAN_START_SEC_CODE_APPL                         /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CODE                               /* mapped to default code section */
#endif
#ifdef CAN_STOP_SEC_CODE_APPL
# undef CAN_STOP_SEC_CODE_APPL                          /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CODE
#endif

/*******  CONST sections  ********************************************************************************************/

/* CONST sections */

#ifdef CAN_START_SEC_CONST_8BIT                       /* Const 8bit */
# undef CAN_START_SEC_CONST_8BIT                        /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_8BIT                         /* mapped to default const 8bit section */
#endif
#ifdef CAN_STOP_SEC_CONST_8BIT
# undef CAN_STOP_SEC_CONST_8BIT                         /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST
#endif

#ifdef CAN_START_SEC_CONST_16BIT                      /* Const 16bit */
# undef CAN_START_SEC_CONST_16BIT                       /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_16BIT                        /* mapped to default const 16bit section */
#endif
#ifdef CAN_STOP_SEC_CONST_16BIT
# undef CAN_STOP_SEC_CONST_16BIT                        /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST
#endif

#ifdef CAN_START_SEC_CONST_32BIT                      /* Const 32bit */
# undef CAN_START_SEC_CONST_32BIT                       /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_32BIT                        /* mapped to default const 32bit section */
#endif
#ifdef CAN_STOP_SEC_CONST_32BIT
# undef CAN_STOP_SEC_CONST_32BIT                        /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST
#endif

#ifdef CAN_START_SEC_CONST_UNSPECIFIED                /* Const unspecified */
# undef CAN_START_SEC_CONST_UNSPECIFIED                 /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_UNSPECIFIED                  /* mapped to default const unspec section */
#endif
#ifdef CAN_STOP_SEC_CONST_UNSPECIFIED
# undef CAN_STOP_SEC_CONST_UNSPECIFIED                  /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST
#endif

/* FAST CONST sections */
/* unused */

/* Postbuild CFG CONST sections */

/* Root table for postbuild data (not relevant for CFG5 AutoSar4.0.3) */
#ifdef CAN_START_SEC_PBCFG_ROOT                       /* Generated Postbuild Root Table */
# undef CAN_START_SEC_PBCFG_ROOT                        /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_PBCFG                        /* mapped to default const postbuild section */
#endif
#ifdef CAN_STOP_SEC_PBCFG_ROOT
# undef CAN_STOP_SEC_PBCFG_ROOT                         /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST
#endif

#ifdef CAN_START_SEC_PBCFG                            /* Generated Postbuild */
# undef CAN_START_SEC_PBCFG                             /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_PBCFG                        /* mapped to default const postbuild section */
#endif
#ifdef CAN_STOP_SEC_PBCFG
# undef CAN_STOP_SEC_PBCFG                              /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST
#endif


/*******  VAR sections  **********************************************************************************************/

/* VAR INIT sections */

#ifdef CAN_START_SEC_VAR_INIT_UNSPECIFIED             /* init RAM*/
# undef CAN_START_SEC_VAR_INIT_UNSPECIFIED              /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_INIT_UNSPECIFIED               /* mapped to default init var section */
#endif
#ifdef CAN_STOP_SEC_VAR_INIT_UNSPECIFIED
# undef CAN_STOP_SEC_VAR_INIT_UNSPECIFIED               /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif


/* VAR NOINIT sections */

#ifdef CAN_START_SEC_VAR_NOINIT_UNSPECIFIED           /* uninit RAM*/
# undef CAN_START_SEC_VAR_NOINIT_UNSPECIFIED            /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_NOINIT_UNSPECIFIED             /* mapped to default uninit var section */
#endif
#ifdef CAN_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef CAN_STOP_SEC_VAR_NOINIT_UNSPECIFIED             /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif


/* VAR PBCFG sections */

#ifdef CAN_START_SEC_VAR_PBCFG           /* Generated Postbuild RAM*/
# undef CAN_START_SEC_VAR_PBCFG            /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_PBCFG             /* mapped to default uninit var section */
#endif
#ifdef CAN_STOP_SEC_VAR_PBCFG
# undef CAN_STOP_SEC_VAR_PBCFG             /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

/* VAR ZERO INIT sections */
/* unused */


/* VAR FAST INIT sections */
/* unused */


/* VAR FAST NOINIT sections */
/* unused */

/* VAR FAST ZERO INIT sections */
/* unused */



/**********************************************************************************************************************
 *  Can END
 *********************************************************************************************************************/

/***********************************************************************************************************************
 *  DIO Sections
 **********************************************************************************************************************/

/**************************************** Start CODE sections *********************************************************/
#ifdef DIO_START_SEC_PUBLIC_CODE
  #undef DIO_START_SEC_PUBLIC_CODE
    #define START_SEC_CODE
#endif
#ifdef DIO_START_SEC_PRIVATE_CODE
  #undef DIO_START_SEC_PRIVATE_CODE
    #define START_SEC_CODE
#endif

#ifdef DIO_START_SEC_APPL_CODE
  #undef DIO_START_SEC_APPL_CODE
    #define START_SEC_CODE
#endif
/**************************************** Stop CODE sections **********************************************************/
#ifdef DIO_STOP_SEC_PUBLIC_CODE
  #undef DIO_STOP_SEC_PUBLIC_CODE
    #define STOP_SEC_CODE
#endif
#ifdef DIO_STOP_SEC_PRIVATE_CODE
  #undef DIO_STOP_SEC_PRIVATE_CODE
    #define STOP_SEC_CODE
#endif
#ifdef DIO_STOP_SEC_APPL_CODE
  #undef DIO_STOP_SEC_APPL_CODE
    #define STOP_SEC_CODE
#endif
/**************************************** Start VAR sections **********************************************************/
#ifdef DIO_START_SEC_VAR_1BIT
  #undef DIO_START_SEC_VAR_1BIT
    #define START_SEC_VAR_INIT_UNSPECIFIED
#endif
#ifdef DIO_START_SEC_VAR_NOINIT_1BIT
  #undef DIO_START_SEC_VAR_NOINIT_1BIT
    #define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#ifdef DIO_START_SEC_VAR_FAST_1BIT
  #undef DIO_START_SEC_VAR_FAST_1BIT
    #define START_SEC_VAR_FAST_INIT_UNSPECIFIED
#endif
#ifdef  DIO_START_SEC_VAR_8BIT
  #undef DIO_START_SEC_VAR_8BIT
    #define START_SEC_VAR_INIT_8BIT
#endif
#ifdef DIO_START_SEC_VAR_NOINIT_8BIT
  #undef DIO_START_SEC_VAR_NOINIT_8BIT
    #define START_SEC_VAR_NOINIT_8BIT
#endif
#ifdef DIO_START_SEC_VAR_FAST_8BIT
  #undef  DIO_START_SEC_VAR_FAST_8BIT
    #define START_SEC_VAR_FAST_INIT_8BIT
#endif
#ifdef DIO_START_SEC_VAR_16BIT
  #undef  DIO_START_SEC_VAR_16BIT
    #define START_SEC_VAR_INIT_16BIT
#endif
#ifdef DIO_START_SEC_VAR_NOINIT_16BIT
  #undef  DIO_START_SEC_VAR_NOINIT_16BIT
    #define START_SEC_VAR_NOINIT_16BIT
#endif
#ifdef DIO_START_SEC_VAR_FAST_16BIT
  #undef  DIO_START_SEC_VAR_FAST_16BIT
    #define START_SEC_VAR_FAST_INIT_16BIT
#endif
#ifdef DIO_START_SEC_VAR_NOINIT_32BIT
  #undef  DIO_START_SEC_VAR_NOINIT_32BIT
    #define START_SEC_VAR_NOINIT_32BIT
#endif
#ifdef DIO_START_SEC_VAR_32BIT
  #undef  DIO_START_SEC_VAR_32BIT
    #define START_SEC_VAR_INIT_32BIT
#endif
#ifdef DIO_START_SEC_VAR_FAST_32BIT
  #undef  DIO_START_SEC_VAR_FAST_32BIT
    #define START_SEC_VAR_FAST_INIT_32BIT
#endif
#ifdef DIO_START_SEC_VAR_UNSPECIFIED
  #undef  DIO_START_SEC_VAR_UNSPECIFIED
    #define START_SEC_VAR_INIT_UNSPECIFIED
#endif
#ifdef DIO_START_SEC_VAR_NOINIT_UNSPECIFIED
  #undef  DIO_START_SEC_VAR_NOINIT_UNSPECIFIED
    #define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#ifdef DIO_START_SEC_VAR_FAST_UNSPECIFIED
  #undef  DIO_START_SEC_VAR_FAST_UNSPECIFIED
    #define START_SEC_VAR_FAST_INIT_UNSPECIFIED
#endif
#ifdef DIO_START_SEC_CONFIG_VAR_NOINIT_UNSPECIFIED
  #undef  DIO_START_SEC_CONFIG_VAR_NOINIT_UNSPECIFIED
    #define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
/**************************************** Stop VAR sections ***********************************************************/
#ifdef DIO_STOP_SEC_VAR_1BIT
  #undef DIO_STOP_SEC_VAR_1BIT
    #define STOP_SEC_VAR
#endif
#ifdef DIO_STOP_SEC_VAR_NOINIT_1BIT
  #undef DIO_STOP_SEC_VAR_NOINIT_1BIT
    #define STOP_SEC_VAR
#endif
#ifdef DIO_STOP_SEC_VAR_FAST_1BIT
  #undef DIO_STOP_SEC_VAR_FAST_1BIT
    #define STOP_SEC_VAR
#endif
#ifdef  DIO_STOP_SEC_VAR_8BIT
  #undef DIO_STOP_SEC_VAR_8BIT
    #define STOP_SEC_VAR
#endif
#ifdef DIO_STOP_SEC_VAR_NOINIT_8BIT
  #undef DIO_STOP_SEC_VAR_NOINIT_8BIT
    #define STOP_SEC_VAR
#endif
#ifdef DIO_STOP_SEC_VAR_FAST_8BIT
  #undef DIO_STOP_SEC_VAR_FAST_8BIT
    #define STOP_SEC_VAR
#endif

#ifdef DIO_STOP_SEC_VAR_16BIT
  #undef DIO_STOP_SEC_VAR_16BIT
    #define STOP_SEC_VAR
#endif
#ifdef DIO_STOP_SEC_VAR_NOINIT_16BIT
  #undef DIO_STOP_SEC_VAR_NOINIT_16BIT
    #define STOP_SEC_VAR
#endif
#ifdef  DIO_STOP_SEC_VAR_FAST_16BIT
  #undef DIO_STOP_SEC_VAR_FAST_16BIT
    #define STOP_SEC_VAR
#endif
#ifdef DIO_STOP_SEC_VAR_32BIT
  #undef DIO_STOP_SEC_VAR_32BIT
    #define STOP_SEC_VAR
#endif
#ifdef  DIO_STOP_SEC_VAR_NOINIT_32BIT
  #undef  DIO_STOP_SEC_VAR_NOINIT_32BIT
    #define STOP_SEC_VAR
#endif
#ifdef DIO_STOP_SEC_VAR_FAST_32BIT
  #undef DIO_STOP_SEC_VAR_FAST_32BIT
    #define STOP_SEC_VAR
#endif
#ifdef DIO_STOP_SEC_VAR_UNSPECIFIED
  #undef DIO_STOP_SEC_VAR_UNSPECIFIED
    #define STOP_SEC_VAR
#endif
#ifdef DIO_STOP_SEC_VAR_NOINIT_UNSPECIFIED
  #undef DIO_STOP_SEC_VAR_NOINIT_UNSPECIFIED
    #define STOP_SEC_VAR
#endif
#ifdef DIO_STOP_SEC_VAR_FAST_UNSPECIFIED
  #undef DIO_STOP_SEC_VAR_FAST_UNSPECIFIED
    #define STOP_SEC_VAR
#endif
#ifdef DIO_STOP_SEC_CONFIG_VAR_NOINIT_UNSPECIFIED
  #undef DIO_STOP_SEC_CONFIG_VAR_NOINIT_UNSPECIFIED
    #define STOP_SEC_VAR
#endif
/**************************************** Start CONST sections ********************************************************/
#ifdef  DIO_START_SEC_CONST_1BIT
  #undef DIO_START_SEC_CONST_1BIT
    #define START_SEC_CONST_UNSPECIFIED
#endif
#ifdef DIO_START_SEC_CONST_8BIT
  #undef DIO_START_SEC_CONST_8BIT
    #define START_SEC_CONST_8BIT
#endif
#ifdef DIO_START_SEC_CONST_16BIT
  #undef DIO_START_SEC_CONST_16BIT
    #define START_SEC_CONST_16BIT
#endif
#ifdef  DIO_START_SEC_CONST_32BIT
  #undef DIO_START_SEC_CONST_32BIT
    #define START_SEC_CONST_32BIT
#endif
#ifdef DIO_START_SEC_CONST_UNSPECIFIED
  #undef DIO_START_SEC_CONST_UNSPECIFIED
    #define START_SEC_CONST_UNSPECIFIED
#endif
/**************************************** Stop CONST sections *********************************************************/
#ifdef DIO_STOP_SEC_CONST_1BIT
  #undef DIO_STOP_SEC_CONST_1BIT
    #define STOP_SEC_CONST
#endif
#ifdef  DIO_STOP_SEC_CONST_8BIT
  #undef DIO_STOP_SEC_CONST_8BIT
    #define STOP_SEC_CONST
#endif
#ifdef DIO_STOP_SEC_CONST_16BIT
  #undef DIO_STOP_SEC_CONST_16BIT
    #define STOP_SEC_CONST
#endif
#ifdef DIO_STOP_SEC_CONST_32BIT
  #undef DIO_STOP_SEC_CONST_32BIT
    #define STOP_SEC_CONST
#endif
#ifdef DIO_STOP_SEC_CONST_UNSPECIFIED
  #undef DIO_STOP_SEC_CONST_UNSPECIFIED
    #define STOP_SEC_CONST
#endif
/**************************************** START CONFIG sections *******************************************************/
#ifdef DIO_START_SEC_CONFIG_DATA_UNSPECIFIED
  #undef  DIO_START_SEC_CONFIG_DATA_UNSPECIFIED
    #define START_SEC_CONST_PBCFG
#endif
#ifdef  DIO_START_SEC_DBTOC_DATA_UNSPECIFIED
  #undef DIO_START_SEC_DBTOC_DATA_UNSPECIFIED
    #define START_SEC_CONST_PBCFG
#endif
/**************************************** START CONFIG sections *******************************************************/
#ifdef DIO_STOP_SEC_CONFIG_DATA_UNSPECIFIED
  #undef DIO_STOP_SEC_CONFIG_DATA_UNSPECIFIED
    #define STOP_SEC_CONST
#endif
#ifdef  DIO_STOP_SEC_DBTOC_DATA_UNSPECIFIED
  #undef DIO_STOP_SEC_DBTOC_DATA_UNSPECIFIED
    #define STOP_SEC_CONST
#endif

/*******************************************************************************************************************************
 *  DIO STOP
 ******************************************************************************************************************************/


/*******************************************************************************************************************************
 *  FLS START
 ******************************************************************************************************************************/

/**************************************** Start CODE sections *****************************************************************/
#ifdef FLS_START_SEC_SCHEDULER_CODE
  #undef FLS_START_SEC_SCHEDULER_CODE
    #define START_SEC_CODE
#endif
#ifdef FLS_START_SEC_BUFFER_CODE
  #undef FLS_START_SEC_BUFFER_CODE
    #define START_SEC_VAR_NOINIT_32BIT
#endif
#ifdef FLS_START_SEC_PUBLIC_CODE
  #undef FLS_START_SEC_PUBLIC_CODE
    #define START_SEC_CODE
#endif
#ifdef FLS_START_SEC_PRIVATE_CODE
  #undef FLS_START_SEC_PRIVATE_CODE
    #define START_SEC_CODE
#endif

#ifdef FLS_START_SEC_APPL_CODE
  #undef FLS_START_SEC_APPL_CODE
    #define START_SEC_CODE
#endif
#ifdef FLS_START_SEC_CODE_FAST
  #undef FLS_START_SEC_CODE_FAST
    #define START_SEC_CODE
#endif

/**************************************** Stop CODE sections *****************************************************************/
#ifdef FLS_STOP_SEC_PUBLIC_CODE
  #undef FLS_STOP_SEC_PUBLIC_CODE
    #define STOP_SEC_CODE
#endif
#ifdef FLS_STOP_SEC_SCHEDULER_CODE
  #undef FLS_STOP_SEC_SCHEDULER_CODE
    #define STOP_SEC_CODE
#endif
#ifdef FLS_STOP_SEC_BUFFER_CODE
  #undef FLS_STOP_SEC_BUFFER_CODE
    #define STOP_SEC_VAR
#endif
#ifdef FLS_STOP_SEC_PRIVATE_CODE
  #undef FLS_STOP_SEC_PRIVATE_CODE
    #define STOP_SEC_CODE
#endif
#ifdef FLS_STOP_SEC_APPL_CODE
  #undef FLS_STOP_SEC_APPL_CODE
    #define STOP_SEC_CODE
#endif
#ifdef FLS_STOP_SEC_CODE_FAST
  #undef FLS_STOP_SEC_CODE_FAST
    #define STOP_SEC_CODE
#endif
/**************************************** Start VAR sections *****************************************************************/
#ifdef FLS_START_SEC_VAR_1BIT
  #undef FLS_START_SEC_VAR_1BIT
    #define START_SEC_VAR_INIT_UNSPECIFIED
#endif
#ifdef FLS_START_SEC_VAR_NOINIT_1BIT
  #undef FLS_START_SEC_VAR_NOINIT_1BIT
    #define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#ifdef FLS_START_SEC_VAR_FAST_1BIT
  #undef FLS_START_SEC_VAR_FAST_1BIT
    #define START_SEC_VAR_FAST_INIT_UNSPECIFIED
#endif
#ifdef  FLS_START_SEC_VAR_8BIT
  #undef FLS_START_SEC_VAR_8BIT
    #define START_SEC_VAR_INIT_8BIT
#endif
#ifdef FLS_START_SEC_VAR_NOINIT_8BIT
  #undef FLS_START_SEC_VAR_NOINIT_8BIT
    #define START_SEC_VAR_NOINIT_8BIT
#endif
#ifdef FLS_START_SEC_VAR_FAST_8BIT
  #undef  FLS_START_SEC_VAR_FAST_8BIT
    #define START_SEC_VAR_FAST_INIT_8BIT
#endif
#ifdef FLS_START_SEC_VAR_16BIT
  #undef  FLS_START_SEC_VAR_16BIT
    #define START_SEC_VAR_INIT_16BIT
#endif
#ifdef FLS_START_SEC_VAR_NOINIT_16BIT
  #undef  FLS_START_SEC_VAR_NOINIT_16BIT
    #define START_SEC_VAR_NOINIT_16BIT
#endif
#ifdef FLS_START_SEC_VAR_FAST_16BIT
  #undef  FLS_START_SEC_VAR_FAST_16BIT
    #define START_SEC_VAR_FAST_INIT_16BIT
#endif
#ifdef FLS_START_SEC_VAR_NOINIT_32BIT
  #undef  FLS_START_SEC_VAR_NOINIT_32BIT
    #define START_SEC_VAR_NOINIT_32BIT
#endif
#ifdef FLS_START_SEC_VAR_32BIT
  #undef  FLS_START_SEC_VAR_32BIT
    #define START_SEC_VAR_INIT_32BIT
#endif
#ifdef FLS_START_SEC_VAR_FAST_32BIT
  #undef  FLS_START_SEC_VAR_FAST_32BIT
    #define START_SEC_VAR_FAST_INIT_32BIT
#endif
#ifdef FLS_START_SEC_VAR_UNSPECIFIED
  #undef  FLS_START_SEC_VAR_UNSPECIFIED
    #define START_SEC_VAR_INIT_UNSPECIFIED
#endif
#ifdef FLS_START_SEC_VAR_NOINIT_UNSPECIFIED
  #undef  FLS_START_SEC_VAR_NOINIT_UNSPECIFIED
    #define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#ifdef FLS_START_SEC_VAR_FAST_UNSPECIFIED
  #undef  FLS_START_SEC_VAR_FAST_UNSPECIFIED
    #define START_SEC_VAR_FAST_INIT_UNSPECIFIED
#endif
#ifdef FLS_START_SEC_CONFIG_VAR_NOINIT_UNSPECIFIED
  #undef  FLS_START_SEC_CONFIG_VAR_NOINIT_UNSPECIFIED
    #define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
/**************************************** Stop VAR sections *****************************************************************/
#ifdef FLS_STOP_SEC_VAR_1BIT
  #undef FLS_STOP_SEC_VAR_1BIT
    #define STOP_SEC_VAR
#endif
#ifdef FLS_STOP_SEC_VAR_NOINIT_1BIT
  #undef FLS_STOP_SEC_VAR_NOINIT_1BIT
    #define STOP_SEC_VAR
#endif
#ifdef FLS_STOP_SEC_VAR_FAST_1BIT
  #undef FLS_STOP_SEC_VAR_FAST_1BIT
    #define STOP_SEC_VAR
#endif
#ifdef  FLS_STOP_SEC_VAR_8BIT
  #undef FLS_STOP_SEC_VAR_8BIT
    #define STOP_SEC_VAR
#endif
#ifdef FLS_STOP_SEC_VAR_NOINIT_8BIT
  #undef FLS_STOP_SEC_VAR_NOINIT_8BIT
    #define STOP_SEC_VAR
#endif
#ifdef FLS_STOP_SEC_VAR_FAST_8BIT
  #undef FLS_STOP_SEC_VAR_FAST_8BIT
    #define STOP_SEC_VAR
#endif

#ifdef FLS_STOP_SEC_VAR_16BIT
  #undef FLS_STOP_SEC_VAR_16BIT
    #define STOP_SEC_VAR
#endif
#ifdef FLS_STOP_SEC_VAR_NOINIT_16BIT
  #undef FLS_STOP_SEC_VAR_NOINIT_16BIT
    #define STOP_SEC_VAR
#endif
#ifdef  FLS_STOP_SEC_VAR_FAST_16BIT
  #undef FLS_STOP_SEC_VAR_FAST_16BIT
    #define STOP_SEC_VAR
#endif
#ifdef FLS_STOP_SEC_VAR_32BIT
  #undef FLS_STOP_SEC_VAR_32BIT
    #define STOP_SEC_VAR
#endif
#ifdef  FLS_STOP_SEC_VAR_NOINIT_32BIT
  #undef  FLS_STOP_SEC_VAR_NOINIT_32BIT
    #define STOP_SEC_VAR
#endif
#ifdef FLS_STOP_SEC_VAR_FAST_32BIT
  #undef FLS_STOP_SEC_VAR_FAST_32BIT
    #define STOP_SEC_VAR
#endif
#ifdef FLS_STOP_SEC_VAR_UNSPECIFIED
  #undef FLS_STOP_SEC_VAR_UNSPECIFIED
    #define STOP_SEC_VAR
#endif
#ifdef FLS_STOP_SEC_VAR_NOINIT_UNSPECIFIED
  #undef FLS_STOP_SEC_VAR_NOINIT_UNSPECIFIED
    #define STOP_SEC_VAR
#endif
#ifdef FLS_STOP_SEC_VAR_FAST_UNSPECIFIED
  #undef FLS_STOP_SEC_VAR_FAST_UNSPECIFIED
    #define STOP_SEC_VAR
#endif
#ifdef FLS_STOP_SEC_CONFIG_VAR_NOINIT_UNSPECIFIED
  #undef FLS_STOP_SEC_CONFIG_VAR_NOINIT_UNSPECIFIED
    #define STOP_SEC_VAR
#endif
/**************************************** Start CONST sections *****************************************************************/
#ifdef  FLS_START_SEC_CONST_1BIT
  #undef FLS_START_SEC_CONST_1BIT
    #define START_SEC_CONST_UNSPECIFIED
#endif
#ifdef FLS_START_SEC_CONST_8BIT
  #undef FLS_START_SEC_CONST_8BIT
    #define START_SEC_CONST_8BIT
#endif
#ifdef FLS_START_SEC_CONST_16BIT
  #undef FLS_START_SEC_CONST_16BIT
    #define START_SEC_CONST_16BIT
#endif
#ifdef  FLS_START_SEC_CONST_32BIT
  #undef FLS_START_SEC_CONST_32BIT
    #define START_SEC_CONST_32BIT
#endif
#ifdef FLS_START_SEC_CONST_UNSPECIFIED
  #undef FLS_START_SEC_CONST_UNSPECIFIED
    #define START_SEC_CONST_UNSPECIFIED
#endif
/**************************************** Stop CONST sections *****************************************************************/
#ifdef FLS_STOP_SEC_CONST_1BIT
  #undef FLS_STOP_SEC_CONST_1BIT
    #define STOP_SEC_CONST
#endif
#ifdef  FLS_STOP_SEC_CONST_8BIT
  #undef FLS_STOP_SEC_CONST_8BIT
    #define STOP_SEC_CONST
#endif
#ifdef FLS_STOP_SEC_CONST_16BIT
  #undef FLS_STOP_SEC_CONST_16BIT
    #define STOP_SEC_CONST
#endif
#ifdef FLS_STOP_SEC_CONST_32BIT
  #undef FLS_STOP_SEC_CONST_32BIT
    #define STOP_SEC_CONST
#endif
#ifdef FLS_STOP_SEC_CONST_UNSPECIFIED
  #undef FLS_STOP_SEC_CONST_UNSPECIFIED
    #define STOP_SEC_CONST
#endif
/**************************************** START CONFIG sections *****************************************************************/
#ifdef FLS_START_SEC_CONFIG_DATA_UNSPECIFIED
  #undef  FLS_START_SEC_CONFIG_DATA_UNSPECIFIED
    #define START_SEC_CONST_PBCFG
#endif
#ifdef  FLS_START_SEC_DBTOC_DATA_UNSPECIFIED
  #undef FLS_START_SEC_DBTOC_DATA_UNSPECIFIED
    #define START_SEC_CONST_PBCFG
#endif
/**************************************** START CONFIG sections *****************************************************************/
#ifdef FLS_STOP_SEC_CONFIG_DATA_UNSPECIFIED
  #undef FLS_STOP_SEC_CONFIG_DATA_UNSPECIFIED
    #define STOP_SEC_CONST
#endif
#ifdef  FLS_STOP_SEC_DBTOC_DATA_UNSPECIFIED
  #undef FLS_STOP_SEC_DBTOC_DATA_UNSPECIFIED
    #define STOP_SEC_CONST
#endif

/*******************************************************************************************************************************
 *  FLS STOP
 ******************************************************************************************************************************/


/**********************************************************************************************************************
 *  GPT START
 **********************************************************************************************************************/

#ifdef GPT_START_SEC_CODE_FAST
  #undef GPT_START_SEC_CODE_FAST
  #define START_SEC_CODE_FAST
#endif

#ifdef GPT_STOP_SEC_CODE_FAST
  #undef GPT_STOP_SEC_CODE_FAST
  #define STOP_SEC_CODE
#endif

#ifdef GPT_START_SEC_PRIVATE_CODE
  #undef GPT_START_SEC_PRIVATE_CODE
  #define START_SEC_CODE
#endif

#ifdef GPT_STOP_SEC_PRIVATE_CODE
  #undef GPT_STOP_SEC_PRIVATE_CODE
  #define STOP_SEC_CODE
#endif

#ifdef GPT_START_SEC_PUBLIC_CODE
  #undef GPT_START_SEC_PUBLIC_CODE
  #define START_SEC_CODE
#endif

#ifdef GPT_STOP_SEC_PUBLIC_CODE
  #undef GPT_STOP_SEC_PUBLIC_CODE
  #define STOP_SEC_CODE
#endif

#ifdef GPT_START_SEC_VAR_1BIT
  #undef GPT_START_SEC_VAR_1BIT
  #define START_SEC_VAR_INIT_UNSPECIFIED
#endif

#ifdef GPT_STOP_SEC_VAR_1BIT
  #undef GPT_STOP_SEC_VAR_1BIT
  #define STOP_SEC_VAR
#endif

#ifdef GPT_START_SEC_VAR_BOOLEAN
  #undef GPT_START_SEC_VAR_BOOLEAN
  #define START_SEC_VAR_INIT_UNSPECIFIED
#endif

#ifdef GPT_STOP_SEC_VAR_BOOLEAN
  #undef GPT_STOP_SEC_VAR_BOOLEAN
  #define STOP_SEC_VAR
#endif

#ifdef GPT_START_SEC_VAR_NOINIT_8
  #undef GPT_START_SEC_VAR_NOINIT_8
  #define START_SEC_VAR_NOINIT_8BIT
#endif

#ifdef GPT_STOP_SEC_VAR_NOINIT_8
  #undef GPT_STOP_SEC_VAR_NOINIT_8
  #define STOP_SEC_VAR
#endif

#ifdef GPT_START_SEC_VAR_NOINIT_8BIT
  #undef GPT_START_SEC_VAR_NOINIT_8BIT
  #define START_SEC_VAR_NOINIT_8BIT
#endif

#ifdef GPT_STOP_SEC_VAR_NOINIT_8BIT
  #undef GPT_STOP_SEC_VAR_NOINIT_8BIT
  #define STOP_SEC_VAR
#endif

#ifdef GPT_START_SEC_VAR_NOINIT_UNSPECIFIED
  #undef GPT_START_SEC_VAR_NOINIT_UNSPECIFIED
  #define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif

#ifdef GPT_STOP_SEC_VAR_NOINIT_UNSPECIFIED
  #undef GPT_STOP_SEC_VAR_NOINIT_UNSPECIFIED
  #define STOP_SEC_VAR
#endif

#ifdef GPT_START_SEC_CONFIG_VAR_NOINIT_UNSPECIFIED
  #undef  GPT_START_SEC_CONFIG_VAR_NOINIT_UNSPECIFIED
    #define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif

#ifdef GPT_STOP_SEC_CONFIG_VAR_NOINIT_UNSPECIFIED
  #undef GPT_STOP_SEC_CONFIG_VAR_NOINIT_UNSPECIFIED
    #define STOP_SEC_VAR
#endif

#ifdef GPT_START_SEC_CONFIG_DATA_UNSPECIFIED
  #undef  GPT_START_SEC_CONFIG_DATA_UNSPECIFIED
    #define START_SEC_CONST_PBCFG
#endif

#ifdef GPT_STOP_SEC_CONFIG_DATA_UNSPECIFIED
  #undef GPT_STOP_SEC_CONFIG_DATA_UNSPECIFIED
    #define STOP_SEC_CONST
#endif

#ifdef  GPT_START_SEC_DBTOC_DATA_UNSPECIFIED
  #undef GPT_START_SEC_DBTOC_DATA_UNSPECIFIED
    #define START_SEC_CONST_PBCFG
#endif

#ifdef  GPT_STOP_SEC_DBTOC_DATA_UNSPECIFIED
  #undef GPT_STOP_SEC_DBTOC_DATA_UNSPECIFIED
    #define STOP_SEC_CONST
#endif

#ifdef GPT_START_SEC_APPL_CODE
  #undef GPT_START_SEC_APPL_CODE
  #define START_SEC_CODE
#endif

#ifdef GPT_STOP_SEC_APPL_CODE
  #undef GPT_STOP_SEC_APPL_CODE
  #define STOP_SEC_CODE
#endif

/*******************************************************************************************************************************
 *  GPT STOP
 ******************************************************************************************************************************/

/***********************************************************************************************************************
 *  ICU Sections
 **********************************************************************************************************************/

/**************************************** Start CODE sections *********************************************************/
#ifdef ICU_START_SEC_CODE_FAST
  #undef ICU_START_SEC_CODE_FAST
    #define START_SEC_CODE
#endif
#ifdef ICU_START_SEC_PUBLIC_CODE
  #undef ICU_START_SEC_PUBLIC_CODE
    #define START_SEC_CODE
#endif
#ifdef ICU_START_SEC_PRIVATE_CODE
  #undef ICU_START_SEC_PRIVATE_CODE
    #define START_SEC_CODE
#endif

#ifdef ICU_START_SEC_APPL_CODE
  #undef ICU_START_SEC_APPL_CODE
    #define START_SEC_CODE
#endif
/**************************************** Stop CODE sections **********************************************************/
#ifdef ICU_STOP_SEC_CODE_FAST
  #undef ICU_STOP_SEC_CODE_FAST
    #define STOP_SEC_CODE
#endif
#ifdef ICU_STOP_SEC_PUBLIC_CODE
  #undef ICU_STOP_SEC_PUBLIC_CODE
    #define STOP_SEC_CODE
#endif
#ifdef ICU_STOP_SEC_PRIVATE_CODE
  #undef ICU_STOP_SEC_PRIVATE_CODE
    #define STOP_SEC_CODE
#endif
#ifdef ICU_STOP_SEC_APPL_CODE
  #undef ICU_STOP_SEC_APPL_CODE
    #define STOP_SEC_CODE
#endif
/**************************************** Start VAR sections **********************************************************/
#ifdef ICU_START_SEC_VAR_1BIT
  #undef ICU_START_SEC_VAR_1BIT
    #define START_SEC_VAR_INIT_UNSPECIFIED
#endif
#ifdef ICU_START_SEC_VAR_NOINIT_1BIT
  #undef ICU_START_SEC_VAR_NOINIT_1BIT
    #define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#ifdef ICU_START_SEC_VAR_FAST_1BIT
  #undef ICU_START_SEC_VAR_FAST_1BIT
    #define START_SEC_VAR_FAST_INIT_UNSPECIFIED
#endif
#ifdef  ICU_START_SEC_VAR_8BIT
  #undef ICU_START_SEC_VAR_8BIT
    #define START_SEC_VAR_INIT_8BIT
#endif
#ifdef ICU_START_SEC_VAR_NOINIT_8BIT
  #undef ICU_START_SEC_VAR_NOINIT_8BIT
    #define START_SEC_VAR_NOINIT_8BIT
#endif
#ifdef ICU_START_SEC_VAR_FAST_8BIT
  #undef  ICU_START_SEC_VAR_FAST_8BIT
    #define START_SEC_VAR_FAST_INIT_8BIT
#endif
#ifdef ICU_START_SEC_VAR_16BIT
  #undef  ICU_START_SEC_VAR_16BIT
    #define START_SEC_VAR_INIT_16BIT
#endif
#ifdef ICU_START_SEC_VAR_NOINIT_16BIT
  #undef  ICU_START_SEC_VAR_NOINIT_16BIT
    #define START_SEC_VAR_NOINIT_16BIT
#endif
#ifdef ICU_START_SEC_VAR_FAST_16BIT
  #undef  ICU_START_SEC_VAR_FAST_16BIT
    #define START_SEC_VAR_FAST_INIT_16BIT
#endif
#ifdef ICU_START_SEC_VAR_NOINIT_32BIT
  #undef  ICU_START_SEC_VAR_NOINIT_32BIT
    #define START_SEC_VAR_NOINIT_32BIT
#endif
#ifdef ICU_START_SEC_VAR_32BIT
  #undef  ICU_START_SEC_VAR_32BIT
    #define START_SEC_VAR_INIT_32BIT
#endif
#ifdef ICU_START_SEC_VAR_FAST_32BIT
  #undef  ICU_START_SEC_VAR_FAST_32BIT
    #define START_SEC_VAR_FAST_INIT_32BIT
#endif
#ifdef ICU_START_SEC_VAR_UNSPECIFIED
  #undef  ICU_START_SEC_VAR_UNSPECIFIED
    #define START_SEC_VAR_INIT_UNSPECIFIED
#endif
#ifdef ICU_START_SEC_VAR_NOINIT_UNSPECIFIED
  #undef  ICU_START_SEC_VAR_NOINIT_UNSPECIFIED
    #define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#ifdef ICU_START_SEC_VAR_FAST_UNSPECIFIED
  #undef  ICU_START_SEC_VAR_FAST_UNSPECIFIED
    #define START_SEC_VAR_FAST_INIT_UNSPECIFIED
#endif
#ifdef ICU_START_SEC_CONFIG_VAR_NOINIT_UNSPECIFIED
  #undef  ICU_START_SEC_CONFIG_VAR_NOINIT_UNSPECIFIED
    #define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
/**************************************** Stop VAR sections ***********************************************************/
#ifdef ICU_STOP_SEC_VAR_1BIT
  #undef ICU_STOP_SEC_VAR_1BIT
    #define STOP_SEC_VAR
#endif
#ifdef ICU_STOP_SEC_VAR_NOINIT_1BIT
  #undef ICU_STOP_SEC_VAR_NOINIT_1BIT
    #define STOP_SEC_VAR
#endif
#ifdef ICU_STOP_SEC_VAR_FAST_1BIT
  #undef ICU_STOP_SEC_VAR_FAST_1BIT
    #define STOP_SEC_VAR
#endif
#ifdef  ICU_STOP_SEC_VAR_8BIT
  #undef ICU_STOP_SEC_VAR_8BIT
    #define STOP_SEC_VAR
#endif
#ifdef ICU_STOP_SEC_VAR_NOINIT_8BIT
  #undef ICU_STOP_SEC_VAR_NOINIT_8BIT
    #define STOP_SEC_VAR
#endif
#ifdef ICU_STOP_SEC_VAR_FAST_8BIT
  #undef ICU_STOP_SEC_VAR_FAST_8BIT
    #define STOP_SEC_VAR
#endif

#ifdef ICU_STOP_SEC_VAR_16BIT
  #undef ICU_STOP_SEC_VAR_16BIT
    #define STOP_SEC_VAR
#endif
#ifdef ICU_STOP_SEC_VAR_NOINIT_16BIT
  #undef ICU_STOP_SEC_VAR_NOINIT_16BIT
    #define STOP_SEC_VAR
#endif
#ifdef  ICU_STOP_SEC_VAR_FAST_16BIT
  #undef ICU_STOP_SEC_VAR_FAST_16BIT
    #define STOP_SEC_VAR
#endif
#ifdef ICU_STOP_SEC_VAR_32BIT
  #undef ICU_STOP_SEC_VAR_32BIT
    #define STOP_SEC_VAR
#endif
#ifdef  ICU_STOP_SEC_VAR_NOINIT_32BIT
  #undef  ICU_STOP_SEC_VAR_NOINIT_32BIT
    #define STOP_SEC_VAR
#endif
#ifdef ICU_STOP_SEC_VAR_FAST_32BIT
  #undef ICU_STOP_SEC_VAR_FAST_32BIT
    #define STOP_SEC_VAR
#endif
#ifdef ICU_STOP_SEC_VAR_UNSPECIFIED
  #undef ICU_STOP_SEC_VAR_UNSPECIFIED
    #define STOP_SEC_VAR
#endif
#ifdef ICU_STOP_SEC_VAR_NOINIT_UNSPECIFIED
  #undef ICU_STOP_SEC_VAR_NOINIT_UNSPECIFIED
    #define STOP_SEC_VAR
#endif
#ifdef ICU_STOP_SEC_VAR_FAST_UNSPECIFIED
  #undef ICU_STOP_SEC_VAR_FAST_UNSPECIFIED
    #define STOP_SEC_VAR
#endif
#ifdef ICU_STOP_SEC_CONFIG_VAR_NOINIT_UNSPECIFIED
  #undef ICU_STOP_SEC_CONFIG_VAR_NOINIT_UNSPECIFIED
    #define STOP_SEC_VAR
#endif
/**************************************** Start CONST sections ********************************************************/
#ifdef  ICU_START_SEC_CONST_1BIT
  #undef ICU_START_SEC_CONST_1BIT
    #define START_SEC_CONST_UNSPECIFIED
#endif
#ifdef ICU_START_SEC_CONST_8BIT
  #undef ICU_START_SEC_CONST_8BIT
    #define START_SEC_CONST_8BIT
#endif
#ifdef ICU_START_SEC_CONST_16BIT
  #undef ICU_START_SEC_CONST_16BIT
    #define START_SEC_CONST_16BIT
#endif
#ifdef  ICU_START_SEC_CONST_32BIT
  #undef ICU_START_SEC_CONST_32BIT
    #define START_SEC_CONST_32BIT
#endif
#ifdef ICU_START_SEC_CONST_UNSPECIFIED
  #undef ICU_START_SEC_CONST_UNSPECIFIED
    #define START_SEC_CONST_UNSPECIFIED
#endif
/**************************************** Stop CONST sections *********************************************************/
#ifdef ICU_STOP_SEC_CONST_1BIT
  #undef ICU_STOP_SEC_CONST_1BIT
    #define STOP_SEC_CONST
#endif
#ifdef  ICU_STOP_SEC_CONST_8BIT
  #undef ICU_STOP_SEC_CONST_8BIT
    #define STOP_SEC_CONST
#endif
#ifdef ICU_STOP_SEC_CONST_16BIT
  #undef ICU_STOP_SEC_CONST_16BIT
    #define STOP_SEC_CONST
#endif
#ifdef ICU_STOP_SEC_CONST_32BIT
  #undef ICU_STOP_SEC_CONST_32BIT
    #define STOP_SEC_CONST
#endif
#ifdef ICU_STOP_SEC_CONST_UNSPECIFIED
  #undef ICU_STOP_SEC_CONST_UNSPECIFIED
    #define STOP_SEC_CONST
#endif
/**************************************** START CONFIG sections *******************************************************/
#ifdef ICU_START_SEC_CONFIG_DATA_UNSPECIFIED
  #undef  ICU_START_SEC_CONFIG_DATA_UNSPECIFIED
    #define START_SEC_CONST_PBCFG
#endif
#ifdef  ICU_START_SEC_DBTOC_DATA_UNSPECIFIED
  #undef ICU_START_SEC_DBTOC_DATA_UNSPECIFIED
    #define START_SEC_CONST_PBCFG
#endif
/**************************************** START CONFIG sections *******************************************************/
#ifdef ICU_STOP_SEC_CONFIG_DATA_UNSPECIFIED
  #undef ICU_STOP_SEC_CONFIG_DATA_UNSPECIFIED
    #define STOP_SEC_CONST
#endif
#ifdef  ICU_STOP_SEC_DBTOC_DATA_UNSPECIFIED
  #undef ICU_STOP_SEC_DBTOC_DATA_UNSPECIFIED
    #define STOP_SEC_CONST
#endif

/*******************************************************************************************************************************
 *  ICU STOP
 ******************************************************************************************************************************/

/***********************************************************************************************************************
 *  MCU Sections
 **********************************************************************************************************************/

#ifdef MCU_START_SEC_CODE_FAST
  #undef MCU_START_SEC_CODE_FAST
    #define START_SEC_CODE
#endif
#ifdef MCU_START_SEC_PUBLIC_CODE
  #undef MCU_START_SEC_PUBLIC_CODE
    #define START_SEC_CODE
#endif
#ifdef MCU_START_SEC_PRIVATE_CODE
  #undef MCU_START_SEC_PRIVATE_CODE
    #define START_SEC_CODE
#endif

#ifdef MCU_START_SEC_APPL_CODE
  #undef MCU_START_SEC_APPL_CODE
    #define START_SEC_CODE
#endif

#ifdef MCU_START_SEC_RRAM_ROM_CODE
  #undef MCU_START_SEC_RRAM_ROM_CODE
    #define START_SEC_CODE
#endif

#ifdef MCU_START_SEC_RRAM_CODE
  #undef MCU_START_SEC_RRAM_CODE
    #define START_SEC_CODE
#endif

/**************************************** Stop CODE sections **********************************************************/
#ifdef MCU_STOP_SEC_CODE_FAST
  #undef MCU_STOP_SEC_CODE_FAST
    #define STOP_SEC_CODE
#endif
#ifdef MCU_STOP_SEC_PUBLIC_CODE
  #undef MCU_STOP_SEC_PUBLIC_CODE
    #define STOP_SEC_CODE
#endif
#ifdef MCU_STOP_SEC_PRIVATE_CODE
  #undef MCU_STOP_SEC_PRIVATE_CODE
    #define STOP_SEC_CODE
#endif
#ifdef MCU_STOP_SEC_APPL_CODE
  #undef MCU_STOP_SEC_APPL_CODE
    #define STOP_SEC_CODE
#endif

#ifdef MCU_STOP_SEC_RRAM_ROM_CODE
  #undef MCU_STOP_SEC_RRAM_ROM_CODE
    #define STOP_SEC_CODE
#endif

#ifdef MCU_STOP_SEC_RRAM_CODE
  #undef MCU_STOP_SEC_RRAM_CODE
    #define STOP_SEC_CODE
#endif

/**************************************** Start VAR sections **********************************************************/
#ifdef MCU_START_SEC_VAR_1BIT
  #undef MCU_START_SEC_VAR_1BIT
    #define START_SEC_VAR_INIT_UNSPECIFIED
#endif
#ifdef MCU_START_SEC_VAR_NOINIT_1BIT
  #undef MCU_START_SEC_VAR_NOINIT_1BIT
    #define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#ifdef MCU_START_SEC_VAR_FAST_1BIT
  #undef MCU_START_SEC_VAR_FAST_1BIT
    #define START_SEC_VAR_FAST_INIT_UNSPECIFIED
#endif
#ifdef  MCU_START_SEC_VAR_8BIT
  #undef MCU_START_SEC_VAR_8BIT
    #define START_SEC_VAR_INIT_8BIT
#endif
#ifdef MCU_START_SEC_VAR_NOINIT_8BIT
  #undef MCU_START_SEC_VAR_NOINIT_8BIT
    #define START_SEC_VAR_NOINIT_8BIT
#endif
#ifdef MCU_START_SEC_VAR_FAST_8BIT
  #undef  MCU_START_SEC_VAR_FAST_8BIT
    #define START_SEC_VAR_FAST_INIT_8BIT
#endif
#ifdef MCU_START_SEC_VAR_16BIT
  #undef  MCU_START_SEC_VAR_16BIT
    #define START_SEC_VAR_INIT_16BIT
#endif
#ifdef MCU_START_SEC_VAR_NOINIT_16BIT
  #undef  MCU_START_SEC_VAR_NOINIT_16BIT
    #define START_SEC_VAR_NOINIT_16BIT
#endif
#ifdef MCU_START_SEC_VAR_FAST_16BIT
  #undef  MCU_START_SEC_VAR_FAST_16BIT
    #define START_SEC_VAR_FAST_INIT_16BIT
#endif
#ifdef MCU_START_SEC_VAR_NOINIT_32BIT
  #undef  MCU_START_SEC_VAR_NOINIT_32BIT
    #define START_SEC_VAR_NOINIT_32BIT
#endif
#ifdef MCU_START_SEC_VAR_32BIT
  #undef  MCU_START_SEC_VAR_32BIT
    #define START_SEC_VAR_INIT_32BIT
#endif
#ifdef MCU_START_SEC_VAR_FAST_32BIT
  #undef  MCU_START_SEC_VAR_FAST_32BIT
    #define START_SEC_VAR_FAST_INIT_32BIT
#endif
#ifdef MCU_START_SEC_VAR_UNSPECIFIED
  #undef  MCU_START_SEC_VAR_UNSPECIFIED
    #define START_SEC_VAR_INIT_UNSPECIFIED
#endif
#ifdef MCU_START_SEC_VAR_NOINIT_UNSPECIFIED
  #undef  MCU_START_SEC_VAR_NOINIT_UNSPECIFIED
    #define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#ifdef MCU_START_SEC_VAR_FAST_UNSPECIFIED
  #undef  MCU_START_SEC_VAR_FAST_UNSPECIFIED
    #define START_SEC_VAR_FAST_INIT_UNSPECIFIED
#endif

#ifdef MCU_START_SEC_BURAM_VAR_NOINIT_UNSPECIFIED
  #undef  MCU_START_SEC_BURAM_VAR_NOINIT_UNSPECIFIED
    #define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif

#ifdef MCU_START_SEC_CONFIG_VAR_NOINIT_UNSPECIFIED
  #undef  MCU_START_SEC_CONFIG_VAR_NOINIT_UNSPECIFIED
    #define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
/**************************************** Stop VAR sections ***********************************************************/
#ifdef MCU_STOP_SEC_VAR_1BIT
  #undef MCU_STOP_SEC_VAR_1BIT
    #define STOP_SEC_VAR
#endif
#ifdef MCU_STOP_SEC_VAR_NOINIT_1BIT
  #undef MCU_STOP_SEC_VAR_NOINIT_1BIT
    #define STOP_SEC_VAR
#endif
#ifdef MCU_STOP_SEC_VAR_FAST_1BIT
  #undef MCU_STOP_SEC_VAR_FAST_1BIT
    #define STOP_SEC_VAR
#endif
#ifdef  MCU_STOP_SEC_VAR_8BIT
  #undef MCU_STOP_SEC_VAR_8BIT
    #define STOP_SEC_VAR
#endif
#ifdef MCU_STOP_SEC_VAR_NOINIT_8BIT
  #undef MCU_STOP_SEC_VAR_NOINIT_8BIT
    #define STOP_SEC_VAR
#endif
#ifdef MCU_STOP_SEC_VAR_FAST_8BIT
  #undef MCU_STOP_SEC_VAR_FAST_8BIT
    #define STOP_SEC_VAR
#endif

#ifdef MCU_STOP_SEC_VAR_16BIT
  #undef MCU_STOP_SEC_VAR_16BIT
    #define STOP_SEC_VAR
#endif
#ifdef MCU_STOP_SEC_VAR_NOINIT_16BIT
  #undef MCU_STOP_SEC_VAR_NOINIT_16BIT
    #define STOP_SEC_VAR
#endif
#ifdef  MCU_STOP_SEC_VAR_FAST_16BIT
  #undef MCU_STOP_SEC_VAR_FAST_16BIT
    #define STOP_SEC_VAR
#endif
#ifdef MCU_STOP_SEC_VAR_32BIT
  #undef MCU_STOP_SEC_VAR_32BIT
    #define STOP_SEC_VAR
#endif
#ifdef  MCU_STOP_SEC_VAR_NOINIT_32BIT
  #undef  MCU_STOP_SEC_VAR_NOINIT_32BIT
    #define STOP_SEC_VAR
#endif
#ifdef MCU_STOP_SEC_VAR_FAST_32BIT
  #undef MCU_STOP_SEC_VAR_FAST_32BIT
    #define STOP_SEC_VAR
#endif
#ifdef MCU_STOP_SEC_VAR_UNSPECIFIED
  #undef MCU_STOP_SEC_VAR_UNSPECIFIED
    #define STOP_SEC_VAR
#endif
#ifdef MCU_STOP_SEC_VAR_NOINIT_UNSPECIFIED
  #undef MCU_STOP_SEC_VAR_NOINIT_UNSPECIFIED
    #define STOP_SEC_VAR
#endif
#ifdef MCU_STOP_SEC_VAR_FAST_UNSPECIFIED
  #undef MCU_STOP_SEC_VAR_FAST_UNSPECIFIED
    #define STOP_SEC_VAR
#endif

#ifdef MCU_STOP_SEC_CONFIG_VAR_NOINIT_UNSPECIFIED
  #undef MCU_STOP_SEC_CONFIG_VAR_NOINIT_UNSPECIFIED
    #define STOP_SEC_VAR
#endif

#ifdef MCU_STOP_SEC_BURAM_VAR_NOINIT_UNSPECIFIED
  #undef MCU_STOP_SEC_BURAM_VAR_NOINIT_UNSPECIFIED
    #define STOP_SEC_VAR
#endif
/**************************************** Start CONST sections ********************************************************/
#ifdef  MCU_START_SEC_CONST_1BIT
  #undef MCU_START_SEC_CONST_1BIT
    #define START_SEC_CONST_UNSPECIFIED
#endif
#ifdef MCU_START_SEC_CONST_8BIT
  #undef MCU_START_SEC_CONST_8BIT
    #define START_SEC_CONST_8BIT
#endif
#ifdef MCU_START_SEC_CONST_16BIT
  #undef MCU_START_SEC_CONST_16BIT
    #define START_SEC_CONST_16BIT
#endif
#ifdef  MCU_START_SEC_CONST_32BIT
  #undef MCU_START_SEC_CONST_32BIT
    #define START_SEC_CONST_32BIT
#endif
#ifdef MCU_START_SEC_CONST_UNSPECIFIED
  #undef MCU_START_SEC_CONST_UNSPECIFIED
    #define START_SEC_CONST_UNSPECIFIED
#endif
/**************************************** Stop CONST sections *********************************************************/
#ifdef MCU_STOP_SEC_CONST_1BIT
  #undef MCU_STOP_SEC_CONST_1BIT
    #define STOP_SEC_CONST
#endif
#ifdef  MCU_STOP_SEC_CONST_8BIT
  #undef MCU_STOP_SEC_CONST_8BIT
    #define STOP_SEC_CONST
#endif
#ifdef MCU_STOP_SEC_CONST_16BIT
  #undef MCU_STOP_SEC_CONST_16BIT
    #define STOP_SEC_CONST
#endif
#ifdef MCU_STOP_SEC_CONST_32BIT
  #undef MCU_STOP_SEC_CONST_32BIT
    #define STOP_SEC_CONST
#endif
#ifdef MCU_STOP_SEC_CONST_UNSPECIFIED
  #undef MCU_STOP_SEC_CONST_UNSPECIFIED
    #define STOP_SEC_CONST
#endif
/**************************************** START CONFIG sections ********************************************************/
#ifdef MCU_START_SEC_CONFIG_DATA_UNSPECIFIED
  #undef  MCU_START_SEC_CONFIG_DATA_UNSPECIFIED
    #define START_SEC_CONST_PBCFG
#endif
#ifdef  MCU_START_SEC_DBTOC_DATA_UNSPECIFIED
  #undef MCU_START_SEC_DBTOC_DATA_UNSPECIFIED
    #define START_SEC_CONST_PBCFG
#endif
/**************************************** START CONFIG sections ********************************************************/
#ifdef MCU_STOP_SEC_CONFIG_DATA_UNSPECIFIED
  #undef MCU_STOP_SEC_CONFIG_DATA_UNSPECIFIED
    #define STOP_SEC_CONST
#endif
#ifdef  MCU_STOP_SEC_DBTOC_DATA_UNSPECIFIED
  #undef MCU_STOP_SEC_DBTOC_DATA_UNSPECIFIED
    #define STOP_SEC_CONST
#endif

/*******************************************************************************************************************************
 *  MCU STOP
 ******************************************************************************************************************************/

/***********************************************************************************************************************
 *  PORT Sections
 **********************************************************************************************************************/

/**************************************** Start CODE sections *********************************************************/
#ifdef PORT_START_SEC_PUBLIC_CODE
  #undef PORT_START_SEC_PUBLIC_CODE
    #define START_SEC_CODE
#endif
#ifdef PORT_START_SEC_PRIVATE_CODE
  #undef PORT_START_SEC_PRIVATE_CODE
    #define START_SEC_CODE
#endif

#ifdef PORT_START_SEC_APPL_CODE
  #undef PORT_START_SEC_APPL_CODE
    #define START_SEC_CODE
#endif
/**************************************** Stop CODE sections **********************************************************/
#ifdef PORT_STOP_SEC_PUBLIC_CODE
  #undef PORT_STOP_SEC_PUBLIC_CODE
    #define STOP_SEC_CODE
#endif
#ifdef PORT_STOP_SEC_PRIVATE_CODE
  #undef PORT_STOP_SEC_PRIVATE_CODE
    #define STOP_SEC_CODE
#endif
#ifdef PORT_STOP_SEC_APPL_CODE
  #undef PORT_STOP_SEC_APPL_CODE
    #define STOP_SEC_CODE
#endif
/**************************************** Start VAR sections **********************************************************/
#ifdef PORT_START_SEC_VAR_1BIT
  #undef PORT_START_SEC_VAR_1BIT
    #define START_SEC_VAR_INIT_UNSPECIFIED
#endif
#ifdef PORT_START_SEC_VAR_NOINIT_1BIT
  #undef PORT_START_SEC_VAR_NOINIT_1BIT
    #define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#ifdef PORT_START_SEC_VAR_FAST_1BIT
  #undef PORT_START_SEC_VAR_FAST_1BIT
    #define START_SEC_VAR_FAST_INIT_UNSPECIFIED
#endif
#ifdef  PORT_START_SEC_VAR_8BIT
  #undef PORT_START_SEC_VAR_8BIT
    #define START_SEC_VAR_INIT_8BIT
#endif
#ifdef PORT_START_SEC_VAR_NOINIT_8BIT
  #undef PORT_START_SEC_VAR_NOINIT_8BIT
    #define START_SEC_VAR_NOINIT_8BIT
#endif
#ifdef PORT_START_SEC_VAR_FAST_8BIT
  #undef  PORT_START_SEC_VAR_FAST_8BIT
    #define START_SEC_VAR_FAST_INIT_8BIT
#endif
#ifdef PORT_START_SEC_VAR_16BIT
  #undef  PORT_START_SEC_VAR_16BIT
    #define START_SEC_VAR_INIT_16BIT
#endif
#ifdef PORT_START_SEC_VAR_NOINIT_16BIT
  #undef  PORT_START_SEC_VAR_NOINIT_16BIT
    #define START_SEC_VAR_NOINIT_16BIT
#endif
#ifdef PORT_START_SEC_VAR_FAST_16BIT
  #undef  PORT_START_SEC_VAR_FAST_16BIT
    #define START_SEC_VAR_FAST_INIT_16BIT
#endif
#ifdef PORT_START_SEC_VAR_NOINIT_32BIT
  #undef  PORT_START_SEC_VAR_NOINIT_32BIT
    #define START_SEC_VAR_NOINIT_32BIT
#endif
#ifdef PORT_START_SEC_VAR_32BIT
  #undef  PORT_START_SEC_VAR_32BIT
    #define START_SEC_VAR_INIT_32BIT
#endif
#ifdef PORT_START_SEC_VAR_FAST_32BIT
  #undef  PORT_START_SEC_VAR_FAST_32BIT
    #define START_SEC_VAR_FAST_INIT_32BIT
#endif
#ifdef PORT_START_SEC_VAR_UNSPECIFIED
  #undef  PORT_START_SEC_VAR_UNSPECIFIED
    #define START_SEC_VAR_INIT_UNSPECIFIED
#endif
#ifdef PORT_START_SEC_VAR_NOINIT_UNSPECIFIED
  #undef  PORT_START_SEC_VAR_NOINIT_UNSPECIFIED
    #define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#ifdef PORT_START_SEC_VAR_FAST_UNSPECIFIED
  #undef  PORT_START_SEC_VAR_FAST_UNSPECIFIED
    #define START_SEC_VAR_FAST_INIT_UNSPECIFIED
#endif
#ifdef PORT_START_SEC_CONFIG_VAR_NOINIT_UNSPECIFIED
  #undef  PORT_START_SEC_CONFIG_VAR_NOINIT_UNSPECIFIED
    #define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
/**************************************** Stop VAR sections ************************************************************/
#ifdef PORT_STOP_SEC_VAR_1BIT
  #undef PORT_STOP_SEC_VAR_1BIT
    #define STOP_SEC_VAR
#endif
#ifdef PORT_STOP_SEC_VAR_NOINIT_1BIT
  #undef PORT_STOP_SEC_VAR_NOINIT_1BIT
    #define STOP_SEC_VAR
#endif
#ifdef PORT_STOP_SEC_VAR_FAST_1BIT
  #undef PORT_STOP_SEC_VAR_FAST_1BIT
    #define STOP_SEC_VAR
#endif
#ifdef  PORT_STOP_SEC_VAR_8BIT
  #undef PORT_STOP_SEC_VAR_8BIT
    #define STOP_SEC_VAR
#endif
#ifdef PORT_STOP_SEC_VAR_NOINIT_8BIT
  #undef PORT_STOP_SEC_VAR_NOINIT_8BIT
    #define STOP_SEC_VAR
#endif
#ifdef PORT_STOP_SEC_VAR_FAST_8BIT
  #undef PORT_STOP_SEC_VAR_FAST_8BIT
    #define STOP_SEC_VAR
#endif

#ifdef PORT_STOP_SEC_VAR_16BIT
  #undef PORT_STOP_SEC_VAR_16BIT
    #define STOP_SEC_VAR
#endif
#ifdef PORT_STOP_SEC_VAR_NOINIT_16BIT
  #undef PORT_STOP_SEC_VAR_NOINIT_16BIT
    #define STOP_SEC_VAR
#endif
#ifdef  PORT_STOP_SEC_VAR_FAST_16BIT
  #undef PORT_STOP_SEC_VAR_FAST_16BIT
    #define STOP_SEC_VAR
#endif
#ifdef PORT_STOP_SEC_VAR_32BIT
  #undef PORT_STOP_SEC_VAR_32BIT
    #define STOP_SEC_VAR
#endif
#ifdef  PORT_STOP_SEC_VAR_NOINIT_32BIT
  #undef  PORT_STOP_SEC_VAR_NOINIT_32BIT
    #define STOP_SEC_VAR
#endif
#ifdef PORT_STOP_SEC_VAR_FAST_32BIT
  #undef PORT_STOP_SEC_VAR_FAST_32BIT
    #define STOP_SEC_VAR
#endif
#ifdef PORT_STOP_SEC_VAR_UNSPECIFIED
  #undef PORT_STOP_SEC_VAR_UNSPECIFIED
    #define STOP_SEC_VAR
#endif
#ifdef PORT_STOP_SEC_VAR_NOINIT_UNSPECIFIED
  #undef PORT_STOP_SEC_VAR_NOINIT_UNSPECIFIED
    #define STOP_SEC_VAR
#endif
#ifdef PORT_STOP_SEC_VAR_FAST_UNSPECIFIED
  #undef PORT_STOP_SEC_VAR_FAST_UNSPECIFIED
    #define STOP_SEC_VAR
#endif
#ifdef PORT_STOP_SEC_CONFIG_VAR_NOINIT_UNSPECIFIED
  #undef PORT_STOP_SEC_CONFIG_VAR_NOINIT_UNSPECIFIED
    #define STOP_SEC_VAR
#endif
/**************************************** Start CONST sections ********************************************************/
#ifdef  PORT_START_SEC_CONST_1BIT
  #undef PORT_START_SEC_CONST_1BIT
    #define START_SEC_CONST_UNSPECIFIED
#endif
#ifdef PORT_START_SEC_CONST_8BIT
  #undef PORT_START_SEC_CONST_8BIT
    #define START_SEC_CONST_8BIT
#endif
#ifdef PORT_START_SEC_CONST_16BIT
  #undef PORT_START_SEC_CONST_16BIT
    #define START_SEC_CONST_16BIT
#endif
#ifdef  PORT_START_SEC_CONST_32BIT
  #undef PORT_START_SEC_CONST_32BIT
    #define START_SEC_CONST_32BIT
#endif
#ifdef PORT_START_SEC_CONST_UNSPECIFIED
  #undef PORT_START_SEC_CONST_UNSPECIFIED
    #define START_SEC_CONST_UNSPECIFIED
#endif
/**************************************** Stop CONST sections *********************************************************/
#ifdef PORT_STOP_SEC_CONST_1BIT
  #undef PORT_STOP_SEC_CONST_1BIT
    #define STOP_SEC_CONST
#endif
#ifdef  PORT_STOP_SEC_CONST_8BIT
  #undef PORT_STOP_SEC_CONST_8BIT
    #define STOP_SEC_CONST
#endif
#ifdef PORT_STOP_SEC_CONST_16BIT
  #undef PORT_STOP_SEC_CONST_16BIT
    #define STOP_SEC_CONST
#endif
#ifdef PORT_STOP_SEC_CONST_32BIT
  #undef PORT_STOP_SEC_CONST_32BIT
    #define STOP_SEC_CONST
#endif
#ifdef PORT_STOP_SEC_CONST_UNSPECIFIED
  #undef PORT_STOP_SEC_CONST_UNSPECIFIED
    #define STOP_SEC_CONST
#endif
/**************************************** START CONFIG sections *******************************************************/
#ifdef PORT_START_SEC_CONFIG_DATA_UNSPECIFIED
  #undef  PORT_START_SEC_CONFIG_DATA_UNSPECIFIED
    #define START_SEC_CONST_PBCFG
#endif
#ifdef  PORT_START_SEC_DBTOC_DATA_UNSPECIFIED
  #undef PORT_START_SEC_DBTOC_DATA_UNSPECIFIED
    #define START_SEC_CONST_PBCFG
#endif
/**************************************** START CONFIG sections *******************************************************/
#ifdef PORT_STOP_SEC_CONFIG_DATA_UNSPECIFIED
  #undef PORT_STOP_SEC_CONFIG_DATA_UNSPECIFIED
    #define STOP_SEC_CONST
#endif
#ifdef  PORT_STOP_SEC_DBTOC_DATA_UNSPECIFIED
  #undef PORT_STOP_SEC_DBTOC_DATA_UNSPECIFIED
    #define STOP_SEC_CONST
#endif

/*******************************************************************************************************************************
 *  PORT STOP
 ******************************************************************************************************************************/

/***********************************************************************************************************************
 *  PWM Sections
 **********************************************************************************************************************/

/**************************************** Start CODE sections *********************************************************/
#ifdef PWM_START_SEC_CODE_FAST
  #undef PWM_START_SEC_CODE_FAST
    #define START_SEC_CODE
#endif
#ifdef PWM_START_SEC_PUBLIC_CODE
  #undef PWM_START_SEC_PUBLIC_CODE
    #define START_SEC_CODE
#endif
#ifdef PWM_START_SEC_PRIVATE_CODE
  #undef PWM_START_SEC_PRIVATE_CODE
    #define START_SEC_CODE
#endif

#ifdef PWM_START_SEC_APPL_CODE
  #undef PWM_START_SEC_APPL_CODE
    #define START_SEC_CODE
#endif
/**************************************** Stop CODE sections **********************************************************/
#ifdef PWM_STOP_SEC_CODE_FAST
  #undef PWM_STOP_SEC_CODE_FAST
    #define STOP_SEC_CODE
#endif
#ifdef PWM_STOP_SEC_PUBLIC_CODE
  #undef PWM_STOP_SEC_PUBLIC_CODE
    #define STOP_SEC_CODE
#endif
#ifdef PWM_STOP_SEC_PRIVATE_CODE
  #undef PWM_STOP_SEC_PRIVATE_CODE
    #define STOP_SEC_CODE
#endif
#ifdef PWM_STOP_SEC_APPL_CODE
  #undef PWM_STOP_SEC_APPL_CODE
    #define STOP_SEC_CODE
#endif
/**************************************** Start VAR sections **********************************************************/
#ifdef PWM_START_SEC_VAR_1BIT
  #undef PWM_START_SEC_VAR_1BIT
    #define START_SEC_VAR_INIT_UNSPECIFIED
#endif
#ifdef PWM_START_SEC_VAR_NOINIT_1BIT
  #undef PWM_START_SEC_VAR_NOINIT_1BIT
    #define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#ifdef PWM_START_SEC_VAR_FAST_1BIT
  #undef PWM_START_SEC_VAR_FAST_1BIT
    #define START_SEC_VAR_FAST_INIT_UNSPECIFIED
#endif
#ifdef  PWM_START_SEC_VAR_8BIT
  #undef PWM_START_SEC_VAR_8BIT
    #define START_SEC_VAR_INIT_8BIT
#endif
#ifdef PWM_START_SEC_VAR_NOINIT_8BIT
  #undef PWM_START_SEC_VAR_NOINIT_8BIT
    #define START_SEC_VAR_NOINIT_8BIT
#endif
#ifdef PWM_START_SEC_VAR_FAST_8BIT
  #undef  PWM_START_SEC_VAR_FAST_8BIT
    #define START_SEC_VAR_FAST_INIT_8BIT
#endif
#ifdef PWM_START_SEC_VAR_16BIT
  #undef  PWM_START_SEC_VAR_16BIT
    #define START_SEC_VAR_INIT_16BIT
#endif
#ifdef PWM_START_SEC_VAR_NOINIT_16BIT
  #undef  PWM_START_SEC_VAR_NOINIT_16BIT
    #define START_SEC_VAR_NOINIT_16BIT
#endif
#ifdef PWM_START_SEC_VAR_FAST_16BIT
  #undef  PWM_START_SEC_VAR_FAST_16BIT
    #define START_SEC_VAR_FAST_INIT_16BIT
#endif
#ifdef PWM_START_SEC_VAR_NOINIT_32BIT
  #undef  PWM_START_SEC_VAR_NOINIT_32BIT
    #define START_SEC_VAR_NOINIT_32BIT
#endif
#ifdef PWM_START_SEC_VAR_32BIT
  #undef  PWM_START_SEC_VAR_32BIT
    #define START_SEC_VAR_INIT_32BIT
#endif
#ifdef PWM_START_SEC_VAR_FAST_32BIT
  #undef  PWM_START_SEC_VAR_FAST_32BIT
    #define START_SEC_VAR_FAST_INIT_32BIT
#endif
#ifdef PWM_START_SEC_VAR_UNSPECIFIED
  #undef  PWM_START_SEC_VAR_UNSPECIFIED
    #define START_SEC_VAR_INIT_UNSPECIFIED
#endif
#ifdef PWM_START_SEC_VAR_NOINIT_UNSPECIFIED
  #undef  PWM_START_SEC_VAR_NOINIT_UNSPECIFIED
    #define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#ifdef PWM_START_SEC_VAR_FAST_UNSPECIFIED
  #undef  PWM_START_SEC_VAR_FAST_UNSPECIFIED
    #define START_SEC_VAR_FAST_INIT_UNSPECIFIED
#endif
#ifdef PWM_START_SEC_CONFIG_VAR_NOINIT_UNSPECIFIED
  #undef  PWM_START_SEC_CONFIG_VAR_NOINIT_UNSPECIFIED
    #define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
/**************************************** Stop VAR sections ***********************************************************/
#ifdef PWM_STOP_SEC_VAR_1BIT
  #undef PWM_STOP_SEC_VAR_1BIT
    #define STOP_SEC_VAR
#endif
#ifdef PWM_STOP_SEC_VAR_NOINIT_1BIT
  #undef PWM_STOP_SEC_VAR_NOINIT_1BIT
    #define STOP_SEC_VAR
#endif
#ifdef PWM_STOP_SEC_VAR_FAST_1BIT
  #undef PWM_STOP_SEC_VAR_FAST_1BIT
    #define STOP_SEC_VAR
#endif
#ifdef  PWM_STOP_SEC_VAR_8BIT
  #undef PWM_STOP_SEC_VAR_8BIT
    #define STOP_SEC_VAR
#endif
#ifdef PWM_STOP_SEC_VAR_NOINIT_8BIT
  #undef PWM_STOP_SEC_VAR_NOINIT_8BIT
    #define STOP_SEC_VAR
#endif
#ifdef PWM_STOP_SEC_VAR_FAST_8BIT
  #undef PWM_STOP_SEC_VAR_FAST_8BIT
    #define STOP_SEC_VAR
#endif

#ifdef PWM_STOP_SEC_VAR_16BIT
  #undef PWM_STOP_SEC_VAR_16BIT
    #define STOP_SEC_VAR
#endif
#ifdef PWM_STOP_SEC_VAR_NOINIT_16BIT
  #undef PWM_STOP_SEC_VAR_NOINIT_16BIT
    #define STOP_SEC_VAR
#endif
#ifdef  PWM_STOP_SEC_VAR_FAST_16BIT
  #undef PWM_STOP_SEC_VAR_FAST_16BIT
    #define STOP_SEC_VAR
#endif
#ifdef PWM_STOP_SEC_VAR_32BIT
  #undef PWM_STOP_SEC_VAR_32BIT
    #define STOP_SEC_VAR
#endif
#ifdef  PWM_STOP_SEC_VAR_NOINIT_32BIT
  #undef  PWM_STOP_SEC_VAR_NOINIT_32BIT
    #define STOP_SEC_VAR
#endif
#ifdef PWM_STOP_SEC_VAR_FAST_32BIT
  #undef PWM_STOP_SEC_VAR_FAST_32BIT
    #define STOP_SEC_VAR
#endif
#ifdef PWM_STOP_SEC_VAR_UNSPECIFIED
  #undef PWM_STOP_SEC_VAR_UNSPECIFIED
    #define STOP_SEC_VAR
#endif
#ifdef PWM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
  #undef PWM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
    #define STOP_SEC_VAR
#endif
#ifdef PWM_STOP_SEC_VAR_FAST_UNSPECIFIED
  #undef PWM_STOP_SEC_VAR_FAST_UNSPECIFIED
    #define STOP_SEC_VAR
#endif
#ifdef PWM_STOP_SEC_CONFIG_VAR_NOINIT_UNSPECIFIED
  #undef PWM_STOP_SEC_CONFIG_VAR_NOINIT_UNSPECIFIED
    #define STOP_SEC_VAR
#endif
/**************************************** Start CONST sections ********************************************************/
#ifdef  PWM_START_SEC_CONST_1BIT
  #undef PWM_START_SEC_CONST_1BIT
    #define START_SEC_CONST_UNSPECIFIED
#endif
#ifdef PWM_START_SEC_CONST_8BIT
  #undef PWM_START_SEC_CONST_8BIT
    #define START_SEC_CONST_8BIT
#endif
#ifdef PWM_START_SEC_CONST_16BIT
  #undef PWM_START_SEC_CONST_16BIT
    #define START_SEC_CONST_16BIT
#endif
#ifdef  PWM_START_SEC_CONST_32BIT
  #undef PWM_START_SEC_CONST_32BIT
    #define START_SEC_CONST_32BIT
#endif
#ifdef PWM_START_SEC_CONST_UNSPECIFIED
  #undef PWM_START_SEC_CONST_UNSPECIFIED
    #define START_SEC_CONST_UNSPECIFIED
#endif
/**************************************** Stop CONST sections **********************************************************/
#ifdef PWM_STOP_SEC_CONST_1BIT
  #undef PWM_STOP_SEC_CONST_1BIT
    #define STOP_SEC_CONST
#endif
#ifdef  PWM_STOP_SEC_CONST_8BIT
  #undef PWM_STOP_SEC_CONST_8BIT
    #define STOP_SEC_CONST
#endif
#ifdef PWM_STOP_SEC_CONST_16BIT
  #undef PWM_STOP_SEC_CONST_16BIT
    #define STOP_SEC_CONST
#endif
#ifdef PWM_STOP_SEC_CONST_32BIT
  #undef PWM_STOP_SEC_CONST_32BIT
    #define STOP_SEC_CONST
#endif
#ifdef PWM_STOP_SEC_CONST_UNSPECIFIED
  #undef PWM_STOP_SEC_CONST_UNSPECIFIED
    #define STOP_SEC_CONST
#endif
/**************************************** START CONFIG sections *******************************************************/
#ifdef PWM_START_SEC_CONFIG_DATA_UNSPECIFIED
  #undef  PWM_START_SEC_CONFIG_DATA_UNSPECIFIED
    #define START_SEC_CONST_PBCFG
#endif
#ifdef  PWM_START_SEC_DBTOC_DATA_UNSPECIFIED
  #undef PWM_START_SEC_DBTOC_DATA_UNSPECIFIED
    #define START_SEC_CONST_PBCFG
#endif
/**************************************** START CONFIG sections *******************************************************/
#ifdef PWM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
  #undef PWM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
    #define STOP_SEC_CONST
#endif
#ifdef  PWM_STOP_SEC_DBTOC_DATA_UNSPECIFIED
  #undef PWM_STOP_SEC_DBTOC_DATA_UNSPECIFIED
    #define STOP_SEC_CONST
#endif

/*******************************************************************************************************************************
 *  PWM STOP
 ******************************************************************************************************************************/


/*******************************************************************************************************************************
 *  SPI START
 ******************************************************************************************************************************/

/**************************************** Start CODE sections *****************************************************************/
#ifdef SPI_START_SEC_CODE_FAST
  #undef SPI_START_SEC_CODE_FAST
    #define START_SEC_CODE
#endif
#ifdef SPI_START_SEC_PUBLIC_CODE
  #undef SPI_START_SEC_PUBLIC_CODE
    #define START_SEC_CODE
#endif
#ifdef SPI_START_SEC_PRIVATE_CODE
  #undef SPI_START_SEC_PRIVATE_CODE
    #define START_SEC_CODE
#endif

#ifdef SPI_START_SEC_APPL_CODE
  #undef SPI_START_SEC_APPL_CODE
    #define START_SEC_CODE
#endif
/**************************************** Stop CODE sections *****************************************************************/
#ifdef SPI_STOP_SEC_CODE_FAST
  #undef SPI_STOP_SEC_CODE_FAST
    #define STOP_SEC_CODE
#endif
#ifdef SPI_STOP_SEC_PUBLIC_CODE
  #undef SPI_STOP_SEC_PUBLIC_CODE
    #define STOP_SEC_CODE
#endif
#ifdef SPI_STOP_SEC_PRIVATE_CODE
  #undef SPI_STOP_SEC_PRIVATE_CODE
    #define STOP_SEC_CODE
#endif
#ifdef SPI_STOP_SEC_APPL_CODE
  #undef SPI_STOP_SEC_APPL_CODE
    #define STOP_SEC_CODE
#endif
/**************************************** Start VAR sections *****************************************************************/
#ifdef SPI_START_SEC_VAR_1BIT
  #undef SPI_START_SEC_VAR_1BIT
    #define START_SEC_VAR_INIT_UNSPECIFIED
#endif
#ifdef SPI_START_SEC_VAR_NOINIT_1BIT
  #undef SPI_START_SEC_VAR_NOINIT_1BIT
    #define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#ifdef SPI_START_SEC_VAR_FAST_1BIT
  #undef SPI_START_SEC_VAR_FAST_1BIT
    #define START_SEC_VAR_FAST_INIT_UNSPECIFIED
#endif
#ifdef  SPI_START_SEC_VAR_8BIT
  #undef SPI_START_SEC_VAR_8BIT
    #define START_SEC_VAR_INIT_8BIT
#endif
#ifdef SPI_START_SEC_VAR_NOINIT_8BIT
  #undef SPI_START_SEC_VAR_NOINIT_8BIT
    #define START_SEC_VAR_NOINIT_8BIT
#endif
#ifdef SPI_START_SEC_VAR_FAST_8BIT
  #undef  SPI_START_SEC_VAR_FAST_8BIT
    #define START_SEC_VAR_FAST_INIT_8BIT
#endif
#ifdef SPI_START_SEC_VAR_16BIT
  #undef  SPI_START_SEC_VAR_16BIT
    #define START_SEC_VAR_INIT_16BIT
#endif
#ifdef SPI_START_SEC_VAR_NOINIT_16BIT
  #undef  SPI_START_SEC_VAR_NOINIT_16BIT
    #define START_SEC_VAR_NOINIT_16BIT
#endif
#ifdef SPI_START_SEC_VAR_FAST_16BIT
  #undef  SPI_START_SEC_VAR_FAST_16BIT
    #define START_SEC_VAR_FAST_INIT_16BIT
#endif
#ifdef SPI_START_SEC_VAR_NOINIT_32BIT
  #undef  SPI_START_SEC_VAR_NOINIT_32BIT
    #define START_SEC_VAR_NOINIT_32BIT
#endif
#ifdef SPI_START_SEC_VAR_32BIT
  #undef  SPI_START_SEC_VAR_32BIT
    #define START_SEC_VAR_INIT_32BIT
#endif
#ifdef SPI_START_SEC_VAR_FAST_32BIT
  #undef  SPI_START_SEC_VAR_FAST_32BIT
    #define START_SEC_VAR_FAST_INIT_32BIT
#endif
#ifdef SPI_START_SEC_VAR_UNSPECIFIED
  #undef  SPI_START_SEC_VAR_UNSPECIFIED
    #define START_SEC_VAR_INIT_UNSPECIFIED
#endif
#ifdef SPI_START_SEC_VAR_NOINIT_UNSPECIFIED
  #undef  SPI_START_SEC_VAR_NOINIT_UNSPECIFIED
    #define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#ifdef SPI_START_SEC_VAR_FAST_UNSPECIFIED
  #undef  SPI_START_SEC_VAR_FAST_UNSPECIFIED
    #define START_SEC_VAR_FAST_INIT_UNSPECIFIED
#endif
#ifdef SPI_START_SEC_CONFIG_VAR_NOINIT_UNSPECIFIED
  #undef  SPI_START_SEC_CONFIG_VAR_NOINIT_UNSPECIFIED
    #define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
/**************************************** Stop VAR sections *****************************************************************/
#ifdef SPI_STOP_SEC_VAR_1BIT
  #undef SPI_STOP_SEC_VAR_1BIT
    #define STOP_SEC_VAR
#endif
#ifdef SPI_STOP_SEC_VAR_NOINIT_1BIT
  #undef SPI_STOP_SEC_VAR_NOINIT_1BIT
    #define STOP_SEC_VAR
#endif
#ifdef SPI_STOP_SEC_VAR_FAST_1BIT
  #undef SPI_STOP_SEC_VAR_FAST_1BIT
    #define STOP_SEC_VAR
#endif
#ifdef  SPI_STOP_SEC_VAR_8BIT
  #undef SPI_STOP_SEC_VAR_8BIT
    #define STOP_SEC_VAR
#endif
#ifdef SPI_STOP_SEC_VAR_NOINIT_8BIT
  #undef SPI_STOP_SEC_VAR_NOINIT_8BIT
    #define STOP_SEC_VAR
#endif
#ifdef SPI_STOP_SEC_VAR_FAST_8BIT
  #undef SPI_STOP_SEC_VAR_FAST_8BIT
    #define STOP_SEC_VAR
#endif

#ifdef SPI_STOP_SEC_VAR_16BIT
  #undef SPI_STOP_SEC_VAR_16BIT
    #define STOP_SEC_VAR
#endif
#ifdef SPI_STOP_SEC_VAR_NOINIT_16BIT
  #undef SPI_STOP_SEC_VAR_NOINIT_16BIT
    #define STOP_SEC_VAR
#endif
#ifdef  SPI_STOP_SEC_VAR_FAST_16BIT
  #undef SPI_STOP_SEC_VAR_FAST_16BIT
    #define STOP_SEC_VAR
#endif
#ifdef SPI_STOP_SEC_VAR_32BIT
  #undef SPI_STOP_SEC_VAR_32BIT
    #define STOP_SEC_VAR
#endif
#ifdef  SPI_STOP_SEC_VAR_NOINIT_32BIT
  #undef  SPI_STOP_SEC_VAR_NOINIT_32BIT
    #define STOP_SEC_VAR
#endif
#ifdef SPI_STOP_SEC_VAR_FAST_32BIT
  #undef SPI_STOP_SEC_VAR_FAST_32BIT
    #define STOP_SEC_VAR
#endif
#ifdef SPI_STOP_SEC_VAR_UNSPECIFIED
  #undef SPI_STOP_SEC_VAR_UNSPECIFIED
    #define STOP_SEC_VAR
#endif
#ifdef SPI_STOP_SEC_VAR_NOINIT_UNSPECIFIED
  #undef SPI_STOP_SEC_VAR_NOINIT_UNSPECIFIED
    #define STOP_SEC_VAR
#endif
#ifdef SPI_STOP_SEC_VAR_FAST_UNSPECIFIED
  #undef SPI_STOP_SEC_VAR_FAST_UNSPECIFIED
    #define STOP_SEC_VAR
#endif
#ifdef SPI_STOP_SEC_CONFIG_VAR_NOINIT_UNSPECIFIED
  #undef SPI_STOP_SEC_CONFIG_VAR_NOINIT_UNSPECIFIED
    #define STOP_SEC_VAR
#endif
/**************************************** Start CONST sections *****************************************************************/
#ifdef  SPI_START_SEC_CONST_1BIT
  #undef SPI_START_SEC_CONST_1BIT
    #define START_SEC_CONST_UNSPECIFIED
#endif
#ifdef SPI_START_SEC_CONST_8BIT
  #undef SPI_START_SEC_CONST_8BIT
    #define START_SEC_CONST_8BIT
#endif
#ifdef SPI_START_SEC_CONST_16BIT
  #undef SPI_START_SEC_CONST_16BIT
    #define START_SEC_CONST_16BIT
#endif
#ifdef  SPI_START_SEC_CONST_32BIT
  #undef SPI_START_SEC_CONST_32BIT
    #define START_SEC_CONST_32BIT
#endif
#ifdef SPI_START_SEC_CONST_UNSPECIFIED
  #undef SPI_START_SEC_CONST_UNSPECIFIED
    #define START_SEC_CONST_UNSPECIFIED
#endif
/**************************************** Stop CONST sections *****************************************************************/
#ifdef SPI_STOP_SEC_CONST_1BIT
  #undef SPI_STOP_SEC_CONST_1BIT
    #define STOP_SEC_CONST
#endif
#ifdef  SPI_STOP_SEC_CONST_8BIT
  #undef SPI_STOP_SEC_CONST_8BIT
    #define STOP_SEC_CONST
#endif
#ifdef SPI_STOP_SEC_CONST_16BIT
  #undef SPI_STOP_SEC_CONST_16BIT
    #define STOP_SEC_CONST
#endif
#ifdef SPI_STOP_SEC_CONST_32BIT
  #undef SPI_STOP_SEC_CONST_32BIT
    #define STOP_SEC_CONST
#endif
#ifdef SPI_STOP_SEC_CONST_UNSPECIFIED
  #undef SPI_STOP_SEC_CONST_UNSPECIFIED
    #define STOP_SEC_CONST
#endif
/**************************************** START CONFIG sections *****************************************************************/
#ifdef SPI_START_SEC_CONFIG_DATA_UNSPECIFIED
  #undef  SPI_START_SEC_CONFIG_DATA_UNSPECIFIED
    #define START_SEC_CONST_PBCFG
#endif
#ifdef  SPI_START_SEC_DBTOC_DATA_UNSPECIFIED
  #undef SPI_START_SEC_DBTOC_DATA_UNSPECIFIED
    #define START_SEC_CONST_PBCFG
#endif
/**************************************** START CONFIG sections *****************************************************************/
#ifdef SPI_STOP_SEC_CONFIG_DATA_UNSPECIFIED
  #undef SPI_STOP_SEC_CONFIG_DATA_UNSPECIFIED
    #define STOP_SEC_CONST
#endif
#ifdef  SPI_STOP_SEC_DBTOC_DATA_UNSPECIFIED
  #undef SPI_STOP_SEC_DBTOC_DATA_UNSPECIFIED
    #define STOP_SEC_CONST
#endif

/*******************************************************************************************************************************
 *  SPI STOP
 ******************************************************************************************************************************/

#if defined (CANTRCV_30_TJA1043_START_SEC_CONST_32BIT) /* PRQA S 0883 */ /* Appears only while testing */
#  undef CANTRCV_30_TJA1043_START_SEC_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#  define START_SEC_CONST_32BIT             /* mapped to default 32-bit const section */
#endif

#if defined (CANTRCV_30_TJA1043_START_SEC_CONST_UNSPECIFIED)
#  undef CANTRCV_30_TJA1043_START_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#  define START_SEC_CONST_UNSPECIFIED      /* unspecified section */
#endif

#if defined (CANTRCV_30_TJA1043_START_SEC_PBCFG_ROOT) 
#  undef CANTRCV_30_TJA1043_START_SEC_PBCFG_ROOT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#  define START_SEC_CONST_PBCFG     /* pb section */

#endif

#if defined (CANTRCV_30_TJA1043_START_SEC_PBCFG)
#  undef CANTRCV_30_TJA1043_START_SEC_PBCFG /* PRQA S 0841 */ /* MD_MSR_19.6 */
#  define START_SEC_CONST_PBCFG      /* pb section */

#endif

#if defined (CANTRCV_30_TJA1043_START_SEC_VAR_NOINIT_8BIT)
#  undef CANTRCV_30_TJA1043_START_SEC_VAR_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#  define START_SEC_VAR_NOINIT_8BIT        /* mapped to default 8-bit uninit var section */
#endif


#if defined (CANTRCV_30_TJA1043_START_SEC_VAR_NOINIT_UNSPECIFIED)
#  undef CANTRCV_30_TJA1043_START_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#  define START_SEC_VAR_NOINIT_UNSPECIFIED                /* mapped to default var section */
#endif


#if defined (CANTRCV_30_TJA1043_START_SEC_CODE)
#  undef CANTRCV_30_TJA1043_START_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#  define START_SEC_CODE                   /* mapped to default code section */
#endif

#if defined (CANTRCV_30_TJA1043_STOP_SEC_CONST_32BIT)
#  undef CANTRCV_30_TJA1043_STOP_SEC_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#  define STOP_SEC_CONST                  /* mapped to default const stop section */
#endif


#if defined (CANTRCV_30_TJA1043_STOP_SEC_CONST_UNSPECIFIED)
#  undef CANTRCV_30_TJA1043_STOP_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#  define STOP_SEC_CONST                  /* mapped to default const stop section */
#endif

#if defined (CANTRCV_30_TJA1043_STOP_SEC_VAR_NOINIT_8BIT)
#  undef CANTRCV_30_TJA1043_STOP_SEC_VAR_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#  define STOP_SEC_VAR                    /* mapped to default uninit var stop section */
#endif

#if defined (CANTRCV_30_TJA1043_STOP_SEC_VAR_NOINIT_UNSPECIFIED)
#  undef CANTRCV_30_TJA1043_STOP_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#  define STOP_SEC_VAR                   /* mapped to default code section */
#endif

#if defined (CANTRCV_30_TJA1043_STOP_SEC_CODE)
#  undef CANTRCV_30_TJA1043_STOP_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#  define STOP_SEC_CODE                    /* mapped to default code stop section */
#endif

#if defined (CANTRCV_30_TJA1043_STOP_SEC_PBCFG_ROOT)
#  undef CANTRCV_30_TJA1043_STOP_SEC_PBCFG_ROOT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#  define STOP_SEC_CONST                  /* mapped to default const stop section */
#endif


#if defined (CANTRCV_30_TJA1043_STOP_SEC_PBCFG)
#  undef CANTRCV_30_TJA1043_STOP_SEC_PBCFG /* PRQA S 0841 */ /* MD_MSR_19.6 */
#  define STOP_SEC_CONST                  /* mapped to default const stop section */
#endif


/***********************************************************************************************************************
 *  WDG Sections
 **********************************************************************************************************************/

/**************************************** Start CODE sections *********************************************************/
#ifdef WDG_59_DRIVERA_START_SEC_CODE_FAST
  #undef WDG_59_DRIVERA_START_SEC_CODE_FAST
    #define START_SEC_CODE
#endif
#ifdef WDG_59_DRIVERA_START_SEC_PUBLIC_CODE
  #undef WDG_59_DRIVERA_START_SEC_PUBLIC_CODE
    #define START_SEC_CODE
#endif
#ifdef WDG_59_DRIVERA_START_SEC_PRIVATE_CODE
  #undef WDG_59_DRIVERA_START_SEC_PRIVATE_CODE
    #define START_SEC_CODE
#endif

#ifdef WDG_59_DRIVERA_START_SEC_APPL_CODE
  #undef WDG_59_DRIVERA_START_SEC_APPL_CODE
    #define START_SEC_CODE
#endif
/**************************************** Stop CODE sections **********************************************************/
#ifdef WDG_59_DRIVERA_STOP_SEC_CODE_FAST
  #undef WDG_59_DRIVERA_STOP_SEC_CODE_FAST
    #define STOP_SEC_CODE
#endif
#ifdef WDG_59_DRIVERA_STOP_SEC_PUBLIC_CODE
  #undef WDG_59_DRIVERA_STOP_SEC_PUBLIC_CODE
    #define STOP_SEC_CODE
#endif
#ifdef WDG_59_DRIVERA_STOP_SEC_PRIVATE_CODE
  #undef WDG_59_DRIVERA_STOP_SEC_PRIVATE_CODE
    #define STOP_SEC_CODE
#endif
#ifdef WDG_59_DRIVERA_STOP_SEC_APPL_CODE
  #undef WDG_59_DRIVERA_STOP_SEC_APPL_CODE
    #define STOP_SEC_CODE
#endif
/**************************************** Start VAR sections **********************************************************/
#ifdef WDG_59_DRIVERA_START_SEC_VAR_1BIT
  #undef WDG_59_DRIVERA_START_SEC_VAR_1BIT
    #define START_SEC_VAR_INIT_UNSPECIFIED
#endif
#ifdef WDG_59_DRIVERA_START_SEC_VAR_NOINIT_1BIT
  #undef WDG_59_DRIVERA_START_SEC_VAR_NOINIT_1BIT
    #define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#ifdef WDG_59_DRIVERA_START_SEC_VAR_FAST_1BIT
  #undef WDG_59_DRIVERA_START_SEC_VAR_FAST_1BIT
    #define START_SEC_VAR_FAST_INIT_UNSPECIFIED
#endif
#ifdef  WDG_59_DRIVERA_START_SEC_VAR_8BIT
  #undef WDG_59_DRIVERA_START_SEC_VAR_8BIT
    #define START_SEC_VAR_INIT_8BIT
#endif
#ifdef WDG_59_DRIVERA_START_SEC_VAR_NOINIT_8BIT
  #undef WDG_59_DRIVERA_START_SEC_VAR_NOINIT_8BIT
    #define START_SEC_VAR_NOINIT_8BIT
#endif
#ifdef WDG_59_DRIVERA_START_SEC_VAR_FAST_8BIT
  #undef  WDG_59_DRIVERA_START_SEC_VAR_FAST_8BIT
    #define START_SEC_VAR_FAST_INIT_8BIT
#endif
#ifdef WDG_59_DRIVERA_START_SEC_VAR_16BIT
  #undef  WDG_59_DRIVERA_START_SEC_VAR_16BIT
    #define START_SEC_VAR_INIT_16BIT
#endif
#ifdef WDG_59_DRIVERA_START_SEC_VAR_NOINIT_16BIT
  #undef  WDG_59_DRIVERA_START_SEC_VAR_NOINIT_16BIT
    #define START_SEC_VAR_NOINIT_16BIT
#endif
#ifdef WDG_59_DRIVERA_START_SEC_VAR_FAST_16BIT
  #undef  WDG_59_DRIVERA_START_SEC_VAR_FAST_16BIT
    #define START_SEC_VAR_FAST_INIT_16BIT
#endif
#ifdef WDG_59_DRIVERA_START_SEC_VAR_NOINIT_32BIT
  #undef  WDG_59_DRIVERA_START_SEC_VAR_NOINIT_32BIT
    #define START_SEC_VAR_NOINIT_32BIT
#endif
#ifdef WDG_59_DRIVERA_START_SEC_VAR_32BIT
  #undef  WDG_59_DRIVERA_START_SEC_VAR_32BIT
    #define START_SEC_VAR_INIT_32BIT
#endif
#ifdef WDG_59_DRIVERA_START_SEC_VAR_FAST_32BIT
  #undef  WDG_59_DRIVERA_START_SEC_VAR_FAST_32BIT
    #define START_SEC_VAR_FAST_INIT_32BIT
#endif
#ifdef WDG_59_DRIVERA_START_SEC_VAR_UNSPECIFIED
  #undef  WDG_59_DRIVERA_START_SEC_VAR_UNSPECIFIED
    #define START_SEC_VAR_INIT_UNSPECIFIED
#endif
#ifdef WDG_59_DRIVERA_START_SEC_VAR_NOINIT_UNSPECIFIED
  #undef  WDG_59_DRIVERA_START_SEC_VAR_NOINIT_UNSPECIFIED
    #define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#ifdef WDG_59_DRIVERA_START_SEC_VAR_FAST_UNSPECIFIED
  #undef  WDG_59_DRIVERA_START_SEC_VAR_FAST_UNSPECIFIED
    #define START_SEC_VAR_FAST_INIT_UNSPECIFIED
#endif
#ifdef WDG_59_DRIVERA_START_SEC_CONFIG_VAR_NOINIT_UNSPECIFIED
  #undef  WDG_59_DRIVERA_START_SEC_CONFIG_VAR_NOINIT_UNSPECIFIED
    #define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
/**************************************** Stop VAR sections ***********************************************************/
#ifdef WDG_59_DRIVERA_STOP_SEC_VAR_1BIT
  #undef WDG_59_DRIVERA_STOP_SEC_VAR_1BIT
    #define STOP_SEC_VAR
#endif
#ifdef WDG_59_DRIVERA_STOP_SEC_VAR_NOINIT_1BIT
  #undef WDG_59_DRIVERA_STOP_SEC_VAR_NOINIT_1BIT
    #define STOP_SEC_VAR
#endif
#ifdef WDG_59_DRIVERA_STOP_SEC_VAR_FAST_1BIT
  #undef WDG_59_DRIVERA_STOP_SEC_VAR_FAST_1BIT
    #define STOP_SEC_VAR
#endif
#ifdef  WDG_59_DRIVERA_STOP_SEC_VAR_8BIT
  #undef WDG_59_DRIVERA_STOP_SEC_VAR_8BIT
    #define STOP_SEC_VAR
#endif
#ifdef WDG_59_DRIVERA_STOP_SEC_VAR_NOINIT_8BIT
  #undef WDG_59_DRIVERA_STOP_SEC_VAR_NOINIT_8BIT
    #define STOP_SEC_VAR
#endif
#ifdef WDG_59_DRIVERA_STOP_SEC_VAR_FAST_8BIT
  #undef WDG_59_DRIVERA_STOP_SEC_VAR_FAST_8BIT
    #define STOP_SEC_VAR
#endif

#ifdef WDG_59_DRIVERA_STOP_SEC_VAR_16BIT
  #undef WDG_59_DRIVERA_STOP_SEC_VAR_16BIT
    #define STOP_SEC_VAR
#endif
#ifdef WDG_59_DRIVERA_STOP_SEC_VAR_NOINIT_16BIT
  #undef WDG_59_DRIVERA_STOP_SEC_VAR_NOINIT_16BIT
    #define STOP_SEC_VAR
#endif
#ifdef  WDG_59_DRIVERA_STOP_SEC_VAR_FAST_16BIT
  #undef WDG_59_DRIVERA_STOP_SEC_VAR_FAST_16BIT
    #define STOP_SEC_VAR
#endif
#ifdef WDG_59_DRIVERA_STOP_SEC_VAR_32BIT
  #undef WDG_59_DRIVERA_STOP_SEC_VAR_32BIT
    #define STOP_SEC_VAR
#endif
#ifdef  WDG_59_DRIVERA_STOP_SEC_VAR_NOINIT_32BIT
  #undef  WDG_59_DRIVERA_STOP_SEC_VAR_NOINIT_32BIT
    #define STOP_SEC_VAR
#endif
#ifdef WDG_59_DRIVERA_STOP_SEC_VAR_FAST_32BIT
  #undef WDG_59_DRIVERA_STOP_SEC_VAR_FAST_32BIT
    #define STOP_SEC_VAR
#endif
#ifdef WDG_59_DRIVERA_STOP_SEC_VAR_UNSPECIFIED
  #undef WDG_59_DRIVERA_STOP_SEC_VAR_UNSPECIFIED
    #define STOP_SEC_VAR
#endif
#ifdef WDG_59_DRIVERA_STOP_SEC_VAR_NOINIT_UNSPECIFIED
  #undef WDG_59_DRIVERA_STOP_SEC_VAR_NOINIT_UNSPECIFIED
    #define STOP_SEC_VAR
#endif
#ifdef WDG_59_DRIVERA_STOP_SEC_VAR_FAST_UNSPECIFIED
  #undef WDG_59_DRIVERA_STOP_SEC_VAR_FAST_UNSPECIFIED
    #define STOP_SEC_VAR
#endif
#ifdef WDG_59_DRIVERA_STOP_SEC_CONFIG_VAR_NOINIT_UNSPECIFIED
  #undef WDG_59_DRIVERA_STOP_SEC_CONFIG_VAR_NOINIT_UNSPECIFIED
    #define STOP_SEC_VAR
#endif
/**************************************** Start CONST sections ********************************************************/
#ifdef  WDG_59_DRIVERA_START_SEC_CONST_1BIT
  #undef WDG_59_DRIVERA_START_SEC_CONST_1BIT
    #define START_SEC_CONST_UNSPECIFIED
#endif
#ifdef WDG_59_DRIVERA_START_SEC_CONST_8BIT
  #undef WDG_59_DRIVERA_START_SEC_CONST_8BIT
    #define START_SEC_CONST_8BIT
#endif
#ifdef WDG_59_DRIVERA_START_SEC_CONST_16BIT
  #undef WDG_59_DRIVERA_START_SEC_CONST_16BIT
    #define START_SEC_CONST_16BIT
#endif
#ifdef  WDG_59_DRIVERA_START_SEC_CONST_32BIT
  #undef WDG_59_DRIVERA_START_SEC_CONST_32BIT
    #define START_SEC_CONST_32BIT
#endif
#ifdef WDG_59_DRIVERA_START_SEC_CONST_UNSPECIFIED
  #undef WDG_59_DRIVERA_START_SEC_CONST_UNSPECIFIED
    #define START_SEC_CONST_UNSPECIFIED
#endif
/**************************************** Stop CONST sections *********************************************************/
#ifdef WDG_59_DRIVERA_STOP_SEC_CONST_1BIT
  #undef WDG_59_DRIVERA_STOP_SEC_CONST_1BIT
    #define STOP_SEC_CONST
#endif
#ifdef  WDG_59_DRIVERA_STOP_SEC_CONST_8BIT
  #undef WDG_59_DRIVERA_STOP_SEC_CONST_8BIT
    #define STOP_SEC_CONST
#endif
#ifdef WDG_59_DRIVERA_STOP_SEC_CONST_16BIT
  #undef WDG_59_DRIVERA_STOP_SEC_CONST_16BIT
    #define STOP_SEC_CONST
#endif
#ifdef WDG_59_DRIVERA_STOP_SEC_CONST_32BIT
  #undef WDG_59_DRIVERA_STOP_SEC_CONST_32BIT
    #define STOP_SEC_CONST
#endif
#ifdef WDG_59_DRIVERA_STOP_SEC_CONST_UNSPECIFIED
  #undef WDG_59_DRIVERA_STOP_SEC_CONST_UNSPECIFIED
    #define STOP_SEC_CONST
#endif
/**************************************** START CONFIG sections *******************************************************/
#ifdef WDG_59_DRIVERA_START_SEC_CONFIG_DATA_UNSPECIFIED
  #undef  WDG_59_DRIVERA_START_SEC_CONFIG_DATA_UNSPECIFIED
    #define START_SEC_CONST_PBCFG
#endif
#ifdef  WDG_59_DRIVERA_START_SEC_DBTOC_DATA_UNSPECIFIED
  #undef WDG_59_DRIVERA_START_SEC_DBTOC_DATA_UNSPECIFIED
    #define START_SEC_CONST_PBCFG
#endif
/**************************************** START CONFIG sections *******************************************************/
#ifdef WDG_59_DRIVERA_STOP_SEC_CONFIG_DATA_UNSPECIFIED
  #undef WDG_59_DRIVERA_STOP_SEC_CONFIG_DATA_UNSPECIFIED
    #define STOP_SEC_CONST
#endif
#ifdef  WDG_59_DRIVERA_STOP_SEC_DBTOC_DATA_UNSPECIFIED
  #undef WDG_59_DRIVERA_STOP_SEC_DBTOC_DATA_UNSPECIFIED
    #define STOP_SEC_CONST
#endif

/*******************************************************************************************************************************
 *  WDG STOP
 ******************************************************************************************************************************/

/**********************************************************************************************************************
 *  PDUR START 
 *********************************************************************************************************************/

/*******  CODE sections **********************************************************************************************/

#ifdef PDUR_START_SEC_CODE
# undef PDUR_START_SEC_CODE
# define START_SEC_CODE
#endif
#ifdef PDUR_STOP_SEC_CODE
# undef PDUR_STOP_SEC_CODE
# define STOP_SEC_CODE
#endif


/*******  CONST sections  ********************************************************************************************/

/* CONST sections */

#ifdef PDUR_START_SEC_CONST_8BIT
# undef PDUR_START_SEC_CONST_8BIT
# define START_SEC_CONST_8BIT
#endif
#ifdef PDUR_STOP_SEC_CONST_8BIT
# undef PDUR_STOP_SEC_CONST_8BIT
# define STOP_SEC_CONST
#endif

#ifdef PDUR_START_SEC_CONST_16BIT
# undef PDUR_START_SEC_CONST_16BIT
# define START_SEC_CONST_16BIT
#endif
#ifdef PDUR_STOP_SEC_CONST_16BIT
# undef PDUR_STOP_SEC_CONST_16BIT
# define STOP_SEC_CONST
#endif

#ifdef PDUR_START_SEC_CONST_32BIT
# undef PDUR_START_SEC_CONST_32BIT
# define START_SEC_CONST_32BIT
#endif
#ifdef PDUR_STOP_SEC_CONST_32BIT
# undef PDUR_STOP_SEC_CONST_32BIT
# define STOP_SEC_CONST
#endif

#ifdef PDUR_START_SEC_CONST_UNSPECIFIED
# undef PDUR_START_SEC_CONST_UNSPECIFIED
# define START_SEC_CONST_UNSPECIFIED
#endif
#ifdef PDUR_STOP_SEC_CONST_UNSPECIFIED
# undef PDUR_STOP_SEC_CONST_UNSPECIFIED
# define STOP_SEC_CONST
#endif


/* FAST CONST sections */



/* Postbuild CFG CONST sections */

/* Root table for postbuild data */
#ifdef PDUR_START_SEC_PBCFG
# undef PDUR_START_SEC_PBCFG
# define START_SEC_CONST_PBCFG
#endif
#ifdef PDUR_STOP_SEC_PBCFG
# undef PDUR_STOP_SEC_PBCFG
# define STOP_SEC_CONST
#endif

#ifdef PDUR_START_SEC_PBCFG_ROOT
# undef PDUR_START_SEC_PBCFG_ROOT
# define START_SEC_CONST_PBCFG
#endif
#ifdef PDUR_STOP_SEC_PBCFG_ROOT
# undef PDUR_STOP_SEC_PBCFG_ROOT
# define STOP_SEC_CONST
#endif


/*******  VAR sections  **********************************************************************************************/

/* VAR INIT sections */

#ifdef PDUR_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
# undef PDUR_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
# define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif
#ifdef PDUR_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
# undef PDUR_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
# define STOP_SEC_VAR
#endif


/* VAR NOINIT sections */

#ifdef PDUR_START_SEC_VAR_NOINIT_BOOLEAN
# undef PDUR_START_SEC_VAR_NOINIT_BOOLEAN
# define START_SEC_VAR_NOINIT_8BIT
#endif
#ifdef PDUR_STOP_SEC_VAR_NOINIT_BOOLEAN
# undef PDUR_STOP_SEC_VAR_NOINIT_BOOLEAN
# define STOP_SEC_VAR
#endif

#ifdef PDUR_START_SEC_VAR_NOINIT_8BIT
# undef PDUR_START_SEC_VAR_NOINIT_8BIT
# define START_SEC_VAR_NOINIT_8BIT
#endif
#ifdef PDUR_STOP_SEC_VAR_NOINIT_8BIT
# undef PDUR_STOP_SEC_VAR_NOINIT_8BIT
# define STOP_SEC_VAR
#endif

#ifdef PDUR_START_SEC_VAR_NOINIT_UNSPECIFIED
# undef PDUR_START_SEC_VAR_NOINIT_UNSPECIFIED
# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#ifdef PDUR_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef PDUR_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# define STOP_SEC_VAR
#endif


/* VAR ZERO INIT sections */



/* VAR FAST INIT sections */



/* VAR FAST NOINIT sections */


/* VAR FAST ZERO INIT sections */



/**********************************************************************************************************************
 *  PDUR END
 *********************************************************************************************************************/

/*-------------------------------------------------------------------------------------------------------------------*/
/* CANIF                                                                                                             */
/*-------------------------------------------------------------------------------------------------------------------*/

/* Code */

#ifdef CANIF_START_SEC_CODE
# undef CANIF_START_SEC_CODE                       /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CODE                            /* mapped to default code section */
#endif

#ifdef CANIF_STOP_SEC_CODE
# undef CANIF_STOP_SEC_CODE                        /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CODE                             /* default code stop section */
#endif


#ifdef CANIF_START_SEC_APPL_CODE
# undef CANIF_START_SEC_APPL_CODE                  /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CODE                            /* mapped to default code section */
#endif

#ifdef CANIF_STOP_SEC_APPL_CODE
# undef CANIF_STOP_SEC_APPL_CODE                   /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CODE                             /* default code stop section */
#endif




/* Const 8bit */

#ifdef CANIF_START_SEC_CONST_8BIT
# undef CANIF_START_SEC_CONST_8BIT                 /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_8BIT                      /* mapped to const 8 bit section */
#endif

#ifdef CANIF_STOP_SEC_CONST_8BIT
# undef CANIF_STOP_SEC_CONST_8BIT                  /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST                            /* default const stop section */
#endif

/* Const 32bit */

#ifdef CANIF_START_SEC_CONST_32BIT
# undef CANIF_START_SEC_CONST_32BIT                 /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_32BIT                      /* mapped to const 32 bit section */
#endif

#ifdef CANIF_STOP_SEC_CONST_32BIT
# undef CANIF_STOP_SEC_CONST_32BIT                 /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST                            /* default const stop section */
#endif


/* Const unspecified */

#ifdef CANIF_START_SEC_CONST_UNSPECIFIED
# undef CANIF_START_SEC_CONST_UNSPECIFIED          /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_UNSPECIFIED               /* mapped to const unspecified section */
#endif

#ifdef CANIF_STOP_SEC_CONST_UNSPECIFIED
# undef CANIF_STOP_SEC_CONST_UNSPECIFIED           /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST                            /* default const stop section */
#endif


/* Post build config unspecified */

#ifdef CANIF_START_SEC_PBCFG
# undef CANIF_START_SEC_PBCFG                      /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_PBCFG                     /* mapped to const unspecified section */
#endif

#ifdef CANIF_STOP_SEC_PBCFG
# undef CANIF_STOP_SEC_PBCFG                       /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST                            /* default const stop section */
#endif

#ifdef CANIF_START_SEC_PBCFG_ROOT
# undef CANIF_START_SEC_PBCFG_ROOT                 /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_PBCFG                     /* mapped to const unspecified section */
#endif

#ifdef CANIF_STOP_SEC_PBCFG_ROOT
# undef CANIF_STOP_SEC_PBCFG_ROOT                  /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST                            /* default const stop section */
#endif


/* Var noinit unspecified */

#ifdef CANIF_START_SEC_VAR_NOINIT_UNSPECIFIED
# undef CANIF_START_SEC_VAR_NOINIT_UNSPECIFIED     /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_NOINIT_UNSPECIFIED          /* mapped to uninitialized RAM unspecified section */
#endif

#ifdef CANIF_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef CANIF_STOP_SEC_VAR_NOINIT_UNSPECIFIED      /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR                              /* default RAM stop section */
#endif

/* Var zero init unspecified */
#ifdef CANIF_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
# undef CANIF_START_SEC_VAR_ZERO_INIT_UNSPECIFIED  /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_ZERO_INIT_UNSPECIFIED       /* mapped to zero initialized RAM unspecified section */
#endif

#ifdef CANIF_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
# undef CANIF_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED   /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR                              /* default RAM stop section */
#endif


/* Var init unspecified */
#ifdef CANIF_START_SEC_VAR_INIT_UNSPECIFIED
# undef CANIF_START_SEC_VAR_INIT_UNSPECIFIED       /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_INIT_UNSPECIFIED            /* mapped to initialized RAM unspecified section */
#endif

#ifdef CANIF_STOP_SEC_VAR_INIT_UNSPECIFIED
# undef CANIF_STOP_SEC_VAR_INIT_UNSPECIFIED        /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR                              /* default RAM stop section */
#endif


/*-------------------------------------------------------------------------------------------------------------------*/
/* CANIF                                                                                                             */
/*-------------------------------------------------------------------------------------------------------------------*/



/**********************************************************************************************************************
 *  FEE START 
 *********************************************************************************************************************/

/*******  CODE sections **********************************************************************************************/

#ifdef FEE_START_SEC_CODE
# undef FEE_START_SEC_CODE
# define START_SEC_CODE                                               /* mapped to default code section */
#endif
#ifdef FEE_STOP_SEC_CODE
# undef FEE_STOP_SEC_CODE
# define STOP_SEC_CODE                                                /* default code stop section */
#endif


/*******  CONST sections  ********************************************************************************************/

/* CONST sections */

#ifdef FEE_START_SEC_CONST_UNSPECIFIED
# undef FEE_START_SEC_CONST_UNSPECIFIED
# define START_SEC_CONST_UNSPECIFIED
#endif
#ifdef FEE_STOP_SEC_CONST_UNSPECIFIED
# undef FEE_STOP_SEC_CONST_UNSPECIFIED
# define STOP_SEC_CONST
#endif

#ifdef FEE_START_SEC_APPL_CONFIG_UNSPECIFIED
# undef FEE_START_SEC_APPL_CONFIG_UNSPECIFIED
# define START_SEC_CONST_UNSPECIFIED
#endif
#ifdef FEE_STOP_SEC_APPL_CONFIG_UNSPECIFIED
# undef FEE_STOP_SEC_APPL_CONFIG_UNSPECIFIED
# define STOP_SEC_CONST
#endif


/*******  VAR sections  **********************************************************************************************/

/* VAR INIT sections */

#ifdef FEE_START_SEC_VAR_NOINIT_UNSPECIFIED
# undef FEE_START_SEC_VAR_NOINIT_UNSPECIFIED
# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#ifdef FEE_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef FEE_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# define STOP_SEC_VAR
#endif

#ifdef FEE_START_SEC_VAR_INIT_UNSPECIFIED
# undef FEE_START_SEC_VAR_INIT_UNSPECIFIED
# define START_SEC_VAR_INIT_UNSPECIFIED
#endif
#ifdef FEE_STOP_SEC_VAR_INIT_UNSPECIFIED
# undef FEE_STOP_SEC_VAR_INIT_UNSPECIFIED
# define STOP_SEC_VAR
#endif
/**********************************************************************************************************************
 *  FEE END
 *********************************************************************************************************************/

#ifdef MEMIF_START_SEC_CONST_8BIT 
    #undef MEMIF_START_SEC_CONST_8BIT 
    #define START_SEC_CONST_8BIT
#endif

#ifdef MEMIF_STOP_SEC_CONST_8BIT 
    #undef MEMIF_STOP_SEC_CONST_8BIT 
    #define STOP_SEC_CONST
#endif


#ifdef MEMIF_START_SEC_CONST_32BIT
    #undef MEMIF_START_SEC_CONST_32BIT
    #define START_SEC_CONST_32BIT
#endif

#ifdef MEMIF_STOP_SEC_CONST_32BIT
    #undef MEMIF_STOP_SEC_CONST_32BIT
    #define STOP_SEC_CONST
#endif


#ifdef MEMIF_START_SEC_CODE
    #undef MEMIF_START_SEC_CODE
    #define START_SEC_CODE
#endif

#ifdef MEMIF_STOP_SEC_CODE
    #undef MEMIF_STOP_SEC_CODE
    #define STOP_SEC_CODE
#endif

#ifdef DCMFBL_START_SEC_CODE
    #undef DCMFBL_START_SEC_CODE
    #define START_SEC_CODE
#endif

#ifdef DCMFBL_START_SEC_CONST_UNSPECIFIED
    #undef DCMFBL_START_SEC_CONST_UNSPECIFIED
    #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef DCMFBL_START_SEC_CONST_8BIT
    #undef DCMFBL_START_SEC_CONST_8BIT
    #define START_SEC_CONST_8BIT
#endif

#ifdef DCMFBL_STOP_SEC_CODE
    #undef DCMFBL_STOP_SEC_CODE
    #define STOP_SEC_CODE
#endif

#ifdef DCMFBL_STOP_SEC_CONST_UNSPECIFIED
    #undef DCMFBL_STOP_SEC_CONST_UNSPECIFIED
    #define STOP_SEC_CONST
#endif

#ifdef DCMFBL_STOP_SEC_CONST_8BIT
    #undef DCMFBL_STOP_SEC_CONST_8BIT
    #define STOP_SEC_CONST
#endif

/**********************************************************************************************************************
 *  Com START 
 *********************************************************************************************************************/

/*******  CODE sections **********************************************************************************************/

#ifdef COM_START_SEC_CODE
# undef COM_START_SEC_CODE
# define START_SEC_CODE
#endif
#ifdef COM_STOP_SEC_CODE
# undef COM_STOP_SEC_CODE
# define STOP_SEC_CODE
#endif
/* COM application callback code section (Rte_Cbk.h)*/
#ifdef COM_START_SEC_APPL_CODE
# undef COM_START_SEC_APPL_CODE
# define START_SEC_CODE
#endif
#ifdef COM_STOP_SEC_APPL_CODE
# undef COM_STOP_SEC_APPL_CODE
# define STOP_SEC_CODE
#endif


/*******  CONST sections  ********************************************************************************************/

/* CONST sections */

#ifdef COM_START_SEC_CONST_32BIT
# undef COM_START_SEC_CONST_32BIT
# define START_SEC_CONST_32BIT
#endif
#ifdef COM_STOP_SEC_CONST_32BIT
# undef COM_STOP_SEC_CONST_32BIT
# define STOP_SEC_CONST
#endif

#ifdef COM_START_SEC_CONST_UNSPECIFIED
# undef COM_START_SEC_CONST_UNSPECIFIED
# define START_SEC_CONST_UNSPECIFIED
#endif
#ifdef COM_STOP_SEC_CONST_UNSPECIFIED
# undef COM_STOP_SEC_CONST_UNSPECIFIED
# define STOP_SEC_CONST
#endif


/* FAST CONST sections */



/* Postbuild CFG CONST sections */

/* Root table for postbuild data */
#ifdef COM_START_SEC_PBCFG_ROOT
# undef COM_START_SEC_PBCFG_ROOT
# define START_SEC_CONST_PBCFG
#endif
#ifdef COM_STOP_SEC_PBCFG_ROOT
# undef COM_STOP_SEC_PBCFG_ROOT
# define STOP_SEC_CONST
#endif

#ifdef COM_START_SEC_PBCFG
# undef COM_START_SEC_PBCFG
# define START_SEC_CONST_PBCFG
#endif
#ifdef COM_STOP_SEC_PBCFG
# undef COM_STOP_SEC_PBCFG
# define STOP_SEC_CONST
#endif


/*******  VAR sections  **********************************************************************************************/

/* VAR INIT sections */

#ifdef COM_START_SEC_VAR_INIT_UNSPECIFIED
# undef COM_START_SEC_VAR_INIT_UNSPECIFIED
# define START_SEC_VAR_INIT_UNSPECIFIED
#endif
#ifdef COM_STOP_SEC_VAR_INIT_UNSPECIFIED
# undef COM_STOP_SEC_VAR_INIT_UNSPECIFIED
# define STOP_SEC_VAR
#endif


/* VAR NOINIT sections */

#ifdef COM_START_SEC_VAR_NOINIT_BOOLEAN
# undef COM_START_SEC_VAR_NOINIT_BOOLEAN
# define START_SEC_VAR_NOINIT_8BIT
#endif
#ifdef COM_STOP_SEC_VAR_NOINIT_BOOLEAN
# undef COM_STOP_SEC_VAR_NOINIT_BOOLEAN
# define STOP_SEC_VAR
#endif

#ifdef COM_START_SEC_VAR_NOINIT_8BIT
# undef COM_START_SEC_VAR_NOINIT_8BIT
# define START_SEC_VAR_NOINIT_8BIT
#endif
#ifdef COM_STOP_SEC_VAR_NOINIT_8BIT
# undef COM_STOP_SEC_VAR_NOINIT_8BIT
# define STOP_SEC_VAR
#endif

#ifdef COM_START_SEC_VAR_NOINIT_16BIT
# undef COM_START_SEC_VAR_NOINIT_16BIT
# define START_SEC_VAR_NOINIT_16BIT
#endif
#ifdef COM_STOP_SEC_VAR_NOINIT_16BIT
# undef COM_STOP_SEC_VAR_NOINIT_16BIT
# define STOP_SEC_VAR
#endif

#ifdef COM_START_SEC_VAR_NOINIT_UNSPECIFIED
# undef COM_START_SEC_VAR_NOINIT_UNSPECIFIED
# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#ifdef COM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef COM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# define STOP_SEC_VAR
#endif


/* VAR ZERO INIT sections */



/* VAR FAST INIT sections */



/* VAR FAST NOINIT sections */


/* VAR FAST ZERO INIT sections */



/**********************************************************************************************************************
 *  Com END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  IpduM START 
 *********************************************************************************************************************/

/*******  CODE sections **********************************************************************************************/

#ifdef IPDUM_START_SEC_CODE
# undef IPDUM_START_SEC_CODE
# define START_SEC_CODE         /* mapped to default code section */
#endif
#ifdef IPDUM_STOP_SEC_CODE
# undef IPDUM_STOP_SEC_CODE
# define STOP_SEC_CODE          /* default code stop section */
#endif


/*******  CONST sections  ********************************************************************************************/

/* Postbuild CFG CONST sections */

#ifdef IPDUM_START_SEC_PBCFG
# undef IPDUM_START_SEC_PBCFG
# define START_SEC_CONST_PBCFG
#endif
#ifdef IPDUM_STOP_SEC_PBCFG
# undef IPDUM_STOP_SEC_PBCFG
# define STOP_SEC_CONST
#endif

/* Postbuild CFG struct sections */

#ifdef IPDUM_START_SEC_PBCFG_ROOT
# undef IPDUM_START_SEC_PBCFG_ROOT
# define START_SEC_CONST_PBCFG
#endif
#ifdef IPDUM_STOP_SEC_PBCFG_ROOT
# undef IPDUM_STOP_SEC_PBCFG_ROOT
# define STOP_SEC_CONST
#endif

/*******  VAR sections  **********************************************************************************************/

/* VAR INIT sections */

#ifdef IPDUM_START_SEC_VAR_INIT_UNSPECIFIED
# undef IPDUM_START_SEC_VAR_INIT_UNSPECIFIED
# define START_SEC_VAR_INIT_UNSPECIFIED
#endif
#ifdef IPDUM_STOP_SEC_VAR_INIT_UNSPECIFIED
# undef IPDUM_STOP_SEC_VAR_INIT_UNSPECIFIED
# define STOP_SEC_VAR
#endif


/* VAR NOINIT sections */

#ifdef IPDUM_START_SEC_VAR_NOINIT_8BIT
# undef IPDUM_START_SEC_VAR_NOINIT_8BIT
# define START_SEC_VAR_NOINIT_8BIT
#endif
#ifdef IPDUM_STOP_SEC_VAR_NOINIT_8BIT
# undef IPDUM_STOP_SEC_VAR_NOINIT_8BIT
# define STOP_SEC_VAR
#endif

#ifdef IPDUM_START_SEC_VAR_NOINIT_UNSPECIFIED
# undef IPDUM_START_SEC_VAR_NOINIT_UNSPECIFIED
# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#ifdef IPDUM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef IPDUM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
 *  IpduM END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  NvM START 
 *********************************************************************************************************************/

/*******  CODE sections **********************************************************************************************/

#ifdef NVM_START_SEC_CODE
    #undef NVM_START_SEC_CODE
    #define START_SEC_CODE                /* mapped to default code section */
#endif
#ifdef NVM_STOP_SEC_CODE
    #undef NVM_STOP_SEC_CODE
    #define STOP_SEC_CODE                /* default code stop section */
#endif


/*******  CONST sections  ********************************************************************************************/

/* CONST sections */

#ifdef NVM_START_SEC_CONST_8BIT
    #undef NVM_START_SEC_CONST_8BIT
    #define START_SEC_CONST_8BIT
#endif
#ifdef NVM_STOP_SEC_CONST_8BIT
    #undef NVM_STOP_SEC_CONST_8BIT
    #define STOP_SEC_CONST
#endif

#ifdef NVM_START_SEC_CONST_16BIT
    #undef NVM_START_SEC_CONST_16BIT
    #define START_SEC_CONST_16BIT
#endif
#ifdef NVM_STOP_SEC_CONST_16BIT
    #undef NVM_STOP_SEC_CONST_16BIT
    #define STOP_SEC_CONST
#endif

#ifdef NVM_START_SEC_CONST_UNSPECIFIED
    #undef NVM_START_SEC_CONST_UNSPECIFIED
    #define START_SEC_CONST_UNSPECIFIED
#endif
#ifdef NVM_STOP_SEC_CONST_UNSPECIFIED
    #undef NVM_STOP_SEC_CONST_UNSPECIFIED
    #define STOP_SEC_CONST
#endif

#ifdef NVM_START_SEC_CONST_DESCRIPTOR_TABLE
    #undef NVM_START_SEC_CONST_DESCRIPTOR_TABLE
    #define START_SEC_CONST_UNSPECIFIED
#endif
#ifdef NVM_STOP_SEC_CONST_DESCRIPTOR_TABLE
    #undef NVM_STOP_SEC_CONST_DESCRIPTOR_TABLE
    #define STOP_SEC_CONST
#endif


/*******  VAR sections  **********************************************************************************************/

/* VAR NOINIT sections */

#ifdef NVM_START_SEC_VAR_NOINIT_8BIT
    #undef NVM_START_SEC_VAR_NOINIT_8BIT
    #define START_SEC_VAR_NOINIT_8BIT
#endif
#ifdef NVM_STOP_SEC_VAR_NOINIT_8BIT
    #undef NVM_STOP_SEC_VAR_NOINIT_8BIT
    #define STOP_SEC_VAR
#endif

#ifdef NVM_START_SEC_VAR_NOINIT_UNSPECIFIED
    #undef NVM_START_SEC_VAR_NOINIT_UNSPECIFIED
    #define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#ifdef NVM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
    #undef NVM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
    #define STOP_SEC_VAR
#endif

#ifdef NVM_START_SEC_VAR_UNSPECIFIED
    #undef NVM_START_SEC_VAR_UNSPECIFIED
    
    /* If Development Error Detection is ON (as well as INIT check),    *
     *   it SHALL be mapped to an initialized section (zeor is ok)      *
     * if Development Error Detection (or at least INIT check) is OFF,  *
     *   it MAY also be mapped to a NOINIT section.                     */
     
    #define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif
#ifdef NVM_STOP_SEC_VAR_UNSPECIFIED
    #undef NVM_STOP_SEC_VAR_UNSPECIFIED
    #define STOP_SEC_VAR
#endif

/* VAR FAST NOINIT sections */

#ifdef NVM_START_SEC_VAR_FAST_8BIT
    #undef NVM_START_SEC_VAR_FAST_8BIT
    #define START_SEC_VAR_FAST_NOINIT_8BIT
#endif
#ifdef NVM_STOP_SEC_VAR_FAST_8BIT
    #undef NVM_STOP_SEC_VAR_FAST_8BIT
    #define STOP_SEC_VAR
#endif

/* VAR ZERO INIT sections */

#ifdef NVM_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
    #undef NVM_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED

    /* SHALL be mapped to a section that is guaranteed to be ZEROed out after Power-On Reset       *
     * (therefore it MAY be a "normal" ZERO_INIT section, being ZEROed out after ANY reset         *
     * Make shure this helds true for all kinds of variable data (esp. "uninitialized).            *
     * If necessary, create a special section (don't map to a common one)                          */    
    #define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif
#ifdef NVM_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
    #undef NVM_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
    #define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
 *  NvM END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  DLT START 
 *********************************************************************************************************************/

/*******  CODE sections **********************************************************************************************/

#ifdef DLT_START_SEC_CODE
  #undef DLT_START_SEC_CODE
  #define START_SEC_CODE                            /* mapped to default code section */
#endif
#ifdef DLT_STOP_SEC_CODE
  #undef DLT_STOP_SEC_CODE
  #define STOP_SEC_CODE                             /* default code stop section */
#endif

#ifdef DLT_START_SEC_CODE_FAST
  #undef DLT_START_SEC_CODE_FAST
  #define START_SEC_CODE_FAST                       /* mapped to default fast code section */
#endif
#ifdef DLT_STOP_SEC_CODE_FAST
  #undef DLT_STOP_SEC_CODE_FAST
  #define STOP_SEC_CODE                             /* default code stop section */
#endif

/*******  CONST sections  ********************************************************************************************/

/* CONST sections */

#ifdef DLT_START_SEC_CONST_8BIT
# undef DLT_START_SEC_CONST_8BIT
# define START_SEC_CONST_8BIT                       /* mapped to default const 8bit section */
#endif
#ifdef DLT_STOP_SEC_CONST_8BIT
# undef DLT_STOP_SEC_CONST_8BIT
# define STOP_SEC_CONST                             /* default const stop section */
#endif

#ifdef DLT_START_SEC_CONST_16BIT
# undef DLT_START_SEC_CONST_16BIT
# define START_SEC_CONST_16BIT
#endif
#ifdef DLT_STOP_SEC_CONST_16BIT
# undef DLT_STOP_SEC_CONST_16BIT
# define STOP_SEC_CONST
#endif

#ifdef DLT_START_SEC_CONST_32BIT
# undef DLT_START_SEC_CONST_32BIT
# define START_SEC_CONST_32BIT
#endif
#ifdef DLT_STOP_SEC_CONST_32BIT
# undef DLT_STOP_SEC_CONST_32BIT
# define STOP_SEC_CONST
#endif

#ifdef DLT_START_SEC_CONST_UNSPECIFIED
# undef DLT_START_SEC_CONST_UNSPECIFIED
# define START_SEC_CONST_UNSPECIFIED
#endif
#ifdef DLT_STOP_SEC_CONST_UNSPECIFIED
# undef DLT_STOP_SEC_CONST_UNSPECIFIED
# define STOP_SEC_CONST
#endif


/*******  VAR sections  **********************************************************************************************/

/* VAR INIT sections */

#ifdef DLT_START_SEC_VAR_INIT_8BIT
# undef DLT_START_SEC_VAR_INIT_8BIT
# define START_SEC_VAR_INIT_8BIT                    /* mapped to default var init 8bit section */
#endif
#ifdef DLT_STOP_SEC_VAR_INIT_8BIT
# undef DLT_STOP_SEC_VAR_INIT_8BIT
# define STOP_SEC_VAR                               /* default var stop section */
#endif

#ifdef DLT_START_SEC_VAR_INIT_16BIT
# undef DLT_START_SEC_VAR_INIT_16BIT
# define START_SEC_VAR_INIT_16BIT
#endif
#ifdef DLT_STOP_SEC_VAR_INIT_16BIT
# undef DLT_STOP_SEC_VAR_INIT_16BIT
# define STOP_SEC_VAR
#endif

#ifdef DLT_START_SEC_VAR_INIT_32BIT
# undef DLT_START_SEC_VAR_INIT_32BIT
# define START_SEC_VAR_INIT_32BIT
#endif
#ifdef DLT_STOP_SEC_VAR_INIT_32BIT
# undef DLT_STOP_SEC_VAR_INIT_32BIT
# define STOP_SEC_VAR
#endif

#ifdef DLT_START_SEC_VAR_INIT_UNSPECIFIED
# undef DLT_START_SEC_VAR_INIT_UNSPECIFIED
# define START_SEC_VAR_INIT_UNSPECIFIED
#endif
#ifdef DLT_STOP_SEC_VAR_INIT_UNSPECIFIED
# undef DLT_STOP_SEC_VAR_INIT_UNSPECIFIED
# define STOP_SEC_VAR
#endif


/* VAR NOINIT sections */

#ifdef DLT_START_SEC_VAR_NOINIT_8BIT
# undef DLT_START_SEC_VAR_NOINIT_8BIT
# define START_SEC_VAR_NOINIT_8BIT
#endif
#ifdef DLT_STOP_SEC_VAR_NOINIT_8BIT
# undef DLT_STOP_SEC_VAR_NOINIT_8BIT
# define STOP_SEC_VAR
#endif

#ifdef DLT_START_SEC_VAR_NOINIT_16BIT
# undef DLT_START_SEC_VAR_NOINIT_16BIT
# define START_SEC_VAR_NOINIT_16BIT
#endif
#ifdef DLT_STOP_SEC_VAR_NOINIT_16BIT
# undef DLT_STOP_SEC_VAR_NOINIT_16BIT
# define STOP_SEC_VAR
#endif

#ifdef DLT_START_SEC_VAR_NOINIT_32BIT
# undef DLT_START_SEC_VAR_NOINIT_32BIT
# define START_SEC_VAR_NOINIT_32BIT
#endif
#ifdef DLT_STOP_SEC_VAR_NOINIT_32BIT
# undef DLT_STOP_SEC_VAR_NOINIT_32BIT
# define STOP_SEC_VAR
#endif

#ifdef DLT_START_SEC_VAR_NOINIT_UNSPECIFIED
# undef DLT_START_SEC_VAR_NOINIT_UNSPECIFIED
# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#ifdef DLT_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef DLT_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# define STOP_SEC_VAR
#endif


/* VAR ZERO INIT sections */

#ifdef DLT_START_SEC_VAR_ZERO_INIT_8BIT
# undef DLT_START_SEC_VAR_ZERO_INIT_8BIT
# define START_SEC_VAR_ZERO_INIT_8BIT
#endif
#ifdef DLT_STOP_SEC_VAR_ZERO_INIT_8BIT
# undef DLT_STOP_SEC_VAR_ZERO_INIT_8BIT
# define STOP_SEC_VAR
#endif

#ifdef DLT_START_SEC_VAR_ZERO_INIT_16BIT
# undef DLT_START_SEC_VAR_ZERO_INIT_16BIT
# define START_SEC_VAR_ZERO_INIT_16BIT
#endif
#ifdef DLT_STOP_SEC_VAR_ZERO_INIT_16BIT
# undef DLT_STOP_SEC_VAR_ZERO_INIT_16BIT
# define STOP_SEC_VAR
#endif

#ifdef DLT_START_SEC_VAR_ZERO_INIT_32BIT
# undef DLT_START_SEC_VAR_ZERO_INIT_32BIT
# define START_SEC_VAR_ZERO_INIT_32BIT
#endif
#ifdef DLT_STOP_SEC_VAR_ZERO_INIT_32BIT
# undef DLT_STOP_SEC_VAR_ZERO_INIT_32BIT
# define STOP_SEC_VAR
#endif

#ifdef DLT_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
# undef DLT_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
# define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif
#ifdef DLT_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
# undef DLT_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
# define STOP_SEC_VAR
#endif



/**********************************************************************************************************************
 *  DLT END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  AMDRTM START 
 *********************************************************************************************************************/


/*******  CODE sections **********************************************************************************************/

#ifdef AMDRTM_START_SEC_CODE
  #undef AMDRTM_START_SEC_CODE
  #define START_SEC_CODE                            /* mapped to default code section */
#endif
#ifdef AMDRTM_STOP_SEC_CODE
  #undef AMDRTM_STOP_SEC_CODE
  #define STOP_SEC_CODE                             /* default code stop section */
#endif

/*******  CONST sections  ********************************************************************************************/

/* CONST sections */

#ifdef AMDRTM_START_SEC_CONST_8BIT
# undef AMDRTM_START_SEC_CONST_8BIT
# define START_SEC_CONST_8BIT
#endif
#ifdef AMDRTM_STOP_SEC_CONST_8BIT
# undef AMDRTM_STOP_SEC_CONST_8BIT
# define STOP_SEC_CONST
#endif

#ifdef AMDRTM_START_SEC_CONST_16BIT
# undef AMDRTM_START_SEC_CONST_16BIT
# define START_SEC_CONST_16BIT
#endif
#ifdef AMDRTM_STOP_SEC_CONST_16BIT
# undef AMDRTM_STOP_SEC_CONST_16BIT
# define STOP_SEC_CONST
#endif

#ifdef AMDRTM_START_SEC_CONST_32BIT
# undef AMDRTM_START_SEC_CONST_32BIT
# define START_SEC_CONST_32BIT
#endif
#ifdef AMDRTM_STOP_SEC_CONST_32BIT
# undef AMDRTM_STOP_SEC_CONST_32BIT
# define STOP_SEC_CONST
#endif


/*******  VAR sections  **********************************************************************************************/

/* VAR INIT sections */

#ifdef AMDRTM_START_SEC_VAR_INIT_8BIT
# undef AMDRTM_START_SEC_VAR_INIT_8BIT
# define START_SEC_VAR_INIT_8BIT
#endif
#ifdef AMDRTM_STOP_SEC_VAR_INIT_8BIT
# undef AMDRTM_STOP_SEC_VAR_INIT_8BIT
# define STOP_SEC_VAR
#endif

#ifdef AMDRTM_START_SEC_VAR_INIT_16BIT
# undef AMDRTM_START_SEC_VAR_INIT_16BIT
# define START_SEC_VAR_INIT_16BIT
#endif
#ifdef AMDRTM_STOP_SEC_VAR_INIT_16BIT
# undef AMDRTM_STOP_SEC_VAR_INIT_16BIT
# define STOP_SEC_VAR
#endif

#ifdef AMDRTM_START_SEC_VAR_INIT_32BIT
# undef AMDRTM_START_SEC_VAR_INIT_32BIT
# define START_SEC_VAR_INIT_32BIT
#endif
#ifdef AMDRTM_STOP_SEC_VAR_INIT_32BIT
# undef AMDRTM_STOP_SEC_VAR_INIT_32BIT
# define STOP_SEC_VAR
#endif

#ifdef AMDRTM_START_SEC_VAR_INIT_UNSPECIFIED
# undef AMDRTM_START_SEC_VAR_INIT_UNSPECIFIED
# define START_SEC_VAR_INIT_UNSPECIFIED
#endif
#ifdef AMDRTM_STOP_SEC_VAR_INIT_UNSPECIFIED
# undef AMDRTM_STOP_SEC_VAR_INIT_UNSPECIFIED
# define STOP_SEC_VAR
#endif

/* VAR NOINIT sections */

#ifdef AMDRTM_START_SEC_VAR_NOINIT_16BIT
# undef AMDRTM_START_SEC_VAR_NOINIT_16BIT
# define START_SEC_VAR_NOINIT_16BIT
#endif
#ifdef AMDRTM_STOP_SEC_VAR_NOINIT_16BIT
# undef AMDRTM_STOP_SEC_VAR_NOINIT_16BIT
# define STOP_SEC_VAR
#endif

#ifdef AMDRTM_START_SEC_VAR_NOINIT_32BIT
# undef AMDRTM_START_SEC_VAR_NOINIT_32BIT
# define START_SEC_VAR_NOINIT_32BIT
#endif
#ifdef AMDRTM_STOP_SEC_VAR_NOINIT_32BIT
# undef AMDRTM_STOP_SEC_VAR_NOINIT_32BIT
# define STOP_SEC_VAR
#endif

#ifdef AMDRTM_START_SEC_VAR_NOINIT_UNSPECIFIED
# undef AMDRTM_START_SEC_VAR_NOINIT_UNSPECIFIED
# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#ifdef AMDRTM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef AMDRTM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
 *  AMDRTM END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  CANNM START 
 *********************************************************************************************************************/

/*******  CODE sections **********************************************************************************************/

#ifdef CANNM_START_SEC_CODE
    #undef CANNM_START_SEC_CODE                         /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define START_SEC_CODE                              /* mapped to default code section */
#endif
#ifdef CANNM_STOP_SEC_CODE
    #undef CANNM_STOP_SEC_CODE                          /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define STOP_SEC_CODE                               /* default code stop section */
#endif

/*******  CONST sections  ********************************************************************************************/

/* CONST sections */

#ifdef CANNM_START_SEC_CONST_8BIT
    #undef CANNM_START_SEC_CONST_8BIT                   /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define START_SEC_CONST_8BIT                        /* mapped to default const section */
#endif
#ifdef CANNM_STOP_SEC_CONST_8BIT
    #undef CANNM_STOP_SEC_CONST_8BIT                    /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define STOP_SEC_CONST                              /* default const stop section */
#endif

#ifdef CANNM_START_SEC_CONST_32BIT
    #undef CANNM_START_SEC_CONST_32BIT                  /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define START_SEC_CONST_32BIT                       /* mapped to default const section */
#endif
#ifdef CANNM_STOP_SEC_CONST_32BIT
    #undef CANNM_STOP_SEC_CONST_32BIT                   /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define STOP_SEC_CONST                              /* default const stop section */
#endif

#ifdef CANNM_START_SEC_CONST_UNSPECIFIED
    #undef CANNM_START_SEC_CONST_UNSPECIFIED            /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define START_SEC_CONST_UNSPECIFIED                 /* mapped to default const section */
#endif
#ifdef CANNM_STOP_SEC_CONST_UNSPECIFIED
    #undef CANNM_STOP_SEC_CONST_UNSPECIFIED             /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define STOP_SEC_CONST                              /* default const stop section */
#endif

/* Postbuild CFG CONST sections */

#ifdef CANNM_START_SEC_PBCFG
    #undef CANNM_START_SEC_PBCFG                        /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define START_SEC_CONST_PBCFG                       /* mapped to default postbuild section */
#endif
#ifdef CANNM_STOP_SEC_PBCFG
    #undef CANNM_STOP_SEC_PBCFG                         /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define STOP_SEC_CONST                              /* default const stop section */
#endif

#ifdef CANNM_START_SEC_PBCFG_ROOT
    #undef CANNM_START_SEC_PBCFG_ROOT                   /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define START_SEC_CONST_PBCFG                       /* mapped to default postbuild section */
#endif
#ifdef CANNM_STOP_SEC_PBCFG_ROOT
    #undef CANNM_STOP_SEC_PBCFG_ROOT                    /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define STOP_SEC_CONST                              /* default const stop section */
#endif

/*******  VAR sections  **********************************************************************************************/

/* VAR NOINIT sections */

#ifdef CANNM_START_SEC_VAR_NOINIT_8BIT
    #undef CANNM_START_SEC_VAR_NOINIT_8BIT              /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define START_SEC_VAR_NOINIT_8BIT                   /* mapped to default var section */
#endif
#ifdef CANNM_STOP_SEC_VAR_NOINIT_8BIT
    #undef CANNM_STOP_SEC_VAR_NOINIT_8BIT               /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define STOP_SEC_VAR                                /* default var stop section */
#endif

#ifdef CANNM_START_SEC_VAR_NOINIT_UNSPECIFIED
    #undef CANNM_START_SEC_VAR_NOINIT_UNSPECIFIED       /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define START_SEC_VAR_NOINIT_UNSPECIFIED            /* mapped to default var section */
#endif
#ifdef CANNM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
    #undef CANNM_STOP_SEC_VAR_NOINIT_UNSPECIFIED        /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define STOP_SEC_VAR                                /* default var stop section */
#endif

/* VAR FAST NOINIT sections */

#ifdef CANNM_START_SEC_VAR_FAST_NOINIT_8BIT
    #undef CANNM_START_SEC_VAR_FAST_NOINIT_8BIT         /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define START_SEC_VAR_FAST_NOINIT_8BIT              /* mapped to default var section */
#endif
#ifdef CANNM_STOP_SEC_VAR_FAST_NOINIT_8BIT
    #undef CANNM_STOP_SEC_VAR_FAST_NOINIT_8BIT          /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define STOP_SEC_VAR                                /* default var stop section */
#endif

#ifdef CANNM_START_SEC_VAR_FAST_NOINIT_16BIT
    #undef CANNM_START_SEC_VAR_FAST_NOINIT_16BIT        /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define START_SEC_VAR_FAST_NOINIT_16BIT             /* mapped to default var section */
#endif
#ifdef CANNM_STOP_SEC_VAR_FAST_NOINIT_16BIT
    #undef CANNM_STOP_SEC_VAR_FAST_NOINIT_16BIT         /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define STOP_SEC_VAR                                /* default var stop section */
#endif

#ifdef CANNM_START_SEC_VAR_FAST_NOINIT_UNSPECIFIED
    #undef CANNM_START_SEC_VAR_FAST_NOINIT_UNSPECIFIED  /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define START_SEC_VAR_FAST_NOINIT_UNSPECIFIED       /* mapped to default var section */
#endif
#ifdef CANNM_STOP_SEC_VAR_FAST_NOINIT_UNSPECIFIED
    #undef CANNM_STOP_SEC_VAR_FAST_NOINIT_UNSPECIFIED   /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define STOP_SEC_VAR                                /* default var stop section */
#endif

/* VAR FAST ZERO INIT sections */

#ifdef CANNM_START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED
    #undef CANNM_START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED      /* mapped to default var section */
#endif
#ifdef CANNM_STOP_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED
    #undef CANNM_STOP_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED  /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define STOP_SEC_VAR                                  /* default var stop section */
#endif

/**********************************************************************************************************************
 *  CANNM END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  NM START 
 *********************************************************************************************************************/

/*******  CODE sections **********************************************************************************************/

#ifdef NM_START_SEC_CODE
# undef NM_START_SEC_CODE                               /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CODE                                 /* mapped to default code section */
#endif
#ifdef NM_STOP_SEC_CODE
# undef NM_STOP_SEC_CODE                                /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CODE                                  /* default code stop section */
#endif

/*******  CONST sections  ********************************************************************************************/

#ifdef NM_START_SEC_CONST_8BIT
# undef NM_START_SEC_CONST_8BIT                         /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_8BIT                           /* mapped to default const section */
#endif
#ifdef NM_STOP_SEC_CONST_8BIT
# undef NM_STOP_SEC_CONST_8BIT                          /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST                                 /* default const stop section */
#endif

#ifdef NM_START_SEC_CONST_32BIT
# undef NM_START_SEC_CONST_32BIT                        /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_32BIT                          /* mapped to default const section */
#endif
#ifdef NM_STOP_SEC_CONST_32BIT
# undef NM_STOP_SEC_CONST_32BIT                         /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST                                 /* default const stop section */
#endif

#ifdef NM_START_SEC_CONST_UNSPECIFIED
# undef NM_START_SEC_CONST_UNSPECIFIED                  /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_UNSPECIFIED                    /* mapped to default const section */
#endif
#ifdef NM_STOP_SEC_CONST_UNSPECIFIED
# undef NM_STOP_SEC_CONST_UNSPECIFIED                   /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST                                 /* default const stop section */
#endif

/*******  VAR sections  **********************************************************************************************/

/* VAR NOINIT sections */

#ifdef NM_START_SEC_VAR_NOINIT_8BIT
# undef NM_START_SEC_VAR_NOINIT_8BIT                    /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_NOINIT_8BIT                      /* mapped to default var section */
#endif
#ifdef NM_STOP_SEC_VAR_NOINIT_8BIT
# undef NM_STOP_SEC_VAR_NOINIT_8BIT                     /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR                                   /* default var stop section */
#endif

#ifdef NM_START_SEC_VAR_NOINIT_UNSPECIFIED
# undef NM_START_SEC_VAR_NOINIT_UNSPECIFIED             /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_NOINIT_UNSPECIFIED               /* mapped to default var section */
#endif
#ifdef NM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef NM_STOP_SEC_VAR_NOINIT_UNSPECIFIED              /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR                                   /* default var stop section */
#endif

/* VAR FAST NOINIT sections */

#ifdef NM_START_SEC_VAR_FAST_NOINIT_8BIT
# undef NM_START_SEC_VAR_FAST_NOINIT_8BIT               /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_FAST_NOINIT_8BIT                 /* mapped to default var section */
#endif
#ifdef NM_STOP_SEC_VAR_FAST_NOINIT_8BIT
# undef NM_STOP_SEC_VAR_FAST_NOINIT_8BIT                /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR                                   /* default var stop section */
#endif

#ifdef NM_START_SEC_VAR_FAST_NOINIT_16BIT
# undef NM_START_SEC_VAR_FAST_NOINIT_16BIT              /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_FAST_NOINIT_16BIT                /* mapped to default var section */
#endif
#ifdef NM_STOP_SEC_VAR_FAST_NOINIT_16BIT
# undef NM_STOP_SEC_VAR_FAST_NOINIT_16BIT               /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR                                   /* default var stop section */
#endif

#ifdef NM_START_SEC_VAR_FAST_NOINIT_UNSPECIFIED
# undef NM_START_SEC_VAR_FAST_NOINIT_UNSPECIFIED        /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_FAST_NOINIT_UNSPECIFIED          /* mapped to default var section */
#endif
#ifdef NM_STOP_SEC_VAR_FAST_NOINIT_UNSPECIFIED
# undef NM_STOP_SEC_VAR_FAST_NOINIT_UNSPECIFIED         /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR                                   /* default var stop section */
#endif

/* VAR FAST ZERO INIT sections */

#ifdef NM_START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED
# undef NM_START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED     /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED       /* mapped to default var section */
#endif
#ifdef NM_STOP_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED
# undef NM_STOP_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED      /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR                                   /* default var stop section */
#endif

/**********************************************************************************************************************
 *  NM END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  BSWM START 
 *********************************************************************************************************************/

/*******  CODE sections **********************************************************************************************/
#ifdef BSWM_START_SEC_CODE
    #undef BSWM_START_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define START_SEC_CODE    /*mapped to default code section*/
#endif

#ifdef BSWM_STOP_SEC_CODE
    #undef BSWM_STOP_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define STOP_SEC_CODE     /*default code stop section*/
#endif

#ifdef BSWM_START_SEC_CONST_UNSPECIFIED
    #undef BSWM_START_SEC_CONST_UNSPECIFIED  /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef BSWM_STOP_SEC_CONST_UNSPECIFIED
    #undef BSWM_STOP_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define STOP_SEC_CONST
#endif

#ifdef BSWM_START_SEC_CONST_8BIT
    #undef BSWM_START_SEC_CONST_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define START_SEC_CONST_8BIT                    /*default code stop section*/
#endif

#ifdef BSWM_STOP_SEC_CONST_8BIT
    #undef BSWM_STOP_SEC_CONST_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define STOP_SEC_CONST                   /*default code stop section*/
#endif

#ifdef BSWM_START_SEC_CONST_32BIT
    #undef BSWM_START_SEC_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define START_SEC_CONST_32BIT     /*default code stop section*/
#endif

#ifdef BSWM_STOP_SEC_CONST_32BIT
    #undef BSWM_STOP_SEC_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define STOP_SEC_CONST           /*default code stop section*/
#endif

#ifdef BSWM_START_SEC_VAR_NOINIT_8BIT
    #undef BSWM_START_SEC_VAR_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define START_SEC_VAR_NOINIT_8BIT     /*mapped to default code section*/
#endif

#ifdef BSWM_STOP_SEC_VAR_NOINIT_8BIT
    #undef BSWM_STOP_SEC_VAR_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define STOP_SEC_VAR                   /*mapped to default code section*/
#endif

#ifdef BSWM_START_SEC_VAR_NOINIT_16BIT
    #undef BSWM_START_SEC_VAR_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define START_SEC_VAR_NOINIT_16BIT      /*mapped to default code section*/
#endif

#ifdef BSWM_STOP_SEC_VAR_NOINIT_16BIT
    #undef BSWM_STOP_SEC_VAR_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define STOP_SEC_VAR                   /*mapped to default code section*/
#endif

#ifdef BSWM_START_SEC_VAR_NOINIT_32BIT
  #undef  BSWM_START_SEC_VAR_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define START_SEC_VAR_NOINIT_32BIT
#endif

#ifdef BSWM_STOP_SEC_VAR_NOINIT_32BIT
# undef BSWM_STOP_SEC_VAR_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR                  /*default var section*/
#endif

#ifdef BSWM_START_SEC_VAR_NOINIT_UNSPECIFIED
    #undef BSWM_START_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define START_SEC_VAR_NOINIT_UNSPECIFIED     /*mapped to default code section*/
#endif

#ifdef BSWM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
    #undef BSWM_STOP_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define STOP_SEC_VAR                        /*mapped to default code section*/
#endif

#ifdef BSWM_START_SEC_VAR_INIT_UNSPECIFIED
    #undef BSWM_START_SEC_VAR_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define START_SEC_VAR_INIT_UNSPECIFIED     /*mapped to default code section*/
#endif

#ifdef BSWM_STOP_SEC_VAR_INIT_UNSPECIFIED
    #undef BSWM_STOP_SEC_VAR_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define STOP_SEC_VAR                      /*mapped to default code section*/
#endif


/**********************************************************************************************************************
 *  BSWM END
 *********************************************************************************************************************/

#ifdef CRC_START_SEC_CODE
    #undef CRC_START_SEC_CODE
    #define START_SEC_CODE
#endif
#ifdef CRC_START_SEC_CONST_8BIT
    #undef CRC_START_SEC_CONST_8BIT
    #define START_SEC_CONST_8BIT
#endif
#ifdef CRC_START_SEC_CONST_16BIT
    #undef CRC_START_SEC_CONST_16BIT
    #define START_SEC_CONST_16BIT
#endif
#ifdef CRC_START_SEC_CONST_32BIT
    #undef CRC_START_SEC_CONST_32BIT
    #define START_SEC_CONST_32BIT
#endif

#ifdef CRC_STOP_SEC_CODE
    #undef CRC_STOP_SEC_CODE
    #define STOP_SEC_CODE
#endif
#ifdef CRC_STOP_SEC_CONST_8BIT
    #undef CRC_STOP_SEC_CONST_8BIT
    #define STOP_SEC_CONST
#endif

#ifdef CRC_STOP_SEC_CONST_16BIT
    #undef CRC_STOP_SEC_CONST_16BIT
    #define STOP_SEC_CONST
#endif

#ifdef CRC_STOP_SEC_CONST_32BIT
    #undef CRC_STOP_SEC_CONST_32BIT
    #define STOP_SEC_CONST
#endif


#ifdef DET_START_SEC_CODE
# undef DET_START_SEC_CODE
# define START_SEC_CODE
#endif
#ifdef DET_STOP_SEC_CODE
# undef DET_STOP_SEC_CODE
# define STOP_SEC_CODE
#endif

#ifdef DET_START_SEC_VAR_UNSPECIFIED
# undef DET_START_SEC_VAR_UNSPECIFIED
# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#ifdef DET_STOP_SEC_VAR_UNSPECIFIED
# undef DET_STOP_SEC_VAR_UNSPECIFIED
# define STOP_SEC_VAR
#endif



/**********************************************************************************************************************
 *  SYSSERVICE_ASRECUM START 
 *********************************************************************************************************************/

/*******  CODE sections **********************************************************************************************/
#ifdef ECUM_START_SEC_CODE
# undef ECUM_START_SEC_CODE
# define START_SEC_CODE                            /* mapped to default code section */
#endif
#ifdef ECUM_STOP_SEC_CODE
# undef ECUM_STOP_SEC_CODE
# define STOP_SEC_CODE                             /* default code stop section */
#endif

#ifdef ECUM_START_SEC_CODE_SET_BOOT_TARGET
# undef ECUM_START_SEC_CODE_SET_BOOT_TARGET
# define START_SEC_CODE                            /* mapped to default fast code section */
#endif
#ifdef ECUM_STOP_SEC_CODE_SET_BOOT_TARGET
# undef ECUM_STOP_SEC_CODE_SET_BOOT_TARGET
# define STOP_SEC_CODE                             /* default code stop section */
#endif

#ifdef ECUM_START_SEC_CODE_GET_BOOT_TARGET
# undef ECUM_START_SEC_CODE_GET_BOOT_TARGET
# define START_SEC_CODE                            /* mapped to default ISR code section */
#endif
#ifdef ECUM_STOP_SEC_CODE_GET_BOOT_TARGET
# undef ECUM_STOP_SEC_CODE_GET_BOOT_TARGET
# define STOP_SEC_CODE                             /* default code stop section */
#endif

/*******  CONST sections  ********************************************************************************************/

/* CONST sections */

#ifdef ECUM_START_SEC_CONST_8BIT
# undef ECUM_START_SEC_CONST_8BIT
# define START_SEC_CONST_8BIT                       /* mapped to default const 8bit section */
#endif
#ifdef ECUM_STOP_SEC_CONST_8BIT
# undef ECUM_STOP_SEC_CONST_8BIT
# define STOP_SEC_CONST                             /* default const stop section */
#endif

#ifdef ECUM_START_SEC_CONST_UNSPECIFIED
# undef ECUM_START_SEC_CONST_UNSPECIFIED
# define START_SEC_CONST_UNSPECIFIED
#endif
#ifdef ECUM_STOP_SEC_CONST_UNSPECIFIED
# undef ECUM_STOP_SEC_CONST_UNSPECIFIED
# define STOP_SEC_CONST
#endif

/* FAST CONST sections */

/* Postbuild CFG CONST sections */

/* Root table for postbuild data */
#ifdef ECUM_START_SEC_CONST_PBCFG_ROOT
# undef ECUM_START_SEC_CONST_PBCFG_ROOT
# define START_SEC_CONST_PBCFG
#endif
#ifdef ECUM_STOP_SEC_CONST_PBCFG_ROOT
# undef ECUM_STOP_SEC_CONST_PBCFG_ROOT
# define STOP_SEC_CONST
#endif

#ifdef ECUM_START_SEC_CONST_PBCFG
# undef ECUM_START_SEC_CONST_PBCFG
# define START_SEC_CONST_PBCFG
#endif
#ifdef ECUM_STOP_SEC_CONST_PBCFG
# undef ECUM_STOP_SEC_CONST_PBCFG
# define STOP_SEC_CONST
#endif

/*******  VAR sections  **********************************************************************************************/

/* VAR INIT sections */

#ifdef ECUM_START_SEC_VAR_INIT_UNSPECIFIED
# undef ECUM_START_SEC_VAR_INIT_UNSPECIFIED
# define START_SEC_VAR_INIT_UNSPECIFIED
#endif
#ifdef ECUM_STOP_SEC_VAR_INIT_UNSPECIFIED
# undef ECUM_STOP_SEC_VAR_INIT_UNSPECIFIED
# define STOP_SEC_VAR
#endif

/* VAR NOINIT sections */

#ifdef ECUM_START_SEC_VAR_NOINIT_8BIT
# undef ECUM_START_SEC_VAR_NOINIT_8BIT
# define START_SEC_VAR_NOINIT_8BIT
#endif
#ifdef ECUM_STOP_SEC_VAR_NOINIT_8BIT
# undef ECUM_STOP_SEC_VAR_NOINIT_8BIT
# define STOP_SEC_VAR
#endif

#ifdef ECUM_START_SEC_VAR_NOINIT_16BIT
# undef ECUM_START_SEC_VAR_NOINIT_16BIT
# define START_SEC_VAR_NOINIT_16BIT
#endif
#ifdef ECUM_STOP_SEC_VAR_NOINIT_16BIT
# undef ECUM_STOP_SEC_VAR_NOINIT_16BIT
# define STOP_SEC_VAR
#endif

#ifdef ECUM_START_SEC_VAR_NOINIT_UNSPECIFIED
# undef ECUM_START_SEC_VAR_NOINIT_UNSPECIFIED
# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#ifdef ECUM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef ECUM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# define STOP_SEC_VAR
#endif

/* VAR ZERO INIT sections */

/* VAR FAST INIT sections */

/* VAR FAST NOINIT sections */

/* VAR FAST ZERO INIT sections */


/**********************************************************************************************************************
 *  SYSSERVICE_ASRECUM END
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  SchM START 
 *********************************************************************************************************************/

/*******  CODE sections **********************************************************************************************/

#ifdef SCHM_START_SEC_CODE
# undef SCHM_START_SEC_CODE
# define START_SEC_CODE
#endif
#ifdef SCHM_STOP_SEC_CODE
# undef SCHM_STOP_SEC_CODE
# define STOP_SEC_CODE
#endif

/*******  CONST sections  ********************************************************************************************/

/* CONST sections */

#ifdef SCHM_START_SEC_CONST_8BIT
# undef SCHM_START_SEC_CONST_8BIT
# define START_SEC_CONST_8BIT
#endif
#ifdef SCHM_STOP_SEC_CONST_8BIT
# undef SCHM_STOP_SEC_CONST_8BIT
# define STOP_SEC_CONST
#endif


/*******  VAR sections  **********************************************************************************************/

/* VAR NOINIT sections */

#ifdef SCHM_START_SEC_VAR_NOINIT_UNSPECIFIED
# undef SCHM_START_SEC_VAR_NOINIT_UNSPECIFIED
# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#ifdef SCHM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef SCHM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# define STOP_SEC_VAR
#endif

/* VAR ZERO_INIT sections */

#ifdef SCHM_START_SEC_VAR_ZERO_INIT_8BIT
# undef SCHM_START_SEC_VAR_ZERO_INIT_8BIT
# define START_SEC_VAR_ZERO_INIT_8BIT
#endif
#ifdef SCHM_STOP_SEC_VAR_ZERO_INIT_8BIT
# undef SCHM_STOP_SEC_VAR_ZERO_INIT_8BIT
# define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
 *  SchM END
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  CANTP START 
 *********************************************************************************************************************/

/*******  CODE sections **********************************************************************************************/

#if defined (CANTP_START_SEC_CODE)
   #undef    CANTP_START_SEC_CODE
   #define         START_SEC_CODE
#endif
#if defined (CANTP_STOP_SEC_CODE)
   #undef    CANTP_STOP_SEC_CODE
   #define         STOP_SEC_CODE
#endif



/*******  CONST sections  ********************************************************************************************/

/* CONST sections */

#if defined (CANTP_START_SEC_CONST_UNSPECIFIED)
   #undef    CANTP_START_SEC_CONST_UNSPECIFIED
   #define         START_SEC_CONST_UNSPECIFIED
#endif
#if defined (CANTP_STOP_SEC_CONST_UNSPECIFIED)
   #undef    CANTP_STOP_SEC_CONST_UNSPECIFIED
   #define         STOP_SEC_CONST
#endif

#if defined (CANTP_START_SEC_CONST_16BIT)
   #undef    CANTP_START_SEC_CONST_16BIT
   #define         START_SEC_CONST_16BIT
#endif
#if defined (CANTP_STOP_SEC_CONST_16BIT)
   #undef    CANTP_STOP_SEC_CONST_16BIT
   #define         STOP_SEC_CONST
#endif

#if defined (CANTP_START_SEC_CONST_32BIT)
   #undef    CANTP_START_SEC_CONST_32BIT
   #define         START_SEC_CONST_32BIT
#endif
#if defined (CANTP_STOP_SEC_CONST_32BIT)
   #undef    CANTP_STOP_SEC_CONST_32BIT
   #define         STOP_SEC_CONST
#endif


/* Postbuild sections */

#if defined (CANTP_START_SEC_CONST_PBCFG)
   #undef    CANTP_START_SEC_CONST_PBCFG
   #define         START_SEC_CONST_PBCFG
#endif
#if defined (CANTP_STOP_SEC_CONST_PBCFG)
   #undef    CANTP_STOP_SEC_CONST_PBCFG
   #define         STOP_SEC_CONST
#endif

#if defined (CANTP_START_SEC_CONST_PBCFG_ROOT)
   #undef    CANTP_START_SEC_CONST_PBCFG_ROOT
   #define         START_SEC_CONST_PBCFG
#endif
#if defined (CANTP_STOP_SEC_CONST_PBCFG_ROOT)
   #undef    CANTP_STOP_SEC_CONST_PBCFG_ROOT
   #define         STOP_SEC_CONST
#endif  



/*******  VAR sections  **********************************************************************************************/

/* VAR INIT sections */

#if defined (CANTP_START_SEC_VAR_INIT_UNSPECIFIED)
   #undef    CANTP_START_SEC_VAR_INIT_UNSPECIFIED
   #define         START_SEC_VAR_INIT_UNSPECIFIED
#endif
#if defined (CANTP_STOP_SEC_VAR_INIT_UNSPECIFIED)
   #undef    CANTP_STOP_SEC_VAR_INIT_UNSPECIFIED
   #define         STOP_SEC_VAR
#endif


/* VAR NOINIT sections */

#if defined (CANTP_START_SEC_VAR_NOINIT_UNSPECIFIED)
   #undef    CANTP_START_SEC_VAR_NOINIT_UNSPECIFIED
   #define         START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#if defined (CANTP_STOP_SEC_VAR_NOINIT_UNSPECIFIED)
   #undef    CANTP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
   #define         STOP_SEC_VAR
#endif

#if defined (CANTP_START_SEC_VAR_NOINIT_8BIT)
   #undef    CANTP_START_SEC_VAR_NOINIT_8BIT
   #define         START_SEC_VAR_NOINIT_8BIT
#endif
#if defined (CANTP_STOP_SEC_VAR_NOINIT_8BIT)
   #undef    CANTP_STOP_SEC_VAR_NOINIT_8BIT
   #define         STOP_SEC_VAR
#endif


/**********************************************************************************************************************
 *  CANTP END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  E2E Lib 
 *********************************************************************************************************************/

/*******  CODE sections **********************************************************************************************/

#ifdef E2E_START_SEC_CODE
# undef E2E_START_SEC_CODE
# define START_SEC_CODE
#endif
#ifdef E2E_STOP_SEC_CODE
# undef E2E_STOP_SEC_CODE
# define STOP_SEC_CODE
#endif

#ifdef SCRC_START_SEC_CODE
# undef SCRC_START_SEC_CODE
# define START_SEC_CODE
#endif
#ifdef SCRC_STOP_SEC_CODE
# undef SCRC_STOP_SEC_CODE
# define STOP_SEC_CODE
#endif


/*******  CONST sections  ********************************************************************************************/

/* CONST sections */

#if defined (SCRC_START_SEC_CONST_8BIT)
   #undef    SCRC_START_SEC_CONST_8BIT
   #define         START_SEC_CONST_8BIT
#endif
#if defined (SCRC_STOP_SEC_CONST_8BIT)
   #undef    SCRC_STOP_SEC_CONST_8BIT
   #define         STOP_SEC_CONST
#endif

/**********************************************************************************************************************
 *  E2E END
 *********************************************************************************************************************/


/*-------------------------------------------------------------------------------------------------------------------*/
/* VStdLib start MemMap.inc                                                                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

/*---------------------------------- Code ---------------------------------------------------------------------------*/

#ifdef VSTDLIB_START_SEC_CODE                             /* VStdLib code */
# undef VSTDLIB_START_SEC_CODE                            /* PRQA S 0841 */
# define START_SEC_CODE                                   /* mapped to default code section */
#endif
#ifdef VSTDLIB_STOP_SEC_CODE
# undef VSTDLIB_STOP_SEC_CODE                             /* PRQA S 0841 */
# define STOP_SEC_CODE
#endif

/*---------------------------------- Const --------------------------------------------------------------------------*/

#ifdef VSTDLIB_START_SEC_CONST_UNSPECIFIED               /* VStdLib const */
# undef VSTDLIB_START_SEC_CONST_UNSPECIFIED              /* PRQA S 0841 */
# define START_SEC_CONST_UNSPECIFIED                     /* mapped to default const section */
#endif
#ifdef VSTDLIB_STOP_SEC_CONST_UNSPECIFIED  
# undef VSTDLIB_STOP_SEC_CONST_UNSPECIFIED               /* PRQA S 0841 */
# define STOP_SEC_CONST
#endif

/*---------------------------------- RAM ----------------------------------------------------------------------------*/

#ifdef VSTDLIB_START_SEC_VAR_NOINIT_UNSPECIFIED          /* VStdLib var */
# undef VSTDLIB_START_SEC_VAR_NOINIT_UNSPECIFIED         /* PRQA S 0841 */
# define START_SEC_VAR_NOINIT_UNSPECIFIED                /* mapped to default noinit var section */
#endif
#ifdef VSTDLIB_STOP_SEC_VAR_NOINIT_UNSPECIFIED  
# undef VSTDLIB_STOP_SEC_VAR_NOINIT_UNSPECIFIED          /* PRQA S 0841 */
# define STOP_SEC_VAR 
#endif

/*-------------------------------------------------------------------------------------------------------------------*/
/* VStdLib end MemMap.inc                                                                                            */
/*-------------------------------------------------------------------------------------------------------------------*/



/* Package Merger: Stop Section MemMapModuleList */


/* ------------------- provide compatibility to former specifications --------- */

#ifdef START_SEC_CONST_8
    #define START_SEC_CONST_8BIT
    #undef START_SEC_CONST_8 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_CONST_16
    #define START_SEC_CONST_16BIT
    #undef START_SEC_CONST_16 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_CONST_32
    #define START_SEC_CONST_32BIT
    #undef START_SEC_CONST_32 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_CONST_FAST_8
    #define START_SEC_CONST_FAST_8BIT
    #undef START_SEC_CONST_FAST_8 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_CONST_FAST_16
    #define START_SEC_CONST_FAST_16BIT
    #undef START_SEC_CONST_FAST_16 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_CONST_FAST_32
    #define START_SEC_CONST_FAST_32BIT
    #undef START_SEC_CONST_FAST_32 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_INIT_8
    #define START_SEC_VAR_INIT_8BIT
    #undef START_SEC_VAR_INIT_8 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_INIT_16
    #define START_SEC_VAR_INIT_16BIT
    #undef START_SEC_VAR_INIT_16 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_INIT_32
    #define START_SEC_VAR_INIT_32BIT
    #undef START_SEC_VAR_INIT_32 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_NO_INIT_8
    #define START_SEC_VAR_NOINIT_8BIT
    #undef START_SEC_VAR_NO_INIT_8 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_NO_INIT_16
    #define START_SEC_VAR_NOINIT_16BIT
    #undef START_SEC_VAR_NO_INIT_16 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_NO_INIT_32
    #define START_SEC_VAR_NOINIT_32BIT
    #undef START_SEC_VAR_NO_INIT_32 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_NO_INIT_UNSPECIFIED
    #define START_SEC_VAR_NOINIT_UNSPECIFIED
    #undef START_SEC_VAR_NO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_CLEARED_8
    #define START_SEC_VAR_ZERO_INIT_8BIT
    #undef START_SEC_VAR_CLEARED_8 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_CLEARED_16
    #define START_SEC_VAR_ZERO_INIT_16BIT
    #undef START_SEC_VAR_CLEARED_16 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_CLEARED_32
    #define START_SEC_VAR_ZERO_INIT_32BIT
    #undef START_SEC_VAR_CLEARED_32 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_CLEARED_UNSPECIFIED
    #define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
    #undef START_SEC_VAR_CLEARED_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_FAST_INIT_8
    #define START_SEC_VAR_FAST_INIT_8BIT
    #undef START_SEC_VAR_FAST_INIT_8 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_FAST_INIT_16
    #define START_SEC_VAR_FAST_INIT_16BIT
    #undef START_SEC_VAR_FAST_INIT_16 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_FAST_INIT_32
    #define START_SEC_VAR_FAST_INIT_32BIT
    #undef START_SEC_VAR_FAST_INIT_32 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_FAST_NO_INIT_8
    #define START_SEC_VAR_FAST_NOINIT_8BIT
    #undef START_SEC_VAR_FAST_NO_INIT_8 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_FAST_NO_INIT_16
    #define START_SEC_VAR_FAST_NOINIT_16BIT
    #undef START_SEC_VAR_FAST_NO_INIT_16 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_FAST_NO_INIT_32
    #define START_SEC_VAR_FAST_NOINIT_32BIT
    #undef START_SEC_VAR_FAST_NO_INIT_32 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_FAST_NO_INIT_UNSPECIFIED
    #define START_SEC_VAR_FAST_NOINIT_UNSPECIFIED
    #undef START_SEC_VAR_FAST_NO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_FAST_CLEARED_8
    #define START_SEC_VAR_FAST_ZERO_INIT_8BIT
    #undef START_SEC_VAR_FAST_CLEARED_8 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_FAST_CLEARED_16
    #define START_SEC_VAR_FAST_ZERO_INIT_16BIT
    #undef START_SEC_VAR_FAST_CLEARED_16 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_FAST_CLEARED_32
    #define START_SEC_VAR_FAST_ZERO_INIT_32BIT
    #undef START_SEC_VAR_FAST_CLEARED_32 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_FAST_CLEARED_UNSPECIFIED
    #define START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED
    #undef START_SEC_VAR_FAST_CLEARED_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_NOCACHE_INIT_8
    #define START_SEC_VAR_NOCACHE_INIT_8BIT
    #undef START_SEC_VAR_NOCACHE_INIT_8 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_NOCACHE_INIT_16
    #define START_SEC_VAR_NOCACHE_INIT_16BIT
    #undef START_SEC_VAR_NOCACHE_INIT_16 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_NOCACHE_INIT_32
    #define START_SEC_VAR_NOCACHE_INIT_32BIT
    #undef START_SEC_VAR_NOCACHE_INIT_32 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_NOCACHE_NO_INIT_8
    #define START_SEC_VAR_NOCACHE_NOINIT_8BIT
    #undef START_SEC_VAR_NOCACHE_NO_INIT_8 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_NOCACHE_NO_INIT_16
    #define START_SEC_VAR_NOCACHE_NOINIT_16BIT
    #undef START_SEC_VAR_NOCACHE_NO_INIT_16 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_NOCACHE_NO_INIT_32
    #define START_SEC_VAR_NOCACHE_NOINIT_32BIT
    #undef START_SEC_VAR_NOCACHE_NO_INIT_32 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_NOCACHE_NO_INIT_UNSPECIFIED
    #define START_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED
    #undef START_SEC_VAR_NOCACHE_NO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_NOCACHE_CLEARED_8
    #define START_SEC_VAR_NOCACHE_ZERO_INIT_8BIT
    #undef START_SEC_VAR_NOCACHE_CLEARED_8 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_NOCACHE_CLEARED_16
    #define START_SEC_VAR_NOCACHE_ZERO_INIT_16BIT
    #undef START_SEC_VAR_NOCACHE_CLEARED_16 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_NOCACHE_CLEARED_32
    #define START_SEC_VAR_NOCACHE_ZERO_INIT_32BIT
    #undef START_SEC_VAR_NOCACHE_CLEARED_32 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_NOCACHE_CLEARED_UNSPECIFIED
    #define START_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED
    #undef START_SEC_VAR_NOCACHE_CLEARED_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

/*------------------------------GLOBAL-SECTIONS-----------------------------*/
/* Check code sections */
#if ( (defined CODE_SEC_OPEN)                            && \
     ((defined START_SEC_CODE                          ) || \
      (defined START_SEC_CODE_FAST                     ) || \
      (defined START_SEC_CODE_ISR                      )    \
      ))
    #error "MemMap.h: Close the former code segment before opening a new one."
#endif

/* Check const sections */
#if ( (defined CONST_SEC_OPEN)                           && \
     ((defined START_SEC_CONST_8BIT                    ) || \
      (defined START_SEC_CONST_16BIT                   ) || \
      (defined START_SEC_CONST_32BIT                   ) || \
      (defined START_SEC_CONST_UNSPECIFIED             ) || \
      (defined START_SEC_CONST_FAST_8BIT               ) || \
      (defined START_SEC_CONST_FAST_16BIT              ) || \
      (defined START_SEC_CONST_FAST_32BIT              ) || \
      (defined START_SEC_CONST_FAST_UNSPECIFIED        ) || \
      (defined START_SEC_CONST_PBCFG                   ) || \
      (defined START_SEC_PBCFG_GLOBALROOT              )    \
      ))
    #error "MemMap.h: Close the former const segment before opening a new one."
#endif

/* Check data sections */
#if ( (defined VAR_SEC_OPEN)                             && \
     ((defined START_SEC_VAR_INIT_8BIT                 ) || \
      (defined START_SEC_VAR_INIT_16BIT                ) || \
      (defined START_SEC_VAR_INIT_32BIT                ) || \
      (defined START_SEC_VAR_INIT_UNSPECIFIED          ) || \
      (defined START_SEC_VAR_NOINIT_8BIT               ) || \
      (defined START_SEC_VAR_NOINIT_16BIT              ) || \
      (defined START_SEC_VAR_NOINIT_32BIT              ) || \
      (defined START_SEC_VAR_NOINIT_UNSPECIFIED        ) || \
      (defined START_SEC_VAR_PBCFG                     ) || \
      (defined START_SEC_VAR_ZERO_INIT_8BIT            ) || \
      (defined START_SEC_VAR_ZERO_INIT_16BIT           ) || \
      (defined START_SEC_VAR_ZERO_INIT_32BIT           ) || \
      (defined START_SEC_VAR_ZERO_INIT_UNSPECIFIED     ) || \
      (defined START_SEC_VAR_FAST_INIT_8BIT            ) || \
      (defined START_SEC_VAR_FAST_INIT_16BIT           ) || \
      (defined START_SEC_VAR_FAST_INIT_32BIT           ) || \
      (defined START_SEC_VAR_FAST_INIT_UNSPECIFIED     ) || \
      (defined START_SEC_VAR_FAST_NOINIT_8BIT          ) || \
      (defined START_SEC_VAR_FAST_NOINIT_16BIT         ) || \
      (defined START_SEC_VAR_FAST_NOINIT_32BIT         ) || \
      (defined START_SEC_VAR_FAST_NOINIT_UNSPECIFIED   ) || \
      (defined START_SEC_VAR_FAST_ZERO_INIT_8BIT       ) || \
      (defined START_SEC_VAR_FAST_ZERO_INIT_16BIT      ) || \
      (defined START_SEC_VAR_FAST_ZERO_INIT_32BIT      ) || \
      (defined START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED) || \
      (defined START_SEC_VAR_NOCACHE_INIT_8BIT         ) || \
      (defined START_SEC_VAR_NOCACHE_INIT_16BIT        ) || \
      (defined START_SEC_VAR_NOCACHE_INIT_32BIT        ) || \
      (defined START_SEC_VAR_NOCACHE_INIT_UNSPECIFIED  ) || \
      (defined START_SEC_VAR_NOCACHE_NOINIT_8BIT       ) || \
      (defined START_SEC_VAR_NOCACHE_NOINIT_16BIT      ) || \
      (defined START_SEC_VAR_NOCACHE_NOINIT_32BIT      ) || \
      (defined START_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED) || \
      (defined START_SEC_VAR_NOCACHE_ZERO_INIT_8BIT    ) || \
      (defined START_SEC_VAR_NOCACHE_ZERO_INIT_16BIT   ) || \
      (defined START_SEC_VAR_NOCACHE_ZERO_INIT_32BIT   ) || \
	  (defined START_SEC_VAR_NOCACHE_ZERO_INIT_32BIT   ) || \
      (defined START_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED)    \
      ))
    #error "MemMap.h: Close the former variable segment before opening a new one."
#endif

/*------------------------------GLOBAL-START-SECTIONS------------------------------*/

/* Code section */

#if defined( FBL_APPLVECT_START_SEC_CONST ) || \
    defined( FBL_APPLVECT_START_SEC_CONST_EXPORT )
#   pragma ghs startdata
#   pragma ghs section rodata=".APPLVECT"
# undef FBL_APPLVECT_START_SEC_CONST
# undef FBL_APPLVECT_START_SEC_CONST_EXPORT
# undef MEMMAP_ERROR
#endif


#ifdef START_SEC_CODE                          
    #define CODE_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_CODE                           /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_CODE_FAST                     
    #define CODE_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_CODE_FAST                      /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_CODE_ISR                      
    #define CODE_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_CODE_ISR                       /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


/* Const section */
#ifdef START_SEC_CONST_8BIT                    
    #define CONST_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_CONST_8BIT                     /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_CONST_16BIT                   
    #define CONST_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_CONST_16BIT                    /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_CONST_32BIT                   
    #define CONST_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_CONST_32BIT                    /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_CONST_UNSPECIFIED             
    #define CONST_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_CONST_UNSPECIFIED              /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_CONST_FAST_8BIT               
    #define CONST_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_CONST_FAST_8BIT                /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_CONST_FAST_16BIT              
    #define CONST_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_CONST_FAST_16BIT               /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_CONST_FAST_32BIT              
    #define CONST_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_CONST_FAST_32BIT               /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_CONST_FAST_UNSPECIFIED        
    #define CONST_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_CONST_FAST_UNSPECIFIED         /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_CONST_PBCFG                   
    #define CONST_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_CONST_PBCFG                    /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_PBCFG_GLOBALROOT              
    #define CONST_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_PBCFG_GLOBALROOT               /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif




/* Var section */
#ifdef START_SEC_VAR_INIT_8BIT                 
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_INIT_8BIT                  /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_INIT_16BIT                
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_INIT_16BIT                 /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_INIT_32BIT                
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_INIT_32BIT                 /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_INIT_UNSPECIFIED          
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_INIT_UNSPECIFIED           /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_NOINIT_8BIT               
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_NOINIT_8BIT                /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_NOINIT_16BIT              
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_NOINIT_16BIT               /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_NOINIT_32BIT              
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_NOINIT_32BIT               /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_NOINIT_UNSPECIFIED        
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_NOINIT_UNSPECIFIED         /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_PBCFG                     
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_PBCFG                      /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_ZERO_INIT_8BIT            
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_ZERO_INIT_8BIT             /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_ZERO_INIT_16BIT           
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_ZERO_INIT_16BIT            /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_ZERO_INIT_32BIT           
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_ZERO_INIT_32BIT            /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_ZERO_INIT_UNSPECIFIED     
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_ZERO_INIT_UNSPECIFIED      /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_FAST_INIT_8BIT            
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_FAST_INIT_8BIT             /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_FAST_INIT_16BIT           
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_FAST_INIT_16BIT            /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_FAST_INIT_32BIT           
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_FAST_INIT_32BIT            /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_FAST_INIT_UNSPECIFIED     
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_FAST_INIT_UNSPECIFIED      /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_FAST_NOINIT_8BIT          
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_FAST_NOINIT_8BIT           /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_FAST_NOINIT_16BIT         
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_FAST_NOINIT_16BIT          /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_FAST_NOINIT_32BIT         
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_FAST_NOINIT_32BIT          /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_FAST_NOINIT_UNSPECIFIED   
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_FAST_NOINIT_UNSPECIFIED    /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_FAST_ZERO_INIT_8BIT       
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_FAST_ZERO_INIT_8BIT        /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_FAST_ZERO_INIT_16BIT      
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_FAST_ZERO_INIT_16BIT       /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_FAST_ZERO_INIT_32BIT      
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_FAST_ZERO_INIT_32BIT       /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_NOCACHE_INIT_8BIT         
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_NOCACHE_INIT_8BIT          /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_NOCACHE_INIT_16BIT        
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_NOCACHE_INIT_16BIT         /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_NOCACHE_INIT_32BIT        
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_NOCACHE_INIT_32BIT         /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_NOCACHE_INIT_UNSPECIFIED  
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_NOCACHE_INIT_UNSPECIFIED   /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_NOCACHE_NOINIT_8BIT       
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_NOCACHE_NOINIT_8BIT        /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_NOCACHE_NOINIT_16BIT      
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_NOCACHE_NOINIT_16BIT       /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_NOCACHE_NOINIT_32BIT      
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_NOCACHE_NOINIT_32BIT       /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_NOCACHE_ZERO_INIT_8BIT    
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_NOCACHE_ZERO_INIT_8BIT     /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_NOCACHE_ZERO_INIT_16BIT   
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_NOCACHE_ZERO_INIT_16BIT    /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_NOCACHE_ZERO_INIT_32BIT   
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_NOCACHE_ZERO_INIT_32BIT    /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif



/*------------------------------GENERAL-STOP-SECTIONS-------------------------------*/

/*default segment for Code*/

#if defined( FBL_APPLVECT_STOP_SEC_CONST ) || \
    defined( FBL_APPLVECT_STOP_SEC_CONST_EXPORT )
#    pragma ghs section rodata=default
#    pragma ghs enddata
# undef FBL_APPLVECT_STOP_SEC_CONST
# undef FBL_APPLVECT_STOP_SEC_CONST_EXPORT
# undef MEMMAP_ERROR
#endif


#ifdef STOP_SEC_CODE
    #undef CODE_SEC_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
/* Enter here a #pragma command for closing the specified section */
/* This should switch back to the default section */
/*    #pragma */
    #undef STOP_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

/*default segment for Constants*/
#ifdef STOP_SEC_CONST
    #undef CONST_SEC_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
/* Enter here a #pragma command for closing the specified section */
/* This should switch back to the default section */
/*    #pragma */
    #undef STOP_SEC_CONST /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

/*default segment for Datas*/
#ifdef STOP_SEC_VAR
    #undef VAR_SEC_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
/* Enter here a #pragma command for closing the specified section */
/* This should switch back to the default section */
/*    #pragma */
    #undef STOP_SEC_VAR /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef MEMMAP_ERROR
    #error "MemMap.h, wrong pragma command"
#endif

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  END OF FILE: MemMap.h
 *********************************************************************************************************************/

/* PRQA L:MEMMAP_0841_TAG */

