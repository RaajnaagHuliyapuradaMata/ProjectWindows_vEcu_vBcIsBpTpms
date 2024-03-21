#pragma once

#define MODE_ok 0U

extern uint8 ucInitUSWalgoNew;
uint8 ucCheckCurrentPminWarn(void);
extern void FillingDetectionMFD(uint8);
extern void FillingDetectionAFDII(void);
extern void FillingDetectionAFDIII(uint8);
extern void DcmFillingDetectionMFD(void);
extern void FD_AbortFillingDetection(uint8);

#ifdef as_16bitP4Average
extern void FD_CalcAverageP4MFD( uint8,uint8,uint8);
#endif

extern uint8 FD_CheckP4AFDstartReason2_3FA( uint8, uint8, sint8, uint8);
extern uint8 FD_CheckP4AFDstartReason2_3RA( uint8, uint8, sint8, uint8);
extern void FD_PlausibilityCheckMFD( sint8);
extern void FD_UnplausibleMFD(void);
extern void FD_Check3RePlausiSetMilage4FinishedMFD(void);
extern void FD_Check3ReAndUpdatePifWarnLampOnOffDefOrInf2Re4FinishedAFD(void);
extern void FD_UpdatePressure4AfdWarnLampON(uint8, sint8 );
extern void FD_UpdatePressure4AfdWarnLampOFF(uint8 , uint8, sint8 );
extern uint8 FD_UpdateComparePressureAfterFBM(void);
extern void FD_UpdateComparePressureAtWarning(uint8);
extern uint8 FD_LoadIdValues4UpdateCompareValue(void);
extern uint8 FD_UpdateIDvalue4MFD(void);
extern uint8 FD_Plausibility_CheckP4DPLR_DPABS(uint8,uint8,uint8,uint8);
extern uint8 FD_CheckCurrentPmin(void);
extern uint8 FD_FlowChartFct1CheckPmin(void);
extern uint8 FD_FlowChartFct1CheckMissingRE(void);
extern uint8 FD_FlowChartFct1(void);
extern uint8 FD_CheckFDpos2ZomPosAfterZOfinish(void);
extern uint8 GetP4NewTempAtCAL(uint8, sint8, sint8);
extern void  PUTucCalNotAckState2Ram(uint8);
extern void ClearCalNotAckState(void);
extern void ClearCalNotAckState4MFD(void);
extern void SetBitCalRequestState2Ram( uint8 );
extern void PUTucCalRequestState2Ram(uint8);
extern uint8 bGETucCalRequestState( uint8 );
extern void ClearBitCalRequestState( uint8  );
extern void ClearCalRequestStateAtMFDfinish( void );
extern void  PUTucIdCalPressure(uint8 , uint8 );
extern uint8 GETucIdCalPressure(uint8);
extern void  PUTscIdCalTemperatur(sint8 , uint8 );
extern sint8 GETscIdCalTemperatur(uint8);
extern void  PUTucPrefFront(uint8);
extern uint8 GETucPrefFront(void);
extern void  PUTucPrefRear(uint8);
extern uint8 GETucPrefRear(void);
extern void  PUTscTref(sint8);
extern sint8 GETscTref(void);
extern void SetBitCalNotAckState2Ram( uint8 );
extern void ClearBitCalNotAckState( uint8 );
extern uint8 GETucCalNotAckStateOfRam(void);
extern uint8 bGETucCalNotAckState( uint8 );
extern void PUTucCalRequestState2Ram( uint8 );
extern uint8 GETucCalRequestStateOfRam(void);
extern void BZ_FZZ_RQ_State4AFD_Finish(void);
extern void PUTucPfillFront(uint8);
extern uint8 GETucPfillFront(void);
extern void PUTucPfillRear(uint8);
extern uint8 GETucPfillRear(void);
extern void PUTscTfill(sint8);
extern sint8 GETscTfill(void);

#ifdef AS_ID_VALUE
extern void PUTucReCntVL4FD(uint8);
extern void INCucReCnt4FD(uint8);
extern uint8 GETucReCntVL4FD(void);
extern uint8 GETucReCnt4FD(uint8);
#endif

extern uint8 GETucPrevPosStatInfoWU(uint8);
extern uint8 FD_CheckHistPos(void);
extern void PUTuiStoragePaverege4CompareValue(uint16, uint8);
extern uint16 GETuiStoragePaverege4CompareValue(uint8);
extern uint8 GETucStoragePaverege4CompareValue(uint8);
extern void FD_HandleReceivedReRadPosVL4AFD(uint8,sint8,uint8,uint8);
extern void FD_HandleReceivedReRadPosVR4AFD(uint8,sint8,uint8,uint8);
extern void FD_HandleReceivedReRadPosHL4AFD(uint8,sint8,uint8,uint8);
extern void FD_HandleReceivedReRadPosHR4AFD(uint8,sint8,uint8,uint8);
extern void PUTucCnt4DP_FILL_DFL(uint8);
extern uint8 GETucCnt4DP_FILL_DFL(void);
extern void PUTucCnt4DP_FILL_IFL(uint8);
extern uint8 GETucCnt4DP_FILL_IFL(void);
extern void ClearBitInNoCheckPmin4StopFD(uint8);

