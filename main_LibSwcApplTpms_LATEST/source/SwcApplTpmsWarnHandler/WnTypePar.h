/***************************************************************************************************
*(c) Beru Electronics GmbH     BES     11/2005
*================================================================================================
*
*  $Archive: /LIB/AUTOSAR/SWC/HufTPMSwnh/wnh/WnTypePar.h $
*
*    ------------------------------------------------------------------------------------------------
*
*   author:        Peter Brand                Beru Electronics GmbH
*
*   intials:       pb
*
*
*   Modul Description
*
*   Global description:
*
*   contains all former parameters of different warning types of USWalgo as define declarations
*   this header is not a part of the USWalgo light implementation ! this is just an example to
*   be adapted to your own series. Do not share this file with the USWalgo light project !
*   Use this example header implementaion and adapt the parameters to your customers wishes.
*
*
*Modul Modification
*
*last modification:
*$Log: /LIB/AUTOSAR/SWC/HufTPMSwnh/wnh/WnTypePar.h $
* 
* 19    3.09.12 10:41 Rapp
* 
* 17    21.02.12 14:49 Rapp
* Anpassung EU Warntyp
* 
* 15    18.10.11 14:12 Rapp
* Headerdatei an Änderung im Warnhandler light Interface angepasst
* 
* 14    18.10.11 14:07 Rapp
* Headerdatei an Änderung im Warnhandler light Interface angepasst
*
* 13    4.01.10 17:02 Peter
*
* 12    21.07.09 11:17 Rapp
* Rücknahme der Panne nicht mehr isochorenbewertet (OIL #442)
*
* 11    16.03.09 13:51 Rapp
* Konstante ucMaxWarnTypeWNc aus USWarnX.h nach hier verschoben
*
* 10    6.11.08 13:24 Peter
* Softwarning delay timer constant set to 10min instead of former 45min.
*
* 9     13.10.08 17:19 Peter
* UpDate suitable to latest uswtime
* configuration data as PL6
*
* 6     2.07.07 10:04 Peter
* refactoring USWarn
*
* 5     1.03.07 14:49 Peter
* FT hysteresis parameter decreased (1200mBar ->1100mBar)
*
* 4     12.01.07 11:17 Peter
* parameter for activate and deactivate freakfilter
*
* 3     14.08.06 15:47 Peter
* FaltTyreWarning activated
*
* 2     14.07.06 9:56 Peter
* Parameter macro definition moves from globfx.h to this file
* constant parameters set to bmw USWalgo configuration according to E6x
*
* 1     9.11.05 9:19 Peter
* constant definitions of warntype parameters
*
*/
#ifndef WNTYPEPAR_H
#define WNTYPEPAR_H
/***************************************************************************************************
Declaration
*/
/***************************************************************************************************
Include
*/
#include "Platform_Types.h"
//#include "cfg.h"
#include "USWarn.h" // for LocalWarnDat decl
#include "USWarnX.h"
/***************************************************************************************************
Prototypes
*/
extern unsigned char bPMin( struct LocalWarnDat *ptLWD, unsigned char ucWarnCfg );
extern unsigned char bDHW( struct LocalWarnDat *ptLWD, unsigned char ucWarnCfg );

extern unsigned char bEcE( struct LocalWarnDat *ptLWD, unsigned char ucWarnCfg);
extern unsigned char bSoftFactor( struct LocalWarnDat *ptLWD, unsigned char ucWarnCfg);


static const unsigned char ucMaxWarnTypeWNc = 4; /* maximum amount of warntypes ( SW_10060 SW_140 )*/


/***************************************************************************************************
Macros
*/
/***************************************************************************************************/

/* WARNING: bPMin, bDHW and bSoftT MUST NOT BE REPLACED OR REMOVED */
#define cAllWT_function {bPMin, bEcE, bSoftFactor, bDHW }

/***************************************************************************************************/
/* the following macros form a list of USWalgo configuration parameters not changable at runtime   */
/* each warning type uses a set of different parameters                                            */

/* WT DAG PMin Bit0 [0...7] in aucWarnBitsWN */
#define ucPMinECE (uint8) (2500 / ucPResInMBarc)
#define ucPMinUS (uint8) (2400 / ucPResInMBarc)

/* WT DAG Fast Pressure Loss (DHW)  Bit2 [0...7] in aucWarnBitsWN*/
#define ucDpTxTriggerc (uint8) 1
#define ucDP_TOLERANCEc (uint8) (200 / ucPResInMBarc)

/* DAG HW = ECE  */
#define ucEcEpcFactorc (uint8) 20
#define ushHWDelayInSec  240

/* DAG soft warning */
#define ucSoftFactorc (uint8) 14
#define ushECESWDelayInSec  480   //  8 min
#define ushUSSWDelayInSec  1080   // 18 min
#define ushV_MINc 20    /* delay timer for soft warning is active if speed vehicule is > than this */

/* PF */
#define  ucUSFactorPFc  (unsigned char) 25
#define  ucEUFactorPFc  (unsigned char) 16
#define  ucAdOnPFc  (unsigned char) 4
#define ucNegHystPFc  (unsigned char) (150 / ucPResInMBarc)
#define  ucHystPFc  (unsigned char) 0


/***************************************************************************************************/
/* the following parameters are common in all  warning typea                                       */
#define cDP_COMP_LIMIT (unsigned char) (100 / ucPResInMBarc)
#define ucHWResetHyst (unsigned char) (50 / ucPResInMBarc)

/***************************************************************************************************/
/* the following parameters are not related directly to any warning type                           */

#define ucFrikModec (unsigned char) 1 /* freak filter activity for every warning type expect ST  */
/*  active = 1 ; inactive = 0 */

#define scTResLimitc (signed char) 25    /* default "grenztemperatur differenz" s.a. (25K) */

#define ushCallFreqInMSWTc 100 /* function TimerWT gets called every 100 ms */
/* WARNING: VALUE MUST NOT BE SMALLER  THAN 80ms */
#define ucTimeFilterPrescInMSc ((unsigned char) (20000 / ushCallFreqInMSWTc))	/* prescaler 4 timefilter in msecs */


/***************************************************************************************************
Data
*/
extern TempWarnParaType tDAG_TemPara;
extern PWarnParaType tDAG_PPara;

/***************************************************************************************************
Implementation
*/
#endif /* WNTYPEPAR_H */
