

#define WALLOC_INT
 #include "WallocX.h"
#include "Walloc_IF.h"
#include "walloc.h"
#include "AEC.h"
#include "FPA.h"
#include "tss_stdX.h"
#define cSLHistAssignTimeInSec 180
 #define cTIME_OUT            540
 #define cHistIDProtectTime  240
 #define c5MinDriveTimeInSec 300

#define cAll (uint8) 0
#define cLearnOnly (uint8) 1

static unsigned short ushIDSetInHist(unsigned long *ptHistSet, unsigned char ucMinProbeCt,
                                     unsigned char ucSlots2Search);
static unsigned short ushIDinLearnModeSetInHist(unsigned long *ptHistSet, unsigned char ucMinProbeCt,
                                                unsigned char ucSlots2Search);

static unsigned short ushSpeciaLearn(tRFTelType * ptInputWA);
static unsigned char ucAssessDAGSLUC(unsigned char ucWPs);
static unsigned char ucNewZomIDsFit2MissingHistID_WP(unsigned char ucNewNMissing);
static unsigned char ucGetNrOfNewIDs(unsigned char * p2Slots);
static unsigned char ucWrZom2History(unsigned char ucNewNMissing);

static unsigned char ucSL3MinHistPreFinish(void);
static unsigned char ucSL31Finish(unsigned char ucMinCt4NewID);
static unsigned char ucGetNrOfNewIDsInLM_SL(unsigned short * p2Slots, unsigned char ucMinCt);
static unsigned char ucGetNrOfNewIDsInLM(unsigned short * p2Slots, unsigned char ucMinCt);
static unsigned char ucGetNrOfNewIDsInLMwoPAL(unsigned short * p2Slots);

static unsigned char uc3NewIDsAllocated(unsigned char ucMinCt4NewID);
static unsigned short ushCompLearn(tRFTelType * ptInputWA);
static unsigned short ushWhlSetRdy2Freeze(unsigned char ucMinCt, unsigned char ucMinCt4HistERc, unsigned char bLearnNewIDsFlag);
static unsigned char ucForceAutoLocate(void);
static unsigned char ucCmpHist2ZOMID(unsigned char ucVZS);
static unsigned char ucNrOfUKWPinZOM(void);
static unsigned char ucNrOfUKWPinHist(void);

static void CheckAutoDeactivateOverride(void);
static unsigned char ucFinishViaHistory(void);
static unsigned char ucBadHist2Def(void);

static unsigned char ucFinalFreeze(unsigned char ucMinCt4HistER, unsigned char ucMinCt);

static void UpdateALState(uint8 ui8Trigger);
static unsigned short ucFindNoLearnHistoryIDs(unsigned long *ptHistID, unsigned char ucMinProbeCt, unsigned char ucSlots2Search);
static unsigned short ucFindMissingHistoryIDs(unsigned long *ptHistID, unsigned char ucMinProbeCt, unsigned char ucSlots2Search);
static unsigned char ucGetMisOrNoLearnError(void);
static unsigned char ucGetAnyLocatErrors(unsigned char ucDontTouch);
static void ClearAlLearNLocatError(unsigned char ucErrType);

static void TOXpired(void);
static void UpdateDAGLearnState(void);

static unsigned char ucTakeOverHistWP(unsigned char ucHistIx,unsigned char ucZomIx);
static unsigned short ushIDSetInHistNAlignWP(unsigned long *ptHistSet, unsigned char ucMinProbeCt, unsigned char ucSlots2Search);
static unsigned short ushSetHistIDs2ER(unsigned long *ptHistSet, unsigned char ucMinProbeCt, unsigned char ucSlots2Search);

static unsigned short ushLearnInOver8(tRFTelType * ptInputWA);

static unsigned char ucPasSupplFilter(tRFTelType * p2Tel);

static void MergeWPandPWP(void);

static unsigned char ucNrOfLocatError(void);
static unsigned char ucNrOfLocatErrorAndPosForce(void);
static unsigned char ucNrOfLearnError(void);

static uint8 considerationeDiAssegnazioneCostretto(void);
static void dblCk4LocEr(void);
static uint16 ui16NewIdFits(uint16 ushNewID, uint16 ushHistSet);
static uint8 ui8AnyHistIdMissing(void);

static unsigned short  ushLqiTribute(unsigned short ushCandidate);

static const unsigned char ucWACtrlFixc = 0x01;
static const unsigned char ucWACtrlBreakc = 0x02;

static unsigned char ucWAState;

static unsigned long aulHistoryID[cMaxLR];
static unsigned char aucHistoryWP[cMaxLR];
static unsigned char ucLearnError[cMaxLR] = {NoError,NoError,NoError,NoError};
static unsigned char ucLocatError[cMaxLR] = {NoError,NoError,NoError,NoError};
static unsigned char ucABSignalMissin = NoError ;

#define cWPER 0x10

static unsigned short ushDriveTimeInSec = 0;
static unsigned short ushDriveTimeOverPalMax = 0;
static unsigned char ucLearnMode = cNoLearn;
static unsigned char ucWAStateHi = 0;

static unsigned char ucDAGLearnState = Autolearn_Learning ;

static unsigned char aucWPorPWP[cMaxLR] = {4,4,4,4};
  unsigned char ucNrOfBitSet(unsigned short ushTarget)
{
  unsigned char i, ucHits= 0;

  for (i = 0; i < 16; i ++)
  {
    if ((ushTarget & (1<<i)) > 0)
    {
      ucHits++;
    }
  }
  return (ucHits);
}
static void SetWAStateZOChange(unsigned char ucChangedPos)
{
  ucWAState &= 0x0F;
  ucWAState |= (unsigned char) ((ucChangedPos&0x0F)<<4);

  ucWAStateHi &= 0x0F;
  ucWAStateHi |= (unsigned char) (ucChangedPos&0xF0);
 }
static void ClearZOM(unsigned char ucIx)
{
  unsigned char i,j;

  if (ucIx > cSumWE)
  {
    /* ERROR */
  }
  else
  {
    if (ucIx == (unsigned char) cSumWE)
    {
      for (i = 0; i < ucIx; i++)
      {
        for (j = 0; j < (unsigned char) sizeof(struct ZOMSlot);j++)
        {
          *((unsigned char *) &tZOM[i] + j) = 0;
        }
      }
    }
    else
    {
      for (j = 0; j < (unsigned char) sizeof(struct ZOMSlot);j++)
      {
        *((unsigned char *) &tZOM[ucIx] + j) = 0;
      }
    }
    /* PutbER(0); */
    /* PutbZO(0); */
  }
}
static unsigned char ucSetWP(void)
{
  unsigned char i, ucRet = 1; /* no error by default */
  for (i = 0; i < cMaxLR; i++)
  {
    tZOM[i].ucStatus &= cNoWPos;
    switch (tZOM[i].ucStatus)
    {
    case 0x50: /* 01010000: */
      tZOM[i].ucStatus |= cWP_FR;
      break;
    case 0x60: /* 0b01100000: */
      tZOM[i].ucStatus |= cWP_RR;
      break;
    case 0x90: /* 0b10010000: */
      tZOM[i].ucStatus |= cWP_FL;
      break;
    case 0xA0:  /* b10100000: */
      tZOM[i].ucStatus |= cWP_RL;
      break;
    default:
      {
        /* ERROR */
        ucRet = 0;
        break; /* exit loop immediately */
      }
    }
  }
  return(ucRet);
}
static void ResetWP(void)
{
  unsigned char i;

  for(i = 0; i < cMaxLR; i++)
  {
    tZOM[i].ucStatus &= cNoWPos;
  }
}

static void PutulZOMID(unsigned char ucIx,unsigned long *p2ID)
{
  if (ucIx < cSumWE)
  {
    tZOM[ucIx].ulID = *p2ID;
  }
}
static unsigned char ucGetZOMWP(unsigned char ucIx)
{
  if (ucIx < cSumWE)
  {
    switch (tZOM[ucIx].ucStatus & ~cNoWPos)
    {
    case 0x01:
      return ( (unsigned char) 0);
    case 0x02:
      return ( (unsigned char) 1);
    case 0x04:
      return ( (unsigned char) 2);
    case 0x08:
      return ( (unsigned char) 3);
    default:
      return ( (unsigned char) 4);  /* ERROR invalid WP */
    }
  }
  else
  {
    return ( (unsigned char) 4);  /* ERROR invalid index */
  }
}
static void ResetAxis(void)
{
  unsigned char i;
  for (i = 0; i < cSumWE; i++)
  {
    tZOM[i].ucStatus &= cNoAxis;
#ifdef CONCEPT4
    tZOM[i].ushLECt = 0;
    tZOM[i].ushSECt = 0;
    tZOM[i].ucFCt = 0;
#endif
  }
  ucWAState &= (unsigned char) ~(cWAStateER);
}
static unsigned char ucGetProbeCt(unsigned char ucIx)
{
  if (ucIx < cSumWE)
  {
    return (tZOM[ucIx].ucProbeCt);
  }
  else
  {
    return ( (unsigned char) 0);
  }
}
static unsigned char ucGetFreeZOMPos(void)
{
  unsigned char i;
  for (i = 0; i < cSumWE; i++)
  {
    if (tZOM[i].ulID == (unsigned long) 0)
    {
      break;
    }
  }
  return(i);
}

 static unsigned char ucStartWA(void)
{
  unsigned char i, ucRet = 0;

  for (i = 0; i < cSumWE; i++)
  {
    if (tZOM[i].ucProbeCt  > 0)
    {
      ucRet++;
    }
  }
  ucRet  =  (ucRet > (unsigned char) 0) ? (unsigned char) 1:(unsigned char) 0;
  return(ucRet);
}
/************************************************************************************************
                                                                                                   * \brief Set Zom entries 0-3 (first 4 positions) with learned Wheel sensors
                                                                                                  *
                                                                                                  *-----------------------------------------------------------------------------------------------
                                                                                                  * \param [in] ushERSlot Bitmap containing learned Wheel sensors
                                                                                                  * \param [inout] tZOM Global ZOM structure
                                                                                                  *
                                                                                                  * \return none
                                                                                                  *
                                                                                                  *------------------------------------------------------------------------------------------------
                                                                                                  */
unsigned short ushAlignZOM(unsigned short ushERSlot)
{
  unsigned char i, j, k, ucCt = 0;
  struct ZOMSlot tempZom; /*   */

  for (i = 0; i < cSumWE; i++)
  {
    if ((((unsigned short ) (1<<i)) & ushERSlot) > 0) /* is this an ER slot ? */
    {
      ucCt++;
    }
    else  /* no ER */
    {
      for (j = i+1; j < cSumWE; j++)  /* find next ER */
      {
        if ((((unsigned short ) (1<<j)) & ushERSlot) > 0)  /* ER ? */
        {
          ucCt++;
          for (k = 0; k < (unsigned char) sizeof(struct ZOMSlot); k++)  /* copy ER slot to current slot */
          {
            /* perform Zom entries permutation                   */
            *(((unsigned char *) &tempZom) + k) = *(((unsigned char *) &tZOM[i]) + k) ;
            *(((unsigned char *) &tZOM[i]) + k) = *(((unsigned char *) &tZOM[j]) + k);
            *(((unsigned char *) &tZOM[j]) + k) = *(((unsigned char *) &tempZom) + k);
          }
          ushERSlot |= (1<<i);  /* slot i is now ER */
          ushERSlot &= ~(1<<j); /*  but j is ER not any longer */
#ifdef AEC
          ResetACM();
#endif
          break;
        }
      }
    }
    if (ucCt == cMaxLR)
    {
      break;
    }
  }
  return (ushERSlot);
}

static unsigned char ucLowestProbe(unsigned short ushException)
{
  unsigned char i, ucMinIx = cSumWE;

  for( i = 0; i < cSumWE; i++)
   {
    if (((0x01<<i) & ushException) == 0)
     {
      ucMinIx = i;
      break;
     }
  }
  for( i = (ucMinIx + 1); i < cSumWE; i++)
  {
    if (((0x01<<i) & ushException) == 0)
     {
      if (tZOM[i].ucTelCtLearnBit < tZOM[ucMinIx ].ucTelCtLearnBit)
      {
        ucMinIx = i;
      }
    }
  }
  return( ucMinIx );
}

/************************************************************************************************
                                                                                                   * \brief  checks whether a specific wheel position is already set in the history
                                                                                                  *
                                                                                                  *-----------------------------------------------------------------------------------------------
                                                                                                  * \param [in] p2HistoryWP pointr to  array containing wheel position
                                                                                                  * \param [in] ucWP wheel position of interest
                                                                                                  *
                                                                                                  * \return   - 1  True
                                                                                                  **         - 0  False
                                                                                                  *
                                                                                                  *------------------------------------------------------------------------------------------------
                                                                                                  */
static unsigned char bWPExistInHist(unsigned char *p2HistoryWP, unsigned char ucWP)
{

  unsigned char i;
  unsigned char ucRetVal = 0;

  for (i=0; i<cMaxLR; i++){
    if(p2HistoryWP[i] == ucWP){
      ucRetVal= 1;
      break;
    }
  }
  return ucRetVal;
}
/************************************************************************************************
                                                                                                   * \brief  checks whether all prelearned IDs have been received at least once
                                                                                                  *
                                                                                                  *-----------------------------------------------------------------------------------------------
                                                                                                  * \param [in] none
                                                                                                  * \param [out] none
                                                                                                  *
                                                                                                  * \return   - 1  True
                                                                                                  **         - 0  False
                                                                                                  *
                                                                                                  *------------------------------------------------------------------------------------------------
                                                                                                  */
unsigned char bCheckHistIDReception(void){
  unsigned short ushHelp;

  ushHelp = ushIDSetInHist(aulHistoryID, 1, cSumWE);

  if ((cMaxLR == ucNrOfBitSet(ushHelp)) && ((ucGetHistoryState()&cHiStateZG) == cHiStateZG)) /* complete "history ER set" found ? */
    return 1;
  else
    return 0;

}

/************************************************************************************************
                                                                                                   * \brief  checks ID set to ERstate based on amount of receive events
                                                                                                  *
                                                                                                  *-----------------------------------------------------------------------------------------------
                                                                                                  * \param [in] ucMinCt minimum number of events
                                                                                                  * \param [in] aulHistoryID  Global static array containing Wheel IDs
                                                                                                  *
                                                                                                  * \return   - 1  means set of IDs is in ERstate
                                                                                                  **         - 0  no ERState reached up to now
                                                                                                  *
                                                                                                  *------------------------------------------------------------------------------------------------
                                                                                                  */
static unsigned short ushCheckERState(unsigned char ucMinCt, unsigned char ucMinCt4HistERc, unsigned char bLearnNewIDsFlag)
{
  unsigned short ushRet = 0;
  const unsigned char ucMinCt4ERResetc = 6;  /* <TSS_basis311_TSS_G3 SW_30769> */

  ushRet = ushIDinLearnModeSetInHist(aulHistoryID,ucMinCt4HistERc,cSumWE); /* try to find history ID set in ZOM */
  if (ucNrOfBitSet(ushRet) < cMaxLR)   /* history ID set not in ZOM ? */
  {
    if (bLearnNewIDsFlag == 1) /* New ID set can be learned ?*/
    {
      if (ucSumCtID(ucMinCt4ERResetc, &ushRet) > ((unsigned char) cMaxLR)) /* heavy multiburst attack ? */
      {
        ClearZOM(cSumWE); /* restart ER detection */
#ifdef AEC
        ResetACM();
#endif
        ushRet = 0;
      }
      else  /* perform conventional ER check */
      {
        if (ucSumCtID(ucMinCt, &ushRet) != cMaxLR)  /* NEW ER set of 4 ? */
        {
          ushRet = 0; /* no ER state */
        }
      }
    }
    else{
      ushRet = 0; /* no ER state */
    }
  }
  return(ushRet);
}

/************************************************************************************************
                                                                                                   * \brief  identifies wheel position based on turning direction and axis position
                                                                                                  *
                                                                                                  *-----------------------------------------------------------------------------------------------
                                                                                                  * \param [in] *ptInputWA pointer to telegramm buffer
                                                                                                  * \param [in] ucID Sensor position in ZOM
                                                                                                  *
                                                                                                  * \return   1 means wheel positions identified
                                                                                                  *          0  wheel positions still unknown
                                                                                                  *
                                                                                                  *------------------------------------------------------------------------------------------------
                                                                                                  */
static unsigned char ucCheckWheelPos(unsigned char ucID, tRFTelType * ptInputWA)
{
  unsigned char ucRet = 0;  /* wheel positions not found by default */
  unsigned short ushTmp = 0x000F;
#ifdef AEC
  if ( ptInputWA->Header .ucTType == cTelTypePeak )
    Concept5pb8(ucID, ptInputWA);
  else
#endif
 #ifdef FPA
   if ((ucWAStateHi & cTO) > (unsigned char) 0)
   {
    if (ucAdjABSIface(ucID, ptInputWA) > (unsigned char) 0)
       BuildCmpVal (ucID);
   }
   else
    ucRet = ucConceptFixPos0(ucID, ptInputWA);

  if ((unsigned char) 0 == ucRet)
    if ((unsigned char) cMaxLR == ucFPDecPossible (&ushTmp, cMinCt4Dec ))
      if ((unsigned char) 0 == ucNrOfUKWPinZOM() )
        ucRet = (unsigned char) 1;
#endif
 #ifdef AEC
  if  (ucDirectionDetection((unsigned char) 1) == 0x0F)   /* all wheel sensor's spinning direction detected ? */
  {
 #ifdef CONCEPT4
    if (((tZOM[ucID].ucStatus & 0x30) == 0) && (ptInputWA->Header .ucTType == cTelTypeEdgeCnt))
      Concept4Op2(ucID,ushGetTruECt(ptInputWA,ucID) );
#endif
    if (ucAxisDetection() == 1)
    {
      if (ucWPConsistent() == 1)
      {

        if (ucSetWP() == 1)
        {
          ucRet = 1;
        }
        else
        {

          ResetAxis();
        }
      }
      else
      {
        ResetAxis();
      }
    }
  }
  else
  {
    if (ucRet == 0)
       ResetWP();
  }
#endif
  return((unsigned char) ucRet);
}

static unsigned short ushIDSetInHist(unsigned long *ptHistSet, unsigned char ucMinProbeCt,
                                     unsigned char ucSlots2Search)
{
  unsigned char i,j;
  unsigned short ushRet = 0;

  for ( i = 0; i < cMaxLR; i++)
  {
    if (ptHistSet[i] == (unsigned long) 0)
    {
      ushRet = 0;
      break;
    }
    else
    {
      for( j = 0; j < ucSlots2Search; j++)
      {
        if ((ptHistSet[i] == ulGetZOMID(j)) && (ucGetProbeCt(j) >= ucMinProbeCt ))
        {
          ushRet |= (1<<j);
          break;
        }
        else
        {
          if (ulGetZOMID(j) == (unsigned long) 0)
          {
            break;
          }
        }
      }
    }
  }
  return (ushRet);
}

static unsigned short ushIDinLearnModeSetInHist(unsigned long *ptHistSet, unsigned char ucMinProbeCt,
                                                unsigned char ucSlots2Search)
{
  unsigned char i,j;
  unsigned short ushRet = 0;

  for ( i = 0; i < cMaxLR; i++)
  {
    if (ptHistSet[i] == (unsigned long) 0)
    {
      ushRet = 0;
      break;
    }
    else
    {
      for( j = 0; j < ucSlots2Search; j++)
      {
        if ((ptHistSet[i] == ulGetZOMID(j)) && (ucGetZomTelCtLearnBit(j) >= ucMinProbeCt ))
        {
          tZOM[j].ucStatus |= cZOMStatHistER;
          ushRet |= (1<<j);
          break;
        }
        else
        {
          if (ulGetZOMID(j) == (unsigned long) 0)
          {
            break;
          }
        }
      }
    }
  }
  return (ushRet);
}

static void Put2Slot(tRFTelType *ptInputWA, unsigned char ucIx)
{
  unsigned char ucSpin = (unsigned char) 0;

  if (ucIx < cSumWE)
  {
    tZOM[ucIx].ulID = ptInputWA->EdgeCnt.ulID;

    if ( (tZOM[ucIx].ucProbeCt < (unsigned char) 255) &&
       ((tZOM[ucIx].ushRssiSum + (unsigned short) ptInputWA->Struc .ucAvg) >= tZOM[ucIx].ushRssiSum) )
    {
      tZOM[ucIx].ushRssiSum += (unsigned short) ptInputWA->Struc .ucAvg;
      tZOM[ucIx].ucProbeCt++;
    }

    if( (cTelTypeSELPAL1== ptInputWA->Header.ucTType) || ( cTelTypeAK35defLMA == ptInputWA->Header.ucTType))
    {
      tZOM[ucIx].ucTelCtLearnBit++;
    }

    if ( (cTelTypeSELPAL  == (ptInputWA->Header.ucTType&0x0F)) )
     {
      /* update the frame counter of PAL telegramm */
      tZOM[ucIx].ucFrameCounter = (unsigned char)((ptInputWA->SchraderFP.ushStatusField>>8)&0x1F);

      if (ptInputWA->SchraderFP.ucPAL == 0x0){
 #ifdef Test_LOG_ENABLE
        tZOM[ucIx].ucToothTelCtNoLearnMode++;
 #endif
      }
      else if (ptInputWA->SchraderFP.ucPAL == 0x01){
 #ifdef Test_LOG_ENABLE
        tZOM[ucIx].ucToothTelCtNoCorr++;
 #endif
      }
      else if (ptInputWA->SchraderFP.ucPAL == 0xFF){
 #ifdef Test_LOG_ENABLE
        tZOM[ucIx].ucToothTelCtNoCorr++;
 #endif
      }
      else{
#ifdef Test_LOG_ENABLE
        if ((ptInputWA->Header .ucTType & 0x20) == 0x20)
           tZOM[ucIx].ucToothTelCtCorrLearnBit++;
        else
          tZOM[ucIx].ucToothTelCtCorrNoLearnBit++;
#endif
      }
    }
    else if (cTelTypePeak == ptInputWA->Header.ucTType)
     {
#ifdef AEC
      tZOM[ucIx].ushXPSum++;
#endif
#ifdef Test_LOG_ENABLE
                tZOM[ucIx].ucToothTelCtNoLearnMode++;
 #endif
    }
    else if (cTelTypeAK35def == ptInputWA->Header.ucTType)
     {
#ifdef Test_LOG_ENABLE
      tZOM[ucIx].ucToothTelCtNoLearnMode++;
 #endif
    }
    else if ( cTelTypeEdgeCnt == ptInputWA->Header.ucTType )
     {
       ucSpin = ptInputWA->EdgeCnt.ucSpin;
#ifdef CONCEPT4
      /* start time recognition */
      if (tZOM[ucIx].ushStarTi == 0)  /* 1st access */
      { /* YES */
        tZOM[ucIx].ushStarTi = ptInputWA->Struc.ushTimeStamp; /* start time is this */
        tZOM[ucIx].ushLogTime = ptInputWA->Struc.ushTimeStamp;
        tZOM[ucIx].ucStarTiHi = (unsigned char) 0;
       }
      else
      {
         if (ptInputWA->Struc.ushTimeStamp < tZOM[ucIx].ushLogTime)
          tZOM[ucIx].ucStarTiHi +=1;
        tZOM[ucIx].ushLogTime = ptInputWA->Struc.ushTimeStamp;
      }
#endif
#ifdef Test_LOG_ENABLE
                tZOM[ucIx].ucToothTelCtNoLearnMode++;
 #endif
    }
    else if(cTelTypeAK35BeruMed == ptInputWA->Header.ucTType)
     {
      ucSpin = ptInputWA->AK35BeruMed .ucSpinDir;
#ifdef AEC
      if ( ucEarlyEnd(ucIx) > 0 )
        StartWATO( 1 );
 #endif
#ifdef Test_LOG_ENABLE
                tZOM[ucIx].ucToothTelCtNoLearnMode++;
 #endif
    }
    else if(cTelTypeAK35BeruL == ptInputWA->Header.ucTType)
     {
      ucSpin = ptInputWA->AK35BeruL  .ucSpinDir;
#ifdef Test_LOG_ENABLE
                tZOM[ucIx].ucToothTelCtNoLearnMode++;
 #endif
    }
    else if(cTelTypeAK35BeruS  == ptInputWA->Header.ucTType)
     {
      ucSpin = ptInputWA->AK35BeruS  .ucSpinDir;
#ifdef Test_LOG_ENABLE
          tZOM[ucIx].ucToothTelCtNoLearnMode++;
 #endif
        }else
        {
#ifdef Test_LOG_ENABLE
           tZOM[ucIx].ucToothTelCtNoLearnMode++;
 #endif
    }

    if( (ucSpin > 0) &&
      (tZOM[ucIx].ucLeftCt  < (unsigned char) 255) &&
      (tZOM[ucIx].ucRightCt < (unsigned char) 255)    )
    {
      if ( (ucSpin & cIDStateSpinLeft) == cIDStateSpinLeft) /* left spinning ? */
      {
        tZOM[ucIx].ucLeftCt++;
      }

      if ( (ucSpin & cIDStateSpinRight) == cIDStateSpinRight) /* right spinning ? */
      {
        tZOM[ucIx].ucRightCt++;
      }
    }
  }
  else
  {
    /* index ERROR */
  }
  return;
}

/************************************************************************************************
                                                                                                   * \brief  collects ID data essential for WA in dependence of WE status
                                                                                                  *
                                                                                                  *-----------------------------------------------------------------------------------------------
                                                                                                  * \param [in] *ptInputWA pointer to telegramm buffer
                                                                                                  * \param [in] *tWAPar Pointer to global structure containing wheel allocation parameters
                                                                                                  * \param [in] aulHistoryID Global static array containing Wheel IDs
                                                                                                  *
                                                                                                  * \return   - 1 = ZOM data changed
                                                                                                  *          - 0 = ZOM data left untouched
                                                                                                  *
                                                                                                  *------------------------------------------------------------------------------------------------
                                                                                                  */
static unsigned char ucPutInZOM(tRFTelType *ptInputWA, WAParameter *ptWAPar)
{
  unsigned char ucIx;

  ucIx = ucGetZOMPosOfID( &ptInputWA->AK35def.ulID );

  if (ucIx < cSumWE)  /* ID already in ZOM */
  {
    Put2Slot(ptInputWA, ucIx);
  }
  else  /* id not in ZOM */
  {
    ucIx = ucGetFreeZOMPos();
    if ( ucIx < cSumWE )  /* any free slot ? */
    {
      Put2Slot(ptInputWA, ucIx);
    }
    else /* ZOM overcrowded */
    {
      if (ucGetERState() == 0)  /* ER state not yet reached ? */
      {
        ucIx = ucLowestProbe(ushIDSetInHist(aulHistoryID,(unsigned char) 1,cSumWE));
        if (ucIx < cSumWE) /* is there a lowest probe id ? */
        {
          ClearZOM(ucIx);  /* delete old id */
#ifdef AEC
          ResetACM();
#endif
          Put2Slot(ptInputWA, ucIx);  /* insert new one */
        }
        else /* no lowest probe found */
        {
          ucIx = cSumWE;
        }
      }
      else /* already in ER state */
      {
        ucIx = cSumWE;
      }
    }
  }
  return(ucIx);
 }

        unsigned char ucSetHistory(unsigned char ucType, unsigned char ucVZS)
{
  unsigned char i,j,ucNrUK,ucNew,ucRet = 0x0f, ucChangedHistSlots = 0; /* no position has been changed by default , all ids have been changed (low nibble bits indicate !ZOM slots! w/ new IDs)*/

  GetWADataEE(cHistorySet1, (unsigned char *) aulHistoryID, (unsigned char) sizeof(aulHistoryID) );
  GetWADataEE(cHistoryWPSet1, aucHistoryWP, (unsigned char) sizeof(aucHistoryWP) );

  ucNew = ucCmpHist2ZOMID(ucVZS);
  ucNrUK = ucNrOfUKWPinZOM();

  if ( (((unsigned char) 0) == ucNrOfBitSet ((unsigned short) ucNew) ) && (ucNrUK > ucNrOfUKWPinHist ()) && !((((uint8) 1) ==  ucNrUK) && (ui8AnyHistIdMissing () == ((uint8) 0)))  )
     ucType = cWAStateER;

  for (i = 0; i < cMaxLR; i++)  /* detect changes of wheel positions */
  {
    for (j = 0; j < cMaxLR; j++)
    {
      if (( aulHistoryID[i] == ulGetZOMID(j) ) && (((ucVZS & (unsigned char) (1<<j)) > 0))) /* history id also in ZOM ? */
      {
        ucRet &= (unsigned char) (~(unsigned char) (0x01 << j));  /* this ZOM ID was already in history */
        if (ucType == cWAStateZO)
        {
          if ((ucGetZOMWP(j) != aucHistoryWP[i]) && (ucGetZOMWP(j) < 4))  /* change position ? */
          {
            ucNrUK = ucGetColOfWP(ucGetZOMWP(j));
            if ( cMaxLR > ucNrUK )
             {
              aucHistoryWP[ucNrUK] = 4;
              ucRet |= (unsigned char) (0x10 << ucNrUK); /* wheel position changed */
            }
            aucHistoryWP[i] = ucGetZOMWP(j);
            ucRet |= (unsigned char) (0x10 << i); /* wheel position changed */
          }
        }
        break;
      }
    }
  }

  ucRet = ucRet & (0xF0|ucVZS);

  if (1 < ucNrOfBitSet((unsigned short) (ucRet & 0x0F)))
   {
    if ( ucWACtrlFixc == tWAPar.ucWACtrl )
     {
      tWAPar.ucWACtrl = ucDefWACtrl;
      ucWAState &= (unsigned char) ~(cWAStateZO);
      PutWADataEE(cWAParameter, (unsigned char *) &tWAPar , (unsigned char) sizeof(WAParameter));
    }
  }

  if (ucRet > 0)
  {
    for (i = 0; i < cMaxLR; i++)
    {
      if ((ucRet & (0x01 << i)) > 0)
      {
        ucNrUK = ucGetColOfWP(ucGetZOMWP(i));
        if ((ucGetZOMWP(i) <= cWheelPos_RR  )  && ((ucNew & ((1<<ucNrUK)&0x0F)) > 0))
          {
          aulHistoryID[ucNrUK] = ulGetZOMID(i);
          ucNew &= (unsigned char) (~(unsigned char) (1 << ucNrUK));
          ucChangedHistSlots |= (unsigned char) (1 << ucNrUK);
        }
        else
        {
          for ( j = 0; j < cMaxLR; j++)
          {
            if ((ucNew & ((unsigned char) (1 << j))) > 0)
            {
              aulHistoryID[j] = ulGetZOMID(i);
              ucNew &= (unsigned char) (~(unsigned char) (1 << j));
              ucChangedHistSlots |= (unsigned char) (1 << j);
              if ((0 < ucNrOfBitSet((unsigned short) (ucRet & 0x0F)))||(ucNrOfUKWPinHist() > 0))
               {
                  aucHistoryWP[j] = 4;
                  ucRet |= (unsigned char) (0x10 << j); /* new wheel position at this history ID */
              }
              if (cWAStateZO == ucType)
              {
                if ((ucGetZOMWP(i) <= cWheelPos_RR ) && (aucHistoryWP[j] != ucGetZOMWP(i)))  /* change position ? */
                {
                  if ( cMaxLR > ucNrUK )
                   {
                    aucHistoryWP[ucNrUK] = 4;
                    ucRet |= (unsigned char) (0x10 << ucNrUK); /* wheel position changed */
                  }
                  aucHistoryWP[j] = ucGetZOMWP(i);
                  ucRet |= (unsigned char) (0x10 << j); /* wheel position changed */
                }
              }
              break;
            }
          }
        }
      }
    }

    if ((cMaxLR == ucNrOfBitSet ((unsigned short) ucVZS )) || ((unsigned char) 2 > ucNrOfUKWPinHist ()))
      ucRet |= ucForceAutoLocate ();

    PutWADataEE(cHistorySet1, (unsigned char *) aulHistoryID, (unsigned char) sizeof(aulHistoryID));  /* write history to eeprom */
    PutWADataEE(cHistoryWPSet1, aucHistoryWP, (unsigned char) sizeof(aucHistoryWP));
  }

  return ((ucRet&0xF0)|ucChangedHistSlots);
}

/************************************************************************************************
                                                                                                   * \brief  sets the WA state saved in the history to current state in dependency of ER state
                                                                                                  *          WARNING: if ER state is reached the content of the ZOM will be respected
                                                                                                  *
                                                                                                  *-----------------------------------------------------------------------------------------------
                                                                                                  * \param [inout] ucWAState Global static variable containing the WA status
                                                                                                  * \param [in] aulHistoryID Global static array containing Wheel IDs
                                                                                                  * \param [in] aucHistoryWP Global static array containing Wheel positions
                                                                                                  *
                                                                                                  * \return   none
                                                                                                  *
                                                                                                  *------------------------------------------------------------------------------------------------
                                                                                                  */
static void RestoreHistory(void)
{
  unsigned char i,j,ucCt = 0;

  if (aulHistoryID[0] > (unsigned long) 0)  /* history exists ? */
  { /* yes */
    if ( ucGetERState() == 1 )  /* system in ER state ? */
    { /* yes */
      for ( i = 0; i < cMaxLR; i++)   /* takeover historical wheel positions if id set matches */
      {
        for ( j = 0; j < cMaxLR; j++ )
        {
          if ((unsigned char) 0 < ucTakeOverHistWP (j,i))
            ucCt++;
        }
      }
    }
    else
    { /* take over history to ZOM 1:1 , and don't care about anything like spin directions*/
      for ( i = 0; i < cMaxLR; i++)
      {
        PutulZOMID(i,&aulHistoryID[i]);
        if ((unsigned char) 0 < ucTakeOverHistWP (i,i))
            ucCt++;
      }
      ucWAState |= cWAStateER;
    }

    if (ucCt < cMaxLR)
    {
      for ( i = 0; i < cMaxLR; i++)
      {
        SetZOMWP(i, cWPER);
      }
    }
    else
    {
      ucWAState |= cWAStateZO;
    }
  }
}

unsigned char ucGetZOMPosOfID(unsigned long *pt2ID)
{
  unsigned char i;
  for (i = 0; i < cSumWE; i++)
  {
    if (*pt2ID == tZOM[i].ulID)
    {
      break;
    }
  }
  return(i);
}

unsigned char ucGetZOMPalFrameCounter(unsigned char ucIx)
{
  if (ucIx < cSumWE)
  {
    return (tZOM[ucIx].ucFrameCounter);
  }
  else
  {
    return ( (unsigned char) 0);
  }
}

void SetZOMWP(unsigned char ucIx,unsigned char ucWP)
{
  if (ucIx < cSumWE)
  {
    tZOM[ucIx].ucStatus &= cNoWPos;
    if (ucWP < cMaxLR)
    {
      tZOM[ucIx].ucStatus |= (unsigned char) (0x01 << ucWP);
    }
  }
}

unsigned long ulGetZOMID(unsigned char ucIx)
{
  if (ucIx < cSumWE)
  {
    return (tZOM[ucIx].ulID);
  }
  else
  {
    return ( (unsigned long) 0);
  }
}

unsigned long ulGetID(unsigned char ucIx)
{
  if (ucIx < cMaxLR)
  {
    return (aulHistoryID[ucIx]);
  }
  else
  {
    return ( (unsigned char) 0);
  }
}

unsigned char ucGetColOfID(unsigned long *pt2ID)
{
  unsigned char i;
  for (i = 0; i < cMaxLR; i++)
  {
    if (*pt2ID == aulHistoryID[i])
    {
      break;
    }
  }
  return(i);
}

unsigned char ucGetWPOfCol(unsigned char ucIx)
{
  if (ucIx < cMaxLR)
  {
    return (aucHistoryWP[ucIx]);
  }
  else
  {
    return ((unsigned char) 4);
  }
}

unsigned char ucGetColOfWP(unsigned char ucIx)
{
  unsigned char i;

  for( i = 0; i < cMaxLR; i++ )
  {
    if(aucHistoryWP[i] == ucIx)
    {
      break;
    }
  }
  return i;
}

unsigned char * GETpucStartAdrWP(void)
{
  return (aucHistoryWP);
}

unsigned char ucSetID(unsigned long *pt2ID, unsigned char *pt2Pos, unsigned char ucSum)
{
  unsigned char i, j, ucRet = 0, ucHelp;
  unsigned long ulBufID;

  ucSum = (ucSum > cMaxLR) ? cMaxLR:ucSum;

  if (pt2ID[0] == (unsigned long) 0)
  {
    for ( i = 0; i < cMaxLR; i++)
    {
      aulHistoryID[i] = 0;
      aucHistoryWP[i] = 4;
    }
    PutWADataEE(cHistorySet1, (unsigned char *) aulHistoryID, (unsigned char) sizeof(aulHistoryID));
    PutWADataEE(cHistoryWPSet1, aucHistoryWP, (unsigned char) sizeof(aucHistoryWP));
    (void) WAInit((WAParNCfgType *) &ucLearnMode );
    ucRet = 0x0F;
  }
  else
  {
    GetWADataEE(cHistorySet1, (unsigned char *) aulHistoryID, (unsigned char) sizeof(aulHistoryID));
    GetWADataEE(cHistoryWPSet1, aucHistoryWP, (unsigned char) sizeof(aucHistoryWP));
    if ((aulHistoryID[0] == 0) && (ucSum == 1))
    {
      for (i = 0; i < cMaxLR; i++)
      {
        aulHistoryID[i] = i + 1;
        if ( pt2Pos[0] > 3 )
        {
          aucHistoryWP[i] = 4;
        }
        else
        {
          aucHistoryWP[i] = i;
        }
      }
    }

    ucHelp = 0x0f;
    for (i = 0; i < ucSum; i++)
    {
      for (j = 0; j < cMaxLR; j++)
      {
        if (pt2ID[i] == aulHistoryID[j])
        {
          ucHelp &= (unsigned char) (~(unsigned char) (0x01 << j));
          break;
        }
      }
    }

    for (i = 0; i < ucSum; i++)
    {
      for (j = 0; j < cMaxLR; j++)
      {
        if (pt2ID[i] == aulHistoryID[j])
        {
          break;
        }
      }
      pt2Pos[i] = (pt2Pos[i] < (unsigned char) 9) ? pt2Pos[i]:4;
      if (j == cMaxLR)
      {
        if ( pt2Pos[i] > cWheelPos_RR)
        {
          if ( pt2Pos[i] == (unsigned char) 4 )
          {
            ucRet = 0;
            i = ucSum;
          }
          else
          {
            ucHelp = pt2Pos[i] - (unsigned char) 5;
            aulHistoryID[ucHelp] = pt2ID[i];
            aucHistoryWP[ucHelp] = (unsigned char) 4;
            ucRet |= (0x10 << ucHelp);
            ucWAState &= (unsigned char) ~(cWAStateZO);
          }
        }
        else
        {
          for (j = 0; j < cMaxLR; j++)
          {
            if (pt2Pos[i] == aucHistoryWP[j])
            {
              break;
            }
          }
          if ( j == cMaxLR )
          {
            for (j = 0; j < cMaxLR; j++)
            {
              if ((ucHelp & (unsigned char)(0x01 << j)) > 0)
              {
                ucHelp =  (unsigned char) (ucHelp & (unsigned char) ~((unsigned char) (0x01 << j)));

                break;
              }
            }
          }

          ulBufID = aulHistoryID[j];
          aulHistoryID[j] = pt2ID[i];
          aucHistoryWP[j] = pt2Pos[i];

          if ((ucWAState & cWAStateZO) == cWAStateZO)
          {
            ucHelp = ucGetZOMPosOfID(&ulBufID);
            tZOM[ucHelp].ulID = pt2ID[i];
            SetZOMWP(ucHelp, pt2Pos[i]);
            ucRet |= (1 << ucHelp);
          }
          else
          {
            ucRet |= (1 << pt2Pos[i]);
          }
        }
      }
      else
      {
        if (aucHistoryWP[j] == pt2Pos[i])
        {

        }
        else
        {
          if ( pt2Pos[i] > cWheelPos_RR)
          {
            if ( pt2Pos[i] == (unsigned char) 4 )
            {
              ucRet = 0;
              i = ucSum;
            }
            else
            {
              aulHistoryID[j] = (unsigned long) i + 1;
              aucHistoryWP[j] = (unsigned char) 4;
              ucHelp = pt2Pos[i] - (unsigned char) 5;
              aulHistoryID[ucHelp] = pt2ID[i];
              aucHistoryWP[ucHelp] = (unsigned char) 4;
              ucRet |= (0x10 << ucHelp);
              ucWAState &= (unsigned char) ~(cWAStateZO);
            }
          }
          else
          {
            ucHelp = j;
            for (j = 0; j < cMaxLR; j++)
            {
              if (pt2Pos[i] == aucHistoryWP[j])
              {
                aucHistoryWP[j] = aucHistoryWP[ucHelp];
                break;
              }
            }
            aucHistoryWP[ucHelp] = pt2Pos[i];
            if ((ucWAState & cWAStateZO) == cWAStateZO)
            {
              SetZOMWP(j, aucHistoryWP[j]);
              SetZOMWP(ucHelp, pt2Pos[i]);
              ucRet |= (unsigned char) (0x10 << pt2Pos[i]);
              ucRet |= (unsigned char) (0x10 << aucHistoryWP[j]);
            }
            else
            {
              ucRet |= (unsigned char) (1 << pt2Pos[i]);
            }
          }
        }
      }
    }
    if (ucRet > 0)
    {
      PutWADataEE(cHistorySet1, (unsigned char *) aulHistoryID, (unsigned char) sizeof(aulHistoryID));
      PutWADataEE(cHistoryWPSet1, aucHistoryWP, (unsigned char) sizeof(aucHistoryWP));
    }

    if ((ucWAState & cWAStateZO) == 0)
    {
      (void) WAInit((WAParNCfgType *) &ucLearnMode);
      ucRet = 0x0f;
    }
  }
  return (ucRet);
}

unsigned char ucGetHistoryState(void)
{
  unsigned char i, ucRet = 0;
  if (aulHistoryID[0] > (unsigned long) 0)
  {
    ucRet |= (cHiStateER | cHiStateZG);
    for (i = 0; i < cMaxLR; i++)
    {
      if (aucHistoryWP[i] > cWheelPos_RR)
      {
        ucRet &= ~cHiStateZG;
      }
    }
  }
  return (ucRet);
}

unsigned char ucGetERState(void)
{
  return( ((ucWAState & cWAStateER) == cWAStateER) ? (unsigned char) 1:(unsigned char) 0);
}
unsigned char ucSumCtID(unsigned char ucMinCt, unsigned short *ushRet)
{
  unsigned char i, ucCt= 0;
  *ushRet = 0;
  for ( i = 0; i < cSumWE; i++)
  {
    if (ucGetZomTelCtLearnBit(i) >= ucMinCt  )
    {
      ucCt++;
      *ushRet |= (unsigned short) (1 << i);
    }
  }
  return(ucCt);
}

               unsigned short ushLearnID(tRFTelType * ptInputWA)
{
  unsigned short ushRet;
  ucWAStateHi &= 0x0F;
   ucWAState &= 0x0F;
  ushRet = GETushWAState();

  if ((unsigned char) 0 < ucPasSupplFilter(ptInputWA ) )
   {
    if (!(((ucWAState & cWAStateZO) == cWAStateZO) || ((ucWAStateHi & cTO) > (unsigned char) 0)))
    {
      if ((tWAPar.ucWACtrl & ucWACtrlFixc) > 0)
        (void) (ushLearnInOver8(ptInputWA ));
      else if (cCompleteLearn == ucLearnMode)
        (void) (ushCompLearn(ptInputWA ));
      else if (cSpeciaLearn == ucLearnMode )
        (void) (ushSpeciaLearn(ptInputWA));

      ProvideFPAlgo2MT_DAG();
    }
  }

  if ((GETushWAState()) != ushRet)
   {
    if ((ucNrOfUKWPinHist () > 0) && ((ucWAState & 0xF0) > 0))
    {
      UpdateALState (cEvNewIDs);
    }
    if ((ucNrOfUKWPinHist () == 0) && ((ucWAState & cWAStateZO ) > 0) && (((unsigned char) 2) > ucNrOfLocatError()))
     {
         if((ucNrOfLocatErrorAndPosForce() == 0) || (tWAPar.AL_State != cAL_Stored))
         {
            UpdateALState (cEv4WPs);
         }
    }
  }
  ushRet = GETushWAState();

  return(ushRet);
}

unsigned char ucWATO(void)
{
  unsigned char ucRet = (unsigned char) 0;

  if ((ucWAState & cWAStateZO) == 0)
  {
    ucRet = ucGetMisOrNoLearnError ();
    ucRet |= ucGetAnyLocatErrors(ucRet);
  }

  if ( (unsigned char) 0 == ucRet )
    ClearAlLearNLocatError(cAll);

  return (ucRet);
}

unsigned char WAInit(WAParNCfgType * p2ParNCfg)
{
  ucWAState &= (unsigned char) ~(cWAStateZO);
  ucWAState &= (unsigned char) ~(cWAStateER);
  ucWAState &= (unsigned char) ~(cWAStateActive);
  ucWAStateHi = (unsigned char) 0;
  SetWAStateZOChange(0);
  ushDriveTimeInSec = 0;
  ushDriveTimeOverPalMax = 0;
  ucLearnMode = p2ParNCfg ->ucWACfg ;
  ClearAlLearNLocatError(cAll);
  ClearZOM(cSumWE);

  GetWADataEE(cWAParameter, (unsigned char *) &tWAPar , (unsigned char) sizeof(WAParameter));
  GetWADataEE(cHistorySet1, (unsigned char *) aulHistoryID, (unsigned char) sizeof(aulHistoryID));
  GetWADataEE(cHistoryWPSet1, aucHistoryWP, (unsigned char) sizeof(aucHistoryWP));
  if (ucBadHist2Def() > 0)
    PutWADataEE(cHistorySet1, (unsigned char *) aulHistoryID, (unsigned char) sizeof(aulHistoryID));
  if ((cNoLearn == ucLearnMode) && (ucHistInConsist () > 0))
    ucLearnMode = cCompleteLearn ;
  if (cNoLearn == ucLearnMode)
  {
    RestoreHistory();
  }
  tWAPar.ucWACtrl &= ~ucWACtrlBreakc;

     ucDAGLearnState = Autolearn_Learning ;
#ifdef FPA
  Very1stABSTickIinit();
#endif
  WAStatusChangedEvent(GETushWAState() );
  return (ucGetHistoryState());
}

unsigned char ucSetAutolocationOveride(unsigned char ucPalOverideFlag)
{

  unsigned char ucRetVal;

  if (ucPalOverideFlag==1)
  {
    if ((((ucGetHistoryState()&cHiStateZG) == cHiStateZG) == 1) && (cAL_OK == ui8GetALState()))
    {
      ucRetVal=1;
      if (tWAPar.ucWACtrl != ucWACtrlFixc)
      {
        tWAPar.ucWACtrl = ucWACtrlFixc;
        PutWADataEE(cWAParameter, (unsigned char *) &tWAPar , (unsigned char) sizeof(WAParameter));
        ucRetVal=1;
      }
    }
    else{
      ucRetVal=0;
    }
  }
  else if  (ucPalOverideFlag==0)
  {
    ucRetVal=1;
    if (tWAPar.ucWACtrl != ucDefWACtrl)
    {
      tWAPar.ucWACtrl = ucDefWACtrl;
      PutWADataEE(cWAParameter, (unsigned char *) &tWAPar , (unsigned char) sizeof(WAParameter));
    }
  }
  else
   {
    ucRetVal=0;
  }
  return ucRetVal;

}

unsigned char ucReadAutolocationOverideFlag ()
{
  unsigned char ucRetVal;
  if (tWAPar.ucWACtrl == ucWACtrlFixc)
    ucRetVal = 1;
  else
    ucRetVal = 0;

  return ucRetVal;
}

unsigned char ucSet1HistID(unsigned long *pt2ID, unsigned char *pt2Pos, unsigned char ucIdx)
{
  unsigned char i, ucRetVal;

  ucRetVal=0;

  for(i=0; i<cMaxLR; i++)
  {
    if (i == ucIdx)
      continue;

    if ( (pt2ID[0] == 0) || (pt2Pos[0] > cMaxLR ) )
    {
      ucRetVal =0;
      break;
    }

    if ( (pt2ID[0] == aulHistoryID[i]) || ((pt2Pos[0] == aucHistoryWP[i] ) && (pt2Pos[0]!=cMaxLR) ) )
    {
      ucRetVal =0;
      break;
    }
  }
  if (i==cMaxLR)
  {
    aulHistoryID[ucIdx] = pt2ID[0];
    aucHistoryWP[ucIdx] = pt2Pos[0];

    PutWADataEE(cHistorySet1, (unsigned char *) aulHistoryID, (unsigned char) sizeof(aulHistoryID));
    PutWADataEE(cHistoryWPSet1, aucHistoryWP, (unsigned char) sizeof(aucHistoryWP));

    ucLearnMode = cCompleteLearn ;
     (void) WAInitByDiag((WAParNCfgType *) &ucLearnMode );

    ucRetVal = ((unsigned char) 0 == ucNrOfUKWPinHist ()) ? (unsigned char) 4:(unsigned char) 1;
  }

  return ucRetVal;
}

unsigned char ucSet4HistIDs(unsigned long *pt2ID, unsigned char *pt2Pos)
{
  unsigned char i, j, ucRetVal;

  ucRetVal=0;
  j=0;

  for(i=0; i<cMaxLR; i++)
  {

    if ( (pt2ID[i] == 0) || (pt2Pos[i] > cMaxLR ) )
    {
      ucRetVal =0;
      break;
    }

    for(j=0; j<cMaxLR; j++)
    {
      if (i == j)
        continue;
       if ( (pt2ID[i] == pt2ID[j]) || ((pt2Pos[i] == pt2Pos[j] ) && (pt2Pos[i]!=cMaxLR)) )
      {
        ucRetVal =0;
        i=cMaxLR;
        break;
      }
    }
  }

  if (j==cMaxLR)
  {
    for(i=0; i<cMaxLR; i++)
    {
      aulHistoryID[i] = pt2ID[i];
      aucHistoryWP[i] = pt2Pos[i];
    }
    PutWADataEE(cHistorySet1, (unsigned char *) aulHistoryID, (unsigned char) sizeof(aulHistoryID));
    PutWADataEE(cHistoryWPSet1, aucHistoryWP, (unsigned char) sizeof(aucHistoryWP));

     ucLearnMode = cCompleteLearn ;
     (void) WAInitByDiag((WAParNCfgType *) &ucLearnMode );

    ucRetVal = ((unsigned char) 0 == ucNrOfUKWPinHist ()) ? (unsigned char) 4:(unsigned char) 1;
  }

  return ucRetVal;
}
#ifdef Test_LOG_ENABLE

unsigned char ucGetZomStatus(unsigned char  ucIdx)
{
  if (ucIdx < cSumWE)
  {
    return (tZOM[ucIdx].ucStatus);
  }
  else
  {
    return ((unsigned char) cNoWPos);
  }
}

unsigned char ucGetZomToothTelCtCorrLearnBit(unsigned char  ucIdx)
{
  if (ucIdx < cSumWE)
  {
    return (tZOM[ucIdx].ucToothTelCtCorrLearnBit);
  }
  else
  {
    return ((unsigned char) 0);
  }
}

unsigned char ucGetZomTelCtLearnBit(unsigned char ucIdx)
{
  if (ucIdx < cSumWE)
  {
    return (tZOM[ucIdx].ucTelCtLearnBit);
  }
  else
  {
    return ((unsigned char) 0);
  }
}

unsigned char ucGetZomToothTelCtCorrNoLearnBit(unsigned char  ucIdx)
{
  if (ucIdx < cSumWE)
  {
    return (tZOM[ucIdx].ucToothTelCtCorrNoLearnBit);
  }
  else
  {
    return ((unsigned char) 0);
  }
}

unsigned char ucGetZomToothTelCtrNoCorr(unsigned char  ucIdx)
{
  if (ucIdx < cSumWE)
  {
    return (tZOM[ucIdx].ucToothTelCtNoCorr);
  }
  else
  {
    return ((unsigned char) 0);
  }
}

unsigned char ucGetZomToothTelCtNoLearnMode(unsigned char  ucIdx)
{
  if (ucIdx < cSumWE)
  {
    return (tZOM[ucIdx].ucToothTelCtNoLearnMode);
  }
  else
  {
    return ((unsigned char) 0);
  }
}

unsigned char ucGetZomToothTelCt(unsigned char  ucIdx)
{
  if (ucIdx < cSumWE)
  {
    return (tZOM[ucIdx].ucToothTelCt);
  }
  else
  {
    return ((unsigned char) 0);
  }
}

unsigned char ucGetZomResetAbsRefFlag(unsigned char  ucIdx)
{
  if (ucIdx < cSumWE)
  {
    return (tZOM[ucIdx].ucResetABSRefFlag);
  }
  else
  {
    return ((unsigned char) 0);
  }
}

unsigned char ucGetZomDeltaMin(unsigned char  ucIdx)
{
  if (ucIdx < cSumWE)
  {
    return (tZOM[ucIdx].ucDeltaMin);
  }
  else
  {
    return ((unsigned char) 0);
  }
}

unsigned char *ucGetZomAbsComp(unsigned char  ucIdx)
{
  if (ucIdx < cSumWE)
  {
    return (&tZOM[ucIdx].ucABSComp[0]);
  }
  else
  {
    return ((unsigned char*) 0);
  }
}

unsigned short *ushGetZomAbsSums(unsigned char  ucIdx)
{
  if (ucIdx < cSumWE)
  {
    return (&tZOM[ucIdx].ushRelCmpVal[0]);
  }
  else
  {
    return ((unsigned short*) 0);
  }
}

#endif

unsigned char ucGetZomLqi(unsigned char  ucIdx)
{
  if (ucIdx < cSumWE)
  {
    if( tZOM[ucIdx].ushLqi < 0xFF)
    {
      return (unsigned char) tZOM[ucIdx].ushLqi;
    }else
    {
      return (unsigned char) 0xFF;
    }
  }
  else
  {
    return ((unsigned char) 0x00);
  }
}

void WATimer1sec(unsigned short ushVSpeedInKmh)
{
  unsigned char ucTmp;

  if (cV_MIN < ushVSpeedInKmh)
  {
    if (cV_MAX_PAL < ushVSpeedInKmh )
      if ( cTIME_OUT > ushDriveTimeOverPalMax  )
        ushDriveTimeOverPalMax++;

    if ((unsigned char) 0 == (ucWAState & cWAStateZO))
    {
      if (cTIME_OUT > ushDriveTimeInSec  )
      {
        ushDriveTimeInSec ++;
        if (cSpeciaLearn == ucLearnMode )
          if (ucSL3MinHistPreFinish() > 0)
            WAStatusChangedEvent((unsigned short) ucWAState );
      }
      else if (0 == (ucWAStateHi & cTO))
      {
        ucWAStateHi |= cTO;
        ucTmp = ucWAState;
        TOXpired ();

        if (((ucTmp & (unsigned char) 0xF0) == (unsigned char) 0) && ((ucWAState & (unsigned char) 0xF0) > (unsigned char) 0))
          UpdateALState (cEvNewIDs );
        if ((((unsigned char) 0 == ucNrOfLocatError()) && (cMaxLR  > ucNrOfUKWPinZOM())) || ((((unsigned char) 1 == ucNrOfLocatError() ) && ((unsigned char) 1 == ucNrOfUKWPinZOM()))))
             {
               if((ucNrOfLocatErrorAndPosForce() == 0) || (tWAPar.AL_State != cAL_Stored))
               {
                  UpdateALState (cEv4WPs );
               }
            }
        else
        {
          if (!(((unsigned char) 0 == ucNrOfLocatError()) && ((unsigned char) 4 == ucNrOfLearnError()) ))
          {
            UpdateALState (cEvALFailed );
          }
        }
      }
    }
  }
  UpdateDAGLearnState ();
}

 unsigned char * pucGetLearnError(void)
{
  return ucLearnError ;
}

 unsigned char * pucGetLocatError(void)
{
  return ucLocatError;
}

unsigned short ushGetDriveTimeInSec(void)
{
  return ushDriveTimeInSec ;
}

static unsigned short ushSpeciaLearn(tRFTelType * ptInputWA)
{
  unsigned short ushHelp, ushHistID, ushNewID;
  unsigned char ucCurID, ucIdentifiedWP = 0;

  ucCurID = ucPutInZOM(ptInputWA, &tWAPar);
  if ( ucCurID < cSumWE)
  {
    if ((ucWAState & cWAStateActive) == 0)
      if ( ucStartWA() == 1 )
        ucWAState |= cWAStateActive;

    (void) ucGetNrOfNewIDsInLM_SL (&ushNewID, (ucNoWheelSensorMounted() > 0) ? ucDefMinCt4ER+3:ucDefMinCt4ER );
    ushHistID = ushIDSetInHistNAlignWP(aulHistoryID,ucDefMinCt4HistER,cSumWE );

    if (ucAdjABSIface(ucCurID, ptInputWA) > (unsigned char) 0)
    {
      BuildCmpVal (ucCurID);
    }

    ushHelp = ushHistID | ushNewID;
    if (cMaxLR == ucNrOfBitSet (ushHelp ))
    {
      ucWAState |= cWAStateER;
      (void) ushAlignZOM (ushHelp);

      ucIdentifiedWP = ucGenDMnD2(10,4,0xFFFF);

      ushHistID = ushIDSetInHistNAlignWP(aulHistoryID,ucDefMinCt4HistER,cMaxLR );
      if ((unsigned char) 0 ==  ucAssessDAGSLUC(ucNrOfBitSet ((unsigned short) ucIdentifiedWP)))
      {
        if ((unsigned char) 4 != ucNrOfBitSet(ushHistID))
        {
          ucWAState &= (unsigned char) ~cWAStateER;
        }
      }
    }

    if ((unsigned char) 0 == (ucWAState & cWAStateZO ))
          (void) ucSL3MinHistPreFinish();
  }

  return(GETushWAState());
}
 static unsigned char ucAssessDAGSLUC(unsigned char ucWPs)
{
  unsigned char ucIDSlots,ucNewSensors, i,ucRet = 0;

  ucNewSensors = ucGetNrOfNewIDs(&ucIDSlots );

  if (0 == ucNewSensors )
   {
    ucRet = 1;
  }
  else if (cMaxLR == ucNewSensors )
  {
     if ((cHistIDProtectTime < ushDriveTimeInSec) && (cMaxLR == ucWPs))
       ucRet = 1;
   }
  else if (cMaxLR > ucNewSensors)
  {
    if ((c5MinDriveTimeInSec < ushDriveTimeInSec))
       if (ucNewZomIDsFit2MissingHistID_WP(ucIDSlots) > 0)
      {
        ucRet = 1;
      }
  }
  for (i = 0; i < cMaxLR; i++)
   {
    if ((tZOM [i].ucStatus & 0x0F) == 0)
    {
      ucRet = 0;
      break;
    }
  }
  if (ucRet > 0)
  {
    ucRet = ucWrZom2History(ucIDSlots) ;
    ucWAState |= (cWAStateZO+cWAStateER);
    ucWAState &= 0x0F;
     ucWAState |= (ucRet&0xF0);
    ucWAStateHi &= 0x0F;
     ucWAStateHi |= ((ucRet&0x0F)<<4);
    ucRet = (unsigned char) 0xFF;
  }

  return (ucRet);
}

      static unsigned char ucGetNrOfNewIDs(unsigned char * p2Slots)
{
  unsigned char i,j,ucOldID = 0;
  *p2Slots = (unsigned char) 0xFF;

  for (i = 0; i < cMaxLR ; i++)
  {
    for (j = 0; j < cMaxLR ; j++)
    {
      if (tZOM [i].ulID == aulHistoryID [j])
      {
        ucOldID++;
        *p2Slots &= ~(1<<i);
        *p2Slots &= ~((unsigned char) 0x10<<j);
        break;
      }
    }
  }

  return ( (unsigned char) (cMaxLR-ucOldID) );
}

     static unsigned char ucNewZomIDsFit2MissingHistID_WP(unsigned char ucNewNMissing)
{
  unsigned char i,j, ucNewCt=0, ucMatchCt=0;

  for (i = 0; i < cMaxLR ; i++)
   {
    if (((unsigned char) (1<<i) & ucNewNMissing ) > 0)
     {
      ucNewCt++;
      for ( j  = 0; j < cMaxLR; j++)
       {
        if (((unsigned char) (0x10<<j) & ucNewNMissing ) > 0)
         {
          if (ucGetZOMWP(i) == aucHistoryWP [j])
          {
            ucMatchCt ++;
            ucNewNMissing &= ~((unsigned char) (0x10<<j));
             break;
          }
        }
      }

      if (cMaxLR == j)
       {
        for ( j  = 0; j < cMaxLR; j++)
        {
          if (cWheelPos_RR  < aucHistoryWP [j])
          {
            ucMatchCt ++;
            ucNewNMissing &= ~((unsigned char) (0x10<<j));
             break;
          }
        }
      }
    }
  }

  if ( ucNewCt == ucMatchCt )
    return ((unsigned char) 1);
  else
    return ((unsigned char) 0);
}

            static unsigned char ucWrZom2History(unsigned char ucNewNMissing)
{
  unsigned char i,j,ucRet, ucNewCt = ucNrOfBitSet ((unsigned short) (ucNewNMissing & 0x0F));
  ucRet = 0;

  if (ucNrOfBitSet ((unsigned short) (ucNewNMissing & 0xF0)) == ucNewCt )
   {
    for ( i = 0; i < cMaxLR ; i++)
    {
      if ((ucNewNMissing & (1<<i)) > 0)
       {
        for ( j = 0; j < cMaxLR; j++)
          if ((ucNewNMissing & (0x10<<j)) > 0)
           {
            ucNewNMissing &= ~(0x10<<j);
             aulHistoryID [j] = tZOM [i].ulID;
            if (aucHistoryWP [j] != ucGetZOMWP(i))
            {
              ucRet |= (0x11<<j);
              aucHistoryWP [j] = ucGetZOMWP(i);
            }
            else
              ucRet |= (0x10<<j);
            break;
          }
      }
      else
      {
         for ( j = 0; j < cMaxLR; j++)
          if (tZOM [i].ulID == aulHistoryID [j])
          {
            if (ucGetZOMWP(i) == aucHistoryWP [j])
               break;
            else
            {
              aucHistoryWP [j] = ucGetZOMWP(i);
               ucRet |= (1<<j);
              break;
            }
          }
          }
    }
    if (ucHistInConsist() > 0)
    {
       GetWADataEE(cHistorySet1, (unsigned char *) aulHistoryID, (unsigned char) sizeof(aulHistoryID));
      GetWADataEE(cHistoryWPSet1, aucHistoryWP, (unsigned char) sizeof(aucHistoryWP));
      ucRet = 0;
    }
    else
    {
      PutWADataEE(cHistorySet1, (unsigned char *) aulHistoryID, (unsigned char) sizeof(aulHistoryID));
       PutWADataEE(cHistoryWPSet1, aucHistoryWP, (unsigned char) sizeof(aucHistoryWP));
    }
  }
  else
     ucRet = 0;

  return (ucRet);
}

 unsigned char ucHistInConsist(void)
{
  unsigned char i,j, ucRet = 0xF0;

  for ( i = 0; i < cMaxLR ; i++)
   {
    if (aulHistoryID [i] < (unsigned long) 1)
    {
      ucRet |= (0x01<<i);
    }
  }

  for ( i = 0; i < cMaxLR ; i++)
   {
    for ( j = 0; j < cMaxLR ; j++)
    {
      if ( i != j)
      {
        if (aulHistoryID [i] == aulHistoryID [j])
        {
          ucRet |= (1<<i);
          break;
        }
      }
    }
  }

  for ( i = 0; i < cMaxLR ; i++)
   {
    if (aucHistoryWP [i] < (cWheelPos_RR + 1))
    {
      ucRet &= ~(0x10<<aucHistoryWP [i]);
     }
  }

  return (ucRet);
}

  static unsigned char ucSL3MinHistPreFinish(void)
{
  unsigned char ucRet = 0;
  unsigned short usHelp = 0;

  if ( (unsigned char) 0 == (ucWAState & cWAStateZO))
   {
    if ((unsigned char) 0 == ucHistInConsist ())
    {
      usHelp = ushIDSetInHist(aulHistoryID,3,cSumWE );
      if (ucNrOfBitSet (usHelp) == cMaxLR )
       {
        (void) ushAlignZOM(usHelp);                    /* put "ER set" to the 4 first ZOM slots */
        ucWAState = (cWAStateZO+cWAStateER);
        RestoreHistory ();
        ucRet = (unsigned char) 1;
      }
    }
  }

  return (ucRet);
}

  static unsigned char ucSL31Finish(unsigned char ucMinCt4NewID)
{
  unsigned short ushNewID = 0;

  if ( (unsigned char) 0 == (ucWAState & cWAStateZO))
   {
    if ( (unsigned char) 1 == ucGetNrOfNewIDsInLM_SL(&ushNewID,ucMinCt4NewID) )
    {
      if (0 < ui16NewIdFits(ushNewID, ushIDSetInHist(aulHistoryID,3,cSumWE )))
       {
        ucWAState |= cWAStateER;
        SetWAStateZOChange (ucSetHistory (cWAStateZO,0x0F));
        dblCk4LocEr ();
        if ((unsigned char) 0 == ucNrOfUKWPinHist())
        {
          ucWAState |= cWAStateZO;
          ucWAStateHi |= cForcedZO ;
        }
        return ((unsigned char) 1);
      }
    }

  }

  return ( (unsigned char) 0);
}

  static unsigned char ucGetNrOfNewIDsInLM_SL(unsigned short * p2Slots, unsigned char ucMinCt)
{
  unsigned char i,j,ucNewID = (unsigned char) 0;
  *p2Slots = 0;

  for (i = 0; i < cSumWE ; i++)
  {
    if (tZOM [i].ucProbeCt  > 0)
     {
      for (j = 0; j < cMaxLR ; j++)
      {
        if (tZOM [i].ulID == aulHistoryID [j])
        {
          break;
        }
      }
      if ( cMaxLR == j )
       {
        if (tZOM[i].ucTelCtLearnBit > ucMinCt)
        {
          tZOM[i].ucStatus |= cZOMStatER;
          ucNewID++;
          *p2Slots |= 1<<i;
        }
      }
    }
    else
      break;
   }
  return ( ucNewID );
}

  static unsigned char ucGetNrOfNewIDsInLM(unsigned short * p2Slots, unsigned char ucMinCt)
{
  unsigned char i,j,ucNewID = (unsigned char) 0;
  *p2Slots = 0;

  for (i = 0; i < cSumWE ; i++)
  {
    if (tZOM [i].ucProbeCt  > 0)
     {
      for (j = 0; j < cMaxLR ; j++)
      {
        if (tZOM [i].ulID == aulHistoryID [j])
        {
          break;
        }
      }
      if ( cMaxLR == j )
       {
        if (ucMinCt < tZOM[i].ucTelCtLearnBit)
        {
          if (ucDefMinCt4ER <= ucMinCt)
          {
            tZOM[i].ucStatus |= cZOMStatER;
          }
          ucNewID++;
          *p2Slots |= 1<<i;
        }
      }
    }
    else
      break;
   }
  return ( ucNewID );
}

  static void CheckAutoDeactivateOverride(void)
{
  unsigned short ushHelp;

  ushHelp = ushCheckERState(ucDefMinCt4ER, ucDefMinCt4HistER, (ushDriveTimeInSec > cHistIDProtectTime ) ? (unsigned char) 1:(unsigned char) 0);     /* get all ERs */
  if ( ushHelp > 0)                       /* ERState met ? */
  {
    ucWAState |= cWAStateER;             /* ER state reached now */
    (void) ushAlignZOM(ushHelp);                    /* put "ER set" to the 4 first ZOM slots */
    SetWAStateZOChange(ucSetHistory((unsigned char)cWAStateER, 0x0F)); /* freeze IDset */
  }
}

  static unsigned char ucFinishViaHistory(void)
{
  unsigned short ushHelp = ushIDSetInHist(aulHistoryID,ucDefMinCt4HistER,cSumWE);

  if (cMaxLR == ucNrOfBitSet(ushHelp)) /* complete "history ER set" found ? */
  { /* yes */
    if ((ucGetERState() < 1) || (0x000F != ushHelp )) /* not even ER state reached OR ER w/ other wheel set ? */
    {
      (void) ushAlignZOM(ushHelp);
      ucWAState |= cWAStateER;
    }
    (void) ucGenDMnD2(10,4,0xFFFF);
    if ( (ucNrOfUKWPinZOM () > ucNrOfUKWPinHist ()) && !( 1 == ucNrOfUKWPinZOM ()))
    {
      ucWAState &= (unsigned char) ~cWAStateZO;
     }
    else
    {
      SetWAStateZOChange (ucSetHistory (cWAStateZO,0x0F));
      if ((unsigned char) 0 == ucNrOfUKWPinHist())
      {
        ucWAState |= cWAStateZO;
        if ( 1 == ucNrOfUKWPinZOM ())
          ucWAStateHi |= cForcedZO ;
      }
    }

    return ((unsigned char) 1);
  }
  else
    return ((unsigned char) 0);
}
static unsigned char ucBadHist2Def(void)
 {
  unsigned char i, ucBadIDCt = (unsigned char) 0;

  for (i = 0; i < cMaxLR; i++)
   {
    if ( aulHistoryID[i] < 1UL )
     {
      aulHistoryID[i] = (unsigned long) i + 1;
      ucBadIDCt++;
    }
  }
  return (ucBadIDCt );
}

  static unsigned char ucGetNrOfNewIDsInLMwoPAL(unsigned short * p2Slots)
{
  unsigned char i,j,ucNewID = (unsigned char) 0;
  *p2Slots = 0;

  for (i = 0; i < cSumWE ; i++)
  {
    if (tZOM [i].ucProbeCt  > 0)
     {
      for (j = 0; j < cMaxLR ; j++)
      {
        if (tZOM [i].ulID == aulHistoryID [j])
        {
          break;
        }
      }
      if ( cMaxLR == j )
       {
        if (tZOM[i].ucToothTelCtNoLearnMode > 0)
        {
          ucNewID++;
          *p2Slots |= 1<<i;
        }
      }
    }
    else
      break;
   }
  return ( ucNewID );
}

  static unsigned char uc3NewIDsAllocated(unsigned char ucMinCt4NewID)
{
  unsigned short ushHistSet = 0, ushNewID = 0;

  if ( (unsigned char) 0 == (ucWAState & cWAStateZO))
   {
    ushHistSet = ushIDSetInHist(aulHistoryID,3,cSumWE );
    if (ucNrOfBitSet (ushHistSet) == 0 )
     {
      if ( (unsigned char) 3 == ucGetNrOfNewIDsInLM_SL(&ushNewID,ucMinCt4NewID))
      {
        ushNewID = ushAlignZOM(ushNewID );
        if ((unsigned char) 3 == ucNrOfBitSet((unsigned short) ucGenDMnD2(10,4,ushNewID)))
        {
           SetWAStateZOChange (ucSetHistory (cWAStateZO,(unsigned char) ushNewID));
          return ((unsigned char) 1);
        }
      }
    }
  }
  return ( (unsigned char) 0);
}

static unsigned short ushCompLearn(tRFTelType * ptInputWA)
{
  unsigned char ucCurID;
  unsigned short ushHelp;

  if( (tWAPar.ucWACtrl & ucWACtrlBreakc) == 0)  /* WA actions not breaked */
  { /* try to reach a higher state */
    ucCurID = ucPutInZOM(ptInputWA, &tWAPar);
    if ( ucCurID < cSumWE)   /* new data to assess ? */
    {
      if ((ucWAState & cWAStateActive) == 0)             /* identification already running ? OBSOLETE TODO:remove */
        if ( ucStartWA() == 1 )                 /* no, start conditions met ? */
          ucWAState |= cWAStateActive;          /* yes, WA official start */

      if (  ucGetERState() == 0 )                /* ER state already reached */
      {
        ushHelp = ushWhlSetRdy2Freeze ((ucNoWheelSensorMounted() > 0) ? ucDefMinCt4ER+3:ucDefMinCt4ER, ucDefMinCt4HistER, (ushDriveTimeInSec > cHistIDProtectTime ) ? (unsigned char) 1:(unsigned char) 0);     /* get all ERs */
        if ( ushHelp > 0)                       /* ERState met ? */
        {
          ucWAState |= cWAStateER;              /* ER state reached now */
          (void) ushAlignZOM(ushHelp);                    /* put "ER set" to the 4 first ZOM slots */
          ucCurID = ucGetZOMPosOfID( &ptInputWA->AK35def.ulID); /* ZOM has just be sorted, so need to update ID position in Zom */
        }

        if ((ucCheckWheelPos(ucCurID, ptInputWA ) == 1) && (ucGetERState()==1))    /* ZOState met ? */
        {   /* autolocation shouldn't be reached before autolearn*/
          SetWAStateZOChange(ucSetHistory((unsigned char)cWAStateZO, 0x0F));
          ucWAState |= cWAStateZO;
        }
        else if( ucGetERState()==1 )
        {
          SetWAStateZOChange(ucSetHistory((unsigned char)cWAStateER, 0x0F));
        }
      }
      else
      {
        if (ucCheckWheelPos(ucCurID,ptInputWA ) == 1)
        {
          SetWAStateZOChange(ucSetHistory((unsigned char)cWAStateZO, 0x0F));
          ucWAState |= cWAStateZO;
        }
      }
    }
    else
    {
    }
  }
  return(GETushWAState());
}

static unsigned short ushWhlSetRdy2Freeze(unsigned char ucMinCt, unsigned char ucMinCt4HistERc, unsigned char bLearnNewIDsFlag)
{
  unsigned char ucNewCt,ucOldCt, ucOtherCt;
  unsigned short ushNew, ushOld, ushOther, ushRet = 0;

  ushOld = ushIDinLearnModeSetInHist(aulHistoryID,ucMinCt4HistERc,cSumWE);
  ushOld |= ushSetHistIDs2ER (aulHistoryID,ucDefMinCt4HistER,cSumWE);
  ucOldCt = ucNrOfBitSet(ushOld);
  ucNewCt = ucGetNrOfNewIDsInLM (&ushNew,ucMinCt );

  ucOtherCt = ucGetNrOfNewIDsInLM (&ushOther,(unsigned char) 4 );
  ucOtherCt -= ucNewCt;
  ushOther &= ((unsigned short) ~ushNew);

  if (cMaxLR == ucOldCt)
     ushRet = ushOld;
  else if ((cMaxLR == ucNewCt) && (0 == ucOldCt) && bLearnNewIDsFlag && ( 0 == ucOtherCt ))
      ushRet = ushNew;
  else if ((cMaxLR == (ucNewCt + ucOldCt)) && bLearnNewIDsFlag && ( 0 == ucOtherCt ))
    ushRet = (ushNew|ushOld);

  return(ushRet);
}
   static unsigned char ucForceAutoLocate(void)
{
  unsigned char i,j, ucUK, ucUnusedWP;

  ucUnusedWP = 0x0F;
  ucUK = 0;

  if (ui8AnyHistIdMissing () == ((uint8) 0))
   {
     for (i = 0; i < cMaxLR; i++)
      {
        if ( aucHistoryWP[i] > cWheelPos_RR  )
        {
           ucUK |= (unsigned char) (0x10<<i);
        }
        else
        {
           ucUnusedWP &= (unsigned char) ~(1<<aucHistoryWP [i]);
        }
     }

     if (ucNrOfBitSet ((unsigned short) ucUK) == (unsigned char) 1)
     {
        for (i = 0; i < cMaxLR; i++)
         {
           if ((ucUK & (0x10<<i)) > 0)
           {
              for (j = 0; j < cMaxLR ; j++)
              {
                 if ( (ucUnusedWP & (1<<j)) > 0 )
                 {
                    aucHistoryWP [i] = j;
                    ucWAStateHi |= cForcedZO ;
                    j = cMaxLR;
                  }
              }
           }
        }
     }
     else
     {
        ucUK = (unsigned char) 0;
     }
  }

  return ( ucUK );
}
 static unsigned char ucCmpHist2ZOMID(unsigned char ucVZS)
{
  unsigned char i,j, ucRet = (unsigned char) 0x0F;

  for (i = 0; i < cMaxLR; i++)
  {
    for (j = 0; j < cMaxLR; j++)
    {
      if ((aulHistoryID [i] == tZOM[j].ulID) && (((ucVZS & (unsigned char) (1<<j)) > 0)))
      {
        ucRet &= (unsigned char) ~(1<<i);
        break;
      }
    }
  }

  return (ucRet);
}
 static unsigned char ucNrOfUKWPinZOM(void)
{
  unsigned char i, ucRet = 0;

  for ( i = 0; i < cMaxLR ; i++)
  {
    if ((unsigned char) 0 == (tZOM[i].ucStatus & 0x0F))
    {
      ucRet++;
    }
  }

  return (ucRet);
}

static unsigned char ucNrOfUKWPinHist(void)
{
  unsigned char i, ucRet = 0;

  for ( i = 0; i < cMaxLR ; i++)
  {
    if ((unsigned char) cWheelPos_RR  < aucHistoryWP [i])
    {
      ucRet++;
    }
  }

  return (ucRet);
}

static unsigned char ucFinalFreeze(unsigned char ucMinCt4HistER, unsigned char ucMinCt)
{
  unsigned char ucIdentifiedWP;
  unsigned short ushNew,ushOld,ushFRS;

  if ((unsigned char) 0 == ucFinishViaHistory())
  {
    (void) ucGetNrOfNewIDsInLM (&ushNew,ucMinCt );
    ushOld = ushIDSetInHist(aulHistoryID,ucDefMinCt4HistER,cSumWE);

    if (( cMaxLR < ucNrOfBitSet (ushNew|ushOld)) && (((unsigned char) 0) == ucGetERState () ))
    {
      ushNew = ushReduceCorel24(ushNew|ushOld);
      ushOld = 0;
      ushNew = ushAlignZOM(ushNew);
      if (cMaxLR == ucNrOfBitSet (ushNew))
        ucWAState |= cWAStateER;
      if ((unsigned char) 0 == ucNrOfUKWPinZOM ())
        ucWAState |=  cWAStateZO;
      SetWAStateZOChange (ucSetHistory (cWAStateZO,(unsigned char) ushNew));
      dblCk4LocEr ();
    }
    else
    {
      if ( ucNrOfBitSet (ushNew|ushOld) < cMaxLR )
       {
          ushNew = ushLqiTribute(ushNew);
       }

      ucIdentifiedWP = ucGenDMnD2(10,4,(ushOld|ushNew));

      ushOld = ushIDSetInHist(aulHistoryID,ucDefMinCt4HistER,cSumWE);
       ushNew = 0;
      (void) ucGetNrOfNewIDsInLM (&ushNew,ucMinCt );
      ushNew &= ((unsigned short) ucIdentifiedWP);

      ushOld |= (unsigned short) ucIdentifiedWP ;
      if (ucNrOfBitSet (ushOld) > cMaxLR )
      {
        SetWAStateZOChange (ucSetHistory (cWAStateZO,ucIdentifiedWP));
         dblCk4LocEr( );
      }
      else
      {
        ushNew |= ushOld;
        ushNew = ushAlignZOM(ushNew);
        if (ucNrOfBitSet (ushNew) > cMaxLR)
        {
          SetWAStateZOChange (ucSetHistory (cWAStateZO,(unsigned char)ushOld));
           dblCk4LocEr ();
        }
        else if (0 < ushNew )
        {
          SetWAStateZOChange (ucSetHistory (cWAStateZO,(unsigned char) ushNew));
          dblCk4LocEr ();
        }
        else
          return ((unsigned char) 0);
      }
    }
  }

  ucIdentifiedWP = ((unsigned char) 4 - ucNrOfUKWPinHist());
  if (cMaxLR == ucIdentifiedWP)
  {
    ucWAStateHi &= (unsigned char) ~cTZG;
  }
  else if ((unsigned char) 0 == ucIdentifiedWP )
  {
    ucWAStateHi &= (unsigned char) ~cTZG;
  }
  else
  {
    ucWAState &= (unsigned char) ~cWAStateZO;
    ucWAStateHi |= cTZG;
  }

  return ((unsigned char) 1);
 }
 static void UpdateALState(uint8 ui8Trigger)
{
  uint8 ui8ALState = tWAPar.AL_State;

  switch (ui8ALState)
  {
  case cAL_OK :
    if (cEvALFailed == ui8Trigger)
      tWAPar.AL_State = cAL_Stored;
    else if ( cEvNewIDs == ui8Trigger)
      tWAPar.AL_State = cAL_Unknown ;
    break;
  case cAL_Stored :
    if (cEv4WPs == ui8Trigger)
      tWAPar .AL_State = cAL_OK ; /* #OIL 1273 --> SOLL: Bei Rückfall auf Historie kein Wechsel von cAL_Stored 2 cAL_OK!!*/
    else if ( cEvNewIDs == ui8Trigger)
      tWAPar .AL_State = cAL_Unknown ;
    break;
  case cAL_Unknown :
    if (cEv4WPs == ui8Trigger)
      tWAPar .AL_State = cAL_OK ;
    else if (( cEvALFailed == ui8Trigger))
       tWAPar .AL_State = cAL_Error ;
    break;
  case cAL_Error :
    if (cEv4WPs == ui8Trigger)
      tWAPar .AL_State = cAL_OK ;
    else if ( cEvNewIDs == ui8Trigger)
      tWAPar .AL_State = cAL_Unknown ;
    break;
  default:
    if ((unsigned char) 0 == ucNrOfUKWPinHist () )
      tWAPar .AL_State = cAL_Stored ;
    else
      tWAPar .AL_State = cAL_Unknown ;
    break;
  }

  if (ui8ALState != tWAPar.AL_State)
    PutWADataEE(cWAParameter, (unsigned char *) &tWAPar , (unsigned char) sizeof(WAParameter));
}

uint8 ui8GetALState(void)
{
  return (tWAPar.AL_State);
}

unsigned char ucGetLearnMode(void)
{
  return ucLearnMode ;
}

   static unsigned short ucFindNoLearnHistoryIDs(unsigned long *ptHistID, unsigned char ucMinProbeCt, unsigned char ucSlots2Search)
{
  unsigned char j, ucRet = (unsigned char) 0xFF;

  for( j = 0; j < ucSlots2Search; j++)
  {
    if ((*ptHistID == ulGetZOMID(j)) && (ucGetZomTelCtLearnBit(j) >= ucMinProbeCt ))
    {
      ucRet = (unsigned char) 0;
      break;
    }
    else
    {
      if (ulGetZOMID(j) == (unsigned long) 0)
      {
        break;
      }
    }
  }
  return (ucRet);
}

  static unsigned short ucFindMissingHistoryIDs(unsigned long *ptHistID, unsigned char ucMinProbeCt, unsigned char ucSlots2Search)
{
  unsigned char j, ucRet = (unsigned char) 0xFF;

  for( j = 0; j < ucSlots2Search; j++)
  {
    if ((*ptHistID == ulGetZOMID(j)) && (ucGetProbeCt(j) >= ucMinProbeCt ))
    {
      ucRet = (unsigned char) 0;
      break;
    }
    else
    {
      if (ulGetZOMID(j) == (unsigned long) 0)
      {
        break;
      }
    }
  }
  return (ucRet);
}

 static unsigned char ucGetMisOrNoLearnError(void)
{
  unsigned char i, ucRet = (unsigned char) 0;

  for (i = 0; i < cMaxLR ; i++)
  {
    if (ucFindMissingHistoryIDs(&aulHistoryID[i],ucDefMinCt4HistER, cSumWE ) > ((unsigned char) 0) )
    {
      ucLearnError [i] = SensorMissin ;
      ucRet |= (1<<i);
    }
    else if (ucFindNoLearnHistoryIDs (&aulHistoryID[i] ,ucDefMinCt4HistER , cSumWE ) > ((unsigned char) 0) )
    {
      ucLearnError [i] = NoLearnSensor ;
      ucRet |= (1<<i);
    }
    else
    {
      ucLearnError [i] = NoError ;
    }
  }

  return (ucRet);
}

 static unsigned char ucGetAnyLocatErrors(unsigned char ucDontTouch)
{
  unsigned char i, ucRet = 0;

  for ( i = 0; i < cMaxLR ; i++)
  {
    if ( ucGetLocatError(i) != NoError )
    {
      ucRet |= (1<<i);
    }
  }
   if (ABSignalMissin == ucABSignalMissin)
  {
    for ( i = 0; i < cMaxLR ; i++)
    {
      if ( ucGetLocatError(i) != NoError )
      {
        PutLocatError( ABSignalMissin, i);
      }
    }
    return (ucRet);
  }
   if ((ushDriveTimeInSec >> 1) < ushDriveTimeOverPalMax )
   {
    for ( i = 0; i < cMaxLR ; i++)
    {
      if ( ucGetLocatError(i) != NoError )
      {
        PutLocatError( BadSpeed, i);
      }
    }
  }

  return (ucRet);
}
void ClearAlLearNLocatError(unsigned char ucErrType)
{
  unsigned char i;

  for ( i = 0; i < cMaxLR ; i++)
  {
    if (cAll == ucErrType )
    {
      ucLocatError [i] = NoError ;
    }
    ucLearnError [i] = NoError ;
  }

  ucABSignalMissin = NoError ;
}
 void PutLocatError(unsigned char ucTipicoDiErrori, unsigned char ucZomSlot)
{
  unsigned char i;

  if ( cSumWE > ucZomSlot)
  {
    for ( i = 0; i < cMaxLR ;i++)
    {
      if (ulGetZOMID (ucZomSlot) == ulGetID(i))
       {
        if (AssegnazioneCostretto != ucLocatError [i])
        {
          if ((AmbigWP == ucTipicoDiErrori) && (tZOM [ucZomSlot].ucToothTelCt <= cMinCt4Dec )) /*CRS_1211_080_003*/
            ucTipicoDiErrori = TooFewPalTels; /*CRS_1211_080_003*/
          ucLocatError [i] = ucTipicoDiErrori;
          break;
        }
      }
    }
  }

  return;
}
 unsigned char ucGetLocatError(unsigned char ucZomSlot)
{
  unsigned char i;

  if ( cSumWE > ucZomSlot)
  {
    for ( i = 0; i < cMaxLR ;i++)
    {
      if (ulGetZOMID (ucZomSlot) == ulGetID(i))
       {
        return (ucLocatError [i]);
      }
    }
  }

  return (NoError );
}

 static unsigned char ucNrOfLocatError(void)
{
  unsigned char i, ucRet;

  ucRet = (unsigned char) 0;
  for ( i = 0; i < cMaxLR ; i++)
  {
    if (( NoError != ucLocatError [i]) && ( AssegnazioneCostretto != ucLocatError[i]))
    {
      ucRet++;
    }
  }

  return (ucRet);
}

 static unsigned char ucNrOfLocatErrorAndPosForce(void)
{
  unsigned char i, ucRet;

  ucRet = (unsigned char) 0;
  for ( i = 0; i < cMaxLR ; i++)
  {
    if (( NoError != ucLocatError [i]) && ( AssegnazioneCostretto == ucLocatError[i]))
    {
      ucRet++;
    }
  }

  return (ucRet);
}

 static unsigned char ucNrOfLearnError(void)
{
  unsigned char i, ucRet;

  ucRet = (unsigned char) 0;
  for ( i = 0; i < cMaxLR ; i++)
  {
    if ( ucLearnError [i] != NoError )
    {
      ucRet++;
    }
  }

  return (ucRet);
}

 static void TOXpired(void)
{
  if ((unsigned char) 0 == (ucWAState & cWAStateZO))
   {
    if (cCompleteLearn == ucLearnMode )
    {
      if ((unsigned char) 0 < ucFinalFreeze(ucDefMinCt4HistER, (ucNoWheelSensorMounted() > 0) ? ucDefMinCt4ER+3:ucDefMinCt4ER))
         WAStatusChangedEvent(GETushWAState() );
    }
    else if (cSpeciaLearn == ucLearnMode )
    {
      if ( 0 == ucSL31Finish ((ucNoWheelSensorMounted() > 0) ? ucDefMinCt4ER+3:ucDefMinCt4ER))
      {
        if (uc3NewIDsAllocated((ucNoWheelSensorMounted() > 0) ? ucDefMinCt4ER+3:ucDefMinCt4ER) > 0)
        {
          ucWAStateHi |= cTZG ;
        }
        else
        {
          (void) ucFinishViaHistory ();
          dblCk4LocEr ();
        }
      }
    }

    if ((ucWAState & cWAStateZO) == 0)
     {
      (void) considerationeDiAssegnazioneCostretto();
    }

    if ((ucWAState & cWAStateZO) == 0)
     {
      if (ucWATO() > 0)
      {
        ucWAStateHi |= cErrorActive ;
        WAStatusChangedEvent(GETushWAState() );
      }
    }
    else
    {
      if (!(ucWAStateHi & cForcedZO))
      {
        ClearAlLearNLocatError (cAll );
      }
      else
      {
        ucWAStateHi |= cErrorActive ;
            (void) ucGetAnyLocatErrors(0); /*pb Empfehlung für #OIL1314 CRS_1211_090_003 */
      }
      WAStatusChangedEvent(GETushWAState() );
    }
  }
}

unsigned char ui8GetDAGAutoLearnState(void)
{
  return (ucDAGLearnState );
}

static void UpdateDAGLearnState(void)
{
  unsigned char i, ucMissin = 0;

  if (Autolearn_Learning == ucDAGLearnState)
  {
    if (ucGetERState() > 0)
    {
      ucDAGLearnState = Autolearn_OK ;
    }
    else if ((ucWAStateHi & cErrorActive) > 0)
    {
      for (i = 0; i < cMaxLR ; i++)
      {
        if ( SensorMissin == ucLearnError [i] )
        {
          ucMissin++;
        }
      }
      switch (ucMissin )
      {
      case 1:
        ucDAGLearnState = Timeout_3_Sensors;
        break;
      case 2:
        ucDAGLearnState = Timeout_2_Sensors;
        break;
      case 3:
        ucDAGLearnState = Timeout_1_Sensor;
        break;
      case 4:
        ucDAGLearnState = Timeout_No_Sensors;
        break;
      default:
        ucDAGLearnState = Autolearn_OK;
        break;
      }
    }
  }
}

void PutABSErrorActive(void)
{
#ifdef WAModulTest

#else
  if (bGetABSSignalDTCActive() == TRUE)
   {
    ucABSignalMissin = ABSignalMissin ;
  }
#endif
}
static unsigned char ucTakeOverHistWP(unsigned char ucHistIx,unsigned char ucZomIx)
{
  if (ucHistIx < cMaxLR )
  {
    if (ucZomIx < cSumWE )
    {
      if ((aulHistoryID[ucHistIx] == ulGetZOMID(ucZomIx)) && ((unsigned char) 4 > aucHistoryWP [ucHistIx]))
      {
        SetZOMWP(ucZomIx,aucHistoryWP[ucHistIx]);
        tZOM[ucZomIx].ucStatus |= cZOMStatHistER;
        return ((unsigned char) 0xFF);
      }
      else
      {
        return ((unsigned char) 0);
      }
    }
    else
    {
      return ((unsigned char) 0);
    }
  }
  else
  {
    return ((unsigned char) 0);
  }
}

      static unsigned short ushIDSetInHistNAlignWP(unsigned long *ptHistSet, unsigned char ucMinProbeCt,
                                     unsigned char ucSlots2Search)
{
  unsigned char i,j;
  unsigned short ushRet = 0;

  for ( i = 0; i < cMaxLR; i++)
  {
    if (ptHistSet[i] == (unsigned long) 0)
    {
      ushRet = 0;
      break;
    }
    else
    {
      for( j = 0; j < ucSlots2Search; j++)
      {
        if ((ptHistSet[i] == ulGetZOMID(j)) && (ucGetProbeCt(j) >= ucMinProbeCt ))
        {
          ushRet |= (1<<j);
          if ((unsigned char) 0 == (tZOM[j].ucStatus & (unsigned char) 0x0F))
          {
            if ((unsigned char) 0 == ucTakeOverHistWP(i,j))
             {
               tZOM[j].ucStatus |= cZOMStatHistER;
            }
            else
            {
              PutLocatError (AssegnazioneCostretto ,j);
            }
          }
          break;
        }
        else
        {
          if (ulGetZOMID(j) == (unsigned long) 0)
          {
            break;
          }
        }
      }
    }
  }
  return (ushRet);
}

      static unsigned short ushSetHistIDs2ER(unsigned long *ptHistSet, unsigned char ucMinProbeCt,
                                     unsigned char ucSlots2Search)
{
  unsigned char i,j;
  unsigned short ushRet = 0;

  for ( i = 0; i < cMaxLR; i++)
  {
    if (ptHistSet[i] == (unsigned long) 0)
    {
      ushRet = 0;
      break;
    }
    else
    {
      for( j = 0; j < ucSlots2Search; j++)
      {
        if ((ptHistSet[i] == ulGetZOMID(j)) && (ucGetProbeCt(j) >= ucMinProbeCt ) )
        {
          ushRet |= (1<<j);
          tZOM[j].ucStatus |= cZOMStatHistER;
          break;
        }
        else
        {
          if (ulGetZOMID(j) == (unsigned long) 0)
          {
            break;
          }
        }
      }
    }
  }
  return (ushRet);
}

static unsigned short ushLearnInOver8(tRFTelType * ptInputWA)
{
  unsigned char ucCurID;
  unsigned short ushHelp;

  ucCurID = ucPutInZOM(ptInputWA, &tWAPar);
  if ( ucCurID < cSumWE)   /* new data to assess ? */
  {
    if ((ucWAState & cWAStateActive) == 0)             /* identification already running ? OBSOLETE TODO:remove */
      if ( ucStartWA() == 1 )                 /* no, start conditions met ? */
        ucWAState |= cWAStateActive;          /* yes, WA official start */

    if (  ucGetERState() == 0 )                /* ER state already reached */
    {
      ushHelp = ushWhlSetRdy2Freeze ((ucNoWheelSensorMounted() > 0) ? ucDefMinCt4ER+3:ucDefMinCt4ER, ucDefMinCt4HistER, (ushDriveTimeInSec > cHistIDProtectTime ) ? (unsigned char) 1:(unsigned char) 0);     /* get all ERs */
      if ( ushHelp > 0)                       /* ERState met ? */
      {
        ucWAState |= cWAStateER;              /* ER state reached now */
        (void) ushAlignZOM(ushHelp);                    /* put "ER set" to the 4 first ZOM slots */
        ucCurID = ucGetZOMPosOfID( &ptInputWA->AK35def.ulID); /* ZOM has just be sorted, so need to update ID position in Zom */
        SetWAStateZOChange(ucSetHistory((unsigned char)cWAStateER, 0x0F)); /* freeze IDset .. this might reset over8-mode*/
        if ( ucWACtrlFixc == tWAPar.ucWACtrl )
         {
            RestoreHistory ();
        }
      }
    }
  }
  else
  { /* wheel is not turning, too small or too much or anything else*/
  }

  return(GETushWAState());
}

  static unsigned char ucPasSupplFilter(tRFTelType * p2Tel)
{
  unsigned char i;
  const unsigned char aucLearnType[] = {cTelTypeSELPAL, cTelTypeSELPAL1, cTelTypeAK35def, cTelTypeAK35defLMA, cTelTypeAK35defLF };
  unsigned char ucRet = (unsigned char) 0;
   {
    for ( i = ((unsigned char) 0); i < sizeof(aucLearnType);  i++)
    {
      if (aucLearnType[i] == p2Tel->AK35def .ucCmdID )
      {
        ucRet = (unsigned char) 0xFF;
        break;
      }
    }
  }

  return (ucRet);
}

 static void MergeWPandPWP(void)
{
  unsigned char i;

  for ( i = (unsigned char) 0; i < cMaxLR ;i++)
  {
#ifndef WAModulTest
    if (aucHistoryWP [i] > cWheelPos_RR  )
    {
      aucWPorPWP[i] = USEui8PWPofHistCol (i);
    }
    else
#endif
    {
      aucWPorPWP[i] = aucHistoryWP[i];
    }
  }
}

 unsigned char * GETpucStartAdrWPorPWP(void)
{
  MergeWPandPWP ();

  return (aucWPorPWP);
}

 unsigned char GETucWPorPWPofHistCol(unsigned char ucCol)
{
  if (ucCol < cMaxLR)
  {
    MergeWPandPWP();
    return(aucWPorPWP[ucCol]);
  }
  else
  {
    return (cMaxLR);
  }
}

          unsigned short GETushWAState(void)
{
  return ((unsigned short) (ucWAStateHi << 8) + (unsigned short) ucWAState);
}

unsigned char WAInitByDiag(WAParNCfgType * p2ParNCfg)
{
  ucWAState &= (unsigned char) ~(cWAStateZO);
  ucWAState &= (unsigned char) ~(cWAStateER);
  ucWAState &= (unsigned char) ~(cWAStateActive);
  ucWAStateHi = (unsigned char) 0;
  SetWAStateZOChange(0);
  ushDriveTimeInSec = 0;
  ushDriveTimeOverPalMax = 0;
  ucLearnMode = p2ParNCfg ->ucWACfg ;
  ClearAlLearNLocatError(cAll);
  ClearZOM(cSumWE);

  GetWADataEE(cWAParameter, (unsigned char *) &tWAPar , (unsigned char) sizeof(WAParameter));
  if ((ucHistInConsist () > (unsigned char) 0) && ((cAL_OK == tWAPar.AL_State ) || (cAL_Stored == tWAPar.AL_State) || (cAL_Error == tWAPar.AL_State)))
  {
    tWAPar.AL_State = cAL_Unknown ;
    PutWADataEE(cWAParameter, (unsigned char *) &tWAPar , (unsigned char) sizeof(WAParameter));
  }
  else if (((unsigned char) 0) == ucHistInConsist ())
  {
    tWAPar.AL_State = cAL_OK ;
    PutWADataEE(cWAParameter, (unsigned char *) &tWAPar , (unsigned char) sizeof(WAParameter));
  }

  ucDAGLearnState = Autolearn_Learning ;

  Very1stABSTickIinit();

  WAStatusChangedEvent(GETushWAState() );

  return (ucGetHistoryState());
}

 static uint8 considerationeDiAssegnazioneCostretto(void)
{
  uint8 ui8ChangeWPSlot = ucForceAutoLocate ();

  if ((uint8) 1 == ucNrOfBitSet ((uint16) ui8ChangeWPSlot ))
   {
    ucWAStateHi |= ui8ChangeWPSlot;
    PutWADataEE(cHistoryWPSet1, aucHistoryWP, (unsigned char) sizeof(aucHistoryWP));

       return (ui8ChangeWPSlot);
  }

  return((uint8) 0);

}

  static void dblCk4LocEr(void)
{
  uint8 i;
  uint16 zomSlot2Chk;

  zomSlot2Chk = ushIDSetInHist(aulHistoryID,ucDefMinCt4HistER,cSumWE);
  for ( i = (uint8) 0; i < cSumWE ; i++)
  {
    if ((zomSlot2Chk & (1<<i)) > 0)
    {
      if (((uint8) 0) == (tZOM[i].ucStatus & 0x0F))
       {
        if (NoError == ucGetLocatError (i))
        {
          PutLocatError ( (cMinCt4Dec < tZOM[i].ucToothTelCt) ? AmbigWP:TooFewPalTels , i);
        }
      }
      else
      {
        PutLocatError ( NoError, i);
      }
      zomSlot2Chk &= ~(1<<i);
    }
    if (zomSlot2Chk < 1 )
      i = cSumWE;
   }
}

static uint16 ui16NewIdFits(uint16 ushNewID, uint16 ushHistSet)
{
  uint8 ui8Tmp,i,ui8NewSlot = (uint8) 0,ui8NeWP = (uint8) 0;
  uint16 ui16Ret = 0;

  if ((ucNrOfBitSet (ushHistSet) == 3 ) && (ucNrOfBitSet (ushNewID) == 1 ))
   {
    for ( i = 0; i < cSumWE ; i++)
    {
      if ((ushNewID & (1<<i)) > 0)
      {
        ui8NeWP =  ucGetZOMWP (i);
        ui8NewSlot = i;
        break;
      }
    }

    if (cWheelPos_RR < ui8NeWP)
     {
      if (GETuCorWPofSlot(ui8NewSlot , &ui8NeWP , &ui8Tmp) > 0)
       {
         for ( i = 0; i < cSumWE ; i++)
           if (( i != ui8NewSlot ) && ((ushHistSet & (1<<i)) > 0) )
            if ((tZOM[i].ucStatus & 0x0F) == ui8NeWP)
              break;
      }
      else
      {
        i = cSumWE;
      }
    }
    else
    {
      for ( i = 0; i < cSumWE ; i++)
         if (( i != ui8NewSlot ) && ((ushHistSet & (1<<i)) > 0) )
          if (ucGetZOMWP (i) == ui8NeWP)
            break;
    }

    if (cSumWE == i)
     {
      if (((uint8) 0 == tZOM[ui8NewSlot].ucToothTelCt ) && ((uint8) 0 == tZOM[ui8NewSlot].ucToothTelCtNoCorr ))
      {
        i = (uint8) 0;
      }
    }

    if (cSumWE == i)
     {
      ui16Ret = 1;
    }
  }

  return ( ui16Ret );
}

static uint8 ui8AnyHistIdMissing(void)
{
   uint8 i;

   for (i = 0; i < cMaxLR ; i++)
   {
      if (ucFindMissingHistoryIDs(&aulHistoryID[i],ucDefMinCt4HistER, cSumWE ) > ((unsigned char) 0) )
      {
         return ((uint8) 0xFF);
      }
   }

   return ((uint8) 0);
}

static unsigned short  ushLqiTribute(unsigned short ushCandidate)
{
  unsigned char i;

  for (i = 0; i < cSumWE; i++)
  {
    if (((1 << i) & ushCandidate) > 0)
    {
      if (ucGetZomLqi(i) <= ucDAG_LQIParameter())
       {
        ushCandidate &= (unsigned short)(~(1 << i));
      }
    }
  }
  return (ushCandidate);
}

#ifdef WAModulTest

void TESTPutDriveTimeInSec(unsigned short ushTimeInSec)
{
  ushDriveTimeInSec = ushTimeInSec;
}

void SetALState(uint8 ui8State)
{
  tWAPar .AL_State = ui8State;
}
#endif
