#pragma once
/******************************************************************************/
/* File              : USWarnX.h                                              */
/* Author            : Nagaraja HULIYAPURADA MATA                             */
/* Copyright (c)2024 : All rights reserved.                                   */
/******************************************************************************/

/******************************************************************************/
/*#includeS                                                                  */
/******************************************************************************/

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define ucPMinIxc    ((uint8) 0)
#define ucDHWIxc     ((uint8) 3)
#define ucSoftTIxc   ((uint8) 4)
#define ucEcEIxc     ((uint8) 1)
#define ucSFactorIxc ((uint8) 2)
#define cDAG_PMin_WN ((uint8) 1)
#define cDAG_Hard_WN ((uint8) 2)
#define cDAG_FPL_WN  ((uint8) 8)
#define cDAG_Soft_WN ((uint8) 4)
#define ushGSFc      (1024)

#define cKl15Init 2
#define cSingleIdInit 3
#define ucDiagServicec 4
#define ucPorInitUSc 5
#define ucComparec 5
#define ucCfgCtryCodec  1
#define ucResetWarnVectorc 14
#define ucCfgPSollMinAtIdc 15
#define ucGetIsoc 16
#define ucGetPSollAtTempc 17
#define ucGetPSollMinc 18
#define ucCfgPFactorc  24
#define ucCfgDHWc 25
#define ucCfgFTc  26
#define ucCfgEcEc 27
#define ucCfgHTVc 28
#define ucCfgSTc  29
#define ucCfgTSc 30
#define ucGetWarnTypec 31
#define ucClearPosc 3
#define ucCountc (uint8) 7
#define ucIniTimec (uint8) 8

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/
extern uint8 aucWheelPosWarn[];
#define GETaucWheelPosWarn(Pos) (aucWheelPosWarn[Pos])

extern void InitUSWAlgo(const uint8*);


extern uint8 ui8GetHardWrnOfWP(uint8 ui8WP);
#define GETbWrnHard_WP(Pos)     ((uint8) 1 == ui8GetHardWrnOfWP(Pos))

extern uint8 ui8GetSoftWrnOfWP(uint8 ui8WP);
#define GETbWrnSoft_WP(Pos)     ((uint8) 1 == ui8GetSoftWrnOfWP(Pos))

/*
#define GETbWrnFastLoss_FL()    ((aucWheelPosWarn[ucWPFLc] & ((uint8) (1<<ucDHWIxc))) == ((uint8) (1<<ucDHWIxc)))
#define GETbWrnFastLoss_FR()    ((aucWheelPosWarn[ucWPFRc] & ((uint8) (1<<ucDHWIxc))) == ((uint8) (1<<ucDHWIxc)))
#define GETbWrnFastLoss_RL()    ((aucWheelPosWarn[ucWPRLc] & ((uint8) (1<<ucDHWIxc))) == ((uint8) (1<<ucDHWIxc)))
#define GETbWrnFastLoss_RR()    ((aucWheelPosWarn[ucWPRRc] & ((uint8) (1<<ucDHWIxc))) == ((uint8) (1<<ucDHWIxc)))
#define GETbWrnFastLoss_UK()    ((aucWheelPosWarn[4] & ((uint8) (1<<ucDHWIxc))) == ((uint8) (1<<ucDHWIxc)))
#define GETbWrnFastLoss_WP(Pos) ((aucWheelPosWarn[Pos] & ((uint8) (1<<ucDHWIxc))) == ((uint8) (1<<ucDHWIxc)))
#define GETbWrnHard_FL()        (GETbWrnHard_WP(ucWPFLc))
#define GETbWrnHard_FR()        (GETbWrnHard_WP(ucWPFRc))
#define GETbWrnHard_RL()        (GETbWrnHard_WP(ucWPRLc))
#define GETbWrnHard_RR()        (GETbWrnHard_WP(ucWPRRc))
#define GETbWrnHard_UK()        (GETbWrnHard_WP(4))
#define GETbWrnPreSoft_FL()     ((aucWheelPosWarn[ucWPFLc] & ((uint8) (1<<ucSoftTIxc))) == ((uint8) (1<<ucSoftTIxc)))
#define GETbWrnPreSoft_FR()     ((aucWheelPosWarn[ucWPFRc] & ((uint8) (1<<ucSoftTIxc))) == ((uint8) (1<<ucSoftTIxc)))
#define GETbWrnPreSoft_RL()     ((aucWheelPosWarn[ucWPRLc] & ((uint8) (1<<ucSoftTIxc))) == ((uint8) (1<<ucSoftTIxc)))
#define GETbWrnPreSoft_RR()     ((aucWheelPosWarn[ucWPRRc] & ((uint8) (1<<ucSoftTIxc))) == ((uint8) (1<<ucSoftTIxc)))
#define GETbWrnPreSoft_UK()     ((aucWheelPosWarn[4] & ((uint8) (1<<ucSoftTIxc))) == ((uint8) (1<<ucSoftTIxc)))
#define GETbWrnPreSoft_WP(Pos)  ((aucWheelPosWarn[Pos] & ((uint8) (1<<ucSoftTIxc))) == ((uint8) (1<<ucSoftTIxc)))
#define GETbWrnSoft_FL()        (GETbWrnSoft_WP(ucWPFLc))
#define GETbWrnSoft_FR()        (GETbWrnSoft_WP(ucWPFRc))
#define GETbWrnSoft_RL()        (GETbWrnSoft_WP(ucWPRLc))
#define GETbWrnSoft_RR()        (GETbWrnSoft_WP(ucWPRRc))
#define GETbWrnSoft_UK()        (GETbWrnSoft_WP(4))
#define GETucHiWarnstatus1WN()  ((uint8) (ushWarnOutTM >> 8))
#define GETucLoWarnstatus1WN()  ((uint8)  ushWarnOutTM)
*/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
struct HFTel{
   uint8  ucId;
   uint8  ucP;
   sint8  scTWE;
   uint8  ucLifeTime;
   uint8  ucState;
   uint16 ushVehicleSpeed;
   sint8  scTa;
   uint8  ucKLState;
};

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
extern uint16 ui16GetCombVSpeed           (uint16 ui16CurVehSpeed);
extern uint16 ui16GetFilterSpeedInKmh     (void);
extern uint16 ui16GetHarTimerInSec        (void);
extern uint16 ui16GetOvrHeatCt            (void);
extern uint16 ui16GetSofTimerInSec        (void);
extern uint16 ui16GetSpeedCtInSec         (void);
extern uint8  NewPositionsUSWIF           (const uint8*);
extern uint8  ui8GenPWP                   (uint8* p2PWP);
extern uint8  ui8GETDAGClrWrnThresOfIdCol (uint8  ui8ColOfId);
extern uint8  ui8GetOvrHeatId             (uint8* pui8ZPos);
extern uint8  ui8GetPRefRel               (uint8  ui8Ix);
extern uint8  ui8GetPRelComp2Tref         (sint8  i8Tcur, uint8 ui8Ix);
extern uint8  ui8GetTempColeurWP          (const uint8 ui8WP);
extern uint8  ui8GetTempColeurWP_UK       (void);
extern uint8  ui8GetWarntypeOfHistCol     (uint8 ui8WnType, uint8 ui8HistCol);
extern uint8  ui8HarTimerActive           (void);
extern uint8  ui8SofTimerActive           (void);
extern sint8  i8GetTref                   (uint8 ui8Ix);
extern void   DelWarnOfId                 (uint8 ui8HistColOfID);
extern void   GETDAGWrnLvlOfIdCol         (uint8 ui8ColOfId, uint8* p2WrnLvls);
extern void   KL15OffWarnInit             (const uint8 *ptWPos);


/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

