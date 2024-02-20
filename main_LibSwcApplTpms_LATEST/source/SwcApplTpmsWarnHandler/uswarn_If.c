

#include "Platform_Types.h"
#include "global.h"
#include "uswarn_ifx.h"
#include "HMI_handlerX.h"
#include "USWarn.h"
#include "WallocX.h"
#include "filling_detection.h"
#include "state_fdX.h"

void UpdateDAGsOldOff(void)
{
   updateHoldOff4Pmin();
   updateHoldOffWarning();
}

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
  pRefMinRelFA = GETucPcalMinVaRelativCodOfRam();
  pRefMinRelRA = GETucPcalMinHaRelativCodOfRam();
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

 uint8 Getui8AtmosphericP(void)
{
  return (uc1Barc );
}
