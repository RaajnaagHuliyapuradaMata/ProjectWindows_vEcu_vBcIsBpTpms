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
 *          File:  Components/Rte_CtApHufTPMSmgr.h
 *     Workspace:  C:/_TSS/DAG/MFA2/Target/Config/Developer/HufTPMS_G6_F1L.dev
 *   ECU-Project:  TPM
 *  Generated at:  Fri Dec 15 13:11:50 2017
 *
 *     Generator:  MICROSAR RTE Generator Version 2.27.0
 *                 RTE Core Version 1.6.0
 *       License:  License CBD1500122 valid for Huf Electronics Bretten GmbH Package: MSR Daimler SLP10 Micro: R7F7010133AFP Compiler: Green Hills 6.1.4
 *
 *   Description:  Application header file for SW-C
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_CTAPHUFTPMSMGR_H
# define _RTE_CTAPHUFTPMSMGR_H

# ifndef RTE_CORE
#  ifdef RTE_APPLICATION_HEADER_FILE
#   error Multiple application header files included.
#  endif
#  define RTE_APPLICATION_HEADER_FILE
# endif

# ifdef __cplusplus
extern "C"
{
# endif /* __cplusplus */

/* include files */

# include "Rte_Type.h"

# ifndef RTE_CORE

#  define RTE_START_SEC_VAR_NOINIT_UNSPECIFIED
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/************************************************************************/
/* extern declaration of RTE buffers for optimized macro implementation */
/************************************************************************/
extern VAR(DT_ushWAState, RTE_VAR_NOINIT) Rte_CpApHufTPMSwpa_PP_WAState_DE_ushWAState; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern VAR(DT_ushWarnOut, RTE_VAR_NOINIT) Rte_CpApHufTPMSwnh_PP_WarnOut_DE_ushWarnOut; /* PRQA S 0850 */ /* MD_MSR_19.8 */

#  define RTE_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# endif /* !defined(RTE_CORE) */


# ifndef RTE_CORE
/**********************************************************************************************************************
 * Init Values for unqueued S/R communication (primitive types only)
 *********************************************************************************************************************/

#  define Rte_InitValue_PP_WAState_DE_ushWAState (0U)
#  define Rte_InitValue_PP_WarnOut_DE_ushWarnOut (0U)
#  define Rte_InitValue_P_Awake_Diag_Actv_Awake_Diag_Actv (FALSE)
#  define Rte_InitValue_P_Awake_Ignition_On_Awake_Ignition_On (FALSE)
#  define Rte_InitValue_P_Awake_NwSt_Awake_NwSt (FALSE)
#  define Rte_InitValue_P_Awake_Warn_Actv_Awake_Warn_Actv (FALSE)
#  define Rte_InitValue_P_WakeupRsn_TPM_WakeupRsn_TPM (255U)
#  define Rte_InitValue_R_AirPress_Outsd_AirPress_Outsd (255U)
#  define Rte_InitValue_R_AirTemp_Outsd_Disp_AirTemp_Outsd_Disp (255U)
#  define Rte_InitValue_R_Odo_Odo (16777215U)
#  define Rte_InitValue_R_PN14_EOL_Disp_Rq_PN14_EOL_Disp_Rq (0U)
#  define Rte_InitValue_R_RevGr_Engg_RevGr_Engg (3U)
#  define Rte_InitValue_R_TPM_Actv_Rq_V2_TPM_Actv_Rq_V2 (3U)
#  define Rte_InitValue_R_VehSpd_Disp_VehSpd_Disp (4095U)
# endif


# ifndef RTE_CORE
/**********************************************************************************************************************
 * Buffers for inter-runnable variables
 *********************************************************************************************************************/

#  define RTE_START_SEC_VAR_NOINIT_UNSPECIFIED
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

extern VAR(Boolean, RTE_VAR_NOINIT) Rte_Irv_CpApHufTPMSmgr_IRV_TpmActvRq_TpmMsgDispRq; /* PRQA S 0850 */ /* MD_MSR_19.8 */

#  define RTE_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
# endif /* !defined(RTE_CORE) */


# define RTE_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 * API prototypes
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_CtApHufTPMSmgr_PP_RfStructIn_DE_auRfStruct(P2VAR(UInt8, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_CtApHufTPMSmgr_PP_RfStructIn_DE_auRfStruct(P2VAR(DT_auRfStruct, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_CtApHufTPMSmgr_R_AirPress_Outsd_AirPress_Outsd(P2VAR(c08_hPa_0_1980_7k8, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_CtApHufTPMSmgr_R_AirTemp_Outsd_Disp_AirTemp_Outsd_Disp(P2VAR(c08_degC_m40_85_0k5, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_CtApHufTPMSmgr_R_Eng_Rs_EngCtrl_Pr2_Eng_Rs_EngCtrl_Pr2(P2VAR(REC_Eng_Rs_EngCtrl_Pr2_1j00gxu3p5exa8awg915k1zy, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_CtApHufTPMSmgr_R_Ign_Stat_Pr2_Ign_Stat_Pr2(P2VAR(REC_Ign_Stat_Pr2_71njeubj9ico1p8v4pmslfcno, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_CtApHufTPMSmgr_R_Odo_Odo(P2VAR(c24_km_0_999999k9_0k1, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_CtApHufTPMSmgr_R_PN14_EOL_Disp_Rq_PN14_EOL_Disp_Rq(P2VAR(c03_EOL_Disp_Rq, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_CtApHufTPMSmgr_R_RevGr_Engg_RevGr_Engg(P2VAR(c02_Disengg_Engg, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_CtApHufTPMSmgr_R_TPM_Actv_Rq_V2_TPM_Actv_Rq_V2(P2VAR(c02_TPM_Actv_Rq_V2, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_CtApHufTPMSmgr_R_VehSpd_Disp_VehSpd_Disp(P2VAR(c12_km_p_h_0_409k4_0k1, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_CtApHufTPMSmgr_R_WhlPlsCnt_TPM_Pr2_WhlPlsCnt_TPM_Pr2(P2VAR(REC_WhlPlsCnt_TPM_Pr2_5hishd08ma5z1luev78umdwvx, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_CtApHufTPMSmgr_PP_EnvData_DE_tEnvData(P2CONST(DT_tEnvData, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_CtApHufTPMSmgr_PP_RfStructOut_DE_auRfStruct(P2CONST(UInt8, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_CtApHufTPMSmgr_PP_RfStructOut_DE_auRfStruct(P2CONST(DT_auRfStruct, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_CtApHufTPMSmgr_P_Awake_Diag_Actv_Awake_Diag_Actv(DC_BOOL data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_CtApHufTPMSmgr_P_Awake_Ignition_On_Awake_Ignition_On(DC_BOOL data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_CtApHufTPMSmgr_P_Awake_NwSt_Awake_NwSt(DC_BOOL data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_CtApHufTPMSmgr_P_Awake_Warn_Actv_Awake_Warn_Actv(DC_BOOL data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_CtApHufTPMSmgr_P_Meas_TPM_1_Meas_XX(P2CONST(c08_UInt_SNA_na, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_CtApHufTPMSmgr_P_Meas_TPM_1_Meas_XX(P2CONST(ARR_08_UInt_noSNA_8, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_CtApHufTPMSmgr_P_RefPress_RefPress(P2CONST(REC_RefPress, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_CtApHufTPMSmgr_P_TPM_Lmp_On_Rq_Pr2_TPM_Lmp_On_Rq_Pr2(P2CONST(REC_TPM_Lmp_On_Rq_Pr2_cp6wyrd9cg7ec7y2w3khz1gyt, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_CtApHufTPMSmgr_P_TPM_Lmp_On_Rq_old_TPM_Lmp_On_Rq_old(P2CONST(REC_TPM_Lmp_On_Rq_old, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_CtApHufTPMSmgr_P_Tire_Stat_V2_Tire_Stat_V2(P2CONST(REC_Tire_Stat_V2, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_CtApHufTPMSmgr_P_Tire_Temp_V2_Tire_Temp_V2(P2CONST(REC_Tire_Temp_V2, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_DATA) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_CtApHufTPMSmgr_P_WakeupRsn_TPM_WakeupRsn_TPM(c08_WakeupRsn_TPM data); /* PRQA S 0850 */ /* MD_MSR_19.8 */

# define RTE_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# ifndef RTE_CORE

/**********************************************************************************************************************
 * Rte_Read_<p>_<d> (explicit S/R communication with isQueued = false)
 *********************************************************************************************************************/
#  define Rte_Read_PP_RfStructIn_DE_auRfStruct Rte_Read_CtApHufTPMSmgr_PP_RfStructIn_DE_auRfStruct
#  define Rte_Read_PP_WAState_DE_ushWAState Rte_Read_CtApHufTPMSmgr_PP_WAState_DE_ushWAState
#  define Rte_Read_CtApHufTPMSmgr_PP_WAState_DE_ushWAState(data) (*(data) = Rte_CpApHufTPMSwpa_PP_WAState_DE_ushWAState, ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Read_PP_WarnOut_DE_ushWarnOut Rte_Read_CtApHufTPMSmgr_PP_WarnOut_DE_ushWarnOut
#  define Rte_Read_CtApHufTPMSmgr_PP_WarnOut_DE_ushWarnOut(data) (*(data) = Rte_CpApHufTPMSwnh_PP_WarnOut_DE_ushWarnOut, ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Read_R_AirPress_Outsd_AirPress_Outsd Rte_Read_CtApHufTPMSmgr_R_AirPress_Outsd_AirPress_Outsd
#  define Rte_Read_R_AirTemp_Outsd_Disp_AirTemp_Outsd_Disp Rte_Read_CtApHufTPMSmgr_R_AirTemp_Outsd_Disp_AirTemp_Outsd_Disp
#  define Rte_Read_R_Eng_Rs_EngCtrl_Pr2_Eng_Rs_EngCtrl_Pr2 Rte_Read_CtApHufTPMSmgr_R_Eng_Rs_EngCtrl_Pr2_Eng_Rs_EngCtrl_Pr2
#  define Rte_Read_R_Ign_Stat_Pr2_Ign_Stat_Pr2 Rte_Read_CtApHufTPMSmgr_R_Ign_Stat_Pr2_Ign_Stat_Pr2
#  define Rte_Read_R_Odo_Odo Rte_Read_CtApHufTPMSmgr_R_Odo_Odo
#  define Rte_Read_R_PN14_EOL_Disp_Rq_PN14_EOL_Disp_Rq Rte_Read_CtApHufTPMSmgr_R_PN14_EOL_Disp_Rq_PN14_EOL_Disp_Rq
#  define Rte_Read_R_RevGr_Engg_RevGr_Engg Rte_Read_CtApHufTPMSmgr_R_RevGr_Engg_RevGr_Engg
#  define Rte_Read_R_TPM_Actv_Rq_V2_TPM_Actv_Rq_V2 Rte_Read_CtApHufTPMSmgr_R_TPM_Actv_Rq_V2_TPM_Actv_Rq_V2
#  define Rte_Read_R_VehSpd_Disp_VehSpd_Disp Rte_Read_CtApHufTPMSmgr_R_VehSpd_Disp_VehSpd_Disp
#  define Rte_Read_R_WhlPlsCnt_TPM_Pr2_WhlPlsCnt_TPM_Pr2 Rte_Read_CtApHufTPMSmgr_R_WhlPlsCnt_TPM_Pr2_WhlPlsCnt_TPM_Pr2


/**********************************************************************************************************************
 * Rte_Write_<p>_<d> (explicit S/R communication with isQueued = false)
 *********************************************************************************************************************/
#  define Rte_Write_PP_EnvData_DE_tEnvData Rte_Write_CtApHufTPMSmgr_PP_EnvData_DE_tEnvData
#  define Rte_Write_PP_RfStructOut_DE_auRfStruct Rte_Write_CtApHufTPMSmgr_PP_RfStructOut_DE_auRfStruct
#  define Rte_Write_P_Awake_Diag_Actv_Awake_Diag_Actv Rte_Write_CtApHufTPMSmgr_P_Awake_Diag_Actv_Awake_Diag_Actv
#  define Rte_Write_P_Awake_Ignition_On_Awake_Ignition_On Rte_Write_CtApHufTPMSmgr_P_Awake_Ignition_On_Awake_Ignition_On
#  define Rte_Write_P_Awake_NwSt_Awake_NwSt Rte_Write_CtApHufTPMSmgr_P_Awake_NwSt_Awake_NwSt
#  define Rte_Write_P_Awake_Warn_Actv_Awake_Warn_Actv Rte_Write_CtApHufTPMSmgr_P_Awake_Warn_Actv_Awake_Warn_Actv
#  define Rte_Write_P_Meas_TPM_1_Meas_XX Rte_Write_CtApHufTPMSmgr_P_Meas_TPM_1_Meas_XX
#  define Rte_Write_P_RefPress_RefPress Rte_Write_CtApHufTPMSmgr_P_RefPress_RefPress
#  define Rte_Write_P_TPM_Lmp_On_Rq_Pr2_TPM_Lmp_On_Rq_Pr2 Rte_Write_CtApHufTPMSmgr_P_TPM_Lmp_On_Rq_Pr2_TPM_Lmp_On_Rq_Pr2
#  define Rte_Write_P_TPM_Lmp_On_Rq_old_TPM_Lmp_On_Rq_old Rte_Write_CtApHufTPMSmgr_P_TPM_Lmp_On_Rq_old_TPM_Lmp_On_Rq_old
#  define Rte_Write_P_Tire_Stat_V2_Tire_Stat_V2 Rte_Write_CtApHufTPMSmgr_P_Tire_Stat_V2_Tire_Stat_V2
#  define Rte_Write_P_Tire_Temp_V2_Tire_Temp_V2 Rte_Write_CtApHufTPMSmgr_P_Tire_Temp_V2_Tire_Temp_V2
#  define Rte_Write_P_WakeupRsn_TPM_WakeupRsn_TPM Rte_Write_CtApHufTPMSmgr_P_WakeupRsn_TPM_WakeupRsn_TPM


/**********************************************************************************************************************
 * Rte_Call_<p>_<o> (unmapped) for synchronous C/S communication
 *********************************************************************************************************************/
#  define RTE_START_SEC_CTAPHUFTPMSWPA_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_ReceiveData2Alloc_Operation(P2CONST(DT_tData2Alloc, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_DATA) tData2Alloc); /* PRQA S 0850 */ /* MD_MSR_19.8 */
#  define RTE_STOP_SEC_CTAPHUFTPMSWPA_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_PP_Data2Walloc_OP_SendData2Walloc(arg1) (RCtApHufTPMSwpa_ReceiveData2Alloc_Operation(arg1), ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define RTE_START_SEC_CTAPHUFTPMSWNH_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(void, RTE_CTAPHUFTPMSWNH_APPL_CODE) RCtApHufTPMSwnh_ReceiveData2Warn_Operatation(P2CONST(DT_tData2Warn, AUTOMATIC, RTE_CTAPHUFTPMSWNH_APPL_DATA) tData2Warn); /* PRQA S 0850 */ /* MD_MSR_19.8 */
#  define RTE_STOP_SEC_CTAPHUFTPMSWNH_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_PP_Data2Warn_OP_SendTelData2WarnHdlr(arg1) (RCtApHufTPMSwnh_ReceiveData2Warn_Operatation(arg1), ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define RTE_START_SEC_CTAPHUFTPMSWPA_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetRecHistIDs_Operation(P2VAR(UInt8, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ucRecHistID); /* PRQA S 0850 */ /* MD_MSR_19.8 */
#  define RTE_STOP_SEC_CTAPHUFTPMSWPA_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_PP_GetRecHistIDs_OP_GetRecHistIDs(arg1) (RCtApHufTPMSwpa_GetRecHistIDs_Operation(arg1), ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define RTE_START_SEC_CTAPHUFTPMSWPA_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetHistID_Operation(UInt8 ucCol, P2VAR(UInt32, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ulID); /* PRQA S 0850 */ /* MD_MSR_19.8 */
#  define RTE_STOP_SEC_CTAPHUFTPMSWPA_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_PP_GetWANonVolatileData_OP_GetHistID(arg1, arg2) (RCtApHufTPMSwpa_GetHistID_Operation(arg1, arg2), ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define RTE_START_SEC_CTAPHUFTPMSWPA_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetHistWPOfID_Operation(UInt32 ulID, P2VAR(UInt8, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ucZomPos); /* PRQA S 0850 */ /* MD_MSR_19.8 */
#  define RTE_STOP_SEC_CTAPHUFTPMSWPA_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_PP_GetWANonVolatileData_OP_GetHistWPOfID(arg1, arg2) (RCtApHufTPMSwpa_GetHistWPOfID_Operation(arg1, arg2), ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define RTE_START_SEC_CTAPHUFTPMSWPA_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetHistWPOfCol_Operation(UInt8 ucCol, P2VAR(UInt8, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ucWP); /* PRQA S 0850 */ /* MD_MSR_19.8 */
#  define RTE_STOP_SEC_CTAPHUFTPMSWPA_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_PP_GetWANonVolatileData_OP_GetWPOfCol(arg1, arg2) (RCtApHufTPMSwpa_GetHistWPOfCol_Operation(arg1, arg2), ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define RTE_START_SEC_CTAPHUFTPMSWPA_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetWaTOErrorCode_Operation(P2VAR(UInt8, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ucWaToErr, UInt8 ucColOfID); /* PRQA S 0850 */ /* MD_MSR_19.8 */
#  define RTE_STOP_SEC_CTAPHUFTPMSWPA_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_PP_GetWaTOErrorCode_OP_GetWaTOErrorCode(arg1, arg2) (RCtApHufTPMSwpa_GetWaTOErrorCode_Operation(arg1, arg2), ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define RTE_START_SEC_CTAPHUFTPMSWNH_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(void, RTE_CTAPHUFTPMSWNH_APPL_CODE) RCtApHufTPMSwnh_GETaucWheelPosWarn_Operation(UInt8 pos, P2VAR(UInt8, AUTOMATIC, RTE_CTAPHUFTPMSWNH_APPL_VAR) ucWheelPosWarn); /* PRQA S 0850 */ /* MD_MSR_19.8 */
#  define RTE_STOP_SEC_CTAPHUFTPMSWNH_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_PP_GetWarningVectors_OP_GETaucWheelPosWarn(arg1, arg2) (RCtApHufTPMSwnh_GETaucWheelPosWarn_Operation(arg1, arg2), ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define RTE_START_SEC_CTAPHUFTPMSWNH_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(void, RTE_CTAPHUFTPMSWNH_APPL_CODE) RCtApHufTPMSwnh_GETucHiWarnstatus1WN_Operation(P2VAR(UInt16, AUTOMATIC, RTE_CTAPHUFTPMSWNH_APPL_VAR) ushWarnOUtTM); /* PRQA S 0850 */ /* MD_MSR_19.8 */
#  define RTE_STOP_SEC_CTAPHUFTPMSWNH_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_PP_GetWarningVectors_OP_GETushWarnstatus1WN(arg1) (RCtApHufTPMSwnh_GETucHiWarnstatus1WN_Operation(arg1), ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define RTE_START_SEC_CTAPHUFTPMSWPA_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomAbsSumCorrFL_Operation(UInt8 ucIdx, P2VAR(UInt16, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ushAbsSumCorr); /* PRQA S 0850 */ /* MD_MSR_19.8 */
#  define RTE_STOP_SEC_CTAPHUFTPMSWPA_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_PP_GetZomData_OP_GetAbsSumCorrFL(arg1, arg2) (RCtApHufTPMSwpa_GetZomAbsSumCorrFL_Operation(arg1, arg2), ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define RTE_START_SEC_CTAPHUFTPMSWPA_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomAbsSumCorrFR_Operation(UInt8 ucIdx, P2VAR(UInt16, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ushAbsSumCorr); /* PRQA S 0850 */ /* MD_MSR_19.8 */
#  define RTE_STOP_SEC_CTAPHUFTPMSWPA_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_PP_GetZomData_OP_GetAbsSumCorrFR(arg1, arg2) (RCtApHufTPMSwpa_GetZomAbsSumCorrFR_Operation(arg1, arg2), ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define RTE_START_SEC_CTAPHUFTPMSWPA_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomAbsSumCorrRL_Operation(UInt8 ucIdx, P2VAR(UInt16, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ushAbsSumCorr); /* PRQA S 0850 */ /* MD_MSR_19.8 */
#  define RTE_STOP_SEC_CTAPHUFTPMSWPA_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_PP_GetZomData_OP_GetAbsSumCorrRL(arg1, arg2) (RCtApHufTPMSwpa_GetZomAbsSumCorrRL_Operation(arg1, arg2), ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define RTE_START_SEC_CTAPHUFTPMSWPA_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomAbsSumCorrRR_Operation(UInt8 ucIdx, P2VAR(UInt16, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ushAbsSumCorr); /* PRQA S 0850 */ /* MD_MSR_19.8 */
#  define RTE_STOP_SEC_CTAPHUFTPMSWPA_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_PP_GetZomData_OP_GetAbsSumCorrRR(arg1, arg2) (RCtApHufTPMSwpa_GetZomAbsSumCorrRR_Operation(arg1, arg2), ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define RTE_START_SEC_CTAPHUFTPMSWPA_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomAbsCompFL_Operation(UInt8 ucIdx, P2VAR(UInt8, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ucAbsCompStick); /* PRQA S 0850 */ /* MD_MSR_19.8 */
#  define RTE_STOP_SEC_CTAPHUFTPMSWPA_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_PP_GetZomData_OP_GetZomAbsCompFL(arg1, arg2) (RCtApHufTPMSwpa_GetZomAbsCompFL_Operation(arg1, arg2), ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define RTE_START_SEC_CTAPHUFTPMSWPA_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomAbsCompFR_Operation(UInt8 ucIdx, P2VAR(UInt8, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ucAbsCompStick); /* PRQA S 0850 */ /* MD_MSR_19.8 */
#  define RTE_STOP_SEC_CTAPHUFTPMSWPA_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_PP_GetZomData_OP_GetZomAbsCompFR(arg1, arg2) (RCtApHufTPMSwpa_GetZomAbsCompFR_Operation(arg1, arg2), ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define RTE_START_SEC_CTAPHUFTPMSWPA_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomAbsCompRL_Operation(UInt8 ucIdx, P2VAR(UInt8, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ucAbsCompStick); /* PRQA S 0850 */ /* MD_MSR_19.8 */
#  define RTE_STOP_SEC_CTAPHUFTPMSWPA_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_PP_GetZomData_OP_GetZomAbsCompRL(arg1, arg2) (RCtApHufTPMSwpa_GetZomAbsCompRL_Operation(arg1, arg2), ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define RTE_START_SEC_CTAPHUFTPMSWPA_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomAbsCompRR_Operation(UInt8 ucIdx, P2VAR(UInt8, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ucAbsCompStick); /* PRQA S 0850 */ /* MD_MSR_19.8 */
#  define RTE_STOP_SEC_CTAPHUFTPMSWPA_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_PP_GetZomData_OP_GetZomAbsCompRR(arg1, arg2) (RCtApHufTPMSwpa_GetZomAbsCompRR_Operation(arg1, arg2), ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define RTE_START_SEC_CTAPHUFTPMSWPA_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomAbsLinFL_Operation(UInt8 ucIdx, P2VAR(UInt16, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ushAbsLinStick); /* PRQA S 0850 */ /* MD_MSR_19.8 */
#  define RTE_STOP_SEC_CTAPHUFTPMSWPA_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_PP_GetZomData_OP_GetZomAbsLinFL(arg1, arg2) (RCtApHufTPMSwpa_GetZomAbsLinFL_Operation(arg1, arg2), ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define RTE_START_SEC_CTAPHUFTPMSWPA_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomAbsLinFR_Operation(UInt8 ucIdx, P2VAR(UInt16, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ushAbsLinStick); /* PRQA S 0850 */ /* MD_MSR_19.8 */
#  define RTE_STOP_SEC_CTAPHUFTPMSWPA_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_PP_GetZomData_OP_GetZomAbsLinFR(arg1, arg2) (RCtApHufTPMSwpa_GetZomAbsLinFR_Operation(arg1, arg2), ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define RTE_START_SEC_CTAPHUFTPMSWPA_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomAbsLinRL_Operation(UInt8 ucIdx, P2VAR(UInt16, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ushAbsLinStick); /* PRQA S 0850 */ /* MD_MSR_19.8 */
#  define RTE_STOP_SEC_CTAPHUFTPMSWPA_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_PP_GetZomData_OP_GetZomAbsLinRL(arg1, arg2) (RCtApHufTPMSwpa_GetZomAbsLinRL_Operation(arg1, arg2), ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define RTE_START_SEC_CTAPHUFTPMSWPA_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomAbsLinRR_Operation(UInt8 ucIdx, P2VAR(UInt16, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ushAbsLinStick); /* PRQA S 0850 */ /* MD_MSR_19.8 */
#  define RTE_STOP_SEC_CTAPHUFTPMSWPA_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_PP_GetZomData_OP_GetZomAbsLinRR(arg1, arg2) (RCtApHufTPMSwpa_GetZomAbsLinRR_Operation(arg1, arg2), ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define RTE_START_SEC_CTAPHUFTPMSWPA_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomID_Operation(UInt8 ucIdx, P2VAR(UInt32, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ucZomID); /* PRQA S 0850 */ /* MD_MSR_19.8 */
#  define RTE_STOP_SEC_CTAPHUFTPMSWPA_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_PP_GetZomData_OP_GetZomID(arg1, arg2) (RCtApHufTPMSwpa_GetZomID_Operation(arg1, arg2), ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define RTE_START_SEC_CTAPHUFTPMSWPA_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomPosOfID_Operation(UInt32 ulID, P2VAR(UInt8, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ucPos); /* PRQA S 0850 */ /* MD_MSR_19.8 */
#  define RTE_STOP_SEC_CTAPHUFTPMSWPA_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_PP_GetZomData_OP_GetZomPosOfID(arg1, arg2) (RCtApHufTPMSwpa_GetZomPosOfID_Operation(arg1, arg2), ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define RTE_START_SEC_CTAPHUFTPMSWPA_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomStatisticTelCtr_Opetation(UInt8 ucIdx, P2VAR(UInt8, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ucRetVal); /* PRQA S 0850 */ /* MD_MSR_19.8 */
#  define RTE_STOP_SEC_CTAPHUFTPMSWPA_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_PP_GetZomData_OP_GetZomStatisticTelCounter(arg1, arg2) (RCtApHufTPMSwpa_GetZomStatisticTelCtr_Opetation(arg1, arg2), ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define RTE_START_SEC_CTAPHUFTPMSWPA_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomStatus_Operation(UInt8 ucIdx, P2VAR(UInt8, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ucZomStatus); /* PRQA S 0850 */ /* MD_MSR_19.8 */
#  define RTE_STOP_SEC_CTAPHUFTPMSWPA_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_PP_GetZomData_OP_GetZomStatus(arg1, arg2) (RCtApHufTPMSwpa_GetZomStatus_Operation(arg1, arg2), ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define RTE_START_SEC_CTAPHUFTPMSWPA_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomToothTelCtCorrLearnBit_Opetation(UInt8 ucIdx, P2VAR(UInt8, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ucRetVal); /* PRQA S 0850 */ /* MD_MSR_19.8 */
#  define RTE_STOP_SEC_CTAPHUFTPMSWPA_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_PP_GetZomData_OP_GetZomToothTelCtCorrLearnBit(arg1, arg2) (RCtApHufTPMSwpa_GetZomToothTelCtCorrLearnBit_Opetation(arg1, arg2), ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define RTE_START_SEC_CTAPHUFTPMSWPA_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomToothTelCtCorrNoLearnBit_Opetation(UInt8 ucIdx, P2VAR(UInt8, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ucRetVal); /* PRQA S 0850 */ /* MD_MSR_19.8 */
#  define RTE_STOP_SEC_CTAPHUFTPMSWPA_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_PP_GetZomData_OP_GetZomToothTelCtCorrNoLearnBit(arg1, arg2) (RCtApHufTPMSwpa_GetZomToothTelCtCorrNoLearnBit_Opetation(arg1, arg2), ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define RTE_START_SEC_CTAPHUFTPMSWPA_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomToothTelCtNoCorr_Opetation(UInt8 ucIdx, P2VAR(UInt8, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ucRetVal); /* PRQA S 0850 */ /* MD_MSR_19.8 */
#  define RTE_STOP_SEC_CTAPHUFTPMSWPA_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_PP_GetZomData_OP_GetZomToothTelCtrNoCorr(arg1, arg2) (RCtApHufTPMSwpa_GetZomToothTelCtNoCorr_Opetation(arg1, arg2), ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define RTE_START_SEC_CTAPHUFTPMSWPA_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomToothTelCtCorrNoLearnMode_Opetation(UInt8 ucIdx, P2VAR(UInt8, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ucRetVal); /* PRQA S 0850 */ /* MD_MSR_19.8 */
#  define RTE_STOP_SEC_CTAPHUFTPMSWPA_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_PP_GetZomData_OP_GetZomToothTelCtrNoLearnMode(arg1, arg2) (RCtApHufTPMSwpa_GetZomToothTelCtCorrNoLearnMode_Opetation(arg1, arg2), ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define RTE_START_SEC_NVM_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(void, RTE_NVM_APPL_CODE) NvM_GetErrorStatus(NvM_BlockIdType parg0, P2VAR(NvM_RequestResultType, AUTOMATIC, RTE_NVM_APPL_VAR) ErrorStatus); /* PRQA S 0850 */ /* MD_MSR_19.8 */
#  define RTE_STOP_SEC_NVM_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_GetErrorStatus(arg1) (NvM_GetErrorStatus((NvM_BlockIdType)17, arg1), ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define RTE_START_SEC_NVM_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(void, RTE_NVM_APPL_CODE) NvM_SetRamBlockStatus(NvM_BlockIdType parg0, Boolean RamBlockStatus); /* PRQA S 0850 */ /* MD_MSR_19.8 */
#  define RTE_STOP_SEC_NVM_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_SetRamBlockStatus(arg1) (NvM_SetRamBlockStatus((NvM_BlockIdType)17, arg1), ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCodNvMBlock_GetErrorStatus(arg1) (NvM_GetErrorStatus((NvM_BlockIdType)18, arg1), ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCodNvMBlock_SetRamBlockStatus(arg1) (NvM_SetRamBlockStatus((NvM_BlockIdType)18, arg1), ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define RTE_START_SEC_NVM_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_NVM_APPL_CODE) NvM_WriteBlock(NvM_BlockIdType parg0, P2CONST(UInt8, AUTOMATIC, RTE_NVM_APPL_DATA) DstPtr); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, RTE_NVM_APPL_CODE) NvM_WriteBlock(NvM_BlockIdType parg0, P2CONST(NvM_DestPtr, AUTOMATIC, RTE_NVM_APPL_DATA) DstPtr); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
#  define RTE_STOP_SEC_NVM_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCodNvMBlock_WriteBlock(arg1) (NvM_WriteBlock((NvM_BlockIdType)18, arg1)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define RTE_START_SEC_OHDSCANSLAVE_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(Std_ReturnType, RTE_OHDSCANSLAVE_APPL_CODE) OHDSCanSlave_GetOperatingHours(P2VAR(DC_U32, AUTOMATIC, RTE_OHDSCANSLAVE_APPL_VAR) value, P2VAR(DC_U8, AUTOMATIC, RTE_OHDSCANSLAVE_APPL_VAR) valueMsb, P2VAR(DC_U8, AUTOMATIC, RTE_OHDSCANSLAVE_APPL_VAR) status); /* PRQA S 0850 */ /* MD_MSR_19.8 */
#  define RTE_STOP_SEC_OHDSCANSLAVE_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_R_OHDS_GetOperatingHours_GetOperatingHours OHDSCanSlave_GetOperatingHours
#  define RTE_START_SEC_COMM_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(Std_ReturnType, RTE_COMM_APPL_CODE) ComM_GetCurrentComMode(ComM_UserHandleType parg0, P2VAR(ComM_ModeType, AUTOMATIC, RTE_COMM_APPL_VAR) ComMode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
#  define RTE_STOP_SEC_COMM_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_UR_ComMUser_HMI_GetCurrentComMode(arg1) (ComM_GetCurrentComMode((ComM_UserHandleType)0, arg1)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define RTE_START_SEC_COMM_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(Std_ReturnType, RTE_COMM_APPL_CODE) ComM_GetRequestedComMode(ComM_UserHandleType parg0, P2VAR(ComM_ModeType, AUTOMATIC, RTE_COMM_APPL_VAR) ComMode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
#  define RTE_STOP_SEC_COMM_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_UR_ComMUser_HMI_GetRequestedMode(arg1) (ComM_GetRequestedComMode((ComM_UserHandleType)0, arg1)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define RTE_START_SEC_COMM_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(Std_ReturnType, RTE_COMM_APPL_CODE) ComM_RequestComMode(ComM_UserHandleType parg0, ComM_ModeType ComMode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
#  define RTE_STOP_SEC_COMM_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_UR_ComMUser_HMI_RequestComMode(arg1) (ComM_RequestComMode((ComM_UserHandleType)0, arg1)) /* PRQA S 3453 */ /* MD_MSR_19.7 */


/**********************************************************************************************************************
 * Inter-runnable variables
 *********************************************************************************************************************/

/* PRQA S 3453 L1 */ /* MD_MSR_19.7 */
#  define Rte_IrvWrite_RCtApHufTPMSmgr_RdTpmActvRq_IRV_TpmActvRq_TpmMsgDispRq(data) \
  (Rte_Irv_CpApHufTPMSmgr_IRV_TpmActvRq_TpmMsgDispRq = (data))
/* PRQA L:L1 */

/* PRQA S 3453 L1 */ /* MD_MSR_19.7 */
#  define Rte_IrvRead_RCtApHufTPMSmgr_WrTpmMsgDispRq_IRV_TpmActvRq_TpmMsgDispRq() \
  Rte_Irv_CpApHufTPMSmgr_IRV_TpmActvRq_TpmMsgDispRq
/* PRQA L:L1 */

/* PRQA S 3453 L1 */ /* MD_MSR_19.7 */
#  define Rte_IrvWrite_RCtApHufTPMSmgr_WrTpmMsgDispRq_IRV_TpmActvRq_TpmMsgDispRq(data) \
  (Rte_Irv_CpApHufTPMSmgr_IRV_TpmActvRq_TpmMsgDispRq = (data))
/* PRQA L:L1 */


/**********************************************************************************************************************
 * Rte_CData (SW-C local calibration parameters)
 *********************************************************************************************************************/

#  ifndef RTE_MICROSAR_PIM_EXPORT

#   define RTE_START_SEC_CONST_DEFAULT_RTE_CDATA_GROUP_UNSPECIFIED
#   include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

extern CONST(DT_tCalNvMBlock, RTE_CONST_DEFAULT_RTE_CDATA_GROUP) Rte_CtApHufTPMSmgr_Cal_tCalNvMBlock_DefaultValue; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern CONST(DT_tCodNvMBlock, RTE_CONST_DEFAULT_RTE_CDATA_GROUP) Rte_CtApHufTPMSmgr_Cal_tCodNvMBlock_DefaultValue; /* PRQA S 0850 */ /* MD_MSR_19.8 */

#   define RTE_STOP_SEC_CONST_DEFAULT_RTE_CDATA_GROUP_UNSPECIFIED
#   include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  endif

#  define Rte_CData_Cal_tCalNvMBlock_DefaultValue() (&Rte_CtApHufTPMSmgr_Cal_tCalNvMBlock_DefaultValue) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_CData_Cal_tCodNvMBlock_DefaultValue() (&Rte_CtApHufTPMSmgr_Cal_tCodNvMBlock_DefaultValue) /* PRQA S 3453 */ /* MD_MSR_19.7 */

/**********************************************************************************************************************
 * Per-Instance Memory User Types
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Rte_Pim (Per-Instance Memory)
 *********************************************************************************************************************/

#  ifndef RTE_MICROSAR_PIM_EXPORT
#   define RTE_START_SEC_VAR_DEFAULT_RTE_PIM_GROUP_UNSPECIFIED
#   include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

extern VAR(DT_tCalNvMBlock, RTE_VAR_DEFAULT_RTE_PIM_GROUP) Rte_CpApHufTPMSmgr_Pim_tCalNvMBlock; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern VAR(DT_tCodNvMBlock, RTE_VAR_DEFAULT_RTE_PIM_GROUP) Rte_CpApHufTPMSmgr_Pim_tCodNvMBlock; /* PRQA S 0850 */ /* MD_MSR_19.8 */

#   define RTE_STOP_SEC_VAR_DEFAULT_RTE_PIM_GROUP_UNSPECIFIED
#   include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  endif

#  define Rte_Pim_Pim_tCalNvMBlock() \
  (&Rte_CpApHufTPMSmgr_Pim_tCalNvMBlock) /* PRQA S 3453 */ /* MD_MSR_19.7 */

#  define Rte_Pim_Pim_tCodNvMBlock() \
  (&Rte_CpApHufTPMSmgr_Pim_tCodNvMBlock) /* PRQA S 3453 */ /* MD_MSR_19.7 */


# endif /* !defined(RTE_CORE) */


# define RTE_START_SEC_CTAPHUFTPMSMGR_APPL_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 * Runnable entities
 *********************************************************************************************************************/

# ifndef RTE_CORE
#  define RTE_RUNNABLE_RCtApHufTPMSmgr_ControlEcuStandbyTimer RCtApHufTPMSmgr_ControlEcuStandbyTimer
#  define RTE_RUNNABLE_RCtApHufTPMSmgr_GenInternalClock RCtApHufTPMSmgr_GenInternalClock
#  define RTE_RUNNABLE_RCtApHufTPMSmgr_Init RCtApHufTPMSmgr_Init
#  define RTE_RUNNABLE_RCtApHufTPMSmgr_RdDateTm RCtApHufTPMSmgr_RdDateTm
#  define RTE_RUNNABLE_RCtApHufTPMSmgr_RdEngCtrl RCtApHufTPMSmgr_RdEngCtrl
#  define RTE_RUNNABLE_RCtApHufTPMSmgr_RdEnvPressure RCtApHufTPMSmgr_RdEnvPressure
#  define RTE_RUNNABLE_RCtApHufTPMSmgr_RdEnvTemperature RCtApHufTPMSmgr_RdEnvTemperature
#  define RTE_RUNNABLE_RCtApHufTPMSmgr_RdGrBac RCtApHufTPMSmgr_RdGrBac
#  define RTE_RUNNABLE_RCtApHufTPMSmgr_RdIgnStat RCtApHufTPMSmgr_RdIgnStat
#  define RTE_RUNNABLE_RCtApHufTPMSmgr_RdOdo RCtApHufTPMSmgr_RdOdo
#  define RTE_RUNNABLE_RCtApHufTPMSmgr_RdPN14EOLDispRq RCtApHufTPMSmgr_RdPN14EOLDispRq
#  define RTE_RUNNABLE_RCtApHufTPMSmgr_RdSupPN14BatStat RCtApHufTPMSmgr_RdSupPN14BatStat
#  define RTE_RUNNABLE_RCtApHufTPMSmgr_RdTpmActvRq RCtApHufTPMSmgr_RdTpmActvRq
#  define RTE_RUNNABLE_RCtApHufTPMSmgr_RdVehSpeed RCtApHufTPMSmgr_RdVehSpeed
#  define RTE_RUNNABLE_RCtApHufTPMSmgr_RdWhlPlsCnt RCtApHufTPMSmgr_RdWhlPlsCnt
#  define RTE_RUNNABLE_RCtApHufTPMSmgr_ReceiveTelData RCtApHufTPMSmgr_ReceiveTelData
#  define RTE_RUNNABLE_RCtApHufTPMSmgr_ReceiveWAState RCtApHufTPMSmgr_ReceiveWAState
#  define RTE_RUNNABLE_RCtApHufTPMSmgr_ReceiveWarnOut RCtApHufTPMSmgr_ReceiveWarnOut
#  define RTE_RUNNABLE_RCtApHufTPMSmgr_SI_GetInternalClock RCtApHufTPMSmgr_SI_GetInternalClock
#  define RTE_RUNNABLE_RCtApHufTPMSmgr_TimeOutEngCtrl RCtApHufTPMSmgr_TimeOutEngCtrl
#  define RTE_RUNNABLE_RCtApHufTPMSmgr_TimeOutEnvPressure RCtApHufTPMSmgr_TimeOutEnvPressure
#  define RTE_RUNNABLE_RCtApHufTPMSmgr_TimeOutIcBasicInfo RCtApHufTPMSmgr_TimeOutIcBasicInfo
#  define RTE_RUNNABLE_RCtApHufTPMSmgr_TimeOutIcDateTime RCtApHufTPMSmgr_TimeOutIcDateTime
#  define RTE_RUNNABLE_RCtApHufTPMSmgr_TimeOutIcSettings RCtApHufTPMSmgr_TimeOutIcSettings
#  define RTE_RUNNABLE_RCtApHufTPMSmgr_TimeOutIgnStat RCtApHufTPMSmgr_TimeOutIgnStat
#  define RTE_RUNNABLE_RCtApHufTPMSmgr_TimeOutPN14EOLDispRq RCtApHufTPMSmgr_TimeOutPN14EOLDispRq
#  define RTE_RUNNABLE_RCtApHufTPMSmgr_TimeOutSupPN14BatStat RCtApHufTPMSmgr_TimeOutSupPN14BatStat
#  define RTE_RUNNABLE_RCtApHufTPMSmgr_TimeOutWhlPlsCnt RCtApHufTPMSmgr_TimeOutWhlPlsCnt
#  define RTE_RUNNABLE_RCtApHufTPMSmgr_WrBusMsg RCtApHufTPMSmgr_WrBusMsg
#  define RTE_RUNNABLE_RCtApHufTPMSmgr_WrDisplayMsg RCtApHufTPMSmgr_WrDisplayMsg
#  define RTE_RUNNABLE_RCtApHufTPMSmgr_WrTpmMsgDispRq RCtApHufTPMSmgr_WrTpmMsgDispRq
# endif

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_ControlEcuStandbyTimer(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_GenInternalClock(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_Init(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_RdDateTm(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_RdEngCtrl(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_RdEnvPressure(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_RdEnvTemperature(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_RdGrBac(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_RdIgnStat(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_RdOdo(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_RdPN14EOLDispRq(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_RdSupPN14BatStat(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_RdTpmActvRq(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_RdVehSpeed(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_RdWhlPlsCnt(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_ReceiveTelData(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_ReceiveWAState(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_ReceiveWarnOut(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_SI_GetInternalClock(P2VAR(UInt32, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR) ulInternalCLock); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_TimeOutEngCtrl(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_TimeOutEnvPressure(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_TimeOutIcBasicInfo(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_TimeOutIcDateTime(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_TimeOutIcSettings(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_TimeOutIgnStat(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_TimeOutPN14EOLDispRq(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_TimeOutSupPN14BatStat(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_TimeOutWhlPlsCnt(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_WrBusMsg(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_WrDisplayMsg(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_WrTpmMsgDispRq(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */

# define RTE_STOP_SEC_CTAPHUFTPMSMGR_APPL_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# ifndef RTE_CORE
/**********************************************************************************************************************
 * Application errors
 *********************************************************************************************************************/

#  define RTE_E_ComM_UserRequest_E_MODE_LIMITATION (2U)

#  define RTE_E_ComM_UserRequest_E_NOT_OK (1U)

#  define RTE_E_NvMService_AC3_SRBS_Defs_E_NOT_OK (1U)

#  define RTE_E_OHDS_GetOperatingHours_E_NOT_OK (1U)
# endif /* !defined(RTE_CORE) */

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */

/* begin Fileversion check */
# ifndef SKIP_MAGIC_NUMBER /* PRQA S 0828 */ /* MD_MSR_1.1_828 */
#  ifdef RTE_MAGIC_NUMBER
#   if RTE_MAGIC_NUMBER != 1513305418
#    error "The magic number of the generated file <C:/_TSS/DAG/MFA2/Target/Appl/GenData/Rte/Components/Rte_CtApHufTPMSmgr.h> is different. Please check time and date of the generated RTE files!"
#   endif
#  else
#   define RTE_MAGIC_NUMBER 1513305418
#  endif  /* RTE_MAGIC_NUMBER */
# endif  /* SKIP_MAGIC_NUMBER */
/* end Fileversion check */

#endif /* _RTE_CTAPHUFTPMSMGR_H */
