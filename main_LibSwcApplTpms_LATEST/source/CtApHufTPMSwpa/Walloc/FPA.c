
#define FPA_INT

#include "WallocX.h"
#include "Walloc_IF.h"
#include "walloc.h"
#include "FPA.h"
#ifdef Test_LOG_ENABLE

#endif

#ifdef FPA

static void GenCmpVal(unsigned char ucID);

static unsigned short ushMinStretch4Decision(void);

static unsigned short ushGetABSingleTickFr2(unsigned char ucIx);
static unsigned short ushGetABSingleTickFr3(unsigned char ucIx);
static unsigned short ushGetABSingleTickN90(unsigned char ucIx);
static unsigned short ushGetABSingleTickN90Fr2(unsigned char ucIx);
static unsigned short ushGetABSingleTickN90Fr3(unsigned char ucIx);
static unsigned short ushGetABSingleTickTDL(unsigned char ucIx);
static unsigned short ushGetABSingleTickTDLn180(unsigned char ucIx);
static unsigned short ushGetABSingleTickTDL_HS(unsigned char ucIx);
static unsigned short ushGetABSingleTickTDL_LS(unsigned char ucIx);
static unsigned short ushGetABSingleTickTDL_HSn180(unsigned char ucIx);
static unsigned short ushGetABSingleTickTDL_LSn180(unsigned char ucIx);
static unsigned short ushGetABSingleTickPAL(unsigned char ucIx);
static unsigned char ucGetTDL(unsigned char ucCorType);
static unsigned char ucGetTDL100(void);
static unsigned short ushGetTDL210(void);

static void MakeReLine(unsigned char ucSlot, unsigned char * pucLine);
static unsigned char ucBestFit(unsigned char ucSlot1, unsigned char ucSlot2, unsigned char ucPCVal1,  unsigned char ucPCVal2);

#ifdef WAModulTest
extern unsigned char TESTucPrepareFPAResult(void);
extern unsigned char TESTucPrepareFPAFinalResult(void);
extern unsigned char TESTucGetFpaWPOfZomSlot(unsigned char ucSlot);
#endif

#define cMinStretch (unsigned char) 0x30
 #define cFPARefWidth 1

#define cRE15_4_2 0
#define cHSrange 1
#define cLSrange 2
#define cIFS 3

#define RE1562
#define SPEEDWEIGHT

#define FULLTURNINABSTICKS 134
 #define HALFTURNINABSTICKS ((uint16) (FULLTURNINABSTICKS/2))
#define QUARTURNINABSTICKS ((uint16) (HALFTURNINABSTICKS/2))

#define ABSigOFL_MOD_ZAHN (cAbsOverflowValue % FULLTURNINABSTICKS)
#define MINUS_ABSigOFL_MOD_ZAHN  (FULLTURNINABSTICKS - ABSigOFL_MOD_ZAHN)

static unsigned short ush1stABSTickFL;

unsigned short (*fp2ushABSingleTick) (unsigned char ucPos);

unsigned short ushCuRotatsIn05msec = 0;

unsigned char ucFPActive(void)
{
  unsigned char i, ucRet = 0;

  for (i = 0; i < cMaxLR; i++)
  {
    if (tZOM[i].ucToothTelCt > 0)
    {
      ucRet++;
    }
  }
  ucRet  =  (ucRet == cMaxLR) ? (unsigned char) 1:(unsigned char) 0;
  return(ucRet);
}

unsigned char ucConceptFixPos0(unsigned char ucID, tRFTelType * ptInputWA)
{

  fp2ushABSingleTick = ((void *)0);

  if (ptInputWA->Header .ucTType == cTelTypeG4Std )
    fp2ushABSingleTick = ushGetABSingleTickTDL;
   else if (ptInputWA->Header .ucTType == cTelTypeRotatS )
  {
    ushCuRotatsIn05msec = (((unsigned short) (ptInputWA->RotatS .ucSnRH & 0x0F)) << 8) + (unsigned short) ptInputWA->RotatS .ucRL;
    if ( (ptInputWA->RotatS .ucSnRH & 0x80) == 0x80 )
 #ifdef RE1562
      if ( (ptInputWA->RotatS .ucSnRH & 0x20) == 0x20 )
         fp2ushABSingleTick = ushGetABSingleTickTDL_HSn180;
      else
      {
          fp2ushABSingleTick = ushGetABSingleTickTDL_LSn180;
          ushCuRotatsIn05msec <<=2;
       }
#else
      fp2ushABSingleTick = ushGetABSingleTickTDLn180;
#endif
    else
 #ifdef RE1562
      if ( (ptInputWA->RotatS .ucSnRH & 0x20) == 0x20 )
         fp2ushABSingleTick = ushGetABSingleTickTDL_HS;
      else
      {
          fp2ushABSingleTick = ushGetABSingleTickTDL_LS;
          ushCuRotatsIn05msec <<=2;
       }
#else
      fp2ushABSingleTick = ushGetABSingleTickTDL;
#endif
  }
  else if (ptInputWA->Header .ucTType == cTelTypeCorntiFP )
  {
      if ((ptInputWA->ContiFP .ucModeNCode & 0x0C) == 0x08)
      {
        if ((ptInputWA->ContiFP .ucModeNCode & 0x03) == 0x02)
          fp2ushABSingleTick = ushGetABSingleTickFr2 ;
        else if ((ptInputWA->ContiFP .ucModeNCode & 0x03) == 0x03)
          fp2ushABSingleTick = ushGetABSingleTickFr3 ;
        else
          fp2ushABSingleTick = ushGetABSingleTick ;
      }
      else if ((ptInputWA->ContiFP .ucModeNCode & 0x0C) == 0x0C)
      {
        if ((ptInputWA->ContiFP .ucModeNCode & 0x03) == 0x02)
          fp2ushABSingleTick = ushGetABSingleTickN90Fr2 ;
        else if ((ptInputWA->ContiFP .ucModeNCode & 0x03) == 0x03)
          fp2ushABSingleTick = ushGetABSingleTickN90Fr3 ;
        else
          fp2ushABSingleTick = ushGetABSingleTickN90  ;
      }
    ptInputWA->Header .ucTType = cTelTypeAK35def ;
     ptInputWA->AK35def .ucCmdID = cTelTypeAK35def ;
  }
  else if (ptInputWA->Header .ucTType == cTelTypeSELPAL ||  ptInputWA->Header .ucTType == cTelTypeSELPAL1){
     if (ptInputWA->SchraderFP.ucPAL == 0x0){
#ifdef Test_LOG_ENABLE
        tZOM[ucID].ucABSComp[0] = FULLTURNINABSTICKS;
         tZOM[ucID].ucABSComp[1] = FULLTURNINABSTICKS;
         tZOM[ucID].ucABSComp[2] = FULLTURNINABSTICKS;
         tZOM[ucID].ucABSComp[3] = FULLTURNINABSTICKS;
 #endif
        return (0);

     }
     else if (ptInputWA->SchraderFP.ucPAL == 0x01){
 #ifdef Test_LOG_ENABLE
        tZOM[ucID].ucABSComp[0] = FULLTURNINABSTICKS;
         tZOM[ucID].ucABSComp[1] = FULLTURNINABSTICKS;
         tZOM[ucID].ucABSComp[2] = FULLTURNINABSTICKS;
         tZOM[ucID].ucABSComp[3] = FULLTURNINABSTICKS;
 #endif
        return (0);

     }
     else if (ptInputWA->SchraderFP.ucPAL == 0xFF){
 #ifdef Test_LOG_ENABLE
         tZOM[ucID].ucABSComp[0] = FULLTURNINABSTICKS;
          tZOM[ucID].ucABSComp[1] = FULLTURNINABSTICKS;
          tZOM[ucID].ucABSComp[2] = FULLTURNINABSTICKS;
          tZOM[ucID].ucABSComp[3] = FULLTURNINABSTICKS;
 #endif
         return (0);
     }
     fp2ushABSingleTick =  ushGetABSingleTickPAL;
  }
  else if (ptInputWA->Header .ucTType == cTelTypeAK35def){
#ifdef Test_LOG_ENABLE
        tZOM[ucID].ucABSComp[0] = FULLTURNINABSTICKS;
         tZOM[ucID].ucABSComp[1] = FULLTURNINABSTICKS;
         tZOM[ucID].ucABSComp[2] = FULLTURNINABSTICKS;
         tZOM[ucID].ucABSComp[3] = FULLTURNINABSTICKS;
 #endif
   return (0);
  }

  if (!(fp2ushABSingleTick == ((void *)0)) && (fp2ushABSingleTick(0) != cABSStickError))
   {
      GenCmpVal(ucID);

#ifdef Test_LOG_ENABLE
     tZOM[ucID].ucABSComp[0] = (fp2ushABSingleTick(0) +  tZOM[ucID].ushABSRefOffset [0] )%FULLTURNINABSTICKS;
     tZOM[ucID].ucABSComp[1] = (fp2ushABSingleTick(1) +  tZOM[ucID].ushABSRefOffset [1] )%FULLTURNINABSTICKS;
     tZOM[ucID].ucABSComp[2] = (fp2ushABSingleTick(2) +  tZOM[ucID].ushABSRefOffset [2] )%FULLTURNINABSTICKS;
     tZOM[ucID].ucABSComp[3] = (fp2ushABSingleTick(3) +  tZOM[ucID].ushABSRefOffset [3] )%FULLTURNINABSTICKS;
#endif

#ifdef SPEEDWEIGHT
      if (ucGetSpeed() < (unsigned char) 60)
         GenCmpVal(ucID);
#endif
   }

  else
  {
    if (fp2ushABSingleTick == ((void *)0))
      return ((unsigned char) 0);

    PutABSErrorActive ();
    return ((unsigned char) 0);
  }

  if (ucNrOfBitSet ((unsigned short) ucGenDMnD2(10,4,0xFFFF)) == 4)
      return(1);
  else
    return(0);
}

static void GenCmpVal(unsigned char ucID)
{
  unsigned long ulTmp;
  unsigned short ushdN, ushTmp, ushdN2;
  unsigned char i;

  if ((tZOM[ucID].ucToothTelCt > (cFPARefWidth-1))  && (tZOM[ucID].ucResetABSRefFlag !=1))
   {
    if ((unsigned char) (128 + cFPARefWidth + 1) > tZOM[ucID].ucToothTelCt)
      tZOM[ucID].ucToothTelCt++;

    ushTmp = fp2ushABSingleTick(0);

    for (i = 0; i < cSumABSig; i++)
    {

      ushTmp = FULLTURNINABSTICKS;
      ushdN =  fp2ushABSingleTick(i);
      ushdN %= ushTmp;

      if ( ushdN < tZOM[ucID].ucABSRef [i])
       ushdN += ushTmp;
      ushdN -= (unsigned short) tZOM[ucID].ucABSRef [i];

      ushTmp >>= 1;
       ushdN = ( ushdN > ushTmp) ? (ushdN - ushTmp):(ushdN + ushTmp);
      ushdN2 = (ushdN+HALFTURNINABSTICKS)% FULLTURNINABSTICKS;
      if (tZOM[ucID].ucToothTelCt > cFPARefWidth + 1)
      {
        if (tZOM[ucID].ucToothTelCt < (unsigned char) (128 + cFPARefWidth))
        {
          tZOM[ucID].ushMVdN[i] += ushdN;
          tZOM[ucID].ushMVdN2[i] += ushdN2;
        }
        else
        {
           if (tZOM[ucID].ucToothTelCt == (unsigned char) (128 + cFPARefWidth) )
          {
            tZOM[ucID].ushMVdN[i] +=64;
            tZOM[ucID].ushMVdN[i] >>= 7;
            tZOM[ucID].ushMVdN2[i] +=64;
            tZOM[ucID].ushMVdN2[i] >>= 7;

          }
          ushTmp = tZOM[ucID].ushMVdN[i];
           ulTmp = (unsigned long) ushTmp << 7;
          ulTmp -= (unsigned long) ushTmp;
          ulTmp += (unsigned long) ushdN;
          ulTmp += (unsigned long) 64;
           ulTmp >>= 7;
          tZOM[ucID].ushMVdN[i] = (unsigned short) ulTmp;

          ushTmp = tZOM[ucID].ushMVdN2[i];
           ulTmp = (unsigned long) ushTmp << 7;
          ulTmp -= (unsigned long) ushTmp;
          ulTmp += (unsigned long) ushdN2;
          ulTmp += (unsigned long) 64;
           ulTmp >>= 7;
          tZOM[ucID].ushMVdN2[i] = (unsigned short) ulTmp;
        }
      }
      else
      {
        tZOM[ucID].ushMVdN[i] = ushdN;
        tZOM[ucID].ushMVdN2[i] = ushdN2;
      }

      /*______________________________________________________________________________________________________________________________________________________________________*/
      /*Sum of current differences of dN pos i n and the corresponding mean value of dN pos i n.*/
      if (tZOM[ucID].ucToothTelCt < (unsigned char) (128 + cFPARefWidth))
      {
         ushTmp =  tZOM[ucID].ushMVdN[i] / ((unsigned short) (tZOM[ucID].ucToothTelCt - cFPARefWidth));
        if ( ushdN > ushTmp )
          ushTmp = ushdN - ushTmp;
        else
          ushTmp -= ushdN;
      }
      else
      {
         if (ushdN > tZOM[ucID].ushMVdN[i])
          ushTmp = ushdN - tZOM[ucID].ushMVdN[i];
        else
          ushTmp = tZOM[ucID].ushMVdN[i] - ushdN;
      }
      ushTmp += tZOM[ucID].ushPosCompVal[i];     /**/
      if (ushTmp > tZOM[ucID].ushPosCompVal[i]) /* overflow check */
        tZOM[ucID].ushPosCompVal[i] = ushTmp;  /**/
        if (tZOM[ucID].ucToothTelCt < (unsigned char) (128 + cFPARefWidth))
      {
         ushTmp =  tZOM[ucID].ushMVdN2[i] / ((unsigned short) (tZOM[ucID].ucToothTelCt - cFPARefWidth));
        if ( ushdN2 > ushTmp )
          ushTmp = ushdN2 - ushTmp;
        else
          ushTmp -= ushdN2;
      }
      else
      {
         if (ushdN2 > tZOM[ucID].ushMVdN2[i])
          ushTmp = ushdN2 - tZOM[ucID].ushMVdN2[i];
        else
          ushTmp = tZOM[ucID].ushMVdN2[i] - ushdN2;
      }
      ushTmp += tZOM[ucID].ushPosCompVal2[i];     /**/
      if (ushTmp > tZOM[ucID].ushPosCompVal2[i]) /* overflow check */
        tZOM[ucID].ushPosCompVal2[i] = ushTmp;  /**/
    }
  }
  else
  {
     if (tZOM[ucID].ucToothTelCt < (unsigned char) 1)
      ush1stABSTickFL = fp2ushABSingleTick(0);
    for (i = 0; i < cMaxLR; i++)
    {
      ushdN =  (fp2ushABSingleTick(i) % FULLTURNINABSTICKS);
       tZOM[ucID].ucABSRef[i] = ushdN;
    }
   if(tZOM[ucID].ucResetABSRefFlag == 1)
      tZOM[ucID].ucResetABSRefFlag=0;
   else
      tZOM[ucID].ucToothTelCt++;
  }
}

void RebuildABSRef(unsigned char ucWP)
 {
  unsigned char i;

  for (i = 0; i < cSumWE ;i++)
  {
    if (tZOM[i].ucToothTelCt > 0)
    {
#ifdef Test_LOG_ENABLE
      tZOM[i].ushABSRefOffset [ucWP] = (tZOM[i].ushABSRefOffset [ucWP] + ABSigOFL_MOD_ZAHN)% FULLTURNINABSTICKS;
#endif
      if ( tZOM[i].ucABSRef [ucWP] > ((unsigned char)ABSigOFL_MOD_ZAHN) )
        tZOM[i].ucABSRef [ucWP] -= ((unsigned char)ABSigOFL_MOD_ZAHN);
      else
        tZOM[i].ucABSRef [ucWP] += ((unsigned char)MINUS_ABSigOFL_MOD_ZAHN);
    }
  }
}

void ReNewABSRef(void)
 {
  unsigned char i;

  for (i = 0; i < cSumWE ;i++)
  {
     if (tZOM[i].ucToothTelCt != 0)
      tZOM[i].ucResetABSRefFlag = 1;
  }
}

/************************************************************************************************************
 ** function:   SortBiggest1st
 **
 ** ---------------------------------------------------------------------------------------------------------
 **
 ** purpose: grades an unsigned character array indirect via index array (bubblesort algorithm)
 ** ---------------------------------------------------------------------------------------------------------
 **
 ** input: ptVal = pointer to unsigned character array wich contains values to be graded
 **        ptIx = pointer to index array (uc) to safe the graduation result
 **        ucMax = amount of elements in the arrays above
 **
 **
 ** output:ptIx = sortde index array (element 0 cointains the index to the BIGGEST number in ptVal)
 **
 ************************************************************************************************************/

/************************************************************************************************************
 ** changes in 2003
 **
 ** 05.01.2004 pb - set up
 ************************************************************************************************************/

void SortBiggest1st(unsigned char *ptVal, unsigned char *ptIx, unsigned char ucMax)
{
  unsigned char i,j, ucBuffer;

  for(i=0;i<ucMax;i++)
  {
    ptIx[i] = i;
  }

  for (i = 1; i < ucMax; i++)
  {
    for (j = i; j >= 1; j--)
    {
      if (ptVal[ptIx[j]] > ptVal[ptIx[j-1]])
      {
        ucBuffer = ptIx[j];
        ptIx[j] = ptIx[j-1];
        ptIx[j-1] = ucBuffer;
      }
      else
      {
        break;
      }
    }
  }
}

void Very1stABSTickIinit(void)
{
  ush1stABSTickFL = 0;
}

static unsigned short ushMinStretch4Decision(void)
{
  return ( 24000 );
 }
 unsigned short ushGetABSingleTickFr2(unsigned char ucIx)
 {
   return (ushGetABSingleTick (ucIx)-((unsigned short) ucGetTDL100()));
}
unsigned short ushGetABSingleTickFr3(unsigned char ucIx)
 {
 return (ushGetABSingleTick (ucIx) - ushGetTDL210());
}
unsigned short ushGetABSingleTickN90(unsigned char ucIx)
{
  return (ushGetABSingleTick (ucIx)- QUARTURNINABSTICKS);
}
unsigned short ushGetABSingleTickN90Fr2(unsigned char ucIx)
 {
  return (ushGetABSingleTick (ucIx)-((unsigned short) ucGetTDL100() + QUARTURNINABSTICKS));
}
unsigned short ushGetABSingleTickN90Fr3(unsigned char ucIx)
 {
  return (ushGetABSingleTick (ucIx)-(ushGetTDL210() + QUARTURNINABSTICKS));
}
unsigned short ushGetABSingleTickTDL(unsigned char ucIx)
{
  return ( ushGetABSingleTick (ucIx) + (unsigned short) ucGetTDL(cRE15_4_2 ) );
}
unsigned short ushGetABSingleTickTDLn180(unsigned char ucIx)
{
  return ( ushGetABSingleTick (ucIx) + (unsigned short) ucGetTDL(cRE15_4_2 ) - HALFTURNINABSTICKS);
}
unsigned short ushGetABSingleTickTDL_HS(unsigned char ucIx)
{
  return ( ushGetABSingleTick (ucIx) + (unsigned short) ucGetTDL(cHSrange ) );
}
unsigned short ushGetABSingleTickTDL_LS(unsigned char ucIx)
{
  return ( ushGetABSingleTick (ucIx) + (unsigned short) ucGetTDL(cLSrange ) );
}
unsigned short ushGetABSingleTickTDL_HSn180(unsigned char ucIx)
{
  return ( ushGetABSingleTick (ucIx) + (unsigned short) ucGetTDL(cHSrange ) - (unsigned short) ucGetTDL(cIFS ));
}
unsigned short ushGetABSingleTickTDL_LSn180(unsigned char ucIx)
{
  return ( ushGetABSingleTick (ucIx) + (unsigned short) ucGetTDL(cLSrange ) - (unsigned short) ucGetTDL(cIFS ));
}
 unsigned short ushGetABSingleTickPAL(unsigned char ucIx)
{
  return ( ushGetABSingleTick (ucIx));
}
static unsigned char ucGetTDL(unsigned char ucCorType)
{
  unsigned short ushVtmp;
  unsigned char ucIx;
  unsigned char * puCTab;
          static const unsigned char cucCvHS[] =     {27,   27,   27,   27,   27,   27,   27,   27,   27,   27,   27,   27,   27,   27,   27,   27,   27,   27,   27,   27,   27,   27,   27,   27,   27,   27,   27,   27,   27,   25,   22,   21,   24,   25,   25,   25,   25,   25,   25,   25};
   static const unsigned char cucIFS[] =      {46,   47,   47,   47,   47,   47,   47,   47,   47,   47,   47,   47, 47,   46,   46,   45,   45,   45,   43,   45,   45,   46,   46,   48,   49,   47,   47,   49,   49,   48,   49,   46,   48,   50,   50,   50,   50,   50,   50,   50};
   static const unsigned char cucCvLS[] =     {48,   48,   46,   42,   39,   36,   34,   33,   31,   30,   30,   28,   26,   26,   24,   24,   25,   22,   21,   24,   25,   24,   26,   21,   18,   19,   22,   30,   30,   30,   30,   30,   30,   30,   30,   30,   30,   30,   30,   30};
      static const unsigned char cucTDLatV[] = { 48,   48,   48,   46,   42,   39,   37,   36,   34,   34,   32,   31,   31,   29,   29,   29,   29,   28,   28,   28,   28,   28,   28,   28,   27,   27,   27,   27,   27, 27,   27,   27,   27,   27,   27,   27,   27,   27,   27,   27 };
     switch ( ucCorType )
  {
  case cRE15_4_2:
    puCTab = (unsigned char *) cucTDLatV;
    break;
  case cHSrange:
    puCTab = (unsigned char *) cucCvHS;
    break;
  case cLSrange:
    puCTab = (unsigned char *) cucCvLS;
    break;
  case cIFS:
    puCTab = (unsigned char *) cucIFS;
    break;
  default:
    puCTab = (unsigned char *) cucTDLatV;
    break;
  }
   if (ushCuRotatsIn05msec > 0)
  {
    ushVtmp = (ushCuRotatsIn05msec>>1) + 48000;
    ushVtmp /= ushCuRotatsIn05msec;
   }
  else
    ushVtmp =  (unsigned short) ucGetSpeed();
  if ((unsigned short) ucGetSpeed() >= 20)
    if ((ushVtmp >  ((unsigned short) ucGetSpeed() + 20)) || (ushVtmp <  ((unsigned short) ucGetSpeed() - 20)))
       ushVtmp =  (unsigned short) ucGetSpeed();
   ushVtmp =  (unsigned short) ucGetSpeed();

  ucIx = (unsigned char) ((((ushVtmp * 10)/5)+5)/10);
   if (ucIx > 0)
  {
    ucIx--;
    if (ucIx > (sizeof(cucTDLatV) - (unsigned char) 1))
      ucIx = sizeof(cucTDLatV) - (unsigned char) 1;
  }

  return(puCTab[ucIx]);
}
static unsigned char ucGetTDL100(void)
{
  unsigned short ushVtmp;
  unsigned char ucIx;
                                                                                static const unsigned char cucTDL100atV[] = {6,12,18,24,30,36,42,48,55,61,67,73,79,85,91,97,103,109,115,121,127,133,139,145,152,158};

  ushVtmp =  (unsigned short) ucGetSpeed();
  ucIx = (unsigned char) ((((ushVtmp * 10)/5)+5)/10);
   if (ucIx > 0)
  {
    ucIx--;
    if (ucIx > (unsigned char) 25)
      ucIx = (unsigned char) 25;
  }

  return(cucTDL100atV[ucIx]);
}
static unsigned short ushGetTDL210(void)
{
  unsigned short ushVtmp;
  unsigned char ucIx;
                                                                                static const unsigned short cushTDL210atV[] = {13,25,38,51,64,76,89,102,115,127,140,153,165,178,191,204,216,229,242,255,267,280,293,305,318, 331};

  ushVtmp =  (unsigned short) ucGetSpeed();
  ucIx = (unsigned char) ((((ushVtmp * 10)/5)+5)/10);
   if (ucIx > 0)
  {
    ucIx--;
    if (ucIx > (unsigned char) 25)
      ucIx = (unsigned char) 25;
  }

  return(cushTDL210atV[ucIx]);
}

unsigned char ucFPDecPossible(unsigned short * p2ushSlots,unsigned char ucCtLimit)
 {
  unsigned char i, ucRdyCt = (unsigned char) 0;

  *p2ushSlots = 0;
  for ( i = 0; i < cSumWE; i++)
  {
    if ( tZOM[i].ushPosCompVal2[0] > 0)
      if ( ucCtLimit <= tZOM[i].ucToothTelCt)
      {
        tZOM[i].ucStatus |= cZOMStatWPDec;
        ucRdyCt ++;
        *p2ushSlots |= (unsigned short) (1<<i);
        if (TooFewPalTels == ucGetLocatError(i))
          PutLocatError (NoError , i);
      }
      else
      {
        PutLocatError (TooFewPalTels, i);
      }
    else
    {
      PutLocatError (TooFewPalTels, i);
    }
  }

  return ( ucRdyCt );
}

unsigned char ucAdjABSIface(unsigned char ucID, tRFTelType * ptInputWA)
 {
  fp2ushABSingleTick = ((void *)0);

  if (ptInputWA->Header .ucTType == cTelTypeG4Std )
    fp2ushABSingleTick = ushGetABSingleTickTDL;
   else if (ptInputWA->Header .ucTType == cTelTypeRotatS )
  {
    ushCuRotatsIn05msec = (((unsigned short) (ptInputWA->RotatS .ucSnRH & 0x0F)) << 8) + (unsigned short) ptInputWA->RotatS .ucRL;
    if ( (ptInputWA->RotatS .ucSnRH & 0x80) == 0x80 )
 #ifdef RE1562
      if ( (ptInputWA->RotatS .ucSnRH & 0x20) == 0x20 )
         fp2ushABSingleTick = ushGetABSingleTickTDL_HSn180;
      else
      {
        fp2ushABSingleTick = ushGetABSingleTickTDL_LSn180;
        ushCuRotatsIn05msec <<=2;
       }
#else
      fp2ushABSingleTick = ushGetABSingleTickTDLn180;
#endif
    else
 #ifdef RE1562
      if ( (ptInputWA->RotatS .ucSnRH & 0x20) == 0x20 )
         fp2ushABSingleTick = ushGetABSingleTickTDL_HS;
      else
      {
        fp2ushABSingleTick = ushGetABSingleTickTDL_LS;
        ushCuRotatsIn05msec <<=2;
       }
#else
      fp2ushABSingleTick = ushGetABSingleTickTDL;
#endif
  }
  else if (ptInputWA->Header .ucTType == cTelTypeCorntiFP )
  {
    if ((ptInputWA->ContiFP .ucModeNCode & 0x0C) == 0x08)
    {
      if ((ptInputWA->ContiFP .ucModeNCode & 0x03) == 0x02)
        fp2ushABSingleTick = ushGetABSingleTickFr2 ;
      else if ((ptInputWA->ContiFP .ucModeNCode & 0x03) == 0x03)
        fp2ushABSingleTick = ushGetABSingleTickFr3 ;
      else
        fp2ushABSingleTick = ushGetABSingleTick ;
    }
    else if ((ptInputWA->ContiFP .ucModeNCode & 0x0C) == 0x0C)
    {
      if ((ptInputWA->ContiFP .ucModeNCode & 0x03) == 0x02)
        fp2ushABSingleTick = ushGetABSingleTickN90Fr2 ;
      else if ((ptInputWA->ContiFP .ucModeNCode & 0x03) == 0x03)
        fp2ushABSingleTick = ushGetABSingleTickN90Fr3 ;
      else
        fp2ushABSingleTick = ushGetABSingleTickN90  ;
    }
    ptInputWA->Header .ucTType = cTelTypeAK35def ;
     ptInputWA->AK35def .ucCmdID = cTelTypeAK35def ;
  }
  else if (ptInputWA->Header .ucTType == cTelTypeSELPAL ||  ptInputWA->Header .ucTType == cTelTypeSELPAL1)
  {
    if (ptInputWA->SchraderFP.ucPAL == 0x0){
 #ifdef Test_LOG_ENABLE
      tZOM[ucID].ucABSComp[0] = FULLTURNINABSTICKS;
       tZOM[ucID].ucABSComp[1] = FULLTURNINABSTICKS;
       tZOM[ucID].ucABSComp[2] = FULLTURNINABSTICKS;
       tZOM[ucID].ucABSComp[3] = FULLTURNINABSTICKS;
 #endif
      return (0);
    }
    else if (ptInputWA->SchraderFP.ucPAL == 0x01){
 #ifdef Test_LOG_ENABLE
      tZOM[ucID].ucABSComp[0] = FULLTURNINABSTICKS;
       tZOM[ucID].ucABSComp[1] = FULLTURNINABSTICKS;
       tZOM[ucID].ucABSComp[2] = FULLTURNINABSTICKS;
       tZOM[ucID].ucABSComp[3] = FULLTURNINABSTICKS;
 #endif
      return (0);

    }
    else if (ptInputWA->SchraderFP.ucPAL == 0xFF){
 #ifdef Test_LOG_ENABLE
      tZOM[ucID].ucABSComp[0] = FULLTURNINABSTICKS;
       tZOM[ucID].ucABSComp[1] = FULLTURNINABSTICKS;
       tZOM[ucID].ucABSComp[2] = FULLTURNINABSTICKS;
       tZOM[ucID].ucABSComp[3] = FULLTURNINABSTICKS;
 #endif
      return (0);
    }
    fp2ushABSingleTick =  ushGetABSingleTickPAL;
  }
  else if (ptInputWA->Header .ucTType == cTelTypeAK35def){
#ifdef Test_LOG_ENABLE
    tZOM[ucID].ucABSComp[0] = FULLTURNINABSTICKS;
     tZOM[ucID].ucABSComp[1] = FULLTURNINABSTICKS;
     tZOM[ucID].ucABSComp[2] = FULLTURNINABSTICKS;
     tZOM[ucID].ucABSComp[3] = FULLTURNINABSTICKS;
 #endif
    return (0);
  }

  if (!(fp2ushABSingleTick == ((void *)0)) && (fp2ushABSingleTick(0) != cABSStickError))
    return ((unsigned char) 1);
   else
  {
     if (fp2ushABSingleTick == ((void *)0))
      return ((unsigned char) 0);

    PutABSErrorActive ();
    return ((unsigned char) 0);
  }
}

void BuildCmpVal(unsigned char ucID)
{
  GenCmpVal(ucID);

#ifdef Test_LOG_ENABLE
  tZOM[ucID].ucABSComp[0] = (fp2ushABSingleTick(0) +  tZOM[ucID].ushABSRefOffset [0] )% FULLTURNINABSTICKS;
  tZOM[ucID].ucABSComp[1] = (fp2ushABSingleTick(1) +  tZOM[ucID].ushABSRefOffset [1] )% FULLTURNINABSTICKS;
  tZOM[ucID].ucABSComp[2] = (fp2ushABSingleTick(2) +  tZOM[ucID].ushABSRefOffset [2] )% FULLTURNINABSTICKS;
  tZOM[ucID].ucABSComp[3] = (fp2ushABSingleTick(3) +  tZOM[ucID].ushABSRefOffset [3] )% FULLTURNINABSTICKS;
#endif

#ifdef SPEEDWEIGHT
  if (ucGetSpeed() < (unsigned char) 60)
     GenCmpVal(ucID);
#endif
 }

unsigned char ucGenDMnD2(unsigned char ucDifDblWPinPC, unsigned char ucDifWPinPc, unsigned short ushSlotFilter)
{
  union
   {
    unsigned long ulTmp;
    unsigned char ucSort[4];
  } tTmp;

  unsigned long ulCmpSum;
  unsigned char i,j, ucRelCmpVal[4][4], ucTmp, ucMinIx, ucIdCt, ucRet = 0;
   unsigned short ushPoSlots = 0;

  ucIdCt = ucFPDecPossible (&ushPoSlots, cMinCt4Dec );
  ushPoSlots &= ushSlotFilter ;
  ucIdCt = ucNrOfBitSet(ushPoSlots);

  if (ucGetERState () > (unsigned char) 0)
   {
    ushPoSlots &= 0x000F;
    ucIdCt = ucNrOfBitSet(ushPoSlots);
  }
  else
  {
    if (ucIdCt > cMaxLR)
    {
        ucIdCt = 0;
     }
    if ( 0 < ucIdCt)
    {
      ushPoSlots = ushAlignZOM(ushPoSlots);
     }
  }

  if ( ucIdCt > 0 )
  {
     for (i = 0; i < cMaxLR; i++)
     {
      if ((ushPoSlots & (1<<i)) > 0)
      {
        ulCmpSum = 0;
         for ( j = 0; j < cSumABSig; j++)
          ulCmpSum += ((tZOM[i].ushPosCompVal2 [j] < tZOM[i].ushPosCompVal [j]) ? tZOM[i].ushPosCompVal2 [j]:tZOM[i].ushPosCompVal [j]);
        for ( j = 0; j < cSumABSig; j++)
         {
          if (tZOM[i].ushPosCompVal[j] < tZOM[i].ushPosCompVal2[j])
          {
            if (tZOM[i].ushPosCompVal[j] > 0)
            {
              tTmp.ulTmp =  (unsigned long) tZOM[i].ushPosCompVal[j] * 100;
              tTmp.ulTmp /= ulCmpSum;
              ucRelCmpVal[i][j] = (unsigned char) tTmp.ulTmp;
            }
            else
              ucRelCmpVal[i][j] = (unsigned char) 1;
          }
          else
          {
             if (tZOM[i].ushPosCompVal2[j] > 0)
            {
              tTmp.ulTmp =  (unsigned long) tZOM[i].ushPosCompVal2[j] * 100;
              tTmp.ulTmp /= ulCmpSum;
              ucRelCmpVal[i][j] = (unsigned char) tTmp.ulTmp;
            }
            else
              ucRelCmpVal[i][j] = (unsigned char) 1;
          }
 #ifdef pb_ModulTest_050104
          tZOM[i].ucRelCmpVal[j] = ucRelCmpVal[i][j];
#endif
        }
#ifdef pb_ModulTest_050104
        tZOM[i].ucRelCmpVal[cSumABSig-1] = ucRelCmpVal[i][cSumABSig-1];
#endif
      }
      else
      {
         for ( j = 0; j < cSumABSig; j++)
           ucRelCmpVal[i][j] = (unsigned char) 0;
      }
    }
       tTmp.ulTmp = (unsigned long) 0;
      ucTmp = (unsigned char) 0;
       for (i = 0; i < cMaxLR; i++)
      {
        if ((ushPoSlots & (1<<i)) > 0)
        {
          SortBiggest1st(ucRelCmpVal[i],tTmp.ucSort,cSumABSig);
           if ((ucRelCmpVal[i][tTmp.ucSort[cSumABSig-2]] - ucRelCmpVal[i][tTmp.ucSort[cSumABSig-1]]) > ucDifWPinPc)
           {
             for ( j = 0; j < cMaxLR; j++)
               if ( j != tTmp.ucSort[cSumABSig-1])
                ucRelCmpVal[i][j] = (unsigned char) 0;
              else
                if ((unsigned char) 0 == ucRelCmpVal[i][j])
                  ucRelCmpVal[i][j] = (unsigned char) 1;
            ucTmp |= (unsigned char) (1<<i);
          }
          else
          {
             for ( j = 0; j < cMaxLR; j++)
               ucRelCmpVal[i][j] = (unsigned char) 0;
            PutLocatError (AmbigWP ,i);
            tZOM[i].ucStatus &= (unsigned char) 0xF0;
           }
        }
        else
        {
          PutLocatError (AmbigWP ,i);
          tZOM[i].ucStatus &= (unsigned char) 0xF0;
         }
      }
      if (ucTmp > (unsigned char) 0)
       {
        for ( j = 0; j < cMaxLR; j++ )
         {
          ucMinIx = cMaxLR;
           for (i = 0; i < cMaxLR; i++)
           {
            if (ucRelCmpVal[i][j] > 0)
             {
              if (ucMinIx == cMaxLR)
                ucMinIx = i;
               else
               {
                if (ucRelCmpVal[i][j] < ucRelCmpVal[ucMinIx][j])
                {
                  if ((ucRelCmpVal[ucMinIx][j] - ucRelCmpVal[i][j]) > ucDifDblWPinPC)
                  {
                    ucTmp &= (unsigned char) ~(1<<ucMinIx);
                     ucRelCmpVal[ucMinIx][j] = 0;
                    PutLocatError (AmbigWP ,ucMinIx);
                    tZOM[ucMinIx].ucStatus &= (unsigned char) 0xF0;
                     ucMinIx = i;
                   }
                  else
                  {
                    ucTmp &= (unsigned char) ~(1<<ucMinIx);
                     ucRelCmpVal[ucMinIx][j] = 0;
                    PutLocatError (RivalSensors ,ucMinIx);
                    tZOM[ucMinIx].ucStatus &= (unsigned char) 0xF0;
                     ucTmp &= (unsigned char) ~(1<<i);
                     ucRelCmpVal[i][j] = 0;
                    PutLocatError (RivalSensors ,i);
                    tZOM[i].ucStatus &= (unsigned char) 0xF0;
                     ucMinIx = cMaxLR;
                   }
                }
                else
                {
                  if ((ucRelCmpVal[i][j] - ucRelCmpVal[ucMinIx][j]) > ucDifDblWPinPC)
                  {
                     ucTmp &= (unsigned char) ~(1<<i);
                     ucRelCmpVal[i][j] = 0;
                    PutLocatError (AmbigWP ,i);
                    tZOM[i].ucStatus &= (unsigned char) 0xF0;
                   }
                  else
                  {
                    ucTmp &= (unsigned char) ~(1<<ucMinIx);
                     ucRelCmpVal[ucMinIx][j] = 0;
                    PutLocatError (RivalSensors ,ucMinIx);
                    tZOM[ucMinIx].ucStatus &= (unsigned char) 0xF0;
                     ucTmp &= (unsigned char) ~(1<<i);
                     ucRelCmpVal[i][j] = 0;
                    PutLocatError (RivalSensors ,i);
                    tZOM[i].ucStatus &= (unsigned char) 0xF0;
                     ucMinIx = cMaxLR;
                   }
                }
              }
            }
          }
        }
        if ( (unsigned char) 0 < ucTmp )
        {
          for (i = 0; i < cMaxLR; i++)
          {
#ifdef pb_ModulTest_050104
            if ( cMinCt4Dec > tZOM[i].ucToothTelCt)
              break;
#endif
            if ((ucTmp & (1<<i)) > 0)
              for ( j = 0; j < cMaxLR; j++)
                if (ucRelCmpVal[i][j] > 0 )
                 {
                   if (ucGetWPOfCol(ucGetColOfID(&tZOM[i].ulID)) == j)
                   {
                    SetZOMWP(i,j);
                    PutLocatError (NoError ,i);
                  }
                  else
                  {
                    if (ucRelCmpVal[i][j] < 15)
                     {
                      SetZOMWP(i,j);
                      PutLocatError (NoError ,i);
                    }
                    else
                    {
                      ucTmp &= (unsigned char) ~(1<<i);
                      break;
                    }
                  }
                }

          }
          ucRet = ucTmp;
         }
      }
  }
#ifdef pb_ModulTest_050104
  else
   {
    for (i = 0; i < cMaxLR; i++)
      for ( j = 0; j < cMaxLR; j++)
        tZOM[i].ucRelCmpVal[j] = (unsigned char) 0;
  }
#endif
#ifdef WAModulTest
  ucRet = (TESTucPrepareFPAFinalResult ()) & ushPoSlots;
#endif
  return (ucRet);
}

unsigned char ucGetCorER(unsigned short * p2Slots )
{
  unsigned char i,j, aucReLine[4],ucErCt = 0;
  unsigned long ulCmpSum, ulTmp;

  for (i = 0; i < cSumWE; i++)
   {
    if ((*p2Slots & (1<<i)) > 0)
    {
      if ( cMinCt4Dec  <= tZOM[i].ucToothTelCt)
      {
        ulCmpSum = 0;
         for ( j = 0; j < cMaxLR; j++)
          ulCmpSum += ((tZOM[i].ushPosCompVal2 [j] < tZOM[i].ushPosCompVal [j]) ? tZOM[i].ushPosCompVal2 [j]:tZOM[i].ushPosCompVal [j]);

        for ( j = 0; j < cMaxLR; j++)
         {
          if (tZOM[i].ushPosCompVal[j] < tZOM[i].ushPosCompVal2[j])
          {
            if (tZOM[i].ushPosCompVal[j] > 0)
            {
              ulTmp =  (unsigned long) tZOM[i].ushPosCompVal[j] * 100;
              ulTmp /= ulCmpSum;
              aucReLine[j] = (unsigned char) ulTmp;
            }
            else
              aucReLine[j] = (unsigned char) 1;
          }
          else
          {
             if (tZOM[i].ushPosCompVal2[j] > 0)
            {
              ulTmp =  (unsigned long) tZOM[i].ushPosCompVal2[j] * 100;
              ulTmp /= ulCmpSum;
              aucReLine[j] = (unsigned char) ulTmp;
            }
            else
              aucReLine[j] = (unsigned char) 1;
          }
          if (0 == aucReLine[j])
            aucReLine[j] = 1;

        }
        if (ucCorLine(aucReLine, 8) > 0)
          ucErCt++;
        else
          *p2Slots &= ~(1<<i);
       }
      else
        *p2Slots &= ~(1<<i);
     }
  }
  return (ucErCt );
}

unsigned char ucCorLine(unsigned char  p2Line[], const unsigned char ucMaxDev)
{
  unsigned char i;
  const unsigned char ucDefMeanVal = 0x19;

  for (i = 0; i < cMaxLR ; i++)
  {
    if ( ucDefMeanVal > p2Line[i] )
    {
      if ( (ucDefMeanVal - p2Line[i]) > ucMaxDev)
        break;
    }
    else
      if ( (p2Line[i] - ucDefMeanVal) > ucMaxDev)
        break;
  }

  if (cMaxLR == i)
    return ((unsigned char) 0);
  else
    return ((unsigned char) 1);
}

void ProvideFPAlgo2MT_DAG(void)
{
  union
   {
    unsigned long ulTmp;
    unsigned char ucSort[4];
  } tTmp;

  unsigned long ulCmpSum;

  unsigned char  ucRelCmpVal[cSumWE][4];

  unsigned char i,j ;

  for (i = 0; i < cSumWE; i++)
   {
    if (0 == tZOM[i].ushPosCompVal2[0])
      continue;
    ulCmpSum = 0;
     for ( j = 0; j < cSumABSig; j++)
      ulCmpSum += ((tZOM[i].ushPosCompVal2 [j] < tZOM[i].ushPosCompVal [j]) ? tZOM[i].ushPosCompVal2 [j]:tZOM[i].ushPosCompVal [j]);

    for ( j = 0; j < cSumABSig; j++)
     {
      if (tZOM[i].ushPosCompVal[j] < tZOM[i].ushPosCompVal2[j])
      {
        if (tZOM[i].ushPosCompVal[j] > 0)
        {
          tTmp.ulTmp =  (unsigned long) tZOM[i].ushPosCompVal[j] * 100;
          tTmp.ulTmp /= ulCmpSum;
          ucRelCmpVal[i][j] = (unsigned char) tTmp.ulTmp;
        }
        else
          ucRelCmpVal[i][j] = (unsigned char) 1;
      }
      else
      {
         if (tZOM[i].ushPosCompVal2[j] > 0)
        {
          tTmp.ulTmp =  (unsigned long) tZOM[i].ushPosCompVal2[j] * 100;
          tTmp.ulTmp /= ulCmpSum;
          ucRelCmpVal[i][j] = (unsigned char) tTmp.ulTmp;
        }
        else
          ucRelCmpVal[i][j] = (unsigned char) 1;
      }
      if (0 == ucRelCmpVal[i][j])
        ucRelCmpVal[i][j] = 1;

      tZOM[i].ushRelCmpVal[j] = ucRelCmpVal[i][j];
     }
  }
   tTmp.ulTmp = (unsigned long) 0;
  for (i = 0; i < cSumWE; i++)
  {
    if (0 == tZOM[i].ushPosCompVal2[0])
      continue;
    SortBiggest1st(ucRelCmpVal[i],tTmp.ucSort,cSumABSig);
     tZOM[i].ucDeltaMin = (ucRelCmpVal[i][tTmp.ucSort[cSumABSig-2]] - ucRelCmpVal[i][tTmp.ucSort[cSumABSig-1]]);
      ucRelCmpVal[i][tTmp.ucSort[cSumABSig-2]] = (ucRelCmpVal[i][tTmp.ucSort[cSumABSig-2]]) > 2 ? ucRelCmpVal[i][tTmp.ucSort[cSumABSig-2]] : 2;
    ucRelCmpVal[i][tTmp.ucSort[cSumABSig-1]] = (ucRelCmpVal[i][tTmp.ucSort[cSumABSig-1]]) > 2 ? ucRelCmpVal[i][tTmp.ucSort[cSumABSig-1]] : 2;
     if ( (tZOM[i].ucToothTelCtCorrLearnBit + tZOM[i].ucToothTelCtCorrNoLearnBit) > 6)
    {
      tZOM[i].ushLqi = (unsigned short) ( ((tZOM[i].ucToothTelCtCorrLearnBit + tZOM[i].ucToothTelCtCorrNoLearnBit - 2) * tZOM[i].ucDeltaMin)/ucRelCmpVal[i][tTmp.ucSort[cSumABSig-1]] );
     }
    else{
      tZOM[i].ushLqi = (unsigned short) 0;
    }
  }
}

 unsigned short ushReduceCorel24(unsigned short ushCandidate)
{
  unsigned char i, j, ucCorWP[cSumWE],ucWPinPerc[cSumWE];

  for (i = 0; i < cSumWE ; i++)
   {
    if ( (ushCandidate & (1<<i)) > 0)
    {
      if ((unsigned char) 0 == GETuCorWPofSlot(i, &ucCorWP[i], &ucWPinPerc[i]))
      {
        if ( cWheelPos_RR < ucGetWPOfCol (ucGetColOfID ( &tZOM [i].ulID)))
         {
          ushCandidate &= ((unsigned short) (~(1<<i)));
          tZOM[i].ucStatus &= 0xF0;
        }
        else
        {
          ucCorWP[i] = (1<<ucGetWPOfCol (ucGetColOfID ( &tZOM [i].ulID)));
           ucWPinPerc[i] = 0;
        }
      }
    }
  }

  for (i = 0; i < cSumWE ; i++)
   {
    tZOM[i].ucStatus &= 0xF0;
    if ( (ushCandidate & (1<<i)) > 0)
    {
      tZOM[i].ucStatus |= ucCorWP [i];
       for (j = i; j < cSumWE; j++)
      {
        if ( ((ushCandidate & (1<<j)) > 0) && (j != i) )
        {
          if (ucCorWP [i] == ucCorWP[j])
          {
             if (i == ucBestFit(i,j,ucWPinPerc [i],ucWPinPerc [j]))
            {
               ushCandidate &= ((unsigned short) (~(1<<j)));
            }
            else
            {
               ushCandidate &= ((unsigned short) (~(1<<i)));
              tZOM[i].ucStatus &= 0xF0;
              break;
            }
          }
        }
      }
    }
  }

  return (ushCandidate);
}

  unsigned char GETuCorWPofSlot(unsigned char ucSlot, unsigned char * pucWP, unsigned char * pucPcVal)
{
  unsigned char aucReLine[4], aucSortedShares[4];

  *pucWP = (unsigned char) 0;
  *pucPcVal = (unsigned char) 100;

  if ( cMinCt4Dec  <= tZOM[ucSlot].ucToothTelCt)
  {
#ifdef WAModulTest
    if ( TESTucGetFpaWPOfZomSlot(ucSlot) > 3 )
       return (0);
    else
    {
      *pucWP = 1<<TESTucGetFpaWPOfZomSlot (ucSlot);
      *pucPcVal = (unsigned char) 5;
      return (0xFF);
    }
#endif
    MakeReLine(ucSlot,aucReLine);
    SortBiggest1st(aucReLine,aucSortedShares,4);

    if (((aucReLine[aucSortedShares[2]] - aucReLine[aucSortedShares[3]]) > 4) && (15 > aucReLine[aucSortedShares[3]]))
     {
      *pucPcVal = aucReLine[aucSortedShares[3]];
      *pucWP = (unsigned char) (1<<aucSortedShares[3]);
      return ((unsigned char) 0xFF);
    }
  }
  return ((unsigned char) 0);
}

 static void MakeReLine(unsigned char ucSlot, unsigned char * pucLine)
{
  unsigned char j;
  unsigned long ulTmp, ulCmpSum = 0;

  for ( j = 0; j < cMaxLR; j++)
    ulCmpSum += ((tZOM[ucSlot].ushPosCompVal2 [j] < tZOM[ucSlot].ushPosCompVal [j]) ? tZOM[ucSlot].ushPosCompVal2 [j]:tZOM[ucSlot].ushPosCompVal [j]);

  for ( j = 0; j < cMaxLR; j++)
  {
    if (tZOM[ucSlot].ushPosCompVal[j] < tZOM[ucSlot].ushPosCompVal2[j])
    {
      if (tZOM[ucSlot].ushPosCompVal[j] > 0)
      {
        ulTmp =  (unsigned long) tZOM[ucSlot].ushPosCompVal[j] * 100;
        ulTmp /= ulCmpSum;
        pucLine[j] = (unsigned char) ulTmp;
      }
      else
        pucLine[j] = (unsigned char) 1;
    }
    else
    {
       if (tZOM[ucSlot].ushPosCompVal2[j] > 0)
      {
        ulTmp =  (unsigned long) tZOM[ucSlot].ushPosCompVal2[j] * 100;
        ulTmp /= ulCmpSum;
        pucLine[j] = (unsigned char) ulTmp;
      }
      else
        pucLine[j] = (unsigned char) 1;
    }
   }
}

 static unsigned char ucBestFit(unsigned char ucSlot1, unsigned char ucSlot2, unsigned char ucPCVal1,  unsigned char ucPCVal2)
{
  unsigned char ucRet = 0xFF;

  if (cMaxLR > ucGetColOfID ( &tZOM [ucSlot1].ulID))
   {
    if (cMaxLR  <= ucGetColOfID ( &tZOM [ucSlot2].ulID))
     {
      ucRet = ucSlot1;
    }
  }
  else if (cMaxLR  > ucGetColOfID ( &tZOM [ucSlot2].ulID))
   {
    ucRet = ucSlot2;
  }
  if (0xFF == ucRet)
   {
    if ((ucDAG_LQIParameter() <= ucGetZomLqi(ucSlot1)) && (ucDAG_LQIParameter() > ucGetZomLqi(ucSlot2)))
     {
      ucRet = ucSlot1;
    }
    else if ((ucDAG_LQIParameter() <= ucGetZomLqi(ucSlot2)) && (ucDAG_LQIParameter() > ucGetZomLqi(ucSlot1)))
    {
      ucRet = ucSlot2;
    }
    else
    {
      if ((ucGetZomTelCtLearnBit(ucSlot1) > ((unsigned char) 15)) && (ucGetZomTelCtLearnBit(ucSlot2) <= ((unsigned char) 15)))
       {
        ucRet = ucSlot1;
      }
      else if ((ucGetZomTelCtLearnBit(ucSlot2) > ((unsigned char) 15)) && (ucGetZomTelCtLearnBit(ucSlot1) <= ((unsigned char) 15)))
      {
        ucRet = ucSlot2;
      }
      else
      {
        if (ucGetZomLqi(ucSlot2) > ucGetZomLqi(ucSlot1))
         {
          ucRet = ucSlot2;
        }
        else
        {
          ucRet = ucSlot1;
        }
      }
    }
  }

  return (ucRet);
}

#ifdef pb_ModulTest_050104
void TESTPrintToothZOM_HL(void)
{
  unsigned char i,j;
  unsigned char aucWPSeq[][3] = {"FL","RL","FR","RR"};

  for (i = 0; i < 4;i++)
  {
    printf(";ID[%s];Status[%s];ucFPATelCt[%s]",aucWPSeq[i],aucWPSeq[i],aucWPSeq[i]);
    for ( j  = 0; j < 4 ; j++)
      printf(";dN[%s][%d]",aucWPSeq[i],j);
    for ( j  = 0; j < 4 ; j++)
      printf(";MVdN[%s][%d]",aucWPSeq[i],j);
    for ( j  = 0; j < 4 ; j++)
      printf(";CmpVal[%s][%d]",aucWPSeq[i],j);
    for ( j  = 0; j < 4 ; j++)
      printf(";MVdN2[%s][%d]",aucWPSeq[i],j);
    for ( j  = 0; j < 4 ; j++)
      printf(";CmpVal2[%s][%d]",aucWPSeq[i],j);
    for ( j  = 0; j < 4 ; j++)
      printf(";RelCmp[%s][%d]",aucWPSeq[i],j);
  }
}
void TESTPrintToothZOMAsLine(void)
{
  unsigned long ulID;

  ulID = ulGetRatIDatWP(0);
    TESTPrintFPAZOMSlot(ucGetZOMPosOfID( &ulID));

    ulID = ulGetRatIDatWP(2);
    TESTPrintFPAZOMSlot(ucGetZOMPosOfID( &ulID));

    ulID = ulGetRatIDatWP(1);
    TESTPrintFPAZOMSlot(ucGetZOMPosOfID( &ulID));

    ulID = ulGetRatIDatWP(3);
    TESTPrintFPAZOMSlot(ucGetZOMPosOfID( &ulID));

  printf(";");

}
void TESTPrintFPAZOMSlot(unsigned char ucSlot)
{
  unsigned char j;

  printf(";%lu;0x%02X;%d",tZOM[ucSlot].ulID,tZOM[ucSlot].ucStatus,tZOM[ucSlot].ucToothTelCt );
  for ( j  = 0; j < 4 ; j++)
    printf(";%d",tZOM[ucSlot].ucCurdN[j]);
  for ( j  = 0; j < 4 ; j++)
    printf(";%d", tZOM[ucSlot].ushMVdN [j]);
  for ( j  = 0; j < 4 ; j++)
    printf(";%d", tZOM[ucSlot].ushPosCompVal [j]);
  for ( j  = 0; j < 4 ; j++)
    printf(";%d", tZOM[ucSlot].ushMVdN2 [j]);
  for ( j  = 0; j < 4 ; j++)
    printf(";%d", tZOM[ucSlot].ushPosCompVal2 [j]);
  for ( j  = 0; j < 4 ; j++)
    printf(";%d",tZOM[ucSlot].ucRelCmpVal [j]);
}
void TESTPrinToothZOMSummary(unsigned char i)
{
  unsigned char j;

  if (i < 4)
  {
      printf(" %d; 0x%02X; %d; %d;",tZOM[i].ulID,tZOM[i].ucStatus ,tZOM[i].ucProbeCt ,tZOM[i].ucToothTelCt);
      for ( j = 0; j < cMaxLR; j++)
        printf("%d;",tZOM[i].ucRelCmpVal[j]);
      for ( j = 0; j < cMaxLR; j++)
        printf("%d;",tZOM[i].ushPosCompVal[j]);
  }
  else
    for ( j = 0; j < 3; j++)
     printf(" %d; %d; %d; %d;",0,0,0,0);
}
#endif
 #endif

