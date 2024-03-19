/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  Copyright (c) 2006-2015 by Vector Informatik GmbH.                                             All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Rte.c
 *     Workspace:  C:/_TSS/DAG/MFA2/Target/Config/Developer/HufTPMS_G6_F1L.dev
 *   ECU-Project:  TPM
 *  Generated at:  Fri Dec 15 13:11:50 2017
 *
 *     Generator:  MICROSAR RTE Generator Version 2.27.0
 *                 RTE Core Version 1.6.0
 *       License:  License CBD1500122 valid for Huf Electronics Bretten GmbH Package: MSR Daimler SLP10 Micro: R7F7010133AFP Compiler: Green Hills 6.1.4
 *
 *   Description:  RTE implementation file
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* PRQA S 0777, 0779, 0781, 0857 EOF */ /* MD_Rte_0777, MD_Rte_0779, MD_Rte_0781, MD_MSR_1.1_857 */

#define RTE_CORE
#include "Os.h" /* PRQA S 0828, 0883 */ /* MD_MSR_1.1_828, MD_Rte_Os */
#include "Rte_Type.h"
#include "Rte_Main.h"

#include "Rte_ComM.h"
#include "Rte_CtApHufTPMSdia.h"
#include "Rte_CtApHufTPMSmgr.h"
#include "Rte_CtApHufTPMSroe.h"
#include "Rte_CtApHufTPMSwnh.h"
#include "Rte_CtApHufTPMSwpa.h"
#include "Rte_CtCdHufTPMSrfd.h"
#include "Rte_NvM.h"
#include "Rte_OHDSCanSlave.h"

#include "Rte_Hook.h"

#include "Com.h"

/* Com.h Compatibility Check */
#ifndef RTE_COM_VERSION
# if defined (IL_VECTOR_VERSION)
#  define RTE_COM_VERSION 20U
# else
#  if defined (IL_ASRCOM_VERSION)
#   if (IL_ASRCOM_VERSION < 0x0201U)
#    define RTE_COM_VERSION 20U
#   endif
#  endif
# endif
# if defined (COM_AR_MAJOR_VERSION) && defined (COM_AR_MINOR_VERSION)
#  define RTE_COM_VERSION ((COM_AR_MAJOR_VERSION * 10) + COM_AR_MINOR_VERSION)
# endif
#endif
#ifndef RTE_COM_VERSION
# define RTE_COM_VERSION 33U
#endif

#if (RTE_COM_VERSION == 20U) || (RTE_COM_VERSION == 21U)
# define RTE_COM_SENDCAST(x) (x)
#else
# define RTE_COM_SENDCAST(x)
#endif

#if defined(IL_VECTOR_VERSION) || defined(IL_ASRCOM_VERSION)
# define RTE_USE_COM_TXSIGNAL_RDACCESS
#endif

#include "Rte_Cbk.h"

/* AUTOSAR 2.1 compatibility */
#if !defined (STATIC) && defined (_STATIC_)
# define STATIC _STATIC_
#endif

#ifndef V_USE_DUMMY_STATEMENT
# define V_USE_DUMMY_STATEMENT STD_OFF
#endif

/**********************************************************************************************************************
 * API for enable / disable interrupts global
 *********************************************************************************************************************/

#ifdef osRteDisableGlobal
# define Rte_DisableAllInterrupts() osRteDisableGlobal()   /* MICROSAR OS */
#else
# define Rte_DisableAllInterrupts() DisableAllInterrupts()   /* AUTOSAR OS */
#endif

#ifdef osRteEnableGlobal
# define Rte_EnableAllInterrupts() osRteEnableGlobal()   /* MICROSAR OS */
#else
# define Rte_EnableAllInterrupts() EnableAllInterrupts()   /* AUTOSAR OS */
#endif

/**********************************************************************************************************************
 * API for enable / disable interrupts up to the systemLevel
 *********************************************************************************************************************/

#ifdef osRteDisableLevel
# define Rte_DisableOSInterrupts() osRteDisableLevel()   /* MICROSAR OS */
#else
# define Rte_DisableOSInterrupts() SuspendOSInterrupts()   /* AUTOSAR OS */
#endif

#ifdef osRteEnableLevel
# define Rte_EnableOSInterrupts() osRteEnableLevel()   /* MICROSAR OS */
#else
# define Rte_EnableOSInterrupts() ResumeOSInterrupts()   /* AUTOSAR OS */
#endif

/**********************************************************************************************************************
 * Rte Init State Variable
 *********************************************************************************************************************/

#define RTE_START_SEC_VAR_ZERO_INIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

VAR(uint8, RTE_VAR_ZERO_INIT) Rte_InitState = RTE_STATE_UNINIT; /* PRQA S 0850, 3408 */ /* MD_MSR_19.8, MD_Rte_3408 */

#define RTE_STOP_SEC_VAR_ZERO_INIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/**********************************************************************************************************************
 * Buffers for unqueued S/R
 *********************************************************************************************************************/

#define RTE_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

VAR(DT_tEnvData, RTE_VAR_NOINIT) Rte_CpApHufTPMSmgr_PP_EnvData_DE_tEnvData; /* PRQA S 0850, 3408, 1504 */ /* MD_MSR_19.8, MD_Rte_3408, MD_MSR_8.10 */
VAR(DT_auRfStruct, RTE_VAR_NOINIT) Rte_CpApHufTPMSmgr_PP_RfStructOut_DE_auRfStruct; /* PRQA S 0850, 3408, 1504 */ /* MD_MSR_19.8, MD_Rte_3408, MD_MSR_8.10 */
VAR(DT_ushWarnOut, RTE_VAR_NOINIT) Rte_CpApHufTPMSwnh_PP_WarnOut_DE_ushWarnOut; /* PRQA S 0850, 3408, 1504 */ /* MD_MSR_19.8, MD_Rte_3408, MD_MSR_8.10 */
VAR(DT_ushWAState, RTE_VAR_NOINIT) Rte_CpApHufTPMSwpa_PP_WAState_DE_ushWAState; /* PRQA S 0850, 3408, 1504 */ /* MD_MSR_19.8, MD_Rte_3408, MD_MSR_8.10 */
VAR(DT_auRfStruct, RTE_VAR_NOINIT) Rte_CpCdHufTPMSrfd_PP_RfStruct_DE_auRfStruct; /* PRQA S 0850, 3408, 1504 */ /* MD_MSR_19.8, MD_Rte_3408, MD_MSR_8.10 */

#define RTE_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/**********************************************************************************************************************
 * Constants
 *********************************************************************************************************************/

#define RTE_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* PRQA S 0850 L1 */ /* MD_MSR_19.8 */
CONST(ARR_08_UInt_noSNA_8, RTE_CONST) Rte_XDIS_bzm3suyimc3lnij4fzlwpgwm4 = {
  0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U
};
/* PRQA L:L1 */
/* PRQA S 0850 L1 */ /* MD_MSR_19.8 */
CONST(DT_auRfStruct, RTE_CONST) Rte_C_aucRfStruct = {
  0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 
  0U, 0U, 0U, 0U, 0U
};
/* PRQA L:L1 */
/* PRQA S 0850 L1 */ /* MD_MSR_19.8 */
CONST(DT_tEnvData, RTE_CONST) Rte_C_tEnvData = {
  0U, 0U, 0U, 0U, 0U, 0U
};
/* PRQA L:L1 */
/* PRQA S 0850 L1 */ /* MD_MSR_19.8 */
CONST(REC_DateTm_AR2_f0ifkphxunpp94u3ro8qn5tdm, RTE_CONST) Rte_XDIS_8oeobqbbrmj8fyiongo6ax1xv = {
  255U, 255U, 255U, 255U, 255U, 7U, 255U
};
/* PRQA L:L1 */
/* PRQA S 0850 L1 */ /* MD_MSR_19.8 */
CONST(REC_EVC_CfgBit_01_32_Pr2_d23bad5cnts3f65mtgoqoxmrz, RTE_CONST) Rte_XDIS_9rt50469dx6jveycvwiekru9s = {
  3U, FALSE, FALSE, FALSE
};
/* PRQA L:L1 */
/* PRQA S 0850 L1 */ /* MD_MSR_19.8 */
CONST(REC_EVC_CfgList_01_0C_Pr2_ah3rxaqpfvlnju8848jpspm9p, RTE_CONST) Rte_XDIS_69nqj71u0pbksk5hjvodygwvd = {
  31U, 3U, 7U, 63U
};
/* PRQA L:L1 */
/* PRQA S 0850 L1 */ /* MD_MSR_19.8 */
CONST(REC_Eng_Rs_EngCtrl_Pr2_1j00gxu3p5exa8awg915k1zy, RTE_CONST) Rte_XDIS_b1gz9poycm6ddxgidqfjet2pv = {
  7U
};
/* PRQA L:L1 */
/* PRQA S 0850 L1 */ /* MD_MSR_19.8 */
CONST(REC_Ign_Stat_Pr2_71njeubj9ico1p8v4pmslfcno, RTE_CONST) Rte_XDIS_a24im2m55sztow8orofz1re4l = {
  7U, FALSE
};
/* PRQA L:L1 */
/* PRQA S 0850 L1 */ /* MD_MSR_19.8 */
CONST(REC_Ign_Stat_Pr2_b0ko81o0x5jgvwtduf99gvzi0, RTE_CONST) Rte_XDIS_9d6x34bvkzvn1spi8e3620s3f = {
  7U
};
/* PRQA L:L1 */
/* PRQA S 0850 L1 */ /* MD_MSR_19.8 */
CONST(REC_PN14_SupBat_Stat_2is6fi0meeac78nkn35zc5ui3, RTE_CONST) Rte_XDIS_63893tj3bpxgywawhjj46oa1d = {
  0U, 255U
};
/* PRQA L:L1 */
/* PRQA S 0850 L1 */ /* MD_MSR_19.8 */
CONST(REC_ROE_XX, RTE_CONST) Rte_XDIS_cduaikm94dzygis49e7i8n2vd = {
  0U, 0U, 940295U
};
/* PRQA L:L1 */
/* PRQA S 0850 L1 */ /* MD_MSR_19.8 */
CONST(REC_RefPress, RTE_CONST) Rte_XDIS_5lnq4pgpv2f92y9v99h1532rc = {
  0U, 0U
};
/* PRQA L:L1 */
/* PRQA S 0850 L1 */ /* MD_MSR_19.8 */
CONST(REC_TPM_Lmp_On_Rq_Pr2_cp6wyrd9cg7ec7y2w3khz1gyt, RTE_CONST) Rte_XDIS_agb15wb9uilg0ni8bte2ez7oc = {
  61U, 0U, 0U, FALSE, FALSE
};
/* PRQA L:L1 */
/* PRQA S 0850 L1 */ /* MD_MSR_19.8 */
CONST(REC_TPM_Lmp_On_Rq_old, RTE_CONST) Rte_XDIS_1d7ph8epnzfwmb1z8ubz5caiq = {
  FALSE, FALSE
};
/* PRQA L:L1 */
/* PRQA S 0850 L1 */ /* MD_MSR_19.8 */
CONST(REC_Tire_Stat_V2, RTE_CONST) Rte_XDIS_c887fxti3dvrcxpco5w1om6lw = {
  FALSE, 255U, 255U, 255U, 255U, 0U, 0U, 0U, 0U, 0U, 0U, 7U
};
/* PRQA L:L1 */
/* PRQA S 0850 L1 */ /* MD_MSR_19.8 */
CONST(REC_Tire_Temp_V2, RTE_CONST) Rte_XDIS_17gsj8drc9emz51ybjnyn4din = {
  0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U
};
/* PRQA L:L1 */
/* PRQA S 0850 L1 */ /* MD_MSR_19.8 */
CONST(REC_WhlPlsCnt_TPM_Pr2_5hishd08ma5z1luev78umdwvx, RTE_CONST) Rte_XDIS_3bcpjgb37kcc1t679g9053jt5 = {
  63U, 0U, 0U, 255U, 255U, 255U, 255U, 0U, 0U
};
/* PRQA L:L1 */

#define RTE_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/**********************************************************************************************************************
 * Calibration Parameters (SW-C local and calibration component calibration parameters)
 *********************************************************************************************************************/

#define RTE_START_SEC_CONST_DEFAULT_RTE_CDATA_GROUP_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* PRQA S 0850, 3408 L1 */ /* MD_MSR_19.8, MD_Rte_3408 */
CONST(DT_tDiagNvMBlock0, RTE_CONST_DEFAULT_RTE_CDATA_GROUP) Rte_CtApHufTPMSdia_Cal_tDiagNvMBlock0_DefaultValue = {
  {0U, 0U, 0U, 0U}, {0U, 0U, 0U, 0U}, {0U, 3U, 31U, 7U, 63U, 3U, 0U, 0U, 0U, 0U}, {0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 
  0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 
  0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U}, {0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U}, {0U, 0U, 0U, 
  0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 
  0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U}, {0U, 0U, 0U, 0U}, {
  0U, 0U, 0U, 0U}, {0U, 0U, 0U, 0U}, {0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U}, {0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 
  0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U}, {7U, 
  7U, 7U, 7U}
};
/* PRQA L:L1 */
/* PRQA S 0850, 3408 L1 */ /* MD_MSR_19.8, MD_Rte_3408 */
CONST(DT_tDiagNvMBlock1, RTE_CONST_DEFAULT_RTE_CDATA_GROUP) Rte_CtApHufTPMSdia_Cal_tDiagNvMBlock1_DefaultValue = {
  {0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U}, 0U, {0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 
  0U, 0U, 0U, 0U, 0U}
};
/* PRQA L:L1 */
/* PRQA S 0850, 3408 L1 */ /* MD_MSR_19.8, MD_Rte_3408 */
CONST(DT_tDiagNvMBlock2, RTE_CONST_DEFAULT_RTE_CDATA_GROUP) Rte_CtApHufTPMSdia_Cal_tDiagNvMBlock2_DefaultValue = {
  {1U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 2U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 3U, 0U, 0U, 0U, 0U, 0U, 0U, 
  0U, 0U, 0U, 0U, 4U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U}, {0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 
  0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 
  0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 
  0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U}, {0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 
  0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 
  0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 
  0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U}
};
/* PRQA L:L1 */
/* PRQA S 0850, 3408 L1 */ /* MD_MSR_19.8, MD_Rte_3408 */
CONST(DT_tDiagNvMBlock3, RTE_CONST_DEFAULT_RTE_CDATA_GROUP) Rte_CtApHufTPMSdia_Cal_tDiagNvMBlock3_DefaultValue = {
  {0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 255U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 
  0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 255U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 255U, 
  0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 255U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 
  0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 255U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U}, 0U, {0U, 0U, 0U, 0U, 0U, 
  0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U}
};
/* PRQA L:L1 */
/* PRQA S 0850, 3408 L1 */ /* MD_MSR_19.8, MD_Rte_3408 */
CONST(DT_tCalNvMBlock, RTE_CONST_DEFAULT_RTE_CDATA_GROUP) Rte_CtApHufTPMSmgr_Cal_tCalNvMBlock_DefaultValue = {
  {76U, 76U, 76U, 76U}, 4294967295U, 76U, 76U, 20, 0U, 0U, {0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 
  0U, 0U, 0U, 0U, 0U}
};
/* PRQA L:L1 */
/* PRQA S 0850, 3408 L1 */ /* MD_MSR_19.8, MD_Rte_3408 */
CONST(DT_tCodNvMBlock, RTE_CONST_DEFAULT_RTE_CDATA_GROUP) Rte_CtApHufTPMSmgr_Cal_tCodNvMBlock_DefaultValue = {
  {60U, 1U, 8U, 14U, 4U, 20U, 1U}, {120U, 170U, 200U, 70, 75, 80, 600U}, 76U, 76U, {1U, 15U}, 0U, 0U, 30U, {20U, 0U, 
  0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U}
};
/* PRQA L:L1 */
/* PRQA S 0850, 3408 L1 */ /* MD_MSR_19.8, MD_Rte_3408 */
CONST(DT_tWarnHdlrNvMBlock, RTE_CONST_DEFAULT_RTE_CDATA_GROUP) Rte_CtApHufTPMSwnh_Cal_tWarnHdlrNvMBlock_DefaultValue = {
  {0U}, {0U, 0U, 0U, 0U, 0U}, {0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U}
};
/* PRQA L:L1 */
/* PRQA S 0850, 3408 L1 */ /* MD_MSR_19.8, MD_Rte_3408 */
CONST(DT_tWallocNvMBlock, RTE_CONST_DEFAULT_RTE_CDATA_GROUP) Rte_CtApHufTPMSwpa_Cal_tWallocNvMBlock_DefaultValue = {
  {0U, 100U}, {0U, 1U, 2U, 3U}, {0U, 1U, 2U, 3U}, {1U, 2U, 3U, 4U}, 0U, {0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 
  0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U}
};
/* PRQA L:L1 */

#define RTE_STOP_SEC_CONST_DEFAULT_RTE_CDATA_GROUP_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/**********************************************************************************************************************
 * Per-Instance Memory
 *********************************************************************************************************************/

#define RTE_START_SEC_VAR_DEFAULT_RTE_PIM_GROUP_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

VAR(DT_tDiagNvMBlock0, RTE_VAR_DEFAULT_RTE_PIM_GROUP) Rte_CpApHufTPMSdia_Pim_tDiagNvMBlock0; /* PRQA S 0850, 3408, 1504 */ /* MD_MSR_19.8, MD_Rte_3408, MD_MSR_8.10 */
VAR(DT_tDiagNvMBlock1, RTE_VAR_DEFAULT_RTE_PIM_GROUP) Rte_CpApHufTPMSdia_Pim_tDiagNvMBlock1; /* PRQA S 0850, 3408, 1504 */ /* MD_MSR_19.8, MD_Rte_3408, MD_MSR_8.10 */
VAR(DT_tDiagNvMBlock2, RTE_VAR_DEFAULT_RTE_PIM_GROUP) Rte_CpApHufTPMSdia_Pim_tDiagNvMBlock2; /* PRQA S 0850, 3408, 1504 */ /* MD_MSR_19.8, MD_Rte_3408, MD_MSR_8.10 */
VAR(DT_tDiagNvMBlock3, RTE_VAR_DEFAULT_RTE_PIM_GROUP) Rte_CpApHufTPMSdia_Pim_tDiagNvMBlock3; /* PRQA S 0850, 3408, 1504 */ /* MD_MSR_19.8, MD_Rte_3408, MD_MSR_8.10 */
VAR(DT_tCalNvMBlock, RTE_VAR_DEFAULT_RTE_PIM_GROUP) Rte_CpApHufTPMSmgr_Pim_tCalNvMBlock; /* PRQA S 0850, 3408, 1504 */ /* MD_MSR_19.8, MD_Rte_3408, MD_MSR_8.10 */
VAR(DT_tCodNvMBlock, RTE_VAR_DEFAULT_RTE_PIM_GROUP) Rte_CpApHufTPMSmgr_Pim_tCodNvMBlock; /* PRQA S 0850, 3408, 1504 */ /* MD_MSR_19.8, MD_Rte_3408, MD_MSR_8.10 */
VAR(DT_tWarnHdlrNvMBlock, RTE_VAR_DEFAULT_RTE_PIM_GROUP) Rte_CpApHufTPMSwnh_Pim_tWarnHdlrNvMBlock; /* PRQA S 0850, 3408, 1504 */ /* MD_MSR_19.8, MD_Rte_3408, MD_MSR_8.10 */
VAR(DT_tWallocNvMBlock, RTE_VAR_DEFAULT_RTE_PIM_GROUP) Rte_CpApHufTPMSwpa_Pim_tWallocNvMBlock; /* PRQA S 0850, 3408, 1504 */ /* MD_MSR_19.8, MD_Rte_3408, MD_MSR_8.10 */

#define RTE_STOP_SEC_VAR_DEFAULT_RTE_PIM_GROUP_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/**********************************************************************************************************************
 * Timeout Flags for each external Rx Signals with aliveTimeout != 0
 *********************************************************************************************************************/

#define RTE_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

VAR(Rte_RxTimeoutFlagsType, RTE_VAR_ZERO_INIT) Rte_RxTimeoutFlags = {
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0
}; /* PRQA S 0850 */ /* MD_MSR_19.8 */

#define RTE_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define Rte_RxTimeoutFlagsInit() (Rte_MemClr(&Rte_RxTimeoutFlags, sizeof(Rte_RxTimeoutFlagsType)))


/**********************************************************************************************************************
 * Buffer for inter-runnable variables
 *********************************************************************************************************************/

#define RTE_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

VAR(Boolean, RTE_VAR_NOINIT) Rte_Irv_CpApHufTPMSmgr_IRV_TpmActvRq_TpmMsgDispRq; /* PRQA S 0850, 3408, 1504 */ /* MD_MSR_19.8, MD_Rte_3408, MD_MSR_8.10 */

#define RTE_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#define RTE_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

STATIC FUNC(void, RTE_CODE) Rte_MemClr(P2VAR(void, AUTOMATIC, RTE_VAR_NOINIT) ptr, uint16_least num); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(void, RTE_CODE) Rte_MemCpy(P2VAR(void, AUTOMATIC, RTE_APPL_VAR) destination, P2CONST(void, AUTOMATIC, RTE_APPL_DATA) source, uint16_least num); /* PRQA S 0850, 1505, 3447, 3408 */ /* MD_MSR_19.8, MD_MSR_8.10, MD_Rte_3447, MD_Rte_3408 */
FUNC(void, RTE_CODE) Rte_MemCpy32(P2VAR(void, AUTOMATIC, RTE_APPL_VAR) destination, P2CONST(void, AUTOMATIC, RTE_APPL_DATA) source, uint16_least num); /* PRQA S 0850, 1505, 3447, 3408 */ /* MD_MSR_19.8, MD_MSR_8.10, MD_Rte_3447, MD_Rte_3408 */

#define RTE_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/**********************************************************************************************************************
 * Timer handling
 *********************************************************************************************************************/

#if defined(RTE_OSTICKDURATION)
# define RTE_TICKDURATION (RTE_OSTICKDURATION / 1000U)
#elif defined OSTICKDURATION
# define RTE_TICKDURATION (OSTICKDURATION / 1000U)
#else
# error "Please define RTE_OSTICKDURATION in ns e.g. by command line argument when compilation of the RTE files."
#endif

#if (RTE_TICKDURATION <= 0)
# error "The MICROSAR RTE does not support RTE_OSTICKDURATION < 1000 ns"
#endif

#define RTE_USEC(val) ((TickType)((uint32)(val) / (uint32)RTE_TICKDURATION)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#define RTE_MSEC(val) ((TickType)RTE_CONST_MSEC_##val) /* PRQA S 0342 */ /* MD_Rte_0342 */
#define RTE_SEC(val)  ((TickType)RTE_CONST_SEC_##val) /* PRQA S 0342 */ /* MD_Rte_0342 */

#define RTE_MSEC_BASE 1000UL
#define RTE_SEC_BASE  1000000UL

#if ((0) < (0xFFFFFFFFUL / RTE_MSEC_BASE))
# define RTE_CONST_MSEC_0 (((uint32)(0) * RTE_MSEC_BASE) / (uint32)RTE_TICKDURATION)
#else
# if (RTE_TICKDURATION > RTE_MSEC_BASE)
#  define RTE_CONST_MSEC_0 ((uint32)(0) / ((uint32)RTE_TICKDURATION / RTE_MSEC_BASE))
# else
#  define RTE_CONST_MSEC_0 ((uint32)(0) * (RTE_MSEC_BASE / (uint32)RTE_TICKDURATION))
# endif
#endif

#if ((10) < (0xFFFFFFFFUL / RTE_MSEC_BASE))
# define RTE_CONST_MSEC_10 (((uint32)(10) * RTE_MSEC_BASE) / (uint32)RTE_TICKDURATION)
#else
# if (RTE_TICKDURATION > RTE_MSEC_BASE)
#  define RTE_CONST_MSEC_10 ((uint32)(10) / ((uint32)RTE_TICKDURATION / RTE_MSEC_BASE))
# else
#  define RTE_CONST_MSEC_10 ((uint32)(10) * (RTE_MSEC_BASE / (uint32)RTE_TICKDURATION))
# endif
#endif

#if ((200) < (0xFFFFFFFFUL / RTE_MSEC_BASE))
# define RTE_CONST_MSEC_200 (((uint32)(200) * RTE_MSEC_BASE) / (uint32)RTE_TICKDURATION)
#else
# if (RTE_TICKDURATION > RTE_MSEC_BASE)
#  define RTE_CONST_MSEC_200 ((uint32)(200) / ((uint32)RTE_TICKDURATION / RTE_MSEC_BASE))
# else
#  define RTE_CONST_MSEC_200 ((uint32)(200) * (RTE_MSEC_BASE / (uint32)RTE_TICKDURATION))
# endif
#endif

#if ((50) < (0xFFFFFFFFUL / RTE_MSEC_BASE))
# define RTE_CONST_MSEC_50 (((uint32)(50) * RTE_MSEC_BASE) / (uint32)RTE_TICKDURATION)
#else
# if (RTE_TICKDURATION > RTE_MSEC_BASE)
#  define RTE_CONST_MSEC_50 ((uint32)(50) / ((uint32)RTE_TICKDURATION / RTE_MSEC_BASE))
# else
#  define RTE_CONST_MSEC_50 ((uint32)(50) * (RTE_MSEC_BASE / (uint32)RTE_TICKDURATION))
# endif
#endif

#if ((0) < (0xFFFFFFFFUL / RTE_SEC_BASE))
# define RTE_CONST_SEC_0 (((uint32)(0) * RTE_SEC_BASE) / (uint32)RTE_TICKDURATION)
#else
# if (RTE_TICKDURATION > RTE_SEC_BASE)
#  define RTE_CONST_SEC_0 ((uint32)(0) / ((uint32)RTE_TICKDURATION / RTE_SEC_BASE))
# else
#  define RTE_CONST_SEC_0 ((uint32)(0) * (RTE_SEC_BASE / (uint32)RTE_TICKDURATION))
# endif
#endif

#if ((1) < (0xFFFFFFFFUL / RTE_SEC_BASE))
# define RTE_CONST_SEC_1 (((uint32)(1) * RTE_SEC_BASE) / (uint32)RTE_TICKDURATION)
#else
# if (RTE_TICKDURATION > RTE_SEC_BASE)
#  define RTE_CONST_SEC_1 ((uint32)(1) / ((uint32)RTE_TICKDURATION / RTE_SEC_BASE))
# else
#  define RTE_CONST_SEC_1 ((uint32)(1) * (RTE_SEC_BASE / (uint32)RTE_TICKDURATION))
# endif
#endif


/**********************************************************************************************************************
 * Internal definitions
 *********************************************************************************************************************/

#define RTE_TASK_TIMEOUT_EVENT_MASK   ((EventMaskType)0x01)
#define RTE_TASK_WAITPOINT_EVENT_MASK ((EventMaskType)0x02)

/**********************************************************************************************************************
 * RTE life cycle API
 *********************************************************************************************************************/

#define RTE_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if (RTE_TICKDURATION > (50UL * 1000UL))
# error "The cycle time of runnable(s) <RCtCdHufTPMSrfd_ChkRfStruct> is smaller than the tick time of the operating system."
#endif

#if (RTE_TICKDURATION > (10UL * 1000UL))
# error "The cycle time of runnable(s) <RCtApHufTPMSmgr_WrDisplayMsg> is smaller than the tick time of the operating system."
#endif

#if (RTE_TICKDURATION > (10UL * 1000UL))
# error "The cycle time of runnable(s) <RCtApHufTPMSmgr_GenInternalClock> is smaller than the tick time of the operating system."
#endif

#if (RTE_TICKDURATION > (1UL * 1000000UL))
# error "The cycle time of runnable(s) <RCtApHufTPMSmgr_WrTpmMsgDispRq>, <RCtApHufTPMSmgr_WrBusMsg>, <RCtApHufTPMSmgr_ControlEcuStandbyTimer>, <RCtApHufTPMSwpa_TimerWA>, <RCtApHufTPMSwnh_TimerWT>, <RCtApHufTPMSdia_StatusInfoWu> is smaller than the tick time of the operating system."
#endif

#if (RTE_TICKDURATION > (200UL * 1000UL))
# error "The cycle time of runnable(s) <RCtApHufTPMSroe_RoElite>, <RCtApHufTPMSdia_SgDiagnosis> is smaller than the tick time of the operating system."
#endif

FUNC(void, RTE_CODE) Rte_MemCpy(P2VAR(void, AUTOMATIC, RTE_APPL_VAR) destination, P2CONST(void, AUTOMATIC, RTE_APPL_DATA) source, uint16_least num) /* PRQA S 3408, 1505 */ /* MD_Rte_3408, MD_MSR_8.10 */
{
  P2CONST(uint8, AUTOMATIC, RTE_APPL_DATA) src = source;
  P2VAR(uint8, AUTOMATIC, RTE_APPL_VAR) dst = destination;
  uint16_least i;
  for (i = 0; i < num ; i++)
  {
    dst[i] = src[i];
  }
}

FUNC(void, RTE_CODE) Rte_MemCpy32(P2VAR(void, AUTOMATIC, RTE_APPL_VAR) destination, P2CONST(void, AUTOMATIC, RTE_APPL_DATA) source, uint16_least num)
{
  P2CONST(uint8, AUTOMATIC, RTE_APPL_DATA) src = source;
  P2VAR(uint8, AUTOMATIC, RTE_APPL_VAR) dst = destination;
  uint16_least i = 0;

  if (num >= 16)
  {
    for (i = 0 ; (i + 15) < num; i += 16)
    {
      dst[i] = src[i];
      dst[i+1] = src[i+1];
      dst[i+2] = src[i+2];
      dst[i+3] = src[i+3];
      dst[i+4] = src[i+4];
      dst[i+5] = src[i+5];
      dst[i+6] = src[i+6];
      dst[i+7] = src[i+7];
      dst[i+8] = src[i+8];
      dst[i+9] = src[i+9];
      dst[i+10] = src[i+10];
      dst[i+11] = src[i+11];
      dst[i+12] = src[i+12];
      dst[i+13] = src[i+13];
      dst[i+14] = src[i+14];
      dst[i+15] = src[i+15];
    }

  }
  while (i < num)
  {
    dst[i] = src[i];
    ++i;
  }
}

STATIC FUNC(void, RTE_CODE) Rte_MemClr(P2VAR(void, AUTOMATIC, RTE_VAR_NOINIT) ptr, uint16_least num)
{
  P2VAR(uint8, AUTOMATIC, RTE_VAR_NOINIT) dst = ptr;
  uint16_least i;
  for (i = 0; i < num; i++)
  {
    dst[i] = 0;
  }
}

FUNC(Std_ReturnType, RTE_CODE) Rte_Start(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
  /* set default values for internal data */
  Rte_CpApHufTPMSmgr_PP_EnvData_DE_tEnvData = Rte_C_tEnvData;
  Rte_MemCpy32(Rte_CpApHufTPMSmgr_PP_RfStructOut_DE_auRfStruct, Rte_C_aucRfStruct, sizeof(DT_auRfStruct));
  Rte_CpApHufTPMSwnh_PP_WarnOut_DE_ushWarnOut = 0U;
  Rte_CpApHufTPMSwpa_PP_WAState_DE_ushWAState = 0U;
  Rte_MemCpy32(Rte_CpCdHufTPMSrfd_PP_RfStruct_DE_auRfStruct, Rte_C_aucRfStruct, sizeof(DT_auRfStruct));

  /* initialize inter-runnable variables */
  Rte_Irv_CpApHufTPMSmgr_IRV_TpmActvRq_TpmMsgDispRq = FALSE;

  /* activate the tasks */
  Rte_Task_Activate(HufTPMS_Task1); /* PRQA S 3112 */ /* MD_Rte_3112 */
  (void)ActivateTask(HufTPMS_Task1); /* PRQA S 3417 */ /* MD_Rte_Os */
  Rte_Task_Activate(HufTPMS_Task2); /* PRQA S 3112 */ /* MD_Rte_3112 */
  (void)ActivateTask(HufTPMS_Task2); /* PRQA S 3417 */ /* MD_Rte_Os */
  Rte_Task_Activate(HufTPMS_Task3); /* PRQA S 3112 */ /* MD_Rte_3112 */
  (void)ActivateTask(HufTPMS_Task3); /* PRQA S 3417 */ /* MD_Rte_Os */
  Rte_Task_Activate(HufTPMS_Task4); /* PRQA S 3112 */ /* MD_Rte_3112 */
  (void)ActivateTask(HufTPMS_Task4); /* PRQA S 3417 */ /* MD_Rte_Os */

  /* activate the alarms used for TimingEvents */
  (void)SetRelAlarm(Rte_Al_TE_CpCdHufTPMSrfd_RCtCdHufTPMSrfd_ChkRfStruct, RTE_MSEC(0) + (TickType)1, RTE_MSEC(50)); /* PRQA S 3417 */ /* MD_Rte_Os */
  (void)SetRelAlarm(Rte_Al_TE_CpApHufTPMSmgr_RCtApHufTPMSmgr_WrDisplayMsg, RTE_MSEC(0) + (TickType)1, RTE_MSEC(10)); /* PRQA S 3417 */ /* MD_Rte_Os */
  (void)SetRelAlarm(Rte_Al_TE_CpApHufTPMSmgr_RCtApHufTPMSmgr_GenInternalClock, RTE_MSEC(0) + (TickType)1, RTE_MSEC(10)); /* PRQA S 3417 */ /* MD_Rte_Os */
  (void)SetRelAlarm(Rte_Al_TE_HufTPMS_Task4_0_1s, RTE_SEC(0) + (TickType)1, RTE_SEC(1)); /* PRQA S 3417 */ /* MD_Rte_Os */
  (void)SetRelAlarm(Rte_Al_TE_HufTPMS_Task4_0_200ms, RTE_MSEC(0) + (TickType)1, RTE_MSEC(200)); /* PRQA S 3417 */ /* MD_Rte_Os */

  Rte_InitState = RTE_STATE_INIT;

  return RTE_E_OK;
} /* PRQA S 6050 */ /* MD_MSR_STCAL */

FUNC(Std_ReturnType, RTE_CODE) Rte_Stop(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
  /* deactivate alarms */
  (void)CancelAlarm(Rte_Al_TE_CpCdHufTPMSrfd_RCtCdHufTPMSrfd_ChkRfStruct); /* PRQA S 3417 */ /* MD_Rte_Os */
  (void)CancelAlarm(Rte_Al_TE_CpApHufTPMSmgr_RCtApHufTPMSmgr_WrDisplayMsg); /* PRQA S 3417 */ /* MD_Rte_Os */
  (void)CancelAlarm(Rte_Al_TE_CpApHufTPMSmgr_RCtApHufTPMSmgr_GenInternalClock); /* PRQA S 3417 */ /* MD_Rte_Os */
  (void)CancelAlarm(Rte_Al_TE_HufTPMS_Task4_0_1s); /* PRQA S 3417 */ /* MD_Rte_Os */
  (void)CancelAlarm(Rte_Al_TE_HufTPMS_Task4_0_200ms); /* PRQA S 3417 */ /* MD_Rte_Os */

  Rte_InitState = RTE_STATE_UNINIT;

  return RTE_E_OK;
}

FUNC(void, RTE_CODE) Rte_InitMemory(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
  Rte_InitState = RTE_STATE_UNINIT;
  /* reset Rx Timeout Flags */
  Rte_RxTimeoutFlagsInit();

}


/**********************************************************************************************************************
 * Internal/External Tx connections
 *********************************************************************************************************************/

FUNC(Std_ReturnType, RTE_CODE) Rte_Write_CtApHufTPMSmgr_PP_EnvData_DE_tEnvData(P2CONST(DT_tEnvData, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA) data) /* PRQA S 0850, 1505 */ /* MD_MSR_19.8, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  Rte_WriteHook_CtApHufTPMSmgr_PP_EnvData_DE_tEnvData_Start(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Rte_CpApHufTPMSmgr_PP_EnvData_DE_tEnvData = *(data);
  Rte_Task_SetEvent(HufTPMS_Task3, Rte_Ev_OnRx_HufTPMS_Task3_CpApHufTPMSmgr_PP_EnvData_DE_tEnvData); /* PRQA S 3112 */ /* MD_Rte_3112 */
  /* scheduled trigger for runnables: RCtApHufTPMSwnh_ReceiveEnvData, RCtApHufTPMSwpa_ReceiveEnvData */
  (void)SetEvent(HufTPMS_Task3, Rte_Ev_OnRx_HufTPMS_Task3_CpApHufTPMSmgr_PP_EnvData_DE_tEnvData); /* PRQA S 3417 */ /* MD_Rte_Os */
  Rte_WriteHook_CtApHufTPMSmgr_PP_EnvData_DE_tEnvData_Return(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  return ret;
} /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

FUNC(Std_ReturnType, RTE_CODE) Rte_Write_CtApHufTPMSmgr_PP_RfStructOut_DE_auRfStruct(P2CONST(DT_auRfStruct, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA) data) /* PRQA S 0850, 1505 */ /* MD_MSR_19.8, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  Rte_WriteHook_CtApHufTPMSmgr_PP_RfStructOut_DE_auRfStruct_Start(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Rte_MemCpy32(Rte_CpApHufTPMSmgr_PP_RfStructOut_DE_auRfStruct, *(data), sizeof(DT_auRfStruct));
  Rte_Task_SetEvent(HufTPMS_Task3, Rte_Ev_Run_CpApHufTPMSdia_RCtApHufTPMSdia_ReceiveTelData); /* PRQA S 3112 */ /* MD_Rte_3112 */
  /* scheduled trigger for runnables: RCtApHufTPMSdia_ReceiveTelData */
  (void)SetEvent(HufTPMS_Task3, Rte_Ev_Run_CpApHufTPMSdia_RCtApHufTPMSdia_ReceiveTelData); /* PRQA S 3417 */ /* MD_Rte_Os */
  Rte_WriteHook_CtApHufTPMSmgr_PP_RfStructOut_DE_auRfStruct_Return(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  return ret;
} /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

FUNC(Std_ReturnType, RTE_CODE) Rte_Write_CtApHufTPMSmgr_P_Awake_Diag_Actv_Awake_Diag_Actv(DC_BOOL data) /* PRQA S 0850, 1505 */ /* MD_MSR_19.8, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  Rte_WriteHook_CtApHufTPMSmgr_P_Awake_Diag_Actv_Awake_Diag_Actv_Start(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
#if defined(IL_VECTOR_VERSION)
  Rte_ComHook_Com_Awake_Diag_Actv_TX_SigTx(&data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  (void)Com_SendSignal(Com_Com_Awake_Diag_Actv_TX, (P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR))(&data));
#else
  Rte_ComHook_Com_Awake_Diag_Actv_TX_SigTx(&data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  ret |= Com_SendSignal(Com_Com_Awake_Diag_Actv_TX, RTE_COM_SENDCAST(P2VAR(void, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA))(&data)); /* PRQA S 0850 */ /* MD_MSR_19.8 */
#endif
  Rte_WriteHook_CtApHufTPMSmgr_P_Awake_Diag_Actv_Awake_Diag_Actv_Return(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  return ret;
} /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

FUNC(Std_ReturnType, RTE_CODE) Rte_Write_CtApHufTPMSmgr_P_Awake_Ignition_On_Awake_Ignition_On(DC_BOOL data) /* PRQA S 0850, 1505 */ /* MD_MSR_19.8, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  Rte_WriteHook_CtApHufTPMSmgr_P_Awake_Ignition_On_Awake_Ignition_On_Start(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
#if defined(IL_VECTOR_VERSION)
  Rte_ComHook_Com_Awake_Ignition_On_TX_SigTx(&data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  (void)Com_SendSignal(Com_Com_Awake_Ignition_On_TX, (P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR))(&data));
#else
  Rte_ComHook_Com_Awake_Ignition_On_TX_SigTx(&data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  ret |= Com_SendSignal(Com_Com_Awake_Ignition_On_TX, RTE_COM_SENDCAST(P2VAR(void, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA))(&data)); /* PRQA S 0850 */ /* MD_MSR_19.8 */
#endif
  Rte_WriteHook_CtApHufTPMSmgr_P_Awake_Ignition_On_Awake_Ignition_On_Return(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  return ret;
} /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

FUNC(Std_ReturnType, RTE_CODE) Rte_Write_CtApHufTPMSmgr_P_Awake_NwSt_Awake_NwSt(DC_BOOL data) /* PRQA S 0850, 1505 */ /* MD_MSR_19.8, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  Rte_WriteHook_CtApHufTPMSmgr_P_Awake_NwSt_Awake_NwSt_Start(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
#if defined(IL_VECTOR_VERSION)
  Rte_ComHook_Com_Awake_NwSt_TX_SigTx(&data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  (void)Com_SendSignal(Com_Com_Awake_NwSt_TX, (P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR))(&data));
#else
  Rte_ComHook_Com_Awake_NwSt_TX_SigTx(&data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  ret |= Com_SendSignal(Com_Com_Awake_NwSt_TX, RTE_COM_SENDCAST(P2VAR(void, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA))(&data)); /* PRQA S 0850 */ /* MD_MSR_19.8 */
#endif
  Rte_WriteHook_CtApHufTPMSmgr_P_Awake_NwSt_Awake_NwSt_Return(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  return ret;
} /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

FUNC(Std_ReturnType, RTE_CODE) Rte_Write_CtApHufTPMSmgr_P_Awake_Warn_Actv_Awake_Warn_Actv(DC_BOOL data) /* PRQA S 0850, 1505 */ /* MD_MSR_19.8, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  Rte_WriteHook_CtApHufTPMSmgr_P_Awake_Warn_Actv_Awake_Warn_Actv_Start(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
#if defined(IL_VECTOR_VERSION)
  Rte_ComHook_Com_Awake_Warn_Actv_TX_SigTx(&data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  (void)Com_SendSignal(Com_Com_Awake_Warn_Actv_TX, (P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR))(&data));
#else
  Rte_ComHook_Com_Awake_Warn_Actv_TX_SigTx(&data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  ret |= Com_SendSignal(Com_Com_Awake_Warn_Actv_TX, RTE_COM_SENDCAST(P2VAR(void, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA))(&data)); /* PRQA S 0850 */ /* MD_MSR_19.8 */
#endif
  Rte_WriteHook_CtApHufTPMSmgr_P_Awake_Warn_Actv_Awake_Warn_Actv_Return(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  return ret;
} /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

FUNC(Std_ReturnType, RTE_CODE) Rte_Write_CtApHufTPMSmgr_P_Meas_TPM_1_Meas_XX(P2CONST(ARR_08_UInt_noSNA_8, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA) data) /* PRQA S 0850, 1505 */ /* MD_MSR_19.8, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  Rte_WriteHook_CtApHufTPMSmgr_P_Meas_TPM_1_Meas_XX_Start(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
#if defined(IL_VECTOR_VERSION)
  Rte_ComHook_Com_Meas_TPM_1A_SigTx(&(*(data))[0]); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_Meas_TPM_1A, (P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR))&(*(data))[0]);
  Rte_ComHook_Com_Meas_TPM_1B_SigTx(&(*(data))[1]); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_Meas_TPM_1B, (P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR))&(*(data))[1]);
  Rte_ComHook_Com_Meas_TPM_1C_SigTx(&(*(data))[2]); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_Meas_TPM_1C, (P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR))&(*(data))[2]);
  Rte_ComHook_Com_Meas_TPM_1D_SigTx(&(*(data))[3]); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_Meas_TPM_1D, (P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR))&(*(data))[3]);
  Rte_ComHook_Com_Meas_TPM_1E_SigTx(&(*(data))[4]); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_Meas_TPM_1E, (P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR))&(*(data))[4]);
  Rte_ComHook_Com_Meas_TPM_1F_SigTx(&(*(data))[5]); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_Meas_TPM_1F, (P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR))&(*(data))[5]);
  Rte_ComHook_Com_Meas_TPM_1G_SigTx(&(*(data))[6]); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_Meas_TPM_1G, (P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR))&(*(data))[6]);
  Rte_ComHook_Com_Meas_TPM_1H_SigTx(&(*(data))[7]); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_Meas_TPM_1H, (P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR))&(*(data))[7]);
  (void)Com_SendSignalGroup(Com_Com_Grp_Meas_TPM_1_3132ken15lz5pbvyxcg5h44pj);
#else
  Rte_ComHook_Com_Meas_TPM_1A_SigTx(&(*(data))[0]); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_Meas_TPM_1A, RTE_COM_SENDCAST(P2VAR(void, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA))&(*(data))[0]); /* PRQA S 0850 */ /* MD_MSR_19.8 */
  Rte_ComHook_Com_Meas_TPM_1B_SigTx(&(*(data))[1]); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_Meas_TPM_1B, RTE_COM_SENDCAST(P2VAR(void, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA))&(*(data))[1]); /* PRQA S 0850 */ /* MD_MSR_19.8 */
  Rte_ComHook_Com_Meas_TPM_1C_SigTx(&(*(data))[2]); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_Meas_TPM_1C, RTE_COM_SENDCAST(P2VAR(void, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA))&(*(data))[2]); /* PRQA S 0850 */ /* MD_MSR_19.8 */
  Rte_ComHook_Com_Meas_TPM_1D_SigTx(&(*(data))[3]); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_Meas_TPM_1D, RTE_COM_SENDCAST(P2VAR(void, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA))&(*(data))[3]); /* PRQA S 0850 */ /* MD_MSR_19.8 */
  Rte_ComHook_Com_Meas_TPM_1E_SigTx(&(*(data))[4]); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_Meas_TPM_1E, RTE_COM_SENDCAST(P2VAR(void, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA))&(*(data))[4]); /* PRQA S 0850 */ /* MD_MSR_19.8 */
  Rte_ComHook_Com_Meas_TPM_1F_SigTx(&(*(data))[5]); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_Meas_TPM_1F, RTE_COM_SENDCAST(P2VAR(void, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA))&(*(data))[5]); /* PRQA S 0850 */ /* MD_MSR_19.8 */
  Rte_ComHook_Com_Meas_TPM_1G_SigTx(&(*(data))[6]); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_Meas_TPM_1G, RTE_COM_SENDCAST(P2VAR(void, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA))&(*(data))[6]); /* PRQA S 0850 */ /* MD_MSR_19.8 */
  Rte_ComHook_Com_Meas_TPM_1H_SigTx(&(*(data))[7]); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_Meas_TPM_1H, RTE_COM_SENDCAST(P2VAR(void, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA))&(*(data))[7]); /* PRQA S 0850 */ /* MD_MSR_19.8 */
  ret |= Com_SendSignalGroup(Com_Com_Grp_Meas_TPM_1_3132ken15lz5pbvyxcg5h44pj);
#endif
  Rte_WriteHook_CtApHufTPMSmgr_P_Meas_TPM_1_Meas_XX_Return(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  return ret;
} /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

FUNC(Std_ReturnType, RTE_CODE) Rte_Write_CtApHufTPMSmgr_P_RefPress_RefPress(P2CONST(REC_RefPress, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA) data) /* PRQA S 0850, 1505 */ /* MD_MSR_19.8, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  Rte_WriteHook_CtApHufTPMSmgr_P_RefPress_RefPress_Start(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
#if defined(IL_VECTOR_VERSION)
  Rte_ComHook_Com_RefPress_Front_SigTx(&(*(data)).RefPress_Front); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_RefPress_Front, (P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR))&(*(data)).RefPress_Front);
  Rte_ComHook_Com_RefPress_Rear_SigTx(&(*(data)).RefPress_Rear); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_RefPress_Rear, (P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR))&(*(data)).RefPress_Rear);
  (void)Com_SendSignalGroup(Com_Com_Grp_RefPress_e6b62hvisjl8h41vpowm4r3qf);
#else
  Rte_ComHook_Com_RefPress_Front_SigTx(&(*(data)).RefPress_Front); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_RefPress_Front, RTE_COM_SENDCAST(P2VAR(void, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA))&(*(data)).RefPress_Front); /* PRQA S 0850 */ /* MD_MSR_19.8 */
  Rte_ComHook_Com_RefPress_Rear_SigTx(&(*(data)).RefPress_Rear); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_RefPress_Rear, RTE_COM_SENDCAST(P2VAR(void, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA))&(*(data)).RefPress_Rear); /* PRQA S 0850 */ /* MD_MSR_19.8 */
  ret |= Com_SendSignalGroup(Com_Com_Grp_RefPress_e6b62hvisjl8h41vpowm4r3qf);
#endif
  Rte_WriteHook_CtApHufTPMSmgr_P_RefPress_RefPress_Return(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  return ret;
} /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

FUNC(Std_ReturnType, RTE_CODE) Rte_Write_CtApHufTPMSmgr_P_TPM_Lmp_On_Rq_Pr2_TPM_Lmp_On_Rq_Pr2(P2CONST(REC_TPM_Lmp_On_Rq_Pr2_cp6wyrd9cg7ec7y2w3khz1gyt, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA) data) /* PRQA S 0850, 1505 */ /* MD_MSR_19.8, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  Rte_WriteHook_CtApHufTPMSmgr_P_TPM_Lmp_On_Rq_Pr2_TPM_Lmp_On_Rq_Pr2_Start(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
#if defined(IL_VECTOR_VERSION)
  Rte_ComHook_Com_CRC_TPM_Lmp_On_Rq_Pr2_SigTx(&(*(data)).CRC_TPM_Lmp_On_Rq_Pr2); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_CRC_TPM_Lmp_On_Rq_Pr2, (P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR))&(*(data)).CRC_TPM_Lmp_On_Rq_Pr2);
  Rte_ComHook_Com_Rsrv1_TPM_Lmp_On_Rq_Pr2_SigTx(&(*(data)).Rsrv1_TPM_Lmp_On_Rq_Pr2); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_Rsrv1_TPM_Lmp_On_Rq_Pr2, (P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR))&(*(data)).Rsrv1_TPM_Lmp_On_Rq_Pr2);
  Rte_ComHook_Com_SQC_TPM_Lmp_On_Rq_Pr2_SigTx(&(*(data)).SQC_TPM_Lmp_On_Rq_Pr2); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_SQC_TPM_Lmp_On_Rq_Pr2, (P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR))&(*(data)).SQC_TPM_Lmp_On_Rq_Pr2);
  Rte_ComHook_Com_TPM_IndLmp_On_Rq_SigTx(&(*(data)).TPM_IndLmp_On_Rq); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_TPM_IndLmp_On_Rq, (P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR))&(*(data)).TPM_IndLmp_On_Rq);
  Rte_ComHook_Com_TPM_MalfLmp_On_Rq_SigTx(&(*(data)).TPM_MalfLmp_On_Rq); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_TPM_MalfLmp_On_Rq, (P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR))&(*(data)).TPM_MalfLmp_On_Rq);
  (void)Com_SendSignalGroup(Com_Com_Grp_TPM_Lmp_On_Rq_Pr2_7585r0i3a3k9gf2uhjuwskcs8);
#else
  Rte_ComHook_Com_CRC_TPM_Lmp_On_Rq_Pr2_SigTx(&(*(data)).CRC_TPM_Lmp_On_Rq_Pr2); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_CRC_TPM_Lmp_On_Rq_Pr2, RTE_COM_SENDCAST(P2VAR(void, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA))&(*(data)).CRC_TPM_Lmp_On_Rq_Pr2); /* PRQA S 0850 */ /* MD_MSR_19.8 */
  Rte_ComHook_Com_Rsrv1_TPM_Lmp_On_Rq_Pr2_SigTx(&(*(data)).Rsrv1_TPM_Lmp_On_Rq_Pr2); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_Rsrv1_TPM_Lmp_On_Rq_Pr2, RTE_COM_SENDCAST(P2VAR(void, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA))&(*(data)).Rsrv1_TPM_Lmp_On_Rq_Pr2); /* PRQA S 0850 */ /* MD_MSR_19.8 */
  Rte_ComHook_Com_SQC_TPM_Lmp_On_Rq_Pr2_SigTx(&(*(data)).SQC_TPM_Lmp_On_Rq_Pr2); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_SQC_TPM_Lmp_On_Rq_Pr2, RTE_COM_SENDCAST(P2VAR(void, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA))&(*(data)).SQC_TPM_Lmp_On_Rq_Pr2); /* PRQA S 0850 */ /* MD_MSR_19.8 */
  Rte_ComHook_Com_TPM_IndLmp_On_Rq_SigTx(&(*(data)).TPM_IndLmp_On_Rq); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_TPM_IndLmp_On_Rq, RTE_COM_SENDCAST(P2VAR(void, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA))&(*(data)).TPM_IndLmp_On_Rq); /* PRQA S 0850 */ /* MD_MSR_19.8 */
  Rte_ComHook_Com_TPM_MalfLmp_On_Rq_SigTx(&(*(data)).TPM_MalfLmp_On_Rq); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_TPM_MalfLmp_On_Rq, RTE_COM_SENDCAST(P2VAR(void, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA))&(*(data)).TPM_MalfLmp_On_Rq); /* PRQA S 0850 */ /* MD_MSR_19.8 */
  ret |= Com_SendSignalGroup(Com_Com_Grp_TPM_Lmp_On_Rq_Pr2_7585r0i3a3k9gf2uhjuwskcs8);
#endif
  Rte_WriteHook_CtApHufTPMSmgr_P_TPM_Lmp_On_Rq_Pr2_TPM_Lmp_On_Rq_Pr2_Return(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  return ret;
} /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

FUNC(Std_ReturnType, RTE_CODE) Rte_Write_CtApHufTPMSmgr_P_TPM_Lmp_On_Rq_old_TPM_Lmp_On_Rq_old(P2CONST(REC_TPM_Lmp_On_Rq_old, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA) data) /* PRQA S 0850, 1505 */ /* MD_MSR_19.8, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  Rte_WriteHook_CtApHufTPMSmgr_P_TPM_Lmp_On_Rq_old_TPM_Lmp_On_Rq_old_Start(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
#if defined(IL_VECTOR_VERSION)
  Rte_ComHook_Com_TPM_IndLmp_On_Rq_old_SigTx(&(*(data)).TPM_IndLmp_On_Rq_old); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_TPM_IndLmp_On_Rq_old, (P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR))&(*(data)).TPM_IndLmp_On_Rq_old);
  Rte_ComHook_Com_TPM_MalfLmp_On_Rq_old_SigTx(&(*(data)).TPM_MalfLmp_On_Rq_old); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_TPM_MalfLmp_On_Rq_old, (P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR))&(*(data)).TPM_MalfLmp_On_Rq_old);
  (void)Com_SendSignalGroup(Com_Com_Grp_TPM_Lmp_On_Rq_old_6ojk1jt26qecmpesbn0qmd1gk);
#else
  Rte_ComHook_Com_TPM_IndLmp_On_Rq_old_SigTx(&(*(data)).TPM_IndLmp_On_Rq_old); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_TPM_IndLmp_On_Rq_old, RTE_COM_SENDCAST(P2VAR(void, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA))&(*(data)).TPM_IndLmp_On_Rq_old); /* PRQA S 0850 */ /* MD_MSR_19.8 */
  Rte_ComHook_Com_TPM_MalfLmp_On_Rq_old_SigTx(&(*(data)).TPM_MalfLmp_On_Rq_old); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_TPM_MalfLmp_On_Rq_old, RTE_COM_SENDCAST(P2VAR(void, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA))&(*(data)).TPM_MalfLmp_On_Rq_old); /* PRQA S 0850 */ /* MD_MSR_19.8 */
  ret |= Com_SendSignalGroup(Com_Com_Grp_TPM_Lmp_On_Rq_old_6ojk1jt26qecmpesbn0qmd1gk);
#endif
  Rte_WriteHook_CtApHufTPMSmgr_P_TPM_Lmp_On_Rq_old_TPM_Lmp_On_Rq_old_Return(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  return ret;
} /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

FUNC(Std_ReturnType, RTE_CODE) Rte_Write_CtApHufTPMSmgr_P_Tire_Stat_V2_Tire_Stat_V2(P2CONST(REC_Tire_Stat_V2, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA) data) /* PRQA S 0850, 1505 */ /* MD_MSR_19.8, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  Rte_WriteHook_CtApHufTPMSmgr_P_Tire_Stat_V2_Tire_Stat_V2_Start(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
#if defined(IL_VECTOR_VERSION)
  Rte_ComHook_Com_Press_Disp_Avl_SigTx(&(*(data)).Press_Disp_Avl); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_Press_Disp_Avl, (P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR))&(*(data)).Press_Disp_Avl);
  Rte_ComHook_Com_TPM_MsgDisp_Rq_SigTx(&(*(data)).TPM_MsgDisp_Rq); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_TPM_MsgDisp_Rq, (P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR))&(*(data)).TPM_MsgDisp_Rq);
  Rte_ComHook_Com_TPM_Stat_SigTx(&(*(data)).TPM_Stat); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_TPM_Stat, (P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR))&(*(data)).TPM_Stat);
  Rte_ComHook_Com_TPM_WarnDisp_Rq_SigTx(&(*(data)).TPM_WarnDisp_Rq); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_TPM_WarnDisp_Rq, (P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR))&(*(data)).TPM_WarnDisp_Rq);
  Rte_ComHook_Com_TirePress_FL_SigTx(&(*(data)).TirePress_FL); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_TirePress_FL, (P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR))&(*(data)).TirePress_FL);
  Rte_ComHook_Com_TirePress_FR_SigTx(&(*(data)).TirePress_FR); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_TirePress_FR, (P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR))&(*(data)).TirePress_FR);
  Rte_ComHook_Com_TirePress_RL_SigTx(&(*(data)).TirePress_RL); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_TirePress_RL, (P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR))&(*(data)).TirePress_RL);
  Rte_ComHook_Com_TirePress_RR_SigTx(&(*(data)).TirePress_RR); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_TirePress_RR, (P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR))&(*(data)).TirePress_RR);
  Rte_ComHook_Com_TireStat_FL_SigTx(&(*(data)).TireStat_FL); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_TireStat_FL, (P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR))&(*(data)).TireStat_FL);
  Rte_ComHook_Com_TireStat_FR_SigTx(&(*(data)).TireStat_FR); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_TireStat_FR, (P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR))&(*(data)).TireStat_FR);
  Rte_ComHook_Com_TireStat_RL_SigTx(&(*(data)).TireStat_RL); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_TireStat_RL, (P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR))&(*(data)).TireStat_RL);
  Rte_ComHook_Com_TireStat_RR_SigTx(&(*(data)).TireStat_RR); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_TireStat_RR, (P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR))&(*(data)).TireStat_RR);
  (void)Com_SendSignalGroup(Com_Com_Grp_Tire_Stat_V2_a08d173x6dha8wdge8n213tva);
#else
  Rte_ComHook_Com_Press_Disp_Avl_SigTx(&(*(data)).Press_Disp_Avl); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_Press_Disp_Avl, RTE_COM_SENDCAST(P2VAR(void, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA))&(*(data)).Press_Disp_Avl); /* PRQA S 0850 */ /* MD_MSR_19.8 */
  Rte_ComHook_Com_TPM_MsgDisp_Rq_SigTx(&(*(data)).TPM_MsgDisp_Rq); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_TPM_MsgDisp_Rq, RTE_COM_SENDCAST(P2VAR(void, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA))&(*(data)).TPM_MsgDisp_Rq); /* PRQA S 0850 */ /* MD_MSR_19.8 */
  Rte_ComHook_Com_TPM_Stat_SigTx(&(*(data)).TPM_Stat); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_TPM_Stat, RTE_COM_SENDCAST(P2VAR(void, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA))&(*(data)).TPM_Stat); /* PRQA S 0850 */ /* MD_MSR_19.8 */
  Rte_ComHook_Com_TPM_WarnDisp_Rq_SigTx(&(*(data)).TPM_WarnDisp_Rq); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_TPM_WarnDisp_Rq, RTE_COM_SENDCAST(P2VAR(void, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA))&(*(data)).TPM_WarnDisp_Rq); /* PRQA S 0850 */ /* MD_MSR_19.8 */
  Rte_ComHook_Com_TirePress_FL_SigTx(&(*(data)).TirePress_FL); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_TirePress_FL, RTE_COM_SENDCAST(P2VAR(void, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA))&(*(data)).TirePress_FL); /* PRQA S 0850 */ /* MD_MSR_19.8 */
  Rte_ComHook_Com_TirePress_FR_SigTx(&(*(data)).TirePress_FR); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_TirePress_FR, RTE_COM_SENDCAST(P2VAR(void, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA))&(*(data)).TirePress_FR); /* PRQA S 0850 */ /* MD_MSR_19.8 */
  Rte_ComHook_Com_TirePress_RL_SigTx(&(*(data)).TirePress_RL); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_TirePress_RL, RTE_COM_SENDCAST(P2VAR(void, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA))&(*(data)).TirePress_RL); /* PRQA S 0850 */ /* MD_MSR_19.8 */
  Rte_ComHook_Com_TirePress_RR_SigTx(&(*(data)).TirePress_RR); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_TirePress_RR, RTE_COM_SENDCAST(P2VAR(void, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA))&(*(data)).TirePress_RR); /* PRQA S 0850 */ /* MD_MSR_19.8 */
  Rte_ComHook_Com_TireStat_FL_SigTx(&(*(data)).TireStat_FL); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_TireStat_FL, RTE_COM_SENDCAST(P2VAR(void, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA))&(*(data)).TireStat_FL); /* PRQA S 0850 */ /* MD_MSR_19.8 */
  Rte_ComHook_Com_TireStat_FR_SigTx(&(*(data)).TireStat_FR); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_TireStat_FR, RTE_COM_SENDCAST(P2VAR(void, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA))&(*(data)).TireStat_FR); /* PRQA S 0850 */ /* MD_MSR_19.8 */
  Rte_ComHook_Com_TireStat_RL_SigTx(&(*(data)).TireStat_RL); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_TireStat_RL, RTE_COM_SENDCAST(P2VAR(void, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA))&(*(data)).TireStat_RL); /* PRQA S 0850 */ /* MD_MSR_19.8 */
  Rte_ComHook_Com_TireStat_RR_SigTx(&(*(data)).TireStat_RR); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_TireStat_RR, RTE_COM_SENDCAST(P2VAR(void, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA))&(*(data)).TireStat_RR); /* PRQA S 0850 */ /* MD_MSR_19.8 */
  ret |= Com_SendSignalGroup(Com_Com_Grp_Tire_Stat_V2_a08d173x6dha8wdge8n213tva);
#endif
  Rte_WriteHook_CtApHufTPMSmgr_P_Tire_Stat_V2_Tire_Stat_V2_Return(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  return ret;
} /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

FUNC(Std_ReturnType, RTE_CODE) Rte_Write_CtApHufTPMSmgr_P_Tire_Temp_V2_Tire_Temp_V2(P2CONST(REC_Tire_Temp_V2, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA) data) /* PRQA S 0850, 1505 */ /* MD_MSR_19.8, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  Rte_WriteHook_CtApHufTPMSmgr_P_Tire_Temp_V2_Tire_Temp_V2_Start(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
#if defined(IL_VECTOR_VERSION)
  Rte_ComHook_Com_TireTemp_FL_SigTx(&(*(data)).TireTemp_FL); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_TireTemp_FL, (P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR))&(*(data)).TireTemp_FL);
  Rte_ComHook_Com_TireTemp_FR_SigTx(&(*(data)).TireTemp_FR); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_TireTemp_FR, (P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR))&(*(data)).TireTemp_FR);
  Rte_ComHook_Com_TireTemp_RL_SigTx(&(*(data)).TireTemp_RL); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_TireTemp_RL, (P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR))&(*(data)).TireTemp_RL);
  Rte_ComHook_Com_TireTemp_RR_SigTx(&(*(data)).TireTemp_RR); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_TireTemp_RR, (P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR))&(*(data)).TireTemp_RR);
  Rte_ComHook_Com_Tire_Temp_Stat_FL_SigTx(&(*(data)).Tire_Temp_Stat_FL); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_Tire_Temp_Stat_FL, (P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR))&(*(data)).Tire_Temp_Stat_FL);
  Rte_ComHook_Com_Tire_Temp_Stat_FR_SigTx(&(*(data)).Tire_Temp_Stat_FR); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_Tire_Temp_Stat_FR, (P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR))&(*(data)).Tire_Temp_Stat_FR);
  Rte_ComHook_Com_Tire_Temp_Stat_RL_SigTx(&(*(data)).Tire_Temp_Stat_RL); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_Tire_Temp_Stat_RL, (P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR))&(*(data)).Tire_Temp_Stat_RL);
  Rte_ComHook_Com_Tire_Temp_Stat_RR_SigTx(&(*(data)).Tire_Temp_Stat_RR); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_Tire_Temp_Stat_RR, (P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR))&(*(data)).Tire_Temp_Stat_RR);
  Rte_ComHook_Com_Tire_Temp_WarnDisp_Rq_SigTx(&(*(data)).Tire_Temp_WarnDisp_Rq); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_Tire_Temp_WarnDisp_Rq, (P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR))&(*(data)).Tire_Temp_WarnDisp_Rq);
  (void)Com_SendSignalGroup(Com_Com_Grp_Tire_Temp_V2_9s8yrzmswsh2tdh4weqzip9n5);
#else
  Rte_ComHook_Com_TireTemp_FL_SigTx(&(*(data)).TireTemp_FL); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_TireTemp_FL, RTE_COM_SENDCAST(P2VAR(void, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA))&(*(data)).TireTemp_FL); /* PRQA S 0850 */ /* MD_MSR_19.8 */
  Rte_ComHook_Com_TireTemp_FR_SigTx(&(*(data)).TireTemp_FR); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_TireTemp_FR, RTE_COM_SENDCAST(P2VAR(void, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA))&(*(data)).TireTemp_FR); /* PRQA S 0850 */ /* MD_MSR_19.8 */
  Rte_ComHook_Com_TireTemp_RL_SigTx(&(*(data)).TireTemp_RL); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_TireTemp_RL, RTE_COM_SENDCAST(P2VAR(void, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA))&(*(data)).TireTemp_RL); /* PRQA S 0850 */ /* MD_MSR_19.8 */
  Rte_ComHook_Com_TireTemp_RR_SigTx(&(*(data)).TireTemp_RR); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_TireTemp_RR, RTE_COM_SENDCAST(P2VAR(void, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA))&(*(data)).TireTemp_RR); /* PRQA S 0850 */ /* MD_MSR_19.8 */
  Rte_ComHook_Com_Tire_Temp_Stat_FL_SigTx(&(*(data)).Tire_Temp_Stat_FL); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_Tire_Temp_Stat_FL, RTE_COM_SENDCAST(P2VAR(void, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA))&(*(data)).Tire_Temp_Stat_FL); /* PRQA S 0850 */ /* MD_MSR_19.8 */
  Rte_ComHook_Com_Tire_Temp_Stat_FR_SigTx(&(*(data)).Tire_Temp_Stat_FR); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_Tire_Temp_Stat_FR, RTE_COM_SENDCAST(P2VAR(void, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA))&(*(data)).Tire_Temp_Stat_FR); /* PRQA S 0850 */ /* MD_MSR_19.8 */
  Rte_ComHook_Com_Tire_Temp_Stat_RL_SigTx(&(*(data)).Tire_Temp_Stat_RL); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_Tire_Temp_Stat_RL, RTE_COM_SENDCAST(P2VAR(void, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA))&(*(data)).Tire_Temp_Stat_RL); /* PRQA S 0850 */ /* MD_MSR_19.8 */
  Rte_ComHook_Com_Tire_Temp_Stat_RR_SigTx(&(*(data)).Tire_Temp_Stat_RR); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_Tire_Temp_Stat_RR, RTE_COM_SENDCAST(P2VAR(void, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA))&(*(data)).Tire_Temp_Stat_RR); /* PRQA S 0850 */ /* MD_MSR_19.8 */
  Rte_ComHook_Com_Tire_Temp_WarnDisp_Rq_SigTx(&(*(data)).Tire_Temp_WarnDisp_Rq); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_Tire_Temp_WarnDisp_Rq, RTE_COM_SENDCAST(P2VAR(void, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA))&(*(data)).Tire_Temp_WarnDisp_Rq); /* PRQA S 0850 */ /* MD_MSR_19.8 */
  ret |= Com_SendSignalGroup(Com_Com_Grp_Tire_Temp_V2_9s8yrzmswsh2tdh4weqzip9n5);
#endif
  Rte_WriteHook_CtApHufTPMSmgr_P_Tire_Temp_V2_Tire_Temp_V2_Return(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  return ret;
} /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

FUNC(Std_ReturnType, RTE_CODE) Rte_Write_CtApHufTPMSmgr_P_WakeupRsn_TPM_WakeupRsn_TPM(c08_WakeupRsn_TPM data) /* PRQA S 0850, 1505 */ /* MD_MSR_19.8, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  Rte_WriteHook_CtApHufTPMSmgr_P_WakeupRsn_TPM_WakeupRsn_TPM_Start(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
#if defined(IL_VECTOR_VERSION)
  Rte_ComHook_Com_WakeupRsn_TPM_TX_SigTx(&data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  (void)Com_SendSignal(Com_Com_WakeupRsn_TPM_TX, (P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR))(&data));
#else
  Rte_ComHook_Com_WakeupRsn_TPM_TX_SigTx(&data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  ret |= Com_SendSignal(Com_Com_WakeupRsn_TPM_TX, RTE_COM_SENDCAST(P2VAR(void, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA))(&data)); /* PRQA S 0850 */ /* MD_MSR_19.8 */
#endif
  Rte_WriteHook_CtApHufTPMSmgr_P_WakeupRsn_TPM_WakeupRsn_TPM_Return(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  return ret;
} /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

FUNC(Std_ReturnType, RTE_CODE) Rte_Write_CtApHufTPMSroe_P_ROE_XX_ROE_XX(P2CONST(REC_ROE_XX, AUTOMATIC, RTE_CTAPHUFTPMSROE_APPL_DATA) data) /* PRQA S 0850, 1505 */ /* MD_MSR_19.8, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  Rte_WriteHook_CtApHufTPMSroe_P_ROE_XX_ROE_XX_Start(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
#if defined(IL_VECTOR_VERSION)
  Rte_ComHook_Com_ROE_DTC_Stat_TPM_SigTx(&(*(data)).ROE_DTC_Stat_XX); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_ROE_DTC_Stat_TPM, (P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSROE_APPL_VAR))&(*(data)).ROE_DTC_Stat_XX);
  Rte_ComHook_Com_ROE_DTC_TPM_SigTx(&(*(data)).ROE_DTC_XX); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_ROE_DTC_TPM, (P2VAR(uint32, AUTOMATIC, RTE_CTAPHUFTPMSROE_APPL_VAR))&(*(data)).ROE_DTC_XX);
  Rte_ComHook_Com_ROE_Header_TPM_SigTx(&(*(data)).ROE_Header_XX); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_ROE_Header_TPM, (P2VAR(uint32, AUTOMATIC, RTE_CTAPHUFTPMSROE_APPL_VAR))&(*(data)).ROE_Header_XX);
  (void)Com_SendSignalGroup(Com_Com_Grp_ROE_TPM_mn20b0yk2zhdvrshr3hnfsn1);
#else
  Rte_ComHook_Com_ROE_DTC_Stat_TPM_SigTx(&(*(data)).ROE_DTC_Stat_XX); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_ROE_DTC_Stat_TPM, RTE_COM_SENDCAST(P2VAR(void, AUTOMATIC, RTE_CTAPHUFTPMSROE_APPL_DATA))&(*(data)).ROE_DTC_Stat_XX); /* PRQA S 0850 */ /* MD_MSR_19.8 */
  Rte_ComHook_Com_ROE_DTC_TPM_SigTx(&(*(data)).ROE_DTC_XX); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_ROE_DTC_TPM, RTE_COM_SENDCAST(P2VAR(void, AUTOMATIC, RTE_CTAPHUFTPMSROE_APPL_DATA))&(*(data)).ROE_DTC_XX); /* PRQA S 0850 */ /* MD_MSR_19.8 */
  Rte_ComHook_Com_ROE_Header_TPM_SigTx(&(*(data)).ROE_Header_XX); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Com_UpdateShadowSignal(Com_Com_ROE_Header_TPM, RTE_COM_SENDCAST(P2VAR(void, AUTOMATIC, RTE_CTAPHUFTPMSROE_APPL_DATA))&(*(data)).ROE_Header_XX); /* PRQA S 0850 */ /* MD_MSR_19.8 */
  ret |= Com_SendSignalGroup(Com_Com_Grp_ROE_TPM_mn20b0yk2zhdvrshr3hnfsn1);
#endif
  Rte_WriteHook_CtApHufTPMSroe_P_ROE_XX_ROE_XX_Return(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  return ret;
} /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

FUNC(Std_ReturnType, RTE_CODE) Rte_Write_CtApHufTPMSwnh_PP_WarnOut_DE_ushWarnOut(DT_ushWarnOut data) /* PRQA S 0850, 1505 */ /* MD_MSR_19.8, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  Rte_WriteHook_CtApHufTPMSwnh_PP_WarnOut_DE_ushWarnOut_Start(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Rte_CpApHufTPMSwnh_PP_WarnOut_DE_ushWarnOut = *(&data);
  Rte_Task_SetEvent(HufTPMS_Task3, Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_ReceiveWarnOut); /* PRQA S 3112 */ /* MD_Rte_3112 */
  /* scheduled trigger for runnables: RCtApHufTPMSmgr_ReceiveWarnOut */
  (void)SetEvent(HufTPMS_Task3, Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_ReceiveWarnOut); /* PRQA S 3417 */ /* MD_Rte_Os */
  Rte_WriteHook_CtApHufTPMSwnh_PP_WarnOut_DE_ushWarnOut_Return(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  return ret;
} /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

FUNC(Std_ReturnType, RTE_CODE) Rte_Write_CtApHufTPMSwpa_PP_WAState_DE_ushWAState(DT_ushWAState data) /* PRQA S 0850, 1505 */ /* MD_MSR_19.8, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  Rte_WriteHook_CtApHufTPMSwpa_PP_WAState_DE_ushWAState_Start(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Rte_CpApHufTPMSwpa_PP_WAState_DE_ushWAState = *(&data);
  Rte_Task_SetEvent(HufTPMS_Task3, Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_ReceiveWAState); /* PRQA S 3112 */ /* MD_Rte_3112 */
  /* scheduled trigger for runnables: RCtApHufTPMSmgr_ReceiveWAState */
  (void)SetEvent(HufTPMS_Task3, Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_ReceiveWAState); /* PRQA S 3417 */ /* MD_Rte_Os */
  Rte_WriteHook_CtApHufTPMSwpa_PP_WAState_DE_ushWAState_Return(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  return ret;
} /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

FUNC(Std_ReturnType, RTE_CODE) Rte_Write_CtCdHufTPMSrfd_PP_RfStruct_DE_auRfStruct(P2CONST(DT_auRfStruct, AUTOMATIC, RTE_CTCDHUFTPMSRFD_APPL_DATA) data) /* PRQA S 0850, 1505 */ /* MD_MSR_19.8, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  Rte_WriteHook_CtCdHufTPMSrfd_PP_RfStruct_DE_auRfStruct_Start(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Rte_MemCpy32(Rte_CpCdHufTPMSrfd_PP_RfStruct_DE_auRfStruct, *(data), sizeof(DT_auRfStruct));
  Rte_Task_SetEvent(HufTPMS_Task3, Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_ReceiveTelData); /* PRQA S 3112 */ /* MD_Rte_3112 */
  /* scheduled trigger for runnables: RCtApHufTPMSmgr_ReceiveTelData */
  (void)SetEvent(HufTPMS_Task3, Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_ReceiveTelData); /* PRQA S 3417 */ /* MD_Rte_Os */
  Rte_WriteHook_CtCdHufTPMSrfd_PP_RfStruct_DE_auRfStruct_Return(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  return ret;
} /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */


/**********************************************************************************************************************
 * Internal/External Rx connections
 *********************************************************************************************************************/

FUNC(Std_ReturnType, RTE_CODE) Rte_Read_CtApHufTPMSdia_PP_RfStructFiltered_DE_auRfStruct(P2VAR(DT_auRfStruct, AUTOMATIC, RTE_CTAPHUFTPMSDIA_APPL_VAR) data) /* PRQA S 0850, 3673, 1505 */ /* MD_MSR_19.8, MD_Rte_Qac, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  Rte_ReadHook_CtApHufTPMSdia_PP_RfStructFiltered_DE_auRfStruct_Start(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Rte_MemCpy32(*(data), Rte_CpApHufTPMSmgr_PP_RfStructOut_DE_auRfStruct, sizeof(DT_auRfStruct));
  Rte_ReadHook_CtApHufTPMSdia_PP_RfStructFiltered_DE_auRfStruct_Return(data); /* PRQA S 3112 */ /* MD_Rte_3112 */

  return ret;
} /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

FUNC(Std_ReturnType, RTE_CODE) Rte_Read_CtApHufTPMSdia_R_DidA_ExtTest_Pres_DidA_ExtTest_Pres(P2VAR(DC_BOOL, AUTOMATIC, RTE_CTAPHUFTPMSDIA_APPL_VAR) data) /* PRQA S 0850, 3673, 1505 */ /* MD_MSR_19.8, MD_Rte_Qac, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  Rte_ReadHook_CtApHufTPMSdia_R_DidA_ExtTest_Pres_DidA_ExtTest_Pres_Start(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
#if defined(IL_VECTOR_VERSION)
  (void)Com_ReceiveSignal(Com_Com_DidA_ExtTest_Pres, (P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSDIA_APPL_VAR))(data));
  Rte_ComHook_Com_DidA_ExtTest_Pres_SigRx(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
#else
  (void)Com_ReceiveSignal(Com_Com_DidA_ExtTest_Pres, (data)); /* PRQA S 3453 */ /* MD_MSR_19.7 */
  Rte_ComHook_Com_DidA_ExtTest_Pres_SigRx(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
#endif
  if (Rte_RxTimeoutFlags.Rte_RxTimeout_Com_DidA_ExtTest_Pres != 0)
  {
    ret |= RTE_E_MAX_AGE_EXCEEDED;
  }
  Rte_ReadHook_CtApHufTPMSdia_R_DidA_ExtTest_Pres_DidA_ExtTest_Pres_Return(data); /* PRQA S 3112 */ /* MD_Rte_3112 */

  return ret;
} /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

FUNC(Std_ReturnType, RTE_CODE) Rte_Read_CtApHufTPMSdia_R_EVC_CfgBit_01_32_Pr2_EVC_CfgBit_01_32_Pr2(P2VAR(REC_EVC_CfgBit_01_32_Pr2_d23bad5cnts3f65mtgoqoxmrz, AUTOMATIC, RTE_CTAPHUFTPMSDIA_APPL_VAR) data) /* PRQA S 0850, 3673, 1505 */ /* MD_MSR_19.8, MD_Rte_Qac, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  Rte_ReadHook_CtApHufTPMSdia_R_EVC_CfgBit_01_32_Pr2_EVC_CfgBit_01_32_Pr2_Start(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
#if defined(IL_VECTOR_VERSION)
  (void)Com_ReceiveSignalGroup(Com_Com_Grp_EVC_CfgBit_01_32_Pr2_9rceoqjm3g6d48sc5qcm0ihhi); /* PRQA S 3453 */ /* MD_MSR_19.7 */
  (void)Com_ReceiveShadowSignal(Com_Com_EVC_1E_GuardLvl_B4_Avl, (P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSDIA_APPL_VAR))&(*(data)).EVC_1E_GuardLvl_B4_Avl); /* PRQA S 3453, 3321 */ /* MD_MSR_19.7, MD_Rte_Qac */
  Rte_ComHook_Com_EVC_1E_GuardLvl_B4_Avl_SigRx(&(*(data)).EVC_1E_GuardLvl_B4_Avl); /* PRQA S 3112 */ /* MD_Rte_3112 */
  (void)Com_ReceiveShadowSignal(Com_Com_EVC_1F_GuardLvl_B6_Avl, (P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSDIA_APPL_VAR))&(*(data)).EVC_1F_GuardLvl_B6_Avl); /* PRQA S 3453, 3321 */ /* MD_MSR_19.7, MD_Rte_Qac */
  Rte_ComHook_Com_EVC_1F_GuardLvl_B6_Avl_SigRx(&(*(data)).EVC_1F_GuardLvl_B6_Avl); /* PRQA S 3112 */ /* MD_Rte_3112 */
  (void)Com_ReceiveShadowSignal(Com_Com_EVC_20_GuardLvl_B7_Avl, (P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSDIA_APPL_VAR))&(*(data)).EVC_20_GuardLvl_B7_Avl); /* PRQA S 3453, 3321 */ /* MD_MSR_19.7, MD_Rte_Qac */
  Rte_ComHook_Com_EVC_20_GuardLvl_B7_Avl_SigRx(&(*(data)).EVC_20_GuardLvl_B7_Avl); /* PRQA S 3112 */ /* MD_Rte_3112 */
  (void)Com_ReceiveShadowSignal(Com_Com_EVC_CfgBit_01_32_Stat, &(*(data)).EVC_CfgBit_01_32_Stat); /* PRQA S 3453, 3321 */ /* MD_MSR_19.7, MD_Rte_Qac */
  Rte_ComHook_Com_EVC_CfgBit_01_32_Stat_SigRx(&(*(data)).EVC_CfgBit_01_32_Stat); /* PRQA S 3112 */ /* MD_Rte_3112 */
#else
  (void)Com_ReceiveSignalGroup(Com_Com_Grp_EVC_CfgBit_01_32_Pr2_9rceoqjm3g6d48sc5qcm0ihhi); /* PRQA S 3453 */ /* MD_MSR_19.7 */
  (void)Com_ReceiveShadowSignal(Com_Com_EVC_1E_GuardLvl_B4_Avl, &(*(data)).EVC_1E_GuardLvl_B4_Avl); /* PRQA S 3453, 3321 */ /* MD_MSR_19.7, MD_Rte_Qac */
  Rte_ComHook_Com_EVC_1E_GuardLvl_B4_Avl_SigRx(&(*(data)).EVC_1E_GuardLvl_B4_Avl); /* PRQA S 3112 */ /* MD_Rte_3112 */
  (void)Com_ReceiveShadowSignal(Com_Com_EVC_1F_GuardLvl_B6_Avl, &(*(data)).EVC_1F_GuardLvl_B6_Avl); /* PRQA S 3453, 3321 */ /* MD_MSR_19.7, MD_Rte_Qac */
  Rte_ComHook_Com_EVC_1F_GuardLvl_B6_Avl_SigRx(&(*(data)).EVC_1F_GuardLvl_B6_Avl); /* PRQA S 3112 */ /* MD_Rte_3112 */
  (void)Com_ReceiveShadowSignal(Com_Com_EVC_20_GuardLvl_B7_Avl, &(*(data)).EVC_20_GuardLvl_B7_Avl); /* PRQA S 3453, 3321 */ /* MD_MSR_19.7, MD_Rte_Qac */
  Rte_ComHook_Com_EVC_20_GuardLvl_B7_Avl_SigRx(&(*(data)).EVC_20_GuardLvl_B7_Avl); /* PRQA S 3112 */ /* MD_Rte_3112 */
  (void)Com_ReceiveShadowSignal(Com_Com_EVC_CfgBit_01_32_Stat, &(*(data)).EVC_CfgBit_01_32_Stat); /* PRQA S 3453, 3321 */ /* MD_MSR_19.7, MD_Rte_Qac */
  Rte_ComHook_Com_EVC_CfgBit_01_32_Stat_SigRx(&(*(data)).EVC_CfgBit_01_32_Stat); /* PRQA S 3112 */ /* MD_Rte_3112 */
#endif
  Rte_ReadHook_CtApHufTPMSdia_R_EVC_CfgBit_01_32_Pr2_EVC_CfgBit_01_32_Pr2_Return(data); /* PRQA S 3112 */ /* MD_Rte_3112 */

  return ret;
} /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

FUNC(Std_ReturnType, RTE_CODE) Rte_Read_CtApHufTPMSdia_R_EVC_CfgList_01_0C_Pr2_EVC_CfgList_01_0C_Pr2(P2VAR(REC_EVC_CfgList_01_0C_Pr2_ah3rxaqpfvlnju8848jpspm9p, AUTOMATIC, RTE_CTAPHUFTPMSDIA_APPL_VAR) data) /* PRQA S 0850, 3673, 1505 */ /* MD_MSR_19.8, MD_Rte_Qac, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  Rte_ReadHook_CtApHufTPMSdia_R_EVC_CfgList_01_0C_Pr2_EVC_CfgList_01_0C_Pr2_Start(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  (void)Com_ReceiveSignalGroup(Com_Com_Grp_EVC_CfgList_01_0C_Pr2_3qvfhaj56jpqdd0izhj6fs0z3); /* PRQA S 3453 */ /* MD_MSR_19.7 */
  (void)Com_ReceiveShadowSignal(Com_Com_EVC_CfgList_01_0C_Stat, &(*(data)).EVC_CfgList_01_0C_Stat); /* PRQA S 3453, 3321 */ /* MD_MSR_19.7, MD_Rte_Qac */
  Rte_ComHook_Com_EVC_CfgList_01_0C_Stat_SigRx(&(*(data)).EVC_CfgList_01_0C_Stat); /* PRQA S 3112 */ /* MD_Rte_3112 */
  (void)Com_ReceiveShadowSignal(Com_Com_EVC_List02_BodyStyle, &(*(data)).EVC_List02_BodyStyle); /* PRQA S 3453, 3321 */ /* MD_MSR_19.7, MD_Rte_Qac */
  Rte_ComHook_Com_EVC_List02_BodyStyle_SigRx(&(*(data)).EVC_List02_BodyStyle); /* PRQA S 3112 */ /* MD_Rte_3112 */
  (void)Com_ReceiveShadowSignal(Com_Com_EVC_List0A_TPM_Style, &(*(data)).EVC_List0A_TPM_Style); /* PRQA S 3453, 3321 */ /* MD_MSR_19.7, MD_Rte_Qac */
  Rte_ComHook_Com_EVC_List0A_TPM_Style_SigRx(&(*(data)).EVC_List0A_TPM_Style); /* PRQA S 3112 */ /* MD_Rte_3112 */
  (void)Com_ReceiveShadowSignal(Com_Com_EVC_List0C_VehLine, &(*(data)).EVC_List0C_VehLine); /* PRQA S 3453, 3321 */ /* MD_MSR_19.7, MD_Rte_Qac */
  Rte_ComHook_Com_EVC_List0C_VehLine_SigRx(&(*(data)).EVC_List0C_VehLine); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Rte_ReadHook_CtApHufTPMSdia_R_EVC_CfgList_01_0C_Pr2_EVC_CfgList_01_0C_Pr2_Return(data); /* PRQA S 3112 */ /* MD_Rte_3112 */

  return ret;
} /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

FUNC(Std_ReturnType, RTE_CODE) Rte_Read_CtApHufTPMSdia_R_PN14_SupBat_Stat_PN14_SupBat_Stat(P2VAR(REC_PN14_SupBat_Stat_2is6fi0meeac78nkn35zc5ui3, AUTOMATIC, RTE_CTAPHUFTPMSDIA_APPL_VAR) data) /* PRQA S 0850, 3673, 1505 */ /* MD_MSR_19.8, MD_Rte_Qac, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  Rte_ReadHook_CtApHufTPMSdia_R_PN14_SupBat_Stat_PN14_SupBat_Stat_Start(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  (void)Com_ReceiveSignalGroup(Com_Com_Grp_PN14_SupBat_Stat_aleu8fy7bsux9kh42xfztkzmi); /* PRQA S 3453 */ /* MD_MSR_19.7 */
  (void)Com_ReceiveShadowSignal(Com_Com_PN14_SupBatCutSw_Stat, &(*(data)).PN14_SupBatCutSw_Stat); /* PRQA S 3453, 3321 */ /* MD_MSR_19.7, MD_Rte_Qac */
  Rte_ComHook_Com_PN14_SupBatCutSw_Stat_SigRx(&(*(data)).PN14_SupBatCutSw_Stat); /* PRQA S 3112 */ /* MD_Rte_3112 */
  (void)Com_ReceiveShadowSignal(Com_Com_PN14_SupBat_Volt, &(*(data)).PN14_SupBat_Volt); /* PRQA S 3453, 3321 */ /* MD_MSR_19.7, MD_Rte_Qac */
  Rte_ComHook_Com_PN14_SupBat_Volt_SigRx(&(*(data)).PN14_SupBat_Volt); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Rte_ReadHook_CtApHufTPMSdia_R_PN14_SupBat_Stat_PN14_SupBat_Stat_Return(data); /* PRQA S 3112 */ /* MD_Rte_3112 */

  return ret;
} /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

FUNC(Std_ReturnType, RTE_CODE) Rte_Read_CtApHufTPMSmgr_PP_RfStructIn_DE_auRfStruct(P2VAR(DT_auRfStruct, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR) data) /* PRQA S 0850, 3673, 1505 */ /* MD_MSR_19.8, MD_Rte_Qac, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  Rte_ReadHook_CtApHufTPMSmgr_PP_RfStructIn_DE_auRfStruct_Start(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  Rte_MemCpy32(*(data), Rte_CpCdHufTPMSrfd_PP_RfStruct_DE_auRfStruct, sizeof(DT_auRfStruct));
  Rte_ReadHook_CtApHufTPMSmgr_PP_RfStructIn_DE_auRfStruct_Return(data); /* PRQA S 3112 */ /* MD_Rte_3112 */

  return ret;
} /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

FUNC(Std_ReturnType, RTE_CODE) Rte_Read_CtApHufTPMSmgr_R_AirPress_Outsd_AirPress_Outsd(P2VAR(c08_hPa_0_1980_7k8, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR) data) /* PRQA S 0850, 3673, 1505 */ /* MD_MSR_19.8, MD_Rte_Qac, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  Rte_ReadHook_CtApHufTPMSmgr_R_AirPress_Outsd_AirPress_Outsd_Start(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  (void)Com_ReceiveSignal(Com_Com_AirPress_Outsd, (data)); /* PRQA S 3453 */ /* MD_MSR_19.7 */
  Rte_ComHook_Com_AirPress_Outsd_SigRx(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  if (Rte_RxTimeoutFlags.Rte_RxTimeout_Com_AirPress_Outsd != 0)
  {
    ret |= RTE_E_MAX_AGE_EXCEEDED;
  }
  Rte_ReadHook_CtApHufTPMSmgr_R_AirPress_Outsd_AirPress_Outsd_Return(data); /* PRQA S 3112 */ /* MD_Rte_3112 */

  return ret;
} /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

FUNC(Std_ReturnType, RTE_CODE) Rte_Read_CtApHufTPMSmgr_R_AirTemp_Outsd_Disp_AirTemp_Outsd_Disp(P2VAR(c08_degC_m40_85_0k5, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR) data) /* PRQA S 0850, 3673, 1505 */ /* MD_MSR_19.8, MD_Rte_Qac, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  Rte_ReadHook_CtApHufTPMSmgr_R_AirTemp_Outsd_Disp_AirTemp_Outsd_Disp_Start(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  (void)Com_ReceiveSignal(Com_Com_AirTemp_Outsd_Disp, (data)); /* PRQA S 3453 */ /* MD_MSR_19.7 */
  Rte_ComHook_Com_AirTemp_Outsd_Disp_SigRx(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  if (Rte_RxTimeoutFlags.Rte_RxTimeout_Com_AirTemp_Outsd_Disp != 0)
  {
    ret |= RTE_E_MAX_AGE_EXCEEDED;
  }
  Rte_ReadHook_CtApHufTPMSmgr_R_AirTemp_Outsd_Disp_AirTemp_Outsd_Disp_Return(data); /* PRQA S 3112 */ /* MD_Rte_3112 */

  return ret;
} /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

FUNC(Std_ReturnType, RTE_CODE) Rte_Read_CtApHufTPMSmgr_R_Eng_Rs_EngCtrl_Pr2_Eng_Rs_EngCtrl_Pr2(P2VAR(REC_Eng_Rs_EngCtrl_Pr2_1j00gxu3p5exa8awg915k1zy, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR) data) /* PRQA S 0850, 3673, 1505 */ /* MD_MSR_19.8, MD_Rte_Qac, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  Rte_ReadHook_CtApHufTPMSmgr_R_Eng_Rs_EngCtrl_Pr2_Eng_Rs_EngCtrl_Pr2_Start(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  (void)Com_ReceiveSignalGroup(Com_Com_Grp_Eng_Rs_EngCtrl_Pr2_1g6e1wh7aspfj509n9mt9fl55); /* PRQA S 3453 */ /* MD_MSR_19.7 */
  (void)Com_ReceiveShadowSignal(Com_Com_EngRun_Stat, &(*(data)).EngRun_Stat); /* PRQA S 3453, 3321 */ /* MD_MSR_19.7, MD_Rte_Qac */
  Rte_ComHook_Com_EngRun_Stat_SigRx(&(*(data)).EngRun_Stat); /* PRQA S 3112 */ /* MD_Rte_3112 */
  if (Rte_RxTimeoutFlags.Rte_RxTimeout_Com_Grp_Eng_Rs_EngCtrl_Pr2_1g6e1wh7aspfj509n9mt9fl55 != 0)
  {
    ret |= RTE_E_MAX_AGE_EXCEEDED;
  }
  Rte_ReadHook_CtApHufTPMSmgr_R_Eng_Rs_EngCtrl_Pr2_Eng_Rs_EngCtrl_Pr2_Return(data); /* PRQA S 3112 */ /* MD_Rte_3112 */

  return ret;
} /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

FUNC(Std_ReturnType, RTE_CODE) Rte_Read_CtApHufTPMSmgr_R_Ign_Stat_Pr2_Ign_Stat_Pr2(P2VAR(REC_Ign_Stat_Pr2_71njeubj9ico1p8v4pmslfcno, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR) data) /* PRQA S 0850, 3673, 1505 */ /* MD_MSR_19.8, MD_Rte_Qac, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  Rte_ReadHook_CtApHufTPMSmgr_R_Ign_Stat_Pr2_Ign_Stat_Pr2_Start(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
#if defined(IL_VECTOR_VERSION)
  (void)Com_ReceiveSignalGroup(Com_Com_Grp_Ign_Stat_Pr2_457i75qk4uen9ahb37ecxdhxz); /* PRQA S 3453 */ /* MD_MSR_19.7 */
  (void)Com_ReceiveShadowSignal(Com_Com_ISw_Stat, &(*(data)).ISw_Stat); /* PRQA S 3453, 3321 */ /* MD_MSR_19.7, MD_Rte_Qac */
  Rte_ComHook_Com_ISw_Stat_SigRx(&(*(data)).ISw_Stat); /* PRQA S 3112 */ /* MD_Rte_3112 */
  (void)Com_ReceiveShadowSignal(Com_Com_Ign_On_StartProc_Inact, (P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR))&(*(data)).Ign_On_StartProc_Inact); /* PRQA S 3453, 3321 */ /* MD_MSR_19.7, MD_Rte_Qac */
  Rte_ComHook_Com_Ign_On_StartProc_Inact_SigRx(&(*(data)).Ign_On_StartProc_Inact); /* PRQA S 3112 */ /* MD_Rte_3112 */
#else
  (void)Com_ReceiveSignalGroup(Com_Com_Grp_Ign_Stat_Pr2_457i75qk4uen9ahb37ecxdhxz); /* PRQA S 3453 */ /* MD_MSR_19.7 */
  (void)Com_ReceiveShadowSignal(Com_Com_ISw_Stat, &(*(data)).ISw_Stat); /* PRQA S 3453, 3321 */ /* MD_MSR_19.7, MD_Rte_Qac */
  Rte_ComHook_Com_ISw_Stat_SigRx(&(*(data)).ISw_Stat); /* PRQA S 3112 */ /* MD_Rte_3112 */
  (void)Com_ReceiveShadowSignal(Com_Com_Ign_On_StartProc_Inact, &(*(data)).Ign_On_StartProc_Inact); /* PRQA S 3453, 3321 */ /* MD_MSR_19.7, MD_Rte_Qac */
  Rte_ComHook_Com_Ign_On_StartProc_Inact_SigRx(&(*(data)).Ign_On_StartProc_Inact); /* PRQA S 3112 */ /* MD_Rte_3112 */
#endif
  if (Rte_RxTimeoutFlags.Rte_RxTimeout_Com_Grp_Ign_Stat_Pr2_457i75qk4uen9ahb37ecxdhxz != 0)
  {
    ret |= RTE_E_MAX_AGE_EXCEEDED;
  }
  Rte_ReadHook_CtApHufTPMSmgr_R_Ign_Stat_Pr2_Ign_Stat_Pr2_Return(data); /* PRQA S 3112 */ /* MD_Rte_3112 */

  return ret;
} /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

FUNC(Std_ReturnType, RTE_CODE) Rte_Read_CtApHufTPMSmgr_R_Odo_Odo(P2VAR(c24_km_0_999999k9_0k1, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR) data) /* PRQA S 0850, 3673, 1505 */ /* MD_MSR_19.8, MD_Rte_Qac, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  Rte_ReadHook_CtApHufTPMSmgr_R_Odo_Odo_Start(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  (void)Com_ReceiveSignal(Com_Com_Odo, (data)); /* PRQA S 3453 */ /* MD_MSR_19.7 */
  Rte_ComHook_Com_Odo_SigRx(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  if (Rte_RxTimeoutFlags.Rte_RxTimeout_Com_Odo != 0)
  {
    ret |= RTE_E_MAX_AGE_EXCEEDED;
  }
  Rte_ReadHook_CtApHufTPMSmgr_R_Odo_Odo_Return(data); /* PRQA S 3112 */ /* MD_Rte_3112 */

  return ret;
} /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

FUNC(Std_ReturnType, RTE_CODE) Rte_Read_CtApHufTPMSmgr_R_PN14_EOL_Disp_Rq_PN14_EOL_Disp_Rq(P2VAR(c03_EOL_Disp_Rq, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR) data) /* PRQA S 0850, 3673, 1505 */ /* MD_MSR_19.8, MD_Rte_Qac, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  Rte_ReadHook_CtApHufTPMSmgr_R_PN14_EOL_Disp_Rq_PN14_EOL_Disp_Rq_Start(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  (void)Com_ReceiveSignal(Com_Com_PN14_EOL_Disp_Rq, (data)); /* PRQA S 3453 */ /* MD_MSR_19.7 */
  Rte_ComHook_Com_PN14_EOL_Disp_Rq_SigRx(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  if (Rte_RxTimeoutFlags.Rte_RxTimeout_Com_PN14_EOL_Disp_Rq != 0)
  {
    ret |= RTE_E_MAX_AGE_EXCEEDED;
  }
  Rte_ReadHook_CtApHufTPMSmgr_R_PN14_EOL_Disp_Rq_PN14_EOL_Disp_Rq_Return(data); /* PRQA S 3112 */ /* MD_Rte_3112 */

  return ret;
} /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

FUNC(Std_ReturnType, RTE_CODE) Rte_Read_CtApHufTPMSmgr_R_RevGr_Engg_RevGr_Engg(P2VAR(c02_Disengg_Engg, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR) data) /* PRQA S 0850, 3673, 1505 */ /* MD_MSR_19.8, MD_Rte_Qac, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  Rte_ReadHook_CtApHufTPMSmgr_R_RevGr_Engg_RevGr_Engg_Start(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  (void)Com_ReceiveSignal(Com_Com_RevGr_Engg, (data)); /* PRQA S 3453 */ /* MD_MSR_19.7 */
  Rte_ComHook_Com_RevGr_Engg_SigRx(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  if (Rte_RxTimeoutFlags.Rte_RxTimeout_Com_RevGr_Engg != 0)
  {
    ret |= RTE_E_MAX_AGE_EXCEEDED;
  }
  Rte_ReadHook_CtApHufTPMSmgr_R_RevGr_Engg_RevGr_Engg_Return(data); /* PRQA S 3112 */ /* MD_Rte_3112 */

  return ret;
} /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

FUNC(Std_ReturnType, RTE_CODE) Rte_Read_CtApHufTPMSmgr_R_TPM_Actv_Rq_V2_TPM_Actv_Rq_V2(P2VAR(c02_TPM_Actv_Rq_V2, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR) data) /* PRQA S 0850, 3673, 1505 */ /* MD_MSR_19.8, MD_Rte_Qac, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  Rte_ReadHook_CtApHufTPMSmgr_R_TPM_Actv_Rq_V2_TPM_Actv_Rq_V2_Start(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  (void)Com_ReceiveSignal(Com_Com_TPM_Actv_Rq_V2, (data)); /* PRQA S 3453 */ /* MD_MSR_19.7 */
  Rte_ComHook_Com_TPM_Actv_Rq_V2_SigRx(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  if (Rte_RxTimeoutFlags.Rte_RxTimeout_Com_TPM_Actv_Rq_V2 != 0)
  {
    ret |= RTE_E_MAX_AGE_EXCEEDED;
  }
  Rte_ReadHook_CtApHufTPMSmgr_R_TPM_Actv_Rq_V2_TPM_Actv_Rq_V2_Return(data); /* PRQA S 3112 */ /* MD_Rte_3112 */

  return ret;
} /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

FUNC(Std_ReturnType, RTE_CODE) Rte_Read_CtApHufTPMSmgr_R_VehSpd_Disp_VehSpd_Disp(P2VAR(c12_km_p_h_0_409k4_0k1, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR) data) /* PRQA S 0850, 3673, 1505 */ /* MD_MSR_19.8, MD_Rte_Qac, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  Rte_ReadHook_CtApHufTPMSmgr_R_VehSpd_Disp_VehSpd_Disp_Start(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  (void)Com_ReceiveSignal(Com_Com_VehSpd_Disp, (data)); /* PRQA S 3453 */ /* MD_MSR_19.7 */
  Rte_ComHook_Com_VehSpd_Disp_SigRx(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  if (Rte_RxTimeoutFlags.Rte_RxTimeout_Com_VehSpd_Disp != 0)
  {
    ret |= RTE_E_MAX_AGE_EXCEEDED;
  }
  Rte_ReadHook_CtApHufTPMSmgr_R_VehSpd_Disp_VehSpd_Disp_Return(data); /* PRQA S 3112 */ /* MD_Rte_3112 */

  return ret;
} /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

FUNC(Std_ReturnType, RTE_CODE) Rte_Read_CtApHufTPMSmgr_R_WhlPlsCnt_TPM_Pr2_WhlPlsCnt_TPM_Pr2(P2VAR(REC_WhlPlsCnt_TPM_Pr2_5hishd08ma5z1luev78umdwvx, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR) data) /* PRQA S 0850, 3673, 1505 */ /* MD_MSR_19.8, MD_Rte_Qac, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  Rte_ReadHook_CtApHufTPMSmgr_R_WhlPlsCnt_TPM_Pr2_WhlPlsCnt_TPM_Pr2_Start(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  (void)Com_ReceiveSignalGroup(Com_Com_Grp_WhlPlsCnt_TPM_Pr2_ci3hi3ex1xdl3zn6k2mcbudsp); /* PRQA S 3453 */ /* MD_MSR_19.7 */
  (void)Com_ReceiveShadowSignal(Com_Com_CRC_WhlPlsCnt_TPM_Pr2, &(*(data)).CRC_WhlPlsCnt_TPM_Pr2); /* PRQA S 3453, 3321 */ /* MD_MSR_19.7, MD_Rte_Qac */
  Rte_ComHook_Com_CRC_WhlPlsCnt_TPM_Pr2_SigRx(&(*(data)).CRC_WhlPlsCnt_TPM_Pr2); /* PRQA S 3112 */ /* MD_Rte_3112 */
  (void)Com_ReceiveShadowSignal(Com_Com_Rsrv1_WhlPlsCnt_TPM_Pr2, &(*(data)).Rsrv1_WhlPlsCnt_TPM_Pr2); /* PRQA S 3453, 3321 */ /* MD_MSR_19.7, MD_Rte_Qac */
  Rte_ComHook_Com_Rsrv1_WhlPlsCnt_TPM_Pr2_SigRx(&(*(data)).Rsrv1_WhlPlsCnt_TPM_Pr2); /* PRQA S 3112 */ /* MD_Rte_3112 */
  (void)Com_ReceiveShadowSignal(Com_Com_Rsrv2_WhlPlsCnt_TPM_Pr2, &(*(data)).Rsrv2_WhlPlsCnt_TPM_Pr2); /* PRQA S 3453, 3321 */ /* MD_MSR_19.7, MD_Rte_Qac */
  Rte_ComHook_Com_Rsrv2_WhlPlsCnt_TPM_Pr2_SigRx(&(*(data)).Rsrv2_WhlPlsCnt_TPM_Pr2); /* PRQA S 3112 */ /* MD_Rte_3112 */
  (void)Com_ReceiveShadowSignal(Com_Com_SQC_WhlPlsCnt_TPM_Pr2, &(*(data)).SQC_WhlPlsCnt_TPM_Pr2); /* PRQA S 3453, 3321 */ /* MD_MSR_19.7, MD_Rte_Qac */
  Rte_ComHook_Com_SQC_WhlPlsCnt_TPM_Pr2_SigRx(&(*(data)).SQC_WhlPlsCnt_TPM_Pr2); /* PRQA S 3112 */ /* MD_Rte_3112 */
  (void)Com_ReceiveShadowSignal(Com_Com_WhlPlsCnt_FL, &(*(data)).WhlPlsCnt_FL); /* PRQA S 3453, 3321 */ /* MD_MSR_19.7, MD_Rte_Qac */
  Rte_ComHook_Com_WhlPlsCnt_FL_SigRx(&(*(data)).WhlPlsCnt_FL); /* PRQA S 3112 */ /* MD_Rte_3112 */
  (void)Com_ReceiveShadowSignal(Com_Com_WhlPlsCnt_FR, &(*(data)).WhlPlsCnt_FR); /* PRQA S 3453, 3321 */ /* MD_MSR_19.7, MD_Rte_Qac */
  Rte_ComHook_Com_WhlPlsCnt_FR_SigRx(&(*(data)).WhlPlsCnt_FR); /* PRQA S 3112 */ /* MD_Rte_3112 */
  (void)Com_ReceiveShadowSignal(Com_Com_WhlPlsCnt_RL, &(*(data)).WhlPlsCnt_RL); /* PRQA S 3453, 3321 */ /* MD_MSR_19.7, MD_Rte_Qac */
  Rte_ComHook_Com_WhlPlsCnt_RL_SigRx(&(*(data)).WhlPlsCnt_RL); /* PRQA S 3112 */ /* MD_Rte_3112 */
  (void)Com_ReceiveShadowSignal(Com_Com_WhlPlsCnt_RR, &(*(data)).WhlPlsCnt_RR); /* PRQA S 3453, 3321 */ /* MD_MSR_19.7, MD_Rte_Qac */
  Rte_ComHook_Com_WhlPlsCnt_RR_SigRx(&(*(data)).WhlPlsCnt_RR); /* PRQA S 3112 */ /* MD_Rte_3112 */
  (void)Com_ReceiveShadowSignal(Com_Com_WhlPlsCnt_TmStmp, &(*(data)).WhlPlsCnt_TmStmp); /* PRQA S 3453, 3321 */ /* MD_MSR_19.7, MD_Rte_Qac */
  Rte_ComHook_Com_WhlPlsCnt_TmStmp_SigRx(&(*(data)).WhlPlsCnt_TmStmp); /* PRQA S 3112 */ /* MD_Rte_3112 */
  if (Rte_RxTimeoutFlags.Rte_RxTimeout_Com_Grp_WhlPlsCnt_TPM_Pr2_ci3hi3ex1xdl3zn6k2mcbudsp != 0)
  {
    ret |= RTE_E_MAX_AGE_EXCEEDED;
  }
  Rte_ReadHook_CtApHufTPMSmgr_R_WhlPlsCnt_TPM_Pr2_WhlPlsCnt_TPM_Pr2_Return(data); /* PRQA S 3112 */ /* MD_Rte_3112 */

  return ret;
} /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

FUNC(Std_ReturnType, RTE_CODE) Rte_Read_CtApHufTPMSwnh_PP_EnvData_DE_tEnvData(P2VAR(DT_tEnvData, AUTOMATIC, RTE_CTAPHUFTPMSWNH_APPL_VAR) data) /* PRQA S 0850, 3673, 1505 */ /* MD_MSR_19.8, MD_Rte_Qac, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  Rte_ReadHook_CtApHufTPMSwnh_PP_EnvData_DE_tEnvData_Start(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  *(data) = Rte_CpApHufTPMSmgr_PP_EnvData_DE_tEnvData;
  Rte_ReadHook_CtApHufTPMSwnh_PP_EnvData_DE_tEnvData_Return(data); /* PRQA S 3112 */ /* MD_Rte_3112 */

  return ret;
} /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

FUNC(Std_ReturnType, RTE_CODE) Rte_Read_CtApHufTPMSwpa_PP_EnvData_DE_tEnvData(P2VAR(DT_tEnvData, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) data) /* PRQA S 0850, 3673, 1505 */ /* MD_MSR_19.8, MD_Rte_Qac, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  Rte_ReadHook_CtApHufTPMSwpa_PP_EnvData_DE_tEnvData_Start(data); /* PRQA S 3112 */ /* MD_Rte_3112 */
  *(data) = Rte_CpApHufTPMSmgr_PP_EnvData_DE_tEnvData;
  Rte_ReadHook_CtApHufTPMSwpa_PP_EnvData_DE_tEnvData_Return(data); /* PRQA S 3112 */ /* MD_Rte_3112 */

  return ret;
} /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */


/**********************************************************************************************************************
 * COM-Callbacks for DataReceivedEvent triggered runnables, inter-ECU client/server communication, for queued com. and for Rx timeout / Rx inv. flag (reset)
 *********************************************************************************************************************/

FUNC(void, RTE_CODE) Rte_COMCbk_Com_AirPress_Outsd(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
  if (Rte_InitState == RTE_STATE_INIT)
  {
    Rte_ComHook_Com_AirPress_Outsd(); /* PRQA S 3112 */ /* MD_Rte_3112 */

    Rte_RxTimeoutFlags.Rte_RxTimeout_Com_AirPress_Outsd = 0;

    Rte_Task_SetEvent(HufTPMS_Task2, Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdEnvPressure); /* PRQA S 3112 */ /* MD_Rte_3112 */
    /* scheduled trigger for runnables: RCtApHufTPMSmgr_RdEnvPressure */
    (void)SetEvent(HufTPMS_Task2, Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdEnvPressure); /* PRQA S 3417 */ /* MD_Rte_Os */
  }
} /* PRQA S 6010, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCAL */

FUNC(void, RTE_CODE) Rte_COMCbk_Com_AirTemp_Outsd_Disp(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
  if (Rte_InitState == RTE_STATE_INIT)
  {
    Rte_ComHook_Com_AirTemp_Outsd_Disp(); /* PRQA S 3112 */ /* MD_Rte_3112 */

    Rte_RxTimeoutFlags.Rte_RxTimeout_Com_AirTemp_Outsd_Disp = 0;

    Rte_Task_SetEvent(HufTPMS_Task2, Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdEnvTemperature); /* PRQA S 3112 */ /* MD_Rte_3112 */
    /* scheduled trigger for runnables: RCtApHufTPMSmgr_RdEnvTemperature */
    (void)SetEvent(HufTPMS_Task2, Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdEnvTemperature); /* PRQA S 3417 */ /* MD_Rte_Os */
  }
} /* PRQA S 6010, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCAL */

FUNC(void, RTE_CODE) Rte_COMCbk_Com_DidA_ExtTest_Pres(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
  if (Rte_InitState == RTE_STATE_INIT)
  {
    Rte_ComHook_Com_DidA_ExtTest_Pres(); /* PRQA S 3112 */ /* MD_Rte_3112 */

    Rte_RxTimeoutFlags.Rte_RxTimeout_Com_DidA_ExtTest_Pres = 0;

    Rte_Task_SetEvent(HufTPMS_Task2, Rte_Ev_Run_CpApHufTPMSdia_RCtApHufTPMSdia_RdTesterPresent); /* PRQA S 3112 */ /* MD_Rte_3112 */
    /* scheduled trigger for runnables: RCtApHufTPMSdia_RdTesterPresent */
    (void)SetEvent(HufTPMS_Task2, Rte_Ev_Run_CpApHufTPMSdia_RCtApHufTPMSdia_RdTesterPresent); /* PRQA S 3417 */ /* MD_Rte_Os */
  }
} /* PRQA S 6010, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCAL */

FUNC(void, RTE_CODE) Rte_COMCbk_Com_Grp_DateTm_AR2_5h1zg0kdztpv8ox5dnrew2st8(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
  if (Rte_InitState == RTE_STATE_INIT)
  {
    Rte_ComHook_Com_Grp_DateTm_AR2_5h1zg0kdztpv8ox5dnrew2st8(); /* PRQA S 3112 */ /* MD_Rte_3112 */

    Rte_RxTimeoutFlags.Rte_RxTimeout_Com_Grp_DateTm_AR2_5h1zg0kdztpv8ox5dnrew2st8 = 0;

    Rte_Task_SetEvent(HufTPMS_Task2, Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdDateTm); /* PRQA S 3112 */ /* MD_Rte_3112 */
    /* scheduled trigger for runnables: RCtApHufTPMSmgr_RdDateTm */
    (void)SetEvent(HufTPMS_Task2, Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdDateTm); /* PRQA S 3417 */ /* MD_Rte_Os */
  }
} /* PRQA S 6010, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCAL */

FUNC(void, RTE_CODE) Rte_COMCbk_Com_Grp_EVC_CfgBit_01_32_Pr2_9rceoqjm3g6d48sc5qcm0ihhi(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
  if (Rte_InitState == RTE_STATE_INIT)
  {
    Rte_ComHook_Com_Grp_EVC_CfgBit_01_32_Pr2_9rceoqjm3g6d48sc5qcm0ihhi(); /* PRQA S 3112 */ /* MD_Rte_3112 */

    Rte_Task_SetEvent(HufTPMS_Task3, Rte_Ev_Run_CpApHufTPMSdia_RCtApHufTPMSdia_RdEvcCfgBit0132); /* PRQA S 3112 */ /* MD_Rte_3112 */
    /* scheduled trigger for runnables: RCtApHufTPMSdia_RdEvcCfgBit0132 */
    (void)SetEvent(HufTPMS_Task3, Rte_Ev_Run_CpApHufTPMSdia_RCtApHufTPMSdia_RdEvcCfgBit0132); /* PRQA S 3417 */ /* MD_Rte_Os */
  }
} /* PRQA S 6010, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCAL */

FUNC(void, RTE_CODE) Rte_COMCbk_Com_Grp_EVC_CfgList_01_0C_Pr2_3qvfhaj56jpqdd0izhj6fs0z3(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
  if (Rte_InitState == RTE_STATE_INIT)
  {
    Rte_ComHook_Com_Grp_EVC_CfgList_01_0C_Pr2_3qvfhaj56jpqdd0izhj6fs0z3(); /* PRQA S 3112 */ /* MD_Rte_3112 */

    Rte_Task_SetEvent(HufTPMS_Task3, Rte_Ev_Run_CpApHufTPMSdia_RCtApHufTPMSdia_RdEvcCfgBit010C); /* PRQA S 3112 */ /* MD_Rte_3112 */
    /* scheduled trigger for runnables: RCtApHufTPMSdia_RdEvcCfgBit010C */
    (void)SetEvent(HufTPMS_Task3, Rte_Ev_Run_CpApHufTPMSdia_RCtApHufTPMSdia_RdEvcCfgBit010C); /* PRQA S 3417 */ /* MD_Rte_Os */
  }
} /* PRQA S 6010, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCAL */

FUNC(void, RTE_CODE) Rte_COMCbk_Com_Grp_Eng_Rs_EngCtrl_Pr2_1g6e1wh7aspfj509n9mt9fl55(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
  if (Rte_InitState == RTE_STATE_INIT)
  {
    Rte_ComHook_Com_Grp_Eng_Rs_EngCtrl_Pr2_1g6e1wh7aspfj509n9mt9fl55(); /* PRQA S 3112 */ /* MD_Rte_3112 */

    Rte_RxTimeoutFlags.Rte_RxTimeout_Com_Grp_Eng_Rs_EngCtrl_Pr2_1g6e1wh7aspfj509n9mt9fl55 = 0;

    Rte_Task_SetEvent(HufTPMS_Task2, Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdEngCtrl); /* PRQA S 3112 */ /* MD_Rte_3112 */
    /* scheduled trigger for runnables: RCtApHufTPMSmgr_RdEngCtrl */
    (void)SetEvent(HufTPMS_Task2, Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdEngCtrl); /* PRQA S 3417 */ /* MD_Rte_Os */
  }
} /* PRQA S 6010, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCAL */

FUNC(void, RTE_CODE) Rte_COMCbk_Com_Grp_Ign_Stat_Pr2_457i75qk4uen9ahb37ecxdhxz(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
  if (Rte_InitState == RTE_STATE_INIT)
  {
    Rte_ComHook_Com_Grp_Ign_Stat_Pr2_457i75qk4uen9ahb37ecxdhxz(); /* PRQA S 3112 */ /* MD_Rte_3112 */

    Rte_RxTimeoutFlags.Rte_RxTimeout_Com_Grp_Ign_Stat_Pr2_457i75qk4uen9ahb37ecxdhxz = 0;

    Rte_Task_SetEvent(HufTPMS_Task2, Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdIgnStat); /* PRQA S 3112 */ /* MD_Rte_3112 */
    /* scheduled trigger for runnables: RCtApHufTPMSmgr_RdIgnStat */
    (void)SetEvent(HufTPMS_Task2, Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdIgnStat); /* PRQA S 3417 */ /* MD_Rte_Os */
  }
} /* PRQA S 6010, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCAL */

FUNC(void, RTE_CODE) Rte_COMCbk_Com_Grp_PN14_SupBat_Stat_aleu8fy7bsux9kh42xfztkzmi(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
  if (Rte_InitState == RTE_STATE_INIT)
  {
    Rte_ComHook_Com_Grp_PN14_SupBat_Stat_aleu8fy7bsux9kh42xfztkzmi(); /* PRQA S 3112 */ /* MD_Rte_3112 */

    Rte_RxTimeoutFlags.Rte_RxTimeout_Com_Grp_PN14_SupBat_Stat_aleu8fy7bsux9kh42xfztkzmi = 0;

    Rte_Task_SetEvent(HufTPMS_Task2, Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdSupPN14BatStat); /* PRQA S 3112 */ /* MD_Rte_3112 */
    /* scheduled trigger for runnables: RCtApHufTPMSmgr_RdSupPN14BatStat */
    (void)SetEvent(HufTPMS_Task2, Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdSupPN14BatStat); /* PRQA S 3417 */ /* MD_Rte_Os */
    Rte_Task_SetEvent(HufTPMS_Task3, Rte_Ev_Run_CpApHufTPMSdia_RCtApHufTPMSdia_PN14SupBatStat); /* PRQA S 3112 */ /* MD_Rte_3112 */
    /* scheduled trigger for runnables: RCtApHufTPMSdia_PN14SupBatStat */
    (void)SetEvent(HufTPMS_Task3, Rte_Ev_Run_CpApHufTPMSdia_RCtApHufTPMSdia_PN14SupBatStat); /* PRQA S 3417 */ /* MD_Rte_Os */
  }
} /* PRQA S 6010, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCAL */

FUNC(void, RTE_CODE) Rte_COMCbk_Com_Grp_WhlPlsCnt_TPM_Pr2_ci3hi3ex1xdl3zn6k2mcbudsp(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
  if (Rte_InitState == RTE_STATE_INIT)
  {
    Rte_ComHook_Com_Grp_WhlPlsCnt_TPM_Pr2_ci3hi3ex1xdl3zn6k2mcbudsp(); /* PRQA S 3112 */ /* MD_Rte_3112 */

    Rte_RxTimeoutFlags.Rte_RxTimeout_Com_Grp_WhlPlsCnt_TPM_Pr2_ci3hi3ex1xdl3zn6k2mcbudsp = 0;

    Rte_Task_SetEvent(HufTPMS_Task2, Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdWhlPlsCnt); /* PRQA S 3112 */ /* MD_Rte_3112 */
    /* scheduled trigger for runnables: RCtApHufTPMSmgr_RdWhlPlsCnt */
    (void)SetEvent(HufTPMS_Task2, Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdWhlPlsCnt); /* PRQA S 3417 */ /* MD_Rte_Os */
  }
} /* PRQA S 6010, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCAL */

FUNC(void, RTE_CODE) Rte_COMCbk_Com_Odo(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
  if (Rte_InitState == RTE_STATE_INIT)
  {
    Rte_ComHook_Com_Odo(); /* PRQA S 3112 */ /* MD_Rte_3112 */

    Rte_RxTimeoutFlags.Rte_RxTimeout_Com_Odo = 0;

    Rte_Task_SetEvent(HufTPMS_Task2, Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdOdo); /* PRQA S 3112 */ /* MD_Rte_3112 */
    /* scheduled trigger for runnables: RCtApHufTPMSmgr_RdOdo */
    (void)SetEvent(HufTPMS_Task2, Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdOdo); /* PRQA S 3417 */ /* MD_Rte_Os */
  }
} /* PRQA S 6010, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCAL */

FUNC(void, RTE_CODE) Rte_COMCbk_Com_PN14_EOL_Disp_Rq(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
  if (Rte_InitState == RTE_STATE_INIT)
  {
    Rte_ComHook_Com_PN14_EOL_Disp_Rq(); /* PRQA S 3112 */ /* MD_Rte_3112 */

    Rte_RxTimeoutFlags.Rte_RxTimeout_Com_PN14_EOL_Disp_Rq = 0;

    Rte_Task_SetEvent(HufTPMS_Task2, Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdPN14EOLDispRq); /* PRQA S 3112 */ /* MD_Rte_3112 */
    /* scheduled trigger for runnables: RCtApHufTPMSmgr_RdPN14EOLDispRq */
    (void)SetEvent(HufTPMS_Task2, Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdPN14EOLDispRq); /* PRQA S 3417 */ /* MD_Rte_Os */
  }
} /* PRQA S 6010, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCAL */

FUNC(void, RTE_CODE) Rte_COMCbk_Com_RevGr_Engg(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
  if (Rte_InitState == RTE_STATE_INIT)
  {
    Rte_ComHook_Com_RevGr_Engg(); /* PRQA S 3112 */ /* MD_Rte_3112 */

    Rte_RxTimeoutFlags.Rte_RxTimeout_Com_RevGr_Engg = 0;

    Rte_Task_SetEvent(HufTPMS_Task2, Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdGrBac); /* PRQA S 3112 */ /* MD_Rte_3112 */
    /* scheduled trigger for runnables: RCtApHufTPMSmgr_RdGrBac */
    (void)SetEvent(HufTPMS_Task2, Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdGrBac); /* PRQA S 3417 */ /* MD_Rte_Os */
  }
} /* PRQA S 6010, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCAL */

FUNC(void, RTE_CODE) Rte_COMCbk_Com_TPM_Actv_Rq_V2(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
  if (Rte_InitState == RTE_STATE_INIT)
  {
    Rte_ComHook_Com_TPM_Actv_Rq_V2(); /* PRQA S 3112 */ /* MD_Rte_3112 */

    Rte_RxTimeoutFlags.Rte_RxTimeout_Com_TPM_Actv_Rq_V2 = 0;

    Rte_Task_SetEvent(HufTPMS_Task2, Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdTpmActvRq); /* PRQA S 3112 */ /* MD_Rte_3112 */
    /* scheduled trigger for runnables: RCtApHufTPMSmgr_RdTpmActvRq */
    (void)SetEvent(HufTPMS_Task2, Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdTpmActvRq); /* PRQA S 3417 */ /* MD_Rte_Os */
  }
} /* PRQA S 6010, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCAL */

FUNC(void, RTE_CODE) Rte_COMCbk_Com_VehSpd_Disp(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
  if (Rte_InitState == RTE_STATE_INIT)
  {
    Rte_ComHook_Com_VehSpd_Disp(); /* PRQA S 3112 */ /* MD_Rte_3112 */

    Rte_RxTimeoutFlags.Rte_RxTimeout_Com_VehSpd_Disp = 0;

    Rte_Task_SetEvent(HufTPMS_Task2, Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdVehSpeed); /* PRQA S 3112 */ /* MD_Rte_3112 */
    /* scheduled trigger for runnables: RCtApHufTPMSmgr_RdVehSpeed */
    (void)SetEvent(HufTPMS_Task2, Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdVehSpeed); /* PRQA S 3417 */ /* MD_Rte_Os */
  }
} /* PRQA S 6010, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCAL */


/**********************************************************************************************************************
 * COM Callbacks for Rx Timeout Notification
 *********************************************************************************************************************/

#if RTE_COM_VERSION == 21U
FUNC(void, RTE_CODE) Rte_COMCbkTOut_Com_AirPress_Outsd(uint8 error) /* PRQA S 0850 */ /* MD_MSR_19.8 */
#else
FUNC(void, RTE_CODE) Rte_COMCbkTOut_Com_AirPress_Outsd(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
#endif
{
  Rte_ComHookTOut_Com_AirPress_Outsd(); /* PRQA S 3112 */ /* MD_Rte_3112 */

#if RTE_COM_VERSION == 21U
  if (error == COM_TIMEOUT)
#endif
  {
    Rte_RxTimeoutFlags.Rte_RxTimeout_Com_AirPress_Outsd = 1;

    if (Rte_InitState == RTE_STATE_INIT)
    {
      Rte_Task_SetEvent(HufTPMS_Task2, Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutEnvPressure); /* PRQA S 3112 */ /* MD_Rte_3112 */
      /* scheduled trigger for runnables: RCtApHufTPMSmgr_TimeOutEnvPressure */
      (void)SetEvent(HufTPMS_Task2, Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutEnvPressure); /* PRQA S 3417 */ /* MD_Rte_Os */
    }
  }
}

#if RTE_COM_VERSION == 21U
FUNC(void, RTE_CODE) Rte_COMCbkTOut_Com_AirTemp_Outsd_Disp(uint8 error) /* PRQA S 0850 */ /* MD_MSR_19.8 */
#else
FUNC(void, RTE_CODE) Rte_COMCbkTOut_Com_AirTemp_Outsd_Disp(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
#endif
{
  Rte_ComHookTOut_Com_AirTemp_Outsd_Disp(); /* PRQA S 3112 */ /* MD_Rte_3112 */

#if RTE_COM_VERSION == 21U
  if (error == COM_TIMEOUT)
#endif
  {
    Rte_RxTimeoutFlags.Rte_RxTimeout_Com_AirTemp_Outsd_Disp = 1;

    if (Rte_InitState == RTE_STATE_INIT)
    {
      Rte_Task_SetEvent(HufTPMS_Task2, Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutIcBasicInfo); /* PRQA S 3112 */ /* MD_Rte_3112 */
      /* scheduled trigger for runnables: RCtApHufTPMSmgr_TimeOutIcBasicInfo */
      (void)SetEvent(HufTPMS_Task2, Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutIcBasicInfo); /* PRQA S 3417 */ /* MD_Rte_Os */
    }
  }
}

#if RTE_COM_VERSION == 21U
FUNC(void, RTE_CODE) Rte_COMCbkTOut_Com_DidA_ExtTest_Pres(uint8 error) /* PRQA S 0850 */ /* MD_MSR_19.8 */
#else
FUNC(void, RTE_CODE) Rte_COMCbkTOut_Com_DidA_ExtTest_Pres(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
#endif
{
  Rte_ComHookTOut_Com_DidA_ExtTest_Pres(); /* PRQA S 3112 */ /* MD_Rte_3112 */

#if RTE_COM_VERSION == 21U
  if (error == COM_TIMEOUT)
#endif
  {
    Rte_RxTimeoutFlags.Rte_RxTimeout_Com_DidA_ExtTest_Pres = 1;
  }
}

#if RTE_COM_VERSION == 21U
FUNC(void, RTE_CODE) Rte_COMCbkTOut_Com_Grp_DateTm_AR2_5h1zg0kdztpv8ox5dnrew2st8(uint8 error) /* PRQA S 0850 */ /* MD_MSR_19.8 */
#else
FUNC(void, RTE_CODE) Rte_COMCbkTOut_Com_Grp_DateTm_AR2_5h1zg0kdztpv8ox5dnrew2st8(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
#endif
{
  Rte_ComHookTOut_Com_Grp_DateTm_AR2_5h1zg0kdztpv8ox5dnrew2st8(); /* PRQA S 3112 */ /* MD_Rte_3112 */

#if RTE_COM_VERSION == 21U
  if (error == COM_TIMEOUT)
#endif
  {
    Rte_RxTimeoutFlags.Rte_RxTimeout_Com_Grp_DateTm_AR2_5h1zg0kdztpv8ox5dnrew2st8 = 1;

    if (Rte_InitState == RTE_STATE_INIT)
    {
      Rte_Task_SetEvent(HufTPMS_Task2, Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutIcDateTime); /* PRQA S 3112 */ /* MD_Rte_3112 */
      /* scheduled trigger for runnables: RCtApHufTPMSmgr_TimeOutIcDateTime */
      (void)SetEvent(HufTPMS_Task2, Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutIcDateTime); /* PRQA S 3417 */ /* MD_Rte_Os */
    }
  }
}

#if RTE_COM_VERSION == 21U
FUNC(void, RTE_CODE) Rte_COMCbkTOut_Com_Grp_Eng_Rs_EngCtrl_Pr2_1g6e1wh7aspfj509n9mt9fl55(uint8 error) /* PRQA S 0850 */ /* MD_MSR_19.8 */
#else
FUNC(void, RTE_CODE) Rte_COMCbkTOut_Com_Grp_Eng_Rs_EngCtrl_Pr2_1g6e1wh7aspfj509n9mt9fl55(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
#endif
{
  Rte_ComHookTOut_Com_Grp_Eng_Rs_EngCtrl_Pr2_1g6e1wh7aspfj509n9mt9fl55(); /* PRQA S 3112 */ /* MD_Rte_3112 */

#if RTE_COM_VERSION == 21U
  if (error == COM_TIMEOUT)
#endif
  {
    Rte_RxTimeoutFlags.Rte_RxTimeout_Com_Grp_Eng_Rs_EngCtrl_Pr2_1g6e1wh7aspfj509n9mt9fl55 = 1;

    if (Rte_InitState == RTE_STATE_INIT)
    {
      Rte_Task_SetEvent(HufTPMS_Task2, Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutEngCtrl); /* PRQA S 3112 */ /* MD_Rte_3112 */
      /* scheduled trigger for runnables: RCtApHufTPMSmgr_TimeOutEngCtrl */
      (void)SetEvent(HufTPMS_Task2, Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutEngCtrl); /* PRQA S 3417 */ /* MD_Rte_Os */
    }
  }
}

#if RTE_COM_VERSION == 21U
FUNC(void, RTE_CODE) Rte_COMCbkTOut_Com_Grp_Ign_Stat_Pr2_457i75qk4uen9ahb37ecxdhxz(uint8 error) /* PRQA S 0850 */ /* MD_MSR_19.8 */
#else
FUNC(void, RTE_CODE) Rte_COMCbkTOut_Com_Grp_Ign_Stat_Pr2_457i75qk4uen9ahb37ecxdhxz(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
#endif
{
  Rte_ComHookTOut_Com_Grp_Ign_Stat_Pr2_457i75qk4uen9ahb37ecxdhxz(); /* PRQA S 3112 */ /* MD_Rte_3112 */

#if RTE_COM_VERSION == 21U
  if (error == COM_TIMEOUT)
#endif
  {
    Rte_RxTimeoutFlags.Rte_RxTimeout_Com_Grp_Ign_Stat_Pr2_457i75qk4uen9ahb37ecxdhxz = 1;

    if (Rte_InitState == RTE_STATE_INIT)
    {
      Rte_Task_SetEvent(HufTPMS_Task2, Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutIgnStat); /* PRQA S 3112 */ /* MD_Rte_3112 */
      /* scheduled trigger for runnables: RCtApHufTPMSmgr_TimeOutIgnStat */
      (void)SetEvent(HufTPMS_Task2, Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutIgnStat); /* PRQA S 3417 */ /* MD_Rte_Os */
    }
  }
}

#if RTE_COM_VERSION == 21U
FUNC(void, RTE_CODE) Rte_COMCbkTOut_Com_Grp_PN14_SupBat_Stat_aleu8fy7bsux9kh42xfztkzmi(uint8 error) /* PRQA S 0850 */ /* MD_MSR_19.8 */
#else
FUNC(void, RTE_CODE) Rte_COMCbkTOut_Com_Grp_PN14_SupBat_Stat_aleu8fy7bsux9kh42xfztkzmi(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
#endif
{
  Rte_ComHookTOut_Com_Grp_PN14_SupBat_Stat_aleu8fy7bsux9kh42xfztkzmi(); /* PRQA S 3112 */ /* MD_Rte_3112 */

#if RTE_COM_VERSION == 21U
  if (error == COM_TIMEOUT)
#endif
  {
    Rte_RxTimeoutFlags.Rte_RxTimeout_Com_Grp_PN14_SupBat_Stat_aleu8fy7bsux9kh42xfztkzmi = 1;

    if (Rte_InitState == RTE_STATE_INIT)
    {
      Rte_Task_SetEvent(HufTPMS_Task2, Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutSupPN14BatStat); /* PRQA S 3112 */ /* MD_Rte_3112 */
      /* scheduled trigger for runnables: RCtApHufTPMSmgr_TimeOutSupPN14BatStat */
      (void)SetEvent(HufTPMS_Task2, Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutSupPN14BatStat); /* PRQA S 3417 */ /* MD_Rte_Os */
    }
  }
}

#if RTE_COM_VERSION == 21U
FUNC(void, RTE_CODE) Rte_COMCbkTOut_Com_Grp_WhlPlsCnt_TPM_Pr2_ci3hi3ex1xdl3zn6k2mcbudsp(uint8 error) /* PRQA S 0850 */ /* MD_MSR_19.8 */
#else
FUNC(void, RTE_CODE) Rte_COMCbkTOut_Com_Grp_WhlPlsCnt_TPM_Pr2_ci3hi3ex1xdl3zn6k2mcbudsp(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
#endif
{
  Rte_ComHookTOut_Com_Grp_WhlPlsCnt_TPM_Pr2_ci3hi3ex1xdl3zn6k2mcbudsp(); /* PRQA S 3112 */ /* MD_Rte_3112 */

#if RTE_COM_VERSION == 21U
  if (error == COM_TIMEOUT)
#endif
  {
    Rte_RxTimeoutFlags.Rte_RxTimeout_Com_Grp_WhlPlsCnt_TPM_Pr2_ci3hi3ex1xdl3zn6k2mcbudsp = 1;

    if (Rte_InitState == RTE_STATE_INIT)
    {
      Rte_Task_SetEvent(HufTPMS_Task2, Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutWhlPlsCnt); /* PRQA S 3112 */ /* MD_Rte_3112 */
      /* scheduled trigger for runnables: RCtApHufTPMSmgr_TimeOutWhlPlsCnt */
      (void)SetEvent(HufTPMS_Task2, Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutWhlPlsCnt); /* PRQA S 3417 */ /* MD_Rte_Os */
    }
  }
}

#if RTE_COM_VERSION == 21U
FUNC(void, RTE_CODE) Rte_COMCbkTOut_Com_Odo(uint8 error) /* PRQA S 0850 */ /* MD_MSR_19.8 */
#else
FUNC(void, RTE_CODE) Rte_COMCbkTOut_Com_Odo(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
#endif
{
  Rte_ComHookTOut_Com_Odo(); /* PRQA S 3112 */ /* MD_Rte_3112 */

#if RTE_COM_VERSION == 21U
  if (error == COM_TIMEOUT)
#endif
  {
    Rte_RxTimeoutFlags.Rte_RxTimeout_Com_Odo = 1;

    if (Rte_InitState == RTE_STATE_INIT)
    {
      Rte_Task_SetEvent(HufTPMS_Task2, Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutIcBasicInfo); /* PRQA S 3112 */ /* MD_Rte_3112 */
      /* scheduled trigger for runnables: RCtApHufTPMSmgr_TimeOutIcBasicInfo */
      (void)SetEvent(HufTPMS_Task2, Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutIcBasicInfo); /* PRQA S 3417 */ /* MD_Rte_Os */
    }
  }
}

#if RTE_COM_VERSION == 21U
FUNC(void, RTE_CODE) Rte_COMCbkTOut_Com_PN14_EOL_Disp_Rq(uint8 error) /* PRQA S 0850 */ /* MD_MSR_19.8 */
#else
FUNC(void, RTE_CODE) Rte_COMCbkTOut_Com_PN14_EOL_Disp_Rq(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
#endif
{
  Rte_ComHookTOut_Com_PN14_EOL_Disp_Rq(); /* PRQA S 3112 */ /* MD_Rte_3112 */

#if RTE_COM_VERSION == 21U
  if (error == COM_TIMEOUT)
#endif
  {
    Rte_RxTimeoutFlags.Rte_RxTimeout_Com_PN14_EOL_Disp_Rq = 1;

    if (Rte_InitState == RTE_STATE_INIT)
    {
      Rte_Task_SetEvent(HufTPMS_Task2, Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutPN14EOLDispRq); /* PRQA S 3112 */ /* MD_Rte_3112 */
      /* scheduled trigger for runnables: RCtApHufTPMSmgr_TimeOutPN14EOLDispRq */
      (void)SetEvent(HufTPMS_Task2, Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutPN14EOLDispRq); /* PRQA S 3417 */ /* MD_Rte_Os */
    }
  }
}

#if RTE_COM_VERSION == 21U
FUNC(void, RTE_CODE) Rte_COMCbkTOut_Com_RevGr_Engg(uint8 error) /* PRQA S 0850 */ /* MD_MSR_19.8 */
#else
FUNC(void, RTE_CODE) Rte_COMCbkTOut_Com_RevGr_Engg(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
#endif
{
  Rte_ComHookTOut_Com_RevGr_Engg(); /* PRQA S 3112 */ /* MD_Rte_3112 */

#if RTE_COM_VERSION == 21U
  if (error == COM_TIMEOUT)
#endif
  {
    Rte_RxTimeoutFlags.Rte_RxTimeout_Com_RevGr_Engg = 1;
  }
}

#if RTE_COM_VERSION == 21U
FUNC(void, RTE_CODE) Rte_COMCbkTOut_Com_TPM_Actv_Rq_V2(uint8 error) /* PRQA S 0850 */ /* MD_MSR_19.8 */
#else
FUNC(void, RTE_CODE) Rte_COMCbkTOut_Com_TPM_Actv_Rq_V2(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
#endif
{
  Rte_ComHookTOut_Com_TPM_Actv_Rq_V2(); /* PRQA S 3112 */ /* MD_Rte_3112 */

#if RTE_COM_VERSION == 21U
  if (error == COM_TIMEOUT)
#endif
  {
    Rte_RxTimeoutFlags.Rte_RxTimeout_Com_TPM_Actv_Rq_V2 = 1;

    if (Rte_InitState == RTE_STATE_INIT)
    {
      Rte_Task_SetEvent(HufTPMS_Task2, Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutIcSettings); /* PRQA S 3112 */ /* MD_Rte_3112 */
      /* scheduled trigger for runnables: RCtApHufTPMSmgr_TimeOutIcSettings */
      (void)SetEvent(HufTPMS_Task2, Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutIcSettings); /* PRQA S 3417 */ /* MD_Rte_Os */
    }
  }
}

#if RTE_COM_VERSION == 21U
FUNC(void, RTE_CODE) Rte_COMCbkTOut_Com_VehSpd_Disp(uint8 error) /* PRQA S 0850 */ /* MD_MSR_19.8 */
#else
FUNC(void, RTE_CODE) Rte_COMCbkTOut_Com_VehSpd_Disp(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
#endif
{
  Rte_ComHookTOut_Com_VehSpd_Disp(); /* PRQA S 3112 */ /* MD_Rte_3112 */

#if RTE_COM_VERSION == 21U
  if (error == COM_TIMEOUT)
#endif
  {
    Rte_RxTimeoutFlags.Rte_RxTimeout_Com_VehSpd_Disp = 1;

    if (Rte_InitState == RTE_STATE_INIT)
    {
      Rte_Task_SetEvent(HufTPMS_Task2, Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutIcBasicInfo); /* PRQA S 3112 */ /* MD_Rte_3112 */
      /* scheduled trigger for runnables: RCtApHufTPMSmgr_TimeOutIcBasicInfo */
      (void)SetEvent(HufTPMS_Task2, Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutIcBasicInfo); /* PRQA S 3417 */ /* MD_Rte_Os */
    }
  }
}


/**********************************************************************************************************************
 * Task bodies for RTE controlled tasks
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Task:     HufTPMS_Task1
 * Priority: 7
 * Schedule: NON
 *********************************************************************************************************************/
TASK(HufTPMS_Task1) /* PRQA S 3408, 1503 */ /* MD_Rte_3408, MD_MSR_14.1 */
{
  Rte_Task_Dispatch(HufTPMS_Task1); /* PRQA S 3112 */ /* MD_Rte_3112 */

  /* call runnable */
  Rte_Runnable_CtApHufTPMSwpa_RCtApHufTPMSwpa_Init_Start(); /* PRQA S 3112 */ /* MD_Rte_3112 */
  RCtApHufTPMSwpa_Init();
  Rte_Runnable_CtApHufTPMSwpa_RCtApHufTPMSwpa_Init_Return(); /* PRQA S 3112 */ /* MD_Rte_3112 */

  /* call runnable */
  Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_Init_Start(); /* PRQA S 3112 */ /* MD_Rte_3112 */
  RCtApHufTPMSmgr_Init();
  Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_Init_Return(); /* PRQA S 3112 */ /* MD_Rte_3112 */

  /* call runnable */
  Rte_Runnable_CtApHufTPMSwnh_RCtApHufTPMSwnh_Init_Start(); /* PRQA S 3112 */ /* MD_Rte_3112 */
  RCtApHufTPMSwnh_Init();
  Rte_Runnable_CtApHufTPMSwnh_RCtApHufTPMSwnh_Init_Return(); /* PRQA S 3112 */ /* MD_Rte_3112 */

  /* call runnable */
  Rte_Runnable_CtApHufTPMSdia_CtApHufTPMSdia_Init_Start(); /* PRQA S 3112 */ /* MD_Rte_3112 */
  CtApHufTPMSdia_Init();
  Rte_Runnable_CtApHufTPMSdia_CtApHufTPMSdia_Init_Return(); /* PRQA S 3112 */ /* MD_Rte_3112 */

  /* call runnable */
  Rte_Runnable_CtApHufTPMSroe_RCtApHufTPMSroe_Init_Start(); /* PRQA S 3112 */ /* MD_Rte_3112 */
  RCtApHufTPMSroe_Init();
  Rte_Runnable_CtApHufTPMSroe_RCtApHufTPMSroe_Init_Return(); /* PRQA S 3112 */ /* MD_Rte_3112 */

  (void)TerminateTask(); /* PRQA S 3417 */ /* MD_Rte_Os */
} /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

/**********************************************************************************************************************
 * Task:     HufTPMS_Task2
 * Priority: 6
 * Schedule: NON
 *********************************************************************************************************************/
TASK(HufTPMS_Task2) /* PRQA S 3408, 1503 */ /* MD_Rte_3408, MD_MSR_14.1 */
{
  EventMaskType ev;

  Rte_Task_Dispatch(HufTPMS_Task2); /* PRQA S 3112 */ /* MD_Rte_3112 */

  for(;;)
  {
    Rte_Task_WaitEvent(HufTPMS_Task2, Rte_Ev_Run_CpApHufTPMSdia_RCtApHufTPMSdia_RdTesterPresent | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdDateTm | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdEngCtrl | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdEnvPressure | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdEnvTemperature | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdGrBac | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdIgnStat | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdOdo | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdPN14EOLDispRq | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdSupPN14BatStat | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdTpmActvRq | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdVehSpeed | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdWhlPlsCnt | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutEngCtrl | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutEnvPressure | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutIcBasicInfo | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutIcDateTime | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutIcSettings | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutIgnStat | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutPN14EOLDispRq | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutSupPN14BatStat | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutWhlPlsCnt | Rte_Ev_Run_CpCdHufTPMSrfd_RCtCdHufTPMSrfd_ChkRfStruct); /* PRQA S 3112 */ /* MD_Rte_3112 */
    (void)WaitEvent(Rte_Ev_Run_CpApHufTPMSdia_RCtApHufTPMSdia_RdTesterPresent | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdDateTm | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdEngCtrl | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdEnvPressure | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdEnvTemperature | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdGrBac | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdIgnStat | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdOdo | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdPN14EOLDispRq | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdSupPN14BatStat | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdTpmActvRq | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdVehSpeed | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdWhlPlsCnt | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutEngCtrl | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutEnvPressure | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutIcBasicInfo | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutIcDateTime | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutIcSettings | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutIgnStat | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutPN14EOLDispRq | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutSupPN14BatStat | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutWhlPlsCnt | Rte_Ev_Run_CpCdHufTPMSrfd_RCtCdHufTPMSrfd_ChkRfStruct); /* PRQA S 3417 */ /* MD_Rte_Os */
    Rte_Task_WaitEventRet(HufTPMS_Task2, Rte_Ev_Run_CpApHufTPMSdia_RCtApHufTPMSdia_RdTesterPresent | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdDateTm | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdEngCtrl | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdEnvPressure | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdEnvTemperature | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdGrBac | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdIgnStat | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdOdo | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdPN14EOLDispRq | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdSupPN14BatStat | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdTpmActvRq | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdVehSpeed | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdWhlPlsCnt | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutEngCtrl | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutEnvPressure | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutIcBasicInfo | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutIcDateTime | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutIcSettings | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutIgnStat | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutPN14EOLDispRq | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutSupPN14BatStat | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutWhlPlsCnt | Rte_Ev_Run_CpCdHufTPMSrfd_RCtCdHufTPMSrfd_ChkRfStruct); /* PRQA S 3112 */ /* MD_Rte_3112 */
    (void)GetEvent(HufTPMS_Task2, &ev); /* PRQA S 3417 */ /* MD_Rte_Os */
    (void)ClearEvent(ev & (Rte_Ev_Run_CpApHufTPMSdia_RCtApHufTPMSdia_RdTesterPresent | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdDateTm | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdEngCtrl | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdEnvPressure | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdEnvTemperature | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdGrBac | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdIgnStat | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdOdo | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdPN14EOLDispRq | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdSupPN14BatStat | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdTpmActvRq | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdVehSpeed | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdWhlPlsCnt | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutEngCtrl | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutEnvPressure | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutIcBasicInfo | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutIcDateTime | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutIcSettings | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutIgnStat | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutPN14EOLDispRq | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutSupPN14BatStat | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutWhlPlsCnt | Rte_Ev_Run_CpCdHufTPMSrfd_RCtCdHufTPMSrfd_ChkRfStruct)); /* PRQA S 3417 */ /* MD_Rte_Os */

    if ((ev & Rte_Ev_Run_CpCdHufTPMSrfd_RCtCdHufTPMSrfd_ChkRfStruct) != (EventMaskType)0)
    {
      /* call runnable */
      Rte_Runnable_CtCdHufTPMSrfd_RCtCdHufTPMSrfd_ChkRfStruct_Start(); /* PRQA S 3112 */ /* MD_Rte_3112 */
      RCtCdHufTPMSrfd_ChkRfStruct();
      Rte_Runnable_CtCdHufTPMSrfd_RCtCdHufTPMSrfd_ChkRfStruct_Return(); /* PRQA S 3112 */ /* MD_Rte_3112 */

      (void)Schedule(); /* PRQA S 3417 */ /* MD_Rte_Os */
    }

    if ((ev & Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdIgnStat) != (EventMaskType)0)
    {
      /* call runnable */
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_RdIgnStat_Start(); /* PRQA S 3112 */ /* MD_Rte_3112 */
      RCtApHufTPMSmgr_RdIgnStat();
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_RdIgnStat_Return(); /* PRQA S 3112 */ /* MD_Rte_3112 */

      (void)Schedule(); /* PRQA S 3417 */ /* MD_Rte_Os */
    }

    if ((ev & Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdWhlPlsCnt) != (EventMaskType)0)
    {
      /* call runnable */
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_RdWhlPlsCnt_Start(); /* PRQA S 3112 */ /* MD_Rte_3112 */
      RCtApHufTPMSmgr_RdWhlPlsCnt();
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_RdWhlPlsCnt_Return(); /* PRQA S 3112 */ /* MD_Rte_3112 */

      (void)Schedule(); /* PRQA S 3417 */ /* MD_Rte_Os */
    }

    if ((ev & Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdGrBac) != (EventMaskType)0)
    {
      /* call runnable */
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_RdGrBac_Start(); /* PRQA S 3112 */ /* MD_Rte_3112 */
      RCtApHufTPMSmgr_RdGrBac();
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_RdGrBac_Return(); /* PRQA S 3112 */ /* MD_Rte_3112 */

      (void)Schedule(); /* PRQA S 3417 */ /* MD_Rte_Os */
    }

    if ((ev & Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdVehSpeed) != (EventMaskType)0)
    {
      /* call runnable */
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_RdVehSpeed_Start(); /* PRQA S 3112 */ /* MD_Rte_3112 */
      RCtApHufTPMSmgr_RdVehSpeed();
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_RdVehSpeed_Return(); /* PRQA S 3112 */ /* MD_Rte_3112 */

      (void)Schedule(); /* PRQA S 3417 */ /* MD_Rte_Os */
    }

    if ((ev & Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdEnvTemperature) != (EventMaskType)0)
    {
      /* call runnable */
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_RdEnvTemperature_Start(); /* PRQA S 3112 */ /* MD_Rte_3112 */
      RCtApHufTPMSmgr_RdEnvTemperature();
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_RdEnvTemperature_Return(); /* PRQA S 3112 */ /* MD_Rte_3112 */

      (void)Schedule(); /* PRQA S 3417 */ /* MD_Rte_Os */
    }

    if ((ev & Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdEnvPressure) != (EventMaskType)0)
    {
      /* call runnable */
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_RdEnvPressure_Start(); /* PRQA S 3112 */ /* MD_Rte_3112 */
      RCtApHufTPMSmgr_RdEnvPressure();
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_RdEnvPressure_Return(); /* PRQA S 3112 */ /* MD_Rte_3112 */

      (void)Schedule(); /* PRQA S 3417 */ /* MD_Rte_Os */
    }

    if ((ev & Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdOdo) != (EventMaskType)0)
    {
      /* call runnable */
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_RdOdo_Start(); /* PRQA S 3112 */ /* MD_Rte_3112 */
      RCtApHufTPMSmgr_RdOdo();
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_RdOdo_Return(); /* PRQA S 3112 */ /* MD_Rte_3112 */

      (void)Schedule(); /* PRQA S 3417 */ /* MD_Rte_Os */
    }

    if ((ev & Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdTpmActvRq) != (EventMaskType)0)
    {
      /* call runnable */
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_RdTpmActvRq_Start(); /* PRQA S 3112 */ /* MD_Rte_3112 */
      RCtApHufTPMSmgr_RdTpmActvRq();
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_RdTpmActvRq_Return(); /* PRQA S 3112 */ /* MD_Rte_3112 */

      (void)Schedule(); /* PRQA S 3417 */ /* MD_Rte_Os */
    }

    if ((ev & Rte_Ev_Run_CpApHufTPMSdia_RCtApHufTPMSdia_RdTesterPresent) != (EventMaskType)0)
    {
      /* call runnable */
      Rte_Runnable_CtApHufTPMSdia_RCtApHufTPMSdia_RdTesterPresent_Start(); /* PRQA S 3112 */ /* MD_Rte_3112 */
      RCtApHufTPMSdia_RdTesterPresent();
      Rte_Runnable_CtApHufTPMSdia_RCtApHufTPMSdia_RdTesterPresent_Return(); /* PRQA S 3112 */ /* MD_Rte_3112 */

      (void)Schedule(); /* PRQA S 3417 */ /* MD_Rte_Os */
    }

    if ((ev & Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdSupPN14BatStat) != (EventMaskType)0)
    {
      /* call runnable */
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_RdSupPN14BatStat_Start(); /* PRQA S 3112 */ /* MD_Rte_3112 */
      RCtApHufTPMSmgr_RdSupPN14BatStat();
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_RdSupPN14BatStat_Return(); /* PRQA S 3112 */ /* MD_Rte_3112 */

      (void)Schedule(); /* PRQA S 3417 */ /* MD_Rte_Os */
    }

    if ((ev & Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdEngCtrl) != (EventMaskType)0)
    {
      /* call runnable */
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_RdEngCtrl_Start(); /* PRQA S 3112 */ /* MD_Rte_3112 */
      RCtApHufTPMSmgr_RdEngCtrl();
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_RdEngCtrl_Return(); /* PRQA S 3112 */ /* MD_Rte_3112 */

      (void)Schedule(); /* PRQA S 3417 */ /* MD_Rte_Os */
    }

    if ((ev & Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdDateTm) != (EventMaskType)0)
    {
      /* call runnable */
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_RdDateTm_Start(); /* PRQA S 3112 */ /* MD_Rte_3112 */
      RCtApHufTPMSmgr_RdDateTm();
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_RdDateTm_Return(); /* PRQA S 3112 */ /* MD_Rte_3112 */

      (void)Schedule(); /* PRQA S 3417 */ /* MD_Rte_Os */
    }

    if ((ev & Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutWhlPlsCnt) != (EventMaskType)0)
    {
      /* call runnable */
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutWhlPlsCnt_Start(); /* PRQA S 3112 */ /* MD_Rte_3112 */
      RCtApHufTPMSmgr_TimeOutWhlPlsCnt();
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutWhlPlsCnt_Return(); /* PRQA S 3112 */ /* MD_Rte_3112 */

      (void)Schedule(); /* PRQA S 3417 */ /* MD_Rte_Os */
    }

    if ((ev & Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutIgnStat) != (EventMaskType)0)
    {
      /* call runnable */
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutIgnStat_Start(); /* PRQA S 3112 */ /* MD_Rte_3112 */
      RCtApHufTPMSmgr_TimeOutIgnStat();
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutIgnStat_Return(); /* PRQA S 3112 */ /* MD_Rte_3112 */

      (void)Schedule(); /* PRQA S 3417 */ /* MD_Rte_Os */
    }

    if ((ev & Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutEngCtrl) != (EventMaskType)0)
    {
      /* call runnable */
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutEngCtrl_Start(); /* PRQA S 3112 */ /* MD_Rte_3112 */
      RCtApHufTPMSmgr_TimeOutEngCtrl();
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutEngCtrl_Return(); /* PRQA S 3112 */ /* MD_Rte_3112 */

      (void)Schedule(); /* PRQA S 3417 */ /* MD_Rte_Os */
    }

    if ((ev & Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutIcSettings) != (EventMaskType)0)
    {
      /* call runnable */
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutIcSettings_Start(); /* PRQA S 3112 */ /* MD_Rte_3112 */
      RCtApHufTPMSmgr_TimeOutIcSettings();
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutIcSettings_Return(); /* PRQA S 3112 */ /* MD_Rte_3112 */

      (void)Schedule(); /* PRQA S 3417 */ /* MD_Rte_Os */
    }

    if ((ev & Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutSupPN14BatStat) != (EventMaskType)0)
    {
      /* call runnable */
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutSupPN14BatStat_Start(); /* PRQA S 3112 */ /* MD_Rte_3112 */
      RCtApHufTPMSmgr_TimeOutSupPN14BatStat();
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutSupPN14BatStat_Return(); /* PRQA S 3112 */ /* MD_Rte_3112 */

      (void)Schedule(); /* PRQA S 3417 */ /* MD_Rte_Os */
    }

    if ((ev & Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutEnvPressure) != (EventMaskType)0)
    {
      /* call runnable */
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutEnvPressure_Start(); /* PRQA S 3112 */ /* MD_Rte_3112 */
      RCtApHufTPMSmgr_TimeOutEnvPressure();
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutEnvPressure_Return(); /* PRQA S 3112 */ /* MD_Rte_3112 */

      (void)Schedule(); /* PRQA S 3417 */ /* MD_Rte_Os */
    }

    if ((ev & Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutIcDateTime) != (EventMaskType)0)
    {
      /* call runnable */
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutIcDateTime_Start(); /* PRQA S 3112 */ /* MD_Rte_3112 */
      RCtApHufTPMSmgr_TimeOutIcDateTime();
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutIcDateTime_Return(); /* PRQA S 3112 */ /* MD_Rte_3112 */

      (void)Schedule(); /* PRQA S 3417 */ /* MD_Rte_Os */
    }

    if ((ev & Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutIcBasicInfo) != (EventMaskType)0)
    {
      /* call runnable */
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutIcBasicInfo_Start(); /* PRQA S 3112 */ /* MD_Rte_3112 */
      RCtApHufTPMSmgr_TimeOutIcBasicInfo();
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutIcBasicInfo_Return(); /* PRQA S 3112 */ /* MD_Rte_3112 */

      (void)Schedule(); /* PRQA S 3417 */ /* MD_Rte_Os */
    }

    if ((ev & Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_RdPN14EOLDispRq) != (EventMaskType)0)
    {
      /* call runnable */
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_RdPN14EOLDispRq_Start(); /* PRQA S 3112 */ /* MD_Rte_3112 */
      RCtApHufTPMSmgr_RdPN14EOLDispRq();
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_RdPN14EOLDispRq_Return(); /* PRQA S 3112 */ /* MD_Rte_3112 */

      (void)Schedule(); /* PRQA S 3417 */ /* MD_Rte_Os */
    }

    if ((ev & Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutPN14EOLDispRq) != (EventMaskType)0)
    {
      /* call runnable */
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutPN14EOLDispRq_Start(); /* PRQA S 3112 */ /* MD_Rte_3112 */
      RCtApHufTPMSmgr_TimeOutPN14EOLDispRq();
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_TimeOutPN14EOLDispRq_Return(); /* PRQA S 3112 */ /* MD_Rte_3112 */

      (void)Schedule(); /* PRQA S 3417 */ /* MD_Rte_Os */
    }
  }
} /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

/**********************************************************************************************************************
 * Task:     HufTPMS_Task3
 * Priority: 5
 * Schedule: NON
 *********************************************************************************************************************/
TASK(HufTPMS_Task3) /* PRQA S 3408, 1503 */ /* MD_Rte_3408, MD_MSR_14.1 */
{
  EventMaskType ev;
  EventMaskType evRun;

  Rte_Task_Dispatch(HufTPMS_Task3); /* PRQA S 3112 */ /* MD_Rte_3112 */

  for(;;)
  {
    Rte_Task_WaitEvent(HufTPMS_Task3, Rte_Ev_OnRx_HufTPMS_Task3_CpApHufTPMSmgr_PP_EnvData_DE_tEnvData | Rte_Ev_Run_CpApHufTPMSdia_RCtApHufTPMSdia_PN14SupBatStat | Rte_Ev_Run_CpApHufTPMSdia_RCtApHufTPMSdia_RdEvcCfgBit010C | Rte_Ev_Run_CpApHufTPMSdia_RCtApHufTPMSdia_RdEvcCfgBit0132 | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_ReceiveTelData | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_WrDisplayMsg); /* PRQA S 3112 */ /* MD_Rte_3112 */
    (void)WaitEvent(Rte_Ev_OnRx_HufTPMS_Task3_CpApHufTPMSmgr_PP_EnvData_DE_tEnvData | Rte_Ev_Run_CpApHufTPMSdia_RCtApHufTPMSdia_PN14SupBatStat | Rte_Ev_Run_CpApHufTPMSdia_RCtApHufTPMSdia_RdEvcCfgBit010C | Rte_Ev_Run_CpApHufTPMSdia_RCtApHufTPMSdia_RdEvcCfgBit0132 | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_ReceiveTelData | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_WrDisplayMsg); /* PRQA S 3417 */ /* MD_Rte_Os */
    Rte_Task_WaitEventRet(HufTPMS_Task3, Rte_Ev_OnRx_HufTPMS_Task3_CpApHufTPMSmgr_PP_EnvData_DE_tEnvData | Rte_Ev_Run_CpApHufTPMSdia_RCtApHufTPMSdia_PN14SupBatStat | Rte_Ev_Run_CpApHufTPMSdia_RCtApHufTPMSdia_RdEvcCfgBit010C | Rte_Ev_Run_CpApHufTPMSdia_RCtApHufTPMSdia_RdEvcCfgBit0132 | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_ReceiveTelData | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_WrDisplayMsg); /* PRQA S 3112 */ /* MD_Rte_3112 */
    (void)GetEvent(HufTPMS_Task3, &ev); /* PRQA S 3417 */ /* MD_Rte_Os */
    (void)ClearEvent(ev & (Rte_Ev_OnRx_HufTPMS_Task3_CpApHufTPMSmgr_PP_EnvData_DE_tEnvData | Rte_Ev_Run_CpApHufTPMSdia_RCtApHufTPMSdia_PN14SupBatStat | Rte_Ev_Run_CpApHufTPMSdia_RCtApHufTPMSdia_RdEvcCfgBit010C | Rte_Ev_Run_CpApHufTPMSdia_RCtApHufTPMSdia_RdEvcCfgBit0132 | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_ReceiveTelData | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_WrDisplayMsg)); /* PRQA S 3417 */ /* MD_Rte_Os */

    if ((ev & Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_ReceiveTelData) != (EventMaskType)0)
    {
      /* call runnable */
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_ReceiveTelData_Start(); /* PRQA S 3112 */ /* MD_Rte_3112 */
      RCtApHufTPMSmgr_ReceiveTelData();
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_ReceiveTelData_Return(); /* PRQA S 3112 */ /* MD_Rte_3112 */

      (void)Schedule(); /* PRQA S 3417 */ /* MD_Rte_Os */
    }

    if ((ev & Rte_Ev_OnRx_HufTPMS_Task3_CpApHufTPMSmgr_PP_EnvData_DE_tEnvData) != (EventMaskType)0)
    {
      /* call runnable */
      Rte_Runnable_CtApHufTPMSwpa_RCtApHufTPMSwpa_ReceiveEnvData_Start(); /* PRQA S 3112 */ /* MD_Rte_3112 */
      RCtApHufTPMSwpa_ReceiveEnvData();
      Rte_Runnable_CtApHufTPMSwpa_RCtApHufTPMSwpa_ReceiveEnvData_Return(); /* PRQA S 3112 */ /* MD_Rte_3112 */

      (void)Schedule(); /* PRQA S 3417 */ /* MD_Rte_Os */

      /* call runnable */
      Rte_Runnable_CtApHufTPMSwnh_RCtApHufTPMSwnh_ReceiveEnvData_Start(); /* PRQA S 3112 */ /* MD_Rte_3112 */
      RCtApHufTPMSwnh_ReceiveEnvData();
      Rte_Runnable_CtApHufTPMSwnh_RCtApHufTPMSwnh_ReceiveEnvData_Return(); /* PRQA S 3112 */ /* MD_Rte_3112 */

      (void)Schedule(); /* PRQA S 3417 */ /* MD_Rte_Os */
    }

    (void)GetEvent(HufTPMS_Task3, &evRun); /* PRQA S 3417 */ /* MD_Rte_Os */
    if ((evRun & Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_ReceiveWAState) != (EventMaskType)0)
    {
      /* call runnable */
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_ReceiveWAState_Start(); /* PRQA S 3112 */ /* MD_Rte_3112 */
      RCtApHufTPMSmgr_ReceiveWAState();
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_ReceiveWAState_Return(); /* PRQA S 3112 */ /* MD_Rte_3112 */

      (void)Schedule(); /* PRQA S 3417 */ /* MD_Rte_Os */
      (void)ClearEvent(evRun & Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_ReceiveWAState); /* PRQA S 3417 */ /* MD_Rte_Os */
    }

    (void)GetEvent(HufTPMS_Task3, &evRun); /* PRQA S 3417 */ /* MD_Rte_Os */
    if ((evRun & Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_ReceiveWarnOut) != (EventMaskType)0)
    {
      /* call runnable */
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_ReceiveWarnOut_Start(); /* PRQA S 3112 */ /* MD_Rte_3112 */
      RCtApHufTPMSmgr_ReceiveWarnOut();
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_ReceiveWarnOut_Return(); /* PRQA S 3112 */ /* MD_Rte_3112 */

      (void)Schedule(); /* PRQA S 3417 */ /* MD_Rte_Os */
      (void)ClearEvent(evRun & Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_ReceiveWarnOut); /* PRQA S 3417 */ /* MD_Rte_Os */
    }

    if ((ev & Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_WrDisplayMsg) != (EventMaskType)0)
    {
      /* call runnable */
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_WrDisplayMsg_Start(); /* PRQA S 3112 */ /* MD_Rte_3112 */
      RCtApHufTPMSmgr_WrDisplayMsg();
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_WrDisplayMsg_Return(); /* PRQA S 3112 */ /* MD_Rte_3112 */

      (void)Schedule(); /* PRQA S 3417 */ /* MD_Rte_Os */
    }

    (void)GetEvent(HufTPMS_Task3, &evRun); /* PRQA S 3417 */ /* MD_Rte_Os */
    if ((evRun & Rte_Ev_Run_CpApHufTPMSdia_RCtApHufTPMSdia_ReceiveTelData) != (EventMaskType)0)
    {
      /* call runnable */
      Rte_Runnable_CtApHufTPMSdia_RCtApHufTPMSdia_ReceiveTelData_Start(); /* PRQA S 3112 */ /* MD_Rte_3112 */
      RCtApHufTPMSdia_ReceiveTelData();
      Rte_Runnable_CtApHufTPMSdia_RCtApHufTPMSdia_ReceiveTelData_Return(); /* PRQA S 3112 */ /* MD_Rte_3112 */

      (void)Schedule(); /* PRQA S 3417 */ /* MD_Rte_Os */
      (void)ClearEvent(evRun & Rte_Ev_Run_CpApHufTPMSdia_RCtApHufTPMSdia_ReceiveTelData); /* PRQA S 3417 */ /* MD_Rte_Os */
    }

    if ((ev & Rte_Ev_Run_CpApHufTPMSdia_RCtApHufTPMSdia_RdEvcCfgBit0132) != (EventMaskType)0)
    {
      /* call runnable */
      Rte_Runnable_CtApHufTPMSdia_RCtApHufTPMSdia_RdEvcCfgBit0132_Start(); /* PRQA S 3112 */ /* MD_Rte_3112 */
      RCtApHufTPMSdia_RdEvcCfgBit0132();
      Rte_Runnable_CtApHufTPMSdia_RCtApHufTPMSdia_RdEvcCfgBit0132_Return(); /* PRQA S 3112 */ /* MD_Rte_3112 */

      (void)Schedule(); /* PRQA S 3417 */ /* MD_Rte_Os */
    }

    if ((ev & Rte_Ev_Run_CpApHufTPMSdia_RCtApHufTPMSdia_RdEvcCfgBit010C) != (EventMaskType)0)
    {
      /* call runnable */
      Rte_Runnable_CtApHufTPMSdia_RCtApHufTPMSdia_RdEvcCfgBit010C_Start(); /* PRQA S 3112 */ /* MD_Rte_3112 */
      RCtApHufTPMSdia_RdEvcCfgBit010C();
      Rte_Runnable_CtApHufTPMSdia_RCtApHufTPMSdia_RdEvcCfgBit010C_Return(); /* PRQA S 3112 */ /* MD_Rte_3112 */

      (void)Schedule(); /* PRQA S 3417 */ /* MD_Rte_Os */
    }

    if ((ev & Rte_Ev_Run_CpApHufTPMSdia_RCtApHufTPMSdia_PN14SupBatStat) != (EventMaskType)0)
    {
      /* call runnable */
      Rte_Runnable_CtApHufTPMSdia_RCtApHufTPMSdia_PN14SupBatStat_Start(); /* PRQA S 3112 */ /* MD_Rte_3112 */
      RCtApHufTPMSdia_PN14SupBatStat();
      Rte_Runnable_CtApHufTPMSdia_RCtApHufTPMSdia_PN14SupBatStat_Return(); /* PRQA S 3112 */ /* MD_Rte_3112 */

      (void)Schedule(); /* PRQA S 3417 */ /* MD_Rte_Os */
    }
  }
} /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

/**********************************************************************************************************************
 * Task:     HufTPMS_Task4
 * Priority: 4
 * Schedule: NON
 *********************************************************************************************************************/
TASK(HufTPMS_Task4) /* PRQA S 3408, 1503 */ /* MD_Rte_3408, MD_MSR_14.1 */
{
  EventMaskType ev;

  Rte_Task_Dispatch(HufTPMS_Task4); /* PRQA S 3112 */ /* MD_Rte_3112 */

  for(;;)
  {
    Rte_Task_WaitEvent(HufTPMS_Task4, Rte_Ev_Cyclic_HufTPMS_Task4_0_1s | Rte_Ev_Cyclic_HufTPMS_Task4_0_200ms | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_GenInternalClock); /* PRQA S 3112 */ /* MD_Rte_3112 */
    (void)WaitEvent(Rte_Ev_Cyclic_HufTPMS_Task4_0_1s | Rte_Ev_Cyclic_HufTPMS_Task4_0_200ms | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_GenInternalClock); /* PRQA S 3417 */ /* MD_Rte_Os */
    Rte_Task_WaitEventRet(HufTPMS_Task4, Rte_Ev_Cyclic_HufTPMS_Task4_0_1s | Rte_Ev_Cyclic_HufTPMS_Task4_0_200ms | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_GenInternalClock); /* PRQA S 3112 */ /* MD_Rte_3112 */
    (void)GetEvent(HufTPMS_Task4, &ev); /* PRQA S 3417 */ /* MD_Rte_Os */
    (void)ClearEvent(ev & (Rte_Ev_Cyclic_HufTPMS_Task4_0_1s | Rte_Ev_Cyclic_HufTPMS_Task4_0_200ms | Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_GenInternalClock)); /* PRQA S 3417 */ /* MD_Rte_Os */

    if ((ev & Rte_Ev_Run_CpApHufTPMSmgr_RCtApHufTPMSmgr_GenInternalClock) != (EventMaskType)0)
    {
      /* call runnable */
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_GenInternalClock_Start(); /* PRQA S 3112 */ /* MD_Rte_3112 */
      RCtApHufTPMSmgr_GenInternalClock();
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_GenInternalClock_Return(); /* PRQA S 3112 */ /* MD_Rte_3112 */

      (void)Schedule(); /* PRQA S 3417 */ /* MD_Rte_Os */
    }

    if ((ev & Rte_Ev_Cyclic_HufTPMS_Task4_0_1s) != (EventMaskType)0)
    {
      /* call runnable */
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_ControlEcuStandbyTimer_Start(); /* PRQA S 3112 */ /* MD_Rte_3112 */
      RCtApHufTPMSmgr_ControlEcuStandbyTimer();
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_ControlEcuStandbyTimer_Return(); /* PRQA S 3112 */ /* MD_Rte_3112 */

      (void)Schedule(); /* PRQA S 3417 */ /* MD_Rte_Os */

      /* call runnable */
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_WrBusMsg_Start(); /* PRQA S 3112 */ /* MD_Rte_3112 */
      RCtApHufTPMSmgr_WrBusMsg();
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_WrBusMsg_Return(); /* PRQA S 3112 */ /* MD_Rte_3112 */

      (void)Schedule(); /* PRQA S 3417 */ /* MD_Rte_Os */

      /* call runnable */
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_WrTpmMsgDispRq_Start(); /* PRQA S 3112 */ /* MD_Rte_3112 */
      RCtApHufTPMSmgr_WrTpmMsgDispRq();
      Rte_Runnable_CtApHufTPMSmgr_RCtApHufTPMSmgr_WrTpmMsgDispRq_Return(); /* PRQA S 3112 */ /* MD_Rte_3112 */

      (void)Schedule(); /* PRQA S 3417 */ /* MD_Rte_Os */

      /* call runnable */
      Rte_Runnable_CtApHufTPMSwpa_RCtApHufTPMSwpa_TimerWA_Start(); /* PRQA S 3112 */ /* MD_Rte_3112 */
      RCtApHufTPMSwpa_TimerWA();
      Rte_Runnable_CtApHufTPMSwpa_RCtApHufTPMSwpa_TimerWA_Return(); /* PRQA S 3112 */ /* MD_Rte_3112 */

      (void)Schedule(); /* PRQA S 3417 */ /* MD_Rte_Os */

      /* call runnable */
      Rte_Runnable_CtApHufTPMSwnh_RCtApHufTPMSwnh_TimerWT_Start(); /* PRQA S 3112 */ /* MD_Rte_3112 */
      RCtApHufTPMSwnh_TimerWT();
      Rte_Runnable_CtApHufTPMSwnh_RCtApHufTPMSwnh_TimerWT_Return(); /* PRQA S 3112 */ /* MD_Rte_3112 */

      (void)Schedule(); /* PRQA S 3417 */ /* MD_Rte_Os */
    }

    if ((ev & Rte_Ev_Cyclic_HufTPMS_Task4_0_200ms) != (EventMaskType)0)
    {
      /* call runnable */
      Rte_Runnable_CtApHufTPMSdia_RCtApHufTPMSdia_SgDiagnosis_Start(); /* PRQA S 3112 */ /* MD_Rte_3112 */
      RCtApHufTPMSdia_SgDiagnosis();
      Rte_Runnable_CtApHufTPMSdia_RCtApHufTPMSdia_SgDiagnosis_Return(); /* PRQA S 3112 */ /* MD_Rte_3112 */

      (void)Schedule(); /* PRQA S 3417 */ /* MD_Rte_Os */
    }

    if ((ev & Rte_Ev_Cyclic_HufTPMS_Task4_0_1s) != (EventMaskType)0)
    {
      /* call runnable */
      Rte_Runnable_CtApHufTPMSdia_RCtApHufTPMSdia_StatusInfoWu_Start(); /* PRQA S 3112 */ /* MD_Rte_3112 */
      RCtApHufTPMSdia_StatusInfoWu();
      Rte_Runnable_CtApHufTPMSdia_RCtApHufTPMSdia_StatusInfoWu_Return(); /* PRQA S 3112 */ /* MD_Rte_3112 */

      (void)Schedule(); /* PRQA S 3417 */ /* MD_Rte_Os */
    }

    if ((ev & Rte_Ev_Cyclic_HufTPMS_Task4_0_200ms) != (EventMaskType)0)
    {
      /* call runnable */
      Rte_Runnable_CtApHufTPMSroe_RCtApHufTPMSroe_RoElite_Start(); /* PRQA S 3112 */ /* MD_Rte_3112 */
      RCtApHufTPMSroe_RoElite();
      Rte_Runnable_CtApHufTPMSroe_RCtApHufTPMSroe_RoElite_Return(); /* PRQA S 3112 */ /* MD_Rte_3112 */

      (void)Schedule(); /* PRQA S 3417 */ /* MD_Rte_Os */
    }
  }
} /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

#define RTE_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER /* PRQA S 0828 */ /* MD_MSR_1.1_828 */
# ifdef RTE_MAGIC_NUMBER
#  if RTE_MAGIC_NUMBER != 1513305418
#   error "The magic number of the generated file <C:/_TSS/DAG/MFA2/Target/Appl/GenData/Rte/Rte.c> is different. Please check time and date of the generated RTE files!"
#  endif
# else
#  define RTE_MAGIC_NUMBER 1513305418
# endif  /* RTE_MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */
/* end Fileversion check */

/**********************************************************************************************************************
 MISRA 2004 violations and justifications
 *********************************************************************************************************************/

/* module specific MISRA deviations:
   MD_Rte_0342:  MISRA rule: 19.13
     Reason:     For efficient code the use of macros and the operator '##' is necessary.
     Risk:       The used compiler is not ANSI/ISO C89 compatible. No functional risk.
     Prevention: AUTOSAR is based on ANSI/ISO C89. Compatible compilers are required.

   MD_Rte_0777:  MISRA rule: 5.1
     Reason:     The defined RTE naming convention may result in identifiers with more than 31 characters. The compliance to this rule is under user's control.
                 This is covered in the MISRA C compliance section of the Rte specification.
     Risk:       Ambiguous identifiers can lead to compiler errors / warnings.
     Prevention: Verified during compile time. If the compiler reports an error / warning. The user has to rename the objects to be unique within the significant characters.

   MD_Rte_0779:  MISRA rule: 5.1
     Reason:     The defined RTE naming convention may result in identifiers with more than 31 characters. The compliance to this rule is under user's control.
                 This is covered in the MISRA C compliance section of the Rte specification.
     Risk:       Ambiguous identifiers can lead to compiler errors / warnings.
     Prevention: Verified during compile time. If the compiler reports an error / warning. The user has to rename the objects to be unique within the significant characters.

   MD_Rte_0781:  MISRA rule: 5.6
     Reason:     The name is being used as a structure/union member as well as being a label, tag or ordinary identifier.
                 The compliance to this rule is under user's control.
     Risk:       Ambiguous identifiers can lead to compiler errors / warnings.
     Prevention: Verified during compile time. If the compiler reports an error / warning. The user has to rename the objects leading to the violation.

   MD_Rte_3112:  MISRA rule: 14.2
     Reason:     The structures of macros are specified in the RTE specification [rte_sws_1236].
     Risk:       No functional risk.
     Prevention: Not required.

   MD_Rte_3408:  MISRA rule: 8.8
     Reason:     For the purpose of monitoring during calibration or debugging it is necessary to use non-static declarations.
                 This is covered in the MISRA C compliance section of the Rte specification.
     Risk:       No functional risk.
     Prevention: Not required.

   MD_Rte_3447:  MISRA rule: 8.8
     Reason:     For the purpose of monitoring during calibration or debugging it is necessary to use non-static declarations.
                 This is covered in the MISRA C compliance section of the Rte specification.
     Risk:       No functional risk.
     Prevention: Not required.

   MD_Rte_Os:
     Reason:     This justification is used as summary justification for all deviations caused by the MICROSAR OS
                 which is for testing of the RTE. Those deviations are no issues in the RTE code.
     Risk:       No functional risk.
     Prevention: Not required.

   MD_Rte_Qac:
     Reason:     This justification is used as summary justification for all deviations caused by wrong analysis tool results.
                 The used analysis tool QAC 7.0 sometimes creates wrong messages. Those deviations are no issues in the RTE code.
     Risk:       No functional risk.
     Prevention: Not required.

*/
