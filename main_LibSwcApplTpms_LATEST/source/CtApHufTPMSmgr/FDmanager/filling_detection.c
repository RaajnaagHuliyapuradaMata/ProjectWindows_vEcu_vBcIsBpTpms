/************************************************************************************************************
 * (c) HuF Hülsbeck & Fürst GmbH Co.KG      Abteilung PDSTPS     2016
 ************************************************************************************************************/

/*********************************************************************************************************//**
 * \file filling_detection.c
 * \brief Manager 4 Filling Detection Manual + Automatic
 *
 *------------------------------------------------------------------------------------------------------------
 * Global Description
 * 
 *
 *
 *
 *
 *------------------------------------------------------------------------------------------------------------
 * Modul Description
 * 
 *
 * Purpose:
 *
 *
 *
 *------------------------------------------------------------------------------------------------------------
 */


/************************************************************************************************************
 *                                             include
 ************************************************************************************************************/
//#include "filling_detectionX.h"
#include "filling_detection.h"
#include "Rte_CtApHufTPMSmgr.h"
#include "HMI_handlerX.h" /*CRS_1211_130_156*/
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
/************************************************************************************************************
 *                                             macro
 ************************************************************************************************************/
#define cFD_TIME_OUT  540 // 9 min 
#define cFD_MIN_TIME4RESTART_AFD 420 // 7min 
/************************************************************************************************************
 *                                            typedef
 ************************************************************************************************************/
/***********************************************************************************************************
 *                                 prototype (local functions - private)
 ***********************************************************************************************************/
//void FillingDetectionMFD(void);
void FillingDetectionMFD(uint8); /*CRS_1211_130_312*/
void FillingDetectionAFDII(void);
void FillingDetectionAFDIII(uint8);

void FD_AbortFillingDetection(uint8);
#ifdef as_16BitP4Average
//void FD_CalcAverageP4MFD( uint8, uint8, uint8, uint8);
void FD_CalcAverageP4MFD( uint8, uint8, uint8);
#endif
uint8 FD_CheckP4AFDstartReason2_3FA( uint8, uint8, sint8, uint8); 
uint8 FD_CheckP4AFDstartReason2_3RA( uint8, uint8, sint8, uint8); 


//void FD_CheckP4DPLR_DPABSandSetPrefMFD( sint8);
void FD_PlausibilityCheckMFD( sint8); 
void FD_UnplausibleMFD(void); /*CRS_1211_500_1279 CRS_1211_130_216*/
void FD_Check3RePlausiSetMilage4FinishedMFD(void); /*CRS_1211_130_335*/
void FD_Check3ReAndUpdatePifWarnLampOnOffDefOrInf2Re4FinishedAFD(void); /*CRS_1211_130_335*/
void FD_UpdatePressure4AfdWarnLampON(uint8, sint8 );
void FD_UpdatePressure4AfdWarnLampOFF(uint8 , uint8, sint8 );

uint8 FD_UpdateComparePressureAfterFBM(void);
void FD_UpdateComparePressureAtWarning(uint8);
// never used void FD_UpdateComparePressure4NewId(uint8, sint8, sint8, uint8); /*CRS_1211_130_184 */
uint8 FD_UpdateIDvalue4MFD(void); /*CRS_1211_130_335*/

uint8 FD_Plausibility_CheckP4DPLR_DPABS(uint8,uint8,uint8,uint8); /* Check pressure: DP_LR + DP_ABS and set Pref Tref Pcompare*/
void  FD_CheckResetCondition4ImplausiMsg(uint8,uint8,uint8,uint8); /* Check Reset Condition 4 Implausible Pressure Warning */
uint8 FD_CheckCurrentPmin(void); /*CRS_1211_130_332 Check Pmin for stoped the FD immediately*/

uint8 FD_FlowChartFct1CheckPmin(void); /*CRS_1211_130_347*/
uint8 FD_FlowChartFct1CheckMissingRE(void); /*CRS_1211_130_347*/

uint8 FD_FlowChartFct1(void); /*CRS_1211_130_335*/

uint8 FD_CheckFDpos2ZomPosAfterZOfinish(void); /*CRS_1211_130_336*/
uint8 FD_CheckHistPos(void); /*CRS_1211_130_345*/

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
void PUTucLockByt4DFL_LTS(uint8 x);/*CRS_1211_130_371*/ 
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

void InitRePosStorage4FD(void); /*CRS_1211_130_373*/


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
void ClearKplNoCheckPmin4StopFD(void); /*CRS_1211_130_330*/

void PUTucFDcheckP2PosOk(uint8);
uint8 GETucFDcheckP2PosOk(void);
void DECucFDcheckP2PosOk(void);
void ClearFDcheckP2PosOk(void); /*CRS_1211_130_336*/

void PUTushZomTioFreeze(uint16); /*CRS_1211_130_336*/
uint16 GETushZomTioFreeze(void); /*CRS_1211_130_336*/

void FD_HandleReceivedReRadPosVL4AFD(uint8,sint8,uint8,uint8);
void FD_HandleReceivedReRadPosVR4AFD(uint8,sint8,uint8,uint8);
void FD_HandleReceivedReRadPosHL4AFD(uint8,sint8,uint8,uint8);
void FD_HandleReceivedReRadPosHR4AFD(uint8,sint8,uint8,uint8);

uint8 FD_LoadIdValues4MFD(void);
uint8 FD_TimeoutHandle4AFD(void);
uint8 FD_LoadIdValues4UpdateCompareValue(void);


/************************************************************************************************************
 *                               prototype (external functions - interface)
 ************************************************************************************************************/

/************************************************************************************************************
 *                                    data (Modulglobal) - ROM
 ************************************************************************************************************/

/************************************************************************************************************
 *                                    data (Modulglobal) - RAM
 ************************************************************************************************************/
uint8 ucStoreCompValueVL;
uint8 ucStoreCompValueVR;
uint8 ucStoreCompValueHL;
uint8 ucStoreCompValueHR;
uint8 ucIdCalPressure[4]; /*cache 4x pressure modulglobal CRS_1211_130_250*/
uint8 ucDpStabiPressure[4];
sint8 scIdCalTemperatur[4];/*cache 4x temperature  modulglobal CRS_1211_130_250*/
uint16 uiStoragePaverege4CompareValue[4]; /*CRS_1211_130_205*/
uint8 ucPfillFront;
uint8 ucPfillRear;
sint8 scTfill;
uint8 ucReCntVL4FD;	/*CRS_1211_130_335*/
uint8 ucReCntVR4FD;	/*CRS_1211_130_335*/
uint8 ucReCntHL4FD;	/*CRS_1211_130_335*/
uint8 ucReCntHR4FD;	/*CRS_1211_130_335*/
uint8 ucRePosStorageVL4FD; /* rette die AFDII Position nach 3 Telegrammen CRS_1211_130_336*/
uint8 ucRePosStorageVR4FD; /*CRS_1211_130_336*/
uint8 ucRePosStorageHL4FD; /*CRS_1211_130_336*/
uint8 ucRePosStorageHR4FD; /*CRS_1211_130_336*/
uint16 ushZomTioFreez;/*CRS_1211_130_336*/


uint8 ucCnt4DP_FILL_DFL;
uint8 ucCnt4DP_FILL_IFL;
uint8 ucLockByt4DFL_LTS; /*CRS_1211_130_371 im Zusammenhang! */

uint8 ucNoCheckPmin4StopFD; //CRS_1211_130_325 SOFT RESET or Globaler RESET--> No Check P below P_MIN_TIRE!

uint8 ucFDcheckP2PosOk; /*CRS_1211_130_336*/


//uint8 ucWheelPosWarn4FD;
extern DT_tEnvData tEnvDataToSend;
/************************************************************************************************************
 *                                       data (global) - ROM
 ************************************************************************************************************/



/************************************************************************************************************
 *                                       data (global) - RAM
 ************************************************************************************************************/



 /************************************************************************************************
 * \brief routine start: Filling Detection MANUAL Restart of TPMS 
 * 
 *-----------------------------------------------------------------------------------------------
 * \param [in] ucRestartAnzeige [TRUE= RESTART LAMPE[6] ON],[FALSE= RESTART LAMPE[6] OFF CRS_1211_130_312
 * \param [out] none
 *
 * \return none
 *
 *------------------------------------------------------------------------------------------------
 */
void FillingDetectionMFD(uint8 ucRestartAnzeige)
{
  uint8 i;
  
	if((bGetBitBetriebszustandBZ(cCAL_REQUEST) == FALSE)
	|| ((bGetBitBetriebszustandBZ(cCAL_REQUEST) == TRUE) && (bGETucCalRequestState(cCAL_AUTO_ACTIV))))/*CRS_1211_130_073 CRS_1211_130_151*/
	{
			ClearCalNotAckState4MFD(); /*CRS_1211_130_274*/
			//ClearCalNotAckState();
			//CRS_1211_130_249 PUTucCalNotAckState2Nvm(); /*CRS_1211_130_240*/
			ClearAllReCnt4FD(); /* ReCounter4CalVL CRS_1211_130_058*/
			ClearFDcheckP2PosOk();     /*CRS_1211_130_336*/     

#ifdef AVG_PRESS_ENABLED			
			ClearAvgPress4FD();
#endif

      /*@@AS CR_1211_130_050  Kalibrieranforderung!*/ 
		  SetBitBetriebszustandBZ(cCAL_REQUEST);
			ClearBitBetriebszustandBZ(cCAL_FINISH | cCAL_MFD_PLAUSI_ERROR | cCAL_AFD_PLAUSI_ERROR);
			//ClearBitBetriebszustandBZ(cCAL_MFD_PLAUSI_ERROR);/*CRS_1211_130_202 first reset condition of 5.5.5 */
			//ClearBitBetriebszustandBZ(cCAL_AFD_PLAUSI_ERROR); /*CRS_1211_130_290 Clear Bit 4  "Filling not detected" for AFD  (Filling detection flow chart 5.2) */	

		  ClearBitZustandskennungZK(cZK_ALLE_BITS); /*init cal bits in ZK */

      for (i = 0; i < cAnzRad; i++) /*CLEAR cRadPosVL ...cRadPosHR*/
		  {
		    PUTucIdCalPressure(FALSE,i); /*clear pressure ID spezifisch*/
		    PUTscIdCalTemperatur(FALSE,i); /*clear temperature ID spezifisch*/
		  }
      /*CRS_1211_130_052 Start 5sec Timer und setze "TPM_Msg_Disp_Rq =I_C04_TPM_MSGDISP_RQ_RESTART=6 "  in Botschaft 0x409 TireState_2  */
			//ClearBitCalRequestState(cCAL_MANUAL_FINISH); 
			ClearBitCalRequestState(cCAL_MANUAL_FINISH | cCAL_AUTO_ACTIV | cCAL_AUTO_ENABLE2 | cCAL_AUTO_ENABLE3 | cCAL_AUTO_NEW_ID);		     
			SetBitCalRequestState2Ram(cCAL_MSG2DISP | cCAL_MANUAL_ACTIV);
			//SetBitCalRequestState2Ram(cCAL_MANUAL_ACTIV);
			ClearBitFahrzeugzustandFZZ(cKFZPARKING_START_AFD); /* CRS_1211_130_170 clear look bit for AFD start reason 2*/
			//ClearBitCalRequestState(cCAL_AUTO_ACTIV);
			//ClearBitCalRequestState(cCAL_AUTO_ENABLE2);
			//ClearBitCalRequestState(cCAL_AUTO_ENABLE3);
			//ClearBitCalRequestState(cCAL_AUTO_NEW_ID);
			
			//CRS_1211_130_249 PUTucCalRequestState2Nvm(); /* CRS_1211_130_243 CalRequestState into Nvm if Kl15off and softreset*/				
			ClearKplNoCheckPmin4StopFD(); /*CRS_1211_130_330*/				
			PUTucNoCheckPmin4StopFD(ucCheckLOW_PRESS_ReState()); /* CRS_1211_130_358 HW or PminFL=0x01, FR=0x02, HL=0x04, HR=0x08 --> 0x0C=HL+HR in ucNoCheckPmin4StopAFD spez. Bits 4 HW+ Pmin*/
					
			ClearAbortReasonFD();	/*CRS_1211_130_181	   */
			ClearPlausiFailureFD(); /*clear Plausi kpl. DP_Left_Right, MINIMUM_PRESSURE, DP_ABS, DP_MANUAL  */
			SetState2FillingDetectionStateFD(cMFD_RUNNING); /*CRS_1211_130_181	   */

			if( ucRestartAnzeige == TRUE)
			{	 		 		
				PUTucTimer4MsgDispRq(5); /*5 sec */
			} 			
			PUTushFDtimeout(cFD_TIME_OUT); /*CRS_1211_130_335  */
			PUTushSupervisoryTimerFD(cFD_TIME_OUT);/*CRS_1211_130_335  */
			PUTucFDtimerStop(FALSE); /*CRS_1211_130_337  */
			PUTucOnceCheckMissingRE4FD(0);
			//ResetWarningsUSWIF(); /* reset all warnings and timers for waallgo*/
			DelWarnOfId(4); /*MFA2: CRS_1211_130_234 neu aus papenburg April --> 4=all DelWarnOfId(uint8 ui8HistColOfID) */
		} 
		else
		{
			 /*CRS_1211_130_073*/
			if(GETucTimer4MsgDispRq() == 0) /*timer 4 cal request 2 display is empty -> start again */
			{
				
#ifdef AVG_PRESS_ENABLED			
				ClearAvgPress4FD();
#endif
				ClearAllReCnt4FD(); /* CRS_1211_130_289 ReCounter4CalVL */    
				for (i = 0; i < cAnzRad; i++) /*CRS_1211_130_289 CLEAR cRadPosVL ...cRadPosHR*/
				{
					PUTucIdCalPressure(FALSE,i); /*clear pressure ID spezifisch*/
					PUTscIdCalTemperatur(FALSE,i); /*clear temperature ID spezifisch*/
				}
				if( ucRestartAnzeige == TRUE)
				{					
					PUTucTimer4MsgDispRq(5); /*5 sec */
				}
				PUTushFDtimeout(cFD_TIME_OUT); /*CRS_1211_130_335  */
				PUTushSupervisoryTimerFD(cFD_TIME_OUT);/*CRS_1211_130_335  */
				PUTucOnceCheckMissingRE4FD(0);
				PUTucFDtimerStop(FALSE); /*CRS_1211_130_337  */

				ClearAbortReasonFD();	/*CRS_1211_130_181	   */
				SetBitCalRequestState2Ram(cCAL_MSG2DISP);
			}
		}
}

/*************************************************************************************************
 * \brief routine start: AUTO Filling Detection Start Reason II  Restart of TPMS 
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] none
 * \param [out] none
 *
 * \return none
 *
 *------------------------------------------------------------------------------------------------
 */
void FillingDetectionAFDII(void)
{
	uint8 ucTmp;
	/*ACHTUNG!! TEST mit cT_STANBY4AFD =1min 19min=cT_STANBY */
	if(Getui8ColPWPActive() == FALSE) /*CRS_1211_130_210 FALLbackMode activ?*/
	{
		if((GETucAutoFillDetectionOnOffOfRam() == TRUE) && (bGETucCalRequestState(cCAL_MANUAL_ACTIV) == FALSE))  /*CRS_1211_130_210/_153/_151*/
		{
			if(  bGETucCalNotAckState(cCAL_FBM_ACTIV_NAK) == FALSE) /*CRS_1211_130_344  first return from FALLbackMode!!!*/
			{

				/*Papenburg CRS_1211_130_172*/
				/* ALT: && (((GETulKmStand4AutoCAL() < c_100km) && (GETulKmStand4AutoCAL() > c_50km)) */
				if( (bGETucCalRequestState(cCAL_AUTO_FIRST) == FALSE) && (((GETulKmStand4AutoCAL() < c_100km) && (GETulKmStand4AutoCAL() > c_0km)) /*CRS_1211_130_155 first auto filling detection*/
				||((GETulKmStand4AutoCAL() >= c_100km) && (GETulLastCalMileage() == c_FFFFkm)))) /*CRS_1211_130_201 first auto filling detection*/
				{
					if ((bGetBitFahrzeugzustandFZZ(cKFZPARKING_START_AFD ) == FALSE) && (bGETucCalRequestState(cCAL_AUTO_ENABLE2) == TRUE)) /* Kl.15 OFF --> set cCAL_AUTO_ENABLE2 !*/ 
					{
						SetState2FillingDetectionStateFD(cAFD_RUNNING2); /*CRS_1211_130_285 Schweden Wunsch*/
						ClearAbortReasonFD();/*CRS_1211_130_285 Schweden Wunsch*/
#ifdef AVG_PRESS_ENABLED			
						ClearAvgPress4FD();
#endif

						if(bGetBitFahrzeugzustandFZZ( cFAHRZEUG_FAEHRT ) == TRUE ) /* Papenburg && (GETulKmStand4AutoCAL() < c_100km) && (GETulKmStand4AutoCAL() > c_50km)) driving ? + odometer<100km*/			
						{
							//SetState2FillingDetectionStateFD(cAFD_RUNNING2); /*CRS_1211_130_181*/
							//ClearAbortReasonFD();	/*CRS_1211_130_181 */
							PUTucCalRequestState2Ram(FALSE); /* Clear all bits, CRS_1211_130_151 cCAL_AKTIV_AUTOMATIC cCAL_AKTIV_AUTOMATIC1 cCAL_AKTIV_AUTOMATIC2*/	
							SetBitFahrzeugzustandFZZ(cKFZPARKING_START_AFD ); /* set Look bit */
							SetBitCalRequestState2Ram(cCAL_AUTO_ACTIV | cCAL_AUTO_ENABLE2);/* Kl.15 OFF --> set cCAL_AUTO_ENABLE2 !*/ 				
							//SetBitCalRequestState2Ram(cCAL_AUTO_ACTIV);
							//CRS_1211_130_249 PUTucCalRequestState2Nvm(); /* CRS_1211_130_243 CalRequestState into Nvm if Kl15off and softreset*/	
							InitRePosStorage4FD(); /*CRS_1211_130_373*/

							ClearBitCalRequestState(cCAL_MANUAL_FINISH);/*NEW State 4 AFD is running*/
							PUTucOnceCheckMissingRE4FD(0);
							//PUTucCalNotAckState2Ram(cCAL_VALID); /*clear all bits in CalNotAck state*/
							ClearCalNotAckState();
							//CRS_1211_130_249 PUTucCalNotAckState2Nvm(); /*CRS_1211_130_240*/
							ClearAllReCnt4FD(); /* ucRErecCounter4FDXX=0 ucTmp4CalXX=0; ReCounter4CalVL CRS_1211_130_058*/ 
							ClearFDcheckP2PosOk();     /*CRS_1211_130_336*/
					
							ClearBitBetriebszustandBZ(cCAL_FINISH);
							//ClearBitBetriebszustandBZ(cCAL_MFD_PLAUSI_ERROR); /*CRS_1211_130_202) her AFD only!! */ 
							/*CRS_1211_130_322 ClearBitBetriebszustandBZ(cCAL_AFD_PLAUSI_ERROR); conseve HMI unplausible message! BZ:CRS_1211_130_166 Filling not detected ONE wheel inflated/deflated( Filling detection flow chart 5.2) */	
							SetBitBetriebszustandBZ(cCAL_REQUEST);
							for (ucTmp = 0; ucTmp < cAnzRad; ucTmp++) /*CLEAR cRadPosVL ...cRadPosHR*/
							{
								PUTucIdCalPressure(FALSE,ucTmp); /*clear pressure ID for DP_STABI check  spezifisch*/
								PUTscIdCalTemperatur(FALSE,ucTmp); /*clear temperature ID spezifisch*/
							}
							PUTushFDtimeout(cFD_TIME_OUT); /*CRS_1211_130_335  */
							PUTushSupervisoryTimerFD(cFD_TIME_OUT);/*CRS_1211_130_335  */
							PUTucFDtimerStop(FALSE); /*CRS_1211_130_337  */

						}			
					}
				}
				else
				{
					/* cT_STANBY second and next auto filling detection TEST @@ AS with cT_STANBY4AFD =1min*/
					/* ATTENTION: 1.)INIT ECUParkingTime with cT_STANBY 2.)first car driving  cKFZPARKING_START=TRUE!! counter is starting*/ 
					/*CRS_1211_130_356||(bGETucCalRequestState(cCAL_AUTO_NEW_ID) == TRUE &&  bGETucCalRequestState(cCAL_AUTO_ENABLE2) == TRUE))precondition Kl15off= set cCAL_AUTO_ENABLE2 5.6.3 New sensors are learnt:sart AFD in next drive! */
					if(ushGetCurrentECUParkingTime() >= cT_STANBY ) /* 04.05.2017 Darf AFDII eine AFDIII ablösen??? CRS_1211_130_284 Start AFDII ohne Klemmenwechsel &&  bGETucCalRequestState(cCAL_AUTO_ENABLE2) == TRUE)*/
					{
						if((bGetBitFahrzeugzustandFZZ(cKFZPARKING_START_AFD ) == FALSE) && (bGetBitFahrzeugzustandFZZ( cKL_15_EIN ) == TRUE)) /* CRS_1211_130_170 */		
						{
							SetState2FillingDetectionStateFD(cAFD_RUNNING2);/*CRS_1211_130_342 */
							if(bGETucCalRequestState(cCAL_AUTO_NEW_ID) == FALSE)
							{
								/*ALT SetState2FillingDetectionStateFD(cAFD_RUNNING2);CRS_1211_130_181 */
								SetBitCalRequestState2Ram(cCAL_AUTO_ENABLE2); /* setze AFDII bit wenn NUR cT_STANDBY erreicht, wenn Klemmenwechsel sitzt dieses Bit sowieso!!*/
							}
				
							ClearAbortReasonFD();	/*CRS_1211_130_181 */
#ifdef AVG_PRESS_ENABLED			
							ClearAvgPress4FD();
#endif
							//PUTucCalRequestState2Ram(FALSE); /* Clear all bits, CRS_1211_130_151 cCAL_AKTIV_AUTOMATIC cCAL_AKTIV_AUTOMATIC1 cCAL_AKTIV_AUTOMATIC2*/				
							SetBitFahrzeugzustandFZZ(cKFZPARKING_START_AFD ); /* set Look bit CRS_1211_130_170 */					
							ClearBitCalRequestState(cCAL_MANUAL_FINISH |cCAL_AUTO_NEW_ID | cCAL_AUTO_ENABLE3); /*CRS_1211_130_184*/
							//ClearBitCalRequestState(cCAL_AUTO_ENABLE3);
							SetBitCalRequestState2Ram(cCAL_AUTO_ACTIV);
							//ClearBitCalRequestState(cCAL_MANUAL_FINISH);/*NEW State 4 AFD is running*/
							//CRS_1211_130_249 PUTucCalRequestState2Nvm(); /* CRS_1211_130_243 CalRequestState into Nvm if Kl15off and softreset*/				
							
							InitRePosStorage4FD(); /*CRS_1211_130_373*/
							PUTucOnceCheckMissingRE4FD(0);
							//if(ushGetCurrentECUParkingTime() >= cT_STANBY )  entfällt wegen umbau Thema "Next Drive"
							//{ 
							PUTucNoCheckPmin4StopFD(ucCheckLOW_PRESS_ReState()); /* CRS_1211_130_325 HW or PminFL=0x01, FR=0x02, HL=0x04, HR=0x08 --> 0x0C=HL+HR in ucNoCheckPmin4StopAFD spez. Bits 4 HW+ Pmin*/
							//}

							//PUTucCalNotAckState2Ram(cCAL_VALID); /*clear all bits in CalNotAck state*/
							ClearCalNotAckState();
							//CRS_1211_130_249 PUTucCalNotAckState2Nvm(); /*CRS_1211_130_240*/
							ClearAllReCnt4FD(); /* ucRErecCounter4FDXX=0 ucTmp4CalXX=0; ReCounter4CalVL CRS_1211_130_058*/  
							ClearFDcheckP2PosOk();     /*CRS_1211_130_336*/   
					
							ClearBitBetriebszustandBZ(cCAL_FINISH);
							/*CRS_1211_130_322 ClearBitBetriebszustandBZ(cCAL_AFD_PLAUSI_ERROR);conseve HMI unplausible message! Clear Bit 4  "Filling not detected" (Filling detection flow chart 5.2) */	
							SetBitBetriebszustandBZ(cCAL_REQUEST);

							for (ucTmp = 0; ucTmp < cAnzRad; ucTmp++) /*CLEAR cRadPosVL ...cRadPosHR*/
							{
								PUTucIdCalPressure(FALSE,ucTmp); /*clear pressure ID for DP_STABI check  spezifisch*/
								PUTscIdCalTemperatur(FALSE,ucTmp); /*clear temperature ID spezifisch*/
							}

							PUTushFDtimeout(cFD_TIME_OUT); /*CRS_1211_130_335  */
							PUTushSupervisoryTimerFD(cFD_TIME_OUT);/*CRS_1211_130_335  */

							PUTucFDtimerStop(FALSE); /*CRS_1211_130_337  */
							PUTushZomTioFreeze(0);
						}
					}
					else
					{
						if(((bGetBitBetriebszustandBZ(cZO_FINISH) == TRUE ) || (bGetBitBetriebszustandBZ(cZO_TIMEOUT) == TRUE)) && (GETucFDcheckP2PosOk() >= 1)) /*CRS_1211_130_336*/ 
						{
							
							//CRS_1211_130_383 if((bGetBitBetriebszustandBZ(cZO_FINISH) == TRUE ) && (bGetBitBetriebszustandBZ(cZO_TIMEOUT) != TRUE))
							//{							

								if(GETucFDcheckP2PosOk() == 1)
								{
									/* Prüfe ob alle ID's deren Positionen, Kalibrier Druck- und Temperaturwerte aktuell sind! */
									if(FD_CheckFDpos2ZomPosAfterZOfinish() != FALSE) /*CRS_1211_130_336*/
									{
										//ReplayLastREvalue2Walgo();
										//DelWarnOfId(4); 
										PUTucFDcheckP2PosOk(0x0F); /*CRS_1211_130_383 REF Reifendruckwerte Abgleich im NVM abwarten*/
										/* Achtung! AFD   MFD läuft sowieso bis zum ZO_Finish oder ZO_Timeout*/
									}
									else
									{
										ClearFDcheckP2PosOk(); /*CRS_1211_130_336*/
									}
								}
								else
								{
									if(GETucFDcheckP2PosOk() == 0x0E)
									{
										ReplayLastREvalue2Walgo(); /*CRS_1211_130_383*/
										ReStart4SetValue2ActivationMemAFD(); 
										ClearFDcheckP2PosOk(); /*CRS_1211_130_336*/
									}
									else
									{
										DECucFDcheckP2PosOk();
									}
								}
							//}
						}	
					}
				}
			}
			else
			{
				ClearBitCalNotAckState(cCAL_FBM_ACTIV_NAK); /*CRS_1211_130_344*/
				FD_UpdateComparePressureAfterFBM();/*CRS_1211_130_344*/
			}
		}
		else
		{
			/* CRS_1211_130_348 MFD aktiv, Kfz fährt, jetzt Softreset! prüfe ob die MFD wirklich läuft??? siehe OIL#1214, wenn nicht starte MFD ohne Lampe!*/
			if((GETushFDtimeout()  == 0 ) && (bGetBitBetriebszustandBZ(cCAL_REQUEST) == TRUE) && (bGETucCalRequestState(cCAL_AUTO_ENABLE2) == TRUE) )/* */
			{
				FillingDetectionMFD(FALSE);	/* CRS_1211_130_348 KEIN Ansteuern der Laompe mit 6= RESTART --> FALSE! */
			}
		}
	}
	else
	{
		FD_AfdStopp4PWP();
	}
}

/*************************************************************************************************
 * \brief routine start: AUTO Filling Detection Start Reason III  Restart of TPMS 
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] ucFastDelation (ucTxTrigger)=  Trigger Mode Bit for fast deflation
 * \param [out] none
 *
 * \return none 
 *
 *------------------------------------------------------------------------------------------------
 */
void FillingDetectionAFDIII(uint8 ucFastDeflation)
{
	uint8 ucTmp;

	if(Getui8ColPWPActive() == FALSE) /*CRS_1211_130_210 FALLbackMode activ?*/
	{
		if(  bGETucCalNotAckState(cCAL_FBM_ACTIV_NAK) == FALSE) /*CRS_1211_130_274 first return from FALLbackMode!!!*/
		{
			/*alt: if(ucTxTrigger == ucDpTxTriggerc) */
			/*ucDpTxTriggerc ==1 --> delta P für 30sec nach letzten delta P down or up*/
			if(ucFastDeflation == ucDpTxTriggerc) /* CRS_1211_130_158 delta p telegram , AFD enabled? and vehicle stationary ? */
			{
				if((GETucAutoFillDetectionOnOffOfRam() == TRUE) && (bGetBitFahrzeugzustandFZZ( cFAHRZEUG_FAEHRT ) == FALSE)) /*CRS_1211_130_210/ 162 / 163 */
				{
					if((bGETucCalRequestState(cCAL_MANUAL_ACTIV) == FALSE) && (bGETucCalRequestState(cCAL_AUTO_ENABLE3) == FALSE)) 
					{
						/*if(bGETucCalRequestState(cCAL_AUTO_ENABLE2) == FALSE) start reason2 high prio than start reason 3!!*/
						/*if((bGetBitFahrzeugzustandFZZ(cKFZPARKING_START_AFD) == FALSE) && (GETucCalNotAckStateOfRam() != cCAL_P_MIN_TIRE_NAK)) ADD cCAL_P_MIN_TIRE_NAK NO P_MIN_TIRE!!*/
						/*if(GETucCalNotAckStateOfRam() != cCAL_P_MIN_TIRE_NAK) CRS_1211_130_306  CRS_1211_130_288 ohne cKFZPARKING_START_AFD d.h. ohne Klemmemwechsel ABER im STAND!!*/	
						
						SetState2FillingDetectionStateFD(cAFD_RUNNING3);/*CRS_1211_130_181 */
						ClearAbortReasonFD();	/*CRS_1211_130_181 */
#ifdef AVG_PRESS_ENABLED			
						ClearAvgPress4FD();
#endif
						/*ClearPlausiFailureFD(); CRS_1211_130_322 Erst nach Gutprüfung der DP_LR und DP_ABS HMI PLAUSI löschen   CRS_1211_130_318 */
						
						PUTucOnceCheckMissingRE4FD(0);
						//SetBitCalRequestState2Ram(cCAL_AUTO_ACTIV);
						SetBitCalRequestState2Ram(cCAL_AUTO_ENABLE3 | cCAL_AUTO_ACTIV); /* AFD of TPMS (5.1.2) reason 3 */
						ClearBitCalRequestState(cCAL_MANUAL_FINISH | cCAL_AUTO_ENABLE2);/*NEW State 4 AFD is running*/
						//ClearBitCalRequestState(cCAL_AUTO_ENABLE2);/* 07.10.2016 AFDII wird bei Parkingtime>= 1140 gestartet*/
						//CRS_1211_130_249 PUTucCalRequestState2Nvm(); /* CRS_1211_130_243 CalRequestState into Nvm if Kl15off and softreset*/				
						ClearCalNotAckState(); /*--> Erprobg2017KW20:AFDIII=L/R Diff: -> CalNotAck=0x01 -> HMI= unplausibel! Erneut AFDIII --> HMI=plausible=FEHLER!!*/
						ClearAllReCnt4FD(); /* ucRErecCounter4FDXX=0 ucTmp4CalXX=0; ReCounter4CalVL CRS_1211_130_058*/  
						ClearFDcheckP2PosOk();     /*CRS_1211_130_336*/   
					
						ClearBitBetriebszustandBZ(cCAL_FINISH);
						/* CRS_1211_130_322 ClearBitBetriebszustandBZ(cCAL_AFD_PLAUSI_ERROR); Erst nach Gutprüfung der DP_LR und DP_ABS HMI PLAUSI löschen  CRS_1211_130_202) her AFD only!! */ 
						SetBitBetriebszustandBZ(cCAL_REQUEST);
			
						PUTucCnt4DP_FILL_DFL(0);
						PUTucCnt4DP_FILL_IFL(0);
						PUTucLockByt4DFL_LTS(0);
						for (ucTmp = 0; ucTmp < cAnzRad; ucTmp++) /*CLEAR cRadPosVL ...cRadPosHR*/
						{
							PUTucIdCalPressure(FALSE,ucTmp); /*clear pressure ID for DP_STABI check  spezifisch*/
							PUTscIdCalTemperatur(FALSE,ucTmp); /*clear temperature ID spezifisch*/
						}
						PUTushFDtimeout(cFD_TIME_OUT); /*CRS_1211_130_335  */
						PUTushSupervisoryTimerFD(cFD_TIME_OUT);/*CRS_1211_130_335  */
						PUTucFDtimerStop(FALSE); /*CRS_1211_130_337  */
					}
					else /* AFDIII ist schon aktiv*/
					{
						if(GetOneReCnt4FD() == TRUE) /* CRS_1211_130_217 Delta P erneut im Fahrzeug steht Zustand  NEUSTART der AFDIII */
						{
							
#ifdef AVG_PRESS_ENABLED			
							ClearAvgPress4FD();/*CRS_1211_130_366*/
#endif
							ClearAllReCnt4FD(); /* ucRErecCounter4FDXX=0 ucTmp4CalXX=0; ReCounter4CalVL CRS_1211_130_058*/  
							PUTucCnt4DP_FILL_DFL(0);
							PUTucCnt4DP_FILL_IFL(0);
							PUTucLockByt4DFL_LTS(0);
							for (ucTmp = 0; ucTmp < cAnzRad; ucTmp++) /*CLEAR cRadPosVL ...cRadPosHR*/
							{
								PUTucIdCalPressure(FALSE,ucTmp); /*clear pressure ID for DP_STABI check  spezifisch*/
								PUTscIdCalTemperatur(FALSE,ucTmp); /*clear temperature ID spezifisch*/
							}
							PUTushFDtimeout(cFD_TIME_OUT); /*CRS_1211_130_335  */
							PUTushSupervisoryTimerFD(cFD_TIME_OUT);/*CRS_1211_130_335  */
							PUTucFDtimerStop(FALSE); /*CRS_1211_130_337  */
						}
					}
				}
			}
			else/*CRS_1211_130_215 RE Receice counter stand still, check Kfz drive? enable fct 4 check fill pressure? Papenburg KW38in2016 WK-Problem!! */
			{
				/*Retriggert AFDIII but not refill pressure! --> countinue AFDIII !!!*/
				if((bGETucCalRequestState(cCAL_AUTO_ACTIV) == TRUE) && (bGETucCalRequestState(cCAL_AUTO_ENABLE2) == FALSE)) 
				{
					if((bGetBitFahrzeugzustandFZZ( cKFZFAEHRT_20KMH ) == TRUE ) && (bGETucCalRequestState(cCAL_AUTO_ENABLE3) == FALSE)) /* */
					{
						SetBitCalRequestState2Ram(cCAL_AUTO_ENABLE3); /* AFD of TPMS (5.1.2) reason 3 */
						//CRS_1211_130_249 PUTucCalRequestState2Nvm(); /* CRS_1211_130_243 CalRequestState into Nvm if Kl15off and softreset*/				
					}
				}
			}	

		}
		else /* CRS_1211_130_274 FBM zurückgesetzt, dann speichere die aktuellen P werte in Comparevalue!  */
		{
			ClearBitCalNotAckState(cCAL_FBM_ACTIV_NAK);
			FD_UpdateComparePressureAfterFBM();
		}

	}
	else
	{
		FD_AfdStopp4PWP();
	}
}
/*************************************************************************************************
 * \brief routine start: AUTO Filling Detection AFD Wheel electronic receiver at Pos VL of TPMS 
 * \CRS_1211_130_335
 * \Number of calls: 1 
 * \Call in Modul: CtApHufTPMSmgr "RCtApHufTPMSmgr_ReceiveTelData(void)"
 *-----------------------------------------------------------------------------------------------
 * \param [in] FD_HandleReceivedReRadPosVL4AFD( pressure, temperatur, colPosOfID, LTSmode)
 * \param [out] none
 *
 * \return none 
 *
 *------------------------------------------------------------------------------------------------
 */
void FD_HandleReceivedReRadPosVL4AFD(uint8 ucP,sint8 scT,uint8 ucColOfID, uint8 ucLTSmode) 
{
	
uint8 ucTmpPiso4Cal;
/* FD_HandleReceivedRE4AFD(cRadPosVL, ucLastTirePressure,scTireTemp,ucGetColOfID(&ulTelID); CRS_1211_130_335 */

#ifdef as_16BitP4Average /* CRS_1211_130_369 im Statistik Modul wird der Zähler ebenfalls erst bei "Fahrzeug fährt" inkrementiert*/
	if(bGetBitFahrzeugzustandFZZ( cKFZFAEHRT_20KMH ) == TRUE )
	{								
		INCucRErecCounter4FDVL(); /*CRS_1211_130_244 Nur bei Fahrt*/
	}
#endif

	//CRS_1211_130_358 ClearBitInNoCheckPmin4StopFD(cAfdPmin_FL);/*CRS_1211_130_325 Freigabe der Prüfung von P_MIN immediately */
	if(FD_CheckP4AFDstartReason2_3FA(ucP,GETucRErecCounter4FDVL(),scT,ucColOfID) == FALSE)	/*CRS_1211_130_305 cPMIN;cDP_AUTO;cCAL_RE30K2AMBIENT, DP_STABI	auch im Stand!*/
	{								
		PUTushFDtimeout(0); /*Abort filling detection 3,4,5,6,  for AFD without CalNAK!!! */
		PUTucFDtimerStop(TRUE); /*CRS_1211_130_337 Vorzeitiger FD Timeout*/
	}
	else
	{
		/************* VL: check DP_FILL now 2 wheels are inflated or deflated *******************/
		//if(GETucRErecCounter4FDVL() == 3) 
		if(GETucRErecCounter4FDVL() >= 3) /* CRS_1211_130_369 */
		{
			ucRePosStorageVL4FD=ucColOfID; /*CRS_1211_130_373*/
			ucTmpPiso4Cal= GetP4NewTempAtCAL(((uint8) GETuiStoragePaverege4CompareValue(ucColOfID)),GETscIdCalTemperatur(ucColOfID), GETscTref());/*CRS_1211_130_298*/
			if(ucTmpPiso4Cal >  GETucPosComparePressure(cRadPosVL)) /*Relativ*/
			{
				if((ucTmpPiso4Cal - GETucPosComparePressure(cRadPosVL)) >= cDP_FILL) /* CRS_1211_130_194 >=!!  CurrentP- LastP > 200mbar --> inflated IFL*/
				{
				
					if(GETucCnt4DP_FILL_IFLloggedFL() == FALSE)/*CRS_1211_130_371*/
					{
						INCucCnt4DP_FILL_IFL();
						PUTucCnt4DP_FILL_IFLloggedFL();/* cDP_FILL_FL add 0x10 Ident4FL */
					}
					//INCucCnt4DP_FILL_IFL();
					//PUTucCnt4DP_FILL_IFLloggedFL();	/* cDP_FILL_FL add 0x10 Ident4FL ! CRS_1211_130_220  */ 
				}
			}
			else
			{
				if((GETucPosComparePressure(cRadPosVL) - ucTmpPiso4Cal) >= cDP_FILL)/*CRS_1211_130_194 >=!! LastP-CurrentP > 200mbar DP_FILL --> deflated DFL*/
				{
					if((ucLTSmode == cLTS30Days) && (GETucCnt4DP_FILL_DFL4LTSlogged() == FALSE)) /*CRS_1211_130_245*/
					{
						PUTucCnt4DP_FILL_DFL4LTSlogged();/* |= 0x80;*/
					}
					
					if(GETucCnt4DP_FILL_DFLloggedFL() == FALSE)/*CRS_1211_130_371 |= 0x10;*/
					{
						INCucCnt4DP_FILL_DFL();
						PUTucCnt4DP_FILL_DFLloggedFL();
					}
				}
			}
		}
	}
}

/*************************************************************************************************
 * \brief routine start: AUTO Filling Detection AFD Wheel electronic receiver at Pos VR of TPMS 
 *  \CRS_1211_130_335
 * \Number of calls: 1 
 * \Call in Modul: CtApHufTPMSmgr "RCtApHufTPMSmgr_ReceiveTelData(void)"
 *-----------------------------------------------------------------------------------------------
 * \param [in] FD_HandleReceivedReRadPosVR4AFD( pressure, temperatur, colPosOfID, LTSmode)
 * \param [out] none
 *
 * \return none 
 *
 *------------------------------------------------------------------------------------------------
 */
void FD_HandleReceivedReRadPosVR4AFD(uint8 ucP,sint8 scT,uint8 ucColOfID, uint8 ucLTSmode) 
{
	
uint8 ucTmpPiso4Cal;

#ifdef as_16BitP4Average /*CRS_1211_130_369 im Statistik Modul wird der Zähler ebenfalls erst bei "Fahrzeug fährt" inkrementiert*/
	if(bGetBitFahrzeugzustandFZZ( cKFZFAEHRT_20KMH ) == TRUE )
	{								
		INCucRErecCounter4FDVR(); /*CRS_1211_130_244 Nur bei Fahrt*/
	}
#endif 

	//CRS_1211_130_358 ClearBitInNoCheckPmin4StopFD(cAfdPmin_FR);/*CRS_1211_130_325 Freigabe der Prüfung von P_MIN immediately */
	if(FD_CheckP4AFDstartReason2_3FA(ucP,GETucRErecCounter4FDVR(),scT,ucColOfID) == FALSE)	/*CRS_1211_130_305 cPMIN;cDP_AUTO;cCAL_RE30K2AMBIENT, DP_STABI	auch im Stand!*/
	{								
		PUTushFDtimeout(0); /*Abort filling detection 3,4,5,6,  for AFD without CalNAK!!! */
		PUTucFDtimerStop(TRUE); /*CRS_1211_130_337 Vorzeitiger FD Timeout*/
	}
	else
	{
		/************* VR: check DP_FILL now 2 wheels are inflated or deflated *******************/
		//if(GETucRErecCounter4FDVR() == 3)
		if(GETucRErecCounter4FDVR() >= 3) /*CRS_1211_130_369*/
		{
			ucRePosStorageVR4FD=ucColOfID; /*CRS_1211_130_373*/			
			ucTmpPiso4Cal= GetP4NewTempAtCAL(((uint8) GETuiStoragePaverege4CompareValue(ucColOfID)),GETscIdCalTemperatur(ucColOfID), GETscTref());/*CRS_1211_130_298*/
			if(ucTmpPiso4Cal >  GETucPosComparePressure(cRadPosVR)) /*Relativ*/
			{
				if((ucTmpPiso4Cal - GETucPosComparePressure(cRadPosVR)) >= cDP_FILL) /* CRS_1211_130_194 >=!!  CurrentP- LastP > 200mbar --> inflated IFL*/
				{
					if(GETucCnt4DP_FILL_IFLloggedFR() == FALSE)
					{
						INCucCnt4DP_FILL_IFL();
						PUTucCnt4DP_FILL_IFLloggedFR();	/* cDP_FILL_FR add 0x20 Ident4FR */ 
					}
					//INCucCnt4DP_FILL_IFL();
					//PUTucCnt4DP_FILL_IFLloggedFR();	/* cDP_FILL_FR add 0x20 Ident4FR ! CRS_1211_130_220  */ 
				}
			}
			else
			{
				if((GETucPosComparePressure(cRadPosVR) - ucTmpPiso4Cal) >= cDP_FILL)/*CRS_1211_130_194 >=!! LastP-CurrentP > 200mbar --> deflated DFL*/
				{
					if((ucLTSmode == cLTS30Days) && (GETucCnt4DP_FILL_DFL4LTSlogged() == FALSE)) /*CRS_1211_130_245*/
					{
						PUTucCnt4DP_FILL_DFL4LTSlogged();/* |= 0x80;*/
					}
					if(GETucCnt4DP_FILL_DFLloggedFR() == FALSE)/*CRS_1211_130_371 |= 0x20;*/
					{
						INCucCnt4DP_FILL_DFL();
						PUTucCnt4DP_FILL_DFLloggedFR();
					}
				}
			}
		}
	}
}

/*************************************************************************************************
 * \brief routine start: AUTO Filling Detection AFD Wheel electronic receiver at Pos HL of TPMS 
 * \CRS_1211_130_335
 * \Number of calls: 1 
 * \Call in Modul: CtApHufTPMSmgr "RCtApHufTPMSmgr_ReceiveTelData(void)"
 *-----------------------------------------------------------------------------------------------
 * \param [in] FD_HandleReceivedReRadPosHL4AFD( pressure, temperatur, colPosOfID, LTSmode)
 * \param [out] none
 *
 * \return none 
 *
 *------------------------------------------------------------------------------------------------
 */
void FD_HandleReceivedReRadPosHL4AFD(uint8 ucP,sint8 scT,uint8 ucColOfID, uint8 ucLTSmode) 
{
	
uint8 ucTmpPiso4Cal;
/* FD_HandleReceivedRE4AFD(cRadPosVL, ucLastTirePressure,scTireTemp,ucGetColOfID(&ulTelID); CRS_1211_130_335 */

#ifdef as_16BitP4Average /*CRS_1211_130_369 im Statistik Modul wird der Zähler ebenfalls erst bei "Fahrzeug fährt" inkrementiert*/
	if(bGetBitFahrzeugzustandFZZ( cKFZFAEHRT_20KMH ) == TRUE )
	{								
		INCucRErecCounter4FDHL(); /*CRS_1211_130_244 Nur bei Fahrt*/
	}
#endif
	//CRS_1211_130_358 ClearBitInNoCheckPmin4StopFD(cAfdPmin_RL);/*CRS_1211_130_325 Freigabe der Prüfung von P_MIN immediately */
	if(FD_CheckP4AFDstartReason2_3RA(ucP,GETucRErecCounter4FDHL(),scT,ucColOfID) == FALSE)	/*CRS_1211_130_305 cPMIN;cDP_AUTO;cCAL_RE30K2AMBIENT, DP_STABI	auch im Stand!*/
	{								
		PUTushFDtimeout(0); /*Abort filling detection 3,4,5,6,  for AFD without CalNAK!!! */
		PUTucFDtimerStop(TRUE); /*CRS_1211_130_337 Vorzeitiger FD Timeout*/
	}
	else
	{
		/************* HL: check DP_FILL now 2 wheels are inflated or deflated *******************/
		//if(GETucRErecCounter4FDHL() == 3)
		if(GETucRErecCounter4FDHL() >= 3) /*CRS_1211_130_369*/
		{
			ucRePosStorageHL4FD=ucColOfID; /*CRS_1211_130_373*/			
			ucTmpPiso4Cal= GetP4NewTempAtCAL(((uint8) GETuiStoragePaverege4CompareValue(ucColOfID)),GETscIdCalTemperatur(ucColOfID), GETscTref());/*CRS_1211_130_298*/
			if(ucTmpPiso4Cal >  GETucPosComparePressure(cRadPosHL)) /*Relativ*/
			{
				if((ucTmpPiso4Cal - GETucPosComparePressure(cRadPosHL)) >= cDP_FILL) /* CRS_1211_130_194 >=!!  CurrentP- LastP > 200mbar --> inflated IFL*/
				{
					if(GETucCnt4DP_FILL_IFLloggedRL() == FALSE)/*CRS_1211_130_371*/
					{
						INCucCnt4DP_FILL_IFL();
						PUTucCnt4DP_FILL_IFLloggedRL();	/* cDP_FILL_RL add 0x40 Ident4RL */ 
					}					
					//INCucCnt4DP_FILL_IFL();
					//PUTucCnt4DP_FILL_IFLloggedRL();	/* cDP_FILL_RL add 0x40 Ident4RL ! CRS_1211_130_220  */ 
				}
			}
			else
			{
				if((GETucPosComparePressure(cRadPosHL) - ucTmpPiso4Cal) >= cDP_FILL)/*CRS_1211_130_194 >=!! LastP-CurrentP > 200mbar --> deflated DFL*/
				{
					if((ucLTSmode == cLTS30Days) && (GETucCnt4DP_FILL_DFL4LTSlogged() == FALSE)) /*CRS_1211_130_245*/
					{
						PUTucCnt4DP_FILL_DFL4LTSlogged();/* |= 0x80;*/
					}
					if(GETucCnt4DP_FILL_DFLloggedRL() == FALSE)/*CRS_1211_130_371*/
					{
						INCucCnt4DP_FILL_DFL();
						PUTucCnt4DP_FILL_DFLloggedRL();/*CRS_1211_130_371 |= 0x40;*/
					}
				}
			}
		}
	}
}
/*************************************************************************************************
 * \brief routine start: AUTO Filling Detection AFD Wheel electronic receiver at Pos HR of TPMS 
 * \CRS_1211_130_335
 * \Number of calls: 1 
 * \Call in Modul: CtApHufTPMSmgr "RCtApHufTPMSmgr_ReceiveTelData(void)"
 *-----------------------------------------------------------------------------------------------
 * \param [in] FD_HandleReceivedReRadPosHL4AFD( pressure, temperatur, colPosOfID, LTSmode)
 * \param [out] none
 *
 * \return none 
 *
 *------------------------------------------------------------------------------------------------
 */
void FD_HandleReceivedReRadPosHR4AFD(uint8 ucP,sint8 scT,uint8 ucColOfID, uint8 ucLTSmode) 
{
	
uint8 ucTmpPiso4Cal;

#ifdef as_16BitP4Average /*CRS_1211_130_369 im Statistik Modul wird der Zähler ebenfalls erst bei "Fahrzeug fährt" inkrementiert*/
	if(bGetBitFahrzeugzustandFZZ( cKFZFAEHRT_20KMH ) == TRUE )
	{								
		INCucRErecCounter4FDHR(); /*CRS_1211_130_244 Nur bei Fahrt*/
	}
#endif
	//CRS_1211_130_358 ClearBitInNoCheckPmin4StopFD(cAfdPmin_RR);/*CRS_1211_130_325 Freigabe der Prüfung von P_MIN immediately */
	if(FD_CheckP4AFDstartReason2_3RA(ucP,GETucRErecCounter4FDHR(),scT,ucColOfID) == FALSE)	/*CRS_1211_130_305 cPMIN;cDP_AUTO;cCAL_RE30K2AMBIENT, DP_STABI	auch im Stand!*/
	{								
		PUTushFDtimeout(0); /*Abort filling detection 3,4,5,6,  for AFD without CalNAK!!! */
		PUTucFDtimerStop(TRUE); /*CRS_1211_130_337 Vorzeitiger FD Timeout*/
	}
	else
	{
		/************* HL: check DP_FILL now 2 wheels are inflated or deflated *******************/
		//if(GETucRErecCounter4FDHR() == 3)
		if(GETucRErecCounter4FDHR() >= 3) /* CRS_1211_130_369*/
		{
			ucRePosStorageHR4FD=ucColOfID; /*CRS_1211_130_373*/			
			ucTmpPiso4Cal= GetP4NewTempAtCAL(((uint8) GETuiStoragePaverege4CompareValue(ucColOfID)),GETscIdCalTemperatur(ucColOfID), GETscTref());/*CRS_1211_130_298*/
			if(ucTmpPiso4Cal >  GETucPosComparePressure(cRadPosHR)) /*Relativ*/
			{
				if((ucTmpPiso4Cal - GETucPosComparePressure(cRadPosHR)) >= cDP_FILL) /* CRS_1211_130_194 >=!!  CurrentP- LastP > 200mbar --> inflated IFL*/
				{
					if(GETucCnt4DP_FILL_IFLloggedRR() == FALSE)/*CRS_1211_130_371*/
					{
						INCucCnt4DP_FILL_IFL();
						PUTucCnt4DP_FILL_IFLloggedRR();	/* cDP_FILL_RR add 0x80 Ident4RR */ 
					}
					//INCucCnt4DP_FILL_IFL();
					//PUTucCnt4DP_FILL_IFLloggedRR();	/* cDP_FILL_RR add 0x80 Ident4RR ! CRS_1211_130_220  */ 
				}
			}
			else
			{
				if((GETucPosComparePressure(cRadPosHR) - ucTmpPiso4Cal) >= cDP_FILL)/*CRS_1211_130_194 >=!! LastP-CurrentP > 200mbar --> deflated DFL*/
				{
					if((ucLTSmode == cLTS30Days) && (GETucCnt4DP_FILL_DFL4LTSlogged() == FALSE)) /*CRS_1211_130_245*/
					{
						PUTucCnt4DP_FILL_DFL4LTSlogged();/* |= 0x80;*/
					}
					if(GETucCnt4DP_FILL_DFLloggedRR() == FALSE)/*CRS_1211_130_371*/
					{
						INCucCnt4DP_FILL_DFL();
						PUTucCnt4DP_FILL_DFLloggedRR();/*CRS_1211_130_371 |= 0x80;*/
					}
				}
			}
		}
	}
}


/************************************************************************************************
 * \brief routine start: Abort Filling Detection MANUAL and AUTO : P_MIN_TIRE, Missing Sensor  
 *
 *-----------------------------------------------------------------------------------------------
 * \CRS_1211_130_161 filter pal telegramm , only 1 telegramm per frame is allowed can be disabled!
 * \param [in]  1.) cCAL_P_MIN_TIRE_NAK=0x80
 * \param [in]  2.) cCAL_RE_MISSING_NAK=0x40 wenn Timeout ungleich 0 auch Fahrzeug steht und Timeout=cFD_TIME_OUT! Und auch wenn Timeout=0!
 * \param [in]  3.) cCAL_AUTO_NEW_ID=8! --> Timeout +new ID 
 * \param [in]  4.) cCAL_ABORT_REASON_2_3=0! --> Timeout 
 * \param [out] none
 *
 * \return none
 *
 *------------------------------------------------------------------------------------------------
 */
void FD_AbortFillingDetection(uint8 ucNotAckState) /*1. Pmin AUCH für (ucGetSensorState(ucGetColOfID(&ulTelID)) != SENSOR_STATE_MISSING))*/
{
	/* allways FD timeout=0*/
	if((bGetBitBetriebszustandBZ(cCAL_FINISH) != TRUE)) /*echter timeout=0: regular, KL.30 a.s.o. and calibration empty!*/
	{

		SetBitBetriebszustandBZ(cCAL_FINISH);
		ClearBitBetriebszustandBZ(cCAL_REQUEST); /*delete request bit 4 next calibration*/

   /***** MFD ?09.02.2018 CRS_1211_130 --> OIL#1310 * **************************************************************************************/	 
		// am09.02.2018 entfernt -->OIL#1310
		//if(bGETucCalRequestState(cCAL_MANUAL_ACTIV)) 
		//{
			/* check cal pressure value in ZOM number! possibly refill old pressure and temperatur value from RadPOS 2 ZOMPOS */
      /* knowhow: ucIdCalPressure and scIdCalTemperatur() are cleared if start the manual filling detection!*/
      /*CRS_1211_130_069*/
		//ClearBitCalRequestState(cCAL_MANUAL_ACTIV);
		//	SetBitCalRequestState2Ram(cCAL_MANUAL_FINISH);
		//}
		if(ucNotAckState == cCAL_P_MIN_TIRE_NAK)
		{
			//SetState2AbortReasonFD(cFD_P_MIN_TIRE_AFD); /*entfällt! CRS_1211_130_206  CRS_1211_130_187*/	
			SetState2AbortReasonFD(cFD_P_MIN_TIRE); /*CRS_1211_130_255 CRS_1211_130_206 CRS_1211_130_187*/
			ClearKplNoCheckPmin4StopFD();/*CRS_1211_130_358*/
			SetState2FillingDetectionStateFD(cFILLING_DETECT_ABORTED); /* CRS_1211_130_181 / 198*/	
			SetBitCalNotAckState2Ram(cCAL_P_MIN_TIRE_NAK); /*NEU für FBM <-> FD  P_MIN_TIRE  1,5bar! CalNotAck*/											
		}
		else
		{
			if(ucNotAckState != cCAL_AUTO_NEW_ID)
			{
				ClearBitCalRequestState(cCAL_AUTO_NEW_ID); 
			}
		}
	}

	if(ucNotAckState == cCAL_RE_MISSING_NAK)
	{
		SetState2AbortReasonFD(cFD_MISSING_SENSOR); /*CRS_1211_130_187*/	
		SetState2FillingDetectionStateFD(cFILLING_DETECT_ABORTED); /* CRS_1211_130_181 / 198*/
	}

	if((ucNotAckState == cCAL_ABORT_REASON_2_3) && (Get_FD_ABORT_REASON() == FALSE)) /* FD_ABORT_REASON has already set e.g. STABI*/
	{
		/*****  CRS_1211_130_335  Hier Einbau der AFD echte FD Timeout behandlung **************************************************************/	
		/*1. Lade die ID spezifischen eingesammelten P Mittelwerte, den dazugehörigen ID spezifischen  Empfangszähler*/
		/*2. Prüfung cPMIN;cDP_AUTO;cCAL_RE30K2AMBIENT, DP_STABI	auch im Stand! Achtung! Mit dem zuletzt empfangenen P Wert*/
		/*3. check DP_FILL now 2 wheels are inflated or deflated Achtung! Vor dieser Prüfung Bits für infalted und deflated löschen!*/
		/*4. FD_Check3ReAndUpdatePifWarnLampOnOffDefOrInf2Re4FinishedAFD() */ 

		if((FD_TimeoutHandle4AFD() == TRUE) && (bGETucCalRequestState(cCAL_AUTO_ACTIV)))
		{
			FD_Check3ReAndUpdatePifWarnLampOnOffDefOrInf2Re4FinishedAFD();
		}
		else
		{
			/* AUCH MFD mit OIL#1310 vom 09.02.2018 CRS_1211_130_367 */
			SetState2AbortReasonFD(cFD_TIMEOUT); /*CRS_1211_130_207 CRS_1211_130_198 */	
			SetState2FillingDetectionStateFD(cFILLING_DETECT_ABORTED); /* CRS_1211_130_181 / 198*/				
		}


	}
  /*allways*/
 /***** MFD ? 09.02.2018 CRS_1211_130 --> OIL#1310 **********************************************************************************************/	 
	if(bGETucCalRequestState(cCAL_MANUAL_ACTIV)) /* manual calibration aktiv? */
	{
		/* check cal pressure value in ZOM number! possibly refill old pressure and temperatur value from RadPOS 2 ZOMPOS */
    /* knowhow: ucIdCalPressure and scIdCalTemperatur() are cleared if start the manual filling detection!*/
		/*CRS_1211_130_069*/
		ClearBitCalRequestState(cCAL_MANUAL_ACTIV);
		SetBitCalRequestState2Ram(cCAL_MANUAL_FINISH);
	}

	/***** AFD ?  CRS_1211_130_339 + 335 **********************************************************************************************************/	
	if(bGETucCalRequestState(cCAL_AUTO_ACTIV)) /* AFD activ: ABORT AUTO FILLING DETECTION do nothing ACHTUNG bei NEW ID sitzt kein "cCAL_AUTO_ACTIV" */
	{
		ClearBitCalRequestState(cCAL_AUTO_ENABLE3 | cCAL_AUTO_ENABLE2 | cCAL_AUTO_ACTIV);
		//ClearBitCalRequestState(cCAL_AUTO_ENABLE2);
		//ClearBitCalRequestState(cCAL_AUTO_ENABLE3);
	}
	/***** MFD + AFD ***********************************************************************************************************************/		
}

#ifdef as_16bitP4Average
/************************************************************************************************
 * \brief routine start: Filling Detection MANUAL: pressure average calulation  
 * 116= 2,9bar abs  in ucPcalMinVaAbsCodOfRam pressure absolut!!!
 *  24.01.2017 NEU CRS_1211_130_268 76= 1,9bar relativ  in ucPcalMinVaAbsCodOfRam pressure relativ!!!
 *-----------------------------------------------------------------------------------------------
 * \CRS_1211_130_161 filter pal telegramm , only 1 telegramm per frame is allowed can be disabled!
 * \param [in] Wheel Position (ucRadPos),(ucREcnt4FD)(ucGetColOfID(&ulTelID))
 * \param [out] none
 *
 * \return none
 *
 *------------------------------------------------------------------------------------------------
 */

void FD_CalcAverageP4MFD(uint8 ucREcnt4FD,uint8 ucLastReceivedP, uint8 ucColOfID)
{
	uint16 uiPaverage;
	uint16 uiPaverege4CompareValue; /*CRS_1211_130_205*/

	if(ucREcnt4FD != 0)  /* check ucREcnt4FD 4 division by zero! OIL#1165 - 69 */
	{
		if(ucREcnt4FD == 1) /*CRS_1211_130_079 average of each 3 wheel*/
		{	
			/*CRS_1211_130_070 + CRS_1211_130_070 load pressure each TeLRec reason: check pressure/temp precondition  */
			uiPaverage=(uint16)(ucLastReceivedP); /*CRS_1211_130_268 (ucLastReceivedP)  + TirePressureDiffAbsRel)*/
			uiPaverege4CompareValue=(uint16)(ucLastReceivedP); /*relative pressure 4 compare value CRS_1211_130_205*/

			PUTucIdCalPressure(uiPaverage,ucColOfID); /*CRS_1211_130_268 jetzt IdCalP relativ Werte*/
			PUTuiStoragePaverege4CompareValue(uiPaverege4CompareValue,ucColOfID); /* CRS_1211_130_263 P relativ*/
		}
		else
		{
			if(ucREcnt4FD < 250)  /* limit for ucREcnt4FD --> overflow! OIL#1165 - 69 */
			{
				uiPaverage=(uint16)(GETucIdCalPressure(ucColOfID) * (ucREcnt4FD-1));
				uiPaverege4CompareValue=(GETuiStoragePaverege4CompareValue(ucColOfID) * (ucREcnt4FD-1)); /*CRS_1211_130_263*/

				uiPaverage=(uint16)(ucLastReceivedP + uiPaverage ); /*CRS_1211_130_268 (ucLastReceivedP + TirePressureDiffAbsRel) + uiPaverage)*/
				uiPaverege4CompareValue=((uint16)(ucLastReceivedP) + uiPaverege4CompareValue ); 

				PUTucIdCalPressure((uiPaverage/ucREcnt4FD),ucColOfID); /* CRS_1211_130_268 neu Prelativ , alt Pabsolut */
				PUTuiStoragePaverege4CompareValue((uiPaverege4CompareValue/ucREcnt4FD),ucColOfID); /*CRS_1211_130_263 P relativ*/		
			}
		}
	}
}

#endif

/************************************************************************************************
 * \brief routine start: Filling Detection AUTO(AFD): Check pressure 4 criteria in Front Axis(FA),
 * \AFD: ucCalRequestState: cCAL_AUTO_ACTIV=1 and Kfz no drive BUT receive WE!   
 * \ucREcnt4FD>0 ERST bei Fahrzeug fährt!!
 *-----------------------------------------------------------------------------------------------
 * \
 * \param [in] ucCurrentPressure (CRS_1211_130_268 relativ), RE Counter value, Tiretemperature , ucGetColOfID(&ulTelID) Wheel Position 
 * \param [out] none
 *
 * \return none
 *
 *------------------------------------------------------------------------------------------------
 *  ||	(ucCurrentPressure < (GETucPosComparePressure(ucRadPos) - cDP_STABI)))	  CRS_1211_130_319 DP_STABI Sonderbehandlung	
 *------------------------------------------------------------------------------------------------		 
*/
uint8 FD_CheckP4AFDstartReason2_3FA( uint8 ucCurrentPressure,uint8 ucREcnt4FD, sint8 scCurrentTireTemp, uint8 ucColOfID)
{
	uint8 ucRtn=TRUE;
#ifdef as_16BitP4Average /*CRS_1211_130_369*/
	uint16 uiPaverage;
	uint16 uiPaverege4CompareValue;
#endif

	if(( ucCurrentPressure < GETucMinWarnThresholdOfRam())						/*CRS_1211_130_268 NEU 1,5bar ALT: default 2,5bar-1bar P_MIN_TIRE CalNotAck*/
	|| (scCurrentTireTemp > GETscOutdoorTemperatureFZZ() + 30)																														/*actual RE_p < Pmin or RE_temp<Tout+30K*/              
	|| (ucCurrentPressure < (GETucPcalMinVaRelativCodOfRam() - cDP_AUTO)))	/*CRS_1211_130_268 NEU 1,9bar check Nr.3 CRS_1211_130_067 default 2,9bar-1bar-0,2bar P_MIN_X CalNotAck*/
	{
			if(GETucCalNotAckStateOfRam() == cCAL_VALID) /* CRS_1211_130_262 CalNotAckState empty??*/
		{

			if (ucCurrentPressure < GETucMinWarnThresholdOfRam()) /* CRS_1211_130_268 NEU 1,5bar ALT: logical data PAL: P_MIN_TIRE 2,5bar!*/
			{
				SetBitCalNotAckState2Ram(cCAL_P_MIN_TIRE_NAK); /*reason 2  P_MIN_TIRE 2,5bar! CalNotAck*/
				SetState2AbortReasonFD(cFD_P_MIN_TIRE); /* CRS_1211_130_212 entfällt CRS_1211_130_206 CRS_1211_130_181*/

				/*SetState2PlausiFailureFD(cFD_MINIMUM_PRESSURE);  Hier AFD, keine Eintrag für MFD Plausi Check CRS_1211_130_230*/
			}
			else
			{
				if ( ucCurrentPressure < (GETucPcalMinVaRelativCodOfRam() - cDP_AUTO)) /* CRS_1211_130_268 NEU 1,5bar ALT: CRS_1211_130_067 logical data PAL: P_MIN_TIRE_4CAL  2,9bar!*/
				{
					/* not for AFD!!!CRS_1211_130_272 SetBitCalNotAckState2Ram(cCAL_P_MIN_X_MINUS_DP_MANUAL); AFD reason 2  P_MIN_TIRE_4CAL  2,9bar! CalNotAck*/
					SetState2AbortReasonFD(cFD_DP_AUTO); /*2 CRS_1211_130_181 */
				}
				else
				{
					if(scCurrentTireTemp > (GETscOutdoorTemperatureFZZ() + 30))
					{
						SetBitCalNotAckState2Ram(cCAL_RE30K2AMBIENT); /*reason 4 CalNotAck*/
						SetState2AbortReasonFD(cFD_TIRE2HOT); /*3 CRS_1211_130_181*/
					}
				}
			}
			ucRtn=FALSE; /*Abort filling detection 3,4,5,6,*/
			SetState2FillingDetectionStateFD(cFILLING_DETECT_ABORTED); /*New tire pressure are not plausibl CRS_1211_130_181*/
			ClearPlausiFailureFD(); /*CRS_1211_130_277 _320*/
		}
	}
 	else
	{
		if(ucREcnt4FD == 1) /* 1. RE Telegramm bei Fahrzeug fährt */
		{							
			
			PUTucDpStabiPressure(ucCurrentPressure,ucColOfID); /* CRS_1211_130_319 DP_STABI Sonderbehandlung: Referenzdruck ucREcnt4FD =1 -> Fahrzeug fährt!*/
#ifdef as_16BitP4Average /*CRS_1211_130_369*/
			PUTucIdCalPressure(ucCurrentPressure,ucColOfID); /*CRS_1211_130_310*/
			PUTuiStoragePaverege4CompareValue(ucCurrentPressure,ucColOfID); 
			PUTscIdCalTemperatur(scCurrentTireTemp,ucColOfID);	/*CRS_1211_130_173 Storage current pressure for CHECK DP_STAPI (100mbar) and DP_Fill*/
#endif
		}
		else
		{
			if(ucREcnt4FD != 0) /*CRS_1211_130_316*/
			{
				
				if(ucREcnt4FD == 0xFF) /*CRS_1211_130_335 KEIN EMPFANG!*/
				{
					if(ucCurrentPressure < (GETucDpStabiPressure(ucColOfID) - cDP_STABI))  /* CRS_1211_130_319 DP_STABI Sonderbehandlung: Referenzdruck ucREcnt4FD =1 -> Fahrzeug fährt!*/
					{
						SetBitCalNotAckState2Ram(cCAL_DP_STABI_NAK ); /* CRS_1211_130_166 reason DP_STABI-> CalNotAck*/	
						SetState2AbortReasonFD(cFD_DP_STABI); /*4 CRS_1211_130_181*/	
						SetState2FillingDetectionStateFD(cFILLING_DETECT_ABORTED); /*New tire pressure are not plausibl CRS_1211_130_181*/
						ClearPlausiFailureFD(); /*CRS_1211_130_277*/
						ucRtn=FALSE; /*Abort filling detection 3,4,5,6,*/
					}
				}
				else
				{
#ifdef as_16BitP4Average /*CRS_1211_130_369*/
					uiPaverage=(uint16)(GETucIdCalPressure(ucColOfID) * (ucREcnt4FD-1));
					uiPaverege4CompareValue=(GETuiStoragePaverege4CompareValue(ucColOfID) * (ucREcnt4FD-1)); 

					uiPaverage=(uint16)(ucCurrentPressure + uiPaverage ); 
					uiPaverege4CompareValue=((uint16)(ucCurrentPressure) + uiPaverege4CompareValue ); 

					PUTucIdCalPressure((uiPaverage/ucREcnt4FD),ucColOfID); /* CRS_1211_130_268 neu Prelativ */
					PUTuiStoragePaverege4CompareValue((uiPaverege4CompareValue/ucREcnt4FD),ucColOfID); /*CRS_1211_130_263 P relativ*/		
#endif

					if(ucCurrentPressure < (GETucDpStabiPressure(ucColOfID) - cDP_STABI))  /* CRS_1211_130_319 DP_STABI Sonderbehandlung: Referenzdruck ucREcnt4FD =1 -> Fahrzeug fährt!*/
					{
						SetBitCalNotAckState2Ram(cCAL_DP_STABI_NAK ); /* CRS_1211_130_166 reason DP_STABI-> CalNotAck*/	
						SetState2AbortReasonFD(cFD_DP_STABI); /*4 CRS_1211_130_181*/	
						SetState2FillingDetectionStateFD(cFILLING_DETECT_ABORTED); /*New tire pressure are not plausibl CRS_1211_130_181*/
						ClearPlausiFailureFD(); /*CRS_1211_130_277*/
						ucRtn=FALSE; /*Abort filling detection 3,4,5,6,*/
					}
				}
			}
		}
	}
	return ucRtn;
}

/************************************************************************************************
 * \brief routine start: Filling Detection AUTO(AFD): Check pressure 4 criteria in Rear Axis(RA),
 * \AFD: ucCalRequestState:cCAL_AUTO_ACTIV=1 and Kfz no drive BUT receive WE!  
 * \ucREcnt4FD>0 ERST bei Fahrzeug fährt!!
 *-----------------------------------------------------------------------------------------------
 * \
 * \param [in] ucCurrentPressure (CRS_1211_130_268 relativ), RE Counter value, Tiretemperature , ucGetColOfID(&ulTelID) Wheel Position 
 * \param [out] none
 *
 * \return none
 *------------------------------------------------------------------------------------------------
 *  ||	(ucCurrentPressure < (GETucPosComparePressure(ucRadPos) - cDP_STABI)))	  CRS_1211_130_319 DP_STABI Sonderbehandlung	
 *------------------------------------------------------------------------------------------------
 */
uint8 FD_CheckP4AFDstartReason2_3RA( uint8 ucCurrentPressure,uint8 ucREcnt4FD, sint8 scCurrentTireTemp, uint8 ucColOfID)
{
	uint8 ucRtn=TRUE;
#ifdef as_16BitP4Average /*CRS_1211_130_369*/
	uint16 uiPaverage;
	uint16 uiPaverege4CompareValue;
#endif

	if(( ucCurrentPressure < GETucMinWarnThresholdOfRam())						/*CRS_1211_130_268 NEU 1,5bar ALT: default 2,5bar-1bar P_MIN_TIRE CalNotAck*/
	|| (scCurrentTireTemp > GETscOutdoorTemperatureFZZ() + 30)																														/*actual RE_p < Pmin or RE_temp<Tout+30K*/              
	|| (ucCurrentPressure < (GETucPcalMinHaRelativCodOfRam() - cDP_AUTO)))	/*CRS_1211_130_268 NEU 1,9bar check Nr.3 CRS_1211_130_067 default 2,9bar-1bar-0,2bar P_MIN_X CalNotAck*/
	{
		if(GETucCalNotAckStateOfRam() == cCAL_VALID) /* CRS_1211_130_262 CalNotAckState empty??*/
		{

			if (ucCurrentPressure < GETucMinWarnThresholdOfRam()) /* CRS_1211_130_268 NEU 1,5bar ALT: logical data PAL: P_MIN_TIRE 2,5bar!*/
			{
				SetBitCalNotAckState2Ram(cCAL_P_MIN_TIRE_NAK); /*reason 2  P_MIN_TIRE 2,5bar! CalNotAck*/
				SetState2AbortReasonFD(cFD_P_MIN_TIRE); /* CRS_1211_130_212 entfällt CRS_1211_130_206 CRS_1211_130_181*/

				/*SetState2PlausiFailureFD(cFD_MINIMUM_PRESSURE);  Hier AFD, keine Eintrag für MFD Plausi Check CRS_1211_130_230*/
			}
			else
			{
				if ( ucCurrentPressure < (GETucPcalMinHaRelativCodOfRam() - cDP_AUTO)) /* CRS_1211_130_268 NEU 1,5bar ALT: CRS_1211_130_067 logical data PAL: P_MIN_TIRE_4CAL  2,9bar!*/
				{
					/* not for AFD!!!CRS_1211_130_272 SetBitCalNotAckState2Ram(cCAL_P_MIN_X_MINUS_DP_MANUAL); AFD reason 2  P_MIN_TIRE_4CAL  2,9bar! CalNotAck*/
					SetState2AbortReasonFD(cFD_DP_AUTO); /*2 CRS_1211_130_181 */
				}
				else
				{
					if(scCurrentTireTemp > (GETscOutdoorTemperatureFZZ() + 30))
					{
						SetBitCalNotAckState2Ram(cCAL_RE30K2AMBIENT); /*reason 4 CalNotAck*/
						SetState2AbortReasonFD(cFD_TIRE2HOT); /*3 CRS_1211_130_181*/
					}
				}
			}
			ucRtn=FALSE; /*Abort filling detection 3,4,5,6,*/
			SetState2FillingDetectionStateFD(cFILLING_DETECT_ABORTED); /*New tire pressure are not plausibl CRS_1211_130_181*/
			ClearPlausiFailureFD(); /*CRS_1211_130_277 _320*/
		}
	}
 	else
	{
		if(ucREcnt4FD==1) /* 1. RE Telegramm bei Fahrzeug fährt */
		{							
			PUTucDpStabiPressure(ucCurrentPressure,ucColOfID); /* CRS_1211_130_319 DP_STABI Sonderbehandlung: Referenzdruck ucREcnt4FD =1 -> Fahrzeug fährt!*/
#ifdef as_16BitP4Average /*CRS_1211_130_369*/
			PUTucIdCalPressure(ucCurrentPressure,ucColOfID); /*CRS_1211_130_268 NEU relativer Druck ALT	CRS_1211_130_173 Storage first current pressure for CHECK DP_STAPI (100mbar) and DP_Fill*/
			PUTuiStoragePaverege4CompareValue(ucCurrentPressure,ucColOfID); /* CRS_1211_130_228 P relativ NICHT gedeckelt! */
			PUTscIdCalTemperatur(scCurrentTireTemp,ucColOfID);	/*CRS_1211_130_173 Storage current pressure for CHECK DP_STAPI (100mbar) and DP_Fill*/
#endif
		}
		else
		{
			if(ucREcnt4FD != 0) /*CRS_1211_130_316*/
			{
				if(ucREcnt4FD == 0xFF) /*CRS_1211_130_335 KEIN EMPFANG!*/
				{
					if(ucCurrentPressure < (GETucDpStabiPressure(ucColOfID) - cDP_STABI))  /* CRS_1211_130_319 DP_STABI Sonderbehandlung: Referenzdruck ucREcnt4FD =1 -> Fahrzeug fährt!*/
					{
						SetBitCalNotAckState2Ram(cCAL_DP_STABI_NAK ); /* CRS_1211_130_166 reason DP_STABI-> CalNotAck*/	
						SetState2AbortReasonFD(cFD_DP_STABI); /*4 CRS_1211_130_181*/	
						SetState2FillingDetectionStateFD(cFILLING_DETECT_ABORTED); /*New tire pressure are not plausibl CRS_1211_130_181*/
						ClearPlausiFailureFD(); /*CRS_1211_130_277*/
						ucRtn=FALSE; /*Abort filling detection 3,4,5,6,*/
					}
				}
				else
				{

#ifdef as_16BitP4Average /*CRS_1211_130_369*/
					uiPaverage=(uint16)(GETucIdCalPressure(ucColOfID) * (ucREcnt4FD-1));
					uiPaverege4CompareValue=(GETuiStoragePaverege4CompareValue(ucColOfID) * (ucREcnt4FD-1));	

					uiPaverage=(uint16)(ucCurrentPressure + uiPaverage );		
					uiPaverege4CompareValue=((uint16)(ucCurrentPressure) + uiPaverege4CompareValue ); 

					PUTucIdCalPressure((uiPaverage/ucREcnt4FD),ucColOfID); /* CRS_1211_130_268 neu Prelativ */
					PUTuiStoragePaverege4CompareValue((uiPaverege4CompareValue/ucREcnt4FD),ucColOfID); /*CRS_1211_130_263 P relativ*/	
#endif	

					if(ucCurrentPressure < (GETucDpStabiPressure(ucColOfID) - cDP_STABI))  /*CRS_1211_130_317 GETucPosComparePressure(cRadPosVL) */
					{
						SetBitCalNotAckState2Ram(cCAL_DP_STABI_NAK ); /* CRS_1211_130_166 reason DP_STABI-> CalNotAck*/	
						SetState2AbortReasonFD(cFD_DP_STABI); /*4 CRS_1211_130_181*/	
						SetState2FillingDetectionStateFD(cFILLING_DETECT_ABORTED); /*New tire pressure are not plausibl CRS_1211_130_181*/
						ClearPlausiFailureFD(); /*CRS_1211_130_277*/
						ucRtn=FALSE; /*Abort filling detection 3,4,5,6,*/
					}
				}
			}
		}
	}
 return ucRtn;
}


/*-------------------------------------------------------------------------------------------------
/  FD_PlausibilityCheckMFD( sint8);  Check pressure: DP_LR + DP_ABS and set Pref Tref Pcompare  /
/
/ Description/
/
/ Purpose:             MFD Kalibrierung: Plausibility Check Prüfung Druckwert bei aktueller Temperatur/
/											(MFD= manual filling detection)/
/  ------------------------------------------------------------------------------------------------/
/  Input:              /
/ 
/  Output:             Druckwert/
/ ------------------------------------------------------------------------------------------------*/
void FD_PlausibilityCheckMFD(sint8 scTemperaturOutside)
{

	uint8 ucColOfIdVL,ucColOfIdVR,ucColOfIdHL, ucColOfIdHR;  //4 CRS_1211_130_075
	uint8 i;
	sint8 scTfillVA;
	sint8 scTfillHA;
	sint8 scTfill_Tref;
	uint8 ucRtn=FALSE;


/*  uint8 ui8GetPPWP(uint8 * p2P, uint8 * p2PWP, uint8 ui8MinRefPF, uint8 ui8MinRefPR) PreProvisionalWhellPosition*/

 /*ui8GetPPWP(uint8 * p2P, uint8 * p2PWP,GETucPcalMinVaRelativCodOfRam(),GETucPcalMinHaRelativCodOfRam());*/

	for( i = 0; i < cAnzRad; i++ ) /*i=ZOMPOS*/
	{
		switch (GETucWPorPWPofHistCol(i))
		{
			case cRadPosVL: 
						ucColOfIdVL=i; /*ZOM-COLpos of cRadPosVL*/
			break;
			case cRadPosVR: 
   					ucColOfIdVR=i; /*ZOM-COLpos of cRadPosVR*/
			break;
			case cRadPosHL: 
						ucColOfIdHL=i; /*ZOM-COLpos of cRadPosHL*/
			break;
			case cRadPosHR: 
  					ucColOfIdHR=i; /*ZOM-COLpos of cRadPosHR*/
			break;
			default:
			{
				ucRtn = TRUE;
			}
		}
	}

	if(ucRtn == FALSE)  /* ID pos not found, neither ZOMnormal  neither provisional ?????*/
	{

		/* plausibility check ok: 5.2 Filling detection flow chart result:(B) ************************************************************************************************/
		if(FD_Plausibility_CheckP4DPLR_DPABS(ucColOfIdVL,ucColOfIdVR,ucColOfIdHL,ucColOfIdHR) == TRUE)
		{
			/* CRS_1211_130_336 für MFD nicht nötig!!*/
			//ucRePosStorageVL4FD=ucColOfIdVL; /*CRS_1211_130_336 MFD*/
			//ucRePosStorageVR4FD=ucColOfIdVR; /*CRS_1211_130_336 MFD*/
			//ucRePosStorageHL4FD=ucColOfIdHL; /*CRS_1211_130_336 MFD*/
			//ucRePosStorageHR4FD=ucColOfIdHR; /*CRS_1211_130_336 MFD*/

			/*@@AS was passiert mit der Kalibrierung in der Sonder funktion Teilüberwachung???? d.h. es sind nur 3 Räder verbaut??*/	  
			SetBitBetriebszustandBZ(cCAL_FINISH);
			ClearBitBetriebszustandBZ(cCAL_REQUEST); /*delete request bit 4 next calibration*/
			// ClearBitBetriebszustandBZ(cCAL_MFD_PLAUSI_ERROR); in FD_Plausi Fkt. integriert  CRS_1211_130_313 delete "plausible error" for unplausible message in HMI! */
			ClearPlausiFailureFD();														/* */
			ClearBitCalRequestState(cCAL_MANUAL_ACTIV);

			ClearCalRequestStateAtMFDfinish(); /*CRS_1211_130_278*/
			SetBitCalRequestState2Ram(cCAL_MANUAL_FINISH); 
			SetState2FillingDetectionStateFD(cFILLING_DETECTED);/* Filling detected: Update Pref,Tref, Compare Value CRS_1211_130_184 */
	 
			/*tTireTemp.TireTemp_FL-ucPalTempNormFACTOR4Calc --> TireTemp -50!!!!!!!!!!!! */
			/*CRS_1211_130_075*/
			/*Average pressure 2 Pref 4 front and rear axis*/ 

			PUTucPrefFront((GETucIdCalPressure(ucColOfIdVL) + GETucIdCalPressure(ucColOfIdVR))/2);/*load Average pressure VL,VR*/
			PUTucPrefRear((GETucIdCalPressure(ucColOfIdHL) + GETucIdCalPressure(ucColOfIdHR))/2);/*load Average pressure HL,HR*/
			/*Average pressure 2 Pfill 4 front and rear axis*/ 
			PUTucPfillFront(GETucPrefFront());	/*CRS_1211_130_268 NEU relativer Druck CRS_1211_130_100 p_fill_front 4 measurement interface*/
			PUTucPfillRear(GETucPrefRear());	/* CRS_1211_130_268 NEU relativer Druck CRS_1211_130_100p_fill_front 4 measurement interface*/		

			/******************************************************************************************************************************************************************/
			/* @@@AS 4 01.04.2016						*/
			/*5.8.1.												*/
			/*t_fill_front=		((GETscIdCalTemperatur(ucColOfIdVL) + GETscIdCalTemperatur(ucColOfIdVR))/2); */		
			/*t_fill_rear=		((GETscIdCalTemperatur(ucColOfIdHL) + GETscIdCalTemperatur(ucColOfIdHR))/2);		*/		
			/*t_fill=((GETscIdCalTemperatur(ucColOfIdVL) + GETscIdCalTemperatur(ucColOfIdVR) + GETscIdCalTemperatur(ucColOfIdHL) + GETscIdCalTemperatur(ucColOfIdHR)) /4)*/
			/*t_ref=KweightCalculation(t_fill, tEnvDataToSend.ucTempOut); CRS_1211_130_083 weighting factor K_WEIGHT for Tref*/
			/*        5.8.3 */
			/*P_VA for WARNHANDLER: p_ref_front= (((p_fill_front+1bar)*t_ref+273))/(t_fill_front+273))*/
			/*if p_ref_front <P_MIN_F --> p_ref_front=P_MIN_F*/
			/*P_HA for WARNHANDLER: p_ref_rear= (((p_fill_rear+1bar)*t_ref+273))/(t_fill_rear+273))*/
			/*if p_ref_tear <P_MIN_F --> p_ref_rear=P_MIN_F*/
			/* Rte_Write_PP_Data2Warn_DE_tData2Warn(&tData2Warn); CRS_1211_130_089 */ 
			/* ResetWarningsUSWIF(); CRS_1211_130_090 OPL172 */ 
			/*****************************************************************************************************************************************************************/
	
			scTfillVA=((GETscIdCalTemperatur(ucColOfIdVL) + GETscIdCalTemperatur(ucColOfIdVR))/2);/*CRS_1211_130_085*/
			scTfillHA=((GETscIdCalTemperatur(ucColOfIdHL) + GETscIdCalTemperatur(ucColOfIdHR))/2);/*CRS_1211_130_085*/

			if(scTfillVA > cTfillLimitH) /*CRS_1211_130_219*/
			{
				scTfillVA=cTfillLimitH;
			}	
			if(scTfillHA > cTfillLimitH)/*CRS_1211_130_219*/
			{
				scTfillHA=cTfillLimitH;
			}		

 			scTfill_Tref=(scTfillVA + scTfillHA)/2;
			PUTscTfill(scTfill_Tref);   /* CRS_1211_130_219 to store it for DCM purpose */
			scTfill_Tref=KweightCalculation(scTfill_Tref, scTemperaturOutside); /*CRS_1211_131_083 weighting factor K_WEIGHT for Tref*/

			/*CRS_1211_130_218 IF p_ref_rear < P_MIN_R THEN p_ref_rear = P_MIN_R ISOCHOR Pressure absolut 4 WARNALGO*/
			/* front axis */
			/*CRS_1211_130_309 1. Isochorendruck berechnen, 2. Prüfung auf kleiner Mindestkalibrierdruck! */
			PUTucPrefFront(GetP4NewTempAtCAL(GETucPrefFront(),scTfillVA, scTfill_Tref));	/*CRS_1211_130_268 GetPabs4NewTempAtCAL 4 relativen Druck! VA: 5.8.3 Calculation of the cold tire inflation pressure*/	
			if (GETucPrefFront() <= GETucPcalMinVaRelativCodOfRam()) /* CRS_1211_130_268 NEU relativ ALT:absolut <= absolut*/
			{
				PUTucPrefFront( GETucPcalMinVaRelativCodOfRam());/* CRS_1211_130_268 NEU relativ ALT:absolut <= absolut*/
			}
			/* rear axis */
			/*CRS_1211_130_309 1. Isochorendruck berechnen, 2. Prüfung auf kleiner Mindestkalibrierdruck! */
			PUTucPrefRear(GetP4NewTempAtCAL(GETucPrefRear(),scTfillHA, scTfill_Tref));	/*CRS_1211_130_268 GetPabs4NewTempAtCAL 4 relativen Druck! VA: 5.8.3 Calculation of the cold tire inflation pressure*/	
			if(GETucPrefRear() <= GETucPcalMinHaRelativCodOfRam()) /* CRS_1211_130_268 NEU relativ ALT:absolut <= absolut*/
			{
				PUTucPrefRear( GETucPcalMinHaRelativCodOfRam());/* CRS_1211_130_268 NEU relativ ALT:absolut <= absolut*/
			}
		
			PUTscTref(scTfill_Tref);

			/**************************************************************************/
			/*update compare pressure value, after manual calibration CRS_1211_130_150*/
			/******** CRS_1211_130_157 RELATIV P- VALUE  TirePressureDiffAbsRel ***************/
			/*CRS_1211_130_241 Compare value nicht auf 1,9bar deckeln! Hier falsch! ucIdCalPressure wird beim sammeln der MFD Druckwerte auf 1,9bar gedeckelt!!*/
			/*ACHTUNG! MFD/AFD speichert in uiStoragePaverege4CompareValue() relative Drucklwerte ZOM spezifisch ab! */
			/* CRS_1211_130_263 GETuiStoragePaverege4CompareValue(ucColOfIdVL)) ALT und Falsch:GETuiStoragePaverege4CompareValue(cRadPosVL)) */
			/*CRS_1211_130_268 relativ pressure allways!*/
			PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdVL)),GETscIdCalTemperatur(ucColOfIdVL), scTfill_Tref),cRadPosVL);	/*Pvl + Tvl @ Tref: PnewRelativ*/		
			PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdVR)),GETscIdCalTemperatur(ucColOfIdVR), scTfill_Tref),cRadPosVR);	/*Pvr + Tvr @ Tref: PnewRelativ*/										
			PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdHL)),GETscIdCalTemperatur(ucColOfIdHL), scTfill_Tref),cRadPosHL);	/*Phl + Thl @ Tref: PnewRelativ*/				
			PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdHR)),GETscIdCalTemperatur(ucColOfIdHR), scTfill_Tref),cRadPosHR);	/*Phr + Thr @ Tref: PnewRelativ*/	

			/*************************************************************************/		
			//ResetWarningsUSWIF(); /* CRS_1211_130_090 OPL172*/
			DelWarnOfId(4); /*MFA2: CRS_1211_130_234neu aus papenburg April --> 4=all DelWarnOfId(uint8 ui8HistColOfID) */

			/* bei Neuinitialisierung an dieser Stelle werden Warnungen ausgegeben LOW PRESSURE*/
			ReplayLastREvalue2Walgo();	

#ifdef FD_CONTROLS_FALLBACK
			/*FD_CONTROLS_FALLBACK*/
			if(bGETucCalNotAckState(cCAL_FBM_ACTIV_NAK) == TRUE)
			{
			 /* Kein Pmin!! dann lösche die Alte FBM ZO und stoße die Ermittlung der NEUEN FBM ZO an*/ 
			 ClearPWP(); /* Lösche FB Mode Zuordnung*/
			 Check4PWP();/* Bilde neue FB Mode Zuordnung*/
			}
			/*FD_CONTROLS_FALLBACK*/
#endif
	
		}
		else 
		{
			/* MISSING cDP_LR and DP_ABS -->  calibration stopp --> abort filling detection*/
			/* plausibility check NOT OK: New tire pressure are not plausible update compare pressure only 5.2 Filling detection flow chart result:(A)*/
			SetState2FillingDetectionStateFD(cFILLING_UNPLAUSIBLE); /*New tire pressure are not plausibl CRS_1211_130_181*/			

			if((bGetBitBetriebszustandBZ(cCAL_FINISH) != TRUE) && (bGETucCalRequestState(cCAL_MANUAL_ACTIV)== TRUE)) /*timeout and calibration empty?*/
			{
			
				SetBitBetriebszustandBZ(cCAL_FINISH | cCAL_MFD_PLAUSI_ERROR);
				//SetBitBetriebszustandBZ(cCAL_MFD_PLAUSI_ERROR);  /* CRS_1211_130_202 CRS_1211_130_101 only if plausibility check NOT OKAY! */
				ClearBitBetriebszustandBZ(cCAL_REQUEST); /*delete request bit 4 next calibration*/
				ClearBitCalRequestState(cCAL_MANUAL_ACTIV | cCAL_AUTO_NEW_ID); /*CRS_1211_130_267*/			
				//ClearBitCalRequestState(cCAL_MANUAL_ACTIV);
				SetBitCalRequestState2Ram(cCAL_MANUAL_FINISH);
				/*update compare relativ pressure value, without limit! MFA2: CRS_1211_130_205 -> siehe FD_CalcAverageP4MFD() Pist<Pmin*/ 
				/*CRS_1211_130_304 Tref mit GETscTref()() synchonisieren*/
				PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdVL)),GETscIdCalTemperatur(ucColOfIdVL), GETscTref()),cRadPosVL);	/*Pvl + Tvl @ Tref: PnewRelativ*/		
				PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdVR)),GETscIdCalTemperatur(ucColOfIdVR), GETscTref()),cRadPosVR);	/*Pvr + Tvr @ Tref: PnewRelativ*/										
				PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdHL)),GETscIdCalTemperatur(ucColOfIdHL), GETscTref()),cRadPosHL);	/*Phl + Thl @ Tref: PnewRelativ*/				
				PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdHR)),GETscIdCalTemperatur(ucColOfIdHR), GETscTref()),cRadPosHR);	/*Phr + Thr @ Tref: PnewRelativ*/	
				/*****************************************************************/
 			}
			else
			{
				if((bGetBitBetriebszustandBZ(cCAL_FINISH) != TRUE) && (bGETucCalRequestState(cCAL_AUTO_ACTIV)== TRUE)) /*timeout and calibration empty?*/
				{
					SetBitBetriebszustandBZ(cCAL_AFD_PLAUSI_ERROR); /*CRS_1211_130_227 Hier OKAY da "new tire pressure are not plausible", altCRS_1211_130_202*/
					BZ_FZZ_RQ_State4AFD_Finish(); /*CRS_1211_130_267*/
 				}
			}
		}
	}
	else
	{
		SetState2PlausiFailureFD(cFD_FALL_BACK_NOPOS); /*FALL BACK MODE Without POS --> Code Review*/	
		if((bGetBitBetriebszustandBZ(cCAL_FINISH) != TRUE) && (bGETucCalRequestState(cCAL_MANUAL_ACTIV)== TRUE)) /*timeout and calibration empty?*/
		{
			
			SetBitBetriebszustandBZ(cCAL_FINISH | cCAL_MFD_PLAUSI_ERROR);
			//SetBitBetriebszustandBZ(cCAL_MFD_PLAUSI_ERROR);  /* CRS_1211_130_202 CRS_1211_130_101 only if plausibility check NOT OKAY! */
    	ClearBitBetriebszustandBZ(cCAL_REQUEST); /*delete request bit 4 next calibration*/
			//ClearBitCalRequestState(cCAL_MANUAL_ACTIV);
			SetBitCalRequestState2Ram(cCAL_MANUAL_FINISH);
			ClearBitCalRequestState(cCAL_MANUAL_ACTIV | cCAL_AUTO_NEW_ID); /*CRS_1211_130_267*/
			//CRS_1211_130_249 PUTucCalRequestState2Nvm(); /* CRS_1211_130_243 CalRequestState into Nvm if Kl15off and softreset*/				
		}
	}

}

/*-------------------------------------------------------------------------------------------------
** FD_UnplausibleMFD(sint8 scTemperaturOutside) Pmin-DP_MANUAL only!  CRS_1211_130_216
** FD_UnplausibleMFD() CRS_1211_500_1279
**/
/*
** Description
**/
/*
** Purpose:   SetState2FillingDetectionStateFD(Pmin-DP_MANUAL) 
**            New tire pressure are not plausibl CRS_1211_130_181			
**
** ------------------------------------------------------------------------------------------------
** Input:      scTemperaturOutside        
**
** Output:     nothing
** ------------------------------------------------------------------------------------------------
**/
void FD_UnplausibleMFD(void) /*CRS_1211_500_1279*/
{
	uint8 ucColOfIdVL,ucColOfIdVR,ucColOfIdHL, ucColOfIdHR;  /*4 CRS_1211_130_075*/
	uint8 i;
	uint8 ucRtn=FALSE;

	for( i = 0; i < cAnzRad; i++ ) /*i=ZOMPOS*/
	{
		switch (GETucWPorPWPofHistCol(i))
		{
			case cRadPosVL: 
						ucColOfIdVL=i; /*ZOM/COLpos of cRadPosVL*/
			break;
			case cRadPosVR: 
   					ucColOfIdVR=i; /*ZOM/COLpos of cRadPosVR*/
			break;
			case cRadPosHL: 
						ucColOfIdHL=i; /*ZOM/COLpos of cRadPosVR*/
			break;
			case cRadPosHR: 
  					ucColOfIdHR=i; /*ZOM/COLpos of cRadPosVR*/
			break;
			default:
			{
				ucRtn = TRUE;				
			}
		}
	}

	if(ucRtn == FALSE)  /* ID pos not found, neither ZOMnormal  neither provisional ?????*/
	{
		/* MISSING cDP_LR and DP_ABS -->  calibration stopp --> abort filling detection*/
		/* plausibility check NOT OK: New tire pressure are not plausible update compare pressure only 5.2 Filling detection flow chart result:(A)*/
		SetState2FillingDetectionStateFD(cFILLING_UNPLAUSIBLE); /*New tire pressure are not plausibl CRS_1211_130_181*/			
		SetBitCalNotAckState2Ram(cCAL_P_MIN_X_MINUS_DP_MANUAL); /*MFD reason 2  P_MIN_TIRE_4CAL  2,9bar- 200mbar ! CalNotAck*/
		SetState2PlausiFailureFD(cFD_DP_MANUAL); /* CRS_1211_130_206*/
		ClearAbortReasonFD(); /* CRS_1211_130_277 FD_PLAUSIBILITY_FAILURE dann kein FD_ABORT_REASON*/

		SetBitBetriebszustandBZ(cCAL_FINISH | cCAL_MFD_PLAUSI_ERROR);
		//SetBitBetriebszustandBZ(cCAL_MFD_PLAUSI_ERROR);  /* CRS_1211_130_202 CRS_1211_130_101 only if plausibility check NOT OKAY! */
   	ClearBitBetriebszustandBZ(cCAL_REQUEST); /*delete request bit 4 next calibration*/
		ClearBitCalRequestState(cCAL_MANUAL_ACTIV | cCAL_AUTO_NEW_ID);
		//ClearBitCalRequestState(cCAL_AUTO_NEW_ID); /*CRS_1211_130_267*/
		SetBitCalRequestState2Ram(cCAL_MANUAL_FINISH);
		/*update compare relativ pressure value, without limit! MFA2: CRS_1211_130_205 -> siehe FD_CalcAverageP4MFD() Pist<Pmin*/ 
		/*CRS_1211_130_304 Tref mit GETscTref()() synchonisieren*/
		PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdVL)),GETscIdCalTemperatur(ucColOfIdVL), GETscTref()),cRadPosVL);	/*Pvl + Tvl @ Tref: PnewRelativ*/		
		PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdVR)),GETscIdCalTemperatur(ucColOfIdVR), GETscTref()),cRadPosVR);	/*Pvr + Tvr @ Tref: PnewRelativ*/										
		PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdHL)),GETscIdCalTemperatur(ucColOfIdHL), GETscTref()),cRadPosHL);	/*Phl + Thl @ Tref: PnewRelativ*/				
		PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdHR)),GETscIdCalTemperatur(ucColOfIdHR), GETscTref()),cRadPosHR);	/*Phr + Thr @ Tref: PnewRelativ*/	

		/*****************************************************************/
	}
	else
	{
		//SetState2FillingDetectionStateFD(cFD_FALL_BACK_NOPOS); /*FALL BACK MODE Without POS --> Code Review*/			
		SetState2PlausiFailureFD(cFD_FALL_BACK_NOPOS);
		if((bGetBitBetriebszustandBZ(cCAL_FINISH) != TRUE) && (bGETucCalRequestState(cCAL_MANUAL_ACTIV)== TRUE)) /*timeout and calibration empty?*/
		{
			
			SetBitBetriebszustandBZ(cCAL_FINISH | cCAL_MFD_PLAUSI_ERROR);
			//SetBitBetriebszustandBZ(cCAL_MFD_PLAUSI_ERROR);  /* CRS_1211_130_202 CRS_1211_130_101 only if plausibility check NOT OKAY! */
    	ClearBitBetriebszustandBZ(cCAL_REQUEST); /*delete request bit 4 next calibration*/
			ClearBitCalRequestState(cCAL_MANUAL_ACTIV | cCAL_AUTO_NEW_ID);
			//ClearBitCalRequestState(cCAL_AUTO_NEW_ID); /*CRS_1211_130_267*/
			SetBitCalRequestState2Ram(cCAL_MANUAL_FINISH);
			//CRS_1211_130_249 PUTucCalRequestState2Nvm(); /* CRS_1211_130_243 CalRequestState into Nvm if Kl15off and softreset*/				
		}
	}
}

/*-------------------------------------------------------------------------------------------------
/	void FD_Check3RePlausiSetMilage4FinishedMFD( void );  Check RE FDcounterValue and set MFD 2 state "Finish"  /
/	CRS_1211_130_335
/ Description/
/
/ Purpose:						MFD Kalibrierung: Check RE FDcounterValue and set MFD 2 state "Finish"/
/											(MFD= manual filling detection)/
/  ------------------------------------------------------------------------------------------------/
/  Input:              /
/ 
/  Output:             TRUE= MFD is finshed  FALSE= MFD can not finished /
/ ------------------------------------------------------------------------------------------------*/
void FD_Check3RePlausiSetMilage4FinishedMFD(void)
{
	//uint8 ucRtn =FALSE;
	
	if(Get_FD_STATUS() == FALSE) /* Kl.15 changed and FD_STATUS=0 ??--> reload*/
	{
		if(bGETucCalRequestState(cCAL_MANUAL_ACTIV) == TRUE)
		{
			SetState2FillingDetectionStateFD(cMFD_RUNNING);
		}
	}

	if(( GETucRErecCounter4FDVL() <3) && ( GETucRErecCounter4FDVR() <3) && ( GETucRErecCounter4FDHL() <3) &&( GETucRErecCounter4FDHR() <3))
	{
		if((bGetBitBetriebszustandBZ(cZO_TIMEOUT) == TRUE ) || (bGetBitBetriebszustandBZ(cZO_FINISH) == TRUE ))  /* ZO_Timeout vor (M)FD_Timeout? Dann Lade die ID spezif. Werte */
		{
			FD_LoadIdValues4MFD(); /* TRUE = reload ID Values 4 MFD Checker OKAY! --> NEXT run through FD_Check3RePlausiSetMilage4FinishedMFD() */
		}
	}

  /*if(( ucTmp4CalVL >=3) && ( ucTmp4CalVR >=3) && ( ucTmp4CalHL >=3) &&( ucTmp4CalHR >=3))*/
	/*CRS_1211_130_300*/
	if(( GETucRErecCounter4FDVL() >=3) && ( GETucRErecCounter4FDVR() >=3) && ( GETucRErecCounter4FDHL() >=3) &&( GETucRErecCounter4FDHR() >=3)
		&& (((bGetBitBetriebszustandBZ(cZO_FINISH) == TRUE)
		|| ((bGetBitBetriebszustandBZ(cZO_TIMEOUT) == TRUE ) && (ui8GetALState() == cAL_Stored))
		|| ((bGetBitBetriebszustandBZ(cZO_TIMEOUT) == TRUE ) && (ui8GetALState() == cAL_OK))
		|| (Getui8ColPWPActive() != FALSE) )))/*CRS_1211_130_301 FALSE= FALLbackMode activ?*/
	{
		if(ucCheckAllRePcalMinDPmanualMFD() == TRUE) /*Prio1 check TRUE= MFD Aborted! CRS_1211_130_099 5.5 Plausibility check criteria: Pcompare < (Pmin_x - DP_Manual) 4 MFD*/
		{
			/* FD_UnplausibleMFD((sint8)(tEnvDataToSend.ucTempOut));CRS_1211_130_216 MFD reason 2 DP_Manual pressure are not plausibl-->  P_MIN_TIRE_4CAL  2,9bar! CalNotAck*/
			FD_UnplausibleMFD(); /*CRS_1211_500_1279*/
		}
		else
		{
			FD_PlausibilityCheckMFD((sint8)(tEnvDataToSend.ucTempOut)); /*5.5 Plausibility check criteria her MFD only:  DP_ABS, DP_LR -> Pref2Warn, compare pressure */
			PUTucOnceCheckMissingRE4FD(TRUE);				
		}					
		PUTushFDtimeout(0); /*MFD finish  auch Pist< Pmin: CalNAK immediately */	
		PUTucFDtimerStop(TRUE); /*CRS_1211_130_337 Vorzeitiger FD Timeout*/	
		
		if(Get_FD_STATUS() == cFILLING_DETECTED) /*CRS_1211_130_188 Mileage storage if MFD OKAY*/
		{					
			PUTulLastCalMileage(GETulKmStand4AutoCAL());  /*CRS_1211_130_096*/ 
		}          
		if( bGETucCalRequestState(cCAL_AUTO_FIRST) == FALSE) /*CRS_1211_130_155 first auto filling detection*/
		{
			SetBitCalRequestState2Ram(cCAL_AUTO_FIRST); 
		}
	}
} 

/*-------------------------------------------------------------------------------------------------
/	void FD_Check3ReAndUpdatePifWarnLampOnOffDefOrInf2Re4FinishedAFD( void );
/ Check RE FDcounterValue and set AFD 2 state "Finish"  /
/	CRS_1211_130_335
/ Description/
/
/ Purpose:						AFD Kalibrierung: Check RE FDcounterValue and set AFD 2 state "Finish"/
/											(AFD= automatoc filling detection)/
/  ------------------------------------------------------------------------------------------------/
/  Input:              /
/ 
/  Output:             TRUE= MFD is finshed  FALSE= MFD can not finished /
/ ------------------------------------------------------------------------------------------------*/
void FD_Check3ReAndUpdatePifWarnLampOnOffDefOrInf2Re4FinishedAFD(void)
{
	uint8 ucDeflationLTS; 

	if(bGETucCalRequestState(cCAL_AUTO_ACTIV) == TRUE) /*auto CAL started ??????? CHECK Pist<P_MIN_X-DP_AUTO*/
	{
		if(Get_FD_STATUS() == FALSE) /* Kl.15 changed and FD_STATUS=0 ?? -> updated and reload*/
		{
			if(bGETucCalRequestState(cCAL_AUTO_ENABLE2) == TRUE)
			{
				SetState2FillingDetectionStateFD(cAFD_RUNNING2);
			}
			else
			{
				if(bGETucCalRequestState(cCAL_AUTO_ENABLE3) == TRUE)
				{
					SetState2FillingDetectionStateFD(cAFD_RUNNING3);
				}
			}
		}

/* Schlupfloch beim Start der AFD und Radtausch innerhalb! --> Lösung: WARTEN BIS c_ZO_FINISH bit gesetzt! Wie bei der MFD, dann ist der Käs gegessen!*/ 		
/*if(( GETucRErecCounter4FDVL() >=3) && ( GETucRErecCounter4FDVR() >=3) && ( GETucRErecCounter4FDHL() >=3) &&( GETucRErecCounter4FDHR() >=3)
		&& (((bGetBitBetriebszustandBZ(cZO_FINISH) == TRUE)
		|| ((bGetBitBetriebszustandBZ(cZO_TIMEOUT) == TRUE ) && (ui8GetALState() == cAL_Stored))
		|| ((bGetBitBetriebszustandBZ(cZO_TIMEOUT) == TRUE ) && (ui8GetALState() == cAL_OK))*/

		if(( GETucRErecCounter4FDVL() >=3) && ( GETucRErecCounter4FDVR() >=3) && ( GETucRErecCounter4FDHL() >=3) &&( GETucRErecCounter4FDHR() >=3) )
		{
			//ucCnt4DP_FILL=3; /*TEST 4 CAL*/
			/**************************************************************/	
			/*Finish Check Nr 9 iso 2 or more wheels inflated or deflated */
			/*ONE or more wheel inflated or deflated differnce counter 5.4 Filling Detected DP_FILL 200mbar  */
			ucDeflationLTS=(GETucCnt4DP_FILL_DFL() & 0x0F);/*CRS_1211_130_371 Zählerstand im unteren nibble*/
			ucDeflationLTS=(ucDeflationLTS | (GETucDFL_LTS3() & 0xF0));/*CRS_1211_130_371 LTS im oberen nibble*/
			if(GETushWarnstatus1WN() == FALSE)/*CRS_1211_130_195 5.4.2 Filling Detected if warning lamp is OFF*/	
			{
				FD_UpdatePressure4AfdWarnLampOFF(ucDeflationLTS, GETucCnt4DP_FILL_IFL(), (sint8)(tEnvDataToSend.ucTempOut) );
			}
			else
			{
				FD_UpdatePressure4AfdWarnLampON(GETucCnt4DP_FILL_IFL(), (sint8)(tEnvDataToSend.ucTempOut) );
			}
			/*PUTucCnt4DP_FILL_DFL(0); CRS_1211_130_374 KEIN RESET      reset deflated counter for next AFD */
			/*PUTucCnt4DP_FILL_IFL(0);  CRS_1211_130_374 KEIN RESET      reset inflated counter for next AFD */

			PUTushFDtimeout(0); /*AFD  finish */ 
			PUTucFDtimerStop(TRUE);/*CRS_1211_130_337 Vorzeitiger FD Timeout*/
			if( bGETucCalRequestState(cCAL_AUTO_FIRST) == FALSE) /*CRS_1211_130_155 first auto filling detection*/
			{
				SetBitCalRequestState2Ram(cCAL_AUTO_FIRST); 
			}
			if(bGetBitBetriebszustandBZ(cZO_FINISH) == FALSE) /*CRS_1211_130_336 noch keine gültige ZO ABER AFD ist mit 3 Telegrammen fertig!CRS_1211_130_336 */
			{
				//PUTucFDcheckP2PosOk(TRUE);
				PUTucFDcheckP2PosOk(5);
			}
		}
	} 
}

/*-------------------------------------------------------------------------------------------------
** FD_UpdatePressure4AfdWarnLampON(uint8, sint8)
**/
/*
** Description
**/
/*
** Purpose: AFD Kalibrierung: Warning Lamp ON
**        auto filling detected --> Check condition for Update Pcompare and Pref
**				2 or more wheels inflated od deflated: 5.2 Filling detection flow chart result:(B)
**        filling detected after 100km above the last manual calibration 5.4.2
**
** ------------------------------------------------------------------------------------------------
** Input:      COUNTER 4  COUNTER 4 ucAfd_Inflated, scTemperaturOutside        
**
** Output:             Druckwert
** ------------------------------------------------------------------------------------------------
**/
void FD_UpdatePressure4AfdWarnLampON( uint8 ucAfd_Inflated, sint8 scTemperaturOutside)
{
	uint8 ucColOfIdVL,ucColOfIdVR,ucColOfIdHL, ucColOfIdHR;  /*4 CRS_1211_130_075*/
	uint8 i;
	sint8 scTfillVA;
	sint8 scTfillHA;
	sint8 scTfill_Tref;
	uint8 ucRtn=FALSE;

	for( i = 0; i < cAnzRad; i++ ) /*i=ZOMPOS*/
	{
		switch (GETucWPorPWPofHistCol(i))
		{
			case cRadPosVL: 
						ucColOfIdVL=i; /*ZOM/COLpos of cRadPosVL*/
			break;
			case cRadPosVR: 
  					ucColOfIdVR=i; /*ZOM/COLpos of cRadPosVR*/
			break;
			case cRadPosHL: 
						ucColOfIdHL=i; /*ZOM/COLpos of cRadPosVR*/
			break;
			case cRadPosHR: 
 						ucColOfIdHR=i; /*ZOM/COLpos of cRadPosVR*/
			break;
			default:
			{
				ucRtn = TRUE;
			}
		}
	}

	if(ucRtn == FALSE)
	{
		/******************* 5.4.3 Filling Detected ? if warning lamp is ON***************************************/         
		if((ucAfd_Inflated & 0x0F) >= 2) /* 1. Bedingung: sind mindestens 2 Räder befüllt? Sind die Räder mit Warnung befüllt?*/
		{


			if((GETaucWheelPosWarn(cRadPosVL) != FALSE) && ((ucAfd_Inflated & cDP_FILL_FL) != cDP_FILL_FL)) /*CRS_1211_130_220 AFD: inflated all wheels with warnning level*/
			{
				ucRtn=TRUE;/* Warnung VL steht an und RadVL wurde ABER NICHT befüllt! -->  RAUS Filling NOT Detected */
			}
			if((GETaucWheelPosWarn(cRadPosVR) != FALSE) && ((ucAfd_Inflated & cDP_FILL_FR) != cDP_FILL_FR)) /*CRS_1211_130_220 AFD: inflated all wheels with warnning level*/
			{
				ucRtn=TRUE; /* Warnung VR steht an und RadVR wurde ABER NICHT befüllt! -->  RAUS Filling NOT Detected */
			}
			if((GETaucWheelPosWarn(cRadPosHL) != FALSE) && ((ucAfd_Inflated & cDP_FILL_RL) != cDP_FILL_RL)) /*CRS_1211_130_220 AFD: inflated all wheels with warnning level*/
			{
				ucRtn=TRUE;/* Warnung HL steht an und RadHL wurde ABER NICHT befüllt! -->  RAUS Filling NOT Detected */
			}
			if((GETaucWheelPosWarn(cRadPosHR) != FALSE) && ((ucAfd_Inflated & cDP_FILL_RR) != cDP_FILL_RR)) /*CRS_1211_130_220 AFD: inflated all wheels with warnning level*/
			{
				ucRtn=TRUE;/* Warnung HR steht an und RadHR wurde ABER NICHT befüllt! -->  RAUS Filling NOT Detected */
			}

			if(ucRtn == TRUE) 
			{
				/*ucRtn= TRUE: es gibt noch mindestens EIN Rad mit Warnung wurde ABER nicht befüllt dann cFD_ACTIV_WARNING!!!!*/				
				SetState2FillingDetectionStateFD(cFD_ACTIV_WARNING);/*CRS_1211_130_379*/

				if((GETaucWheelPosWarn(cRadPosVL) == FALSE) && ((ucAfd_Inflated & cDP_FILL_FL) == cDP_FILL_FL)) /*2 Räder befüllt: VL nicht bewarnt aber befüllt, setze die Vergleichsdrücke für diese Rad*/
				{
					/*CRS_1211_130_382*/
					PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdVL)),GETscIdCalTemperatur(ucColOfIdVL), GETscTref()),cRadPosVL);	/*Pvl + Tvl @ Tref: PnewRelativ*/
					ucRePosStorageVL4FD=ucColOfIdVL; /*CRS_1211_130_336 AFD*/				
				}
				if((GETaucWheelPosWarn(cRadPosVR) == FALSE) && ((ucAfd_Inflated & cDP_FILL_FR) == cDP_FILL_FR)) /*2 Räder befüllt: VR nicht bewarnt aber befüllt, setze die Vergleichsdrücke für diese Rad*/
				{
					/*CRS_1211_130_382*/
					PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdVR)),GETscIdCalTemperatur(ucColOfIdVR), GETscTref()),cRadPosVR);	/*Pvr + Tvr @ Tref: PnewRelativ*/	
					ucRePosStorageVR4FD=ucColOfIdVR; /*CRS_1211_130_336 AFD*/		
				}
				if((GETaucWheelPosWarn(cRadPosHL) == FALSE) && ((ucAfd_Inflated & cDP_FILL_RL) == cDP_FILL_RL))/*2 Räder befüllt: HL nicht bewarnt aber befüllt, setze die Vergleichsdrücke für diese Rad*/
				{
					/*CRS_1211_130_382*/
					PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdHL)),GETscIdCalTemperatur(ucColOfIdHL), GETscTref()),cRadPosHL);	/*Phl + Thl @ Tref: PnewRelativ*/
					ucRePosStorageHL4FD=ucColOfIdHL; /*CRS_1211_130_336 AFD*/		
				}	
				if((GETaucWheelPosWarn(cRadPosHR) == FALSE) && ((ucAfd_Inflated & cDP_FILL_RR) == cDP_FILL_RR)) /*2 Räder befüllt: HL nicht bewarnt aber befüllt, setze die Vergleichsdrücke für diese Rad*/
				{
					/*CRS_1211_130_382*/
					PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdHR)),GETscIdCalTemperatur(ucColOfIdHR), GETscTref()),cRadPosHR);	/*Phr + Thr @ Tref: PnewRelativ*/	
					ucRePosStorageHR4FD=ucColOfIdHR; /*CRS_1211_130_336 AFD*/
				}
			}
			else
			{			
				/*ucRtn=FALSE: 2 Räder befüllt auch die mit Warnung(en) SetState2FillingDetectionStateFD(cFILLING_DETECTED); */				
				SetState2FillingDetectionStateFD(cFILLING_DETECTED); /* CRS_1211_130_378 nach FD_Plausibility_CheckP4DPLR_DPABS   SetState2FillingDetectionStateFD(cFILLING_DETECTED) entfernt!*/
			}
		}
		else
		{
			if((ucAfd_Inflated & 0x0F) == 1) /*CRS_1211_130_381 CRS_1211_130_375 2. Bedingung: ein Rad wurde befüllt? Prüfe ob dieses Rad die Wanung hatte sezte Filling not Detected anstelle cFd_ACTIV_Warning!!*/
			{
				SetState2FillingDetectionStateFD(cFILLING_NOT_DETECTED); /* NUR ein Rad wurde befüllt! --> Filling NOT Detected und setze NUR die Vergleichswerte (compare value!)*/
			
				/******************************************************************************************/
				/* CRS_1211_130_381 CRS_1211_130_236 update compare pressure value	 																				*/
				/* CONDITION and REASON: 	1warnung, 1wheel pressure inflated															*/
				/******************************************************************************************/
				PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdVL)),GETscIdCalTemperatur(ucColOfIdVL), GETscTref()),cRadPosVL);	/*Pvl + Tvl @ Tref: PnewRelativ*/						
				PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdVR)),GETscIdCalTemperatur(ucColOfIdVR), GETscTref()),cRadPosVR);	/*Pvr + Tvr @ Tref: PnewRelativ*/						
				PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdHL)),GETscIdCalTemperatur(ucColOfIdHL), GETscTref()),cRadPosHL);	/*Phl + Thl @ Tref: PnewRelativ*/		
				PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdHR)),GETscIdCalTemperatur(ucColOfIdHR), GETscTref()),cRadPosHR);	/*Phr + Thr @ Tref: PnewRelativ*/	
				/******************************************************************************************/
				ucRePosStorageVL4FD=ucColOfIdVL; /*CRS_1211_130_336 AFD*/
				ucRePosStorageVR4FD=ucColOfIdVR; /*CRS_1211_130_336 AFD*/
				ucRePosStorageHL4FD=ucColOfIdHL; /*CRS_1211_130_336 AFD*/
				ucRePosStorageHR4FD=ucColOfIdHR; /*CRS_1211_130_336 AFD*/

			}
			else /* Kein Rad aufgefüllt!!!!*/
			{
				if((GETaucWheelPosWarn(cRadPosVL) != FALSE) || (GETaucWheelPosWarn(cRadPosVR) != FALSE) || (GETaucWheelPosWarn(cRadPosHL) != FALSE) || (GETaucWheelPosWarn(cRadPosHR) != FALSE))
				{
					SetState2FillingDetectionStateFD(cFD_ACTIV_WARNING); /* CRS_1211_130_380 Kein Rad aufgefüllt ABER Warnung immer noch aktiv */
				}
				else
				{
					SetState2FillingDetectionStateFD(cFILLING_NOT_DETECTED);/* Kein Rad aufgefüllt KEINE Warnung aktiv */
				}

			}
			ucRtn=TRUE; /* KEIN Rad befüllt */
		}
		/*5.4.3 Filling Detected if warning lamp is ON AND not including all warned wheels bzw. Warnung VL steht und RadVL wurde befüllt! */
		/******************* 5.4.3 Filling Detected ? if warning lamp is ON***************************************/         
			if(ucRtn == FALSE)/* Mindestens 2Räder wurden befüllt und AUCH ALLE Räder mit Warnung !*/
			{
				ClearBitBetriebszustandBZ(cCAL_AFD_PLAUSI_ERROR);		/*Clear Bit 4  "Filling not detected" (Filling detection flow chart 5.2) */	
				/********************************************************************************************************************************/
				if(FD_Plausibility_CheckP4DPLR_DPABS(ucColOfIdVL,ucColOfIdVR,ucColOfIdHL,ucColOfIdHR) == TRUE)  /* plausibility check ok: 5.2 Filling detection flow chart result:(B)*/
				{
			
					ucRePosStorageVL4FD=ucColOfIdVL; /*CRS_1211_130_336 AFD*/
					ucRePosStorageVR4FD=ucColOfIdVR; /*CRS_1211_130_336 AFD*/
					ucRePosStorageHL4FD=ucColOfIdHL; /*CRS_1211_130_336 AFD*/
					ucRePosStorageHR4FD=ucColOfIdHR; /*CRS_1211_130_336 AFD*/

					SetBitBetriebszustandBZ(cCAL_FINISH);
					BZ_FZZ_RQ_State4AFD_Finish();		/*CRS_1211_130_267*/			
					// CRS_1211_130_378 Wird oben bei ucRtn == FALSE gesetzt !! SetState2FillingDetectionStateFD(cFILLING_DETECTED); /*CRS_1211_130_190 */	 

					/*Average pressure in Pref front and rear axis*/ 
					PUTucPrefFront(((GETucIdCalPressure(ucColOfIdVL) + GETucIdCalPressure(ucColOfIdVR))/2));/*load Average pressure VL,VR*/
					PUTucPrefRear(((GETucIdCalPressure(ucColOfIdHL) + GETucIdCalPressure(ucColOfIdHR))/2));/*load Average pressure HL,HR*/
					/*NONISOCHOR Average pressure in Pfill front and rear axis*/ 
					PUTucPfillFront(GETucPrefFront());	/* CRS_1211_130_268 CRS_1211_130_100 p_fill_front 4 measurement interface*/
					PUTucPfillRear(GETucPrefRear());	/* CRS_1211_130_268 CRS_1211_130_100 p_fill_rear 4 measurement interface*/				
		
					scTfillVA=((GETscIdCalTemperatur(ucColOfIdVL) + GETscIdCalTemperatur(ucColOfIdVR))/2);/*CRS_1211_130_085*/
					scTfillHA=((GETscIdCalTemperatur(ucColOfIdHL) + GETscIdCalTemperatur(ucColOfIdHR))/2);/*CRS_1211_130_085*/		
					if(scTfillVA > cTfillLimitH) /*CRS_1211_130_219*/
					{
						scTfillVA=cTfillLimitH;
					}
					if(scTfillHA > cTfillLimitH)/*CRS_1211_130_219*/
					{
						scTfillHA=cTfillLimitH;
					}			

					scTfill_Tref=(scTfillVA + scTfillHA)/2;
					PUTscTfill(scTfill_Tref);   /* CRS_1211_130_219 to store it for DCM purpose */
					scTfill_Tref=KweightCalculation(scTfill_Tref, scTemperaturOutside); /*CRS_1211_131_083 weighting factor K_WEIGHT for Tref*/

					/*CRS_1211_130_218 IF p_ref_rear < P_MIN_R THEN p_ref_rear = P_MIN_R ISOCHOR Pressure absolut 4 WARNALGO*/
					/* front axis */
					/*CRS_1211_130_309 1. Isochorendruck berechnen, 2. Prüfung auf kleiner Mindestkalibrierdruck! */
					PUTucPrefFront(GetP4NewTempAtCAL(GETucPrefFront(),scTfillVA, scTfill_Tref));	/*CRS_1211_130_268 GetPabs4NewTempAtCAL 4 relativen Druck! VA: 5.8.3 Calculation of the cold tire inflation pressure*/	
					if (GETucPrefFront() <= GETucPcalMinVaRelativCodOfRam()) /* CRS_1211_130_268 NEU relativ ALT:absolut <= absolut*/
					{
						PUTucPrefFront(GETucPcalMinVaRelativCodOfRam());/* CRS_1211_130_268 NEU relativ ALT:absolut <= absolut*/
					}

					/* rear axis */
					/*CRS_1211_130_309 1. Isochorendruck berechnen, 2. Prüfung auf kleiner Mindestkalibrierdruck! */		
					PUTucPrefRear(GetP4NewTempAtCAL(GETucPrefRear(),scTfillHA, scTfill_Tref));	/*CRS_1211_130_268 GetPabs4NewTempAtCAL 4 relativen Druck!VA: 5.8.3 Calculation of the cold tire inflation pressure*/	
					if (GETucPrefRear() <= GETucPcalMinHaRelativCodOfRam()) /* CRS_1211_130_268 NEU relativ ALT:absolut <= absolut*/
					{
						PUTucPrefRear(GETucPcalMinHaRelativCodOfRam());/* CRS_1211_130_268 NEU relativ ALT:absolut <= absolut*/
					}

					PUTscTref(scTfill_Tref);

					/*****************************************************************/
					/*update compare pressure value, after Mcalibration CRS_1211_130_150 and first 100km driving Acalibration*/
					/******** CRS_1211_130_157 RELATIV P- VALUE  ***************/
					/*CRS_1211_130_228 Compare value nicht auf 1,9bar deckeln! Hier falsch! ucIdCalPressure wird beim sammeln der AFD Druckwerte auf 1,9bar gedeckelt!!*/
					/*ACHTUNG! AFD speichert in uiStoragePaverege4CompareValue() relative Drucklwerte ZOM spezifisch ab! */
					/*CRS_1211_130_268 relativ pressure allways!*/					
					PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdVL)),GETscIdCalTemperatur(ucColOfIdVL), scTfill_Tref),cRadPosVL);	/*Pvl + Tvl @ Tref: PnewRelativ*/		
					PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdVR)),GETscIdCalTemperatur(ucColOfIdVR), scTfill_Tref),cRadPosVR);	/*Pvr + Tvr @ Tref: PnewRelativ*/										
					PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdHL)),GETscIdCalTemperatur(ucColOfIdHL), scTfill_Tref),cRadPosHL);	/*Phl + Thl @ Tref: PnewRelativ*/				
					PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdHR)),GETscIdCalTemperatur(ucColOfIdHR), scTfill_Tref),cRadPosHR);	/*Phr + Thr @ Tref: PnewRelativ*/	
					/*****************************************************************/
					DelWarnOfId(4); /*MFA2: CRS_1211_130_234neu aus papenburg April --> 4=all DelWarnOfId(uint8 ui8HistColOfID) */
					ReplayLastREvalue2Walgo();  /* 27.09.2016 CodeReview CRS_1211_032_121*/
				}
				else
				{
					/*********************************************************************************************/			
					/* plausibility check NOT OK: New tire pressure are not plausible update compare pressure only*/
					SetState2FillingDetectionStateFD(cFILLING_UNPLAUSIBLE); /*CRS_1211_130_181*/	

					//SetBitBetriebszustandBZ(cCAL_MFD_PLAUSI_ERROR); /* CRS_1211_130_101 only if plausibility check NOT OKAY! */
					SetBitBetriebszustandBZ(cCAL_AFD_PLAUSI_ERROR);  /*CRS_1211_130_227 Hier OKAY da "new tire pressure are not plausible", altCRS_1211_130_202*/
					BZ_FZZ_RQ_State4AFD_Finish(); /*CRS_1211_130_267*/
					/*****************************************************************/
					/*update compare pressure value, after Mcalibration CRS_1211_130_150 and first 100km driving Acalibration*/
					/******** CRS_1211_130_157 RELATIV P- VALUE  ***************/
					/*CRS_1211_130_228 Compare value nicht auf 1,9bar deckeln! Hier falsch! ucIdCalPressure wird beim sammeln der AFD Druckwerte auf 1,9bar gedeckelt!!*/
					/*ACHTUNG! AFD speichert in uiStoragePaverege4CompareValue() relative Drucklwerte ZOM spezifisch ab! */
					/*CRS_1211_130_304 Tref mit GETscTref()() synchonisieren*/
					PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdVL)),GETscIdCalTemperatur(ucColOfIdVL), GETscTref()),cRadPosVL);	/*Pvl + Tvl @ Tref: PnewRelativ*/		
					PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdVR)),GETscIdCalTemperatur(ucColOfIdVR), GETscTref()),cRadPosVR);	/*Pvr + Tvr @ Tref: PnewRelativ*/										
					PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdHL)),GETscIdCalTemperatur(ucColOfIdHL), GETscTref()),cRadPosHL);	/*Phl + Thl @ Tref: PnewRelativ*/				
					PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdHR)),GETscIdCalTemperatur(ucColOfIdHR), GETscTref()),cRadPosHR);	/*Phr + Thr @ Tref: PnewRelativ*/
					/*****************************************************************/
					ucRePosStorageVL4FD=ucColOfIdVL; /*CRS_1211_130_336 AFD*/
					ucRePosStorageVR4FD=ucColOfIdVR; /*CRS_1211_130_336 AFD*/
					ucRePosStorageHL4FD=ucColOfIdHL; /*CRS_1211_130_336 AFD*/
					ucRePosStorageHR4FD=ucColOfIdHR; /*CRS_1211_130_336 AFD*/
	
					/*****************************************************************/
				}		
			}
			else /*5.4.3 Filling Detected if warning lamp is ON AND not including all warned wheels */
			{
				ClearBitBetriebszustandBZ(cCAL_AFD_PLAUSI_ERROR);		/*Clear Bit 4  "Filling not detected" (Filling detection flow chart 5.2) */	
				BZ_FZZ_RQ_State4AFD_Finish(); /*CRS_1211_130_267  */
			}
	}
	else
	{
		BZ_FZZ_RQ_State4AFD_Finish(); /*CRS_1211_130_267*/
	}
}

/*-------------------------------------------------------------------------------------------------
** FD_UpdatePressure4AfdWarnLampOFF(uint8,uint8, sint8)
**/
/*
** Description
**/
/*
** Purpose: AFD Kalibrierung: Warning Lamp OFF
**        auto filling detected --> Check condition for Update Pcompare and Pref
**				2 or more wheels inflated od deflated: 5.2 Filling detection flow chart result:(B)
**        filling detected after 100km above the last manual calibration 5.4.2
**
** ------------------------------------------------------------------------------------------------
** Input:      COUNTER 4 ucAfd_Deflated,  COUNTER 4 ucAfd_Inflated, scTemperaturOutside        
**
** Output:             Druckwert
** ------------------------------------------------------------------------------------------------
**/
void FD_UpdatePressure4AfdWarnLampOFF(uint8 ucAfd_Deflated, uint8 ucAfd_Inflated, sint8 scTemperaturOutside)
{
	uint8 ucColOfIdVL,ucColOfIdVR,ucColOfIdHL, ucColOfIdHR;  /*4 CRS_1211_130_075*/
	uint8 i;
	sint8 scTfillVA;
	sint8 scTfillHA;
	sint8 scTfill_Tref;
	uint8 ucRtn=FALSE;

	for( i = 0; i < cAnzRad; i++ ) /*i=ZOMPOS*/
	{
		switch (GETucWPorPWPofHistCol(i))
		{
			case cRadPosVL: 
						ucColOfIdVL=i; /*ZOM/COLpos of cRadPosVL*/
			break;
			case cRadPosVR: 
  					ucColOfIdVR=i; /*ZOM/COLpos of cRadPosVR*/
			break;
			case cRadPosHL: 
						ucColOfIdHL=i; /*ZOM/COLpos of cRadPosVR*/
			break;
			case cRadPosHR: 
 						ucColOfIdHR=i; /*ZOM/COLpos of cRadPosVR*/
			break;
			default:
			{
				ucRtn = TRUE;
			}
		}
	}

	if(((ucRtn == FALSE) && ((GETulLastCalMileage() != c_FFFFkm) && (GETulLastCalMileage() < c_FF9Bkm))) || ((ucRtn == FALSE) && (GETulLastCalMileage() == c_FFFFkm)))  /* OIL#1170*/
	{
			/***************  5.4.2 "Filling Detected" if the warning lamp is OFF  *******************************************************************/
			/***************  1. ODER-Abfrage mit LTS=3 CRS_1211_130_245 */
			/***************  2. ODER-Abfrage CRS_1211_130_246: Attention!! 5.4.2 brandnew ECU without MFD: init value for ulLastCalMileage=0xFFFF!!!*/
			/*if(((ucAfd_Inflated & 0x0F) >= 2) || ((((ucAfd_Deflated & 0x0F) >=2) && (GETulLastCalMileage() != c_FFFFkm) && (GETulKmStand4AutoCAL() > (GETulLastCalMileage() + c_100km))) && (ucAfd_Deflated & 0x80) != 0x80 )*/
			/*|| (((ucAfd_Deflated & 0x0F) >=2) && (GETulLastCalMileage() == c_FFFFkm)))  CRS_1211_130_303 && (GETulKmStand4AutoCAL() < c_100km)  ) )  */

			/***************  CRS_1211_130_307 ****************************************************************************************************************************************************/
			/***************  5.4.2 "Filling Detected" if the warning lamp is OFF  ****************************************************************************************************************/
			/***************  1. kein brandneues SG (MFD war aktiv!) dann: 1a.) mind. 2Räder P aufgefüllt ODER mind.2Räder P abgelassen und 100km zur letzten MFD und für diese Räder kein  LTS=3 */
			/***************  2. brandneues SG und 2a.) mind. 2Räder P aufgefüllt *****************************************************************************************************************/
			if(((GETulLastCalMileage() != c_FFFFkm) && (((ucAfd_Inflated & 0x0F) >= 2) || ((((ucAfd_Deflated & 0x0F) >=2) && (GETulKmStand4AutoCAL() > (GETulLastCalMileage() + c_100km))) && (ucAfd_Deflated & 0x80) != 0x80 )))
			|| (((GETulLastCalMileage() == c_FFFFkm)  && ((ucAfd_Deflated & 0x0F) >=2) ||  ((ucAfd_Inflated & 0x0F) >= 2) ))) // CRS_1211_130_303 && (GETulKmStand4AutoCAL() < c_100km)  ) )  
			{
		
				/* 5.4.2/.3 GETushWarnstatus1WN() == FALSE) => CRS_1211_130_182  2 or more wheels Inflated IMPORTEND:  INCLUDING WARNED WHEEL*/
				ClearBitBetriebszustandBZ(cCAL_AFD_PLAUSI_ERROR); /*Clear Bit 4  "Filling not detected" (Filling detection flow chart 5.2) */	
/********************************************************************************************************************************/
				if(FD_Plausibility_CheckP4DPLR_DPABS(ucColOfIdVL,ucColOfIdVR,ucColOfIdHL,ucColOfIdHR) == TRUE)  /* plausibility check ok: 5.2 Filling detection flow chart result:(B)*/
				{
					
					ucRePosStorageVL4FD=ucColOfIdVL; /*CRS_1211_130_336 AFD*/
					ucRePosStorageVR4FD=ucColOfIdVR; /*CRS_1211_130_336 AFD*/
					ucRePosStorageHL4FD=ucColOfIdHL; /*CRS_1211_130_336 AFD*/
					ucRePosStorageHR4FD=ucColOfIdHR; /*CRS_1211_130_336 AFD*/

					BZ_FZZ_RQ_State4AFD_Finish(); /*CRS_1211_130_267*/
					SetState2FillingDetectionStateFD(cFILLING_DETECTED); /*CRS_1211_130_190 */	 
					/*Average pressure in Pref front and rear axis*/ 
					PUTucPrefFront(((GETucIdCalPressure(ucColOfIdVL) + GETucIdCalPressure(ucColOfIdVR))/2));/*load Average pressure VL,VR*/
					PUTucPrefRear(((GETucIdCalPressure(ucColOfIdHL) + GETucIdCalPressure(ucColOfIdHR))/2));/*load Average pressure HL,HR*/
					/*NONISOCHOR Average pressure in Pfill front and rear axis*/ 
					PUTucPfillFront(GETucPrefFront());	/* CRS_1211_130_268 CRS_1211_130_100 p_fill_front 4 measurement interface*/
					PUTucPfillRear(GETucPrefRear());	/* CRS_1211_130_268 CRS_1211_130_100 p_fill_rear 4 measurement interface*/				

					/******************************************************************************************************************************************************************/
					/* @@@AS 4 01.04.2016						*/
					/*5.8.1.												*/
					/*t_fill_front=		((GETscIdCalTemperatur(ucColOfIdVL) + GETscIdCalTemperatur(ucColOfIdVR))/2); */		
					/*t_fill_rear=		((GETscIdCalTemperatur(ucColOfIdHL) + GETscIdCalTemperatur(ucColOfIdHR))/2);		*/		
					/*t_fill=((GETscIdCalTemperatur(ucColOfIdVL) + GETscIdCalTemperatur(ucColOfIdVR) + GETscIdCalTemperatur(ucColOfIdHL) + GETscIdCalTemperatur(ucColOfIdHR)) /4)*/
					/*t_ref=KweightCalculation(t_fill, tEnvDataToSend.ucTempOut); CRS_1211_130_083 weighting factor K_WEIGHT for Tref*/
					/*        5.8.3 */
					/*P_VA for WARNHANDLER: p_ref_front= (((p_fill_front+1bar)*t_ref+273))/(t_fill_front+273))*/
					/*if p_ref_front <P_MIN_F --> p_ref_front=P_MIN_F*/
					/*P_HA for WARNHANDLER: p_ref_rear= (((p_fill_rear+1bar)*t_ref+273))/(t_fill_rear+273))*/
					/*if p_ref_tear <P_MIN_F --> p_ref_rear=P_MIN_F*/
					/* Rte_Write_PP_Data2Warn_DE_tData2Warn(&tData2Warn); CRS_1211_130_089 */ 
					/*****************************************************************************************************************************************************************/
		
					scTfillVA=((GETscIdCalTemperatur(ucColOfIdVL) + GETscIdCalTemperatur(ucColOfIdVR))/2);/*CRS_1211_130_085*/
					scTfillHA=((GETscIdCalTemperatur(ucColOfIdHL) + GETscIdCalTemperatur(ucColOfIdHR))/2);/*CRS_1211_130_085*/		
					if(scTfillVA > cTfillLimitH) /*CRS_1211_130_219*/
					{
						scTfillVA=cTfillLimitH;
					}
					if(scTfillHA > cTfillLimitH)/*CRS_1211_130_219*/
					{
						scTfillHA=cTfillLimitH;
					}							
					
					scTfill_Tref=(scTfillVA + scTfillHA)/2;
					PUTscTfill(scTfill_Tref);   /* CRS_1211_130_219 to store it for DCM purpose */
					scTfill_Tref=KweightCalculation(scTfill_Tref, scTemperaturOutside); /*CRS_1211_131_083 weighting factor K_WEIGHT for Tref*/
					/* front axis */
					/*CRS_1211_130_309 1. Isochorendruck berechnen, 2. Prüfung auf kleiner Mindestkalibrierdruck! */
					PUTucPrefFront(GetP4NewTempAtCAL(GETucPrefFront(),scTfillVA, scTfill_Tref));	/*CRS_1211_130_268 GetPabs4NewTempAtCAL 4 relativen Druck!VA: 5.8.3 Calculation of the cold tire inflation pressure*/	
					if (GETucPrefFront() <= GETucPcalMinVaRelativCodOfRam()) /* CRS_1211_130_268 NEU relativ ALT:absolut <= absolut*/
					{
						PUTucPrefFront(GETucPcalMinVaRelativCodOfRam());/* CRS_1211_130_268 NEU relativ ALT:absolut <= absolut*/
					}
					/* rear axis */
					/*CRS_1211_130_309 1. Isochorendruck berechnen, 2. Prüfung auf kleiner Mindestkalibrierdruck! */
					PUTucPrefRear(GetP4NewTempAtCAL(GETucPrefRear(),scTfillHA, scTfill_Tref));	/*CRS_1211_130_268 GetPabs4NewTempAtCAL 4 relativen Druck!VA: 5.8.3 Calculation of the cold tire inflation pressure*/
					if (GETucPrefRear() <= GETucPcalMinHaRelativCodOfRam()) /* CRS_1211_130_268 NEU relativ ALT:absolut <= absolut*/
					{
						PUTucPrefRear(GETucPcalMinHaRelativCodOfRam());/* CRS_1211_130_268 NEU relativ ALT:absolut <= absolut*/
					}

	
					PUTscTref(scTfill_Tref);
					/*****************************************************************/
					/*update compare pressure value, after Mcalibration CRS_1211_130_150 and first 100km driving Acalibration*/
					/******** CRS_1211_130_157 RELATIV P- VALUE  ***************/
					/*CRS_1211_130_228 Compare value nicht auf 1,9bar deckeln! Hier falsch! ucIdCalPressure wird beim sammeln der AFD Druckwerte auf 1,9bar gedeckelt!!*/
					/*ACHTUNG! AFD speichert in uiStoragePaverege4CompareValue() relative Drucklwerte ZOM spezifisch ab! */
				
					/*CRS_1211_130_268 relativ pressure always!*/	
					PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdVL)),GETscIdCalTemperatur(ucColOfIdVL), scTfill_Tref),cRadPosVL);	/*Pvl + Tvl @ Tref: PnewRelativ*/		
					PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdVR)),GETscIdCalTemperatur(ucColOfIdVR), scTfill_Tref),cRadPosVR);	/*Pvr + Tvr @ Tref: PnewRelativ*/										
					PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdHL)),GETscIdCalTemperatur(ucColOfIdHL), scTfill_Tref),cRadPosHL);	/*Phl + Thl @ Tref: PnewRelativ*/				
					PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdHR)),GETscIdCalTemperatur(ucColOfIdHR), scTfill_Tref),cRadPosHR);	/*Phr + Thr @ Tref: PnewRelativ*/	
					/*****************************************************************/
					DelWarnOfId(4); /*MFA2: CRS_1211_130_234neu aus papenburg April --> 4=all DelWarnOfId(uint8 ui8HistColOfID) */
					ReplayLastREvalue2Walgo();  /* 27.09.2016 CodeReview CRS_1211_032_121*/

				}
				else
				{
					/*********************************************************************************************/			
					/* plausibility check NOT OK: New tire pressure are not plausible update compare pressure only*/
					SetState2FillingDetectionStateFD(cFILLING_UNPLAUSIBLE); /*CRS_1211_130_181*/	
					//SetBitBetriebszustandBZ(cCAL_MFD_PLAUSI_ERROR); /* CRS_1211_130_101 only if plausibility check NOT OKAY! */
					SetBitBetriebszustandBZ(cCAL_AFD_PLAUSI_ERROR);  /*CRS_1211_130_227 Hier OKAY da "new tire pressure are not plausible", altCRS_1211_130_202*/

					BZ_FZZ_RQ_State4AFD_Finish(); /*CRS_1211_130_267*/
					/*****************************************************************/
					/*update compare pressure value, after Mcalibration CRS_1211_130_150 and first 100km driving Acalibration*/
					/******** CRS_1211_130_157 RELATIV P- VALUE  ***************/
					/*CRS_1211_130_228 Compare value nicht auf 1,9bar deckeln! Hier falsch! ucIdCalPressure wird beim sammeln der AFD Druckwerte auf 1,9bar gedeckelt!!*/
					/*ACHTUNG! AFD speichert in uiStoragePaverege4CompareValue() relative Drucklwerte ZOM spezifisch ab! */
						/*CRS_1211_130_304 Tref mit GETscTref()() synchonisieren*/
					PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdVL)),GETscIdCalTemperatur(ucColOfIdVL), GETscTref()),cRadPosVL);	/*Pvl + Tvl @ Tref: PnewRelativ*/		
					PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdVR)),GETscIdCalTemperatur(ucColOfIdVR), GETscTref()),cRadPosVR);	/*Pvr + Tvr @ Tref: PnewRelativ*/										
					PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdHL)),GETscIdCalTemperatur(ucColOfIdHL), GETscTref()),cRadPosHL);	/*Phl + Thl @ Tref: PnewRelativ*/				
					PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdHR)),GETscIdCalTemperatur(ucColOfIdHR), GETscTref()),cRadPosHR);	/*Phr + Thr @ Tref: PnewRelativ*/	

					ucRePosStorageVL4FD=ucColOfIdVL;	/*CRS_1211_130_336 AFD*/
					ucRePosStorageVR4FD=ucColOfIdVR;	/*CRS_1211_130_336 AFD*/
					ucRePosStorageHL4FD=ucColOfIdHL;	/*CRS_1211_130_336 AFD*/
					ucRePosStorageHR4FD=ucColOfIdHR;	/*CRS_1211_130_336 AFD*/
					/*****************************************************************/
				}
			}
			else
			{
			
				/*1.) Warning lamp = on and one wheel inflated only*/
				SetState2FillingDetectionStateFD(cFILLING_NOT_DETECTED); /*CRS_1211_130_181 +208 Filling Not Detected BUT update compare value */	

				/* ONE wheel inflated or deflated --> 5.2 Filling detection flow chart result:(C)*/
				if((bGetBitBetriebszustandBZ(cCAL_FINISH) != TRUE) && (bGETucCalRequestState(cCAL_AUTO_ACTIV)== TRUE)) /*timeout and calibration empty?*/
				{
					ucRtn = TRUE; /* CRS_1211_130_354*/

					if((ucAfd_Deflated & 0x0F) >= 2) /* 5.4.2 */
					{
						if((ucAfd_Deflated & 0x80) == 0x80) /* ucAfd_Deflated&0x80==0x80 --> LTS=3!! CRS_1211_130_245*/
						{
							SetState2FillingDetectionStateFD(cFD_LTS30DAYS); /*CRS_1211_130_245*/
						}
						else
						{
							if(GETulLastCalMileage() == c_FFFFkm) /*CRS_1211_130_286 noch nie eine MFD aktiv gewesen? */
							{
								if(FD_Plausibility_CheckP4DPLR_DPABS(ucColOfIdVL,ucColOfIdVR,ucColOfIdHL,ucColOfIdHR) == FALSE)  /* plausibility check ok: 5.2 Filling detection flow chart result:(B)*/
								{
									/* plausibility check NOT OK: New tire pressure are not plausible update compare pressure only*/
									SetState2FillingDetectionStateFD(cFILLING_UNPLAUSIBLE); /*CRS_1211_130_286*/	
									SetBitBetriebszustandBZ(cCAL_AFD_PLAUSI_ERROR);  /*CRS_1211_130_286  Hier OKAY da "new tire pressure are not plausible", altCRS_1211_130_202*/
									ucRtn = FALSE;/* CRS_1211_130_354*/
								}
							}
							else
							{
								if(GETulKmStand4AutoCAL() <= (GETulLastCalMileage() + c_100km)) /* CRS_1211_130_286|| (GETulLastCalMileage() == c_FFFFkm)) < fehlt! CRS_1211_130_229*/
								{
									//SetState2AbortReasonFD(cFD_MILEAGE2SMALL);
									SetState2FillingDetectionStateFD(cFD_MILEAGE2SMALL); /*CRS_1211_130_206*/
								}

							}
						}
					}
					/* else  CRS_1211_130_354 KEIN ELSE da 5.5.5 Reset Condition for Implausible Pressure Warning */
					if(ucRtn == TRUE ) /* CRS_1211_130_354*/
					{
						/* 5.5.5 Reset Condition for Implausible Pressure Warnimg*/
						FD_CheckResetCondition4ImplausiMsg(ucColOfIdVL,ucColOfIdVR,ucColOfIdHL,ucColOfIdHR); /* Check Reset Condition 4 Implausible Pressure Warning */
						
					}
				}

				BZ_FZZ_RQ_State4AFD_Finish(); /*CRS_1211_130_267*/ 		
				/*****************************************************************/
				/*update compare pressure value ONLY , after Mcalibration CRS_1211_130_150 and first 100km driving Acalibration*/
				/******** CRS_1211_130_228 + CRS_1211_130_157 RELATIV P- VALUE  ***************/
				/*ACHTUNG! AFD speichert in uiStoragePaverege4CompareValue() relative Drucklwerte ZOM spezifisch ab! */
			
			/*CRS_1211_130_304 Tref mit GETscTref()() synchonisieren*/
				PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdVL)),GETscIdCalTemperatur(ucColOfIdVL), GETscTref()),cRadPosVL);	/*Pvl + Tvl @ Tref: PnewRelativ*/	
				PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdVR)),GETscIdCalTemperatur(ucColOfIdVR), GETscTref()),cRadPosVR);	/*Pvr + Tvr @ Tref: PnewRelativ*/						
				PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdHL)),GETscIdCalTemperatur(ucColOfIdHL), GETscTref()),cRadPosHL);	/*Phl + Thl @ Tref: PnewRelativ*/		
				PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdHR)),GETscIdCalTemperatur(ucColOfIdHR), GETscTref()),cRadPosHR);	/*Phr + Thr @ Tref: PnewRelativ*/	

				/*****************************************************************/
				ucRePosStorageVL4FD=ucColOfIdVL; /*CRS_1211_130_336 AFD*/
				ucRePosStorageVR4FD=ucColOfIdVR; /*CRS_1211_130_336 AFD*/
				ucRePosStorageHL4FD=ucColOfIdHL; /*CRS_1211_130_336 AFD*/
				ucRePosStorageHR4FD=ucColOfIdHR; /*CRS_1211_130_336 AFD*/
				
				ReplayLastREvalue2Walgo();  /*CRS_1211_032_121*/
			}
	}
	else
	{
		BZ_FZZ_RQ_State4AFD_Finish(); /*CRS_1211_130_267*/ 	
	}
}

/*-------------------------------------------------------------------------------------------------
** FD_UpdateComparePressureatWarning()
**/
/*
** Description
**/
/*
** Purpose:   FD Kalibrierung: filling detected
**						5.6.2 Storing compare value (isochore +relativ value) after warning message P&T of THIS TIRE!**
** I_C02_TIRE_STAT_SOFT_WARN (1U)
** I_C02_TIRE_STAT_LOW_PRESS (2U) logical data PAL: CRS_1211_130_268 NEU Relativer Druck  ALT:P_MIN_TIRE 2,5bar!
** I_C02_TIRE_STAT_DEFLATION (3U)
** cDP_STABI=4 --> 100mbar 
** ------------------------------------------------------------------------------------------------
** Input:          
**
** Output:             Druckwert
** ------------------------------------------------------------------------------------------------
**/
void FD_UpdateComparePressureAtWarning(uint8 ucTPM_WarnDisp_Rq4CmpP)
{
	uint8 i;
	uint8 ucColOfIdVL,ucColOfIdVR,ucColOfIdHL, ucColOfIdHR;  /*4 CRS_1211_130_075*/
	uint8 ucPcompareVL,ucPcompareVR,ucPcompareHL,ucPcompareHR;
	uint8 ucLastReceivedTemp; /* OIL#1164 */
	uint8 ucRtn=FALSE;

	if(Getui8ColPWPActive() == FALSE) /*CRS_1211_130_232 CRS_1211_130_210 FALLbackMode activ?*/
	{

		if(ucTPM_WarnDisp_Rq4CmpP != FALSE)
		{
/*********************************************/
			for( i = 0; i < cAnzRad; i++ ) /*i=ZOMPOS*/
			{
				switch (GETucWPorPWPofHistCol(i))
				{
					case cRadPosVL: 
								ucColOfIdVL=i; /*ZOM/COLpos of cRadPosVL*/
					break;
					case cRadPosVR: 
  							ucColOfIdVR=i; /*ZOM/COLpos of cRadPosVR*/
					break;
					case cRadPosHL: 
								ucColOfIdHL=i; /*ZOM/COLpos of cRadPosVR*/
					break;
					case cRadPosHR: 
 								ucColOfIdHR=i; /*ZOM/COLpos of cRadPosVR*/
					break;
					default:
					{
						ucRtn = TRUE;
					}
				}
			}
/*********************************************/

			if(ucRtn == FALSE)
			{

				if((ucGetLastReceivedPress(ulGetID(ucColOfIdVL)) != 0xFF)
				&&(ucGetLastReceivedPress(ulGetID(ucColOfIdVR)) != 0xFF)
				&&(ucGetLastReceivedPress(ulGetID(ucColOfIdHL)) != 0xFF)
				&&(ucGetLastReceivedPress(ulGetID(ucColOfIdHR)) != 0xFF))
				{
					/*ucLastTirePressure = ucGetLastReceivedPress(ulTelID); CRS_1211_130_214*/
					ClearBitBetriebszustandBZ(cCAL_AFD_PLAUSI_ERROR | cCAL_MFD_PLAUSI_ERROR); /*CRS_1211_130_098 if TPMS warning message activ, delete NAK in BZ: reset condition 5.5.5 (4)*/
					//ClearBitBetriebszustandBZ(cCAL_AFD_PLAUSI_ERROR); /*CRS_1211_130_331: PM_WarnDisp_Rq>0 --> reset condition 5.5.5 (4) NO FB Mode*/
					/*@@ASTEST ucGetHMICurrentTirePress= Prelativ  */
					/*********************** VL *********************************/
					
					//ucPcompareVL=GetPrel4NewTempAtCAL((ucGetLastReceivedPress(ulGetID(ucColOfIdVL)) + TirePressureDiffAbsRel),(ucGetLastReceivedTemp(ulGetID(ucColOfIdVL))- ucPalTempNormFACTOR4Calc), scTfill_Tref);
					/*CRS_1211_130_268 relativ pressure always*/
					ucLastReceivedTemp=(ucGetLastReceivedTemp(ulGetID(ucColOfIdVL)));
					if((ucLastReceivedTemp != 0xFF) && (ucLastReceivedTemp != 0x00)) /* OIL#1164 */
					{

						ucPcompareVL=GetP4NewTempAtCAL(ucGetLastReceivedPress(ulGetID(ucColOfIdVL)),((sint8) (ucLastReceivedTemp- ucPalTempNormFACTOR4Calc)), GETscTref());
						if ((ucGetHMICurrentTireStat(cRadPosVL) != I_C02_TIRE_STAT_NORMAL) && (ucStoreCompValueVL== FALSE)) /* Merker=TRUE;*/// && Merker == FALSE @@AS FALSE=no warning /*CRS_1211_130_156*/
						{
							//ucPcompareVL=GetPrel4NewTempAtCAL((ucGetLastReceivedPress(ulGetID(ucColOfIdVL)) + TirePressureDiffAbsRel),(ucGetLastReceivedTemp(ulGetID(ucColOfIdVL))- ucPalTempNormFACTOR4Calc), scTfill_Tref);
							PUTucPosComparePressure(ucPcompareVL,cRadPosVL);
							ucStoreCompValueVL=TRUE; 
							ucRtn=TRUE;
 						}
						else
						{
							if(ucStoreCompValueVL == TRUE)
							{
								//ucPcompareVL=GetPrel4NewTempAtCAL((ucGetLastReceivedPress(ulGetID(ucColOfIdVL)) + TirePressureDiffAbsRel),(ucGetLastReceivedTemp(ulGetID(ucColOfIdVL))- ucPalTempNormFACTOR4Calc), scTfill_Tref);
								if(GETucPosComparePressure(cRadPosVL) > ucPcompareVL)
								{
									if((GETucPosComparePressure(cRadPosVL) - ucPcompareVL) >= cDP_STABI)
									{
										PUTucPosComparePressure(ucPcompareVL,cRadPosVL);/* CRS_1211_130_254+  P relativ NICHT gedeckelt! */
									}
								}
							}
						}
					}
					/*********************** VR *********************************/
					//ucPcompareVR=GetPrel4NewTempAtCAL((ucGetLastReceivedPress(ulGetID(ucColOfIdVR)) + TirePressureDiffAbsRel),(ucGetLastReceivedTemp(ulGetID(ucColOfIdVR))- ucPalTempNormFACTOR4Calc), scTfill_Tref);					
					/*CRS_1211_130_268 relativ pressure always*/
					ucLastReceivedTemp=(ucGetLastReceivedTemp(ulGetID(ucColOfIdVR)));
					if((ucLastReceivedTemp != 0xFF) && (ucLastReceivedTemp != 0x00)) /* OIL#1164 */
					{
						ucPcompareVR=GetP4NewTempAtCAL(ucGetLastReceivedPress(ulGetID(ucColOfIdVR)),((sint8) (ucLastReceivedTemp- ucPalTempNormFACTOR4Calc)), GETscTref());
						if ((ucGetHMICurrentTireStat(cRadPosVR) != I_C02_TIRE_STAT_NORMAL) && (ucStoreCompValueVR== FALSE)) // && Merker == FALSE @@AS FASLE=no warning /*CRS_1211_130_156*/
						{
							//ucPcompareVR=GetPrel4NewTempAtCAL((ucGetLastReceivedPress(ulGetID(ucColOfIdVR)) + TirePressureDiffAbsRel),(ucGetLastReceivedTemp(ulGetID(ucColOfIdVR))- ucPalTempNormFACTOR4Calc), scTfill_Tref);
							PUTucPosComparePressure(ucPcompareVR,cRadPosVR);
							//PUTucPosComparePressure(GetPrel4NewTempAtCAL((ucGetLastReceivedPress(ulGetID(ucGetColOfWP(cRadPosVR))) + TirePressureDiffAbsRel),(ucGetLastReceivedTemp(ulGetID(ucGetColOfWP(cRadPosVR)))- ucPalTempNormFACTOR4Calc), scTfill_Tref),cRadPosVR);
							ucStoreCompValueVR=TRUE; 
							ucRtn=TRUE;
						}
						else
						{
							if(ucStoreCompValueVR == TRUE)
							{
								//ucPcompareVR=GetPrel4NewTempAtCAL((ucGetLastReceivedPress(ulGetID(ucColOfIdVR)) + TirePressureDiffAbsRel),(ucGetLastReceivedTemp(ulGetID(ucColOfIdVR))- ucPalTempNormFACTOR4Calc), scTfill_Tref);
								if(GETucPosComparePressure(cRadPosVR) > ucPcompareVR)
								{
									if((GETucPosComparePressure(cRadPosVR) - ucPcompareVR) >= cDP_STABI)
									{
										PUTucPosComparePressure(ucPcompareVR,cRadPosVR);/* CRS_1211_130_254+  P relativ NICHT gedeckelt! */
									}
								}
							}
						}
					}
					/*********************** HL *********************************/
					//ucPcompareHL=GetPrel4NewTempAtCAL((ucGetLastReceivedPress(ulGetID(ucColOfIdHL)) + TirePressureDiffAbsRel),(ucGetLastReceivedTemp(ulGetID(ucColOfIdHL))- ucPalTempNormFACTOR4Calc), scTfill_Tref);
					/*CRS_1211_130_268 relativ pressure always*/
					ucLastReceivedTemp=(ucGetLastReceivedTemp(ulGetID(ucColOfIdHL)));
					if((ucLastReceivedTemp != 0xFF) && (ucLastReceivedTemp != 0x00)) /* OIL#1164 */
					{
						ucPcompareHL=GetP4NewTempAtCAL(ucGetLastReceivedPress(ulGetID(ucColOfIdHL)),((sint8) (ucLastReceivedTemp- ucPalTempNormFACTOR4Calc)), GETscTref());
						if ((ucGetHMICurrentTireStat(cRadPosHL) != I_C02_TIRE_STAT_NORMAL) && (ucStoreCompValueHL == FALSE)) // && Merker == FALSE @@AS FASLE=no warning /*CRS_1211_130_156*/
						{
							//ucPcompareHL=GetPrel4NewTempAtCAL((ucGetLastReceivedPress(ulGetID(ucColOfIdHL)) + TirePressureDiffAbsRel),(ucGetLastReceivedTemp(ulGetID(ucColOfIdHL))- ucPalTempNormFACTOR4Calc), scTfill_Tref);
							PUTucPosComparePressure(ucPcompareHL,cRadPosHL);
							//PUTucPosComparePressure(GetPrel4NewTempAtCAL((ucGetLastReceivedPress(ulGetID(ucGetColOfWP(cRadPosHL))) + TirePressureDiffAbsRel),(ucGetLastReceivedTemp(ulGetID(ucGetColOfWP(cRadPosHL)))- ucPalTempNormFACTOR4Calc), scTfill_Tref),cRadPosHL);
							//PUTucPosComparePressure(GETucPcalMinHaAbsCodOfRam(),cRadPosHL); /* @@ AS Test*/
							ucStoreCompValueHL=TRUE; 
							ucRtn=TRUE; 
						}
						else
						{
							if(ucStoreCompValueHL == TRUE)
							{
								//ucPcompareHL=GetPrel4NewTempAtCAL((ucGetLastReceivedPress(ulGetID(ucColOfIdHL)) + TirePressureDiffAbsRel),(ucGetLastReceivedTemp(ulGetID(ucColOfIdHL))- ucPalTempNormFACTOR4Calc), scTfill_Tref);
								if(GETucPosComparePressure(cRadPosHL) > ucPcompareHL)
								{
									if((GETucPosComparePressure(cRadPosHL) - ucPcompareHL) >= cDP_STABI)
									{
										PUTucPosComparePressure(ucPcompareHL,cRadPosHL);/* CRS_1211_130_254+  P relativ NICHT gedeckelt! */
									}
								}
							}
						}
					}
					/*********************** HR *********************************/
					//ucPcompareHR=GetPrel4NewTempAtCAL((ucGetLastReceivedPress(ulGetID(ucColOfIdHR)) + TirePressureDiffAbsRel),(ucGetLastReceivedTemp(ulGetID(ucColOfIdHR))- ucPalTempNormFACTOR4Calc), scTfill_Tref);					
					/*CRS_1211_130_268 relativ pressure always*/
					ucLastReceivedTemp=(ucGetLastReceivedTemp(ulGetID(ucColOfIdHR)));
					if((ucLastReceivedTemp != 0xFF) && (ucLastReceivedTemp != 0x00)) /* OIL#1164 */
					{
						ucPcompareHR=GetP4NewTempAtCAL(ucGetLastReceivedPress(ulGetID(ucColOfIdHR)),((sint8) (ucLastReceivedTemp- ucPalTempNormFACTOR4Calc)), GETscTref());
						if ((ucGetHMICurrentTireStat(cRadPosHR) != I_C02_TIRE_STAT_NORMAL) && (ucStoreCompValueHR == FALSE))  // && Merker == FALSE @@AS FASLE=no warning /*CRS_1211_130_156*/
						{
							//ucPcompareHR=GetPrel4NewTempAtCAL((ucGetLastReceivedPress(ulGetID(ucColOfIdHR)) + TirePressureDiffAbsRel),(ucGetLastReceivedTemp(ulGetID(ucColOfIdHR))- ucPalTempNormFACTOR4Calc), scTfill_Tref);
							PUTucPosComparePressure(ucPcompareHR,cRadPosHR);
							//PUTucPosComparePressure(GetPrel4NewTempAtCAL((ucGetLastReceivedPress(ulGetID(ucGetColOfWP(cRadPosHR))) + TirePressureDiffAbsRel),(ucGetLastReceivedTemp(ulGetID(ucGetColOfWP(cRadPosHR)))- ucPalTempNormFACTOR4Calc), scTfill_Tref),cRadPosHR);
							//PUTucPosComparePressure(GETucPcalMinHaAbsCodOfRam(),cRadPosHR); /* @@ AS Test*/
							ucStoreCompValueHR=TRUE; 
							ucRtn=TRUE;
						}
						else
						{
							if(ucStoreCompValueHR == TRUE)
							{
								//ucPcompareHR=GetPrel4NewTempAtCAL((ucGetLastReceivedPress(ulGetID(ucColOfIdHR)) + TirePressureDiffAbsRel),(ucGetLastReceivedTemp(ulGetID(ucColOfIdHR))- ucPalTempNormFACTOR4Calc), scTfill_Tref);
								if(GETucPosComparePressure(cRadPosHR) > ucPcompareHR)
								{
									if((GETucPosComparePressure(cRadPosHR) - ucPcompareHR) >= cDP_STABI)
									{
										PUTucPosComparePressure(ucPcompareHR,cRadPosHR);/* CRS_1211_130_254+  P relativ NICHT gedeckelt! */
									}
								}
							}
						}
					}
					/********** CRS_1211_130_262 **********************************************/
					if(GETucAutoFillDetectionOnOffOfRam() == FALSE) /* FALSE= AFD disabled!!! CRS_1211_130_282*/
					{
						if((ucPcompareVL < GETucMinWarnThresholdOfRam()) /* CRS_1211_130_268 NEU relativer Druck ALT:GETucMinWarnThresholdOfRam() - TirePressureDiffAbsRel */
							||(ucPcompareVR < GETucMinWarnThresholdOfRam())/* CRS_1211_130_268 */
							||(ucPcompareHL < GETucMinWarnThresholdOfRam())/* CRS_1211_130_268 */
							||(ucPcompareHR < GETucMinWarnThresholdOfRam()))/* CRS_1211_130_268 */
						{
							//ClearCalNotAckState(); /*CRS_1211_130_262 reason 2  P_MIN_TIRE  1,5bar! CalNotAck*/	
							ClearCalNotAckState4MFD();/*CRS_1211_130_359 Bit: cCAL_FBM_ACTIV_NAK erhalten! */					
							SetBitCalNotAckState2Ram(cCAL_P_MIN_TIRE_NAK); /*CRS_1211_130_262 reason 2  P_MIN_TIRE  1,5bar! CalNotAck*/
							SetState2AbortReasonFD(cFD_P_MIN_TIRE); /*CRS_1211_130_262 */
							SetState2FillingDetectionStateFD(cFILLING_DETECT_ABORTED); /*CRS_1211_130_262 P_MIN_TIRE*/		
						}
						else
						{
							if(	GETucCalNotAckStateOfRam() ==  cCAL_P_MIN_TIRE_NAK) /*CRS_1211_130_262 reason 2  P_MIN_TIRE  1,5bar! CalNotAck*/	
							{
								//ClearCalNotAckState();/*CRS_1211_130_262 reason 2  P_MIN_TIRE  1,5bar! CalNotAck*/
								ClearCalNotAckState4MFD();/*CRS_1211_130_359 Bit: cCAL_FBM_ACTIV_NAK erhalten! */
								ClearAbortReasonFD();	
								ClearFillingDetectionStateFD();
							}
						}
					}	
					/********************************************************/
					if(ucRtn==TRUE)
					{
						//CRS_1211_130_249 PUTucPosComparePressureNVM();/*CRS_1211_130_150*/  
						ucRtn=FALSE;
					}
				}
			}
		}
		else /* TPMS ohne Warnung!*/
		{
			ucStoreCompValueVL=FALSE;
			ucStoreCompValueVR=FALSE;
			ucStoreCompValueHL=FALSE;
			ucStoreCompValueHR=FALSE;
		}
	}
	else
	{
		FD_AfdStopp4PWP();/*CRS_1211_130_232*/
	}


}

/*-------------------------------------------------------------------------------------------------
** FD_UpdateComparePressureAfterFBM()
**/
/*
** Description
**/
/*
** Purpose:   FD Kalibrierung: filling detected
**						5.6.2 Storing compare value (isochore +relativ value) after FallBackMode
** 
**  
** ------------------------------------------------------------------------------------------------
** Input:          
**
** Output:             Druckwert
** ------------------------------------------------------------------------------------------------
**/
uint8 FD_UpdateComparePressureAfterFBM(void)
{
	uint8 i;
	uint8 ucColOfIdVL,ucColOfIdVR,ucColOfIdHL, ucColOfIdHR; 
	uint8 ucPcompareVL,ucPcompareVR,ucPcompareHL,ucPcompareHR;
	uint8 ucLastReceivedTemp;
	uint8 ucRtn=TRUE;
/*********************************************/
	for( i = 0; i < cAnzRad; i++ ) /*i=ZOMPOS*/
	{
		switch (GETucWPorPWPofHistCol(i))
		{
			case cRadPosVL: 
						ucColOfIdVL=i; /*ZOM/COLpos of cRadPosVL*/
			break;
			case cRadPosVR: 
						ucColOfIdVR=i; /*ZOM/COLpos of cRadPosVR*/
			break;
			case cRadPosHL: 
						ucColOfIdHL=i; /*ZOM/COLpos of cRadPosVR*/
			break;
			case cRadPosHR: 
						ucColOfIdHR=i; /*ZOM/COLpos of cRadPosVR*/
			break;
			default:
			{
				ucRtn = FALSE;				
			}
		}
	}
/*********************************************/
	if(ucRtn == TRUE)
	{
		if((ucGetLastReceivedPress(ulGetID(ucColOfIdVL)) != 0xFF)
			&&(ucGetLastReceivedPress(ulGetID(ucColOfIdVR)) != 0xFF)
			&&(ucGetLastReceivedPress(ulGetID(ucColOfIdHL)) != 0xFF)
			&&(ucGetLastReceivedPress(ulGetID(ucColOfIdHR)) != 0xFF))
		{
			/*ucLastTirePressure = ucGetLastReceivedPress(ulTelID); CRS_1211_130_214*/
			ClearBitBetriebszustandBZ(cCAL_MFD_PLAUSI_ERROR); /*CRS_1211_130_098 if TPMS warning message activ, delete NAK in BZ: reset condition 5.5.5 (3+4)*/
			
			/*********************** VL *********************************/
			ucLastReceivedTemp=ucGetLastReceivedTemp(ulGetID(ucColOfIdVL));
			if((ucLastReceivedTemp != 0xFF) && (ucLastReceivedTemp != 0x00)) /*OIL#1163*/
			{
				ucPcompareVL=GetP4NewTempAtCAL(ucGetLastReceivedPress(ulGetID(ucColOfIdVL)),((sint8)(ucLastReceivedTemp- ucPalTempNormFACTOR4Calc)), GETscTref());
				PUTucPosComparePressure(ucPcompareVL,cRadPosVL);
			}
		
			/*********************** VR *********************************/
			ucLastReceivedTemp=ucGetLastReceivedTemp(ulGetID(ucColOfIdVR));/*OIL#1163*/
			if((ucLastReceivedTemp != 0xFF) && (ucLastReceivedTemp != 0x00))
			{
				ucPcompareVR=GetP4NewTempAtCAL(ucGetLastReceivedPress(ulGetID(ucColOfIdVR)),((sint8)(ucLastReceivedTemp- ucPalTempNormFACTOR4Calc)), GETscTref());
				PUTucPosComparePressure(ucPcompareVR,cRadPosVR);
			}
	
			/*********************** HL *********************************/
			ucLastReceivedTemp=ucGetLastReceivedTemp(ulGetID(ucColOfIdHL));/*OIL#1163*/
			if((ucLastReceivedTemp != 0xFF) && (ucLastReceivedTemp != 0x00))
			{
				ucPcompareHL=GetP4NewTempAtCAL(ucGetLastReceivedPress(ulGetID(ucColOfIdHL)),((sint8)(ucLastReceivedTemp- ucPalTempNormFACTOR4Calc)), GETscTref());
				PUTucPosComparePressure(ucPcompareHL,cRadPosHL);
			}

			/*********************** HR *********************************/
			ucLastReceivedTemp=ucGetLastReceivedTemp(ulGetID(ucColOfIdHR));/*OIL#1163*/
			if((ucLastReceivedTemp != 0xFF) && (ucLastReceivedTemp != 0x00))
			{
				ucPcompareHR=GetP4NewTempAtCAL(ucGetLastReceivedPress(ulGetID(ucColOfIdHR)),((sint8)(ucLastReceivedTemp- ucPalTempNormFACTOR4Calc)), GETscTref());
				PUTucPosComparePressure(ucPcompareHR,cRadPosHR);
			}
			/********** CRS_1211_130_262 **********************************************/
			/*OLI#850 evtl. Fehler hier: wenn AFD disabled NUR die compare werte sichern, kein Ergebnis setzen */

			if((ucPcompareVL < GETucMinWarnThresholdOfRam()) /* CRS_1211_130_268 NEU relativer Druck ALT:GETucMinWarnThresholdOfRam() - TirePressureDiffAbsRel */
				||(ucPcompareVR < GETucMinWarnThresholdOfRam())/* CRS_1211_130_268 */
				||(ucPcompareHL < GETucMinWarnThresholdOfRam())/* CRS_1211_130_268 */
				||(ucPcompareHR < GETucMinWarnThresholdOfRam()))/* CRS_1211_130_268 */
			{
				//ClearCalNotAckState(); /*CRS_1211_130_262 reason 2  P_MIN_TIRE  1,5bar! CalNotAck*/	
				ClearCalNotAckState4MFD();/*CRS_1211_130_359 Bit: cCAL_FBM_ACTIV_NAK erhalten! */										
				SetBitCalNotAckState2Ram(cCAL_P_MIN_TIRE_NAK); /*CRS_1211_130_262 reason 2  P_MIN_TIRE  1,5bar! CalNotAck*/
				SetState2AbortReasonFD(cFD_P_MIN_TIRE); /*CRS_1211_130_262 */
				SetState2FillingDetectionStateFD(cFILLING_DETECT_ABORTED); /*CRS_1211_130_262 P_MIN_TIRE*/		
			}
			else
			{
				ClearFillingDetectionStateFD();/*CRS_1211_130_357*/				
				ClearPlausiFailureFD(); /*CRS_1211_130_357*/
				ClearAbortReasonFD(); /*CRS_1211_130_357*/
			}
		}
		else
		{
			ucRtn = FALSE;			
		}
	}
	return ucRtn;
}


/*-------------------------------------------------------------------------------------------------
** uint8 FD_UpdateIDvalue4MFD() CRS_1211_130_335
**/
/*
** Description
**/
/*
** Purpose:   FD Kalibrierung: filling detected 4 MFD only
**						ID specific P and T to MFD function
** 
**  
** ------------------------------------------------------------------------------------------------
** Input:          
**
** Output:             Non
** ------------------------------------------------------------------------------------------------
**/
uint8 FD_UpdateIDvalue4MFD(void)
{

	uint8 i;
	uint8 ucColOfIdVL,ucColOfIdVR,ucColOfIdHL, ucColOfIdHR; 
	uint32 ulTelID;
	uint8 ucRtn=TRUE;
	uint8 ucReCounter4FDVL,ucReCounter4FDVR,ucReCounter4FDHL,ucReCounter4FDHR;
	//sint8 scTvonReDVL,scTvonReDVR,scTvonReDHL,scTvonReDHR;
	uint8 ucPvonReDVL,ucPvonReDVR,ucPvonReDHL,ucPvonReDHR;
/*********************************************/
	for( i = 0; i < cAnzRad; i++ ) /*i=ZOMPOS*/
	{
		switch (GETucWPorPWPofHistCol(i))
		{
			case cRadPosVL: 
						ucColOfIdVL=i; /*ZOM/COLpos of cRadPosVL*/
			break;
			case cRadPosVR: 
						ucColOfIdVR=i; /*ZOM/COLpos of cRadPosVR*/
			break;
			case cRadPosHL: 
						ucColOfIdHL=i; /*ZOM/COLpos of cRadPosVR*/
			break;
			case cRadPosHR: 
						ucColOfIdHR=i; /*ZOM/COLpos of cRadPosVR*/
			break;
			default:
			{
				ucRtn = FALSE;     /* 4 for unknow --> MFD aborted */
			}
		}
	}

	if(ucRtn == TRUE)
	{
		
		ulTelID =	ulGetID(ucColOfIdVL); /*hole ID auf POS VL*/
		ucReCounter4FDVL=ucGetAvgCntr4FD( ulTelID); /*CRS_1211_130_335*/
		ucPvonReDVL = ucGetAvgPress4FD(ulTelID); /*CRS_1211_130_335*/
		if((ucPvonReDVL != 0xFF)  && (ucPvonReDVL!= 0x00) && (ucReCounter4FDVL !=0xFF ))/* invalid pressure and invalid avg counter*/
		{
			if(ucReCounter4FDVL >= 3) /* VL RE counter >3   */
			{
				PUTucRErecCounter4FDVL(ucReCounter4FDVL); /* Anzahl ID Empfänge*/
				PUTucIdCalPressure(ucPvonReDVL,ucGetColOfID(&ulTelID)); /* Id spezifischer Mittelwert Prelativ, VL ID  */
				PUTuiStoragePaverege4CompareValue(ucPvonReDVL,ucGetColOfID(&ulTelID)); /* P relativ*/	
				PUTscIdCalTemperatur((ucGetLastReceivedTemp(ulTelID)- ucPalTempNormFACTOR4Calc),ucGetColOfID(&ulTelID)); 	
		
				//scTvonReDVL=GETscIdCalTemperatur(ucColOfIdVL);
				//ucPvonReDVL=GETucIdCalPressure(ucColOfIdVL);
			}	
		}
		ulTelID =	ulGetID(ucColOfIdVR); /*hole ID auf POS VR*/
		ucReCounter4FDVR=ucGetAvgCntr4FD( ulTelID); /*CRS_1211_130_335*/
		ucPvonReDVR = ucGetAvgPress4FD(ulTelID); /*CRS_1211_130_335*/
		if((ucPvonReDVR != 0xFF)  && (ucPvonReDVR!= 0x00) && (ucReCounter4FDVR !=0xFF ))/* invalid pressure and invalid avg counter*/
		{
			if(ucReCounter4FDVR >= 3) /* VR RE counter >3   */
			{				
				PUTucRErecCounter4FDVR(ucReCounter4FDVR); /* Anzahl ID Empfänge*/
				PUTucIdCalPressure(ucPvonReDVR,ucGetColOfID(&ulTelID)); /* Id spezifischer Mittelwert Prelativ, VL ID  */
				PUTuiStoragePaverege4CompareValue(ucPvonReDVR,ucGetColOfID(&ulTelID)); /* P relativ*/	
				PUTscIdCalTemperatur((ucGetLastReceivedTemp(ulTelID)- ucPalTempNormFACTOR4Calc),ucGetColOfID(&ulTelID)); 
			
				//scTvonReDVR=GETscIdCalTemperatur(ucColOfIdVR);
				//ucPvonReDVR=GETucIdCalPressure(ucColOfIdVR);
	
			}
		}

		ulTelID =	ulGetID(ucColOfIdHL); /*hole ID auf POS HL*/
		ucPvonReDHL = ucGetAvgPress4FD(ulTelID); /*CRS_1211_130_335*/
		ucReCounter4FDHL=ucGetAvgCntr4FD( ulTelID); /*CRS_1211_130_335*/

		if((ucPvonReDHL != 0xFF)  && (ucPvonReDHL!= 0x00) && (ucReCounter4FDHL !=0xFF ))/* invalid pressure and invalid avg counter*/
		{
			if(ucReCounter4FDHL >= 3 ) /* HL RE counter >3   */
			{				
				PUTucRErecCounter4FDHL(ucReCounter4FDHL); /* Anzahl ID Empfänge*/
				PUTucIdCalPressure(ucPvonReDHL,ucGetColOfID(&ulTelID)); /* Id spezifischer Mittelwert Prelativ, VL ID  */
				PUTuiStoragePaverege4CompareValue(ucPvonReDHL,ucGetColOfID(&ulTelID)); /* P relativ*/	
				PUTscIdCalTemperatur((ucGetLastReceivedTemp(ulTelID)- ucPalTempNormFACTOR4Calc),ucGetColOfID(&ulTelID)); 

				//scTvonReDHL=GETscIdCalTemperatur(ucColOfIdHL);
				//ucPvonReDHL=GETucIdCalPressure(ucColOfIdHL);
			}
		}

		ulTelID =	ulGetID(ucColOfIdHR); /*hole ID auf POS HR*/
		ucPvonReDHR = ucGetAvgPress4FD(ulTelID); /*CRS_1211_130_335*/
		ucReCounter4FDHR=ucGetAvgCntr4FD( ulTelID); 

		if((ucPvonReDHR != 0xFF)  && (ucPvonReDHR != 0x00 ) && (ucReCounter4FDHR !=0xFF ))/* invalid pressure and invalid avg counter*/
		{
			if(ucReCounter4FDHR >= 3 ) /* HR RE received?? */
			{				
				PUTucRErecCounter4FDHR(ucReCounter4FDHR); /* Anzahl ID Empfänge*/
				PUTucIdCalPressure(ucPvonReDHR,ucGetColOfID(&ulTelID)); /* Id spezifischer Mittelwert Prelativ, VL ID  */
				PUTuiStoragePaverege4CompareValue(ucPvonReDHR,ucGetColOfID(&ulTelID)); /* P relativ*/	
				PUTscIdCalTemperatur((ucGetLastReceivedTemp(ulTelID)- ucPalTempNormFACTOR4Calc),ucGetColOfID(&ulTelID)); 
				
				//scTvonReDHR=GETscIdCalTemperatur(ucColOfIdHR);
				//ucPvonReDHR=GETucIdCalPressure(ucColOfIdHR);
			}
		}
	}
	return ucRtn;
}

/*-------------------------------------------------------------------------------------------------
** uint8 FD_LoadIdValues4MFD() CRS_1211_130_335
**/
/*
** Description
**/
/*
** Purpose:   FD Kalibrierung: ZO Timeout+ZO_Finish and MFD activ 
**						ID specific P and T to MFD function
**						Without check LTS mode
**  
** ------------------------------------------------------------------------------------------------
** Input:          
**
** Output:             Non
** ------------------------------------------------------------------------------------------------
**/
uint8 FD_LoadIdValues4MFD(void)
{

	uint8 i;
	uint8 ucColOfIdVL,ucColOfIdVR,ucColOfIdHL, ucColOfIdHR; 
	uint32 ulTelID;
	uint8 ucRtn=TRUE;
	//uint8 ucTmpPiso4Cal;
	uint8 ucReCounter4FDVL,ucReCounter4FDVR,ucReCounter4FDHL,ucReCounter4FDHR;
	//sint8 scTvonReDVL,scTvonReDVR,scTvonReDHL,scTvonReDHR;
	uint8 ucPvonReDVL,ucPvonReDVR,ucPvonReDHL,ucPvonReDHR;

/*********************************************/
	for( i = 0; i < cAnzRad; i++ ) /*i=ZOMPOS*/
	{
		switch (GETucWPorPWPofHistCol(i))
		{
			case cRadPosVL: 
						ucColOfIdVL=i; /*ZOM/COLpos of cRadPosVL*/
			break;
			case cRadPosVR: 
						ucColOfIdVR=i; /*ZOM/COLpos of cRadPosVR*/
			break;
			case cRadPosHL: 
						ucColOfIdHL=i; /*ZOM/COLpos of cRadPosVR*/
			break;
			case cRadPosHR: 
						ucColOfIdHR=i; /*ZOM/COLpos of cRadPosVR*/
			break;
			default:
			{
				ucRtn = FALSE;
			}				
		}
	}

	if(ucRtn == TRUE) 
	{
		/* VL **********************************************************************************/
		ulTelID =	ulGetID(ucColOfIdVL); /*hole ID auf POS VL*/
		ucReCounter4FDVL=ucGetAvgCntr4FD( ulTelID);
		ucPvonReDVL = ucGetAvgPress4FD(ulTelID);
		if((ucPvonReDVL != 0xFF)  && (ucPvonReDVL!= 0x00) && (ucReCounter4FDVL !=0xFF ))/* invalid pressure and invalid avg counter*/
		{
			if(ucReCounter4FDVL >= 3) /* VL RE counter >3   */
			{
				PUTucRErecCounter4FDVL(ucReCounter4FDVL); /* Anzahl ID Empfänge für Messechnik Ausgabe wie INCucRErecCounter4FDVL*/
				PUTucIdCalPressure(ucPvonReDVL,ucGetColOfID(&ulTelID)); /* Id spezifischer Mittelwert Prelativ, VL ID  */
				PUTuiStoragePaverege4CompareValue(ucPvonReDVL,ucGetColOfID(&ulTelID)); /* P relativ*/	
				PUTscIdCalTemperatur((ucGetLastReceivedTemp(ulTelID)- ucPalTempNormFACTOR4Calc),ucGetColOfID(&ulTelID)); 	
				
				//scTvonReDVL=GETscIdCalTemperatur(ucColOfIdVL);
				//ucPvonReDVL=GETucIdCalPressure(ucColOfIdVL);
				//ucPvonReDVL=ucGetLastReceivedPress(ulTelID); /* Prüfe mit zuletzt empfangenen Druck!! OHNE MITTELWERTBILDUNG --> 0xFF*/
			}
		}
		/* VR **********************************************************************************/
		ulTelID =	ulGetID(ucColOfIdVR); /*hole ID auf POS VR*/
		ucReCounter4FDVR=ucGetAvgCntr4FD( ulTelID);
		ucPvonReDVR = ucGetAvgPress4FD(ulTelID);
		if((ucPvonReDVR != 0xFF)  && (ucPvonReDVR!= 0x00) && (ucReCounter4FDVR !=0xFF ))/* invalid pressure and invalid avg counter*/
		{
			if(ucReCounter4FDVR >= 3) /* VR RE counter >3   */
			{				
				PUTucRErecCounter4FDVR(ucReCounter4FDVR); /* Anzahl ID Empfänge*/
				PUTucIdCalPressure(ucPvonReDVR,ucGetColOfID(&ulTelID)); /* Id spezifischer Mittelwert Prelativ, VL ID  */
				PUTuiStoragePaverege4CompareValue(ucPvonReDVR,ucGetColOfID(&ulTelID)); /* P relativ*/	
				PUTscIdCalTemperatur((ucGetLastReceivedTemp(ulTelID)- ucPalTempNormFACTOR4Calc),ucGetColOfID(&ulTelID)); 
			
				//scTvonReDVR=GETscIdCalTemperatur(ucColOfIdVR);
				//ucPvonReDVR=GETucIdCalPressure(ucColOfIdVR);
				//ucPvonReDVR=ucGetLastReceivedPress(ulTelID); /* Prüfe mit zuletzt empfangenen Druck!! OHNE MITTELWERTBILDUNG --> 0xFF*/
			}
		}
		/* HL **********************************************************************************/
		ulTelID =	ulGetID(ucColOfIdHL); /*hole ID auf POS HL*/
		ucPvonReDHL = ucGetAvgPress4FD(ulTelID);
		ucReCounter4FDHL=ucGetAvgCntr4FD( ulTelID);

		if((ucPvonReDHL != 0xFF)  && (ucPvonReDHL!= 0x00) && (ucReCounter4FDHL !=0xFF ))/* invalid pressure and invalid avg counter*/
		{
			if(ucReCounter4FDHL >= 3 ) /* HL RE counter >3   */
			{				
				PUTucRErecCounter4FDHL(ucReCounter4FDHL); /* Anzahl ID Empfänge*/
				PUTucIdCalPressure(ucPvonReDHL,ucGetColOfID(&ulTelID)); /* Id spezifischer Mittelwert Prelativ, VL ID  */
				PUTuiStoragePaverege4CompareValue(ucPvonReDHL,ucGetColOfID(&ulTelID)); /* P relativ*/	
				PUTscIdCalTemperatur((ucGetLastReceivedTemp(ulTelID)- ucPalTempNormFACTOR4Calc),ucGetColOfID(&ulTelID)); 

				//scTvonReDHL=GETscIdCalTemperatur(ucColOfIdHL);
				//ucPvonReDHL=GETucIdCalPressure(ucColOfIdHL);
				//ucPvonReDHL=ucGetLastReceivedPress(ulTelID); /* Prüfe mit zuletzt empfangenen Druck!! OHNE MITTELWERTBILDUNG --> 0xFF*/
			}
		}
		/* HR **********************************************************************************/
		ulTelID =	ulGetID(ucColOfIdHR); /*hole ID auf POS HR*/
		ucPvonReDHR = ucGetAvgPress4FD(ulTelID);
		ucReCounter4FDHR=ucGetAvgCntr4FD( ulTelID);

		if((ucPvonReDHR != 0xFF)  && (ucPvonReDHR != 0x00 ) && (ucReCounter4FDHR !=0xFF ))/* invalid pressure and invalid avg counter*/
		{
			if(ucReCounter4FDHR >= 3 ) /* HR RE received?? */
			{				
				PUTucRErecCounter4FDHR(ucReCounter4FDHR); /* Anzahl ID Empfänge*/
				PUTucIdCalPressure(ucPvonReDHR,ucGetColOfID(&ulTelID)); /* Id spezifischer Mittelwert Prelativ, VL ID  */
				PUTuiStoragePaverege4CompareValue(ucPvonReDHR,ucGetColOfID(&ulTelID)); /* P relativ*/	
				PUTscIdCalTemperatur((ucGetLastReceivedTemp(ulTelID)- ucPalTempNormFACTOR4Calc),ucGetColOfID(&ulTelID)); 
				
				//scTvonReDHR=GETscIdCalTemperatur(ucColOfIdHR);
				//ucPvonReDHR=GETucIdCalPressure(ucColOfIdHR);
				//ucPvonReDHR=ucGetLastReceivedPress(ulTelID); /* Prüfe mit zuletzt empfangenen Druck!! OHNE MITTELWERTBILDUNG --> 0xFF*/
			}
		}
	}
	return ucRtn; /* TRUE = reload ID Values 4 MFD Checker OKAY!*/
}
/*-------------------------------------------------------------------------------------------------
** uint8 FD_TimeoutHandle4AFD() CRS_1211_130_335
**/
/*
** Description
**/
/*
** Purpose:   FD Kalibrierung: Timeout filling detected in AFD
**						ID specific P and T to AFD function
**						Without check LTS mode
**  
** ------------------------------------------------------------------------------------------------
** Input:          
**
** Output:             Non
** ------------------------------------------------------------------------------------------------
**/
uint8 FD_TimeoutHandle4AFD(void)
{

	uint8 i;
	uint8 ucColOfIdVL,ucColOfIdVR,ucColOfIdHL, ucColOfIdHR; 
	uint32 ulTelID;
	uint8 ucRtn=TRUE;
	uint8 ucTmpPiso4Cal;
	uint8 ucReCounter4FDVL,ucReCounter4FDVR,ucReCounter4FDHL,ucReCounter4FDHR;
	sint8 scTvonReDVL,scTvonReDVR,scTvonReDHL,scTvonReDHR;
	uint8 ucPvonReDVL,ucPvonReDVR,ucPvonReDHL,ucPvonReDHR;

/*********************************************/
	for( i = 0; i < cAnzRad; i++ ) /*i=ZOMPOS*/
	{
		switch (GETucWPorPWPofHistCol(i))
		{
			case cRadPosVL: 
						ucColOfIdVL=i; /*ZOM/COLpos of cRadPosVL*/
			break;
			case cRadPosVR: 
						ucColOfIdVR=i; /*ZOM/COLpos of cRadPosVR*/
			break;
			case cRadPosHL: 
						ucColOfIdHL=i; /*ZOM/COLpos of cRadPosVR*/
			break;
			case cRadPosHR: 
						ucColOfIdHR=i; /*ZOM/COLpos of cRadPosVR*/
			break;
			default:
			{
				ucRtn = FALSE;
			}				
		}
	}

	if(ucRtn == TRUE) /* Im Fall von provisorische Radzuordnung ABBRUCH AUCH BEI TIMEOUT AFD!*/
	{
		PUTucCnt4DP_FILL_IFL(0);	
		PUTucCnt4DP_FILL_DFL(0);  
		PUTucLockByt4DFL_LTS(0);		

/* VL **********************************************************************************/
		ulTelID =	ulGetID(ucColOfIdVL); /*hole ID auf POS VL*/
		ucReCounter4FDVL=ucGetAvgCntr4FD( ulTelID);
		ucPvonReDVL = ucGetAvgPress4FD(ulTelID);
		if((ucPvonReDVL != 0xFF)  && (ucPvonReDVL!= 0x00) && (ucReCounter4FDVL !=0xFF ))/* invalid pressure and invalid avg counter*/
		{
			if(ucReCounter4FDVL >= 3) /* VL RE counter >3   */
			{
				PUTucRErecCounter4FDVL(ucReCounter4FDVL); /* Anzahl ID Empfänge für Messechnik Ausgabe wie INCucRErecCounter4FDVL*/
				PUTucIdCalPressure(ucPvonReDVL,ucGetColOfID(&ulTelID)); /* Id spezifischer Mittelwert Prelativ, VL ID  */
				PUTuiStoragePaverege4CompareValue(ucPvonReDVL,ucGetColOfID(&ulTelID)); /* P relativ*/	
				PUTscIdCalTemperatur((ucGetLastReceivedTemp(ulTelID)- ucPalTempNormFACTOR4Calc),ucGetColOfID(&ulTelID)); 	
				
				scTvonReDVL=GETscIdCalTemperatur(ucColOfIdVL);
				//ucPvonReDVL=GETucIdCalPressure(ucColOfIdVL);
				ucPvonReDVL=ucGetLastReceivedPress(ulTelID); /* Prüfe mit zuletzt empfangenen Druck!! OHNE MITTELWERTBILDUNG --> 0xFF*/
				if(FD_CheckP4AFDstartReason2_3FA(ucPvonReDVL,0xFF,scTvonReDVL,ucColOfIdVL) == FALSE)	/*CRS_1211_130_305 cPMIN;cDP_AUTO;cCAL_RE30K2AMBIENT, DP_STABI	auch im Stand!*/
				{								
					ucRtn = FALSE;     /* AFD aborted -> FALSE*/
				}
				else
				{
					/************* VL: check DP_FILL now 2 wheels are inflated or deflated *******************/
					if(ucReCounter4FDVL >= 3)
					{
						ucTmpPiso4Cal= GetP4NewTempAtCAL(((uint8) GETuiStoragePaverege4CompareValue(ucColOfIdVL)),scTvonReDVL, GETscTref());/*CRS_1211_130_298*/
						if(ucTmpPiso4Cal >  GETucPosComparePressure(cRadPosVL)) /*Relativ*/
						{
							if((ucTmpPiso4Cal - GETucPosComparePressure(cRadPosVL)) >= cDP_FILL) /* CRS_1211_130_194 >=!!  CurrentP- LastP > 200mbar --> inflated IFL*/
							{
								if(GETucCnt4DP_FILL_IFLloggedFL() == FALSE)/*CRS_1211_130_371*/
								{
									INCucCnt4DP_FILL_IFL();
									PUTucCnt4DP_FILL_IFLloggedFL();/* cDP_FILL_FL add 0x10 Ident4FL */
								}
								//INCucCnt4DP_FILL_IFL();
								//PUTucCnt4DP_FILL_IFLloggedFL();	/* cDP_FILL_FL add 0x10 Ident4FL ! CRS_1211_130_220  */ 
							}
						}
						else
						{
							if((GETucPosComparePressure(cRadPosVL) - ucTmpPiso4Cal) >= cDP_FILL)/*CRS_1211_130_194 >=!! LastP-CurrentP > 200mbar --> deflated DFL*/
							{
								if(GETucCnt4DP_FILL_DFLloggedFL() == FALSE)/*CRS_1211_130_371*/
								{
									INCucCnt4DP_FILL_DFL();
									PUTucCnt4DP_FILL_DFLloggedFL();
								}
							}
						}
					}
				}
			}	
		}		
		/* VR **********************************************************************************/
		ulTelID =	ulGetID(ucColOfIdVR); /*hole ID auf POS VR*/
		ucReCounter4FDVR=ucGetAvgCntr4FD( ulTelID);
		ucPvonReDVR = ucGetAvgPress4FD(ulTelID);
		if((ucPvonReDVR != 0xFF)  && (ucPvonReDVR!= 0x00) && (ucReCounter4FDVR !=0xFF ))/* invalid pressure and invalid avg counter*/
		{
			if(ucReCounter4FDVR >= 3) /* VR RE counter >3   */
			{				
				PUTucRErecCounter4FDVR(ucReCounter4FDVR); /* Anzahl ID Empfänge*/
				PUTucIdCalPressure(ucPvonReDVR,ucGetColOfID(&ulTelID)); /* Id spezifischer Mittelwert Prelativ, VL ID  */
				PUTuiStoragePaverege4CompareValue(ucPvonReDVR,ucGetColOfID(&ulTelID)); /* P relativ*/	
				PUTscIdCalTemperatur((ucGetLastReceivedTemp(ulTelID)- ucPalTempNormFACTOR4Calc),ucGetColOfID(&ulTelID)); 
			
				scTvonReDVR=GETscIdCalTemperatur(ucColOfIdVR);
				//ucPvonReDVR=GETucIdCalPressure(ucColOfIdVR);
				ucPvonReDVR=ucGetLastReceivedPress(ulTelID); /* Prüfe mit zuletzt empfangenen Druck!! OHNE MITTELWERTBILDUNG --> 0xFF*/
				if(FD_CheckP4AFDstartReason2_3FA(ucPvonReDVR,0xFF,scTvonReDVR,ucColOfIdVR) == FALSE)	/*CRS_1211_130_305 cPMIN;cDP_AUTO;cCAL_RE30K2AMBIENT, DP_STABI	auch im Stand!*/
				{								
					ucRtn = FALSE;     /* AFD aborted -> F*/
				}
				else
				{
					/************* VR: check DP_FILL now 2 wheels are inflated or deflated *******************/
					if(ucReCounter4FDVR >= 3)
					{
						ucTmpPiso4Cal= GetP4NewTempAtCAL(((uint8) GETuiStoragePaverege4CompareValue(ucColOfIdVR)),scTvonReDVR, GETscTref());/*CRS_1211_130_298*/
						if(ucTmpPiso4Cal >  GETucPosComparePressure(cRadPosVR)) /*Relativ*/
						{
							if((ucTmpPiso4Cal - GETucPosComparePressure(cRadPosVR)) >= cDP_FILL) /* CRS_1211_130_194 >=!!  CurrentP- LastP > 200mbar --> inflated IFL*/
							{
								if(GETucCnt4DP_FILL_IFLloggedFR() == FALSE)
								{
									INCucCnt4DP_FILL_IFL();
									PUTucCnt4DP_FILL_IFLloggedFR();	/* cDP_FILL_FR add 0x20 Ident4FR */ 
								}
								//INCucCnt4DP_FILL_IFL();
								//PUTucCnt4DP_FILL_IFLloggedFR();	/* cDP_FILL_FR add 0x20 Ident4FR ! CRS_1211_130_220  */ 
							}
						}
						else
						{
							if((GETucPosComparePressure(cRadPosVR) - ucTmpPiso4Cal) >= cDP_FILL)/*CRS_1211_130_194 >=!! LastP-CurrentP > 200mbar --> deflated DFL*/
							{
								INCucCnt4DP_FILL_DFL();
							}
						}
					}
				}	
			}
		}
		/* HL **********************************************************************************/
		ulTelID =	ulGetID(ucColOfIdHL); /*hole ID auf POS HL*/
		ucPvonReDHL = ucGetAvgPress4FD(ulTelID);
		ucReCounter4FDHL=ucGetAvgCntr4FD( ulTelID);

		if((ucPvonReDHL != 0xFF)  && (ucPvonReDHL!= 0x00) && (ucReCounter4FDHL !=0xFF ))/* invalid pressure and invalid avg counter*/
		{
			if(ucReCounter4FDHL >= 3 ) /* HL RE counter >3   */
			{				
				PUTucRErecCounter4FDHL(ucReCounter4FDHL); /* Anzahl ID Empfänge*/
				PUTucIdCalPressure(ucPvonReDHL,ucGetColOfID(&ulTelID)); /* Id spezifischer Mittelwert Prelativ, VL ID  */
				PUTuiStoragePaverege4CompareValue(ucPvonReDHL,ucGetColOfID(&ulTelID)); /* P relativ*/	
				PUTscIdCalTemperatur((ucGetLastReceivedTemp(ulTelID)- ucPalTempNormFACTOR4Calc),ucGetColOfID(&ulTelID)); 

				scTvonReDHL=GETscIdCalTemperatur(ucColOfIdHL);
				//ucPvonReDHL=GETucIdCalPressure(ucColOfIdHL);
				ucPvonReDHL=ucGetLastReceivedPress(ulTelID); /* Prüfe mit zuletzt empfangenen Druck!! OHNE MITTELWERTBILDUNG --> 0xFF*/
				if(FD_CheckP4AFDstartReason2_3RA(ucPvonReDHL,0xFF,scTvonReDHL,ucColOfIdHL) == FALSE)	/*CRS_1211_130_305 cPMIN;cDP_AUTO;cCAL_RE30K2AMBIENT, DP_STABI	auch im Stand!*/
				{								
					ucRtn = FALSE;     /* AFD aborted -> F*/
				}
				else
				{
					/************* HL: check DP_FILL now 2 wheels are inflated or deflated *******************/
					if(ucReCounter4FDHL >= 3)
					{
						ucTmpPiso4Cal= GetP4NewTempAtCAL(((uint8) GETuiStoragePaverege4CompareValue(ucColOfIdHL)),scTvonReDHL, GETscTref());/*CRS_1211_130_298*/
						if(ucTmpPiso4Cal >  GETucPosComparePressure(cRadPosHL)) /*Relativ*/
						{
							if((ucTmpPiso4Cal - GETucPosComparePressure(cRadPosHL)) >= cDP_FILL) /* CRS_1211_130_194 >=!!  CurrentP- LastP > 200mbar --> inflated IFL*/
							{
								if(GETucCnt4DP_FILL_IFLloggedRL() == FALSE)/*CRS_1211_130_371*/
								{
									INCucCnt4DP_FILL_IFL();
									PUTucCnt4DP_FILL_IFLloggedRL();	/* cDP_FILL_RL add 0x40 Ident4RL */ 
								}					
								//INCucCnt4DP_FILL_IFL();
								//PUTucCnt4DP_FILL_IFLloggedRL();	/* cDP_FILL_FL add 0x40 Ident4RL ! CRS_1211_130_220  */ 
							}
						}
						else
						{
							if((GETucPosComparePressure(cRadPosHL) - ucTmpPiso4Cal) >= cDP_FILL)/*CRS_1211_130_194 >=!! LastP-CurrentP > 200mbar --> deflated DFL*/
							{
								if(GETucCnt4DP_FILL_DFLloggedRL() == FALSE)/*CRS_1211_130_371*/
								{
									INCucCnt4DP_FILL_DFL();
									PUTucCnt4DP_FILL_DFLloggedRL();/* cDP_FILL_RL add 0x40 Ident4RL */ 
								}
							}
						}
					}
				}
			}
		}
		/* HR **********************************************************************************/
		ulTelID =	ulGetID(ucColOfIdHR); /*hole ID auf POS HR*/
		ucPvonReDHR = ucGetAvgPress4FD(ulTelID);
		ucReCounter4FDHR=ucGetAvgCntr4FD( ulTelID);

		if((ucPvonReDHR != 0xFF)  && (ucPvonReDHR != 0x00 ) && (ucReCounter4FDHR !=0xFF ))/* invalid pressure and invalid avg counter*/
		{
			if(ucReCounter4FDHR >= 3 ) /* HR RE received?? */
			{				
				PUTucRErecCounter4FDHR(ucReCounter4FDHR); /* Anzahl ID Empfänge*/
				PUTucIdCalPressure(ucPvonReDHR,ucGetColOfID(&ulTelID)); /* Id spezifischer Mittelwert Prelativ, VL ID  */
				PUTuiStoragePaverege4CompareValue(ucPvonReDHR,ucGetColOfID(&ulTelID)); /* P relativ*/	
				PUTscIdCalTemperatur((ucGetLastReceivedTemp(ulTelID)- ucPalTempNormFACTOR4Calc),ucGetColOfID(&ulTelID)); 
				
				scTvonReDHR=GETscIdCalTemperatur(ucColOfIdHR);
				//ucPvonReDHR=GETucIdCalPressure(ucColOfIdHR);
				ucPvonReDHR=ucGetLastReceivedPress(ulTelID); /* Prüfe mit zuletzt empfangenen Druck!! OHNE MITTELWERTBILDUNG --> 0xFF*/

				if(FD_CheckP4AFDstartReason2_3RA(ucPvonReDHR,0xFF,scTvonReDHR,ucColOfIdHR) == FALSE)	/*CRS_1211_130_305 cPMIN;cDP_AUTO;cCAL_RE30K2AMBIENT, DP_STABI	auch im Stand!*/
				{								
					ucRtn = FALSE;     /* AFD aborted -> F*/
				}
				else
				{
					/************* HR: check DP_FILL now 2 wheels are inflated or deflated *******************/
					if(ucReCounter4FDHR >= 3)
					{
						ucTmpPiso4Cal= GetP4NewTempAtCAL(((uint8) GETuiStoragePaverege4CompareValue(ucColOfIdHR)),scTvonReDHR, GETscTref());/*CRS_1211_130_298*/
						if(ucTmpPiso4Cal >  GETucPosComparePressure(cRadPosHR)) /*Relativ*/
						{
							if((ucTmpPiso4Cal - GETucPosComparePressure(cRadPosHR)) >= cDP_FILL) /* CRS_1211_130_194 >=!!  CurrentP- LastP > 200mbar --> inflated IFL*/
							{
								if(GETucCnt4DP_FILL_IFLloggedRR() == FALSE)/*CRS_1211_130_371*/
								{
									INCucCnt4DP_FILL_IFL();
									PUTucCnt4DP_FILL_IFLloggedRR();	/* cDP_FILL_RR add 0x80 Ident4RR */ 
								}
								//INCucCnt4DP_FILL_IFL();
								//PUTucCnt4DP_FILL_IFLloggedRR();	/* cDP_FILL_FL add 0x10 Ident4FL ! CRS_1211_130_220  */ 
							}
						}
						else
						{
							if((GETucPosComparePressure(cRadPosHR) - ucTmpPiso4Cal) >= cDP_FILL)/*CRS_1211_130_194 >=!! LastP-CurrentP > 200mbar --> deflated DFL*/
							{
								if(GETucCnt4DP_FILL_DFLloggedRR() == FALSE)/*CRS_1211_130_371*/
								{
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
	return ucRtn; /* TRUE = AFDtimeout handle OKAY!*/
}

/*-------------------------------------------------------------------------------------------------
** uint8 FD_LoadIdValues4UpdateCompareValue() CRS_1211_130_340  CRS_1211_130_363
**/
/*
** Description
**/
/*
** Purpose:   Update compare value 4 NEW Sensor: New Sensor + Whitout FD, New Sensor + AFDII or AFDIII aktiv 
**						ID specific P iso in compare value 
**            Check Pmin
**						
**  
** ------------------------------------------------------------------------------------------------
** Input:          
**
** Output:             Non
** ------------------------------------------------------------------------------------------------
**/
uint8 FD_LoadIdValues4UpdateCompareValue(void)
{

	uint8 i;
	uint8 ucColOfIdVL,ucColOfIdVR,ucColOfIdHL, ucColOfIdHR; 
	uint32 ulTelID;
	uint8 ucRtn=TRUE;
	sint8 scTvonReDxx;
	uint8 ucPvonReDxx;
	uint8 ucPmin=FALSE;/*CRS_1211_130_360*/

		/*********************************************/
		for( i = 0; i < cAnzRad; i++ ) /*i=ZOMPOS*/
		{
			switch (GETucWPorPWPofHistCol(i))
			{
				case cRadPosVL: 
							ucColOfIdVL=i; /*ZOM/COLpos of cRadPosVL*/
				break;
				case cRadPosVR: 
							ucColOfIdVR=i; /*ZOM/COLpos of cRadPosVR*/
				break;
				case cRadPosHL: 
							ucColOfIdHL=i; /*ZOM/COLpos of cRadPosVR*/
				break;
				case cRadPosHR: 
							ucColOfIdHR=i; /*ZOM/COLpos of cRadPosVR*/
				break;
				case cRadPosUkw: 
							ucRtn = cRadPosUkw;; /*unknow =4  handling tbd 4 as */
				break;
				default:
				{
					ucRtn = FALSE;
				}				
			}
		}
		if(ucRtn == TRUE) /* CRS_1211_130_363  Im Fall von provisorische Radzuordnung ABBRUCH AUCH BEI TIMEOUT AFD!*/
		{


			/* VL **********************************************************************************/
			/* ALT if((GetNewIdColX4FD( ucColOfIdVL ) == TRUE) || (bGETucCalRequestState(cCAL_AUTO_ENABLE2) == TRUE ) || (bGETucCalRequestState(cCAL_AUTO_ENABLE3) == TRUE )) Prüfe ob VL new ID? */
			/* CRS_1211_130_373: ucRePosStorageVL4FD == 0xFF bedeutet, wenn keine NEUE RE dann ein Wechsel der vorhandenen RE auf andere Position*/
			if((GetNewIdColX4FD( ucColOfIdVL ) == TRUE) || (bGetBitBetriebszustandBZ(cCAL_REQUEST) == TRUE)  || ( ucRePosStorageVL4FD == 0xFF))  /*Prüfe ob VL new ID? CRS_1211_130_372*/
			{
				ulTelID =	ulGetID(ucColOfIdVL); /*hole ID auf POS VL*/
				//cReCounter4FDVL=ucGetAvgCntr4FD( ulTelID);
				//ucPvonReDVL = ucGetAvgPress4FD(ulTelID);
				ucPvonReDxx=ucGetLastReceivedPress(ulTelID); /* Prüfe mit zuletzt empfangenen Druck!! OHNE MITTELWERTBILDUNG --> 0xFF*/

				if((ucPvonReDxx != 0xFF)  && (ucPvonReDxx != 0x00))/* invalid pressure and invalid avg counter*/
				{
					scTvonReDxx=(signed) (ucGetLastReceivedTemp(ulTelID) - ucPalTempNormFACTOR4Calc);
					PUTucPosComparePressure(GetP4NewTempAtCAL(ucPvonReDxx,scTvonReDxx,GETscTref()),cRadPosVL);/*CRS_1211_130_340 Pvl + Tvl @ Tref: PnewRelativ 4 New ID is learnt*/		
					ClearNewIdColXMem4FD(ucColOfIdVL);/* CRS_1211_130_356 Schalte new ID VL ab! */
					if(ucPvonReDxx < GETucMinWarnThresholdOfRam())/*CRS_1211_130_360*/
					{
						ucPmin|=cFD_Pmin_FL;
					}
				}
				else 
				{
					ucRtn = FALSE;/*CRS_1211_130_356 pressure not available */
				}
			}
			
			/* VR **********************************************************************************/
			if((GetNewIdColX4FD( ucColOfIdVR ) == TRUE) || (bGetBitBetriebszustandBZ(cCAL_REQUEST) == TRUE) || ( ucRePosStorageVR4FD == 0xFF)) /*Prüfe ob VR new ID? CRS_1211_130_372*/
			{
				ulTelID =	ulGetID(ucColOfIdVR); /*hole ID auf POS VR*/
				//ucReCounter4FDVR=ucGetAvgCntr4FD( ulTelID);
				//ucPvonReDVR = ucGetAvgPress4FD(ulTelID);
				ucPvonReDxx=ucGetLastReceivedPress(ulTelID); /* Prüfe mit zuletzt empfangenen Druck!! OHNE MITTELWERTBILDUNG --> 0xFF*/

				if((ucPvonReDxx != 0xFF)  && (ucPvonReDxx != 0x00))/* invalid pressure and invalid avg counter*/
				{
					scTvonReDxx=(signed) (ucGetLastReceivedTemp(ulTelID) - ucPalTempNormFACTOR4Calc);
					PUTucPosComparePressure(GetP4NewTempAtCAL(ucPvonReDxx,scTvonReDxx,GETscTref()),cRadPosVR);/*CRS_1211_130_340 Pvr + Tvr @ Tref: PnewRelativ 4 New ID is learnt*/	
					ClearNewIdColXMem4FD(ucColOfIdVR);/* CRS_1211_130_356 Schalte new ID VR ab! */
					if(ucPvonReDxx < GETucMinWarnThresholdOfRam())/*CRS_1211_130_360*/
					{
						ucPmin|=cFD_Pmin_FR;
					}		
				}
				else
				{
					ucRtn = FALSE;/*CRS_1211_130_356 pressure not available */
				}
			}

			/* HL **********************************************************************************/
			if((GetNewIdColX4FD( ucColOfIdHL ) == TRUE) || (bGetBitBetriebszustandBZ(cCAL_REQUEST) == TRUE) || ( ucRePosStorageHL4FD == 0xFF)) /*Prüfe ob HL new ID? CRS_1211_130_372*/
			{
				ulTelID =	ulGetID(ucColOfIdHL); /*hole ID auf POS HL*/
				//ucPvonReDHL = ucGetAvgPress4FD(ulTelID);
				//ucReCounter4FDHL=ucGetAvgCntr4FD( ulTelID);
				ucPvonReDxx=ucGetLastReceivedPress(ulTelID); /* Prüfe mit zuletzt empfangenen Druck!! OHNE MITTELWERTBILDUNG --> 0xFF*/
				if((ucPvonReDxx != 0xFF)  && (ucPvonReDxx != 0x00))/* invalid pressure and invalid avg counter*/
				{
					scTvonReDxx=(signed) (ucGetLastReceivedTemp(ulTelID) - ucPalTempNormFACTOR4Calc);
					PUTucPosComparePressure(GetP4NewTempAtCAL(ucPvonReDxx,scTvonReDxx,GETscTref()),cRadPosHL);/*CRS_1211_130_340 Phl + Thl @ Tref: PnewRelativ 4 New ID is learnt*/	
					ClearNewIdColXMem4FD(ucColOfIdHL);/* CRS_1211_130_356 Schalte new ID HL ab! */
					if(ucPvonReDxx < GETucMinWarnThresholdOfRam())/*CRS_1211_130_360*/
					{
						ucPmin|=cFD_Pmin_RL;
					}		
				}
				else
				{
					ucRtn = FALSE;/*CRS_1211_130_356 pressure not available */
				}
			}
			/* HR **********************************************************************************/
			if((GetNewIdColX4FD( ucColOfIdHR ) == TRUE) || (bGetBitBetriebszustandBZ(cCAL_REQUEST) == TRUE) || ( ucRePosStorageHR4FD == 0xFF)) /*Prüfe ob HR new ID? CRS_1211_130_372*/
			{
				ulTelID =	ulGetID(ucColOfIdHR); /*hole ID auf POS HR*/
				//ucPvonReDHR = ucGetAvgPress4FD(ulTelID);
				//ucReCounter4FDHR=ucGetAvgCntr4FD( ulTelID);
				ucPvonReDxx=ucGetLastReceivedPress(ulTelID); /* Prüfe mit zuletzt empfangenen Druck!! OHNE MITTELWERTBILDUNG --> 0xFF*/
				if((ucPvonReDxx != 0xFF)  && (ucPvonReDxx != 0x00))/* invalid pressure and invalid avg counter*/
				{
					scTvonReDxx=(signed) (ucGetLastReceivedTemp(ulTelID) - ucPalTempNormFACTOR4Calc);
					PUTucPosComparePressure(GetP4NewTempAtCAL(ucPvonReDxx,scTvonReDxx,GETscTref()),cRadPosHR);/*CRS_1211_130_340 Phr + Thr @ Tref: PnewRelativ 4 New ID is learnt*/	
					ClearNewIdColXMem4FD(ucColOfIdHR);/*CRS_1211_130_356 Schalte new ID HL ab! */	
					if(ucPvonReDxx < GETucMinWarnThresholdOfRam()) /*CRS_1211_130_360*/
					{
						ucPmin|=cFD_Pmin_RR;
					}	
				}
				else
				{
					ucRtn = FALSE;/*CRS_1211_130_356 pressure not available */
				}
			}
#ifdef as_CmpValue4NewIDonly
//#else

			/* ChkNewIdColX4FD();CRS_1211_130_373 Neue Anforderung von DAG: Wenn eine neue ID im System erkannt, DANN setze für alle RE's die Vergleichsdrücke neu! */
			if((ChkNewIdColX4FD() == TRUE) || (bGetBitBetriebszustandBZ(cCAL_REQUEST) == TRUE))  /*Prüfe ob NUR eine new ID im SYSTEM ? CRS_1211_130_373*/
			{

			/* VL **********************************************************************************/
				ulTelID =	ulGetID(ucColOfIdVL); /*hole ID auf POS VL*/
				//cReCounter4FDVL=ucGetAvgCntr4FD( ulTelID);
				//ucPvonReDVL = ucGetAvgPress4FD(ulTelID);
				ucPvonReDxx=ucGetLastReceivedPress(ulTelID); /* Prüfe mit zuletzt empfangenen Druck!! OHNE MITTELWERTBILDUNG --> 0xFF*/

				if((ucPvonReDxx != 0xFF)  && (ucPvonReDxx != 0x00))/* invalid pressure and invalid avg counter*/
				{
					scTvonReDxx=(signed) (ucGetLastReceivedTemp(ulTelID) - ucPalTempNormFACTOR4Calc);
					PUTucPosComparePressure(GetP4NewTempAtCAL(ucPvonReDxx,scTvonReDxx,GETscTref()),cRadPosVL);/*CRS_1211_130_340 Pvl + Tvl @ Tref: PnewRelativ 4 New ID is learnt*/		
					ClearNewIdColXMem4FD(ucColOfIdVL);/* CRS_1211_130_356 Schalte new ID VL ab! */
					if(ucPvonReDxx < GETucMinWarnThresholdOfRam())/*CRS_1211_130_360*/
					{
						ucPmin|=cFD_Pmin_FL;
					}
				}
				else 
				{
					ucRtn = FALSE;/*CRS_1211_130_356 pressure not available */
				}
				/* VR **********************************************************************************/
				ulTelID =	ulGetID(ucColOfIdVR); /*hole ID auf POS VR*/
				//ucReCounter4FDVR=ucGetAvgCntr4FD( ulTelID);
				//ucPvonReDVR = ucGetAvgPress4FD(ulTelID);
				ucPvonReDxx=ucGetLastReceivedPress(ulTelID); /* Prüfe mit zuletzt empfangenen Druck!! OHNE MITTELWERTBILDUNG --> 0xFF*/

				if((ucPvonReDxx != 0xFF)  && (ucPvonReDxx != 0x00))/* invalid pressure and invalid avg counter*/
				{
					scTvonReDxx=(signed) (ucGetLastReceivedTemp(ulTelID) - ucPalTempNormFACTOR4Calc);
					PUTucPosComparePressure(GetP4NewTempAtCAL(ucPvonReDxx,scTvonReDxx,GETscTref()),cRadPosVR);/*CRS_1211_130_340 Pvr + Tvr @ Tref: PnewRelativ 4 New ID is learnt*/	
					ClearNewIdColXMem4FD(ucColOfIdVR);/* CRS_1211_130_356 Schalte new ID VR ab! */
					if(ucPvonReDxx < GETucMinWarnThresholdOfRam())/*CRS_1211_130_360*/
					{
						ucPmin|=cFD_Pmin_FR;
					}		
				}
				else
				{
					ucRtn = FALSE;/*CRS_1211_130_356 pressure not available */
				}
				/* HL **********************************************************************************/
				ulTelID =	ulGetID(ucColOfIdHL); /*hole ID auf POS HL*/
				//ucPvonReDHL = ucGetAvgPress4FD(ulTelID);
				//ucReCounter4FDHL=ucGetAvgCntr4FD( ulTelID);
				ucPvonReDxx=ucGetLastReceivedPress(ulTelID); /* Prüfe mit zuletzt empfangenen Druck!! OHNE MITTELWERTBILDUNG --> 0xFF*/
				if((ucPvonReDxx != 0xFF)  && (ucPvonReDxx != 0x00))/* invalid pressure and invalid avg counter*/
				{
					scTvonReDxx=(signed) (ucGetLastReceivedTemp(ulTelID) - ucPalTempNormFACTOR4Calc);
					PUTucPosComparePressure(GetP4NewTempAtCAL(ucPvonReDxx,scTvonReDxx,GETscTref()),cRadPosHL);/*CRS_1211_130_340 Phl + Thl @ Tref: PnewRelativ 4 New ID is learnt*/	
					ClearNewIdColXMem4FD(ucColOfIdHL);/* CRS_1211_130_356 Schalte new ID HL ab! */
					if(ucPvonReDxx < GETucMinWarnThresholdOfRam())/*CRS_1211_130_360*/
					{
						ucPmin|=cFD_Pmin_RL;
					}		
				}
				else
				{
					ucRtn = FALSE;/*CRS_1211_130_356 pressure not available */
				}

				/* HR **********************************************************************************/
				ulTelID =	ulGetID(ucColOfIdHR); /*hole ID auf POS HR*/
				//ucPvonReDHR = ucGetAvgPress4FD(ulTelID);
				//ucReCounter4FDHR=ucGetAvgCntr4FD( ulTelID);
				ucPvonReDxx=ucGetLastReceivedPress(ulTelID); /* Prüfe mit zuletzt empfangenen Druck!! OHNE MITTELWERTBILDUNG --> 0xFF*/
				if((ucPvonReDxx != 0xFF)  && (ucPvonReDxx != 0x00))/* invalid pressure and invalid avg counter*/
				{
					scTvonReDxx=(signed) (ucGetLastReceivedTemp(ulTelID) - ucPalTempNormFACTOR4Calc);
					PUTucPosComparePressure(GetP4NewTempAtCAL(ucPvonReDxx,scTvonReDxx,GETscTref()),cRadPosHR);/*CRS_1211_130_340 Phr + Thr @ Tref: PnewRelativ 4 New ID is learnt*/	
					ClearNewIdColXMem4FD(ucColOfIdHR);/*CRS_1211_130_356 Schalte new ID HL ab! */	
					if(ucPvonReDxx < GETucMinWarnThresholdOfRam()) /*CRS_1211_130_360*/
					{
						ucPmin|=cFD_Pmin_RR;
					}	
				}
				else
				{
					ucRtn = FALSE;/*CRS_1211_130_356 pressure not available */
				}
			}
#endif


			/* VL VR HL HR HR ***********************************************************************/	
			if(ucPmin != FALSE) /*CRS_1211_130_360*/
			{
				if(GETucCalNotAckStateOfRam() != cCAL_P_MIN_TIRE_NAK) /*CRS_1211_130_360*/
				{
					SetState2AbortReasonFD(cFD_P_MIN_TIRE); 
					ClearKplNoCheckPmin4StopFD();
					SetState2FillingDetectionStateFD(cFILLING_DETECT_ABORTED); 
					SetBitCalNotAckState2Ram(cCAL_P_MIN_TIRE_NAK); /*NEU für FBM <-> FD  P_MIN_TIRE  1,5bar! CalNotAck*/								
				}
			}
			else
			{
				if((ucRtn == TRUE) && ((GETucCalNotAckStateOfRam() & 0xBF) == FALSE )) /*cCAL_FBM_ACTIV_NAK CRS_1211_130_360 all pressure for update compare value are available! */
				{
					ClearFillingDetectionStateFD();/*CRS_1211_130_xxx*/	
					ClearAbortReasonFD();	/*CRS_1211_130_356*/
					ClearAllReCnt4FD(); /*wenn AFDII aktiv, dann AFD beenden, wenn MFD aktiv MFD weiterlaufen lassen, die Telegramzaehler zuruecksetzen!*/			
					//CRS_1211_130_249 PUTucPosComparePressureNVM();/*CRS_1211_130_150*/
					if((bGETucCalRequestState(cCAL_AUTO_ENABLE2) == TRUE ) || (bGETucCalRequestState(cCAL_AUTO_ENABLE3) == TRUE ))
					{
						SetBitFillingDetectionStateFD(cFILLING_NOT_DETECTED); /* CRS_1211_130_283 und TEST für ID bezogenen FD!*/
						ClearBitCalRequestState(cCAL_AUTO_ENABLE3 | cCAL_AUTO_ENABLE2); /*CRS_1211_130_353 AFDII oder AFDIII aktiv-> rücksetzen. ACHTUNG bei NEW ID ist "cCAL_AUTO_ACTIV" bereits gelöscht!*/
					}
				}
			}
		}
	return ucRtn; /* TRUE = reload ID Values 4 MFD Checker OKAY!*/
}


/*-------------------------------------------------------------------------------------------------
** FD_Plausibility_CheckP4DPLR_DPABS(uint8,uint8,uint8,uint8)
**/
/*
** Description
**/
/*
** Purpose: filling detected: Plausibility Check 4 MFD and AFD
**					5.2 Filling detection flow chart 
**					DP_LR: 17% (higher value = 100%)
**					DP_ABS: maximal absolut difference =1,5bar
**
** ------------------------------------------------------------------------------------------------
** Input:   ucZOMPosVL,ucZOMPosVR,ucZOMPosHL,ucZOMPosHR,           
**
** Output:  ucRtn (FALSE, TRUE)
** ------------------------------------------------------------------------------------------------
**/
uint8 FD_Plausibility_CheckP4DPLR_DPABS(uint8 ucZOMPosVL,uint8 ucZOMPosVR,uint8 ucZOMPosHL,uint8 ucZOMPosHR)
{

#ifdef as_DP_APS /*CRS_1211_130_368*/
	uint8	ucP_Low, ucP_High;
#endif
	uint16 uiDP_REL;
	uint8 ucRtn=TRUE;

	/* CHECk Nr. M3  cDP_LR: pressure left 2 right CRS_1211_130_066*/
	/*first check greater pressure for 100%! CRS_1211_131_066*/ 
	/* compare Prel! -> CRS_1211_130_091*/
  if (GETucIdCalPressure(ucZOMPosVL) > GETucIdCalPressure(ucZOMPosVR)) /*check Nr.M3 CRS_1211_131_066 rel:  2,6bar>2,3bar ->(0,025): 104>92 -> 104*83=8632 < 9200 --> i.O.*/
	{
		uiDP_REL=(GETucIdCalPressure(ucZOMPosVL) * cDP_LR);  /*CRS_1211_130_268 CRS_1211_130_091*/
		if (uiDP_REL > (GETucIdCalPressure(ucZOMPosVR) *100))  /*CRS_1211_130_268 CRS_1211_130_091*/
		{
			ucRtn=FALSE;/* calibration stopp --> abort filling detection*/
			//SetState2AbortReasonFD(cFD_DP_LR);/* Doppelt siehe "cFD_LEFT_RIGHT_DIFFERENCE" CRS_1211_130_181*/
			SetBitCalNotAckState2Ram(cCAL_DP_LR_FA_NAK);
			SetState2PlausiFailureFD(cFD_LEFT_RIGHT_DIFFERENCE);
		}
	}
	else 
	{
		uiDP_REL=(GETucIdCalPressure(ucZOMPosVR) * cDP_LR); /*CRS_1211_130_268*/ 
		if (uiDP_REL > (GETucIdCalPressure(ucZOMPosVL) *100))/*CRS_1211_130_268*/
		{
			ucRtn=FALSE;/* calibration stopp --> abort filling detection*/
			//SetState2AbortReasonFD(cFD_DP_LR);/* Doppelt siehe "cLEFT_RIGHT_DIFFERENCE" CRS_1211_130_181*/
			SetBitCalNotAckState2Ram(cCAL_DP_LR_FA_NAK);
			SetState2PlausiFailureFD(cFD_LEFT_RIGHT_DIFFERENCE);
		}
	}
	if (GETucIdCalPressure(ucZOMPosHL) > GETucIdCalPressure(ucZOMPosHR)) /*CRS_1211_131_066 rel:  2,6bar>2,3bar ->(0,025): 104>92 -> 104*83=8632 < 9200 --> i.O.*/
	{
		uiDP_REL=(GETucIdCalPressure(ucZOMPosHL) * cDP_LR); /*CRS_1211_130_268*/  
		if (uiDP_REL > (GETucIdCalPressure(ucZOMPosHR) *100))/*CRS_1211_130_268*/ 
		{
				ucRtn=FALSE;/* calibration stopp --> abort filling detection*/
				//SetState2AbortReasonFD(cFD_DP_LR);/* Doppelt siehe "cLEFT_RIGHT_DIFFERENCE" CRS_1211_130_181*/
				SetBitCalNotAckState2Ram(cCAL_DP_LR_RA_NAK);
				SetState2PlausiFailureFD(cFD_LEFT_RIGHT_DIFFERENCE);
		}
	}
	else 
	{
		uiDP_REL=(GETucIdCalPressure(ucZOMPosHR) * cDP_LR);/*CRS_1211_130_268*/ 
		if (uiDP_REL > (GETucIdCalPressure(ucZOMPosHL)  *100))/*CRS_1211_130_268*/ 
		{
			ucRtn=FALSE;/* calibration stopp --> abort filling detection*/
			//SetState2AbortReasonFD(cFD_DP_LR);/* Doppelt siehe "cLEFT_RIGHT_DIFFERENCE" CRS_1211_130_181*/
			SetBitCalNotAckState2Ram(cCAL_DP_LR_RA_NAK);
			SetState2PlausiFailureFD(cFD_LEFT_RIGHT_DIFFERENCE);
		}
	}
				
	if(ucRtn == TRUE)
	{
#ifdef as_DP_APS /*CRS_1211_130_368*/
		/*****************************************************************************************************************/
		/* CHECk Nr. M2 DP_ABS :Find low pressure and high pressure --> check difference CRS_1211_130_068*/
		/* ucGetHMICurrentTirePress(cRadPosVL)            ucGetHMICurrentTirePress(cRadPosVR)           ucGetHMICurrentTirePress(cRadPosHL)         ucGetHMICurrentTirePress(cRadPosHR)*/
		if (GETucIdCalPressure(ucZOMPosVL) > GETucIdCalPressure(ucZOMPosVR)) /*CRS_1211_131_068*/
		{
			ucP_High= GETucIdCalPressure(ucZOMPosVL);				  
			ucP_Low = GETucIdCalPressure(ucZOMPosVR);
			/* 1.) P_High ??*/         
			if(ucP_High > GETucIdCalPressure(ucZOMPosHL))
			{
				if(ucP_High < GETucIdCalPressure(ucZOMPosHR))
				{
					ucP_High= GETucIdCalPressure(ucZOMPosHR);	 /*HR = P_High!OR  in else VL = P_High!*/
				}
			}
			else
			{
				ucP_High= GETucIdCalPressure(ucZOMPosHL);
				if(ucP_High < GETucIdCalPressure(ucZOMPosHR))
				{
					ucP_High= GETucIdCalPressure(ucZOMPosHR);	/*HR = P_High!OR  in else HL = P_High!*/
				}						
 			}
			/* 1.) P_Low?? start with P_Low=VR */          
			if(ucP_Low < GETucIdCalPressure(ucZOMPosHL))
			{
				if(ucP_Low > GETucIdCalPressure(ucZOMPosHR))
				{
					ucP_Low = GETucIdCalPressure(ucZOMPosHR); /*HR = P_Low!OR  in else VR = P_Low!*/	
				}
			}
			else
			{
				ucP_Low = GETucIdCalPressure(ucZOMPosHL);
				if(ucP_Low > GETucIdCalPressure(ucZOMPosHR))
				{
					ucP_Low = GETucIdCalPressure(ucZOMPosHR);	/*HR = P_Low!OR  in else HL = P_Low!*/	
				}
			}
		}
		else
		{
			/* VR=P_High!*/					
			ucP_Low = GETucIdCalPressure(ucZOMPosVL);		  
			ucP_High= GETucIdCalPressure(ucZOMPosVR);
			if(ucP_High > GETucIdCalPressure(ucZOMPosHL))
			{
				if(ucP_High < GETucIdCalPressure(ucZOMPosHR))
				{
					ucP_High= GETucIdCalPressure(ucZOMPosHR);	 /*HR = P_High!  OR  in else VR = P_High!*/
				}					
			}
			else
			{
				ucP_High= GETucIdCalPressure(ucZOMPosHL);	
				if(ucP_High < GETucIdCalPressure(ucZOMPosHR))
				{
					ucP_High= GETucIdCalPressure(ucZOMPosHR);	/*HR = P_High! OR in else HL = P_High!*/
				}					
 			}				
			/* 2.) P_Low??  start with P_Low=VL*/          
			if(ucP_Low < GETucIdCalPressure(ucZOMPosHL))
			{
				if(ucP_Low > GETucIdCalPressure(ucZOMPosHR))
				{
					ucP_Low = GETucIdCalPressure(ucZOMPosHR);/*HR = P_Low!OR  in else VR = P_Low!*/	
				}
			}
			else
			{
				ucP_Low = GETucIdCalPressure(ucZOMPosHL);
				if(ucP_Low > GETucIdCalPressure(ucZOMPosHR))
				{
					ucP_Low = GETucIdCalPressure(ucZOMPosHR);	/*HR = P_Low!OR  in else HL = P_Low!*/	
				}
			}
		}
		/* 	CRS_1211_130_068 check difference */			
		if((ucP_High - ucP_Low) > cDP_Abs) /*1,50bar*/
		{
			ucRtn=FALSE;/* calibration stopp --> abort filling detection*/
			//SetState2AbortReasonFD(cFD_DP_ABS); /*Doppelt "cABSOLUTE_PRESSURE_DIFF" siehe CRS_1211_130_181*/
			SetBitCalNotAckState2Ram(cCAL_DP_ABS_NAK);	
			SetState2PlausiFailureFD(cFD_ABSOLUTE_PRESSURE_DIFF);	
		}
		else
		{
			ClearBitBetriebszustandBZ(cCAL_AFD_PLAUSI_ERROR | cCAL_MFD_PLAUSI_ERROR);/*CRS_1211_130_322 Erst nach FD Gutprüfung der DP_LR und DP_ABS die "HMI Unplausible Meldung" löschen (3)*/
			//ClearBitBetriebszustandBZ(cCAL_MFD_PLAUSI_ERROR);/*CRS_1211_130_322 Erst nach FD Gutprüfung der DP_LR und DP_ABS die "HMI Unplausible Meldung" löschen (3)*/
			ClearPlausiFailureLeftRightAbsFD();						  /*CRS_1211_130_313 delete "plausible error" for unplausible message in HMI! */
		}
#else /*as_DP_APS */
		ClearBitBetriebszustandBZ(cCAL_AFD_PLAUSI_ERROR | cCAL_MFD_PLAUSI_ERROR);/*CRS_1211_130_322 Erst nach FD Gutprüfung der DP_LR und DP_ABS die "HMI Unplausible Meldung" löschen (3)*/
		ClearPlausiFailureLeftRightAbsFD();						  /*CRS_1211_130_313 delete "plausible error" for unplausible message in HMI! */
#endif  /*as_DP_APS */
	}

return ucRtn;

}

/*-------------------------------------------------------------------------------------------------
** FD_CheckResetCondition4ImplausiMsg(uint8,uint8,uint8,uint8)
**/
/*
** Description
**/
/*
** Purpose: filling detected: AFD Check Reset Conditions 4 Implausible Pressure Warning
**					5.5.5 Filling detection Logik Doku 
**					DP_LR: 17% (higher value = 100%)
**					DP_ABS: maximal absolut difference =1,5bar
**
** ------------------------------------------------------------------------------------------------
** Input:   ucZOMPosVL,ucZOMPosVR,ucZOMPosHL,ucZOMPosHR,           
**
** Output:  CRS_1211_130_322 New: no return value   Old:ucRtn (FALSE, TRUE)
** ------------------------------------------------------------------------------------------------
**/
void FD_CheckResetCondition4ImplausiMsg(uint8 ucZOMPosVL,uint8 ucZOMPosVR,uint8 ucZOMPosHL,uint8 ucZOMPosHR)
{
#ifdef as_DP_APS /*CRS_1211_130_368*/
	uint8	ucP_Low, ucP_High;
#endif
	uint16 uiDP_REL;
	uint8 ucRtn=TRUE;

	/* CHECk Nr. M3  cDP_LR: pressure left 2 right CRS_1211_130_066*/
	/*first check greater pressure for 100%! CRS_1211_131_066*/ 
	/* compare Prel! -> CRS_1211_130_091*/
  if (GETucIdCalPressure(ucZOMPosVL) > GETucIdCalPressure(ucZOMPosVR)) /*check Nr.M3 CRS_1211_131_066 rel:  2,6bar>2,3bar ->(0,025): 104>92 -> 104*83=8632 < 9200 --> i.O.*/
	{
		uiDP_REL=(GETucIdCalPressure(ucZOMPosVL) * cDP_LR);  /*CRS_1211_130_268 CRS_1211_130_091*/
		if (uiDP_REL > (GETucIdCalPressure(ucZOMPosVR) *100))  /*CRS_1211_130_268 CRS_1211_130_091*/
		{
			ucRtn=FALSE;/*NO RESET Conditions 4 Implausible HMI message and Pressure Warning  */
		}
	}
	else 
	{
		uiDP_REL=(GETucIdCalPressure(ucZOMPosVR) * cDP_LR); /*CRS_1211_130_268*/ 
		if (uiDP_REL > (GETucIdCalPressure(ucZOMPosVL) *100))/*CRS_1211_130_268*/
		{
			ucRtn=FALSE;/*NO RESET Conditions 4 Implausible HMI message and Pressure Warning  */
		}
	}
	if (GETucIdCalPressure(ucZOMPosHL) > GETucIdCalPressure(ucZOMPosHR)) /*CRS_1211_131_066 rel:  2,6bar>2,3bar ->(0,025): 104>92 -> 104*83=8632 < 9200 --> i.O.*/
	{
		uiDP_REL=(GETucIdCalPressure(ucZOMPosHL) * cDP_LR); /*CRS_1211_130_268*/  
		if (uiDP_REL > (GETucIdCalPressure(ucZOMPosHR) *100))/*CRS_1211_130_268*/ 
		{
				ucRtn=FALSE;/*NO RESET Conditions 4 Implausible HMI message and Pressure Warning  */
		}
	}
	else 
	{
		uiDP_REL=(GETucIdCalPressure(ucZOMPosHR) * cDP_LR);/*CRS_1211_130_268*/ 
		if (uiDP_REL > (GETucIdCalPressure(ucZOMPosHL)  *100))/*CRS_1211_130_268*/ 
		{
			ucRtn=FALSE;/*NO RESET Conditions 4 Implausible HMI message and Pressure Warning  */
		}
	}
				
	if(ucRtn == TRUE)
	{
#ifdef as_DP_APS /*CRS_1211_130_368*/
		/*****************************************************************************************************************/
		/* CHECk Nr. M2 DP_ABS :Find low pressure and high pressure --> check difference CRS_1211_130_068*/
		/* ucGetHMICurrentTirePress(cRadPosVL)            ucGetHMICurrentTirePress(cRadPosVR)           ucGetHMICurrentTirePress(cRadPosHL)         ucGetHMICurrentTirePress(cRadPosHR)*/
		if (GETucIdCalPressure(ucZOMPosVL) > GETucIdCalPressure(ucZOMPosVR)) /*CRS_1211_131_068*/
		{
			ucP_High= GETucIdCalPressure(ucZOMPosVL);				  
			ucP_Low = GETucIdCalPressure(ucZOMPosVR);
			/* 1.) P_High ??*/         
			if(ucP_High > GETucIdCalPressure(ucZOMPosHL))
			{
				if(ucP_High < GETucIdCalPressure(ucZOMPosHR))
				{
					ucP_High= GETucIdCalPressure(ucZOMPosHR);	 /*HR = P_High!OR  in else VL = P_High!*/
				}
			}
			else
			{
				ucP_High= GETucIdCalPressure(ucZOMPosHL);
				if(ucP_High < GETucIdCalPressure(ucZOMPosHR))
				{
					ucP_High= GETucIdCalPressure(ucZOMPosHR);	/*HR = P_High!OR  in else HL = P_High!*/
				}						
 			}
			/* 1.) P_Low?? start with P_Low=VR */          
			if(ucP_Low < GETucIdCalPressure(ucZOMPosHL))
			{
				if(ucP_Low > GETucIdCalPressure(ucZOMPosHR))
				{
					ucP_Low = GETucIdCalPressure(ucZOMPosHR); /*HR = P_Low!OR  in else VR = P_Low!*/	
				}
			}
			else
			{
				ucP_Low = GETucIdCalPressure(ucZOMPosHL);
				if(ucP_Low > GETucIdCalPressure(ucZOMPosHR))
				{
					ucP_Low = GETucIdCalPressure(ucZOMPosHR);	/*HR = P_Low!OR  in else HL = P_Low!*/	
				}
			}
		}
		else
		{
			/* VR=P_High!*/					
			ucP_Low = GETucIdCalPressure(ucZOMPosVL);		  
			ucP_High= GETucIdCalPressure(ucZOMPosVR);
			if(ucP_High > GETucIdCalPressure(ucZOMPosHL))
			{
				if(ucP_High < GETucIdCalPressure(ucZOMPosHR))
				{
					ucP_High= GETucIdCalPressure(ucZOMPosHR);	 /*HR = P_High!  OR  in else VR = P_High!*/
				}					
			}
			else
			{
				ucP_High= GETucIdCalPressure(ucZOMPosHL);	
				if(ucP_High < GETucIdCalPressure(ucZOMPosHR))
				{
					ucP_High= GETucIdCalPressure(ucZOMPosHR);	/*HR = P_High! OR in else HL = P_High!*/
				}					
 			}				
			/* 2.) P_Low??  start with P_Low=VL*/          
			if(ucP_Low < GETucIdCalPressure(ucZOMPosHL))
			{
				if(ucP_Low > GETucIdCalPressure(ucZOMPosHR))
				{
					ucP_Low = GETucIdCalPressure(ucZOMPosHR);/*HR = P_Low!OR  in else VR = P_Low!*/	
				}
			}
			else
			{
				ucP_Low = GETucIdCalPressure(ucZOMPosHL);
				if(ucP_Low > GETucIdCalPressure(ucZOMPosHR))
				{
					ucP_Low = GETucIdCalPressure(ucZOMPosHR);	/*HR = P_Low!OR  in else HL = P_Low!*/	
				}
			}
		}
		/* 	CRS_1211_130_068 check difference */			
		if((ucP_High - ucP_Low) > cDP_Abs) /*1,50bar*/
		{
			ucRtn=FALSE;/*NO RESET Conditions 4 Implausible HMI message and Pressure Warning  */
		}
		else
		{
			ClearBitBetriebszustandBZ(cCAL_AFD_PLAUSI_ERROR); /*CRS_1211_130_322 Erst nach FD Gutprüfung der DP_LR und DP_ABS die "HMI Unplausible Meldung" löschen 5.5.5 (3)*/
			ClearBitBetriebszustandBZ(cCAL_MFD_PLAUSI_ERROR); /*CRS_1211_130_322 Erst nach FD Gutprüfung der DP_LR und DP_ABS die "HMI Unplausible Meldung" löschen 5.5.5 (3)*/
			ClearPlausiFailureLeftRightAbsFD();							  /*CRS_1211_130_313 delete "plausible error" for unplausible message in HMI! */

		}
#else /*as_DP_APS */
		ClearBitBetriebszustandBZ(cCAL_AFD_PLAUSI_ERROR); /*CRS_1211_130_322 Erst nach FD Gutprüfung der DP_LR und DP_ABS die "HMI Unplausible Meldung" löschen 5.5.5 (3)*/
		ClearBitBetriebszustandBZ(cCAL_MFD_PLAUSI_ERROR); /*CRS_1211_130_322 Erst nach FD Gutprüfung der DP_LR und DP_ABS die "HMI Unplausible Meldung" löschen 5.5.5 (3)*/
		ClearPlausiFailureLeftRightAbsFD();							  /*CRS_1211_130_313 delete "plausible error" for unplausible message in HMI! */
#endif /*as_DP_APS */
	}
}

/*-------------------------------------------------------------------------------------------------
** uint8 GetPabs4NewTempAtCAL(uint8, sint8, sint8) CRS_1211_130_268 ALTE nicht mehr verwendete Fkt.
**/
/*
** Description
**/
/*
** Purpose:             Berechnet aus Druckwert und Erfassungstemperatur den
**                      Druckwert bei aktueller Temperatur (relativ oder absolut)
**
** ------------------------------------------------------------------------------------------------
** Input:              Druckwert absolut , Temperatur, aktuelle Temperatur
**
** Output:             Druckwert absolut  (no relativ //ui8Pcomp -= uc1Barc ;)
** ------------------------------------------------------------------------------------------------
**/
uint8 GetPabs4NewTempAtCAL(uint8 ui8PCur, sint8 i8Tcur, sint8 i8Tnew) // returns relative pressure value compensated to Tref
 {
    uint16 ui16M;
    uint8 ui8Pcomp;

    ui16M = ushMIso ((ui8PCur), i8Tcur ); /*rel 2,4bar=0x60=96dez 96+40=136*10240/293=4753+5=4758/10=475*/ 
    ui8Pcomp = ucPfT(ui16M,(uint16) i8Tnew + ush273Kelvinc);/*475*10*293=1391750/1024=1359+5=1364/10=136*/
    return (ui8Pcomp);
 }

/*-------------------------------------------------------------------------------------------------
** uint8 GetP4NewTempAtCAL(uint8, sint8, sint8)
**/
/*
** Description
**/
/*
** Purpose:             Berechnet aus Druckwert und Erfassungstemperatur den
**                      Druckwert bei aktueller Temperatur 
**
** ------------------------------------------------------------------------------------------------
** Input:              Druckwert (relativ), CRS_1211_130_268 Temperatur, aktuelle Temperatur
**
** Output:             Druckwert (relativ)
** ------------------------------------------------------------------------------------------------
**/
uint8 GetP4NewTempAtCAL(uint8 ui8PCur, sint8 i8Tcur, sint8 i8Tnew) // returns relative pressure value compensated to Tref
 {
    uint16 ui16M;
    uint8 ui8Pcomp;
    
		ui16M = ui16MIsoRel ((ui8PCur), i8Tcur ); /*CRS_1211_130_268 NEU: ucPfT liefert relativen Druckwert!  2,4bar=0x60=96dez 96+40=136*10240/293=4753+5=4758/10=475*/ 
    ui8Pcomp = ucPfT(ui16M,(uint16) i8Tnew + ush273Kelvinc);/*CRS_1211_130_268 NEU: ucPfT liefert relativen Druckwert! 475*10*293=1391750/1024=1359+5=1364/10=136*/
    return (ui8Pcomp);
 }

/*-------------------------------------------------------------------------------------------------
**	void FD_AfdStop(void)
**/
/*
**	Description
**/
/*
**	Purpose:             Stoppt die AFD aufgrund z.B. ZO nach druck FBMode CRS_1211_130_224
**                      Bei NEUER ID Update der CMP Werte!
**	#define cZO_TIMEOUT           ((uint16) 0x1000)   // Timer Radmanagement abgelaufen
**	#define cZO_ERROR             ((uint16) 0x2000)   // AUTOLOCATE Error
**	#define cTEILZUGEORDNET       ((uint16) 0x4000)   // FBM o.ä. WP_0=4, WP_1=4, WP_2=2, WP_3=3 und HistUsedWP_0...3=0,1,2,3!!!!!!!
**
** ------------------------------------------------------------------------------------------------
**	Input:              non
**
**	Output:             non
** ------------------------------------------------------------------------------------------------
**/
void FD_AfdStopp4PWP(void)
{
	if( bGETucCalNotAckState(cCAL_FBM_ACTIV_NAK) == FALSE) /*CRS_1211_130_275 Stopp AFD once*/
	{
		if((bGETucCalRequestState(cCAL_AUTO_NEW_ID) == TRUE))  /*CRS_1211_130_357 ZO_Timer=240 --> NEW_ID -->FD_Timeout=0!  Sonderfall  */
		{
			if((FD_LoadIdValues4UpdateCompareValue() == TRUE) || ((bGetBitBetriebszustandBZ(cZO_TIMEOUT) == TRUE ) && (bGetBitBetriebszustandBZ(cZO_ERROR) == TRUE)))/* TRUE= ZO okay FALSE =keine ZO mgl. auch nicht im FB Mode */
			{
					ClearBitCalRequestState(cCAL_AUTO_NEW_ID);
					SetBitCalNotAckState2Ram(cCAL_FBM_ACTIV_NAK); /*CRS_1211_130_275 Stopp AFD once*/
			}
		}
		else
		{
			if(FD_UpdateComparePressureAfterFBM() == TRUE)
			{
				SetBitCalNotAckState2Ram(cCAL_FBM_ACTIV_NAK); /*CRS_1211_130_275 Stopp AFD once*/
			}
		}

		ClearBitFahrzeugzustandFZZ(cKFZPARKING_START_AFD); 
		ClearBitCalRequestState(cCAL_AUTO_ENABLE3 | cCAL_AUTO_ENABLE2 | cCAL_AUTO_ACTIV);
		ClearPlausiFailureFD(); /*CRS_1211_130_224*/
		//ClearAbortReasonFD(); /*CRS_1211_130_224*/
		//ClearFillingDetectionStateFD(); /*CRS_1211_130_224*/

		if(bGETucCalRequestState(cCAL_MANUAL_ACTIV) == FALSE) /* KEINE MFD? */
		{
			ClearBitBetriebszustandBZ(cCAL_REQUEST); /*AFD only*/
			//ClearFillingDetectionStateFD(); /*CRS_1211_130_263*/
			PUTushFDtimeout(0); /* FBM mode, Softreset zuruecksetzen */
			if(Get_FD_ABORT_REASON() == FALSE)
			{			
				SetState2FillingDetectionStateFD(cFILLING_DETECT_ABORTED);/* AFD only CRS_1211_130_274*/
				SetState2AbortReasonFD(cFD_FBM_ACTIV); /*CRS_1211_130_323 AFD only OIL#1079  #  OIL#954 SW Workshop KW13 Stopp AFD once*/
			}
		}
#ifdef as_357
		 SetBitCalNotAckState2Ram(cCAL_FBM_ACTIV_NAK); /*CRS_1211_130_275 Stopp AFD once*/
#endif
	}
	else
	{
    if((GetucTPM_WarnDisp_Rq() > 0) && (bGetBitBetriebszustandBZ(cCAL_MFD_PLAUSI_ERROR) || bGetBitBetriebszustandBZ(cCAL_AFD_PLAUSI_ERROR))) /*CRS_1211_130_331*/
		{
			ClearBitBetriebszustandBZ(cCAL_AFD_PLAUSI_ERROR | cCAL_MFD_PLAUSI_ERROR);/*CRS_1211_130_331: PM_WarnDisp_Rq>0 --> reset condition 5.5.5 (4) FB Mode*/
		}
	}
}

/*-------------------------------------------------------------------------------------------------
** uint8 FD_CheckCurrentPmin(void) CRS_1211_130_332
**/
/*
** Description
**/
/*
** Purpose:             Kalibrierung: MANUAL and AUTO 1.Check Pmin warning?
**                      
**
** ------------------------------------------------------------------------------------------------
** Input:              
**
** Output:             Result: TRUE/FALSE
** ------------------------------------------------------------------------------------------------
**/

uint8 FD_CheckCurrentPmin(void)
{
	uint8 ucRtn = FALSE;
	uint8 i;
	uint32 ulTelID;
	uint8 ucColOfIdVL,ucColOfIdVR,ucColOfIdHL,ucColOfIdHR;

/*********************************************/
	for( i = 0; i < cAnzRad; i++ ) /*i=ZOMPOS*/
	{
		switch (GETucWPorPWPofHistCol(i))
		{
			case cRadPosVL: 
						ucColOfIdVL=i; /*ZOM/COLpos of cRadPosVL*/
			break;
			case cRadPosVR: 
						ucColOfIdVR=i; /*ZOM/COLpos of cRadPosVR*/
			break;
			case cRadPosHL: 
						ucColOfIdHL=i; /*ZOM/COLpos of cRadPosVR*/
			break;
			case cRadPosHR: 
 						ucColOfIdHR=i; /*ZOM/COLpos of cRadPosVR*/
			break;
			default:  /* cRadPosUkw: 4= RADpos unknow  ACHTUNG! Eigenrad*/
			{
				ucRtn = TRUE; /* cRadPosUkw: 4= RADpos unknow  ACHTUNG!!!!! Eigenrad*/
			}
		}
	}
/*********************************************/
	if(ucRtn == FALSE)
	{
		if(ucGetLastReceivedPress(ulGetID(ucColOfIdVL)) != 0xFF)
		{
			if(ucGetLastReceivedPress(ulGetID(ucColOfIdVL))  < GETucMinWarnThresholdOfRam())
			{
				ucRtn =TRUE;
			}
		}
		if(ucGetLastReceivedPress(ulGetID(ucColOfIdVR)) != 0xFF)
		{
			if(ucGetLastReceivedPress(ulGetID(ucColOfIdVR))  < GETucMinWarnThresholdOfRam())
			{
				ucRtn =TRUE;
			}
		}
		if(ucGetLastReceivedPress(ulGetID(ucColOfIdHL)) != 0xFF)
		{	
			if(ucGetLastReceivedPress(ulGetID(ucColOfIdHL))  < GETucMinWarnThresholdOfRam())
			{
				ucRtn =TRUE;
			}
		}
		if(ucGetLastReceivedPress(ulGetID(ucColOfIdHR)) != 0xFF)
		{
			if(ucGetLastReceivedPress(ulGetID(ucColOfIdHR))  < GETucMinWarnThresholdOfRam())
			{
				ucRtn =TRUE;
			}
		}
	}
	else
	{
			
		if(bGetBitBetriebszustandBZ(cER_FINISH)) /*CRS_1211_130_349*/
		{
			ucRtn = FALSE; /*CRS_1211_130_352*/

			ulTelID =	ulGetID(cRadPosVL); /*hole ID aus HIST_ID_0*/
			if(ucGetLastReceivedPress(ulTelID) != 0xFF)
			{
				if(ucGetLastReceivedPress(ulTelID) < GETucMinWarnThresholdOfRam())
				{
					ucRtn =TRUE; /*CRS_1211_130_349*/
				}
			}
			ulTelID =	ulGetID(cRadPosVR); /*hole ID aus HIST_ID_1*/
			if(ucGetLastReceivedPress(ulTelID) != 0xFF)
			{
				if(ucGetLastReceivedPress(ulTelID) < GETucMinWarnThresholdOfRam())
				{
					ucRtn =TRUE; /*CRS_1211_130_349*/
				}
			}
			ulTelID =	ulGetID(cRadPosHL); /*hole ID aus HIST_ID_2*/
			if(ucGetLastReceivedPress(ulTelID) != 0xFF)
			{
				if(ucGetLastReceivedPress(ulTelID) < GETucMinWarnThresholdOfRam())
				{
					ucRtn =TRUE; /*CRS_1211_130_349*/
				}
			}
			ulTelID =	ulGetID(cRadPosHR); /*hole ID aus HIST_ID_2*/
			if(ucGetLastReceivedPress(ulTelID) != 0xFF)
			{
				if(ucGetLastReceivedPress(ulTelID) < GETucMinWarnThresholdOfRam())
				{
					ucRtn =TRUE; /*CRS_1211_130_349*/
				}
			}
		}
		else
		{
			ucRtn =FALSE; /* Pmin can not determined */
		}
	}
	return ucRtn;
}


/*-------------------------------------------------------------------------------------------------
**	uint8 FD_FlowChartFct1(void)
**/
/*
**	Description
**/
/*
**	Purpose:	Kalibrierung: MANUAL and AUTO 1.Check Pmin Missing Sensor according FlowChart1
**                      
**	Changes:
**	CRS_1211_130_365 if((ucCheckLOW_PRESS_ReState() != FALSE) && (GETucNoCheckPmin4StopFD() == FALSE))
**  @@@35 Pmn check in FD_CheckP4AFDstartReason2_3FA CRS_1211_130_325  CRS_1211_130_214 CRS_1211_130_177
**	allways first check Pmin warning?
**
** ------------------------------------------------------------------------------------------------
**	Input:              
**
**	Output:             FALSE=FD Abort TRUE=FD okay
** ------------------------------------------------------------------------------------------------
**/

uint8 FD_FlowChartFct1(void)
{
	uint8 ucRtn=TRUE;
	uint8 i;

	if(FD_CheckCurrentPmin() == TRUE) //CRS_1211_130_365 OIL#1294 && (GETucNoCheckPmin4StopFD() == FALSE)) /*CRS_1211_130_332 CRS_1211_130_325 */
	{   
		/* Abort filling detection immediately*/
		PUTucOnceCheckMissingRE4FD(TRUE);	
		PUTushFDtimeout(0);
		PUTucFDtimerStop(TRUE); /*CRS_1211_130_337 Vorzeitiger FD Timeout*/
		FD_AbortFillingDetection(cCAL_P_MIN_TIRE_NAK); /* Abort reason PminNEU*/
		ucRtn=FALSE; /*FALSE --> Abort */

	}
	else 
	{
		//if((GETucOnceCheckMissingRE4FD() == FALSE) && ((GETushCalTimeout() < (cFD_TIME_OUT/2)) || (bGetBitBetriebszustandBZ(cZO_TIMEOUT) == TRUE ))) /* CRS_1211_130_308 u.295 CRS_1211_130_180 check RE missing once or twice only*/
		/*CRS_1211_130_311  @@@ AS+GL: nachdem AL_MODE == cSpeciaLearn oder cCompleteLearn WIRD im ZO_TIMEOUT unter auf cNoLearn gesetzt!!!!!!!!!!! PRÜFEN  */
		/* CRS_1211_130_321 Autolocate_Mode=cNoLearn: z.B. wenn ZO Timeout =cFD_TIME_OUT und erneut Start der MFD, so läuft MFD immer bit TIMEOUT d.h. ushCalTimeout=0 */
		/* CRS_1211_130_321 Autolocate_Mode=COMPLATE_LEARN und RE missing dann bei ZO Timeout=cFD_TIME_OUT wechselt Autolocate_Mode von COMPLATE_LEARN zu cNoLearn*/ 
		if(((GETucOnceCheckMissingRE4FD() == FALSE) && ((ucGetFzzCurrentLearnMode() == cNoLearn) && (bGetBitBetriebszustandBZ(cZO_TIMEOUT) == TRUE))) ||
			((GETucOnceCheckMissingRE4FD() == FALSE) && (ucGetFzzCurrentLearnMode() != cNoLearn) && (GETushFDtimeout() == 0)))
		{
			for (i = 0; i < cMaxLR; i++)  /*CRS_1211_130_093 immediately update walgo all RE value */
			{
				if(ucGetSensorState(i) == SENSOR_STATE_MISSING)	/* RE_STATE RE Missing??  control!*/					
				{
					ucRtn=FALSE; /*FALSE; RE Missing AFD */
				}
			}
			if (ucRtn==FALSE)
			{
				PUTucOnceCheckMissingRE4FD(TRUE);
				PUTushFDtimeout(0);
				PUTucFDtimerStop(TRUE); /*CRS_1211_130_337*/
				FD_AbortFillingDetection(cCAL_RE_MISSING_NAK); /*Abort reason RE missing without 9min RE received*/
			}
		}
		else
		{
			if(GETucOnceCheckMissingRE4FD() == TRUE) /*  TRUE= bereits geprüft und RE Missing gesetzt!*/
			{
				ucRtn=FALSE; 
			}
		}
	}

	return ucRtn;
}

/*-------------------------------------------------------------------------------------------------
**	uint8 FD_FlowChartFct1CheckPmin(void)
**/
/*
**	Description
**/
/*
**	Purpose:	Kalibrierung: MANUAL and AUTO 1.Check Pmin according FlowChart1
**                      
**	Changes:	FD_CONTROLS_FALLBACK CRS_1211_130_347
**	
**  
**	check Pmin ?
**
** ------------------------------------------------------------------------------------------------
**	Input:              
**
**	Output:             FALSE=FD Abort TRUE=FD okay
** ------------------------------------------------------------------------------------------------
**/

uint8 FD_FlowChartFct1CheckPmin(void)
{
	uint8 ucRtn=TRUE;

	if(FD_CheckCurrentPmin() == TRUE) // CRS_1211_130_365 OIL#1294 && (GETucNoCheckPmin4StopFD() == FALSE)) /*CRS_1211_130_332 CRS_1211_130_325 */
	{   
		/* Abort filling detection immediately*/
		PUTucOnceCheckMissingRE4FD(TRUE);	
		PUTushFDtimeout(0);
		PUTucFDtimerStop(TRUE); /*CRS_1211_130_337 Vorzeitiger FD Timeout*/
		FD_AbortFillingDetection(cCAL_P_MIN_TIRE_NAK); /* Abort reason PminNEU*/
		ucRtn=FALSE; /*FALSE --> Abort */
	}

	return ucRtn;
}

/*-------------------------------------------------------------------------------------------------
**	uint8 FD_FlowChartFct1CheckMissingRE(void)
**/
/*
**	Description
**/
/*
**	Purpose:	Kalibrierung: MANUAL and AUTO 2.Check Missing Sensor according FlowChart1
**                      
**	Changes:	FD_CONTROLS_FALLBACK CRS_1211_130_347
**	
** 
**	
**
** ------------------------------------------------------------------------------------------------
**	Input:              
**
**	Output:             FALSE=FD Abort TRUE=FD okay
** ------------------------------------------------------------------------------------------------
**/

uint8 FD_FlowChartFct1CheckMissingRE(void)
{
	uint8 ucRtn=TRUE;
	uint8 i;

	//if((GETucOnceCheckMissingRE4FD() == FALSE) && ((GETushCalTimeout() < (cFD_TIME_OUT/2)) || (bGetBitBetriebszustandBZ(cZO_TIMEOUT) == TRUE ))) /* CRS_1211_130_308 u.295 CRS_1211_130_180 check RE missing once or twice only*/
	/*CRS_1211_130_311  @@@ AS+GL: nachdem AL_MODE == cSpeciaLearn oder cCompleteLearn WIRD im ZO_TIMEOUT unter auf cNoLearn gesetzt!!!!!!!!!!! PRÜFEN  */
	/* CRS_1211_130_321 Autolocate_Mode=cNoLearn: z.B. wenn ZO Timeout =cFD_TIME_OUT und erneut Start der MFD, so läuft MFD immer bit TIMEOUT d.h. ushCalTimeout=0 */
	/* CRS_1211_130_321 Autolocate_Mode=COMPLATE_LEARN und RE missing dann bei ZO Timeout=cFD_TIME_OUT wechselt Autolocate_Mode von COMPLATE_LEARN zu cNoLearn*/ 
	if(((GETucOnceCheckMissingRE4FD() == FALSE) && ((ucGetFzzCurrentLearnMode() == cNoLearn) && (bGetBitBetriebszustandBZ(cZO_TIMEOUT) == TRUE))) ||
		((GETucOnceCheckMissingRE4FD() == FALSE) && (ucGetFzzCurrentLearnMode() != cNoLearn) && (GETushFDtimeout() == 0)))
	{
		for (i = 0; i < cMaxLR; i++)  /*CRS_1211_130_093 immediately update walgo all RE value */
		{
			if(ucGetSensorState(i) == SENSOR_STATE_MISSING)	/* RE_STATE RE Missing??  control!*/					
			{
				ucRtn=FALSE; /*FALSE; RE Missing AFD */
			}
		}
		if (ucRtn==FALSE)
		{
			PUTucOnceCheckMissingRE4FD(TRUE);
			PUTushFDtimeout(0);
			PUTucFDtimerStop(TRUE); /*CRS_1211_130_337*/
			FD_AbortFillingDetection(cCAL_RE_MISSING_NAK); /*Abort reason RE missing without 9min RE received*/
		}
	}
	else
	{
		if(GETucOnceCheckMissingRE4FD() == TRUE) /*  TRUE= bereits geprüft und RE Missing gesetzt!*/
		{
			ucRtn=FALSE; 
		}
	}
	return ucRtn;
}


/*-------------------------------------------------------------------------------------------------
**	uint8 FD_CheckFDpos2ZomPosAfterZOfinish(void) CRS_1211_130_336
**/ 
/*
**	Description
**/
/*
**	Purpose:	Kalibrierung: MANUAL and AUTO start again
**                      
**	Changes:	CRS_1211_130_336 / CRS_1211_130_351
**	
**  
**	
**
** ------------------------------------------------------------------------------------------------
**	Input:              
**
**	Output:             FALSE=FD Abort // 1= start MFD // 2= start AFD
** ------------------------------------------------------------------------------------------------
**/
uint8 FD_CheckFDpos2ZomPosAfterZOfinish(void)
{
	uint8 ucColOfIdVL,ucColOfIdVR,ucColOfIdHL, ucColOfIdHR; 
	uint8 aucOldColOfID[4];
	uint8 aucP_OfID[4];
	sint8 ascT_OfID[4];
	uint8 aucPaverege_OfID[4];
	sint8 scTfillVA, scTfillHA, scTfill_Tref;
	uint8 ucReVa2Ha_Ha2VA=FALSE;/*CRS_1211_130_383*/
	uint8 i;
	uint8 ucRtn=TRUE;
		
	for( i = 0; i < cAnzRad; i++ ) /*i=ZOMPOS*/
	{
		switch (GETucWPorPWPofHistCol(i))
		{
			case cRadPosVL: 
				ucColOfIdVL=i; /*ZOM-COLpos of cRadPosVL*/
			break;
			case cRadPosVR: 
   			ucColOfIdVR=i; /*ZOM-COLpos of cRadPosVR*/
			break;
			case cRadPosHL: 

				ucColOfIdHL=i; /*ZOM-COLpos of cRadPosHL*/
			break;
			case cRadPosHR: 
  			ucColOfIdHR=i; /*ZOM-COLpos of cRadPosHR*/
			break;
			default:
			{
				ucRtn = FALSE;
			}
		}
	}
	if(ucRtn == TRUE)
	{
	  	if((ucRePosStorageVL4FD + ucRePosStorageVR4FD + ucRePosStorageHL4FD +ucRePosStorageHR4FD) == (ucColOfIdVL + ucColOfIdVR + ucColOfIdHL + ucColOfIdHR))
			{
				/* AFD was running in past*/
				if((ucRePosStorageVL4FD != ucColOfIdVL) || (ucRePosStorageVR4FD != ucColOfIdVR) || (ucRePosStorageHL4FD != ucColOfIdHL) || (ucRePosStorageHR4FD != ucColOfIdHR))
				{
					if((ucRePosStorageVL4FD != ucColOfIdVL) && (ucRePosStorageVR4FD != ucColOfIdVR) && (ucRePosStorageHL4FD != ucColOfIdHL) && (ucRePosStorageHR4FD != ucColOfIdHR))
					{
						ucReVa2Ha_Ha2VA=TRUE; /*CRS_1211_130_383*/
					}
					ucRtn=cAFD_RUNNING2; /* CRS_1211_130_336 AFDII  !!!*/
					/* Hier CRS_1211_130_336 Funktion zum NEUSETZEN der COMPARE und REf WERTE*/
					/* replacement pressure*/
					aucOldColOfID[cRadPosVL]=ucRePosStorageVL4FD; /*2   aucNewColOfID[cRadPosVL]=0;*/ 
					aucOldColOfID[cRadPosVR]=ucRePosStorageVR4FD; /*1   aucNewColOfID[cRadPosVR]=3;*/
					aucOldColOfID[cRadPosHL]=ucRePosStorageHL4FD; /*0   aucNewColOfID[cRadPosHL]=2;*/
					aucOldColOfID[cRadPosHR]=ucRePosStorageHR4FD; /*3   aucNewColOfID[cRadPosHR]=1;*/

					aucP_OfID[0]=GETucIdCalPressure(ucRePosStorageVL4FD); /*[0]=(2)=  2,4bar WP_0:--> ucRePosStorageVL4FD=2 P=96dez(2,4bar!) */
					aucP_OfID[1]=GETucIdCalPressure(ucRePosStorageVR4FD); /*[1]=(1)=  2,5bar WP_1:--> ucRePosStorageVL4FD= P=100dez(2,5bar!) */
					aucP_OfID[2]=GETucIdCalPressure(ucRePosStorageHL4FD); /*[2]=(0)=  2,8bar */
					aucP_OfID[3]=GETucIdCalPressure(ucRePosStorageHR4FD); /*[3]=(3) = 2,9bar */
					
					ascT_OfID[0]=GETscIdCalTemperatur(ucRePosStorageVL4FD);
					ascT_OfID[1]=GETscIdCalTemperatur(ucRePosStorageVR4FD);
					ascT_OfID[2]=GETscIdCalTemperatur(ucRePosStorageHL4FD);
					ascT_OfID[3]=GETscIdCalTemperatur(ucRePosStorageHR4FD);

					aucPaverege_OfID[0]=GETucStoragePaverege4CompareValue(ucRePosStorageVL4FD);
					aucPaverege_OfID[1]=GETucStoragePaverege4CompareValue(ucRePosStorageVR4FD);
					aucPaverege_OfID[2]=GETucStoragePaverege4CompareValue(ucRePosStorageHL4FD);
					aucPaverege_OfID[3]=GETucStoragePaverege4CompareValue(ucRePosStorageHR4FD);

					/*NOW: replacement pressure, replacement temperatur, replacement averege P CRS_1211_130_351 */
					for( i = 0; i < cAnzRad; i++ ) /*i=ZOMPOS*/
					{
						switch (aucOldColOfID[i]) /* old: 2,1,0,3 new: 0,3,2,1  */
						{
							case cRadPosVL: 
							{
								PUTucIdCalPressure(aucP_OfID[i],cRadPosVL); /*2,4bar --> 2 HL */
								PUTscIdCalTemperatur(ascT_OfID[i],cRadPosVL);
								PUTuiStoragePaverege4CompareValue(((uint16)aucPaverege_OfID[i]),cRadPosVL);
							}
							break;
							case cRadPosVR: 
							{
   							PUTucIdCalPressure(aucP_OfID[i],cRadPosVR); /*2,4bar --> 2 HL */
								PUTscIdCalTemperatur(ascT_OfID[i],cRadPosVR);
								PUTuiStoragePaverege4CompareValue(((uint16)aucPaverege_OfID[i]),cRadPosVR);
							}
							break;
							case cRadPosHL: 
							{
								PUTucIdCalPressure(aucP_OfID[i],cRadPosHL); /*2,4bar zu HL */
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
	
					ClearBitBetriebszustandBZ(cCAL_AFD_PLAUSI_ERROR); /*Clear Bit 4  "Filling not detected" (Filling detection flow chart 5.2) */	
					//ClearFillingDetectionStateFD();
					/********************************************************************************************************************************/
					if(Get_FD_STATUS() == cFILLING_DETECTED)/*CRS_1211_130_384*/
					{
						//if(FD_Plausibility_CheckP4DPLR_DPABS(ucColOfIdVL,ucColOfIdVR,ucColOfIdHL,ucColOfIdHR) == TRUE)  /* plausibility check ok: 5.2 Filling detection flow chart result:(B)*/
						if((FD_Plausibility_CheckP4DPLR_DPABS(ucColOfIdVL,ucColOfIdVR,ucColOfIdHL,ucColOfIdHR) == TRUE) && (GETushWarnstatus1WN() == FALSE)) /*OIL1364 check warnstate */
						{
						
							//ClearFillingDetectionStateFD(); /*CRS_1211_130_384*/

							BZ_FZZ_RQ_State4AFD_Finish(); /*CRS_1211_130_267*/
							//SetState2FillingDetectionStateFD(cFILLING_DETECTED); /*CRS_1211_130_190 */	 
							/*Average pressure in Pref front and rear axis*/ 
							PUTucPrefFront(((GETucIdCalPressure(ucColOfIdVL) + GETucIdCalPressure(ucColOfIdVR))/2));/*load Average pressure VL,VR*/
							PUTucPrefRear(((GETucIdCalPressure(ucColOfIdHL) + GETucIdCalPressure(ucColOfIdHR))/2));/*load Average pressure HL,HR*/
							/*NONISOCHOR Average pressure in Pfill front and rear axis*/ 
							PUTucPfillFront(GETucPrefFront());	/* CRS_1211_130_268 CRS_1211_130_100 p_fill_front 4 measurement interface*/
							PUTucPfillRear(GETucPrefRear());	/* CRS_1211_130_268 CRS_1211_130_100 p_fill_rear 4 measurement interface*/				
	
							scTfillVA=((GETscIdCalTemperatur(ucColOfIdVL) + GETscIdCalTemperatur(ucColOfIdVR))/2);/*CRS_1211_130_085*/
							scTfillHA=((GETscIdCalTemperatur(ucColOfIdHL) + GETscIdCalTemperatur(ucColOfIdHR))/2);/*CRS_1211_130_085*/		
							if(scTfillVA > cTfillLimitH) /*CRS_1211_130_219*/
							{
							scTfillVA=cTfillLimitH;
							}
							if(scTfillHA > cTfillLimitH)/*CRS_1211_130_219*/
							{
								scTfillHA=cTfillLimitH;
							}							
					
							scTfill_Tref=(scTfillVA + scTfillHA)/2;
							PUTscTfill(scTfill_Tref);   /* CRS_1211_130_219 to store it for DCM purpose */
							scTfill_Tref=KweightCalculation(scTfill_Tref, (sint8)(tEnvDataToSend.ucTempOut)); /*CRS_1211_131_083 weighting factor K_WEIGHT for Tref*/
							/*CRS_1211_130_309 1. Isochorendruck berechnen, 2. Prüfung auf kleiner Mindestkalibrierdruck! */
							PUTucPrefFront(GetP4NewTempAtCAL(GETucPrefFront(),scTfillVA, scTfill_Tref));	/*CRS_1211_130_268 GetPabs4NewTempAtCAL 4 relativen Druck!VA: 5.8.3 Calculation of the cold tire inflation pressure*/	
							if (GETucPrefFront() <= GETucPcalMinVaRelativCodOfRam()) /* CRS_1211_130_268 NEU relativ ALT:absolut <= absolut*/
							{
								PUTucPrefFront(GETucPcalMinVaRelativCodOfRam());/* CRS_1211_130_268 NEU relativ ALT:absolut <= absolut*/
							}
							/* rear axis */
							/*CRS_1211_130_309 1. Isochorendruck berechnen, 2. Prüfung auf kleiner Mindestkalibrierdruck! */
							PUTucPrefRear(GetP4NewTempAtCAL(GETucPrefRear(),scTfillHA, scTfill_Tref));	/*CRS_1211_130_268 GetPabs4NewTempAtCAL 4 relativen Druck!VA: 5.8.3 Calculation of the cold tire inflation pressure*/
							if (GETucPrefRear() <= GETucPcalMinHaRelativCodOfRam()) /* CRS_1211_130_268 NEU relativ ALT:absolut <= absolut*/
							{
								PUTucPrefRear(GETucPcalMinHaRelativCodOfRam());/* CRS_1211_130_268 NEU relativ ALT:absolut <= absolut*/
							}

							PUTscTref(scTfill_Tref);
	
							/*CRS_1211_130_268 relativ pressure always!*/	
							PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdVL)),GETscIdCalTemperatur(ucColOfIdVL), scTfill_Tref),cRadPosVL);	/*Pvl + Tvl @ Tref: PnewRelativ*/		
							PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdVR)),GETscIdCalTemperatur(ucColOfIdVR), scTfill_Tref),cRadPosVR);	/*Pvr + Tvr @ Tref: PnewRelativ*/										
							PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdHL)),GETscIdCalTemperatur(ucColOfIdHL), scTfill_Tref),cRadPosHL);	/*Phl + Thl @ Tref: PnewRelativ*/				
							PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdHR)),GETscIdCalTemperatur(ucColOfIdHR), scTfill_Tref),cRadPosHR);	/*Phr + Thr @ Tref: PnewRelativ*/	
							/*****************************************************************/
							///*CRS_1211_130_383*/ DelWarnOfId(4); /*MFA2: CRS_1211_130_234neu aus papenburg April --> 4=all DelWarnOfId(uint8 ui8HistColOfID) */
							//ReplayLastREvalue2Walgo();  /* 27.09.2016 CodeReview CRS_1211_032_121*/
							///*CRS_1211_130_383*/ ReStart4SetValue2ActivationMemAFD(); /*CRS_1211_130_376*/
						}
						else
						{
							ClearFillingDetectionStateFD(); /*CRS_1211_130_384*/
							if(GETushWarnstatus1WN() == TRUE) /*Warnung aktiv --> KEINE Neuberechnung der CMP und REF Druckwerte! NUR Tausch, siehe auch Warnung aktiv UND KEIN Auffüllen erkannt CRS_1211_130_380 */
							{
								if(Get_FD_STATUS() == FALSE)
								{
									SetState2FillingDetectionStateFD(cFD_ACTIV_WARNING); /* CRS_1211_130_380 Kein Rad aufgefüllt ABER Warnung immer noch aktiv */
								}
							}
							else
							{
								/*********************************************************************************************/			
								/* plausibility check NOT OK: New tire pressure are not plausible update compare pressure only*/
								SetState2FillingDetectionStateFD(cFILLING_UNPLAUSIBLE); /*CRS_1211_130_181*/	
								//SetBitBetriebszustandBZ(cCAL_MFD_PLAUSI_ERROR); /* CRS_1211_130_101 only if plausibility check NOT OKAY! */
								SetBitBetriebszustandBZ(cCAL_AFD_PLAUSI_ERROR);  /*CRS_1211_130_227 Hier OKAY da "new tire pressure are not plausible", altCRS_1211_130_202*/
								BZ_FZZ_RQ_State4AFD_Finish(); /*CRS_1211_130_267*/
							}
							if(ucReVa2Ha_Ha2VA==TRUE) /*CRS_1211_130_383 Tausch der VA HA Referenz Drücke NUR wenn wirklich Achsen Tausch! --> KEINE Wegkalibrierung von Warnungen mgl.*/
							{
								aucP_OfID[0]=GETucPrefFront();
								aucP_OfID[1]=GETucPrefRear();
								PUTucPrefFront(aucP_OfID[1]);
								PUTucPrefRear(aucP_OfID[0]);
							}

							PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdVL)),GETscIdCalTemperatur(ucColOfIdVL), GETscTref()),cRadPosVL);	/*Pvl + Tvl @ Tref: PnewRelativ*/		
							PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdVR)),GETscIdCalTemperatur(ucColOfIdVR), GETscTref()),cRadPosVR);	/*Pvr + Tvr @ Tref: PnewRelativ*/										
							PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdHL)),GETscIdCalTemperatur(ucColOfIdHL), GETscTref()),cRadPosHL);	/*Phl + Thl @ Tref: PnewRelativ*/				
							PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdHR)),GETscIdCalTemperatur(ucColOfIdHR), GETscTref()),cRadPosHR);	/*Phr + Thr @ Tref: PnewRelativ*/	
						
							///*CRS_1211_130_383*/ DelWarnOfId(4); /*MFA2: CRS_1211_130_234neu aus papenburg April --> 4=all DelWarnOfId(uint8 ui8HistColOfID) */
							//ReplayLastREvalue2Walgo();  /* 27.09.2016 CodeReview CRS_1211_032_121*/
							///*CRS_1211_130_383*/ ReStart4SetValue2ActivationMemAFD(); /*CRS_1211_130_376*/
							/*****************************************************************/
						}
					}
					else
					{
						if(Get_FD_STATUS() == FALSE)
						{
							SetState2FillingDetectionStateFD(cFILLING_NOT_DETECTED); /*CRS_1211_130_384*/
						}
						/*CRS_1211_130_385 entfernen -> Kein Tausch der Referenz Drücke!*/
						//if(ucReVa2Ha_Ha2VA==TRUE) /*CRS_1211_130_383 Tausch der VA HA Referenz Drücke NUR wenn wirklich Achsen Tausch! --> KEINE Wegkalibrierung von Warnungen mgl.*/
						//{
						//	aucP_OfID[0]=GETucPrefFront();
						//	aucP_OfID[1]=GETucPrefRear();
						//	PUTucPrefFront(aucP_OfID[1]);
						//	PUTucPrefRear(aucP_OfID[0]);
						//}

						PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdVL)),GETscIdCalTemperatur(ucColOfIdVL), GETscTref()),cRadPosVL);	/*Pvl + Tvl @ Tref: PnewRelativ*/		
						PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdVR)),GETscIdCalTemperatur(ucColOfIdVR), GETscTref()),cRadPosVR);	/*Pvr + Tvr @ Tref: PnewRelativ*/										
						PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdHL)),GETscIdCalTemperatur(ucColOfIdHL), GETscTref()),cRadPosHL);	/*Phl + Thl @ Tref: PnewRelativ*/				
						PUTucPosComparePressure(GetP4NewTempAtCAL(((uint8)GETuiStoragePaverege4CompareValue(ucColOfIdHR)),GETscIdCalTemperatur(ucColOfIdHR), GETscTref()),cRadPosHR);	/*Phr + Thr @ Tref: PnewRelativ*/	

					}
				}
				else
				{
					ucRtn = FALSE;
				}
			}
			else
			{
				ucRtn = FALSE;
			}
	}
	return ucRtn;
}


/*-------------------------------------------------------------------------------------------------
** PUTuiStoragePaverege4CompareValue
**/
/*
** Description
**/
/*
** Purpose:	Storage Makro 4 MFD: PUT relative pressure for update FD Compare pressure value
**                      
**
** ------------------------------------------------------------------------------------------------
** Input:		non
**
** Output:	non
** ------------------------------------------------------------------------------------------------
**/
void PUTuiStoragePaverege4CompareValue(uint16 x, uint8 i)
{
	uiStoragePaverege4CompareValue[i]=x;
}

/*-------------------------------------------------------------------------------------------------
** GETuiStoragePaverege4CompareValue
**/
/*
** Description
**/
/*
** Purpose:	Storage Makro 4 MFD: GET 2Byte relativ pressure for update FD Compare pressure value
**                      
**
** ------------------------------------------------------------------------------------------------
** Input:		non
**
** Output:	non
** ------------------------------------------------------------------------------------------------
**/

uint16 GETuiStoragePaverege4CompareValue(uint8 i)
{
	return (uiStoragePaverege4CompareValue[i]);
}

/*-------------------------------------------------------------------------------------------------
** GETucStoragePaverege4CompareValue 
**/
/*
** Description		
**/
/*
** Purpose:	Storage Makro 4 MFD: GET 1Byte relativ pressure for update FD Compare pressure value
**                      
**
** ------------------------------------------------------------------------------------------------
** Input:   non
**
** Output:	non
** ------------------------------------------------------------------------------------------------
**/

uint8 GETucStoragePaverege4CompareValue(uint8 i)
{
	return ((uint8)(uiStoragePaverege4CompareValue[i]));
}

/*-------------------------------------------------------------------------------------------------
** PUTucDpStabiPressure
**/
/*
** Description
**/
/*
** Purpose:	Storage Makro 4 FD: Cache 4 absolut pressure value modulglobal 4 check DP_STABI
**                  
**
** ------------------------------------------------------------------------------------------------
** Input:		non
**
** Output:	non
** ------------------------------------------------------------------------------------------------
**/
void PUTucDpStabiPressure(uint8 x, uint8 i)
{
	ucDpStabiPressure[i]=x;
}

/*-------------------------------------------------------------------------------------------------
** GETucDpStabiPressure
**/
/*
** Description
**/
/*
** Purpose:	Load of Cache 4 absolut pressure value modulglobal 4 check DP_STABI
**                      
**
** ------------------------------------------------------------------------------------------------
** Input:		non
**
** Output:	non
** ------------------------------------------------------------------------------------------------
**/
uint8 GETucDpStabiPressure( uint8 i)
{
	return ucDpStabiPressure[i];
}

/*-------------------------------------------------------------------------------------------------
** PUTucIdCalPressure
**/
/*
** Description
**/
/*
** Purpose:	Storage Makro 4 FD: Cache 4 absolut pressure value modulglobal
**                  
**
** ------------------------------------------------------------------------------------------------
** Input:		non
**
** Output:	non
** ------------------------------------------------------------------------------------------------
**/
void PUTucIdCalPressure(uint8 x, uint8 i)
{
	ucIdCalPressure[i]=x;
}

/*-------------------------------------------------------------------------------------------------
** GETucIdCalPressure
**/
/*
** Description
**/
/*
** Purpose:	Load of Cache 4 absolut pressure value modulglobal
**                      
**
** ------------------------------------------------------------------------------------------------
** Input:		non
**
** Output:	non
** ------------------------------------------------------------------------------------------------
**/
uint8 GETucIdCalPressure( uint8 i)
{
	return ucIdCalPressure[i];
}



/*-------------------------------------------------------------------------------------------------
** PUTscIdCalTemperatur
**/
/*
** Description
**/
/*
** Purpose:	Storage Makro 4 FD: Cache 4 temperature value modulglobal
**                  
**
** ------------------------------------------------------------------------------------------------
** Input:		non
**
** Output:	non
** ------------------------------------------------------------------------------------------------
**/
void PUTscIdCalTemperatur(sint8 x, uint8 i)
{
  scIdCalTemperatur[i]=x;
}



/*-------------------------------------------------------------------------------------------------
** GETscIdCalTemperatur
**/
/*
** Description
**/
/*
** Purpose:	Load of Cache 4 absolut temperature value modulglobal
**                      
**
** ------------------------------------------------------------------------------------------------
** Input:		non
**
** Output:	non
** ------------------------------------------------------------------------------------------------
**/
sint8 GETscIdCalTemperatur(uint8 i)
{
  return scIdCalTemperatur[i];
}

/*-------------------------------------------------------------------------------------------------
** PUTucPfillFront
**/
/*
** Description
**/
/*
** Purpose:	Storage Makro 4 FD: Cache 4 relativ fillpressure front axis value modulglobal
**                  
**
** ------------------------------------------------------------------------------------------------
** Input:		non
**
** Output:	non
** ------------------------------------------------------------------------------------------------
**/
void PUTucPfillFront(uint8 x)
{
	ucPfillFront=x;
}

/*-------------------------------------------------------------------------------------------------
** GETucPfillFront
**/
/*
** Description
**/
/*
** Purpose:	GetMakro 4 FD: Cache 4 relativ fillpressure front axis value modulglobal
**                  
**
** ------------------------------------------------------------------------------------------------
** Input:		non
**
** Output:	non
** ------------------------------------------------------------------------------------------------
**/
uint8 GETucPfillFront(void)
{
	return ucPfillFront;
}



/*-------------------------------------------------------------------------------------------------
** PUTucPfillRear
**/
/*
** Description
**/
/*
** Purpose:	Storage Makro 4 FD: Cache 4 relativ fillpressure rear axis value modulglobal
**                  
**
** ------------------------------------------------------------------------------------------------
** Input:		non
**
** Output:	non
** ------------------------------------------------------------------------------------------------
**/
void PUTucPfillRear(uint8 x)
{
	ucPfillRear=x;
}

/*-------------------------------------------------------------------------------------------------
** GETucPfillRear
**/
/*
** Description
**/
/*
** Purpose:	GetMakro 4 FD: Cache 4 relativ fillpressure rear axis value modulglobal
**                  
**
** ------------------------------------------------------------------------------------------------
** Input:		non
**
** Output:	non
** ------------------------------------------------------------------------------------------------
**/
uint8 GETucPfillRear(void)
{
	return ucPfillRear;
}

/*-------------------------------------------------------------------------------------------------
** PUTucTfill
**/
/*
** Description
**/
/*
** Purpose:	Storage Makro 4 FD: Cache 4 fill temperatur average front+axis value modulglobal
**    Tfill= (FD_T_FillVA+FD_T_FillRA)/2;              
**
** ------------------------------------------------------------------------------------------------
** Input:		non
**
** Output:	non
** ------------------------------------------------------------------------------------------------
**/
void PUTscTfill(sint8 x)
{
	scTfill=x;
}
/*-------------------------------------------------------------------------------------------------
** GETucTfill
**/
/*
** Description
**/
/*
** Purpose:	GETMakro 4 FD: Cache 4 fill temperatur average front+axis value modulglobal
**    Tfill= (FD_T_FillVA+FD_T_FillRA)/2;              
**
** ------------------------------------------------------------------------------------------------
** Input:		non
**
** Output:	non
** ------------------------------------------------------------------------------------------------
**/
sint8 GETscTfill(void)
{
	return scTfill;
}

/************************************************************************************************//**
 * \brief interface used by AFD 4 deflated 
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] none
 * \param [out] none
 *
 * \return value none
 *
 *------------------------------------------------------------------------------------------------
 */

void PUTucCnt4DP_FILL_DFL(uint8 x)
{
  ucCnt4DP_FILL_DFL = x;
}

uint8 GETucCnt4DP_FILL_DFL(void)
{
	return ucCnt4DP_FILL_DFL;
}

uint8 GETucCnt4DP_FILL_DFL4LTSlogged(void)
{
	if((ucLockByt4DFL_LTS & 0x80) == 0x80 )
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

uint8 GETucDFL_LTS3(void)
{
	return ucLockByt4DFL_LTS;
}


void INCucCnt4DP_FILL_DFL(void) /* LastP-CurrentP > 200mbar DP_FILL --> deflated DFL 0 ...4 */
{
	if(ucCnt4DP_FILL_DFL < 0xFF)/*CRS_1211_500_1283*/
	{
		ucCnt4DP_FILL_DFL++;
	}
}

void PUTucCnt4DP_FILL_DFL4LTSlogged(void)
{
	if((ucLockByt4DFL_LTS & 0x80) != 0x80 )
	{
		ucLockByt4DFL_LTS |= 0x80;
	}
}


void PUTucCnt4DP_FILL_DFLloggedFL(void)/*CRS_1211_130_371*/
{
	if((ucCnt4DP_FILL_DFL & cDP_FILL_FL) != cDP_FILL_FL)
	{
		ucCnt4DP_FILL_DFL+=cDP_FILL_FL; /* add 0x10 Ident4FL */ 
	}
}

uint8 GETucCnt4DP_FILL_DFLloggedFL(void) /*CRS_1211_130_371*/
{
	if((ucCnt4DP_FILL_DFL & cDP_FILL_FL) != cDP_FILL_FL)
	{
		return FALSE; /* add 0x10 Ident4FL  */ 
	}
	else
	{
		return TRUE;
	}
}

void PUTucCnt4DP_FILL_DFLloggedFR(void)/*CRS_1211_130_371*/
{
	if((ucCnt4DP_FILL_DFL & cDP_FILL_FR) != cDP_FILL_FR)
	{
		ucCnt4DP_FILL_DFL+=cDP_FILL_FR; /* add 0x20 Ident4FR  */ 
	}
}
uint8 GETucCnt4DP_FILL_DFLloggedFR(void) /*CRS_1211_130_371*/
{
	if((ucCnt4DP_FILL_DFL & cDP_FILL_FR) != cDP_FILL_FR)
	{
		return FALSE; /* add 0x20 Ident4FR */ 
	}
	else
	{
		return TRUE;
	}
}

void PUTucCnt4DP_FILL_DFLloggedRL(void) /*CRS_1211_130_371*/
{
	if((ucCnt4DP_FILL_DFL & cDP_FILL_RL) != cDP_FILL_RL)
	{
		ucCnt4DP_FILL_DFL+=cDP_FILL_RL; /* add 0x40 Ident4RL  */ 
	}
}

uint8 GETucCnt4DP_FILL_DFLloggedRL(void) /*CRS_1211_130_371*/
{
	if((ucCnt4DP_FILL_DFL & cDP_FILL_RL) != cDP_FILL_RL)
	{
		return FALSE; /* add 0x40 Ident4RL */ 
	}
	else
	{
		return TRUE;
	}
}

void PUTucCnt4DP_FILL_DFLloggedRR(void)/*CRS_1211_130_371*/
{
	if((ucCnt4DP_FILL_DFL & cDP_FILL_RR) != cDP_FILL_RR)
	{
		ucCnt4DP_FILL_DFL+=cDP_FILL_RR; /* add 0x80 Ident4RR  */ 
	}
}
uint8 GETucCnt4DP_FILL_DFLloggedRR(void) /*CRS_1211_130_371*/
{
	if((ucCnt4DP_FILL_DFL & cDP_FILL_RR) != cDP_FILL_RR)
	{
		return FALSE; /* add 0x80 Ident4RR */ 
	}
	else
	{
		return TRUE;
	}
}

void PUTucLockByt4DFL_LTS(uint8 x)
{
		ucLockByt4DFL_LTS = x;
}

/************************************************************************************************//**
 * \brief interface used by AFD 4 inflated
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] none
 * \param [out] none
 *
 * \return none
 *
 *------------------------------------------------------------------------------------------------
 */

void PUTucCnt4DP_FILL_IFL(uint8 x)
{
  ucCnt4DP_FILL_IFL = x;
}

void PUTucCnt4DP_FILL_IFLloggedFL(void)
{
	if((ucCnt4DP_FILL_IFL & cDP_FILL_FL) != cDP_FILL_FL)
	{
		ucCnt4DP_FILL_IFL+=cDP_FILL_FL; /* add 0x10 Ident4FL ! CRS_1211_130_220  */ 
	}
}

uint8 GETucCnt4DP_FILL_IFLloggedFL(void) /*CRS_1211_130_371*/
{
	if((ucCnt4DP_FILL_IFL & cDP_FILL_FL) != cDP_FILL_FL)
	{
		return FALSE; /* add 0x10 Ident4FL  */ 
	}
	else
	{
		return TRUE;
	}
}


void PUTucCnt4DP_FILL_IFLloggedFR(void)
{
	if((ucCnt4DP_FILL_IFL & cDP_FILL_FR) != cDP_FILL_FR)
	{
		ucCnt4DP_FILL_IFL+=cDP_FILL_FR; /* add 0x20 Ident4FR ! CRS_1211_130_220  */ 
	}
}
uint8 GETucCnt4DP_FILL_IFLloggedFR(void) /*CRS_1211_130_371*/
{
	if((ucCnt4DP_FILL_IFL & cDP_FILL_FR) != cDP_FILL_FR)
	{
		return FALSE; /* add 0x20 Ident4FR */ 
	}
	else
	{
		return TRUE;
	}
}

void PUTucCnt4DP_FILL_IFLloggedRL(void)
{
	if((ucCnt4DP_FILL_IFL & cDP_FILL_RL) != cDP_FILL_RL)
	{
		ucCnt4DP_FILL_IFL+=cDP_FILL_RL; /* add 0x40 Ident4RL ! CRS_1211_130_220  */ 
	}
}

uint8 GETucCnt4DP_FILL_IFLloggedRL(void) /*CRS_1211_130_371*/
{
	if((ucCnt4DP_FILL_IFL & cDP_FILL_RL) != cDP_FILL_RL)
	{
		return FALSE; /* add 0x40 Ident4RL */ 
	}
	else
	{
		return TRUE;
	}
}

void PUTucCnt4DP_FILL_IFLloggedRR(void)
{
	if((ucCnt4DP_FILL_IFL & cDP_FILL_RR) != cDP_FILL_RR)
	{
		ucCnt4DP_FILL_IFL+=cDP_FILL_RR; /* add 0x80 Ident4RR ! CRS_1211_130_220  */ 
	}
}
uint8 GETucCnt4DP_FILL_IFLloggedRR(void) /*CRS_1211_130_371*/
{
	if((ucCnt4DP_FILL_IFL & cDP_FILL_RR) != cDP_FILL_RR)
	{
		return FALSE; /* add 0x80 Ident4RR */ 
	}
	else
	{
		return TRUE;
	}
}

uint8 GETucCnt4DP_FILL_IFL(void)
{
	return ucCnt4DP_FILL_IFL;
}
void INCucCnt4DP_FILL_IFL(void)/* LastP-CurrentP > 200mbar DP_FILL --> inflated IFL 0 ...4 */
{
	if(ucCnt4DP_FILL_IFL < 0xFF) /*CRS_1211_500_1283*/
	{
		ucCnt4DP_FILL_IFL++;
	}
}


void PUTucNoCheckPmin4StopFD(uint8 x) /*CRS_1211_130_325*/
{
  ucNoCheckPmin4StopFD = x;
}

uint8 GETucNoCheckPmin4StopFD(void)/*CRS_1211_130_325*/
{
	return ucNoCheckPmin4StopFD;
}
					
void ClearBitInNoCheckPmin4StopFD( uint8 ucBitMask )
{
	ucNoCheckPmin4StopFD &= (~ucBitMask);
}

void ClearKplNoCheckPmin4StopFD(void) /*CRS_1211_130_330*/	
{
	ucNoCheckPmin4StopFD = 0;
}


void PUTucFDcheckP2PosOk(uint8 x) /*CRS_1211_130_336*/
{
  ucFDcheckP2PosOk = x;
}

uint8 GETucFDcheckP2PosOk(void)/*CRS_1211_130_336*/
{
	return ucFDcheckP2PosOk;
}
	
void DECucFDcheckP2PosOk(void) /*CRS_1211_130_336*/
{
  ucFDcheckP2PosOk--;
}

				
void ClearBitInucFDcheckP2PosOk( uint8 ucBitMask )
{
	ucFDcheckP2PosOk &= (~ucBitMask);
}


void ClearFDcheckP2PosOk(void) /*CRS_1211_130_330*/	
{
	ucFDcheckP2PosOk = 0;
}

void PUTushZomTioFreeze(uint16 x) /*CRS_1211_130_336*/
{
	ushZomTioFreez = x;
}

uint16 GETushZomTioFreeze(void) /*CRS_1211_130_336*/
{
	return ushZomTioFreez;
	}

void DECushZomTioFreeze(void)/*CRS_1211_130_336*/
{
	if(ushZomTioFreez != 0)
	{
		ushZomTioFreez--;
	}

}
#ifdef AS_ID_VALUE
/*-------------------------------------------------------------------------------------------------
** PUTucReCntVL4FD
**/
/*
** Description
**/
/*
** Purpose:	Storage RE Counter value VL 4 FD  
**                 
**
** ------------------------------------------------------------------------------------------------
** Input:		non
**
** Output:	non
** ------------------------------------------------------------------------------------------------
**/
void PUTucReCntVL4FD(uint8 x)
{
	ucReCntVL4FD=x;
}
/*-------------------------------------------------------------------------------------------------
** PLUSPLUSucReCntVL4FD
**/
/*
** Description
**/
/*
** Purpose:	Increment RE Counter value VL 4 FD  
**                 
**
** ------------------------------------------------------------------------------------------------
** Input:		non
**
** Output:	non
** ------------------------------------------------------------------------------------------------
**/
void INCucReCnt4FD(uint8 ucRadPos)
{
	switch (ucRadPos)
	{
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
/*-------------------------------------------------------------------------------------------------
** GETucReCntVL4FD
**/
/*
** Description
**/
/*
** Purpose:	GETMakro RE Counter value VL 4 FD
**    
**
** ------------------------------------------------------------------------------------------------
** Input:		non
**
** Output:	non
** ------------------------------------------------------------------------------------------------
**/
uint8 GETucReCntVL4FD(void)
{
	return ucReCntVL4FD;
}

/*-------------------------------------------------------------------------------------------------
** PLUSPLUSucReCnt4FD
**/
/*
** Description
**/
/*
** Purpose:	get RE Counter value   
**                 
**
** ------------------------------------------------------------------------------------------------
** Input:		ucRadPos
**
** Output:	RE Counter value 4 FD 0...254 
** ------------------------------------------------------------------------------------------------
**/
uint8 GETucReCnt4FD(uint8 ucRadPos)
{
uint8 ucReturnValue;	

	switch (ucRadPos)
	{
		case cRadPosVL:
		{
			if(ucReCntVL4FD == 0xFF)
			{
				ucReCntVL4FD--;
			}
			ucReturnValue= ucReCntVL4FD;
		}
		break;
    
		case cRadPosVR:
		{
			if(ucReCntVR4FD == 0xFF)
			{
				ucReCntVR4FD--;
			}
			ucReturnValue= ucReCntVR4FD;
		}
		break;
			
		case cRadPosHL:
		{
			if(ucReCntHL4FD == 0xFF)
			{
				ucReCntHL4FD--;
			}
			ucReturnValue= ucReCntHL4FD;
		}
		break;
		
		case cRadPosHR: 
		{
			if(ucReCntHR4FD == 0xFF)
			{
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

/*-------------------------------------------------------------------------------------------------
** InitRePosStorage4FD
**/
/*
** Description CRS_1211_130_373
**/
/*
** Purpose:	INIT REPOS MEM 4 FD if changed inside wheels  
**                 
**
** ------------------------------------------------------------------------------------------------
** Input:		non
**
** Output:	non
** ------------------------------------------------------------------------------------------------
**/
void InitRePosStorage4FD(void) 
{
	ucRePosStorageVL4FD=0xFF;
	ucRePosStorageVR4FD=0xFF;
	ucRePosStorageHL4FD=0xFF;
	ucRePosStorageHR4FD=0xFF;
}



/*-------------------------------------------------------------------------------------------------
** PUTucCalNotAckState2Ram
**/
/*
** Description
**/
/*
** Purpose:	FD Bits for control, rejection of filling detection 
**                      
**
** ------------------------------------------------------------------------------------------------
** Input:		non
**
** Output:	non
** ------------------------------------------------------------------------------------------------
**/

/* **********************************************************************************************/
/* CalNotAckState Start Value 4 Kalibrierung  CR_1211_130_050 */

void PUTucCalNotAckState2Ram(uint8 x)
{
  NvM_RequestResultType ErrorStatus;

  Rte_Pim_Pim_tCalNvMBlock()->ucCalNotAckState = (x);
  Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_GetErrorStatus(&ErrorStatus); /* to avoid multi requests */
  if (ErrorStatus  != NVM_REQ_PENDING)
  {
    Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_SetRamBlockStatus(TRUE);/*Kl.15off->2NVM*/
  }
}

/*-------------------------------------------------------------------------------------------------
** ClearCalNotAckState2Ram
**/
/*
** Description
**/
/*
** Purpose:	Clear all FD Bits for control, rejection of filling detection 
**                      
**
** ------------------------------------------------------------------------------------------------
** Input:		non
**
** Output:	non
** ------------------------------------------------------------------------------------------------
**/

/* **********************************************************************************************/
/* CalNotAckState Start Value 4 Kalibrierung  CR_1211_130_050 */

void ClearCalNotAckState(void)
{
  NvM_RequestResultType ErrorStatus;

  Rte_Pim_Pim_tCalNvMBlock()->ucCalNotAckState = FALSE;
  Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_GetErrorStatus(&ErrorStatus); /* to avoid multi requests */
  if (ErrorStatus  != NVM_REQ_PENDING)
  {
    Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_SetRamBlockStatus(TRUE);/*Kl.15off->2NVM*/
  }
}


void ClearCalNotAckState4MFD(void) /*CRS_1211_130_274 cCAL_FBM_ACTIV_NAK	0x40 Fall Back Mode activ --> disable AFD */
{
	Rte_Pim_Pim_tCalNvMBlock()->ucCalNotAckState &= (~0xBF); /*0b1011.1111 conserve FallBack Mode Bit 0x40*/
	Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_SetRamBlockStatus(TRUE);/*Kl.15off->2NVM*/
}


void ClearBitCalNotAckState( uint8 ucBitMask )
{
  uint8 ui8IsModified;
  
  ui8IsModified = Rte_Pim_Pim_tCalNvMBlock()->ucCalNotAckState;

  //(*(uint8*) Rte_Pim_Pim_CalRequestState()) &= ~ucBitMask;
  Rte_Pim_Pim_tCalNvMBlock()->ucCalNotAckState &= (~ucBitMask);
  
  if(ui8IsModified != Rte_Pim_Pim_tCalNvMBlock()->ucCalNotAckState)
  {
    Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_SetRamBlockStatus(TRUE);/*Kl.15off->2NVM*/
  }
} 
/*-------------------------------------------------------------------------------------------------
** GETucCalNotAckStateOfRam
**/
/*
** Description
**/
/*
** Purpose:	FD Bits for control, rejection of filling detection 
**                      
**
** ------------------------------------------------------------------------------------------------
** Input:		non
**
** Output:	non
** ------------------------------------------------------------------------------------------------
**/
uint8 GETucCalNotAckStateOfRam(void)
{
	return Rte_Pim_Pim_tCalNvMBlock()->ucCalNotAckState;
}

/*-------------------------------------------------------------------------------------------------
** SetBitCalNotAckState2Ram
**/
/*
** Description
**/
/*
** Purpose:	FD Bits for control, rejection of filling detection 
**                      
**
** ------------------------------------------------------------------------------------------------
** Input:		non
**
** Output:	non
** ------------------------------------------------------------------------------------------------
**/
void SetBitCalNotAckState2Ram( uint8 ucBitMask )
{
  NvM_RequestResultType ErrorStatus;

  Rte_Pim_Pim_tCalNvMBlock()->ucCalNotAckState |= (ucBitMask);
  
  Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_GetErrorStatus(&ErrorStatus); /* to avoid multi requests */
  if (ErrorStatus  != NVM_REQ_PENDING)
  {
    Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_SetRamBlockStatus(TRUE);/*Kl.15off->2NVM*/
  }
} 

uint8 bGETucCalNotAckState( uint8 ucBitMask )
{
  if((Rte_Pim_Pim_tCalNvMBlock()->ucCalNotAckState & ucBitMask) !=0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
} 


/* CalNotAckState END Value 4 Kalibrierung  CR_1211_130_050 */
/* **********************************************************************************************/


/* **********************************************************************************************/
/* CalRequestState Start Value 4 Kalibrierung */
void PUTucCalRequestState2Ram(uint8 x)
{
  NvM_RequestResultType ErrorStatus;
  //*(uint8*) Rte_Pim_Pim_CalRequestState()= (x);
  Rte_Pim_Pim_tCalNvMBlock()->ucCalRequestState = (x);
  Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_GetErrorStatus(&ErrorStatus); /* to avoid multi requests */
  if (ErrorStatus  != NVM_REQ_PENDING)
  {
    Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_SetRamBlockStatus(TRUE);/*Kl.15off->2NVM*/
  }
}
void SetBitCalRequestState2Ram( uint8 ucBitMask )
{
  NvM_RequestResultType ErrorStatus;
  //(*(uint8*) Rte_Pim_Pim_CalRequestState()) |= ucBitMask;
  Rte_Pim_Pim_tCalNvMBlock()->ucCalRequestState |= (ucBitMask);
  Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_GetErrorStatus(&ErrorStatus); /* to avoid multi requests */
  if (ErrorStatus  != NVM_REQ_PENDING)
  {
    Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_SetRamBlockStatus(TRUE);/*Kl.15off->2NVM*/
  }
} 

void ClearBitCalRequestState( uint8 ucBitMask )
{
  uint8 ui8IsModified;
  NvM_RequestResultType ErrorStatus;
  
  ui8IsModified = Rte_Pim_Pim_tCalNvMBlock()->ucCalRequestState;

  //(*(uint8*) Rte_Pim_Pim_CalRequestState()) &= ~ucBitMask;
  Rte_Pim_Pim_tCalNvMBlock()->ucCalRequestState &= (~ucBitMask);
  
  if(ui8IsModified != Rte_Pim_Pim_tCalNvMBlock()->ucCalRequestState)
  {
    Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_GetErrorStatus(&ErrorStatus); /* to avoid multi requests */
    if (ErrorStatus  != NVM_REQ_PENDING)
    {
      Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_SetRamBlockStatus(TRUE);/*Kl.15off->2NVM*/
    }
  }
} 

void ClearCalRequestStateAtMFDfinish( void )
{
  uint8 ui8IsModified;
  
  ui8IsModified = Rte_Pim_Pim_tCalNvMBlock()->ucCalRequestState;

  //(*(uint8*) Rte_Pim_Pim_CalRequestState()) &= ~ucBitMask;
  Rte_Pim_Pim_tCalNvMBlock()->ucCalRequestState &= (~0x0F);
  
  if(ui8IsModified != Rte_Pim_Pim_tCalNvMBlock()->ucCalRequestState)
  {
    Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_SetRamBlockStatus(TRUE);/*Kl.15off->2NVM*/
  }
} 

uint8 GETucCalRequestStateOfRam(void)
{
  //return (*(uint8*) Rte_Pim_Pim_CalRequestState());
	return Rte_Pim_Pim_tCalNvMBlock()->ucCalRequestState;
}

uint8 bGETucCalRequestState( uint8 ucBitMask )
{
  if((Rte_Pim_Pim_tCalNvMBlock()->ucCalRequestState & ucBitMask) !=0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
} 
/* CalRequestState END Value 4 Kalibrierung  CR_1211_130_050 */
/* **********************************************************************************************/
/* **********************************************************************************************/
/* FD: PrefFront PrefRear Value */
/*CRS_1211_130_251*/
uint8 GETucPrefFront(void)
{
	return Rte_Pim_Pim_tCalNvMBlock()->ucPrefFront;
}
uint8 GETucPrefRear(void)
{
 	return Rte_Pim_Pim_tCalNvMBlock()->ucPrefRear;
}

void PUTucPrefFront(uint8 x)
{
  NvM_RequestResultType ErrorStatus;
  Rte_Pim_Pim_tCalNvMBlock()->ucPrefFront = (x);
  Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_GetErrorStatus(&ErrorStatus); /* to avoid multi requests */
  if (ErrorStatus  != NVM_REQ_PENDING)
  {
    Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_SetRamBlockStatus(TRUE);/*Kl.15off->2NVM*/
  }
}
void PUTucPrefRear(uint8 x)
{
  NvM_RequestResultType ErrorStatus;
  Rte_Pim_Pim_tCalNvMBlock()->ucPrefRear = (x);
  Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_GetErrorStatus(&ErrorStatus); /* to avoid multi requests */
  if (ErrorStatus  != NVM_REQ_PENDING)
  {
    Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_SetRamBlockStatus(TRUE);/*Kl.15off->2NVM*/
  }
}
/* FD: PrefFront PrefRear Value */
/* **********************************************************************************************/
/* FD: Tref*/

sint8 GETscTref(void)
{
	return Rte_Pim_Pim_tCalNvMBlock()->scTref; 
}
void PUTscTref(sint8 x)
{
  NvM_RequestResultType ErrorStatus;
  Rte_Pim_Pim_tCalNvMBlock()->scTref = (x);
  Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_GetErrorStatus(&ErrorStatus); /* to avoid multi requests */
  if (ErrorStatus  != NVM_REQ_PENDING)
  {
    Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_SetRamBlockStatus(TRUE);/*Kl.15off->2NVM*/
  }
}
/*-------------------------------------------------------------------------------------------------
** BZ_FZZ_RQ_State4AFD_Finish
**/
/*
** Description
**/
/*
** Purpose:	Set and Clear all control Bits for Finish AFD 
**                      
**
** ------------------------------------------------------------------------------------------------
** Input:		non
**
** Output:	non
** ------------------------------------------------------------------------------------------------
**/
void BZ_FZZ_RQ_State4AFD_Finish(void)
{
	SetBitBetriebszustandBZ(cCAL_FINISH);
	ClearBitBetriebszustandBZ(cCAL_REQUEST); /*delete request bit 4 next calibration*/
	ClearBitFahrzeugzustandFZZ(cKFZPARKING_START_AFD); /* CRS_1211_130_170 clear look bit for AFD start reason 2*/
	//ClearBitCalRequestState(cCAL_AUTO_ACTIV);
	//ClearBitCalRequestState(cCAL_AUTO_ENABLE2);
	//ClearBitCalRequestState(cCAL_AUTO_ENABLE3);
	//ClearBitCalRequestState(cCAL_AUTO_NEW_ID); /*CRS_1211_130_267*/
	ClearBitCalRequestState(cCAL_AUTO_ACTIV | cCAL_AUTO_ENABLE2 | cCAL_AUTO_ENABLE3 | cCAL_AUTO_NEW_ID);
}	

/*-------------------------------------------------------------------------------------------------
** uint8 ucCheckPminDPautoAFD(uint8 ucRadPos)
**/
/*
** Description
**/
/*
** Purpose:             Kalibrierung: Plausibility Check 5.3.4 Minimum Pressure DP_AUTO
**                      
**
** ------------------------------------------------------------------------------------------------
** Input:              
**
** Output:             Result: TRUE/FALSE
** ------------------------------------------------------------------------------------------------
**/

uint8 ucCheckPminDPautoAFD(uint8 ucRadPos)
{
	uint8 ucRtn = FALSE;

	switch (ucRadPos)
	{
		case cRadPosVL:
    case cRadPosVR: /*ZOM/COLpos of cRadPosVL, cRadPosVR*/
		{
			if ( ucGetLastReceivedPress(ulGetID(ucGetColOfWP(ucRadPos))) <= (GETucPcalMinVaRelativCodOfRam() - cDP_AUTO)) /*100mbar CRS_1211_130_268 CRS_1211_130_152 logical data PAL: P_MIN_TIRE_4CAL  1,9bar!*/
			{
				ucRtn=TRUE; /*Abort filling detection*/
			}
		}
		break;
			
		case cRadPosHL:
		case cRadPosHR: /*ZOM/COLpos of cRadPosHL, cRadPosHR*/
		{
			if ( ucGetLastReceivedPress(ulGetID(ucGetColOfWP(ucRadPos))) <= (GETucPcalMinHaRelativCodOfRam() - cDP_AUTO)) /*100mbar CRS_1211_130_268 CRS_1211_130_152 logical data PAL: P_MIN_TIRE_4CAL  1,9bar!*/
			{
				ucRtn=TRUE; /*Abort filling detection*/
			}
		}
		break;
	}
	return ucRtn;
}
#ifdef as_FD_CalculateTref

/*-------------------------------------------------------------------------------------------------
** uint8 FD_CalculateTref(sint8 scTemperaturOutside)
**/
/*
** Description
**/
/*
** Purpose:             Berechnet Tref aus aktueller Reifentemperatur und Außentemperatur
**
**
** ------------------------------------------------------------------------------------------------
** Input:              Außentemperatur
**
** Output:             Referenztemperatur
** ------------------------------------------------------------------------------------------------
**/

sint8 FD_CalculateTref(sint8 scTemperaturOutside) 
{

	sint8 scTfillVA;
	sint8 scTfillHA;
	sint8 scTfill_Tref;

	scTfillVA= (ucGetHMICurrentTirePress(cRadPosVL) +  ucGetHMICurrentTirePress(cRadPosVR))/2);/*relativ pressure*/ 

	scTfillHA= (ucGetHMICurrentTirePress(cRadPosHL) +  ucGetHMICurrentTirePress(cRadPosHR))/2);/*relativ pressure*/		
	scTfill_Tref=(scTfillVA + scTfillHA)/2;
	scTfill_Tref=KweightCalculation(scTfill_Tref, scTemperaturOutside); /*CRS_1211_131_083 weighting factor K_WEIGHT for Tref*/

	return scTfill_Tref;
}

#endif