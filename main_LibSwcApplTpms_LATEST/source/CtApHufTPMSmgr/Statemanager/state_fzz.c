

#include "state_fzz.h"
#include "internal_clockX.h"
#include "Rte_CtApHufTPMSmgr.h"
#include "WallocX.h"
#include "state_fzzX.h"
#include "SupplyBattery.h"
#include "state_bzX.h"
#include "USWarnX.H"
#include "HMI_handlerX.h"
#include "SensorLoBat.h"
#include "filling_detectionX.h"
#include "DEM.h"
#include "EcuM_Generated_Types.h"
extern uint8   bAwakeIgnOn;

#define cMIN_TIME_SNA_ERROR   ((uint8) 60)
 #define cMIN_TIME_AFTER_IGN_START ((uint8) 10)
 #define cMIN_TIME_AFTER_ENG_START ((uint8) 10)

static uint16 ushVehicleSpeed = 0;
static sint8 scOutdoorTemperature = 0;
static uint8 ucEcuStopCntr = 0;
static uint8 ucFzzCurrentLearnMode = cCompleteLearn;
static uint8 ucFzzPreviousParkingState = 1;

static uint8 ucTimeSinceLastKL15On = 0;
static uint8 ucTimeSinceLastEngStart = cMIN_TIME_AFTER_ENG_START;

static uint8 ucTimeSnaWhlplsFL = 0;
 static uint8 ucTimeSnaWhlplsFR = 0;
 static uint8 ucTimeSnaWhlplsRL = 0;
 static uint8 ucTimeSnaWhlplsRR = 0;
 static uint8 ucTimeSnaTractSystem = 0;
 static uint8 ucTimeSnavehSpeed = 0;
 static uint8 ucTimeSnaAirTempOut = 0;
 static uint8 ucTimeSnaIcA3TpmActiv = 0;

static uint8 ucIgnOnStartProc = 0;

void InitAfterKl15OffSM(void);
void InitWATCF(void);
void InitAfterKl15OnSM(void);
void InitFDAfterKl15On(void);
void InitFDAfterKl15OffSM(void);
void UpdateFzzCurrentLearnMode(void);
uint8 ucGetFzzCurrentLearnMode(void);

void ClearFzzSignalUnplausibleState(uint16 ushBitMask);
static void  UpdateFzzAllSignalDTCSetCond(void);
static void UpdateFzzAllSignalImplausibleCntr(void);
void SetFzzSignalImplauState(uint16 ucBitMask);
void InitFzzCanSignalMonitoring(void);
static boolean bFzzSignalFailureMonitoringActiv(void);
static boolean bGetFzzSignalTimeOutState(uint16 ushBitMask);

void SetFzzState4MM(uint8 state);
uint8 GetFzzState4MM(void);

void SetGlobWarnState4MM(uint8 state);
uint8 GetGlobWarnState4MM(void);

extern void InitTxBusMsg(void);
extern FUNC(Std_ReturnType, ECUM_API_CODE) EcuM_GetState(P2VAR(EcuM_StateType, AUTOMATIC, ECUM_APPL_DATA) state);
extern void UpdateSensorStateAtClamp15Off(void);
extern void InitTelStatInfoAtModeChange(void);
extern void UpdateHMICurrentTireStat4MM(void);

void InitFZZ( void ){
  ClearBitFahrzeugzustandFZZ( cFZZ_ALLE_BITS );

 ushVehicleSpeed=0;
 scOutdoorTemperature=0;
 ucEcuStopCntr=0;
 ucFzzCurrentLearnMode = cCompleteLearn;
  ucFzzPreviousParkingState = 1;

  InitFzzCanSignalMonitoring();
}

void SetBitFahrzeugzustandFZZ( uint16 ushBitMask ){
   ushFahrzeugzustand |= ushBitMask;
}

void ClearBitFahrzeugzustandFZZ( uint16 ushBitMask ){
   ushFahrzeugzustand &= ~ushBitMask;
}

boolean bGetBitFahrzeugzustandFZZ( uint16 ushBitMask ){
   return (boolean) ((ushFahrzeugzustand & ushBitMask) != 0 );
}

uint16 ushGetFahrzeugzustandFZZ( uint16 ushBitMask ){
   return (ushFahrzeugzustand & ushBitMask);
}

void EvTerminal15OnFZZ( void ){
  if( bGetBitFahrzeugzustandFZZ( cKL_15_EIN ) == FALSE ){
    SetBitFahrzeugzustandFZZ( cKL_15_EIN );

    InitWATCF();
    InitAfterKl15OnSM();
      InitFDAfterKl15On();
      Rte_Call_UR_ComMUser_HMI_RequestComMode(COMM_FULL_COMMUNICATION);
  }
}

void EvTerminal15OffFZZ( void ){
  if( bGetBitFahrzeugzustandFZZ( cKL_15_EIN ) == TRUE ){
    ClearBitFahrzeugzustandFZZ( cKL_15_EIN );

    InitFDAfterKl15OffSM();
    InitAfterKl15OffSM();
      ClearBitBetriebszustandBZ(cCAL_AFD_PLAUSI_ERROR | cCAL_MFD_PLAUSI_ERROR);

  }
  }

void EvVehicleRollingFZZ( void ){
  if( bGetBitFahrzeugzustandFZZ( cFAHRZEUG_FAEHRT ) == FALSE ){
    SetBitFahrzeugzustandFZZ( cFAHRZEUG_FAEHRT );
  }
}

void EvVehicleSpeed4CalFZZ( void ){
  if( bGetBitFahrzeugzustandFZZ( cKFZFAEHRT_20KMH ) == FALSE ){
    SetBitFahrzeugzustandFZZ( cKFZFAEHRT_20KMH );
  }
}

void EvVehicleStandsStillFZZ( void ){
  if( bGetBitFahrzeugzustandFZZ( cFAHRZEUG_FAEHRT ) == TRUE ){
    ClearBitFahrzeugzustandFZZ( cFAHRZEUG_FAEHRT );
    ucEcuStopCntr++;
  }
}

void EvVehicleNoSpeed4CalFZZ( void ){
  if( bGetBitFahrzeugzustandFZZ( cKFZFAEHRT_20KMH ) == TRUE ){
    ClearBitFahrzeugzustandFZZ( cKFZFAEHRT_20KMH );

  }
}

void EvReDiagActiveFZZ( void ){
  if( bGetBitFahrzeugzustandFZZ( cRS_VTHRES ) == FALSE ){
    SetBitFahrzeugzustandFZZ( cRS_VTHRES );
  }
}

void EvReDiagInactiveFZZ( void ){
  if( bGetBitFahrzeugzustandFZZ( cRS_VTHRES ) == TRUE ){
    ClearBitFahrzeugzustandFZZ( cRS_VTHRES );
  }
}

void EvEngineRunningFZZ( void ){
  if( bGetBitFahrzeugzustandFZZ( cENG_STARTING ) == TRUE ){
    ucTimeSinceLastEngStart = 0;
   }
  SetBitFahrzeugzustandFZZ( cENG_RUNNING );
  ClearBitFahrzeugzustandFZZ( cENG_STARTING );
}

void EvEngineStopedFZZ( void ){

  if( bGetBitFahrzeugzustandFZZ( cENG_STARTING ) == TRUE ){
    ucTimeSinceLastEngStart = 0;
   }
  ClearBitFahrzeugzustandFZZ( cENG_STARTING );
  ClearBitFahrzeugzustandFZZ( cENG_RUNNING );

}

void EvEngineStartingFZZ(void){
   ucTimeSinceLastEngStart = 0;
    ClearBitFahrzeugzustandFZZ(cENG_RUNNING);
   SetBitFahrzeugzustandFZZ( cENG_STARTING);
}

void EvDriveDirectionForwardFZZ( void ){
  ClearBitFahrzeugzustandFZZ( cRUECKWAERTSFAHRT );
}

void EvDriveDirectionBackwardFZZ( void ){
  SetBitFahrzeugzustandFZZ( cRUECKWAERTSFAHRT );
#ifdef FPA
  ReNewABSRef();
#endif
}

void EvKl30DiagNoUnterSpgFZZ( void ){
  if( bGetBitFahrzeugzustandFZZ( cKL30_UNTERSPG ) == TRUE ){
    ClearBitFahrzeugzustandFZZ( cKL30_UNTERSPG );
  }
}

void EvKl30DiagUnterSpgFZZ( void ){
  if( bGetBitFahrzeugzustandFZZ( cKL30_UNTERSPG ) == FALSE ){
      SetBitFahrzeugzustandFZZ( cKL30_UNTERSPG );
  }
}

uint8 GetEvKl30DiagUnterSpgFZZ( void ){
  if( bGetBitFahrzeugzustandFZZ( cKL30_UNTERSPG ) == TRUE ){
      return ( TRUE );
  }
   else
   {
      return ( FALSE );
   }
}

void EvKl30DiagNoUeberSpgFZZ( void ){
  if( bGetBitFahrzeugzustandFZZ( cKL30_UEBERSPG ) == TRUE ){
    ClearBitFahrzeugzustandFZZ( cKL30_UEBERSPG );
  }
}

void EvKl30DiagUeberSpgFZZ( void ){
  if( bGetBitFahrzeugzustandFZZ( cKL30_UEBERSPG ) == FALSE ){
      SetBitFahrzeugzustandFZZ( cKL30_UEBERSPG );
  }
}

uint8 GetEvKl30DiagUeberSpgFZZ( void ){
  if( bGetBitFahrzeugzustandFZZ( cKL30_UEBERSPG ) == TRUE ){
      return( TRUE );
  }
   else
   {
      return( FALSE );
   }
}

void EvTPMS433MhzFZZ( void ){
  if( bGetBitFahrzeugzustandFZZ( cTPMS433Mhz ) == FALSE ){
      SetBitFahrzeugzustandFZZ( cTPMS433Mhz );
  }

  if( bGetBitFahrzeugzustandFZZ( cTPMS315Mhz ) == TRUE ){
    ClearBitFahrzeugzustandFZZ( cTPMS315Mhz );
  }

}

void EvTPMS315MhzFZZ( void ){
  if( bGetBitFahrzeugzustandFZZ( cTPMS315Mhz ) == FALSE ){
      SetBitFahrzeugzustandFZZ( cTPMS315Mhz );
  }

  if( bGetBitFahrzeugzustandFZZ( cTPMS433Mhz ) == TRUE ){
    ClearBitFahrzeugzustandFZZ( cTPMS433Mhz );
  }

}

uint32 GETulKilometersFZZ( void ){
  uint32 ulKilometers=0;
   return ulKilometers;
}

sint8 GETscOutdoorTemperatureFZZ( void ){
  return scOutdoorTemperature;
}

uint16 GETushSpeedFZZ( void ){

  return ushVehicleSpeed;
}

void SendEnvData2VehStateMgr(uint8* data){
  DT_tEnvData* tEnvData = (DT_tEnvData*)data;
   ushVehicleSpeed = tEnvData->ushVehSpeed;
   scOutdoorTemperature = (sint8)tEnvData->ucTempOut;

   if(tEnvData->ucKlState == TRUE){
      EvTerminal15OnFZZ();
   }else{

      EvTerminal15OffFZZ();
   }

  if( ucIgnOnStartProc==0){
    ucTimeSinceLastKL15On = 0;
  }
  ucIgnOnStartProc = tEnvData->ucIgnOnStartProc;

  if(ushVehicleSpeed > 5){
      EvVehicleRollingFZZ();
    if(ushVehicleSpeed > cV_MIN){
         EvVehicleSpeed4CalFZZ();
    }
      else
      {
         EvVehicleNoSpeed4CalFZZ();
      }
   }
  else
  {
     if(ushVehicleSpeed < 2){
         EvVehicleStandsStillFZZ();
      }
      EvVehicleNoSpeed4CalFZZ();
   }

  if(tEnvData->ucEngStat == cEngStat_STOPPED){
    EvEngineStopedFZZ();
  }
  else if(tEnvData->ucEngStat == cEngStat_STARTING){
    EvEngineStartingFZZ();
  }
  else if(tEnvData->ucEngStat == cEngStat_RUNNING){
    EvEngineRunningFZZ();
  }

}

void InitAfterKl15OffSM(void){

      SetFzzState4MM(FALSE);		/*CRS_1211_130_377*/
   KL15OffWarnInit(GETpucStartAdrWPorPWP ());
   InitHMIAfterKL15Off();
   UpdateSensorStateAtClamp15Off();

}

void InitWATCF(void){

}

void InitAfterKl15OnSM(void){

  InitHMIAfterKL15On();

  InitSensorLoBat ();

  KL15OffWarnInit(GETpucStartAdrWPorPWP ());
   SetFzzState4MM(TRUE);
   SetGlobWarnState4MM(GETushWarnstatus1WN());
   UpdateHMICurrentTireStat4MM();

}

void InitFDAfterKl15On(void){
   if((bGETucCalRequestState(cCAL_MANUAL_ACTIV) == TRUE) && (bGetBitBetriebszustandBZ(cCAL_REQUEST) == FALSE) && (bGETucCalRequestState(cCAL_AUTO_ENABLE2) == TRUE) ){
       FillingDetectionMFD(FALSE);
   }
   else
   {
      if((bGETucCalRequestState(cCAL_AUTO_ACTIV) == TRUE) && (bGETucCalRequestState(cCAL_AUTO_ENABLE3) == TRUE)){
         ClearBitCalRequestState(cCAL_AUTO_ENABLE3);
         FillingDetectionAFDIII(TRUE);
      }
      else
      {
         if((GETucPfillFront() == 0) && (GETucPfillRear() == 0 ) &&  (bGETucCalNotAckState(cCAL_FBM_ACTIV_NAK) == FALSE)){
            SetBitCalRequestState2Ram(cCAL_AUTO_ENABLE2);
         }
      }
   }
   if((GETucPfillFront() == 0) && (GETucPfillRear() == 0 )){
      PUTucPfillFront(InvalidValue_c08_kPa_0_632d5_2d5);
      PUTucPfillRear(InvalidValue_c08_kPa_0_632d5_2d5);
      PUTscTfill(127);
   }
}

void InitFDAfterKl15OffSM(void){
   ClearBitFahrzeugzustandFZZ(cKFZPARKING_START_AFD);

      if((   bGETucCalRequestState(cCAL_AUTO_ENABLE3) ==   FALSE)  &&  (bGETucCalNotAckState(cCAL_FBM_ACTIV_NAK) == FALSE)){
         SetBitCalRequestState2Ram(cCAL_AUTO_ENABLE2);
      }

}

uint8 ucGetEcuStopCntr(void){

  return ucEcuStopCntr;

}

void UpdateFzzCurrentLearnMode(void){
  WAParNCfgType ucParkingState;

   ucParkingState.ucWACfg = (uint8)ucGetCurrentECUParkingState();
  if((ucFzzPreviousParkingState == 1) && (ucParkingState.ucWACfg == 2) && (bGetBitBetriebszustandBZ(cZO_FINISH) ||  bGetBitBetriebszustandBZ(cZO_ERROR))){
    InitBZ();
    InitTelStatInfoAtModeChange();
    WAInit(&ucParkingState);
  }else if((ucFzzPreviousParkingState == 2) && (ucParkingState.ucWACfg == 3)){
    InitBZ();
    InitTelStatInfoAtModeChange();
    WAInit(&ucParkingState);
  }
  ucFzzPreviousParkingState = ucParkingState.ucWACfg;
  if( bGetBitBetriebszustandBZ(cZO_FINISH) ||  bGetBitBetriebszustandBZ(cZO_ERROR)){
    ucFzzCurrentLearnMode = cNoLearn;
  }
  else
   {
    ucFzzCurrentLearnMode = ucGetLearnMode();
   }
}

uint8 ucGetFzzCurrentLearnMode(void){
  return ucFzzCurrentLearnMode;
}

void UpdateFzzDTcEnableCond(void){
  EcuM_StateType  EcuM_State;

  (void)EcuM_GetState(&EcuM_State);
  if( EcuM_State == ECUM_STATE_APP_RUN ){
    UpdateFzzAllSignalImplausibleCntr();
    UpdateFzzAllSignalDTCSetCond();
     if(bGetFzzSignalTimeOutState(cFZZ_CANSM_BUSOFF_Network)){
      Dem_SetEnableCondition( DEM_SL_NETWORK_COMM_WITH_CLAMP15, FALSE);
      Dem_SetEnableCondition( DEM_SL_NETWORK_COMM_NO_CLAMP15, FALSE);
    }
    else
    {
      if(!bGetBitFahrzeugzustandFZZ( cKL_15_EIN )){
           Dem_SetEnableCondition( DEM_SL_POWER_DISTRIBUTION, FALSE);
           Dem_SetEnableCondition( DEM_SL_NETWORK_COMM_WITH_CLAMP15, FALSE);
        Dem_SetEnableCondition( DEM_SL_NETWORK_COMM_NO_CLAMP15, TRUE);
      }
      else
      {
           Dem_SetEnableCondition( DEM_SL_POWER_DISTRIBUTION, TRUE);
           Dem_SetEnableCondition( DEM_SL_NETWORK_COMM_WITH_CLAMP15, TRUE);
        Dem_SetEnableCondition( DEM_SL_NETWORK_COMM_NO_CLAMP15, FALSE);
      }
    }
    UpdateFzzAllSignalDTCSetCond();
  }
}

void InitFzzCanSignalMonitoring(void){
  ucTimeSinceLastKL15On = 0;
   ucTimeSinceLastEngStart = cMIN_TIME_AFTER_ENG_START;

  ucTimeSnaWhlplsFL = 0;
   ucTimeSnaWhlplsFR = 0;
   ucTimeSnaWhlplsRL = 0;
   ucTimeSnaWhlplsRR = 0;
   ucTimeSnaTractSystem = 0;
   ucTimeSnavehSpeed = 0;
   ucTimeSnaAirTempOut = 0;
   ucTimeSnaIcA3TpmActiv = 0;

  ushFzzCanSignalImplauState = 0xFFFF;
  ushFzzCanSignalTimeOutState = 0xFFFF;
 }

void SetFzzSignalImplauState(uint16 ushBitMask){
    ushFzzCanSignalImplauState |= ushBitMask;

}

boolean bGetFzzCanSignalImplausibleState(uint16 ushBitMask){
  return (boolean) ((ushBitMask & ushFzzCanSignalImplauState)!= 0);
}

static void UpdateFzzAllSignalDTCSetCond(void){
  if( (ucTimeSnaWhlplsFL==cMIN_TIME_SNA_ERROR) && (ushVehicleSpeed>5) && bGetBitFahrzeugzustandFZZ( cKL_15_EIN ) && !bGetFzzSignalTimeOutState(cFZZ_WHLPLS_CNT_TIMEOUT)){
    Dem_SetEventStatus( Dem_DTC_0xd41208, DEM_EVENT_STATUS_FAILED);
   }
  else
  {
  }
  if( (ucTimeSnaWhlplsFR==cMIN_TIME_SNA_ERROR) && (ushVehicleSpeed>5) && bGetBitFahrzeugzustandFZZ( cKL_15_EIN ) && !bGetFzzSignalTimeOutState(cFZZ_WHLPLS_CNT_TIMEOUT)){
    Dem_SetEventStatus( Dem_DTC_0xd41308, DEM_EVENT_STATUS_FAILED);
   }else
  {
  }
  if( (ucTimeSnaWhlplsRL==cMIN_TIME_SNA_ERROR) && (ushVehicleSpeed>5) && bGetBitFahrzeugzustandFZZ( cKL_15_EIN ) && !bGetFzzSignalTimeOutState(cFZZ_WHLPLS_CNT_TIMEOUT)){
      Dem_SetEventStatus( Dem_DTC_0xd41008, DEM_EVENT_STATUS_FAILED);

  }else
  {
  }
  if( (ucTimeSnaWhlplsRR==cMIN_TIME_SNA_ERROR) && (ushVehicleSpeed>5) && bGetBitFahrzeugzustandFZZ( cKL_15_EIN ) && !bGetFzzSignalTimeOutState(cFZZ_WHLPLS_CNT_TIMEOUT)){
    Dem_SetEventStatus( Dem_DTC_0xd41108, DEM_EVENT_STATUS_FAILED);
   }else
  {
  }
  if( ((ucTimeSnavehSpeed==cMIN_TIME_SNA_ERROR) || (ucTimeSnaAirTempOut==cMIN_TIME_SNA_ERROR) || (ucTimeSnaIcA3TpmActiv==cMIN_TIME_SNA_ERROR)) && bFzzSignalFailureMonitoringActiv() && (!bGetFzzSignalTimeOutState(cFZZ_CANSM_BUSOFF_Network)) ){
    Dem_SetEventStatus( Dem_DTC_0xc42308, DEM_EVENT_STATUS_FAILED);
   }
  else
  {
  }
   if( (ucTimeSnaTractSystem==cMIN_TIME_SNA_ERROR) && bFzzSignalFailureMonitoringActiv() && (!bGetFzzSignalTimeOutState(cFZZ_CANSM_BUSOFF_Network)) && !bGetFzzSignalTimeOutState(cFZZ_WHLPLS_CNT_TIMEOUT)){
      Dem_SetEventStatus( Dem_DTC_0xc41608, DEM_EVENT_STATUS_FAILED);
   }
  else
  {
  }
  if(bGetFzzSignalTimeOutState(cFZZ_WHLPLS_CNT_TIMEOUT) && bFzzSignalFailureMonitoringActiv()){
    Dem_SetEventStatus( Dem_DTC_0xc12287, DEM_EVENT_STATUS_FAILED);
   }
  else
  {
  }
  if(bGetFzzSignalTimeOutState(cFZZ_IGN_VEH_STAT_TIMEOUT)){
    Dem_SetEventStatus( Dem_DTC_0xc16887, DEM_EVENT_STATUS_FAILED);
   }
  else
  {
  }
   if(bGetFzzSignalTimeOutState(cFZZ_PN14_STAT_TIMEOUT) && bFzzSignalFailureMonitoringActiv()){
    Dem_SetEventStatus( Dem_DTC_0xc14187, DEM_EVENT_STATUS_FAILED);
   }
  else
  {
  }
   if( (bGetFzzSignalTimeOutState(cFZZ_IC_BASIC_INFO_TIMEOUT) || bGetFzzSignalTimeOutState(cFZZ_IC_DATE_TIME_TIMEOUT) || bGetFzzSignalTimeOutState(cFZZ_IC_SETTINGS_TIMEOUT))&& bFzzSignalFailureMonitoringActiv()){
    Dem_SetEventStatus( Dem_DTC_0xc15587, DEM_EVENT_STATUS_FAILED);
   }
  else
  {
  }
   if( ( bGetFzzSignalTimeOutState(cFZZ_ENG_CTRL_TIMEOUT) )&& bFzzSignalFailureMonitoringActiv()){
    Dem_SetEventStatus( Dem_DTC_0xc10087, DEM_EVENT_STATUS_FAILED);
   }
  else
  {
  }

  if(bGetFzzSignalTimeOutState(cFZZ_CANSM_BUSOFF_Network)){
    Dem_SetEventStatus( Dem_CANSM_E_BUSOFF_Network_0, DEM_EVENT_STATUS_FAILED);
   }
  else
  {
    Dem_SetEventStatus( Dem_CANSM_E_BUSOFF_Network_0, DEM_EVENT_STATUS_PASSED);
   }
}

static void UpdateFzzAllSignalImplausibleCntr(void){
  if( (ucIgnOnStartProc == 1) && (ucTimeSinceLastKL15On < cMIN_TIME_AFTER_IGN_START) ){
    ucTimeSinceLastKL15On++;
  }

  if( (bGetBitFahrzeugzustandFZZ( cENG_STARTING ) == FALSE) && (ucTimeSinceLastEngStart<cMIN_TIME_AFTER_ENG_START) ){
    ucTimeSinceLastEngStart++;
  }

  if(bFzzSignalFailureMonitoringActiv()){
    SetBitFahrzeugzustandFZZ(cFAILURE_MONITORING);
  }
  else
  {
    ClearBitFahrzeugzustandFZZ(cFAILURE_MONITORING);
  }
  if( bGetFzzCanSignalImplausibleState(cFZZ_WHLPLS_FL_IMPLAU) && (ucTimeSnaWhlplsFL < cMIN_TIME_SNA_ERROR) ){
    ucTimeSnaWhlplsFL++;
  }
   if( bGetFzzCanSignalImplausibleState(cFZZ_WHLPLS_FR_IMPLAU) && (ucTimeSnaWhlplsFR < cMIN_TIME_SNA_ERROR)){
    ucTimeSnaWhlplsFR++;
  }
   if( bGetFzzCanSignalImplausibleState(cFZZ_WHLPLS_RL_IMPLAU) && (ucTimeSnaWhlplsRL < cMIN_TIME_SNA_ERROR) ){
    ucTimeSnaWhlplsRL++;
  }
   if( bGetFzzCanSignalImplausibleState(cFZZ_WHLPLS_RR_IMPLAU) && (ucTimeSnaWhlplsRR < cMIN_TIME_SNA_ERROR) ){
    ucTimeSnaWhlplsRR++;
  }
   if( bGetFzzCanSignalImplausibleState(cFZZ_VEH_SPEED_IMPLAU) && (ucTimeSnavehSpeed < cMIN_TIME_SNA_ERROR) ){
    ucTimeSnavehSpeed ++;
  }
   if( bGetFzzCanSignalImplausibleState(cFZZ_AIRTEMP_OUT_IMPLAU) && (ucTimeSnaAirTempOut < cMIN_TIME_SNA_ERROR) ){
    ucTimeSnaAirTempOut ++;
  }
   if( bGetFzzCanSignalImplausibleState(cFZZ_IC_A3_TPM_ACTV_IMPLAU) && (ucTimeSnaIcA3TpmActiv < cMIN_TIME_SNA_ERROR) ){
    ucTimeSnaIcA3TpmActiv ++;
  }
   if( bGetFzzCanSignalImplausibleState(cFZZ_TRACTION_SYSTEM_IMPLAU) && (ucTimeSnaTractSystem < cMIN_TIME_SNA_ERROR) ){
    ucTimeSnaTractSystem ++;
  }

}

void ClearFzzSignalUnplausibleCntr(uint16 ushBitMask){

  if( (ushBitMask & cFZZ_WHLPLS_FR_IMPLAU) > 0 ){
    ucTimeSnaWhlplsFR = 0;
   }
  if( (ushBitMask & cFZZ_WHLPLS_FL_IMPLAU) > 0 ){
    ucTimeSnaWhlplsFL = 0;
   }
  if( (ushBitMask & cFZZ_WHLPLS_RL_IMPLAU) > 0 ){
    ucTimeSnaWhlplsRL = 0;
   }
  if( (ushBitMask & cFZZ_WHLPLS_RR_IMPLAU) > 0 ){
    ucTimeSnaWhlplsRR = 0;
   }
   if( (ushBitMask & cFZZ_VEH_SPEED_IMPLAU) > 0 ){
    ucTimeSnavehSpeed = 0;
   }
  if( (ushBitMask & cFZZ_AIRTEMP_OUT_IMPLAU) > 0 ){
    ucTimeSnaAirTempOut = 0;
   }
  if( (ushBitMask & cFZZ_IC_A3_TPM_ACTV_IMPLAU) > 0 ){
    ucTimeSnaIcA3TpmActiv = 0;
   }
  if( (ushBitMask & cFZZ_TRACTION_SYSTEM_IMPLAU) > 0 ){
    ucTimeSnaTractSystem = 0;
   }
}

void ClearFzzSignalUnplausibleState(uint16 ushBitMask){
  ushFzzCanSignalImplauState &= ~ushBitMask;

  if(!bGetFzzCanSignalImplausibleState(cFZZ_WHLPLS_FR_IMPLAU)){
    ucTimeSnaWhlplsFR = 0;
     Dem_SetEventStatus( Dem_DTC_0xd41308, DEM_EVENT_STATUS_PASSED);
   }
  if(!bGetFzzCanSignalImplausibleState(cFZZ_WHLPLS_FL_IMPLAU)){
    ucTimeSnaWhlplsFL = 0;
     Dem_SetEventStatus( Dem_DTC_0xd41208, DEM_EVENT_STATUS_PASSED);
   }
  if(!bGetFzzCanSignalImplausibleState(cFZZ_WHLPLS_RL_IMPLAU)){
    ucTimeSnaWhlplsRL = 0;
     Dem_SetEventStatus( Dem_DTC_0xd41008, DEM_EVENT_STATUS_PASSED);
   }
  if(!bGetFzzCanSignalImplausibleState(cFZZ_WHLPLS_RR_IMPLAU)){
    ucTimeSnaWhlplsRR = 0;
     Dem_SetEventStatus( Dem_DTC_0xd41108, DEM_EVENT_STATUS_PASSED);
   }
   if(!bGetFzzCanSignalImplausibleState(cFZZ_VEH_SPEED_IMPLAU) ){
    ucTimeSnavehSpeed = 0;
   }
  if(!bGetFzzCanSignalImplausibleState(cFZZ_AIRTEMP_OUT_IMPLAU) ){
    ucTimeSnaAirTempOut = 0;
   }
  if(!bGetFzzCanSignalImplausibleState(cFZZ_IC_A3_TPM_ACTV_IMPLAU) ){
    ucTimeSnaIcA3TpmActiv = 0;
   }
  if( (!bGetFzzCanSignalImplausibleState(cFZZ_VEH_SPEED_IMPLAU)) && (!bGetFzzCanSignalImplausibleState(cFZZ_AIRTEMP_OUT_IMPLAU)) && (!bGetFzzCanSignalImplausibleState(cFZZ_IC_A3_TPM_ACTV_IMPLAU)) ){
    Dem_SetEventStatus( Dem_DTC_0xc42308, DEM_EVENT_STATUS_PASSED);
   }
  if(!bGetFzzCanSignalImplausibleState(cFZZ_TRACTION_SYSTEM_IMPLAU) ){
    ucTimeSnaTractSystem = 0;
     Dem_SetEventStatus( Dem_DTC_0xc41608, DEM_EVENT_STATUS_PASSED);
   }
}

static boolean bFzzSignalFailureMonitoringActiv(void){
  return ( (ucTimeSinceLastEngStart == cMIN_TIME_AFTER_ENG_START) && (ucTimeSinceLastKL15On == cMIN_TIME_AFTER_IGN_START) );
}

void ClearFzzSignalTimeOutState(uint16 ushBitMask){
  ushFzzCanSignalTimeOutState &= ~ushBitMask;
   if(!bGetFzzSignalTimeOutState(cFZZ_WHLPLS_CNT_TIMEOUT)){
    Dem_SetEventStatus( Dem_DTC_0xc12287, DEM_EVENT_STATUS_PASSED);
   }
   if(!bGetFzzSignalTimeOutState(cFZZ_IGN_VEH_STAT_TIMEOUT)){
    Dem_SetEventStatus( Dem_DTC_0xc16887, DEM_EVENT_STATUS_PASSED);
   }
   if(!bGetFzzSignalTimeOutState(cFZZ_PN14_STAT_TIMEOUT) ){
    Dem_SetEventStatus( Dem_DTC_0xc14187, DEM_EVENT_STATUS_PASSED);
   }
   if( !bGetFzzSignalTimeOutState(cFZZ_IC_BASIC_INFO_TIMEOUT) && !bGetFzzSignalTimeOutState(cFZZ_IC_DATE_TIME_TIMEOUT) && !bGetFzzSignalTimeOutState(cFZZ_IC_SETTINGS_TIMEOUT) ){
    Dem_SetEventStatus( Dem_DTC_0xc15587, DEM_EVENT_STATUS_PASSED);
   }
   if( !bGetFzzSignalTimeOutState(cFZZ_ENG_CTRL_TIMEOUT) ){
    Dem_SetEventStatus( Dem_DTC_0xc10087, DEM_EVENT_STATUS_PASSED);
   }

}

void SetFzzSignalTimeOutState(uint16 ushBitMask){
    ushFzzCanSignalTimeOutState |= ushBitMask;

}

void SetFzzState4MM(uint8 state){
   ucFzzState4MessageMemory=state;
}

void SetGlobWarnState4MM(uint8 state){
   ucGlobWarnState4MessageMemory=state;
}

static boolean bGetFzzSignalTimeOutState(uint16 ushBitMask){
   return (boolean) ((ushFzzCanSignalTimeOutState & ushBitMask) != 0 );
}

uint8 GetFzzState4MM(void){
   return ucFzzState4MessageMemory;
}

uint8 GetGlobWarnState4MM(void){
   return ucGlobWarnState4MessageMemory;
}

uint8  bGetABSSignalDTCActive(void){
  uint8 ucEventStatus0, ucEventStatus1, ucEventStatus2, ucEventStatus3, ucEventStatus4;

  Dem_GetEventStatus(Dem_DTC_0xc12287, &ucEventStatus0);
   Dem_GetEventStatus(Dem_DTC_0xd41008, &ucEventStatus1);
   Dem_GetEventStatus(Dem_DTC_0xd41108, &ucEventStatus2);
   Dem_GetEventStatus(Dem_DTC_0xd41208, &ucEventStatus3);
   Dem_GetEventStatus(Dem_DTC_0xd41208, &ucEventStatus4);

  if((ucEventStatus0 == DEM_EVENT_STATUS_PASSED) &&
    (ucEventStatus1 == DEM_EVENT_STATUS_PASSED) &&
    (ucEventStatus2 == DEM_EVENT_STATUS_PASSED) &&
    (ucEventStatus3 == DEM_EVENT_STATUS_PASSED) &&
    (ucEventStatus4 == DEM_EVENT_STATUS_PASSED)){
    return (uint8)FALSE;
  }
  else
  {
    return (uint8)TRUE;
  }
}

uint8  bGetKl30HighDTCActive(void){
  uint8 ucEventStatus0;

   Dem_GetEventStatus(Dem_DTC_0xa10e00, &ucEventStatus0);

  if(ucEventStatus0 == DEM_EVENT_STATUS_PASSED){
    return (uint8)FALSE;
  }
  else
  {
    return (uint8)TRUE;
  }
}

uint8  bGetKl30LowDTCActive(void){
  uint8 ucEventStatus0;

  Dem_GetEventStatus(Dem_DTC_0xa10d00, &ucEventStatus0);

  if(ucEventStatus0 == DEM_EVENT_STATUS_PASSED){
    return (uint8)FALSE;
  }
  else
  {
    return (uint8)TRUE;
  }
}

uint8  bGetPN14SupbatHighDTCActive(void){
  uint8 ucEventStatus0;

   Dem_GetEventStatus(Dem_DTC_0xa10b00, &ucEventStatus0);

  if(ucEventStatus0 == DEM_EVENT_STATUS_PASSED){
    return (uint8)FALSE;
  }
  else
  {
    return (uint8)TRUE;
  }
}

uint8  bGetPN14SupbatLowDTCActive(void){
  uint8 ucEventStatus0;

  Dem_GetEventStatus(Dem_DTC_0xa10a00, &ucEventStatus0);

  if(ucEventStatus0 == DEM_EVENT_STATUS_PASSED){
    return (uint8)FALSE;
  }
  else
  {
    return (uint8)TRUE;
  }
}
