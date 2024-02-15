/************************************************************************************************************
 * (c) Beru Electronics GmbH      Abteilung BES2     2008
 ************************************************************************************************************/
/************************************************************************************************************
 * Project:       Reifendruckkontrolle TSS (TSS = tyre safety system)
 *
 * $Archive: /VAG/VW47x/SW/S12XS/SP/application/source/tssappl/statemanager/state_bzX.h $
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
 * BZ: Betriebszustand
 *
 ************************************************************************************************************/
/************************************************************************************************************
 * Glossary
 * ========
 *
 *
 *
 ************************************************************************************************************/
/************************************************************************************************************
 * Modul Modification
 * ==================
 *
 * $Log: /VAG/VW47x/SW/S12XS/SP/application/source/tssappl/statemanager/state_bzX.h $
 * 
 * 5     26.02.10 10:29 Dederer
 * Systemzustand Teileigenrad definiert (VW47x OIL #62)
 *
 * 4     14.07.09 15:31 Rapp
 * OIL #395: Zustandsbit der Schatten-ZOM in BZ spiegeln
 *
 * 3     11.12.08 18:51 Rapp
 * Reaktion bei ZO-Timeout korrigiert
 *
 * 2     27.06.08 10:03 Rapp
 * Bitfelder umsortiert (wie G2)
 *
 * 1     17.06.08 10:43 Rapp
 * Integration "Statemanager"
 *
 *
 ************************************************************************************************************/
#ifndef _state_bz_X_H /* [0] */
#define _state_bz_X_H



/************************************************************************************************************
 *                                             include
 ************************************************************************************************************/
#include "tss_stdx.h"         /* TSS specific defines                                                       */
//#include "statemanager_CFG.h" /* Configuration-Header of statemanager module                                */



/************************************************************************************************************
 *                                             macro
 ************************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////
// Bitmasken für Interfacefunktionen                                                                                         *
////////////////////////////////////////////////////////////////////////////////////////////
// BETRIEBSZUSTAND
#define cER_FINISH            ((uint16) 0x0001)   // Eigenradbestimmung abgeschlossen
#define cBZ_Frei0             ((uint16) 0x0002)   // ALT: Zu viele RE während der Eigenradbestimmung empfangen
#define cAL_RUNNING           ((uint16) 0x0004)   // Autolacation  is running
#define cEIGENRAD             ((uint16) 0x0008)   // Radzuordnung (Historie): 0 = kein Eigenrad, 1 = Eigenrad
#define cZUGEORDNET           ((uint16) 0x0010)   // Radzuordnung (Historie): 0 = nicht zugeordnet, 1 = zugeordnet
#define cZO_Fallback2Hist     ((uint16) 0x0020)   // all wheel allocation actions are finally stopped
#define cHIST_PRELOAD         ((uint16) 0x0040)   // system is running with history wheel allocation
#define cZO_FINISH            ((uint16) 0x0080)   // Radpositionsbestimmung abgeschlossen
#define cCAL_REQUEST          ((uint16) 0x0100)   // 1 => Kalibrierung angefordert
#define cCAL_MFD_PLAUSI_ERROR ((uint16) 0x0200)   // 1 => negative Quittung auf eine MFD Kalibrierung + 9min calibration timeout expired
#define cCAL_AFD_PLAUSI_ERROR ((uint16) 0x0400)   // AFD auto filling detect: Filling not detected ONE wheel inflated/deflated( Filling detection flow chart 5.2) 
#define cDTC_INACTIVE         ((uint16) 0x0800)   // Inaktiv durch Fehlerspeichereintrag 21.11.2016 AS ROM Fehler
#define cZO_TIMEOUT           ((uint16) 0x1000)   // Timer Radmanagement abgelaufen
#define cZO_ERROR             ((uint16) 0x2000)   // AUTOLOCATE Error
#define cTEILZUGEORDNET       ((uint16) 0x4000)    // frei
#define cCAL_FINISH           ((uint16) 0x8000)   // Calibration is finish: set all pressure 2 warnhandler
#define cBZ_ALLE_BITS         ((uint16) 0xffff)   // Maske für komplette Betriebszustandsvariable

/* FD KALIBRRIERUNG **ucCalNotAckState**  */
#define cCAL_VALID										((uint8) 0x00)   // valid 
#define cCAL_DP_LR_FA_NAK							((uint8) 0x01)   // MFD Plausi check 17%:							set MFD_PLAUSI ERROR - tire pressure on front axis invalid 17%
#define cCAL_DP_LR_RA_NAK							((uint8) 0x02)   // MFD Plausi check 17%:							set MFD_PLAUSI ERROR - tire pressure on rear axis invalid 17%
#define cCAL_DP_ABS_NAK								((uint8) 0x04)   // MFD Plausi check DP_ABS:					set MFD_PLAUSI ERROR - differenc pressure between wheels >150mbar DP_ABS
#define cCAL_P_MIN_X_MINUS_DP_MANUAL	((uint8) 0x08)   // MFD Plausi check Pmin-DP_MANUAL(200mbar) : set MFD_PLAUSI ERROR in BZ 
#define cCAL_RE30K2AMBIENT						((uint8) 0x10)   // AFD Start Reason 2 or 3: tire temp  over t_ambient+30K
#define cCAL_DP_STABI_NAK							((uint8) 0x20)   // AFD  DP_STABI: max pressure difference for stabilized condition 10kPa 5.3.4 AFD
#define cCAL_FBM_ACTIV_NAK						((uint8) 0x40)   // Fall Back Mode activ --> disable AFD 
#define cCAL_P_MIN_TIRE_NAK						((uint8) 0x80)   // NO Plausi -> Pmin= ABORT FDtire pressure to small below P_MIN_TIRE

/* FD Übergabe wert 4 Funktion FD_AbortFillingDetection ONLY*/
#define cCAL_ABORT_REASON_2_3 ((uint8) 0x00)   // AFD Plausi&AbortFD: set AFD_PLAUSI ERROR ->Abort - reason in Fill_detect_start_reason2_3 5.2 FD: AFD Check in ReceivTelData() 
#define cCAL_RE_MISSING_NAK   ((uint8) 0x40)   // NO Plausi -> NO 3 or more telegrams received from all 4 sensors


/* FD KALIBRRIERUNG **ucCalRequestState** */
#define cCAL_AUTO_ACTIV 						((uint8) 0x01)   // Kalibrieranforderung aktiv, Filling Detection AUTOMATIC of TPMS (5.1.2) 
#define cCAL_AUTO_ENABLE2						((uint8) 0x02)   // Kalibrieranforderung aktiv, Filling Detection AUTOMATIC of TPMS (5.1.2) reason 2 
#define cCAL_AUTO_ENABLE3						((uint8) 0x04)   // Kalibrieranforderung aktiv, Filling Detection AUTOMATIC of TPMS (5.1.2) reason 3
//#define cCAL_AUTO_FINISH						((uint8) 0x08)   // Kalibrieranforderung aktiv, Filling Detection AUTOMATIC of TPMS (5.1.2)
#define cCAL_AUTO_NEW_ID						((uint8) 0x08)   // 5.6.3 New sensors are learnt: Storing compare value of THIS SENSOR and start AFD in next drive!
#define cCAL_AUTO_FIRST							((uint8) 0x10)   // AFD auto filling detected FREE for first time (within first 100km*/ 
#define cCAL_MANUAL_ACTIV						((uint8) 0x20)   // Kalibrieranforderung aktiv, Filling Detection MANUAL Restart of TPMS (5.1.1)
#define cCAL_MSG2DISP								((uint8) 0x40)   // Kalibrieranforderung aktiv, Filling Detection MANUAL Restart of TPMS (5.1.1)
#define cCAL_MANUAL_FINISH					((uint8) 0x80)   // Kalibrieranforderung aktiv, Filling Detection MANUAL Restart of TPMS (5.1.1)


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
extern void InitBZ( void );

extern void SetBitBetriebszustandBZ( uint16 );
extern void ClearBitBetriebszustandBZ( uint16 );
extern boolean bGetBitBetriebszustandBZ( uint16 );
extern uint16 ushGetBetriebszustandBZ( uint16 );
extern uint8 ucGetBetriebszustandLByte( void );
extern uint8 ucGetBetriebszustandHByte( void );



/************************************************************************************************************
 *                               prototype (external functions - interface)
 ************************************************************************************************************/



#endif /* #ifndef _state_bz_X_H [0] */
