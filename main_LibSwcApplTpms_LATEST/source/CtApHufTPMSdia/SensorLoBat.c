

#include "SensorLoBat.h"
#include "WallocX.h"
#include "state_fdX.h"
#include "Rte_Type.h"
#include "Dem.h"
 #include "Rte_CtApHufTPMSdia.h"
#include "tel_statisticX.h"

#define LB_LIMIT (uint8) 15
#define cLoBatRxInCurCycle (uint8) 0xFF
#define cMaxRxOkEvents (uint8) 10
#define cNOK ((uint8) 1)
#define cOK ((uint8) 0x80)
#define cDtcWasCleared ((uint8) 0)

 uint8 ui8SensorBatCtrl[cMAXWU4BATINFO];

extern DT_tEnvData tEnvDataToSend;
 extern uint8 GETui8LastSensorTemperature(uint8 idx);
 extern uint32 GETulKmStand4AutoCAL(void);

static void ClearBatInfo(BaType * pt2BatInfo);
static uint16 GETui16Odometer(void);
static uint8 GETui8AmbienTemp(void);
static uint8 ui8Check4AllSensorCounts0(void);
static void PUTtSensorBatInfo2NVM(void);
static uint8 ui8All4SensorsOK(uint8 idx);

static void ClearBatInfo(BaType * pt2BatInfo){
  uint8 i;

  for(i = 0; i < sizeof (BaType ) ; i++){
    *(((uint8 *) pt2BatInfo) + i) = (uint8) 0;
  }
}

static uint16 GETui16Odometer(void){
    uint32 ui32OdoVal;
    uint16 ui16RetVal = 0;
    uint8* p2RetVal = (uint8 *) &ui16RetVal;

    ui32OdoVal = GETulKmStand4AutoCAL() >> 4;

    p2RetVal[0] = (uint8)(ui32OdoVal>>8);
      p2RetVal[1] = ((uint8)ui32OdoVal);

    return (ui16RetVal );
}

static uint8 GETui8AmbienTemp(void){
  return (tEnvDataToSend .ucTempOut + 50u);
}

 static uint8 ui8Check4AllSensorCounts0(void){
  uint8 i;
  BaType tbatinfo;

  for( i = 0; i < cMAXWU4BATINFO ; i++){
    tbatinfo = GETtSensorBatInfOfRam (i);
    if( tbatinfo.ui8Count > ((uint8) 0)){
      break;
    }
  }

  if(cMAXWU4BATINFO == i){
    return ((uint8) 0xFF);
  }
  else{
    return ((uint8) 0);
  }
}

 static uint8 ui8All4SensorsOK(uint8 idx){
  uint8 i;
  BaType tbatinfo;

  for( i = 0; i < cMAXWU4BATINFO ; i++){
    if(i == idx)
      continue;
    else{
      tbatinfo = GETtSensorBatInfOfRam (i);
      if( cOK != tbatinfo.ui8Status ){
        break;
      }
    }
  }

  if(cMAXWU4BATINFO == i){
    return ((uint8) 0xFF);
  }
  else{
    return ((uint8) 0);
  }
}
 BaType GETtSensorBatInfOfRam(uint8 idx){
  BaType tLocalBatInfo;

  if(cMAXWU4BATINFO > idx){
    return ( *((BaType*) ((uint8 *)&Rte_Pim_Pim_tDiagNvMBlock2()->tSensorBatInfo + (idx * sizeof (BaType )))) );
  }
  else{
    ClearBatInfo (&tLocalBatInfo);
    return (tLocalBatInfo );
  }

}

void PUTtSensorBatInfo2Ram(BaType* pt2x, uint8 idx){
  if(cMAXWU4BATINFO > idx){
    *((BaType*) ((uint8 *)&Rte_Pim_Pim_tDiagNvMBlock2()->tSensorBatInfo + (idx * sizeof (BaType )))) = (*pt2x);
  }
}

static void PUTtSensorBatInfo2NVM(void){
  NvM_RequestResultType ErrorStatus;

  Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSdia_Pim_tDiagNvMBlock2_GetErrorStatus(&ErrorStatus);
  if(ErrorStatus  != NVM_REQ_PENDING){
    Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSdia_Pim_tDiagNvMBlock2_SetRamBlockStatus(TRUE);
  }
}

  void CheckSensorLoBat(uint8 idx, uint8 ui8BatteryStatus, boolean bForceInit){
  BaType tLocalBatInfo;
  uint8 ui8Update;
  boolean bStoreAmbientVal;

  ui8Update = FALSE ;
  bStoreAmbientVal = FALSE ;

  if(( cMaxLR > idx ) && !(((uint8) 0 == ui8BatteryStatus) || ((uint8) 11 < ui8BatteryStatus))){
    tLocalBatInfo = GETtSensorBatInfOfRam (idx);

    if( (ulGetID(idx) != tLocalBatInfo .ui32ID) || bForceInit ){
      tLocalBatInfo .ui8Count = (uint8) 0;
      tLocalBatInfo .ui32ID =  ulGetID(idx);

      tLocalBatInfo .ui16Odometer = 0xFFFF;
      tLocalBatInfo. ui8SensorTemp = 0xFF;
      tLocalBatInfo. ui8AmbienTemp = 0xFF;

      ui8Update = TRUE ;
    }

    if(ui8BatteryStatus > 1){
      if((tLocalBatInfo .ui8LifeInPercent != ui8BatteryStatus) && !((11 == ui8BatteryStatus) && (10 == tLocalBatInfo .ui8LifeInPercent))){
        ui8Update = TRUE ;
        tLocalBatInfo .ui8LifeInPercent = ( ui8BatteryStatus < 11) ? ui8BatteryStatus:10;
      }
      if((cDtcWasCleared == tLocalBatInfo .ui8Status) && (!bForceInit)){
        ui8Update = TRUE ;
        tLocalBatInfo .ui8Status = cOK;
        if(ui8All4SensorsOK (idx) > ((uint8) 0)){

          Dem_SetEventStatus( Dem_DTC_0x559916, DEM_EVENT_STATUS_PASSED);
        }
      }
      else{
            if(bForceInit){
               if(ui8All4SensorsOK (idx) > ((uint8) 0)){
                  Dem_SetEventStatus( Dem_DTC_0x559916, DEM_EVENT_STATUS_PASSED);
               }
            }
        tLocalBatInfo .ui8Status = cOK;
      }

      if(cLoBatRxInCurCycle != ui8SensorBatCtrl [idx] ){
        if(cMaxRxOkEvents > ui8SensorBatCtrl [idx]){
          ui8SensorBatCtrl [idx]++ ;
          if(cMaxRxOkEvents == ui8SensorBatCtrl [idx]){
            if((uint8) 0 < tLocalBatInfo .ui8Count){
              ui8Update = TRUE ;
              tLocalBatInfo .ui8Count--;
              if((uint8) 0 == tLocalBatInfo .ui8Count){
                PUTtSensorBatInfo2Ram ( &tLocalBatInfo , idx);
                 if(ui8Check4AllSensorCounts0 () > 0){
                  Dem_SetEventStatus( Dem_DTC_0x559916, DEM_EVENT_STATUS_PASSED);
                }
              }
            }
          }
        }
      }
    }
    else{
      if(cLoBatRxInCurCycle != ui8SensorBatCtrl [idx]  ){
        ui8SensorBatCtrl [idx] = cLoBatRxInCurCycle;
        tLocalBatInfo .ui8Status = cNOK;
         tLocalBatInfo .ui8LifeInPercent = (uint8) 1;
        ui8Update = TRUE;
        if(tLocalBatInfo .ui8Count < LB_LIMIT ){
          tLocalBatInfo .ui8Count ++;
          bStoreAmbientVal = TRUE ;
          if(LB_LIMIT == tLocalBatInfo .ui8Count){
            Dem_SetEventStatus( Dem_DTC_0x559916, DEM_EVENT_STATUS_FAILED);
          }
        }
      }
      if((uint8) 1 != tLocalBatInfo .ui8LifeInPercent ){
        tLocalBatInfo .ui8Status = cNOK;
         tLocalBatInfo .ui8LifeInPercent = (uint8) 1;
        ui8Update = TRUE;
      }
    }

    if(TRUE == ui8Update ){

      MakeRoeObsMsg( GETtSensorBatInfOfRam(idx).ui8LifeInPercent, tLocalBatInfo.ui8LifeInPercent, idx);

      if(bStoreAmbientVal){
        tLocalBatInfo .ui16Odometer = GETui16Odometer();
        tLocalBatInfo. ui8SensorTemp = GETui8LastSensorTemperature(idx);
        tLocalBatInfo. ui8AmbienTemp = GETui8AmbienTemp();
      }

      PUTtSensorBatInfo2Ram ( &tLocalBatInfo , idx);
      PUTtSensorBatInfo2NVM();
    }
  }
}

void InitSensorLoBat(void){
  ui8SensorBatCtrl [0] = 0;
  ui8SensorBatCtrl [1] = 0;
  ui8SensorBatCtrl [2] = 0;
  ui8SensorBatCtrl [3] = 0;
}

void ClearAllBatStatCounts(void){
  uint8 i;
  BaType tbatinfo;

  for( i = 0; i < cMAXWU4BATINFO ; i++){
    tbatinfo = GETtSensorBatInfOfRam (i);
    tbatinfo.ui8Status = cDtcWasCleared;
    tbatinfo .ui8Count = 0;
    PUTtSensorBatInfo2Ram ( &tbatinfo , i);
  }

  PUTtSensorBatInfo2NVM ();
}

void PrepareLoBat4Obsolescence(uint8* p2dat){

  uint8 i;
  BaType tbatinfo;

  for( i = 0; i < 4; i++){
    tbatinfo = GETtSensorBatInfOfRam (i);
    if((uint32) 4 < tbatinfo .ui32ID  ){
      if(ucGetSensorState(i) == SENSOR_STATE_MISSING){
        p2dat[1] = 0x00;
       }
      else{
        p2dat[1] = tbatinfo.ui8LifeInPercent;
      }
    }
    else{
      p2dat[1] = 0x0F;
     }

    p2dat[0] = 0;
    p2dat[3] = 1;
    p2dat[2] = 0;
    p2dat[4] = 0;
    p2dat[5] = 0;
    p2dat+=6;
  }
}

void ClearAllParaApartId(void){
  uint8 i;
  BaType tbatinfo;

  for( i = 0; i < cMAXWU4BATINFO ; i++){
    tbatinfo = GETtSensorBatInfOfRam (i);
    tbatinfo.ui8Status = cOK;
    tbatinfo .ui8Count = 0;
    tbatinfo.ui16Odometer = 0xFFFF;
    tbatinfo .ui8AmbienTemp  = 0xFF;
    tbatinfo .ui8SensorTemp = 0xFF;
    tbatinfo.ui8LifeInPercent = 0;
    PUTtSensorBatInfo2Ram ( &tbatinfo , i);
  }

  PUTtSensorBatInfo2NVM ();
}
