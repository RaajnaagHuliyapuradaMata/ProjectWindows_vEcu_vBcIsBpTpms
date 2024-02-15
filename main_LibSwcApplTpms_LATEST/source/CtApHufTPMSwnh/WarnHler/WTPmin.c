/*
*(c) Huf Electronics GmbH     ENTS4     05/2015
*================================================================================================
*
* $Archive: /MFA2/WARN/WTPmin.c $
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
*
*/
/**************************************************************************************************
* Declaration
*/
/*
* Include
*/
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
/**************************************************************************************************
 * private
 */


/*****************************************************************************
PMin

Function bPMin(..)

Description

Purpose:                       generation of pmin concerning DAG's 'TPMS Logic  PAL2 V1.2' document
-----------------------------------------------------------------------------------------------
Input:                         ucP

Output:                        1 warning type = active
                               0 warning type = inactive

------------------------------------------------------------------------------------------------
*/

uint8 bPMin( struct LocalWarnDat *ptLWD, uint8 ucWarnCfg )
{
	uint8 ucPCompare, ucRet;
	ucPCompare = tDAG_PPara .ui8_P_MIN_TIRE ;   // isn't absolute value any more , now relative - as everything else too

	ptLWD->ucCurWarnLevel = ucPCompare;
	if (ptLWD->tHFD.tHF.ucP < ucPCompare)
	{
		ucRet = ucSetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucPMinIxc);
	}
	else
	{
		if (ucGetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucPMinIxc) == 1)
		{
			if ((ui8SWTimerExpired() > 0) || ( ushWarnOutTM != cNORMAL )) /*CRS_1211_080_001 refer to TPMS Logic PAL2 V1.4.docx chapter 6.5 "pressure > hard-threshold  (without 5 kPa) "*/
			{
				ucPCompare += ucHWResetHyst ; // refer to TPMS Logic PAL2 V1.4.docx chapter 6.5 "pressure > hard-threshold + 5 kPa" for very low temperatures (refer to OIL #
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
