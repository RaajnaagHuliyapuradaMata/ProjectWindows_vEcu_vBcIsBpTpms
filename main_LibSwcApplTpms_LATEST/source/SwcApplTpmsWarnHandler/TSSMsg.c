/******************************************************************************/
/* File              : TSSMsg.c                                               */
/* Author            : Nagaraja HULIYAPURADA MATA                             */
/* Copyright (c)2024 : All rights reserved.                                   */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "Std_Types.hpp"

#include "infTssMsg.hpp"

#include "uswarn_Ifx.h"
#include "infRteSwcApplTpmsWarnHandler.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define ucMaxPosc 4
#define ucCbIdTMc ((uint16) 5)
#define ucTssMsgOutc        6
#define ucAllDAGWarningBits ((uint8) 0x1F)

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
struct TssMsg{
   uint8 ucId;
   uint8 ucPos;
   uint8 ucSystemState;
   uint8 ucWarning;
};

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
static uint8 ucGlobalWarnStatus;
static uint8 aucWarnAtPosTM[ucMaxPosc + 1];
static uint8 ucTPM_WarnDisp_Rq = cNORMAL;

uint16 ushWarnOutTM;
uint8  aucWheelPosWarn[ucMaxPosc + 1];

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
static void  TSSMsgInit               (void);
static void  GenTPM_WarnDisp_Rq       (void);
static void  GenDAGlobalWarningLevel  (void);
static void  TSSMsgOut                (const uint8* ptData);
static void  IdWarn2WP                (const uint8* p2WP);
static uint8 ucTSSMsgService          (      uint8* pucData);

extern uint8 ui8HWTimerExpired        (void);
extern uint8 ui8KL15OFFnXsec          (void);
extern uint8 ui8NoHoldOff             (void);
extern uint8 ui8CalActive             (void);
extern uint8 ui8MfdCalActive          (void);
extern uint8 ui8KL15OFF               (void);

static uint8 ucAnyHWActive(void){
  if(((aucWarnAtPosTM[ucSumWEc] & (1<<ucPMinIxc)) > 0) || (((aucWarnAtPosTM[ucSumWEc] & (1<<ucEcEIxc)) > 0) && (ui8HWTimerExpired() > (uint8)0))) return ((uint8)1);
  else                                                                                                                                            return ((uint8)0);
}

static uint8 ucAnySWActive(void){
  if(((aucWarnAtPosTM[ucSumWEc] & (1<<ucSFactorIxc)) > 0) && (ui8SWTimerExpired () > (uint8) 0)) return ((uint8)1);
  else                                                                                           return ((uint8)0);
}

static void TSSMsgOut(const uint8* ptData){
   union TssMsgAccess{
      struct TssMsg tTssMsg;
      uint8 ucByte[sizeof(struct TssMsg)];
   }tTMD;
   uint8 i;

   for(i=0; i < (uint8) sizeof(struct TssMsg) ;i++){
      tTMD.ucByte[i] = ptData[i];
   }
   if(tTMD.tTssMsg.ucId < ucSumWEc){
      aucWarnAtPosTM[tTMD.tTssMsg.ucId] = tTMD.tTssMsg.ucWarning;
      IdWarn2WP (GETpui82SysWP());
   }
}

static uint8 ucTSSMsgService(uint8* pucData){
   uint8 i, ucRet = 0;

   switch(*pucData){
      case (uint16) ucNewPositionsc:
         IdWarn2WP (GETpui82SysWP());
         ucRet = 0;
         break;

      case (uint16) ucPutWarnVectorSetc:
         pucData++;
         for(i=0;i<ucSumWEc;i++){
            aucWarnAtPosTM[i] = pucData[i];
         }
         break;

      default:
         ucRet = 0xff;
         break;
   }
   return ucRet;
}

static void TSSMsgInit(void){
   uint8 i;
   GetDataEE(ucCbIdTMc,&ucGlobalWarnStatus , 1);
   for(i = 0; i < (ucSumWEc + 1);i++){
      aucWarnAtPosTM[i]  = 0;
      aucWheelPosWarn[i] = 0;
   }
   if(cFAST_DEFLATION == ucGlobalWarnStatus){
      ucGlobalWarnStatus = cHARD_WARNING;
      PutDataEE(ucCbIdTMc, &ucGlobalWarnStatus , 1);
   }
   ushWarnOutTM = ucGlobalWarnStatus;
   ucTPM_WarnDisp_Rq = cNORMAL;
}

uint8 ucTSSMsgManagerTM(uint8 ucAction, uint8* ptData){
   uint8 ucRet = 0;
   switch(ucAction){
      case (uint16)ucPorInitc:             TSSMsgInit();            break;
      case (uint16)ucTssMsgOutc:           TSSMsgOut(ptData);       break;
      case (uint16)ucDiagServicec: ucRet = ucTSSMsgService(ptData); break;
      default:                     ucRet = 0xff;                    break;
   }
   return ucRet;
}

static void GenTPM_WarnDisp_Rq(void){
   if(ui8KL15OFFnXsec() > 0){
      ucTPM_WarnDisp_Rq = cNORMAL;
   }
   switch(ucTPM_WarnDisp_Rq){
      case cNORMAL:
         if(cFAST_DEFLATION == ushWarnOutTM)
         ucTPM_WarnDisp_Rq = cFAST_DEFLATION;
         else if((cHARD_WARNING == ushWarnOutTM) && (ui8NoHoldOff () > (uint8) 0) )
         ucTPM_WarnDisp_Rq = cHARD_WARNING;
         else if((cSOFT_WARNING == ushWarnOutTM) && (ui8NoHoldOff () > (uint8) 0) )
         ucTPM_WarnDisp_Rq = cSOFT_WARNING;
         break;

      case cSOFT_WARNING:
         if(cFAST_DEFLATION == ushWarnOutTM)
         ucTPM_WarnDisp_Rq = cFAST_DEFLATION;
         else if(cHARD_WARNING == ushWarnOutTM)
         ucTPM_WarnDisp_Rq = cHARD_WARNING;
         else if(cNORMAL == ushWarnOutTM )
         ucTPM_WarnDisp_Rq = cNORMAL;
         break;

      case cHARD_WARNING:
         if(cFAST_DEFLATION == ushWarnOutTM)
         ucTPM_WarnDisp_Rq = cFAST_DEFLATION;
         else if(cNORMAL == ushWarnOutTM )
         ucTPM_WarnDisp_Rq = cNORMAL;
         break;

      case cFAST_DEFLATION :
         if(cNORMAL == ushWarnOutTM )
         ucTPM_WarnDisp_Rq = cNORMAL;
         break;

      default:
         ucTPM_WarnDisp_Rq = cNORMAL;
         break;
   }
}

static void GenDAGlobalWarningLevel(void){
  ushWarnOutTM = (uint16) ucGlobalWarnStatus;
  switch (ucGlobalWarnStatus){
  case cNORMAL:
    if((aucWarnAtPosTM[ucSumWEc] & (1<<ucDHWIxc)) > 0)
      ucGlobalWarnStatus = cFAST_DEFLATION;
    else if((ucAnyHWActive () > 0) && (ui8CalActive () == 0))
      ucGlobalWarnStatus = cHARD_WARNING;
    else if((ucAnySWActive () > 0) && (ui8CalActive () == 0))
      ucGlobalWarnStatus = cSOFT_WARNING;
    break;

  case cSOFT_WARNING:
    if((aucWarnAtPosTM[ucSumWEc] & (1<<ucDHWIxc)) > 0)
      ucGlobalWarnStatus = cFAST_DEFLATION;
    else if((ucAnyHWActive () > 0) )
       ucGlobalWarnStatus = cHARD_WARNING;
    else if(((aucWarnAtPosTM[ucSumWEc] & ucAllDAGWarningBits) == (uint8) 0) || ((ui8MfdCalActive () == 1)))
      ucGlobalWarnStatus = cNORMAL;
    break;

  case cHARD_WARNING:
    if(((aucWarnAtPosTM[ucSumWEc] & (1<<ucDHWIxc)) > 0) && (ui8KL15OFF () == 0))
      ucGlobalWarnStatus = cFAST_DEFLATION;
   else if(ui8MfdCalActive () == 1)
         ucGlobalWarnStatus = cNORMAL;
    else if((aucWarnAtPosTM[ucSumWEc] & ((1<<ucPMinIxc)|(1<<ucEcEIxc))) == ((uint8) 0))
      ucGlobalWarnStatus = cSOFT_WARNING;
    break;

  case cFAST_DEFLATION :
    if(ui8KL15OFF () > 0)
      ucGlobalWarnStatus = cHARD_WARNING;
    else if(((aucWarnAtPosTM[ucSumWEc] & ucAllDAGWarningBits) == (uint8) 0) || ((ui8MfdCalActive () == 1)))
      ucGlobalWarnStatus = cNORMAL;
    break;
  
  default:
    ucGlobalWarnStatus = cNORMAL;
    break;
    }
  if(((uint8) ushWarnOutTM) !=  ucGlobalWarnStatus){
    PutDataEE(ucCbIdTMc, &ucGlobalWarnStatus , 1);
    ushWarnOutTM = (uint16) ucGlobalWarnStatus;
  }
}

uint8 GetucTPM_WarnDisp_Rq(void){
  return (ucTPM_WarnDisp_Rq);
}

void UpdateGlobWrnLvlNWarnDisp(void){
  GenDAGlobalWarningLevel ();
  UpdateDAGsOldOff();
  GenTPM_WarnDisp_Rq();
}

uint8 ui8GetHardWrnOfWP(uint8 ui8WP){
  if(sizeof(aucWheelPosWarn) > ui8WP)
    return( (( (aucWheelPosWarn[ui8WP] & ((uint8) (1<<ucEcEIxc)) ) == ((uint8) (1<<ucEcEIxc))  ) && (ui8HWTimerExpired() > (uint8) 0)) ? (uint8)1:(uint8)0);

  return ((uint8) 0);
}

uint8 ui8GetSoftWrnOfWP(uint8 ui8WP){
  if(sizeof(aucWheelPosWarn) > ui8WP)
    return( ( (aucWheelPosWarn[ui8WP] & ((uint8) (1<<ucSFactorIxc)) ) == ((uint8) (1<<ucSFactorIxc)) && (ui8SWTimerExpired() > (uint8) 0)) ? (uint8)1:(uint8)0);

  return ( (uint8) 0);
}
uint8 ui8GetWarntypeOfHistCol(uint8 ui8WnType, uint8 ui8HistCol){
  if(((uint8) 4) > ui8HistCol ){
    ui8WnType &= ucAllDAGWarningBits;
    if(ui8WnType == (aucWarnAtPosTM[ui8HistCol ] & ui8WnType )){
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
static void IdWarn2WP(const uint8* p2WP){
  uint8 i, ui8UnusedWP;
  ui8UnusedWP = (uint8) 0x0F;
  aucWheelPosWarn[ucSumWEc] = (uint8) 0;
  aucWarnAtPosTM[ucSumWEc] = (uint8) 0;

  for(i = 0; i < ucSumWEc; i++){
    switch(p2WP[i]){
    case (uint16) ucWPFLc:
      aucWheelPosWarn[ucWPFLc] = aucWarnAtPosTM[i];
      ui8UnusedWP &= ((uint8) ~1);
       break;
    case (uint16) ucWPFRc:
      aucWheelPosWarn[ucWPFRc] = aucWarnAtPosTM[i];
      ui8UnusedWP &= ((uint8) ~2);
       break;
    case (uint16) ucWPRLc:
      aucWheelPosWarn[ucWPRLc] = aucWarnAtPosTM[i];
      ui8UnusedWP &= ((uint8) ~4);
       break;
    case (uint16) ucWPRRc:
      aucWheelPosWarn[ucWPRRc] = aucWarnAtPosTM[i];
      ui8UnusedWP &= ((uint8) ~8);
       break;
    default:
      aucWheelPosWarn[ucSumWEc] |= aucWarnAtPosTM[i];
      break;
    }
    aucWarnAtPosTM[ucSumWEc] |= aucWarnAtPosTM[i];
  }

  for(i = 0; i < ucSumWEc; i++){
    if((uint8) 0 < (ui8UnusedWP & ((uint8) (1<<i)))){
      aucWheelPosWarn[i] = (uint8) 0;
    }
  }
  UpdateGlobWrnLvlNWarnDisp();
}
uint8 NewPositionsUSWIF(const uint8* pucRadPos){
  uint8 i, ucResult, aucDiagService[5];
  aucDiagService[0] = ucNewPositionsc;
  for(i = 0; i < ucSumWEc; i++){
    aucDiagService[i + 1] = pucRadPos[i];
  }
  if(0x00 ==  ucTSSMsgManagerTM(ucDiagServicec, aucDiagService)){
    ucResult = 0;
  }
  else{
    ucResult = 0xff;
  }
  return ucResult;
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

