#pragma once

#ifndef RTE_CORE
#ifdef RTE_APPLICATION_HEADER_FILE
#error Multiple application header files included.
#endif
#define RTE_APPLICATION_HEADER_FILE
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#include "Rte_Type.h"

#ifndef RTE_CORE
#define Rte_InitValue_PP_WAState_DE_ushWAState (0U)
#endif

FUNC(Std_ReturnType, RTE_CODE) Rte_Read_CtApHufTPMSwpa_PP_EnvData_DE_tEnvData(P2VAR(DT_tEnvData, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) data);
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_CtApHufTPMSwpa_PP_WAState_DE_ushWAState(DT_ushWAState data);

#ifndef RTE_CORE
#define Rte_Read_PP_EnvData_DE_tEnvData Rte_Read_CtApHufTPMSwpa_PP_EnvData_DE_tEnvData
#define Rte_Write_PP_WAState_DE_ushWAState Rte_Write_CtApHufTPMSwpa_PP_WAState_DE_ushWAState
FUNC(void, RTE_NVM_APPL_CODE) NvM_GetErrorStatus(NvM_BlockIdType parg0, P2VAR(NvM_RequestResultType, AUTOMATIC, RTE_NVM_APPL_VAR) ErrorStatus);

#define Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSwpa_Pim_tWallocNvMBlock_GetErrorStatus(arg1) (NvM_GetErrorStatus((NvM_BlockIdType)15, arg1)/*, ((Std_ReturnType)RTE_E_OK)*/)
FUNC(void, RTE_NVM_APPL_CODE) NvM_SetRamBlockStatus(NvM_BlockIdType parg0, Boolean RamBlockStatus);

#define Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSwpa_Pim_tWallocNvMBlock_SetRamBlockStatus(arg1) (NvM_SetRamBlockStatus((NvM_BlockIdType)15, arg1)/*, ((Std_ReturnType)RTE_E_OK)*/)
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_NVM_APPL_CODE) NvM_WriteBlock(NvM_BlockIdType parg0, P2CONST(UInt8, AUTOMATIC, RTE_NVM_APPL_DATA) DstPtr);
#else
FUNC(Std_ReturnType, RTE_NVM_APPL_CODE) NvM_WriteBlock(NvM_BlockIdType parg0, P2CONST(NvM_DestPtr, AUTOMATIC, RTE_NVM_APPL_DATA) DstPtr);
#endif

#define Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSwpa_Pim_tWallocNvMBlock_WriteBlock(arg1) (NvM_WriteBlock((NvM_BlockIdType)15, arg1))

#ifndef RTE_MICROSAR_PIM_EXPORT
extern CONST(DT_tWallocNvMBlock, RTE_CONST_DEFAULT_RTE_CDATA_GROUP) Rte_CtApHufTPMSwpa_Cal_tWallocNvMBlock_DefaultValue;
extern VAR(DT_tWallocNvMBlock, RTE_VAR_DEFAULT_RTE_PIM_GROUP) Rte_CpApHufTPMSwpa_Pim_tWallocNvMBlock;
#endif

#define Rte_CData_Cal_tWallocNvMBlock_DefaultValue() (&Rte_CtApHufTPMSwpa_Cal_tWallocNvMBlock_DefaultValue)
#define Rte_Pim_Pim_tWallocNvMBlock() (&Rte_CpApHufTPMSwpa_Pim_tWallocNvMBlock)
#endif

#ifndef RTE_CORE
#define RTE_RUNNABLE_RCtApHufTPMSwpa_GetHistID_Operation RCtApHufTPMSwpa_GetHistID_Operation
#define RTE_RUNNABLE_RCtApHufTPMSwpa_GetHistWPOfCol_Operation RCtApHufTPMSwpa_GetHistWPOfCol_Operation
#define RTE_RUNNABLE_RCtApHufTPMSwpa_GetHistWPOfID_Operation RCtApHufTPMSwpa_GetHistWPOfID_Operation
#define RTE_RUNNABLE_RCtApHufTPMSwpa_GetRecHistIDs_Operation RCtApHufTPMSwpa_GetRecHistIDs_Operation
#define RTE_RUNNABLE_RCtApHufTPMSwpa_GetWaTOErrorCode_Operation RCtApHufTPMSwpa_GetWaTOErrorCode_Operation
#define RTE_RUNNABLE_RCtApHufTPMSwpa_GetZomAbsCompFL_Operation RCtApHufTPMSwpa_GetZomAbsCompFL_Operation
#define RTE_RUNNABLE_RCtApHufTPMSwpa_GetZomAbsCompFR_Operation RCtApHufTPMSwpa_GetZomAbsCompFR_Operation
#define RTE_RUNNABLE_RCtApHufTPMSwpa_GetZomAbsCompRL_Operation RCtApHufTPMSwpa_GetZomAbsCompRL_Operation
#define RTE_RUNNABLE_RCtApHufTPMSwpa_GetZomAbsCompRR_Operation RCtApHufTPMSwpa_GetZomAbsCompRR_Operation
#define RTE_RUNNABLE_RCtApHufTPMSwpa_GetZomAbsLinFL_Operation RCtApHufTPMSwpa_GetZomAbsLinFL_Operation
#define RTE_RUNNABLE_RCtApHufTPMSwpa_GetZomAbsLinFR_Operation RCtApHufTPMSwpa_GetZomAbsLinFR_Operation
#define RTE_RUNNABLE_RCtApHufTPMSwpa_GetZomAbsLinRL_Operation RCtApHufTPMSwpa_GetZomAbsLinRL_Operation
#define RTE_RUNNABLE_RCtApHufTPMSwpa_GetZomAbsLinRR_Operation RCtApHufTPMSwpa_GetZomAbsLinRR_Operation
#define RTE_RUNNABLE_RCtApHufTPMSwpa_GetZomAbsSumCorrFL_Operation RCtApHufTPMSwpa_GetZomAbsSumCorrFL_Operation
#define RTE_RUNNABLE_RCtApHufTPMSwpa_GetZomAbsSumCorrFR_Operation RCtApHufTPMSwpa_GetZomAbsSumCorrFR_Operation
#define RTE_RUNNABLE_RCtApHufTPMSwpa_GetZomAbsSumCorrRL_Operation RCtApHufTPMSwpa_GetZomAbsSumCorrRL_Operation
#define RTE_RUNNABLE_RCtApHufTPMSwpa_GetZomAbsSumCorrRR_Operation RCtApHufTPMSwpa_GetZomAbsSumCorrRR_Operation
#define RTE_RUNNABLE_RCtApHufTPMSwpa_GetZomID_Operation RCtApHufTPMSwpa_GetZomID_Operation
#define RTE_RUNNABLE_RCtApHufTPMSwpa_GetZomPosOfID_Operation RCtApHufTPMSwpa_GetZomPosOfID_Operation
#define RTE_RUNNABLE_RCtApHufTPMSwpa_GetZomStatisticTelCtr_Opetation RCtApHufTPMSwpa_GetZomStatisticTelCtr_Opetation
#define RTE_RUNNABLE_RCtApHufTPMSwpa_GetZomStatus_Operation RCtApHufTPMSwpa_GetZomStatus_Operation
#define RTE_RUNNABLE_RCtApHufTPMSwpa_GetZomToothTelCtCorrLearnBit_Opetation RCtApHufTPMSwpa_GetZomToothTelCtCorrLearnBit_Opetation
#define RTE_RUNNABLE_RCtApHufTPMSwpa_GetZomToothTelCtCorrNoLearnBit_Opetation RCtApHufTPMSwpa_GetZomToothTelCtCorrNoLearnBit_Opetation
#define RTE_RUNNABLE_RCtApHufTPMSwpa_GetZomToothTelCtCorrNoLearnMode_Opetation RCtApHufTPMSwpa_GetZomToothTelCtCorrNoLearnMode_Opetation
#define RTE_RUNNABLE_RCtApHufTPMSwpa_GetZomToothTelCtNoCorr_Opetation RCtApHufTPMSwpa_GetZomToothTelCtNoCorr_Opetation
#define RTE_RUNNABLE_RCtApHufTPMSwpa_Init RCtApHufTPMSwpa_Init
#define RTE_RUNNABLE_RCtApHufTPMSwpa_ReceiveData2Alloc_Operation RCtApHufTPMSwpa_ReceiveData2Alloc_Operation
#define RTE_RUNNABLE_RCtApHufTPMSwpa_ReceiveEnvData RCtApHufTPMSwpa_ReceiveEnvData
#define RTE_RUNNABLE_RCtApHufTPMSwpa_TimerWA RCtApHufTPMSwpa_TimerWA
#endif

FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetHistID_Operation(UInt8 ucCol, P2VAR(UInt32, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ulID);
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetHistWPOfCol_Operation(UInt8 ucCol, P2VAR(UInt8, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ucWP);
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetHistWPOfID_Operation(UInt32 ulID, P2VAR(UInt8, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ucZomPos);
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetRecHistIDs_Operation(P2VAR(UInt8, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ucRecHistID);
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetWaTOErrorCode_Operation(P2VAR(UInt8, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ucWaToErr, UInt8 ucColOfID);
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomAbsCompFL_Operation(UInt8 ucIdx, P2VAR(UInt8, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ucAbsCompStick);
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomAbsCompFR_Operation(UInt8 ucIdx, P2VAR(UInt8, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ucAbsCompStick);
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomAbsCompRL_Operation(UInt8 ucIdx, P2VAR(UInt8, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ucAbsCompStick);
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomAbsCompRR_Operation(UInt8 ucIdx, P2VAR(UInt8, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ucAbsCompStick);
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomAbsLinFL_Operation(UInt8 ucIdx, P2VAR(UInt16, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ushAbsLinStick);
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomAbsLinFR_Operation(UInt8 ucIdx, P2VAR(UInt16, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ushAbsLinStick);
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomAbsLinRL_Operation(UInt8 ucIdx, P2VAR(UInt16, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ushAbsLinStick);
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomAbsLinRR_Operation(UInt8 ucIdx, P2VAR(UInt16, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ushAbsLinStick);
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomAbsSumCorrFL_Operation(UInt8 ucIdx, P2VAR(UInt16, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ushAbsSumCorr);
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomAbsSumCorrFR_Operation(UInt8 ucIdx, P2VAR(UInt16, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ushAbsSumCorr);
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomAbsSumCorrRL_Operation(UInt8 ucIdx, P2VAR(UInt16, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ushAbsSumCorr);
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomAbsSumCorrRR_Operation(UInt8 ucIdx, P2VAR(UInt16, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ushAbsSumCorr);
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomID_Operation(UInt8 ucIdx, P2VAR(UInt32, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ucZomID);
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomPosOfID_Operation(UInt32 ulID, P2VAR(UInt8, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ucPos);
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomStatisticTelCtr_Opetation(UInt8 ucIdx, P2VAR(UInt8, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ucRetVal);
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomStatus_Operation(UInt8 ucIdx, P2VAR(UInt8, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ucZomStatus);
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomToothTelCtCorrLearnBit_Opetation(UInt8 ucIdx, P2VAR(UInt8, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ucRetVal);
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomToothTelCtCorrNoLearnBit_Opetation(UInt8 ucIdx, P2VAR(UInt8, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ucRetVal);
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomToothTelCtCorrNoLearnMode_Opetation(UInt8 ucIdx, P2VAR(UInt8, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ucRetVal);
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomToothTelCtNoCorr_Opetation(UInt8 ucIdx, P2VAR(UInt8, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ucRetVal);
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_Init(void);
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_ReceiveData2Alloc_Operation(P2CONST(DT_tData2Alloc, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_DATA) tData2Alloc);
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_ReceiveEnvData(void);
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_TimerWA(void);

#ifndef RTE_CORE
#define RTE_E_NvMService_AC3_SRBS_Defs_E_NOT_OK (1U)
#endif

#ifdef __cplusplus
}
#endif

#ifndef SKIP_MAGIC_NUMBER
#ifdef RTE_MAGIC_NUMBER
#if RTE_MAGIC_NUMBER != 1513305418
#error "The magic number of the generated file <C:/_TSS/DAG/MFA2/Target/Appl/GenData/Rte/Components/Rte_CtApHufTPMSwpa.h> is different. Please check time and date of the generated RTE files!"
#endif
#else
#define RTE_MAGIC_NUMBER 1513305418
#endif
#endif
