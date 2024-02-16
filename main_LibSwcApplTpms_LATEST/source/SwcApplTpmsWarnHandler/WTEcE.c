/*
*(c) Huf Electronics GmbH     ENTS4     05/2015
*================================================================================================
*
* $Archive: /MFA2/WARN/WTEcE.c $
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
* realization of hard warning warntype concerning DAG's 'TPMS Logic  PAL2 V1.2' document
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
//#include "uswarn_Ifx.h" /* types for warn algo 2 MISRA */
#include "global.h" /* cSumWE */
#include "uswarn.h"
#include "WnTypePar.h"
#include "USWTime.h"


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
WTEcE
*/
/*
Function bEcE(..)
*/
/*
Description
*/
/*
Purpose:                       generation of pEcE R64 concerning the us warningalgorithem spec
-----------------------------------------------------------------------------------------------
Input:

Output:                        1 warning type = active
0 warning type = inactive
------------------------------------------------------------------------------------------------
*/

uint8 bEcE( struct LocalWarnDat *ptLWD, uint8 ucWarnCfg)
{
  uint8 ucPCompare, ucRet;
  uint16 ushHelp;

  ushHelp = (uint16) ptLWD->tHFD.tHF.scTWE + ush273Kelvinc;
  ucPCompare = ucPfT((ptLWD->tSD.ushMSoll), ushHelp);
  ucPCompare -= (uint8) (((uint16) (tDAG_PPara .ui8_PERCENT_HARD) * ucPCompare) / 100);  /* calculate EU factor deduction */

  if (ucPCompare > (ptLWD ->tSD .ucPSoll - cDP_COMP_LIMIT) )
    ucPCompare = (ptLWD ->tSD .ucPSoll - cDP_COMP_LIMIT);

  ptLWD->ucCurWarnLevel = ucPCompare;

  if (ucGetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucEcEIxc) == 1)  /* ECE set? */
  {
		if ((ui8SWTimerExpired() > 0) || ( ushWarnOutTM != cNORMAL )) /*CRS_1211_080_001 refer to TPMS Logic PAL2 V1.4.docx chapter 6.5 "pressure > hard-threshold  (without 5 kPa) "*/
		{    
			ucPCompare += ucHWResetHyst ; // refer to TPMS Logic PAL2 V1.4.docx chapter 6.5 "pressure > hard-threshold + 5 kPa"
		}
    if (( ptLWD ->tHFD .tHF .ucP  > ucPCompare ) || ( ptLWD ->tHFD .tHF .ucP  > (ptLWD ->tSD .ucPSoll - (cDP_COMP_LIMIT - ucHWResetHyst)) ))
    {
      ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucEcEIxc);
      ucRet = 0;
    }
    else
      ucRet = ucSetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucEcEIxc);;  // is set and remains, set again for timer might standstill due to POR
  }
  else
  {
    if (ptLWD->tHFD.tHF.ucP < ucPCompare)		/* conventional ece hard warning (speed independent) */
    {
      ucRet = ucSetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucEcEIxc); /* set ECE warning */
    }
    else
    {
      ucRet = 0;  // not yet set and cannot be set now
      ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucEcEIxc); // for resetting the time filter
    }
  }

  return(ucRet);
}


