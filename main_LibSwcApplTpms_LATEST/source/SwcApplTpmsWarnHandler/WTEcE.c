#include "global.h"
#include "uswarn.h"
#include "WnTypePar.h"
#include "USWTime.h"

uint8 bEcE( struct LocalWarnDat *ptLWD, uint8 ucWarnCfg)
{
  uint8 ucPCompare, ucRet;
  uint16 ushHelp;

  ushHelp = (uint16) ptLWD->tHFD.tHF.scTWE + ush273Kelvinc;
  ucPCompare = ucPfT((ptLWD->tSD.ushMSoll), ushHelp);
  ucPCompare -= (uint8) (((uint16) (tDAG_PPara .ui8_PERCENT_HARD) * ucPCompare) / 100);

  if (ucPCompare > (ptLWD ->tSD .ucPSoll - cDP_COMP_LIMIT) )
    ucPCompare = (ptLWD ->tSD .ucPSoll - cDP_COMP_LIMIT);

  ptLWD->ucCurWarnLevel = ucPCompare;

  if (ucGetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucEcEIxc) == 1)
  {
      if ((ui8SWTimerExpired() > 0) || ( ushWarnOutTM != cNORMAL ))
      {
         ucPCompare += ucHWResetHyst ;
       }
    if (( ptLWD ->tHFD .tHF .ucP  > ucPCompare ) || ( ptLWD ->tHFD .tHF .ucP  > (ptLWD ->tSD .ucPSoll - (cDP_COMP_LIMIT - ucHWResetHyst)) ))
    {
      ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucEcEIxc);
      ucRet = 0;
    }
    else
      ucRet = ucSetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucEcEIxc);;
   }
  else
  {
    if (ptLWD->tHFD.tHF.ucP < ucPCompare)
    {
      ucRet = ucSetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucEcEIxc);
    }
    else
    {
      ucRet = 0;
       ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucEcEIxc);
     }
  }

  return(ucRet);
}

