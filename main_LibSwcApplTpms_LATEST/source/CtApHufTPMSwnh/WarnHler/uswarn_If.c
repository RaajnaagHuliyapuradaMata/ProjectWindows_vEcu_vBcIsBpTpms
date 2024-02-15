/*
(c)  Electronics GmbH     BEE1     11/2015
================================================================================================

file name:     DAG_TVWarn.c

file status:   fine

------------------------------------------------------------------------------------------------

author:        Peter Brand                 Electronics GmbH

intials:       pb

Purpose:
used interfaces all combined in one - and be aware used means used by warnlogic itself nothing else
THIS IS NOT A PROVIDED INTERFACE - THIS IS NOT A PROVIDED INTERFACE - THIS IS NOT A PROVIDED INTERFACE


*/


/************************************************************************************************************
 *                                             include
 ************************************************************************************************************/
#include "Platform_Types.h" /*BSW types.h*/ 
#include "global.h"
#include "uswarn_ifx.h"
#include "HMI_handlerX.h"
#include "USWarn.h"
#include "WallocX.h"
#include "filling_detection.h"
#include "state_fdX.h"

/************************************************************************************************************
 *                                             define
 ************************************************************************************************************/



/************************************************************************************************************
 *                                            typedef
 ************************************************************************************************************/



/************************************************************************************************************
 *                                    data (Modulglobal) - ROM
 ************************************************************************************************************/


/************************************************************************************************************
 *                                    data (Modulglobal) - RAM
 ************************************************************************************************************/



/************************************************************************************************************
 *                                       data (global) - ROM
 ************************************************************************************************************/



/************************************************************************************************************
 *                                       data (global) - RAM
 ************************************************************************************************************/



/***********************************************************************************************************
 *                                     prototype (private function)
 ***********************************************************************************************************/



/************************************************************************************************************
 *                                     prototype (public function)
 ************************************************************************************************************/



/************************************************************************************************************
 *                                             macro
 ************************************************************************************************************/


void UpdateDAGsOldOff(void)
{
	updateHoldOff4Pmin(); /*CRS_1211_010_020*/
	updateHoldOffWarning();
}

// GetRatValOfId purpose:
// provides rated pressure/temperature and quotient of both from a sensor in history column[0..3] to p2RatVal
void GetRatValOfId(uint8 uiHistCol, struct SollDat * p2RatVal)
{
  uint8 ui8WP,ui8PFA,ui8PRA;
  sint8 i8TFA,i8TRA;
  
  ui8WP = GETucWPorPWPofHistCol(uiHistCol);

  ui8PFA = GETucPrefFront();
  ui8PRA = GETucPrefRear();
  i8TFA = GETscTref();
  i8TRA = GETscTref();

  switch (ui8WP)
  {
  case cWheelPos_FL :
  case cWheelPos_FR :
    p2RatVal->ucPSoll = ui8PFA;
    p2RatVal->scTSoll = i8TFA ;
    break;
  case cWheelPos_RL :
  case cWheelPos_RR :
    p2RatVal->ucPSoll = ui8PRA;
    p2RatVal->scTSoll = i8TRA;
    break;
  default:
    p2RatVal->ucPSoll = (ui8PRA > ui8PFA) ? ui8PFA:ui8PRA;
    p2RatVal->scTSoll = (ui8PRA > ui8PFA) ? i8TFA:i8TRA;
    break;
  }

  p2RatVal ->ushMSoll = ui16MIsoRel (p2RatVal->ucPSoll,p2RatVal->scTSoll);
}

const uint8 * GETpui82SysWP(void)
{
  return ((const uint8 *) GETpucStartAdrWPorPWP());
}

uint8 Getui8PrefMinOfId(uint8 histCol)
{
  uint8 wp, pRefMinRelFA, pRefMinRelRA, pRefMinRel;
    
  wp = GETucWPorPWPofHistCol(histCol);
  pRefMinRelFA = GETucPcalMinVaRelativCodOfRam(); /*CRS_1211_130_268 relativ pressure always*/
  pRefMinRelRA = GETucPcalMinHaRelativCodOfRam(); /*CRS_1211_130_268 relativ pressure always*/
  pRefMinRel = 0;

  switch (wp)
  {
  case cWheelPos_FL :
  case cWheelPos_FR :
    pRefMinRel = pRefMinRelFA ;
    break;
  case cWheelPos_RL :
  case cWheelPos_RR :
    pRefMinRel = pRefMinRelRA ;
    break;
  default:
    pRefMinRel = (pRefMinRelFA < pRefMinRelRA) ? pRefMinRelFA:pRefMinRelRA;
    break;
  }
 
 return (pRefMinRel);
}

// Getui8AtmosphericP purpose:
// return current atmospheric pressure (default = 1Bar)
// for future use
uint8 Getui8AtmosphericP(void)
{
  return (uc1Barc );
}