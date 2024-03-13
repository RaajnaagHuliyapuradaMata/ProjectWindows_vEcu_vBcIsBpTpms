#include "Std_Types.hpp"

boolean bGetBitBetriebszustandBZ   (uint16 ushBitMask) {UNUSED(ushBitMask); return 0;}
boolean bGetBitFahrzeugzustandFZZ  (uint16 ushBitMask) {UNUSED(ushBitMask); return 0;}
boolean bGetSensorStateMissing     (uint8  ucColOfID)  {UNUSED(ucColOfID);  return 0;}
uint8   ucGetLastReceivedPress     (uint32 ulTelID)    {UNUSED(ulTelID);    return 0;}
uint8   ucGetLastReceivedTemp      (uint32 ulTelID)    {UNUSED(ulTelID);    return 0;}
uint8   USEui8PWPofHistCol         (uint8  ui8HistCol) {UNUSED(ui8HistCol); return 0;}
uint32  ulGetID                    (uint8  ucIx)       {UNUSED(ucIx);       return 0;}
uint8   ucGetColOfWP               (uint8  ucIx)       {UNUSED(ucIx);       return 0;}
uint8   ucGetWPOfCol               (uint8  ucIx)       {UNUSED(ucIx);       return 0;}
uint8   GETucPrefFront             (void)              {return 0;}
uint8   GETucPrefRear              (void)              {return 0;}
uint8   ucGetFailureState          (void)              {return 0;}
boolean bCheckHistIDReception1     (void)              {return 0;}
uint8   ui8GetALState              (void)              {return 0;}
uint8   ucGetHistoryState          (void)              {return 0;}
uint8   GETucMinWarnThresholdOfRam (void)              {return 0;}

int main(void){
   return 0;
}

/******************************************************************************/
/* Wrappers for SwcApplTpmsHmiHandler                                         */
/******************************************************************************/
#include "infRteSwcApplTpmsHmiHandler.hpp"

FUNC(Std_ReturnType, DCM_CODE) Dcm_GetSesCtrlType(
   P2VAR(Dcm_SesCtrlType, AUTOMATIC, DCM_APPL_DATA) SessionCtrlType
){
   UNUSED(SessionCtrlType);
   return 0;
}

FUNC(Std_ReturnType, DEM_CODE) Dem_GetIndicatorStatus(
      Dem_IndicatorIdType Dem_IndicatorId
   ,  P2VAR(Dem_IndicatorStatusType, AUTOMATIC, DEM_APPL_DATA) Dem_IndicatorStatus
){
   UNUSED(Dem_IndicatorId);
   UNUSED(Dem_IndicatorStatus);
   return 0;
}

FUNC(Std_ReturnType, ECUM_API_CODE) EcuM_GetState(
   P2VAR(EcuM_StateType, AUTOMATIC, ECUM_APPL_DATA) state
){
   UNUSED(state);
   return 0;
}

FUNC(Nm_ReturnType, NM_CODE) Nm_GetState(
      CONST(NetworkHandleType, AUTOMATIC             ) nmChannelHandle
   ,  CONSTP2VAR(Nm_StateType, AUTOMATIC, NM_APPL_VAR) nmStatePtr
   ,  CONSTP2VAR(Nm_ModeType,  AUTOMATIC, NM_APPL_VAR) nmModePtr
){
   (void)nmChannelHandle;
   UNUSED(*nmStatePtr);
   UNUSED(*nmModePtr);
   return 0;
}

FUNC(void, RTE_CTAPHUFTPMSWNH_APPL_CODE) RCtApHufTPMSwnh_GETucHiWarnstatus1WN_Operation(
   P2VAR(UInt16, AUTOMATIC, RTE_CTAPHUFTPMSWNH_APPL_VAR) ushWarnOUtTM
){
   UNUSED(ushWarnOUtTM);
}

FUNC(void, RTE_CTAPHUFTPMSWNH_APPL_CODE) RCtApHufTPMSwnh_GETaucWheelPosWarn_Operation(
      UInt8 pos
   ,  P2VAR(UInt8, AUTOMATIC, RTE_CTAPHUFTPMSWNH_APPL_VAR) ucWheelPosWarn
){
   UNUSED(pos);
   UNUSED(ucWheelPosWarn);
}

/******************************************************************************/
/* Wrappers for USWarn.c                                                      */
/******************************************************************************/
#include "infRteSwcApplTpmsWarnHandler.hpp"
void   StopFilterSTWT        (void){}
void   StopFilterHDWT        (void){}
uint8* GETpucStartAdrWPorPWP (void){return NULL_PTR;}
uint8  ucStartFilterSTWT     (       uint16        x                ){UNUSED(x); return 0;}
uint8  ucStartFilterHDWT     (       uint16        x                ){UNUSED(x); return 0;}
void   GetDataEE             (       uint8         x,           uint8* y,    uint8 z)     {UNUSED(x);     UNUSED(y);    UNUSED(z);}
void   PutDataEE             (       uint8         x,     const uint8* y,    uint8 z)     {UNUSED(x);     UNUSED(y);    UNUSED(z);}
void   SortBiggest1st        (       uint8*        ptVal,       uint8* ptIx, uint8 ucMax) {UNUSED(ptVal); UNUSED(ptIx); UNUSED(ucMax);}

/******************************************************************************/
/* Wrappers for uswarn_If.c                                                   */
/******************************************************************************/
sint8 GETscTref                     (void)        {               return 0;}
uint8 GETucPcalMinVaRelativCodOfRam (void)        {               return 0;}
uint8 GETucPcalMinHaRelativCodOfRam (void)        {               return 0;}
uint8 GETucWPorPWPofHistCol         (uint8 ucCol) {UNUSED(ucCol); return 0;}

/******************************************************************************/
/* Wrappers for ctrl.c                                                        */
/******************************************************************************/
void   TimerWTinit             (void){}
uint8  GETucT_HardOfRam        (void){return 0;}
uint8  GETucT_SoftOfRam        (void){return 0;}
uint8  GETucPercent_HardOfRam  (void){return 0;}
uint8  GETucPercent_SoftOfRam  (void){return 0;}
sint8  GETscT0OfRam            (void){return 0;}
sint8  GETscT1OfRam            (void){return 0;}
sint8  GETscT2OfRam            (void){return 0;}
uint16 GETushV1                (void){return 0;}
uint16 GETushV2                (void){return 0;}
uint16 GETushV3                (void){return 0;}
uint16 GETushHCmax             (void){return 0;}
uint8  GETucTempWarnOnOffOfRam (void){return 0;}

/******************************************************************************/
/* Wrappers for TSSMsg.c                                                      */
/******************************************************************************/
uint8 ui8HWTimerExpired (void){return 0;}
uint8 ui8SWTimerExpired (void){return 0;}
uint8 ui8KL15OFFnXsec   (void){return 0;}
uint8 ui8NoHoldOff      (void){return 0;}
uint8 ui8CalActive      (void){return 0;}
uint8 ui8MfdCalActive   (void){return 0;}
uint8 ui8KL15OFF        (void){return 0;}
