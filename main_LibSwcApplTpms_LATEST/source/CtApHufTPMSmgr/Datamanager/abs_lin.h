/************************************************************************************************************
 * (c) HuF Electronics GmbH      Abteilung ENTS4     2015
 ************************************************************************************************************/
/*********************************************************************************************************//**
 * \file abs_lin.h
 * \brief ABS Data management
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
#ifndef _abs_lin_H /* [0] */
#define _abs_lin_H



/************************************************************************************************************
 *                                             include
 ************************************************************************************************************/
#include "tss_stdx.h"         /* TSS specific defines                                                       */
#include "Compiler_Cfg.h"
/************************************************************************************************************
 *                                             macro
 ************************************************************************************************************/
#define cABS_DEBUG_MODE                       0x00 // OFF

#define cABS_STATE_INIT						            ((uint8) 0x00)
#define ccABS_STATE_LinABS_AVL                ((uint8) 0x01)
#define ccABS_STATE_LinABS_ERR                ((uint8) 0x02)

#define cDEBUG_ERROR_NO_ERROR                 ((uint8) 0x00)
#define cDEBUG_ERROR_OVERFLOW_ABSTIMEDIFF     ((uint8) 0x01)
#define cDEBUG_ERROR_OVERFLOW_ABSCNTVL        ((uint8) 0x02)
#define cDEBUG_ERROR_OVERFLOW_ABSCNTVR        ((uint8) 0x04)
#define cDEBUG_ERROR_OVERFLOW_ABSCNTHL        ((uint8) 0x08)
#define cDEBUG_ERROR_OVERFLOW_ABSCNTHR        ((uint8) 0x10)

#define PAL
# define cTimeOverflowValue 0xFFFFU



#ifdef PAL
#define cPalTimingRange 1260   //!< 1260 ms
#ifndef ABS_SIG_PERIODICITY
#define cAbsSignalPeriodicity 20  //!< expected peridicity of ABS signals
#else
#define cAbsSignalPeriodicity ABS_SIG_PERIODICITY
#endif
#define cAbsBufferSize cPalTimingRange/cAbsSignalPeriodicity
#else
#define cAbsBufferSize 2
#endif
/************************************************************************************************************
 *                                            typedef
 ************************************************************************************************************/
//! Structure ABS Buffer
typedef struct typedef_struct_tABS_DATA
{
  uint16 ushAbsTimeStamp; //!< Zeitmarke ABS-Signal
  uint16 ushAbsCntVl;     //!< Impulszähler (ABS-Signal) für Rad vorne links
  uint16 ushAbsCntVr;     //!< Impulszähler (ABS-Signal) für Rad vorne rechts
  uint16 ushAbsCntHl;     //!< Impulszähler (ABS-Signal) für Rad hinten links
  uint16 ushAbsCntHr;     //!< Impulszähler (ABS-Signal) für Rad hinten rechts
  uint8 ucOverflowCntVl;
  uint8 ucOverflowCntVr;
  uint8 ucOverflowCntHl;
  uint8 ucOverflowCntHr;
} tABS_DATA;



/************************************************************************************************************
 *                                    data (Modulglobal) - ROM
 ************************************************************************************************************/



/************************************************************************************************************
 *                                    data (Modulglobal) - RAM
 ************************************************************************************************************/
static uint8 ucAbsState;							//!< wird für Zustandssteuerung benötigt
static tABS_DATA tAbsDataBuff[cAbsBufferSize];		//!< Global Abs Buffer
static uint16 ushLinAbsData [4];					//!< Linearisierte ABS Zähler
static uint8 ucAbsIndex;							//!< index inside the buffer
static uint16 ushAbsStickDiff200msOffset;
static uint16 ushAbsStickPrevStop;
static uint16 ushCumAbsStickDiffOffset;

static  uint8 ucPreviousOverflowCntVl;
static  uint8 ucPreviousOverflowCntVr;
static  uint8 ucPreviousOverflowCntHl;
static  uint8 ucPreviousOverflowCntHr;

static  uint8 ucCurrentOverflowCntVl;
static  uint8 ucCurrentOverflowCntVr;
static  uint8 ucCurrentOverflowCntHl;
static  uint8 ucCurrentOverflowCntHr;
/************************************************************************************************************
 *                                       data (global) - ROM
 ************************************************************************************************************/



/************************************************************************************************************
 *                                       data (global) - RAM
 ************************************************************************************************************/
#if (cABS_DEBUG_MODE)    /* for debugging only */
  uint16 ushDebugAbsTimeDiff     = 0; //!< Zeitlicher Abstand zwischen 1. und 2. ABS-Botschaft

  uint16 ushDebugRfTimeStamp     = 0; //!< Zeitstempel des aktuellen RF-Telegramms
  uint16 ushDebugRfTimeStampDiff = 0; //!< Zeitlicher Abstand zwischen letztem und aktuellem RF-Telegramm

  uint16 ushDebugAbs2RfTimeDiff  = 0; //!< Zeitlicher Abstand zwischen 1. ABS-Botschaft und aktuellem RF-Telegramm

  uint16 ushDebugAbsCntVlDiff    = 0; //!< Anzahl der Raddrehimpulse des ABS-Sensors vorne links zwischen 1. und 2. ABS-Botschaft
  uint16 ushDebugAbsCntVrDiff    = 0; //!< Anzahl der Raddrehimpulse des ABS-Sensors vorne rechts zwischen 1. und 2. ABS-Botschaft
  uint16 ushDebugAbsCntHlDiff    = 0; //!< Anzahl der Raddrehimpulse des ABS-Sensors hinten links zwischen 1. und 2. ABS-Botschaft
  uint16 ushDebugAbsCntHrDiff    = 0; //!< Anzahl der Raddrehimpulse des ABS-Sensors hinten rechts zwischen 1. und 2. ABS-Botschaft

  uint16 ushDebugDivisor         = 0; //!< Teiler für Linearisierung

  uint16 ushDebugAbsCntVlLin     = 0; //!< Linearisierte Raddrehimpulse des ABS-Sensors vorne links
  uint16 ushDebugAbsCntVrLin     = 0; //!< Linearisierte Raddrehimpulse des ABS-Sensors vorne rechts
  uint16 ushDebugAbsCntHlLin     = 0; //!< Linearisierte Raddrehimpulse des ABS-Sensors hinten links
  uint16 ushDebugAbsCntHrLin     = 0; //!< Linearisierte Raddrehimpulse des ABS-Sensors hinten rechts

  uint8  ucDebugError            = 0; //!< Fehlervariable
#endif



/***********************************************************************************************************
 *                                 prototype (local functions - private)
 ***********************************************************************************************************/

/***********************************************************************************************************
 *                                 prototype (local functions - public)
 ***********************************************************************************************************/
  uint8 LinABS( uint16 ushRfTimeStamp);


/************************************************************************************************************
 *                               prototype (external functions - interface)
 ************************************************************************************************************/



#endif /* #ifndef _abs_lin_H [0] */
