/*
*(c) Huf Electronics GmbH     ENTS4     05/2015
*================================================================================================
*
* $Archive: /MFA2/WARN/WTSFactor.c $
*
* file status:   under construction
*
*------------------------------------------------------------------------------------------------
*
* author:        Peter Brand                Huf Electronics GmbH
*                A. Schubert                Huf Electronics GmbH
*
* intials:       pb
*                as
*
*
* Modul Description
*
*
* Global description:
* Purpose:
* realization of one warntype
*
*
* Modul Modification
*
*
* 2     18.05.15    as
* MFA2 adaptation + refactoring
*
* 1     18.05.07 13:51 pb
* warning type file seperated
*/
/**************************************************************************************************
* Declaration
*/
/*
* Include
*/

#include "global.h" /* cSumWE */
#include "uswarn.h"
#include "WnTypePar.h"
#include "USWTime.h"

#define ucPreSoftRangeInMBar (unsigned char) 100
#define ucPreSoftRange (unsigned char)  (ucPreSoftRangeInMBar/ucPResInMBarc)


/**************************************************************************************************
*Prototypes
*/

/**************************************************************************************************
*Data
*/



/**********************************************************************************/

/**************************************************************************************************
* Implementation
*/

/**************************************************************************************************
*functions
*/
/*
WTSFactor
*/
/*
Function bSoftX(..)  [old warn type HardVT changed 2 bSoftFactorX]
*/
/*
Description
*/
/*
Purpose:                       generation of pmin concerning the us warningalgorithem spec
-----------------------------------------------------------------------------------------------
Input:                         SFactor warn type bSoftFactor(old)

Output:                        1 warning type = active
0 warning type = inactive
------------------------------------------------------------------------------------------------
*/

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
    ucPCompareLowest -= (uint8) (((uint16) (tDAG_PPara .ui8_PERCENT_HARD  ) * ucPCompareLowest) / 100); // soft warning drop point   20% below Pref(rel)
  }
  else
  {
    ucPCompareLowest = (uint8) 0;
  }

  ucPCompare = (ucPCompare > ucPCompareLowest) ? ucPCompare:ucPCompareLowest; 

  if (cSOFT_WARNING <= GETushWarnstatus1WN()) /*alt: == NEU<=CRS_1211_080_004*/ 
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
      ucRet = 0;  // is not set and cannot be set
      ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucSFactorIxc);  // for reset the time filter
    }
  }
  else
  {  // warning is set, try reset:
    if ((ui8SWTimerExpired() > 0) || ( ushWarnOutTM != cNORMAL ))
    {
      ucPCompare = ptLWD ->tSD .ucPSoll ; 
      ucPCompare -= (uint8) (((uint16) (tDAG_PPara .ui8_PERCENT_HARD  ) * ucPCompare) / 100); // soft warning drop point   20% below Pref(rel)
      ucPCompare += cDP_COMP_LIMIT; // refer to OIL #292
      if (ptLWD->tHFD.tHF.ucP >= ucPCompare )
      {
        ucPCompare = ucPfT((uint16) (ptLWD->tSD.ushMSoll - ushMIso(ucDP_TOLERANCEc, ptLWD->tSD.scTSoll )), curTinK) ;
        if (ptLWD->tHFD.tHF.ucP > ucPCompare )  // #oil129 now compare on '>' no moore '>='
        {
          ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucSFactorIxc);
          ucRet = 0;
        }
        else
          ucRet = ucSetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucSFactorIxc);  // is set and remains set, but set again to restart timer in case it was reset by POR
      }
      else
        ucRet = ucSetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucSFactorIxc);  // is set and remains set, but set again to restart timer in case it was reset by POR
    }
    else
    {  
      if ( (ptLWD->tHFD.tHF.ucP < ucPCompare) && (ptLWD ->tHFD .tHF .ucP  < (ptLWD ->tSD .ucPSoll - cDP_COMP_LIMIT)))
        ucRet = ucSetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucSFactorIxc); // set but timer not yet expired
      else 
      {
        ucRet = 0;  // // clear immediate if timer is not yet expired (OIL #???)
        ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucSFactorIxc);  //  reset the time filter
      }    
    }
  }

  // generate reset level as debug value for Mr.Kiesewetter:    START
  ucPCompare = ptLWD ->tSD .ucPSoll ; 
  ucPCompare -= (uint8) (((uint16) (tDAG_PPara .ui8_PERCENT_HARD  ) * ucPCompare) / 100); // soft warning drop point   20% below Pref(rel)
  ucPCompare += cDP_COMP_LIMIT; // refer to OIL #292
  ucPCompareLowest = ucPfT((uint16) (ptLWD->tSD.ushMSoll - ushMIso(ucDP_TOLERANCEc, ptLWD->tSD.scTSoll )), curTinK) ;
  ptLWD ->ucResetLvl = (ucPCompare < ucPCompareLowest)  ? ucPCompareLowest:ucPCompare;
  // generate reset level as debug value for Mr.Kiesewetter:    END

  return(ucRet);
}


