#include "Std_Types.h"

#include "infRteSwcApplTpmsHmiHandler.hpp"

/*
extern void                                             UpdateTxBusMsg                   (void);
extern void                                             InitTxBusMsg                     (void);
extern void                                             setTireStatMsgDispRestart        (void);
extern void                                             clearTireStatMsgDispRestart      (void);
extern boolean                                          bHoldOffWarningEnabled           (void);
extern void                                             updateHoldOff4Pmin               (void);
extern void                                             updateHoldOffWarning             (void);
extern uint8                                            ucGetHMITPMMsgDisp               (void);
extern uint8                                            ucGetHMITPMStat                  (void);
extern uint8                                            ucGetHMITPMWarnDisp              (void);
extern DC_BOOL                                          bGetHMITPMIndLmpOn               (void);
extern DC_BOOL                                          bGetHMITPMMalfLmpOn              (void);
extern DC_BOOL                                          bGetHMITirePressAvlBit           (void);
extern uint8                                            ucGetHMITireTempWarnDisp         (void);
extern REC_TPM_Lmp_On_Rq_Pr2_cp6wyrd9cg7ec7y2w3khz1gyt* pGetTpmLmpOnRq                   (void);
extern REC_TPM_Lmp_On_Rq_old*                           pGetTpmLmpOnRqOld                (void);
extern REC_Tire_Stat_V2*                                pGetTireStat                     (void);
extern REC_Tire_Temp_V2*                                pGetTireTemp                     (void);
extern REC_RefPress*                                    pGetHmiRefPress                  (void);
extern uint8                                            ucGetHMIWakeUpRsn                (void);
extern boolean                                          bGetHMIAwakeDiagActv             (void);
extern boolean                                          bGetHMIAwakeIgnitionOn           (void);
extern boolean                                          bGetHMIAwakeNwSt                 (void);
extern uint8                                            bGetHMIAwakeWarnActv             (void);
extern void                                             InitHMIAfterKL15On               (void);
extern void                                             InitHMIAfterKL15Off              (void);
extern void                                             InitHMIAfterSetIDsOverDiag       (void);
extern void                                             ClearTPM_StatNoSensors           (void);
extern void                                             ClearTPM_StatSensorsMissing      (void);
extern void                                             ClearTPM_MsgDispRqSensorsMissing (void);
extern void                                             ClearTPM_MsgDispRqNoSensors      (void);
*/

int main(void){
/*
   UpdateTxBusMsg                   ();
   InitTxBusMsg                     ();
   setTireStatMsgDispRestart        ();
   clearTireStatMsgDispRestart      ();
   bHoldOffWarningEnabled           ();
   updateHoldOff4Pmin               ();
   updateHoldOffWarning             ();
   (void)ucGetHMITPMMsgDisp         ();
   (void)ucGetHMITPMStat            ();
   (void)ucGetHMITPMWarnDisp        ();
   (void)bGetHMITPMIndLmpOn         ();
   (void)bGetHMITPMMalfLmpOn        ();
   (void)bGetHMITirePressAvlBit     ();
   (void)ucGetHMITireTempWarnDisp   ();
   (void)pGetTpmLmpOnRq             ();
   (void)pGetTpmLmpOnRqOld          ();
   (void)pGetTireStat               ();
   (void)pGetTireTemp               ();
   (void)pGetHmiRefPress            ();
   (void)ucGetHMIWakeUpRsn          ();
   (void)bGetHMIAwakeDiagActv       ();
   (void)bGetHMIAwakeIgnitionOn     ();
   (void)bGetHMIAwakeNwSt           ();
   (void)bGetHMIAwakeWarnActv       ();
   InitHMIAfterKL15On               ();
   InitHMIAfterKL15Off              ();
   InitHMIAfterSetIDsOverDiag       ();
   ClearTPM_StatNoSensors           ();
   ClearTPM_StatSensorsMissing      ();
   ClearTPM_MsgDispRqSensorsMissing ();
   ClearTPM_MsgDispRqNoSensors      ();
*/
   return 0;
}

boolean bGetBitBetriebszustandBZ   (uint16 ushBitMask) {ushBitMask = ushBitMask; return 0;}
boolean bGetBitFahrzeugzustandFZZ  (uint16 ushBitMask) {ushBitMask = ushBitMask; return 0;}
boolean bGetSensorStateMissing     (uint8  ucColOfID)  {ucColOfID  = ucColOfID;  return 0;}
uint8   ucGetLastReceivedPress     (uint32 ulTelID)    {ulTelID    = ulTelID;    return 0;}
uint8   ucGetLastReceivedTemp      (uint32 ulTelID)    {ulTelID    = ulTelID;    return 0;}
uint8   USEui8PWPofHistCol         (uint8 ui8HistCol)  {ui8HistCol = ui8HistCol; return 0;}
uint32  ulGetID                    (uint8 ucIx)        {ucIx       = ucIx;       return 0;}
uint8   ucGetColOfWP               (uint8 ucIx)        {ucIx       = ucIx;       return 0;}
uint8   ucGetWPOfCol               (uint8 ucIx)        {ucIx       = ucIx;       return 0;}
uint8   GETucPrefFront             (void)              {return 0;}
uint8   GETucPrefRear              (void)              {return 0;}
uint8   ucGetFailureState          (void)              {return 0;}
boolean bCheckHistIDReception1     (void)              {return 0;}
uint8   ui8GetALState              (void)              {return 0;}
uint8   GetucTPM_WarnDisp_Rq       (void)              {return 0;}
uint8   ucGetHistoryState          (void)              {return 0;}
uint8   ui8OvrHeatWrnIsActive      (void)              {return 0;}
uint8   ui8GetTempColeurWP_FL      (void)              {return 0;}
uint8   ui8GetTempColeurWP_FR      (void)              {return 0;}
uint8   ui8GetTempColeurWP_RL      (void)              {return 0;}
uint8   ui8GetTempColeurWP_RR      (void)              {return 0;}
uint8   GETucMinWarnThresholdOfRam (void)              {return 0;}

FUNC(Std_ReturnType, DCM_CODE) Dcm_GetSesCtrlType(
   P2VAR(Dcm_SesCtrlType, AUTOMATIC, DCM_APPL_DATA) SessionCtrlType
){
   SessionCtrlType = SessionCtrlType;
   return 0;
}

FUNC(Std_ReturnType, DEM_CODE) Dem_GetIndicatorStatus(
      Dem_IndicatorIdType Dem_IndicatorId
   ,  P2VAR(Dem_IndicatorStatusType, AUTOMATIC, DEM_APPL_DATA) Dem_IndicatorStatus
){
   Dem_IndicatorId     = Dem_IndicatorId;
   Dem_IndicatorStatus = Dem_IndicatorStatus;
   return 0;
}

FUNC(Std_ReturnType, ECUM_API_CODE) EcuM_GetState(
   P2VAR(EcuM_StateType, AUTOMATIC, ECUM_APPL_DATA) state
){
   state = state;
   return 0;
}

FUNC(Nm_ReturnType, NM_CODE) Nm_GetState(
      CONST(NetworkHandleType, AUTOMATIC             ) nmChannelHandle
   ,  CONSTP2VAR(Nm_StateType, AUTOMATIC, NM_APPL_VAR) nmStatePtr
   ,  CONSTP2VAR(Nm_ModeType,  AUTOMATIC, NM_APPL_VAR) nmModePtr
){
   (void)nmChannelHandle;
   *nmStatePtr = *nmStatePtr;
   *nmModePtr  = *nmModePtr;
   return 0;
}

FUNC(void, RTE_CTAPHUFTPMSWNH_APPL_CODE) RCtApHufTPMSwnh_GETucHiWarnstatus1WN_Operation(
   P2VAR(UInt16, AUTOMATIC, RTE_CTAPHUFTPMSWNH_APPL_VAR) ushWarnOUtTM
){
   ushWarnOUtTM = ushWarnOUtTM;
}

FUNC(void, RTE_CTAPHUFTPMSWNH_APPL_CODE) RCtApHufTPMSwnh_GETaucWheelPosWarn_Operation(
      UInt8 pos
   ,  P2VAR(UInt8, AUTOMATIC, RTE_CTAPHUFTPMSWNH_APPL_VAR) ucWheelPosWarn
){
   pos            = pos;
   ucWheelPosWarn = ucWheelPosWarn;
}
