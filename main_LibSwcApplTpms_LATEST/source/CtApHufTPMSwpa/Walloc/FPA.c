/*
 *(c)  Electronics GmbH     BEE1     2012
 *================================================================================================
 *
 *$Archive: /BMW/G3kompakt/Sw/SC6demo/template_can/application/source/tssappl/walloc/FPA.c $
 *
  *
 *------------------------------------------------------------------------------------------------
 *
 *author:        Peter Brand                Electronics GmbH
 *
 *intials:       pb
 *
 *
 *
 *Modul Description
 *
 *
 *Global description:
 *Purpose:
 *
 *
 *
 *Modul Modification
 *
 *
 *
 * $Log: /BMW/G3kompakt/Sw/SC6demo/template_can/application/source/tssappl/walloc/FPA.c $
 * 
 * 6     2.04.14 11:22 Peter
 * support for Schrader Pal rf telegram (SELPAL 2)
 *
 * 5     21.09.12 16:27 Peter
 * increase MinFPA Tel count from 5 to 14 !!
 *
 * 4     7.09.12 17:48 Peter
 * pb_ModulTest_050104
 *
 * 3     7.09.12 16:54 Peter
 * adaption to sensor revision 15 6 2
 * works with 2 delay correction tabs and different speed ranges (lo/hi)
 * on correction tab 4 2nd frames of the multiburst
 *
 * 2     21.08.12 17:52 Peter
 * new module structure (FPA and AEC, CA seperated)
 *
 * 1     17.08.12 17:27 Peter
 *
 * 1     10.08.12 10:09 Peter
 *
    13.01.04 14:05 Peter


Include
*/
#define FPA_INT

#include "WallocX.h"
#include "Walloc_IF.h"
#include "walloc.h"
#include "FPA.h"
#ifdef Test_LOG_ENABLE

#endif


#ifdef FPA
/*
Prototypes
*/
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
/*
Macros
*/
#define cMinStretch (unsigned char) 0x30  // ID in this slot achieved minimum way stretch between 1st RF tel reception and current reception PURE FPA
#define cFPARefWidth 1



#define cRE15_4_2 0
#define cHSrange 1
#define cLSrange 2
#define cIFS 3

#define RE1562
#define SPEEDWEIGHT

#define FULLTURNINABSTICKS 134                   // change this if ABS resolution changes 
#define HALFTURNINABSTICKS ((uint16) (FULLTURNINABSTICKS/2))
#define QUARTURNINABSTICKS ((uint16) (HALFTURNINABSTICKS/2))

#define ABSigOFL_MOD_ZAHN (cAbsOverflowValue % FULLTURNINABSTICKS)
#define MINUS_ABSigOFL_MOD_ZAHN  (FULLTURNINABSTICKS - ABSigOFL_MOD_ZAHN)
/*
Data
*/
static unsigned short ush1stABSTickFL;

unsigned short (*fp2ushABSingleTick) (unsigned char ucPos);

unsigned short ushCuRotatsIn05msec = 0;
/*
Definitions
*/
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
    fp2ushABSingleTick = ushGetABSingleTickTDL; // replace by `ushGetABSingleTick´ for switching off teethdelay
  else if (ptInputWA->Header .ucTType == cTelTypeRotatS )
  {
    ushCuRotatsIn05msec = (((unsigned short) (ptInputWA->RotatS .ucSnRH & 0x0F)) << 8) + (unsigned short) ptInputWA->RotatS .ucRL;
    //ushCuRotatsIn05msec <<=2; // RE 15 4 2
    if ( (ptInputWA->RotatS .ucSnRH & 0x80) == 0x80 ) // 2nd tel ?
#ifdef RE1562
      if ( (ptInputWA->RotatS .ucSnRH & 0x20) == 0x20 ) // hi speed range ?
        fp2ushABSingleTick = ushGetABSingleTickTDL_HSn180;
      else
      {
          fp2ushABSingleTick = ushGetABSingleTickTDL_LSn180;
          ushCuRotatsIn05msec <<=2; // change 2msec resolution to 500usec
      }
#else
      fp2ushABSingleTick = ushGetABSingleTickTDLn180;
#endif
    else  // 1st Tel
#ifdef RE1562
      if ( (ptInputWA->RotatS .ucSnRH & 0x20) == 0x20 ) // hi speed range ?
        fp2ushABSingleTick = ushGetABSingleTickTDL_HS;
      else
      {
          fp2ushABSingleTick = ushGetABSingleTickTDL_LS;
          ushCuRotatsIn05msec <<=2; // change 2msec resolution to 500usec
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
    ptInputWA->Header .ucTType = cTelTypeAK35def ;  // open the doors and let them all in
    ptInputWA->AK35def .ucCmdID = cTelTypeAK35def ;
  }
  else if (ptInputWA->Header .ucTType == cTelTypeSELPAL ||  ptInputWA->Header .ucTType == cTelTypeSELPAL1){
	  // check validity of PAL byte
	  if (ptInputWA->SchraderFP.ucPAL == 0x0){	// no PAL data
#ifdef Test_LOG_ENABLE
		  tZOM[ucID].ucABSComp[0] = FULLTURNINABSTICKS; // not valid
		  tZOM[ucID].ucABSComp[1] = FULLTURNINABSTICKS; // not valid
		  tZOM[ucID].ucABSComp[2] = FULLTURNINABSTICKS; // not valid
		  tZOM[ucID].ucABSComp[3] = FULLTURNINABSTICKS; // not valid
#endif
		  return (0);

	  }
	  else if (ptInputWA->SchraderFP.ucPAL == 0x01){  // no Correlation
#ifdef Test_LOG_ENABLE
		  tZOM[ucID].ucABSComp[0] = FULLTURNINABSTICKS; // not valid
		  tZOM[ucID].ucABSComp[1] = FULLTURNINABSTICKS; // not valid
		  tZOM[ucID].ucABSComp[2] = FULLTURNINABSTICKS; // not valid
		  tZOM[ucID].ucABSComp[3] = FULLTURNINABSTICKS; // not valid
#endif
		  return (0);

	  }
	  else if (ptInputWA->SchraderFP.ucPAL == 0xFF){  // overflow
#ifdef Test_LOG_ENABLE
		   tZOM[ucID].ucABSComp[0] = FULLTURNINABSTICKS; // not valid
		   tZOM[ucID].ucABSComp[1] = FULLTURNINABSTICKS; // not valid
		   tZOM[ucID].ucABSComp[2] = FULLTURNINABSTICKS; // not valid
		   tZOM[ucID].ucABSComp[3] = FULLTURNINABSTICKS; // not valid
#endif
		   return (0);
	  }
	  fp2ushABSingleTick =  ushGetABSingleTickPAL;
  }
  else if (ptInputWA->Header .ucTType == cTelTypeAK35def){
#ifdef Test_LOG_ENABLE
		  tZOM[ucID].ucABSComp[0] = FULLTURNINABSTICKS; // not valid
		  tZOM[ucID].ucABSComp[1] = FULLTURNINABSTICKS; // not valid
		  tZOM[ucID].ucABSComp[2] = FULLTURNINABSTICKS; // not valid
		  tZOM[ucID].ucABSComp[3] = FULLTURNINABSTICKS; // not valid
#endif
	return (0);
  }

  if (!(fp2ushABSingleTick == ((void *)0)) && (fp2ushABSingleTick(0) != cABSStickError))//(ptInputWA->G4Std .ucTelSentnEnergy & 0x0F) > 0)  /* FPE valid ? */
  {
      GenCmpVal(ucID);
	  
	  /* store compensated ABS values */
#ifdef Test_LOG_ENABLE
	  tZOM[ucID].ucABSComp[0] = (fp2ushABSingleTick(0) +  tZOM[ucID].ushABSRefOffset [0] )%FULLTURNINABSTICKS; 
	  tZOM[ucID].ucABSComp[1] = (fp2ushABSingleTick(1) +  tZOM[ucID].ushABSRefOffset [1] )%FULLTURNINABSTICKS; 
	  tZOM[ucID].ucABSComp[2] = (fp2ushABSingleTick(2) +  tZOM[ucID].ushABSRefOffset [2] )%FULLTURNINABSTICKS; 
	  tZOM[ucID].ucABSComp[3] = (fp2ushABSingleTick(3) +  tZOM[ucID].ushABSRefOffset [3] )%FULLTURNINABSTICKS; 
#endif

#ifdef SPEEDWEIGHT
      if (ucGetSpeed() < (unsigned char) 60)  // FP telegrams at low speed are high precise and therefore to be double weighted
        GenCmpVal(ucID);
#endif //SPEEDWEIGHT
  }

  else
  {
    if (fp2ushABSingleTick == ((void *)0))
      return ((unsigned char) 0);
    
    PutABSErrorActive ();
    return ((unsigned char) 0); 
  }

  
  if (ucNrOfBitSet ((unsigned short) ucGenDMnD2(10,4,0xFFFF)) == 4) //(ucGenDMnD() > 0)
	  return(1);
  else
    return(0);
}

static void GenCmpVal(unsigned char ucID)
{
  unsigned long ulTmp;
  unsigned short ushdN, ushTmp, ushdN2;
  unsigned char i;

  if ((tZOM[ucID].ucToothTelCt > (cFPARefWidth-1))  && (tZOM[ucID].ucResetABSRefFlag !=1)) // == cFPARefWidth
  {
    if ((unsigned char) (128 + cFPARefWidth + 1) > tZOM[ucID].ucToothTelCt)
      tZOM[ucID].ucToothTelCt++;

    ushTmp = fp2ushABSingleTick(0);

    for (i = 0; i < cSumABSig; i++)
    {
      /*______________________________________________________________________________________________________________________________________________________________________*/
      /* Difference to integer revolution amount (=modulo) between very first and current RF receptions of a fix position sending TPMS sensor at wheel position I: dNintpos i */
      ushTmp = FULLTURNINABSTICKS;
      ushdN =  fp2ushABSingleTick(i);
      ushdN %= ushTmp;                                                         // ABStickMOD96

      if ( ushdN < tZOM[ucID].ucABSRef [i]) // allways stay in the range 0..96   ABStickMOD96 < ABSrefMOD96 ->
       ushdN += ushTmp;                                                        // -> ABStickMOD96 + 96
      ushdN -= (unsigned short) tZOM[ucID].ucABSRef [i];                       // dN = ABStick'MOD96 - ABSrefMOD96

      ushTmp >>= 1; //96 -> 48 ( make a half turn)
      ushdN = ( ushdN > ushTmp) ? (ushdN - ushTmp):(ushdN + ushTmp);           // dN > 48 ? YES-> dN = dN - 48 ; NO -> dN = dN + 48
      //ushdN2= ( ushdN > ushTmp) ? (ushdN - ushTmp):(ushdN + ushGetAnZahn());   // dN2 > 48 ? YES-> dN = dN - 48 ; NO -> dN = dN + 96
	  //ushdN2= ( ushdN > ushTmp) ? (ushdN ): ushdN;
	  ushdN2 = (ushdN+HALFTURNINABSTICKS)% FULLTURNINABSTICKS;
      /*______________________________________________________________________________________________________________________________________________________________________*/
      /* Mean difference to integer number of revolutions between current RF telegram receptions and 1st RF telegramm reception of one fix pos sending TPMS sensor at wheel position I:*/
      if (tZOM[ucID].ucToothTelCt > cFPARefWidth + 1)
      {
        if (tZOM[ucID].ucToothTelCt < (unsigned char) (128 + cFPARefWidth))
        { // arithmet. mean val
          tZOM[ucID].ushMVdN[i] += ushdN;
          tZOM[ucID].ushMVdN2[i] += ushdN2;
        }
        else
        { // weighted mean val: MVdN = (MVdNalt x 127 + dN) / 128
          if (tZOM[ucID].ucToothTelCt == (unsigned char) (128 + cFPARefWidth) )
          {
            tZOM[ucID].ushMVdN[i] +=64;
            tZOM[ucID].ushMVdN[i] >>= 7;
            tZOM[ucID].ushMVdN2[i] +=64;
            tZOM[ucID].ushMVdN2[i] >>= 7;

          }
          ushTmp = tZOM[ucID].ushMVdN[i]; // generate weighted mean value
          ulTmp = (unsigned long) ushTmp << 7;
          ulTmp -= (unsigned long) ushTmp;
          ulTmp += (unsigned long) ushdN;
          ulTmp += (unsigned long) 64;  // round
          ulTmp >>= 7;
          tZOM[ucID].ushMVdN[i] = (unsigned short) ulTmp;

          ushTmp = tZOM[ucID].ushMVdN2[i]; // generate weighted mean value 2
          ulTmp = (unsigned long) ushTmp << 7;
          ulTmp -= (unsigned long) ushTmp;
          ulTmp += (unsigned long) ushdN2;
          ulTmp += (unsigned long) 64;  // round
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
      { // generate deviation with arithmet. mean val
        ushTmp =  tZOM[ucID].ushMVdN[i] / ((unsigned short) (tZOM[ucID].ucToothTelCt - cFPARefWidth));
        if ( ushdN > ushTmp )
          ushTmp = ushdN - ushTmp;
        else
          ushTmp -= ushdN;
      }
      else
      { // generate deviation with weighted mean val
        if (ushdN > tZOM[ucID].ushMVdN[i])
          ushTmp = ushdN - tZOM[ucID].ushMVdN[i];
        else
          ushTmp = tZOM[ucID].ushMVdN[i] - ushdN;
      }
      // ushTmp now contains deviation

      ushTmp += tZOM[ucID].ushPosCompVal[i];     /**/
      if (ushTmp > tZOM[ucID].ushPosCompVal[i]) /* overflow check */
        tZOM[ucID].ushPosCompVal[i] = ushTmp;  /**/

      // the same 4 2nd PosCompareVal
       if (tZOM[ucID].ucToothTelCt < (unsigned char) (128 + cFPARefWidth))
      { // generate deviation with arithmet. mean val
        ushTmp =  tZOM[ucID].ushMVdN2[i] / ((unsigned short) (tZOM[ucID].ucToothTelCt - cFPARefWidth));
        if ( ushdN2 > ushTmp )
          ushTmp = ushdN2 - ushTmp;
        else
          ushTmp -= ushdN2;
      }
      else
      { // generate deviation with weighted mean val
        if (ushdN2 > tZOM[ucID].ushMVdN2[i])
          ushTmp = ushdN2 - tZOM[ucID].ushMVdN2[i];
        else
          ushTmp = tZOM[ucID].ushMVdN2[i] - ushdN2;
      }
      // ushTmp now contains deviation

      ushTmp += tZOM[ucID].ushPosCompVal2[i];     /**/
      if (ushTmp > tZOM[ucID].ushPosCompVal2[i]) /* overflow check */
        tZOM[ucID].ushPosCompVal2[i] = ushTmp;  /**/
    }
  }
  else
  { // very 1st reception
    if (tZOM[ucID].ucToothTelCt < (unsigned char) 1)
      ush1stABSTickFL = fp2ushABSingleTick(0);
    for (i = 0; i < cMaxLR; i++)
    {
      ushdN =  (fp2ushABSingleTick(i) % FULLTURNINABSTICKS);
      //ushTmp = (unsigned short) tZOM[ucID].ucABSRef[i] * (unsigned short) tZOM[ucID].ucToothTelCt;
      //ushTmp += ushdN;
      //ushTmp /= (unsigned short) (tZOM[ucID].ucToothTelCt + 1);
      //ZOM[ucID].ucABSRef[i] = (unsigned char) ushTmp;
	  tZOM[ucID].ucABSRef[i] = ushdN;
    }
	if(tZOM[ucID].ucResetABSRefFlag == 1)
		tZOM[ucID].ucResetABSRefFlag=0;
	else
		//no need to increment the counter after a reference point reset
		tZOM[ucID].ucToothTelCt++;
  }
}

void RebuildABSRef(unsigned char ucWP)    // provided interface function of Walloc module -> wallocX.h decl
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

void ReNewABSRef(void)  // provided interface function of Walloc module -> wallocX.h decl
{
  unsigned char i;

  for (i = 0; i < cSumWE ;i++)
  {
    //tZOM[i].ucToothTelCt = 0;
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
  return ( 24000 ); // minimum waystretch in teeth (500m = 500/Utyre * 96 = 500m/2m * 96 = 24000) which must be achieved by one ID for WP assignment; 3000 = 73m
}
//
// WARNING: for this functions OVER- and UNDERFLOWS are considered and welcome START
//
unsigned short ushGetABSingleTickFr2(unsigned char ucIx)  // angletracking for the 2nd conti frame (100msec delay to the fixpoint)
{
   return (ushGetABSingleTick (ucIx)-((unsigned short) ucGetTDL100()));
}
unsigned short ushGetABSingleTickFr3(unsigned char ucIx)  // angletracking for the 3rd conti frame (210msec delay to the fixpoint)
{
 return (ushGetABSingleTick (ucIx) - ushGetTDL210());
}
unsigned short ushGetABSingleTickN90(unsigned char ucIx)
{// reduce current ABS value by 90° ( = 90/360 x 96 = 24 teeth)
 return (ushGetABSingleTick (ucIx)- QUARTURNINABSTICKS);
}
unsigned short ushGetABSingleTickN90Fr2(unsigned char ucIx)  // angletracking for the 2nd conti frame (100msec delay to the fixpoint)
{
  return (ushGetABSingleTick (ucIx)-((unsigned short) ucGetTDL100() + QUARTURNINABSTICKS));
}
unsigned short ushGetABSingleTickN90Fr3(unsigned char ucIx)  // angletracking for the 2nd conti frame (100msec delay to the fixpoint)
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
//
// WARNING: for this functions OVER- and UNDERFLOWS are considered and welcome END
//
unsigned short ushGetABSingleTickPAL(unsigned char ucIx)
{
  return ( ushGetABSingleTick (ucIx));
}
static unsigned char ucGetTDL(unsigned char ucCorType)
{
  unsigned short ushVtmp;
  unsigned char ucIx;
  unsigned char * puCTab;
  // ToothDeLay at Vehicle Speed: telegramm sent at speed x has a delay to fixed 180° delay variable by speed.
  //  At speed 0 tx delay is 0 -> rx correction to fixed point at 180° = 180° (= 48ticks)
  //  at speed = 5km/h tx delay is 32°-> rx correction = 148° (= 39ticks)
  //   ...
  //  at speed 130km/h tx delay = 135° -> rx correction = 45° (=12ticks)
  //  at speed 200km/h tx delay = 117° -> rx correction = 63° (=17ticks)
  //////////////////////////////////////////////////////////////////////////////
  // WARNING: the numbers are based ALL on a 96 teeth = 360 ° resolution  !!! //
  //////////////////////////////////////////////////////////////////////////////
  //                                                                                                                                                 |--> enlarged speed range 4 new sensor types
  // speedrange:                             5km/h        20              40      50      60      70      80      90     100     110     120     130     140     150     160     170     180     190     200
  //static const unsigned char cucCvLS[] =     {48, 48,	47,	43,	40,	36,	33,	30,	29,	27,	26,	25,	24,	24,	23,	22,	22,	20,	19,	19,	19,	19,	20,	17,	18,	16,	17,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20};  // sensor 15 6 2 DSA
  static const unsigned char cucCvHS[] =     {27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	25,	22,	21,	24,	25,	25,	25,	25,	25,	25,	25};  // sensor 15 6 2 DSA
  static const unsigned char cucIFS[] =      {46,	47,	47,	47,	47,	47,	47,	47,	47,	47,	47,	47, 47,	46,	46,	45,	45,	45,	43,	45,	45,	46,	46,	48,	49,	47,	47,	49,	49,	48,	49,	46,	48,	50,	50,	50,	50,	50,	50,	50};  // sensor 15 6 2 DSA
  static const unsigned char cucCvLS[] =     {48,	48,	46,	42,	39,	36,	34,	33,	31,	30,	30,	28,	26,	26,	24,	24,	25,	22,	21,	24,	25,	24,	26,	21,	18,	19,	22,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30};  // sensor 15 6 2 ALX
  //static const unsigned char cucCvLS[] =     {48,	48,	46,	45,	40,	37,	33,	32,	31,	30,	29,	29,	18,	18,	19,	16,	17,	16,	15,	16,	17,	16,	18,	20,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17};  // sensor 15 6 2 DSA n-table (not v)
  //static const unsigned char cucCvHS[] =     {27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	26,	26,	26,	26,	26,	24,	24,	24,	24,	24,	24,	24,	24,	24};  // sensor 15 6 2 ALX
  //static const unsigned char cucIFS[] =      {};    // sensor 15 6 2 ALX
  //static const unsigned char cucTDLatV[] = { 48	,39	,35	,32	,28	,25	,25	,23	,23	,21	,21	,18	,18	,18	,18	,18	,18	,18	,15	,15	,15	,12	,12	,12	,12	,12, 3,	23,	23,	22,	23,	23,	20,	18,	21,	23,	23,	20,	22,	17 };
  static const unsigned char cucTDLatV[] = { 48,	48,	48,	46,	42,	39,	37,	36,	34,	34,	32,	31,	31,	29,	29,	29,	29,	28,	28,	28,	28,	28,	28,	28,	27,	27,	27,	27,	27, 27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27 }; //RE 15 4 2 alx
//static const unsigned char cucTDLatV[] = { 48,	48,	48,	45,	43,	42,	40,	38,	37,	36,	34,	33,	32,	31,	30,	29,	28,	27,	27,	26,	26,	25,	25,	25,	25,	25,	25,	25,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24 }; //RE 15 5 2 alx
//static const unsigned char cucTDLatV[] = {48,48,47,47,46,45,44,44,43,42,42,41,41,40,40,39,39,38,38,38,38,37,37,37,36,37,37,38,37,38,38,38,38,37,37,38,38,38,38,38,38};  //DSA 15_5 MV
//static const unsigned char cucTDLatV[] = {48,48,48,46,42,38,34,31,29,27,26,25,24,24,23,23,22,22,22,22,22,21,22,21,19,18,19,21,21,20,20,20,19,19,19,19,19,19,19};//DSA 15 4
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

  //calculate index with the help of the global rotats ush
  if (ushCuRotatsIn05msec > 0)
  {
    ushVtmp = (ushCuRotatsIn05msec>>1) + 48000;
    ushVtmp /= ushCuRotatsIn05msec; // ushVtmp contains sensor revolution in `10 rev per minute`, means: 200 = 2000revs per minute
  }
  else
    ushVtmp =  (unsigned short) ucGetSpeed();
  if ((unsigned short) ucGetSpeed() >= 20)
    if ((ushVtmp >  ((unsigned short) ucGetSpeed() + 20)) || (ushVtmp <  ((unsigned short) ucGetSpeed() - 20)))  // plausi check for sensor revolution
      ushVtmp =  (unsigned short) ucGetSpeed();
  //if ( ucCorType == (unsigned char) cucCvHS)  // 4 high speed we take speed as index not sensor's revol info
   ushVtmp =  (unsigned short) ucGetSpeed();

  ucIx = (unsigned char) ((((ushVtmp * 10)/5)+5)/10);  // /5 = stepsize in tooth delay tab
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
  // ToothDeLay at Vehicle Speed 210msec after fixpoint:
  //////////////////////////////////////////////////////////////////////////////
  // WARNING: the numbers are based ALL on a 96 teeth = 360 ° resolution  !!! //
  //////////////////////////////////////////////////////////////////////////////
  static const unsigned char cucTDL100atV[] = {6,12,18,24,30,36,42,48,55,61,67,73,79,85,91,97,103,109,115,121,127,133,139,145,152,158};

  ushVtmp =  (unsigned short) ucGetSpeed();
  ucIx = (unsigned char) ((((ushVtmp * 10)/5)+5)/10);  // /5 = stepsize in tooth delay tab
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
  // ToothDeLay at Vehicle Speed 210msec after fixpoint:
  //////////////////////////////////////////////////////////////////////////////
  // WARNING: the numbers are based ALL on a 96 teeth = 360 ° resolution  !!! //
  //////////////////////////////////////////////////////////////////////////////
  static const unsigned short cushTDL210atV[] = {13,25,38,51,64,76,89,102,115,127,140,153,165,178,191,204,216,229,242,255,267,280,293,305,318, 331};

  ushVtmp =  (unsigned short) ucGetSpeed();
  ucIx = (unsigned char) ((((ushVtmp * 10)/5)+5)/10);  // /5 = stepsize in tooth delay tab
  if (ucIx > 0)
  {
    ucIx--;
    if (ucIx > (unsigned char) 25)
      ucIx = (unsigned char) 25;
  }

  return(cushTDL210atV[ucIx]);
}

unsigned char ucFPDecPossible(unsigned short * p2ushSlots,unsigned char ucCtLimit) // returns nr of zom slots ready to decide
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

unsigned char ucAdjABSIface(unsigned char ucID, tRFTelType * ptInputWA) // returns > 0 if ABS iface could be adjusted - means further FPA allocate actions possible
{
  fp2ushABSingleTick = ((void *)0);

  if (ptInputWA->Header .ucTType == cTelTypeG4Std )
    fp2ushABSingleTick = ushGetABSingleTickTDL; // replace by `ushGetABSingleTick´ for switching off teethdelay
  else if (ptInputWA->Header .ucTType == cTelTypeRotatS )
  {
    ushCuRotatsIn05msec = (((unsigned short) (ptInputWA->RotatS .ucSnRH & 0x0F)) << 8) + (unsigned short) ptInputWA->RotatS .ucRL;
    //ushCuRotatsIn05msec <<=2; // RE 15 4 2
    if ( (ptInputWA->RotatS .ucSnRH & 0x80) == 0x80 ) // 2nd tel ?
#ifdef RE1562
      if ( (ptInputWA->RotatS .ucSnRH & 0x20) == 0x20 ) // hi speed range ?
        fp2ushABSingleTick = ushGetABSingleTickTDL_HSn180;
      else
      {
        fp2ushABSingleTick = ushGetABSingleTickTDL_LSn180;
        ushCuRotatsIn05msec <<=2; // change 2msec resolution to 500usec
      }
#else
      fp2ushABSingleTick = ushGetABSingleTickTDLn180;
#endif
    else  // 1st Tel
#ifdef RE1562
      if ( (ptInputWA->RotatS .ucSnRH & 0x20) == 0x20 ) // hi speed range ?
        fp2ushABSingleTick = ushGetABSingleTickTDL_HS;
      else
      {
        fp2ushABSingleTick = ushGetABSingleTickTDL_LS;
        ushCuRotatsIn05msec <<=2; // change 2msec resolution to 500usec
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
    ptInputWA->Header .ucTType = cTelTypeAK35def ;  // open the doors and let them all in
    ptInputWA->AK35def .ucCmdID = cTelTypeAK35def ;
  }
  else if (ptInputWA->Header .ucTType == cTelTypeSELPAL ||  ptInputWA->Header .ucTType == cTelTypeSELPAL1)
  {
    // check validity of PAL byte
    if (ptInputWA->SchraderFP.ucPAL == 0x0){	// no PAL data
#ifdef Test_LOG_ENABLE
      tZOM[ucID].ucABSComp[0] = FULLTURNINABSTICKS; // not valid
      tZOM[ucID].ucABSComp[1] = FULLTURNINABSTICKS; // not valid
      tZOM[ucID].ucABSComp[2] = FULLTURNINABSTICKS; // not valid
      tZOM[ucID].ucABSComp[3] = FULLTURNINABSTICKS; // not valid
#endif
      return (0);
    }
    else if (ptInputWA->SchraderFP.ucPAL == 0x01){  // no Correlation
#ifdef Test_LOG_ENABLE
      tZOM[ucID].ucABSComp[0] = FULLTURNINABSTICKS; // not valid
      tZOM[ucID].ucABSComp[1] = FULLTURNINABSTICKS; // not valid
      tZOM[ucID].ucABSComp[2] = FULLTURNINABSTICKS; // not valid
      tZOM[ucID].ucABSComp[3] = FULLTURNINABSTICKS; // not valid
#endif
      return (0);

    }
    else if (ptInputWA->SchraderFP.ucPAL == 0xFF){  // overflow
#ifdef Test_LOG_ENABLE
      tZOM[ucID].ucABSComp[0] = FULLTURNINABSTICKS; // not valid
      tZOM[ucID].ucABSComp[1] = FULLTURNINABSTICKS; // not valid
      tZOM[ucID].ucABSComp[2] = FULLTURNINABSTICKS; // not valid
      tZOM[ucID].ucABSComp[3] = FULLTURNINABSTICKS; // not valid
#endif
      return (0);
    }
    fp2ushABSingleTick =  ushGetABSingleTickPAL;
  }
  else if (ptInputWA->Header .ucTType == cTelTypeAK35def){
#ifdef Test_LOG_ENABLE
    tZOM[ucID].ucABSComp[0] = FULLTURNINABSTICKS; // not valid
    tZOM[ucID].ucABSComp[1] = FULLTURNINABSTICKS; // not valid
    tZOM[ucID].ucABSComp[2] = FULLTURNINABSTICKS; // not valid
    tZOM[ucID].ucABSComp[3] = FULLTURNINABSTICKS; // not valid
#endif
    return (0);
  }

  if (!(fp2ushABSingleTick == ((void *)0)) && (fp2ushABSingleTick(0) != cABSStickError))
    return ((unsigned char) 1); // ABS interface adjusted correctly
  else
  {// ABS interface NOT adjusted correctly
    if (fp2ushABSingleTick == ((void *)0))
      return ((unsigned char) 0);

    PutABSErrorActive ();
    return ((unsigned char) 0); 
  }
}

void BuildCmpVal(unsigned char ucID)
{
  GenCmpVal(ucID);

  /* store compensated ABS values */
#ifdef Test_LOG_ENABLE
  tZOM[ucID].ucABSComp[0] = (fp2ushABSingleTick(0) +  tZOM[ucID].ushABSRefOffset [0] )% FULLTURNINABSTICKS; 
  tZOM[ucID].ucABSComp[1] = (fp2ushABSingleTick(1) +  tZOM[ucID].ushABSRefOffset [1] )% FULLTURNINABSTICKS;
  tZOM[ucID].ucABSComp[2] = (fp2ushABSingleTick(2) +  tZOM[ucID].ushABSRefOffset [2] )% FULLTURNINABSTICKS;
  tZOM[ucID].ucABSComp[3] = (fp2ushABSingleTick(3) +  tZOM[ucID].ushABSRefOffset [3] )% FULLTURNINABSTICKS;
#endif

#ifdef SPEEDWEIGHT
  if (ucGetSpeed() < (unsigned char) 60)  // FP telegrams at low speed are high precise and therefore to be double weighted
    GenCmpVal(ucID);
#endif //SPEEDWEIGHT
}

/*!**********************************************************************************************************
 *\Function          ucGenDMnD2(unsigned char ucDifDblWPinPC, unsigned char ucDifWPinPc, unsigned short ushSlotFilter)  // Generate DecisionMatrix and Decide 2nd ed.
 *
 *\Typ                private
 * ----------------------------------------------------------------------------------------------------------
 *\Purpose            draws decision matrix out of compare values as follows:
 * B1]
 *     compare values          relative shares
 * WP->FL  FR  RL  RR          FL  FR  RL  RR
 * ID0 123 78  8   1003        10  6   1   83  => 6-1 = 5 < 10 -> unclear line
 * ID1   8 780 120 901   =%=>  0   43  7   50  => 7-0 = 7 < 10 -> unclear line
 * ID2 13  907 1000 93         1   45  50  5    .
 * ID3 18  780 960  7          1   44  54  0    .                              =>> no decision
 * !! for 2nd edition aligned ZOM w/ 4 ERs is no precondition !!
 * !! WP is also met for <4 IDs if correlation reqs are met   !!
 * ----------------------------------------------------------------------------------------------------------
 *\SW_Requirements    none
 * ----------------------------------------------------------------------------------------------------------
 *\Parameter          if 2 IDs claim 1 WP the Id w/ the Minimum ucDifDblWPinPC below the others ID's minimum wins (value in PerCent)
 *                    if one Id has the absolute minimum ucDifWPinPc below the 2nd minimum it is approved as minimum other is ambiguous (value in PerCent)
 *
 *\Input              tZOM[0..cSumWE].ushPosCompVal[FL..RR]
 *                    ushSlotFilter : bit indexed filter for ZOM slots t considere (1=consider,0=skip) e.g.0xFFFF all slots get considered, 0 none
 *\Output             WheelPositions if decision is possible
 *
 *\Return             0 -> no decision
 *                    0..0x0F -> assigned WPs , bit indexed
 ***********************************************************************************************************/
unsigned char ucGenDMnD2(unsigned char ucDifDblWPinPC, unsigned char ucDifWPinPc, unsigned short ushSlotFilter)
{
  union // save RAM with this...
  {
    unsigned long ulTmp;
    unsigned char ucSort[4];
  } tTmp;

  unsigned long ulCmpSum;
  unsigned char i,j, ucRelCmpVal[4][4], ucTmp, ucMinIx, ucIdCt, ucRet = 0; // syntax is RelCmpVal[ID][WheelPos] i = ID, j = WP
  unsigned short ushPoSlots = 0;

  ucIdCt = ucFPDecPossible (&ushPoSlots, cMinCt4Dec );
  ushPoSlots &= ushSlotFilter ;
  ucIdCt = ucNrOfBitSet(ushPoSlots);

  if (ucGetERState () > (unsigned char) 0)  // an identified ER set must not be changed in a final decision...
  {
    ushPoSlots &= 0x000F;
    ucIdCt = ucNrOfBitSet(ushPoSlots);
  }
  else
  {
    if (ucIdCt > cMaxLR)
    {
      //ucIdCt = ucGetCorER(&ushPoSlots );
      //ucIdCt = (ucIdCt > cMaxLR) ? 0:ucIdCt;  // TOO MUCH corelating IDs in LM leads to no further locate actions 
      ucIdCt = 0; // wait for the clear overall picture at TO
    }
    if ( 0 < ucIdCt)
    {
      ushPoSlots = ushAlignZOM(ushPoSlots); // now we have IDs in the 1st ucIdCt [1..3] slots
    }
  }

  if ( ucIdCt > 0 )
  { // at leat some may be all values are present, let it whip...
    for (i = 0; i < cMaxLR; i++)             // A) build up ucIdCt x 4 WP relative shares
    {
      if ((ushPoSlots & (1<<i)) > 0)
      {
        ulCmpSum = 0;                          // 1st build base of ID
        for ( j = 0; j < cSumABSig; j++)
          ulCmpSum += ((tZOM[i].ushPosCompVal2 [j] < tZOM[i].ushPosCompVal [j]) ? tZOM[i].ushPosCompVal2 [j]:tZOM[i].ushPosCompVal [j]);
        //ulCmpSum += tZOM[i].ushPosCompVal [j];
        for ( j = 0; j < cSumABSig; j++)          // 2nd build relative share
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
          { //use 2nd
            if (tZOM[i].ushPosCompVal2[j] > 0)
            {
              tTmp.ulTmp =  (unsigned long) tZOM[i].ushPosCompVal2[j] * 100;
              tTmp.ulTmp /= ulCmpSum;
              ucRelCmpVal[i][j] = (unsigned char) tTmp.ulTmp;
            }
            else
              ucRelCmpVal[i][j] = (unsigned char) 1;
          }
          //if (0 == ucRelCmpVal[i][j]) OIL 983 in the WBT result we trust
          //  ucRelCmpVal[i][j] = 1;
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

      // ____________________________________________________B) reduce ucIdCt x 4 WP relative shares to one minimum in each line, count unclear lines
      tTmp.ulTmp = (unsigned long) 0;
      ucTmp = (unsigned char) 0;  // use as index to clear (none ambiguos) lines (bit indexed)
      for (i = 0; i < cMaxLR; i++)
      {
        if ((ushPoSlots & (1<<i)) > 0)
        {
          SortBiggest1st(ucRelCmpVal[i],tTmp.ucSort,cSumABSig);   //  1st find abs min in each ID line and 2nd minimum
          if ((ucRelCmpVal[i][tTmp.ucSort[cSumABSig-2]] - ucRelCmpVal[i][tTmp.ucSort[cSumABSig-1]]) > ucDifWPinPc) // minimum lays 10% below 2nd minimum
          { // clear line
            for ( j = 0; j < cMaxLR; j++) //delete all but not the minimum
              if ( j != tTmp.ucSort[cSumABSig-1])
                ucRelCmpVal[i][j] = (unsigned char) 0;
              else
                if ((unsigned char) 0 == ucRelCmpVal[i][j])
                  ucRelCmpVal[i][j] = (unsigned char) 1;
            ucTmp |= (unsigned char) (1<<i);
          }
          else
          { // realtive distance's too small
            for ( j = 0; j < cMaxLR; j++) // matrix line is not clear at this ID
              ucRelCmpVal[i][j] = (unsigned char) 0;
            PutLocatError (AmbigWP ,i);
            tZOM[i].ucStatus &= (unsigned char) 0xF0; // clear WP
          }
        }
        else
        {
          PutLocatError (AmbigWP ,i);
          tZOM[i].ucStatus &= (unsigned char) 0xF0; // clear WP
        }
      }
      if (ucTmp > (unsigned char) 0)                      // _______________C) go searching 4 double or none taken WPs if at least 1 clear line exists and resolve
      {                                                  // a none 4 wheel system will not come in here w/ ambiguous lines(IDs)
        for ( j = 0; j < cMaxLR; j++ ) //FL..RR
        {
          ucMinIx = cMaxLR; // WP j is not yet claimed by any ID
          for (i = 0; i < cMaxLR; i++)  //ID0..ID3
          {
            if (ucRelCmpVal[i][j] > 0)  // is there a minimum ?
            {
              if (ucMinIx == cMaxLR) 
                ucMinIx = i;  // ID i possess WP j so far
              else // there is already an ID claiming to be at WP j -> find the lower minimum
              {
                if (ucRelCmpVal[i][j] < ucRelCmpVal[ucMinIx][j])
                {
                  if ((ucRelCmpVal[ucMinIx][j] - ucRelCmpVal[i][j]) > ucDifDblWPinPC)
                  {
                    ucTmp &= (unsigned char) ~(1<<ucMinIx); // ID at ucMinIx has no longer clear line
                    ucRelCmpVal[ucMinIx][j] = 0;
                    PutLocatError (AmbigWP ,ucMinIx);
                    tZOM[ucMinIx].ucStatus &= (unsigned char) 0xF0; // clear WP
                    ucMinIx = i;  // change minimum index
                  }
                  else
                  {
                    ucTmp &= (unsigned char) ~(1<<ucMinIx); // ID at ucMinIx has no longer clear line
                    ucRelCmpVal[ucMinIx][j] = 0;
                    PutLocatError (RivalSensors ,ucMinIx);
                    tZOM[ucMinIx].ucStatus &= (unsigned char) 0xF0; // clear WP
                    ucTmp &= (unsigned char) ~(1<<i); // ID at i has no longer clear line also
                    ucRelCmpVal[i][j] = 0;
                    PutLocatError (RivalSensors ,i);
                    tZOM[i].ucStatus &= (unsigned char) 0xF0; // clear WP
                    ucMinIx = cMaxLR;  // 2 different sensors claim the same WP w/o sufficient differenc -> exit
                  }
                }
                else
                {
                  if ((ucRelCmpVal[i][j] - ucRelCmpVal[ucMinIx][j]) > ucDifDblWPinPC)
                  { // minimum remains
                    ucTmp &= (unsigned char) ~(1<<i); // ID at i has no longer clear line also
                    ucRelCmpVal[i][j] = 0;
                    PutLocatError (AmbigWP ,i);
                    tZOM[i].ucStatus &= (unsigned char) 0xF0; // clear WP
                  }
                  else
                  {
                    ucTmp &= (unsigned char) ~(1<<ucMinIx); // ID at ucMinIx has no longer clear line
                    ucRelCmpVal[ucMinIx][j] = 0;
                    PutLocatError (RivalSensors ,ucMinIx);
                    tZOM[ucMinIx].ucStatus &= (unsigned char) 0xF0; // clear WP
                    ucTmp &= (unsigned char) ~(1<<i); // ID at i has no longer clear line also
                    ucRelCmpVal[i][j] = 0;
                    PutLocatError (RivalSensors ,i);
                    tZOM[i].ucStatus &= (unsigned char) 0xF0; // clear WP
                    ucMinIx = cMaxLR;  // 2 different sensors claim the same WP w/o sufficient differenc -> exit
                  }
                }
              }
            }
          }
        }
        // ______________________________________________________________D) go and assign (all) the WPs now if no more than 1 ambigous ID exists for 4 IDs, or no amiguous line and not too much (3..1) unused WP at 1..3 IDs
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
                if (ucRelCmpVal[i][j] > 0 )                           // abs min at this WP ?
                { // deactivate 15% limit for bad G34 performance on snow NO MOORE...
                  if (ucGetWPOfCol(ucGetColOfID(&tZOM[i].ulID)) == j) // no history change pos ?
                  {
                    SetZOMWP(i,j);
                    PutLocatError (NoError ,i);
                  }
                  else
                  {                                                   // history position changed or new
                    if (ucRelCmpVal[i][j] < 15)                // changed or new WP must be obviously clear (means abs min < 15%)
                    { 
                      SetZOMWP(i,j);
                      PutLocatError (NoError ,i);
                    }
                    else
                    {
                      ucTmp &= (unsigned char) ~(1<<i);
                      break;                                          // other wise we exit here
                    }
                  }
                }

          }
          ucRet = ucTmp;  // allocated that much IDs
        }
      }
  }
#ifdef pb_ModulTest_050104
  else  // reset 4x4 relative share values
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

  for (i = 0; i < cSumWE; i++)             // A) build up 1 ID line w/ 4 WP relative shares
  {
    if ((*p2Slots & (1<<i)) > 0) 
    {
      if ( cMinCt4Dec  <= tZOM[i].ucToothTelCt)
      { 
        ulCmpSum = 0;                          // 1st build base of ID
        for ( j = 0; j < cMaxLR; j++)
          ulCmpSum += ((tZOM[i].ushPosCompVal2 [j] < tZOM[i].ushPosCompVal [j]) ? tZOM[i].ushPosCompVal2 [j]:tZOM[i].ushPosCompVal [j]);

        for ( j = 0; j < cMaxLR; j++)          // 2nd build relative share
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
          { //use 2nd
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
          *p2Slots &= ~(1<<i);  // no ER any longer
      }
      else
        *p2Slots &= ~(1<<i);  // no ER any longer
    }
  }
  return (ucErCt );
}

unsigned char ucCorLine(unsigned char  p2Line[], const unsigned char ucMaxDev)
{
  unsigned char i;
  const unsigned char ucDefMeanVal = 0x19;
  //for (i = 0; i < cMaxLR ; i++)
  //  ushSum += (unsigned short) p2Line [i];

  //ushSum >>= 2; // arithm. mean vaue

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
  union // save RAM with this...
  {
    unsigned long ulTmp;
    unsigned char ucSort[4];
  } tTmp;

  unsigned long ulCmpSum;

  unsigned char  ucRelCmpVal[cSumWE][4];

  unsigned char i,j ; // syntax is RelCmpVal[ID][WheelPos] i = ID, j = WP

  for (i = 0; i < cSumWE; i++)             // A) build up 4x4 WP relative shares GL: in debug mode we do it for all Zom entries!!
  {
    if (0 == tZOM[i].ushPosCompVal2[0])
      continue;
    ulCmpSum = 0;                          // 1st build base of ID
    for ( j = 0; j < cSumABSig; j++)
      ulCmpSum += ((tZOM[i].ushPosCompVal2 [j] < tZOM[i].ushPosCompVal [j]) ? tZOM[i].ushPosCompVal2 [j]:tZOM[i].ushPosCompVal [j]);

    for ( j = 0; j < cSumABSig; j++)          // 2nd build relative share
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
      { //use 2nd
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

      tZOM[i].ushRelCmpVal[j] = ucRelCmpVal[i][j];  // pure MT debug variable
    }
  }

  // ____________________________________________________B) reduce 4x4 WP relative shares to one minimum in each line, count unclear lines
  tTmp.ulTmp = (unsigned long) 0;
  for (i = 0; i < cSumWE; i++)
  {
    if (0 == tZOM[i].ushPosCompVal2[0])
      continue;
    SortBiggest1st(ucRelCmpVal[i],tTmp.ucSort,cSumABSig);   //  1st find abs min in each ID line and 2nd minimum
    tZOM[i].ucDeltaMin = (ucRelCmpVal[i][tTmp.ucSort[cSumABSig-2]] - ucRelCmpVal[i][tTmp.ucSort[cSumABSig-1]]); // pure MT debug variable

    //avoid division by zero, avoid negativ lqi
    ucRelCmpVal[i][tTmp.ucSort[cSumABSig-2]] = (ucRelCmpVal[i][tTmp.ucSort[cSumABSig-2]]) > 2 ? ucRelCmpVal[i][tTmp.ucSort[cSumABSig-2]] : 2;
    ucRelCmpVal[i][tTmp.ucSort[cSumABSig-1]] = (ucRelCmpVal[i][tTmp.ucSort[cSumABSig-1]]) > 2 ? ucRelCmpVal[i][tTmp.ucSort[cSumABSig-1]] : 2;

    //compute lqi
    if ( (tZOM[i].ucToothTelCtCorrLearnBit + tZOM[i].ucToothTelCtCorrNoLearnBit) > 6)
    {
      tZOM[i].ushLqi = (unsigned short) ( ((tZOM[i].ucToothTelCtCorrLearnBit + tZOM[i].ucToothTelCtCorrNoLearnBit - 2) * tZOM[i].ucDeltaMin)/ucRelCmpVal[i][tTmp.ucSort[cSumABSig-1]] ); //  ( (corr-2)*(Dev2 -Dev1) ) / Dev1
    }
    else{
      tZOM[i].ushLqi = (unsigned short) 0;
    }
  }
}

// ushReduceCorel24 purpose:
// reduce >4 ER sensors to <=4 corellating w/o conflicts
// return in ret val
unsigned short ushReduceCorel24(unsigned short ushCandidate)
{
  unsigned char i, j, ucCorWP[cSumWE],ucWPinPerc[cSumWE];

  for (i = 0; i < cSumWE ; i++) // 1st run:build WP and corresponding precentage values while history WPs allways win
  {
    if ( (ushCandidate & (1<<i)) > 0)
    {
      if ((unsigned char) 0 == GETuCorWPofSlot(i, &ucCorWP[i], &ucWPinPerc[i]))
      {
        if ( cWheelPos_RR < ucGetWPOfCol (ucGetColOfID ( &tZOM [i].ulID))) // no historic WP
        {
          ushCandidate &= ((unsigned short) (~(1<<i)));
          tZOM[i].ucStatus &= 0xF0;
        }
        else
        {
          ucCorWP[i] = (1<<ucGetWPOfCol (ucGetColOfID ( &tZOM [i].ulID)));  // history prevails
          ucWPinPerc[i] = 0;
        }
      }
    }
  }

  for (i = 0; i < cSumWE ; i++) // 2nd run:find rival sensors 4 one WP and make dr.best's fit decission
  {
    tZOM[i].ucStatus &= 0xF0;
    if ( (ushCandidate & (1<<i)) > 0)
    {
      tZOM[i].ucStatus |= ucCorWP [i];  // set WP in case no rival sensor is present
      for (j = i; j < cSumWE; j++)
      {
        if ( ((ushCandidate & (1<<j)) > 0) && (j != i) )
        {
          if (ucCorWP [i] == ucCorWP[j])
          {  // rivals found
            if (i == ucBestFit(i,j,ucWPinPerc [i],ucWPinPerc [j]))
            {  // i keeps WP, j lost - clear WP and go on
              ushCandidate &= ((unsigned short) (~(1<<j)));
            }
            else
            {  // j won and now earns WP - i disappears -> next slot i + 1
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

// GETuCorWPofSlot purpose:
// find WheelPosition by corellation values of ZOM slot ucSlot[0..cSumWE-1], 
// support 5% minimum diff and max.15% abs criterion
// return > 0 if succeeded -> *pucWP = 1,2,4,8 and *pucPcVal = 0..100
// return 0 if failed ->  *pucWP = 0 *pucPcVal = 100
unsigned char GETuCorWPofSlot(unsigned char ucSlot, unsigned char * pucWP, unsigned char * pucPcVal)
{
  unsigned char aucReLine[4], aucSortedShares[4];
  
  *pucWP = (unsigned char) 0;
  *pucPcVal = (unsigned char) 100;

  if ( cMinCt4Dec  <= tZOM[ucSlot].ucToothTelCt)
  { 
#ifdef WAModulTest
    if ( TESTucGetFpaWPOfZomSlot(ucSlot) > 3 ) // no valid WP?
      return (0);
    else
    {
      *pucWP = 1<<TESTucGetFpaWPOfZomSlot (ucSlot);
      *pucPcVal = (unsigned char) 5;
      return (0xFF);
    }
#endif
    MakeReLine(ucSlot,aucReLine);
    SortBiggest1st(aucReLine,aucSortedShares,4);   //  1st find abs min in each ID line and 2nd minimum

    if (((aucReLine[aucSortedShares[2]] - aucReLine[aucSortedShares[3]]) > 4) && (15 > aucReLine[aucSortedShares[3]])) // minimum lays >4% below 2nd minimum
    {
      *pucPcVal = aucReLine[aucSortedShares[3]];
      *pucWP = (unsigned char) (1<<aucSortedShares[3]);
      return ((unsigned char) 0xFF);
    }
  }
  return ((unsigned char) 0);
}

// MakeReLine purpose:
// generate 4 relative shares of corelation value deployment from wheel psotion FL..RR from ZOM slot ucSlot[0..cSumWE-1]
// and write to pucLine[0..3]
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
    { //use 2nd
      if (tZOM[ucSlot].ushPosCompVal2[j] > 0)
      {
        ulTmp =  (unsigned long) tZOM[ucSlot].ushPosCompVal2[j] * 100;
        ulTmp /= ulCmpSum;
        pucLine[j] = (unsigned char) ulTmp;
      }
      else
        pucLine[j] = (unsigned char) 1;
    }
    //if (0 == pucLine[j])  OIL 978 in the WBT result we trust
    //  pucLine[j] = 1;
  }
}

// ucBestFit purpose:
// if 2 ZOM slots ucSlot1[0..cSumWE-1] and ucSlot2[0..cSumWE-1] corelate on same WP w/ share values ucPCVal1[0..100] and ucPCVal2[0..100]
// the slot that fits better to WP is returned[0..cSumWE-1]
static unsigned char ucBestFit(unsigned char ucSlot1, unsigned char ucSlot2, unsigned char ucPCVal1,  unsigned char ucPCVal2)
{
  unsigned char ucRet = 0xFF;

  if (cMaxLR > ucGetColOfID ( &tZOM [ucSlot1].ulID))   // max prio has history - ucSlot1 inside history ?
  {
    if (cMaxLR  <= ucGetColOfID ( &tZOM [ucSlot2].ulID)) // ucSlot2 not inside history ?
    {
      ucRet = ucSlot1;
    }
  }
  else if (cMaxLR  > ucGetColOfID ( &tZOM [ucSlot2].ulID))  // ucSlot2 inside history ?
  {
    ucRet = ucSlot2;
  }
  if (0xFF == ucRet)  // none or both in history
  {
    if ((ucDAG_LQIParameter() <= ucGetZomLqi(ucSlot1)) && (ucDAG_LQIParameter() > ucGetZomLqi(ucSlot2))) //2nd prio is abs LQI above threshold
    {
      ucRet = ucSlot1;
    }
    else if ((ucDAG_LQIParameter() <= ucGetZomLqi(ucSlot2)) && (ucDAG_LQIParameter() > ucGetZomLqi(ucSlot1)))
    {
      ucRet = ucSlot2;
    }
    else
    {
      if ((ucGetZomTelCtLearnBit(ucSlot1) > ((unsigned char) 15)) && (ucGetZomTelCtLearnBit(ucSlot2) <= ((unsigned char) 15)))      //3rd prio is abs learnbit count >15
      {
        ucRet = ucSlot1;
      }
      else if ((ucGetZomTelCtLearnBit(ucSlot2) > ((unsigned char) 15)) && (ucGetZomTelCtLearnBit(ucSlot1) <= ((unsigned char) 15)))
      {
        ucRet = ucSlot2;
      }
      else
      {
        if (ucGetZomLqi(ucSlot2) > ucGetZomLqi(ucSlot1))  // 4th prio is no longer WP corellation quality (percentage value) but LQI
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

  for (i = 0; i < 4;i++)  /* headline */
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
#endif // pb_ModulTest_050104
#endif //FPA
