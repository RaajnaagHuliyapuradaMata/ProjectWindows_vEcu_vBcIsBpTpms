/*
(c)  Electronics GmbH     BEE1     08/2016
================================================================================================

file name:     SensorLoBat.c

file status:   fine

------------------------------------------------------------------------------------------------

author:        Peter Brand                 Electronics GmbH

intials:       pb

Purpose:
sensor low battery diagnostice logic  according to TPMS Logic  PAL2 V1.5


*/
/*******************************************************************************
Declaration
*/

/*******************************************************************************
Include
*/

#include "LegacyWD.h"
#include "RH850F1L_dvf.h"
#ifdef TestPin4WD
#include "CtCdHufTPMSrfd.h" // for testpoints - only for debug
#endif

/*******************************************************************************
Macros
*/

/*******************************************************************************
Data
*/

/*******************************************************************************
prototipicos locale
*/

/*******************************************************************************
Implementation
*/

/*******************************************************************************
private functions
*/
void ShowWDTrigger(void) // display watchdog trigger on alternating testpin 3 (pin48)
{
#ifdef TestPin4WD
  static uint8 ui8Ct;

  ui8Ct++;
  if (ui8Ct&0x01)
    TP3 (1);
  else
    TP3 (0);
#endif
}

/*******************************************************************************
public functions
*/

void TriggerLegacyWD1(void)
{

  WDTA1.WDTE = (uint8) 0xAC;
}

// InitLegacyWD purpose:
// initialize watchdog 0 as none windowed reset generator w/ a typical 273msec TO
void InitLegacyWD1(void)
{
  WDTA1.MD = (uint8) 0x77;  // ToTime = 2^16/240kHz, no 75% IR, generate reset, window = 100%
  WDTA1.WDTE = (uint8) 0xAC;// after this mode should be active mode 
}

void TriggerLegacyWD0(void)
{
#if 1
   WDTA0.WDTE = (uint8) 0xAC;
   ShowWDTrigger();
#endif
}

// InitLegacyWD purpose:
// initialize watchdog 0 as none windowed reset generator w/ a typical 3,662109375sec TO
void InitLegacyWD0(void)
{
#if 1
#ifdef WDTime4sec
  WDTA0.MD = (uint8) 0x47;  // ToTime = 273msec ((2^9 x 128)/240kHz), no 75% IR, generate reset, window = 100% 
#else
  WDTA0.MD = (uint8) 0x07;  // ToTime = 4,369sec) ((2^9 x 128)/240kHz), no 75% IR, generate reset, window = 100% 
#endif
  WDTA0.WDTE = (uint8) 0xAC;// after this mode should be active mode 
  ShowWDTrigger();
#endif
}
/******************************************************************************/