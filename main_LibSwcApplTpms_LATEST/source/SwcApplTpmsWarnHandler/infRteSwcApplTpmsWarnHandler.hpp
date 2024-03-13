#pragma once
/******************************************************************************/
/* File              : infRteSwcApplTpmsWarnHandler.hpp                       */
/* Author            : Nagaraja HULIYAPURADA MATA                             */
/* Copyright (c)2024 : All rights reserved.                                   */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "infSwcApplTpmsSMRte.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define ucPorInitc                                                             1
#define cKl15Init                                                              2
#define cSingleIdInit                                                          3
#define ucDiagServicec                                                         4
#define ucPorInitUSc                                                           5
#define ucComparec                                                             5
#define ucCfgCtryCodec                                                         1
#define ucResetWarnVectorc                                                    14
#define ucCfgPSollMinAtIdc                                                    15
#define ucGetIsoc                                                             16
#define ucGetPSollAtTempc                                                     17
#define ucGetPSollMinc                                                        18
#define ucGetWarnVectorsc                                                     19
#define ucCfgPFactorc                                                         24
#define ucCfgDHWc                                                             25
#define ucCfgFTc                                                              26
#define ucCfgEcEc                                                             27
#define ucCfgHTVc                                                             28
#define ucCfgSTc                                                              29
#define ucCfgTSc                                                              30
#define ucGetWarnTypec                                                        31
#define cNORMAL                                                     ((uint8)  0)
#define ucPMinIxc                                                   ((uint8)  0)
#define ucEcEIxc                                                    ((uint8)  1)
#define ucSFactorIxc                                                ((uint8)  2)
#define ucDHWIxc                                                    ((uint8)  3)
#define ucSoftTIxc                                                  ((uint8)  4)
#define ucSumWEc                                                    ((uint8)  4)
#define ucWarnTypeArrayIdWNc                                        ((uint16) 6)

#define cSOFT_WARNING                                                ((uint8) 1)
#define cHARD_WARNING                                                ((uint8) 2)
#define cFAST_DEFLATION                                              ((uint8) 3)

#define ush273Kelvinc                                                        273
#define ushGSFc                                                             1024

#define ucPResInMBarc                                                         25
#define ucDP_TOLERANCEc                           ((uint8)(200 / ucPResInMBarc)) //TBD: Optimize implementation
#define ucPreSoftRange                            ((uint8)(100 / ucPResInMBarc)) //TBD: Optimize implementation
#define cDP_COMP_LIMIT                            ((uint8)(100 / ucPResInMBarc)) //TBD: Optimize implementation
#define ucHWResetHyst                             ((uint8)( 50 / ucPResInMBarc)) //TBD: Optimize implementation

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef struct{
   uint8  ui8_P_MIN_F;
   uint8  ui8_P_MIN_R;
   uint8  ui8_P_MIN_TIRE;
   uint16 ui16_T_SOFT;
   uint8  ui8_PERCENT_SOFT;
   uint16 ui16_T_HARD;
   uint8  ui8_PERCENT_HARD;
   uint16 ui16_CONSTANT_DELAY;
}PWarnParaType;

struct HFTelIntern{
   uint8  ucId;
   uint8  ucP;
   sint8  scTWE;
   uint8  ucLifeTime;
   uint8  ucState;
   uint16 ushVehicleSpeed;
   sint8  scTa;
   uint8  ucKLState;
};

union HFTelAccess{
   struct HFTelIntern tHF;
   uint8              ucByte[(uint8) sizeof(struct HFTelIntern)];
};

struct SollDat{
   uint8  ucPSoll;
   sint8  scTSoll;
   uint16 ushMSoll;
};

struct LocalWarnDat{
   union  HFTelAccess tHFD;
   struct SollDat     tSD;
   uint8              ucCurWarnLevel;
   uint8              PRefMin;
   uint8              ucResetLvl;
};

extern uint8  bPMin               (struct LocalWarnDat* ptLWD, uint8 ucWarnCfg); //TBD: Optimize implementation
extern uint8  bEcE                (struct LocalWarnDat* ptLWD, uint8 ucWarnCfg); //TBD: Optimize implementation
extern uint8  bSoftFactor         (struct LocalWarnDat* ptLWD, uint8 ucWarnCfg); //TBD: Optimize implementation
extern uint8  bDHW                (struct LocalWarnDat* ptLWD, uint8 ucWarnCfg); //TBD: Optimize implementation
#define cAllWT_function                         {bPMin, bEcE, bSoftFactor, bDHW}

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
extern PWarnParaType tDAG_PPara;   //TBD: Optimize with getters and setters
extern uint16        ushWarnOutTM; //TBD: Optimize with getters and setters

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
extern uint8  ui8GetPMIN_F          (void);
extern uint8  ui8GetPMIN_R          (void);
extern uint8  ui8SWTimerExpired     (void);
extern uint8  ucStartFilterSTWT     (uint16);
extern uint8  ucStartFilterHDWT     (uint16);
extern void   StopFilterSTWT        (void);
extern void   StopFilterHDWT        (void);
extern uint8  Getui8AtmosphericP    (void);
extern void   PuT                   (uint8 ui8Ix, sint8 i8T);
extern void   GetRatValOfId         (uint8 uiHistCol, struct SollDat* p2RatVal);
extern uint8  Getui8PrefMinOfId     (uint8 histCol);
extern uint8  ucGetWPOfCol          (uint8 ucIx);
extern void   SortBiggest1st        (uint8* ptVal, uint8* ptIx,  uint8 ucMax);
extern void   GetDataEE             (uint8,       uint8*, uint8);
extern void   PutDataEE             (uint8, const uint8*, uint8);
extern uint8* GETpucStartAdrWPorPWP (void);
extern uint8  ucPfT                 (uint16 ushM,  uint16 ushTabs);
extern void   ClearWarnBitWN        (uint8  ucIdX, uint8  ucWarnTypeIx);
extern uint8  ucGetWarnBitWN        (uint8  ucIdX, uint8  ucWarnTypeIx);
extern uint8  ucSetWarnBitWN        (uint8  ucIdX, uint8  ucWarnTypeIx);
extern uint16 ushMIso               (uint8  ucP,   sint8  scT);

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

