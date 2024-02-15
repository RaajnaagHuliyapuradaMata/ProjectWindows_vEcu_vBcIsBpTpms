/************************************************************************************************************
 * (c) HuF Electronics GmbH      Abteilung ENTS4     2015
 ************************************************************************************************************/
/*********************************************************************************************************//**
 * \file internal_clock.h
 * \brief Manage internal clock and timers
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
#ifndef _INTERNAL_CLOCK_X_H
# define _INTERNAL_CLOCK_X_H



/************************************************************************************************************
 *                                             include
 ************************************************************************************************************/
#include "Platform_Types.h"
#include "Compiler_Cfg.h"

/************************************************************************************************************
 *                                             macro
 ************************************************************************************************************/
#define cT_STANBY               (uint16) 1140//s 19 min ECU stanby time after ignition off

#define cT_STANBY4AFD           (uint16) 60//s 1 min ECU parking+stanby time for auto filling detection
#define c_100km                 (uint32) 100/* 1000 == 100km 4 first Acalibration startWITHOUT Mcalibartion*/
#define c_50km                  (uint32) 50 /*  after 50km 4 first Acalibration start WITHOUT Mcalibartion*/
#define c_0km				            (uint32) 0 /*  first Acalibration start WITHOUT Mcalibartion*/
#define c_FFFFkm                (uint32) 0xFFFFFFFF /*  default and start value for "brandneues" TPMS AG WITHOUT Mcalibartion*/
#define c_FF9Bkm                (uint32) 0xFFFFFF9B /*  default and start value for "brandneues" TPMS AG WITHOUT Mcalibartion*/

#define OP_TIME_METHOD_OHDS 0x01U // OHDS
#define OP_TIME_METHOD_CSTDELAY 0x00U //Constant delay

#define PAL_TEL_CST_DELAY_TIME 0x05U //ms
//#define c_AFDfirstStart					(uint8) 1  // first auto filling detection start within first 100km drive
//#define c_AFDsecondStart				(uint8) 2  // after first filling detection start and parking time  
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
void InternTimersInit(void);

void IncrInternMsTimer(void);

void GetInternMSTime(uint32* ulInternalTime);

void UpdateStanbyTimer(boolean bIgnState, uint16 ushVSpeed, uint8 ucVmin);

void ResetStanbyTimer(void);

boolean bStanbyTimerElapsed(void);

void SkipStanbyTimer(void);

uint8 ucGetCurrentECUParkingState(void);

uint16 ushGetCurrentECUStanbyTime(void);

void UpdateParkingTimer(uint16 ushVSpeed);

uint16 ushGetCurrentECUParkingTime(void);

uint16 ushGetCurrentECUKl15OffParkingTime(void);

uint8 ucGetCurrentECUAfdStartState(void);

void GetSystemOperatingTime(uint32* ulOpTime);
uint8 GetOpTimeMehodTarget(void);
uint8 GetPalAbsConstantDelay(void);
uint8  GetOpTimeMethodCurrent(void);
void SetOpTimeMethodTarget(uint8 ucTimeMethod, uint8 ucCstDelay);
void SetPalAbsTimeInfoSNA(void);
/************************************************************************************************************
 *                               prototype (external functions - interface)
 ************************************************************************************************************/

/************************************************************************************************************
 *                                             include
 ************************************************************************************************************/




#endif