/******************************************************************************/
/* File              : WAlloc.c                                               */
/* Author            : Nagaraja HULIYAPURADA MATA                             */
/* Copyright (c)2024 : All rights reserved.                                   */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#define WALLOC_INT
#include "Std_Types.hpp"

#include "WallocX.h"
#include "Walloc_IF.h"
#include "walloc.h"
#include "AEC.h"
#include "FPA.h"
#include "tss_stdX.h"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define cWheelPos_RR                                                        0x03 //TBD: Move to RTE
#define cSLHistAssignTimeInSec                                               180
#define cTIME_OUT                                                            540
#define cHistIDProtectTime                                                   240
#define c5MinDriveTimeInSec                                                  300
#define cAll                                                         ((uint8) 0)
#define cLearnOnly                                                   ((uint8) 1)
#define cWPER                                                               0x10

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/
static const uint8 ucWACtrlBreakc = 0x02;
static const uint8 ucWACtrlFixc   = 0x01;

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
static uint32 aulHistoryID[cMaxLR];
static uint8  aucHistoryWP[cMaxLR];
static uint8  aucWPorPWP[cMaxLR]     = {4, 4, 4, 4};
static uint16 ushDriveTimeInSec      = 0;
static uint16 ushDriveTimeOverPalMax = 0;
static uint8  ucLearnError[cMaxLR]   = {NoError, NoError, NoError, NoError};
static uint8  ucLocatError[cMaxLR]   = {NoError, NoError, NoError, NoError};
static uint8  ucABSignalMissin       = NoError;
static uint8  ucDAGLearnState        = Autolearn_Learning;
static uint8  ucLearnMode            = cNoLearn;
static uint8  ucWAStateHi            = 0;
static uint8  ucWAState;

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
static void   dblCk4LocEr                           (void);
static void   MergeWPandPWP                         (void);
static void   TOXpired                              (void);
static void   UpdateDAGLearnState                   (void);
static void   ClearAlLearNLocatError                (uint8 ucErrType);
static void   UpdateALState                         (uint8 ui8Trigger);
static uint8  considerationeDiAssegnazioneCostretto (void);
static uint8  ucBadHist2Def                         (void);
static uint8  ucFinishViaHistory                    (void);
static uint8  ucForceAutoLocate                     (void);
static uint8  ucGetMisOrNoLearnError                (void);
static uint8  ucNrOfLearnError                      (void);
static uint8  ucNrOfLocatError                      (void);
static uint8  ucNrOfLocatErrorAndPosForce           (void);
static uint8  ucNrOfUKWPinHist                      (void);
static uint8  ucNrOfUKWPinZOM                       (void);
static uint8  ucSL3MinHistPreFinish                 (void);
static uint8  ui8AnyHistIdMissing                   (void);
static uint8  uc3NewIDsAllocated                    (uint8       ucMinCt4NewID);
static uint8  ucAssessDAGSLUC                       (uint8       ucWPs);
static uint8  ucCmpHist2ZOMID                       (uint8       ucVZS);
static uint8  ucGetAnyLocatErrors                   (uint8       ucDontTouch);
static uint8  ucNewZomIDsFit2MissingHistID_WP       (uint8       ucNewNMissing);
static uint8  ucFinalFreeze                         (uint8       ucMinCt4HistER, uint8 ucMinCt);
static uint8  ucGetNrOfNewIDs                       (uint8*      p2Slots);
static uint8  ucGetNrOfNewIDsInLM                   (uint16*     p2Slots, uint8 ucMinCt);
static uint8  ucGetNrOfNewIDsInLM_SL                (uint16*     p2Slots, uint8 ucMinCt);
static uint8  ucPasSupplFilter                      (tRFTelType* p2Tel);
static uint8  ucSL31Finish                          (uint8       ucMinCt4NewID);
static uint8  ucTakeOverHistWP                      (uint8       ucHistIx, uint8 ucZomIx);
static uint8  ucWrZom2History                       (uint8       ucNewNMissing);
static uint16 ushLqiTribute                         (uint16      ushCandidate);
static uint16 ushCompLearn                          (tRFTelType* ptInputWA);
static uint16 ushLearnInOver8                       (tRFTelType* ptInputWA);
static uint16 ushSpeciaLearn                        (tRFTelType* ptInputWA);
static uint16 ui16NewIdFits                         (uint16      ushNewID,  uint16 ushHistSet);
static uint16 ushWhlSetRdy2Freeze                   (uint8       ucMinCt,   uint8  ucMinCt4HistERc, uint8 bLearnNewIDsFlag);
static uint16 ucFindMissingHistoryIDs               (uint32*     ptHistID,  uint8  ucMinProbeCt,    uint8 ucSlots2Search);
static uint16 ucFindNoLearnHistoryIDs               (uint32*     ptHistID,  uint8  ucMinProbeCt,    uint8 ucSlots2Search);
static uint16 ushIDinLearnModeSetInHist             (uint32*     ptHistSet, uint8  ucMinProbeCt,    uint8 ucSlots2Search);
static uint16 ushIDSetInHist                        (uint32*     ptHistSet, uint8  ucMinProbeCt,    uint8 ucSlots2Search);
static uint16 ushIDSetInHistNAlignWP                (uint32*     ptHistSet, uint8  ucMinProbeCt,    uint8 ucSlots2Search);
static uint16 ushSetHistIDs2ER                      (uint32*     ptHistSet, uint8  ucMinProbeCt,    uint8 ucSlots2Search);

uint8 ucNrOfBitSet(uint16 ushTarget){
  uint8 i, ucHits = 0;
  for(i = 0; i < 16; i ++){
    if((ushTarget & (1<<i)) > 0){
      ucHits++;
    }
  }
  return ucHits;
}

static void SetWAStateZOChange(uint8 ucChangedPos){
  ucWAState   &= 0x0F;
  ucWAState   |= (uint8) ((ucChangedPos&0x0F)<<4);
  ucWAStateHi &= 0x0F;
  ucWAStateHi |= (uint8) (ucChangedPos&0xF0);
}

static void ClearZOM(uint8 ucIx){
  uint8 i,j;
  if(ucIx > cSumWE){
  }
  else{
    if(ucIx == (uint8) cSumWE){
      for(i = 0; i < ucIx; i++){
        for(j = 0; j < (uint8) sizeof(struct ZOMSlot);j++){
          *((uint8 *) &tZOM[i] + j) = 0;
        }
      }
    }
    else{
      for(j = 0; j < (uint8) sizeof(struct ZOMSlot);j++){
        *((uint8 *) &tZOM[ucIx] + j) = 0;
      }
    }
  }
}

static void PutulZOMID(uint8 ucIx,uint32 *p2ID){
  if(ucIx < cSumWE){
    tZOM[ucIx].ulID = *p2ID;
  }
}

static uint8 ucGetZOMWP(uint8 ucIx){
   if(ucIx < cSumWE){
      switch(tZOM[ucIx].ucStatus & ~cNoWPos){
         case 0x01: return((uint8)0);
         case 0x02: return((uint8)1);
         case 0x04: return((uint8)2);
         case 0x08: return((uint8)3);
         default:   return((uint8)4);
      }
   }
   else{
      return((uint8)4);
   }
}

static uint8 ucGetProbeCt(uint8 ucIx){
  if(ucIx < cSumWE){
    return (tZOM[ucIx].ucProbeCt);
  }
  else{
    return ( (uint8) 0);
  }
}

static uint8 ucGetFreeZOMPos(void){
  uint8 i;
  for(i = 0; i < cSumWE; i++){
    if(tZOM[i].ulID == (uint32) 0){
      break;
    }
  }
  return(i);
}

static uint8 ucStartWA(void){
  uint8 i, ucRet = 0;
  for(i = 0; i < cSumWE; i++){
    if(tZOM[i].ucProbeCt  > 0){
      ucRet++;
    }
  }
  ucRet  =  (ucRet > (uint8) 0) ? (uint8) 1:(uint8) 0;
  return(ucRet);
}

uint16 ushAlignZOM(uint16 ushERSlot){
  uint8 i, j, k, ucCt = 0;
  struct ZOMSlot tempZom;

  for(i = 0; i < cSumWE; i++){
    if((((uint16 ) (1<<i)) & ushERSlot) > 0){
      ucCt++;
    }
    else{
      for(j = i+1; j < cSumWE; j++){
        if((((uint16 ) (1<<j)) & ushERSlot) > 0){
          ucCt++;
          for(k = 0; k < (uint8) sizeof(struct ZOMSlot); k++){
            *(((uint8 *) &tempZom) + k) = *(((uint8 *) &tZOM[i]) + k) ;
            *(((uint8 *) &tZOM[i]) + k) = *(((uint8 *) &tZOM[j]) + k);
            *(((uint8 *) &tZOM[j]) + k) = *(((uint8 *) &tempZom) + k);
          }
          ushERSlot |= (1<<i);
          ushERSlot &= ~(1<<j);
#ifdef AEC
          ResetACM();
#endif
          break;
        }
      }
    }
    if(ucCt == cMaxLR){
      break;
    }
  }
  return (ushERSlot);
}

static uint8 ucLowestProbe(uint16 ushException){
  uint8 i, ucMinIx = cSumWE;
  for( i = 0; i < cSumWE; i++){
    if(((0x01<<i) & ushException) == 0){
      ucMinIx = i;
      break;
     }
  }
  for( i = (ucMinIx + 1); i < cSumWE; i++){
    if(((0x01<<i) & ushException) == 0){
      if(tZOM[i].ucTelCtLearnBit < tZOM[ucMinIx ].ucTelCtLearnBit){
        ucMinIx = i;
      }
    }
  }
  return( ucMinIx );
}

uint8 bCheckHistIDReception(void){
  uint16 ushHelp;
  ushHelp = ushIDSetInHist(aulHistoryID, 1, cSumWE);
  if((cMaxLR == ucNrOfBitSet(ushHelp)) && ((ucGetHistoryState()&cHiStateZG) == cHiStateZG))    return 1;
  else    return 0;
}

static uint8 ucCheckWheelPos(uint8 ucID, tRFTelType * ptInputWA){
  uint8 ucRet = 0;
  uint16 ushTmp = 0x000F;
#ifdef FPA
   if((ucWAStateHi & cTO) > (uint8) 0){
    if(ucAdjABSIface(ucID, ptInputWA) > (uint8) 0)
       BuildCmpVal (ucID);
   }
   else
    ucRet = ucConceptFixPos0(ucID, ptInputWA);
  if((uint8) 0 == ucRet)
    if((uint8) cMaxLR == ucFPDecPossible (&ushTmp, cMinCt4Dec ))
      if((uint8) 0 == ucNrOfUKWPinZOM() )
        ucRet = (uint8) 1;
#endif
  return((uint8) ucRet);
}

static uint16 ushIDSetInHist(uint32 *ptHistSet, uint8 ucMinProbeCt, uint8 ucSlots2Search){
  uint8 i,j;
  uint16 ushRet = 0;
  for( i = 0; i < cMaxLR; i++){
    if(ptHistSet[i] == (uint32) 0){
      ushRet = 0;
      break;
    }
    else{
      for( j = 0; j < ucSlots2Search; j++){
        if((ptHistSet[i] == ulGetZOMID(j)) && (ucGetProbeCt(j) >= ucMinProbeCt )){
          ushRet |= (1<<j);
          break;
        }
        else{
          if(ulGetZOMID(j) == (uint32) 0){
            break;
          }
        }
      }
    }
  }
  return ushRet;
}

static uint16 ushIDinLearnModeSetInHist(uint32 *ptHistSet, uint8 ucMinProbeCt, uint8 ucSlots2Search){
  uint8 i,j;
  uint16 ushRet = 0;
  for( i = 0; i < cMaxLR; i++){
    if(ptHistSet[i] == (uint32) 0){
      ushRet = 0;
      break;
    }
    else{
      for( j = 0; j < ucSlots2Search; j++){
        if((ptHistSet[i] == ulGetZOMID(j)) && (ucGetZomTelCtLearnBit(j) >= ucMinProbeCt )){
          tZOM[j].ucStatus |= cZOMStatHistER;
          ushRet |= (1<<j);
          break;
        }
        else{
          if(ulGetZOMID(j) == (uint32) 0){
            break;
          }
        }
      }
    }
  }
  return ushRet;
}

static void Put2Slot(tRFTelType *ptInputWA, uint8 ucIx){
  uint8 ucSpin = (uint8) 0;
  if(ucIx < cSumWE){
    tZOM[ucIx].ulID = ptInputWA->EdgeCnt.ulID;
    if( (tZOM[ucIx].ucProbeCt < (uint8) 255) && ((tZOM[ucIx].ushRssiSum + (uint16) ptInputWA->Struc .ucAvg) >= tZOM[ucIx].ushRssiSum) ){
      tZOM[ucIx].ushRssiSum += (uint16) ptInputWA->Struc .ucAvg;
      tZOM[ucIx].ucProbeCt++;
    }
    if( (cTelTypeSELPAL1== ptInputWA->Header.ucTType) || ( cTelTypeAK35defLMA == ptInputWA->Header.ucTType)){
      tZOM[ucIx].ucTelCtLearnBit++;
    }
    if( (cTelTypeSELPAL  == (ptInputWA->Header.ucTType&0x0F)) ){
      tZOM[ucIx].ucFrameCounter = (uint8)((ptInputWA->SchraderFP.ushStatusField>>8)&0x1F);
      if(ptInputWA->SchraderFP.ucPAL == 0x0){
 #ifdef Test_LOG_ENABLE
        tZOM[ucIx].ucToothTelCtNoLearnMode++;
 #endif
      }
      else if(ptInputWA->SchraderFP.ucPAL == 0x01){
 #ifdef Test_LOG_ENABLE
        tZOM[ucIx].ucToothTelCtNoCorr++;
 #endif
      }
      else if(ptInputWA->SchraderFP.ucPAL == 0xFF){
 #ifdef Test_LOG_ENABLE
        tZOM[ucIx].ucToothTelCtNoCorr++;
 #endif
      }
      else{
#ifdef Test_LOG_ENABLE
        if((ptInputWA->Header .ucTType & 0x20) == 0x20)
           tZOM[ucIx].ucToothTelCtCorrLearnBit++;
        else
          tZOM[ucIx].ucToothTelCtCorrNoLearnBit++;
#endif
      }
    }
    else if(cTelTypePeak == ptInputWA->Header.ucTType){
#ifdef AEC
      tZOM[ucIx].ushXPSum++;
#endif
#ifdef Test_LOG_ENABLE
                tZOM[ucIx].ucToothTelCtNoLearnMode++;
 #endif
    }
    else if(cTelTypeAK35def == ptInputWA->Header.ucTType){
#ifdef Test_LOG_ENABLE
      tZOM[ucIx].ucToothTelCtNoLearnMode++;
 #endif
    }
    else if( cTelTypeEdgeCnt == ptInputWA->Header.ucTType ){
       ucSpin = ptInputWA->EdgeCnt.ucSpin;
#ifdef CONCEPT4
      if(tZOM[ucIx].ushStarTi == 0){
        tZOM[ucIx].ushStarTi = ptInputWA->Struc.ushTimeStamp;
        tZOM[ucIx].ushLogTime = ptInputWA->Struc.ushTimeStamp;
        tZOM[ucIx].ucStarTiHi = (uint8) 0;
       }
      else{
         if(ptInputWA->Struc.ushTimeStamp < tZOM[ucIx].ushLogTime)
          tZOM[ucIx].ucStarTiHi +=1;
        tZOM[ucIx].ushLogTime = ptInputWA->Struc.ushTimeStamp;
      }
#endif
#ifdef Test_LOG_ENABLE
                tZOM[ucIx].ucToothTelCtNoLearnMode++;
 #endif
    }
    else if(cTelTypeAK35BeruMed == ptInputWA->Header.ucTType){
      ucSpin = ptInputWA->AK35BeruMed .ucSpinDir;
#ifdef AEC
      if( ucEarlyEnd(ucIx) > 0 )
        StartWATO( 1 );
 #endif
#ifdef Test_LOG_ENABLE
                tZOM[ucIx].ucToothTelCtNoLearnMode++;
 #endif
    }
    else if(cTelTypeAK35BeruL == ptInputWA->Header.ucTType){
      ucSpin = ptInputWA->AK35BeruL  .ucSpinDir;
#ifdef Test_LOG_ENABLE
                tZOM[ucIx].ucToothTelCtNoLearnMode++;
 #endif
    }
    else if(cTelTypeAK35BeruS  == ptInputWA->Header.ucTType){
      ucSpin = ptInputWA->AK35BeruS  .ucSpinDir;
#ifdef Test_LOG_ENABLE
          tZOM[ucIx].ucToothTelCtNoLearnMode++;
 #endif
        }
    else{
#ifdef Test_LOG_ENABLE
           tZOM[ucIx].ucToothTelCtNoLearnMode++;
 #endif
    }

    if( (ucSpin > 0) &&
      (tZOM[ucIx].ucLeftCt  < (uint8) 255) &&
      (tZOM[ucIx].ucRightCt < (uint8) 255)
   ){
      if( (ucSpin & cIDStateSpinLeft) == cIDStateSpinLeft){
        tZOM[ucIx].ucLeftCt++;
      }
      if( (ucSpin & cIDStateSpinRight) == cIDStateSpinRight){
        tZOM[ucIx].ucRightCt++;
      }
    }
  }
  else{
  }
  return;
}

static uint8 ucPutInZOM(tRFTelType* ptInputWA, WAParameter* ptWAPar){
  uint8 ucIx;
  ucIx = ucGetZOMPosOfID(&ptInputWA->AK35def.ulID);
  if(ucIx < cSumWE){
    Put2Slot(ptInputWA, ucIx);
  }
  else{
    ucIx = ucGetFreeZOMPos();
    if( ucIx < cSumWE ){
      Put2Slot(ptInputWA, ucIx);
    }
    else{
      if(ucGetERState() == 0){
        ucIx = ucLowestProbe(ushIDSetInHist(aulHistoryID,(uint8) 1,cSumWE));
        if(ucIx < cSumWE){
          ClearZOM(ucIx);
#ifdef AEC
          ResetACM();
#endif
          Put2Slot(ptInputWA, ucIx);
        }
        else{
          ucIx = cSumWE;
        }
      }
      else{
        ucIx = cSumWE;
      }
    }
  }
  UNUSED(ptWAPar);
  return ucIx;
}

uint8 ucSetHistory(uint8 ucType, uint8 ucVZS){
  uint8 i,j,ucNrUK,ucNew,ucRet = 0x0f, ucChangedHistSlots = 0;
  GetWADataEE(cHistorySet1, (uint8 *) aulHistoryID, (uint8) sizeof(aulHistoryID) );
  GetWADataEE(cHistoryWPSet1, aucHistoryWP, (uint8) sizeof(aucHistoryWP) );
  ucNew = ucCmpHist2ZOMID(ucVZS);
  ucNrUK = ucNrOfUKWPinZOM();
  if( (((uint8) 0) == ucNrOfBitSet ((uint16) ucNew) ) && (ucNrUK > ucNrOfUKWPinHist ()) && !((((uint8) 1) ==  ucNrUK) && (ui8AnyHistIdMissing () == ((uint8) 0)))  )
     ucType = cWAStateER;

  for(i = 0; i < cMaxLR; i++){
    for(j = 0; j < cMaxLR; j++){
      if(( aulHistoryID[i] == ulGetZOMID(j) ) && (((ucVZS & (uint8) (1<<j)) > 0))){
        ucRet &= (uint8) (~(uint8) (0x01 << j));
        if(ucType == cWAStateZO){
          if((ucGetZOMWP(j) != aucHistoryWP[i]) && (ucGetZOMWP(j) < 4)){
            ucNrUK = ucGetColOfWP(ucGetZOMWP(j));
            if( cMaxLR > ucNrUK ){
              aucHistoryWP[ucNrUK] = 4;
              ucRet |= (uint8) (0x10 << ucNrUK);
            }
            aucHistoryWP[i] = ucGetZOMWP(j);
            ucRet |= (uint8) (0x10 << i);
          }
        }
        break;
      }
    }
  }

  ucRet = ucRet & (0xF0|ucVZS);

  if(1 < ucNrOfBitSet((uint16) (ucRet & 0x0F))){
    if( ucWACtrlFixc == tWAPar.ucWACtrl ){
      tWAPar.ucWACtrl = ucDefWACtrl;
      ucWAState &= (uint8) ~(cWAStateZO);
      PutWADataEE(cWAParameter, (uint8 *) &tWAPar , (uint8) sizeof(WAParameter));
    }
  }
  if(ucRet > 0){
    for(i = 0; i < cMaxLR; i++){
      if((ucRet & (0x01 << i)) > 0){
        ucNrUK = ucGetColOfWP(ucGetZOMWP(i));
        if((ucGetZOMWP(i) <= cWheelPos_RR)  && ((ucNew & ((1<<ucNrUK)&0x0F)) > 0)){
          aulHistoryID[ucNrUK] = ulGetZOMID(i);
          ucNew &= (uint8) (~(uint8) (1 << ucNrUK));
          ucChangedHistSlots |= (uint8) (1 << ucNrUK);
        }
        else{
          for( j = 0; j < cMaxLR; j++){
            if((ucNew & ((uint8) (1 << j))) > 0){
              aulHistoryID[j] = ulGetZOMID(i);
              ucNew &= (uint8) (~(uint8) (1 << j));
              ucChangedHistSlots |= (uint8) (1 << j);
              if((0 < ucNrOfBitSet((uint16) (ucRet & 0x0F)))||(ucNrOfUKWPinHist() > 0)){
                  aucHistoryWP[j] = 4;
                  ucRet |= (uint8) (0x10 << j);
              }
              if(cWAStateZO == ucType){
                if((ucGetZOMWP(i) <= cWheelPos_RR ) && (aucHistoryWP[j] != ucGetZOMWP(i))){
                  if( cMaxLR > ucNrUK ){
                    aucHistoryWP[ucNrUK] = 4;
                    ucRet |= (uint8) (0x10 << ucNrUK);
                  }
                  aucHistoryWP[j] = ucGetZOMWP(i);
                  ucRet |= (uint8) (0x10 << j);
                }
              }
              break;
            }
          }
        }
      }
    }

    if((cMaxLR == ucNrOfBitSet ((uint16) ucVZS )) || ((uint8) 2 > ucNrOfUKWPinHist ()))
      ucRet |= ucForceAutoLocate ();
    PutWADataEE(cHistorySet1, (uint8 *) aulHistoryID, (uint8) sizeof(aulHistoryID));
    PutWADataEE(cHistoryWPSet1, aucHistoryWP, (uint8) sizeof(aucHistoryWP));
  }

  return ((ucRet&0xF0)|ucChangedHistSlots);
}

static void RestoreHistory(void){
  uint8 i,j,ucCt = 0;
  if(aulHistoryID[0] > (uint32) 0){
    if( ucGetERState() == 1 ){
      for( i = 0; i < cMaxLR; i++){
        for( j = 0; j < cMaxLR; j++ ){
          if((uint8) 0 < ucTakeOverHistWP (j,i))
            ucCt++;
        }
      }
    }
    else{
      for( i = 0; i < cMaxLR; i++){
        PutulZOMID(i,&aulHistoryID[i]);
        if((uint8) 0 < ucTakeOverHistWP (i,i))
            ucCt++;
      }
      ucWAState |= cWAStateER;
    }
    if(ucCt < cMaxLR){
      for( i = 0; i < cMaxLR; i++){
        SetZOMWP(i, cWPER);
      }
    }
    else{
      ucWAState |= cWAStateZO;
    }
  }
}

uint8 ucGetZOMPosOfID(uint32 *pt2ID){
  uint8 i;
  for(i = 0; i < cSumWE; i++){
    if(*pt2ID == tZOM[i].ulID){
      break;
    }
  }
  return i;
}

uint8 ucGetZOMPalFrameCounter(uint8 ucIx){
  if(ucIx < cSumWE){
    return (tZOM[ucIx].ucFrameCounter);
  }
  else{
    return ( (uint8) 0);
  }
}

void SetZOMWP(uint8 ucIx,uint8 ucWP){
  if(ucIx < cSumWE){
    tZOM[ucIx].ucStatus &= cNoWPos;
    if(ucWP < cMaxLR){
      tZOM[ucIx].ucStatus |= (uint8) (0x01 << ucWP);
    }
  }
}

uint32 ulGetZOMID(uint8 ucIx){
  if(ucIx < cSumWE){
    return (tZOM[ucIx].ulID);
  }
  else{
    return ( (uint32) 0);
  }
}

uint32 ulGetID(uint8 ucIx){
  if(ucIx < cMaxLR){
    return (aulHistoryID[ucIx]);
  }
  else{
    return ( (uint8) 0);
  }
}

uint8 ucGetColOfID(uint32 *pt2ID){
  uint8 i;
  for(i = 0; i < cMaxLR; i++){
    if(*pt2ID == aulHistoryID[i]){
      break;
    }
  }
  return i;
}

uint8 ucGetWPOfCol(uint8 ucIx){
  if(ucIx < cMaxLR){
    return (aucHistoryWP[ucIx]);
  }
  else{
    return ((uint8) 4);
  }
}

uint8 ucGetColOfWP(uint8 ucIx){
  uint8 i;

  for( i = 0; i < cMaxLR; i++ ){
    if(aucHistoryWP[i] == ucIx){
      break;
    }
  }
  return i;
}

uint8* GETpucStartAdrWP(void){
  return (aucHistoryWP);
}

uint8 ucSetID(uint32 *pt2ID, uint8 *pt2Pos, uint8 ucSum){
  uint8 i, j, ucRet = 0, ucHelp;
  uint32 ulBufID;
  ucSum = (ucSum > cMaxLR) ? cMaxLR:ucSum;
  if(pt2ID[0] == (uint32) 0){
    for( i = 0; i < cMaxLR; i++){
      aulHistoryID[i] = 0;
      aucHistoryWP[i] = 4;
    }
    PutWADataEE(cHistorySet1, (uint8 *) aulHistoryID, (uint8) sizeof(aulHistoryID));
    PutWADataEE(cHistoryWPSet1, aucHistoryWP, (uint8) sizeof(aucHistoryWP));
    (void) WAInit((WAParNCfgType *) &ucLearnMode );
    ucRet = 0x0F;
  }
  else{
    GetWADataEE(cHistorySet1, (uint8 *) aulHistoryID, (uint8) sizeof(aulHistoryID));
    GetWADataEE(cHistoryWPSet1, aucHistoryWP, (uint8) sizeof(aucHistoryWP));
    if((aulHistoryID[0] == 0) && (ucSum == 1)){
      for(i = 0; i < cMaxLR; i++){
        aulHistoryID[i] = i + 1;
        if( pt2Pos[0] > 3 ){
          aucHistoryWP[i] = 4;
        }
        else{
          aucHistoryWP[i] = i;
        }
      }
    }
    ucHelp = 0x0f;
    for(i = 0; i < ucSum; i++){
      for(j = 0; j < cMaxLR; j++){
        if(pt2ID[i] == aulHistoryID[j]){
          ucHelp &= (uint8) (~(uint8) (0x01 << j));
          break;
        }
      }
    }
    for(i = 0; i < ucSum; i++){
      for(j = 0; j < cMaxLR; j++){
        if(pt2ID[i] == aulHistoryID[j]){
          break;
        }
      }
      pt2Pos[i] = (pt2Pos[i] < (uint8) 9) ? pt2Pos[i]:4;
      if(j == cMaxLR){
        if( pt2Pos[i] > cWheelPos_RR){
          if( pt2Pos[i] == (uint8) 4 ){
            ucRet = 0;
            i = ucSum;
          }
          else{
            ucHelp = pt2Pos[i] - (uint8) 5;
            aulHistoryID[ucHelp] = pt2ID[i];
            aucHistoryWP[ucHelp] = (uint8) 4;
            ucRet |= (0x10 << ucHelp);
            ucWAState &= (uint8) ~(cWAStateZO);
          }
        }
        else{
          for(j = 0; j < cMaxLR; j++){
            if(pt2Pos[i] == aucHistoryWP[j]){
              break;
            }
          }
          if( j == cMaxLR ){
            for(j = 0; j < cMaxLR; j++){
              if((ucHelp & (uint8)(0x01 << j)) > 0){
                ucHelp =  (uint8) (ucHelp & (uint8) ~((uint8) (0x01 << j)));
                break;
              }
            }
          }
          ulBufID = aulHistoryID[j];
          aulHistoryID[j] = pt2ID[i];
          aucHistoryWP[j] = pt2Pos[i];
          if((ucWAState & cWAStateZO) == cWAStateZO){
            ucHelp = ucGetZOMPosOfID(&ulBufID);
            tZOM[ucHelp].ulID = pt2ID[i];
            SetZOMWP(ucHelp, pt2Pos[i]);
            ucRet |= (1 << ucHelp);
          }
          else{
            ucRet |= (1 << pt2Pos[i]);
          }
        }
      }
      else{
        if(aucHistoryWP[j] == pt2Pos[i]){
        }
        else{
          if( pt2Pos[i] > cWheelPos_RR){
            if( pt2Pos[i] == (uint8) 4 ){
              ucRet = 0;
              i = ucSum;
            }
            else{
              aulHistoryID[j] = (uint32) i + 1;
              aucHistoryWP[j] = (uint8) 4;
              ucHelp = pt2Pos[i] - (uint8) 5;
              aulHistoryID[ucHelp] = pt2ID[i];
              aucHistoryWP[ucHelp] = (uint8) 4;
              ucRet |= (0x10 << ucHelp);
              ucWAState &= (uint8) ~(cWAStateZO);
            }
          }
          else{
            ucHelp = j;
            for(j = 0; j < cMaxLR; j++){
              if(pt2Pos[i] == aucHistoryWP[j]){
                aucHistoryWP[j] = aucHistoryWP[ucHelp];
                break;
              }
            }
            aucHistoryWP[ucHelp] = pt2Pos[i];
            if((ucWAState & cWAStateZO) == cWAStateZO){
              SetZOMWP(j, aucHistoryWP[j]);
              SetZOMWP(ucHelp, pt2Pos[i]);
              ucRet |= (uint8) (0x10 << pt2Pos[i]);
              ucRet |= (uint8) (0x10 << aucHistoryWP[j]);
            }
            else{
              ucRet |= (uint8) (1 << pt2Pos[i]);
            }
          }
        }
      }
    }
    if(ucRet > 0){
      PutWADataEE(cHistorySet1, (uint8 *) aulHistoryID, (uint8) sizeof(aulHistoryID));
      PutWADataEE(cHistoryWPSet1, aucHistoryWP, (uint8) sizeof(aucHistoryWP));
    }
    if((ucWAState & cWAStateZO) == 0){
      (void) WAInit((WAParNCfgType *) &ucLearnMode);
      ucRet = 0x0f;
    }
  }
  return ucRet;
}

uint8 ucGetHistoryState(void){
  uint8 i, ucRet = 0;
  if(aulHistoryID[0] > (uint32) 0){
    ucRet |= (cHiStateER | cHiStateZG);
    for(i = 0; i < cMaxLR; i++){
      if(aucHistoryWP[i] > cWheelPos_RR){
        ucRet &= ~cHiStateZG;
      }
    }
  }
  return ucRet;
}

uint8 ucGetERState(void){
  return( ((ucWAState & cWAStateER) == cWAStateER) ? (uint8) 1:(uint8) 0);
}

uint8 ucSumCtID(uint8 ucMinCt, uint16 *ushRet){
  uint8 i, ucCt= 0;
  *ushRet = 0;
  for( i = 0; i < cSumWE; i++){
    if(ucGetZomTelCtLearnBit(i) >= ucMinCt  ){
      ucCt++;
      *ushRet |= (uint16) (1 << i);
    }
  }
  return ucCt;
}

uint16 ushLearnID(tRFTelType * ptInputWA){
  uint16 ushRet;
  ucWAStateHi &= 0x0F;
   ucWAState &= 0x0F;
  ushRet = GETushWAState();

  if((uint8) 0 < ucPasSupplFilter(ptInputWA ) ){
    if(!(((ucWAState & cWAStateZO) == cWAStateZO) || ((ucWAStateHi & cTO) > (uint8) 0))){
      if((tWAPar.ucWACtrl & ucWACtrlFixc) > 0)
        (void) (ushLearnInOver8(ptInputWA ));
      else if(cCompleteLearn == ucLearnMode)
        (void) (ushCompLearn(ptInputWA ));
      else if(cSpeciaLearn == ucLearnMode )
        (void) (ushSpeciaLearn(ptInputWA));
      ProvideFPAlgo2MT_DAG();
    }
  }

  if((GETushWAState()) != ushRet){
    if((ucNrOfUKWPinHist () > 0) && ((ucWAState & 0xF0) > 0)){
      UpdateALState (cEvNewIDs);
    }
    if((ucNrOfUKWPinHist () == 0) && ((ucWAState & cWAStateZO ) > 0) && (((uint8) 2) > ucNrOfLocatError())){
         if((ucNrOfLocatErrorAndPosForce() == 0) || (tWAPar.AL_State != cAL_Stored)){
            UpdateALState (cEv4WPs);
         }
    }
  }
  ushRet = GETushWAState();
  return(ushRet);
}

uint8 ucWATO(void){
  uint8 ucRet = (uint8) 0;
  if((ucWAState & cWAStateZO) == 0){
    ucRet = ucGetMisOrNoLearnError ();
    ucRet |= ucGetAnyLocatErrors(ucRet);
  }
  if( (uint8) 0 == ucRet )
    ClearAlLearNLocatError(cAll);
  return ucRet;
}

uint8 WAInit(WAParNCfgType * p2ParNCfg){
  ucWAState &= (uint8) ~(cWAStateZO);
  ucWAState &= (uint8) ~(cWAStateER);
  ucWAState &= (uint8) ~(cWAStateActive);
  ucWAStateHi = (uint8) 0;
  SetWAStateZOChange(0);
  ushDriveTimeInSec = 0;
  ushDriveTimeOverPalMax = 0;
  ucLearnMode = p2ParNCfg ->ucWACfg ;
  ClearAlLearNLocatError(cAll);
  ClearZOM(cSumWE);
  GetWADataEE(cWAParameter, (uint8 *) &tWAPar , (uint8) sizeof(WAParameter));
  GetWADataEE(cHistorySet1, (uint8 *) aulHistoryID, (uint8) sizeof(aulHistoryID));
  GetWADataEE(cHistoryWPSet1, aucHistoryWP, (uint8) sizeof(aucHistoryWP));
  if(ucBadHist2Def() > 0)
    PutWADataEE(cHistorySet1, (uint8 *) aulHistoryID, (uint8) sizeof(aulHistoryID));
  if((cNoLearn == ucLearnMode) && (ucHistInConsist () > 0))
    ucLearnMode = cCompleteLearn ;
  if(cNoLearn == ucLearnMode){
    RestoreHistory();
  }
  tWAPar.ucWACtrl &= ~ucWACtrlBreakc;

     ucDAGLearnState = Autolearn_Learning ;

#ifdef FPA
  Very1stABSTickIinit();
#endif

  WAStatusChangedEvent(GETushWAState() );
  return ucGetHistoryState();
}

uint8 ucSetAutolocationOveride(uint8 ucPalOverideFlag){
  uint8 ucRetVal;
  if(ucPalOverideFlag==1){
    if((((ucGetHistoryState()&cHiStateZG) == cHiStateZG) == 1) && (cAL_OK == ui8GetALState())){
      ucRetVal=1;
      if(tWAPar.ucWACtrl != ucWACtrlFixc){
        tWAPar.ucWACtrl = ucWACtrlFixc;
        PutWADataEE(cWAParameter, (uint8 *) &tWAPar , (uint8) sizeof(WAParameter));
        ucRetVal=1;
      }
    }
    else{
      ucRetVal=0;
    }
  }
  else if  (ucPalOverideFlag==0){
    ucRetVal=1;
    if(tWAPar.ucWACtrl != ucDefWACtrl){
      tWAPar.ucWACtrl = ucDefWACtrl;
      PutWADataEE(cWAParameter, (uint8 *) &tWAPar , (uint8) sizeof(WAParameter));
    }
  }
  else{
    ucRetVal=0;
  }
  return ucRetVal;
}

uint8 ucReadAutolocationOverideFlag(void){
  uint8 ucRetVal;
  if(tWAPar.ucWACtrl == ucWACtrlFixc)
    ucRetVal = 1;
  else
    ucRetVal = 0;

  return ucRetVal;
}

uint8 ucSet1HistID(uint32 *pt2ID, uint8 *pt2Pos, uint8 ucIdx){
  uint8 i, ucRetVal;
  ucRetVal=0;
  for(i=0; i<cMaxLR; i++){
    if(i == ucIdx)
      continue;

    if( (pt2ID[0] == 0) || (pt2Pos[0] > cMaxLR ) ){
      ucRetVal =0;
      break;
    }

    if( (pt2ID[0] == aulHistoryID[i]) || ((pt2Pos[0] == aucHistoryWP[i] ) && (pt2Pos[0]!=cMaxLR) ) ){
      ucRetVal =0;
      break;
    }
  }
  if(i==cMaxLR){
    aulHistoryID[ucIdx] = pt2ID[0];
    aucHistoryWP[ucIdx] = pt2Pos[0];
    PutWADataEE(cHistorySet1, (uint8 *) aulHistoryID, (uint8) sizeof(aulHistoryID));
    PutWADataEE(cHistoryWPSet1, aucHistoryWP, (uint8) sizeof(aucHistoryWP));
    ucLearnMode = cCompleteLearn ;
     (void) WAInitByDiag((WAParNCfgType *) &ucLearnMode );
    ucRetVal = ((uint8) 0 == ucNrOfUKWPinHist ()) ? (uint8) 4:(uint8) 1;
  }

  return ucRetVal;
}

uint8 ucSet4HistIDs(uint32 *pt2ID, uint8 *pt2Pos){
  uint8 i, j, ucRetVal;
  ucRetVal=0;
  j=0;
  for(i=0; i<cMaxLR; i++){
    if( (pt2ID[i] == 0) || (pt2Pos[i] > cMaxLR ) ){
      ucRetVal =0;
      break;
    }
    for(j=0; j<cMaxLR; j++){
      if(i == j)
        continue;
       if( (pt2ID[i] == pt2ID[j]) || ((pt2Pos[i] == pt2Pos[j] ) && (pt2Pos[i]!=cMaxLR)) ){
        ucRetVal =0;
        i=cMaxLR;
        break;
      }
    }
  }
  if(j==cMaxLR){
    for(i=0; i<cMaxLR; i++){
      aulHistoryID[i] = pt2ID[i];
      aucHistoryWP[i] = pt2Pos[i];
    }
    PutWADataEE(cHistorySet1, (uint8 *) aulHistoryID, (uint8) sizeof(aulHistoryID));
    PutWADataEE(cHistoryWPSet1, aucHistoryWP, (uint8) sizeof(aucHistoryWP));
     ucLearnMode = cCompleteLearn ;
     (void) WAInitByDiag((WAParNCfgType *) &ucLearnMode );
    ucRetVal = ((uint8) 0 == ucNrOfUKWPinHist ()) ? (uint8) 4:(uint8) 1;
  }
  return ucRetVal;
}

#ifdef Test_LOG_ENABLE
uint8 ucGetZomStatus(uint8  ucIdx){
  if(ucIdx < cSumWE){
    return (tZOM[ucIdx].ucStatus);
  }
  else{
    return ((uint8) cNoWPos);
  }
}

uint8 ucGetZomToothTelCtCorrLearnBit(uint8  ucIdx){
  if(ucIdx < cSumWE){
    return (tZOM[ucIdx].ucToothTelCtCorrLearnBit);
  }
  else{
    return ((uint8) 0);
  }
}

uint8 ucGetZomTelCtLearnBit(uint8 ucIdx){
  if(ucIdx < cSumWE){
    return (tZOM[ucIdx].ucTelCtLearnBit);
  }
  else{
    return ((uint8) 0);
  }
}

uint8 ucGetZomToothTelCtCorrNoLearnBit(uint8  ucIdx){
  if(ucIdx < cSumWE){
    return (tZOM[ucIdx].ucToothTelCtCorrNoLearnBit);
  }
  else{
    return ((uint8) 0);
  }
}

uint8 ucGetZomToothTelCtrNoCorr(uint8  ucIdx){
  if(ucIdx < cSumWE){
    return (tZOM[ucIdx].ucToothTelCtNoCorr);
  }
  else{
    return ((uint8) 0);
  }
}

uint8 ucGetZomToothTelCtNoLearnMode(uint8  ucIdx){
  if(ucIdx < cSumWE){
    return (tZOM[ucIdx].ucToothTelCtNoLearnMode);
  }
  else{
    return ((uint8) 0);
  }
}

uint8 ucGetZomToothTelCt(uint8  ucIdx){
  if(ucIdx < cSumWE){
    return (tZOM[ucIdx].ucToothTelCt);
  }
  else{
    return ((uint8) 0);
  }
}

uint8 ucGetZomResetAbsRefFlag(uint8  ucIdx){
  if(ucIdx < cSumWE){
    return (tZOM[ucIdx].ucResetABSRefFlag);
  }
  else{
    return ((uint8) 0);
  }
}

uint8 ucGetZomDeltaMin(uint8  ucIdx){
  if(ucIdx < cSumWE){
    return (tZOM[ucIdx].ucDeltaMin);
  }
  else{
    return ((uint8) 0);
  }
}

uint8 *ucGetZomAbsComp(uint8  ucIdx){
  if(ucIdx < cSumWE){
    return (&tZOM[ucIdx].ucABSComp[0]);
  }
  else{
    return ((uint8*) 0);
  }
}

uint16 *ushGetZomAbsSums(uint8  ucIdx){
  if(ucIdx < cSumWE){
    return (&tZOM[ucIdx].ushRelCmpVal[0]);
  }
  else{
    return ((uint16*) 0);
  }
}
#endif

uint8 ucGetZomLqi(uint8  ucIdx){
  if(ucIdx < cSumWE){
    if( tZOM[ucIdx].ushLqi < 0xFF){
      return (uint8) tZOM[ucIdx].ushLqi;
    }
    else{
      return (uint8) 0xFF;
    }
  }
  else{
    return ((uint8) 0x00);
  }
}

void WATimer1sec(uint16 ushVSpeedInKmh){
  uint8 ucTmp;
  if(cV_MIN < ushVSpeedInKmh){
    if(cV_MAX_PAL < ushVSpeedInKmh )
      if( cTIME_OUT > ushDriveTimeOverPalMax  )
        ushDriveTimeOverPalMax++;

    if((uint8) 0 == (ucWAState & cWAStateZO)){
      if(cTIME_OUT > ushDriveTimeInSec  ){
        ushDriveTimeInSec ++;
        if(cSpeciaLearn == ucLearnMode )
          if(ucSL3MinHistPreFinish() > 0)
            WAStatusChangedEvent((uint16) ucWAState );
      }
      else if(0 == (ucWAStateHi & cTO)){
        ucWAStateHi |= cTO;
        ucTmp = ucWAState;
        TOXpired ();
        if(((ucTmp & (uint8) 0xF0) == (uint8) 0) && ((ucWAState & (uint8) 0xF0) > (uint8) 0))
          UpdateALState (cEvNewIDs );
        if((((uint8) 0 == ucNrOfLocatError()) && (cMaxLR  > ucNrOfUKWPinZOM())) || ((((uint8) 1 == ucNrOfLocatError() ) && ((uint8) 1 == ucNrOfUKWPinZOM())))){
               if((ucNrOfLocatErrorAndPosForce() == 0) || (tWAPar.AL_State != cAL_Stored)){
                  UpdateALState (cEv4WPs );
               }
            }
        else{
          if(!(((uint8) 0 == ucNrOfLocatError()) && ((uint8) 4 == ucNrOfLearnError()) )){
            UpdateALState (cEvALFailed );
          }
        }
      }
    }
  }
  UpdateDAGLearnState ();
}

uint8* pucGetLearnError(void){
  return ucLearnError ;
}

uint8* pucGetLocatError(void){
  return ucLocatError;
}

uint16 ushGetDriveTimeInSec(void){
  return ushDriveTimeInSec ;
}

static uint16 ushSpeciaLearn(tRFTelType * ptInputWA){
  uint16 ushHelp, ushHistID, ushNewID;
  uint8 ucCurID, ucIdentifiedWP = 0;
  ucCurID = ucPutInZOM(ptInputWA, &tWAPar);
  if( ucCurID < cSumWE){
    if((ucWAState & cWAStateActive) == 0)
      if( ucStartWA() == 1 )
        ucWAState |= cWAStateActive;

    (void) ucGetNrOfNewIDsInLM_SL (&ushNewID, (ucNoWheelSensorMounted() > 0) ? ucDefMinCt4ER+3:ucDefMinCt4ER );
    ushHistID = ushIDSetInHistNAlignWP(aulHistoryID,ucDefMinCt4HistER,cSumWE );
    if(ucAdjABSIface(ucCurID, ptInputWA) > (uint8) 0){
      BuildCmpVal (ucCurID);
    }
    ushHelp = ushHistID | ushNewID;
    if(cMaxLR == ucNrOfBitSet (ushHelp )){
      ucWAState |= cWAStateER;
      (void) ushAlignZOM (ushHelp);
      ucIdentifiedWP = ucGenDMnD2(10,4,0xFFFF);
      ushHistID = ushIDSetInHistNAlignWP(aulHistoryID,ucDefMinCt4HistER,cMaxLR );
      if((uint8) 0 ==  ucAssessDAGSLUC(ucNrOfBitSet ((uint16) ucIdentifiedWP))){
        if((uint8) 4 != ucNrOfBitSet(ushHistID)){
          ucWAState &= (uint8) ~cWAStateER;
        }
      }
    }
    if((uint8) 0 == (ucWAState & cWAStateZO ))
          (void) ucSL3MinHistPreFinish();
  }
  return(GETushWAState());
}

static uint8 ucAssessDAGSLUC(uint8 ucWPs){
  uint8 ucIDSlots,ucNewSensors, i,ucRet = 0;
  ucNewSensors = ucGetNrOfNewIDs(&ucIDSlots );
  if(0 == ucNewSensors ){
    ucRet = 1;
  }
  else if(cMaxLR == ucNewSensors){
     if((cHistIDProtectTime < ushDriveTimeInSec) && (cMaxLR == ucWPs))
       ucRet = 1;
   }
  else if(cMaxLR > ucNewSensors){
    if((c5MinDriveTimeInSec < ushDriveTimeInSec))
       if(ucNewZomIDsFit2MissingHistID_WP(ucIDSlots) > 0){
        ucRet = 1;
      }
  }
  for(i = 0; i < cMaxLR; i++){
    if((tZOM [i].ucStatus & 0x0F) == 0){
      ucRet = 0;
      break;
    }
  }
  if(ucRet > 0){
    ucRet = ucWrZom2History(ucIDSlots) ;
    ucWAState |= (cWAStateZO+cWAStateER);
    ucWAState &= 0x0F;
     ucWAState |= (ucRet&0xF0);
    ucWAStateHi &= 0x0F;
     ucWAStateHi |= ((ucRet&0x0F)<<4);
    ucRet = (uint8) 0xFF;
  }
  return ucRet;
}

static uint8 ucGetNrOfNewIDs(uint8* p2Slots){
  uint8 i,j,ucOldID = 0;
  *p2Slots = (uint8) 0xFF;
  for(i = 0; i < cMaxLR ; i++){
    for(j = 0; j < cMaxLR ; j++){
      if(tZOM [i].ulID == aulHistoryID [j]){
        ucOldID++;
        *p2Slots &= ~(1<<i);
        *p2Slots &= ~((uint8) 0x10<<j);
        break;
      }
    }
  }
  return ( (uint8) (cMaxLR-ucOldID) );
}

static uint8 ucNewZomIDsFit2MissingHistID_WP(uint8 ucNewNMissing){
  uint8 i,j, ucNewCt=0, ucMatchCt=0;
  for(i = 0; i < cMaxLR ; i++){
    if(((uint8) (1<<i) & ucNewNMissing ) > 0){
      ucNewCt++;
      for( j  = 0; j < cMaxLR; j++){
        if(((uint8) (0x10<<j) & ucNewNMissing ) > 0){
          if(ucGetZOMWP(i) == aucHistoryWP [j]){
            ucMatchCt ++;
            ucNewNMissing &= ~((uint8) (0x10<<j));
             break;
          }
        }
      }
      if(cMaxLR == j){
        for( j  = 0; j < cMaxLR; j++){
          if(cWheelPos_RR  < aucHistoryWP [j]){
            ucMatchCt ++;
            ucNewNMissing &= ~((uint8) (0x10<<j));
             break;
          }
        }
      }
    }
  }
  if( ucNewCt == ucMatchCt )
    return ((uint8) 1);
  else
    return ((uint8) 0);
}

static uint8 ucWrZom2History(uint8 ucNewNMissing){
  uint8 i,j,ucRet, ucNewCt = ucNrOfBitSet ((uint16) (ucNewNMissing & 0x0F));
  ucRet = 0;
  if(ucNrOfBitSet ((uint16) (ucNewNMissing & 0xF0)) == ucNewCt ){
    for( i = 0; i < cMaxLR ; i++){
      if((ucNewNMissing & (1<<i)) > 0){
        for( j = 0; j < cMaxLR; j++)
          if((ucNewNMissing & (0x10<<j)) > 0){
            ucNewNMissing &= ~(0x10<<j);
             aulHistoryID [j] = tZOM [i].ulID;
            if(aucHistoryWP [j] != ucGetZOMWP(i)){
              ucRet |= (0x11<<j);
              aucHistoryWP [j] = ucGetZOMWP(i);
            }
            else
              ucRet |= (0x10<<j);
            break;
          }
      }
      else{
         for( j = 0; j < cMaxLR; j++)
          if(tZOM [i].ulID == aulHistoryID [j]){
            if(ucGetZOMWP(i) == aucHistoryWP [j])
               break;
            else{
              aucHistoryWP [j] = ucGetZOMWP(i);
               ucRet |= (1<<j);
              break;
            }
          }
          }
    }
    if(ucHistInConsist() > 0){
       GetWADataEE(cHistorySet1, (uint8 *) aulHistoryID, (uint8) sizeof(aulHistoryID));
      GetWADataEE(cHistoryWPSet1, aucHistoryWP, (uint8) sizeof(aucHistoryWP));
      ucRet = 0;
    }
    else{
      PutWADataEE(cHistorySet1, (uint8 *) aulHistoryID, (uint8) sizeof(aulHistoryID));
       PutWADataEE(cHistoryWPSet1, aucHistoryWP, (uint8) sizeof(aucHistoryWP));
    }
  }
  else
     ucRet = 0;

  return ucRet;
}

uint8 ucHistInConsist(void){
  uint8 i,j, ucRet = 0xF0;
  for( i = 0; i < cMaxLR ; i++){
    if(aulHistoryID [i] < (uint32) 1){
      ucRet |= (0x01<<i);
    }
  }
  for( i = 0; i < cMaxLR ; i++){
    for( j = 0; j < cMaxLR ; j++){
      if( i != j){
        if(aulHistoryID [i] == aulHistoryID [j]){
          ucRet |= (1<<i);
          break;
        }
      }
    }
  }
  for( i = 0; i < cMaxLR ; i++){
    if(aucHistoryWP [i] < (cWheelPos_RR + 1)){
      ucRet &= ~(0x10<<aucHistoryWP [i]);
     }
  }
  return ucRet;
}

static uint8 ucSL3MinHistPreFinish(void){
  uint8 ucRet = 0;
  uint16 usHelp = 0;
  if( (uint8) 0 == (ucWAState & cWAStateZO)){
    if((uint8) 0 == ucHistInConsist ()){
      usHelp = ushIDSetInHist(aulHistoryID,3,cSumWE );
      if(ucNrOfBitSet (usHelp) == cMaxLR ){
        (void) ushAlignZOM(usHelp);
        ucWAState = (cWAStateZO+cWAStateER);
        RestoreHistory ();
        ucRet = (uint8) 1;
      }
    }
  }

  return ucRet;
}

static uint8 ucSL31Finish(uint8 ucMinCt4NewID){
  uint16 ushNewID = 0;
  if( (uint8) 0 == (ucWAState & cWAStateZO)){
    if( (uint8) 1 == ucGetNrOfNewIDsInLM_SL(&ushNewID,ucMinCt4NewID) ){
      if(0 < ui16NewIdFits(ushNewID, ushIDSetInHist(aulHistoryID,3,cSumWE ))){
        ucWAState |= cWAStateER;
        SetWAStateZOChange (ucSetHistory (cWAStateZO,0x0F));
        dblCk4LocEr ();
        if((uint8) 0 == ucNrOfUKWPinHist()){
          ucWAState |= cWAStateZO;
          ucWAStateHi |= cForcedZO ;
        }
        return ((uint8) 1);
      }
    }
  }
  return ( (uint8) 0);
}

static uint8 ucGetNrOfNewIDsInLM_SL(uint16 * p2Slots, uint8 ucMinCt){
  uint8 i,j,ucNewID = (uint8) 0;
  *p2Slots = 0;
  for(i = 0; i < cSumWE ; i++){
    if(tZOM [i].ucProbeCt  > 0){
      for(j = 0; j < cMaxLR ; j++){
        if(tZOM [i].ulID == aulHistoryID [j]){
          break;
        }
      }
      if( cMaxLR == j ){
        if(tZOM[i].ucTelCtLearnBit > ucMinCt){
          tZOM[i].ucStatus |= cZOMStatER;
          ucNewID++;
          *p2Slots |= 1<<i;
        }
      }
    }
    else
      break;
   }
  return ucNewID;
}

static uint8 ucGetNrOfNewIDsInLM(uint16 * p2Slots, uint8 ucMinCt){
  uint8 i,j,ucNewID = (uint8) 0;
  *p2Slots = 0;
  for(i = 0; i < cSumWE ; i++){
    if(tZOM [i].ucProbeCt  > 0){
      for(j = 0; j < cMaxLR ; j++){
        if(tZOM [i].ulID == aulHistoryID [j]){
          break;
        }
      }
      if( cMaxLR == j ){
        if(ucMinCt < tZOM[i].ucTelCtLearnBit){
          if(ucDefMinCt4ER <= ucMinCt){
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
  return ucNewID;
}

static uint8 ucFinishViaHistory(void){
  uint16 ushHelp = ushIDSetInHist(aulHistoryID,ucDefMinCt4HistER,cSumWE);
  if(cMaxLR == ucNrOfBitSet(ushHelp)){
    if((ucGetERState() < 1) || (0x000F != ushHelp )){
      (void) ushAlignZOM(ushHelp);
      ucWAState |= cWAStateER;
    }
    (void) ucGenDMnD2(10,4,0xFFFF);
    if( (ucNrOfUKWPinZOM () > ucNrOfUKWPinHist ()) && !( 1 == ucNrOfUKWPinZOM ())){
      ucWAState &= (uint8) ~cWAStateZO;
     }
    else{
      SetWAStateZOChange (ucSetHistory (cWAStateZO,0x0F));
      if((uint8) 0 == ucNrOfUKWPinHist()){
        ucWAState |= cWAStateZO;
        if( 1 == ucNrOfUKWPinZOM ())
          ucWAStateHi |= cForcedZO ;
      }
    }
    return ((uint8) 1);
  }
  else
    return ((uint8) 0);
}

static uint8 ucBadHist2Def(void){
  uint8 i, ucBadIDCt = (uint8) 0;
  for(i = 0; i < cMaxLR; i++){
    if( aulHistoryID[i] < 1UL ){
      aulHistoryID[i] = (uint32) i + 1;
      ucBadIDCt++;
    }
  }
  return ucBadIDCt;
}

static uint8 uc3NewIDsAllocated(uint8 ucMinCt4NewID){
  uint16 ushHistSet = 0, ushNewID = 0;
  if( (uint8) 0 == (ucWAState & cWAStateZO)){
    ushHistSet = ushIDSetInHist(aulHistoryID,3,cSumWE );
    if(ucNrOfBitSet (ushHistSet) == 0 ){
      if( (uint8) 3 == ucGetNrOfNewIDsInLM_SL(&ushNewID,ucMinCt4NewID)){
        ushNewID = ushAlignZOM(ushNewID );
        if((uint8) 3 == ucNrOfBitSet((uint16) ucGenDMnD2(10,4,ushNewID))){
           SetWAStateZOChange (ucSetHistory (cWAStateZO,(uint8) ushNewID));
          return ((uint8) 1);
        }
      }
    }
  }
  return ( (uint8) 0);
}

static uint16 ushCompLearn(tRFTelType * ptInputWA){
  uint8 ucCurID;
  uint16 ushHelp;
  if( (tWAPar.ucWACtrl & ucWACtrlBreakc) == 0){
    ucCurID = ucPutInZOM(ptInputWA, &tWAPar);
    if( ucCurID < cSumWE){
      if((ucWAState & cWAStateActive) == 0)
        if( ucStartWA() == 1 )
          ucWAState |= cWAStateActive;

      if(  ucGetERState() == 0 ){
        ushHelp = ushWhlSetRdy2Freeze ((ucNoWheelSensorMounted() > 0) ? ucDefMinCt4ER+3:ucDefMinCt4ER, ucDefMinCt4HistER, (ushDriveTimeInSec > cHistIDProtectTime ) ? (uint8) 1:(uint8) 0);     /* get all ERs */
        if( ushHelp > 0){
          ucWAState |= cWAStateER;
          (void) ushAlignZOM(ushHelp);
          ucCurID = ucGetZOMPosOfID( &ptInputWA->AK35def.ulID);
        }

        if((ucCheckWheelPos(ucCurID, ptInputWA ) == 1) && (ucGetERState()==1)){
          SetWAStateZOChange(ucSetHistory((uint8)cWAStateZO, 0x0F));
          ucWAState |= cWAStateZO;
        }
        else if( ucGetERState()==1 ){
          SetWAStateZOChange(ucSetHistory((uint8)cWAStateER, 0x0F));
        }
      }
      else{
        if(ucCheckWheelPos(ucCurID,ptInputWA ) == 1){
          SetWAStateZOChange(ucSetHistory((uint8)cWAStateZO, 0x0F));
          ucWAState |= cWAStateZO;
        }
      }
    }
    else{
    }
  }
  return GETushWAState();
}

static uint16 ushWhlSetRdy2Freeze(uint8 ucMinCt, uint8 ucMinCt4HistERc, uint8 bLearnNewIDsFlag){
  uint8 ucNewCt,ucOldCt, ucOtherCt;
  uint16 ushNew, ushOld, ushOther, ushRet = 0;
  ushOld = ushIDinLearnModeSetInHist(aulHistoryID,ucMinCt4HistERc,cSumWE);
  ushOld |= ushSetHistIDs2ER (aulHistoryID,ucDefMinCt4HistER,cSumWE);
  ucOldCt = ucNrOfBitSet(ushOld);
  ucNewCt = ucGetNrOfNewIDsInLM (&ushNew,ucMinCt );
  ucOtherCt = ucGetNrOfNewIDsInLM (&ushOther,(uint8) 4 );
  ucOtherCt -= ucNewCt;
  ushOther &= ((uint16) ~ushNew);

  if(cMaxLR == ucOldCt)
     ushRet = ushOld;
  else if((cMaxLR == ucNewCt) && (0 == ucOldCt) && bLearnNewIDsFlag && ( 0 == ucOtherCt ))
      ushRet = ushNew;
  else if((cMaxLR == (ucNewCt + ucOldCt)) && bLearnNewIDsFlag && ( 0 == ucOtherCt ))
    ushRet = (ushNew|ushOld);

  return ushRet;
}

static uint8 ucForceAutoLocate(void){
  uint8 i,j, ucUK, ucUnusedWP;
  ucUnusedWP = 0x0F;
  ucUK = 0;

  if(ui8AnyHistIdMissing () == ((uint8) 0)){
     for(i = 0; i < cMaxLR; i++){
        if( aucHistoryWP[i] > cWheelPos_RR  ){
           ucUK |= (uint8) (0x10<<i);
        }
        else{
           ucUnusedWP &= (uint8) ~(1<<aucHistoryWP [i]);
        }
     }
     if(ucNrOfBitSet ((uint16) ucUK) == (uint8) 1){
        for(i = 0; i < cMaxLR; i++){
           if((ucUK & (0x10<<i)) > 0){
              for(j = 0; j < cMaxLR ; j++){
                 if( (ucUnusedWP & (1<<j)) > 0 ){
                    aucHistoryWP [i] = j;
                    ucWAStateHi |= cForcedZO ;
                    j = cMaxLR;
                  }
              }
           }
        }
     }
     else{
        ucUK = (uint8) 0;
     }
  }
  return ucUK;
}

static uint8 ucCmpHist2ZOMID(uint8 ucVZS){
  uint8 i,j, ucRet = (uint8) 0x0F;
  for(i = 0; i < cMaxLR; i++){
    for(j = 0; j < cMaxLR; j++){
      if((aulHistoryID [i] == tZOM[j].ulID) && (((ucVZS & (uint8) (1<<j)) > 0))){
        ucRet &= (uint8) ~(1<<i);
        break;
      }
    }
  }
  return ucRet;
}

static uint8 ucNrOfUKWPinZOM(void){
  uint8 i, ucRet = 0;
  for( i = 0; i < cMaxLR ; i++){
    if((uint8) 0 == (tZOM[i].ucStatus & 0x0F)){
      ucRet++;
    }
  }
  return ucRet;
}

static uint8 ucNrOfUKWPinHist(void){
  uint8 i, ucRet = 0;
  for( i = 0; i < cMaxLR ; i++){
    if((uint8) cWheelPos_RR  < aucHistoryWP [i]){
      ucRet++;
    }
  }
  return ucRet;
}

static uint8 ucFinalFreeze(uint8 ucMinCt4HistER, uint8 ucMinCt){
  uint8 ucIdentifiedWP;
  uint16 ushNew;
  uint16 ushOld;
//  uint16 ushFRS;
  if((uint8) 0 == ucFinishViaHistory()){
    (void) ucGetNrOfNewIDsInLM(&ushNew,ucMinCt);
    ushOld = ushIDSetInHist(aulHistoryID,ucDefMinCt4HistER,cSumWE);
    if((cMaxLR < ucNrOfBitSet (ushNew|ushOld)) && (((uint8) 0) == ucGetERState())){
      ushNew = ushReduceCorel24(ushNew|ushOld);
      ushOld = 0;
      ushNew = ushAlignZOM(ushNew);
      if(cMaxLR == ucNrOfBitSet (ushNew))
        ucWAState |= cWAStateER;
      if((uint8) 0 == ucNrOfUKWPinZOM ())
        ucWAState |=  cWAStateZO;
      SetWAStateZOChange (ucSetHistory (cWAStateZO,(uint8) ushNew));
      dblCk4LocEr ();
    }
    else{
      if( ucNrOfBitSet (ushNew|ushOld) < cMaxLR ){
          ushNew = ushLqiTribute(ushNew);
       }
      ucIdentifiedWP = ucGenDMnD2(10,4,(ushOld|ushNew));
      ushOld = ushIDSetInHist(aulHistoryID,ucDefMinCt4HistER,cSumWE);
       ushNew = 0;
      (void) ucGetNrOfNewIDsInLM (&ushNew,ucMinCt );
      ushNew &= ((uint16) ucIdentifiedWP);
      ushOld |= (uint16) ucIdentifiedWP ;
      if(ucNrOfBitSet (ushOld) > cMaxLR ){
        SetWAStateZOChange (ucSetHistory (cWAStateZO,ucIdentifiedWP));
         dblCk4LocEr( );
      }
      else{
        ushNew |= ushOld;
        ushNew = ushAlignZOM(ushNew);
        if(ucNrOfBitSet (ushNew) > cMaxLR){
          SetWAStateZOChange (ucSetHistory (cWAStateZO,(uint8)ushOld));
           dblCk4LocEr ();
        }
        else if(0 < ushNew ){
          SetWAStateZOChange (ucSetHistory (cWAStateZO,(uint8) ushNew));
          dblCk4LocEr ();
        }
        else
          return ((uint8) 0);
      }
    }
  }
  ucIdentifiedWP = ((uint8) 4 - ucNrOfUKWPinHist());
  if(cMaxLR == ucIdentifiedWP){
    ucWAStateHi &= (uint8) ~cTZG;
  }
  else if((uint8) 0 == ucIdentifiedWP ){
    ucWAStateHi &= (uint8) ~cTZG;
  }
  else{
    ucWAState &= (uint8) ~cWAStateZO;
    ucWAStateHi |= cTZG;
  }
   UNUSED(ucMinCt4HistER);
  return((uint8)1);
}

static void UpdateALState(uint8 ui8Trigger){
  uint8 ui8ALState = tWAPar.AL_State;
  switch (ui8ALState){
  case cAL_OK:
    if(cEvALFailed == ui8Trigger)
      tWAPar.AL_State = cAL_Stored;
    else if( cEvNewIDs == ui8Trigger)
      tWAPar.AL_State = cAL_Unknown;
    break;
  case cAL_Stored:
    if(cEv4WPs == ui8Trigger)
      tWAPar.AL_State = cAL_OK;
    else if( cEvNewIDs == ui8Trigger)
      tWAPar.AL_State = cAL_Unknown;
    break;
  case cAL_Unknown:
    if(cEv4WPs == ui8Trigger)
      tWAPar.AL_State = cAL_OK;
    else if(( cEvALFailed == ui8Trigger))
       tWAPar.AL_State = cAL_Error;
    break;
  case cAL_Error:
    if(cEv4WPs == ui8Trigger)
      tWAPar.AL_State = cAL_OK;
    else if( cEvNewIDs == ui8Trigger)
      tWAPar.AL_State = cAL_Unknown;
    break;
  default:
    if((uint8) 0 == ucNrOfUKWPinHist())
      tWAPar.AL_State = cAL_Stored;
    else
      tWAPar.AL_State = cAL_Unknown;
    break;
  }

  if(ui8ALState != tWAPar.AL_State)
    PutWADataEE(cWAParameter, (uint8 *) &tWAPar , (uint8) sizeof(WAParameter));
}

uint8 ui8GetALState(void){
  return (tWAPar.AL_State);
}

uint8 ucGetLearnMode(void){
  return ucLearnMode ;
}

static uint16 ucFindNoLearnHistoryIDs(uint32 *ptHistID, uint8 ucMinProbeCt, uint8 ucSlots2Search){
  uint8 j, ucRet = (uint8) 0xFF;
  for( j = 0; j < ucSlots2Search; j++){
    if((*ptHistID == ulGetZOMID(j)) && (ucGetZomTelCtLearnBit(j) >= ucMinProbeCt )){
      ucRet = (uint8) 0;
      break;
    }
    else{
      if(ulGetZOMID(j) == (uint32) 0){
        break;
      }
    }
  }
  return ucRet;
}

static uint16 ucFindMissingHistoryIDs(uint32 *ptHistID, uint8 ucMinProbeCt, uint8 ucSlots2Search){
  uint8 j, ucRet = (uint8) 0xFF;
  for( j = 0; j < ucSlots2Search; j++){
    if((*ptHistID == ulGetZOMID(j)) && (ucGetProbeCt(j) >= ucMinProbeCt )){
      ucRet = (uint8) 0;
      break;
    }
    else{
      if(ulGetZOMID(j) == (uint32) 0){
        break;
      }
    }
  }
  return ucRet;
}

static uint8 ucGetMisOrNoLearnError(void){
  uint8 i, ucRet = (uint8) 0;
  for(i = 0; i < cMaxLR ; i++){
    if(ucFindMissingHistoryIDs(&aulHistoryID[i],ucDefMinCt4HistER, cSumWE ) > ((uint8) 0) ){
      ucLearnError [i] = SensorMissin ;
      ucRet |= (1<<i);
    }
    else if(ucFindNoLearnHistoryIDs (&aulHistoryID[i] ,ucDefMinCt4HistER , cSumWE ) > ((uint8) 0) ){
      ucLearnError [i] = NoLearnSensor ;
      ucRet |= (1<<i);
    }
    else{
      ucLearnError [i] = NoError ;
    }
  }
  return ucRet;
}

static uint8 ucGetAnyLocatErrors(uint8 ucDontTouch){
  uint8 i, ucRet = 0;
  for( i = 0; i < cMaxLR ; i++){
    if( ucGetLocatError(i) != NoError ){
      ucRet |= (1<<i);
    }
  }
   if(ABSignalMissin == ucABSignalMissin){
    for( i = 0; i < cMaxLR ; i++){
      if( ucGetLocatError(i) != NoError ){
        PutLocatError( ABSignalMissin, i);
      }
    }
    return ucRet;
  }
   if((ushDriveTimeInSec >> 1) < ushDriveTimeOverPalMax ){
    for( i = 0; i < cMaxLR ; i++){
      if( ucGetLocatError(i) != NoError ){
        PutLocatError( BadSpeed, i);
      }
    }
  }
   UNUSED(ucDontTouch);
  return ucRet;
}

void ClearAlLearNLocatError(uint8 ucErrType){
  uint8 i;
  for( i = 0; i < cMaxLR ; i++){
    if(cAll == ucErrType ){
      ucLocatError [i] = NoError ;
    }
    ucLearnError [i] = NoError ;
  }
  ucABSignalMissin = NoError ;
}

void PutLocatError(uint8 ucTipicoDiErrori, uint8 ucZomSlot){
  uint8 i;
  if( cSumWE > ucZomSlot){
    for( i = 0; i < cMaxLR ;i++){
      if(ulGetZOMID (ucZomSlot) == ulGetID(i)){
        if(AssegnazioneCostretto != ucLocatError [i]){
          if((AmbigWP == ucTipicoDiErrori) && (tZOM [ucZomSlot].ucToothTelCt <= cMinCt4Dec ))
            ucTipicoDiErrori = TooFewPalTels;
          ucLocatError [i] = ucTipicoDiErrori;
          break;
        }
      }
    }
  }
  return;
}

uint8 ucGetLocatError(uint8 ucZomSlot){
  uint8 i;
  if( cSumWE > ucZomSlot){
    for( i = 0; i < cMaxLR ;i++){
      if(ulGetZOMID (ucZomSlot) == ulGetID(i)){
        return (ucLocatError [i]);
      }
    }
  }
  return NoError;
}

static uint8 ucNrOfLocatError(void){
  uint8 i, ucRet;
  ucRet = (uint8) 0;
  for( i = 0; i < cMaxLR ; i++){
    if(( NoError != ucLocatError [i]) && ( AssegnazioneCostretto != ucLocatError[i])){
      ucRet++;
    }
  }
  return ucRet;
}

static uint8 ucNrOfLocatErrorAndPosForce(void){
  uint8 i, ucRet;
  ucRet = (uint8) 0;
  for( i = 0; i < cMaxLR ; i++){
    if(( NoError != ucLocatError [i]) && ( AssegnazioneCostretto == ucLocatError[i])){
      ucRet++;
    }
  }
  return ucRet;
}

static uint8 ucNrOfLearnError(void){
  uint8 i, ucRet;
  ucRet = (uint8) 0;
  for( i = 0; i < cMaxLR ; i++){
    if( ucLearnError [i] != NoError ){
      ucRet++;
    }
  }
  return ucRet;
}

static void TOXpired(void){
  if((uint8) 0 == (ucWAState & cWAStateZO)){
    if(cCompleteLearn == ucLearnMode ){
      if((uint8) 0 < ucFinalFreeze(ucDefMinCt4HistER, (ucNoWheelSensorMounted() > 0) ? ucDefMinCt4ER+3:ucDefMinCt4ER))
         WAStatusChangedEvent(GETushWAState() );
    }
    else if(cSpeciaLearn == ucLearnMode ){
      if( 0 == ucSL31Finish ((ucNoWheelSensorMounted() > 0) ? ucDefMinCt4ER+3:ucDefMinCt4ER)){
        if(uc3NewIDsAllocated((ucNoWheelSensorMounted() > 0) ? ucDefMinCt4ER+3:ucDefMinCt4ER) > 0){
          ucWAStateHi |= cTZG ;
        }
        else{
          (void) ucFinishViaHistory ();
          dblCk4LocEr ();
        }
      }
    }
    if((ucWAState & cWAStateZO) == 0){
      (void) considerationeDiAssegnazioneCostretto();
    }
    if((ucWAState & cWAStateZO) == 0){
      if(ucWATO() > 0){
        ucWAStateHi |= cErrorActive ;
        WAStatusChangedEvent(GETushWAState() );
      }
    }
    else{
      if(!(ucWAStateHi & cForcedZO)){
        ClearAlLearNLocatError (cAll );
      }
      else{
        ucWAStateHi |= cErrorActive ;
            (void) ucGetAnyLocatErrors(0);
      }
      WAStatusChangedEvent(GETushWAState() );
    }
  }
}

uint8 ui8GetDAGAutoLearnState(void){
  return ucDAGLearnState;
}

static void UpdateDAGLearnState(void){
  uint8 i, ucMissin = 0;
  if(Autolearn_Learning == ucDAGLearnState){
    if(ucGetERState() > 0){
      ucDAGLearnState = Autolearn_OK ;
    }
    else if((ucWAStateHi & cErrorActive) > 0){
      for(i = 0; i < cMaxLR ; i++){
        if( SensorMissin == ucLearnError [i] ){
          ucMissin++;
        }
      }
      switch(ucMissin){
      case 1:        ucDAGLearnState = Timeout_3_Sensors;        break;
      case 2:        ucDAGLearnState = Timeout_2_Sensors;        break;
      case 3:        ucDAGLearnState = Timeout_1_Sensor;        break;
      case 4:        ucDAGLearnState = Timeout_No_Sensors;        break;
      default:        ucDAGLearnState = Autolearn_OK;        break;
      }
    }
  }
}

void PutABSErrorActive(void){
  if(bGetABSSignalDTCActive() == TRUE){
    ucABSignalMissin = ABSignalMissin ;
  }
}

static uint8 ucTakeOverHistWP(uint8 ucHistIx,uint8 ucZomIx){
  if(ucHistIx < cMaxLR ){
    if(ucZomIx < cSumWE ){
      if((aulHistoryID[ucHistIx] == ulGetZOMID(ucZomIx)) && ((uint8) 4 > aucHistoryWP [ucHistIx])){
        SetZOMWP(ucZomIx,aucHistoryWP[ucHistIx]);
        tZOM[ucZomIx].ucStatus |= cZOMStatHistER;
        return ((uint8) 0xFF);
      }
      else{
        return ((uint8) 0);
      }
    }
    else{
      return ((uint8) 0);
    }
  }
  else{
    return ((uint8) 0);
  }
}

static uint16 ushIDSetInHistNAlignWP(uint32 *ptHistSet, uint8 ucMinProbeCt, uint8 ucSlots2Search){
  uint8 i,j;
  uint16 ushRet = 0;
  for( i = 0; i < cMaxLR; i++){
    if(ptHistSet[i] == (uint32) 0){
      ushRet = 0;
      break;
    }
    else{
      for( j = 0; j < ucSlots2Search; j++){
        if((ptHistSet[i] == ulGetZOMID(j)) && (ucGetProbeCt(j) >= ucMinProbeCt )){
          ushRet |= (1<<j);
          if((uint8) 0 == (tZOM[j].ucStatus & (uint8) 0x0F)){
            if((uint8) 0 == ucTakeOverHistWP(i,j)){
               tZOM[j].ucStatus |= cZOMStatHistER;
            }
            else{
              PutLocatError (AssegnazioneCostretto ,j);
            }
          }
          break;
        }
        else{
          if(ulGetZOMID(j) == (uint32) 0){
            break;
          }
        }
      }
    }
  }
  return ushRet;
}

static uint16 ushSetHistIDs2ER(uint32 *ptHistSet, uint8 ucMinProbeCt, uint8 ucSlots2Search){
  uint8 i,j;
  uint16 ushRet = 0;
  for( i = 0; i < cMaxLR; i++){
    if(ptHistSet[i] == (uint32) 0){
      ushRet = 0;
      break;
    }
    else{
      for( j = 0; j < ucSlots2Search; j++){
        if((ptHistSet[i] == ulGetZOMID(j)) && (ucGetProbeCt(j) >= ucMinProbeCt ) ){
          ushRet |= (1<<j);
          tZOM[j].ucStatus |= cZOMStatHistER;
          break;
        }
        else{
          if(ulGetZOMID(j) == (uint32) 0){
            break;
          }
        }
      }
    }
  }
  return ushRet;
}

static uint16 ushLearnInOver8(tRFTelType * ptInputWA){
  uint8 ucCurID;
  uint16 ushHelp;
  ucCurID = ucPutInZOM(ptInputWA, &tWAPar);
  if( ucCurID < cSumWE){
    if((ucWAState & cWAStateActive) == 0)
      if( ucStartWA() == 1 )
        ucWAState |= cWAStateActive;
    if(  ucGetERState() == 0 ){
      ushHelp = ushWhlSetRdy2Freeze ((ucNoWheelSensorMounted() > 0) ? ucDefMinCt4ER+3:ucDefMinCt4ER, ucDefMinCt4HistER, (ushDriveTimeInSec > cHistIDProtectTime ) ? (uint8) 1:(uint8) 0);     /* get all ERs */
      if( ushHelp > 0){
        ucWAState |= cWAStateER;
        (void) ushAlignZOM(ushHelp);
        ucCurID = ucGetZOMPosOfID( &ptInputWA->AK35def.ulID);
        SetWAStateZOChange(ucSetHistory((uint8)cWAStateER, 0x0F));
        if( ucWACtrlFixc == tWAPar.ucWACtrl ){
            RestoreHistory ();
        }
      }
    }
  }
  else{
  }
  return GETushWAState();
}

static uint8 ucPasSupplFilter(tRFTelType * p2Tel){
  uint8 i;
  const uint8 aucLearnType[] = {cTelTypeSELPAL, cTelTypeSELPAL1, cTelTypeAK35def, cTelTypeAK35defLMA, cTelTypeAK35defLF };
  uint8 ucRet = (uint8) 0;

    for( i = ((uint8) 0); i < sizeof(aucLearnType);  i++){
      if(aucLearnType[i] == p2Tel->AK35def .ucCmdID ){
        ucRet = (uint8) 0xFF;
        break;
      }
    }

  return ucRet;
}

static void MergeWPandPWP(void){
  uint8 i;
  for(i = (uint8) 0; i < cMaxLR ;i++){
    if(aucHistoryWP [i] > cWheelPos_RR  ){
      aucWPorPWP[i] = USEui8PWPofHistCol (i);
    }
    else{
      aucWPorPWP[i] = aucHistoryWP[i];
    }
  }
}

uint8* GETpucStartAdrWPorPWP(void){
  MergeWPandPWP ();
  return aucWPorPWP;
}

uint8 GETucWPorPWPofHistCol(uint8 ucCol){
  if(ucCol < cMaxLR){
    MergeWPandPWP();
    return aucWPorPWP[ucCol];
  }
  else{
    return cMaxLR;
  }
}

uint16 GETushWAState(void){
  return ((uint16) (ucWAStateHi << 8) + (uint16) ucWAState);
}

uint8 WAInitByDiag(WAParNCfgType * p2ParNCfg){
  ucWAState &= (uint8) ~(cWAStateZO);
  ucWAState &= (uint8) ~(cWAStateER);
  ucWAState &= (uint8) ~(cWAStateActive);
  ucWAStateHi = (uint8) 0;
  SetWAStateZOChange(0);
  ushDriveTimeInSec = 0;
  ushDriveTimeOverPalMax = 0;
  ucLearnMode = p2ParNCfg ->ucWACfg ;
  ClearAlLearNLocatError(cAll);
  ClearZOM(cSumWE);
  GetWADataEE(cWAParameter, (uint8 *) &tWAPar , (uint8) sizeof(WAParameter));
  if((ucHistInConsist () > (uint8) 0) && ((cAL_OK == tWAPar.AL_State ) || (cAL_Stored == tWAPar.AL_State) || (cAL_Error == tWAPar.AL_State))){
    tWAPar.AL_State = cAL_Unknown ;
    PutWADataEE(cWAParameter, (uint8 *) &tWAPar , (uint8) sizeof(WAParameter));
  }
  else if(((uint8) 0) == ucHistInConsist ()){
    tWAPar.AL_State = cAL_OK ;
    PutWADataEE(cWAParameter, (uint8 *) &tWAPar , (uint8) sizeof(WAParameter));
  }
  ucDAGLearnState = Autolearn_Learning ;
  Very1stABSTickIinit();
  WAStatusChangedEvent(GETushWAState() );
  return ucGetHistoryState();
}

static uint8 considerationeDiAssegnazioneCostretto(void){
  uint8 ui8ChangeWPSlot = ucForceAutoLocate ();
  if((uint8) 1 == ucNrOfBitSet ((uint16) ui8ChangeWPSlot )){
    ucWAStateHi |= ui8ChangeWPSlot;
    PutWADataEE(cHistoryWPSet1, aucHistoryWP, (uint8) sizeof(aucHistoryWP));
       return (ui8ChangeWPSlot);
  }
  return((uint8) 0);
}

static void dblCk4LocEr(void){
  uint8 i;
  uint16 zomSlot2Chk;
  zomSlot2Chk = ushIDSetInHist(aulHistoryID,ucDefMinCt4HistER,cSumWE);
  for( i = (uint8) 0; i < cSumWE ; i++){
    if((zomSlot2Chk & (1<<i)) > 0){
      if(((uint8) 0) == (tZOM[i].ucStatus & 0x0F)){
        if(NoError == ucGetLocatError (i)){
          PutLocatError ( (cMinCt4Dec < tZOM[i].ucToothTelCt) ? AmbigWP:TooFewPalTels , i);
        }
      }
      else{
        PutLocatError ( NoError, i);
      }
      zomSlot2Chk &= ~(1<<i);
    }
    if(zomSlot2Chk < 1 )
      i = cSumWE;
   }
}

static uint16 ui16NewIdFits(uint16 ushNewID, uint16 ushHistSet){
  uint8 ui8Tmp,i,ui8NewSlot = (uint8) 0,ui8NeWP = (uint8) 0;
  uint16 ui16Ret = 0;
  if((ucNrOfBitSet (ushHistSet) == 3 ) && (ucNrOfBitSet (ushNewID) == 1 )){
    for( i = 0; i < cSumWE ; i++){
      if((ushNewID & (1<<i)) > 0){
        ui8NeWP =  ucGetZOMWP (i);
        ui8NewSlot = i;
        break;
      }
    }
    if(cWheelPos_RR < ui8NeWP){
      if(GETuCorWPofSlot(ui8NewSlot , &ui8NeWP , &ui8Tmp) > 0){
         for( i = 0; i < cSumWE ; i++)
           if(( i != ui8NewSlot ) && ((ushHistSet & (1<<i)) > 0) )
            if((tZOM[i].ucStatus & 0x0F) == ui8NeWP)
              break;
      }
      else{
        i = cSumWE;
      }
    }
    else{
      for( i = 0; i < cSumWE ; i++)
         if(( i != ui8NewSlot ) && ((ushHistSet & (1<<i)) > 0) )
          if(ucGetZOMWP (i) == ui8NeWP)
            break;
    }

    if(cSumWE == i){
      if(((uint8) 0 == tZOM[ui8NewSlot].ucToothTelCt ) && ((uint8) 0 == tZOM[ui8NewSlot].ucToothTelCtNoCorr )){
        i = (uint8) 0;
      }
    }
    if(cSumWE == i){
      ui16Ret = 1;
    }
  }
  return ui16Ret;
}

static uint8 ui8AnyHistIdMissing(void){
   uint8 i;
   for(i = 0; i < cMaxLR ; i++){
      if(ucFindMissingHistoryIDs(&aulHistoryID[i],ucDefMinCt4HistER, cSumWE ) > ((uint8) 0) ){
         return ((uint8) 0xFF);
      }
   }
   return ((uint8) 0);
}

static uint16  ushLqiTribute(uint16 ushCandidate){
  uint8 i;
  for(i = 0; i < cSumWE; i++){
    if(((1 << i) & ushCandidate) > 0){
      if(ucGetZomLqi(i) <= ucDAG_LQIParameter()){
        ushCandidate &= (uint16)(~(1 << i));
      }
    }
  }
  return ushCandidate;
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

