/************************************************************************************************************
 * (c) HuF Hülsbeck & Fürst GmbH Co.KG      Abteilung PDSTPS     2016
 ************************************************************************************************************/
/*********************************************************************************************************//**
 * \file filling_detection.h
 * \brief Manager 4 Filling 
* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Attention! Here are all "CtApHufTPMSmgr.c" for "extern" definition for including in other subfunctions
 * ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
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

/* double include prevention */
#ifndef _FILLING_DETECTION_H
#define _FILLING_DETECTION_H

//#define as_16BitP4Average

/************************************************************************************************************
 *                                             include
 ************************************************************************************************************/
#include "Platform_Types.h"


/************************************************************************************************************
 *                                             macro
 ************************************************************************************************************/

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


/************************************************************************************************************
 *                               prototype (external functions - interface) mgr , wnh
 ************************************************************************************************************/
extern void PUTushFDtimeout(uint16); /*mgr*/
extern uint16 GETushFDtimeout(void); /*mgr*/
extern void DECushFDtimeout(void); /*mgr*/

extern void PUTucFDtimerStop(uint8); /*mgr*/
extern uint16 GETucFDtimerStop(void); /*mgr*/

extern uint8 GETucMinWarnThresholdOfRam(void); /*Anzeige Diagnose: CRS_1211_130_268 NEU relativer Druck 150 kpa =150  ALT: RAM Ablage: 100 (100*25=2500=2,5bar*/

extern sint8 KweightCalculation(sint8, sint8); /*wnh*/

extern void ClearAllReCnt4FD(void); /*mgr*/
extern uint8 GetOneReCnt4FD(void); /*mgr*/

void PUTucTimer4MsgDispRq(uint8 x); /*mgr*/
uint8 GETucTimer4MsgDispRq(void); /*mgr*/


extern void PUTushSupervisoryTimerFD(uint16); /*mgr*/
extern uint16 GETushSupervisoryTimerFD(void); /*mgr*/

extern void PUTucOnceCheckMissingRE4FD(uint8); /*mgr*/
extern uint8 GETucOnceCheckMissingRE4FD(void); /*mgr*/

extern uint8 ucCheckCurrentPminWarn(void); /*mgr*/
extern void PUTucNoCheckPmin4StopFD(uint8); /* mgr CRS_1211_130_325*/
extern uint8 GETucNoCheckPmin4StopFD(void); /* mgr CRS_1211_130_325*/
extern void ClearKplNoCheckPmin4StopFD(void); /*mgr CRS_1211_130_330*/

extern uint16 GETushFDtimeout(void); /*mgr*/
extern uint8 GETucRErecCounter4FDVL(void); /*mgr CRS_1211_130_335*/
extern uint8 GETucRErecCounter4FDVR(void); /*mgr CRS_1211_130_335*/
extern uint8 GETucRErecCounter4FDHL(void); /*mgr CRS_1211_130_335*/
extern uint8 GETucRErecCounter4FDHR(void); /*mgr CRS_1211_130_335*/



extern void ReplayLastREvalue2Walgo(void); /*mgr*/

extern void PUTulLastCalMileage(uint32 x); /*mgr*/
extern uint32 GETulLastCalMileage(void); /*mgr*/
extern uint8 GETucPcalMinVaRelativCodOfRam(void); /* mgr CRS_1211_130_268*/
extern uint8 GETucPcalMinHaRelativCodOfRam(void); /* mgr CRS_1211_130_268*/

extern void PUTucPosComparePressure(uint8 , uint8); /*mgr*/
extern uint8 GETucPosComparePressure(uint8 ); /*mgr*/

extern uint8 GETucAutoFillDetectionOnOffOfRam(void); /*mgr*/
extern uint32 GETulKmStand4AutoCAL(void); /*mgr*/
extern uint8 ucCheckLOW_PRESS_ReState(void); /*mgr*/

extern uint8 ucCheckAllRePcalMinDPmanualMFD(void); /*mgr*/

extern uint8 ChkNewIdColX4FD( void ); /* FD CRS_1211_130_373*/

extern void PUTucRErecCounter4FDVL( uint8 ); /*mgr*/
extern void PUTucRErecCounter4FDVR( uint8 ); /*mgr*/
extern void PUTucRErecCounter4FDHL( uint8 ); /*mgr*/
extern void PUTucRErecCounter4FDHR( uint8 ); /*mgr*/

extern void INCucRErecCounter4FDVL( void ); /*mgr*/
extern void INCucRErecCounter4FDVR( void ); /*mgr*/
extern void INCucRErecCounter4FDHL( void ); /*mgr*/
extern void INCucRErecCounter4FDHR( void ); /*mgr*/



/************************************************************************************************************
 *                                             include
 ************************************************************************************************************/

#endif