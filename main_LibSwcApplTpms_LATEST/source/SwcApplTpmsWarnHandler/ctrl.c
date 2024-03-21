/******************************************************************************/
/* File              : ctrl.c                                                 */
/* Author            : Nagaraja HULIYAPURADA MATA                             */
/* Copyright (c)2024 : All rights reserved.                                   */
/******************************************************************************/

/******************************************************************************/
/*#includeS                                                                  */
/******************************************************************************/
#include "Std_Types.hpp"

#include "infCtrl.hpp"

#include "infTssMsg.hpp"
#include "DAG_TVWarn.h"
#include "infRteSwcApplTpmsWarnHandler.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

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
TempWarnParaType tDAG_TemPara;
PWarnParaType    tDAG_PPara;

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
static void   RdDAGPara                     (void);
static void   InitDefValPPara               (void);
static void   InitDefValTemPara             (void);
static uint8  ui8GetDAGTempWarnPara         (TempWarnParaType* ptTemPara);
static uint8  ui8GetDAGPWarnPara            (PWarnParaType*    ptPPara);

extern uint8  ucWarnManagerWN               (uint8 ucAction, uint8* ptData);
extern void   TimerWTinit                   (void);
extern uint8  GETucT_HardOfRam              (void);
extern uint8  GETucT_SoftOfRam              (void);
extern uint8  GETucPercent_HardOfRam        (void);
extern uint8  GETucPercent_SoftOfRam        (void);
extern uint8  GETucPcalMinVaRelativCodOfRam (void);
extern uint8  GETucPcalMinHaRelativCodOfRam (void);
extern uint8  GETucMinWarnThresholdOfRam    (void);
extern sint8  GETscT0OfRam                  (void);
extern sint8  GETscT1OfRam                  (void);
extern sint8  GETscT2OfRam                  (void);
extern uint16 GETushV1                      (void);
extern uint16 GETushV2                      (void);
extern uint16 GETushV3                      (void);
extern uint16 GETushHCmax                   (void);
extern uint8  GETucTempWarnOnOffOfRam       (void);
extern void   USWPostInit                   (void);

void InitUSWAlgo(const uint8* ptWPos){
   uint8 aucDgServ[6] = {0};

   aucDgServ[0] = 0x00;
   aucDgServ[0] = ucWarnManagerWN(ucPorInitc, aucDgServ);
   aucDgServ[0] = 0x00;
   aucDgServ[1] = 0x00;
   aucDgServ[2] = 0x00;
   aucDgServ[0] = ucTSSMsgManagerTM(ucPorInitc, aucDgServ);
   TimerWTinit();
   UpdateWarnOut(ptWPos);
   RdDAGPara();
   IniTVWarn ();
}

static void RdDAGPara(void){
   if(((uint8) 0) == ui8GetDAGPWarnPara(    &tDAG_PPara))   InitDefValPPara();
   if(((uint8) 0) == ui8GetDAGTempWarnPara( &tDAG_TemPara)) InitDefValTemPara ();
}

static void InitDefValPPara(void){
   tDAG_PPara.ui16_CONSTANT_DELAY = 0;
   tDAG_PPara.ui16_T_HARD         = 60 * GETucT_HardOfRam();
   tDAG_PPara.ui16_T_SOFT         = 60 * GETucT_SoftOfRam();
   tDAG_PPara.ui8_PERCENT_HARD    = GETucPercent_HardOfRam();
   tDAG_PPara.ui8_PERCENT_SOFT    = GETucPercent_SoftOfRam();
   tDAG_PPara.ui8_P_MIN_F         = GETucPcalMinVaRelativCodOfRam();
   tDAG_PPara.ui8_P_MIN_R         = GETucPcalMinHaRelativCodOfRam();
   tDAG_PPara.ui8_P_MIN_TIRE      = GETucMinWarnThresholdOfRam();
}

static void InitDefValTemPara(void){
   tDAG_TemPara.i8_T0              = GETscT0OfRam();
   tDAG_TemPara.i8_T1              = GETscT1OfRam();
   tDAG_TemPara.i8_T2              = GETscT2OfRam();
   tDAG_TemPara.ui16_V1            = GETushV1();
   tDAG_TemPara.ui16_V2            = GETushV2();
   tDAG_TemPara.ui16_V3            = GETushV3();
   tDAG_TemPara.ui16_HC_MAX        = GETushHCmax();
   tDAG_TemPara.ui8_TempWarnEnable = GETucTempWarnOnOffOfRam();
}

static uint8 ui8GetDAGTempWarnPara (TempWarnParaType* ptTemPara) {ptTemPara = ptTemPara; return 0;}
static uint8 ui8GetDAGPWarnPara    (PWarnParaType*    ptPPara)   {ptPPara   = ptPPara;   return 0;}

void KL15OffWarnInit(const uint8* ptWPos){
   USWPostInit();
   UpdateWarnOut(ptWPos);
   IniTVWarnAtKL15Off();
   UpdateGlobWrnLvlNWarnDisp();
}

uint8 ui8GetPMIN_F(void){return tDAG_PPara.ui8_P_MIN_F;}
uint8 ui8GetPMIN_R(void){return tDAG_PPara.ui8_P_MIN_R;}

void UpdateWarnOut(const uint8* p2WPs){
   uint8 aucDgServ[6] = {0};
   uint8 i;
   aucDgServ[1] = ucGetWarnVectorsc;
   aucDgServ[0] = (uint8) ucWarnManagerWN(ucDiagServicec, &aucDgServ[1]);
   aucDgServ[0] = ucPutWarnVectorSetc;
   aucDgServ[0] = ucTSSMsgManagerTM(ucDiagServicec, aucDgServ);
   aucDgServ[0] = ucNewPositionsc;
   aucDgServ[1] = *p2WPs;
   for(i = 0; i < (ucSumWEc-1); i++){
      aucDgServ[2+i] = p2WPs[1+i];
   }
   aucDgServ[0] = ucTSSMsgManagerTM(ucDiagServicec, aucDgServ);
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/
