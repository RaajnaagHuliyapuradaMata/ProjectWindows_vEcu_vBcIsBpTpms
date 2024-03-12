/******************************************************************************/
/* File              : SwcApplTpmsWarnHandler.c                               */
/* Author            : Nagaraja HULIYAPURADA MATA                             */
/* Copyright (c)2024 : All rights reserved.                                   */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "Std_Types.hpp"

#include "infCtrl.hpp"
#include "infWTDHW.hpp"
#include "infRteSwcApplTpmsWarnHandler.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define cMaiden       0x00
#define cInitialized  0x01
#define cInitSingleId 0x03
#define cNoWrnLvl     ((uint8) 0xFF)

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
struct Cmp{
   uint8 ucPMin;
   uint8 ucDAGHard;
   uint8 ucDAGSoft;
   uint8 ucDAGDHW;
   uint8 ucDAGResetSoft;
};

static union U{
   struct Cmp tWrnLvl;
   uint8      ucByte[(uint8) sizeof(struct Cmp)];
}tU;

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/
const uint8 ucBitNoc[ucSumWEc] = {1, 2, 4, 8};

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
static uint8 aucWarnBitsWN[5];

static uint8 ui8DAGWrnLvl[4][5] = {
      {cNoWrnLvl, cNoWrnLvl, cNoWrnLvl, cNoWrnLvl, cNoWrnLvl}
   ,  {cNoWrnLvl, cNoWrnLvl, cNoWrnLvl, cNoWrnLvl, cNoWrnLvl}
   ,  {cNoWrnLvl, cNoWrnLvl, cNoWrnLvl, cNoWrnLvl, cNoWrnLvl}
   ,  {cNoWrnLvl, cNoWrnLvl, cNoWrnLvl, cNoWrnLvl, cNoWrnLvl}
};

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
static void  ConvDAG_FPL2HW     (void);
static uint8 ui8GetWrnLvlDHW    (void);
static uint8 ui8GetWrnLvlSoft   (void);
static uint8 ui8GetWrnLvlHard   (void);
static uint8 ui8GetWrnLvlPMin   (void);
static uint8 ui8GetResetLvlSoft (void);
static void  InitWN             (uint8 ucInit, uint8 ucIdX);
static void  ClearX8BitWM       (uint8*, uint8);
static void  SetX8BitWM         (uint8*, uint8);
static uint8 bGetX8BitWM        (const uint8*, uint8);
static uint8 ucGenWNVector      (const uint8* ptData);
static uint8 ucUSWDiagService   (uint8* ptData);
static uint8 ui8GenAllPWP       (uint8* p2PWP);
static void  UpdateDAGWrnLvl    (uint8 uiColOfId);

uint8 ucSetWarnBitWN(uint8 ucIdX, uint8 ucWarnTypeIx){
   if((ucWarnTypeIx < ucMaxWarnTypeWNc) && (ucIdX < ucSumWEc)){
      if(ucWarnTypeIx == ucSFactorIxc){
         (void)ucStartFilterSTWT(tDAG_PPara.ui16_T_SOFT);
      }
      else if(ucWarnTypeIx == ucEcEIxc){
         (void)ucStartFilterHDWT(tDAG_PPara.ui16_T_HARD);
      }
      if(bGetX8BitWM(&aucWarnBitsWN[ucWarnTypeIx], ucIdX) == 0){
         SetX8BitWM(&aucWarnBitsWN[ucWarnTypeIx], ucIdX);
         PutDataEE(ucWarnTypeArrayIdWNc, aucWarnBitsWN, ucMaxWarnTypeWNc);
      }
      return((uint8) 1);
   }
   else{
      return((uint8) 0xff);
   }
}

void ClearWarnBitWN(uint8 ucIdX, uint8 ucWarnTypeIx){
   if((ucWarnTypeIx < ucMaxWarnTypeWNc) && (ucIdX < ucSumWEc)){
      ClearX8BitWM(&aucWarnBitsWN[ucWarnTypeIx], ucIdX);
      if(
            (ucSFactorIxc == ucWarnTypeIx)
         && (((uint8) 0) == aucWarnBitsWN[ucSFactorIxc])
      ){
         StopFilterSTWT();
      }
      else if(
            (ucEcEIxc == ucWarnTypeIx)
         && (((uint8) 0) == aucWarnBitsWN[ucEcEIxc])
      ){
         StopFilterHDWT();
      }
      PutDataEE(ucWarnTypeArrayIdWNc, aucWarnBitsWN, ucMaxWarnTypeWNc);
   }
   return;
}

uint8 ucGetWarnBitWN(uint8 ucIdX, uint8 ucWarnTypeIx){
   if((ucWarnTypeIx < ucMaxWarnTypeWNc) && (ucIdX < ucSumWEc)){return(bGetX8BitWM(&aucWarnBitsWN[ucWarnTypeIx], ucIdX));}
   else                                                       {return((uint8) 0xff);}
}

uint8 ucGetWarnType(uint8 ucWarnTypeIx){
  if((ucWarnTypeIx < ucMaxWarnTypeWNc)){return(aucWarnBitsWN[ucWarnTypeIx]);}
  else                                 {return((uint8) 0);}
}

static uint8 bGetX8BitWM(const uint8* ptByte, uint8 ucBitNo){
  if((*ptByte & ucBitNoc[ucBitNo]) == ucBitNoc[ucBitNo]){return(1);}
  else                                                  {return(0);}
}

static void ClearX8BitWM(uint8* ptByte, uint8 ucBitNo){
   if((*ptByte & ucBitNoc[ucBitNo]) > 0){
      *ptByte &= (uint8) ~ucBitNoc[ucBitNo];
   }
}

static void SetX8BitWM(uint8* ptByte, uint8 ucBitNo){
   if((*ptByte & ucBitNoc[ucBitNo]) == 0){
      *ptByte |= ucBitNoc[ucBitNo];
   }
}

uint8 ucPfT(uint16 ushM, uint16 ushTabs){
   uint32 ulHelp;
   uint16 ushHelp;
   ulHelp = (uint32)ushM * 10;
   ulHelp *=  ushTabs;
   ulHelp /= ushGSFc;
   ulHelp += 5;
   ushHelp = (uint16) (ulHelp / 10);
   ushHelp = (ushHelp > Getui8AtmosphericP()) ? (ushHelp - Getui8AtmosphericP()):ushHelp;
   if(ushHelp > 0x00FF){
      ushHelp = 0x00FF;
   }
   return((uint8) ushHelp);
}

uint16 ushMIso(uint8 ucP, sint8 scT){
   uint32 ulHelp;
   uint16 ushHelp;
   if(ucP == 0){
      ushHelp = 0;
   }
   else{
      ulHelp  = (uint32) ushGSFc *10;
      ulHelp *=  ucP;
      ushHelp = (uint16) scT + ush273Kelvinc;
      ulHelp  = ulHelp / ((uint32) ushHelp);
      ulHelp += 5;
      ushHelp = (uint16) (ulHelp/10);
   }
   return(ushHelp);
}

uint16 ui16MIsoRel(uint8 ucPrel, sint8 scT){
   uint32 ulHelp;
   uint16 ushHelp;
   uint16 pAbs = ucPrel + Getui8AtmosphericP ();
   if(0 == pAbs){
      ushHelp = 0;
   }
   else{
      ulHelp = (uint32) ushGSFc *10;
      ulHelp *=  pAbs ;
      ushHelp = (uint16) scT + ush273Kelvinc;
      ulHelp = ulHelp / ((uint32) ushHelp);
      ulHelp += 5;
      ushHelp = (uint16) (ulHelp/10);
   }
   return(ushHelp);
}

static void InitWN(uint8 ucInit, uint8 ucIdX){
   uint8 i, j;
   switch(ucInit){
      case (uint16) cMaiden:
         for(i = 0; i < ucMaxWarnTypeWNc; i++){
            for(j = 0; j < ucSumWEc; j++){
               ClearWarnBitWN(j, i);
               if(i == ucDHWIxc){
                  ResetM1Pressure(j);
               }
            }
         }
         break;

      case (uint16) cInitialized:
         break;

      case (uint16) cInitSingleId:
         if(ucIdX <= ucSumWEc){
            if(ucIdX == ucSumWEc){
               for(i = 0; i < ucMaxWarnTypeWNc; i++){
                  for(j = 0; j < ucSumWEc; j++){
                     ClearWarnBitWN(j, i);
                     if(i == ucDHWIxc){
                        ResetM1Pressure(j);
                     }
                  }
               }
            }
            else{
               for(i = 0; i < ucMaxWarnTypeWNc; i++){
                  ClearWarnBitWN(ucIdX, i);
                  if(i == ucDHWIxc){
                     ResetM1Pressure(ucIdX);
                  }
               }
            }
         }
         else{
         }
         break;

      default:
         break;
   }
}

static uint8 ucUSWDiagService(uint8* ptData){
   uint8 i, k, ucRet;
   ucRet = 0;
   switch(*ptData){
      case (uint16) ucResetWarnVectorc:
         ptData++;
         InitWN(cInitSingleId, *ptData);
         ucRet = 0;
         break;

      case (uint16) ucGetWarnVectorsc:
         for(k = 0; k < ucSumWEc; k++){
            ptData[k] = 0;
            for(i = 0; i < ucMaxWarnTypeWNc; i++){
               ptData[k] |= (uint8) (ucGetWarnBitWN(k,i) << i);
            }
         }
         ucRet = 0;
         break;

      case (uint16) ucGetWarnTypec:
         ptData[2] = aucWarnBitsWN[ptData[1]];
         ucRet = 0;
         break;

      default:
         break;
   }
   return (ucRet);
}

static uint8 ucGenWNVector(const uint8* ptData){
   uint8(*const fpt2WnType[])(struct LocalWarnDat*, uint8) = cAllWT_function;
   struct LocalWarnDat tLWD;
   uint8 i, ucRet = 0;
   tLWD.tHFD.tHF.ucId = 0;
   tLWD.ucCurWarnLevel = cNoWrnLvl ;
   tLWD.ucResetLvl = cNoWrnLvl ;
   for(i = 0; i < (uint8) sizeof(struct HFTelIntern); i++){
      tLWD.tHFD.ucByte[i] = *ptData;
      ptData++;
   }
   if(tLWD.tHFD.tHF.ucId < ucSumWEc){
      PuT(tLWD.tHFD.tHF.ucId, tLWD.tHFD.tHF.scTWE);
      GetRatValOfId(tLWD.tHFD.tHF.ucId, (struct SollDat*) &tLWD.tSD);
      tLWD.PRefMin = Getui8PrefMinOfId(tLWD.tHFD.tHF.ucId);
      for(i = 0; i < ucMaxWarnTypeWNc;i++){
         if(fpt2WnType[i](&tLWD, (uint8) 0) > 0){
            ucRet |= (uint8) (0x01 << i);
         }
         else{
            ucRet &= (uint8) ~(0x01 << i);
         }
         tU.ucByte[i] = tLWD.ucCurWarnLevel;
         if(bSoftFactor == fpt2WnType[i])
            tU.tWrnLvl.ucDAGResetSoft = tLWD.ucResetLvl;
      }
      UpdateDAGWrnLvl(tLWD.tHFD.tHF.ucId);
   }
   return(ucRet);
}

uint8 ucWarnManagerWN(uint8 ucAction, uint8 *ptData){
   uint8 ucRet;
   switch(ucAction){
      case (uint16) ucPorInitc:
         InitWN((uint8) cInitialized, (uint8) 0xFF);
         GetDataEE(ucWarnTypeArrayIdWNc, aucWarnBitsWN, ucMaxWarnTypeWNc);
         ConvDAG_FPL2HW ();
         ucRet = (uint8) 0;
         break;

      case (uint16) ucComparec :
         ucRet = ucGenWNVector(ptData);
         break;

      case (uint16) ucDiagServicec:
         ucRet = ucUSWDiagService(ptData);
         break;

      default:
         ucRet = 0xFF;
         break;
   }
   return(ucRet);
}

static uint8 ui8GetWrnLvlDHW    (void){return tU.tWrnLvl .ucDAGDHW;}
static uint8 ui8GetWrnLvlSoft   (void){return tU.tWrnLvl .ucDAGSoft;}
static uint8 ui8GetWrnLvlHard   (void){return tU.tWrnLvl .ucDAGHard;}
static uint8 ui8GetWrnLvlPMin   (void){return tU.tWrnLvl .ucPMin;}
static uint8 ui8GetResetLvlSoft (void){return tU.tWrnLvl .ucDAGResetSoft;}

static void ConvDAG_FPL2HW(void){
   uint8 i;
   aucWarnBitsWN [ucEcEIxc]  |= aucWarnBitsWN [ucDHWIxc];
   aucWarnBitsWN [ucPMinIxc] |= aucWarnBitsWN [ucDHWIxc];
   for(i = (uint8) 0; i < 4; i++){
      if((aucWarnBitsWN[ucDHWIxc] & ((uint8) (1<<i))) > (uint8) 0){
         ResetM1Pressure (i);
      }
   }
   aucWarnBitsWN [ucDHWIxc] = 0;
}

uint8 ui8GetPRelComp2Tref(sint8 i8Tcur, uint8 ui8Ix){
   uint8 ui8Pcomp;
   struct SollDat tRatVal;
   GetRatValOfId (ui8Ix, &tRatVal);
   tRatVal.ushMSoll = ui16MIsoRel (tRatVal.ucPSoll , tRatVal.scTSoll);
   ui8Pcomp = ucPfT(tRatVal.ushMSoll,(uint16) i8Tcur + ush273Kelvinc);
   return(ui8Pcomp);
}

sint8 i8GetTref(uint8 ui8Ix){
   struct SollDat tRatVal;
   GetRatValOfId(ui8Ix, &tRatVal);
   return(tRatVal.scTSoll);
}

uint8 ui8GetPRefRel(uint8 ui8Ix){
   struct SollDat tRatVal;
   GetRatValOfId (ui8Ix, &tRatVal);
   return(tRatVal.ucPSoll);
}

void USWPostInit(void){
   ConvDAG_FPL2HW();
   PutDataEE(ucWarnTypeArrayIdWNc, aucWarnBitsWN, ucMaxWarnTypeWNc);
}

uint8 ui8GenPWP(uint8* p2PWP){
   uint8 i, ui8PWP[4];
   if(cMaxLR == ui8GenAllPWP(ui8PWP)){
      for(i = 0; i < cMaxLR; i++){
         p2PWP[i] = ui8PWP[i];
      }
      return(1);
   }
   else{
      return(0);
   }
}

static uint8 ui8GenAllPWP(uint8* p2PWP){
   uint8 i, j, ui8PoSeq[4],ui8SortedCol[cMaxLR], ui8WPinUse = (uint8) 0, ui8PWPCt = (uint8) 0, ui8AlloCol = (uint8) 0;
   for(i = 0; i < cMaxLR; i++){
      if(*(pui8GetLastM1Pressure() + i) < (uint8) 1){
         return(0);
      }
   }
   for(i = 0; i < cMaxLR; i++){
      if(ucGetWPOfCol(i) < cMaxLR){
         p2PWP[i] = ucGetWPOfCol (i);
         ui8WPinUse |= ((uint8) (1<<ucGetWPOfCol (i)));
         ui8AlloCol |= ((uint8) (1 << i));
         ui8PWPCt++;
      }
   }
   if(cMaxLR > ui8PWPCt){
      SortBiggest1st(pui8GetLastM1Pressure(),ui8SortedCol,cMaxLR);
      if(ui8GetPMIN_F() <= ui8GetPMIN_R()){
         ui8PoSeq[0] = (uint8) 2;
         ui8PoSeq[1] = (uint8) 3;
         ui8PoSeq[2] = (uint8) 1;
         ui8PoSeq[3] = (uint8) 0;
      }
      else{
         ui8PoSeq[0] = (uint8) 0;
         ui8PoSeq[1] = (uint8) 1;
         ui8PoSeq[2] = (uint8) 3;
         ui8PoSeq[3] = (uint8) 2;
      }
      for(i = 0; i < cMaxLR; i++){
         if((ui8AlloCol & ((uint8) 1<<ui8SortedCol [i])) > 0)
            continue;
         else{
            for(j = 0; j < cMaxLR; j++){
               if((uint8) 0 == (ui8WPinUse & (1<<ui8PoSeq[j]))){
                  ui8WPinUse |= ((uint8) (1<<ui8PoSeq[j]));
                  ui8PWPCt++;
                  p2PWP [ui8SortedCol [i]] = ui8PoSeq[j];
                  break;
               }
            }
         }
      }
   }
   return(ui8PWPCt);
}

void DelWarnOfId(uint8 ui8HistColOfID){
   uint8 i, aucDiagService[2];
   aucDiagService[0] = ucResetWarnVectorc;
   if(ui8HistColOfID < (uint8)4){
      aucDiagService[1] = ui8HistColOfID;
      (void) ucWarnManagerWN(ucDiagServicec, aucDiagService);
   }
   else{
      for(i = 0; i < 4; i++){
         aucDiagService[1] = i;
         (void) ucWarnManagerWN(ucDiagServicec, aucDiagService);
      }
   }
   UpdateWarnOut((const uint8*) GETpucStartAdrWPorPWP());
}

void GETDAGWrnLvlOfIdCol(uint8 ui8ColOfId, uint8* p2WrnLvls){
   if(cMaxLR > ui8ColOfId){
      p2WrnLvls[0] = ui8DAGWrnLvl [ui8ColOfId ][0];
      p2WrnLvls[1] = ui8DAGWrnLvl [ui8ColOfId ][1];
      p2WrnLvls[2] = ui8DAGWrnLvl [ui8ColOfId ][2];
      p2WrnLvls[3] = ui8DAGWrnLvl [ui8ColOfId ][3];
   }
   else{
      p2WrnLvls[0] = cNoWrnLvl;
      p2WrnLvls[1] = cNoWrnLvl;
      p2WrnLvls[2] = cNoWrnLvl;
      p2WrnLvls[3] = cNoWrnLvl;
   }
}

static void UpdateDAGWrnLvl(uint8 ui8ColOfId){
   if(cMaxLR > ui8ColOfId){
      ui8DAGWrnLvl [ui8ColOfId ][0]  = ui8GetWrnLvlPMin();
      ui8DAGWrnLvl [ui8ColOfId ][1]  = ui8GetWrnLvlDHW();
      ui8DAGWrnLvl [ui8ColOfId ][2]  = ui8GetWrnLvlHard();
      ui8DAGWrnLvl [ui8ColOfId ][3]  = ui8GetWrnLvlSoft();
      ui8DAGWrnLvl [ui8ColOfId ][4]  = ui8GetResetLvlSoft();
   }
}

uint8 ui8GETDAGClrWrnThresOfIdCol(uint8 ui8ColOfId){return(ui8DAGWrnLvl[ui8ColOfId][4]);}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/
