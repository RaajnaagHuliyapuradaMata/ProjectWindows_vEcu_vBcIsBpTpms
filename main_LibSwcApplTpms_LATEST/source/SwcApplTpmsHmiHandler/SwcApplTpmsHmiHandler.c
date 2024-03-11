/******************************************************************************/
/* File              : SwcApplTpmsHmiHandler.c                                */
/* Author            : Nagaraja HULIYAPURADA MATA                             */
/* Copyright (c)2024 : All rights reserved.                                   */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "Std_Types.hpp"

#include "infRteSwcApplTpmsHmiHandler.hpp"

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
static REC_RefPress                                    tRefPress;
static REC_TPM_Lmp_On_Rq_Pr2_cp6wyrd9cg7ec7y2w3khz1gyt tTpmLmpOnRq;
static REC_TPM_Lmp_On_Rq_old                           tTpmLmpOnRqOld;
static REC_Tire_Stat_V2                                tTireStat;
static REC_Tire_Temp_V2                                tTireTemp;
static c08_WakeupRsn_TPM                               ucWakeUpRsn;
static DC_BOOL                                         bAwakeIgnOn;
static DC_BOOL                                         bAwakeWarnActiv;
static DC_BOOL                                         bTireStatMsgDispRestartFlag;
static boolean                                         ucHoldOffWarning = FALSE;
static boolean                                         bPminDetected    = FALSE;

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
static void    GetLastReceivedPress    (void);
static void    GetLastReceivedTemp     (void);
static boolean bPosOfAvlSensorKnown    (void);
static void    UpdateMalfuncLamp       (void);
static void    UpdateTireStatMsgDisp   (void);
static void    UpdateTireStatPressDisp (void);
static void    UpdateTirePresStat      (void);
static void    UpdateTireTempStat      (void);
static void    ResetHmiTpmStat         (void);

extern uint8                               GETucPrefFront    (void);
extern uint8                               GETucPrefRear     (void);
extern unsigned char                       ucGetHistoryState (void);
extern FUNC(Std_ReturnType,      DCM_CODE) Dcm_GetSesCtrlType     (P2VAR(Dcm_SesCtrlType, AUTOMATIC, DCM_APPL_DATA) SessionCtrlType);
extern FUNC(Std_ReturnType,      DEM_CODE) Dem_GetIndicatorStatus (Dem_IndicatorIdType Dem_IndicatorId, P2VAR(Dem_IndicatorStatusType, AUTOMATIC, DEM_APPL_DATA)  Dem_IndicatorStatus);
extern FUNC(Std_ReturnType, ECUM_API_CODE) EcuM_GetState          (P2VAR(EcuM_StateType, AUTOMATIC, ECUM_APPL_DATA) state);

boolean GetPminDetected(void);
void    SetPminDetected(uint8 ucInput);

void UpdateTxBusMsg(void){
   GetLastReceivedPress();
   GetLastReceivedTemp();
   UpdateTireStatMsgDisp();
   UpdateTireStatPressDisp();
   UpdateMalfuncLamp();
   UpdateTirePresStat();
   UpdateTireTempStat();

   tRefPress.RefPress_Front = GETucPrefFront();
   tRefPress.RefPress_Rear  = GETucPrefRear();
#ifdef FDasNewNVMdata
   tRefPress.RefPress_Front = (GETucPosCalPressure(cRadPosVL) > 40) ? GETucPosCalPressure(cRadPosVL)-40 : 0;
   tRefPress.RefPress_Rear  = (GETucPosCalPressure(cRadPosHL) > 40) ? GETucPosCalPressure(cRadPosHL)-40 : 0;
#endif
}

void InitTxBusMsg(void){
   uint16 ushTempWarnlevel         = 0;
   tRefPress.RefPress_Front        = I_C08_KPA_0_632D5_2D5_SNA;
   tRefPress.RefPress_Rear         = I_C08_KPA_0_632D5_2D5_SNA;
   tTpmLmpOnRq.TPM_IndLmp_On_Rq    = FALSE;
   tTpmLmpOnRq.TPM_MalfLmp_On_Rq   = FALSE;
   tTireStat.Press_Disp_Avl        = FALSE;
   tTireStat.TirePress_FL          = InvalidValue_c08_kPa_0_632d5_2d5;
   tTireStat.TirePress_FR          = InvalidValue_c08_kPa_0_632d5_2d5;
   tTireStat.TirePress_RL          = InvalidValue_c08_kPa_0_632d5_2d5;
   tTireStat.TirePress_RR          = InvalidValue_c08_kPa_0_632d5_2d5;
   tTireStat.TireStat_FL           = I_C02_TIRE_STAT_NORMAL;
   tTireStat.TireStat_FR           = I_C02_TIRE_STAT_NORMAL;
   tTireStat.TireStat_RL           = I_C02_TIRE_STAT_NORMAL;
   tTireStat.TireStat_RR           = I_C02_TIRE_STAT_NORMAL;
   tTireStat.TPM_MsgDisp_Rq        = I_C04_TPM_MSGDISP_RQ_NO_MESS;
   tTireStat.TPM_WarnDisp_Rq       = I_C03_TPM_WARNDISP_RQ_NO_WARN;

   ResetHmiTpmStat();

   tTireTemp.TireTemp_FL           = c08_degC_m50_204_1_UpperLimit;
   tTireTemp.TireTemp_FR           = c08_degC_m50_204_1_UpperLimit;
   tTireTemp.TireTemp_RL           = c08_degC_m50_204_1_UpperLimit;
   tTireTemp.TireTemp_RR           = c08_degC_m50_204_1_UpperLimit;
   tTireTemp.Tire_Temp_Stat_FL     = I_C02_TIRE_TEMP_NORMAL;
   tTireTemp.Tire_Temp_Stat_FR     = I_C02_TIRE_TEMP_NORMAL;
   tTireTemp.Tire_Temp_Stat_RL     = I_C02_TIRE_TEMP_NORMAL;
   tTireTemp.Tire_Temp_Stat_RR     = I_C02_TIRE_TEMP_NORMAL;
   tTireTemp.Tire_Temp_WarnDisp_Rq = I_C03_TIRE_TEMP_WARNDISP_NO_MESS;
   ucWakeUpRsn                     = I_C08_WAKEUPRSN_TPM_NETWORK;
   bAwakeIgnOn                     = FALSE;
   bAwakeWarnActiv                 = FALSE;
   bTireStatMsgDispRestartFlag     = FALSE;

   Rte_Call_PP_GetWarningVectors_OP_GETushWarnstatus1WN(&ushTempWarnlevel);
   ucHoldOffWarning = FALSE;
   if(ushTempWarnlevel > I_C03_TPM_WARNDISP_RQ_NO_WARN){
      ucHoldOffWarning = TRUE;
   }
   bPminDetected = 0;
}

void setTireStatMsgDispRestart(void){
   bTireStatMsgDispRestartFlag = TRUE;
}

void clearTireStatMsgDispRestart(void){
   bTireStatMsgDispRestartFlag = FALSE;
}

void UpdateTireStatMsgDisp(){
   static uint8          ucStatus = 0;
          uint8          ucStatusOld;
          EcuM_StateType EcuM_State;

 (void)EcuM_GetState(&EcuM_State);
   ucStatusOld = ucStatus;

   if(EcuM_State == ECUM_STATE_APP_RUN){
      Dem_GetIndicatorStatus(Dem_DEM_IND_ECUFAILURE, &ucStatus);
   }
   if(ucStatus > 0){
      tTireStat.TPM_MsgDisp_Rq = I_C04_TPM_MSGDISP_RQ_ERROR;
   }
   else if(bTireStatMsgDispRestartFlag){
      tTireStat.TPM_MsgDisp_Rq = I_C04_TPM_MSGDISP_RQ_RESTART;
   }
   else if(bGetBitBetriebszustandBZ(cZO_ERROR) && (ucGetFailureState() == FAILURE_MODE_noWE)){
      tTireStat.TPM_MsgDisp_Rq = I_C04_TPM_MSGDISP_RQ_NO_SENSORS;
   }
   else if(bGetBitBetriebszustandBZ(cZO_ERROR) && (ucGetFailureState() == FAILURE_MODE_soWE)){
      if(bPosOfAvlSensorKnown() && (cAL_Error != ui8GetALState ())){
         tTireStat.TPM_MsgDisp_Rq = I_C04_TPM_MSGDISP_RQ_WE_MISS;
      }
      else
      {
         tTireStat.TPM_MsgDisp_Rq = I_C04_TPM_MSGDISP_RQ_ERROR;
      }
   }
   else if(ucGetFailureState() == FAILURE_MODE_RfInterference){
      tTireStat.TPM_MsgDisp_Rq = I_C04_TPM_MSGDISP_RQ_TNA;
   }
   else if((bGetBitBetriebszustandBZ(cCAL_MFD_PLAUSI_ERROR) || (bGetBitBetriebszustandBZ(cCAL_AFD_PLAUSI_ERROR))) && (GetucTPM_WarnDisp_Rq() == 0)){
      tTireStat.TPM_MsgDisp_Rq = I_C04_TPM_MSGDISP_RQ_UNPLAUSIBLE;
   }
   else if((tTireStat.TPM_MsgDisp_Rq == I_C04_TPM_MSGDISP_RQ_RESTART) || (tTireStat.TPM_MsgDisp_Rq == I_C04_TPM_MSGDISP_RQ_UNPLAUSIBLE) || (tTireStat.TPM_MsgDisp_Rq == I_C04_TPM_MSGDISP_RQ_TNA)){
      tTireStat.TPM_MsgDisp_Rq = I_C04_TPM_MSGDISP_RQ_NO_MESS;
   }
   else if((tTireStat.TPM_MsgDisp_Rq == I_C04_TPM_MSGDISP_RQ_WE_MISS) || (tTireStat.TPM_MsgDisp_Rq == I_C04_TPM_MSGDISP_RQ_NO_SENSORS)){
      if(ucGetFailureState() == FAILURE_MODE_ok){
         tTireStat.TPM_MsgDisp_Rq = I_C04_TPM_MSGDISP_RQ_NO_MESS;
      }
   }
   else if((tTireStat.TPM_MsgDisp_Rq == I_C04_TPM_MSGDISP_RQ_ERROR) && (ucGetFailureState() == FAILURE_MODE_ok) && (ucStatus == 0)){
      tTireStat.TPM_MsgDisp_Rq = I_C04_TPM_MSGDISP_RQ_NO_MESS;
   }
   else if((ucStatusOld == 1) && (ucStatus == 0)){
      tTireStat.TPM_MsgDisp_Rq = I_C04_TPM_MSGDISP_RQ_NO_MESS;
   }
}

void UpdateTireStatPressDisp(void){
   uint8 ucRecHistID, ucStatusOld;
   EcuM_StateType  EcuM_State;
   static uint8 ucStatus = 0;

   ucRecHistID = bCheckHistIDReception1();

 (void)EcuM_GetState(&EcuM_State);
   ucStatusOld = ucStatus;

   if(EcuM_State == ECUM_STATE_APP_RUN){
      Dem_GetIndicatorStatus(Dem_DEM_IND_ECUFAILURE, &ucStatus);
   }

   if(ucStatus>0){
      tTireStat.TPM_Stat = I_C03_TPM_STAT_ERROR;
      tTireStat.Press_Disp_Avl = FALSE;
   }
   else if(ucGetFailureState() == FAILURE_MODE_noWE){
      tTireStat.TPM_Stat= I_C03_TPM_STAT_NO_SENSORS;
      tTireStat.Press_Disp_Avl = FALSE;
   }
   else if(bGetBitBetriebszustandBZ(cZO_ERROR) && (ucGetFailureState() == FAILURE_MODE_soWE)){
      if(bPosOfAvlSensorKnown() && (cAL_Error != ui8GetALState ())){
         tTireStat.TPM_Stat= I_C03_TPM_STAT_ACTIVE;
         tTireStat.Press_Disp_Avl = TRUE;
      }
      else
      {
         tTireStat.TPM_Stat= I_C03_TPM_STAT_ERROR;
         tTireStat.Press_Disp_Avl = FALSE;
      }
   }
   else if(ui8GetALState() == cAL_Unknown){
      tTireStat.TPM_Stat= I_C03_TPM_STAT_ACTIVE;
      tTireStat.Press_Disp_Avl = FALSE;
   }
   else if(bGetBitBetriebszustandBZ(cZO_FINISH)){
      if((ucRecHistID == TRUE) && (tTireStat.TirePress_FL != 0xFF) && (tTireStat.TirePress_FR != 0xFF) && (tTireStat.TirePress_RL != 0xFF) && (tTireStat.TirePress_RR != 0xFF)){
         tTireStat.Press_Disp_Avl = TRUE;
      }
      tTireStat.TPM_Stat = I_C03_TPM_STAT_ACTIVE;
   }
   else if(bGetBitBetriebszustandBZ(cER_FINISH)){
      if((ucRecHistID == TRUE) && (tTireStat.TirePress_FL != 0xFF) && (tTireStat.TirePress_FR != 0xFF) && (tTireStat.TirePress_RL != 0xFF) && (tTireStat.TirePress_RR != 0xFF) && ((ucGetHistoryState() & cHiStateZG) == cHiStateZG)){
         tTireStat.Press_Disp_Avl = TRUE;
      }
      tTireStat.TPM_Stat = I_C03_TPM_STAT_ACTIVE;
   }
   else if((ucRecHistID == TRUE) && (tTireStat.TirePress_FL != 0xFF) && (tTireStat.TirePress_FR != 0xFF) && (tTireStat.TirePress_RL != 0xFF) && (tTireStat.TirePress_RR != 0xFF) && ((ucGetHistoryState() & cHiStateZG) == cHiStateZG)){
      tTireStat.Press_Disp_Avl = TRUE;
      tTireStat.TPM_Stat = I_C03_TPM_STAT_ACTIVE;
   }
   else if((ucStatusOld == 1) && (ucStatus == 0)){
      tTireStat.TPM_Stat = I_C03_TPM_STAT_ACTIVE;
   }
   else{
   }
}

void UpdateTireTempStat(void){
   if(tTireStat.Press_Disp_Avl == TRUE){
      if(ui8OvrHeatWrnIsActive() == I_C03_TIRE_TEMP_WARNDISP_REDUCE_SPEED) {
         tTireTemp.Tire_Temp_WarnDisp_Rq = I_C03_TIRE_TEMP_WARNDISP_REDUCE_SPEED;
      }else if(ui8OvrHeatWrnIsActive() == I_C03_TIRE_TEMP_WARNDISP_OVERHEAT){
         tTireTemp.Tire_Temp_WarnDisp_Rq = I_C03_TIRE_TEMP_WARNDISP_OVERHEAT;
      }else{
         tTireTemp.Tire_Temp_WarnDisp_Rq = I_C03_TIRE_TEMP_WARNDISP_NO_MESS;
      }
      if(ui8GetTempColeurWP_FL() == I_C02_TIRE_TEMP_HOT){
         tTireTemp.Tire_Temp_Stat_FL = I_C02_TIRE_TEMP_HOT;
      }else if(ui8GetTempColeurWP_FL() == I_C02_TIRE_TEMP_WARM){
         tTireTemp.Tire_Temp_Stat_FL = I_C02_TIRE_TEMP_WARM;
      }else{
         tTireTemp.Tire_Temp_Stat_FL = I_C02_TIRE_TEMP_NORMAL;
      }
      if(ui8GetTempColeurWP_FR() == I_C02_TIRE_TEMP_HOT){
         tTireTemp.Tire_Temp_Stat_FR = I_C02_TIRE_TEMP_HOT;
      }else if(ui8GetTempColeurWP_FR() == I_C02_TIRE_TEMP_WARM){
         tTireTemp.Tire_Temp_Stat_FR = I_C02_TIRE_TEMP_WARM;
      }else{
         tTireTemp.Tire_Temp_Stat_FR = I_C02_TIRE_TEMP_NORMAL;
      }
      if(ui8GetTempColeurWP_RL() == I_C02_TIRE_TEMP_HOT){
         tTireTemp.Tire_Temp_Stat_RL = I_C02_TIRE_TEMP_HOT;
      }else if(ui8GetTempColeurWP_RL() == I_C02_TIRE_TEMP_WARM){
         tTireTemp.Tire_Temp_Stat_RL = I_C02_TIRE_TEMP_WARM;
      }else{
         tTireTemp.Tire_Temp_Stat_RL = I_C02_TIRE_TEMP_NORMAL;
      }
      if(ui8GetTempColeurWP_RR() == I_C02_TIRE_TEMP_HOT){
         tTireTemp.Tire_Temp_Stat_RR = I_C02_TIRE_TEMP_HOT;
      }else if(ui8GetTempColeurWP_RR() == I_C02_TIRE_TEMP_WARM){
         tTireTemp.Tire_Temp_Stat_RR = I_C02_TIRE_TEMP_WARM;
      }else{
         tTireTemp.Tire_Temp_Stat_RR = I_C02_TIRE_TEMP_NORMAL;
      }
   }
   else{
      tTireTemp.Tire_Temp_WarnDisp_Rq = I_C03_TIRE_TEMP_WARNDISP_NO_MESS;
      tTireTemp.Tire_Temp_Stat_FL = I_C02_TIRE_TEMP_NORMAL;
      tTireTemp.Tire_Temp_Stat_FR = I_C02_TIRE_TEMP_NORMAL;
      tTireTemp.Tire_Temp_Stat_RL = I_C02_TIRE_TEMP_NORMAL;
      tTireTemp.Tire_Temp_Stat_RR = I_C02_TIRE_TEMP_NORMAL;
   }
}

void UpdateTirePresStat(void){
   uint16  ushGlobalWarnStatus;
   DC_BOOL tempIndLmpOnRq = FALSE;
   uint8 ucWheelStatFL, ucWheelStatFR, ucWheelStatRL, ucWheelStatRR;
   c03_TPM_WarnDisp_Rq tempWarnDispRq = I_C03_TPM_WARNDISP_RQ_NO_WARN;

   Rte_Call_PP_GetWarningVectors_OP_GETushWarnstatus1WN(&ushGlobalWarnStatus);
   Rte_Call_PP_GetWarningVectors_OP_GETaucWheelPosWarn(cRadPosVL, &ucWheelStatFL);
   Rte_Call_PP_GetWarningVectors_OP_GETaucWheelPosWarn(cRadPosVR, &ucWheelStatFR);
   Rte_Call_PP_GetWarningVectors_OP_GETaucWheelPosWarn(cRadPosHL, &ucWheelStatRL);
   Rte_Call_PP_GetWarningVectors_OP_GETaucWheelPosWarn(cRadPosHR, &ucWheelStatRR);

   if(ushGlobalWarnStatus == I_C03_TPM_WARNDISP_RQ_NO_WARN){
      tTireStat.TireStat_FL = I_C02_TIRE_STAT_NORMAL;
      tTireStat.TireStat_FR = I_C02_TIRE_STAT_NORMAL;
      tTireStat.TireStat_RL = I_C02_TIRE_STAT_NORMAL;
      tTireStat.TireStat_RR = I_C02_TIRE_STAT_NORMAL;
   }
   else if(ushGlobalWarnStatus == I_C03_TPM_WARNDISP_RQ_SOFT){
      tTireStat.TireStat_FL = (ucWheelStatFL> I_C03_TPM_WARNDISP_RQ_SOFT) ? I_C03_TPM_WARNDISP_RQ_SOFT : ucWheelStatFL;
      tTireStat.TireStat_FR = (ucWheelStatFR> I_C03_TPM_WARNDISP_RQ_SOFT) ? I_C03_TPM_WARNDISP_RQ_SOFT : ucWheelStatFR;
      tTireStat.TireStat_RL = (ucWheelStatRL> I_C03_TPM_WARNDISP_RQ_SOFT) ? I_C03_TPM_WARNDISP_RQ_SOFT : ucWheelStatRL;
      tTireStat.TireStat_RR = (ucWheelStatRR> I_C03_TPM_WARNDISP_RQ_SOFT) ? I_C03_TPM_WARNDISP_RQ_SOFT : ucWheelStatRR;
   }
   else if((ushGlobalWarnStatus == I_C03_TPM_WARNDISP_RQ_FAST) || (ushGlobalWarnStatus == I_C03_TPM_WARNDISP_RQ_LOW_P)){
      tTireStat.TireStat_FL = ucWheelStatFL;
      tTireStat.TireStat_FR = ucWheelStatFR;
      tTireStat.TireStat_RL = ucWheelStatRL;
      tTireStat.TireStat_RR = ucWheelStatRR;
   }

   tempWarnDispRq = GetucTPM_WarnDisp_Rq ();
   tTireStat.TPM_WarnDisp_Rq = tempWarnDispRq;

   if((ushGlobalWarnStatus > 0) && (!bTireStatMsgDispRestartFlag)){
      tempIndLmpOnRq = TRUE;
   }
   else{
      tempIndLmpOnRq = FALSE;
   }
   tTpmLmpOnRq.TPM_IndLmp_On_Rq = tempIndLmpOnRq;
}

void UpdateMalfuncLamp(void){
   EcuM_StateType EcuM_State;
   uint8          ucStatus;

   (void)EcuM_GetState(&EcuM_State);
   if(EcuM_State == ECUM_STATE_APP_RUN){
      Dem_GetIndicatorStatus(Dem_DEM_IND_MALFLAMP, &ucStatus);
      if(ucStatus>0){
         tTpmLmpOnRq.TPM_MalfLmp_On_Rq = TRUE;
      }
      else
      {
         tTpmLmpOnRq.TPM_MalfLmp_On_Rq = FALSE;
      }
   }
}

boolean bHoldOffWarningEnabled(void){return ucHoldOffWarning;}

void updateHoldOff4Pmin(void){
   if(FALSE == GetPminDetected()){
      if((tTireStat.TirePress_FL != 0xFF) && (tTireStat.TirePress_FL < GETucMinWarnThresholdOfRam())){SetPminDetected(TRUE);}
      if((tTireStat.TirePress_FR != 0xFF) && (tTireStat.TirePress_FR < GETucMinWarnThresholdOfRam())){SetPminDetected(TRUE);}
      if((tTireStat.TirePress_RL != 0xFF) && (tTireStat.TirePress_RL < GETucMinWarnThresholdOfRam())){SetPminDetected(TRUE);}
      if((tTireStat.TirePress_RR != 0xFF) && (tTireStat.TirePress_RR < GETucMinWarnThresholdOfRam())){SetPminDetected(TRUE);}
   }
}

void updateHoldOffWarning(void){
   uint16 ushTempWarnlevel = 0;
   Rte_Call_PP_GetWarningVectors_OP_GETushWarnstatus1WN(&ushTempWarnlevel);
   if(FALSE == ucHoldOffWarning){
      if(
            (
                  (ushTempWarnlevel > I_C03_TPM_WARNDISP_RQ_NO_WARN)
               && (FALSE == bGetBitFahrzeugzustandFZZ(cKL_15_EIN))
            )
         && (
                  (FALSE == tTireStat.Press_Disp_Avl)
               || (TRUE  == bGetBitBetriebszustandBZ(cCAL_REQUEST))
            )
      ){
         ucHoldOffWarning = TRUE;
      }
   }
   else{
      if(
         (
               (TRUE == bPminDetected)
            || (bGetBitBetriebszustandBZ(cZO_TIMEOUT))
            || (
                     (TRUE == tTireStat.Press_Disp_Avl)
                  && (FALSE == bGetBitBetriebszustandBZ(cCAL_REQUEST))
               )
         )
         && (TRUE == bGetBitFahrzeugzustandFZZ(cKL_15_EIN))
      ){
         ucHoldOffWarning = FALSE;
      }
   }
}

void    SetPminDetected (boolean ucInput){       bPminDetected = ucInput;}
boolean GetPminDetected (void)           {return bPminDetected;}

uint8 ucGetHMICurrentTirePress(uint8 ucPos){
        if(cRadPosVL == ucPos){return tTireStat.TirePress_FL;}
   else if(cRadPosVR == ucPos){return tTireStat.TirePress_FR;}
   else if(cRadPosHL == ucPos){return tTireStat.TirePress_RL;}
   else if(cRadPosHR == ucPos){return tTireStat.TirePress_RR;}
   else                       {return InvalidValue_c08_kPa_0_632d5_2d5;}
}

uint8 ucGetHMICurrentTireStat(uint8 ucPos){
        if(cRadPosVL == ucPos){return tTireStat.TireStat_FL;}
   else if(cRadPosVR == ucPos){return tTireStat.TireStat_FR;}
   else if(cRadPosHL == ucPos){return tTireStat.TireStat_RL;}
   else if(cRadPosHR == ucPos){return tTireStat.TireStat_RR;}
   else                       {return I_C02_TIRE_STAT_NORMAL;}
}

uint8 ucGetHMICurrentTireTemp(uint8 ucPos){
   if(ucPos == cRadPosVL){
      return tTireTemp.TireTemp_FL;
   }
   else if(ucPos == cRadPosVR){
      return tTireTemp.TireTemp_FR;
   }
   else if(ucPos == cRadPosHL){
      return tTireTemp.TireTemp_RL;
   }
   else if(ucPos == cRadPosHR){
      return tTireTemp.TireTemp_RR;
   }
   else{
      return c08_degC_m50_204_1_UpperLimit;
   }
}

uint8 ucGetHMICurrentTireTempStat(uint8 ucPos){
   if(ucPos == cRadPosVL){
      return tTireTemp.Tire_Temp_Stat_FL;
   }
   else if(ucPos == cRadPosVR){
      return tTireTemp.Tire_Temp_Stat_FR;
   }
   else if(ucPos == cRadPosHL){
      return tTireTemp.Tire_Temp_Stat_RL;
   }
   else if(ucPos == cRadPosHR){
      return tTireTemp.Tire_Temp_Stat_RR;
   }
   else{
      return I_C02_TIRE_TEMP_NORMAL;
   }
}

uint8 ucGetHMITPMMsgDisp(void){
   return tTireStat.TPM_MsgDisp_Rq;
}

uint8 ucGetHMITPMStat(void){
   return tTireStat.TPM_Stat;
}

uint8 ucGetHMITPMWarnDisp(void){
   return tTireStat.TPM_WarnDisp_Rq;
}

DC_BOOL bGetHMITPMIndLmpOn(void){
   return tTpmLmpOnRq.TPM_IndLmp_On_Rq;
}

DC_BOOL bGetHMITPMMalfLmpOn(void){
   return tTpmLmpOnRq.TPM_MalfLmp_On_Rq;
}

DC_BOOL bGetHMITirePressAvlBit(void){
   return tTireStat.Press_Disp_Avl;
}

uint8 ucGetHMITireTempWarnDisp(void){
   return tTireTemp.Tire_Temp_WarnDisp_Rq;
}

REC_TPM_Lmp_On_Rq_Pr2_cp6wyrd9cg7ec7y2w3khz1gyt* pGetTpmLmpOnRq(void){
   return &tTpmLmpOnRq;
}

REC_TPM_Lmp_On_Rq_old* pGetTpmLmpOnRqOld(void){
   tTpmLmpOnRqOld.TPM_IndLmp_On_Rq_old  = tTpmLmpOnRq.TPM_IndLmp_On_Rq;
   tTpmLmpOnRqOld.TPM_MalfLmp_On_Rq_old = tTpmLmpOnRq.TPM_MalfLmp_On_Rq;
   return &tTpmLmpOnRqOld;
}

REC_Tire_Stat_V2* pGetTireStat(void){
   return &tTireStat;
}

REC_Tire_Temp_V2* pGetTireTemp(void){
   return &tTireTemp;
}

REC_RefPress* pGetHmiRefPress(void){
   return &tRefPress;
}

uint8 ucGetHMIWakeUpRsn(void){
   return ucWakeUpRsn;
}

boolean bGetHMIAwakeDiagActv(void){
   Dcm_SesCtrlType CurSession;
   Dcm_GetSesCtrlType(&CurSession);
   return((boolean)(DCM_EXTENDED_DIAGNOSTIC_SESSION == CurSession));
}

boolean bGetHMIAwakeIgnitionOn(void){
   return bAwakeIgnOn;
}

boolean bGetHMIAwakeNwSt(void){
   Nm_StateType  NmState;
   Nm_ModeType   NmMode;

   Nm_GetState(
         0u
      ,  &NmState
      ,  &NmMode
   );

   return(
      (boolean)(
            (NM_STATE_REPEAT_MESSAGE == NmState)
         || (NM_STATE_BUS_SLEEP      == NmState)
      )
   );
}

uint8 bGetHMIAwakeWarnActv(void){
   return bAwakeWarnActiv;
}

void InitHMIAfterKL15On(void){
   tTireStat.TPM_MsgDisp_Rq = I_C04_TPM_MSGDISP_RQ_NO_MESS;
   ucWakeUpRsn              = I_C08_WAKEUPRSN_TPM_NETWORK;
   bAwakeIgnOn              = TRUE;
}

void InitHMIAfterKL15Off(void){
   bAwakeIgnOn = FALSE;
}

void ResetHmiTpmStat(void){
   if((cAL_Error == ui8GetALState ()) && (bGetSensorStateMissing(0) || bGetSensorStateMissing(1) || bGetSensorStateMissing(2) || bGetSensorStateMissing(3))){
      tTireStat.TPM_Stat = I_C03_TPM_STAT_ERROR;
   }
   else{
      if(bPosOfAvlSensorKnown() && (cAL_Error != ui8GetALState ())){
         tTireStat.TPM_Stat = I_C03_TPM_STAT_WAIT;
      }
      else
      {
         tTireStat.TPM_Stat = I_C03_TPM_STAT_ACTIVE;
      }
   }
}

void InitHMIAfterSetIDsOverDiag(void){
   ResetHmiTpmStat();
   tTireStat.Press_Disp_Avl = FALSE;
}

static void GetLastReceivedPress(void){
   uint8 i = 0;

   if(USEui8PWPofHistCol(i) == cMaxLR){
      tTireStat.TirePress_FL  = ucGetLastReceivedPress(ulGetID(ucGetColOfWP(cRadPosVL)));
      tTireStat.TirePress_FR  = ucGetLastReceivedPress(ulGetID(ucGetColOfWP(cRadPosVR)));
      tTireStat.TirePress_RL  = ucGetLastReceivedPress(ulGetID(ucGetColOfWP(cRadPosHL)));
      tTireStat.TirePress_RR  = ucGetLastReceivedPress(ulGetID(ucGetColOfWP(cRadPosHR)));
   }
   else{
      for(i = 0;i < cMaxLR; i++){
         if(USEui8PWPofHistCol(i) == cRadPosVL){
            tTireStat.TirePress_FL = ucGetLastReceivedPress(ulGetID(i));
         }
         else if(USEui8PWPofHistCol(i) == cRadPosVR){
            tTireStat.TirePress_FR = ucGetLastReceivedPress(ulGetID(i));
         }
         else if(USEui8PWPofHistCol(i) == cRadPosHL){
            tTireStat.TirePress_RL = ucGetLastReceivedPress(ulGetID(i));
         }
         else if(USEui8PWPofHistCol(i) == cRadPosHR){
            tTireStat.TirePress_RR = ucGetLastReceivedPress(ulGetID(i));
         }
         else
         {
         }
      }
   }

#ifdef as_AE_Paket
   if((tTireStat.TirePress_FL != 0xFF) && (tTireStat.TirePress_FL < GETucMinWarnThresholdOfRam())){
      SetPminDetected(TRUE);
   }
   if((tTireStat.TirePress_FR != 0xFF) && (tTireStat.TirePress_FR < GETucMinWarnThresholdOfRam())){
      SetPminDetected(TRUE);
   }
   if((tTireStat.TirePress_RL != 0xFF) && (tTireStat.TirePress_RL < GETucMinWarnThresholdOfRam())){
      SetPminDetected(TRUE);
   }
   if((tTireStat.TirePress_RR != 0xFF) && (tTireStat.TirePress_RR < GETucMinWarnThresholdOfRam())){
      SetPminDetected(TRUE);
   }
#endif
}

static void GetLastReceivedTemp(void){
   uint8 i = 0;
   if(USEui8PWPofHistCol(i) == cMaxLR){
      tTireTemp.TireTemp_FL = ucGetLastReceivedTemp(ulGetID(ucGetColOfWP(cRadPosVL)));
      tTireTemp.TireTemp_FR = ucGetLastReceivedTemp(ulGetID(ucGetColOfWP(cRadPosVR)));
      tTireTemp.TireTemp_RL = ucGetLastReceivedTemp(ulGetID(ucGetColOfWP(cRadPosHL)));
      tTireTemp.TireTemp_RR = ucGetLastReceivedTemp(ulGetID(ucGetColOfWP(cRadPosHR)));
   }
   else{
      for(i = 0;i < cMaxLR; i++){
         if(USEui8PWPofHistCol(i) == cRadPosVL){
            tTireTemp.TireTemp_FL = ucGetLastReceivedTemp(ulGetID(i));
         }
         else if(USEui8PWPofHistCol(i) == cRadPosVR){
            tTireTemp.TireTemp_FR = ucGetLastReceivedTemp(ulGetID(i));
         }
         else if(USEui8PWPofHistCol(i) == cRadPosHL){
            tTireTemp.TireTemp_RL = ucGetLastReceivedTemp(ulGetID(i));
         }
         else if(USEui8PWPofHistCol(i) == cRadPosHR){
            tTireTemp.TireTemp_RR = ucGetLastReceivedTemp(ulGetID(i));
         }
         else
         {
         }
      }
   }
}

static boolean  bPosOfAvlSensorKnown(void){
   uint8 i;
   boolean ucRetVal;
   ucRetVal = FALSE;
   for(i = 0; i < cMaxLR; i++){
      if((!bGetSensorStateMissing(i)) && (ucGetWPOfCol(i) < cMaxLR)){
         ucRetVal = TRUE;
      }
   }
   return ucRetVal;
}

void ClearTPM_StatNoSensors(void){
   if(tTireStat.TPM_Stat == I_C03_TPM_STAT_NO_SENSORS){
      tTireStat.TPM_Stat = I_C03_TPM_STAT_ACTIVE;
   }
}

void ClearTPM_StatSensorsMissing(void){
   uint8 ucStatus;
   EcuM_StateType  EcuM_State;

   ucStatus = 0;

   (void)EcuM_GetState(&EcuM_State);
   if(EcuM_State == ECUM_STATE_APP_RUN){
      Dem_GetIndicatorStatus(Dem_DEM_IND_ECUFAILURE, &ucStatus);
   }
   if((tTireStat.TPM_Stat == I_C03_TPM_STAT_ERROR) && (ucStatus == 0)){
      tTireStat.TPM_Stat = I_C03_TPM_STAT_ACTIVE;
   }
}

void ClearTPM_MsgDispRqSensorsMissing(void){
   uint8 ucStatus;
   EcuM_StateType  EcuM_State;

   ucStatus = 0;

   (void)EcuM_GetState(&EcuM_State);
   if(EcuM_State == ECUM_STATE_APP_RUN){
      Dem_GetIndicatorStatus(Dem_DEM_IND_ECUFAILURE, &ucStatus);
   }
   if((tTireStat.TPM_MsgDisp_Rq == I_C04_TPM_MSGDISP_RQ_WE_MISS) || ((tTireStat.TPM_MsgDisp_Rq == I_C04_TPM_MSGDISP_RQ_ERROR) && (ucStatus == 0))){
      tTireStat.TPM_MsgDisp_Rq = I_C04_TPM_MSGDISP_RQ_NO_MESS;
   }
}

void ClearTPM_MsgDispRqNoSensors(void){
   if(tTireStat.TPM_MsgDisp_Rq == I_C04_TPM_MSGDISP_RQ_NO_SENSORS){
      tTireStat.TPM_MsgDisp_Rq = I_C04_TPM_MSGDISP_RQ_NO_MESS;
   }
}

uint8 GetCurUsedWPOfCol(uint8 ucCol){
   if(USEui8PWPofHistCol(ucCol) == cMaxLR){
      return ucGetWPOfCol(ucCol);
   }else{
      return USEui8PWPofHistCol(ucCol);
   }
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

