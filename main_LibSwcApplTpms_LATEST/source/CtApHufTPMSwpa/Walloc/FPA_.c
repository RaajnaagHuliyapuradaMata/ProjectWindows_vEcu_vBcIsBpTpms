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


/*
Include
*/
#ifdef Test_LOG_ENABLE
#include "test.h"
#endif

#define FPA_INT

#include "WallocX.h"
#include "Walloc_IF.h"
#include "walloc.h"
#include "FPA.h"

#ifdef FPA
/*
Prototypes
*/
static void GenCmpVal(unsigned char ucID);
static void GenCmpVal1(unsigned char ucID);
static void GenCmpVal2(unsigned char ucID);
static void GenCmpVal3(unsigned char ucID);
static unsigned short ushGetMean(uint16 a, uint16 b);
static unsigned char ucGenDMnD(void);
static void SortBiggest1st(unsigned char *ptVal, unsigned char *ptIx, unsigned char ucMax);
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


/*
Macros
*/
#define cMinStretch (unsigned char) 0x30  // ID in this slot achieved minimum way stretch between 1st RF tel reception and current reception PURE FPA
#define cFPARefWidth 1

#define cMinCt4Dec (unsigned char) 14

#define cRE15_4_2 0
#define cHSrange 1
#define cLSrange 2
#define cIFS 3

#define RE1562
#define SPEEDWEIGHT
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
  else if (ptInputWA->Header .ucTType == cTelTypeSELPAL ){
	  // check validity of PAL byte
	  if ((ptInputWA->SchraderFP.ucPAL == 0x0)	// no PAL data
			|| (ptInputWA->SchraderFP.ucPAL == 0x01)  // no Correlation
			|| (ptInputWA->SchraderFP.ucPAL == 0xFF)) // overflow

			return (0);


	  fp2ushABSingleTick =  ushGetABSingleTickPAL;

  }

  if (!(fp2ushABSingleTick == ((void *)0)) && (fp2ushABSingleTick(0) != cABSStickError))//(ptInputWA->G4Std .ucTelSentnEnergy & 0x0F) > 0)  /* FPE valid ? */
  {
      GenCmpVal(ucID);

#ifdef Test_LOG_ENABLE
	  testLogLinABSInfo(ucID, fp2ushABSingleTick(0), fp2ushABSingleTick(1), fp2ushABSingleTick(2), fp2ushABSingleTick(3), \
		  tZOM[ucID].ucABSRef[0],  tZOM[ucID].ucABSRef[1], tZOM[ucID].ucABSRef[2], tZOM[ucID].ucABSRef[3]);
#endif

#ifdef SPEEDWEIGHT
      if (ucGetSpeed() < (unsigned char) 60)  // FP telegrams at low speed are high precise and therefore to be double weighted
        GenCmpVal(ucID);
#endif //SPEEDWEIGHT
  }
  else
    return (0);

  if (ucGenDMnD() > 0)
	return(1);
  else
    return(0);
}

static void GenCmpVal(unsigned char ucID)
{
  unsigned long ulTmp;
  unsigned short ushdN, ushTmp, ushdN2;
  unsigned char i;

  if (tZOM[ucID].ucToothTelCt > (cFPARefWidth-1)) // == cFPARefWidth
  {
    if ((unsigned char) (128 + cFPARefWidth + 1) > tZOM[ucID].ucToothTelCt)
      tZOM[ucID].ucToothTelCt++;

    ushTmp = fp2ushABSingleTick(0);
    ushTmp -=ush1stABSTickFL;
    if ( ushTmp > ushMinStretch4Decision())
        tZOM[ucID].ucStatus |= cMinStretch; // multiset has no effect

    for (i = 0; i < cSumABSig; i++)
    {
      /*______________________________________________________________________________________________________________________________________________________________________*/
      /* Difference to integer revolution amount (=modulo) between very first and current RF receptions of a fix position sending TPMS sensor at wheel position I: dNintpos i */
      ushTmp = ushGetAnZahn();
      ushdN =  fp2ushABSingleTick(i);
      ushdN %= ushTmp;                                                         // ABStickMOD96

      if ( ushdN < tZOM[ucID].ucABSRef [i]) // allways stay in the range 0..96   ABStickMOD96 < ABSrefMOD96 ->
       ushdN += ushTmp;                                                        // -> ABStickMOD96 + 96
      ushdN -= (unsigned short) tZOM[ucID].ucABSRef [i];                       // dN = ABStick'MOD96 - ABSrefMOD96

      ushTmp >>= 1; //96 -> 48 ( make a half turn)
      ushdN = ( ushdN > ushTmp) ? (ushdN - ushTmp):(ushdN + ushTmp);           // dN > 48 ? YES-> dN = dN - 48 ; NO -> dN = dN + 48
      //ushdN2= ( ushdN > ushTmp) ? (ushdN - ushTmp):(ushdN + ushGetAnZahn());   // dN2 > 48 ? YES-> dN = dN - 48 ; NO -> dN = dN + 96
	  ushdN2 = ushdN + 48;
	  ushdN2 = (ushdN2 >= 96) ? (ushdN2 - 96) : ushdN2;
#ifdef pb_ModulTest_050104
      tZOM[ucID].ucCurdN[i] = (unsigned char) ushdN;
#endif
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
      ushdN =  (fp2ushABSingleTick(i) % ushGetAnZahn());
      ushTmp = (unsigned short) tZOM[ucID].ucABSRef[i] * (unsigned short) tZOM[ucID].ucToothTelCt;
      ushTmp += ushdN;
      ushTmp /= (unsigned short) (tZOM[ucID].ucToothTelCt + 1);
      tZOM[ucID].ucABSRef[i] = (unsigned char) ushTmp;
    }
    tZOM[ucID].ucToothTelCt++;
  }
}

static void GenCmpVal1(unsigned char ucID)
{
  unsigned long ulTmp;
  unsigned short ushdN, ushTmp, ushdN2;
  unsigned char i;

  if (tZOM[ucID].ucToothTelCt > (cFPARefWidth-1)) // == cFPARefWidth
  {
    if ((unsigned char) (128 + cFPARefWidth + 1) > tZOM[ucID].ucToothTelCt)
      tZOM[ucID].ucToothTelCt++;

    ushTmp = fp2ushABSingleTick(0);
    ushTmp -=ush1stABSTickFL;
    if ( ushTmp > ushMinStretch4Decision())
        tZOM[ucID].ucStatus |= cMinStretch; // multiset has no effect

    for (i = 0; i < cSumABSig; i++)
    {
      /*______________________________________________________________________________________________________________________________________________________________________*/
      /* Difference to integer revolution amount (=modulo) between very first and current RF receptions of a fix position sending TPMS sensor at wheel position I: dNintpos i */
      ushTmp = ushGetAnZahn();
      ushdN =  fp2ushABSingleTick(i);
      ushdN %= ushTmp;                                                         // ABStickMOD96

      if ( ushdN < tZOM[ucID].ucABSRef [i]) // allways stay in the range 0..96   ABStickMOD96 < ABSrefMOD96 ->
       ushdN += ushTmp;                                                        // -> ABStickMOD96 + 96
      ushdN -= (unsigned short) tZOM[ucID].ucABSRef [i];                       // dN = ABStick'MOD96 - ABSrefMOD96

      ushTmp >>= 1; //96 -> 48 ( make a half turn)
      ushdN = ( ushdN > ushTmp) ? (ushdN - ushTmp):(ushdN + ushTmp);           // dN > 48 ? YES-> dN = dN - 48 ; NO -> dN = dN + 48
      ushdN2= ( ushdN > ushTmp) ? (ushdN - ushTmp):(ushdN + ushGetAnZahn());   // dN2 > 48 ? YES-> dN = dN - 48 ; NO -> dN = dN + 96

#ifdef pb_ModulTest_050104
      tZOM[ucID].ucCurdN[i] = (unsigned char) ushdN;
#endif
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
#if(1)
	  if (tZOM[ucID].ucToothTelCt == 3)
		  ushTmp >>= 1;
#endif
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
#if(1)
	  if (tZOM[ucID].ucToothTelCt == 3)
		  ushTmp >>= 1;
#endif
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
      ushdN =  (fp2ushABSingleTick(i) % ushGetAnZahn());
      ushTmp = (unsigned short) tZOM[ucID].ucABSRef[i] * (unsigned short) tZOM[ucID].ucToothTelCt;
      ushTmp += ushdN;
      ushTmp /= (unsigned short) (tZOM[ucID].ucToothTelCt + 1);
      tZOM[ucID].ucABSRef[i] = (unsigned char) ushTmp;
    }
    tZOM[ucID].ucToothTelCt++;
  }
}

static void GenCmpVal2(unsigned char ucID)
{
  unsigned long ulTmp;
  unsigned short ushdN, ushTmp;
  unsigned char i;

  if (tZOM[ucID].ucToothTelCt > (cFPARefWidth-1)) // == cFPARefWidth
  {
    if ((unsigned char) (128 + cFPARefWidth + 1) > tZOM[ucID].ucToothTelCt)
      tZOM[ucID].ucToothTelCt++;

    ushTmp = fp2ushABSingleTick(0);
    ushTmp -=ush1stABSTickFL;
    if ( ushTmp > ushMinStretch4Decision())
        tZOM[ucID].ucStatus |= cMinStretch; // multiset has no effect

    for (i = 0; i < cSumABSig; i++)
    {
      /*______________________________________________________________________________________________________________________________________________________________________*/
      /* Difference to integer revolution amount (=modulo) between very first and current RF receptions of a fix position sending TPMS sensor at wheel position I: dNintpos i */
      ushTmp = ushGetAnZahn();
      ushdN =  fp2ushABSingleTick(i);
      ushdN %= ushTmp;                                                         // ABStickMOD96

      if ( ushdN < tZOM[ucID].ucABSRef [i]) // allways stay in the range 0..96   ABStickMOD96 < ABSrefMOD96 ->
       ushdN += ushTmp;                                                        // -> ABStickMOD96 + 96
      ushdN -= (unsigned short) tZOM[ucID].ucABSRef [i];                       // dN = ABStick'MOD96 - ABSrefMOD96

      ushTmp >>= 1; //96 -> 48 ( make a half turn)
      ushdN = ( ushdN > ushTmp) ? (ushdN - ushTmp):(ushdN + ushTmp);           // dN > 48 ? YES-> dN = dN - 48 ; NO -> dN = dN + 48

#ifdef pb_ModulTest_050104
      tZOM[ucID].ucCurdN[i] = (unsigned char) ushdN;
#endif
      /*______________________________________________________________________________________________________________________________________________________________________*/
      /* Mean difference to integer number of revolutions between current RF telegram receptions and 1st RF telegramm reception of one fix pos sending TPMS sensor at wheel position I:*/
      if (tZOM[ucID].ucToothTelCt > cFPARefWidth + 1)
      {
        if (tZOM[ucID].ucToothTelCt < (unsigned char) (128 + cFPARefWidth))
        { // arithmet. mean val
#if(1)
			ushTmp =ushGetMean(tZOM[ucID].ushMVdN[i], ushdN);

			tZOM[ucID].ushMVdN[i] = ushGetMean(tZOM[ucID].ushMVdN[i], ushTmp);
#else			
			tZOM[ucID].ushMVdN[i] += ushdN;
#endif
        }
        else
        { // weighted mean val: MVdN = (MVdNalt x 127 + dN) / 128
          if (tZOM[ucID].ucToothTelCt == (unsigned char) (128 + cFPARefWidth) )
          {
            tZOM[ucID].ushMVdN[i] +=64;
            tZOM[ucID].ushMVdN[i] >>= 7;

          }
          ushTmp = tZOM[ucID].ushMVdN[i]; // generate weighted mean value
          ulTmp = (unsigned long) ushTmp << 7;
          ulTmp -= (unsigned long) ushTmp;
          ulTmp += (unsigned long) ushdN;
          ulTmp += (unsigned long) 64;  // round
          ulTmp >>= 7;
          tZOM[ucID].ushMVdN[i] = (unsigned short) ulTmp;
		  //
		  //tZOM[ucID].ucABSRef [i] = tZOM[ucID].ushMVdN[i];
		  //
        }
      }
      else
      {
        tZOM[ucID].ushMVdN[i] = ushdN;
      }

      /*______________________________________________________________________________________________________________________________________________________________________*/
      /*Sum of current differences of dN pos i n and the corresponding mean value of dN pos i n.*/
      if (tZOM[ucID].ucToothTelCt < (unsigned char) (128 + cFPARefWidth))
      { // generate deviation with arithmet. mean val
#if(1)
        ushTmp =  tZOM[ucID].ushMVdN[i];
#else
		ushTmp =  tZOM[ucID].ushMVdN[i] / ((unsigned short) (tZOM[ucID].ucToothTelCt - cFPARefWidth));
#endif
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
#if(1)
	  if(ushTmp > 48)
	  ushTmp = 96-ushTmp;
#endif
      // ushTmp now contains deviation

      ushTmp += tZOM[ucID].ushPosCompVal[i];     /**/
      if (ushTmp > tZOM[ucID].ushPosCompVal[i]) /* overflow check */
        tZOM[ucID].ushPosCompVal[i] = ushTmp;  /**/
#if(1)
	  tZOM[ucID].ushPosCompVal2 [i] = 0xFFFF;
#endif
    }
  }
  else
  { // very 1st reception
    if (tZOM[ucID].ucToothTelCt < (unsigned char) 1)
      ush1stABSTickFL = fp2ushABSingleTick(0);
    for (i = 0; i < cMaxLR; i++)
    {
      ushdN =  (fp2ushABSingleTick(i) % ushGetAnZahn());
      ushTmp = (unsigned short) tZOM[ucID].ucABSRef[i] * (unsigned short) tZOM[ucID].ucToothTelCt;
      ushTmp += ushdN;
      ushTmp /= (unsigned short) (tZOM[ucID].ucToothTelCt + 1);
      tZOM[ucID].ucABSRef[i] = (unsigned char) ushTmp;
    }
    tZOM[ucID].ucToothTelCt++;
  }
}

static void GenCmpVal3(unsigned char ucID)
{
  unsigned long ulTmp;
  unsigned short ushdN, ushTmp, ushdN2, ushdN3, ushdN4;
  unsigned char i;

  if (tZOM[ucID].ucToothTelCt > (cFPARefWidth-1)) // == cFPARefWidth
  {
    if ((unsigned char) (128 + cFPARefWidth + 1) > tZOM[ucID].ucToothTelCt)
      tZOM[ucID].ucToothTelCt++;

    ushTmp = fp2ushABSingleTick(0);
    ushTmp -=ush1stABSTickFL;
    if ( ushTmp > ushMinStretch4Decision())
        tZOM[ucID].ucStatus |= cMinStretch; // multiset has no effect

    for (i = 0; i < cSumABSig; i++)
    {
      /*______________________________________________________________________________________________________________________________________________________________________*/
      /* Difference to integer revolution amount (=modulo) between very first and current RF receptions of a fix position sending TPMS sensor at wheel position I: dNintpos i */
      ushTmp = ushGetAnZahn();
      ushdN =  fp2ushABSingleTick(i);
      ushdN %= ushTmp;                                                         // ABStickMOD96
	  /*
      if ( ushdN < tZOM[ucID].ucABSRef [i]) // allways stay in the range 0..96   ABStickMOD96 < ABSrefMOD96 ->
       ushdN += ushTmp;                                                        // -> ABStickMOD96 + 96
      ushdN -= (unsigned short) tZOM[ucID].ucABSRef [i];                       // dN = ABStick'MOD96 - ABSrefMOD96

	  ushdN2  =( ushdN + 24)%96;
	  ushdN3  =( ushdN + 48)%96;
	  ushdN4  =( ushdN + 72)%96;


      ushTmp >>= 1; //96 -> 48 ( make a half turn)
      ushdN = ( ushdN > ushTmp) ? (ushdN - ushTmp):(ushdN + ushTmp);           // dN > 48 ? YES-> dN = dN - 48 ; NO -> dN = dN + 48
      //ushdN2= ( ushdN > ushTmp) ? (ushdN - ushTmp):(ushdN + ushGetAnZahn());   // dN2 > 48 ? YES-> dN = dN - 48 ; NO -> dN = dN + 96
	  */
	  ushdN2= ( ushdN > 0) ? (ushdN - 0):(ushdN + 0);   // dN2 > 48 ? YES-> dN = dN - 48 ; NO -> dN = dN + 96
	  ushdN3= ( ushdN > 24) ? (ushdN - 24):(ushdN + 24);   // dN2 > 48 ? YES-> dN = dN - 48 ; NO -> dN = dN + 96
	  ushdN4= ( ushdN > 72) ? (ushdN - 72):(ushdN + 72);   // dN2 > 48 ? YES-> dN = dN - 48 ; NO -> dN = dN + 96

#ifdef pb_ModulTest_050104
      tZOM[ucID].ucCurdN[i] = (unsigned char) ushdN;
#endif
      /*______________________________________________________________________________________________________________________________________________________________________*/
      /* Mean difference to integer number of revolutions between current RF telegram receptions and 1st RF telegramm reception of one fix pos sending TPMS sensor at wheel position I:*/
      if (tZOM[ucID].ucToothTelCt > cFPARefWidth + 1)
      {
        if (tZOM[ucID].ucToothTelCt < (unsigned char) (128 + cFPARefWidth))
        { // arithmet. mean val
          tZOM[ucID].ushMVdN[i] += ushdN;
          tZOM[ucID].ushMVdN2[i] += ushdN2;
		  tZOM[ucID].ushMVdN3[i] += ushdN3;
          tZOM[ucID].ushMVdN4[i] += ushdN4;
        }
        else
        { // weighted mean val: MVdN = (MVdNalt x 127 + dN) / 128
          if (tZOM[ucID].ucToothTelCt == (unsigned char) (128 + cFPARefWidth) )
          {
            tZOM[ucID].ushMVdN[i] +=64;
            tZOM[ucID].ushMVdN[i] >>= 7;
            tZOM[ucID].ushMVdN2[i] +=64;
            tZOM[ucID].ushMVdN2[i] >>= 7;
#if(1)
			tZOM[ucID].ushMVdN3[i] +=64;
            tZOM[ucID].ushMVdN3[i] >>= 7;
			tZOM[ucID].ushMVdN4[i] +=64;
            tZOM[ucID].ushMVdN4[i] >>= 7;
#endif
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
#if(1)
          ushTmp = tZOM[ucID].ushMVdN3[i]; // generate weighted mean value 2
          ulTmp = (unsigned long) ushTmp << 7;
          ulTmp -= (unsigned long) ushTmp;
          ulTmp += (unsigned long) ushdN3;
          ulTmp += (unsigned long) 64;  // round
          ulTmp >>= 7;
          tZOM[ucID].ushMVdN3[i] = (unsigned short) ulTmp;

		  ushTmp = tZOM[ucID].ushMVdN4[i]; // generate weighted mean value 2
          ulTmp = (unsigned long) ushTmp << 7;
          ulTmp -= (unsigned long) ushTmp;
          ulTmp += (unsigned long) ushdN4;
          ulTmp += (unsigned long) 64;  // round
          ulTmp >>= 7;
          tZOM[ucID].ushMVdN4[i] = (unsigned short) ulTmp;
#endif
        }
      }
      else
      {
        tZOM[ucID].ushMVdN[i] = ushdN;
        tZOM[ucID].ushMVdN2[i] = ushdN2;
#if(1)
		tZOM[ucID].ushMVdN3[i] = ushdN3;
        tZOM[ucID].ushMVdN4[i] = ushdN4;
#endif
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


	   // the same 4 3rd PosCompareVal
       if (tZOM[ucID].ucToothTelCt < (unsigned char) (128 + cFPARefWidth))
      { // generate deviation with arithmet. mean val
        ushTmp =  tZOM[ucID].ushMVdN3[i] / ((unsigned short) (tZOM[ucID].ucToothTelCt - cFPARefWidth));
        if ( ushdN3 > ushTmp )
          ushTmp = ushdN3 - ushTmp;
        else
          ushTmp -= ushdN3;
      }
      else
      { // generate deviation with weighted mean val
        if (ushdN3 > tZOM[ucID].ushMVdN3[i])
          ushTmp = ushdN3 - tZOM[ucID].ushMVdN3[i];
        else
          ushTmp = tZOM[ucID].ushMVdN3[i] - ushdN3;
      }
      // ushTmp now contains deviation
      ushTmp += tZOM[ucID].ushPosCompVal2[i];     /**/
      if (ushTmp > tZOM[ucID].ushPosCompVal2[i]) /* overflow check */
        tZOM[ucID].ushPosCompVal2[i] = ushTmp;  /**/
    

	      // the same 4 4nd PosCompareVal
       if (tZOM[ucID].ucToothTelCt < (unsigned char) (128 + cFPARefWidth))
      { // generate deviation with arithmet. mean val
        ushTmp =  tZOM[ucID].ushMVdN4[i] / ((unsigned short) (tZOM[ucID].ucToothTelCt - cFPARefWidth));
        if ( ushdN4 > ushTmp )
          ushTmp = ushdN4 - ushTmp;
        else
          ushTmp -= ushdN4;
      }
      else
      { // generate deviation with weighted mean val
        if (ushdN4 > tZOM[ucID].ushMVdN4[i])
          ushTmp = ushdN4 - tZOM[ucID].ushMVdN4[i];
        else
          ushTmp = tZOM[ucID].ushMVdN4[i] - ushdN4;
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
      ushdN =  (fp2ushABSingleTick(i) % ushGetAnZahn());
      ushTmp = (unsigned short) tZOM[ucID].ucABSRef[i] * (unsigned short) tZOM[ucID].ucToothTelCt;
      ushTmp += ushdN;
      ushTmp /= (unsigned short) (tZOM[ucID].ucToothTelCt + 1);
      tZOM[ucID].ucABSRef[i] = (unsigned char) ushTmp;
    }
    tZOM[ucID].ucToothTelCt++;
  }
}
/*!**********************************************************************************************************
 *\Function          static unsigned char ucGenDMnD(void);  // Generate DecisionMatirx and Decide
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
 * ----------------------------------------------------------------------------------------------------------
 *\SW_Requirements    none
 * ----------------------------------------------------------------------------------------------------------
 *\Parameter          none
 *
 *\Input              tZOM[ID0..ID3].ushPosCompVal[FL..RR] = compare values
 *
 *\Output             WheelPositions if decision is possible
 *
 *\Return             0 -> no decision
 *********************1 -> WA finished***************************************************************************************/
static unsigned char ucGenDMnD(void)
{
  union // save RAM with this...
  {
    unsigned long ulTmp;
    unsigned char ucSort[4];
  } tTmp;

  unsigned long ulCmpSum;
  unsigned char i,j, ucRelCmpVal[4][4], ucTmp, ucMinIx, ucRet = 0; // syntax is RelCmpVal[ID][WheelPos] i = ID, j = WP

  /* precheck:  compare values of 4 IDs at WP FL present ? */
  for ( i = 0; i < cMaxLR; i++)
  {
    if (0 == tZOM[i].ushPosCompVal2[0])
      break;
#ifndef pb_ModulTest_050104       // if no SIMUL is active function can abort already here, for simulation go on
    if ( cMinCt4Dec > tZOM[i].ucToothTelCt)
      break;
    if (0 == (cMinStretch & tZOM[i].ucStatus))  // minimum waystretch achieved with this ID ?
      break;
#endif
  }
#ifdef FORCEWA
  tZOM[0].ushPosCompVal[0] = 26;
  tZOM[0].ushPosCompVal[1] = 99;
  tZOM[0].ushPosCompVal[2] = 87;
  tZOM[0].ushPosCompVal[3] = 161;
  tZOM[1].ushPosCompVal[0] = 109;
  tZOM[1].ushPosCompVal[1] = 281;
  tZOM[1].ushPosCompVal[2] = 34;
  tZOM[1].ushPosCompVal[3] = 144;
  tZOM[2].ushPosCompVal[0] = 153;
  tZOM[2].ushPosCompVal[1] = 17;
  tZOM[2].ushPosCompVal[2] = 81;
  tZOM[2].ushPosCompVal[3] = 73;
  tZOM[3].ushPosCompVal[0] = 223;
  tZOM[3].ushPosCompVal[1] = 87;
  tZOM[3].ushPosCompVal[2] = 142;
  tZOM[3].ushPosCompVal[3] = 37;

  tZOM[0].ushPosCompVal2[0] = 386;
  tZOM[0].ushPosCompVal2[1] = 604;
  tZOM[0].ushPosCompVal2[2] = 87;
  tZOM[0].ushPosCompVal2[3] = 539;
  tZOM[1].ushPosCompVal2[0] = 282;
  tZOM[1].ushPosCompVal2[1] = 364;
  tZOM[1].ushPosCompVal2[2] = 627;
  tZOM[1].ushPosCompVal2[3] = 290;
  tZOM[2].ushPosCompVal2[0] = 689;
  tZOM[2].ushPosCompVal2[1] = 623;
  tZOM[2].ushPosCompVal2[2] = 81;
  tZOM[2].ushPosCompVal2[3] = 782;
  tZOM[3].ushPosCompVal2[0] = 605;
  tZOM[3].ushPosCompVal2[1] = 612;
  tZOM[3].ushPosCompVal2[2] = 609;
  tZOM[3].ushPosCompVal2[3] = 875;
#endif
  if (cMaxLR == i)
  { // all values are present, let it whip...
    for (i = 0; i < cMaxLR; i++)             // A) build up 4x4 WP relative shares
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
        if (0 == ucRelCmpVal[i][j])
          ucRelCmpVal[i][j] = 1;
#ifdef pb_ModulTest_050104
        tZOM[i].ucRelCmpVal[j] = ucRelCmpVal[i][j];
#endif
      }
      if (3 == cSumABSig) // with only 3 ABS signal set the 4th allways hard to 0
        ucRelCmpVal[i][cSumABSig] = (unsigned char) 0;
#ifdef pb_ModulTest_050104
      tZOM[i].ucRelCmpVal[cSumABSig] = ucRelCmpVal[i][cSumABSig];
#endif
    }

    // ____________________________________________________B) reduce 4x4 WP relative shares to one minimum in each line, count unclear lines
    tTmp.ulTmp = (unsigned long) 0;
    ucTmp = cMaxLR;  // use as index to unclear line (cMaxLR = no unclear, cMaxLR+1 = >1 unclear, < cMaxLR = the unclear)
    for (i = 0; i < cMaxLR; i++)
    {
      SortBiggest1st(ucRelCmpVal[i],tTmp.ucSort,cSumABSig);   //  1st find abs min in each ID line and 2nd minimum
      if ((ucRelCmpVal[i][tTmp.ucSort[cSumABSig-2]] - ucRelCmpVal[i][tTmp.ucSort[cSumABSig-1]]) > 4) // minimum lays 10% below 2nd minimum
      { // clear line
        for ( j = 0; j < cMaxLR; j++) //delete all but not the minimum
          if ( j != tTmp.ucSort[cSumABSig-1])
            ucRelCmpVal[i][j] = (unsigned char) 0;
          else
            if ((unsigned char) 0 == ucRelCmpVal[i][j])
              ucRelCmpVal[i][j] = (unsigned char) 1;
      }
      else
      { // realtive distance's too small
        if ( cMaxLR == ucTmp)
        {
          if (3 == cSumABSig)  // with only 3 ABS signal make forced WA but NOT if 4 signals available
            ucTmp = i;  //this is the 1st unclear line
          else
            ucTmp = cMaxLR + 1;
        }
        else
          ucTmp = cMaxLR + 1; // >1 unclear lines..

        for ( j = 0; j < cMaxLR; j++) // matrix line is not clear at this ID
          ucRelCmpVal[i][j] = (unsigned char) 0;
      }
    }
    if (ucTmp < (cMaxLR + 1))                          // _______________C) go searching 4 double or none taken WPs if no more thAN 1 ambiguous line exists and resolve
    {
      tTmp.ucSort [0] = cMaxLR; // set unused WP to unused
      for ( j = 0; j < cMaxLR; j++) //FL..RR
      {
        ucMinIx = cMaxLR;
        for (i = 0; i < cMaxLR; i++)  //ID0..ID3
        {
          if (ucRelCmpVal[i][j] > 0)
          {
            if (ucMinIx == cMaxLR)
              ucMinIx = i;  // ID i possess WP j so far
            else // there is already an ID claiming to be at WP j -> find the lower minimum
            {
              if (ucTmp < cMaxLR) // is there already an ambigous line ?
                break;  // yes -> 2 ambiguous lines would be too much definetly EXIT
              if (ucRelCmpVal[i][j] < ucRelCmpVal[ucMinIx][j])
              {
                if ((ucRelCmpVal[ucMinIx][j] - ucRelCmpVal[i][j]) > 10)
                {
                  ucTmp = ucMinIx;
                  ucRelCmpVal[ucMinIx][j] = 0;
                  ucMinIx = i;  // change minimum index
                }
                else
                  break;  //1 ambigous slot means also an other WP is not allocated, which ends up in 2 ambigous slots -> EXIT
              }
              else
              {
                if ((ucRelCmpVal[i][j] - ucRelCmpVal[ucMinIx][j]) > 10)
                {
                  ucTmp = i;
                  ucRelCmpVal[i][j] = 0;
                  // minimum remains
                }
                else
                  break;  //1 ambigous slot means also an other WP is not allocated, which ends up in 2 ambigous slots -> EXIT
              }
            }
          }
        }
        if (i < cMaxLR)  // slot is ambiguous for loop was left early  OR  WP FL..RL,RR (j<cSumABSig) is not connected (MinIx == MaxLR)...
          break;  // last exit all lost
        if (ucMinIx == cMaxLR)  // unused WP
        {
          if (tTmp.ucSort [0] < cMaxLR) // 1st unused WP ?
            break;
          else
            tTmp.ucSort [0] = j; // remember this WP
        }
      }
      // ______________________________________________________________D) go and assign all the WPs now if no more than 1 ambigous ID exists
      if ( j == cMaxLR)
      {
        for (i = 0; i < cMaxLR; i++)
        {
#ifdef pb_ModulTest_050104
          if (0 == (cMinStretch & tZOM[i].ucStatus))  // minimum waystretch achieved with this ID ?
            break;
          if ( cMinCt4Dec > tZOM[i].ucToothTelCt)
            break;
#endif
          if ( i == ucTmp ) // the one ambiguous line is set to unused WP
            SetZOMWP(i,tTmp.ucSort [0]);
          else
          {
            for ( j = 0; j < cMaxLR; j++)
              if (ucRelCmpVal[i][j] > 0 )                           // abs min at this WP ?
              { // deactivate 15% limit for bad G34 performance on snow NO MOORE...
                if (ucGetWPOfCol(ucGetColOfID(&tZOM[i].ulID)) == j) // no history change pos ?
                  SetZOMWP(i,j);
                else
                {                                                   // history position changed or new
                  if (ucRelCmpVal[i][j] < 15)                // changed or new WP must be obviously clear (means abs min < 15%)
                    SetZOMWP(i,j);
                  else
                  {
                    i = cMaxLR +1;
                    break;                                          // other wise we exit here
                  }
                }
              }
          }
        }
        if ( cMaxLR == i)
          ucRet = 1;  // allocated conventional
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
  return (ucRet);
}


void RebuildABSRef(unsigned char ucWP)    // provided interface function of Walloc module -> wallocX.h decl
{
  unsigned char i;

  for (i = 0; i < cSumWE ;i++)
  {
    if (tZOM[i].ucToothTelCt > 0)
    {
      if ( tZOM[i].ucABSRef [ucWP] > ucABSigOFL_MOD_ZAHN() )
        tZOM[i].ucABSRef [ucWP] -= ucABSigOFL_MOD_ZAHN();
      else
        tZOM[i].ucABSRef [ucWP] += ucMINUS_ABSigOFL_MOD_ZAHN();
    }
  }
}

void ReNewABSRef(void)  // provided interface function of Walloc module -> wallocX.h decl
{
  unsigned char i;

  for (i = 0; i < cSumWE ;i++)
  {
    tZOM[i].ucToothTelCt = 0;
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

static void SortBiggest1st(unsigned char *ptVal, unsigned char *ptIx, unsigned char ucMax)
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

unsigned short ushGetAnZahn(void)
{
  return ( FULLTURNINABSTICKS );
}

unsigned char ucABSigOFL_MOD_ZAHN(void)
{
  return ( (unsigned char)64); // = 65536 % ushGetAnZahn() )
}

unsigned char ucMINUS_ABSigOFL_MOD_ZAHN(void)
{
  return ( (unsigned char)32); // = ushGetAnZahn - (65536 % ushGetAnZahn() )
}

static unsigned short ushMinStretch4Decision(void)
{
  return ( 24000 ); // minimum waystretch in teeth (500m = 500/Utyre * 96 = 500m/2m * 96 = 24000) which must be achieved by one ID for WP assignment; 3000 = 73m
}

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

static unsigned short ushGetMean(uint16 a, uint16 b){

	uint16 temp;

	temp = (a > b) ? a-b: b-a;

	temp = (temp > 48) ?  ((a + b + 96)/2) :(a+b) /2;

	return (temp > 96) ? temp-96 : temp;
}