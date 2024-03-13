#pragma once

#define ucPMinECE (uint8) (2500 / ucPResInMBarc)
#define ucPMinUS (uint8) (2400 / ucPResInMBarc)
#define ucDpTxTriggerc (uint8) 1
#define ucEcEpcFactorc (uint8) 20
#define ushHWDelayInSec  240
#define ucSoftFactorc (uint8) 14
#define ushECESWDelayInSec  480
#define ushUSSWDelayInSec  1080
#define ushV_MINc 20
#define ucUSFactorPFc  (uint8) 25
#define ucEUFactorPFc  (uint8) 16
#define ucAdOnPFc  (uint8) 4
#define ucNegHystPFc  (uint8) (150 / ucPResInMBarc)
#define ucHystPFc  (uint8) 0
#define ucFrikModec (uint8) 1
#define scTResLimitc ((sint8) 25)
#define ushCallFreqInMSWTc 100
#define ucTimeFilterPrescInMSc ((uint8) (20000 / ushCallFreqInMSWTc))
