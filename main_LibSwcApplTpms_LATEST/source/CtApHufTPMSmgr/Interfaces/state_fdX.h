/************************************************************************************************************
 * (c) Huf Huelsbeck und Fuerst GmbH Co. KG   Abteilung PDSTPS    2016
 ************************************************************************************************************/
/************************************************************************************************************
 * Project:       Reifendruckkontrolle TSS (TSS = tyre safety system)
 *
 * $Archive: /BMW/G3kompakt/Sw/SC4/template_can/application/source/tssappl/statemanager/state_fdX.h $
 *
 * File Status:   compiled           - (under construction, compiled etc.)
 *
 ************************************************************************************************************/
/************************************************************************************************************
 * Author:
 *
 * Initials     Name                           Company
 * --------     --------------------------     --------------------------------------------------------------
 * as           Andreas Schubert               Huf Huelsbeck und Fuerst GmbH Co. KG
 *
 ************************************************************************************************************/
/************************************************************************************************************
 * Global Description
 * ==================
 *
 *
 *
 *
 *
 ************************************************************************************************************/
/************************************************************************************************************
 * Modul Description
 * =================
 *
 * Purpose:
 *
 *
 *
 ************************************************************************************************************/
/************************************************************************************************************
 * Modul Abbreviation:
 * ===================
 *
 *
 ************************************************************************************************************/
/************************************************************************************************************
 * Glossary
 * ========
 *
 *
 ************************************************************************************************************/
/************************************************************************************************************
 * MISRA-C 2004 Regelverletzungen
 * ==============================
 *
 *
 ************************************************************************************************************/
/************************************************************************************************************
 * Modul Modification
 * ==================
 *
 * changes in 2016
 *
 * $Log: /_TSS/DAG/MFA2/Target/SWC/Source/CtApHufTPMSmgr/Statemanager/state_fdX.c $
 * 
 *
 * 1     25.04.16 Schubert
 * creation  "Statemanager"
 *
 ************************************************************************************************************/
#ifndef _state_fd_X_H /* [0] */
#define _state_fd_X_H



/************************************************************************************************************
 *                                             include
 ************************************************************************************************************/
//#include "tss_stdx.h"         /* TSS specific defines                                                       */
//#include "statemanager_CFG.h" /* Configuration-Header of statemanager module                                */



/************************************************************************************************************
 *                                             macro
 ************************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////
// Bitmasken für Interfacefunktionen                                                                                         *
////////////////////////////////////////////////////////////////////////////////////////////


// KALIBRRIERUNG **ucCalNotAckState**
//#define cCAL_VALID            ((uint8) 0x00)   // valid 
//#define cCAL_DP_LR_FA_NAK     ((uint8) 0x01)   // tire pressure on front axis invalid 17%
//#define cCAL_DP_LR_RA_NAK     ((uint8) 0x02)   // tire pressure on rear axis invalid 17%
//#define cCAL_RE_MISSING_NAK   ((uint8) 0x04)   // NO 3 or more telegrams received from all 4 sensors
//#define cCAL_P_MIN_TIRE_NAK   ((uint8) 0x08)   // tire pressure to small below P_MIN_TIRE
//#define cCAL_RE30K2AMBIENT    ((uint8) 0x10)   // tire temp  over t_ambient+30K
//#define cCAL_DP_P_MIN_X_NAK   ((uint8) 0x20)   // tire pressure to small below P_MIN_X (X=VA or X=HA)
//#define cCAL_DP_ABS_NAK       ((uint8) 0x40)   // differenc pressure between wheels >150mbar DP_ABS
//#define cCAL_DP_STABI_NAK     ((uint8) 0x80)   // DP_STABI: max pressure difference for stabilized condition 10kPa 5.3.4 AFD
//#define cCAL_FILL_NOT_DETECT  ((uint8) 0x80)   // Filling not detected ONE wheel inflated/deflated( Filling detection flow chart 5.2) 



// KALIBRRIERUNG **ucCalRequestState**
//#define cCAL_AUTO_ACTIV 						((uint8) 0x01)   // Kalibrieranforderung aktiv, Filling Detection AUTOMATIC of TPMS (5.1.2) 
//#define cCAL_AUTO_ENABLE2						((uint8) 0x02)   // Kalibrieranforderung aktiv, Filling Detection AUTOMATIC of TPMS (5.1.2) reason 2 
//#define cCAL_AUTO_ENABLE3						((uint8) 0x04)   // Kalibrieranforderung aktiv, Filling Detection AUTOMATIC of TPMS (5.1.2) reason 3
//#define cCAL_AUTO_FINISH						((uint8) 0x08)   // Kalibrieranforderung aktiv, Filling Detection AUTOMATIC of TPMS (5.1.2)
//#define cCAL_AUTO_FIRST							((uint8) 0x10)   // AFD auto filling detected FREE for first time (within first 100km*/ 
//#define cCAL_MANUAL_ACTIV						((uint8) 0x20)   // Kalibrieranforderung aktiv, Filling Detection MANUAL Restart of TPMS (5.1.1)
//#define cCAL_MSG2DISP								((uint8) 0x40)   // Kalibrieranforderung aktiv, Filling Detection MANUAL Restart of TPMS (5.1.1)
//#define cCAL_MANUAL_FINISH					((uint8) 0x80)   // Kalibrieranforderung aktiv, Filling Detection MANUAL Restart of TPMS (5.1.1)

// STATE FILLING DETECTED Function
#define cFD_DEFAULT									((uint8) 0x00)	// Filling Detection of TPMS (5.1.2)
#define cMFD_RUNNING								((uint8) 0x01)	// Filling Detection of TPMS (5.1.2)
#define cAFD_RUNNING2 							((uint8) 0x02)	// Filling Detection of TPMS (5.1.2) 
#define cAFD_RUNNING3 							((uint8) 0x03)	// Filling Detection of TPMS (5.1.2) 
//#define cAFD_RUNNING_NEW_ID 				((uint8) 0x04)	// Filling Detection of TPMS (5.1.2) CRS_1211_130_206 entfällt
#define cFILLING_DETECTED						((uint8) 0x04)  // Filling Detection of TPMS (5.1.2)
#define cFILLING_UNPLAUSIBLE				((uint8) 0x05)  // Filling Detection of TPMS (5.1.2)
#define cFILLING_DETECT_ABORTED			((uint8) 0x06)  // Filling Detection of TPMS (5.1.2)
#define cFILLING_NOT_DETECTED				((uint8) 0x07)  // Filling Detection of TPMS (5.1.2)
#define cFD_MILEAGE2SMALL						((uint8) 0x08)  // Filling Detection Failure on the basis of 2.Definition
#define cFD_ACTIV_WARNING						((uint8) 0x09)  // Filling Detection Failure on the basis of 2.Definition
#define cFD_LTS30DAYS								((uint8) 0x0A)	// Filling Detection Failure on the basis of 2.Definition
#define cFD_RE_POS_CHANGE						((uint8) 0x0B)	// Filling Detection Self wheel position change for info only
#define cFD_INDEX_10								((uint8) 0x10)	// TEST AUSGABE 4Filling Detection
#define cFD_INDEX_20								((uint8) 0x20)	// TEST AUSGABE 4Filling Detection
#define cFD_INDEX_30								((uint8) 0x30)	// TEST AUSGABE 4Filling Detection



// STATE FILLING DETECTED ABORT REASON = FD_abort_reason (AFD) complete value NO BITs!!!! 
//#define cFD_P_MIN_TIRE_AFD					((uint8) 0x01)   // CRS_1211_130_206 Filling Detection Abort on the basis of PminTPMS 2.Definition
#define cFD_DP_AUTO		 							((uint8) 0x01)   // Filling Detection Abort on the basis of 2.Definition
#define cFD_TIRE2HOT								((uint8) 0x02)   // Filling Detection Abort on the basis of 2.Definition
#define cFD_DP_STABI								((uint8) 0x03)   // Filling Detection Abort on the basis of 2.Definition
#define cFD_P_MIN_TIRE							((uint8) 0x04)   // CRS_1211_130_206 Filling Detection Plausibility Failure on the basis of 2.Definition
//#define cFD_DP_MANUAL								((uint8) 0x05)   // CRS_1211_130_206  Filling Detection Plausibility Failure on the basis of 2.Definition
//#define cFD_DP_ABS									((uint8) 0x07)   // Doppelt Filling Detection Plausibility Failure on the basis of 2.Definition
//#define cFD_DP_LR										((uint8) 0x08)   // Doppelt Filling Detection Plausibility Failure on the basis of 2.Definition
#define cFD_MISSING_SENSOR					((uint8) 0x05)   // Filling Detection Plausibility Failure on the basis of 2.Definition
#define cFD_TIMEOUT									((uint8) 0x06)   // Filling Detection Plausibility Failure on the basis of 2.Definition
//#define cFD_NON_IN_OR_DEFLATED			((uint8) 0x08)   // CRS_1211_130_206  Filling Detection Plausibility Failure on the basis of 2.Definition
//#define cFD_MILEAGE2SMALL						((uint8) 0x0A)   // Filling Detection Plausibility Failure on the basis of 2.Definition
//#define cFD_ACTIV_WARNING						((uint8) 0x0B)   // Filling Detection Plausibility Failure on the basis of 2.Definition
#define cFD_FBM_ACTIV								((uint8) 0x07)   // TEST AFD Filling Detection Abort: Fall Back Mode aktiv
//#define cFD_NEWID4AFD2NEXTDRIVE			((uint8) 0x08)   // CRS_1211_130_267 disable OIL#755 AFD2 aktiv aber es werden eine oder mehrere neue ID im System erkannt, AFD in next drive

// STATE PLAUSIBILITY FAILURE REASON complete value NO BITs!!!! 
#define cFD_LEFT_RIGHT_DIFFERENCE		((uint8) 0x01)
/*#define cFD_MINIMUM_PRESSURE				((uint8) 0x02)   gibt es nicht mehr  */
#define cFD_ABSOLUTE_PRESSURE_DIFF 	((uint8) 0x03)		// DP_ABS 1,5bar absolute differenz 
#define cFD_DP_MANUAL								((uint8) 0x04)   // DP_MANUAL=200mbar CRS_1211_130_206 Filling Detection Plausibility Failure on the basis of 2.Definition
#define cFD_FALL_BACK_NOPOS					((uint8) 0x05)

#define cFLAG_VL										((uint8) 0x01)   // Filling Detection of TPMS (5.4.1)
#define cFLAG_VR 										((uint8) 0x02)   // Filling Detection of TPMS (5.4.1) 
#define cFLAG_HL 										((uint8) 0x04)   // Filling Detection of TPMS (5.4.1) 
#define cFLAG_HR			 							((uint8) 0x08)   // Filling Detection of TPMS (5.4.1) 




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



/***********************************************************************************************************
 *                                 prototype (local functions - private)
 ***********************************************************************************************************/
extern void ClearNewIdColXMem4FD( uint8 );
extern uint8 GetNewIdColX4FD( uint8 );

extern void  SetIdCol0New4FD( uint8 );
extern uint8 GetIdCol0New4FD( void );
extern void  SetIdCol1New4FD( uint8 );
extern uint8 GetIdCol1New4FD( void );
extern void  SetIdCol2New4FD( uint8 );
extern uint8 GetIdCol2New4FD( void );
extern void  SetIdCol3New4FD( uint8 );
extern uint8 GetIdCol3New4FD( void );


/***********************************************************************************************************
 *                                 prototype (local functions - public)
 ***********************************************************************************************************/
extern uint8 Get_FD_STATUS( void );
extern void SetBitFillingDetectionStateFD( uint8 );
extern void ClearBitFillingDetectionStateFD( uint8 );
extern boolean bGetBitFillingDetectionStateFD( uint8 );
extern void SetState2FillingDetectionStateFD( uint8 );
extern void ClearFillingDetectionStateFD(void);

extern uint8 Get_FD_ABORT_REASON(void );
extern void SetBitAbortReasonFD( uint8 );
extern void ClearBitAbortReasonFD( uint8 );
extern void SetState2AbortReasonFD( uint8 );
extern void ClearAbortReasonFD(void);

extern uint8 Get_FD_PLAUSIBILITY_FAILURE(void );
extern void ClearPlausiFailureLeftRightAbsFD( void );
extern void SetBitPlausiFailureFD( uint8 );
extern void ClearBitPlausiFailureFD( uint8 );
extern void SetState2PlausiFailureFD( uint8 );
extern void ClearPlausiFailureFD(void);



/************************************************************************************************************
 *                               prototype (external functions - interface)
 ************************************************************************************************************/





/************************************************************************************************************
 *                               prototype (external functions - interface)
 ************************************************************************************************************/



#endif /* #ifndef _state_bz_X_H [0] */
