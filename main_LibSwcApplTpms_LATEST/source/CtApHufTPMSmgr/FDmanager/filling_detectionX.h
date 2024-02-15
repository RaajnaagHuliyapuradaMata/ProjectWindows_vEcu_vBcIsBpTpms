/************************************************************************************************************
 * (c) HuF Hülsbeck & Fürst GmbH Co.KG      Abteilung PDSTPS     2016
 ************************************************************************************************************/
/*********************************************************************************************************//**
 * file filling_detectionX.h
 * brief Manager 4 Filling Detection Manual + Automatic
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Attention! Here are all FD function for "extern" definition for including in other subfunctions
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
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

/* double include prevention */
#ifndef _FILLING_DETECTION_X_H
#define _FILLING_DETECTION_X_H



/************************************************************************************************************
 *                                             include
 ************************************************************************************************************/
#include "Platform_Types.h"

/************************************************************************************************************
 *                                             macro
 ************************************************************************************************************/
#define MODE_ok 0U

/************************************************************************************************************
 *                                            typedef
 ************************************************************************************************************/

/************************************************************************************************************
 *                                    data (Modulglobal) - ROM
 ************************************************************************************************************/

/************************************************************************************************************
 *                                    data (Modulglobal) - RAM
 ************************************************************************************************************/

/************************************************************************************************************
 *                                       data (global) - ROM
 ************************************************************************************************************/

/************************************************************************************************************
 *                                       data (global) - RAM
 ************************************************************************************************************/
 extern uint8 ucInitUSWalgoNew;
/***********************************************************************************************************
 *                                 prototype (local functions - private)
 ***********************************************************************************************************/

/***********************************************************************************************************
 *                                 prototype (local functions - public)
 ***********************************************************************************************************/
uint8 ucCheckCurrentPminWarn(void); /* in CtApHufTPMSmgr declaration*/

extern void FillingDetectionMFD(uint8); /*CRS_1211_130_312*/
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
extern void FD_UnplausibleMFD(void);/*CRS_1211_500_1279 CRS_1211_130_216*/
extern void FD_Check3RePlausiSetMilage4FinishedMFD(void);/*FD CRS_1211_130_335*/
extern void FD_Check3ReAndUpdatePifWarnLampOnOffDefOrInf2Re4FinishedAFD(void); /*FD CRS_1211_130_335*/


extern void FD_UpdatePressure4AfdWarnLampON(uint8, sint8 );
extern void FD_UpdatePressure4AfdWarnLampOFF(uint8 , uint8, sint8 );

extern uint8 FD_UpdateComparePressureAfterFBM(void);
extern void FD_UpdateComparePressureAtWarning(uint8);
// never used extern void FD_UpdateComparePressure4NewId(uint8, sint8, sint8, uint8 ); /*CRS_1211_130_184*/
extern uint8 FD_LoadIdValues4UpdateCompareValue(void);

extern uint8 FD_UpdateIDvalue4MFD(void); /*CRS_1211_130_335*/

extern uint8 FD_Plausibility_CheckP4DPLR_DPABS(uint8,uint8,uint8,uint8);/* Check pressure: DP_LR + DP_ABS and set Pref Tref Pcompare*/ 
extern uint8 FD_CheckCurrentPmin(void); /*CRS_1211_130_332 Check Pmin for stoped the FD immediately*/

extern uint8 FD_FlowChartFct1CheckPmin(void); /*CRS_1211_130_347*/
extern uint8 FD_FlowChartFct1CheckMissingRE(void); /*CRS_1211_130_347*/

extern uint8 FD_FlowChartFct1(void);/*CRS_1211_130_335*/

extern uint8 FD_CheckFDpos2ZomPosAfterZOfinish(void);/*CRS_1211_130_336*/

extern uint8 GetP4NewTempAtCAL(uint8, sint8, sint8);

extern void  PUTucCalNotAckState2Ram(uint8);/*FD*/
extern void ClearCalNotAckState(void);/*FD*/
extern void ClearCalNotAckState4MFD(void);/*FD*/
extern void SetBitCalRequestState2Ram( uint8 );/*FD*/
extern void PUTucCalRequestState2Ram(uint8); /*FD*/
extern uint8 bGETucCalRequestState( uint8 );/*FD*/
extern void ClearBitCalRequestState( uint8  );/*FD*/
extern void ClearCalRequestStateAtMFDfinish( void ); /*FD*/

/************************************************************************************************************
 *                               prototype (external functions - interface)
 ************************************************************************************************************/
/* 4x P+T ID ZOM specific in CtApHufTPMSmgr.c */ 
extern void  PUTucIdCalPressure(uint8 , uint8 );/*Init ID Zom spezifisch for first calibration*/
extern uint8 GETucIdCalPressure(uint8);
extern void  PUTscIdCalTemperatur(sint8 , uint8 );/*Init ID Zom spezifisch for first calibration*/
extern sint8 GETscIdCalTemperatur(uint8);/*Init ID Zom spezifisch for first calibration*/


/* 2Pref+1Tref   CtApHufTPMSmgr.c */ 
extern void  PUTucPrefFront(uint8);/*Init Pos spezifisch for first calibration*/
extern uint8 GETucPrefFront(void);
extern void  PUTucPrefRear(uint8);/*Init Pos spezifisch for first calibration*/
extern uint8 GETucPrefRear(void);


extern void  PUTscTref(sint8);/*Tref for first calibration*/
extern sint8 GETscTref(void);/*Init Pos spezifisch for first calibration*/
/* 4x Pref+Tref  4x P+T ID ZOM 2 NVM in CtApHufTPMSmgr.c */ 



extern void SetBitCalNotAckState2Ram( uint8 );
extern void ClearBitCalNotAckState( uint8 );
extern uint8 GETucCalNotAckStateOfRam(void);
extern uint8 bGETucCalNotAckState( uint8 );
extern void PUTucCalRequestState2Ram( uint8 );
extern uint8 GETucCalRequestStateOfRam(void);

extern void BZ_FZZ_RQ_State4AFD_Finish(void);

/*  Pfill Front +Rear in CtApHufTPMSmgr.c */
extern void PUTucPfillFront(uint8);
extern uint8 GETucPfillFront(void);
extern void PUTucPfillRear(uint8);
extern uint8 GETucPfillRear(void);
/*  Tfill Front +Rear in CtApHufTPMSmgr.c */
extern void PUTscTfill(sint8);
extern sint8 GETscTfill(void);

#ifdef AS_ID_VALUE
extern void PUTucReCntVL4FD(uint8);
extern void INCucReCnt4FD(uint8);
extern uint8 GETucReCntVL4FD(void);
extern uint8 GETucReCnt4FD(uint8);

#endif
/* NEW ID changed in history or ZOM CtApHufTPMSdia.c*/
extern uint8 GETucPrevPosStatInfoWU(uint8);

extern uint8 FD_CheckHistPos(void); /*CRS_1211_130_345*/

extern void PUTuiStoragePaverege4CompareValue(uint16, uint8);
extern uint16 GETuiStoragePaverege4CompareValue(uint8);
extern uint8 GETucStoragePaverege4CompareValue(uint8);

extern void FD_HandleReceivedReRadPosVL4AFD(uint8,sint8,uint8,uint8);
extern void FD_HandleReceivedReRadPosVR4AFD(uint8,sint8,uint8,uint8);
extern void FD_HandleReceivedReRadPosHL4AFD(uint8,sint8,uint8,uint8);
extern void FD_HandleReceivedReRadPosHR4AFD(uint8,sint8,uint8,uint8);

extern void PUTucCnt4DP_FILL_DFL(uint8); /*FD*/
extern uint8 GETucCnt4DP_FILL_DFL(void); /*FD*/

extern void PUTucCnt4DP_FILL_IFL(uint8); /*FD*/
extern uint8 GETucCnt4DP_FILL_IFL(void); /*FD*/

extern void ClearBitInNoCheckPmin4StopFD(uint8); /* 4 mgr CRS_1211_130_325*/

/************************************************************************************************************
 *                                             include
 ************************************************************************************************************/




#endif