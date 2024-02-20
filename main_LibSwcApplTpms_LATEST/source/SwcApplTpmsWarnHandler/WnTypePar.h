
#ifndef WNTYPEPAR_H
#define WNTYPEPAR_H

#include "Platform_Types.h"
#include "USWarn.h"
#include "USWarnX.h"

extern unsigned char bPMin( struct LocalWarnDat *ptLWD, unsigned char ucWarnCfg );
extern unsigned char bDHW( struct LocalWarnDat *ptLWD, unsigned char ucWarnCfg );

extern unsigned char bEcE( struct LocalWarnDat *ptLWD, unsigned char ucWarnCfg);
extern unsigned char bSoftFactor( struct LocalWarnDat *ptLWD, unsigned char ucWarnCfg);

static const unsigned char ucMaxWarnTypeWNc = 4;

#define cAllWT_function {bPMin, bEcE, bSoftFactor, bDHW }

#define ucPMinECE (uint8) (2500 / ucPResInMBarc)
#define ucPMinUS (uint8) (2400 / ucPResInMBarc)

#define ucDpTxTriggerc (uint8) 1
#define ucDP_TOLERANCEc (uint8) (200 / ucPResInMBarc)

#define ucEcEpcFactorc (uint8) 20
#define ushHWDelayInSec  240

#define ucSoftFactorc (uint8) 14
#define ushECESWDelayInSec  480
 #define ushUSSWDelayInSec  1080
 #define ushV_MINc 20

#define  ucUSFactorPFc  (unsigned char) 25
#define  ucEUFactorPFc  (unsigned char) 16
#define  ucAdOnPFc  (unsigned char) 4
#define ucNegHystPFc  (unsigned char) (150 / ucPResInMBarc)
#define  ucHystPFc  (unsigned char) 0

#define cDP_COMP_LIMIT (unsigned char) (100 / ucPResInMBarc)
#define ucHWResetHyst (unsigned char) (50 / ucPResInMBarc)

#define ucFrikModec (unsigned char) 1

#define scTResLimitc (signed char) 25

#define ushCallFreqInMSWTc 100

#define ucTimeFilterPrescInMSc ((unsigned char) (20000 / ushCallFreqInMSWTc))

extern TempWarnParaType tDAG_TemPara;
extern PWarnParaType tDAG_PPara;

#endif
