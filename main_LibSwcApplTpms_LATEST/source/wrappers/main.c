#include "Std_Types.hpp"

boolean bGetBitBetriebszustandBZ  (uint16 ushBitMask) {UNUSED(ushBitMask); return 0;}
boolean bGetBitFahrzeugzustandFZZ (uint16 ushBitMask) {UNUSED(ushBitMask); return 0;}
boolean bGetSensorStateMissing    (uint8  ucColOfID)  {UNUSED(ucColOfID);  return 0;}
uint8   ucGetLastReceivedPress    (uint32 ulTelID)    {UNUSED(ulTelID);    return 0;}
uint8   ucGetLastReceivedTemp     (uint32 ulTelID)    {UNUSED(ulTelID);    return 0;}
uint8   GETucPrefFront            (void)              {return 0;}
uint8   GETucPrefRear             (void)              {return 0;}
uint8   ucGetFailureState         (void)              {return 0;}
boolean bCheckHistIDReception1    (void)              {return 0;}

int main(void){
   return 0;
}

/******************************************************************************/
/* Wrappers for SwcApplTpmsHmiHandler                                         */
/******************************************************************************/
#include "infRteSwcApplTpmsHmiHandler.hpp"

FUNC(Std_ReturnType, DCM_CODE) Dcm_GetSesCtrlType(
   P2VAR(Dcm_SesCtrlType, AUTOMATIC, DCM_APPL_DATA) SessionCtrlType
){
   UNUSED(SessionCtrlType);
   return 0;
}

FUNC(Std_ReturnType, DEM_CODE) Dem_GetIndicatorStatus(
      Dem_IndicatorIdType Dem_IndicatorId
   ,  P2VAR(Dem_IndicatorStatusType, AUTOMATIC, DEM_APPL_DATA) Dem_IndicatorStatus
){
   UNUSED(Dem_IndicatorId);
   UNUSED(Dem_IndicatorStatus);
   return 0;
}

FUNC(Std_ReturnType, ECUM_API_CODE) EcuM_GetState(
   P2VAR(EcuM_StateType, AUTOMATIC, ECUM_APPL_DATA) state
){
   UNUSED(state);
   return 0;
}

FUNC(Nm_ReturnType, NM_CODE) Nm_GetState(
      CONST(NetworkHandleType, AUTOMATIC             ) nmChannelHandle
   ,  CONSTP2VAR(Nm_StateType, AUTOMATIC, NM_APPL_VAR) nmStatePtr
   ,  CONSTP2VAR(Nm_ModeType,  AUTOMATIC, NM_APPL_VAR) nmModePtr
){
   (void)nmChannelHandle;
   UNUSED(*nmStatePtr);
   UNUSED(*nmModePtr);
   return 0;
}

FUNC(void, RTE_CTAPHUFTPMSWNH_APPL_CODE) RCtApHufTPMSwnh_GETucHiWarnstatus1WN_Operation(
   P2VAR(UInt16, AUTOMATIC, RTE_CTAPHUFTPMSWNH_APPL_VAR) ushWarnOUtTM
){
   UNUSED(ushWarnOUtTM);
}

FUNC(void, RTE_CTAPHUFTPMSWNH_APPL_CODE) RCtApHufTPMSwnh_GETaucWheelPosWarn_Operation(
      UInt8 pos
   ,  P2VAR(UInt8, AUTOMATIC, RTE_CTAPHUFTPMSWNH_APPL_VAR) ucWheelPosWarn
){
   UNUSED(pos);
   UNUSED(ucWheelPosWarn);
}

/******************************************************************************/
/* Wrappers for USWarn.c                                                      */
/******************************************************************************/
#include "infRteSwcApplTpmsWarnHandler.hpp"
void   StopFilterSTWT    (void){}
void   StopFilterHDWT    (void){}
uint8  ucStartFilterSTWT (uint16 x                         ){UNUSED(x); return 0;}
uint8  ucStartFilterHDWT (uint16 x                         ){UNUSED(x); return 0;}
void   GetDataEE         (uint8  x,       uint8* y, uint8 z){UNUSED(x); UNUSED(y); UNUSED(z);}
void   PutDataEE         (uint8  x, const uint8* y, uint8 z){UNUSED(x); UNUSED(y); UNUSED(z);}

/******************************************************************************/
/* Wrappers for uswarn_If.c                                                   */
/******************************************************************************/
sint8 GETscTref                    (void){return 0;}

/******************************************************************************/
/* Wrappers for ctrl.c                                                        */
/******************************************************************************/
void   TimerWTinit             (void){}

/******************************************************************************/
/* Wrappers for TSSMsg.c                                                      */
/******************************************************************************/
uint8 ui8HWTimerExpired (void){return 0;}
uint8 ui8SWTimerExpired (void){return 0;}
uint8 ui8KL15OFFnXsec   (void){return 0;}
uint8 ui8NoHoldOff      (void){return 0;}
uint8 ui8CalActive      (void){return 0;}
uint8 ui8MfdCalActive   (void){return 0;}
uint8 ui8KL15OFF        (void){return 0;}

/******************************************************************************/
/* Wrappers for SwcApplTpmsWpa.c                                              */
/******************************************************************************/
typedef uint16       NvM_BlockIdType;
typedef uint8        DT_ucPosOfID;
typedef uint32       DT_ulID;
typedef UInt8        DT_tNvMReservedBytes[20];
typedef UInt8        DT_aucWAParam[2];
typedef DT_ucPosOfID DT_aucWAHistWP[4];
typedef DT_ulID      DT_aulWAHistID[4];
typedef struct{
   DT_aucWAParam        aucWAHistParam;
   DT_aucWAHistWP       aucWAHistWP;
   DT_aucWAHistWP       aucWAHistProvWP;
   DT_aulWAHistID       aulWAHistID;
   UInt8                ucWAHistSensorState;
   DT_tNvMReservedBytes tWallocReserved;
}DT_tWallocNvMBlock;
typedef struct{
   UInt8  ucKlState;
   UInt8  ucTempOut;
   UInt16 ushVehSpeed;
   UInt8  ucPressOut;
   UInt8  ucEngStat;
   UInt8  ucIgnOnStartProc;
}DT_tEnvData;
VAR(DT_tWallocNvMBlock, RTE_VAR_DEFAULT_RTE_PIM_GROUP) Rte_CpApHufTPMSwpa_Pim_tWallocNvMBlock;
void InternTimersInit(void){}
FUNC(void,           NVM_PUBLIC_CODE) NvM_SetRamBlockStatus (NvM_BlockIdType BlockId, boolean BlockChanged)                                      {UNUSED(BlockId); UNUSED(BlockChanged);}
FUNC(void,           NVM_PUBLIC_CODE) NvM_GetErrorStatus    (NvM_BlockIdType BlockId,   P2VAR(uint8, AUTOMATIC, NVM_APPL_DATA) RequestResultPtr) {UNUSED(BlockId); UNUSED(RequestResultPtr);}
FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_WriteBlock        (NvM_BlockIdType BlockId, P2CONST(uint8, AUTOMATIC, NVM_APPL_DATA) NvM_SrcPtr)       {UNUSED(BlockId); UNUSED(NvM_SrcPtr); return E_OK;}
FUNC(Std_ReturnType, RTE_CODE)        Rte_Read_CtApHufTPMSwpa_PP_EnvData_DE_tEnvData(P2VAR(DT_tEnvData, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) data){UNUSED(data); return E_OK;}

/******************************************************************************/
/* Wrappers for FPA.c                                                         */
/******************************************************************************/
#define cSumWE  16
struct ZOMSlot{
   uint32 ulID;
   uint8  ucStatus;
   uint8  ucProbeCt;
   uint8  ucLeftCt;
   uint8  ucRightCt;
   uint8  ucFrameCounter;
   uint8  ucResetABSRefFlag;
   uint8  ucABSRef[4];
   uint16 ushMVdN[4];
   uint16 ushPosCompVal[4];
   uint16 ushMVdN2[4];
   uint16 ushPosCompVal2[4];
   uint8  ucABSComp[4];
   uint8  ucDeltaMin;
   uint16 ushRelCmpVal[4];
   uint8  ucToothTelCtCorrLearnBit;
   uint8  ucToothTelCtCorrNoLearnBit;
   uint8  ucToothTelCtNoCorr;
   uint8  ucToothTelCtNoLearnMode;
   uint16 ushABSRefOffset[4];
   uint16 ucTelCtLearnBit;
   uint16 ushLqi;
   uint8  ucToothTelCt;
   uint16 ushMVdN3[4];
   uint16 ushPosCompVal3[4];
   uint16 ushMVdN4[4];
   uint16 ushPosCompVal4[4];
   uint16 ushRssiSum;
};

/******************************************************************************/
/* Wrappers for WAlloc.c                                                      */
/******************************************************************************/
uint8 bGetABSSignalDTCActive(void){return 0;}

/******************************************************************************/
/* Wrappers for Walloc_IF.c                                                   */
/******************************************************************************/
uint8 GetLinABS (uint16 ushCnt[]){UNUSED(ushCnt); return 0;}
typedef uint16 DT_ushWAState;
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_CtApHufTPMSwpa_PP_WAState_DE_ushWAState(DT_ushWAState data){UNUSED(data); return E_OK;}

/******************************************************************************/
/* Wrappers for SwcApplTpmsManager.c                                          */
/******************************************************************************/
uint8 bCarAbsStickStandstill(void){return 0;}
uint8 bGETucCalRequestState(uint8 ucBitMask){}
uint8 bResetAbsRefPoint(void){}
boolean bSensorDefect(uint32 ui32ID, uint8 ui8TT, uint8 ui8P, uint8 ui8T){}
boolean bStanbyTimerElapsed(void){}
void BuildTelStatistics(uint32 ulTelID, uint8 ucTelP, uint8 ucTelT, uint32 ulTime, boolean bSensorDefect){}
void ClearBitBetriebszustandBZ(uint16 ushBitMask){}
void ClearBitCalRequestState(uint8 ucBitMask){}
void ClearBitFahrzeugzustandFZZ(uint16 ushBitMask){}
void ClearBitInNoCheckPmin4StopFD(uint8 ucBitMask){}
void ClearFzzSignalTimeOutState(uint16 ushBitMask){}
void ClearFzzSignalUnplausibleState(uint16 ushBitMask){}
void ClearTelStatisticsStruct(uint8 ucPosMask){}
FUNC(void, COM_CODE) Com_IpduGroupStart(Com_PduGroupIdType IpduGroupId, boolean Initialize){}
FUNC(void, COM_CODE) Com_IpduGroupStop(Com_PduGroupIdType IpduGroupId){}
FUNC(Std_ReturnType, RTE_COMM_APPL_CODE) ComM_GetCurrentComMode(ComM_UserHandleType parg0, P2VAR(ComM_ModeType, AUTOMATIC, RTE_COMM_APPL_VAR) ComMode){}
FUNC(Std_ReturnType, RTE_COMM_APPL_CODE) ComM_RequestComMode(ComM_UserHandleType parg0, ComM_ModeType ComMode){}
FUNC(Std_ReturnType, ECUM_API_CODE) EcuM_ReleasePOST_RUN (EcuM_UserType User_t){}
void FD_AbortFillingDetection(uint8 ucNotAckState){}
FD_Check3ReAndUpdatePifWarnLampOnOffDefOrInf2Re4FinishedAFD
FD_Check3RePlausiSetMilage4FinishedMFD
FD_FlowChartFct1
FD_FlowChartFct1CheckMissingRE
FD_FlowChartFct1CheckPmin
FD_HandleReceivedReRadPosHL4AFD
FD_HandleReceivedReRadPosHR4AFD
FD_HandleReceivedReRadPosVL4AFD
FD_HandleReceivedReRadPosVR4AFD
FD_LoadIdValues4UpdateCompareValue
FD_UpdateComparePressureAtWarning
FD_UpdateIDvalue4MFD
FillingDetectionAFDII
FillingDetectionAFDIII
FillingDetectionMFD
GetDebugVar2beLogged
GetInternMSTime
GetOpTimeMethodCurrent
GetPalAbsConstantDelay
GetSystemOperatingTime
GETucStoragePaverege4CompareValue
HufE2EWrapperInit
IncrInternMsTimer
InitABS
InitBZ
InitFilterTime
InitTelStatInfo
InitZK
LinABS
PutABS
PUTscIdCalTemperatur
PUTucIdCalPressure
PUTuiStoragePaverege4CompareValue
RCtApHufTPMSwnh_ReceiveData2Warn_Operatation
ResetStanbyTimer
Rte_CpApHufTPMSmgr_Pim_tCalNvMBlock
Rte_CpApHufTPMSmgr_Pim_tCodNvMBlock
Rte_CpApHufTPMSwpa_PP_WAState_DE_ushWAState
Rte_Read_CtApHufTPMSmgr_PP_RfStructIn_DE_auRfStruct
Rte_Read_CtApHufTPMSmgr_R_AirPress_Outsd_AirPress_Outsd
Rte_Read_CtApHufTPMSmgr_R_AirTemp_Outsd_Disp_AirTemp_Outsd_Disp
Rte_Read_CtApHufTPMSmgr_R_Eng_Rs_EngCtrl_Pr2_Eng_Rs_EngCtrl_Pr2
Rte_Read_CtApHufTPMSmgr_R_Ign_Stat_Pr2_Ign_Stat_Pr2
Rte_Read_CtApHufTPMSmgr_R_Odo_Odo
Rte_Read_CtApHufTPMSmgr_R_PN14_EOL_Disp_Rq_PN14_EOL_Disp_Rq
Rte_Read_CtApHufTPMSmgr_R_RevGr_Engg_RevGr_Engg
Rte_Read_CtApHufTPMSmgr_R_TPM_Actv_Rq_V2_TPM_Actv_Rq_V2
Rte_Read_CtApHufTPMSmgr_R_VehSpd_Disp_VehSpd_Disp
Rte_Read_CtApHufTPMSmgr_R_WhlPlsCnt_TPM_Pr2_WhlPlsCnt_TPM_Pr2
Rte_Write_CtApHufTPMSmgr_P_Awake_Diag_Actv_Awake_Diag_Actv
Rte_Write_CtApHufTPMSmgr_P_Awake_Ignition_On_Awake_Ignition_On
Rte_Write_CtApHufTPMSmgr_P_Awake_NwSt_Awake_NwSt
Rte_Write_CtApHufTPMSmgr_P_Awake_Warn_Actv_Awake_Warn_Actv
Rte_Write_CtApHufTPMSmgr_P_Meas_TPM_1_Meas_XX
Rte_Write_CtApHufTPMSmgr_P_RefPress_RefPress
Rte_Write_CtApHufTPMSmgr_P_Tire_Stat_V2_Tire_Stat_V2
Rte_Write_CtApHufTPMSmgr_P_Tire_Temp_V2_Tire_Temp_V2
Rte_Write_CtApHufTPMSmgr_P_TPM_Lmp_On_Rq_old_TPM_Lmp_On_Rq_old
Rte_Write_CtApHufTPMSmgr_P_TPM_Lmp_On_Rq_Pr2_TPM_Lmp_On_Rq_Pr2
Rte_Write_CtApHufTPMSmgr_P_WakeupRsn_TPM_WakeupRsn_TPM
Rte_Write_CtApHufTPMSmgr_PP_EnvData_DE_tEnvData
Rte_Write_CtApHufTPMSmgr_PP_RfStructOut_DE_auRfStruct
SendEnvData2VehStateMgr
SetBitBetriebszustandBZ
SetBitCalNotAckState2Ram
SetBitCalRequestState2Ram
SetBitFahrzeugzustandFZZ
SetBitFillingDetectionStateFD
SetFzzSignalImplauState
SetFzzSignalTimeOutState
SetState2AbortReasonFD
SetState2FillingDetectionStateFD
SkipStanbyTimer
tDebugTelStruct
tdebugTelStructPosFL
tdebugTelStructPosFR
tdebugTelStructPosRL
tdebugTelStructPosRR
TPMS_NVM_ActivateWriteAll
TracePutTelStr2Queue
TracePutTelWallocData2Queue
tracerInit
ucGetAvgCntr4FD
ucGetAvgPress4FD
ucHufE2EWrapperProtectTireState2
ucPassTimeFilter
ucTelStatGetLastRxBlocs
ucTraceGetDataFromQueue
ui8GetComptoirRepare
UpdateFzzCurrentLearnMode
UpdateFzzDTcEnableCond
UpdateParkingTimer
UpdateStanbyTimer
UpdateTelStatInfo
ushGetCurrentECUParkingTime
ZomChangedWuInfoDcm

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/
