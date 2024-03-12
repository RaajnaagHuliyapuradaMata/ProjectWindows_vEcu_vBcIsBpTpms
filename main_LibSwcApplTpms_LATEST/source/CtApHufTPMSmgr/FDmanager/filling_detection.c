#include "filling_detection.h"
#include "Rte_CtApHufTPMSmgr.h"
#include "HMI_handlerX.h"
#include "abs_linX.h"
#include "wallocX.h"
#include "USWarnX.h"
#include "cd_decoder_x.h"
#include "state_fdX.h"
#include "state_bzX.h"
#include "state_zkX.h"
#include "tss_stdX.h"
#include "Trace.h"
#include "internal_clockX.h"
#include "state_fZZX.h"
#include "USWarn_IfX.h"
#include "HMI_handlerX.h"
#include "tel_statisticX.h"
#include "CtCdHufTPMSdia.h"

#define cFD_TIME_OUT  540
#define cFD_MIN_TIME4RESTART_AFD 420
void FillingDetectionMFD(uint8);
void FillingDetectionAFDII(void);
void FillingDetectionAFDIII(uint8);

void FD_AbortFillingDetection(uint8);
#ifdef as_16BitP4Average
void FD_CalcAverageP4MFD( uint8, uint8, uint8);
#endif
uint8 FD_CheckP4AFDstartReason2_3FA( uint8, uint8, sint8, uint8);
uint8 FD_CheckP4AFDstartReason2_3RA( uint8, uint8, sint8, uint8);
 void FD_PlausibilityCheckMFD( sint8);
void FD_UnplausibleMFD(void);
void FD_Check3RePlausiSetMilage4FinishedMFD(void);
void FD_Check3ReAndUpdatePifWarnLampOnOffDefOrInf2Re4FinishedAFD(void);
void FD_UpdatePressure4AfdWarnLampON(uint8, sint8 );
void FD_UpdatePressure4AfdWarnLampOFF(uint8 , uint8, sint8 );
uint8 FD_UpdateComparePressureAfterFBM(void);
void FD_UpdateComparePressureAtWarning(uint8);
uint8 FD_UpdateIDvalue4MFD(void);
uint8 FD_Plausibility_CheckP4DPLR_DPABS(uint8,uint8,uint8,uint8);
void  FD_CheckResetCondition4ImplausiMsg(uint8,uint8,uint8,uint8);
uint8 FD_CheckCurrentPmin(void);
uint8 FD_FlowChartFct1CheckPmin(void);
uint8 FD_FlowChartFct1CheckMissingRE(void);
uint8 FD_FlowChartFct1(void);
uint8 FD_CheckFDpos2ZomPosAfterZOfinish(void);
uint8 FD_CheckHistPos(void);
uint8 GetPabs4NewTempAtCAL(uint8, sint8, sint8);
void FD_AfdStopp4PWP(void);
void PUTuiStoragePaverege4CompareValue(uint16, uint8);
uint16 GETuiStoragePaverege4CompareValue(uint8);
uint8 GETucStoragePaverege4CompareValue(uint8);
void PUTucDpStabiPressure(uint8 x, uint8 i);
uint8 GETucDpStabiPressure( uint8 i);
void PUTucIdCalPressure(uint8 x, uint8 i);
uint8 GETucIdCalPressure( uint8 i);
void PUTscIdCalTemperatur(sint8 x, uint8 i);
sint8 GETscIdCalTemperatur(uint8 i);
void PUTucPfillFront(uint8);
uint8 GETucPfillFront(void);
void PUTucPfillRear(uint8);
uint8 GETucPfillRear(void);
void PUTscTfill(sint8);
sint8 GETscTfill(void);
void PUTucCnt4DP_FILL_DFL(uint8);
void PUTucCnt4DP_FILL_DFL4LTSlogged(void);
uint8 GETucCnt4DP_FILL_DFL(void);
uint8 GETucCnt4DP_FILL_DFL4LTSlogged(void);
uint8 GETucDFL_LTS3(void);
void INCucCnt4DP_FILL_DFL(void);
void PUTucLockByt4DFL_LTS(uint8 x);
void PUTucCnt4DP_FILL_DFLloggedFL(void);
uint8 GETucCnt4DP_FILL_DFLloggedFL(void);
void PUTucCnt4DP_FILL_DFLloggedFR(void);
uint8 GETucCnt4DP_FILL_DFLloggedFR(void);
void PUTucCnt4DP_FILL_DFLloggedRL(void);
uint8 GETucCnt4DP_FILL_DFLloggedRL(void);
void PUTucCnt4DP_FILL_DFLloggedRR(void);
uint8 GETucCnt4DP_FILL_DFLloggedRR(void);
void PUTucCnt4DP_FILL_IFL(uint8);
void PUTucCnt4DP_FILL_IFLloggedFL(void);
uint8 GETucCnt4DP_FILL_IFLloggedFL(void);
void PUTucCnt4DP_FILL_IFLloggedFR(void);
uint8 GETucCnt4DP_FILL_IFLloggedFR(void);
void PUTucCnt4DP_FILL_IFLloggedRL(void);
uint8 GETucCnt4DP_FILL_IFLloggedRL(void);
void PUTucCnt4DP_FILL_IFLloggedRR(void);
uint8 GETucCnt4DP_FILL_IFLloggedRR(void);
uint8 GETucCnt4DP_FILL_IFL(void);
void INCucCnt4DP_FILL_IFL(void);
void InitRePosStorage4FD(void);
void PUTucCalNotAckState2Ram(uint8);
void SetBitCalNotAckState2Ram( uint8 );
void ClearBitCalNotAckState( uint8 );
void ClearCalNotAckState( void );
void ClearCalNotAckState4MFD( void );
uint8 GETucCalNotAckStateOfRam(void);
uint8 bGETucCalNotAckState( uint8 );
void PUTucCalRequestState2Ram(uint8);
void SetBitCalRequestState2Ram( uint8 );
void ClearBitCalRequestState( uint8 );
void ClearCalRequestStateAtMFDfinish( void );
uint8 GETucCalRequestStateOfRam(void);
uint8 bGETucCalRequestState( uint8 );
uint8 GETucPrefFront(void);
uint8 GETucPrefRear(void);
void PUTucPrefFront(uint8);
void PUTucPrefRear(uint8);
sint8 GETscTref(void);
void PUTscTref(sint8);
void BZ_FZZ_RQ_State4AFD_Finish(void);
uint8 ucCheckPminDPautoAFD( uint8 );
uint8 GetP4NewTempAtCAL(uint8, sint8, sint8);
void PUTucNoCheckPmin4StopFD(uint8);
uint8 GETucNoCheckPmin4StopFD(void);
void ClearBitInNoCheckPmin4StopFD(uint8);
void ClearKplNoCheckPmin4StopFD(void);
void PUTucFDcheckP2PosOk(uint8);
uint8 GETucFDcheckP2PosOk(void);
void DECucFDcheckP2PosOk(void);
void ClearFDcheckP2PosOk(void);
void PUTushZomTioFreeze(uint16);
uint16 GETushZomTioFreeze(void);
void FD_HandleReceivedReRadPosVL4AFD(uint8,sint8,uint8,uint8);
void FD_HandleReceivedReRadPosVR4AFD(uint8,sint8,uint8,uint8);
void FD_HandleReceivedReRadPosHL4AFD(uint8,sint8,uint8,uint8);
void FD_HandleReceivedReRadPosHR4AFD(uint8,sint8,uint8,uint8);
uint8 FD_LoadIdValues4MFD(void);
uint8 FD_TimeoutHandle4AFD(void);
uint8 FD_LoadIdValues4UpdateCompareValue(void);

uint8 ucStoreCompValueVL;
uint8 ucStoreCompValueVR;
uint8 ucStoreCompValueHL;
uint8 ucStoreCompValueHR;
uint8 ucIdCalPressure[4];
uint8 ucDpStabiPressure[4];
sint8 scIdCalTemperatur[4];
uint16 uiStoragePaverege4CompareValue[4];
uint8 ucPfillFront;
uint8 ucPfillRear;
sint8 scTfill;
uint8 ucReCntVL4FD;
uint8 ucReCntVR4FD;
uint8 ucReCntHL4FD;
uint8 ucReCntHR4FD;
uint8 ucRePosStorageVL4FD;
uint8 ucRePosStorageVR4FD;
uint8 ucRePosStorageHL4FD;
uint8 ucRePosStorageHR4FD;
uint16 ushZomTioFreez;
uint8 ucCnt4DP_FILL_DFL;
uint8 ucCnt4DP_FILL_IFL;
uint8 ucLockByt4DFL_LTS;
uint8 ucNoCheckPmin4StopFD;
uint8 ucFDcheckP2PosOk;

extern DT_tEnvData tEnvDataToSend;

void FillingDetectionMFD(uint8 ucRestartAnzeige){
  uint8 i;

   if((bGetBitBetriebszustandBZ(cCAL_REQUEST) == FALSE)
   || ((bGetBitBetriebszustandBZ(cCAL_REQUEST) == TRUE) && (bGETucCalRequestState(cCAL_AUTO_ACTIV)))){
         ClearCalNotAckState4MFD();
          ClearAllReCnt4FD();
         ClearFDcheckP2PosOk();

#ifdef AVG_PRESS_ENABLED
         ClearAvgPress4FD();
#endif

        SetBitBetriebszustandBZ(cCAL_REQUEST);
         ClearBitBetriebszustandBZ(cCAL_FINISH | cCAL_MFD_PLAUSI_ERROR | cCAL_AFD_PLAUSI_ERROR);

        ClearBitZustandskennungZK(cZK_ALLE_BITS);

      for(i = 0; i < cAnzRad; i++){
          PUTucIdCalPressure(FALSE,i);
          PUTscIdCalTemperatur(FALSE,i);
        }
          ClearBitCalRequestState(cCAL_MANUAL_FINISH | cCAL_AUTO_ACTIV | cCAL_AUTO_ENABLE2 | cCAL_AUTO_ENABLE3 | cCAL_AUTO_NEW_ID);
         SetBitCalRequestState2Ram(cCAL_MSG2DISP | cCAL_MANUAL_ACTIV);
         ClearBitFahrzeugzustandFZZ(cKFZPARKING_START_AFD);
            ClearKplNoCheckPmin4StopFD();
         PUTucNoCheckPmin4StopFD(ucCheckLOW_PRESS_ReState());

         ClearAbortReasonFD();
         ClearPlausiFailureFD();
         SetState2FillingDetectionStateFD(cMFD_RUNNING);

         if( ucRestartAnzeige == TRUE){
            PUTucTimer4MsgDispRq(5);
         }
         PUTushFDtimeout(cFD_TIME_OUT);
         PUTushSupervisoryTimerFD(cFD_TIME_OUT);
         PUTucFDtimerStop(FALSE);
         PUTucOnceCheckMissingRE4FD(0);
         DelWarnOfId(4);
      }
      else{

         if(GETucTimer4MsgDispRq() == 0){

#ifdef AVG_PRESS_ENABLED
            ClearAvgPress4FD();
#endif
            ClearAllReCnt4FD();
            for(i = 0; i < cAnzRad; i++){
               PUTucIdCalPressure(FALSE,i);
               PUTscIdCalTemperatur(FALSE,i);
            }
            if( ucRestartAnzeige == TRUE){
               PUTucTimer4MsgDispRq(5);
            }
            PUTushFDtimeout(cFD_TIME_OUT);
            PUTushSupervisoryTimerFD(cFD_TIME_OUT);
            PUTucOnceCheckMissingRE4FD(0);
            PUTucFDtimerStop(FALSE);

            ClearAbortReasonFD();
            SetBitCalRequestState2Ram(cCAL_MSG2DISP);
         }
      }
}

void FillingDetectionAFDII(void){
   uint8 ucTmp;

   if(Getui8ColPWPActive() == FALSE){
      if((GETucAutoFillDetectionOnOffOfRam() == TRUE) && (bGETucCalRequestState(cCAL_MANUAL_ACTIV) == FALSE)){
         if(  bGETucCalNotAckState(cCAL_FBM_ACTIV_NAK) == FALSE){

            if( (bGETucCalRequestState(cCAL_AUTO_FIRST) == FALSE) && (((GETulKmStand4AutoCAL() < c_100km) && (GETulKmStand4AutoCAL() > c_0km))
            ||((GETulKmStand4AutoCAL() >= c_100km) && (GETulLastCalMileage() == c_FFFFkm)))){
               if((bGetBitFahrzeugzustandFZZ(cKFZPARKING_START_AFD ) == FALSE) && (bGETucCalRequestState(cCAL_AUTO_ENABLE2) == TRUE)){
                  SetState2FillingDetectionStateFD(cAFD_RUNNING2);
                  ClearAbortReasonFD();
#ifdef AVG_PRESS_ENABLED
                  ClearAvgPress4FD();
#endif

                  if(bGetBitFahrzeugzustandFZZ( cFAHRZEUG_FAEHRT ) == TRUE ){
                      PUTucCalRequestState2Ram(FALSE);
                     SetBitFahrzeugzustandFZZ(cKFZPARKING_START_AFD );
                     SetBitCalRequestState2Ram(cCAL_AUTO_ACTIV | cCAL_AUTO_ENABLE2);
                      InitRePosStorage4FD();

                     ClearBitCalRequestState(cCAL_MANUAL_FINISH);
                     PUTucOnceCheckMissingRE4FD(0);
                     ClearCalNotAckState();
                     ClearAllReCnt4FD();
                     ClearFDcheckP2PosOk();

                     ClearBitBetriebszustandBZ(cCAL_FINISH);
                     SetBitBetriebszustandBZ(cCAL_REQUEST);
                     for(ucTmp = 0; ucTmp < cAnzRad; ucTmp++){
                        PUTucIdCalPressure(FALSE,ucTmp);
                        PUTscIdCalTemperatur(FALSE,ucTmp);
                     }
                     PUTushFDtimeout(cFD_TIME_OUT);
                     PUTushSupervisoryTimerFD(cFD_TIME_OUT);
                     PUTucFDtimerStop(FALSE);

                  }
               }
            }
            else{

               if(ushGetCurrentECUParkingTime() >= cT_STANBY ){
                  if((bGetBitFahrzeugzustandFZZ(cKFZPARKING_START_AFD ) == FALSE) && (bGetBitFahrzeugzustandFZZ( cKL_15_EIN ) == TRUE)){
                     SetState2FillingDetectionStateFD(cAFD_RUNNING2);
                     if(bGETucCalRequestState(cCAL_AUTO_NEW_ID) == FALSE){

                        SetBitCalRequestState2Ram(cCAL_AUTO_ENABLE2);
                     }

                     ClearAbortReasonFD();
#ifdef AVG_PRESS_ENABLED
                     ClearAvgPress4FD();
#endif
                     SetBitFahrzeugzustandFZZ(cKFZPARKING_START_AFD );
                     ClearBitCalRequestState(cCAL_MANUAL_FINISH |cCAL_AUTO_NEW_ID | cCAL_AUTO_ENABLE3);
                     SetBitCalRequestState2Ram(cCAL_AUTO_ACTIV);

                     InitRePosStorage4FD();
                     PUTucOnceCheckMissingRE4FD(0);
                      PUTucNoCheckPmin4StopFD(ucCheckLOW_PRESS_ReState());
                     ClearCalNotAckState();
                     ClearAllReCnt4FD();
                     ClearFDcheckP2PosOk();

                     ClearBitBetriebszustandBZ(cCAL_FINISH);

                     SetBitBetriebszustandBZ(cCAL_REQUEST);

                     for(ucTmp = 0; ucTmp < cAnzRad; ucTmp++){
                        PUTucIdCalPressure(FALSE,ucTmp);
                        PUTscIdCalTemperatur(FALSE,ucTmp);
                     }

                     PUTushFDtimeout(cFD_TIME_OUT);
                     PUTushSupervisoryTimerFD(cFD_TIME_OUT);

                     PUTucFDtimerStop(FALSE);
                     PUTushZomTioFreeze(0);
                  }
               }
               else{
                  if(((bGetBitBetriebszustandBZ(cZO_FINISH) == TRUE ) || (bGetBitBetriebszustandBZ(cZO_TIMEOUT) == TRUE)) && (GETucFDcheckP2PosOk() >= 1)){

                        if(GETucFDcheckP2PosOk() == 1){

                           if(FD_CheckFDpos2ZomPosAfterZOfinish() != FALSE){
                               PUTucFDcheckP2PosOk(0x0F);

                           }
                           else
                           {
                              ClearFDcheckP2PosOk();
                           }
                        }
                        else
                        {
                           if(GETucFDcheckP2PosOk() == 0x0E){
                              ReplayLastREvalue2Walgo();
                              ReStart4SetValue2ActivationMemAFD();
                              ClearFDcheckP2PosOk();
                           }
                           else
                           {
                              DECucFDcheckP2PosOk();
                           }
                        }
                  }
               }
            }
         }
         else{
            ClearBitCalNotAckState(cCAL_FBM_ACTIV_NAK);
            FD_UpdateComparePressureAfterFBM();
         }
      }
      else{

         if((GETushFDtimeout()  == 0 ) && (bGetBitBetriebszustandBZ(cCAL_REQUEST) == TRUE) && (bGETucCalRequestState(cCAL_AUTO_ENABLE2) == TRUE) ){
            FillingDetectionMFD(FALSE);
         }
      }
   }
   else{
      FD_AfdStopp4PWP();
   }
}

void FillingDetectionAFDIII(uint8 ucFastDeflation){
   uint8 ucTmp;

   if(Getui8ColPWPActive() == FALSE){
      if(  bGETucCalNotAckState(cCAL_FBM_ACTIV_NAK) == FALSE){

         if(ucFastDeflation == ucDpTxTriggerc){
            if((GETucAutoFillDetectionOnOffOfRam() == TRUE) && (bGetBitFahrzeugzustandFZZ( cFAHRZEUG_FAEHRT ) == FALSE)){
               if((bGETucCalRequestState(cCAL_MANUAL_ACTIV) == FALSE) && (bGETucCalRequestState(cCAL_AUTO_ENABLE3) == FALSE)){

                  SetState2FillingDetectionStateFD(cAFD_RUNNING3);
                  ClearAbortReasonFD();
#ifdef AVG_PRESS_ENABLED
                  ClearAvgPress4FD();
#endif

                  PUTucOnceCheckMissingRE4FD(0);
                  SetBitCalRequestState2Ram(cCAL_AUTO_ENABLE3 | cCAL_AUTO_ACTIV);
                  ClearBitCalRequestState(cCAL_MANUAL_FINISH | cCAL_AUTO_ENABLE2);
                   ClearCalNotAckState();
                  ClearAllReCnt4FD();
                  ClearFDcheckP2PosOk();

                  ClearBitBetriebszustandBZ(cCAL_FINISH);

                  SetBitBetriebszustandBZ(cCAL_REQUEST);

                  PUTucCnt4DP_FILL_DFL(0);
                  PUTucCnt4DP_FILL_IFL(0);
                  PUTucLockByt4DFL_LTS(0);
                  for(ucTmp = 0; ucTmp < cAnzRad; ucTmp++){
                     PUTucIdCalPressure(FALSE,ucTmp);
                     PUTscIdCalTemperatur(FALSE,ucTmp);
                  }
                  PUTushFDtimeout(cFD_TIME_OUT);
                  PUTushSupervisoryTimerFD(cFD_TIME_OUT);
                  PUTucFDtimerStop(FALSE);
               }
               else{
                  if(GetOneReCnt4FD() == TRUE){

#ifdef AVG_PRESS_ENABLED
                     ClearAvgPress4FD();
#endif
                     ClearAllReCnt4FD();
                     PUTucCnt4DP_FILL_DFL(0);
                     PUTucCnt4DP_FILL_IFL(0);
                     PUTucLockByt4DFL_LTS(0);
                     for(ucTmp = 0; ucTmp < cAnzRad; ucTmp++){
                        PUTucIdCalPressure(FALSE,ucTmp);
                        PUTscIdCalTemperatur(FALSE,ucTmp);
                     }
                     PUTushFDtimeout(cFD_TIME_OUT);
                     PUTushSupervisoryTimerFD(cFD_TIME_OUT);
                     PUTucFDtimerStop(FALSE);
                  }
               }
            }
         }
         else{

            if((bGETucCalRequestState(cCAL_AUTO_ACTIV) == TRUE) && (bGETucCalRequestState(cCAL_AUTO_ENABLE2) == FALSE)){
               if((bGetBitFahrzeugzustandFZZ( cKFZFAEHRT_20KMH ) == TRUE ) && (bGETucCalRequestState(cCAL_AUTO_ENABLE3) == FALSE)){
                  SetBitCalRequestState2Ram(cCAL_AUTO_ENABLE3);
               }
            }
         }

      }
      else{
         ClearBitCalNotAckState(cCAL_FBM_ACTIV_NAK);
         FD_UpdateComparePressureAfterFBM();
      }

   }
   else{
      FD_AfdStopp4PWP();
   }
}

void FD_HandleReceivedReRadPosVL4AFD(uint8 ucP,sint8 scT,uint8 ucColOfID, uint8 ucLTSmode){

uint8 ucTmpPiso4Cal;

#ifdef as_16BitP4Average
   if(bGetBitFahrzeugzustandFZZ( cKFZFAEHRT_20KMH ) == TRUE ){
      INCucRErecCounter4FDVL();
   }
#endif
    if(FD_CheckP4AFDstartReason2_3FA(ucP,GETucRErecCounter4FDVL(),scT,ucColOfID) == FALSE){
      PUTushFDtimeout(0);
      PUTucFDtimerStop(TRUE);
   }
   else{
       if(GETucRErecCounter4FDVL() >= 3){
         ucRePosStorageVL4FD=ucColOfID;
         ucTmpPiso4Cal= GetP4NewTempAtCAL(((uint8) GETuiStoragePaverege4CompareValue(ucColOfID)),GETscIdCalTemperatur(ucColOfID), GETscTref());
         if(ucTmpPiso4Cal >  GETucPosComparePressure(cRadPosVL)){
            if((ucTmpPiso4Cal - GETucPosComparePressure(cRadPosVL)) >= cDP_FILL){

               if(GETucCnt4DP_FILL_IFLloggedFL() == FALSE){
                  INCucCnt4DP_FILL_IFL();
                  PUTucCnt4DP_FILL_IFLloggedFL();
               }
             }
         }
         else{
            if((GETucPosComparePressure(cRadPosVL) - ucTmpPiso4Cal) >= cDP_FILL){
               if((ucLTSmode == cLTS30Days) && (GETucCnt4DP_FILL_DFL4LTSlogged() == FALSE)){
                  PUTucCnt4DP_FILL_DFL4LTSlogged();
               }

               if(GETucCnt4DP_FILL_DFLloggedFL() == FALSE){
                  INCucCnt4DP_FILL_DFL();
                  PUTucCnt4DP_FILL_DFLloggedFL();
               }
            }
         }
      }
   }
}

void FD_HandleReceivedReRadPosVR4AFD(uint8 ucP,sint8 scT,uint8 ucColOfID, uint8 ucLTSmode){

uint8 ucTmpPiso4Cal;

#ifdef as_16BitP4Average
   if(bGetBitFahrzeugzustandFZZ( cKFZFAEHRT_20KMH ) == TRUE ){
      INCucRErecCounter4FDVR();
   }
#endif
    if(FD_CheckP4AFDstartReason2_3FA(ucP,GETucRErecCounter4FDVR(),scT,ucColOfID) == FALSE){
      PUTushFDtimeout(0);
      PUTucFDtimerStop(TRUE);
   }
   else{
       if(GETucRErecCounter4FDVR() >= 3){
         ucRePosStorageVR4FD=ucColOfID;
         ucTmpPiso4Cal= GetP4NewTempAtCAL(((uint8) GETuiStoragePaverege4CompareValue(ucColOfID)),GETscIdCalTemperatur(ucColOfID), GETscTref());
         if(ucTmpPiso4Cal >  GETucPosComparePressure(cRadPosVR)){
            if((ucTmpPiso4Cal - GETucPosComparePressure(cRadPosVR)) >= cDP_FILL){
               if(GETucCnt4DP_FILL_IFLloggedFR() == FALSE){
                  INCucCnt4DP_FILL_IFL();
                  PUTucCnt4DP_FILL_IFLloggedFR();
               }
             }
         }
         else{
            if((GETucPosComparePressure(cRadPosVR) - ucTmpPiso4Cal) >= cDP_FILL){
               if((ucLTSmode == cLTS30Days) && (GETucCnt4DP_FILL_DFL4LTSlogged() == FALSE)){
                  PUTucCnt4DP_FILL_DFL4LTSlogged();
               }
               if(GETucCnt4DP_FILL_DFLloggedFR() == FALSE){
                  INCucCnt4DP_FILL_DFL();
                  PUTucCnt4DP_FILL_DFLloggedFR();
               }
            }
         }
      }
   }
}

void FD_HandleReceivedReRadPosHL4AFD(uint8 ucP,sint8 scT,uint8 ucColOfID, uint8 ucLTSmode){

uint8 ucTmpPiso4Cal;

#ifdef as_16BitP4Average
   if(bGetBitFahrzeugzustandFZZ( cKFZFAEHRT_20KMH ) == TRUE ){
      INCucRErecCounter4FDHL();
   }
#endif
   if(FD_CheckP4AFDstartReason2_3RA(ucP,GETucRErecCounter4FDHL(),scT,ucColOfID) == FALSE){
      PUTushFDtimeout(0);
      PUTucFDtimerStop(TRUE);
   }
   else{
       if(GETucRErecCounter4FDHL() >= 3){
         ucRePosStorageHL4FD=ucColOfID;
         ucTmpPiso4Cal= GetP4NewTempAtCAL(((uint8) GETuiStoragePaverege4CompareValue(ucColOfID)),GETscIdCalTemperatur(ucColOfID), GETscTref());
         if(ucTmpPiso4Cal >  GETucPosComparePressure(cRadPosHL)){
            if((ucTmpPiso4Cal - GETucPosComparePressure(cRadPosHL)) >= cDP_FILL){
               if(GETucCnt4DP_FILL_IFLloggedRL() == FALSE){
                  INCucCnt4DP_FILL_IFL();
                  PUTucCnt4DP_FILL_IFLloggedRL();
               }
             }
         }
         else{
            if((GETucPosComparePressure(cRadPosHL) - ucTmpPiso4Cal) >= cDP_FILL){
               if((ucLTSmode == cLTS30Days) && (GETucCnt4DP_FILL_DFL4LTSlogged() == FALSE)){
                  PUTucCnt4DP_FILL_DFL4LTSlogged();
               }
               if(GETucCnt4DP_FILL_DFLloggedRL() == FALSE){
                  INCucCnt4DP_FILL_DFL();
                  PUTucCnt4DP_FILL_DFLloggedRL();
               }
            }
         }
      }
   }
}

void FD_HandleReceivedReRadPosHR4AFD(uint8 ucP,sint8 scT,uint8 ucColOfID, uint8 ucLTSmode){

uint8 ucTmpPiso4Cal;

#ifdef as_16BitP4Average
   if(bGetBitFahrzeugzustandFZZ( cKFZFAEHRT_20KMH ) == TRUE ){
      INCucRErecCounter4FDHR();
   }
#endif
   if(FD_CheckP4AFDstartReason2_3RA(ucP,GETucRErecCounter4FDHR(),scT,ucColOfID) == FALSE){
      PUTushFDtimeout(0);
      PUTucFDtimerStop(TRUE);
   }
   else{
       if(GETucRErecCounter4FDHR() >= 3){
         ucRePosStorageHR4FD=ucColOfID;
         ucTmpPiso4Cal= GetP4NewTempAtCAL(((uint8) GETuiStoragePaverege4CompareValue(ucColOfID)),GETscIdCalTemperatur(ucColOfID), GETscTref());
         if(ucTmpPiso4Cal >  GETucPosComparePressure(cRadPosHR)){
            if((ucTmpPiso4Cal - GETucPosComparePressure(cRadPosHR)) >= cDP_FILL){
               if(GETucCnt4DP_FILL_IFLloggedRR() == FALSE){
                  INCucCnt4DP_FILL_IFL();
                  PUTucCnt4DP_FILL_IFLloggedRR();
               }
             }
         }
         else{
            if((GETucPosComparePressure(cRadPosHR) - ucTmpPiso4Cal) >= cDP_FILL){
               if((ucLTSmode == cLTS30Days) && (GETucCnt4DP_FILL_DFL4LTSlogged() == FALSE)){
                  PUTucCnt4DP_FILL_DFL4LTSlogged();
               }
               if(GETucCnt4DP_FILL_DFLloggedRR() == FALSE){
                  INCucCnt4DP_FILL_DFL();
                  PUTucCnt4DP_FILL_DFLloggedRR();
               }
            }
         }
      }
   }
}

void FD_AbortFillingDetection(uint8 ucNotAckState){

   if((bGetBitBetriebszustandBZ(cCAL_FINISH) != TRUE)){

      SetBitBetriebszustandBZ(cCAL_FINISH);
      ClearBitBetriebszustandBZ(cCAL_REQUEST);

        if(ucNotAckState == cCAL_P_MIN_TIRE_NAK){
         SetState2AbortReasonFD(cFD_P_MIN_TIRE);
         ClearKplNoCheckPmin4StopFD();
         SetState2FillingDetectionStateFD(cFILLING_DETECT_ABORTED);
         SetBitCalNotAckState2Ram(cCAL_P_MIN_TIRE_NAK);
      }
      else{
         if(ucNotAckState != cCAL_AUTO_NEW_ID){
            ClearBitCalRequestState(cCAL_AUTO_NEW_ID);
         }
      }
   }

   if(ucNotAckState == cCAL_RE_MISSING_NAK){
      SetState2AbortReasonFD(cFD_MISSING_SENSOR);
      SetState2FillingDetectionStateFD(cFILLING_DETECT_ABORTED);
   }

   if((ucNotAckState == cCAL_ABORT_REASON_2_3) && (Get_FD_ABORT_REASON() == FALSE)){

      if((FD_TimeoutHandle4AFD() == TRUE) && (bGETucCalRequestState(cCAL_AUTO_ACTIV))){
         FD_Check3ReAndUpdatePifWarnLampOnOffDefOrInf2Re4FinishedAFD();
      }
      else{

         SetState2AbortReasonFD(cFD_TIMEOUT);
         SetState2FillingDetectionStateFD(cFILLING_DETECT_ABORTED);
      }

   }

   if(bGETucCalRequestState(cCAL_MANUAL_ACTIV)){

      ClearBitCalRequestState(cCAL_MANUAL_ACTIV);
      SetBitCalRequestState2Ram(cCAL_MANUAL_FINISH);
   }

   if(bGETucCalRequestState(cCAL_AUTO_ACTIV)){
      ClearBitCalRequestState(cCAL_AUTO_ENABLE3 | cCAL_AUTO_ENABLE2 | cCAL_AUTO_ACTIV);
    }

}

#ifdef as_16bitP4Average

void FD_CalcAverageP4MFD(uint8 ucREcnt4FD,uint8 ucLastReceivedP, uint8 ucColOfID){
   uint16 uiPaverage;
   uint16 uiPaverege4CompareValue;

   if(ucREcnt4FD != 0){
      if(ucREcnt4FD == 1){

         uiPaverage=(uint16)(ucLastReceivedP);
         uiPaverege4CompareValue=(uint16)(ucLastReceivedP);

         PUTucIdCalPressure(uiPaverage,ucColOfID);
         PUTuiStoragePaverege4CompareValue(uiPaverege4CompareValue,ucColOfID);
      }
      else{
         if(ucREcnt4FD < 250){
            uiPaverage=(uint16)(GETucIdCalPressure(ucColOfID) * (ucREcnt4FD-1));
            uiPaverege4CompareValue=(GETuiStoragePaverege4CompareValue(ucColOfID) * (ucREcnt4FD-1));

            uiPaverage=(uint16)(ucLastReceivedP + uiPaverage );
            uiPaverege4CompareValue=((uint16)(ucLastReceivedP) + uiPaverege4CompareValue );

            PUTucIdCalPressure((uiPaverage/ucREcnt4FD),ucColOfID);
            PUTuiStoragePaverege4CompareValue((uiPaverege4CompareValue/ucREcnt4FD),ucColOfID);
         }
      }
   }
}

#endif

uint8 FD_CheckP4AFDstartReason2_3FA( uint8 ucCurrentPressure,uint8 ucREcnt4FD, sint8 scCurrentTireTemp, uint8 ucColOfID){
   uint8 ucRtn=TRUE;
#ifdef as_16BitP4Average
   uint16 uiPaverage;
   uint16 uiPaverege4CompareValue;
#endif

   if(( ucCurrentPressure < GETucMinWarnThresholdOfRam())
   || (scCurrentTireTemp > GETscOutdoorTemperatureFZZ() + 30)
   || (ucCurrentPressure < (GETucPcalMinVaRelativCodOfRam() - cDP_AUTO))){
         if(GETucCalNotAckStateOfRam() == cCAL_VALID){

         if(ucCurrentPressure < GETucMinWarnThresholdOfRam()){
            SetBitCalNotAckState2Ram(cCAL_P_MIN_TIRE_NAK);
            SetState2AbortReasonFD(cFD_P_MIN_TIRE);

         }
         else{
            if( ucCurrentPressure < (GETucPcalMinVaRelativCodOfRam() - cDP_AUTO)){

               SetState2AbortReasonFD(cFD_DP_AUTO);
            }
            else{
               if(scCurrentTireTemp > (GETscOutdoorTemperatureFZZ() + 30)){
                  SetBitCalNotAckState2Ram(cCAL_RE30K2AMBIENT);
                  SetState2AbortReasonFD(cFD_TIRE2HOT);
               }
            }
         }
         ucRtn=FALSE;
         SetState2FillingDetectionStateFD(cFILLING_DETECT_ABORTED);
         ClearPlausiFailureFD();
      }
   }
    else{
      if(ucREcnt4FD == 1){

         PUTucDpStabiPressure(ucCurrentPressure,ucColOfID);
#ifdef as_16BitP4Average
         PUTucIdCalPressure(ucCurrentPressure,ucColOfID);
         PUTuiStoragePaverege4CompareValue(ucCurrentPressure,ucColOfID);
         PUTscIdCalTemperatur(scCurrentTireTemp,ucColOfID);
#endif
      }
      else{
         if(ucREcnt4FD != 0){

            if(ucREcnt4FD == 0xFF){
               if(ucCurrentPressure < (GETucDpStabiPressure(ucColOfID) - cDP_STABI)){
                  SetBitCalNotAckState2Ram(cCAL_DP_STABI_NAK );
                  SetState2AbortReasonFD(cFD_DP_STABI);
                  SetState2FillingDetectionStateFD(cFILLING_DETECT_ABORTED);
                  ClearPlausiFailureFD();
                  ucRtn=FALSE;
               }
            }
            else{
#ifdef as_16BitP4Average
               uiPaverage=(uint16)(GETucIdCalPressure(ucColOfID) * (ucREcnt4FD-1));
               uiPaverege4CompareValue=(GETuiStoragePaverege4CompareValue(ucColOfID) * (ucREcnt4FD-1));

               uiPaverage=(uint16)(ucCurrentPressure + uiPaverage );
               uiPaverege4CompareValue=((uint16)(ucCurrentPressure) + uiPaverege4CompareValue );

               PUTucIdCalPressure((uiPaverage/ucREcnt4FD),ucColOfID);
               PUTuiStoragePaverege4CompareValue((uiPaverege4CompareValue/ucREcnt4FD),ucColOfID);
#endif

               if(ucCurrentPressure < (GETucDpStabiPressure(ucColOfID) - cDP_STABI)){
                  SetBitCalNotAckState2Ram(cCAL_DP_STABI_NAK );
                  SetState2AbortReasonFD(cFD_DP_STABI);
                  SetState2FillingDetectionStateFD(cFILLING_DETECT_ABORTED);
                  ClearPlausiFailureFD();
                  ucRtn=FALSE;
               }
            }
         }
      }
   }
   return ucRtn;
}

uint8 FD_CheckP4AFDstartReason2_3RA( uint8 ucCurrentPressure,uint8 ucREcnt4FD, sint8 scCurrentTireTemp, uint8 ucColOfID){
   uint8 ucRtn=TRUE;
#ifdef as_16BitP4Average
   uint16 uiPaverage;
   uint16 uiPaverege4CompareValue;
#endif

   if(( ucCurrentPressure < GETucMinWarnThresholdOfRam())
   || (scCurrentTireTemp > GETscOutdoorTemperatureFZZ() + 30)
   || (ucCurrentPressure < (GETucPcalMinHaRelativCodOfRam() - cDP_AUTO))){
      if(GETucCalNotAckStateOfRam() == cCAL_VALID){

         if(ucCurrentPressure < GETucMinWarnThresholdOfRam()){
            SetBitCalNotAckState2Ram(cCAL_P_MIN_TIRE_NAK);
            SetState2AbortReasonFD(cFD_P_MIN_TIRE);

         }
         else{
            if( ucCurrentPressure < (GETucPcalMinHaRelativCodOfRam() - cDP_AUTO)){

               SetState2AbortReasonFD(cFD_DP_AUTO);
            }
            else{
               if(scCurrentTireTemp > (GETscOutdoorTemperatureFZZ() + 30)){
                  SetBitCalNotAckState2Ram(cCAL_RE30K2AMBIENT);
                  SetState2AbortReasonFD(cFD_TIRE2HOT);
               }
            }
         }
         ucRtn=FALSE;
         SetState2FillingDetectionStateFD(cFILLING_DETECT_ABORTED);
         ClearPlausiFailureFD();
      }
   }
    else{
      if(ucREcnt4FD==1){
         PUTucDpStabiPressure(ucCurrentPressure,ucColOfID);
#ifdef as_16BitP4Average
         PUTucIdCalPressure(ucCurrentPressure,ucColOfID);
         PUTuiStoragePaverege4CompareValue(ucCurrentPressure,ucColOfID);
         PUTscIdCalTemperatur(scCurrentTireTemp,ucColOfID);
#endif
      }
      else{
         if(ucREcnt4FD != 0){
            if(ucREcnt4FD == 0xFF){
               if(ucCurrentPressure < (GETucDpStabiPressure(ucColOfID) - cDP_STABI)){
                  SetBitCalNotAckState2Ram(cCAL_DP_STABI_NAK );
                  SetState2AbortReasonFD(cFD_DP_STABI);
                  SetState2FillingDetectionStateFD(cFILLING_DETECT_ABORTED);
                  ClearPlausiFailureFD();
                  ucRtn=FALSE;
               }
            }
            else{

#ifdef as_16BitP4Average
               uiPaverage=(uint16)(GETucIdCalPressure(ucColOfID) * (ucREcnt4FD-1));
               uiPaverege4CompareValue=(GETuiStoragePaverege4CompareValue(ucColOfID) * (ucREcnt4FD-1));

               uiPaverage=(uint16)(ucCurrentPressure + uiPaverage );
               uiPaverege4CompareValue=((uint16)(ucCurrentPressure) + uiPaverege4CompareValue );

               PUTucIdCalPressure((uiPaverage/ucREcnt4FD),ucColOfID);
               PUTuiStoragePaverege4CompareValue((uiPaverege4CompareValue/ucREcnt4FD),ucColOfID);
#endif

               if(ucCurrentPressure < (GETucDpStabiPressure(ucColOfID) - cDP_STABI)){
                  SetBitCalNotAckState2Ram(cCAL_DP_STABI_NAK );
                  SetState2AbortReasonFD(cFD_DP_STABI);
                  SetState2FillingDetectionStateFD(cFILLING_DETECT_ABORTED);
                  ClearPlausiFailureFD();
                  ucRtn=FALSE;
               }
            }
         }
      }
   }
 return ucRtn;
}

void FD_PlausibilityCheckMFD(sint8 scTemperaturOutside){

   uint8 ucColOfIdVL,ucColOfIdVR,ucColOfIdHL, ucColOfIdHR;
    uint8 i;
   sint8 scTfillVA;
   sint8 scTfillHA;
   sint8 scTfill_Tref;
   uint8 ucRtn=FALSE;

   for( i = 0; i < cAnzRad; i++ ){
      switch (GETucWPorPWPofHistCol(i)){
         case cRadPosVL:
                  ucColOfIdVL=i;
         break;
         case cRadPosVR:
                  ucColOfIdVR=i;
         break;
         case cRadPosHL:
                  ucColOfIdHL=i;
         break;
         case cRadPosHR:
                 ucColOfIdHR=i;
         break;
         default:
         {
            ucRtn = TRUE;
         }
      }
   }

   if(ucRtn == FALSE){

      if(FD_Plausibility_CheckP4DPLR_DPABS(ucColOfIdVL,ucColOfIdVR,ucColOfIdHL,ucColOfIdHR) == TRUE){

         SetBitBetriebszustandBZ(cCAL_FINISH);
         ClearBitBetriebszustandBZ(cCAL_REQUEST);
         ClearPlausiFailureFD();
         ClearBitCalRequestState(cCAL_MANUAL_ACTIV);

         ClearCalRequestStateAtMFDfinish();
         SetBitCalRequestState2Ram(cCAL_MANUAL_FINISH);
         SetState2FillingDetectionStateFD(cFILLING_DETECTED);

         PUTucPrefFront((GETucIdCalPressure(ucColOfIdVL) + GETucIdCalPressure(ucColOfIdVR))/2);
         PUTucPrefRear((GETucIdCalPressure(ucColOfIdHL) + GETucIdCalPressure(ucColOfIdHR))/2);

         PUTucPfillFront(GETucPrefFront());
         PUTucPfillRear(GETucPrefRear());

         scTfillVA=((GETscIdCalTemperatur(ucColOfIdVL) + GETscIdCalTemperatur(ucColOfIdVR))/2);
         scTfillHA=((GETscIdCalTemperatur(ucColOfIdHL) + GETscIdCalTemperatur(ucColOfIdHR))/2);

         if(scTfillVA > cTfillLimitH){
            scTfillVA=cTfillLimitH;
         }
         if(scTfillHA > cTfillLimitH){
            scTfillHA=cTfillLimitH;
         }

          scTfill_Tref=(scTfillVA + scTfillHA)/2;
         PUTscTfill(scTfill_Tref);
         scTfill_Tref=KweightCalculation(scTfill_Tref, scTemperaturOutside);

         PUTucPrefFront(GetP4NewTempAtCAL(GETucPrefFront(),scTfillVA, scTfill_Tref));
         if(GETucPrefFront() <= GETucPcalMinVaRelativCodOfRam()){
            PUTucPrefFront( GETucPcalMinVaRelativCodOfRam());
         }

         PUTucPrefRear(GetP4NewTempAtCAL(GETucPrefRear(),scTfillHA, scTfill_Tref));
         if(GETucPrefRear() <= GETucPcalMinHaRelativCodOfRam()){
            PUTucPrefRear( GETucPcalMinHaRelativCodOfRam());
         }

         PUTscTref(scTfill_Tref);

         PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdVL)),GETscIdCalTemperatur(ucColOfIdVL), scTfill_Tref),cRadPosVL);
         PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdVR)),GETscIdCalTemperatur(ucColOfIdVR), scTfill_Tref),cRadPosVR);
         PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdHL)),GETscIdCalTemperatur(ucColOfIdHL), scTfill_Tref),cRadPosHL);
         PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdHR)),GETscIdCalTemperatur(ucColOfIdHR), scTfill_Tref),cRadPosHR);
          DelWarnOfId(4);

         ReplayLastREvalue2Walgo();

#ifdef FD_CONTROLS_FALLBACK

         if(bGETucCalNotAckState(cCAL_FBM_ACTIV_NAK) == TRUE){

          ClearPWP();
          Check4PWP();
         }

#endif

      }
      else{

         SetState2FillingDetectionStateFD(cFILLING_UNPLAUSIBLE);

         if((bGetBitBetriebszustandBZ(cCAL_FINISH) != TRUE) && (bGETucCalRequestState(cCAL_MANUAL_ACTIV)== TRUE)){

            SetBitBetriebszustandBZ(cCAL_FINISH | cCAL_MFD_PLAUSI_ERROR);
            ClearBitBetriebszustandBZ(cCAL_REQUEST);
            ClearBitCalRequestState(cCAL_MANUAL_ACTIV | cCAL_AUTO_NEW_ID);
            SetBitCalRequestState2Ram(cCAL_MANUAL_FINISH);

            PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdVL)),GETscIdCalTemperatur(ucColOfIdVL), GETscTref()),cRadPosVL);
            PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdVR)),GETscIdCalTemperatur(ucColOfIdVR), GETscTref()),cRadPosVR);
            PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdHL)),GETscIdCalTemperatur(ucColOfIdHL), GETscTref()),cRadPosHL);
            PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdHR)),GETscIdCalTemperatur(ucColOfIdHR), GETscTref()),cRadPosHR);

          }
         else{
            if((bGetBitBetriebszustandBZ(cCAL_FINISH) != TRUE) && (bGETucCalRequestState(cCAL_AUTO_ACTIV)== TRUE)){
               SetBitBetriebszustandBZ(cCAL_AFD_PLAUSI_ERROR);
               BZ_FZZ_RQ_State4AFD_Finish();
             }
         }
      }
   }
   else{
      SetState2PlausiFailureFD(cFD_FALL_BACK_NOPOS);
      if((bGetBitBetriebszustandBZ(cCAL_FINISH) != TRUE) && (bGETucCalRequestState(cCAL_MANUAL_ACTIV)== TRUE)){

         SetBitBetriebszustandBZ(cCAL_FINISH | cCAL_MFD_PLAUSI_ERROR);
         ClearBitBetriebszustandBZ(cCAL_REQUEST);
         SetBitCalRequestState2Ram(cCAL_MANUAL_FINISH);
         ClearBitCalRequestState(cCAL_MANUAL_ACTIV | cCAL_AUTO_NEW_ID);
      }
   }

}

void FD_UnplausibleMFD(void){
   uint8 ucColOfIdVL,ucColOfIdVR,ucColOfIdHL, ucColOfIdHR;
   uint8 i;
   uint8 ucRtn=FALSE;

   for( i = 0; i < cAnzRad; i++ ){
      switch (GETucWPorPWPofHistCol(i)){
         case cRadPosVL:
                  ucColOfIdVL=i;
         break;
         case cRadPosVR:
                  ucColOfIdVR=i;
         break;
         case cRadPosHL:
                  ucColOfIdHL=i;
         break;
         case cRadPosHR:
                 ucColOfIdHR=i;
         break;
         default:
         {
            ucRtn = TRUE;
         }
      }
   }

   if(ucRtn == FALSE){

      SetState2FillingDetectionStateFD(cFILLING_UNPLAUSIBLE);
      SetBitCalNotAckState2Ram(cCAL_P_MIN_X_MINUS_DP_MANUAL);
      SetState2PlausiFailureFD(cFD_DP_MANUAL);
      ClearAbortReasonFD();

      SetBitBetriebszustandBZ(cCAL_FINISH | cCAL_MFD_PLAUSI_ERROR);
      ClearBitBetriebszustandBZ(cCAL_REQUEST);
      ClearBitCalRequestState(cCAL_MANUAL_ACTIV | cCAL_AUTO_NEW_ID);
      SetBitCalRequestState2Ram(cCAL_MANUAL_FINISH);

      PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdVL)),GETscIdCalTemperatur(ucColOfIdVL), GETscTref()),cRadPosVL);
      PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdVR)),GETscIdCalTemperatur(ucColOfIdVR), GETscTref()),cRadPosVR);
      PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdHL)),GETscIdCalTemperatur(ucColOfIdHL), GETscTref()),cRadPosHL);
      PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdHR)),GETscIdCalTemperatur(ucColOfIdHR), GETscTref()),cRadPosHR);

   }
   else{
      SetState2PlausiFailureFD(cFD_FALL_BACK_NOPOS);
      if((bGetBitBetriebszustandBZ(cCAL_FINISH) != TRUE) && (bGETucCalRequestState(cCAL_MANUAL_ACTIV)== TRUE)){

         SetBitBetriebszustandBZ(cCAL_FINISH | cCAL_MFD_PLAUSI_ERROR);
         ClearBitBetriebszustandBZ(cCAL_REQUEST);
         ClearBitCalRequestState(cCAL_MANUAL_ACTIV | cCAL_AUTO_NEW_ID);
         SetBitCalRequestState2Ram(cCAL_MANUAL_FINISH);
      }
   }
}

void FD_Check3RePlausiSetMilage4FinishedMFD(void){
   if(Get_FD_STATUS() == FALSE){
      if(bGETucCalRequestState(cCAL_MANUAL_ACTIV) == TRUE){
         SetState2FillingDetectionStateFD(cMFD_RUNNING);
      }
   }

   if(( GETucRErecCounter4FDVL() <3) && ( GETucRErecCounter4FDVR() <3) && ( GETucRErecCounter4FDHL() <3) &&( GETucRErecCounter4FDHR() <3)){
      if((bGetBitBetriebszustandBZ(cZO_TIMEOUT) == TRUE ) || (bGetBitBetriebszustandBZ(cZO_FINISH) == TRUE )){
         FD_LoadIdValues4MFD();
      }
   }

   if(( GETucRErecCounter4FDVL() >=3) && ( GETucRErecCounter4FDVR() >=3) && ( GETucRErecCounter4FDHL() >=3) &&( GETucRErecCounter4FDHR() >=3)
      && (((bGetBitBetriebszustandBZ(cZO_FINISH) == TRUE)
      || ((bGetBitBetriebszustandBZ(cZO_TIMEOUT) == TRUE ) && (ui8GetALState() == cAL_Stored))
      || ((bGetBitBetriebszustandBZ(cZO_TIMEOUT) == TRUE ) && (ui8GetALState() == cAL_OK))
      || (Getui8ColPWPActive() != FALSE) ))){
      if(ucCheckAllRePcalMinDPmanualMFD() == TRUE){

         FD_UnplausibleMFD();
      }
      else{
         FD_PlausibilityCheckMFD((sint8)(tEnvDataToSend.ucTempOut));
         PUTucOnceCheckMissingRE4FD(TRUE);
      }
      PUTushFDtimeout(0);
      PUTucFDtimerStop(TRUE);

      if(Get_FD_STATUS() == cFILLING_DETECTED){
         PUTulLastCalMileage(GETulKmStand4AutoCAL());
      }
      if( bGETucCalRequestState(cCAL_AUTO_FIRST) == FALSE){
         SetBitCalRequestState2Ram(cCAL_AUTO_FIRST);
      }
   }
}

void FD_Check3ReAndUpdatePifWarnLampOnOffDefOrInf2Re4FinishedAFD(void){
   uint8 ucDeflationLTS;

   if(bGETucCalRequestState(cCAL_AUTO_ACTIV) == TRUE){
      if(Get_FD_STATUS() == FALSE){
         if(bGETucCalRequestState(cCAL_AUTO_ENABLE2) == TRUE){
            SetState2FillingDetectionStateFD(cAFD_RUNNING2);
         }
         else{
            if(bGETucCalRequestState(cCAL_AUTO_ENABLE3) == TRUE){
               SetState2FillingDetectionStateFD(cAFD_RUNNING3);
            }
         }
      }

      if(( GETucRErecCounter4FDVL() >=3) && ( GETucRErecCounter4FDVR() >=3) && ( GETucRErecCounter4FDHL() >=3) &&( GETucRErecCounter4FDHR() >=3) ){
         ucDeflationLTS=(GETucCnt4DP_FILL_DFL() & 0x0F);
         ucDeflationLTS=(ucDeflationLTS | (GETucDFL_LTS3() & 0xF0));
         if(GETushWarnstatus1WN() == FALSE){
            FD_UpdatePressure4AfdWarnLampOFF(ucDeflationLTS, GETucCnt4DP_FILL_IFL(), (sint8)(tEnvDataToSend.ucTempOut) );
         }
         else{
            FD_UpdatePressure4AfdWarnLampON(GETucCnt4DP_FILL_IFL(), (sint8)(tEnvDataToSend.ucTempOut) );
         }

         PUTushFDtimeout(0);
         PUTucFDtimerStop(TRUE);
         if( bGETucCalRequestState(cCAL_AUTO_FIRST) == FALSE){
            SetBitCalRequestState2Ram(cCAL_AUTO_FIRST);
         }
         if(bGetBitBetriebszustandBZ(cZO_FINISH) == FALSE){
            PUTucFDcheckP2PosOk(5);
         }
      }
   }
}

void FD_UpdatePressure4AfdWarnLampON( uint8 ucAfd_Inflated, sint8 scTemperaturOutside){
   uint8 ucColOfIdVL,ucColOfIdVR,ucColOfIdHL, ucColOfIdHR;
   uint8 i;
   sint8 scTfillVA;
   sint8 scTfillHA;
   sint8 scTfill_Tref;
   uint8 ucRtn=FALSE;

   for( i = 0; i < cAnzRad; i++ ){
      switch (GETucWPorPWPofHistCol(i)){
         case cRadPosVL:
                  ucColOfIdVL=i;
         break;
         case cRadPosVR:
                 ucColOfIdVR=i;
         break;
         case cRadPosHL:
                  ucColOfIdHL=i;
         break;
         case cRadPosHR:
                   ucColOfIdHR=i;
         break;
         default:
         {
            ucRtn = TRUE;
         }
      }
   }

   if(ucRtn == FALSE){

      if((ucAfd_Inflated & 0x0F) >= 2){

         if((GETaucWheelPosWarn(cRadPosVL) != FALSE) && ((ucAfd_Inflated & cDP_FILL_FL) != cDP_FILL_FL)){
            ucRtn=TRUE;
         }
         if((GETaucWheelPosWarn(cRadPosVR) != FALSE) && ((ucAfd_Inflated & cDP_FILL_FR) != cDP_FILL_FR)){
            ucRtn=TRUE;
         }
         if((GETaucWheelPosWarn(cRadPosHL) != FALSE) && ((ucAfd_Inflated & cDP_FILL_RL) != cDP_FILL_RL)){
            ucRtn=TRUE;
         }
         if((GETaucWheelPosWarn(cRadPosHR) != FALSE) && ((ucAfd_Inflated & cDP_FILL_RR) != cDP_FILL_RR)){
            ucRtn=TRUE;
         }

         if(ucRtn == TRUE){

            SetState2FillingDetectionStateFD(cFD_ACTIV_WARNING);

            if((GETaucWheelPosWarn(cRadPosVL) == FALSE) && ((ucAfd_Inflated & cDP_FILL_FL) == cDP_FILL_FL)){

               PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdVL)),GETscIdCalTemperatur(ucColOfIdVL), GETscTref()),cRadPosVL);
               ucRePosStorageVL4FD=ucColOfIdVL;
            }
            if((GETaucWheelPosWarn(cRadPosVR) == FALSE) && ((ucAfd_Inflated & cDP_FILL_FR) == cDP_FILL_FR)){

               PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdVR)),GETscIdCalTemperatur(ucColOfIdVR), GETscTref()),cRadPosVR);
               ucRePosStorageVR4FD=ucColOfIdVR;
            }
            if((GETaucWheelPosWarn(cRadPosHL) == FALSE) && ((ucAfd_Inflated & cDP_FILL_RL) == cDP_FILL_RL)){

               PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdHL)),GETscIdCalTemperatur(ucColOfIdHL), GETscTref()),cRadPosHL);
               ucRePosStorageHL4FD=ucColOfIdHL;
            }
            if((GETaucWheelPosWarn(cRadPosHR) == FALSE) && ((ucAfd_Inflated & cDP_FILL_RR) == cDP_FILL_RR)){

               PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdHR)),GETscIdCalTemperatur(ucColOfIdHR), GETscTref()),cRadPosHR);
               ucRePosStorageHR4FD=ucColOfIdHR;
            }
         }
         else{

            SetState2FillingDetectionStateFD(cFILLING_DETECTED);
         }
      }
      else{
         if((ucAfd_Inflated & 0x0F) == 1){
            SetState2FillingDetectionStateFD(cFILLING_NOT_DETECTED);

            PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdVL)),GETscIdCalTemperatur(ucColOfIdVL), GETscTref()),cRadPosVL);
            PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdVR)),GETscIdCalTemperatur(ucColOfIdVR), GETscTref()),cRadPosVR);
            PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdHL)),GETscIdCalTemperatur(ucColOfIdHL), GETscTref()),cRadPosHL);
            PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdHR)),GETscIdCalTemperatur(ucColOfIdHR), GETscTref()),cRadPosHR);

            ucRePosStorageVL4FD=ucColOfIdVL;
            ucRePosStorageVR4FD=ucColOfIdVR;
            ucRePosStorageHL4FD=ucColOfIdHL;
            ucRePosStorageHR4FD=ucColOfIdHR;

         }
         else{
            if((GETaucWheelPosWarn(cRadPosVL) != FALSE) || (GETaucWheelPosWarn(cRadPosVR) != FALSE) || (GETaucWheelPosWarn(cRadPosHL) != FALSE) || (GETaucWheelPosWarn(cRadPosHR) != FALSE)){
               SetState2FillingDetectionStateFD(cFD_ACTIV_WARNING);
            }
            else{
               SetState2FillingDetectionStateFD(cFILLING_NOT_DETECTED);
            }

         }
         ucRtn=TRUE;
      }

         if(ucRtn == FALSE){
            ClearBitBetriebszustandBZ(cCAL_AFD_PLAUSI_ERROR);

            if(FD_Plausibility_CheckP4DPLR_DPABS(ucColOfIdVL,ucColOfIdVR,ucColOfIdHL,ucColOfIdHR) == TRUE){

               ucRePosStorageVL4FD=ucColOfIdVL;
               ucRePosStorageVR4FD=ucColOfIdVR;
               ucRePosStorageHL4FD=ucColOfIdHL;
               ucRePosStorageHR4FD=ucColOfIdHR;

               SetBitBetriebszustandBZ(cCAL_FINISH);
               BZ_FZZ_RQ_State4AFD_Finish();
               PUTucPrefFront(((GETucIdCalPressure(ucColOfIdVL) + GETucIdCalPressure(ucColOfIdVR))/2));
               PUTucPrefRear(((GETucIdCalPressure(ucColOfIdHL) + GETucIdCalPressure(ucColOfIdHR))/2));

               PUTucPfillFront(GETucPrefFront());
               PUTucPfillRear(GETucPrefRear());

               scTfillVA=((GETscIdCalTemperatur(ucColOfIdVL) + GETscIdCalTemperatur(ucColOfIdVR))/2);
               scTfillHA=((GETscIdCalTemperatur(ucColOfIdHL) + GETscIdCalTemperatur(ucColOfIdHR))/2);
               if(scTfillVA > cTfillLimitH){
                  scTfillVA=cTfillLimitH;
               }
               if(scTfillHA > cTfillLimitH){
                  scTfillHA=cTfillLimitH;
               }

               scTfill_Tref=(scTfillVA + scTfillHA)/2;
               PUTscTfill(scTfill_Tref);
               scTfill_Tref=KweightCalculation(scTfill_Tref, scTemperaturOutside);

               PUTucPrefFront(GetP4NewTempAtCAL(GETucPrefFront(),scTfillVA, scTfill_Tref));
               if(GETucPrefFront() <= GETucPcalMinVaRelativCodOfRam()){
                  PUTucPrefFront(GETucPcalMinVaRelativCodOfRam());
               }

               PUTucPrefRear(GetP4NewTempAtCAL(GETucPrefRear(),scTfillHA, scTfill_Tref));
               if(GETucPrefRear() <= GETucPcalMinHaRelativCodOfRam()){
                  PUTucPrefRear(GETucPcalMinHaRelativCodOfRam());
               }

               PUTscTref(scTfill_Tref);

               PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdVL)),GETscIdCalTemperatur(ucColOfIdVL), scTfill_Tref),cRadPosVL);
               PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdVR)),GETscIdCalTemperatur(ucColOfIdVR), scTfill_Tref),cRadPosVR);
               PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdHL)),GETscIdCalTemperatur(ucColOfIdHL), scTfill_Tref),cRadPosHL);
               PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdHR)),GETscIdCalTemperatur(ucColOfIdHR), scTfill_Tref),cRadPosHR);

               DelWarnOfId(4);
               ReplayLastREvalue2Walgo();
            }
            else{

               SetState2FillingDetectionStateFD(cFILLING_UNPLAUSIBLE);
                SetBitBetriebszustandBZ(cCAL_AFD_PLAUSI_ERROR);
               BZ_FZZ_RQ_State4AFD_Finish();

               PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdVL)),GETscIdCalTemperatur(ucColOfIdVL), GETscTref()),cRadPosVL);
               PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdVR)),GETscIdCalTemperatur(ucColOfIdVR), GETscTref()),cRadPosVR);
               PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdHL)),GETscIdCalTemperatur(ucColOfIdHL), GETscTref()),cRadPosHL);
               PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdHR)),GETscIdCalTemperatur(ucColOfIdHR), GETscTref()),cRadPosHR);

               ucRePosStorageVL4FD=ucColOfIdVL;
               ucRePosStorageVR4FD=ucColOfIdVR;
               ucRePosStorageHL4FD=ucColOfIdHL;
               ucRePosStorageHR4FD=ucColOfIdHR;

            }
         }
         else{
            ClearBitBetriebszustandBZ(cCAL_AFD_PLAUSI_ERROR);
            BZ_FZZ_RQ_State4AFD_Finish();
         }
   }
   else{
      BZ_FZZ_RQ_State4AFD_Finish();
   }
}

void FD_UpdatePressure4AfdWarnLampOFF(uint8 ucAfd_Deflated, uint8 ucAfd_Inflated, sint8 scTemperaturOutside){
   uint8 ucColOfIdVL,ucColOfIdVR,ucColOfIdHL, ucColOfIdHR;
   uint8 i;
   sint8 scTfillVA;
   sint8 scTfillHA;
   sint8 scTfill_Tref;
   uint8 ucRtn=FALSE;

   for( i = 0; i < cAnzRad; i++ ){
      switch (GETucWPorPWPofHistCol(i)){
         case cRadPosVL:
                  ucColOfIdVL=i;
         break;
         case cRadPosVR:
                 ucColOfIdVR=i;
         break;
         case cRadPosHL:
                  ucColOfIdHL=i;
         break;
         case cRadPosHR:
                   ucColOfIdHR=i;
         break;
         default:
         {
            ucRtn = TRUE;
         }
      }
   }

   if(((ucRtn == FALSE) && ((GETulLastCalMileage() != c_FFFFkm) && (GETulLastCalMileage() < c_FF9Bkm))) || ((ucRtn == FALSE) && (GETulLastCalMileage() == c_FFFFkm))){

         if(((GETulLastCalMileage() != c_FFFFkm) && (((ucAfd_Inflated & 0x0F) >= 2) || ((((ucAfd_Deflated & 0x0F) >=2) && (GETulKmStand4AutoCAL() > (GETulLastCalMileage() + c_100km))) && (ucAfd_Deflated & 0x80) != 0x80 )))
         || (((GETulLastCalMileage() == c_FFFFkm)  && ((ucAfd_Deflated & 0x0F) >=2) ||  ((ucAfd_Inflated & 0x0F) >= 2) ))){

            ClearBitBetriebszustandBZ(cCAL_AFD_PLAUSI_ERROR);

            if(FD_Plausibility_CheckP4DPLR_DPABS(ucColOfIdVL,ucColOfIdVR,ucColOfIdHL,ucColOfIdHR) == TRUE){

               ucRePosStorageVL4FD=ucColOfIdVL;
               ucRePosStorageVR4FD=ucColOfIdVR;
               ucRePosStorageHL4FD=ucColOfIdHL;
               ucRePosStorageHR4FD=ucColOfIdHR;

               BZ_FZZ_RQ_State4AFD_Finish();
               SetState2FillingDetectionStateFD(cFILLING_DETECTED);

               PUTucPrefFront(((GETucIdCalPressure(ucColOfIdVL) + GETucIdCalPressure(ucColOfIdVR))/2));
               PUTucPrefRear(((GETucIdCalPressure(ucColOfIdHL) + GETucIdCalPressure(ucColOfIdHR))/2));

               PUTucPfillFront(GETucPrefFront());
               PUTucPfillRear(GETucPrefRear());

               scTfillVA=((GETscIdCalTemperatur(ucColOfIdVL) + GETscIdCalTemperatur(ucColOfIdVR))/2);
               scTfillHA=((GETscIdCalTemperatur(ucColOfIdHL) + GETscIdCalTemperatur(ucColOfIdHR))/2);
               if(scTfillVA > cTfillLimitH){
                  scTfillVA=cTfillLimitH;
               }
               if(scTfillHA > cTfillLimitH){
                  scTfillHA=cTfillLimitH;
               }

               scTfill_Tref=(scTfillVA + scTfillHA)/2;
               PUTscTfill(scTfill_Tref);
               scTfill_Tref=KweightCalculation(scTfill_Tref, scTemperaturOutside);

               PUTucPrefFront(GetP4NewTempAtCAL(GETucPrefFront(),scTfillVA, scTfill_Tref));
               if(GETucPrefFront() <= GETucPcalMinVaRelativCodOfRam()){
                  PUTucPrefFront(GETucPcalMinVaRelativCodOfRam());
               }

               PUTucPrefRear(GetP4NewTempAtCAL(GETucPrefRear(),scTfillHA, scTfill_Tref));
               if(GETucPrefRear() <= GETucPcalMinHaRelativCodOfRam()){
                  PUTucPrefRear(GETucPcalMinHaRelativCodOfRam());
               }

               PUTscTref(scTfill_Tref);

               PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdVL)),GETscIdCalTemperatur(ucColOfIdVL), scTfill_Tref),cRadPosVL);
               PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdVR)),GETscIdCalTemperatur(ucColOfIdVR), scTfill_Tref),cRadPosVR);
               PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdHL)),GETscIdCalTemperatur(ucColOfIdHL), scTfill_Tref),cRadPosHL);
               PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdHR)),GETscIdCalTemperatur(ucColOfIdHR), scTfill_Tref),cRadPosHR);

               DelWarnOfId(4);
               ReplayLastREvalue2Walgo();

            }
            else{

               SetState2FillingDetectionStateFD(cFILLING_UNPLAUSIBLE);
               SetBitBetriebszustandBZ(cCAL_AFD_PLAUSI_ERROR);

               BZ_FZZ_RQ_State4AFD_Finish();

               PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdVL)),GETscIdCalTemperatur(ucColOfIdVL), GETscTref()),cRadPosVL);
               PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdVR)),GETscIdCalTemperatur(ucColOfIdVR), GETscTref()),cRadPosVR);
               PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdHL)),GETscIdCalTemperatur(ucColOfIdHL), GETscTref()),cRadPosHL);
               PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdHR)),GETscIdCalTemperatur(ucColOfIdHR), GETscTref()),cRadPosHR);

               ucRePosStorageVL4FD=ucColOfIdVL;
               ucRePosStorageVR4FD=ucColOfIdVR;
               ucRePosStorageHL4FD=ucColOfIdHL;
               ucRePosStorageHR4FD=ucColOfIdHR;

            }
         }
         else{

            SetState2FillingDetectionStateFD(cFILLING_NOT_DETECTED);

            if((bGetBitBetriebszustandBZ(cCAL_FINISH) != TRUE) && (bGETucCalRequestState(cCAL_AUTO_ACTIV)== TRUE)){
               ucRtn = TRUE;

               if((ucAfd_Deflated & 0x0F) >= 2){
                  if((ucAfd_Deflated & 0x80) == 0x80){
                     SetState2FillingDetectionStateFD(cFD_LTS30DAYS);
                  }
                  else{
                     if(GETulLastCalMileage() == c_FFFFkm){
                        if(FD_Plausibility_CheckP4DPLR_DPABS(ucColOfIdVL,ucColOfIdVR,ucColOfIdHL,ucColOfIdHR) == FALSE){

                           SetState2FillingDetectionStateFD(cFILLING_UNPLAUSIBLE);
                           SetBitBetriebszustandBZ(cCAL_AFD_PLAUSI_ERROR);
                           ucRtn = FALSE;
                        }
                     }
                     else{
                        if(GETulKmStand4AutoCAL() <= (GETulLastCalMileage() + c_100km)){
                           SetState2FillingDetectionStateFD(cFD_MILEAGE2SMALL);
                        }

                     }
                  }
               }

               if(ucRtn == TRUE ){

                  FD_CheckResetCondition4ImplausiMsg(ucColOfIdVL,ucColOfIdVR,ucColOfIdHL,ucColOfIdHR);

               }
            }

            BZ_FZZ_RQ_State4AFD_Finish();

            PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdVL)),GETscIdCalTemperatur(ucColOfIdVL), GETscTref()),cRadPosVL);
            PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdVR)),GETscIdCalTemperatur(ucColOfIdVR), GETscTref()),cRadPosVR);
            PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdHL)),GETscIdCalTemperatur(ucColOfIdHL), GETscTref()),cRadPosHL);
            PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdHR)),GETscIdCalTemperatur(ucColOfIdHR), GETscTref()),cRadPosHR);

            ucRePosStorageVL4FD=ucColOfIdVL;
            ucRePosStorageVR4FD=ucColOfIdVR;
            ucRePosStorageHL4FD=ucColOfIdHL;
            ucRePosStorageHR4FD=ucColOfIdHR;

            ReplayLastREvalue2Walgo();
         }
   }
   else{
      BZ_FZZ_RQ_State4AFD_Finish();
   }
}

void FD_UpdateComparePressureAtWarning(uint8 ucTPM_WarnDisp_Rq4CmpP){
   uint8 i;
   uint8 ucColOfIdVL,ucColOfIdVR,ucColOfIdHL, ucColOfIdHR;
   uint8 ucPcompareVL,ucPcompareVR,ucPcompareHL,ucPcompareHR;
   uint8 ucLastReceivedTemp;
   uint8 ucRtn=FALSE;

   if(Getui8ColPWPActive() == FALSE){

      if(ucTPM_WarnDisp_Rq4CmpP != FALSE){

         for( i = 0; i < cAnzRad; i++ ){
            switch (GETucWPorPWPofHistCol(i)){
               case cRadPosVL:
                        ucColOfIdVL=i;
               break;
               case cRadPosVR:
                       ucColOfIdVR=i;
               break;
               case cRadPosHL:
                        ucColOfIdHL=i;
               break;
               case cRadPosHR:
                         ucColOfIdHR=i;
               break;
               default:
               {
                  ucRtn = TRUE;
               }
            }
         }

         if(ucRtn == FALSE){

            if((ucGetLastReceivedPress(ulGetID(ucColOfIdVL)) != 0xFF)
            &&(ucGetLastReceivedPress(ulGetID(ucColOfIdVR)) != 0xFF)
            &&(ucGetLastReceivedPress(ulGetID(ucColOfIdHL)) != 0xFF)
            &&(ucGetLastReceivedPress(ulGetID(ucColOfIdHR)) != 0xFF)){

               ClearBitBetriebszustandBZ(cCAL_AFD_PLAUSI_ERROR | cCAL_MFD_PLAUSI_ERROR);
               ucLastReceivedTemp=(ucGetLastReceivedTemp(ulGetID(ucColOfIdVL)));
               if((ucLastReceivedTemp != 0xFF) && (ucLastReceivedTemp != 0x00)){

                  ucPcompareVL=GetP4NewTempAtCAL(ucGetLastReceivedPress(ulGetID(ucColOfIdVL)),((sint8) (ucLastReceivedTemp- ucPalTempNormFACTOR4Calc)), GETscTref());
                  if((ucGetHMICurrentTireStat(cRadPosVL) != I_C02_TIRE_STAT_NORMAL) && (ucStoreCompValueVL== FALSE)){
                     PUTucPosComparePressure(ucPcompareVL,cRadPosVL);
                     ucStoreCompValueVL=TRUE;
                     ucRtn=TRUE;
                   }
                  else{
                     if(ucStoreCompValueVL == TRUE){
                        if(GETucPosComparePressure(cRadPosVL) > ucPcompareVL){
                           if((GETucPosComparePressure(cRadPosVL) - ucPcompareVL) >= cDP_STABI){
                              PUTucPosComparePressure(ucPcompareVL,cRadPosVL);
                           }
                        }
                     }
                  }
               }

               ucLastReceivedTemp=(ucGetLastReceivedTemp(ulGetID(ucColOfIdVR)));
               if((ucLastReceivedTemp != 0xFF) && (ucLastReceivedTemp != 0x00)){
                  ucPcompareVR=GetP4NewTempAtCAL(ucGetLastReceivedPress(ulGetID(ucColOfIdVR)),((sint8) (ucLastReceivedTemp- ucPalTempNormFACTOR4Calc)), GETscTref());
                  if((ucGetHMICurrentTireStat(cRadPosVR) != I_C02_TIRE_STAT_NORMAL) && (ucStoreCompValueVR== FALSE)){
                     PUTucPosComparePressure(ucPcompareVR,cRadPosVR);
                     ucStoreCompValueVR=TRUE;
                     ucRtn=TRUE;
                  }
                  else{
                     if(ucStoreCompValueVR == TRUE){
                        if(GETucPosComparePressure(cRadPosVR) > ucPcompareVR){
                           if((GETucPosComparePressure(cRadPosVR) - ucPcompareVR) >= cDP_STABI){
                              PUTucPosComparePressure(ucPcompareVR,cRadPosVR);
                           }
                        }
                     }
                  }
               }

               ucLastReceivedTemp=(ucGetLastReceivedTemp(ulGetID(ucColOfIdHL)));
               if((ucLastReceivedTemp != 0xFF) && (ucLastReceivedTemp != 0x00)){
                  ucPcompareHL=GetP4NewTempAtCAL(ucGetLastReceivedPress(ulGetID(ucColOfIdHL)),((sint8) (ucLastReceivedTemp- ucPalTempNormFACTOR4Calc)), GETscTref());
                  if((ucGetHMICurrentTireStat(cRadPosHL) != I_C02_TIRE_STAT_NORMAL) && (ucStoreCompValueHL == FALSE)){
                     PUTucPosComparePressure(ucPcompareHL,cRadPosHL);
                      ucStoreCompValueHL=TRUE;
                     ucRtn=TRUE;
                  }
                  else{
                     if(ucStoreCompValueHL == TRUE){
                        if(GETucPosComparePressure(cRadPosHL) > ucPcompareHL){
                           if((GETucPosComparePressure(cRadPosHL) - ucPcompareHL) >= cDP_STABI){
                              PUTucPosComparePressure(ucPcompareHL,cRadPosHL);
                           }
                        }
                     }
                  }
               }

               ucLastReceivedTemp=(ucGetLastReceivedTemp(ulGetID(ucColOfIdHR)));
               if((ucLastReceivedTemp != 0xFF) && (ucLastReceivedTemp != 0x00)){
                  ucPcompareHR=GetP4NewTempAtCAL(ucGetLastReceivedPress(ulGetID(ucColOfIdHR)),((sint8) (ucLastReceivedTemp- ucPalTempNormFACTOR4Calc)), GETscTref());
                  if((ucGetHMICurrentTireStat(cRadPosHR) != I_C02_TIRE_STAT_NORMAL) && (ucStoreCompValueHR == FALSE)){
                     PUTucPosComparePressure(ucPcompareHR,cRadPosHR);
                      ucStoreCompValueHR=TRUE;
                     ucRtn=TRUE;
                  }
                  else{
                     if(ucStoreCompValueHR == TRUE){
                        if(GETucPosComparePressure(cRadPosHR) > ucPcompareHR){
                           if((GETucPosComparePressure(cRadPosHR) - ucPcompareHR) >= cDP_STABI){
                              PUTucPosComparePressure(ucPcompareHR,cRadPosHR);
                           }
                        }
                     }
                  }
               }

               if(GETucAutoFillDetectionOnOffOfRam() == FALSE){
                  if((ucPcompareVL < GETucMinWarnThresholdOfRam())
                     ||(ucPcompareVR < GETucMinWarnThresholdOfRam())
                     ||(ucPcompareHL < GETucMinWarnThresholdOfRam())
                     ||(ucPcompareHR < GETucMinWarnThresholdOfRam())){
                     ClearCalNotAckState4MFD();
                     SetBitCalNotAckState2Ram(cCAL_P_MIN_TIRE_NAK);
                     SetState2AbortReasonFD(cFD_P_MIN_TIRE);
                     SetState2FillingDetectionStateFD(cFILLING_DETECT_ABORTED);
                  }
                  else{
                     if(   GETucCalNotAckStateOfRam() ==  cCAL_P_MIN_TIRE_NAK){
                        ClearCalNotAckState4MFD();
                        ClearAbortReasonFD();
                        ClearFillingDetectionStateFD();
                     }
                  }
               }

               if(ucRtn==TRUE){
                  ucRtn=FALSE;
               }
            }
         }
      }
      else{
         ucStoreCompValueVL=FALSE;
         ucStoreCompValueVR=FALSE;
         ucStoreCompValueHL=FALSE;
         ucStoreCompValueHR=FALSE;
      }
   }
   else{
      FD_AfdStopp4PWP();
   }

}

uint8 FD_UpdateComparePressureAfterFBM(void){
   uint8 i;
   uint8 ucColOfIdVL,ucColOfIdVR,ucColOfIdHL, ucColOfIdHR;
   uint8 ucPcompareVL,ucPcompareVR,ucPcompareHL,ucPcompareHR;
   uint8 ucLastReceivedTemp;
   uint8 ucRtn=TRUE;

   for( i = 0; i < cAnzRad; i++ ){
      switch (GETucWPorPWPofHistCol(i)){
         case cRadPosVL:
                  ucColOfIdVL=i;
         break;
         case cRadPosVR:
                  ucColOfIdVR=i;
         break;
         case cRadPosHL:
                  ucColOfIdHL=i;
         break;
         case cRadPosHR:
                  ucColOfIdHR=i;
         break;
         default:
         {
            ucRtn = FALSE;
         }
      }
   }

   if(ucRtn == TRUE){
      if((ucGetLastReceivedPress(ulGetID(ucColOfIdVL)) != 0xFF)
         &&(ucGetLastReceivedPress(ulGetID(ucColOfIdVR)) != 0xFF)
         &&(ucGetLastReceivedPress(ulGetID(ucColOfIdHL)) != 0xFF)
         &&(ucGetLastReceivedPress(ulGetID(ucColOfIdHR)) != 0xFF)){

         ClearBitBetriebszustandBZ(cCAL_MFD_PLAUSI_ERROR);

         ucLastReceivedTemp=ucGetLastReceivedTemp(ulGetID(ucColOfIdVL));
         if((ucLastReceivedTemp != 0xFF) && (ucLastReceivedTemp != 0x00)){
            ucPcompareVL=GetP4NewTempAtCAL(ucGetLastReceivedPress(ulGetID(ucColOfIdVL)),((sint8)(ucLastReceivedTemp- ucPalTempNormFACTOR4Calc)), GETscTref());
            PUTucPosComparePressure(ucPcompareVL,cRadPosVL);
         }

         ucLastReceivedTemp=ucGetLastReceivedTemp(ulGetID(ucColOfIdVR));
         if((ucLastReceivedTemp != 0xFF) && (ucLastReceivedTemp != 0x00)){
            ucPcompareVR=GetP4NewTempAtCAL(ucGetLastReceivedPress(ulGetID(ucColOfIdVR)),((sint8)(ucLastReceivedTemp- ucPalTempNormFACTOR4Calc)), GETscTref());
            PUTucPosComparePressure(ucPcompareVR,cRadPosVR);
         }

         ucLastReceivedTemp=ucGetLastReceivedTemp(ulGetID(ucColOfIdHL));
         if((ucLastReceivedTemp != 0xFF) && (ucLastReceivedTemp != 0x00)){
            ucPcompareHL=GetP4NewTempAtCAL(ucGetLastReceivedPress(ulGetID(ucColOfIdHL)),((sint8)(ucLastReceivedTemp- ucPalTempNormFACTOR4Calc)), GETscTref());
            PUTucPosComparePressure(ucPcompareHL,cRadPosHL);
         }

         ucLastReceivedTemp=ucGetLastReceivedTemp(ulGetID(ucColOfIdHR));
         if((ucLastReceivedTemp != 0xFF) && (ucLastReceivedTemp != 0x00)){
            ucPcompareHR=GetP4NewTempAtCAL(ucGetLastReceivedPress(ulGetID(ucColOfIdHR)),((sint8)(ucLastReceivedTemp- ucPalTempNormFACTOR4Calc)), GETscTref());
            PUTucPosComparePressure(ucPcompareHR,cRadPosHR);
         }

         if((ucPcompareVL < GETucMinWarnThresholdOfRam())
            ||(ucPcompareVR < GETucMinWarnThresholdOfRam())
            ||(ucPcompareHL < GETucMinWarnThresholdOfRam())
            ||(ucPcompareHR < GETucMinWarnThresholdOfRam())){
            ClearCalNotAckState4MFD();
            SetBitCalNotAckState2Ram(cCAL_P_MIN_TIRE_NAK);
            SetState2AbortReasonFD(cFD_P_MIN_TIRE);
            SetState2FillingDetectionStateFD(cFILLING_DETECT_ABORTED);
         }
         else{
            ClearFillingDetectionStateFD();
            ClearPlausiFailureFD();
            ClearAbortReasonFD();
         }
      }
      else{
         ucRtn = FALSE;
      }
   }
   return ucRtn;
}

uint8 FD_UpdateIDvalue4MFD(void){

   uint8 i;
   uint8 ucColOfIdVL,ucColOfIdVR,ucColOfIdHL, ucColOfIdHR;
   uint32 ulTelID;
   uint8 ucRtn=TRUE;
   uint8 ucReCounter4FDVL,ucReCounter4FDVR,ucReCounter4FDHL,ucReCounter4FDHR;
   uint8 ucPvonReDVL,ucPvonReDVR,ucPvonReDHL,ucPvonReDHR;

   for( i = 0; i < cAnzRad; i++ ){
      switch (GETucWPorPWPofHistCol(i)){
         case cRadPosVL:
                  ucColOfIdVL=i;
         break;
         case cRadPosVR:
                  ucColOfIdVR=i;
         break;
         case cRadPosHL:
                  ucColOfIdHL=i;
         break;
         case cRadPosHR:
                  ucColOfIdHR=i;
         break;
         default:
         {
            ucRtn = FALSE;
         }
      }
   }

   if(ucRtn == TRUE){

      ulTelID =   ulGetID(ucColOfIdVL);
      ucReCounter4FDVL=ucGetAvgCntr4FD( ulTelID);
      ucPvonReDVL = ucGetAvgPress4FD(ulTelID);
      if((ucPvonReDVL != 0xFF)  && (ucPvonReDVL!= 0x00) && (ucReCounter4FDVL !=0xFF )){
         if(ucReCounter4FDVL >= 3){
            PUTucRErecCounter4FDVL(ucReCounter4FDVL);
            PUTucIdCalPressure(ucPvonReDVL,ucGetColOfID(&ulTelID));
            PUTuiStoragePaverege4CompareValue(ucPvonReDVL,ucGetColOfID(&ulTelID));
            PUTscIdCalTemperatur((ucGetLastReceivedTemp(ulTelID)- ucPalTempNormFACTOR4Calc),ucGetColOfID(&ulTelID));

          }
      }
      ulTelID =   ulGetID(ucColOfIdVR);
      ucReCounter4FDVR=ucGetAvgCntr4FD( ulTelID);
      ucPvonReDVR = ucGetAvgPress4FD(ulTelID);
      if((ucPvonReDVR != 0xFF)  && (ucPvonReDVR!= 0x00) && (ucReCounter4FDVR !=0xFF )){
         if(ucReCounter4FDVR >= 3){
            PUTucRErecCounter4FDVR(ucReCounter4FDVR);
            PUTucIdCalPressure(ucPvonReDVR,ucGetColOfID(&ulTelID));
            PUTuiStoragePaverege4CompareValue(ucPvonReDVR,ucGetColOfID(&ulTelID));
            PUTscIdCalTemperatur((ucGetLastReceivedTemp(ulTelID)- ucPalTempNormFACTOR4Calc),ucGetColOfID(&ulTelID));

         }
      }

      ulTelID =   ulGetID(ucColOfIdHL);
      ucPvonReDHL = ucGetAvgPress4FD(ulTelID);
      ucReCounter4FDHL=ucGetAvgCntr4FD( ulTelID);

      if((ucPvonReDHL != 0xFF)  && (ucPvonReDHL!= 0x00) && (ucReCounter4FDHL !=0xFF )){
         if(ucReCounter4FDHL >= 3 ){
            PUTucRErecCounter4FDHL(ucReCounter4FDHL);
            PUTucIdCalPressure(ucPvonReDHL,ucGetColOfID(&ulTelID));
            PUTuiStoragePaverege4CompareValue(ucPvonReDHL,ucGetColOfID(&ulTelID));
            PUTscIdCalTemperatur((ucGetLastReceivedTemp(ulTelID)- ucPalTempNormFACTOR4Calc),ucGetColOfID(&ulTelID));

          }
      }

      ulTelID =   ulGetID(ucColOfIdHR);
      ucPvonReDHR = ucGetAvgPress4FD(ulTelID);
      ucReCounter4FDHR=ucGetAvgCntr4FD( ulTelID);

      if((ucPvonReDHR != 0xFF)  && (ucPvonReDHR != 0x00 ) && (ucReCounter4FDHR !=0xFF )){
         if(ucReCounter4FDHR >= 3 ){
            PUTucRErecCounter4FDHR(ucReCounter4FDHR);
            PUTucIdCalPressure(ucPvonReDHR,ucGetColOfID(&ulTelID));
            PUTuiStoragePaverege4CompareValue(ucPvonReDHR,ucGetColOfID(&ulTelID));
            PUTscIdCalTemperatur((ucGetLastReceivedTemp(ulTelID)- ucPalTempNormFACTOR4Calc),ucGetColOfID(&ulTelID));

          }
      }
   }
   return ucRtn;
}

uint8 FD_LoadIdValues4MFD(void){

   uint8 i;
   uint8 ucColOfIdVL,ucColOfIdVR,ucColOfIdHL, ucColOfIdHR;
   uint32 ulTelID;
   uint8 ucRtn=TRUE;
   uint8 ucReCounter4FDVL,ucReCounter4FDVR,ucReCounter4FDHL,ucReCounter4FDHR;
   uint8 ucPvonReDVL,ucPvonReDVR,ucPvonReDHL,ucPvonReDHR;

   for( i = 0; i < cAnzRad; i++ ){
      switch (GETucWPorPWPofHistCol(i)){
         case cRadPosVL:
                  ucColOfIdVL=i;
         break;
         case cRadPosVR:
                  ucColOfIdVR=i;
         break;
         case cRadPosHL:
                  ucColOfIdHL=i;
         break;
         case cRadPosHR:
                  ucColOfIdHR=i;
         break;
         default:
         {
            ucRtn = FALSE;
         }
      }
   }

   if(ucRtn == TRUE){

      ulTelID =   ulGetID(ucColOfIdVL);
      ucReCounter4FDVL=ucGetAvgCntr4FD( ulTelID);
      ucPvonReDVL = ucGetAvgPress4FD(ulTelID);
      if((ucPvonReDVL != 0xFF)  && (ucPvonReDVL!= 0x00) && (ucReCounter4FDVL !=0xFF )){
         if(ucReCounter4FDVL >= 3){
            PUTucRErecCounter4FDVL(ucReCounter4FDVL);
            PUTucIdCalPressure(ucPvonReDVL,ucGetColOfID(&ulTelID));
            PUTuiStoragePaverege4CompareValue(ucPvonReDVL,ucGetColOfID(&ulTelID));
            PUTscIdCalTemperatur((ucGetLastReceivedTemp(ulTelID)- ucPalTempNormFACTOR4Calc),ucGetColOfID(&ulTelID));

       }
      }
      ulTelID =   ulGetID(ucColOfIdVR);
      ucReCounter4FDVR=ucGetAvgCntr4FD( ulTelID);
      ucPvonReDVR = ucGetAvgPress4FD(ulTelID);
      if((ucPvonReDVR != 0xFF)  && (ucPvonReDVR!= 0x00) && (ucReCounter4FDVR !=0xFF )){
         if(ucReCounter4FDVR >= 3){
            PUTucRErecCounter4FDVR(ucReCounter4FDVR);
            PUTucIdCalPressure(ucPvonReDVR,ucGetColOfID(&ulTelID));
            PUTuiStoragePaverege4CompareValue(ucPvonReDVR,ucGetColOfID(&ulTelID));
            PUTscIdCalTemperatur((ucGetLastReceivedTemp(ulTelID)- ucPalTempNormFACTOR4Calc),ucGetColOfID(&ulTelID));

       }
      }
      ulTelID =   ulGetID(ucColOfIdHL);
      ucPvonReDHL = ucGetAvgPress4FD(ulTelID);
      ucReCounter4FDHL=ucGetAvgCntr4FD( ulTelID);

      if((ucPvonReDHL != 0xFF)  && (ucPvonReDHL!= 0x00) && (ucReCounter4FDHL !=0xFF )){
         if(ucReCounter4FDHL >= 3 ){
            PUTucRErecCounter4FDHL(ucReCounter4FDHL);
            PUTucIdCalPressure(ucPvonReDHL,ucGetColOfID(&ulTelID));
            PUTuiStoragePaverege4CompareValue(ucPvonReDHL,ucGetColOfID(&ulTelID));
            PUTscIdCalTemperatur((ucGetLastReceivedTemp(ulTelID)- ucPalTempNormFACTOR4Calc),ucGetColOfID(&ulTelID));

       }
      }
      ulTelID =   ulGetID(ucColOfIdHR);
      ucPvonReDHR = ucGetAvgPress4FD(ulTelID);
      ucReCounter4FDHR=ucGetAvgCntr4FD( ulTelID);

      if((ucPvonReDHR != 0xFF)  && (ucPvonReDHR != 0x00 ) && (ucReCounter4FDHR !=0xFF )){
         if(ucReCounter4FDHR >= 3 ){
            PUTucRErecCounter4FDHR(ucReCounter4FDHR);
            PUTucIdCalPressure(ucPvonReDHR,ucGetColOfID(&ulTelID));
            PUTuiStoragePaverege4CompareValue(ucPvonReDHR,ucGetColOfID(&ulTelID));
            PUTscIdCalTemperatur((ucGetLastReceivedTemp(ulTelID)- ucPalTempNormFACTOR4Calc),ucGetColOfID(&ulTelID));

       }
   }
   }
   return ucRtn;
}

uint8 FD_TimeoutHandle4AFD(void){

   uint8 i;
   uint8 ucColOfIdVL,ucColOfIdVR,ucColOfIdHL, ucColOfIdHR;
   uint32 ulTelID;
   uint8 ucRtn=TRUE;
   uint8 ucTmpPiso4Cal;
   uint8 ucReCounter4FDVL,ucReCounter4FDVR,ucReCounter4FDHL,ucReCounter4FDHR;
   sint8 scTvonReDVL,scTvonReDVR,scTvonReDHL,scTvonReDHR;
   uint8 ucPvonReDVL,ucPvonReDVR,ucPvonReDHL,ucPvonReDHR;

   for( i = 0; i < cAnzRad; i++ ){
      switch (GETucWPorPWPofHistCol(i)){
         case cRadPosVL:
                  ucColOfIdVL=i;
         break;
         case cRadPosVR:
                  ucColOfIdVR=i;
         break;
         case cRadPosHL:
                  ucColOfIdHL=i;
         break;
         case cRadPosHR:
                  ucColOfIdHR=i;
         break;
         default:
         {
            ucRtn = FALSE;
         }
      }
   }

   if(ucRtn == TRUE){
      PUTucCnt4DP_FILL_IFL(0);
      PUTucCnt4DP_FILL_DFL(0);
      PUTucLockByt4DFL_LTS(0);

      ulTelID =   ulGetID(ucColOfIdVL);
      ucReCounter4FDVL=ucGetAvgCntr4FD( ulTelID);
      ucPvonReDVL = ucGetAvgPress4FD(ulTelID);
      if((ucPvonReDVL != 0xFF)  && (ucPvonReDVL!= 0x00) && (ucReCounter4FDVL !=0xFF )){
         if(ucReCounter4FDVL >= 3){
            PUTucRErecCounter4FDVL(ucReCounter4FDVL);
            PUTucIdCalPressure(ucPvonReDVL,ucGetColOfID(&ulTelID));
            PUTuiStoragePaverege4CompareValue(ucPvonReDVL,ucGetColOfID(&ulTelID));
            PUTscIdCalTemperatur((ucGetLastReceivedTemp(ulTelID)- ucPalTempNormFACTOR4Calc),ucGetColOfID(&ulTelID));

            scTvonReDVL=GETscIdCalTemperatur(ucColOfIdVL);
            ucPvonReDVL=ucGetLastReceivedPress(ulTelID);
            if(FD_CheckP4AFDstartReason2_3FA(ucPvonReDVL,0xFF,scTvonReDVL,ucColOfIdVL) == FALSE){
               ucRtn = FALSE;
            }
            else{

               if(ucReCounter4FDVL >= 3){
                  ucTmpPiso4Cal= GetP4NewTempAtCAL(((uint8) GETuiStoragePaverege4CompareValue(ucColOfIdVL)),scTvonReDVL, GETscTref());
                  if(ucTmpPiso4Cal >  GETucPosComparePressure(cRadPosVL)){
                     if((ucTmpPiso4Cal - GETucPosComparePressure(cRadPosVL)) >= cDP_FILL){
                        if(GETucCnt4DP_FILL_IFLloggedFL() == FALSE){
                           INCucCnt4DP_FILL_IFL();
                           PUTucCnt4DP_FILL_IFLloggedFL();
                        }
                      }
                  }
                  else{
                     if((GETucPosComparePressure(cRadPosVL) - ucTmpPiso4Cal) >= cDP_FILL){
                        if(GETucCnt4DP_FILL_DFLloggedFL() == FALSE){
                           INCucCnt4DP_FILL_DFL();
                           PUTucCnt4DP_FILL_DFLloggedFL();
                        }
                     }
                  }
               }
            }
         }
      }

      ulTelID =   ulGetID(ucColOfIdVR);
      ucReCounter4FDVR=ucGetAvgCntr4FD( ulTelID);
      ucPvonReDVR = ucGetAvgPress4FD(ulTelID);
      if((ucPvonReDVR != 0xFF)  && (ucPvonReDVR!= 0x00) && (ucReCounter4FDVR !=0xFF )){
         if(ucReCounter4FDVR >= 3){
            PUTucRErecCounter4FDVR(ucReCounter4FDVR);
            PUTucIdCalPressure(ucPvonReDVR,ucGetColOfID(&ulTelID));
            PUTuiStoragePaverege4CompareValue(ucPvonReDVR,ucGetColOfID(&ulTelID));
            PUTscIdCalTemperatur((ucGetLastReceivedTemp(ulTelID)- ucPalTempNormFACTOR4Calc),ucGetColOfID(&ulTelID));

            scTvonReDVR=GETscIdCalTemperatur(ucColOfIdVR);
            ucPvonReDVR=ucGetLastReceivedPress(ulTelID);
            if(FD_CheckP4AFDstartReason2_3FA(ucPvonReDVR,0xFF,scTvonReDVR,ucColOfIdVR) == FALSE){
               ucRtn = FALSE;
            }
            else{

               if(ucReCounter4FDVR >= 3){
                  ucTmpPiso4Cal= GetP4NewTempAtCAL(((uint8) GETuiStoragePaverege4CompareValue(ucColOfIdVR)),scTvonReDVR, GETscTref());
                  if(ucTmpPiso4Cal >  GETucPosComparePressure(cRadPosVR)){
                     if((ucTmpPiso4Cal - GETucPosComparePressure(cRadPosVR)) >= cDP_FILL){
                        if(GETucCnt4DP_FILL_IFLloggedFR() == FALSE){
                           INCucCnt4DP_FILL_IFL();
                           PUTucCnt4DP_FILL_IFLloggedFR();
                        }
                      }
                  }
                  else{
                     if((GETucPosComparePressure(cRadPosVR) - ucTmpPiso4Cal) >= cDP_FILL){
                        INCucCnt4DP_FILL_DFL();
                     }
                  }
               }
            }
         }
      }

      ulTelID =   ulGetID(ucColOfIdHL);
      ucPvonReDHL = ucGetAvgPress4FD(ulTelID);
      ucReCounter4FDHL=ucGetAvgCntr4FD( ulTelID);

      if((ucPvonReDHL != 0xFF)  && (ucPvonReDHL!= 0x00) && (ucReCounter4FDHL !=0xFF )){
         if(ucReCounter4FDHL >= 3 ){
            PUTucRErecCounter4FDHL(ucReCounter4FDHL);
            PUTucIdCalPressure(ucPvonReDHL,ucGetColOfID(&ulTelID));
            PUTuiStoragePaverege4CompareValue(ucPvonReDHL,ucGetColOfID(&ulTelID));
            PUTscIdCalTemperatur((ucGetLastReceivedTemp(ulTelID)- ucPalTempNormFACTOR4Calc),ucGetColOfID(&ulTelID));

            scTvonReDHL=GETscIdCalTemperatur(ucColOfIdHL);
            ucPvonReDHL=ucGetLastReceivedPress(ulTelID);
            if(FD_CheckP4AFDstartReason2_3RA(ucPvonReDHL,0xFF,scTvonReDHL,ucColOfIdHL) == FALSE){
               ucRtn = FALSE;
            }
            else{

               if(ucReCounter4FDHL >= 3){
                  ucTmpPiso4Cal= GetP4NewTempAtCAL(((uint8) GETuiStoragePaverege4CompareValue(ucColOfIdHL)),scTvonReDHL, GETscTref());
                  if(ucTmpPiso4Cal >  GETucPosComparePressure(cRadPosHL)){
                     if((ucTmpPiso4Cal - GETucPosComparePressure(cRadPosHL)) >= cDP_FILL){
                        if(GETucCnt4DP_FILL_IFLloggedRL() == FALSE){
                           INCucCnt4DP_FILL_IFL();
                           PUTucCnt4DP_FILL_IFLloggedRL();
                        }
                      }
                  }
                  else{
                     if((GETucPosComparePressure(cRadPosHL) - ucTmpPiso4Cal) >= cDP_FILL){
                        if(GETucCnt4DP_FILL_DFLloggedRL() == FALSE){
                           INCucCnt4DP_FILL_DFL();
                           PUTucCnt4DP_FILL_DFLloggedRL();
                        }
                     }
                  }
               }
            }
         }
      }

      ulTelID =   ulGetID(ucColOfIdHR);
      ucPvonReDHR = ucGetAvgPress4FD(ulTelID);
      ucReCounter4FDHR=ucGetAvgCntr4FD( ulTelID);

      if((ucPvonReDHR != 0xFF)  && (ucPvonReDHR != 0x00 ) && (ucReCounter4FDHR !=0xFF )){
         if(ucReCounter4FDHR >= 3 ){
            PUTucRErecCounter4FDHR(ucReCounter4FDHR);
            PUTucIdCalPressure(ucPvonReDHR,ucGetColOfID(&ulTelID));
            PUTuiStoragePaverege4CompareValue(ucPvonReDHR,ucGetColOfID(&ulTelID));
            PUTscIdCalTemperatur((ucGetLastReceivedTemp(ulTelID)- ucPalTempNormFACTOR4Calc),ucGetColOfID(&ulTelID));

            scTvonReDHR=GETscIdCalTemperatur(ucColOfIdHR);
            ucPvonReDHR=ucGetLastReceivedPress(ulTelID);

            if(FD_CheckP4AFDstartReason2_3RA(ucPvonReDHR,0xFF,scTvonReDHR,ucColOfIdHR) == FALSE){
               ucRtn = FALSE;
            }
            else{

               if(ucReCounter4FDHR >= 3){
                  ucTmpPiso4Cal= GetP4NewTempAtCAL(((uint8) GETuiStoragePaverege4CompareValue(ucColOfIdHR)),scTvonReDHR, GETscTref());
                  if(ucTmpPiso4Cal >  GETucPosComparePressure(cRadPosHR)){
                     if((ucTmpPiso4Cal - GETucPosComparePressure(cRadPosHR)) >= cDP_FILL){
                        if(GETucCnt4DP_FILL_IFLloggedRR() == FALSE){
                           INCucCnt4DP_FILL_IFL();
                           PUTucCnt4DP_FILL_IFLloggedRR();
                        }
                      }
                  }
                  else{
                     if((GETucPosComparePressure(cRadPosHR) - ucTmpPiso4Cal) >= cDP_FILL){
                        if(GETucCnt4DP_FILL_DFLloggedRR() == FALSE){
                           INCucCnt4DP_FILL_DFL();
                           PUTucCnt4DP_FILL_DFLloggedRR();
                        }
                     }
                  }
               }
            }
         }
      }
   }
   return ucRtn;
}

uint8 FD_LoadIdValues4UpdateCompareValue(void){

   uint8 i;
   uint8 ucColOfIdVL,ucColOfIdVR,ucColOfIdHL, ucColOfIdHR;
   uint32 ulTelID;
   uint8 ucRtn=TRUE;
   sint8 scTvonReDxx;
   uint8 ucPvonReDxx;
   uint8 ucPmin=FALSE;

      for( i = 0; i < cAnzRad; i++ ){
         switch (GETucWPorPWPofHistCol(i)){
            case cRadPosVL:
                     ucColOfIdVL=i;
            break;
            case cRadPosVR:
                     ucColOfIdVR=i;
            break;
            case cRadPosHL:
                     ucColOfIdHL=i;
            break;
            case cRadPosHR:
                     ucColOfIdHR=i;
            break;
            case cRadPosUkw:
                     ucRtn = cRadPosUkw;;
            break;
            default:
            {
               ucRtn = FALSE;
            }
         }
      }
      if(ucRtn == TRUE){

         if((GetNewIdColX4FD( ucColOfIdVL ) == TRUE) || (bGetBitBetriebszustandBZ(cCAL_REQUEST) == TRUE)  || ( ucRePosStorageVL4FD == 0xFF)){
            ulTelID =   ulGetID(ucColOfIdVL);
             ucPvonReDxx=ucGetLastReceivedPress(ulTelID);

            if((ucPvonReDxx != 0xFF)  && (ucPvonReDxx != 0x00)){
               scTvonReDxx=(signed) (ucGetLastReceivedTemp(ulTelID) - ucPalTempNormFACTOR4Calc);
               PUTucPosComparePressure(GetP4NewTempAtCAL(ucPvonReDxx,scTvonReDxx,GETscTref()),cRadPosVL);
               ClearNewIdColXMem4FD(ucColOfIdVL);
               if(ucPvonReDxx < GETucMinWarnThresholdOfRam()){
                  ucPmin|=cFD_Pmin_FL;
               }
            }
            else{
               ucRtn = FALSE;
            }
         }

         if((GetNewIdColX4FD( ucColOfIdVR ) == TRUE) || (bGetBitBetriebszustandBZ(cCAL_REQUEST) == TRUE) || ( ucRePosStorageVR4FD == 0xFF)){
            ulTelID =   ulGetID(ucColOfIdVR);
             ucPvonReDxx=ucGetLastReceivedPress(ulTelID);

            if((ucPvonReDxx != 0xFF)  && (ucPvonReDxx != 0x00)){
               scTvonReDxx=(signed) (ucGetLastReceivedTemp(ulTelID) - ucPalTempNormFACTOR4Calc);
               PUTucPosComparePressure(GetP4NewTempAtCAL(ucPvonReDxx,scTvonReDxx,GETscTref()),cRadPosVR);
               ClearNewIdColXMem4FD(ucColOfIdVR);
               if(ucPvonReDxx < GETucMinWarnThresholdOfRam()){
                  ucPmin|=cFD_Pmin_FR;
               }
            }
            else{
               ucRtn = FALSE;
            }
         }

         if((GetNewIdColX4FD( ucColOfIdHL ) == TRUE) || (bGetBitBetriebszustandBZ(cCAL_REQUEST) == TRUE) || ( ucRePosStorageHL4FD == 0xFF)){
            ulTelID =   ulGetID(ucColOfIdHL);
             ucPvonReDxx=ucGetLastReceivedPress(ulTelID);
            if((ucPvonReDxx != 0xFF)  && (ucPvonReDxx != 0x00)){
               scTvonReDxx=(signed) (ucGetLastReceivedTemp(ulTelID) - ucPalTempNormFACTOR4Calc);
               PUTucPosComparePressure(GetP4NewTempAtCAL(ucPvonReDxx,scTvonReDxx,GETscTref()),cRadPosHL);
               ClearNewIdColXMem4FD(ucColOfIdHL);
               if(ucPvonReDxx < GETucMinWarnThresholdOfRam()){
                  ucPmin|=cFD_Pmin_RL;
               }
            }
            else{
               ucRtn = FALSE;
            }
         }

         if((GetNewIdColX4FD( ucColOfIdHR ) == TRUE) || (bGetBitBetriebszustandBZ(cCAL_REQUEST) == TRUE) || ( ucRePosStorageHR4FD == 0xFF)){
            ulTelID =   ulGetID(ucColOfIdHR);
             ucPvonReDxx=ucGetLastReceivedPress(ulTelID);
            if((ucPvonReDxx != 0xFF)  && (ucPvonReDxx != 0x00)){
               scTvonReDxx=(signed) (ucGetLastReceivedTemp(ulTelID) - ucPalTempNormFACTOR4Calc);
               PUTucPosComparePressure(GetP4NewTempAtCAL(ucPvonReDxx,scTvonReDxx,GETscTref()),cRadPosHR);
               ClearNewIdColXMem4FD(ucColOfIdHR);
               if(ucPvonReDxx < GETucMinWarnThresholdOfRam()){
                  ucPmin|=cFD_Pmin_RR;
               }
            }
            else{
               ucRtn = FALSE;
            }
         }
#ifdef as_CmpValue4NewIDonly
         if((ChkNewIdColX4FD() == TRUE) || (bGetBitBetriebszustandBZ(cCAL_REQUEST) == TRUE)){

            ulTelID =   ulGetID(ucColOfIdVL);
             ucPvonReDxx=ucGetLastReceivedPress(ulTelID);

            if((ucPvonReDxx != 0xFF)  && (ucPvonReDxx != 0x00)){
               scTvonReDxx=(signed) (ucGetLastReceivedTemp(ulTelID) - ucPalTempNormFACTOR4Calc);
               PUTucPosComparePressure(GetP4NewTempAtCAL(ucPvonReDxx,scTvonReDxx,GETscTref()),cRadPosVL);
               ClearNewIdColXMem4FD(ucColOfIdVL);
               if(ucPvonReDxx < GETucMinWarnThresholdOfRam()){
                  ucPmin|=cFD_Pmin_FL;
               }
            }
            else{
               ucRtn = FALSE;
            }

            ulTelID =   ulGetID(ucColOfIdVR);
             ucPvonReDxx=ucGetLastReceivedPress(ulTelID);

            if((ucPvonReDxx != 0xFF)  && (ucPvonReDxx != 0x00)){
               scTvonReDxx=(signed) (ucGetLastReceivedTemp(ulTelID) - ucPalTempNormFACTOR4Calc);
               PUTucPosComparePressure(GetP4NewTempAtCAL(ucPvonReDxx,scTvonReDxx,GETscTref()),cRadPosVR);
               ClearNewIdColXMem4FD(ucColOfIdVR);
               if(ucPvonReDxx < GETucMinWarnThresholdOfRam()){
                  ucPmin|=cFD_Pmin_FR;
               }
            }
            else{
               ucRtn = FALSE;
            }

            ulTelID =   ulGetID(ucColOfIdHL);
             ucPvonReDxx=ucGetLastReceivedPress(ulTelID);
            if((ucPvonReDxx != 0xFF)  && (ucPvonReDxx != 0x00)){
               scTvonReDxx=(signed) (ucGetLastReceivedTemp(ulTelID) - ucPalTempNormFACTOR4Calc);
               PUTucPosComparePressure(GetP4NewTempAtCAL(ucPvonReDxx,scTvonReDxx,GETscTref()),cRadPosHL);
               ClearNewIdColXMem4FD(ucColOfIdHL);
               if(ucPvonReDxx < GETucMinWarnThresholdOfRam()){
                  ucPmin|=cFD_Pmin_RL;
               }
            }
            else{
               ucRtn = FALSE;
            }

            ulTelID =   ulGetID(ucColOfIdHR);
             ucPvonReDxx=ucGetLastReceivedPress(ulTelID);
            if((ucPvonReDxx != 0xFF)  && (ucPvonReDxx != 0x00)){
               scTvonReDxx=(signed) (ucGetLastReceivedTemp(ulTelID) - ucPalTempNormFACTOR4Calc);
               PUTucPosComparePressure(GetP4NewTempAtCAL(ucPvonReDxx,scTvonReDxx,GETscTref()),cRadPosHR);
               ClearNewIdColXMem4FD(ucColOfIdHR);
               if(ucPvonReDxx < GETucMinWarnThresholdOfRam()){
                  ucPmin|=cFD_Pmin_RR;
               }
            }
            else{
               ucRtn = FALSE;
            }
         }
#endif

         if(ucPmin != FALSE){
            if(GETucCalNotAckStateOfRam() != cCAL_P_MIN_TIRE_NAK){
               SetState2AbortReasonFD(cFD_P_MIN_TIRE);
               ClearKplNoCheckPmin4StopFD();
               SetState2FillingDetectionStateFD(cFILLING_DETECT_ABORTED);
               SetBitCalNotAckState2Ram(cCAL_P_MIN_TIRE_NAK);
            }
         }
         else{
            if((ucRtn == TRUE) && ((GETucCalNotAckStateOfRam() & 0xBF) == FALSE )){
               ClearFillingDetectionStateFD();
               ClearAbortReasonFD();
               ClearAllReCnt4FD();
               if((bGETucCalRequestState(cCAL_AUTO_ENABLE2) == TRUE ) || (bGETucCalRequestState(cCAL_AUTO_ENABLE3) == TRUE )){
                  SetBitFillingDetectionStateFD(cFILLING_NOT_DETECTED);
                  ClearBitCalRequestState(cCAL_AUTO_ENABLE3 | cCAL_AUTO_ENABLE2);
               }
            }
         }
      }
   return ucRtn;
}

uint8 FD_Plausibility_CheckP4DPLR_DPABS(uint8 ucZOMPosVL,uint8 ucZOMPosVR,uint8 ucZOMPosHL,uint8 ucZOMPosHR){

#ifdef as_DP_APS
   uint8   ucP_Low, ucP_High;
#endif
   uint16 uiDP_REL;
   uint8 ucRtn=TRUE;

  if(GETucIdCalPressure(ucZOMPosVL) > GETucIdCalPressure(ucZOMPosVR)){
      uiDP_REL=(GETucIdCalPressure(ucZOMPosVL) * cDP_LR);
      if(uiDP_REL > (GETucIdCalPressure(ucZOMPosVR) *100)){
         ucRtn=FALSE;
         SetBitCalNotAckState2Ram(cCAL_DP_LR_FA_NAK);
         SetState2PlausiFailureFD(cFD_LEFT_RIGHT_DIFFERENCE);
      }
   }
   else{
      uiDP_REL=(GETucIdCalPressure(ucZOMPosVR) * cDP_LR);
      if(uiDP_REL > (GETucIdCalPressure(ucZOMPosVL) *100)){
         ucRtn=FALSE;
         SetBitCalNotAckState2Ram(cCAL_DP_LR_FA_NAK);
         SetState2PlausiFailureFD(cFD_LEFT_RIGHT_DIFFERENCE);
      }
   }
   if(GETucIdCalPressure(ucZOMPosHL) > GETucIdCalPressure(ucZOMPosHR)){
      uiDP_REL=(GETucIdCalPressure(ucZOMPosHL) * cDP_LR);
      if(uiDP_REL > (GETucIdCalPressure(ucZOMPosHR) *100)){
            ucRtn=FALSE;
            SetBitCalNotAckState2Ram(cCAL_DP_LR_RA_NAK);
            SetState2PlausiFailureFD(cFD_LEFT_RIGHT_DIFFERENCE);
      }
   }
   else{
      uiDP_REL=(GETucIdCalPressure(ucZOMPosHR) * cDP_LR);
      if(uiDP_REL > (GETucIdCalPressure(ucZOMPosHL)  *100)){
         ucRtn=FALSE;
         SetBitCalNotAckState2Ram(cCAL_DP_LR_RA_NAK);
         SetState2PlausiFailureFD(cFD_LEFT_RIGHT_DIFFERENCE);
      }
   }

   if(ucRtn == TRUE){
#ifdef as_DP_APS

      if(GETucIdCalPressure(ucZOMPosVL) > GETucIdCalPressure(ucZOMPosVR)){
         ucP_High= GETucIdCalPressure(ucZOMPosVL);
         ucP_Low = GETucIdCalPressure(ucZOMPosVR);

         if(ucP_High > GETucIdCalPressure(ucZOMPosHL)){
            if(ucP_High < GETucIdCalPressure(ucZOMPosHR)){
               ucP_High= GETucIdCalPressure(ucZOMPosHR);
            }
         }
         else{
            ucP_High= GETucIdCalPressure(ucZOMPosHL);
            if(ucP_High < GETucIdCalPressure(ucZOMPosHR)){
               ucP_High= GETucIdCalPressure(ucZOMPosHR);
            }
          }

         if(ucP_Low < GETucIdCalPressure(ucZOMPosHL)){
            if(ucP_Low > GETucIdCalPressure(ucZOMPosHR)){
               ucP_Low = GETucIdCalPressure(ucZOMPosHR);
            }
         }
         else{
            ucP_Low = GETucIdCalPressure(ucZOMPosHL);
            if(ucP_Low > GETucIdCalPressure(ucZOMPosHR)){
               ucP_Low = GETucIdCalPressure(ucZOMPosHR);
            }
         }
      }
      else{

         ucP_Low = GETucIdCalPressure(ucZOMPosVL);
         ucP_High= GETucIdCalPressure(ucZOMPosVR);
         if(ucP_High > GETucIdCalPressure(ucZOMPosHL)){
            if(ucP_High < GETucIdCalPressure(ucZOMPosHR)){
               ucP_High= GETucIdCalPressure(ucZOMPosHR);
            }
         }
         else{
            ucP_High= GETucIdCalPressure(ucZOMPosHL);
            if(ucP_High < GETucIdCalPressure(ucZOMPosHR)){
               ucP_High= GETucIdCalPressure(ucZOMPosHR);
            }
          }

         if(ucP_Low < GETucIdCalPressure(ucZOMPosHL)){
            if(ucP_Low > GETucIdCalPressure(ucZOMPosHR)){
               ucP_Low = GETucIdCalPressure(ucZOMPosHR);
            }
         }
         else{
            ucP_Low = GETucIdCalPressure(ucZOMPosHL);
            if(ucP_Low > GETucIdCalPressure(ucZOMPosHR)){
               ucP_Low = GETucIdCalPressure(ucZOMPosHR);
            }
         }
      }

      if((ucP_High - ucP_Low) > cDP_Abs){
         ucRtn=FALSE;
         SetBitCalNotAckState2Ram(cCAL_DP_ABS_NAK);
         SetState2PlausiFailureFD(cFD_ABSOLUTE_PRESSURE_DIFF);
      }
      else{
         ClearBitBetriebszustandBZ(cCAL_AFD_PLAUSI_ERROR | cCAL_MFD_PLAUSI_ERROR);
         ClearPlausiFailureLeftRightAbsFD();
      }
#else
      ClearBitBetriebszustandBZ(cCAL_AFD_PLAUSI_ERROR | cCAL_MFD_PLAUSI_ERROR);
      ClearPlausiFailureLeftRightAbsFD();
#endif
   }

return ucRtn;

}

void FD_CheckResetCondition4ImplausiMsg(uint8 ucZOMPosVL,uint8 ucZOMPosVR,uint8 ucZOMPosHL,uint8 ucZOMPosHR){
#ifdef as_DP_APS
   uint8   ucP_Low, ucP_High;
#endif
   uint16 uiDP_REL;
   uint8 ucRtn=TRUE;

  if(GETucIdCalPressure(ucZOMPosVL) > GETucIdCalPressure(ucZOMPosVR)){
      uiDP_REL=(GETucIdCalPressure(ucZOMPosVL) * cDP_LR);
      if(uiDP_REL > (GETucIdCalPressure(ucZOMPosVR) *100)){
         ucRtn=FALSE;
      }
   }
   else{
      uiDP_REL=(GETucIdCalPressure(ucZOMPosVR) * cDP_LR);
      if(uiDP_REL > (GETucIdCalPressure(ucZOMPosVL) *100)){
         ucRtn=FALSE;
      }
   }
   if(GETucIdCalPressure(ucZOMPosHL) > GETucIdCalPressure(ucZOMPosHR)){
      uiDP_REL=(GETucIdCalPressure(ucZOMPosHL) * cDP_LR);
      if(uiDP_REL > (GETucIdCalPressure(ucZOMPosHR) *100)){
            ucRtn=FALSE;
      }
   }
   else{
      uiDP_REL=(GETucIdCalPressure(ucZOMPosHR) * cDP_LR);
      if(uiDP_REL > (GETucIdCalPressure(ucZOMPosHL)  *100)){
         ucRtn=FALSE;
      }
   }

   if(ucRtn == TRUE){
#ifdef as_DP_APS

      if(GETucIdCalPressure(ucZOMPosVL) > GETucIdCalPressure(ucZOMPosVR)){
         ucP_High= GETucIdCalPressure(ucZOMPosVL);
         ucP_Low = GETucIdCalPressure(ucZOMPosVR);

         if(ucP_High > GETucIdCalPressure(ucZOMPosHL)){
            if(ucP_High < GETucIdCalPressure(ucZOMPosHR)){
               ucP_High= GETucIdCalPressure(ucZOMPosHR);
            }
         }
         else{
            ucP_High= GETucIdCalPressure(ucZOMPosHL);
            if(ucP_High < GETucIdCalPressure(ucZOMPosHR)){
               ucP_High= GETucIdCalPressure(ucZOMPosHR);
            }
          }

         if(ucP_Low < GETucIdCalPressure(ucZOMPosHL)){
            if(ucP_Low > GETucIdCalPressure(ucZOMPosHR)){
               ucP_Low = GETucIdCalPressure(ucZOMPosHR);
            }
         }
         else{
            ucP_Low = GETucIdCalPressure(ucZOMPosHL);
            if(ucP_Low > GETucIdCalPressure(ucZOMPosHR)){
               ucP_Low = GETucIdCalPressure(ucZOMPosHR);
            }
         }
      }
      else{

         ucP_Low = GETucIdCalPressure(ucZOMPosVL);
         ucP_High= GETucIdCalPressure(ucZOMPosVR);
         if(ucP_High > GETucIdCalPressure(ucZOMPosHL)){
            if(ucP_High < GETucIdCalPressure(ucZOMPosHR)){
               ucP_High= GETucIdCalPressure(ucZOMPosHR);
            }
         }
         else{
            ucP_High= GETucIdCalPressure(ucZOMPosHL);
            if(ucP_High < GETucIdCalPressure(ucZOMPosHR)){
               ucP_High= GETucIdCalPressure(ucZOMPosHR);
            }
          }

         if(ucP_Low < GETucIdCalPressure(ucZOMPosHL)){
            if(ucP_Low > GETucIdCalPressure(ucZOMPosHR)){
               ucP_Low = GETucIdCalPressure(ucZOMPosHR);
            }
         }
         else{
            ucP_Low = GETucIdCalPressure(ucZOMPosHL);
            if(ucP_Low > GETucIdCalPressure(ucZOMPosHR)){
               ucP_Low = GETucIdCalPressure(ucZOMPosHR);
            }
         }
      }

      if((ucP_High - ucP_Low) > cDP_Abs){
         ucRtn=FALSE;
      }
      else{
         ClearBitBetriebszustandBZ(cCAL_AFD_PLAUSI_ERROR);
         ClearBitBetriebszustandBZ(cCAL_MFD_PLAUSI_ERROR);
         ClearPlausiFailureLeftRightAbsFD();

      }
#else
      ClearBitBetriebszustandBZ(cCAL_AFD_PLAUSI_ERROR);
      ClearBitBetriebszustandBZ(cCAL_MFD_PLAUSI_ERROR);
      ClearPlausiFailureLeftRightAbsFD();
#endif
   }
}

uint8 GetPabs4NewTempAtCAL(uint8 ui8PCur, sint8 i8Tcur, sint8 i8Tnew){
    uint16 ui16M;
    uint8 ui8Pcomp;

    ui16M = ushMIso ((ui8PCur), i8Tcur );
    ui8Pcomp = ucPfT(ui16M,(uint16) i8Tnew + ush273Kelvinc);
    return (ui8Pcomp);
 }

uint8 GetP4NewTempAtCAL(uint8 ui8PCur, sint8 i8Tcur, sint8 i8Tnew){
    uint16 ui16M;
    uint8 ui8Pcomp;

      ui16M = ui16MIsoRel ((ui8PCur), i8Tcur );
    ui8Pcomp = ucPfT(ui16M,(uint16) i8Tnew + ush273Kelvinc);
    return (ui8Pcomp);
 }

void FD_AfdStopp4PWP(void){
   if( bGETucCalNotAckState(cCAL_FBM_ACTIV_NAK) == FALSE){
      if((bGETucCalRequestState(cCAL_AUTO_NEW_ID) == TRUE)){
         if((FD_LoadIdValues4UpdateCompareValue() == TRUE) || ((bGetBitBetriebszustandBZ(cZO_TIMEOUT) == TRUE ) && (bGetBitBetriebszustandBZ(cZO_ERROR) == TRUE))){
               ClearBitCalRequestState(cCAL_AUTO_NEW_ID);
               SetBitCalNotAckState2Ram(cCAL_FBM_ACTIV_NAK);
         }
      }
      else{
         if(FD_UpdateComparePressureAfterFBM() == TRUE){
            SetBitCalNotAckState2Ram(cCAL_FBM_ACTIV_NAK);
         }
      }

      ClearBitFahrzeugzustandFZZ(cKFZPARKING_START_AFD);
      ClearBitCalRequestState(cCAL_AUTO_ENABLE3 | cCAL_AUTO_ENABLE2 | cCAL_AUTO_ACTIV);
      ClearPlausiFailureFD();

      if(bGETucCalRequestState(cCAL_MANUAL_ACTIV) == FALSE){
         ClearBitBetriebszustandBZ(cCAL_REQUEST);
         PUTushFDtimeout(0);
         if(Get_FD_ABORT_REASON() == FALSE){
            SetState2FillingDetectionStateFD(cFILLING_DETECT_ABORTED);
            SetState2AbortReasonFD(cFD_FBM_ACTIV);
         }
      }
#ifdef as_357
       SetBitCalNotAckState2Ram(cCAL_FBM_ACTIV_NAK);
#endif
   }
   else{
    if((GetucTPM_WarnDisp_Rq() > 0) && (bGetBitBetriebszustandBZ(cCAL_MFD_PLAUSI_ERROR) || bGetBitBetriebszustandBZ(cCAL_AFD_PLAUSI_ERROR))){
         ClearBitBetriebszustandBZ(cCAL_AFD_PLAUSI_ERROR | cCAL_MFD_PLAUSI_ERROR);
      }
   }
}

uint8 FD_CheckCurrentPmin(void){
   uint8 ucRtn = FALSE;
   uint8 i;
   uint32 ulTelID;
   uint8 ucColOfIdVL,ucColOfIdVR,ucColOfIdHL,ucColOfIdHR;

   for( i = 0; i < cAnzRad; i++ ){
      switch (GETucWPorPWPofHistCol(i)){
         case cRadPosVL:
                  ucColOfIdVL=i;
         break;
         case cRadPosVR:
                  ucColOfIdVR=i;
         break;
         case cRadPosHL:
                  ucColOfIdHL=i;
         break;
         case cRadPosHR:
                   ucColOfIdHR=i;
         break;
         default:
         {
            ucRtn = TRUE;
         }
      }
   }

   if(ucRtn == FALSE){
      if(ucGetLastReceivedPress(ulGetID(ucColOfIdVL)) != 0xFF){
         if(ucGetLastReceivedPress(ulGetID(ucColOfIdVL))  < GETucMinWarnThresholdOfRam()){
            ucRtn =TRUE;
         }
      }
      if(ucGetLastReceivedPress(ulGetID(ucColOfIdVR)) != 0xFF){
         if(ucGetLastReceivedPress(ulGetID(ucColOfIdVR))  < GETucMinWarnThresholdOfRam()){
            ucRtn =TRUE;
         }
      }
      if(ucGetLastReceivedPress(ulGetID(ucColOfIdHL)) != 0xFF){
         if(ucGetLastReceivedPress(ulGetID(ucColOfIdHL))  < GETucMinWarnThresholdOfRam()){
            ucRtn =TRUE;
         }
      }
      if(ucGetLastReceivedPress(ulGetID(ucColOfIdHR)) != 0xFF){
         if(ucGetLastReceivedPress(ulGetID(ucColOfIdHR))  < GETucMinWarnThresholdOfRam()){
            ucRtn =TRUE;
         }
      }
   }
   else{

      if(bGetBitBetriebszustandBZ(cER_FINISH)){
         ucRtn = FALSE;

         ulTelID =   ulGetID(cRadPosVL);
         if(ucGetLastReceivedPress(ulTelID) != 0xFF){
            if(ucGetLastReceivedPress(ulTelID) < GETucMinWarnThresholdOfRam()){
               ucRtn =TRUE;
            }
         }
         ulTelID =   ulGetID(cRadPosVR);
         if(ucGetLastReceivedPress(ulTelID) != 0xFF){
            if(ucGetLastReceivedPress(ulTelID) < GETucMinWarnThresholdOfRam()){
               ucRtn =TRUE;
            }
         }
         ulTelID =   ulGetID(cRadPosHL);
         if(ucGetLastReceivedPress(ulTelID) != 0xFF){
            if(ucGetLastReceivedPress(ulTelID) < GETucMinWarnThresholdOfRam()){
               ucRtn =TRUE;
            }
         }
         ulTelID =   ulGetID(cRadPosHR);
         if(ucGetLastReceivedPress(ulTelID) != 0xFF){
            if(ucGetLastReceivedPress(ulTelID) < GETucMinWarnThresholdOfRam()){
               ucRtn =TRUE;
            }
         }
      }
      else{
         ucRtn =FALSE;
      }
   }
   return ucRtn;
}

uint8 FD_FlowChartFct1(void){
   uint8 ucRtn=TRUE;
   uint8 i;

   if(FD_CheckCurrentPmin() == TRUE){

      PUTucOnceCheckMissingRE4FD(TRUE);
      PUTushFDtimeout(0);
      PUTucFDtimerStop(TRUE);
      FD_AbortFillingDetection(cCAL_P_MIN_TIRE_NAK);
      ucRtn=FALSE;

   }
   else{
      if(((GETucOnceCheckMissingRE4FD() == FALSE) && ((ucGetFzzCurrentLearnMode() == cNoLearn) && (bGetBitBetriebszustandBZ(cZO_TIMEOUT) == TRUE))) ||
         ((GETucOnceCheckMissingRE4FD() == FALSE) && (ucGetFzzCurrentLearnMode() != cNoLearn) && (GETushFDtimeout() == 0))){
         for(i = 0; i < cMaxLR; i++){
            if(ucGetSensorState(i) == SENSOR_STATE_MISSING){
               ucRtn=FALSE;
            }
         }
         if(ucRtn==FALSE){
            PUTucOnceCheckMissingRE4FD(TRUE);
            PUTushFDtimeout(0);
            PUTucFDtimerStop(TRUE);
            FD_AbortFillingDetection(cCAL_RE_MISSING_NAK);
         }
      }
      else{
         if(GETucOnceCheckMissingRE4FD() == TRUE){
            ucRtn=FALSE;
         }
      }
   }

   return ucRtn;
}

uint8 FD_FlowChartFct1CheckPmin(void){
   uint8 ucRtn=TRUE;

   if(FD_CheckCurrentPmin() == TRUE){

      PUTucOnceCheckMissingRE4FD(TRUE);
      PUTushFDtimeout(0);
      PUTucFDtimerStop(TRUE);
      FD_AbortFillingDetection(cCAL_P_MIN_TIRE_NAK);
      ucRtn=FALSE;
   }

   return ucRtn;
}

uint8 FD_FlowChartFct1CheckMissingRE(void){
   uint8 ucRtn=TRUE;
   uint8 i;

   if(((GETucOnceCheckMissingRE4FD() == FALSE) && ((ucGetFzzCurrentLearnMode() == cNoLearn) && (bGetBitBetriebszustandBZ(cZO_TIMEOUT) == TRUE))) ||
      ((GETucOnceCheckMissingRE4FD() == FALSE) && (ucGetFzzCurrentLearnMode() != cNoLearn) && (GETushFDtimeout() == 0))){
      for(i = 0; i < cMaxLR; i++){
         if(ucGetSensorState(i) == SENSOR_STATE_MISSING){
            ucRtn=FALSE;
         }
      }
      if(ucRtn==FALSE){
         PUTucOnceCheckMissingRE4FD(TRUE);
         PUTushFDtimeout(0);
         PUTucFDtimerStop(TRUE);
         FD_AbortFillingDetection(cCAL_RE_MISSING_NAK);
      }
   }
   else{
      if(GETucOnceCheckMissingRE4FD() == TRUE){
         ucRtn=FALSE;
      }
   }
   return ucRtn;
}

uint8 FD_CheckFDpos2ZomPosAfterZOfinish(void){
   uint8 ucColOfIdVL,ucColOfIdVR,ucColOfIdHL, ucColOfIdHR;
   uint8 aucOldColOfID[4];
   uint8 aucP_OfID[4];
   sint8 ascT_OfID[4];
   uint8 aucPaverege_OfID[4];
   sint8 scTfillVA, scTfillHA, scTfill_Tref;
   uint8 ucReVa2Ha_Ha2VA=FALSE;
   uint8 i;
   uint8 ucRtn=TRUE;

   for( i = 0; i < cAnzRad; i++ ){
      switch (GETucWPorPWPofHistCol(i)){
         case cRadPosVL:
            ucColOfIdVL=i;
         break;
         case cRadPosVR:
            ucColOfIdVR=i;
         break;
         case cRadPosHL:

            ucColOfIdHL=i;
         break;
         case cRadPosHR:
           ucColOfIdHR=i;
         break;
         default:
         {
            ucRtn = FALSE;
         }
      }
   }
   if(ucRtn == TRUE){
        if((ucRePosStorageVL4FD + ucRePosStorageVR4FD + ucRePosStorageHL4FD +ucRePosStorageHR4FD) == (ucColOfIdVL + ucColOfIdVR + ucColOfIdHL + ucColOfIdHR)){

            if((ucRePosStorageVL4FD != ucColOfIdVL) || (ucRePosStorageVR4FD != ucColOfIdVR) || (ucRePosStorageHL4FD != ucColOfIdHL) || (ucRePosStorageHR4FD != ucColOfIdHR)){
               if((ucRePosStorageVL4FD != ucColOfIdVL) && (ucRePosStorageVR4FD != ucColOfIdVR) && (ucRePosStorageHL4FD != ucColOfIdHL) && (ucRePosStorageHR4FD != ucColOfIdHR)){
                  ucReVa2Ha_Ha2VA=TRUE;
               }
               ucRtn=cAFD_RUNNING2;

               aucOldColOfID[cRadPosVL]=ucRePosStorageVL4FD;
               aucOldColOfID[cRadPosVR]=ucRePosStorageVR4FD;
               aucOldColOfID[cRadPosHL]=ucRePosStorageHL4FD;
               aucOldColOfID[cRadPosHR]=ucRePosStorageHR4FD;

               aucP_OfID[0]=GETucIdCalPressure(ucRePosStorageVL4FD);
               aucP_OfID[1]=GETucIdCalPressure(ucRePosStorageVR4FD);
               aucP_OfID[2]=GETucIdCalPressure(ucRePosStorageHL4FD);
               aucP_OfID[3]=GETucIdCalPressure(ucRePosStorageHR4FD);

               ascT_OfID[0]=GETscIdCalTemperatur(ucRePosStorageVL4FD);
               ascT_OfID[1]=GETscIdCalTemperatur(ucRePosStorageVR4FD);
               ascT_OfID[2]=GETscIdCalTemperatur(ucRePosStorageHL4FD);
               ascT_OfID[3]=GETscIdCalTemperatur(ucRePosStorageHR4FD);

               aucPaverege_OfID[0]=GETucStoragePaverege4CompareValue(ucRePosStorageVL4FD);
               aucPaverege_OfID[1]=GETucStoragePaverege4CompareValue(ucRePosStorageVR4FD);
               aucPaverege_OfID[2]=GETucStoragePaverege4CompareValue(ucRePosStorageHL4FD);
               aucPaverege_OfID[3]=GETucStoragePaverege4CompareValue(ucRePosStorageHR4FD);

               for( i = 0; i < cAnzRad; i++ ){
                  switch (aucOldColOfID[i]){
                     case cRadPosVL:
                     {
                        PUTucIdCalPressure(aucP_OfID[i],cRadPosVL);
                        PUTscIdCalTemperatur(ascT_OfID[i],cRadPosVL);
                        PUTuiStoragePaverege4CompareValue(((uint16)aucPaverege_OfID[i]),cRadPosVL);
                     }
                     break;
                     case cRadPosVR:
                     {
                        PUTucIdCalPressure(aucP_OfID[i],cRadPosVR);
                        PUTscIdCalTemperatur(ascT_OfID[i],cRadPosVR);
                        PUTuiStoragePaverege4CompareValue(((uint16)aucPaverege_OfID[i]),cRadPosVR);
                     }
                     break;
                     case cRadPosHL:
                     {
                        PUTucIdCalPressure(aucP_OfID[i],cRadPosHL);
                        PUTscIdCalTemperatur(ascT_OfID[i],cRadPosHL);
                        PUTuiStoragePaverege4CompareValue(((uint16)aucPaverege_OfID[i]),cRadPosHL);
                     }
                      break;
                     case cRadPosHR:
                     {
                       PUTucIdCalPressure(aucP_OfID[i],cRadPosHR);
                        PUTscIdCalTemperatur(ascT_OfID[i],cRadPosHR);
                        PUTuiStoragePaverege4CompareValue(((uint16)aucPaverege_OfID[i]),cRadPosHR);
                     }
                     break;
                     default:
                     {
                        ucRtn = FALSE;
                     }
                  }
               }

               ClearBitBetriebszustandBZ(cCAL_AFD_PLAUSI_ERROR);
               if(Get_FD_STATUS() == cFILLING_DETECTED){
                  if((FD_Plausibility_CheckP4DPLR_DPABS(ucColOfIdVL,ucColOfIdVR,ucColOfIdHL,ucColOfIdHR) == TRUE) && (GETushWarnstatus1WN() == FALSE)){

                     BZ_FZZ_RQ_State4AFD_Finish();
                     PUTucPrefFront(((GETucIdCalPressure(ucColOfIdVL) + GETucIdCalPressure(ucColOfIdVR))/2));
                     PUTucPrefRear(((GETucIdCalPressure(ucColOfIdHL) + GETucIdCalPressure(ucColOfIdHR))/2));

                     PUTucPfillFront(GETucPrefFront());
                     PUTucPfillRear(GETucPrefRear());

                     scTfillVA=((GETscIdCalTemperatur(ucColOfIdVL) + GETscIdCalTemperatur(ucColOfIdVR))/2);
                     scTfillHA=((GETscIdCalTemperatur(ucColOfIdHL) + GETscIdCalTemperatur(ucColOfIdHR))/2);
                     if(scTfillVA > cTfillLimitH){
                     scTfillVA=cTfillLimitH;
                     }
                     if(scTfillHA > cTfillLimitH){
                        scTfillHA=cTfillLimitH;
                     }

                     scTfill_Tref=(scTfillVA + scTfillHA)/2;
                     PUTscTfill(scTfill_Tref);
                     scTfill_Tref=KweightCalculation(scTfill_Tref, (sint8)(tEnvDataToSend.ucTempOut));

                     PUTucPrefFront(GetP4NewTempAtCAL(GETucPrefFront(),scTfillVA, scTfill_Tref));
                     if(GETucPrefFront() <= GETucPcalMinVaRelativCodOfRam()){
                        PUTucPrefFront(GETucPcalMinVaRelativCodOfRam());
                     }

                     PUTucPrefRear(GetP4NewTempAtCAL(GETucPrefRear(),scTfillHA, scTfill_Tref));
                     if(GETucPrefRear() <= GETucPcalMinHaRelativCodOfRam()){
                        PUTucPrefRear(GETucPcalMinHaRelativCodOfRam());
                     }

                     PUTscTref(scTfill_Tref);

                     PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdVL)),GETscIdCalTemperatur(ucColOfIdVL), scTfill_Tref),cRadPosVL);
                     PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdVR)),GETscIdCalTemperatur(ucColOfIdVR), scTfill_Tref),cRadPosVR);
                     PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdHL)),GETscIdCalTemperatur(ucColOfIdHL), scTfill_Tref),cRadPosHL);
                     PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdHR)),GETscIdCalTemperatur(ucColOfIdHR), scTfill_Tref),cRadPosHR);

                   }
                  else{
                     ClearFillingDetectionStateFD();
                     if(GETushWarnstatus1WN() == TRUE){
                        if(Get_FD_STATUS() == FALSE){
                           SetState2FillingDetectionStateFD(cFD_ACTIV_WARNING);
                        }
                     }
                     else{

                        SetState2FillingDetectionStateFD(cFILLING_UNPLAUSIBLE);
                        SetBitBetriebszustandBZ(cCAL_AFD_PLAUSI_ERROR);
                        BZ_FZZ_RQ_State4AFD_Finish();
                     }
                     if(ucReVa2Ha_Ha2VA==TRUE){
                        aucP_OfID[0]=GETucPrefFront();
                        aucP_OfID[1]=GETucPrefRear();
                        PUTucPrefFront(aucP_OfID[1]);
                        PUTucPrefRear(aucP_OfID[0]);
                     }

                     PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdVL)),GETscIdCalTemperatur(ucColOfIdVL), GETscTref()),cRadPosVL);
                     PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdVR)),GETscIdCalTemperatur(ucColOfIdVR), GETscTref()),cRadPosVR);
                     PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdHL)),GETscIdCalTemperatur(ucColOfIdHL), GETscTref()),cRadPosHL);
                     PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdHR)),GETscIdCalTemperatur(ucColOfIdHR), GETscTref()),cRadPosHR);

                   }
               }
               else{
                  if(Get_FD_STATUS() == FALSE){
                     SetState2FillingDetectionStateFD(cFILLING_NOT_DETECTED);
                  }

                     PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdVL)),GETscIdCalTemperatur(ucColOfIdVL), GETscTref()),cRadPosVL);
                  PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdVR)),GETscIdCalTemperatur(ucColOfIdVR), GETscTref()),cRadPosVR);
                  PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdHL)),GETscIdCalTemperatur(ucColOfIdHL), GETscTref()),cRadPosHL);
                  PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdHR)),GETscIdCalTemperatur(ucColOfIdHR), GETscTref()),cRadPosHR);

               }
            }
            else{
               ucRtn = FALSE;
            }
         }
         else{
            ucRtn = FALSE;
         }
   }
   return ucRtn;
}

void PUTuiStoragePaverege4CompareValue(uint16 x, uint8 i){
   uiStoragePaverege4CompareValue[i]=x;
}

uint16 GETuiStoragePaverege4CompareValue(uint8 i){
   return (uiStoragePaverege4CompareValue[i]);
}

uint8 GETucStoragePaverege4CompareValue(uint8 i){
   return ((uint8)(uiStoragePaverege4CompareValue[i]));
}

void PUTucDpStabiPressure(uint8 x, uint8 i){
   ucDpStabiPressure[i]=x;
}

uint8 GETucDpStabiPressure( uint8 i){
   return ucDpStabiPressure[i];
}

void PUTucIdCalPressure(uint8 x, uint8 i){
   ucIdCalPressure[i]=x;
}

uint8 GETucIdCalPressure( uint8 i){
   return ucIdCalPressure[i];
}

void PUTscIdCalTemperatur(sint8 x, uint8 i){
  scIdCalTemperatur[i]=x;
}

sint8 GETscIdCalTemperatur(uint8 i){
  return scIdCalTemperatur[i];
}

void PUTucPfillFront(uint8 x){
   ucPfillFront=x;
}

uint8 GETucPfillFront(void){
   return ucPfillFront;
}

void PUTucPfillRear(uint8 x){
   ucPfillRear=x;
}

uint8 GETucPfillRear(void){
   return ucPfillRear;
}

void PUTscTfill(sint8 x){
   scTfill=x;
}

sint8 GETscTfill(void){
   return scTfill;
}

void PUTucCnt4DP_FILL_DFL(uint8 x){
  ucCnt4DP_FILL_DFL = x;
}

uint8 GETucCnt4DP_FILL_DFL(void){
   return ucCnt4DP_FILL_DFL;
}

uint8 GETucCnt4DP_FILL_DFL4LTSlogged(void){
   if((ucLockByt4DFL_LTS & 0x80) == 0x80 ){
      return TRUE;
   }
   else{
      return FALSE;
   }
}

uint8 GETucDFL_LTS3(void){
   return ucLockByt4DFL_LTS;
}

void INCucCnt4DP_FILL_DFL(void){
   if(ucCnt4DP_FILL_DFL < 0xFF){
      ucCnt4DP_FILL_DFL++;
   }
}

void PUTucCnt4DP_FILL_DFL4LTSlogged(void){
   if((ucLockByt4DFL_LTS & 0x80) != 0x80 ){
      ucLockByt4DFL_LTS |= 0x80;
   }
}

void PUTucCnt4DP_FILL_DFLloggedFL(void){
   if((ucCnt4DP_FILL_DFL & cDP_FILL_FL) != cDP_FILL_FL){
      ucCnt4DP_FILL_DFL+=cDP_FILL_FL;
   }
}

uint8 GETucCnt4DP_FILL_DFLloggedFL(void){
   if((ucCnt4DP_FILL_DFL & cDP_FILL_FL) != cDP_FILL_FL){
      return FALSE;
   }
   else{
      return TRUE;
   }
}

void PUTucCnt4DP_FILL_DFLloggedFR(void){
   if((ucCnt4DP_FILL_DFL & cDP_FILL_FR) != cDP_FILL_FR){
      ucCnt4DP_FILL_DFL+=cDP_FILL_FR;
   }
}
uint8 GETucCnt4DP_FILL_DFLloggedFR(void){
   if((ucCnt4DP_FILL_DFL & cDP_FILL_FR) != cDP_FILL_FR){
      return FALSE;
   }
   else{
      return TRUE;
   }
}

void PUTucCnt4DP_FILL_DFLloggedRL(void){
   if((ucCnt4DP_FILL_DFL & cDP_FILL_RL) != cDP_FILL_RL){
      ucCnt4DP_FILL_DFL+=cDP_FILL_RL;
   }
}

uint8 GETucCnt4DP_FILL_DFLloggedRL(void){
   if((ucCnt4DP_FILL_DFL & cDP_FILL_RL) != cDP_FILL_RL){
      return FALSE;
   }
   else{
      return TRUE;
   }
}

void PUTucCnt4DP_FILL_DFLloggedRR(void){
   if((ucCnt4DP_FILL_DFL & cDP_FILL_RR) != cDP_FILL_RR){
      ucCnt4DP_FILL_DFL+=cDP_FILL_RR;
   }
}
uint8 GETucCnt4DP_FILL_DFLloggedRR(void){
   if((ucCnt4DP_FILL_DFL & cDP_FILL_RR) != cDP_FILL_RR){
      return FALSE;
   }
   else{
      return TRUE;
   }
}

void PUTucLockByt4DFL_LTS(uint8 x){
      ucLockByt4DFL_LTS = x;
}

void PUTucCnt4DP_FILL_IFL(uint8 x){
  ucCnt4DP_FILL_IFL = x;
}

void PUTucCnt4DP_FILL_IFLloggedFL(void){
   if((ucCnt4DP_FILL_IFL & cDP_FILL_FL) != cDP_FILL_FL){
      ucCnt4DP_FILL_IFL+=cDP_FILL_FL;
   }
}

uint8 GETucCnt4DP_FILL_IFLloggedFL(void){
   if((ucCnt4DP_FILL_IFL & cDP_FILL_FL) != cDP_FILL_FL){
      return FALSE;
   }
   else{
      return TRUE;
   }
}

void PUTucCnt4DP_FILL_IFLloggedFR(void){
   if((ucCnt4DP_FILL_IFL & cDP_FILL_FR) != cDP_FILL_FR){
      ucCnt4DP_FILL_IFL+=cDP_FILL_FR;
   }
}
uint8 GETucCnt4DP_FILL_IFLloggedFR(void){
   if((ucCnt4DP_FILL_IFL & cDP_FILL_FR) != cDP_FILL_FR){
      return FALSE;
   }
   else{
      return TRUE;
   }
}

void PUTucCnt4DP_FILL_IFLloggedRL(void){
   if((ucCnt4DP_FILL_IFL & cDP_FILL_RL) != cDP_FILL_RL){
      ucCnt4DP_FILL_IFL+=cDP_FILL_RL;
   }
}

uint8 GETucCnt4DP_FILL_IFLloggedRL(void){
   if((ucCnt4DP_FILL_IFL & cDP_FILL_RL) != cDP_FILL_RL){
      return FALSE;
   }
   else{
      return TRUE;
   }
}

void PUTucCnt4DP_FILL_IFLloggedRR(void){
   if((ucCnt4DP_FILL_IFL & cDP_FILL_RR) != cDP_FILL_RR){
      ucCnt4DP_FILL_IFL+=cDP_FILL_RR;
   }
}
uint8 GETucCnt4DP_FILL_IFLloggedRR(void){
   if((ucCnt4DP_FILL_IFL & cDP_FILL_RR) != cDP_FILL_RR){
      return FALSE;
   }
   else{
      return TRUE;
   }
}

uint8 GETucCnt4DP_FILL_IFL(void){
   return ucCnt4DP_FILL_IFL;
}
void INCucCnt4DP_FILL_IFL(void){
   if(ucCnt4DP_FILL_IFL < 0xFF){
      ucCnt4DP_FILL_IFL++;
   }
}

void PUTucNoCheckPmin4StopFD(uint8 x){
  ucNoCheckPmin4StopFD = x;
}

uint8 GETucNoCheckPmin4StopFD(void){
   return ucNoCheckPmin4StopFD;
}

void ClearBitInNoCheckPmin4StopFD( uint8 ucBitMask ){
   ucNoCheckPmin4StopFD &= (~ucBitMask);
}

void ClearKplNoCheckPmin4StopFD(void){
   ucNoCheckPmin4StopFD = 0;
}

void PUTucFDcheckP2PosOk(uint8 x){
  ucFDcheckP2PosOk = x;
}

uint8 GETucFDcheckP2PosOk(void){
   return ucFDcheckP2PosOk;
}

void DECucFDcheckP2PosOk(void){
  ucFDcheckP2PosOk--;
}

void ClearBitInucFDcheckP2PosOk( uint8 ucBitMask ){
   ucFDcheckP2PosOk &= (~ucBitMask);
}

void ClearFDcheckP2PosOk(void){
   ucFDcheckP2PosOk = 0;
}

void PUTushZomTioFreeze(uint16 x){
   ushZomTioFreez = x;
}

uint16 GETushZomTioFreeze(void){
   return ushZomTioFreez;
   }

void DECushZomTioFreeze(void){
   if(ushZomTioFreez != 0){
      ushZomTioFreez--;
   }

}
#ifdef AS_ID_VALUE

void PUTucReCntVL4FD(uint8 x){
   ucReCntVL4FD=x;
}

void INCucReCnt4FD(uint8 ucRadPos){
   switch (ucRadPos){
      case cRadPosVL:
            ucReCntVL4FD++;
      break;

      case cRadPosVR:
            ucReCntVR4FD++;
      break;

      case cRadPosHL:
            ucReCntHL4FD++;
      break;

      case cRadPosHR:
            ucReCntHR4FD++;
      break;
   }
}

uint8 GETucReCntVL4FD(void){
   return ucReCntVL4FD;
}

uint8 GETucReCnt4FD(uint8 ucRadPos){
uint8 ucReturnValue;

   switch (ucRadPos){
      case cRadPosVL:
      {
         if(ucReCntVL4FD == 0xFF){
            ucReCntVL4FD--;
         }
         ucReturnValue= ucReCntVL4FD;
      }
      break;

      case cRadPosVR:
      {
         if(ucReCntVR4FD == 0xFF){
            ucReCntVR4FD--;
         }
         ucReturnValue= ucReCntVR4FD;
      }
      break;

      case cRadPosHL:
      {
         if(ucReCntHL4FD == 0xFF){
            ucReCntHL4FD--;
         }
         ucReturnValue= ucReCntHL4FD;
      }
      break;

      case cRadPosHR:
      {
         if(ucReCntHR4FD == 0xFF){
            ucReCntHR4FD--;
         }
         ucReturnValue= ucReCntHR4FD;
      }
      break;
      default:
            ucReturnValue= 0xFF;
   }

   return ucReturnValue;
}

#endif

void InitRePosStorage4FD(void){
   ucRePosStorageVL4FD=0xFF;
   ucRePosStorageVR4FD=0xFF;
   ucRePosStorageHL4FD=0xFF;
   ucRePosStorageHR4FD=0xFF;
}

void PUTucCalNotAckState2Ram(uint8 x){
  NvM_RequestResultType ErrorStatus;

  Rte_Pim_Pim_tCalNvMBlock()->ucCalNotAckState = (x);
  Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_GetErrorStatus(&ErrorStatus);
  if(ErrorStatus  != NVM_REQ_PENDING){
    Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_SetRamBlockStatus(TRUE);
  }
}

void ClearCalNotAckState(void){
  NvM_RequestResultType ErrorStatus;

  Rte_Pim_Pim_tCalNvMBlock()->ucCalNotAckState = FALSE;
  Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_GetErrorStatus(&ErrorStatus);
  if(ErrorStatus  != NVM_REQ_PENDING){
    Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_SetRamBlockStatus(TRUE);
  }
}

void ClearCalNotAckState4MFD(void){
   Rte_Pim_Pim_tCalNvMBlock()->ucCalNotAckState &= (~0xBF);
   Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_SetRamBlockStatus(TRUE);
}

void ClearBitCalNotAckState( uint8 ucBitMask ){
  uint8 ui8IsModified;

  ui8IsModified = Rte_Pim_Pim_tCalNvMBlock()->ucCalNotAckState;
   Rte_Pim_Pim_tCalNvMBlock()->ucCalNotAckState &= (~ucBitMask);

  if(ui8IsModified != Rte_Pim_Pim_tCalNvMBlock()->ucCalNotAckState){
    Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_SetRamBlockStatus(TRUE);
  }
}

uint8 GETucCalNotAckStateOfRam(void){
   return Rte_Pim_Pim_tCalNvMBlock()->ucCalNotAckState;
}

void SetBitCalNotAckState2Ram( uint8 ucBitMask ){
  NvM_RequestResultType ErrorStatus;

  Rte_Pim_Pim_tCalNvMBlock()->ucCalNotAckState |= (ucBitMask);

  Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_GetErrorStatus(&ErrorStatus);
  if(ErrorStatus  != NVM_REQ_PENDING){
    Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_SetRamBlockStatus(TRUE);
  }
}

uint8 bGETucCalNotAckState( uint8 ucBitMask ){
  if((Rte_Pim_Pim_tCalNvMBlock()->ucCalNotAckState & ucBitMask) !=0){
      return TRUE;
   }
   else{
      return FALSE;
   }
}

void PUTucCalRequestState2Ram(uint8 x){
  NvM_RequestResultType ErrorStatus;
  Rte_Pim_Pim_tCalNvMBlock()->ucCalRequestState = (x);
  Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_GetErrorStatus(&ErrorStatus); /* to avoid multi requests */
  if(ErrorStatus  != NVM_REQ_PENDING){
    Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_SetRamBlockStatus(TRUE);
  }
}
void SetBitCalRequestState2Ram( uint8 ucBitMask ){
  NvM_RequestResultType ErrorStatus;
  Rte_Pim_Pim_tCalNvMBlock()->ucCalRequestState |= (ucBitMask);
  Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_GetErrorStatus(&ErrorStatus);
  if(ErrorStatus  != NVM_REQ_PENDING){
    Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_SetRamBlockStatus(TRUE);
  }
}

void ClearBitCalRequestState( uint8 ucBitMask ){
  uint8 ui8IsModified;
  NvM_RequestResultType ErrorStatus;

  ui8IsModified = Rte_Pim_Pim_tCalNvMBlock()->ucCalRequestState;
   Rte_Pim_Pim_tCalNvMBlock()->ucCalRequestState &= (~ucBitMask);

  if(ui8IsModified != Rte_Pim_Pim_tCalNvMBlock()->ucCalRequestState){
    Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_GetErrorStatus(&ErrorStatus);
    if(ErrorStatus  != NVM_REQ_PENDING){
      Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_SetRamBlockStatus(TRUE);
    }
  }
}

void ClearCalRequestStateAtMFDfinish( void ){
  uint8 ui8IsModified;

  ui8IsModified = Rte_Pim_Pim_tCalNvMBlock()->ucCalRequestState;
   Rte_Pim_Pim_tCalNvMBlock()->ucCalRequestState &= (~0x0F);

  if(ui8IsModified != Rte_Pim_Pim_tCalNvMBlock()->ucCalRequestState){
    Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_SetRamBlockStatus(TRUE);
  }
}

uint8 GETucCalRequestStateOfRam(void){
   return Rte_Pim_Pim_tCalNvMBlock()->ucCalRequestState;
}

uint8 bGETucCalRequestState( uint8 ucBitMask ){
  if((Rte_Pim_Pim_tCalNvMBlock()->ucCalRequestState & ucBitMask) !=0){
      return TRUE;
   }
   else{
      return FALSE;
   }
}

uint8 GETucPrefFront (void){return Rte_Pim_Pim_tCalNvMBlock()->ucPrefFront;}
uint8 GETucPrefRear  (void){return Rte_Pim_Pim_tCalNvMBlock()->ucPrefRear;}

void PUTucPrefFront(uint8 x){
  NvM_RequestResultType ErrorStatus;
  Rte_Pim_Pim_tCalNvMBlock()->ucPrefFront = (x);
  Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_GetErrorStatus(&ErrorStatus);
  if(ErrorStatus  != NVM_REQ_PENDING){
    Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_SetRamBlockStatus(TRUE);
  }
}
void PUTucPrefRear(uint8 x){
  NvM_RequestResultType ErrorStatus;
  Rte_Pim_Pim_tCalNvMBlock()->ucPrefRear = (x);
  Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_GetErrorStatus(&ErrorStatus);
  if(ErrorStatus  != NVM_REQ_PENDING){
    Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_SetRamBlockStatus(TRUE);
  }
}

sint8 GETscTref(void){return Rte_Pim_Pim_tCalNvMBlock()->scTref;}

void PUTscTref(sint8 x){
  NvM_RequestResultType ErrorStatus;
  Rte_Pim_Pim_tCalNvMBlock()->scTref = (x);
  Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_GetErrorStatus(&ErrorStatus);
  if(ErrorStatus  != NVM_REQ_PENDING){
    Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_SetRamBlockStatus(TRUE);
  }
}

void BZ_FZZ_RQ_State4AFD_Finish(void){
   SetBitBetriebszustandBZ(cCAL_FINISH);
   ClearBitBetriebszustandBZ(cCAL_REQUEST);
   ClearBitFahrzeugzustandFZZ(cKFZPARKING_START_AFD);
     ClearBitCalRequestState(cCAL_AUTO_ACTIV | cCAL_AUTO_ENABLE2 | cCAL_AUTO_ENABLE3 | cCAL_AUTO_NEW_ID);
}

uint8 ucCheckPminDPautoAFD(uint8 ucRadPos){
   uint8 ucRtn = FALSE;

   switch (ucRadPos){
      case cRadPosVL:
    case cRadPosVR:
      {
         if( ucGetLastReceivedPress(ulGetID(ucGetColOfWP(ucRadPos))) <= (GETucPcalMinVaRelativCodOfRam() - cDP_AUTO)){
            ucRtn=TRUE;
         }
      }
      break;

      case cRadPosHL:
      case cRadPosHR:
      {
         if( ucGetLastReceivedPress(ulGetID(ucGetColOfWP(ucRadPos))) <= (GETucPcalMinHaRelativCodOfRam() - cDP_AUTO)){
            ucRtn=TRUE;
         }
      }
      break;
   }
   return ucRtn;
}
#ifdef as_FD_CalculateTref

sint8 FD_CalculateTref(sint8 scTemperaturOutside){

   sint8 scTfillVA;
   sint8 scTfillHA;
   sint8 scTfill_Tref;

   scTfillVA= (ucGetHMICurrentTirePress(cRadPosVL) +  ucGetHMICurrentTirePress(cRadPosVR))/2);

   scTfillHA= (ucGetHMICurrentTirePress(cRadPosHL) +  ucGetHMICurrentTirePress(cRadPosHR))/2);
   scTfill_Tref=(scTfillVA + scTfillHA)/2;
   scTfill_Tref=KweightCalculation(scTfill_Tref, scTemperaturOutside);

   return scTfill_Tref;
}

#endif
