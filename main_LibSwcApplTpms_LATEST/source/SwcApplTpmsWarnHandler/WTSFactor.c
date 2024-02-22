#include "global.h"
#include "uswarn.h"
#include "WnTypePar.h"
#include "USWTime.h"

#define ucPreSoftRangeInMBar (unsigned char) 100
#define ucPreSoftRange (unsigned char)  (ucPreSoftRangeInMBar/ucPResInMBarc)

uint8 bSoftFactor( struct LocalWarnDat *ptLWD, uint8 ucWarnCfg)
{
  uint8 ucPCompare, ucPCompareLowest, ucRet;
  uint16 curTinK;

  curTinK = (uint16) ptLWD->tHFD.tHF.scTWE + ush273Kelvinc;

  if ((uint8) 100 > tDAG_PPara .ui8_PERCENT_SOFT)
  {
    ucPCompare = ucPfT((ptLWD->tSD.ushMSoll), curTinK);
    ucPCompare -= (uint8) (((uint16) (tDAG_PPara .ui8_PERCENT_SOFT ) * ucPCompare) / 100);
  }
  else
  {
    ucPCompare = (uint8) 0;
  }

  if ((uint8) 100 > tDAG_PPara .ui8_PERCENT_HARD)
  {
    ucPCompareLowest = ptLWD ->tSD .ucPSoll;
    ucPCompareLowest -= (uint8) (((uint16) (tDAG_PPara .ui8_PERCENT_HARD  ) * ucPCompareLowest) / 100);
   }
  else
  {
    ucPCompareLowest = (uint8) 0;
  }

  ucPCompare = (ucPCompare > ucPCompareLowest) ? ucPCompare:ucPCompareLowest;

  if (cSOFT_WARNING <= GETushWarnstatus1WN())
  {
    ucPCompare += ucPreSoftRange;
  }

  if (cDP_COMP_LIMIT < ptLWD ->tSD .ucPSoll)
  {
    ptLWD->ucCurWarnLevel = (ucPCompare  < (ptLWD ->tSD .ucPSoll - cDP_COMP_LIMIT)) ? ucPCompare:(ptLWD ->tSD .ucPSoll - cDP_COMP_LIMIT);
  }
  else
  {
    ptLWD->ucCurWarnLevel = (ucPCompare  < ptLWD ->tSD .ucPSoll) ? ucPCompare:ptLWD ->tSD .ucPSoll;
  }

  if (ucGetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucSFactorIxc) == 0)
  {
    if ( (ptLWD->tHFD.tHF.ucP < ucPCompare) && (ptLWD ->tHFD .tHF .ucP  < (ptLWD ->tSD .ucPSoll - cDP_COMP_LIMIT)))
      ucRet = ucSetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucSFactorIxc);
    else
    {
      ucRet = 0;
       ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucSFactorIxc);
     }
  }
  else
  {
     if ((ui8SWTimerExpired() > 0) || ( ushWarnOutTM != cNORMAL ))
    {
      ucPCompare = ptLWD ->tSD .ucPSoll ;
      ucPCompare -= (uint8) (((uint16) (tDAG_PPara .ui8_PERCENT_HARD  ) * ucPCompare) / 100);
       ucPCompare += cDP_COMP_LIMIT;
       if (ptLWD->tHFD.tHF.ucP >= ucPCompare )
      {
        ucPCompare = ucPfT((uint16) (ptLWD->tSD.ushMSoll - ushMIso(ucDP_TOLERANCEc, ptLWD->tSD.scTSoll )), curTinK) ;
        if (ptLWD->tHFD.tHF.ucP > ucPCompare )
         {
          ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucSFactorIxc);
          ucRet = 0;
        }
        else
          ucRet = ucSetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucSFactorIxc);
       }
      else
        ucRet = ucSetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucSFactorIxc);
     }
    else
    {
      if ( (ptLWD->tHFD.tHF.ucP < ucPCompare) && (ptLWD ->tHFD .tHF .ucP  < (ptLWD ->tSD .ucPSoll - cDP_COMP_LIMIT)))
        ucRet = ucSetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucSFactorIxc);
       else
      {
        ucRet = 0;
          ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucSFactorIxc);
       }
    }
  }
   ucPCompare = ptLWD ->tSD .ucPSoll ;
  ucPCompare -= (uint8) (((uint16) (tDAG_PPara .ui8_PERCENT_HARD  ) * ucPCompare) / 100);
   ucPCompare += cDP_COMP_LIMIT;
   ucPCompareLowest = ucPfT((uint16) (ptLWD->tSD.ushMSoll - ushMIso(ucDP_TOLERANCEc, ptLWD->tSD.scTSoll )), curTinK) ;
  ptLWD ->ucResetLvl = (ucPCompare < ucPCompareLowest)  ? ucPCompareLowest:ucPCompare;
  return(ucRet);
}

