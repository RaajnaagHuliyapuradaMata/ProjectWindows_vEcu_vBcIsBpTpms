
#include "Platform_Types.h"

#ifndef USWarnX_H

#define USWarnX_H

#define ucPMinIxc (unsigned char) 0
#define ucDHWIxc (unsigned char) 3
#define ucSoftTIxc (unsigned char) 4

#define ucEcEIxc (unsigned char) 1
#define ucSFactorIxc (unsigned char) 2

#define ucAllDAGWarningBits (unsigned char) 0x1F
 #define cDAG_PMin_WN (uint8) 1
#define cDAG_Hard_WN (uint8) 2
#define cDAG_FPL_WN  (uint8) 8
#define cDAG_Soft_WN (uint8) 4

#define ushGSFc 1024

typedef struct {
 uint16 ui16_V1;
  uint16 ui16_V2;
  uint16 ui16_V3;
  sint8 i8_T0;
  sint8 i8_T1;
  sint8 i8_T2;
  uint16 ui16_HC_MAX;
  uint8 ui8_TempWarnEnable;
 } TempWarnParaType;

typedef struct {
    uint8 ui8_P_MIN_F;
     uint8 ui8_P_MIN_R;
     uint8 ui8_P_MIN_TIRE;
     uint16 ui16_T_SOFT;
     uint8 ui8_PERCENT_SOFT;
     uint16 ui16_T_HARD;
     uint8 ui8_PERCENT_HARD;
     uint16 ui16_CONSTANT_DELAY;
 } PWarnParaType;

extern unsigned char ucWarnManagerWN(unsigned char ucAction, unsigned char *ptData);

struct HFTel
{
   unsigned char ucId;
    unsigned char ucP;
    signed char scTWE;
    unsigned char ucLifeTime;
    unsigned char ucState;
    unsigned short ushVehicleSpeed;
    signed char scTa;
    unsigned char ucKLState;
};

extern unsigned char ucTSSMsgManagerTM(unsigned char ucAction, unsigned char *ptData);
struct TssMsg
{
  unsigned char ucId;
  unsigned char ucPos;
  unsigned char ucSystemState;
  unsigned char ucWarning;
};
 extern void TimerWTinit(void);

extern void InitUSWAlgo(const unsigned char *);

#define ucWPFLc (unsigned char) 0
#define ucWPFRc (unsigned char) 1
#define ucWPRLc (unsigned char) 2
#define ucWPRRc (unsigned char) 3
#define ucWPSTc (unsigned char) 4
#define ucWPUNc (unsigned char) 8

#define ucPorInitc 1
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
#define ucGetWarnVectorsc 19
#define ucCfgPFactorc  24
#define ucCfgDHWc 25
#define ucCfgFTc  26
#define ucCfgEcEc 27
#define ucCfgHTVc 28
#define ucCfgSTc  29
#define ucCfgTSc 30
#define ucGetWarnTypec 31

#define ucTssMsgOutc 6

#define ucNewPositionsc   2
#define ucClearPosc 3

#define ucPutWarnVectorSetc 9

#define ucCountc (unsigned char) 7
#define ucIniTimec (unsigned char) 8

extern unsigned char aucWheelPosWarn[];
 #define GETaucWheelPosWarn(Pos) (aucWheelPosWarn[Pos])

extern uint8 ui8GetHardWrnOfWP(uint8 ui8WP);
extern uint8 ui8GetSoftWrnOfWP(uint8 ui8WP);
#define GETbWrnPMin_FL() ( (aucWheelPosWarn[ucWPFLc] & ((unsigned char) (1<<ucPMinIxc)) ) == ((unsigned char) (1<<ucPMinIxc))  )
 #define GETbWrnPMin_FR() ( (aucWheelPosWarn[ucWPFRc] & ((unsigned char) (1<<ucPMinIxc)) ) == ((unsigned char) (1<<ucPMinIxc))  )
#define GETbWrnPMin_RL() ( (aucWheelPosWarn[ucWPRLc] & ((unsigned char) (1<<ucPMinIxc)) ) == ((unsigned char) (1<<ucPMinIxc))  )
#define GETbWrnPMin_RR() ( (aucWheelPosWarn[ucWPRRc] & ((unsigned char) (1<<ucPMinIxc)) ) == ((unsigned char) (1<<ucPMinIxc))  )
#define GETbWrnPMin_UK() ( (aucWheelPosWarn[4] & ((unsigned char) (1<<ucPMinIxc)) ) == ((unsigned char) (1<<ucPMinIxc))  )
#define GETbWrnPMin_WP(Pos) ( (aucWheelPosWarn[Pos] & ((unsigned char) (1<<ucPMinIxc)) ) == ((unsigned char) (1<<ucPMinIxc))  )

#define GETbWrnHard_WP(Pos) ( (uint8) 1 == ui8GetHardWrnOfWP(Pos)  )
#define GETbWrnHard_FL() ( GETbWrnHard_WP(ucWPFLc) )
 #define GETbWrnHard_FR() ( GETbWrnHard_WP(ucWPFRc) )
#define GETbWrnHard_RL() ( GETbWrnHard_WP(ucWPRLc) )
#define GETbWrnHard_RR() ( GETbWrnHard_WP(ucWPRRc) )
#define GETbWrnHard_UK() ( GETbWrnHard_WP(4) )

#define GETbWrnSoft_WP(Pos) ( (uint8) 1 == ui8GetSoftWrnOfWP(Pos)  )
#define GETbWrnSoft_FL()  ( GETbWrnSoft_WP(ucWPFLc) )
 #define GETbWrnSoft_FR()  ( GETbWrnSoft_WP(ucWPFRc) )
#define GETbWrnSoft_RL()  ( GETbWrnSoft_WP(ucWPRLc) )
#define GETbWrnSoft_RR()  ( GETbWrnSoft_WP(ucWPRRc) )
#define GETbWrnSoft_UK()  ( GETbWrnSoft_WP(4) )

#define GETbWrnFastLoss_FL() ( (aucWheelPosWarn[ucWPFLc] & ((unsigned char) (1<<ucDHWIxc)) ) == ((unsigned char) (1<<ucDHWIxc))  )
 #define GETbWrnFastLoss_FR() ( (aucWheelPosWarn[ucWPFRc] & ((unsigned char) (1<<ucDHWIxc)) ) == ((unsigned char) (1<<ucDHWIxc))  )
#define GETbWrnFastLoss_RL() ( (aucWheelPosWarn[ucWPRLc] & ((unsigned char) (1<<ucDHWIxc)) ) == ((unsigned char) (1<<ucDHWIxc))  )
#define GETbWrnFastLoss_RR() ( (aucWheelPosWarn[ucWPRRc] & ((unsigned char) (1<<ucDHWIxc)) ) == ((unsigned char) (1<<ucDHWIxc))  )
#define GETbWrnFastLoss_UK() ( (aucWheelPosWarn[4] & ((unsigned char) (1<<ucDHWIxc)) ) == ((unsigned char) (1<<ucDHWIxc))  )
#define GETbWrnFastLoss_WP(Pos) ( (aucWheelPosWarn[Pos] & ((unsigned char) (1<<ucDHWIxc)) ) == ((unsigned char) (1<<ucDHWIxc))  )

#define GETbWrnPreSoft_FL() ( (aucWheelPosWarn[ucWPFLc] & ((unsigned char) (1<<ucSoftTIxc)) ) == ((unsigned char) (1<<ucSoftTIxc))  )
 #define GETbWrnPreSoft_FR() ( (aucWheelPosWarn[ucWPFRc] & ((unsigned char) (1<<ucSoftTIxc)) ) == ((unsigned char) (1<<ucSoftTIxc))  )
#define GETbWrnPreSoft_RL() ( (aucWheelPosWarn[ucWPRLc] & ((unsigned char) (1<<ucSoftTIxc)) ) == ((unsigned char) (1<<ucSoftTIxc))  )
#define GETbWrnPreSoft_RR() ( (aucWheelPosWarn[ucWPRRc] & ((unsigned char) (1<<ucSoftTIxc)) ) == ((unsigned char) (1<<ucSoftTIxc))  )
#define GETbWrnPreSoft_UK() ( (aucWheelPosWarn[4] & ((unsigned char) (1<<ucSoftTIxc)) ) == ((unsigned char) (1<<ucSoftTIxc))  )
#define GETbWrnPreSoft_WP(Pos) ( (aucWheelPosWarn[Pos] & ((unsigned char) (1<<ucSoftTIxc)) ) == ((unsigned char) (1<<ucSoftTIxc))  )

/************************************************************************************************************
* global output of ushWarnOutTM
*
*MSB
*X   -   not used
*X   -   not used
*X   -   not used
*X   -   not used
*
*X   -   WW No Pos
*X   -   WW spare tyre
*X   -   WW rear right
*X   -   WW rear left
*
*
*X   -   WW front right
*X   -   WW front left
*X   -   (HW spare tyre - not used)
*X   -   HW rear right
*
*X   -   HW rear left
*X   -   HW front right
*X   -   HW front left
*X   -   HW no wheel position
*LSB
*/
extern unsigned short ushWarnOutTM;

/* macros for accessing the global ushWarnOutTM output variable by transmit -modul */
/* the naming convention is dependent to former tss systems */

#define GETushWarnstatus1WN()  ( ushWarnOutTM )
#define GETucLoWarnstatus1WN() ( (unsigned char) ushWarnOutTM )
#define GETucHiWarnstatus1WN() ( (unsigned char) (ushWarnOutTM >> 8) )

/************************************************************************************************************/

extern uint8 ui8OvrHeatWrnIsActive(void);
extern uint8 ui8GetOvrHeatId(uint8 * pui8ZPos);

  extern uint8 ui8GetTempColeurWP(const uint8 ui8WP);
extern uint8 ui8GetTempColeurWP_FL(void);
extern uint8 ui8GetTempColeurWP_FR(void);
extern uint8 ui8GetTempColeurWP_RL(void);
extern uint8 ui8GetTempColeurWP_RR(void);
extern uint8 ui8GetTempColeurWP_UK(void);
extern uint16 ui16GetSofTimerInSec(void);
extern uint16 ui16GetHarTimerInSec(void);
extern uint16 ui16GetFilterSpeedInKmh(void);
extern uint16 ui16GetOvrHeatCt(void);
extern uint16 ui16GetCombVSpeed(uint16 ui16CurVehSpeed);

extern uint8 ui8GetPRelComp2Tref(sint8 i8Tcur, uint8 ui8Ix);
 extern sint8 i8GetTref(uint8 ui8Ix);
 extern uint8 ui8GetPRefRel(uint8 ui8Ix);
 extern uint8 ui8HarTimerActive(void);
 extern uint8 ui8SofTimerActive(void);

extern uint8 ui8CalActive(void);
 extern uint8 ui8MfdCalActive(void);
 extern uint8 ui8NoHoldOff(void);
 extern uint8 ui8KL15OFF(void);

#define cNORMAL (unsigned char) 0
#define cSOFT_WARNING (unsigned char) 1
#define cHARD_WARNING (unsigned char) 2
#define cFAST_DEFLATION (unsigned char) 3

extern unsigned char GetucTPM_WarnDisp_Rq(void);
 extern void TimerWTinit(void);
extern void KL15OffWarnInit(const unsigned char *ptWPos);
extern void UpdateGlobWrnLvlNWarnDisp(void);

extern unsigned short ushMIso(unsigned char ucP, signed char scT);

extern uint8 ui8GenPWP(uint8 * p2PWP);

extern uint16 ui16GetSpeedCtInSec(void);

extern void DelWarnOfId(uint8 ui8HistColOfID);

extern uint8 ui8GetWarntypeOfHistCol(uint8 ui8WnType, uint8 ui8HistCol);
extern void ResetM1Pressure(unsigned char i);
extern void GETDAGWrnLvlOfIdCol(uint8 ui8ColOfId, uint8 * p2WrnLvls);
extern uint8 ui8GETDAGClrWrnThresOfIdCol(uint8 ui8ColOfId);
extern uint8 NewPositionsUSWIF( const uint8 * );
#endif
