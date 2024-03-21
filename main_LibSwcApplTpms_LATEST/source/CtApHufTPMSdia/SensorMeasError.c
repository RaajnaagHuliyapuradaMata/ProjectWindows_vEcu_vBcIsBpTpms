

#define SensorMeasError_C
#include "SensorMeasError.h"
#include "Rte_Type.h"
#include "Dem.h"
#include "tel_statisticX.h"
#include "WallocX.h"
#include "CD_Decoder_X.h"

#define cMaxBaTCt ((uint8) 15)
#define cMaxBadPCt ((uint8) 15)
#define cNull ((uint8) 0)
#define cSensErrorActive ((uint8) 0xFF)

static uint8 ui8BaTempCt[4] = {cNull,cNull,cNull,cNull};
static uint8 ui8BadPressCt[4] = {cNull,cNull,cNull,cNull};
static boolean bNewIDFlag[4] = {FALSE, FALSE, FALSE, FALSE};

extern void Dem_SetEventExData(uint8);

static uint8 GETui8PValid(uint8 ui8AKRawPressure);
static uint8 GETui8TValid(uint8 ui8AKRawTemp);
static boolean bTelTypeHasPT( uint8 ui8TT);

static uint8 GETui8PValid(uint8 ui8AKRawPressure){
  return ((cNull == ui8AKRawPressure) ? cNull:(uint8) 0xFF);
}

static uint8 GETui8TValid(uint8 ui8AKRawTemp){
  return ((cNull == ui8AKRawTemp) ? cNull:(uint8) 0xFF);
}

void ClrMeasError(uint8 ui8HistCol, uint8 ui8ReasonOnly){

  if(((uint8) 4) > ui8HistCol ){
    ui8BaTempCt[ui8HistCol] = cNull;
    ui8BadPressCt[ui8HistCol] = cNull;
    if(ui8ReasonOnly == cNull){
      bNewIDFlag[ui8HistCol] = TRUE;
    }
  }
  else{
    ui8BaTempCt[0] = cNull;
    ui8BadPressCt[0] = cNull;
    ui8BaTempCt[1] = cNull;
    ui8BadPressCt[1] = cNull;
    ui8BaTempCt[2] = cNull;
    ui8BadPressCt[2] = cNull;
    ui8BaTempCt[3] = cNull;
    ui8BadPressCt[3] = cNull;

    if(ui8ReasonOnly == cNull){
      bNewIDFlag[0] = TRUE;
      bNewIDFlag[1] = TRUE;
      bNewIDFlag[2] = TRUE;
      bNewIDFlag[3] = TRUE;
    }
  }

}

void SetMeasError(uint8 ui8HistCol){
  switch (ui8HistCol){
    case 0:
      Dem_SetEventExData( Dem_DTC_0x550196 );
      Dem_SetEventStatus( Dem_DTC_0x550196, DEM_EVENT_STATUS_FAILED);
      break;
    case 1:
      Dem_SetEventExData( Dem_DTC_0x550296 );
      Dem_SetEventStatus( Dem_DTC_0x550296, DEM_EVENT_STATUS_FAILED);
      break;
    case 2:
      Dem_SetEventExData( Dem_DTC_0x550396 );
      Dem_SetEventStatus( Dem_DTC_0x550396, DEM_EVENT_STATUS_FAILED);
      break;
    case 3:
      Dem_SetEventExData( Dem_DTC_0x550496 );
      Dem_SetEventStatus( Dem_DTC_0x550496, DEM_EVENT_STATUS_FAILED);
      break;
    default :
      break;
  }
}

static boolean bMeasErrorActive(uint8 ui8HistCol){
  boolean bRet = FALSE ;
  uint8 ucDtcCode = cNull ;

  switch (ui8HistCol){
    case 0:
      Dem_GetEventFailed ( Dem_DTC_0x550196 , &ucDtcCode );
      break;
    case 1:
      Dem_GetEventFailed ( Dem_DTC_0x550296 , &ucDtcCode );
      break;
    case 2:
      Dem_GetEventFailed ( Dem_DTC_0x550396 , &ucDtcCode );
      break;
    case 3:
      Dem_GetEventFailed ( Dem_DTC_0x550496 , &ucDtcCode );
      break;
    default :
      break;
  }

  if(cNull < ucDtcCode)
    bRet = TRUE ;
  else
    bRet = FALSE ;

  return (bRet);
}

void CheckSensorPnT(uint8 ui8HistCol, uint8 ui8AKRawPressure, uint8 ui8AKRawTemp, boolean bAddCondition, uint8 ui8TelType){

  if((((uint8) 4) > ui8HistCol) && (bAddCondition) && bTelTypeHasPT(ui8TelType)){
    if(cNull == GETui8TValid(ui8AKRawTemp)){
      if(ui8BaTempCt[ui8HistCol] < cMaxBaTCt){
        ui8BaTempCt[ui8HistCol]++;
      }
      if((cMaxBaTCt == ui8BaTempCt[ui8HistCol]) && ((ucGetSensorState(ui8HistCol) == SENSOR_STATE_MISSING) || (SENSOR_STATE_DISTURBED == ucGetSensorState(ui8HistCol)))){
        SetMeasError(ui8HistCol);
        ui8BaTempCt[ui8HistCol] = cSensErrorActive ;
      }
    }
    else{
      ui8BaTempCt[ui8HistCol] = cNull;
    }

    if(cNull == GETui8PValid(ui8AKRawPressure)){
      if(ui8BadPressCt[ui8HistCol] < cMaxBadPCt){
        ui8BadPressCt[ui8HistCol]++;
      }
      if((cMaxBadPCt == ui8BadPressCt[ui8HistCol]) && ((ucGetSensorState(ui8HistCol) == SENSOR_STATE_MISSING) || (SENSOR_STATE_DISTURBED == ucGetSensorState(ui8HistCol)))){
        SetMeasError(ui8HistCol);
        ui8BadPressCt[ui8HistCol] = cSensErrorActive ;
      }
    }
    else{
      ui8BadPressCt[ui8HistCol] = cNull ;
    }
     if( ( bNewIDFlag[ui8HistCol] || (!bMeasErrorActive(ui8HistCol)) ) && ( ui8BadPressCt[ui8HistCol] == cNull) && (ui8BaTempCt[ui8HistCol] == cNull) ){
      bNewIDFlag[ui8HistCol] = FALSE;

      switch (ui8HistCol){
        case 0:
          Dem_SetEventStatus( Dem_DTC_0x550196, DEM_EVENT_STATUS_PASSED);
          break;
        case 1:
          Dem_SetEventStatus( Dem_DTC_0x550296, DEM_EVENT_STATUS_PASSED);
          break;
        case 2:
          Dem_SetEventStatus( Dem_DTC_0x550396, DEM_EVENT_STATUS_PASSED);
          break;
        case 3:
          Dem_SetEventStatus( Dem_DTC_0x550496, DEM_EVENT_STATUS_PASSED);
          break;
        default :
          break;
      }
    }
  }
}

uint8 GetMeasErrorPCt(uint8 ui8HistCol){
  return ui8BadPressCt[ui8HistCol];
}

uint8 GetMeasErrorTCt(uint8 ui8HistCol){
  return ui8BaTempCt[ui8HistCol];
}

boolean bSensorDefect(uint32 ui32ID, uint8 ui8TT, uint8 ui8P, uint8 ui8T){
  uint8 ui8HistCol;
  boolean bRet = FALSE ;

  ui8HistCol = ucGetColOfID( &ui32ID);

  if(bTelTypeHasPT (ui8TT) && ((cNull == ui8P) || (cNull == ui8T ))){
    bRet = TRUE ;
  }
  else if(cMaxLR > ui8HistCol){
    if((cNull < ui8BaTempCt[ui8HistCol]) || (cNull < ui8BadPressCt[ui8HistCol])){
      bRet = TRUE ;
    }
    else if(bMeasErrorActive(ui8HistCol)){
      bRet = TRUE ;
    }
  }

  return (bRet );
}

static boolean bTelTypeHasPT( uint8 ui8TT){
  switch (ui8TT){
  case cTelTypeAK35def:
  case cTelTypeAK35defLF:
  case cTelTypeAK35defLMA:
  case cTelTypeSELPAL:
  case cTelTypeSELPAL1:
    return (TRUE );
  default:
    return (FALSE );
  }
}
