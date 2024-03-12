
#ifdef Test_LOG_ENABLE
#include "test.h"
#endif

#define FPA_INT

#include "WallocX.h"
#include "Walloc_IF.h"
#include "walloc.h"
#include "FPA.h"

#ifdef FPA

static void GenCmpVal(uint8 ucID);
static void GenCmpVal1(uint8 ucID);
static void GenCmpVal2(uint8 ucID);
static void GenCmpVal3(uint8 ucID);
static uint16 ushGetMean(uint16 a, uint16 b);
static uint8 ucGenDMnD(void);
static void SortBiggest1st(uint8 *ptVal, uint8 *ptIx, uint8 ucMax);
static uint16 ushMinStretch4Decision(void);

static uint16 ushGetABSingleTickFr2(uint8 ucIx);
static uint16 ushGetABSingleTickFr3(uint8 ucIx);
static uint16 ushGetABSingleTickN90(uint8 ucIx);
static uint16 ushGetABSingleTickN90Fr2(uint8 ucIx);
static uint16 ushGetABSingleTickN90Fr3(uint8 ucIx);
static uint16 ushGetABSingleTickTDL(uint8 ucIx);
static uint16 ushGetABSingleTickTDLn180(uint8 ucIx);
static uint16 ushGetABSingleTickTDL_HS(uint8 ucIx);
static uint16 ushGetABSingleTickTDL_LS(uint8 ucIx);
static uint16 ushGetABSingleTickTDL_HSn180(uint8 ucIx);
static uint16 ushGetABSingleTickTDL_LSn180(uint8 ucIx);
static uint16 ushGetABSingleTickPAL(uint8 ucIx);
static uint8 ucGetTDL(uint8 ucCorType);
static uint8 ucGetTDL100(void);
static uint16 ushGetTDL210(void);

#define cMinStretch (uint8) 0x30
 #define cFPARefWidth 1

#define cMinCt4Dec (uint8) 14

#define cRE15_4_2 0
#define cHSrange 1
#define cLSrange 2
#define cIFS 3

#define RE1562
#define SPEEDWEIGHT

static uint16 ush1stABSTickFL;

uint16 (*fp2ushABSingleTick) (uint8 ucPos);

uint16 ushCuRotatsIn05msec = 0;

uint8 ucFPActive(void){
  uint8 i, ucRet = 0;

  for(i = 0; i < cMaxLR; i++){
    if(tZOM[i].ucToothTelCt > 0){
      ucRet++;
    }
  }
  ucRet  =  (ucRet == cMaxLR) ? (uint8) 1:(uint8) 0;
  return(ucRet);
}

uint8 ucConceptFixPos0(uint8 ucID, tRFTelType * ptInputWA){

  fp2ushABSingleTick = ((void *)0);

  if(ptInputWA->Header .ucTType == cTelTypeG4Std )
    fp2ushABSingleTick = ushGetABSingleTickTDL;
   else if(ptInputWA->Header .ucTType == cTelTypeRotatS ){
    ushCuRotatsIn05msec = (((uint16) (ptInputWA->RotatS .ucSnRH & 0x0F)) << 8) + (uint16) ptInputWA->RotatS .ucRL;
    if( (ptInputWA->RotatS .ucSnRH & 0x80) == 0x80 )
 #ifdef RE1562
      if( (ptInputWA->RotatS .ucSnRH & 0x20) == 0x20 )
         fp2ushABSingleTick = ushGetABSingleTickTDL_HSn180;
      else{
          fp2ushABSingleTick = ushGetABSingleTickTDL_LSn180;
          ushCuRotatsIn05msec <<=2;
       }
#else
      fp2ushABSingleTick = ushGetABSingleTickTDLn180;
#endif
    else
 #ifdef RE1562
      if( (ptInputWA->RotatS .ucSnRH & 0x20) == 0x20 )
         fp2ushABSingleTick = ushGetABSingleTickTDL_HS;
      else{
          fp2ushABSingleTick = ushGetABSingleTickTDL_LS;
          ushCuRotatsIn05msec <<=2;
       }
#else
      fp2ushABSingleTick = ushGetABSingleTickTDL;
#endif
  }
  else if(ptInputWA->Header .ucTType == cTelTypeCorntiFP ){
      if((ptInputWA->ContiFP .ucModeNCode & 0x0C) == 0x08){
        if((ptInputWA->ContiFP .ucModeNCode & 0x03) == 0x02)
          fp2ushABSingleTick = ushGetABSingleTickFr2 ;
        else if((ptInputWA->ContiFP .ucModeNCode & 0x03) == 0x03)
          fp2ushABSingleTick = ushGetABSingleTickFr3 ;
        else
          fp2ushABSingleTick = ushGetABSingleTick ;
      }
      else if((ptInputWA->ContiFP .ucModeNCode & 0x0C) == 0x0C){
        if((ptInputWA->ContiFP .ucModeNCode & 0x03) == 0x02)
          fp2ushABSingleTick = ushGetABSingleTickN90Fr2 ;
        else if((ptInputWA->ContiFP .ucModeNCode & 0x03) == 0x03)
          fp2ushABSingleTick = ushGetABSingleTickN90Fr3 ;
        else
          fp2ushABSingleTick = ushGetABSingleTickN90  ;
      }
    ptInputWA->Header .ucTType = cTelTypeAK35def ;
     ptInputWA->AK35def .ucCmdID = cTelTypeAK35def ;
  }
  else if(ptInputWA->Header .ucTType == cTelTypeSELPAL ){
     if((ptInputWA->SchraderFP.ucPAL == 0x0)
          || (ptInputWA->SchraderFP.ucPAL == 0x01)
          || (ptInputWA->SchraderFP.ucPAL == 0xFF))

         return (0);

     fp2ushABSingleTick =  ushGetABSingleTickPAL;

  }

  if(!(fp2ushABSingleTick == ((void *)0)) && (fp2ushABSingleTick(0) != cABSStickError)){
      GenCmpVal(ucID);

#ifdef Test_LOG_ENABLE
     testLogLinABSInfo(ucID, fp2ushABSingleTick(0), fp2ushABSingleTick(1), fp2ushABSingleTick(2), fp2ushABSingleTick(3), \
        tZOM[ucID].ucABSRef[0],  tZOM[ucID].ucABSRef[1], tZOM[ucID].ucABSRef[2], tZOM[ucID].ucABSRef[3]);
#endif

#ifdef SPEEDWEIGHT
      if(ucGetSpeed() < (uint8) 60)
         GenCmpVal(ucID);
#endif
   }
  else
    return (0);

  if(ucGenDMnD() > 0)
   return(1);
  else
    return(0);
}

static void GenCmpVal(uint8 ucID){
  unsigned long ulTmp;
  uint16 ushdN, ushTmp, ushdN2;
  uint8 i;

  if(tZOM[ucID].ucToothTelCt > (cFPARefWidth-1)){
    if((uint8) (128 + cFPARefWidth + 1) > tZOM[ucID].ucToothTelCt)
      tZOM[ucID].ucToothTelCt++;

    ushTmp = fp2ushABSingleTick(0);
    ushTmp -=ush1stABSTickFL;
    if( ushTmp > ushMinStretch4Decision())
        tZOM[ucID].ucStatus |= cMinStretch;

    for(i = 0; i < cSumABSig; i++){

      ushTmp = ushGetAnZahn();
      ushdN =  fp2ushABSingleTick(i);
      ushdN %= ushTmp;

      if( ushdN < tZOM[ucID].ucABSRef [i])
        ushdN += ushTmp;
      ushdN -= (uint16) tZOM[ucID].ucABSRef [i];

      ushTmp >>= 1;
       ushdN = ( ushdN > ushTmp) ? (ushdN - ushTmp):(ushdN + ushTmp);
      ushdN2 = ushdN + 48;
     ushdN2 = (ushdN2 >= 96) ? (ushdN2 - 96) : ushdN2;
#ifdef pb_ModulTest_050104
      tZOM[ucID].ucCurdN[i] = (uint8) ushdN;
#endif
      if(tZOM[ucID].ucToothTelCt > cFPARefWidth + 1){
        if(tZOM[ucID].ucToothTelCt < (uint8) (128 + cFPARefWidth)){
           tZOM[ucID].ushMVdN[i] += ushdN;
          tZOM[ucID].ushMVdN2[i] += ushdN2;
        }
        else{
           if(tZOM[ucID].ucToothTelCt == (uint8) (128 + cFPARefWidth) ){
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
          tZOM[ucID].ushMVdN[i] = (uint16) ulTmp;

          ushTmp = tZOM[ucID].ushMVdN2[i];
           ulTmp = (unsigned long) ushTmp << 7;
          ulTmp -= (unsigned long) ushTmp;
          ulTmp += (unsigned long) ushdN2;
          ulTmp += (unsigned long) 64;
           ulTmp >>= 7;
          tZOM[ucID].ushMVdN2[i] = (uint16) ulTmp;
        }
      }
      else{
        tZOM[ucID].ushMVdN[i] = ushdN;
        tZOM[ucID].ushMVdN2[i] = ushdN2;
      }

      /*______________________________________________________________________________________________________________________________________________________________________*/
      /*Sum of current differences of dN pos i n and the corresponding mean value of dN pos i n.*/
      if(tZOM[ucID].ucToothTelCt < (uint8) (128 + cFPARefWidth)){
         ushTmp =  tZOM[ucID].ushMVdN[i] / ((uint16) (tZOM[ucID].ucToothTelCt - cFPARefWidth));
        if( ushdN > ushTmp )
          ushTmp = ushdN - ushTmp;
        else
          ushTmp -= ushdN;
      }
      else{
         if(ushdN > tZOM[ucID].ushMVdN[i])
          ushTmp = ushdN - tZOM[ucID].ushMVdN[i];
        else
          ushTmp = tZOM[ucID].ushMVdN[i] - ushdN;
      }
      ushTmp += tZOM[ucID].ushPosCompVal[i];     /**/
      if(ushTmp > tZOM[ucID].ushPosCompVal[i]) /* overflow check */
        tZOM[ucID].ushPosCompVal[i] = ushTmp;  /**/
        if(tZOM[ucID].ucToothTelCt < (uint8) (128 + cFPARefWidth)){
         ushTmp =  tZOM[ucID].ushMVdN2[i] / ((uint16) (tZOM[ucID].ucToothTelCt - cFPARefWidth));
        if( ushdN2 > ushTmp )
          ushTmp = ushdN2 - ushTmp;
        else
          ushTmp -= ushdN2;
      }
      else{
         if(ushdN2 > tZOM[ucID].ushMVdN2[i])
          ushTmp = ushdN2 - tZOM[ucID].ushMVdN2[i];
        else
          ushTmp = tZOM[ucID].ushMVdN2[i] - ushdN2;
      }
      ushTmp += tZOM[ucID].ushPosCompVal2[i];     /**/
      if(ushTmp > tZOM[ucID].ushPosCompVal2[i]) /* overflow check */
        tZOM[ucID].ushPosCompVal2[i] = ushTmp;  /**/
    }
  }
  else{
     if(tZOM[ucID].ucToothTelCt < (uint8) 1)
      ush1stABSTickFL = fp2ushABSingleTick(0);
    for(i = 0; i < cMaxLR; i++){
      ushdN =  (fp2ushABSingleTick(i) % ushGetAnZahn());
      ushTmp = (uint16) tZOM[ucID].ucABSRef[i] * (uint16) tZOM[ucID].ucToothTelCt;
      ushTmp += ushdN;
      ushTmp /= (uint16) (tZOM[ucID].ucToothTelCt + 1);
      tZOM[ucID].ucABSRef[i] = (uint8) ushTmp;
    }
    tZOM[ucID].ucToothTelCt++;
  }
}

static void GenCmpVal1(uint8 ucID){
  unsigned long ulTmp;
  uint16 ushdN, ushTmp, ushdN2;
  uint8 i;

  if(tZOM[ucID].ucToothTelCt > (cFPARefWidth-1)){
    if((uint8) (128 + cFPARefWidth + 1) > tZOM[ucID].ucToothTelCt)
      tZOM[ucID].ucToothTelCt++;

    ushTmp = fp2ushABSingleTick(0);
    ushTmp -=ush1stABSTickFL;
    if( ushTmp > ushMinStretch4Decision())
        tZOM[ucID].ucStatus |= cMinStretch;

    for(i = 0; i < cSumABSig; i++){
      ushTmp = ushGetAnZahn();
      ushdN =  fp2ushABSingleTick(i);
      ushdN %= ushTmp;

      if( ushdN < tZOM[ucID].ucABSRef [i])
        ushdN += ushTmp;
      ushdN -= (uint16) tZOM[ucID].ucABSRef [i];

      ushTmp >>= 1;
       ushdN = ( ushdN > ushTmp) ? (ushdN - ushTmp):(ushdN + ushTmp);
       ushdN2= ( ushdN > ushTmp) ? (ushdN - ushTmp):(ushdN + ushGetAnZahn());

#ifdef pb_ModulTest_050104
      tZOM[ucID].ucCurdN[i] = (uint8) ushdN;
#endif

      if(tZOM[ucID].ucToothTelCt > cFPARefWidth + 1){
        if(tZOM[ucID].ucToothTelCt < (uint8) (128 + cFPARefWidth)){
           tZOM[ucID].ushMVdN[i] += ushdN;
          tZOM[ucID].ushMVdN2[i] += ushdN2;
        }
        else{
           if(tZOM[ucID].ucToothTelCt == (uint8) (128 + cFPARefWidth) ){
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
          tZOM[ucID].ushMVdN[i] = (uint16) ulTmp;

          ushTmp = tZOM[ucID].ushMVdN2[i];
           ulTmp = (unsigned long) ushTmp << 7;
          ulTmp -= (unsigned long) ushTmp;
          ulTmp += (unsigned long) ushdN2;
          ulTmp += (unsigned long) 64;
           ulTmp >>= 7;
          tZOM[ucID].ushMVdN2[i] = (uint16) ulTmp;
        }
      }
      else{
        tZOM[ucID].ushMVdN[i] = ushdN;
        tZOM[ucID].ushMVdN2[i] = ushdN2;
      }

      if(tZOM[ucID].ucToothTelCt < (uint8) (128 + cFPARefWidth)){
         ushTmp =  tZOM[ucID].ushMVdN[i] / ((uint16) (tZOM[ucID].ucToothTelCt - cFPARefWidth));
        if( ushdN > ushTmp )
          ushTmp = ushdN - ushTmp;
        else
          ushTmp -= ushdN;
      }
      else{
         if(ushdN > tZOM[ucID].ushMVdN[i])
          ushTmp = ushdN - tZOM[ucID].ushMVdN[i];
        else
          ushTmp = tZOM[ucID].ushMVdN[i] - ushdN;
      }
#if(1)
     if(tZOM[ucID].ucToothTelCt == 3)
        ushTmp >>= 1;
#endif
      ushTmp += tZOM[ucID].ushPosCompVal[i];
      if(ushTmp > tZOM[ucID].ushPosCompVal[i])
        tZOM[ucID].ushPosCompVal[i] = ushTmp;
        if(tZOM[ucID].ucToothTelCt < (uint8) (128 + cFPARefWidth)){
         ushTmp =  tZOM[ucID].ushMVdN2[i] / ((uint16) (tZOM[ucID].ucToothTelCt - cFPARefWidth));
        if( ushdN2 > ushTmp )
          ushTmp = ushdN2 - ushTmp;
        else
          ushTmp -= ushdN2;
      }
      else{
         if(ushdN2 > tZOM[ucID].ushMVdN2[i])
          ushTmp = ushdN2 - tZOM[ucID].ushMVdN2[i];
        else
          ushTmp = tZOM[ucID].ushMVdN2[i] - ushdN2;
      }
#if(1)
     if(tZOM[ucID].ucToothTelCt == 3)
        ushTmp >>= 1;
#endif
      ushTmp += tZOM[ucID].ushPosCompVal2[i];
      if(ushTmp > tZOM[ucID].ushPosCompVal2[i])
        tZOM[ucID].ushPosCompVal2[i] = ushTmp;
    }
  }
  else{
     if(tZOM[ucID].ucToothTelCt < (uint8) 1)
      ush1stABSTickFL = fp2ushABSingleTick(0);
    for(i = 0; i < cMaxLR; i++){
      ushdN =  (fp2ushABSingleTick(i) % ushGetAnZahn());
      ushTmp = (uint16) tZOM[ucID].ucABSRef[i] * (uint16) tZOM[ucID].ucToothTelCt;
      ushTmp += ushdN;
      ushTmp /= (uint16) (tZOM[ucID].ucToothTelCt + 1);
      tZOM[ucID].ucABSRef[i] = (uint8) ushTmp;
    }
    tZOM[ucID].ucToothTelCt++;
  }
}

static void GenCmpVal2(uint8 ucID){
  unsigned long ulTmp;
  uint16 ushdN, ushTmp;
  uint8 i;

  if(tZOM[ucID].ucToothTelCt > (cFPARefWidth-1)){
    if((uint8) (128 + cFPARefWidth + 1) > tZOM[ucID].ucToothTelCt)
      tZOM[ucID].ucToothTelCt++;

    ushTmp = fp2ushABSingleTick(0);
    ushTmp -=ush1stABSTickFL;
    if( ushTmp > ushMinStretch4Decision())
        tZOM[ucID].ucStatus |= cMinStretch;

    for(i = 0; i < cSumABSig; i++){

      ushTmp = ushGetAnZahn();
      ushdN =  fp2ushABSingleTick(i);
      ushdN %= ushTmp;

      if( ushdN < tZOM[ucID].ucABSRef [i])
        ushdN += ushTmp;
      ushdN -= (uint16) tZOM[ucID].ucABSRef [i];

      ushTmp >>= 1;
      ushdN = ( ushdN > ushTmp) ? (ushdN - ushTmp):(ushdN + ushTmp);

#ifdef pb_ModulTest_050104
      tZOM[ucID].ucCurdN[i] = (uint8) ushdN;
#endif
      if(tZOM[ucID].ucToothTelCt > cFPARefWidth + 1){
        if(tZOM[ucID].ucToothTelCt < (uint8) (128 + cFPARefWidth)){
 #if(1)
         ushTmp =ushGetMean(tZOM[ucID].ushMVdN[i], ushdN);

         tZOM[ucID].ushMVdN[i] = ushGetMean(tZOM[ucID].ushMVdN[i], ushTmp);
#else
         tZOM[ucID].ushMVdN[i] += ushdN;
#endif
        }
        else{
           if(tZOM[ucID].ucToothTelCt == (uint8) (128 + cFPARefWidth) ){
            tZOM[ucID].ushMVdN[i] +=64;
            tZOM[ucID].ushMVdN[i] >>= 7;

          }
          ushTmp = tZOM[ucID].ushMVdN[i];
           ulTmp = (unsigned long) ushTmp << 7;
          ulTmp -= (unsigned long) ushTmp;
          ulTmp += (unsigned long) ushdN;
          ulTmp += (unsigned long) 64;
           ulTmp >>= 7;
          tZOM[ucID].ushMVdN[i] = (uint16) ulTmp;
         }
      }
      else{
        tZOM[ucID].ushMVdN[i] = ushdN;
      }

      /*______________________________________________________________________________________________________________________________________________________________________*/
      /*Sum of current differences of dN pos i n and the corresponding mean value of dN pos i n.*/
      if(tZOM[ucID].ucToothTelCt < (uint8) (128 + cFPARefWidth)){
 #if(1)
        ushTmp =  tZOM[ucID].ushMVdN[i];
#else
      ushTmp =  tZOM[ucID].ushMVdN[i] / ((uint16) (tZOM[ucID].ucToothTelCt - cFPARefWidth));
#endif
        if( ushdN > ushTmp )
          ushTmp = ushdN - ushTmp;
        else
          ushTmp -= ushdN;
      }
      else{
         if(ushdN > tZOM[ucID].ushMVdN[i])
          ushTmp = ushdN - tZOM[ucID].ushMVdN[i];
        else
          ushTmp = tZOM[ucID].ushMVdN[i] - ushdN;
      }
#if(1)
     if(ushTmp > 48)
     ushTmp = 96-ushTmp;
#endif
      ushTmp += tZOM[ucID].ushPosCompVal[i];     /**/
      if(ushTmp > tZOM[ucID].ushPosCompVal[i]) /* overflow check */
        tZOM[ucID].ushPosCompVal[i] = ushTmp;  /**/
#if(1)
     tZOM[ucID].ushPosCompVal2 [i] = 0xFFFF;
#endif
    }
  }
  else{
     if(tZOM[ucID].ucToothTelCt < (uint8) 1)
      ush1stABSTickFL = fp2ushABSingleTick(0);
    for(i = 0; i < cMaxLR; i++){
      ushdN =  (fp2ushABSingleTick(i) % ushGetAnZahn());
      ushTmp = (uint16) tZOM[ucID].ucABSRef[i] * (uint16) tZOM[ucID].ucToothTelCt;
      ushTmp += ushdN;
      ushTmp /= (uint16) (tZOM[ucID].ucToothTelCt + 1);
      tZOM[ucID].ucABSRef[i] = (uint8) ushTmp;
    }
    tZOM[ucID].ucToothTelCt++;
  }
}

static void GenCmpVal3(uint8 ucID){
  unsigned long ulTmp;
  uint16 ushdN, ushTmp, ushdN2, ushdN3, ushdN4;
  uint8 i;

  if(tZOM[ucID].ucToothTelCt > (cFPARefWidth-1)){
    if((uint8) (128 + cFPARefWidth + 1) > tZOM[ucID].ucToothTelCt)
      tZOM[ucID].ucToothTelCt++;

    ushTmp = fp2ushABSingleTick(0);
    ushTmp -=ush1stABSTickFL;
    if( ushTmp > ushMinStretch4Decision())
        tZOM[ucID].ucStatus |= cMinStretch;

    for(i = 0; i < cSumABSig; i++){
      ushTmp = ushGetAnZahn();
      ushdN =  fp2ushABSingleTick(i);
      ushdN %= ushTmp;
     ushdN2= ( ushdN > 0) ? (ushdN - 0):(ushdN + 0);
      ushdN3= ( ushdN > 24) ? (ushdN - 24):(ushdN + 24);
      ushdN4= ( ushdN > 72) ? (ushdN - 72):(ushdN + 72);

#ifdef pb_ModulTest_050104
      tZOM[ucID].ucCurdN[i] = (uint8) ushdN;
#endif

      if(tZOM[ucID].ucToothTelCt > cFPARefWidth + 1){
        if(tZOM[ucID].ucToothTelCt < (uint8) (128 + cFPARefWidth)){
           tZOM[ucID].ushMVdN[i] += ushdN;
          tZOM[ucID].ushMVdN2[i] += ushdN2;
        tZOM[ucID].ushMVdN3[i] += ushdN3;
          tZOM[ucID].ushMVdN4[i] += ushdN4;
        }
        else{
           if(tZOM[ucID].ucToothTelCt == (uint8) (128 + cFPARefWidth) ){
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
          ushTmp = tZOM[ucID].ushMVdN[i];
           ulTmp = (unsigned long) ushTmp << 7;
          ulTmp -= (unsigned long) ushTmp;
          ulTmp += (unsigned long) ushdN;
          ulTmp += (unsigned long) 64;
           ulTmp >>= 7;
          tZOM[ucID].ushMVdN[i] = (uint16) ulTmp;

          ushTmp = tZOM[ucID].ushMVdN2[i];
           ulTmp = (unsigned long) ushTmp << 7;
          ulTmp -= (unsigned long) ushTmp;
          ulTmp += (unsigned long) ushdN2;
          ulTmp += (unsigned long) 64;
           ulTmp >>= 7;
          tZOM[ucID].ushMVdN2[i] = (uint16) ulTmp;
#if(1)
          ushTmp = tZOM[ucID].ushMVdN3[i];
           ulTmp = (unsigned long) ushTmp << 7;
          ulTmp -= (unsigned long) ushTmp;
          ulTmp += (unsigned long) ushdN3;
          ulTmp += (unsigned long) 64;
           ulTmp >>= 7;
          tZOM[ucID].ushMVdN3[i] = (uint16) ulTmp;

        ushTmp = tZOM[ucID].ushMVdN4[i];
           ulTmp = (unsigned long) ushTmp << 7;
          ulTmp -= (unsigned long) ushTmp;
          ulTmp += (unsigned long) ushdN4;
          ulTmp += (unsigned long) 64;
           ulTmp >>= 7;
          tZOM[ucID].ushMVdN4[i] = (uint16) ulTmp;
#endif
        }
      }
      else{
        tZOM[ucID].ushMVdN[i] = ushdN;
        tZOM[ucID].ushMVdN2[i] = ushdN2;
#if(1)
      tZOM[ucID].ushMVdN3[i] = ushdN3;
        tZOM[ucID].ushMVdN4[i] = ushdN4;
#endif
      }

      if(tZOM[ucID].ucToothTelCt < (uint8) (128 + cFPARefWidth)){
         ushTmp =  tZOM[ucID].ushMVdN[i] / ((uint16) (tZOM[ucID].ucToothTelCt - cFPARefWidth));
        if( ushdN > ushTmp )
          ushTmp = ushdN - ushTmp;
        else
          ushTmp -= ushdN;
      }
      else{
         if(ushdN > tZOM[ucID].ushMVdN[i])
          ushTmp = ushdN - tZOM[ucID].ushMVdN[i];
        else
          ushTmp = tZOM[ucID].ushMVdN[i] - ushdN;
      }
      ushTmp += tZOM[ucID].ushPosCompVal[i];
      if(ushTmp > tZOM[ucID].ushPosCompVal[i])
        tZOM[ucID].ushPosCompVal[i] = ushTmp;
        if(tZOM[ucID].ucToothTelCt < (uint8) (128 + cFPARefWidth)){
         ushTmp =  tZOM[ucID].ushMVdN2[i] / ((uint16) (tZOM[ucID].ucToothTelCt - cFPARefWidth));
        if( ushdN2 > ushTmp )
          ushTmp = ushdN2 - ushTmp;
        else
          ushTmp -= ushdN2;
      }
      else{
         if(ushdN2 > tZOM[ucID].ushMVdN2[i])
          ushTmp = ushdN2 - tZOM[ucID].ushMVdN2[i];
        else
          ushTmp = tZOM[ucID].ushMVdN2[i] - ushdN2;
      }
      ushTmp += tZOM[ucID].ushPosCompVal2[i];
      if(ushTmp > tZOM[ucID].ushPosCompVal2[i])
        tZOM[ucID].ushPosCompVal2[i] = ushTmp;
        if(tZOM[ucID].ucToothTelCt < (uint8) (128 + cFPARefWidth)){
         ushTmp =  tZOM[ucID].ushMVdN3[i] / ((uint16) (tZOM[ucID].ucToothTelCt - cFPARefWidth));
        if( ushdN3 > ushTmp )
          ushTmp = ushdN3 - ushTmp;
        else
          ushTmp -= ushdN3;
      }
      else{
         if(ushdN3 > tZOM[ucID].ushMVdN3[i])
          ushTmp = ushdN3 - tZOM[ucID].ushMVdN3[i];
        else
          ushTmp = tZOM[ucID].ushMVdN3[i] - ushdN3;
      }
      ushTmp += tZOM[ucID].ushPosCompVal2[i];
      if(ushTmp > tZOM[ucID].ushPosCompVal2[i])
        tZOM[ucID].ushPosCompVal2[i] = ushTmp;
        if(tZOM[ucID].ucToothTelCt < (uint8) (128 + cFPARefWidth)){
         ushTmp =  tZOM[ucID].ushMVdN4[i] / ((uint16) (tZOM[ucID].ucToothTelCt - cFPARefWidth));
        if( ushdN4 > ushTmp )
          ushTmp = ushdN4 - ushTmp;
        else
          ushTmp -= ushdN4;
      }
      else{
         if(ushdN4 > tZOM[ucID].ushMVdN4[i])
          ushTmp = ushdN4 - tZOM[ucID].ushMVdN4[i];
        else
          ushTmp = tZOM[ucID].ushMVdN4[i] - ushdN4;
      }
      ushTmp += tZOM[ucID].ushPosCompVal2[i];
      if(ushTmp > tZOM[ucID].ushPosCompVal2[i])
        tZOM[ucID].ushPosCompVal2[i] = ushTmp;
    }
  }
  else{
     if(tZOM[ucID].ucToothTelCt < (uint8) 1)
      ush1stABSTickFL = fp2ushABSingleTick(0);
    for(i = 0; i < cMaxLR; i++){
      ushdN =  (fp2ushABSingleTick(i) % ushGetAnZahn());
      ushTmp = (uint16) tZOM[ucID].ucABSRef[i] * (uint16) tZOM[ucID].ucToothTelCt;
      ushTmp += ushdN;
      ushTmp /= (uint16) (tZOM[ucID].ucToothTelCt + 1);
      tZOM[ucID].ucABSRef[i] = (uint8) ushTmp;
    }
    tZOM[ucID].ucToothTelCt++;
  }
}

static uint8 ucGenDMnD(void){
  union
   {
    unsigned long ulTmp;
    uint8 ucSort[4];
  } tTmp;

  unsigned long ulCmpSum;
  uint8 i,j, ucRelCmpVal[4][4], ucTmp, ucMinIx, ucRet = 0;

  for( i = 0; i < cMaxLR; i++){
    if(0 == tZOM[i].ushPosCompVal2[0])
      break;
#ifndef pb_ModulTest_050104
     if( cMinCt4Dec > tZOM[i].ucToothTelCt)
      break;
    if(0 == (cMinStretch & tZOM[i].ucStatus))
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
  if(cMaxLR == i){
    for(i = 0; i < cMaxLR; i++){
      ulCmpSum = 0;
      for( j = 0; j < cSumABSig; j++)
        ulCmpSum += ((tZOM[i].ushPosCompVal2 [j] < tZOM[i].ushPosCompVal [j]) ? tZOM[i].ushPosCompVal2 [j]:tZOM[i].ushPosCompVal [j]);
      for( j = 0; j < cSumABSig; j++){
        if(tZOM[i].ushPosCompVal[j] < tZOM[i].ushPosCompVal2[j]){
          if(tZOM[i].ushPosCompVal[j] > 0){
            tTmp.ulTmp =  (unsigned long) tZOM[i].ushPosCompVal[j] * 100;
            tTmp.ulTmp /= ulCmpSum;
            ucRelCmpVal[i][j] = (uint8) tTmp.ulTmp;
          }
          else
            ucRelCmpVal[i][j] = (uint8) 1;
        }
        else{
          if(tZOM[i].ushPosCompVal2[j] > 0){
            tTmp.ulTmp =  (unsigned long) tZOM[i].ushPosCompVal2[j] * 100;
            tTmp.ulTmp /= ulCmpSum;
            ucRelCmpVal[i][j] = (uint8) tTmp.ulTmp;
          }
          else
            ucRelCmpVal[i][j] = (uint8) 1;
        }
        if(0 == ucRelCmpVal[i][j])
          ucRelCmpVal[i][j] = 1;
#ifdef pb_ModulTest_050104
        tZOM[i].ucRelCmpVal[j] = ucRelCmpVal[i][j];
#endif
      }
      if(3 == cSumABSig)
        ucRelCmpVal[i][cSumABSig] = (uint8) 0;
#ifdef pb_ModulTest_050104
      tZOM[i].ucRelCmpVal[cSumABSig] = ucRelCmpVal[i][cSumABSig];
#endif
    }

    tTmp.ulTmp = (unsigned long) 0;
    ucTmp = cMaxLR;
    for(i = 0; i < cMaxLR; i++){
      SortBiggest1st(ucRelCmpVal[i],tTmp.ucSort,cSumABSig);
      if((ucRelCmpVal[i][tTmp.ucSort[cSumABSig-2]] - ucRelCmpVal[i][tTmp.ucSort[cSumABSig-1]]) > 4){
        for( j = 0; j < cMaxLR; j++)
          if( j != tTmp.ucSort[cSumABSig-1])
            ucRelCmpVal[i][j] = (uint8) 0;
          else
            if((uint8) 0 == ucRelCmpVal[i][j])
              ucRelCmpVal[i][j] = (uint8) 1;
      }
      else{
        if( cMaxLR == ucTmp){
          if(3 == cSumABSig)
            ucTmp = i;
          else
            ucTmp = cMaxLR + 1;
        }
        else
          ucTmp = cMaxLR + 1;

        for( j = 0; j < cMaxLR; j++)
          ucRelCmpVal[i][j] = (uint8) 0;
      }
    }
    if(ucTmp < (cMaxLR + 1)){
      tTmp.ucSort [0] = cMaxLR;
      for( j = 0; j < cMaxLR; j++){
        ucMinIx = cMaxLR;
        for(i = 0; i < cMaxLR; i++){
          if(ucRelCmpVal[i][j] > 0){
            if(ucMinIx == cMaxLR)
              ucMinIx = i;
            else{
              if(ucTmp < cMaxLR)
                break;
              if(ucRelCmpVal[i][j] < ucRelCmpVal[ucMinIx][j]){
                if((ucRelCmpVal[ucMinIx][j] - ucRelCmpVal[i][j]) > 10){
                  ucTmp = ucMinIx;
                  ucRelCmpVal[ucMinIx][j] = 0;
                  ucMinIx = i;
                }
                else
                  break;
              }
              else{
                if((ucRelCmpVal[i][j] - ucRelCmpVal[ucMinIx][j]) > 10){
                  ucTmp = i;
                  ucRelCmpVal[i][j] = 0;
                }
                else
                  break;
              }
            }
          }
        }
        if(i < cMaxLR)
          break;
        if(ucMinIx == cMaxLR){
          if(tTmp.ucSort [0] < cMaxLR)
            break;
          else
            tTmp.ucSort [0] = j;
        }
      }
      if( j == cMaxLR){
        for(i = 0; i < cMaxLR; i++){
#ifdef pb_ModulTest_050104
          if(0 == (cMinStretch & tZOM[i].ucStatus))
            break;
          if( cMinCt4Dec > tZOM[i].ucToothTelCt)
            break;
#endif
          if( i == ucTmp )
            SetZOMWP(i,tTmp.ucSort [0]);
          else{
            for( j = 0; j < cMaxLR; j++)
              if(ucRelCmpVal[i][j] > 0 ){
                if(ucGetWPOfCol(ucGetColOfID(&tZOM[i].ulID)) == j)
                  SetZOMWP(i,j);
                else{
                  if(ucRelCmpVal[i][j] < 15)
                    SetZOMWP(i,j);
                  else{
                    i = cMaxLR +1;
                    break;
                  }
                }
              }
          }
        }
        if( cMaxLR == i)
          ucRet = 1;
      }
    }
  }
#ifdef pb_ModulTest_050104
  else{
    for(i = 0; i < cMaxLR; i++)
      for( j = 0; j < cMaxLR; j++)
        tZOM[i].ucRelCmpVal[j] = (uint8) 0;
  }
#endif
  return (ucRet);
}

void RebuildABSRef(uint8 ucWP){
  uint8 i;

  for(i = 0; i < cSumWE ;i++){
    if(tZOM[i].ucToothTelCt > 0){
      if( tZOM[i].ucABSRef [ucWP] > ucABSigOFL_MOD_ZAHN() )
        tZOM[i].ucABSRef [ucWP] -= ucABSigOFL_MOD_ZAHN();
      else
        tZOM[i].ucABSRef [ucWP] += ucMINUS_ABSigOFL_MOD_ZAHN();
    }
  }
}

void ReNewABSRef(void){
  uint8 i;

  for(i = 0; i < cSumWE ;i++){
    tZOM[i].ucToothTelCt = 0;
  }
}

/************************************************************************************************************
 ** function:   SortBiggest1st
 **
 ** ---------------------------------------------------------------------------------------------------------
 **
 ** purpose: grades an uint8acter array indirect via index array (bubblesort algorithm)
 ** ---------------------------------------------------------------------------------------------------------
 **
 ** input: ptVal = pointer to uint8acter array wich contains values to be graded
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

static void SortBiggest1st(uint8 *ptVal, uint8 *ptIx, uint8 ucMax){
  uint8 i,j, ucBuffer;

  for(i=0;i<ucMax;i++){
    ptIx[i] = i;
  }

  for(i = 1; i < ucMax; i++){
    for(j = i; j >= 1; j--){
      if(ptVal[ptIx[j]] > ptVal[ptIx[j-1]]){
        ucBuffer = ptIx[j];
        ptIx[j] = ptIx[j-1];
        ptIx[j-1] = ucBuffer;
      }
      else{
        break;
      }
    }
  }
}

void Very1stABSTickIinit(void){
  ush1stABSTickFL = 0;
}

uint16 ushGetAnZahn(void){
  return ( FULLTURNINABSTICKS );
}

uint8 ucABSigOFL_MOD_ZAHN(void){
  return ( (uint8)64);
 }

uint8 ucMINUS_ABSigOFL_MOD_ZAHN(void){
  return ( (uint8)32);
 }

static uint16 ushMinStretch4Decision(void){
  return ( 24000 );
 }

uint16 ushGetABSingleTickFr2(uint8 ucIx){
   return (ushGetABSingleTick (ucIx)-((uint16) ucGetTDL100()));
}
uint16 ushGetABSingleTickFr3(uint8 ucIx){
 return (ushGetABSingleTick (ucIx) - ushGetTDL210());
}
uint16 ushGetABSingleTickN90(uint8 ucIx){
  return (ushGetABSingleTick (ucIx)- QUARTURNINABSTICKS);
}
uint16 ushGetABSingleTickN90Fr2(uint8 ucIx){
  return (ushGetABSingleTick (ucIx)-((uint16) ucGetTDL100() + QUARTURNINABSTICKS));
}
uint16 ushGetABSingleTickN90Fr3(uint8 ucIx){
  return (ushGetABSingleTick (ucIx)-(ushGetTDL210() + QUARTURNINABSTICKS));
}
uint16 ushGetABSingleTickTDL(uint8 ucIx){
  return ( ushGetABSingleTick (ucIx) + (uint16) ucGetTDL(cRE15_4_2 ) );
}
uint16 ushGetABSingleTickTDLn180(uint8 ucIx){
  return ( ushGetABSingleTick (ucIx) + (uint16) ucGetTDL(cRE15_4_2 ) - HALFTURNINABSTICKS);
}
uint16 ushGetABSingleTickTDL_HS(uint8 ucIx){
  return ( ushGetABSingleTick (ucIx) + (uint16) ucGetTDL(cHSrange ) );
}
uint16 ushGetABSingleTickTDL_LS(uint8 ucIx){
  return ( ushGetABSingleTick (ucIx) + (uint16) ucGetTDL(cLSrange ) );
}
uint16 ushGetABSingleTickTDL_HSn180(uint8 ucIx){
  return ( ushGetABSingleTick (ucIx) + (uint16) ucGetTDL(cHSrange ) - (uint16) ucGetTDL(cIFS ));
}
uint16 ushGetABSingleTickTDL_LSn180(uint8 ucIx){
  return ( ushGetABSingleTick (ucIx) + (uint16) ucGetTDL(cLSrange ) - (uint16) ucGetTDL(cIFS ));
}
uint16 ushGetABSingleTickPAL(uint8 ucIx){
  return ( ushGetABSingleTick (ucIx));
}
static uint8 ucGetTDL(uint8 ucCorType){
  uint16 ushVtmp;
  uint8 ucIx;
  uint8* puCTab;
          static const uint8 cucCvHS[] =     {27,   27,   27,   27,   27,   27,   27,   27,   27,   27,   27,   27,   27,   27,   27,   27,   27,   27,   27,   27,   27,   27,   27,   27,   27,   27,   27,   27,   27,   25,   22,   21,   24,   25,   25,   25,   25,   25,   25,   25};
   static const uint8 cucIFS[] =      {46,   47,   47,   47,   47,   47,   47,   47,   47,   47,   47,   47, 47,   46,   46,   45,   45,   45,   43,   45,   45,   46,   46,   48,   49,   47,   47,   49,   49,   48,   49,   46,   48,   50,   50,   50,   50,   50,   50,   50};
   static const uint8 cucCvLS[] =     {48,   48,   46,   42,   39,   36,   34,   33,   31,   30,   30,   28,   26,   26,   24,   24,   25,   22,   21,   24,   25,   24,   26,   21,   18,   19,   22,   30,   30,   30,   30,   30,   30,   30,   30,   30,   30,   30,   30,   30};
      static const uint8 cucTDLatV[] = { 48,   48,   48,   46,   42,   39,   37,   36,   34,   34,   32,   31,   31,   29,   29,   29,   29,   28,   28,   28,   28,   28,   28,   28,   27,   27,   27,   27,   27, 27,   27,   27,   27,   27,   27,   27,   27,   27,   27,   27 };
     switch ( ucCorType ){
  case cRE15_4_2:
    puCTab = (uint8 *) cucTDLatV;
    break;
  case cHSrange:
    puCTab = (uint8 *) cucCvHS;
    break;
  case cLSrange:
    puCTab = (uint8 *) cucCvLS;
    break;
  case cIFS:
    puCTab = (uint8 *) cucIFS;
    break;
  default:
    puCTab = (uint8 *) cucTDLatV;
    break;
  }
   if(ushCuRotatsIn05msec > 0){
    ushVtmp = (ushCuRotatsIn05msec>>1) + 48000;
    ushVtmp /= ushCuRotatsIn05msec;
   }
  else
    ushVtmp =  (uint16) ucGetSpeed();
  if((uint16) ucGetSpeed() >= 20)
    if((ushVtmp >  ((uint16) ucGetSpeed() + 20)) || (ushVtmp <  ((uint16) ucGetSpeed() - 20)))
       ushVtmp =  (uint16) ucGetSpeed();
   ushVtmp =  (uint16) ucGetSpeed();

  ucIx = (uint8) ((((ushVtmp * 10)/5)+5)/10);
   if(ucIx > 0){
    ucIx--;
    if(ucIx > (sizeof(cucTDLatV) - (uint8) 1))
      ucIx = sizeof(cucTDLatV) - (uint8) 1;
  }

  return(puCTab[ucIx]);
}
static uint8 ucGetTDL100(void){
  uint16 ushVtmp;
  uint8 ucIx;
                                                                                static const uint8 cucTDL100atV[] = {6,12,18,24,30,36,42,48,55,61,67,73,79,85,91,97,103,109,115,121,127,133,139,145,152,158};

  ushVtmp =  (uint16) ucGetSpeed();
  ucIx = (uint8) ((((ushVtmp * 10)/5)+5)/10);
   if(ucIx > 0){
    ucIx--;
    if(ucIx > (uint8) 25)
      ucIx = (uint8) 25;
  }

  return(cucTDL100atV[ucIx]);
}
static uint16 ushGetTDL210(void){
  uint16 ushVtmp;
  uint8 ucIx;
                                                                                static const uint16 cushTDL210atV[] = {13,25,38,51,64,76,89,102,115,127,140,153,165,178,191,204,216,229,242,255,267,280,293,305,318, 331};

  ushVtmp =  (uint16) ucGetSpeed();
  ucIx = (uint8) ((((ushVtmp * 10)/5)+5)/10);
   if(ucIx > 0){
    ucIx--;
    if(ucIx > (uint8) 25)
      ucIx = (uint8) 25;
  }

  return(cushTDL210atV[ucIx]);
}

#ifdef pb_ModulTest_050104
void TESTPrintToothZOM_HL(void){
  uint8 i,j;
  uint8 aucWPSeq[][3] = {"FL","RL","FR","RR"};

  for(i = 0; i < 4;i++){
    printf(";ID[%s];Status[%s];ucFPATelCt[%s]",aucWPSeq[i],aucWPSeq[i],aucWPSeq[i]);
    for( j  = 0; j < 4 ; j++)
      printf(";dN[%s][%d]",aucWPSeq[i],j);
    for( j  = 0; j < 4 ; j++)
      printf(";MVdN[%s][%d]",aucWPSeq[i],j);
    for( j  = 0; j < 4 ; j++)
      printf(";CmpVal[%s][%d]",aucWPSeq[i],j);
    for( j  = 0; j < 4 ; j++)
      printf(";MVdN2[%s][%d]",aucWPSeq[i],j);
    for( j  = 0; j < 4 ; j++)
      printf(";CmpVal2[%s][%d]",aucWPSeq[i],j);
    for( j  = 0; j < 4 ; j++)
      printf(";RelCmp[%s][%d]",aucWPSeq[i],j);
  }
}
void TESTPrintToothZOMAsLine(void){
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
void TESTPrintFPAZOMSlot(uint8 ucSlot){
  uint8 j;

  printf(";%lu;0x%02X;%d",tZOM[ucSlot].ulID,tZOM[ucSlot].ucStatus,tZOM[ucSlot].ucToothTelCt );
  for( j  = 0; j < 4 ; j++)
    printf(";%d",tZOM[ucSlot].ucCurdN[j]);
  for( j  = 0; j < 4 ; j++)
    printf(";%d", tZOM[ucSlot].ushMVdN [j]);
  for( j  = 0; j < 4 ; j++)
    printf(";%d", tZOM[ucSlot].ushPosCompVal [j]);
  for( j  = 0; j < 4 ; j++)
    printf(";%d", tZOM[ucSlot].ushMVdN2 [j]);
  for( j  = 0; j < 4 ; j++)
    printf(";%d", tZOM[ucSlot].ushPosCompVal2 [j]);
  for( j  = 0; j < 4 ; j++)
    printf(";%d",tZOM[ucSlot].ucRelCmpVal [j]);
}
void TESTPrinToothZOMSummary(uint8 i){
  uint8 j;

  if(i < 4){
      printf(" %d; 0x%02X; %d; %d;",tZOM[i].ulID,tZOM[i].ucStatus ,tZOM[i].ucProbeCt ,tZOM[i].ucToothTelCt);
      for( j = 0; j < cMaxLR; j++)
        printf("%d;",tZOM[i].ucRelCmpVal[j]);
      for( j = 0; j < cMaxLR; j++)
        printf("%d;",tZOM[i].ushPosCompVal[j]);
  }
  else
    for( j = 0; j < 3; j++)
     printf(" %d; %d; %d; %d;",0,0,0,0);
}
#endif
 #endif

static uint16 ushGetMean(uint16 a, uint16 b){

   uint16 temp;

   temp = (a > b) ? a-b: b-a;

   temp = (temp > 48) ?  ((a + b + 96)/2) :(a+b) /2;

   return (temp > 96) ? temp-96 : temp;
}
