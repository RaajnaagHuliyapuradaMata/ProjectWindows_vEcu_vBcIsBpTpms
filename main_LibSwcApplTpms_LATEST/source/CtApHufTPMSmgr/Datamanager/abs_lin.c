

#include "abs_lin.h"
#include "abs_linX.h"
#include "wallocX.h"

static uint16 ushCalcABS( uint16, uint16, uint16, uint16, uint16 );
static uint8 getDivRemainder(uint8 input, uint8 factor);

uint8 ucGetAbsOverflowCtrFL(void);
uint8 ucGetAbsOverflowCtrFR(void);
uint8 ucGetAbsOverflowCtrRL(void);
uint8 ucGetAbsOverflowCtrRR(void);

void PutABS(uint16 ushTime, const uint16 ushCnt[] )
{
   uint8 ucAbsIndexPrev;
   uint8 ucTempDiff;
   uint8 ucAbsIndex200msOffset;
   uint16 ushTempdiff = 0xFFFF;
   if (ucAbsState == cABS_STATE_INIT){

      tAbsDataBuff[ucAbsIndex].ushAbsTimeStamp = ushTime;

      tAbsDataBuff[ucAbsIndex].ushAbsCntVl = ushCnt[0];
      tAbsDataBuff[ucAbsIndex].ushAbsCntVr = ushCnt[1];
      tAbsDataBuff[ucAbsIndex].ushAbsCntHl = ushCnt[2];
      tAbsDataBuff[ucAbsIndex].ushAbsCntHr = ushCnt[3];

      ucAbsState = ccABS_STATE_LinABS_ERR;
   }
   else{

      if(ucAbsIndex == 0)
         ucAbsIndexPrev = cAbsBufferSize - 1;
      else
         ucAbsIndexPrev = ucAbsIndex-1;

      ucAbsIndex = getDivRemainder(ucAbsIndex, cAbsBufferSize);

      tAbsDataBuff[ucAbsIndex].ushAbsTimeStamp = ushTime;

      if (ushCnt[0] < tAbsDataBuff[ucAbsIndexPrev].ushAbsCntVl)
      {
          ucCurrentOverflowCntVl++;
      }

      tAbsDataBuff[ucAbsIndex].ucOverflowCntVl  = ucCurrentOverflowCntVl;
      tAbsDataBuff[ucAbsIndex].ushAbsCntVl = ushCnt[0];

      if (ushCnt[1] < tAbsDataBuff[ucAbsIndexPrev].ushAbsCntVr)
      {
          ucCurrentOverflowCntVr++;
      }
      tAbsDataBuff[ucAbsIndex].ucOverflowCntVr = ucCurrentOverflowCntVr;
      tAbsDataBuff[ucAbsIndex].ushAbsCntVr = ushCnt[1];

      if (ushCnt[2] < tAbsDataBuff[ucAbsIndexPrev].ushAbsCntHl)
      {
          ucCurrentOverflowCntHl++;
      }
      tAbsDataBuff[ucAbsIndex].ucOverflowCntHl = ucCurrentOverflowCntHl;
      tAbsDataBuff[ucAbsIndex].ushAbsCntHl = ushCnt[2];

      if (ushCnt[3] < tAbsDataBuff[ucAbsIndexPrev].ushAbsCntHr)
      {
          ucCurrentOverflowCntHr++;
      }
      tAbsDataBuff[ucAbsIndex].ucOverflowCntHr  = ucCurrentOverflowCntHr;
      tAbsDataBuff[ucAbsIndex].ushAbsCntHr = ushCnt[3];

   }

   ucTempDiff = (uint8) (200/cAbsSignalPeriodicity);
    ucAbsIndex200msOffset = (ucAbsIndex >= ucTempDiff) ? (ucAbsIndex - ucTempDiff) : (cAbsBufferSize - ucTempDiff + ucAbsIndex);

   ushTempdiff = (tAbsDataBuff[ucAbsIndex].ucOverflowCntVl>=tAbsDataBuff[ucAbsIndex200msOffset].ucOverflowCntVl) ?
      (tAbsDataBuff[ucAbsIndex].ucOverflowCntVl-tAbsDataBuff[ucAbsIndex200msOffset].ucOverflowCntVl):
      (0xFF + tAbsDataBuff[ucAbsIndex].ucOverflowCntVl - tAbsDataBuff[ucAbsIndex200msOffset].ucOverflowCntVl +1);

   ushAbsStickDiff200msOffset = (tAbsDataBuff[ucAbsIndex].ushAbsCntVl >= tAbsDataBuff[ucAbsIndex200msOffset].ushAbsCntVl) ? (tAbsDataBuff[ucAbsIndex].ushAbsCntVl - tAbsDataBuff[ucAbsIndex200msOffset].ushAbsCntVl) : (cAbsOverflowValue + tAbsDataBuff[ucAbsIndex].ushAbsCntVl - tAbsDataBuff[ucAbsIndex200msOffset].ushAbsCntVl);
   ushAbsStickDiff200msOffset = (uint16) (ushAbsStickDiff200msOffset + ushTempdiff*cAbsOverflowValue);

   if (ushAbsStickPrevStop != 0xFFFF){

      ushTempdiff = (tAbsDataBuff[ucAbsIndex].ushAbsCntVl >= ushAbsStickPrevStop)? (tAbsDataBuff[ucAbsIndex].ushAbsCntVl - ushAbsStickPrevStop):
            (cAbsOverflowValue + tAbsDataBuff[ucAbsIndex].ushAbsCntVl - ushAbsStickPrevStop);

      if(ushTempdiff > 8*20/cAbsSignalPeriodicity){
         ushCumAbsStickDiffOffset = 8*20/cAbsSignalPeriodicity;
         ushAbsStickPrevStop = 0xFFFF;
      }
   }

   if(ushAbsStickDiff200msOffset == 0)
   {
      if(ushAbsStickPrevStop != 0xFFFF)
       {
         ushTempdiff = (tAbsDataBuff[ucAbsIndex].ushAbsCntVl >= ushAbsStickPrevStop)? (tAbsDataBuff[ucAbsIndex].ushAbsCntVl - ushAbsStickPrevStop):
            (cAbsOverflowValue + tAbsDataBuff[ucAbsIndex].ushAbsCntVl - ushAbsStickPrevStop);
         ushAbsStickPrevStop = tAbsDataBuff[ucAbsIndex].ushAbsCntVl;

         ushCumAbsStickDiffOffset += ushTempdiff;
      }
      else{

         ushAbsStickPrevStop = tAbsDataBuff[ucAbsIndex].ushAbsCntVl;
      }
   }

   ucAbsIndex++;
}

uint8 GetLinABS( uint16 ushCnt[] )
{
   uint8 ucRet;

   if( ucAbsState == ccABS_STATE_LinABS_AVL)
   {
    ushCnt[0] = ushLinAbsData[0];
    ushCnt[1] = ushLinAbsData[1];
    ushCnt[2] = ushLinAbsData[2];
    ushCnt[3] = ushLinAbsData[3];

    ucRet = cABS_OK;
  }else{
    ushCnt[0] = cAbsOverflowValue;
    ushCnt[1] = cAbsOverflowValue;
    ushCnt[2] = cAbsOverflowValue;
    ushCnt[3] = cAbsOverflowValue;
    ucRet = cABS_ERROR;
  }

  return ucRet;
}

void InitABS( void )
{
  uint8 ucLoop;

  for ( ucLoop = 0; ucLoop < cAbsBufferSize; ucLoop++ )
  {
    tAbsDataBuff[ucLoop].ushAbsTimeStamp = (uint16) 0;

    tAbsDataBuff[ucLoop].ushAbsCntVl = (uint16) 0;
    tAbsDataBuff[ucLoop].ushAbsCntVr = (uint16) 0;
    tAbsDataBuff[ucLoop].ushAbsCntHl = (uint16) 0;
    tAbsDataBuff[ucLoop].ushAbsCntHr = (uint16) 0;
   tAbsDataBuff[ucLoop].ucOverflowCntVl = (uint8) 0;
    tAbsDataBuff[ucLoop].ucOverflowCntVr = (uint8) 0;
    tAbsDataBuff[ucLoop].ucOverflowCntHl = (uint8) 0;
    tAbsDataBuff[ucLoop].ucOverflowCntHr = (uint8) 0;
  }

  ucPreviousOverflowCntVl = 0;
  ucPreviousOverflowCntVr = 0;
  ucPreviousOverflowCntHl = 0;
  ucPreviousOverflowCntHr = 0;

  ucCurrentOverflowCntVl = 0;
  ucCurrentOverflowCntVr = 0;
  ucCurrentOverflowCntHl = 0;
  ucCurrentOverflowCntHr = 0;

  ucAbsState = cABS_STATE_INIT;
  ucAbsIndex = 0;
  ushAbsStickDiff200msOffset = 0;
  ushAbsStickPrevStop = 0xFFFF;
  ushCumAbsStickDiffOffset = 0;
}

uint8 bCarAbsStickStandstill()

{
   if (ushAbsStickDiff200msOffset < 1)
      return 1;

   else
      return 0;

}

uint8 bResetAbsRefPoint()

{
   if (ushCumAbsStickDiffOffset < (8*20/cAbsSignalPeriodicity))
   {
      return 0;
   }
   else
   {
       ushCumAbsStickDiffOffset = 0;
      ushAbsStickPrevStop = 0xFFFF;
      return 1;
   }

}

uint8 LinABS( uint16 ushRfTimeStamp)
{
  uint8 ucRet;

  uint8 ucABSIndex1, ucABSIndex2, ucLoop;
#if 0
   uint16 ushAbs2RfTimeDiff, ushAbsTimeDiff;
#endif
  uint16 ushAbsCntVlDiff, ushAbsCntVrDiff, ushAbsCntHlDiff, ushAbsCntHrDiff;
  uint8  ucDebugError;

  uint8 ucOverflowOffset, ucTempOverflowCntIdx,  i;
   ucRet= 0;
  ucDebugError = 0;
  ucABSIndex1 = 0xFF;
  for (ucLoop = 0; ucLoop < cAbsBufferSize; ucLoop++){
     if (tAbsDataBuff[ucLoop].ushAbsTimeStamp < ushRfTimeStamp) {

        if (ucABSIndex1 == 0xFF)
           ucABSIndex1 = ucLoop;
        else{
         if (tAbsDataBuff[ucLoop].ushAbsTimeStamp > tAbsDataBuff[ucABSIndex1].ushAbsTimeStamp)
            ucABSIndex1 = ucLoop;
        }
     }
  }

  if(ucABSIndex1!=0xFF)
  {

     if(ucABSIndex1 == cAbsBufferSize-1)
        ucABSIndex2 = 0;
     else
        ucABSIndex2 = ucABSIndex1+1;

#if 0
     if( tAbsDataBuff[ucABSIndex1].ushAbsTimeStamp > ushRfTimeStamp )
      {

         ushAbs2RfTimeDiff = (cTimeOverflowValue - tAbsDataBuff[ucABSIndex1].ushAbsTimeStamp) + ushRfTimeStamp;
      }else{
         ushAbs2RfTimeDiff = ushRfTimeStamp - tAbsDataBuff[ucABSIndex1].ushAbsTimeStamp;
      }
#endif

#if 0
       if( tAbsDataBuff[ucABSIndex1].ushAbsTimeStamp > tAbsDataBuff[ucABSIndex2].ushAbsTimeStamp )
      {

         ushAbsTimeDiff = (cTimeOverflowValue - tAbsDataBuff[ucABSIndex1].ushAbsTimeStamp) + tAbsDataBuff[ucABSIndex2].ushAbsTimeStamp;
      }else{
         ushAbsTimeDiff = tAbsDataBuff[ucABSIndex2].ushAbsTimeStamp - tAbsDataBuff[ucABSIndex1].ushAbsTimeStamp;
      }
#endif

      if( tAbsDataBuff[ucABSIndex1].ushAbsCntVl > tAbsDataBuff[ucABSIndex2].ushAbsCntVl )
      {

         ushAbsCntVlDiff = (cAbsOverflowValue - tAbsDataBuff[ucABSIndex1].ushAbsCntVl) + tAbsDataBuff[ucABSIndex2].ushAbsCntVl;
      }else{
         ushAbsCntVlDiff = tAbsDataBuff[ucABSIndex2].ushAbsCntVl - tAbsDataBuff[ucABSIndex1].ushAbsCntVl;
      }

      if( (ushAbsCntVlDiff > 600) || (tAbsDataBuff[ucABSIndex1].ushAbsCntVl == cAbsOverflowValue) || (tAbsDataBuff[ucABSIndex2].ushAbsCntVl == cAbsOverflowValue))
      {

         ucDebugError |= cDEBUG_ERROR_OVERFLOW_ABSCNTVL;
         ucAbsState = ccABS_STATE_LinABS_ERR;
         return cABS_ERROR;
      }

      if( tAbsDataBuff[ucABSIndex1].ushAbsCntVr > tAbsDataBuff[ucABSIndex2].ushAbsCntVr )
      {

         ushAbsCntVrDiff = (cAbsOverflowValue - tAbsDataBuff[ucABSIndex1].ushAbsCntVr) + tAbsDataBuff[ucABSIndex2].ushAbsCntVr;
      }else{
         ushAbsCntVrDiff = tAbsDataBuff[ucABSIndex2].ushAbsCntVr - tAbsDataBuff[ucABSIndex1].ushAbsCntVr;
      }

      if( (ushAbsCntVrDiff > 600) || (tAbsDataBuff[ucABSIndex1].ushAbsCntVr == cAbsOverflowValue) || (tAbsDataBuff[ucABSIndex2].ushAbsCntVr == cAbsOverflowValue) )
      {

         ucDebugError |= cDEBUG_ERROR_OVERFLOW_ABSCNTVR;
         ucAbsState = ccABS_STATE_LinABS_ERR;
         return cABS_ERROR;
      }

      if( tAbsDataBuff[ucABSIndex1].ushAbsCntHl > tAbsDataBuff[ucABSIndex2].ushAbsCntHl )
      {

         ushAbsCntHlDiff = (cAbsOverflowValue - tAbsDataBuff[ucABSIndex1].ushAbsCntHl) + tAbsDataBuff[ucABSIndex2].ushAbsCntHl;
      }else{
         ushAbsCntHlDiff = tAbsDataBuff[ucABSIndex2].ushAbsCntHl - tAbsDataBuff[ucABSIndex1].ushAbsCntHl;
      }

      if( (ushAbsCntHlDiff > 600) || (tAbsDataBuff[ucABSIndex1].ushAbsCntHl == cAbsOverflowValue) || (tAbsDataBuff[ucABSIndex2].ushAbsCntHl == cAbsOverflowValue) )
      {

         ucDebugError |= cDEBUG_ERROR_OVERFLOW_ABSCNTHL;
         ucAbsState = ccABS_STATE_LinABS_ERR;
         return cABS_ERROR;
      }

      if( tAbsDataBuff[ucABSIndex1].ushAbsCntHr > tAbsDataBuff[ucABSIndex2].ushAbsCntHr )
      {

         ushAbsCntHrDiff = (cAbsOverflowValue - tAbsDataBuff[ucABSIndex1].ushAbsCntHr) + tAbsDataBuff[ucABSIndex2].ushAbsCntHr;
      }else{
         ushAbsCntHrDiff = tAbsDataBuff[ucABSIndex2].ushAbsCntHr - tAbsDataBuff[ucABSIndex1].ushAbsCntHr;
      }

      if( (ushAbsCntHrDiff > 600) || (tAbsDataBuff[ucABSIndex1].ushAbsCntHr == cAbsOverflowValue) || (tAbsDataBuff[ucABSIndex2].ushAbsCntHr == cAbsOverflowValue) )
      {

         ucDebugError |= cDEBUG_ERROR_OVERFLOW_ABSCNTHR;
         ucAbsState = ccABS_STATE_LinABS_ERR;
         return cABS_ERROR;
      }

      ushLinAbsData[0] = tAbsDataBuff[ucABSIndex1].ushAbsCntVl + ushCalcABS( ushRfTimeStamp, tAbsDataBuff[ucABSIndex1].ushAbsTimeStamp, tAbsDataBuff[ucABSIndex1].ushAbsCntVl, tAbsDataBuff[ucABSIndex2].ushAbsTimeStamp, tAbsDataBuff[ucABSIndex2].ushAbsCntVl );
      ushLinAbsData[1] = tAbsDataBuff[ucABSIndex1].ushAbsCntVr + ushCalcABS( ushRfTimeStamp, tAbsDataBuff[ucABSIndex1].ushAbsTimeStamp, tAbsDataBuff[ucABSIndex1].ushAbsCntVr, tAbsDataBuff[ucABSIndex2].ushAbsTimeStamp, tAbsDataBuff[ucABSIndex2].ushAbsCntVr );
      ushLinAbsData[2] = tAbsDataBuff[ucABSIndex1].ushAbsCntHl + ushCalcABS( ushRfTimeStamp, tAbsDataBuff[ucABSIndex1].ushAbsTimeStamp, tAbsDataBuff[ucABSIndex1].ushAbsCntHl, tAbsDataBuff[ucABSIndex2].ushAbsTimeStamp, tAbsDataBuff[ucABSIndex2].ushAbsCntHl );
      ushLinAbsData[3] = tAbsDataBuff[ucABSIndex1].ushAbsCntHr + ushCalcABS( ushRfTimeStamp, tAbsDataBuff[ucABSIndex1].ushAbsTimeStamp, tAbsDataBuff[ucABSIndex1].ushAbsCntHr, tAbsDataBuff[ucABSIndex2].ushAbsTimeStamp, tAbsDataBuff[ucABSIndex2].ushAbsCntHr );
#if ABS_SIG_SIZE_ONEBYTE
      ushLinAbsData[0] = (uint8) ushLinAbsData[0];
      ushLinAbsData[1] = (uint8) ushLinAbsData[1];
      ushLinAbsData[2] = (uint8) ushLinAbsData[2];
      ushLinAbsData[3] = (uint8) ushLinAbsData[3];
#endif

      if (ushLinAbsData[0] < tAbsDataBuff[ucABSIndex1].ushAbsCntVl)
         ucTempOverflowCntIdx = ucABSIndex2;
      else
         ucTempOverflowCntIdx = ucABSIndex1;
      ucOverflowOffset = (tAbsDataBuff[ucTempOverflowCntIdx].ucOverflowCntVl >= ucPreviousOverflowCntVl ) ? tAbsDataBuff[ucTempOverflowCntIdx].ucOverflowCntVl - ucPreviousOverflowCntVl: 0xFF - ucPreviousOverflowCntVl + tAbsDataBuff[ucTempOverflowCntIdx].ucOverflowCntVl + 1;
      for (i=0; i<ucOverflowOffset; i++){
         RebuildABSRef(0);
      }
      ucPreviousOverflowCntVl = tAbsDataBuff[ucTempOverflowCntIdx].ucOverflowCntVl;

      if (ushLinAbsData[1] < tAbsDataBuff[ucABSIndex1].ushAbsCntVr)
         ucTempOverflowCntIdx = ucABSIndex2;
      else
         ucTempOverflowCntIdx = ucABSIndex1;
      ucOverflowOffset = (tAbsDataBuff[ucTempOverflowCntIdx].ucOverflowCntVr >= ucPreviousOverflowCntVr ) ? tAbsDataBuff[ucTempOverflowCntIdx].ucOverflowCntVr - ucPreviousOverflowCntVr: 0xFF - ucPreviousOverflowCntVr + tAbsDataBuff[ucTempOverflowCntIdx].ucOverflowCntVr + 1;
      for (i=0; i<ucOverflowOffset; i++){
         RebuildABSRef(1);
      }
      ucPreviousOverflowCntVr = tAbsDataBuff[ucTempOverflowCntIdx].ucOverflowCntVr;

      if (ushLinAbsData[2] < tAbsDataBuff[ucABSIndex1].ushAbsCntHl)
         ucTempOverflowCntIdx = ucABSIndex2;
      else
         ucTempOverflowCntIdx = ucABSIndex1;
      ucOverflowOffset = (tAbsDataBuff[ucTempOverflowCntIdx].ucOverflowCntHl >= ucPreviousOverflowCntHl ) ? tAbsDataBuff[ucTempOverflowCntIdx].ucOverflowCntHl - ucPreviousOverflowCntHl: 0xFF - ucPreviousOverflowCntHl + tAbsDataBuff[ucTempOverflowCntIdx].ucOverflowCntHl + 1;
      for (i=0; i<ucOverflowOffset; i++){
         RebuildABSRef(2);
      }
      ucPreviousOverflowCntHl = tAbsDataBuff[ucTempOverflowCntIdx].ucOverflowCntHl;

      if (ushLinAbsData[3] < tAbsDataBuff[ucABSIndex1].ushAbsCntHr)
         ucTempOverflowCntIdx = ucABSIndex2;
      else
         ucTempOverflowCntIdx = ucABSIndex1;
      ucOverflowOffset = (tAbsDataBuff[ucTempOverflowCntIdx].ucOverflowCntHr >= ucPreviousOverflowCntHr ) ? tAbsDataBuff[ucTempOverflowCntIdx].ucOverflowCntHr - ucPreviousOverflowCntHr: 0xFF - ucPreviousOverflowCntHr + tAbsDataBuff[ucTempOverflowCntIdx].ucOverflowCntHr + 1;
      for (i=0; i<ucOverflowOffset; i++){
         RebuildABSRef(3);
      }
      ucPreviousOverflowCntHr = tAbsDataBuff[ucTempOverflowCntIdx].ucOverflowCntHr;

      ucRet = cABS_OK;
      ucAbsState = ccABS_STATE_LinABS_AVL;

   }else{
         ucRet = cABS_ERROR;
         ucAbsState = ccABS_STATE_LinABS_ERR;
   }

   return ucRet;
}

static uint16 ushCalcABS( uint16 ushRfTimeStamp, uint16 ush1stAbsTimeStamp, uint16 ush1stAbsCnt,
                                                 uint16 ush2ndAbsTimeStamp, uint16 ush2ndAbsCnt )
{
  uint16 ushAbs2RfTimeDiff;
  uint16 ushAbsTimeDiff;
  uint16 ushAbsCntDiff;
  uint16 ushDiv;

  if( ush1stAbsTimeStamp > ushRfTimeStamp )
  {

    ushAbs2RfTimeDiff = (cTimeOverflowValue - ush1stAbsTimeStamp) + ushRfTimeStamp;
  }else{
    ushAbs2RfTimeDiff = ushRfTimeStamp - ush1stAbsTimeStamp;
  }

  if( ush1stAbsTimeStamp > ush2ndAbsTimeStamp )
  {

    ushAbsTimeDiff = (cTimeOverflowValue - ush1stAbsTimeStamp) + ush2ndAbsTimeStamp;
  }else{
    ushAbsTimeDiff = ush2ndAbsTimeStamp - ush1stAbsTimeStamp;
  }

  if( ush1stAbsCnt > ush2ndAbsCnt )
  {

    ushAbsCntDiff = (cAbsOverflowValue - ush1stAbsCnt) + ush2ndAbsCnt;
  }else{
    ushAbsCntDiff = ush2ndAbsCnt - ush1stAbsCnt;
  }

  if (ushAbs2RfTimeDiff == 0)
     return 0;

  ushDiv = ((((ushAbsTimeDiff * 100) / ushAbs2RfTimeDiff) + 5) / 10);

  if (ushDiv == 0)
     return 0;
  else
   return ((((ushAbsCntDiff * 100) / ushDiv) + 5) / 10);
}

static uint8 getDivRemainder(uint8 input, uint8 factor){
    if (factor > 0)
   {
      return (uint8) (input%factor);
   }
   else
      return 0;
}

uint8 ucGetAbsOverflowCtrFL(void)
{

  return ucCurrentOverflowCntVl;

}

uint8 ucGetAbsOverflowCtrFR(void)
{

  return ucCurrentOverflowCntVr;

}

uint8 ucGetAbsOverflowCtrRL(void)
{

  return ucCurrentOverflowCntHl;

}

uint8 ucGetAbsOverflowCtrRR(void)
{

  return ucCurrentOverflowCntHr;

}
