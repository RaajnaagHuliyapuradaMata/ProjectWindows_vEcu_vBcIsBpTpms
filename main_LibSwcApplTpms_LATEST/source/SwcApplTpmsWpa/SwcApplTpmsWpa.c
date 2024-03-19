/******************************************************************************/
/* File              : SwcApplTpmsWpa.c                                       */
/* Author            : Nagaraja HULIYAPURADA MATA                             */
/* Copyright (c)2024 : All rights reserved.                                   */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "Std_Types.hpp"

#include "Rte_CtApHufTPMSwpa.h"

#include "WallocX.h"
#include "CD_Decoder_X.h"
#include  "WatcfX.h"
#include "internal_clockX.h"
#include "Walloc.h"
#include "USWarnX.h"
#include "state_bzX.h"
#include "state_fdX.h"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define Off (0U)
#define On (1U)

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
static uint16 ushLinABStick[4] = {0, 0, 0, 0};
static uint8  ui8WrWANVMBlock;
tRFTelType inputWA;
uint16 ushV;
uint16 ushSysTime;
boolean bIsAutoLocated;

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
static void AlignWallocRam2Nvm(void);

void  StartWallocTOAlarm (uint8 ucTimeInSec);
void  StopWallocTOAlarm  (void);
void  GetVehicleSpeed    (uint16* ushVtmp);
void  PUTtWAparam        (uint8 x, uint8 i);
void  PUTucWAHistID      (uint8 x, uint8 i);
void  PUTucWAHistWP      (uint8 x, uint8 i);
uint8 GETtWAparam        (uint8 i);
uint8 GETucWAHistID      (uint8 i);
uint8 GETucWAHistWP      (uint8 i);

#define RTE_START_SEC_CTAPHUFTPMSWPA_APPL_CODE
#include "MemMap.h"

FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetHistID_Operation(UInt8 ucCol, P2VAR(UInt32, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ulID){
 *ulID=ulGetID(ucCol);
 return;
}

FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetHistWPOfCol_Operation(UInt8 ucCol, P2VAR(UInt8, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ucWP){
 *ucWP = ucGetWPOfCol(ucCol);
 return;
}

FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetHistWPOfID_Operation(UInt32 ulID, P2VAR(UInt8, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ucZomPos){
 uint8 ucTemp;
 ucTemp = ucGetColOfID(&ulID);
 *ucZomPos = ucGetWPOfCol(ucTemp); 
 return;
}

FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetRecHistIDs_Operation(P2VAR(UInt8, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ucRecHistID){
 *ucRecHistID = bCheckHistIDReception();
 return;
}

FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetWaTOErrorCode_Operation(P2VAR(UInt8, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ucWaToErr, UInt8 ucColOfID){
 if(ucColOfID < cMaxLR){
     *ucWaToErr = pucGetLearnError()[ucColOfID];
 }
 else{
   ucWaToErr = 0x00;
 }
 return;
}

FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomAbsCompFL_Operation(UInt8 ucIdx, P2VAR(UInt8, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ucAbsCompStick){
   uint8* ptTemp8 = ucGetZomAbsComp(ucIdx);
   if(ptTemp8 != (void *)0) *ucAbsCompStick = ptTemp8[0];
   else                     *ucAbsCompStick = 96;
   return;
}

FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomAbsCompFR_Operation(UInt8 ucIdx, P2VAR(UInt8, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ucAbsCompStick){
   uint8* ptTemp8 = ucGetZomAbsComp(ucIdx);
   if(ptTemp8 != (void *)0) *ucAbsCompStick = ptTemp8[1];
   else                     *ucAbsCompStick = 96;
   return;
}

FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomAbsCompRL_Operation(UInt8 ucIdx, P2VAR(UInt8, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ucAbsCompStick){
   uint8* ptTemp8 = ucGetZomAbsComp(ucIdx);
   if(ptTemp8 != (void *)0) *ucAbsCompStick = ptTemp8[2];
   else                     *ucAbsCompStick = 96;
   return;
}

FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomAbsCompRR_Operation(UInt8 ucIdx, P2VAR(UInt8, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ucAbsCompStick){
   uint8* ptTemp8 = ucGetZomAbsComp(ucIdx);
   if(ptTemp8 != (void *)0) *ucAbsCompStick=ptTemp8[3];
   else                     *ucAbsCompStick= 96;
   return;
}

FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomAbsLinFL_Operation(UInt8 ucIdx, P2VAR(UInt16, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ushAbsLinStick){
   *ushAbsLinStick = ushLinABStick[0];
   UNUSED(ucIdx);
   return;
}

FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomAbsLinFR_Operation(UInt8 ucIdx, P2VAR(UInt16, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ushAbsLinStick){
   *ushAbsLinStick = ushLinABStick[1];
   UNUSED(ucIdx);
   return;
}

FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomAbsLinRL_Operation(UInt8 ucIdx, P2VAR(UInt16, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ushAbsLinStick){
   *ushAbsLinStick = ushLinABStick[2];
   UNUSED(ucIdx);
   return;
}

FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomAbsLinRR_Operation(UInt8 ucIdx, P2VAR(UInt16, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ushAbsLinStick){
   *ushAbsLinStick = ushLinABStick[3];
   UNUSED(ucIdx);
   return;
}

FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomAbsSumCorrFL_Operation(UInt8 ucIdx, P2VAR(UInt16, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ushAbsSumCorr){
   uint16* ptTemp16 = ushGetZomAbsSums(ucIdx);
   if(ptTemp16 != (void *)0) *ushAbsSumCorr = ptTemp16[0];
   else                      *ushAbsSumCorr = 0x00;
   return;
}

FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomAbsSumCorrFR_Operation(UInt8 ucIdx, P2VAR(UInt16, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ushAbsSumCorr){
   uint16* ptTemp16 = ushGetZomAbsSums(ucIdx);
   if(ptTemp16 != (void *)0) *ushAbsSumCorr = ptTemp16[1];
   else                      *ushAbsSumCorr = 0x00;
   return;
}

FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomAbsSumCorrRL_Operation(UInt8 ucIdx, P2VAR(UInt16, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ushAbsSumCorr){
   uint16* ptTemp16 = ushGetZomAbsSums(ucIdx);
   if(ptTemp16 != (void *)0) *ushAbsSumCorr = ptTemp16[2];
   else                      *ushAbsSumCorr = 0x00;
   return;
}

FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomAbsSumCorrRR_Operation(UInt8 ucIdx, P2VAR(UInt16, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ushAbsSumCorr){
   uint16* ptTemp16 = ushGetZomAbsSums(ucIdx);
   if(ptTemp16 != (void *)0) *ushAbsSumCorr = ptTemp16[3];
   else                      *ushAbsSumCorr = 0x00;
   return;
}

FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomID_Operation(UInt8 ucIdx, P2VAR(UInt32, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ucZomID){
   *ucZomID = ulGetZOMID(ucIdx);
   return;
}

FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomPosOfID_Operation(UInt32 ulID, P2VAR(UInt8, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ucPos){
   *ucPos = ucGetZOMPosOfID(&ulID);
   return;
}

FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomStatisticTelCtr_Opetation(UInt8 ucIdx, P2VAR(UInt8, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ucRetVal){
   *ucRetVal = ucGetZomToothTelCt(ucIdx);
   return;
}

FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomStatus_Operation(UInt8 ucIdx, P2VAR(UInt8, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ucZomStatus){
   *ucZomStatus = ucGetZomStatus(ucIdx);
   return;
}

FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomToothTelCtCorrLearnBit_Opetation(UInt8 ucIdx, P2VAR(UInt8, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ucRetVal){
   *ucRetVal = ucGetZomToothTelCtCorrLearnBit(ucIdx);
   return;
}

FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomToothTelCtCorrNoLearnBit_Opetation(UInt8 ucIdx, P2VAR(UInt8, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ucRetVal){
   *ucRetVal = ucGetZomToothTelCtCorrNoLearnBit(ucIdx);
   return;
}

FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomToothTelCtCorrNoLearnMode_Opetation(UInt8 ucIdx, P2VAR(UInt8, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ucRetVal){
   *ucRetVal = ucGetZomToothTelCtNoLearnMode(ucIdx);
   return;
}

FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_GetZomToothTelCtNoCorr_Opetation(UInt8 ucIdx, P2VAR(UInt8, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_VAR) ucRetVal){
   *ucRetVal = ucGetZomToothTelCtrNoCorr(ucIdx);
   return;
}

FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_Init(void){
   uint8 i;
   WAParNCfgType ucParkingState; 
   ushV = 0;
   bIsAutoLocated = FALSE;
   for(i=0;i<sizeof(inputWA);i++){
      *((uint8*)&inputWA + i) = 0;
   }
   ui8WrWANVMBlock = (uint8) 0;
   InternTimersInit();
   ucParkingState.ucWACfg = 3;
   WAInit(&ucParkingState);
}

#include "infWTDHW.hpp"
FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_ReceiveData2Alloc_Operation(P2CONST(DT_tData2Alloc, AUTOMATIC, RTE_CTAPHUFTPMSWPA_APPL_DATA) tData2Alloc){
   DT_ushWAState ucWAState;
   uint8 i;
   inputWA.AK35def.ulID = (uint32)(tData2Alloc->ulID);
   inputWA.Header.ucTType = (uint8)(tData2Alloc->ucTelType);
   inputWA.SchraderFP.ucPAL = (uint8)tData2Alloc->ucPalData;
   inputWA.SchraderFP.ushStatusField = (uint16)(tData2Alloc->ucFrameCounter<<8);
   ushSysTime = (uint16)tData2Alloc->ushTimeStamp;
   ushLinABStick[0] = tData2Alloc->ushAbsStickFL;
   ushLinABStick[1] = tData2Alloc->ushAbsStickFR;
   ushLinABStick[2] = tData2Alloc->ushAbsStickRL;
   ushLinABStick[3] = tData2Alloc->ushAbsStickRR;
   ucWAState = (DT_ushWAState)ushLearnID(&inputWA );
   if(((ucWAState & cWAStateZO) == cWAStateZO) && (bIsAutoLocated == FALSE ) ){
      bIsAutoLocated = TRUE;
   }
   if((ucWAState & cWAIDChanged) > 0){
      for(i = 0; i < cMaxLR ; i++){
         if((((uint8) 0x10 << i) & ucWAState ) > 0){
            ResetM1Pressure(i);
         }
      }
   }
   Rte_Write_PP_WAState_DE_ushWAState(ucWAState);
}

FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_ReceiveEnvData(void){
	DT_tEnvData tTmpEnvData;
	Rte_Read_PP_EnvData_DE_tEnvData(&tTmpEnvData);
	ushV = tTmpEnvData.ushVehSpeed;   
}

FUNC(void, RTE_CTAPHUFTPMSWPA_APPL_CODE) RCtApHufTPMSwpa_TimerWA(void){
   WATimer1sec(ushV);
   AlignWallocRam2Nvm();
}
#define RTE_STOP_SEC_CTAPHUFTPMSWPA_APPL_CODE
#include "MemMap.h"

void GetVehicleSpeed(uint16* ushVtmp){
	*ushVtmp = ushV;
}

void PUTtWAparam(uint8 x, uint8 i){
  if(i<sizeof(DT_aucWAParam)){
    *( (uint8*)&Rte_Pim_Pim_tWallocNvMBlock()->aucWAHistParam + i)= (x);
  }
}

uint8 GETtWAparam(uint8 i){
  if(i<sizeof(DT_aucWAParam)){
    return( *( (uint8*)&Rte_Pim_Pim_tWallocNvMBlock()->aucWAHistParam + i) );
  }
  else{
    return 0x00;
  }
}

uint8 GETucWAHistID(uint8 i){
  if(i<sizeof(DT_aulWAHistID)){
    return( *( (uint8*)&Rte_Pim_Pim_tWallocNvMBlock()->aulWAHistID + i ) );
  }
  else{
    return 0x00;
  }
}

void PUTucWAHistID(uint8 x, uint8 i){
  if(i<sizeof(DT_aulWAHistID)){
    *( (uint8*)&Rte_Pim_Pim_tWallocNvMBlock()->aulWAHistID + i) = (x);
  }
}

uint8 GETucWAHistWP(uint8 i){
  if(i<sizeof(DT_aucWAHistWP)){
    return( *((uint8*)&Rte_Pim_Pim_tWallocNvMBlock()->aucWAHistWP  + i) );
  }
  else{
    return 0x00;
  }
}

void PUTucWAHistWP(uint8 x, uint8 i){
  if(i<sizeof(DT_aucWAHistWP)){
    *((uint8*)&Rte_Pim_Pim_tWallocNvMBlock()->aucWAHistWP + i) = (x);
  }
}

void PUTaucPWPofHistCol(uint8 ui8HistCol, uint8 ui8Val){
  if(cMaxLR > ui8HistCol){
    if(*((uint8*)&Rte_Pim_Pim_tWallocNvMBlock()->aucWAHistProvWP  + ui8HistCol) != ui8Val){
      *((uint8*)&Rte_Pim_Pim_tWallocNvMBlock()->aucWAHistProvWP + ui8HistCol) = ui8Val;
      SetWaData2NvmFlag();
    }
  }
}

uint8 GETui8PWPofHistCol(uint8 ui8HistCol){
  if(cMaxLR > ui8HistCol){
    return(*((uint8*)&Rte_Pim_Pim_tWallocNvMBlock()->aucWAHistProvWP + ui8HistCol));
  }
  else{
    return((uint8) 0xFF);
  }
}

void PUTucWAHistSensorState(uint8 ui8Val){
    if(*((uint8*)&Rte_Pim_Pim_tWallocNvMBlock()->ucWAHistSensorState ) != ui8Val){
      *((uint8*)&Rte_Pim_Pim_tWallocNvMBlock()->ucWAHistSensorState ) = ui8Val;
      SetWaData2NvmFlag();
    }
}

uint8 GETucWAHistSensorState(void){
  return(*((uint8*)&Rte_Pim_Pim_tWallocNvMBlock()->ucWAHistSensorState  ));
}

#ifndef FD_CONTROLS_FALLBACK
void ClearPWP(void){
  uint8 i;
  for( i = 0; i < cMaxLR ; i++){
     PUTaucPWPofHistCol(i,4);
  }
}

void Check4PWP(void){
  uint8 i,ui8PWP[4];
  uint16 ui16WAState;
  if(  ui8PWPresent () < 1  ){
    if(ui8GenPWP(ui8PWP) > 0){
      for( i = 0; i < cMaxLR ; i++){
        PUTaucPWPofHistCol(i,ui8PWP[i]);
      }
      ui16WAState = GETushWAState();
      if(0x0200 == (ui16WAState & 0x0204)){
        ui16WAState &= 0x0F0F;
        WAStatusChangedEvent( ui16WAState );
      }
    }
  }
}
#else
 uint8 ui8GetPPWP(uint8 * p2P, uint8 * p2PWP, uint8 ui8MinRefPF, uint8 ui8MinRefPR){
   uint8 i,j, ui8PoSeq[4],ui8SortedCol[cMaxLR], ui8WPinUse = (uint8) 0, ui8PWPCt = (uint8) 0, ui8AlloCol = (uint8) 0;
   for( i = 0; i < cMaxLR ; i++ ){
     if(ucGetWPOfCol (i) < cMaxLR){
       p2PWP[i] = ucGetWPOfCol (i);
       ui8WPinUse |= ((uint8) (1<<ucGetWPOfCol (i)));
       ui8AlloCol |= ((uint8) (1 << i));
       ui8PWPCt++;
     }
   }
   if(cMaxLR > ui8PWPCt){
     SortBiggest1st (p2P,ui8SortedCol,cMaxLR);
     if(ui8MinRefPF <= ui8MinRefPR ){
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
     for( i = 0; i < cMaxLR ; i++){
       if((ui8AlloCol & ((uint8) 1<<ui8SortedCol [i])) > 0)
         continue;
       else{
         for(j = 0; j < cMaxLR ; j++){
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
   return(ui8PWPCt );
 }

void Wr4PWP2NVM(uint8 * p24PWP){
  uint8 i;
  uint16 ui16WAState;
  for( i = 0; i < cMaxLR ; i++){
    PUTaucPWPofHistCol(i,p24PWP[i]);
  }
  ui16WAState = GETushWAState();
  if(0x0200 == (ui16WAState & 0x0204)){
    ui16WAState &= 0x0F0F;
    WAStatusChangedEvent( ui16WAState );
  }

}
#endif

uint8 ui8PWPresent(void){
  uint8 i;
  for( i = 0; i < cMaxLR ; i++){
     if(cMaxLR <= GETui8PWPofHistCol(i)){
       break;
     }
  }
  if( cMaxLR == i ) {
    return(1u);
  }
  else{
    return(0u);
  }
}

uint8 USEui8PWPofHistCol(uint8 ui8HistCol){
    if( ( cAL_Error == ui8GetALState ()) && ((uint8) 0 < ui8PWPresent ()) ){
      return(GETui8PWPofHistCol(ui8HistCol));
    }
    else{
      return(cMaxLR);
    }
}

uint8 ui8CheckNWrPWP(uint8 ui8HistCol, uint8 ui8WP){
  uint8 i;
  for(i = 0; i < cMaxLR; i++){
    if((ui8WP == GETui8PWPofHistCol(i)) && (i != ui8HistCol)){
      break;
    }
  }
  if(cMaxLR == i){
    PUTaucPWPofHistCol(ui8HistCol , ui8WP);
    return((uint8) 1);
  }
  else{
    return((uint8) 0);
  }
}

 uint8 Getui8ColPWPActive(void){
   if(cAL_Error == ui8GetALState ()){
     if(ui8PWPresent() > ((uint8) 0)){
       return((uint8) 0x0F );
     }
     else{
       return((uint8) 0);
     }
   }
   else{
     return((uint8) 0);
   }
}

void StartWallocTOAlarm(uint8 ucTimeInSec){UNUSED(ucTimeInSec);}
void StopWallocTOAlarm(){}

static void AlignWallocRam2Nvm(void){
  NvM_RequestResultType ErrorStatus;
  if(0 < ui8WrWANVMBlock){
    Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSwpa_Pim_tWallocNvMBlock_GetErrorStatus(&ErrorStatus);
    if(ErrorStatus  != NVM_REQ_PENDING){
#ifndef WAModulTest		
		  Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSwpa_Pim_tWallocNvMBlock_WriteBlock((const NvM_DestPtr*)Rte_Pim_Pim_tWallocNvMBlock());
#endif
      ui8WrWANVMBlock = 0;
    }
  }
}

void SetWaData2NvmFlag(void){
  ui8WrWANVMBlock = 1;
  Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSwpa_Pim_tWallocNvMBlock_SetRamBlockStatus(TRUE);
}

#if 0
   DT_tData2Alloc tReData4Alloc;
   DT_ushWAState ucWAState;
   uint8 ucRet;
   Rte_Read_PP_Data2Alloc_DE_tData2Alloc(&tReData4Alloc);
   inputWA.AK35def.ulID = (uint32)(tReData4Alloc.ulID);
   inputWA.Header.ucTType = (uint8)(tReData4Alloc.ucTelType);
   inputWA.SchraderFP.ucPAL = (uint8)tReData4Alloc.ucPalData;
   inputWA.SchraderFP.ushStatusField = (uint16)(tReData4Alloc.ucFrameCounter<<8);
   ushSysTime = (uint16)tReData4Alloc.ushTimeStamp;
   ushLinABStick[0] = tReData4Alloc.ushAbsStickFL;
   ushLinABStick[1] = tReData4Alloc.ushAbsStickFR;
   ushLinABStick[2] = tReData4Alloc.ushAbsStickRL;
   ushLinABStick[3] = tReData4Alloc.ushAbsStickRR;
   ucWAState = (DT_ushWAState)ushLearnID(&inputWA );
	if(((ucWAState & cWAStateZO) == cWAStateZO) && (bIsAutoLocated == FALSE ) ){
		bIsAutoLocated = TRUE;
	}
	Rte_Write_PP_WAState_DE_ushWAState(ucWAState);
#endif

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

