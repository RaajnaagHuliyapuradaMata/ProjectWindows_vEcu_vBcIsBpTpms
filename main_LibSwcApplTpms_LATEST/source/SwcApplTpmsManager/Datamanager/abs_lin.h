

#ifndef _abs_lin_H
#define _abs_lin_H

#include "tss_stdx.h"
#include "Compiler_Cfg.h"

#define cABS_DEBUG_MODE                       0x00

#define cABS_STATE_INIT                              ((uint8) 0x00)
#define ccABS_STATE_LinABS_AVL                ((uint8) 0x01)
#define ccABS_STATE_LinABS_ERR                ((uint8) 0x02)

#define cDEBUG_ERROR_NO_ERROR                 ((uint8) 0x00)
#define cDEBUG_ERROR_OVERFLOW_ABSTIMEDIFF     ((uint8) 0x01)
#define cDEBUG_ERROR_OVERFLOW_ABSCNTVL        ((uint8) 0x02)
#define cDEBUG_ERROR_OVERFLOW_ABSCNTVR        ((uint8) 0x04)
#define cDEBUG_ERROR_OVERFLOW_ABSCNTHL        ((uint8) 0x08)
#define cDEBUG_ERROR_OVERFLOW_ABSCNTHR        ((uint8) 0x10)

#define PAL
#define cTimeOverflowValue 0xFFFFU

#ifdef PAL
#define cPalTimingRange 1260
#ifndef ABS_SIG_PERIODICITY
#define cAbsSignalPeriodicity 20
#else
#define cAbsSignalPeriodicity ABS_SIG_PERIODICITY
#endif
#define cAbsBufferSize cPalTimingRange/cAbsSignalPeriodicity
#else
#define cAbsBufferSize 2
#endif
 typedef struct typedef_struct_tABS_DATA
{
  uint16 ushAbsTimeStamp;
   uint16 ushAbsCntVl;
   uint16 ushAbsCntVr;
   uint16 ushAbsCntHl;
   uint16 ushAbsCntHr;
   uint8 ucOverflowCntVl;
  uint8 ucOverflowCntVr;
  uint8 ucOverflowCntHl;
  uint8 ucOverflowCntHr;
}tABS_DATA;

static uint8 ucAbsState;
 static tABS_DATA tAbsDataBuff[cAbsBufferSize];
 static uint16 ushLinAbsData [4];
 static uint8 ucAbsIndex;
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

#if(cABS_DEBUG_MODE)
  uint16 ushDebugAbsTimeDiff     = 0;

  uint16 ushDebugRfTimeStamp     = 0;
   uint16 ushDebugRfTimeStampDiff = 0;

  uint16 ushDebugAbs2RfTimeDiff  = 0;

  uint16 ushDebugAbsCntVlDiff    = 0;
   uint16 ushDebugAbsCntVrDiff    = 0;
   uint16 ushDebugAbsCntHlDiff    = 0;
   uint16 ushDebugAbsCntHrDiff    = 0;

  uint16 ushDebugDivisor         = 0;

  uint16 ushDebugAbsCntVlLin     = 0;
   uint16 ushDebugAbsCntVrLin     = 0;
   uint16 ushDebugAbsCntHlLin     = 0;
   uint16 ushDebugAbsCntHrLin     = 0;

  uint8  ucDebugError            = 0;
#endif

  uint8 LinABS( uint16 ushRfTimeStamp);
#endif
