/************************************************************************************************************
 * (c) Beru Electronics GmbH      Abteilung BES2     2008
 ************************************************************************************************************/
/************************************************************************************************************
 * Project:       Reifendruckkontrolle TSS (TSS = tyre safety system)
 *
 * $Archive: /BMW/G3kompakt/Sw/SC4/template_can/application/source/tssappl/statemanager/state_fzzX.h $
 *
 * File Status:   compiled           - (under construction, compiled etc.)
 *
 ************************************************************************************************************/
/************************************************************************************************************
 * Author:        Uwe Rapp           Beru Electronics GmbH (BES)
 *
 * Intials:       ur
 ************************************************************************************************************/
/************************************************************************************************************
 * Global Description
 * ==================
 *
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
 * FZZ: Fahrzeugzustand
 *
 ************************************************************************************************************/
/************************************************************************************************************
 * Glossary
 * ========
 *
 *
 *
 ************************************************************************************************************/

#ifndef _state_fzz_X_H /* [0] */
#define _state_fzz_X_H



/************************************************************************************************************
 *                                             include
 ************************************************************************************************************/
//#include "tss_stdx.h"         /* TSS specific defines                                                       */
//#include "statemanager_CFG.h" /* Configuration-Header of statemanager module                                */


/************************************************************************************************************
 *                                             macro
 ************************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////
// Bitmasken f�r Interfacefunktionen                                                                                         *
////////////////////////////////////////////////////////////////////////////////////////////
// FAHRZEUGZUSTAND
#define cKL_15_EIN            ((uint16) 0x0001)   // Z�ndung ein
#define cRS_VTHRES            ((uint16) 0x0002)   // "1" => Fahrzeuggeschwindigkeit hat die Ansprechschwelle
                                                  //        f�r Roll-Switch �berschritten
#define cFAHRZEUG_FAEHRT      ((uint16) 0x0004)   // "1" => Fahrzeug f�hrt nach Herstellerspez.
#define cRUECKWAERTSFAHRT     ((uint16) 0x0008)   // "1" => Fahrzeug f�hrt r�ckw�rts
#define cVEH_ABSSTICKS_MOVE   ((uint16) 0x0010)   // "1" => ABS rotation detected for last 200 ms
#define cKFZFAEHRT_20KMH      ((uint16) 0x0020)   // "1" => Fahrzeug f�hrt v>20kmh um RE-Druck bei KAL einzusammlen
#define cKFZPARKING_START_AFD ((uint16) 0x0040)   // "1" => Fahrzeug startet in die Parking Zeit, nach 19min und Kl15Ein start der AUTO calibration
#define cENG_STARTING         ((uint16) 0x0200)   // wie der Name sagt - Motor l�uft
#define cENG_RUNNING          ((uint16) 0x0400)   // wie der Name sagt - Motor l�uft
#define cFAILURE_MONITORING   ((uint16) 0x0800)   // Failure monitoring activated for CAN Timeout and Voltage monitoring DTCs

#define cTPMS433Mhz						((uint16) 0x1000)   // wie der Name sagt - TPMS RE SG Empfangsfrequenz 433Mhz
#define cTPMS315Mhz 					((uint16) 0x2000)   // wie der Name sagt - TPMS RE SG Empfangsfrequenz 315Mhz
#define cKL30_UNTERSPG				((uint16) 0x4000)   // wie der Name sagt - Bordnetz lt. Diagnose Spec Unterspannung
#define cKL30_UEBERSPG				((uint16) 0x8000)   // wie der Name sagt - Bordnetz lt. Diagnose Spec �berspannung
#define cFZZ_ALLE_BITS        ((uint16) 0xffff)   // Maske f�r komplette Fahrzeugzustandsvariable
/*
#define cFAHRZEUG_STEHT       ((uint16) 0x0002)   // Car standstill
#define cFAHRZEUG_FAEHRT      ((uint16) 0x0004)   // "1" => Fahrzeug f�hrt nach Herstellerspez.
#define cRUECKWAERTSFAHRT     ((uint16) 0x0008)   // "1" => Fahrzeug f�hrt r�ckw�rts
#define cENG_RUNNING         ((uint16) 0x0400)   // wie der Name sagt - Motor l�uft
#define cFZZ_ALLE_BITS        ((uint16) 0xffff)   // Maske f�r komplette Fahrzeugzustandsvariable
*/

// list of monitored Can Signals monitored
#define cFZZ_WHLPLS_FL_IMPLAU     ((uint16) 0x0001)   // wheel pulse
#define cFZZ_WHLPLS_FR_IMPLAU     ((uint16) 0x0002)   // wheel pulse
#define cFZZ_WHLPLS_RL_IMPLAU     ((uint16) 0x0004)   // wheel pulse
#define cFZZ_WHLPLS_RR_IMPLAU     ((uint16) 0x0008)   // wheel pulse

#define cFZZ_TRACTION_SYSTEM_IMPLAU     ((uint16) 0x0010)   // "wheel pulse counter time stamp
#define cFZZ_VEH_SPEED_IMPLAU           ((uint16) 0x0020)   // Vehicle speed, Outside air temp, IC-A3_TPM_Activ_Rq
#define cFZZ_AIRTEMP_OUT_IMPLAU         ((uint16) 0x0040)   // Vehicle speed, Outside air temp, IC-A3_TPM_Activ_Rq
#define cFZZ_IC_A3_TPM_ACTV_IMPLAU      ((uint16) 0x0080)   // Vehicle speed, Outside air temp, IC-A3_TPM_Activ_Rq
#define cALL_CAN_SIGNALS                ((uint16) 0xffff) 

#define cFZZ_WHLPLS_CNT_TIMEOUT       ((uint16) 0x0001)   // wheel pulse
#define cFZZ_IGN_VEH_STAT_TIMEOUT     ((uint16) 0x0002)   // ignition stat
#define cFZZ_ENG_CTRL_TIMEOUT         ((uint16) 0x0004)   // engine control, 
#define cFZZ_PRESS_OUT_TIMEOUT        ((uint16) 0x0008)   // engine control
#define cFZZ_PN14_STAT_TIMEOUT        ((uint16) 0x0010)   // front signal aquisition and actuation module
#define cFZZ_IC_BASIC_INFO_TIMEOUT    ((uint16) 0x0020)   // air temp, veh speed, Odo
#define cFZZ_IC_DATE_TIME_TIMEOUT     ((uint16) 0x0040)   // ic date
#define cFZZ_IC_SETTINGS_TIMEOUT      ((uint16) 0x0080)   //tmp actv 
#define cFZZ_CANSM_BUSOFF_Network     ((uint16) 0x0100)   //tmp actv 

typedef enum HufEngStat
{
  cEngStat_STOPPED,
  cEngStat_STARTING,
  cEngStat_RUNNING,
}HufEngStat;
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



/***********************************************************************************************************
 *                                 prototype (local functions - public)
 ***********************************************************************************************************/
extern void InitFZZ( void );

extern void SetBitFahrzeugzustandFZZ( uint16 );
extern void ClearBitFahrzeugzustandFZZ( uint16 );
extern boolean bGetBitFahrzeugzustandFZZ( uint16 );
extern uint16 ushGetFahrzeugzustandFZZ( uint16 );

extern void EvTerminal15OnFZZ( void );
extern void EvTerminal15OffFZZ( void );

extern void EvVehicleRollingFZZ( void );
extern void EvVehicleSpeed4CalFZZ( void ); /*CRS_1211_130_065*/
extern void EvVehicleStandsStillFZZ( void );
extern void EvVehicleNoSpeed4CalFZZ( void ); /*CRS_1211_130_065*/

extern void EvKl30DiagUeberSpgFZZ( void ); /*CRS_1211_050_004*/
extern void EvKl30DiagNoUeberSpgFZZ( void );

extern void EvKl30DiagUnterSpgFZZ( void ); /*CRS_1211_050_004*/
extern void EvKl30DiagNoUnterSpgFZZ( void );

extern void EvTPMS433MhzFZZ( void );	/*CRS_1211_150_100*/
extern void EvTPMS315MhzFZZ( void );	/*CRS_1211_150_100*/

extern void EvReDiagActiveFZZ( void );
extern void EvReDiagInactiveFZZ( void );

extern void EvEngineRunningFZZ( void );
extern void EvEngineStopedFZZ( void );
extern void EvEngineStartingFZZ(void);

extern void EvDriveDirectionForwardFZZ( void );
extern void EvDriveDirectionBackwardFZZ( void );

extern uint32 GETulKilometersFZZ( void );
extern uint32 GETulSysTimeFZZ( void );
extern sint8 GETscOutdoorTemperatureFZZ( void );
extern uint16 GETushSpeedFZZ( void );

extern uint8 ucGetEcuStopCntr(void);
extern void SendEnvData2VehStateMgr(uint8*);
extern void UpdateFzzCurrentLearnMode(void);
extern void UpdateFzzDTcEnableCond(void);
extern uint8 ucGetFzzCurrentLearnMode(void);

extern void ClearFzzSignalUnplausibleState(uint16);
extern void ClearFzzSignalUnplausibleCntr(uint16 ushBitMask);
extern boolean bGetFzzSignalEnableDtcSetCond(uint16);
extern void SetFzzSignalImplauState(uint16);
extern void InitFzzignalMonitor(void);
extern boolean bGetFzzEnableImplauDtcInstruCluster(void);
extern void ClearFzzSignalTimeOutState(uint16 ushBitMask);
extern void SetFzzSignalTimeOutState(uint16 ushBitMask);
extern boolean bGetFzzCanSignalImplausibleState(uint16 ushBitMask);
//extern boolean bGETucCalRequestState( uint8 ushBitMask );
//extern void SetBitCalRequestState2Ram( uint8 ucBitMask );
//extern void ClearBitCalRequestState( uint8 ucBitMask );
//extern void PUTucCalRequestState2Nvm(void);
uint8  bGetABSSignalDTCActive(void);

uint8  bGetKl30HighDTCActive(void);
uint8  bGetKl30LowDTCActive(void);
uint8  bGetPN14SupbatHighDTCActive(void);
uint8  bGetPN14SupbatLowDTCActive(void);


extern void SetFzzState4MM(uint8 state);
extern uint8 GetFzzState4MM(void);
extern void SetGlobWarnState4MM(uint8 state);
extern uint8 GetGlobWarnState4MM(void);
/************************************************************************************************************
 *                               prototype (external functions - interface)
 ************************************************************************************************************/


#endif /* #ifndef _state_fzz_X_H [0] */


