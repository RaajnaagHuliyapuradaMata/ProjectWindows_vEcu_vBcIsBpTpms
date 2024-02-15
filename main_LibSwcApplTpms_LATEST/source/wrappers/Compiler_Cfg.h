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
 *         File:  _Compiler_Cfg.h
 *    Component:  -
 *       Module:  -
 *    Generator:  -
 *
 *  Description:  This File is a template for the Compiler_Cfg.h
 *                This file has to be extended with the memory and pointer classes for all BSW modules
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
 *  01.01.01  2008-12-17  Ht                    Improve list of components  (Tp_AsrTpCan,Tp_AsrTpFr,DrvMcu,DrvIcu added)
 *  01.01.02  2009-04-27  Ht                    support OEM specific _compiler_cfg.inc file, improve list of components 
 *                                              (Cp_XcpOnCanAsr, Il_AsrIpduM, If_VxFblDcm, If_VxFblVpm_Volvo_ab, DrvFls added)
 *  01.01.03  2009-04-24  Msr                   Renamed J1939_AsrBase as TpJ1939_AsrBase
 *  01.01.04  2009-06-03  Ht                    Improve list of components (Adc, Dio, Gpt, Pwm, Spi, Wdg, Fls, Port, Fim)
 *  01.02.00  2009-08-01  Ht                    Improve list of components (Fee_30_Inst2, Can, ...Sub)
 *                                              Support filtering for RTE
 *  01.02.01  2009-09-02  Lo                    add external Flash driver support
 *  01.02.02  2009-09-21  Lo                    add DrvFls_Mcs12xFslftm01ExtVx
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
 *  01.03.02  2010-02-15  Ht                   support SysService_SswRcs_Daimler, SysService_Tls, Tp_Http, 
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
 *  01.05.04  2010-11-16  Ht                    add SysService_Exi, DrvTrans_Int6400EthAsr, Cdd_AsrCdd_Fiat, Diag_AsrDem_Fiat,
 *  01.05.05  2010-12-17  Ht                    add SysService_AsrSchM, DrvEep_XXStubAsr, DrvIcu_Tms570Tinhet01ExtVx
 *                                                  DrvWd_XTle4278gEAsr, DrvWd_XXStubAsr
 *  01.05.06  2011-02-17  Ht                    add DrvEed, SysService_AsrBswM
 *  01.05.07  2011-03-04  Ht                    add DrvTrans_Tja1055CandioAsr
 *                                              rename CanTrcv_30_Tja1040dio to CanTrcv_30_Tja1040
 *                                              add SysService_XmlEngine
 *  01.06.00  2011-03-04  Ht                    support ASR4.0
 *                                              add Ccl_Asr4ComM, Ccl_Asr4SmCan, Nm_Asr4NmIf, Nm_AsrNmDirOsek
 *  01.06.01  2011-04-15  Ht                    add Diag_AsrDcm_<OEM>
 *  01.06.02  2011-06-17  Ht                    correct Diag_AsrDcm_<OEM>
 *                                              add Monitoring_AsrDlt and Monitoring_GenericMeasurement
 *  01.06.03  2011-09-01  Ht                    add DrvTrans_Tja1145CanSpiAsr, DrvTrans_E52013CanspiAsr, DrvFls_XXStubAsr,
 *                                              If_AsrIfFeeV85xNec05Sub, If_AsrIfFeeV85xNec06Sub, If_AsrIfFeeV85xNec07Sub
 *                                              SysService_AsrWdMTttechSub and If_AsrIfWdTttechSub
 *  01.06.04  2011-10-20  Ht                    ESCAN00054334: add If_AsrIfFeeTiSub
 *                                              ESCAN00054719: add Cdd_AsrCdd
 *  01.06.05  2011-12-09  Ht                    add Tp_IpV4, Tp_IpV6
 *  01.06.06  2011-12-14  Ht                    add Monitoring_RuntimeMeasurement
 *  01.06.07  2012-01-03  Ht                    add DrvI2c, SysService_Asr4BswM
 *  01.06.08  2012-01-31  Ht                    add DrvTrans_Ar7000EthAsr, DrvTrans_GenericEthmiiAsr
 *  01.06.09  2012-03-06  Ht                    add If_AsrIfFeeMb9df126Fuji01Sub, 
 *                                              Infineon_Tc1767Inf01Sub, Infineon_Tc178xInf01Sub, Infineon_Tc1797Inf01Sub, Infineon_Tc1797Inf02Sub
 *  01.06.10  2012-03-13  Ht                    add Gw_AsrPduRCfg5, Il_AsrComCfg5, Il_AsrIpduMCfg5, Cdd_AsrCddCfg5,
 *                                              Tp_Asr4TpCan, Diag_Asr4Dcm, Diag_Asr4Dem
 *  01.06.11  2012-03-20  Ht                    add Cp_AsrCcp, Cp_XcpOnTcpIpAsr
 *  01.07.00  2012-07-26  Ht                    add Nm_Asr4NmCan, Nm_Asr4NmFr, Infineon_Xc2000Inf01Sub, Ccl_Asr4ComMCfg5, SysService_Asr4BswMCfg5, SysService_Asr4EcuM, SysService_AsrRamTst,
 *                                                  Ccl_Asr4SmLin
 *                                              add define REGSPACE - add support for ASR specification 4.0 R3
 *  01.07.01  2012-10-23  Seu                   add SysService_XmlSecurity
 *  01.07.02  2013-12-16  Seu                   MISRA compliance: usage of character "'" removed, typos corrected
 *********************************************************************************************************************/
#ifndef COMPILER_CFG_H
#define COMPILER_CFG_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
/* Package Merger: Start Section CompilerCfgIncludes */





#include "Rte_Compiler_Cfg.h"
#include "OHDSCanSlave_Compiler_Cfg.h"
/* Package Merger: Stop Section CompilerCfgIncludes */

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

#define AUTOSAR_COMSTACKDATA

#define MSR_REGSPACE  REGSPACE

/* Configurable memory class for pointers to registers (e.g. static volatile CONSTP2VAR(uint16, PWM_CONST, REGSPACE)). */
#define REGSPACE


/* due to compatibility to ASR 2.1 */
#define _STATIC_   STATIC
#define _INLINE_   INLINE

/* Package Merger: Start Section CompilerCfgModuleList */

#define V_SUPPRESS_EXTENDED_VERSION_CHECK

#if defined ( V_ENABLE_USE_DUMMY_STATEMENT )
#  define V_USE_DUMMY_STATEMENT STD_ON
#else
#  define V_USE_DUMMY_STATEMENT STD_OFF
#endif

/**********************************************************************************************************************
 *  RTE Huf as: 20.07.2015
 *********************************************************************************************************************/
#define RTE_OSTICKDURATION 1000000 /* 10^6 nanoseconds*/
//#define RTE_PTR2ARRAYBASETYPE_PASSING /*Tec. Ref. des RTEs Section 5.1.4 Usage of Array and String Data Types */

/**********************************************************************************************************************
 *  COMM START 
 *********************************************************************************************************************/

#define COMM_CODE

#define COMM_CONST

#define COMM_VAR_INIT
#define COMM_VAR_NOINIT
#define COMM_VAR_NOINIT_8BIT
#define COMM_VAR_NOINIT_16BIT
#define COMM_VAR_NOINIT_UNSPECIFIED
#define COMM_VAR_ZERO_INIT

#define COMM_APPL_CODE
#define COMM_APPL_VAR
#define COMM_APPL_VAR_NVRAM

#define COMM_PBCFG


/**********************************************************************************************************************
 *  COMM END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  CanSM START 
 *********************************************************************************************************************/

#define CANSM_CODE
#define CANSM_APPL_CODE

#define CANSM_CONST
#define CANSM_PBCFG

#define CANSM_VAR_INIT
#define CANSM_VAR_NOINIT
#define CANSM_VAR_ZERO_INIT

#define CANSM_APPL_VAR


/**********************************************************************************************************************
 *  CanSM END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  Cdd_AsrCdd START 
 *********************************************************************************************************************/

/* Copy the compiler abstraction defines for each of your configured CDDs and replace the prefix _CDD with the MSN of your configured CDD as higher case. */

#define _CDD_CODE
#define _CDD_APPL_DATA

/* Add additional compiler abstraction defines for each of you configured CDDs here. */

/**********************************************************************************************************************
 *  Cdd_AsrCdd END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  XCP START 
 *********************************************************************************************************************/

#define XCP_CONST
#define XCP_CODE
#define XCP_APPL_DATA
#define XCP_MTA_DATA
#define XCP_DAQ_DATA
#define XCP_VAR_NOINIT


/**********************************************************************************************************************
 *  XCP END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  CANXCP START 
 *********************************************************************************************************************/

#define CANXCP_VAR_NOINIT
#define CANXCP_CONST
#define CANXCP_PBCFG
#define CANXCP_CODE
#define CANXCP_APPL_VAR

/*-------------------------------------------------------------------------------------------------------------------*/
/* CANXCP END                                                                                                        */
/*-------------------------------------------------------------------------------------------------------------------*/



#define DCM_APPL_CONST
#define DCM_APPL_DATA
#define DCM_CONST
#define DCM_CAL_PRM
#define DCM_PBCFG
#define DCM_CODE
#define DCM_APPL_CODE
#define DCM_VAR_NOINIT



/*==== DEM =================================================================*/
#define DEM_CODE                /* code */
#define DEM_VAR                 /* global/static vars; init after every reset */
#define DEM_VAR_NOINIT_FAST     /* global/static vars; using: bitaccess or frequently used or many accesses in code */
#define DEM_VAR_NOINIT          /* global/static vars; not initialized after reset */
#define DEM_CONST               /* global/static constants */
#define DEM_PBCFG               /* global/static constants for PostBuild */
#define DEM_APPL_CODE           /* callback functions used by DEM, implemented outside DEM */
#define DEM_APPL_DATA           /* vars (buffers) outside DEM, passed via API */
#define DEM_APPL_CONST          /* constants outside DEM, passed via API */
#define FLS_E_WRITE_FAILED          Dem_FLS_E_WRITE_FAILED 
#define FLS_E_READ_FAILED           Dem_FLS_E_READ_FAILED 
#define FLS_E_ERASE_FAILED          Dem_FLS_E_ERASE_FAILED
#define FLS_E_READ_FAILED_DED       Dem_FLS_E_READ_FAILED_DED
#define MCU_E_WRITE_TIMEOUT_FAILURE Dem_MCU_E_WRITE_TIMEOUT_FAILURE
#define MCU_E_CLOCK_FAILURE         Dem_MCU_E_CLOCK_FAILURE
#define BRSASR_ENABLE_BSWINITSUPPORT /*BrsAsrInit Funktionen*/
#define SPI_E_HARDWARE_ERROR        Dem_SPI_E_HARDWARE_ERROR /*as: 62 in Dem_IntErrId.h */
#define SPI_E_DATA_TX_TIMEOUT_FAILURE   Dem_SPI_E_DATA_TX_TIMEOUT_FAILURE/*as: 63 in Dem_IntErrId.h */
#define SPI_E_SELF_TEST_FAILURE         Dem_SPI_E_SELF_TEST_FAILURE/*as: 64 in Dem_IntErrId.h */
#define GPT_E_TIMEOUT_FAILURE       Dem_GPT_E_TIMEOUT_FAILURE
/*==========================================================================*/



#define ADC_PUBLIC_CODE
#define ADC_PUBLIC_CONST
#define ADC_PRIVATE_CODE
#define ADC_FAST_CODE
#define ADC_PRIVATE_DATA
#define ADC_PRIVATE_CONST
#define ADC_APPL_CODE
#define ADC_APPL_CONST
#define ADC_APPL_DATA
#define ADC_FAST_DATA
#define ADC_CONFIG_CONST
#define ADC_CONFIG_DATA
#define ADC_INIT_DATA
#define ADC_NOINIT_DATA
#define ADC_CONST


/* Kernbauer Version: 1.16 Konfiguration: DrvCAN Erzeugungsgangnummer: 1 */


/**********************************************************************************************************************
 *  Can START 
 *********************************************************************************************************************/

#define CAN_CODE                                   /* CAN modules code qualifier               */ /* PRQA S 0883 */ /* Appears only while testing */
#define CAN_STATIC_CODE                            /* CAN local code qualifier                 */
#define CAN_CONST                                  /* constant memory                          */
#define CAN_CONST_PBCFG                            /* postbuild generated constant/flash       */
#define CAN_VAR_NOINIT                             /* none initialized variables               */
#define CAN_VAR_INIT                               /* initialized variables                    */
#define CAN_VAR_PBCFG                              /* postbuild generated variables/dynamic RAM (CFG5 only) */
#define CAN_INT_CTRL                               /* access to Interrupt controller registers */
#define CAN_REG_CANCELL                            /* CAN cell register qualifier              */
#define CAN_RX_TX_DATA        CAN_REG_CANCELL      /* pointer width >= CAN_REG_CANCELL  / CAN rx/tx data / RAM or SFR    (rx data pointer for Indication and PreCopy functions to higher layers / tx data pointers / sdu  from application)   */
#define CAN_APPL_CODE                              /* Application code qualifier               */
#define CAN_APPL_CONST                             /* Application constant memory              */
#define CAN_APPL_VAR                               /* Application variables                    */

/**********************************************************************************************************************
 *  Can END
 *********************************************************************************************************************/
#define CAN_PBCFG  CAN_CONST_PBCFG                 /* used for compatibility (used by upper layer EcuM) */



/* ---------------------------------------------------------------------------*/
/*                   DIO                                                      */
/* ---------------------------------------------------------------------------*/

#define DIO_PUBLIC_CODE                /* API functions                        */
#define DIO_PUBLIC_CONST               /* API constants                        */
#define DIO_PRIVATE_CODE               /* Internal functions                   */
#define DIO_FAST_CODE                  /* Internal functions                   */
#define DIO_PRIVATE_DATA               /* Module internal data                 */
#define DIO_PRIVATE_CONST              /* Internal ROM Data                    */
#define DIO_APPL_CODE                  /* callbacks of the Application         */
#define DIO_APPL_CONST                 /* Applications ROM Data                */
#define DIO_APPL_DATA                  /* Applications RAM Data                */
#define DIO_FAST_DATA                  /* Near RAM Data                        */
#define DIO_CONFIG_CONST               /* Desc. Tables -> Config-dependent     */
#define DIO_CONFIG_DATA                /* Config. dependent (reg. size) data   */
#define DIO_INIT_DATA                  /* Data which is initialized during     */
#define DIO_NOINIT_DATA                /* Data which is not initialized during */
#define DIO_CONST                      /* Data Constants                       */




#define FLS_PUBLIC_CODE                /* API functions                       */
#define FLS_PUBLIC_CONST               /* API constants                       */

#define FLS_PRIVATE_CODE               /* Internal functions                  */
#define FLS_FAST_CODE                  /* Internal functions                  */

#define FLS_PRIVATE_DATA               /* Module internal data                */
#define FLS_PRIVATE_CONST              /* Internal ROM Data                   */

#define FLS_APPL_CODE                  /* callbacks of the Application        */
#define FLS_APPL_CONST                 /* Applications ROM Data               */
#define FLS_APPL_DATA                  /* Applications RAM Data               */
#define FLS_FAST_DATA                  /* Near RAM Data                       */


#define FLS_CONFIG_CONST               /* Desc. Tables -> Config-dependent    */
#define FLS_CONFIG_DATA                /* Config. dependent (reg. size) data  */

#define FLS_INIT_DATA                  /* Data which is initialized during
                                          Startup                             */
#define FLS_NOINIT_DATA                /* Data which is not initialized during
                                          Startup                             */
#define FLS_CONST                      /* Data Constants                      */



/**********************************************************************************************************************
 *  GPT START
 *********************************************************************************************************************/

#define GPT_PUBLIC_CODE                /* API functions                       */
#define GPT_PUBLIC_CONST               /* API constants                       */

#define GPT_PRIVATE_CODE               /* Internal functions                  */
#define GPT_FAST_CODE                  /* Internal functions                  */

#define GPT_PRIVATE_DATA               /* Module internal data                */
#define GPT_PRIVATE_CONST              /* Internal ROM Data                   */

#define GPT_APPL_CODE                  /* callbacks of the Application        */
#define GPT_APPL_CONST                 /* Applications ROM Data               */
#define GPT_APPL_DATA                  /* Applications RAM Data               */
#define GPT_FAST_DATA                  /* Near RAM Data                       */


#define GPT_CONFIG_CONST               /* Desc. Tables -> Config-dependent    */
#define GPT_CONFIG_DATA                /* Config. dependent (reg. size) data  */

#define GPT_INIT_DATA                  /* Data which is initialized during
                                          Startup                             */
#define GPT_NOINIT_DATA                /* Data which is not initialized during
                                          Startup                             */
#define GPT_CONST                      /* Data Constants                      */


/**********************************************************************************************************************
 *  GPT END
 *********************************************************************************************************************/



#define ICU_PUBLIC_CODE                /* API functions                        */
#define ICU_PUBLIC_CONST               /* API constants                        */
#define ICU_PRIVATE_CODE               /* Internal functions                   */
#define ICU_FAST_CODE                  /* Internal functions                   */
#define ICU_PRIVATE_DATA               /* Module internal data                 */
#define ICU_PRIVATE_CONST              /* Internal ROM Data                    */
#define ICU_APPL_CODE                  /* callbacks of the Application         */
#define ICU_APPL_CONST                 /* Applications ROM Data                */
#define ICU_APPL_DATA                  /* Applications RAM Data                */
#define ICU_FAST_DATA                  /* Near RAM Data                        */
#define ICU_CONFIG_CONST               /* Desc. Tables -> Config-dependent     */
#define ICU_CONFIG_DATA                /* Config. dependent (reg. size) data   */
#define ICU_INIT_DATA                  /* Data which is initialized during     */
#define ICU_NOINIT_DATA                /* Data which is not initialized during */
#define ICU_CONST                      /* Data Constants                       */





#define MCU_PUBLIC_CODE                /* API functions                        */
#define MCU_PUBLIC_CONST               /* API constants                        */
#define MCU_PRIVATE_CODE               /* Internal functions                   */
#define MCU_FAST_CODE                  /* Internal functions                   */
#define MCU_PRIVATE_DATA               /* Module internal data                 */
#define MCU_PRIVATE_CONST              /* Internal ROM Data                    */
#define MCU_APPL_CODE                  /* callbacks of the Application         */
#define MCU_APPL_CONST                 /* Applications ROM Data                */
#define MCU_APPL_DATA                  /* Applications RAM Data                */
#define MCU_FAST_DATA                  /* Near RAM Data                        */
#define MCU_CONFIG_CONST               /* Desc. Tables -> Config-dependent     */
#define MCU_CONFIG_DATA                /* Config. dependent (reg. size) data   */
#define MCU_INIT_DATA                  /* Data which is initialized during     */
#define MCU_NOINIT_DATA                /* Data which is not initialized during */
#define MCU_CONST                      /* Data Constants                       */




#define PORT_PUBLIC_CODE                /* API functions                      */
#define PORT_PUBLIC_CONST               /* API constants                      */
#define PORT_PRIVATE_CODE               /* Internal functions                 */
#define PORT_FAST_CODE                  /* Internal functions                 */
#define PORT_PRIVATE_DATA               /* Module internal data               */
#define PORT_PRIVATE_CONST              /* Internal ROM Data                  */
#define PORT_APPL_CODE                  /* callbacks of the Application       */
#define PORT_APPL_CONST                 /* Applications ROM Data             */
#define PORT_APPL_DATA                  /* Applications RAM Data             */
#define PORT_FAST_DATA                  /* Near RAM Data                    */
#define PORT_CONFIG_CONST               /* Desc. Tables -> Config-dependent     */
#define PORT_CONFIG_DATA                /* Config. dependent (reg. size) data   */
#define PORT_INIT_DATA                  /* Data which is initialized during     */
#define PORT_NOINIT_DATA                /* Data which is not initialized during */
#define PORT_CONST                      /* Data Constants                       */



#define PWM_PUBLIC_CODE                /* API functions                         */
#define PWM_PUBLIC_CONST               /* API constants                         */
#define PWM_PRIVATE_CODE               /* Internal functions                    */
#define PWM_FAST_CODE                  /* Internal functions                    */
#define PWM_PRIVATE_DATA               /* Module internal data                  */
#define PWM_PRIVATE_CONST              /* Internal ROM Data                     */
#define PWM_APPL_CODE                  /* callbacks of the Application          */
#define PWM_APPL_CONST                 /* Applications ROM Data                 */
#define PWM_APPL_DATA                  /* Applications RAM Data                 */
#define PWM_FAST_DATA                  /* Near RAM Data                         */
#define PWM_CONFIG_CONST               /* Desc. Tables -> Config-dependent      */
#define PWM_CONFIG_DATA                /* Config. dependent (reg. size) data    */
#define PWM_INIT_DATA                  /* Data which is initialized during      */
#define PWM_NOINIT_DATA                /* Data which is not initialized during  */
#define PWM_CONST                      /* Data Constants                        */




#define SPI_PUBLIC_CODE                /* API functions                       */
#define SPI_PUBLIC_CONST               /* API constants                       */
#define SPI_PRIVATE_CODE               /* Internal functions                  */
#define SPI_FAST_CODE                  /* Internal functions                  */
#define SPI_PRIVATE_DATA               /* Module internal data                */
#define SPI_PRIVATE_CONST              /* Internal ROM Data                   */
#define SPI_APPL_CODE                  /* callbacks of the Application        */
#define SPI_APPL_CONST                 /* Applications ROM Data              */
#define SPI_APPL_DATA                  /* Applications RAM Data              */
#define SPI_FAST_DATA                  /* Near RAM Data                     */
#define SPI_CONFIG_CONST               /* Desc. Tables -> Config-dependent    */
#define SPI_CONFIG_DATA                /* Config. dependent (reg. size) data  */
#define SPI_INIT_DATA                  /* Data which is initialized during Startup */
#define SPI_NOINIT_DATA                /* Data which is not initialized during Startup */
#define SPI_CONST                      /* Data Constants                      */





#define CANTRCV_30_TJA1043_CONST /* PRQA S 0883 */ /* Appears only while testing */
#define CANTRCV_30_TJA1043_VAR
#define CANTRCV_30_TJA1043_VAR_NOINIT
#define CANTRCV_30_TJA1043_APPL_VAR
#define CANTRCV_30_TJA1043_CODE
#define CANTRCV_30_TJA1043_APPL_CODE
#define CANTRCV_30_TJA1043_PBCFG



#define WDG_59_DRIVERA_PUBLIC_CODE        /* API functions                    */
#define WDG_59_DRIVERA_PUBLIC_CONST       /* API constants                    */
#define WDG_59_DRIVERA_PRIVATE_CODE       /* Internal functions               */
#define WDG_59_DRIVERA_FAST_CODE          /* Internal functions               */
#define WDG_59_DRIVERA_PRIVATE_DATA       /* Module internal data             */
#define WDG_59_DRIVERA_PRIVATE_CONST      /* Internal ROM Data                */
#define WDG_59_DRIVERA_APPL_CODE          /* callbacks of the Application     */
#define WDG_59_DRIVERA_APPL_CONST         /* Applications ROM Data           */
#define WDG_59_DRIVERA_APPL_DATA          /* Applications RAM Data           */
#define WDG_59_DRIVERA_FAST_DATA          /* Near RAM Data                  */
#define WDG_59_DRIVERA_CONFIG_CONST       /* Desc. Tables -> Config-dependent */
#define WDG_59_DRIVERA_CONFIG_DATA        /* Config. dependent (reg. size) data */
#define WDG_59_DRIVERA_INIT_DATA          /* Data which is initialized during  Startup */
#define WDG_59_DRIVERA_NOINIT_DATA        /* Data which is not initialized during Startup */
#define WDG_59_DRIVERA_CONST              /* Data Constants                   */


/**********************************************************************************************************************
 *  PDUR START 
 *********************************************************************************************************************/

# define PDUR_CODE
# define PDUR_VAR_NOINIT
# define PDUR_VAR_ZERO_INIT
# define PDUR_VAR
# define PDUR_CONST
# define PDUR_PBCFG
# define PDUR_APPL_DATA
# define PDUR_APPL_CODE
# define PDUR_IPDUM_DATA
# define PDUR_MOST_DATA
# define PDUR_PBCFG_ROOT		PDUR_PBCFG

/**********************************************************************************************************************
 *  PDUR END
 *********************************************************************************************************************/


/*-------------------------------------------------------------------------------------------------------------------*/
/* CANIF                                                                                                             */
/*-------------------------------------------------------------------------------------------------------------------*/


#define CANIF_VAR_NOINIT
#define CANIF_VAR_ZERO_INIT
#define CANIF_VAR_INIT


#define CANIF_CONST
#define CANIF_PBCFG
#define CANIF_PBCFG_ROOT

#define CANIF_CODE


#define CANIF_APPL_CODE
#define CANIF_APPL_VAR
#define CANIF_APPL_PBCFG


/*-------------------------------------------------------------------------------------------------------------------*/

/* Has to be kept in default section -> Default access */
#define CANIF_VAR_STACK


/* VAR section of higher layers (TP / NM / PduR / CanSM / EcuM) automatically mapped to APPL_VAR */
#define CANIF_APPL_STATE_VAR   CANIF_APPL_VAR
#define CANIF_APPL_MSG_VAR     CANIF_APPL_VAR

/* VAR section of lower layers (CAN Driver / Transceiver Driver) automatically mapped to APPL_VAR */
#define CANIF_CBK_VAR          CANIF_APPL_VAR

/* #define CANIF_CBK_TRCV_VAR     CANIF_CBK_VAR    not used yet */
#define CANIF_CBK_DRV_VAR      CANIF_CBK_VAR

/* Code sections - DO NOT MODIFY */
#define CANIF_CBK_TRCV_CODE     CANIF_APPL_CODE
#define CANIF_APPL_STATE_CODE   CANIF_APPL_CODE
#define CANIF_APPL_MSG_CODE     CANIF_APPL_CODE


/* Upper layer data pointer */
#define CANIF_UL_STANDARD_VAR    CANIF_APPL_VAR
#define CANIF_UL_ADVANCED_VAR    CANIF_APPL_VAR
#define CANIF_UL_OSEKNM_VAR      CANIF_APPL_VAR

/*-------------------------------------------------------------------------------------------------------------------*/
/* CANIF                                                                                                             */
/*-------------------------------------------------------------------------------------------------------------------*/




/**********************************************************************************************************************
 *  FEE START 
 *********************************************************************************************************************/

#define FEE_API_CODE
#define FEE_APPL_CODE
#define FEE_APPL_CONFIG
#define FEE_APPL_DATA
#define FEE_CONST
#define FEE_PRIVATE_CODE
#define FEE_PRIVATE_CONST
#define FEE_PRIVATE_DATA
#define FEE_VAR
#define FEE_VAR_NOINIT

/* In ASR4 SchM/RTE declares NvM_MainFunction, using FEE_CODE *
 * It MUST be defined to FEE_API_CODE!                     */
#define FEE_CODE FEE_API_CODE

/**********************************************************************************************************************
 *  FEE END
 *********************************************************************************************************************/


#define MEMIF_CODE
#define MEMIF_CONST
#define MEMIF_APPL_DATA


#define DCMFBL_CODE
#define DCMFBL_APPL_DATA
#define DCMFBL_CONST



/**********************************************************************************************************************
 *  Com START 
 *********************************************************************************************************************/

/* Module Constant Data */
#define COM_CONST
/* Module Constant Data of the Postbuild Configuration */
#define COM_PBCFG
/* Module Root Constant of the Postbuild Configuration */
#define COM_PBCFG_ROOT   COM_PBCFG


/* Module Implementation */
#define COM_CODE

/* Module Variables which are initialized by the startup code or by the call of Com_InitMemory() */
#define COM_VAR_NOINIT
/* Module Variables which are initialized by call of Com_Init() */
#define COM_VAR_INIT

/* Application Code Implementation (e.g. Callbacks) */
#define COM_APPL_CODE
/* Application Buffer which is located in RAM */
#define COM_APPL_VAR
/* Application Buffer which is located in ROM or RAM */
#define COM_APPL_DATA

/**********************************************************************************************************************
 *  Com END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  IpduM START 
 *********************************************************************************************************************/

#define IPDUM_CODE
#define IPDUM_PBCFG
#define IPDUM_VAR_INIT
#define IPDUM_VAR_NOINIT
#define IPDUM_APPL_DATA
#define IPDUM_PBCFG_ROOT                  IPDUM_PBCFG


/**********************************************************************************************************************
 *  IpduM END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  NvM START 
 *********************************************************************************************************************/

#define NVM_APPL_DATA
#define NVM_APPL_CODE
#define NVM_APPL_CONST

#define NVM_CRC_APPL_DATA

#define NVM_CONFIG_DATA
#define NVM_CONFIG_CONST

#define NVM_FAST_DATA

#define NVM_PRIVATE_CODE
#define NVM_PRIVATE_CONST
#define NVM_PRIVATE_DATA

#define NVM_PUBLIC_CODE
#define NVM_PUBLIC_CONST

/**********************************************************************************************************************
 *  NvM END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  DLT START 
 *********************************************************************************************************************/


#define DLT_CODE

#define DLT_CONST

#define DLT_VAR_INIT
#define DLT_VAR_NOINIT
#define DLT_VAR_ZERO_INIT

#define DLT_APPL_VAR
#define DLT_PBCFG


/**********************************************************************************************************************
 *  DLT END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  AMDRTM START 
 *********************************************************************************************************************/

#define AMDRTM_CONST
#define AMDRTM_CODE
#define AMDRTM_VAR
#define AMDRTM_VAR_INIT_8BIT
#define AMDRTM_VAR_INIT_16BIT
#define AMDRTM_VAR_INIT_32BIT
#define AMDRTM_VAR_INIT

/**********************************************************************************************************************
 *  AMDRTM END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  CANNM START 
 *********************************************************************************************************************/

#define CANNM_CODE

#define CANNM_CONST
#define CANNM_PBCFG
#define CANNM_PBCFG_ROOT

#define CANNM_VAR_NOINIT
#define CANNM_VAR_NOINIT_FAST
#define CANNM_VAR_ZERO_INIT_FAST
#define CANNM_APPL_VAR

/**********************************************************************************************************************
 *  CANNM END
 *********************************************************************************************************************/
 



/**********************************************************************************************************************
 *  NM START 
 *********************************************************************************************************************/
 
#define NM_CODE

#define NM_CONST

#define NM_VAR_NOINIT
#define NM_VAR_NOINIT_FAST
#define NM_VAR_ZERO_INIT_FAST
#define NM_APPL_VAR

/**********************************************************************************************************************
 *  NM END
 *********************************************************************************************************************/



/* Inline assembler support for syncp instruction */
#define EXECUTE_SYNCP()           __asm("syncp")

/* Inline assembler support for HALT instruction */
#define ASM_HALT() __asm("halt")

/* Inline assembler support for NOP instruction */
#define ASM_NOP() __asm("nop")

#define _INTERRUPT_  __interrupt

/*Defines for the interrups CAT2 of the ADC */
#define Os_ADC0_SG1_CAT2_ISR
#define Os_ADC0_SG2_CAT2_ISR
#define Os_ADC0_SG3_CAT2_ISR
#define Os_ADC1_SG1_CAT2_ISR
#define Os_ADC1_SG2_CAT2_ISR
#define Os_ADC1_SG3_CAT2_ISR
#define Os_ADC0_ERR_CAT2_ISR
#define Os_ADC_DMA_CH00_CAT2_ISR
#define Os_ADC_DMA_CH01_CAT2_ISR
#define Os_ADC_DMA_CH02_CAT2_ISR
#define Os_ADC_DMA_CH03_CAT2_ISR
#define Os_ADC_DMA_CH04_CAT2_ISR
#define Os_ADC_DMA_CH05_CAT2_ISR
#define Os_ADC_DMA_CH06_CAT2_ISR
#define Os_ADC_DMA_CH07_CAT2_ISR
#define Os_ADC_DMA_CH08_CAT2_ISR
#define Os_ADC_DMA_CH09_CAT2_ISR
#define Os_ADC_DMA_CH10_CAT2_ISR
#define Os_ADC_DMA_CH11_CAT2_ISR
#define Os_ADC_DMA_CH12_CAT2_ISR
#define Os_ADC_DMA_CH13_CAT2_ISR
#define Os_ADC_DMA_CH14_CAT2_ISR
#define Os_ADC_DMA_CH15_CAT2_ISR

/*Defines for the interrups CAT2 of the FLS */
#define Os_FLS_FLERR_CAT2_ISR
#define Os_FLS_FLENDNM_CAT2_ISR

/*Defines for the interrups CAT2 of the GPT */
#define Os_OSTM0_CH00_CAT2_ISR
#define Os_TAUD0_CH00_CAT2_ISR
#define Os_TAUD0_CH01_CAT2_ISR
#define Os_TAUD0_CH02_CAT2_ISR
#define Os_TAUD0_CH03_CAT2_ISR
#define Os_TAUD0_CH04_CAT2_ISR
#define Os_TAUD0_CH05_CAT2_ISR
#define Os_TAUD0_CH06_CAT2_ISR
#define Os_TAUD0_CH07_CAT2_ISR
#define Os_TAUD0_CH08_CAT2_ISR
#define Os_TAUD0_CH09_CAT2_ISR
#define Os_TAUD0_CH10_CAT2_ISR
#define Os_TAUD0_CH11_CAT2_ISR
#define Os_TAUD0_CH12_CAT2_ISR
#define Os_TAUD0_CH13_CAT2_ISR
#define Os_TAUD0_CH14_CAT2_ISR
#define Os_TAUD0_CH15_CAT2_ISR
#define Os_TAUB0_CH00_CAT2_ISR
#define Os_TAUB0_CH01_CAT2_ISR
#define Os_TAUB0_CH02_CAT2_ISR
#define Os_TAUB0_CH03_CAT2_ISR
#define Os_TAUB0_CH04_CAT2_ISR
#define Os_TAUB0_CH05_CAT2_ISR
#define Os_TAUB0_CH06_CAT2_ISR
#define Os_TAUB0_CH07_CAT2_ISR
#define Os_TAUB0_CH08_CAT2_ISR
#define Os_TAUB0_CH09_CAT2_ISR
#define Os_TAUB0_CH10_CAT2_ISR
#define Os_TAUB0_CH11_CAT2_ISR
#define Os_TAUB0_CH12_CAT2_ISR
#define Os_TAUB0_CH13_CAT2_ISR
#define Os_TAUB0_CH14_CAT2_ISR
#define Os_TAUB0_CH15_CAT2_ISR
#define Os_TAUB1_CH00_CAT2_ISR
#define Os_TAUB1_CH01_CAT2_ISR
#define Os_TAUB1_CH02_CAT2_ISR
#define Os_TAUB1_CH03_CAT2_ISR
#define Os_TAUB1_CH04_CAT2_ISR
#define Os_TAUB1_CH05_CAT2_ISR
#define Os_TAUB1_CH06_CAT2_ISR
#define Os_TAUB1_CH07_CAT2_ISR
#define Os_TAUB1_CH08_CAT2_ISR
#define Os_TAUB1_CH09_CAT2_ISR
#define Os_TAUB1_CH10_CAT2_ISR
#define Os_TAUB1_CH11_CAT2_ISR
#define Os_TAUB1_CH12_CAT2_ISR
#define Os_TAUB1_CH13_CAT2_ISR
#define Os_TAUB1_CH14_CAT2_ISR
#define Os_TAUB1_CH15_CAT2_ISR
#define Os_TAUJ0_CH00_CAT2_ISR
#define Os_TAUJ0_CH01_CAT2_ISR
#define Os_TAUJ0_CH02_CAT2_ISR
#define Os_TAUJ0_CH03_CAT2_ISR
#define Os_TAUJ1_CH00_CAT2_ISR
#define Os_TAUJ1_CH01_CAT2_ISR
#define Os_TAUJ1_CH02_CAT2_ISR
#define Os_TAUJ1_CH03_CAT2_ISR


/*Defines for the interrups CAT2 of the ICU */
#define Os_EXT_INTP_CH00_CAT2_ISR
#define Os_EXT_INTP_CH01_CAT2_ISR
#define Os_EXT_INTP_CH02_CAT2_ISR
#define Os_EXT_INTP_CH03_CAT2_ISR
#define Os_EXT_INTP_CH04_CAT2_ISR
#define Os_EXT_INTP_CH05_CAT2_ISR
#define Os_EXT_INTP_CH06_CAT2_ISR
#define Os_EXT_INTP_CH07_CAT2_ISR
#define Os_EXT_INTP_CH08_CAT2_ISR
#define Os_EXT_INTP_CH09_CAT2_ISR
#define Os_EXT_INTP_CH10_CAT2_ISR
#define Os_EXT_INTP_CH11_CAT2_ISR
#define Os_EXT_INTP_CH12_CAT2_ISR
#define Os_EXT_INTP_CH13_CAT2_ISR
#define Os_EXT_INTP_CH14_CAT2_ISR
#define Os_EXT_INTP_CH15_CAT2_ISR
#define Os_TAUD0_CH00_CAT2_ISR
#define Os_TAUD0_CH01_CAT2_ISR
#define Os_TAUD0_CH02_CAT2_ISR
#define Os_TAUD0_CH03_CAT2_ISR
#define Os_TAUD0_CH04_CAT2_ISR
#define Os_TAUD0_CH05_CAT2_ISR
#define Os_TAUD0_CH06_CAT2_ISR
#define Os_TAUD0_CH07_CAT2_ISR
#define Os_TAUD0_CH08_CAT2_ISR
#define Os_TAUD0_CH09_CAT2_ISR
#define Os_TAUD0_CH10_CAT2_ISR
#define Os_TAUD0_CH11_CAT2_ISR
#define Os_TAUD0_CH12_CAT2_ISR
#define Os_TAUD0_CH13_CAT2_ISR
#define Os_TAUD0_CH14_CAT2_ISR
#define Os_TAUD0_CH15_CAT2_ISR
#define Os_TAUB0_CH00_CAT2_ISR
#define Os_TAUB0_CH01_CAT2_ISR
#define Os_TAUB0_CH02_CAT2_ISR
#define Os_TAUB0_CH03_CAT2_ISR
#define Os_TAUB0_CH04_CAT2_ISR
#define Os_TAUB0_CH05_CAT2_ISR
#define Os_TAUB0_CH06_CAT2_ISR
#define Os_TAUB0_CH07_CAT2_ISR
#define Os_TAUB0_CH08_CAT2_ISR
#define Os_TAUB0_CH09_CAT2_ISR
#define Os_TAUB0_CH10_CAT2_ISR
#define Os_TAUB0_CH11_CAT2_ISR
#define Os_TAUB0_CH12_CAT2_ISR
#define Os_TAUB0_CH13_CAT2_ISR
#define Os_TAUB0_CH14_CAT2_ISR
#define Os_TAUB0_CH15_CAT2_ISR
#define Os_TAUB1_CH00_CAT2_ISR
#define Os_TAUB1_CH01_CAT2_ISR
#define Os_TAUB1_CH02_CAT2_ISR
#define Os_TAUB1_CH03_CAT2_ISR
#define Os_TAUB1_CH04_CAT2_ISR
#define Os_TAUB1_CH05_CAT2_ISR
#define Os_TAUB1_CH06_CAT2_ISR
#define Os_TAUB1_CH07_CAT2_ISR
#define Os_TAUB1_CH08_CAT2_ISR
#define Os_TAUB1_CH09_CAT2_ISR
#define Os_TAUB1_CH10_CAT2_ISR
#define Os_TAUB1_CH11_CAT2_ISR
#define Os_TAUB1_CH12_CAT2_ISR
#define Os_TAUB1_CH13_CAT2_ISR
#define Os_TAUB1_CH14_CAT2_ISR
#define Os_TAUB1_CH15_CAT2_ISR
#define Os_TAUJ0_CH00_CAT2_ISR
#define Os_TAUJ0_CH01_CAT2_ISR
#define Os_TAUJ0_CH02_CAT2_ISR
#define Os_TAUJ0_CH03_CAT2_ISR
#define Os_TAUJ1_CH00_CAT2_ISR
#define Os_TAUJ1_CH01_CAT2_ISR
#define Os_TAUJ1_CH02_CAT2_ISR
#define Os_TAUJ1_CH03_CAT2_ISR

/*Defines for the interrups CAT2 of the MCU */
#define Os_MCU_FEINT_CAT2_ISR
#define Os_MCU_INTCWEND_CAT2_ISR

/*Defines for the interrups CAT2 of the SPI */
#define Os_SPI_CSIG0_TIC_CAT2_ISR
#define Os_SPI_CSIG0_TIR_CAT2_ISR
#define Os_SPI_CSIG0_TIRE_CAT2_ISR
#define Os_SPI_CSIG1_TIC_CAT2_ISR
#define Os_SPI_CSIG1_TIR_CAT2_ISR
#define Os_SPI_CSIG1_TIRE_CAT2_ISR
#define Os_SPI_CSIG2_TIC_CAT2_ISR
#define Os_SPI_CSIG2_TIR_CAT2_ISR
#define Os_SPI_CSIG2_TIRE_CAT2_ISR
#define Os_SPI_CSIG3_TIC_CAT2_ISR
#define Os_SPI_CSIG3_TIR_CAT2_ISR
#define Os_SPI_CSIG3_TIRE_CAT2_ISR
#define Os_SPI_CSIG4_TIC_CAT2_ISR
#define Os_SPI_CSIG4_TIR_CAT2_ISR
#define Os_SPI_CSIG4_TIRE_CAT2_ISR
#define Os_SPI_CSIG5_TIC_CAT2_ISR
#define Os_SPI_CSIG5_TIR_CAT2_ISR
#define Os_SPI_CSIG5_TIRE_CAT2_ISR
#define Os_SPI_CSIG6_TIC_CAT2_ISR
#define Os_SPI_CSIG6_TIR_CAT2_ISR
#define Os_SPI_CSIG6_TIRE_CAT2_ISR
#define Os_SPI_CSIG7_TIC_CAT2_ISR
#define Os_SPI_CSIG7_TIR_CAT2_ISR
#define Os_SPI_CSIG7_TIRE_CAT2_ISR
#define Os_SPI_CSIH0_TIC_CAT2_ISR
#define Os_SPI_CSIH0_TIJC_CAT2_ISR
#define Os_SPI_CSIH0_TIR_CAT2_ISR
#define Os_SPI_CSIH0_TIRE_CAT2_ISR
#define Os_SPI_CSIH1_TIC_CAT2_ISR
#define Os_SPI_CSIH1_TIJC_CAT2_ISR
#define Os_SPI_CSIH1_TIR_CAT2_ISR
#define Os_SPI_CSIH1_TIRE_CAT2_ISR
#define Os_SPI_CSIH3_TIC_CAT2_ISR
#define Os_SPI_CSIH3_TIJC_CAT2_ISR
#define Os_SPI_CSIH3_TIR_CAT2_ISR
#define Os_SPI_CSIH3_TIRE_CAT2_ISR
#define Os_SPI_DMA00_CAT2_ISR
#define Os_SPI_DMA01_CAT2_ISR
#define Os_SPI_DMA02_CAT2_ISR
#define Os_SPI_DMA03_CAT2_ISR
#define Os_SPI_DMA04_CAT2_ISR
#define Os_SPI_DMA05_CAT2_ISR
#define Os_SPI_DMA06_CAT2_ISR
#define Os_SPI_DMA07_CAT2_ISR
#define Os_SPI_DMA08_CAT2_ISR
#define Os_SPI_DMA09_CAT2_ISR
#define Os_SPI_DMA10_CAT2_ISR
#define Os_SPI_DMA11_CAT2_ISR
#define Os_SPI_DMA12_CAT2_ISR
#define Os_SPI_DMA13_CAT2_ISR
#define Os_SPI_DMA14_CAT2_ISR
#define Os_SPI_DMA15_CAT2_ISR

/*Defines for the interrups CAT2 of the WDG */
#define Os_WDG_59_DRIVERA_TRIGGERFUNCTION_CAT2_ISR
#define Os_WDG_59_DRIVERA_ERROR_CAT2_ISR



/**********************************************************************************************************************
 *  BSWM START 
 *********************************************************************************************************************/

#define BSWM_CODE
#define BSWM_APPL_CODE
#define BSWM_CONST
#define BSWM_PBCFG
#define BSWM_VAR_INIT
#define BSWM_APPL_DATA
#define BSWM_VAR_NOINIT

/**********************************************************************************************************************
 *  BSWM END
 *********************************************************************************************************************/


#define CRC_APPL_DATA
#define CRC_CODE
#define CRC_CONST



# define DET_CODE
# define DET_VAR
# define DET_APPL_DATA
# define DET_APPL_CODE




/**********************************************************************************************************************
 *  SYSSERVICE_ASRECUM START 
 *********************************************************************************************************************/
#define ECUM_API_CODE 
#define ECUM_APPL_CONFIG 
#define ECUM_APPL_DATA 
#define ECUM_VAR_BOOT
#define ECUM_CODE
#define ECUM_CODE_BOOT_TARGET 
#define ECUM_CONST 
#define ECUM_PBCFG
#define ECUM_VAR 
#define ECUM_VAR_NOINIT 

/**********************************************************************************************************************
 *  SYSSERVICE_ASRECUM END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  SchM START 
 *********************************************************************************************************************/

/* Module Constant Data */
#define SCHM_CONST

/* Module Implementation */
#define SCHM_CODE

/* Module Variables which are not initialized by the startup code of the compiler */
#define SCHM_VAR_NOINIT

/* Module Global or static variables that are initialized with zero by the startup code of the compiler or in SchM_InitMemory */
#define SCHM_VAR_ZERO_INIT

/**********************************************************************************************************************
 *  SchM END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  CANTP START
 *********************************************************************************************************************/

#define CANTP_VAR_INIT
#define CANTP_VAR_NOINIT
#define CANTP_CONST
#define CANTP_APPL_CONST
#define CANTP_CODE
#define CANTP_APPL_CODE
#define CANTP_APPL_DATA
#define CANTP_PBCFG

/**********************************************************************************************************************
 *  CANTP END
 *********************************************************************************************************************/


/*-------------------------------------------------------------------------------------------------------------------*/
/* VStdLib start compiler_cfg                                                                                        */
/*-------------------------------------------------------------------------------------------------------------------*/

#define VSTDLIB_CODE                               /* VStdLib modules code qualifier                                                                        */
#define VSTDLIB_CONST                              /* constant memory                                                                                       */
#define VSTDLIB_VAR_NEAR                           /* near variables: this is the pointer clas for "pOldState" parameter of VStdLL_GlobalInterruptDisable() */
#define VSTDLIB_CONST_FAR                          /* far constant memory: can remain empty if the application is not using FAR data (neither ROM nor RAM)  */
#define VSTDLIB_VAR_FAR                            /* far variables: can remain empty if the application is not using FAR data (neither ROM nor RAM)        */
#define VSTDLIB_VAR_NOINIT

/*-------------------------------------------------------------------------------------------------------------------*/
/* VStdLib end compiler_cfg                                                                                          */
/*-------------------------------------------------------------------------------------------------------------------*/




/* Package Merger: Stop Section CompilerCfgModuleList */

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


#endif  /* COMPILER_CFG_H */

/**********************************************************************************************************************
 *  END OF FILE: Compiler_Cfg.h
 *********************************************************************************************************************/
