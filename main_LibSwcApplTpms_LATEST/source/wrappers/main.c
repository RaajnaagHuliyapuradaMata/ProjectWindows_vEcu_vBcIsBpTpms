#include "Std_Types.hpp"

int main(void){
   return 0;
}

/******************************************************************************/
/* Wrappers for SwcApplTpmsHmiHandler                                         */
/******************************************************************************/
#include "infRteSwcApplTpmsHmiHandler.hpp"
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

/******************************************************************************/
/* Wrappers for SwcApplTpmsHmiHandler                                         */
/******************************************************************************/
#include "infRteSwcApplTpmsWarnHandler.hpp"
PWarnParaType tDAG_PPara;
void   StopFilterSTWT        (void){}
void   StopFilterHDWT        (void){}
uint8  Getui8AtmosphericP    (void){return 0;}
uint8  ui8GetPMIN_F          (void){return 0;}
uint8  ui8GetPMIN_R          (void){return 0;}
uint8* GETpucStartAdrWPorPWP (void){return NULL_PTR;}
uint8* pui8GetLastM1Pressure (void){return NULL_PTR;}
void   ResetM1Pressure       (       uint8         i                ){i     = i;}
void   UpdateWarnOut         (const  uint8*        p2WPs            ){p2WPs = p2WPs;}
uint8  ucStartFilterSTWT     (       uint16        x                ){x     = x; return 0;}
uint8  ucStartFilterHDWT     (       uint16        x                ){x     = x; return 0;}
uint8  Getui8PrefMinOfId     (       uint8         histCol          ){histCol = histCol; return 0;}
void   PuT                   (       uint8         ui8Ix, sint8 i8T ){ui8Ix = ui8Ix; i8T = i8T;}
void   GetDataEE             (       uint8         x,       uint8* y, uint8 z){x = x; y = y; z = z;}
void   PutDataEE             (       uint8         x, const uint8* y, uint8 z){x = x; y = y; z = z;}
void   SortBiggest1st        (       uint8*        ptVal, uint8* ptIx, uint8 ucMax){ptVal = ptVal; ptIx = ptIx; ucMax = ucMax;}
void   GetRatValOfId         (       uint8         uiHistCol, struct SollDat* p2RatVal){uiHistCol = uiHistCol; p2RatVal = p2RatVal;}
uint8  bDHW                  (struct LocalWarnDat* ptLWD, uint8 ucWarnCfg){ptLWD = ptLWD; ucWarnCfg = ucWarnCfg; return 0;}
uint8  bSoftFactor           (struct LocalWarnDat* ptLWD, uint8 ucWarnCfg){ptLWD = ptLWD; ucWarnCfg = ucWarnCfg; return 0;}
uint8  bEcE                  (struct LocalWarnDat* ptLWD, uint8 ucWarnCfg){ptLWD = ptLWD; ucWarnCfg = ucWarnCfg; return 0;}
uint8  bPMin                 (struct LocalWarnDat *ptLWD, uint8 ucWarnCfg){ptLWD = ptLWD; ucWarnCfg = ucWarnCfg; return 0;}
