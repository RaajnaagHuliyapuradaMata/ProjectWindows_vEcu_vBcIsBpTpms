/*
*(c) Beru Electronics GmbH     BEE1     $JustDate: 25.09.12 $
*================================================================================================
*
*$Archive: /LIB/WAF/work/WAlloc.c $
*
*file status:   under construction
*
*------------------------------------------------------------------------------------------------
*
*author:        Peter Brand                Beru Electronics GmbH
*
*intials:       pb
*
*Modul Description
*
*Global description:
*Purpose:
*learn IDs of wheel electronics to Eigenräder
*allocate EIgenräder to wheel positions
*
*/

/************************************************************************************************************
*Declaration
*/

/*
preinclude macros
*/
#define WALLOC_INT

/************************************************************************************************************
*Include
*/
//#include "cfg.h"
#include "WallocX.h"
#include "Walloc_IF.h"
#include "walloc.h"
#include "AEC.h"
#include "FPA.h"
#include "tss_stdX.h"
//#include "WA_time_filter.h"

/************************************************************************************************************
*Macros
*
*/

#define cSLHistAssignTimeInSec 180 // 3min
#define cTIME_OUT   	      540 // 9 min 
#define cHistIDProtectTime  240 // 4 min 
#define c5MinDriveTimeInSec 300 // 5min 

#define cAll (uint8) 0
#define cLearnOnly (uint8) 1

/************************************************************************************************************
* prototypes
*/
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
static unsigned char ucNrOfLocatErrorAndPosForce(void); /*CRS_1211_090_001*/
static unsigned char ucNrOfLearnError(void);

static uint8 considerationeDiAssegnazioneCostretto(void);
static void dblCk4LocEr(void);
static uint16 ui16NewIdFits(uint16 ushNewID, uint16 ushHistSet);
static uint8 ui8AnyHistIdMissing(void);

static unsigned short  ushLqiTribute(unsigned short ushCandidate);

/************************************************************************************************************
*Data
*
*/

static const unsigned char ucWACtrlFixc = 0x01;
static const unsigned char ucWACtrlBreakc = 0x02;

static unsigned char ucWAState;
/* ucWAState : status of wheel identification and Eigen wheel detection :
MSB X 1 -> new ID at history column 3
    X 1 -> new ID at history column 2
    X 1 -> new ID at history column 1
    X 1 -> new ID at history column 0

    X 1 -> all actions are temporarily stopped / BREAK
    X 1 -> wheel position identification is finished -  4 w.p. are known
    X 1 -> eigen wheel finished - ER status - 4 Eigen wheel detected
LSB X 1 -> eigen wheel and wheel identification procedures are active */

static unsigned long aulHistoryID[cMaxLR];
static unsigned char aucHistoryWP[cMaxLR];
static unsigned char ucLearnError[cMaxLR] = {NoError,NoError,NoError,NoError};
static unsigned char ucLocatError[cMaxLR] = {NoError,NoError,NoError,NoError};
static unsigned char ucABSignalMissin = NoError ;

#define cWPER 0x10  /* wheel position ER */

static unsigned short ushDriveTimeInSec = 0;
static unsigned short ushDriveTimeOverPalMax = 0;
static unsigned char ucLearnMode = cNoLearn;
static unsigned char ucWAStateHi = 0; // see below:
/* ucWAStateHi : status of wheel identification and Eigen wheel detection high byte:
MSB X 1 -> new WP at history column 3
    X 1 -> new WP at history column 2
    X 1 -> new WP at history column 1
    X 1 -> new WP at history column 0

    X 1 -> 1 ZO Forced   
    X 1 -> 1 TZG (partially WPs allocated)
    X 1 -> 1 TO
LSB X 1 -> 1 error active */
static unsigned char ucDAGLearnState = Autolearn_Learning ;

static unsigned char aucWPorPWP[cMaxLR] = {4,4,4,4};  // contains history column indexed WP or PWP if WP is unknown, content is generated immediately before access
/************************************************************************************************************
*Implementation
*/

/************************************************************************************************************
*private functions
*/
// ________________________________common auxilliary__________________________________________________________START
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
// ________________________________common auxilliary____________________________________________________________END

//______________________________________private module's data access__________________________________________START

static void SetWAStateZOChange(unsigned char ucChangedPos)
{
  ucWAState &= 0x0F;
  ucWAState |= (unsigned char) ((ucChangedPos&0x0F)<<4);  // changed IDs

  ucWAStateHi &= 0x0F;
  ucWAStateHi |= (unsigned char) (ucChangedPos&0xF0);     // changed WPs
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

//______________________________________private  data access___________________________________________________END
//______________________________________private  control_____________________________________________________START
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
/************************************************************************************************//**
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
          //ClearZOM(j);
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
  unsigned char i, ucMinIx = cSumWE;  // no minimum per default

  for( i = 0; i < cSumWE; i++)  // find 1st none exceptional ID
  {
    if (((0x01<<i) & ushException) == 0)  // no exception ?
    {
      ucMinIx = i;
      break;  // FIX 
    }
  }
  for( i = (ucMinIx + 1); i < cSumWE; i++)
  {
    if (((0x01<<i) & ushException) == 0)  // no exception ?
    {
      if (tZOM[i].ucTelCtLearnBit < tZOM[ucMinIx ].ucTelCtLearnBit)
      {
        ucMinIx = i;
      }
    }
  }
  return( ucMinIx );
}

/************************************************************************************************//**
                                                                                                  * \brief  checks whether a specific wheel position is already set in the history
                                                                                                  *
                                                                                                  *-----------------------------------------------------------------------------------------------
                                                                                                  * \param [in] p2HistoryWP pointr to  array containing wheel position
                                                                                                  * \param [in] ucWP wheel position of interest
                                                                                                  *
                                                                                                  * \return	- 1  True
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
/************************************************************************************************//**
                                                                                                  * \brief  checks whether all prelearned IDs have been received at least once
                                                                                                  *
                                                                                                  *-----------------------------------------------------------------------------------------------
                                                                                                  * \param [in] none
                                                                                                  * \param [out] none
                                                                                                  *
                                                                                                  * \return	- 1  True
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

/************************************************************************************************//**
                                                                                                  * \brief  checks ID set to ERstate based on amount of receive events
                                                                                                  *
                                                                                                  *-----------------------------------------------------------------------------------------------
                                                                                                  * \param [in] ucMinCt minimum number of events
                                                                                                  * \param [in] aulHistoryID  Global static array containing Wheel IDs
                                                                                                  *
                                                                                                  * \return	- 1  means set of IDs is in ERstate
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

/************************************************************************************************//**
                                                                                                  * \brief  identifies wheel position based on turning direction and axis position
                                                                                                  *
                                                                                                  *-----------------------------------------------------------------------------------------------
                                                                                                  * \param [in] *ptInputWA pointer to telegramm buffer
                                                                                                  * \param [in] ucID Sensor position in ZOM  
                                                                                                  *
                                                                                                  * \return	1 means wheel positions identified
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
#endif  //AEC
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
#endif //FPA
#ifdef AEC
  if  (ucDirectionDetection((unsigned char) 1) == 0x0F)   /* all wheel sensor's spinning direction detected ? */
  { // AEC and CA sensors come in here
#ifdef CONCEPT4
    if (((tZOM[ucID].ucStatus & 0x30) == 0) && (ptInputWA->Header .ucTType == cTelTypeEdgeCnt)) /* axxis not yet detected ? */
      Concept4Op2(ucID,ushGetTruECt(ptInputWA,ucID) );
#endif
    if (ucAxisDetection() == 1) /* axis detected ? */
    {
      if (ucWPConsistent() == 1)  /* consistency check of WP */
      {
        /* calculate wheel positions  */
        if (ucSetWP() == 1) /* WPs set correctly ? */
        {
          ucRet = 1;  /* all directions identified */
        }
        else
        {
          /* ERROR while trying to set the wheel position */
          ResetAxis();
        }
      }
      else
      { /* non constistent axis and wheel pos constellation */
        ResetAxis();
      }
    }
  }
  else
  {
    if (ucRet == 0) // if FixPosAlloction (FPA) did succeed, do not reset WPs here !!!
      ResetWP();  /* spinning direction not detectable */
  }
#endif
  return((unsigned char) ucRet);
}

/************************************************************************************************//**
                                                                                                  * \brief  checks ID set to ERstate based on amount of receive events
                                                                                                  *
                                                                                                  *-----------------------------------------------------------------------------------------------
                                                                                                  * \param [in] *ptHistSet pointer to wheel position indexed ID history
                                                                                                  * \param [in] ucMinProbeCt level over that ZOM IDs are accepted to be awar
                                                                                                  * \param [in] ucSlots2Search amount of ZOM slots to check (start a index 0 to cSumWE) 
                                                                                                  *
                                                                                                  * \return	Bit n is set if slot n in ZOM has >= ucMinProbeCt probe counts and is part of history
                                                                                                  * is 0 if not cMaxLR Bits are set or an 0 IDs are in history
                                                                                                  *
                                                                                                  *------------------------------------------------------------------------------------------------
                                                                                                  */
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


/************************************************************************************************//**
                                                                                                  * \brief  checks ID set to ERstate based on amount of receive telegramms in learn mode
                                                                                                  *
                                                                                                  *-----------------------------------------------------------------------------------------------
                                                                                                  * \param [in] *ptHistSet pointer to wheel position indexed ID history
                                                                                                  * \param [in] ucMinProbeCt level over that ZOM IDs are accepted to be awar
                                                                                                  * \param [in] ucSlots2Search amount of ZOM slots to check (start a index 0 to cSumWE) 
                                                                                                  *
                                                                                                  * \return	Bit n is set if slot n in ZOM has >= ucMinProbeCt probe counts and is part of history
                                                                                                  * is 0 if not cMaxLR Bits are set or an 0 IDs are in history
                                                                                                  *
                                                                                                  *------------------------------------------------------------------------------------------------
                                                                                                  */
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


/************************************************************************************************//**
                                                                                                  * \brief  write spin direction to ZOM
                                                                                                  *
                                                                                                  *-----------------------------------------------------------------------------------------------
                                                                                                  * \param [in] *ptInputWA pointer to telegramm buffer
                                                                                                  * \param [in] ucIx Sensor position in ZOM
                                                                                                  * \param [out] tZOM Global ZOM structure
                                                                                                  *
                                                                                                  * \return	none
                                                                                                  *
                                                                                                  *------------------------------------------------------------------------------------------------
                                                                                                  */
static void Put2Slot(tRFTelType *ptInputWA, unsigned char ucIx)
{
  unsigned char ucSpin = (unsigned char) 0;

  if (ucIx < cSumWE) /* index check */
  {
    tZOM[ucIx].ulID = ptInputWA->EdgeCnt.ulID;   // for this might be the very 1st access (it's easier than 2 compare 1st)

    if ( (tZOM[ucIx].ucProbeCt < (unsigned char) 255) &&                // ALL TYPE COMMON: ProbeCt and RssiSum overflow protection
      ((tZOM[ucIx].ushRssiSum + (unsigned short) ptInputWA->Struc .ucAvg) >= tZOM[ucIx].ushRssiSum) )
    {
      tZOM[ucIx].ushRssiSum += (unsigned short) ptInputWA->Struc .ucAvg;
      tZOM[ucIx].ucProbeCt++;
    }

    if( (cTelTypeSELPAL1== ptInputWA->Header.ucTType) || ( cTelTypeAK35defLMA == ptInputWA->Header.ucTType))
    {
      tZOM[ucIx].ucTelCtLearnBit++;
    }

    if ( (cTelTypeSELPAL  == (ptInputWA->Header.ucTType&0x0F)) ) // PAL
    {
      /* update the frame counter of PAL telegramm */
      tZOM[ucIx].ucFrameCounter = (unsigned char)((ptInputWA->SchraderFP.ushStatusField>>8)&0x1F);

      if (ptInputWA->SchraderFP.ucPAL == 0x0){	// no PAL data
#ifdef Test_LOG_ENABLE
        tZOM[ucIx].ucToothTelCtNoLearnMode++;     // update counters
#endif
      }
      else if (ptInputWA->SchraderFP.ucPAL == 0x01){  // no Correlation
#ifdef Test_LOG_ENABLE
        tZOM[ucIx].ucToothTelCtNoCorr++;    // update counters
#endif
      }
      else if (ptInputWA->SchraderFP.ucPAL == 0xFF){  // overflow
#ifdef Test_LOG_ENABLE
        tZOM[ucIx].ucToothTelCtNoCorr++;    // update counters
#endif
      }
      else{
#ifdef Test_LOG_ENABLE
        if ((ptInputWA->Header .ucTType & 0x20) == 0x20) // check learn bit
          tZOM[ucIx].ucToothTelCtCorrLearnBit++;
        else
          tZOM[ucIx].ucToothTelCtCorrNoLearnBit++;	
#endif
      }
    }
    else if (cTelTypePeak == ptInputWA->Header.ucTType)                  // PEAK
    {
#ifdef AEC
      tZOM[ucIx].ushXPSum++;
#endif
#ifdef Test_LOG_ENABLE
                tZOM[ucIx].ucToothTelCtNoLearnMode++;     // update counters
#endif
    }
    else if (cTelTypeAK35def == ptInputWA->Header.ucTType)          // AKdef
    {
#ifdef Test_LOG_ENABLE
      tZOM[ucIx].ucToothTelCtNoLearnMode++;    // update counters
#endif
    }
    else if ( cTelTypeEdgeCnt == ptInputWA->Header.ucTType )        // EdgeCnt
    {   // EdgeCnt
      ucSpin = ptInputWA->EdgeCnt.ucSpin;
#ifdef CONCEPT4
      /* start time recognition */
      if (tZOM[ucIx].ushStarTi == 0)  /* 1st access */
      { /* YES */
        tZOM[ucIx].ushStarTi = ptInputWA->Struc.ushTimeStamp; /* start time is this */
        tZOM[ucIx].ushLogTime = ptInputWA->Struc.ushTimeStamp;
        tZOM[ucIx].ucStarTiHi = (unsigned char) 0;
        //tZOM[ucIx].ucXPEvCt = 0;
        //tZOM[ucIx].ucZPEvCt = 0;
      }
      else
      { // recognize current EdgCt times and overflows
        if (ptInputWA->Struc.ushTimeStamp < tZOM[ucIx].ushLogTime)
          tZOM[ucIx].ucStarTiHi +=1;
        tZOM[ucIx].ushLogTime = ptInputWA->Struc.ushTimeStamp;
      }
#endif
      // ABS ticks are saved in ushGeTrueDECt
#ifdef Test_LOG_ENABLE
                tZOM[ucIx].ucToothTelCtNoLearnMode++;     // update counters
#endif
    }
    else if(cTelTypeAK35BeruMed == ptInputWA->Header.ucTType)       // MED
    {
      ucSpin = ptInputWA->AK35BeruMed .ucSpinDir;
#ifdef AEC
      if ( ucEarlyEnd(ucIx) > 0 )
        StartWATO( 1 ); // WATO will be soon...
#endif
#ifdef Test_LOG_ENABLE
                tZOM[ucIx].ucToothTelCtNoLearnMode++;     // update counters
#endif
    }
    else if(cTelTypeAK35BeruL == ptInputWA->Header.ucTType)         // LONG
    {
      ucSpin = ptInputWA->AK35BeruL  .ucSpinDir;
#ifdef Test_LOG_ENABLE
                tZOM[ucIx].ucToothTelCtNoLearnMode++;     // update counters
#endif
    }
    else if(cTelTypeAK35BeruS  == ptInputWA->Header.ucTType)        // SHORT
    {
      ucSpin = ptInputWA->AK35BeruS  .ucSpinDir;
#ifdef Test_LOG_ENABLE
          tZOM[ucIx].ucToothTelCtNoLearnMode++;     // update counters
#endif
        }else
        {
#ifdef Test_LOG_ENABLE
          // we will receive here answers to LR commandos
          tZOM[ucIx].ucToothTelCtNoLearnMode++;     // update counters
#endif
    }

    if( (ucSpin > 0) &&                                                     // wind up spin counters...
      (tZOM[ucIx].ucLeftCt  < (unsigned char) 255) &&                                                       /* OIL_L7 #074 *//* OIL_L7 #146 */
      (tZOM[ucIx].ucRightCt < (unsigned char) 255)    )                                                     /* OIL_L7 #074 *//* OIL_L7 #146 */
    {                                                                                                         /* OIL_L7 #074 *//* OIL_L7 #146 */
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

/************************************************************************************************//**
                                                                                                  * \brief  collects ID data essential for WA in dependence of WE status
                                                                                                  *
                                                                                                  *-----------------------------------------------------------------------------------------------
                                                                                                  * \param [in] *ptInputWA pointer to telegramm buffer
                                                                                                  * \param [in] *tWAPar Pointer to global structure containing wheel allocation parameters
                                                                                                  * \param [in] aulHistoryID Global static array containing Wheel IDs
                                                                                                  *
                                                                                                  * \return	- 1 = ZOM data changed
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
  return(ucIx); //  returns Index of Current ID
}

// ucSetHistory purpose:
// saves current ZOM content (1st 4 slots) to history ( NVM ) under consideration of some rules
// parameter : type = cWAStateER -> wr w/o WPs only IDs
//             type = cWAStateZG -> wr w/ WPs and IDs
// return:
// MSB 
//  x = 1 -> new WP at history column 3 (also set if ID at this slot is new but WP remains)
//  x = 1 -> new WP at history column 2 (also set if ID at this slot is new but WP remains)
//  x = 1 -> new WP at history column 1 (also set if ID at this slot is new but WP remains)
//  x = 1 -> new WP at history column 0 (also set if ID at this slot is new but WP remains)
//
//  x = 1 -> new ID at history column 3
//  x = 1 -> new ID at history column 2
//  x = 1 -> new ID at history column 1
//  x = 1 -> new ID at history column 0
// LSB
unsigned char ucSetHistory(unsigned char ucType, unsigned char ucVZS)
{
  unsigned char i,j,ucNrUK,ucNew,ucRet = 0x0f, ucChangedHistSlots = 0; /* no position has been changed by default , all ids have been changed (low nibble bits indicate !ZOM slots! w/ new IDs)*/

  GetWADataEE(cHistorySet1, (unsigned char *) aulHistoryID, (unsigned char) sizeof(aulHistoryID) );
  GetWADataEE(cHistoryWPSet1, aucHistoryWP, (unsigned char) sizeof(aucHistoryWP) );

  ucNew = ucCmpHist2ZOMID(ucVZS);
  ucNrUK = ucNrOfUKWPinZOM();
 
  if ( (((unsigned char) 0) == ucNrOfBitSet ((unsigned short) ucNew) ) && (ucNrUK > ucNrOfUKWPinHist ()) && !((((uint8) 1) ==  ucNrUK) && (ui8AnyHistIdMissing () == ((uint8) 0)))  ) //  same history wheel set and fewer WPs ?
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
            if ( cMaxLR > ucNrUK )  // for this WP is already present at other Hist slot
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

  if (1 < ucNrOfBitSet((unsigned short) (ucRet & 0x0F)))  // set new ID's WPs to UK (4 only 1 new ID the WP remains)
  {
    if ( ucWACtrlFixc == tWAPar.ucWACtrl ) // Pal overide configured?
    {/* Autolocation overide is disabled when more than one new sensor is learnt */
      tWAPar.ucWACtrl = ucDefWACtrl;
      ucWAState &= (unsigned char) ~(cWAStateZO); /* ZG can be definetly reset */
      PutWADataEE(cWAParameter, (unsigned char *) &tWAPar , (unsigned char) sizeof(WAParameter));
    }
  }

  if (ucRet > 0)  /* any changes detected ? */
  {
    for (i = 0; i < cMaxLR; i++)  /* write history new */
    {
      if ((ucRet & (0x01 << i)) > 0)  /* new ZOM ID ?*/
      {
        ucNrUK = ucGetColOfWP(ucGetZOMWP(i));  
        if ((ucGetZOMWP(i) <= cWheelPos_RR  )  && ((ucNew & ((1<<ucNrUK)&0x0F)) > 0)) // w/ WP ? AND // WP already exists in History and to be replaced ?
        {
          aulHistoryID[ucNrUK] = ulGetZOMID(i);
          ucNew &= (unsigned char) (~(unsigned char) (1 << ucNrUK));  /* not any longer old */
          ucChangedHistSlots |= (unsigned char) (1 << ucNrUK);       
        }
        else
        {
          for ( j = 0; j < cMaxLR; j++) /* check history 4 old IDs */
          {
            if ((ucNew & ((unsigned char) (1 << j))) > 0)  /* old history ID (to be replaced) ?*/
            {	  /* replace by new one */
              aulHistoryID[j] = ulGetZOMID(i);
              ucNew &= (unsigned char) (~(unsigned char) (1 << j));  /* not any longer old */
              ucChangedHistSlots |= (unsigned char) (1 << j);
              if ((0 < ucNrOfBitSet((unsigned short) (ucRet & 0x0F)))||(ucNrOfUKWPinHist() > 0))  // set new ID's WPs to UK (4 only 1 new ID the WP does not remain anymoore..)
              {
                  aucHistoryWP[j] = 4;
                  ucRet |= (unsigned char) (0x10 << j); /* new wheel position at this history ID */
              }
              if (cWAStateZO == ucType)
              {
                if ((ucGetZOMWP(i) <= cWheelPos_RR ) && (aucHistoryWP[j] != ucGetZOMWP(i)))  /* change position ? */
                {
                  if ( cMaxLR > ucNrUK )  // for this WP is already present at other Hist slot
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

/************************************************************************************************//**
                                                                                                  * \brief  sets the WA state saved in the history to current state in dependency of ER state
                                                                                                  *          WARNING: if ER state is reached the content of the ZOM will be respected
                                                                                                  *
                                                                                                  *-----------------------------------------------------------------------------------------------
                                                                                                  * \param [inout] ucWAState Global static variable containing the WA status
                                                                                                  * \param [in] aulHistoryID Global static array containing Wheel IDs
                                                                                                  * \param [in] aucHistoryWP Global static array containing Wheel positions
                                                                                                  *
                                                                                                  * \return	none
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

    if (ucCt < cMaxLR) /* all wheel positions taken over ? */
    { /* no */
      for ( i = 0; i < cMaxLR; i++) /* clear wheel position informations */
      {
        SetZOMWP(i, cWPER);
      }
    }
    else
    { /* yes */
      ucWAState |= cWAStateZO;
    }
  }
}


//______________________________________private  control______________________________________________________END


//___________________________public data access_____________________________________________________________START

/************************************************************************************************//**
                                                                                                  * \brief get ZOM position of wheel sensor
                                                                                                  *
                                                                                                  *-----------------------------------------------------------------------------------------------
                                                                                                  * \param [in] *pt2ID Pointer to sensor ID
                                                                                                  * \param [in] tZOM Global ZOM structure
                                                                                                  *
                                                                                                  * \return ZOM position of wheel sensor
                                                                                                  *
                                                                                                  *------------------------------------------------------------------------------------------------
                                                                                                  */
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

/************************************************************************************************//**
                                                                                                  * \brief get ZOM  Frame Counter (in PAL)
                                                                                                  *
                                                                                                  *-----------------------------------------------------------------------------------------------
                                                                                                  * \param [in] *pt2ID Pointer to sensor ID
                                                                                                  * \param [in] tZOM Global ZOM structure
                                                                                                  *
                                                                                                  * \return ZOM position of wheel sensor
                                                                                                  *
                                                                                                  *------------------------------------------------------------------------------------------------
                                                                                                  */
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

/************************************************************************************************//**
                                                                                                  * \brief set wheel position in ZOM
                                                                                                  *
                                                                                                  *-----------------------------------------------------------------------------------------------
                                                                                                  * \param [in] ucIdx Sensor position in ZOM range [0 cMaxLR]
                                                                                                  * \param [in] ucWP Wheel position
                                                                                                  * \param [out] tZOM Global ZOM structure
                                                                                                  *
                                                                                                  * \return none
                                                                                                  *
                                                                                                  *------------------------------------------------------------------------------------------------
                                                                                                  */
void SetZOMWP(unsigned char ucIx,unsigned char ucWP)
{
  if (ucIx < cSumWE)
  {
    tZOM[ucIx].ucStatus &= cNoWPos; /* clear WP */
    if (ucWP < cMaxLR)  /* valid WP ? */
    {
      tZOM[ucIx].ucStatus |= (unsigned char) (0x01 << ucWP);
    }
  }
}


/************************************************************************************************//**
                                                                                                  * \brief gets ID of wheel sensor in ZOM
                                                                                                  *
                                                                                                  *-----------------------------------------------------------------------------------------------
                                                                                                  * \param [in] ucIdx Sensor position in ZOM range [0 cSumWE]
                                                                                                  * \param [in] tZOM Global ZOM structure
                                                                                                  *
                                                                                                  * \return wheel sensor ID
                                                                                                  *
                                                                                                  *------------------------------------------------------------------------------------------------
                                                                                                  */
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

/************************************************************************************************//**
                                                                                                  * \brief  gets ID in ZOM
                                                                                                  *
                                                                                                  *-----------------------------------------------------------------------------------------------
                                                                                                  * \param [in] ucIx column range [0 cMaxLR]
                                                                                                  * \param [in] aulHistoryID Global static array containing Wheel IDs
                                                                                                  * 
                                                                                                  * \return wheel sensor ID
                                                                                                  *
                                                                                                  *------------------------------------------------------------------------------------------------
                                                                                                  */
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

/************************************************************************************************//**
                                                                                                  * \brief  gets column of ID
                                                                                                  *
                                                                                                  *-----------------------------------------------------------------------------------------------
                                                                                                  * \param [in] *pt2ID Pointer to sensor ID
                                                                                                  * \param [in] aulHistoryID Global static array containing Wheel IDs
                                                                                                  * 
                                                                                                  * \return column in ZOM
                                                                                                  *
                                                                                                  *------------------------------------------------------------------------------------------------
                                                                                                  */
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

/************************************************************************************************//**
                                                                                                  * \brief  gets wheel position of colunm
                                                                                                  *
                                                                                                  *-----------------------------------------------------------------------------------------------
                                                                                                  * \param [in] ucIx Pointer to an WA parameters structure
                                                                                                  * \param [in] aucHistoryWP Global static array containing Wheel positions
                                                                                                  * 
                                                                                                  * \return wheel position
                                                                                                  *
                                                                                                  *------------------------------------------------------------------------------------------------
                                                                                                  */
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

/************************************************************************************************//**
* \brief  gets column of wheel position
*
*-----------------------------------------------------------------------------------------------
* \param [in] ucIx wheel position
* \param [in] aucHistoryWP Global static array containing Wheel positions
* 
* \return wheel position
*
*------------------------------------------------------------------------------------------------*/
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


/************************************************************************************************//**
                                                                                                  * \brief  saves 1 or a set of 4 ids with wheel position to the history set
                                                                                                  *
                                                                                                  *-----------------------------------------------------------------------------------------------
                                                                                                  * \param [in] pt2ID Pointer to an array of 4 ul IDs or 1 ul ID [1,2,..,2^32]
                                                                                                  * \param [in] pt2Pos points to an array of 4 uc WPs or 1 uc WP [0,1,2,3], WP 4 and >8 will be rejected,
                                                                                                  *				WP[5..8] are interprated as history index
                                                                                                  * \param [in] ucSum  conatains the amount of ids to be saved [1,4]
                                                                                                  * \param [inout] aulHistoryID Global static array containing Wheel IDs
                                                                                                  * \param [inout] aucHistoryWP Global static array containing Wheel positions
                                                                                                  * \param [out] ucWAState Global static variable containing the WA status
                                                                                                  * \param [out] tZOM Global ZOM structure
                                                                                                  *
                                                                                                  * \return ucRet Bit indexed information of changed ZOMpos and WP coded as follows:
                                                                                                  *         - MSB 
                                                                                                  * 				 - x ->  ID at ZOMpos 3d has been replaced
                                                                                                  *               - x ->  ID at ZOMpos 2d has been replaced             HI-NIBBLE
                                                                                                  *               - x ->  ID at ZOMpos 1d has been replaced
                                                                                                  *               - x ->  ID at ZOMpos 0d has been replaced
                                                                                                  *
                                                                                                  *               - x ->  WP RR has been allocated to an other ID
                                                                                                  *               - x ->  ID RL has been allocated to an other ID       LO-NIBBLE
                                                                                                  *               - x ->  ID FR has been allocated to an other ID
                                                                                                  *               - x ->  ID FL has been allocated to an other ID
                                                                                                  *			- LSB 
                                                                                                  *
                                                                                                  *------------------------------------------------------------------------------------------------
                                                                                                  */
unsigned char ucSetID(unsigned long *pt2ID, unsigned char *pt2Pos, unsigned char ucSum)
{
  unsigned char i, j, ucRet = 0, ucHelp;
  unsigned long ulBufID;

  ucSum = (ucSum > cMaxLR) ? cMaxLR:ucSum;

  if (pt2ID[0] == (unsigned long) 0)  /* clear history ? */
  {
    for ( i = 0; i < cMaxLR; i++)
    {
      aulHistoryID[i] = 0;
      aucHistoryWP[i] = 4;
    }
    PutWADataEE(cHistorySet1, (unsigned char *) aulHistoryID, (unsigned char) sizeof(aulHistoryID));  /* write history to eeprom */
    PutWADataEE(cHistoryWPSet1, aucHistoryWP, (unsigned char) sizeof(aucHistoryWP));  /* write history WP to eeprom */
    (void) WAInit((WAParNCfgType *) &ucLearnMode );
    ucRet = 0x0F; /* all IDs changed */
  }
  else
  {
    GetWADataEE(cHistorySet1, (unsigned char *) aulHistoryID, (unsigned char) sizeof(aulHistoryID));  /* actualize history from eeprom */
    GetWADataEE(cHistoryWPSet1, aucHistoryWP, (unsigned char) sizeof(aucHistoryWP));
    if ((aulHistoryID[0] == 0) && (ucSum == 1)) /* history empty and only 1 ID to write ? */
    { /* fill history with fantasy values */
      for (i = 0; i < cMaxLR; i++)
      {
        aulHistoryID[i] = i + 1;  /* write fantasy IDs to History */
        if ( pt2Pos[0] > 3 ) /* no valid WP ? */
        {
          aucHistoryWP[i] = 4; /* set WP 2 unknown */
        }
        else
        {
          aucHistoryWP[i] = i;
        }
      }
    }
    /* writing to history allowed */
    ucHelp = 0x0f;  /* classify all history IDs as OLD by default */
    for (i = 0; i < ucSum; i++)   /* process all ids */
    {
      for (j = 0; j < cMaxLR; j++)  /* check all history ids */
      {
        if (pt2ID[i] == aulHistoryID[j]) /* ID 2 write already in history ? */
        {
          ucHelp &= (unsigned char) (~(unsigned char) (0x01 << j));
          break;  /* for same ID is 2 write this history ID is not old anymore */
        }
      }
    }
    /* ucHelp low nibble now contains bit indexed old history ID positions, ie. ucHelp = 0x03 means ID at
    aulHistoryID[0] and aulHistoryID[1] are old ones */
    for (i = 0; i < ucSum; i++)   /* process all IDs */
    {
      for (j = 0; j < cMaxLR; j++)  /* check all history IDs */
      {
        if (pt2ID[i] == aulHistoryID[j])  /* id to set already in history ? */
        {
          break;  /* id found */
        }
      }
      pt2Pos[i] = (pt2Pos[i] < (unsigned char) 9) ? pt2Pos[i]:4;  /* no valid WP parameter is set to spare tyre */
      if (j == cMaxLR)  /* new id ? */
      { /* new id */
        if ( pt2Pos[i] > cWheelPos_RR) /* write unknown WP to defined index pos */
        {
          if ( pt2Pos[i] == (unsigned char) 4 )  /* spare tyre position ? */
          { /* reject spare tyre WP strictly ! */
            ucRet = 0;  /* no success */
            i = ucSum;  /* leave loop and function immediately */
          }
          else
          {
            ucHelp = pt2Pos[i] - (unsigned char) 5;
            aulHistoryID[ucHelp] = pt2ID[i];
            aucHistoryWP[ucHelp] = (unsigned char) 4;
            ucRet |= (0x10 << ucHelp);
            ucWAState &= (unsigned char) ~(cWAStateZO); /* ZG can be definetly reset */
          }
        }
        else
        {
          for (j = 0; j < cMaxLR; j++)  /* find history id with matching wheel pos */
          {
            if (pt2Pos[i] == aucHistoryWP[j])  /* WP to set already in history ? */
            {
              break;  /* WP found */
            }
          }
          if ( j == cMaxLR )  /* WP NOT found in history ? */
          {
            for (j = 0; j < cMaxLR; j++)  /* replace next old history ID */
            {
              if ((ucHelp & (unsigned char)(0x01 << j)) > 0)
              {
                ucHelp =  (unsigned char) (ucHelp & (unsigned char) ~((unsigned char) (0x01 << j)));
                /* thank MISRA for that above which was once simply: ucHelp &= ~(0x01 << j); */
                break;
              }
            }
          }
          /* WP or old ID found in history - replace old ID with new one */
          ulBufID = aulHistoryID[j];
          aulHistoryID[j] = pt2ID[i]; /* setze in ZOM wenn ZO */
          aucHistoryWP[j] = pt2Pos[i];

          if ((ucWAState & cWAStateZO) == cWAStateZO)
          {
            ucHelp = ucGetZOMPosOfID(&ulBufID);
            tZOM[ucHelp].ulID = pt2ID[i];  /* update ZOM with new ID */
            SetZOMWP(ucHelp, pt2Pos[i]);
            ucRet |= (1 << ucHelp); /* ZOMPos changed */
          }
          else
          { /* notice zompos to safe in history later on */
            ucRet |= (1 << pt2Pos[i]);
          }
        }
      }
      else
      { /* id known at History[j] */
        if (aucHistoryWP[j] == pt2Pos[i]) /* WP changed ? */
        { /* no: same WP */

        }
        else
        { /* WP changed */
          if ( pt2Pos[i] > cWheelPos_RR) /* write unknown WP to defined index pos */
          {
            if ( pt2Pos[i] == (unsigned char) 4 )  /* spare tyre position ? */
            { /* reject spare tyre WP strictly ! */
              ucRet = 0;  /* no success */
              i = ucSum;  /* leave loop and function immediately */
            }
            else
            {
              aulHistoryID[j] = (unsigned long) i + 1;  /* clear same ID at maybe other history index */
              aucHistoryWP[j] = (unsigned char) 4;
              ucHelp = pt2Pos[i] - (unsigned char) 5;
              aulHistoryID[ucHelp] = pt2ID[i];
              aucHistoryWP[ucHelp] = (unsigned char) 4;
              ucRet |= (0x10 << ucHelp);
              ucWAState &= (unsigned char) ~(cWAStateZO);  /* ZG can be definetly reset */
            }
          }
          else
          {
            ucHelp = j;
            for (j = 0; j < cMaxLR; j++)  /* find history id with same wheel pos */
            {
              if (pt2Pos[i] == aucHistoryWP[j])  /* WP to set already in history ? */
              {
                aucHistoryWP[j] = aucHistoryWP[ucHelp];  /* change WP */
                break;  /* WP found */
              }
            }
            aucHistoryWP[ucHelp] = pt2Pos[i];
            if ((ucWAState & cWAStateZO) == cWAStateZO)
            {
              SetZOMWP(j, aucHistoryWP[j]);
              SetZOMWP(ucHelp, pt2Pos[i]);
              ucRet |= (unsigned char) (0x10 << pt2Pos[i]);  /* 2 WPs changed */
              ucRet |= (unsigned char) (0x10 << aucHistoryWP[j]);
            }
            else
            { /* notice zompos to safe in history later on */
              ucRet |= (unsigned char) (1 << pt2Pos[i]);
            }
          }
        }
      }
    }
    if (ucRet > 0)  /* any changes in history */
    { /* yes */
      PutWADataEE(cHistorySet1, (unsigned char *) aulHistoryID, (unsigned char) sizeof(aulHistoryID)); /* actualize history from eeprom */
      PutWADataEE(cHistoryWPSet1, aucHistoryWP, (unsigned char) sizeof(aucHistoryWP)); /* WPs also */
    }

    if ((ucWAState & cWAStateZO) == 0)
    {
      (void) WAInit((WAParNCfgType *) &ucLearnMode);
      ucRet = 0x0f; /* all WPs and all IDs changed */
    }
  }
  return (ucRet);
}


/************************************************************************************************//**
                                                                                                  * \brief returns history's state
                                                                                                  *
                                                                                                  *-----------------------------------------------------------------------------------------------
                                                                                                  * \param [in] aulHistoryID Global static array containing Wheel IDs
                                                                                                  * \param [in] aucHistoryWP Global static array containing Wheel positions
                                                                                                  *
                                                                                                  * \return ucRet History state
                                                                                                  *          - 0 - No ER, No ZG
                                                                                                  *          - 1 - ER, no ZG
                                                                                                  *          - 3 - ER, ZG
                                                                                                  *
                                                                                                  *------------------------------------------------------------------------------------------------
                                                                                                  */
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

/************************************************************************************************//**
                                                                                                  * \brief checks if ER state has been already reached
                                                                                                  *
                                                                                                  *-----------------------------------------------------------------------------------------------
                                                                                                  * \param [inout] ucWAState Global static variable containing the WA status
                                                                                                  *
                                                                                                  * \return tbd  1 --> yes 0 --> no
                                                                                                  *
                                                                                                  *------------------------------------------------------------------------------------------------
                                                                                                  */
unsigned char ucGetERState(void)
{
  return( ((ucWAState & cWAStateER) == cWAStateER) ? (unsigned char) 1:(unsigned char) 0);
}
//___________________________public data access_______________________________________________________________END


// ___________________________________public control________________________________________________________START

/************************************************************************************************//**
                                                                                                  * \brief counts IDs in ZOM with >=ucMinCt ProbeCts and >= ucMinRssi MeanRssi value
                                                                                                  *
                                                                                                  *-----------------------------------------------------------------------------------------------
                                                                                                  * \param [in] ucMinCt Minimum amount of occurrence
                                                                                                  * \param [in] ucMinRssi GL: Tbd  Minimum RSSI
                                                                                                  * \param [out] *ushRet Pointer to bitmask (range:0..0xFFFF = bit n is set if ID in ZOM slot fullfills conditions)
                                                                                                  *
                                                                                                  * \return ucCt amount of IDs fullfilling the condition
                                                                                                  *
                                                                                                  *------------------------------------------------------------------------------------------------
                                                                                                  */
unsigned char ucSumCtID(unsigned char ucMinCt, unsigned short *ushRet)
{
  unsigned char i, ucCt= 0;
  *ushRet = 0;
  for ( i = 0; i < cSumWE; i++) /* check complete ZOM */
  {
    if (ucGetZomTelCtLearnBit(i) >= ucMinCt  ) /* conditions fullfilled reached ? */
    {
      ucCt++;
      *ushRet |= (unsigned short) (1 << i);  /* set ZOM slot corresponding bit */
    }
  }
  return(ucCt);
}

//\brief collects ID data and reviews ZOM state for ERstate and wheel allocation
//
//----------------------------------------------------------------------------------------------
//\param [in] *ptInputWA pointer to telegramm buffer
//\param [in] tWAPar Global structure containing wheel allocation parameters
//\param [inout] ucWAState Global static variable containing the WA status
//
//\return  ushWAstatus:
// ucWAState : status of wheel identification and Eigen wheel detection :
//
//HighByte:
//MSB X 1 -> new WP at history column 3
//    X 1 -> new WP at history column 2
//    X 1 -> new WP at history column 1
//    X 1 -> new WP at history column 0
//
//    X 1 ->   
//    X 1 -> 1 TZG (partially WPs allocated)
//    X 1 -> 1 TO
//LSB X 1 -> 1 error active 
//
//LowByte:
//MSB X 1 -> new ID at history column 3
//    X 1 -> new ID at history column 2
//    X 1 -> new ID at history column 1
//    X 1 -> new ID at history column 0
//
//    X 1 -> all actions are temporarily stopped / BREAK
//    X 1 -> wheel position identification is finished -  4 w.p. are known
//    X 1 -> eigen wheel finished - ER status - 4 Eigen wheel detected
//LSB X 1 -> eigen wheel and wheel identification procedures are active 


unsigned short ushLearnID(tRFTelType * ptInputWA)
{
  unsigned short ushRet;
  ucWAStateHi &= 0x0F;  // reset change info
  ucWAState &= 0x0F;
  ushRet = GETushWAState();

  if ((unsigned char) 0 < ucPasSupplFilter(ptInputWA ) ) // NOT only Huf and Schrader IDs are supported
  {
    if (!(((ucWAState & cWAStateZO) == cWAStateZO) || ((ucWAStateHi & cTO) > (unsigned char) 0))) /* WA process already finished ? OR definitely failed  ? */
    {
      if ((tWAPar.ucWACtrl & ucWACtrlFixc) > 0)  /* fixed wheel allocation/Override activated ? */
        (void) (ushLearnInOver8(ptInputWA )); 
      else if (cCompleteLearn == ucLearnMode)
        (void) (ushCompLearn(ptInputWA ));    
      else if (cSpeciaLearn == ucLearnMode )
        (void) (ushSpeciaLearn(ptInputWA));

      ProvideFPAlgo2MT_DAG();
    }
  }

  if ((GETushWAState()) != ushRet) // any WAState changes ?
  {
    if ((ucNrOfUKWPinHist () > 0) && ((ucWAState & 0xF0) > 0))
    {
      UpdateALState (cEvNewIDs);
    }
    // BAD: if (((unsigned char) 0 == ucNrOfLocatError()) && (cMaxLR  > ucNrOfUKWPinZOM())) // decission SW WS 2016-05-12: if present sensors could be located go to OK,  
    if ((ucNrOfUKWPinHist () == 0) && ((ucWAState & cWAStateZO ) > 0) && (((unsigned char) 2) > ucNrOfLocatError()))  // max. 1 LocatError is for forced allocation
    {
			if((ucNrOfLocatErrorAndPosForce() == 0) || (tWAPar.AL_State != cAL_Stored)) /*cEvHoldStore halte cAL_Stored CRS_1211_090_001*/
			{
				UpdateALState (cEv4WPs);
			}
    }
  }
  ushRet = GETushWAState();

  return(ushRet);
}

/**
 * \brief figure out error type if allocation did not finish
 *
 *-----------------------------------------------------------------------------------------------
 * \param [inout] ucWAState Global static variable containing the WA status
 *
 * \return ucRet contains bit indexed, history columns that have active learn or locate errors
 *
 *------------------------------------------------------------------------------------------------
 */
unsigned char ucWATO(void)
{
  unsigned char ucRet = (unsigned char) 0;  /* no error by default */

  if ((ucWAState & cWAStateZO) == 0) /* ZO already reached ? */
  { /* no */
    ucRet = ucGetMisOrNoLearnError ();
    ucRet |= ucGetAnyLocatErrors(ucRet);
  }

  if ( (unsigned char) 0 == ucRet )
    ClearAlLearNLocatError(cAll);

  return (ucRet);
}


/**************************************************************************************************
* \brief sets wheel allocation to initial state, loads all ee values
*
*-----------------------------------------------------------------------------------------------
* \param [inout] tWAPar Global structure containing WA parameters
* \param [out] aulHistoryID Global static array containing Wheel IDs
* \param [out] aucHistoryWP Global static array containing Wheel positions
*
* \return tbd
*
*------------------------------------------------------------------------------------------------
*/
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
  if (cNoLearn == ucLearnMode)  /* fixed wheel allocation ? */
  { /* only already initialized histories can get fixed to current state */
    RestoreHistory();
  }
  tWAPar.ucWACtrl &= ~ucWACtrlBreakc; /* WA open at default */


  //if ((ucHistInConsist () > (unsigned char) 0) && ((cAL_OK == tWAPar.AL_State ) || (cAL_Stored == tWAPar.AL_State)))
  //{
  //  tWAPar.AL_State = cAL_Unknown ;
  //  PutWADataEE(cWAParameter, (unsigned char *) &tWAPar , (unsigned char) sizeof(WAParameter));
  //}
  ucDAGLearnState = Autolearn_Learning ;
#ifdef FPA 
  Very1stABSTickIinit();
  //InitFilterTime();
#endif
  WAStatusChangedEvent(GETushWAState() );
  return (ucGetHistoryState());
}



/************************************************************************************************//**
                                                                                                  * \brief enable / disable walloc/autolocation overide feature
                                                                                                  *
                                                                                                  *-----------------------------------------------------------------------------------------------
                                                                                                  * \param [in] ucPalOverideFlag pal overide enable flag
                                                                                                  * \param [out] none
                                                                                                  *
                                                                                                  * \return ucRelVal 0 condition not meet 
                                                                                                  *				    1 succesfull
                                                                                                  *
                                                                                                  *------------------------------------------------------------------------------------------------
                                                                                                  */
unsigned char ucSetAutolocationOveride(unsigned char ucPalOverideFlag)
{

  unsigned char ucRetVal;

  /*  Autolocation overide can only be configured when history IDs and history WP are available */
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
      // condition not meet
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
  else // input value out of range
  {
    ucRetVal=0;
  }
  return ucRetVal;

}

/************************************************************************************************//**
                                                                                                  * \brief returns autolocation overide status
                                                                                                  *
                                                                                                  *-----------------------------------------------------------------------------------------------
                                                                                                  * \param [in] void
                                                                                                  * \param [out] none
                                                                                                  *
                                                                                                  * \return 0 off 
                                                                                                  *         1 on
                                                                                                  *
                                                                                                  *------------------------------------------------------------------------------------------------
                                                                                                  */
unsigned char ucReadAutolocationOverideFlag ()
{
  unsigned char ucRetVal;
  if (tWAPar.ucWACtrl == ucWACtrlFixc)
    ucRetVal = 1;
  else
    ucRetVal = 0;

  return ucRetVal;
}

/************************************************************************************************//**
 * \brief replace 1 history ID / 1 history WP
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] pt2ID pointer to new ID
 * \param [in] pt2Pos pointer to new wheel position
 * \param [in] ucIdx Index of the ID/WP to be replacec
 *
 * \return ucRetVal 4 operation succesfull history 4 WP known (ZG)
                    1 operation succesfull history <4 WPs known (ER)
 *                  0 opreation not succesfull
 *
 *------------------------------------------------------------------------------------------------
 */
unsigned char ucSet1HistID(unsigned long *pt2ID, unsigned char *pt2Pos, unsigned char ucIdx)
{
  unsigned char i, ucRetVal;

  ucRetVal=0;

  /*check whether ID already exist at other position */
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
    
    ucLearnMode = cCompleteLearn ;  // refer to OIL #323
    (void) WAInitByDiag((WAParNCfgType *) &ucLearnMode );

    ucRetVal = ((unsigned char) 0 == ucNrOfUKWPinHist ()) ? (unsigned char) 4:(unsigned char) 1;
  }

  return ucRetVal;
}

/************************************************************************************************//**
                                                                                                  * \brief replace 4 history ID / 4 history WP
                                                                                                  *
                                                                                                  *-----------------------------------------------------------------------------------------------
                                                                                                  * \param [in] pt2ID pointer to new IDs
                                                                                                  * \param [in] pt2Pos pointer to new wheel positions
                                                                                                  *
                                                                                                  * \return ucRetVal 1 operation succesfull
                                                                                                  *                  0 opreation not succesfull
                                                                                                  *
                                                                                                  *------------------------------------------------------------------------------------------------
                                                                                                  */
unsigned char ucSet4HistIDs(unsigned long *pt2ID, unsigned char *pt2Pos)
{
  unsigned char i, j, ucRetVal;

  ucRetVal=0;
  j=0;

  /*check input parameters for consistency */
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

      // check input parameters for ambiguities. All IDs and positions should be unique. pos=4 can be set for more than 1 sensors
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

     ucLearnMode = cCompleteLearn ; // refer to OIL #323
    (void) WAInitByDiag((WAParNCfgType *) &ucLearnMode );

    ucRetVal = ((unsigned char) 0 == ucNrOfUKWPinHist ()) ? (unsigned char) 4:(unsigned char) 1;
  }

  return ucRetVal;
}
#ifdef Test_LOG_ENABLE
/************************************************************************************************//**
                                                                                                  * \brief returns status of wheel allocation in ZOM
                                                                                                  *
                                                                                                  *-----------------------------------------------------------------------------------------------
                                                                                                  * \param [in] ucIdx Sensor position in ZOM
                                                                                                  * \param [in] tZOM Global ZOM structure
                                                                                                  *
                                                                                                  * \return none
                                                                                                  *
                                                                                                  *------------------------------------------------------------------------------------------------
                                                                                                  */
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



/************************************************************************************************//**
                                                                                                  * \brief returns number of valid PAL telegramms received
                                                                                                  *
                                                                                                  *-----------------------------------------------------------------------------------------------
                                                                                                  * \param [in] ucIdx Sensor position in ZOM
                                                                                                  * \param [in] tZOM Global ZOM structure
                                                                                                  *
                                                                                                  * \return Tooth telegramm counter
                                                                                                  *
                                                                                                  *------------------------------------------------------------------------------------------------
                                                                                                  */
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

/************************************************************************************************//**
                                                                                                  * \brief returns number of received telegramm with learnbit set
                                                                                                  *
                                                                                                  *-----------------------------------------------------------------------------------------------
                                                                                                  * \param [in] ucIdx Sensor position in ZOM
                                                                                                  * \param [in] tZOM Global ZOM structure
                                                                                                  *
                                                                                                  * \return  telegramm counter
                                                                                                  *
                                                                                                  *------------------------------------------------------------------------------------------------
                                                                                                  */
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
/************************************************************************************************//**
                                                                                                  * \brief returns number of valid PAL telegramms received
                                                                                                  *
                                                                                                  *-----------------------------------------------------------------------------------------------
                                                                                                  * \param [in] ucIdx Sensor position in ZOM
                                                                                                  * \param [in] tZOM Global ZOM structure
                                                                                                  *
                                                                                                  * \return Tooth telegramm counter
                                                                                                  *
                                                                                                  *------------------------------------------------------------------------------------------------
                                                                                                  */
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
/************************************************************************************************//**
                                                                                                  * \brief returns number of PAL telegramms received w/o PAL info (time out)
                                                                                                  *
                                                                                                  *-----------------------------------------------------------------------------------------------
                                                                                                  * \param [in] ucIdx Sensor position in ZOM
                                                                                                  * \param [in] tZOM Global ZOM structure
                                                                                                  *
                                                                                                  * \return Tooth telegramm counter
                                                                                                  *
                                                                                                  *------------------------------------------------------------------------------------------------
                                                                                                  */
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

/************************************************************************************************//**
                                                                                                  * \brief returns number of invalid PAL telegramms received
                                                                                                  *
                                                                                                  *-----------------------------------------------------------------------------------------------
                                                                                                  * \param [in] ucIdx Sensor position in ZOM
                                                                                                  * \param [in] tZOM Global ZOM structure
                                                                                                  *
                                                                                                  * \return Tooth telegramm counter
                                                                                                  *
                                                                                                  *------------------------------------------------------------------------------------------------
                                                                                                  */
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

/************************************************************************************************//**
                                                                                                  * \brief returns number of used telegrams by the walloc
                                                                                                  *
                                                                                                  *-----------------------------------------------------------------------------------------------
                                                                                                  * \param [in] ucIdx Sensor position in ZOM
                                                                                                  * \param [in] tZOM Global ZOM structure
                                                                                                  *
                                                                                                  * \return Tooth telegramm counter
                                                                                                  *
                                                                                                  *------------------------------------------------------------------------------------------------
                                                                                                  */
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

/************************************************************************************************//**
                                                                                                  * \brief returns Abs metric reset flag
                                                                                                  *
                                                                                                  *-----------------------------------------------------------------------------------------------
                                                                                                  * \param [in] ucIdx Sensor position in ZOM
                                                                                                  * \param [in] tZOM Global ZOM structure
                                                                                                  *
                                                                                                  * \return reset flag status
                                                                                                  *
                                                                                                  *------------------------------------------------------------------------------------------------
                                                                                                  */
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

/**************************************************************************************************
* \brief returns Delta Min Value in ZOM
*
*-----------------------------------------------------------------------------------------------
* \param [in] ucIdx Sensor position in ZOM
* \param [in] tZOM Global ZOM structure
*
* \return Delta_min
*
*------------------------------------------------------------------------------------------------
*/
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


/**************************************************************************************************
* \brief returns currently interpolated ABS values
*
*-----------------------------------------------------------------------------------------------
* \param [in] ucIdx Sensor position in ZOM
* \param [in] tZOM Global ZOM structure
*
* \return Interpolated ABS values Range 0-95
*
*------------------------------------------------------------------------------------------------
*/
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

/**************************************************************************************************
* \brief returns ABS metrics (sums) in ZOM used in the WA algorithms
*
*-----------------------------------------------------------------------------------------------
* \param [in] ucIdx Sensor position in ZOM
* \param [in] tZOM Global ZOM structure
*
* \return Wheel allocation algorithms metrics
*
*------------------------------------------------------------------------------------------------
*/
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

/**************************************************************************************************
* \brief returns learn quality index in ZOM used in the WA algorithms
*
*-----------------------------------------------------------------------------------------------
* \param [in] ucIdx Sensor position in ZOM
* \param [in] tZOM Global ZOM structure
*
* \return learn quality index
*
*------------------------------------------------------------------------------------------------
*/
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

//**
// \brief WA timer, called cyclically every sec. Controls time thresholds for allocation actions
//  and initiats time triggered ZOM allocactions (briefly allactions)
//-----------------------------------------------------------------------------------------------
// \param [in] s.b.
// \param [in] s.b.
//
// \return s.b. (???)
//
//------------------------------------------------------------------------------------------------
///
void WATimer1sec(unsigned short ushVSpeedInKmh)
{
  unsigned char ucTmp;

  if (cV_MIN < ushVSpeedInKmh)
  {
    if (cV_MAX_PAL < ushVSpeedInKmh )
      if ( cTIME_OUT > ushDriveTimeOverPalMax  )  
        ushDriveTimeOverPalMax++;

    if ((unsigned char) 0 == (ucWAState & cWAStateZO)) // SW WS 230217 decission stop WATimer after finishing allocation OIL #903
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
        if ((((unsigned char) 0 == ucNrOfLocatError()) && (cMaxLR  > ucNrOfUKWPinZOM())) || ((((unsigned char) 1 == ucNrOfLocatError() ) && ((unsigned char) 1 == ucNrOfUKWPinZOM())))) // decission SW WS 2016-05-12: if present sensors could be located go to OK, forced allocation shall also lead to OK (former SWWS decision)
				{
					if((ucNrOfLocatErrorAndPosForce() == 0) || (tWAPar.AL_State != cAL_Stored)) /*cEvHoldStore halte cAL_Stored CRS_1211_090_001*/
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

// pucGetLearnError purpose:
// returns address of a 4 byte char array that contains learn error codes for each sensor in history, index is history column
unsigned char * pucGetLearnError(void)
{
  return ucLearnError ;
}

// pucGetLocatError purpose:
// returns address of a 4 byte char array that contains locate error codes for each sensor in history, index is history column
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
  if ( ucCurID < cSumWE)   /* new data to assess ? */
  {
    if ((ucWAState & cWAStateActive) == 0)             /* identification already running ? */
      if ( ucStartWA() == 1 )                 /* no, start conditions met ? */
        ucWAState |= cWAStateActive;          /* yes, WA official start : has no more effect - obsolete*/


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

    if ((unsigned char) 0 == (ucWAState & cWAStateZO ))  // not yet finished ?
      // SW Workshop avril 26th 2016 'close allocation w/ history wheelset as early as possible': if ( cSLHistAssignTimeInSec < ushDriveTimeInSec )
        (void) ucSL3MinHistPreFinish();
  }


  return(GETushWAState());
}
// ucAssessDAGSLUC purpose:
// covers DAG's Special Learn UseCases see TPMS Logic  PAL2 V1.3 - 4.2.2
// !!! assumes an aligned ZOM w/ 4 WPs inside and TeethTelCt > cMinCt4Dec !!!
static unsigned char ucAssessDAGSLUC(unsigned char ucWPs)  
{
  unsigned char ucIDSlots,ucNewSensors, i,ucRet = 0;

  ucNewSensors = ucGetNrOfNewIDs(&ucIDSlots );

  if (0 == ucNewSensors ) // history ID set has been allocated in < 3 min time (TODO: WPs might have changed, is this accepted by DAG ? yes )
  {
    ucRet = 1;
  }
  else if (cMaxLR == ucNewSensors )
  {  // write 4 new IDs and WPs to history
    if ((cHistIDProtectTime < ushDriveTimeInSec) && (cMaxLR == ucWPs))// see TPMS Logic  PAL2 V1.3 - 4.1 Autolearn - In the first 4 Minutes only prelearned IDs can be learnt.
      ucRet = 1; // see TPMS Logic  PAL2 V1.3 - 4.2.2 "4 new sensors in learnmode with PAL data"
  }
  else if (cMaxLR > ucNewSensors)
  {
    if ((c5MinDriveTimeInSec < ushDriveTimeInSec))  // see TPMS Logic  PAL2 V1.3 - 4.1.2 Special Learn - If there is one new sensor (in Learn mode) and three prelearned sensors, the new ID must be learned after 5 minutes driving time. Prelearned IDs stay at the same position, the new ID is placed to the position of the missing sensor.
      if (ucNewZomIDsFit2MissingHistID_WP(ucIDSlots) > 0)
      {
        ucRet = 1;
      }
  }
  for (i = 0; i < cMaxLR; i++)  // check all WPs in ZOM before
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
    ucWAState &= 0x0F;  // update changed ID information
    ucWAState |= (ucRet&0xF0);
    ucWAStateHi &= 0x0F;  // update changed WP information
    ucWAStateHi |= ((ucRet&0x0F)<<4);
    ucRet = (unsigned char) 0xFF;
  }

  return (ucRet);
}

// ucGetNrOfNewIDs purpose:
// 1st 4 ZOM slots get considered, 
//  returns directly nr of new ZOM-IDs compared to history, 
//          in p2Slots receives bit indexed new ZOM slots low nibble, old missing HistorySlots in HiNibble as follows:
// parameter *p2Slots       MSB 1 : ID in History slot 3 [0..3] missing
//                              1 : ID in History slot 2 [0..3] missing 
//                              1 : ID in History slot 1 [0..3] missing
//                              1 : ID in History slot 0 [0..3] missing
//
//                              1 : ID in ZOM slot 3 [0..3] is new
//                              1 : ID in ZOM slot 2 [0..3] is new
//                              1 : ID in ZOM slot 1 [0..3] is new
//                          LSB 1 : ID in ZOM slot 0 [0..3] is new
static unsigned char ucGetNrOfNewIDs(unsigned char * p2Slots)   
{
  unsigned char i,j,ucOldID = 0;
  *p2Slots = (unsigned char) 0xFF; // per default all 4 ZOM IDs are brand new ones and all history IDs are missing

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

// ucNewZomIDsFit2MissingHistID_WP purpose:
// returns > 0 if all new ZOM ID WPs fit to missing History ID WPs
// parameter ucNewNMissing  MSB 1 : ID in History slot 3 [0..3] missing
//                              1 : ID in History slot 2 [0..3] missing 
//                              1 : ID in History slot 1 [0..3] missing
//                              1 : ID in History slot 0 [0..3] missing
//
//                              1 : ID in ZOM slot 3 [0..3] is new
//                              1 : ID in ZOM slot 2 [0..3] is new
//                              1 : ID in ZOM slot 1 [0..3] is new
//                          LSB 1 : ID in ZOM slot 0 [0..3] is new
static unsigned char ucNewZomIDsFit2MissingHistID_WP(unsigned char ucNewNMissing)
{
  unsigned char i,j, ucNewCt=0, ucMatchCt=0;

  for (i = 0; i < cMaxLR ; i++)                                 // compare ZOM WPs ..
  {
    if (((unsigned char) (1<<i) & ucNewNMissing ) > 0)          // ..if it is a new one..
    {
      ucNewCt++;
      for ( j  = 0; j < cMaxLR; j++)                            // ..to History WPs  ..
      {
        if (((unsigned char) (0x10<<j) & ucNewNMissing ) > 0)   // ..if it is a missing one
        {
          if (ucGetZOMWP(i) == aucHistoryWP [j])
          {
            ucMatchCt ++;
            ucNewNMissing &= ~((unsigned char) (0x10<<j));  // no more missing
            break;
          }
        }
      }

      if (cMaxLR == j) // if new WP was not found check for UK
      {
        for ( j  = 0; j < cMaxLR; j++)
        {
          if (cWheelPos_RR  < aucHistoryWP [j])
          {
            //aucHistoryWP [j] = ucGetZOMWP(i);
            ucMatchCt ++;
            ucNewNMissing &= ~((unsigned char) (0x10<<j));  // no more missing
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

// ucWrZom2History purpose:
// Write ZOM ID and WP to history, new ZOM IDs replace missing History IDs, 
//  if no new ZOM IDs are present, the ZOM WPs are written over history WPs, for this
//  WP-changes are notified and new History entries as well in the return value
//  !!! for all ZOM actions the 4 1st ZOM slots are considered !!!
// parameter ucNewNMissing  MSB 1 : ID in History slot 3 [0..3] missing
//                              1 : ID in History slot 2 [0..3] missing 
//                              1 : ID in History slot 1 [0..3] missing
//                              1 : ID in History slot 0 [0..3] missing
//
//                              1 : ID in ZOM slot 3 [0..3] is new
//                              1 : ID in ZOM slot 2 [0..3] is new
//                              1 : ID in ZOM slot 1 [0..3] is new
//                          LSB 1 : ID in ZOM slot 0 [0..3] is new
//
// return                   MSB 1 : ID in History slot 3 [0..3] replaced
//                              1 : ID in History slot 2 [0..3] replaced 
//                              1 : ID in History slot 1 [0..3] replaced
//                              1 : ID in History slot 0 [0..3] replaced
//
//                              1 : History WP at slot 3 [0..3] changed
//                              1 : History WP at slot 2 [0..3] changed
//                              1 : History WP at slot 1 [0..3] changed
//                          LSB 1 : History WP at slot 0 [0..3] changed
static unsigned char ucWrZom2History(unsigned char ucNewNMissing)
{
  unsigned char i,j,ucRet, ucNewCt = ucNrOfBitSet ((unsigned short) (ucNewNMissing & 0x0F));
  ucRet = 0; // nothing changed by default

  if (ucNrOfBitSet ((unsigned short) (ucNewNMissing & 0xF0)) == ucNewCt ) // parameter check: as much missing as new ones ?
  {
    for ( i = 0; i < cMaxLR ; i++)
    {
      if ((ucNewNMissing & (1<<i)) > 0) // new ZOM ID in slot i ?
      {
        for ( j = 0; j < cMaxLR; j++)
          if ((ucNewNMissing & (0x10<<j)) > 0) // missing history ID in slot j ?
          {
            ucNewNMissing &= ~(0x10<<j); // no more missing
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
      {  // known ID - check for WP change
        for ( j = 0; j < cMaxLR; j++)
          if (tZOM [i].ulID == aulHistoryID [j])
          {
            if (ucGetZOMWP(i) == aucHistoryWP [j])  // no WP change ?
              break;
            else
            {
              aucHistoryWP [j] = ucGetZOMWP(i); // new WP
              ucRet |= (1<<j);
              break;
            }
          }
          }
    }
    if (ucHistInConsist() > 0)
    {  // restore
      GetWADataEE(cHistorySet1, (unsigned char *) aulHistoryID, (unsigned char) sizeof(aulHistoryID));
      GetWADataEE(cHistoryWPSet1, aucHistoryWP, (unsigned char) sizeof(aucHistoryWP));
      ucRet = 0;
    }
    else
    {
      PutWADataEE(cHistorySet1, (unsigned char *) aulHistoryID, (unsigned char) sizeof(aulHistoryID));  // TODO: ask gl if 2 wr access works fine
      PutWADataEE(cHistoryWPSet1, aucHistoryWP, (unsigned char) sizeof(aucHistoryWP));
    }
  }
  else  // bad parameter
    ucRet = 0;

  return (ucRet);
}

// ucHistInConsist purpose:
// returns > 0 if current history is inconsistent concerning IDs or WPs ( none present WP sets bit in hi nibble return value)
unsigned char ucHistInConsist(void) 
{
  unsigned char i,j, ucRet = 0xF0;  // all IDs are fine, all WPs are not present

  for ( i = 0; i < cMaxLR ; i++)  // check IDs for not being zéro
  {
    if (aulHistoryID [i] < (unsigned long) 1)
    {
      ucRet |= (0x01<<i);
    }
  }

  for ( i = 0; i < cMaxLR ; i++)  // check 4 at least one pair of double IDs 
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

  for ( i = 0; i < cMaxLR ; i++)  // check WPs for all 4 are present
  {
    if (aucHistoryWP [i] < (cWheelPos_RR + 1))
    {
      ucRet &= ~(0x10<<aucHistoryWP [i]); // this one is present
    }
  }

  return (ucRet);
}


// ucSL3MinHistPreFinish purpose:
// returns > 0 if ZG status could by reached by History - ZOM ID match
// refer to TPMS Logic  PAL2 V1.3 - 4.1.2 Special Learn - ... After typical 3 minutes driving the prelearned IDs must be confirmed
static unsigned char ucSL3MinHistPreFinish(void)
{
  unsigned char ucRet = 0;
  unsigned short usHelp = 0;

  if ( (unsigned char) 0 == (ucWAState & cWAStateZO)) // ZO not yet finished ?
  {
    if ((unsigned char) 0 == ucHistInConsist ())
    {
      // WARNING: ZOM might not be aligned to 1st 4 slots yet !!!
      usHelp = ushIDSetInHist(aulHistoryID,3,cSumWE );
      if (ucNrOfBitSet (usHelp) == cMaxLR ) // all history IDs found in ZOM ?
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

// ucSL31Finish purpose:
// returns >0 if 3 history IDs are in ZOM and exactly 1 new ID, sets WAState to ZG and writes new ID to history
// refer to: TPMS Logic  PAL2 V1.3 - 4.2.2 Autolearn Use Cases - New sensor shall be learned and placed to the
// empty position (at timeout)
// Status info WUx shall show failed PAL localization.
static unsigned char ucSL31Finish(unsigned char ucMinCt4NewID)
{
  unsigned short ushNewID = 0;

  if ( (unsigned char) 0 == (ucWAState & cWAStateZO)) // ZO not yet finished ?
  {
    // WARNING: ZOM might not be aligned to 1st 4 slots yet !!!
    if ( (unsigned char) 1 == ucGetNrOfNewIDsInLM_SL(&ushNewID,ucMinCt4NewID) )
    { 
      if (0 < ui16NewIdFits(ushNewID, ushIDSetInHist(aulHistoryID,3,cSumWE )))  // new WP is not in use and not actively rival 2 existing history ID's WP and has valid PAL telegrams
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


// ucGetNrOfNewIDsInLM_SL purpose:
// ALL ZOM slots get considered, 
//  returns directly nr of new ZOM-IDs compared to history in Learn Mode, 
//          in p2Slots receives bit indexed new ZOM slots 
// parameter *p2Slots       bit indexed the corresponding slot w/ new IDs in LearnMode
static unsigned char ucGetNrOfNewIDsInLM_SL(unsigned short * p2Slots, unsigned char ucMinCt)   
{
  unsigned char i,j,ucNewID = (unsigned char) 0;
  *p2Slots = 0; 

  for (i = 0; i < cSumWE ; i++)
  {
    if (tZOM [i].ucProbeCt  > 0)  // slot s not empty
    {
      for (j = 0; j < cMaxLR ; j++)
      {
        if (tZOM [i].ulID == aulHistoryID [j])
        {
          break;
        }
      }
      if ( cMaxLR == j )  // ID not found in History
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
      break;  // empty slot -> abort
  }
  return ( ucNewID );
}

// ucGetNrOfNewIDsInLM purpose:
// ALL ZOM slots get considered, 
//  returns directly nr of new ZOM-IDs compared to history in Learn Mode, 
//          in p2Slots receives bit indexed new ZOM slots 
// parameter *p2Slots       bit indexed the corresponding slot w/ new IDs in LearnMode
static unsigned char ucGetNrOfNewIDsInLM(unsigned short * p2Slots, unsigned char ucMinCt)   
{
  unsigned char i,j,ucNewID = (unsigned char) 0;
  *p2Slots = 0; 

  for (i = 0; i < cSumWE ; i++)
  {
    if (tZOM [i].ucProbeCt  > 0)  // slot s not empty
    {
      for (j = 0; j < cMaxLR ; j++)
      {
        if (tZOM [i].ulID == aulHistoryID [j])
        {
          break;
        }
      }
      if ( cMaxLR == j )  // ID not found in History
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
      break;  // empty slot -> abort
  }
  return ( ucNewID );
}

// CheckAutoDeactivateOverride purpose:
//  deactivates DAG's override feature (fixed WA) if >1 new IDs are present in ZOM
//  if exactly one is present and 1 history is missing the new ID is put to missing WP
//  refer to TPMS Logic  PAL2 V1.3 - 4.3 Autolocation Override Feature - Autolocation override will be automatically disabled when more than one new wheel sensor ID is learnt. One single new sensor ID shall
//  be placed to the position of the missing sensor ID.
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

// purpose ucFinishViaHistory
// find history wheel set in ZOM
// if present and has more identified WPs write history new w/ current WPs 
// if present but w/ less identified WPs restore history to ZOM
// returns > 0 if History could be found in ZOM , and has been written or restored
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
      /// RestoreHistory(); we must not set WPs if not actively located
      ucWAState &= (unsigned char) ~cWAStateZO; // NEW: in case of finishing w/ history WPs, cWAStateZO MUST NOT be set any longer
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
static unsigned char ucBadHist2Def(void)  // returns number of history IDs with value 0 replaced by default IDs [1,2,3,4]
{
  unsigned char i, ucBadIDCt = (unsigned char) 0;

  for (i = 0; i < cMaxLR; i++)  // prevent inconsistent history IDs (prevent TER)
  {
    if ( aulHistoryID[i] < 1UL )  // might be 0 due to bad diag service ID write access
    {
      aulHistoryID[i] = (unsigned long) i + 1;
      ucBadIDCt++;
    }
  }
  return (ucBadIDCt );
}

// ucGetNrOfNewIDsInLMwoPAL purpose:
// ALL ZOM slots get considered, 
//  returns directly nr of new ZOM-IDs compared to history in Learn Mode, 
//          in p2Slots receives bit indexed new ZOM slots 
// parameter *p2Slots       bit indexed the corresponding slot w/ new IDs in LearnMode w/o PAL data
static unsigned char ucGetNrOfNewIDsInLMwoPAL(unsigned short * p2Slots)   
{
  unsigned char i,j,ucNewID = (unsigned char) 0;
  *p2Slots = 0; 

  for (i = 0; i < cSumWE ; i++)
  {
    if (tZOM [i].ucProbeCt  > 0)  // slot s not empty
    {
      for (j = 0; j < cMaxLR ; j++)
      {
        if (tZOM [i].ulID == aulHistoryID [j])
        {
          break;
        }
      }
      if ( cMaxLR == j )  // ID not found in History
      {
        if (tZOM[i].ucToothTelCtNoLearnMode > 0)
        {
          ucNewID++;
          *p2Slots |= 1<<i;
        }
      }
    }
    else
      break;  // empty slot -> abort
  }
  return ( ucNewID );
}

// uc3NewIDsAllocated purpose:
// checks if exactly 3 new IDs corellate fine and not any of the old history IDs are present
// then and only then write the  3 new ones to history and replace old IDs with same(1) or invalid(2) WP
// if after that the histoy is consistent set ZG otherwise ER only, ucWAState is served for changed IDs as well
static unsigned char uc3NewIDsAllocated(unsigned char ucMinCt4NewID)
{
  unsigned short ushHistSet = 0, ushNewID = 0;

  if ( (unsigned char) 0 == (ucWAState & cWAStateZO)) // ZO not yet finished ?
  {
    // WARNING: ZOM might not be aligned to 1st 4 slots yet !!!
    ushHistSet = ushIDSetInHist(aulHistoryID,3,cSumWE );
    if (ucNrOfBitSet (ushHistSet) == 0 ) // not any history IDs found in ZOM ?
    { 
      if ( (unsigned char) 3 == ucGetNrOfNewIDsInLM_SL(&ushNewID,ucMinCt4NewID))
      {
        ushNewID = ushAlignZOM(ushNewID );
        if ((unsigned char) 3 == ucNrOfBitSet((unsigned short) ucGenDMnD2(10,4,ushNewID)))
        {  // 3 corelating WPs: the 4 st ZOM slots contain 3 valid WPs
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
          SetWAStateZOChange(ucSetHistory((unsigned char)cWAStateZO, 0x0F)); /* freeze WPset */
          ucWAState |= cWAStateZO;                      /* ZOState reached now */
        }
        else if( ucGetERState()==1 )
        {
          SetWAStateZOChange(ucSetHistory((unsigned char)cWAStateER, 0x0F)); /* freeze IDset */
        }
      }
      else                                      /* ERState already reached but not ZO */
      {
        if (ucCheckWheelPos(ucCurID,ptInputWA ) == 1)      /* ZOState met ? */
        {
          SetWAStateZOChange(ucSetHistory((unsigned char)cWAStateZO, 0x0F));   /* freeze WPset */
          ucWAState |= cWAStateZO;                        /* ZOState reached now */
        }
      }
    }
    else
    { /* wheel is not turning, too small or too much or anything else*/
    }
  }
  return(GETushWAState());
}

static unsigned short ushWhlSetRdy2Freeze(unsigned char ucMinCt, unsigned char ucMinCt4HistERc, unsigned char bLearnNewIDsFlag)
{
  unsigned char ucNewCt,ucOldCt, ucOtherCt;
  unsigned short ushNew, ushOld, ushOther, ushRet = 0;

  ushOld = ushIDinLearnModeSetInHist(aulHistoryID,ucMinCt4HistERc,cSumWE); /* try to find history ID set in ZOM */
  ushOld |= ushSetHistIDs2ER (aulHistoryID,ucDefMinCt4HistER,cSumWE);  /* new in DMC20056, see seperate mail Mr.Kiesewetter */
  ucOldCt = ucNrOfBitSet(ushOld);
  ucNewCt = ucGetNrOfNewIDsInLM (&ushNew,ucMinCt );
  
  ucOtherCt = ucGetNrOfNewIDsInLM (&ushOther,(unsigned char) 4 );
  ucOtherCt -= ucNewCt;
  ushOther &= ((unsigned short) ~ushNew);

  if (cMaxLR == ucOldCt)  // max prio has history wheel set
    ushRet = ushOld;
  else if ((cMaxLR == ucNewCt) && (0 == ucOldCt) && bLearnNewIDsFlag && ( 0 == ucOtherCt ))
      ushRet = ushNew;
  else if ((cMaxLR == (ucNewCt + ucOldCt)) && bLearnNewIDsFlag && ( 0 == ucOtherCt ))
    ushRet = (ushNew|ushOld);
  
  return(ushRet);
}
// ucForceAutoLocate purpose:
// checks history for exactly one unknown WP
// if existent it will be replaced by the so far unused valid WP
// returns the history slot that has been auto located (set to the unused WP)
// bit indexed in the high nibble
// eg. return = 0x80 -> history slot 3 [0..3] has been set to valid WP
static unsigned char ucForceAutoLocate(void)
{
  unsigned char i,j, ucUK, ucUnusedWP; 

  ucUnusedWP = 0x0F;  
  ucUK = 0;

  if (ui8AnyHistIdMissing () == ((uint8) 0))	// none present hist IDs shall prevent forced localization see OIL #1033
  {
	  for (i = 0; i < cMaxLR; i++)  // find unknown WP slot and unused WP
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
		  for (i = 0; i < cMaxLR; i++)  // wr unused WP to slot w/ so far unknown WP
		  {
			  if ((ucUK & (0x10<<i)) > 0)
			  {
				  for (j = 0; j < cMaxLR ; j++)
				  {
					  if ( (ucUnusedWP & (1<<j)) > 0 )
					  {
						  aucHistoryWP [i] = j;
						  ucWAStateHi |= cForcedZO ;
						  j = cMaxLR;   // formerly break;
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

// returns bit indexed the history slots which ID's cannot be found in 1st 4 valid ZOM slots
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

// returns number of unknown WPs in ZOM
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

// returns number of unknown WPs in History
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

// if no full (< 4 history IDs) history is present:
// 1. make end correlation 
// 2. if wheel set is not complete take corelating and try filling up w/ none corel. history wheels or new ERs
// 3. write available IDs and WPs to history
// WARNING: expects ZO is not met yet
// returns > 0 if allocation was improoved or finishe, 0 if nothing's left to do
static unsigned char ucFinalFreeze(unsigned char ucMinCt4HistER, unsigned char ucMinCt)  
{
  unsigned char ucIdentifiedWP;
  unsigned short ushNew,ushOld,ushFRS;

  if ((unsigned char) 0 == ucFinishViaHistory())        // no chance to finish w/ help of history ? ..
  {                                     // ..so take what you have 
    (void) ucGetNrOfNewIDsInLM (&ushNew,ucMinCt );
    ushOld = ushIDSetInHist(aulHistoryID,ucDefMinCt4HistER,cSumWE);  // new : accept also Hist IDs not in LM

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
      if ( ucNrOfBitSet (ushNew|ushOld) < cMaxLR )  // req: "weniger als 4 Räder erfüllen Eigenradkriterium"
      {
          ushNew = ushLqiTribute(ushNew); // req: "bei nicht bestandener ER PRüfung wird das Rad nicht als ER verwendet"
      }

      ucIdentifiedWP = ucGenDMnD2(10,4,(ushOld|ushNew));

      ushOld = ushIDSetInHist(aulHistoryID,ucDefMinCt4HistER,cSumWE);  // do this a 2nd because ZOM might have been aligned and ZOMPos' changed
      ushNew = 0;
      (void) ucGetNrOfNewIDsInLM (&ushNew,ucMinCt );
      ushNew &= ((unsigned short) ucIdentifiedWP);

      ushOld |= (unsigned short) ucIdentifiedWP ;
      if (ucNrOfBitSet (ushOld) > cMaxLR )
      {
        SetWAStateZOChange (ucSetHistory (cWAStateZO,ucIdentifiedWP));  // wr only corelating ones 
        dblCk4LocEr( );
      }
      else
      {
        ushNew |= ushOld;
        ushNew = ushAlignZOM(ushNew);
        if (ucNrOfBitSet (ushNew) > cMaxLR)
        {
          SetWAStateZOChange (ucSetHistory (cWAStateZO,(unsigned char)ushOld));  // wr corelating and history
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
    //ucWAState |= (cWAStateER | cWAStateZO);
    ucWAStateHi &= (unsigned char) ~cTZG;
  }
  else if ((unsigned char) 0 == ucIdentifiedWP )
  {
    //ucWAState &= (unsigned char) ~cWAStateZO;
    ucWAStateHi &= (unsigned char) ~cTZG;
  }
  else
  {
    ucWAState &= (unsigned char) ~cWAStateZO;
    ucWAStateHi |= cTZG;
  }

  return ((unsigned char) 1);  // could improove allocation state or finish via history
}
// UpdateALState purpose:
// implementation of 4.2.5 Autolocate_Status see TPMS Logic PAL2 V1.5.docx
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
    else if (( cEvALFailed == ui8Trigger)) // decision SW-WS_261016: remove this "&& !((ushDriveTimeInSec >> 1) < ushDriveTimeOverPalMax ))" for getting fallback active
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

// ucFindNoLearnHistoryIDs purpose:
// search after not learnable history ID in ZOM 
// not learnable means ID is with learn bit counter below ucMinProbeCt in ZOM
// returns: // returns: 0xFF if not learnable, 0 if present
static unsigned short ucFindNoLearnHistoryIDs(unsigned long *ptHistID, unsigned char ucMinProbeCt, unsigned char ucSlots2Search)
{
  unsigned char j, ucRet = (unsigned char) 0xFF;  // history ID not learnable by default
  
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

// ucFindNoLearnHistoryIDs purpose:
// search after missing history ID in ZOM 
// missing means ID is NOT in ZOM
// returns: 0xFF if missing, 0 if present
static unsigned short ucFindMissingHistoryIDs(unsigned long *ptHistID, unsigned char ucMinProbeCt, unsigned char ucSlots2Search)
{
  unsigned char j, ucRet = (unsigned char) 0xFF;  // ID missing by default
  
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

// purpose ucGetMisOrNoLearnError:
// returns history colunm bit index of affected (by missin or no learn bit, where missin is prior) history IDs
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

// purpose ucGetMisOrNoLearnError:
// param ucDontTouch : do not check this history columns for errors
// returns history colunm bit index of learn error affected  history IDs
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

  // convert if ABS signal was not available once
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
  
  // convert if bad speed
  if ((ushDriveTimeInSec >> 1) < ushDriveTimeOverPalMax )         // TPMS Logic  PAL2 V1.3.pdf 4.2.1.1 "When the vehicle speed has exceeded V_MAX_PAL for more than 50%..."
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
//ClearAlLearNLocatError purpose: delete all learn and locate errors
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
// PutLocatError purpose:
// makes error entry to locate errors if ucZomSlot`s ID is in history
void PutLocatError(unsigned char ucTipicoDiErrori, unsigned char ucZomSlot)
{
  unsigned char i;

  if ( cSumWE > ucZomSlot)
  {
    for ( i = 0; i < cMaxLR ;i++)
    {
      if (ulGetZOMID (ucZomSlot) == ulGetID(i)) // in history ?
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
// PutLocatError purpose:
// makes error entry to locate errors if ucZomSlot`s ID is in history
unsigned char ucGetLocatError(unsigned char ucZomSlot)
{
  unsigned char i;

  if ( cSumWE > ucZomSlot)
  {
    for ( i = 0; i < cMaxLR ;i++)
    {
      if (ulGetZOMID (ucZomSlot) == ulGetID(i)) // in history ?
      {
        return (ucLocatError [i]); 
      }
    }
  }

  return (NoError );
}

// ucNrOfLocatError purpose: CRS_1211_090_001
// returns number of active locate errors
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

// ucNrOfLocatError and force position purpose: CRS_1211_090_001
// returns number of active locate errors
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



// ucNrOfLearnError purpose:
// returns number of active learn errors
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

// TOXpired purpose:
// common timout handling routin, tries to reach any better state of location depending on active learnmodes and
// makes final error entries.
static void TOXpired(void)
{
  if ((unsigned char) 0 == (ucWAState & cWAStateZO))  // ZO not yet finished ?
  {
    if (cCompleteLearn == ucLearnMode )
    {
      if ((unsigned char) 0 < ucFinalFreeze(ucDefMinCt4HistER, (ucNoWheelSensorMounted() > 0) ? ucDefMinCt4ER+3:ucDefMinCt4ER))  // improoved anything ?
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

    if ((ucWAState & cWAStateZO) == 0)  // still not succeeded completed ?
    {
      (void) considerationeDiAssegnazioneCostretto();
    }

    if ((ucWAState & cWAStateZO) == 0)  // still not succeeded completed ?
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
  if (bGetABSSignalDTCActive() == TRUE) //first check if ABS DTCs are active
  {
    ucABSignalMissin = ABSignalMissin ;
  }
#endif
}
// ucTakeOverHistWP purpose:  takeover historical wheel positions if id set matches
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

//**
// \brief  checks ID set to ERstate based on amount of receive events
//
//-----------------------------------------------------------------------------------------------
// \param [in] *ptHistSet pointer to wheel position indexed ID history
// \param [in] ucMinProbeCt level over that ZOM IDs are accepted to be awar
// \param [in] ucSlots2Search amount of ZOM slots to check (start a index 0 to cSumWE) 
//
// \return	Bit n is set if slot n in ZOM has >= ucMinProbeCt probe counts and is part of history
// is 0 if not cMaxLR Bits are set or an 0 IDs are in history
//
//------------------------------------------------------------------------------------------------
///
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
            if ((unsigned char) 0 == ucTakeOverHistWP(i,j)) // no WP available
            { // so take at ER status at least
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

//**
// \brief  checks ID set to ERstate based on amount of receive events
//
//-----------------------------------------------------------------------------------------------
// \param [in] *ptHistSet pointer to wheel position indexed ID history
// \param [in] ucMinProbeCt level over that ZOM IDs are accepted to be awar
// \param [in] ucSlots2Search amount of ZOM slots to check (start a index 0 to cSumWE) 
//
// \return	Bit n is set if slot n in ZOM has >= ucMinProbeCt probe counts and is part of history
// is 0 if not cMaxLR Bits are set or an 0 IDs are in history
//
//------------------------------------------------------------------------------------------------
///
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
        if ( ucWACtrlFixc == tWAPar.ucWACtrl )  // over8 still active ?
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

// ucPasSupplFilter purpose: returns > 0 if AK-telegram is learnable
// learnable telegrams are telegrams from any supplier w/ supplier code >= 0 AND
// has a teltype dedicated to learn
// formerly (p2Tel->byte[cByteOffset2HiNibID] & 0xF0) == ucSupplFilter1 || (p2Tel->byte[cByteOffset2HiNibID] & 0xF0) == ucSupplFilter2
static unsigned char ucPasSupplFilter(tRFTelType * p2Tel)
{
  unsigned char i;
  const unsigned char aucLearnType[] = {cTelTypeSELPAL, cTelTypeSELPAL1, cTelTypeAK35def, cTelTypeAK35defLMA, cTelTypeAK35defLF };
  unsigned char ucRet = (unsigned char) 0;
  
  //if (p2Tel->AK35def .ulID > 0x0FFFFFFL)  filter supplier code > 0
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

// MergeWPandPWP purpose:
// updates aucWPorPWP
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

// GETpucStartAdrWPorPWP purpose:
// updates aucWPorPWP and returns start address of aucWPorPWP
unsigned char * GETpucStartAdrWPorPWP(void)
{
  MergeWPandPWP ();

  return (aucWPorPWP);
}

// GETucWPorPWPofHistCol purpose:
// updates aucWPorPWP and returns WP or PWP [0=FL,1,FR,2=RL,3=RR,4=unknown] of 1 historical column
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

// GETushWAState purpose:
// returns WA internal state as this:
//MSB X 1 -> new WP at history column 3
//    X 1 -> new WP at history column 2
//    X 1 -> new WP at history column 1
//    X 1 -> new WP at history column 0
//
//    X 1 -> 1 forcedZO  
//    X 1 -> 1 TZG (partially WPs allocated)
//    X 1 -> 1 TO
//    X 1 -> 1 error active 
//
//    X 1 -> new ID at history column 3
//    X 1 -> new ID at history column 2
//    X 1 -> new ID at history column 1
//    X 1 -> new ID at history column 0
//
//    X 1 -> all actions are temporarily stopped / BREAK
//    X 1 -> wheel position identification is finished -  4 w.p. are known
//    X 1 -> eigen wheel finished - ER status - 4 Eigen wheel detected
//LSB X 1 -> eigen wheel and wheel identification procedures are active 
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

// checks if forced allocation is possibile
// in case it sets WP corresponding change bit in ushWAState 
// writes forced WP to NVM
static uint8 considerationeDiAssegnazioneCostretto(void)
{
  uint8 ui8ChangeWPSlot = ucForceAutoLocate ();

  if ((uint8) 1 == ucNrOfBitSet ((uint16) ui8ChangeWPSlot ))  // did work ?
  {
    ucWAStateHi |= ui8ChangeWPSlot;
    PutWADataEE(cHistoryWPSet1, aucHistoryWP, (unsigned char) sizeof(aucHistoryWP));

    //for ( i = 0; i < cMaxLR ;i++) // do better not miss error entry 
    //{
    //  if (ui8ChangeWPSlot & ((uint8) (0x10<<i)))
    //  {
    //    PutLocatError (AssegnazioneCostretto ,i);
    //  }
    //}

    return (ui8ChangeWPSlot);
  }

  return((uint8) 0);

}

// dblCk4LocEr purpose:
// checks history IDs if present in zom for not allocated to a WP
// if so, makes sure a locate error is present for the corresponding 
//  slot
static void dblCk4LocEr(void)
{
  uint8 i;
  uint16 zomSlot2Chk;

  zomSlot2Chk = ushIDSetInHist(aulHistoryID,ucDefMinCt4HistER,cSumWE); 
  for ( i = (uint8) 0; i < cSumWE ; i++)
  {
    if ((zomSlot2Chk & (1<<i)) > 0)
    {
      if (((uint8) 0) == (tZOM[i].ucStatus & 0x0F)) // not any WP ?
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
      i = cSumWE;  // done (formerly break;)
  }
}

static uint16 ui16NewIdFits(uint16 ushNewID, uint16 ushHistSet)
{
  uint8 ui8Tmp,i,ui8NewSlot = (uint8) 0,ui8NeWP = (uint8) 0;
  uint16 ui16Ret = 0;

  // WARNING: ZOM might not be aligned to 1st 4 slots yet !!!

  if ((ucNrOfBitSet (ushHistSet) == 3 ) && (ucNrOfBitSet (ushNewID) == 1 )) // 3 history IDs and 1 new ID in ZOM ?
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

    if (cWheelPos_RR < ui8NeWP) // new ID has invalide WP ?
    {
      // extended rival check II 4 history ID might be actively rival to new ID in SL (no error entry is active, so better check actual correlating WP of new ID to historic ones)
      if (GETuCorWPofSlot(ui8NewSlot , &ui8NeWP , &ui8Tmp) > 0) // at least a currently corelating WP ?
      {  // warning ui8NeWP is now in ZOM nomenklatur (1,2,4,8)
        for ( i = 0; i < cSumWE ; i++)  // double check new WP is not rival to active history ID (both have no current WP then)
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
      for ( i = 0; i < cSumWE ; i++)  // double check new WP is not rival to active history ID (both have no current WP then)
        if (( i != ui8NewSlot ) && ((ushHistSet & (1<<i)) > 0) )
          if (ucGetZOMWP (i) == ui8NeWP)
            break;
    }

    if (cSumWE == i) // check for valid PAL telegrams of candidate
    {
      if (((uint8) 0 == tZOM[ui8NewSlot].ucToothTelCt ) && ((uint8) 0 == tZOM[ui8NewSlot].ucToothTelCtNoCorr ))
      {
        i = (uint8) 0;
      }
    }

    if (cSumWE == i)  // new WP is not in use and not actively rival 2 existing history ID's WP and has valid PAL telegrams
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
      if (ucGetZomLqi(i) <= ucDAG_LQIParameter())  // ER candidate fullfills LQI criterion NOT
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