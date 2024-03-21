

#include "LegacyWD.h"
#include "RH850F1L_dvf.h"
#ifdef TestPin4WD
#include "CtCdHufTPMSrfd.h"
#endif

void ShowWDTrigger(void){
#ifdef TestPin4WD
  static uint8 ui8Ct;

  ui8Ct++;
  if(ui8Ct&0x01)
    TP3 (1);
  else
    TP3 (0);
#endif
}

void TriggerLegacyWD1(void){

  WDTA1.WDTE = (uint8) 0xAC;
}

void InitLegacyWD1(void){
  WDTA1.MD = (uint8) 0x77;
   WDTA1.WDTE = (uint8) 0xAC;
 }

void TriggerLegacyWD0(void){
#if 1
   WDTA0.WDTE = (uint8) 0xAC;
   ShowWDTrigger();
#endif
}

void InitLegacyWD0(void){
#if 1
#ifdef WDTime4sec
  WDTA0.MD = (uint8) 0x47;
#else
  WDTA0.MD = (uint8) 0x07;
#endif
  WDTA0.WDTE = (uint8) 0xAC;
   ShowWDTrigger();
#endif
}
