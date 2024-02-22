#include "uswarn.h"
#include "WnTypePar.h"
#include "USWTime.h"

uint8 bPMin( struct LocalWarnDat *ptLWD, uint8 ucWarnCfg )
{
   uint8 ucPCompare, ucRet;
   ucPCompare = tDAG_PPara .ui8_P_MIN_TIRE ;

   ptLWD->ucCurWarnLevel = ucPCompare;
   if (ptLWD->tHFD.tHF.ucP < ucPCompare)
   {
      ucRet = ucSetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucPMinIxc);
   }
   else
   {
      if (ucGetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucPMinIxc) == 1)
      {
         if ((ui8SWTimerExpired() > 0) || ( ushWarnOutTM != cNORMAL ))
         {
            ucPCompare += ucHWResetHyst ;
          }
         if (ptLWD->tHFD.tHF.ucP > ucPCompare)
         {
            ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucPMinIxc);
            ucRet = 0;
         }
         else
         {
            ucRet = 1;
         }
      }
      else
      {
         ucRet = 0;
      }
   }
   return(ucRet);
}
