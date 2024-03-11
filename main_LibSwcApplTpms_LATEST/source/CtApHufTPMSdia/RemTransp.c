

#include "RemTransp.h"

#define cRemeasure (uint8) 1
#define cTransmissionTriggered (uint8) 2
#define cModeStationary (uint8) 2

RemTranspResulType tResult = {0xFFFFFFFF,0xFF,0xFF,0xFF};
uint8 ui8RoutineActive = (uint8) 0;

void StartRoutine302(uint8 ui8Meffed){
  uint8 i;
  uint8 * p2Result;

  p2Result = (uint8 *) &tResult;

  for(i = 0; i < sizeof(RemTranspResulType ); i++){
    p2Result [i] = (uint8) 0xff;
  }

  if(ui8Meffed < ((uint8) 2)){
    ui8RoutineActive = 1u + ui8Meffed;
  }
  tResult .ui8Method = ui8Meffed;
}

void StopRoutine302(void){
  ui8RoutineActive = 0u;
}

void Check4RemOrTrig(uint32 ui32ID, uint8 ui8P, uint8 ui8T, uint8 ui8TxTrig, uint8 ui8Mode){
  if( 1u == ui8RoutineActive ){
    if  ((cRemeasure == ui8TxTrig) && (cModeStationary == ui8Mode)){
      tResult .ui32ID = ui32ID ;
      tResult .ui8P = ui8P;
      tResult .ui8Temp = ui8T;
      tResult .ui8Method = 0u;
    }
  }
  else if(2u == ui8RoutineActive){
    if(cTransmissionTriggered == ui8TxTrig){
      tResult .ui32ID = ui32ID ;
      tResult .ui8P = ui8P;
      tResult .ui8Temp = ui8T;
      tResult .ui8Method = 1u;
    }
  }
}

RemTranspResulType GETtRemTranspResult(void){
  return tResult;
}

uint8 GETui8RemTranspActive(void){
  return ((ui8RoutineActive>0) ? 1:0);
}
