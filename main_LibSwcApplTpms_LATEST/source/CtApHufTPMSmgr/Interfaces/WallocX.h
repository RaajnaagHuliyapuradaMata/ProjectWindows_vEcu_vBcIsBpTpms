#pragma once

#include "walloc_if.h"

#define cNoWPos (uint8) 0xF0
#define cWP_RR  (uint8) 0x08
#define cWP_RL  (uint8) 0x04
#define cWP_FR  (uint8) 0x02
#define cWP_FL  (uint8) 0x01

struct InputWA{
  unsigned long ulID;
  uint8 ucStatus;
  uint8 ucRssi;
};

typedef struct{
  uint8 ucWACtrl;
  uint8 AL_State;
}WAParameter;

typedef struct{
    uint8 ucWACfg;
}WAParNCfgType;

#define cSumWE  16
#define cMaxLR  4

#define cHiStateTZG (uint8) 0x04
#define cHiStateZG  (uint8) 0x02
#define cHiStateER  (uint8) 0x01
#define cIDStateSpinning 0x0C
#define cIDStateSpinLeft 0x08
#define cIDStateSpinRight 0x04
#define cRLTelValid 0x80
#define ucBkwdc (uint8) 0x40
#define ucNoDriveInfoc (uint8) 0x80
#define cIDStateDrvBack 0x40
#define cIDStateNoDrvInfo 0x80
#define cIDStateM4 0x04
#define cWAChange (uint8) 0xF0
#define cWAStateChange_FL (uint8) 0x80
#define cWAStateChange_FR (uint8) 0x40
#define cWAStateChange_RL (uint8) 0x20
#define cWAStateChange_RR (uint8) 0x10
#define cWAStateBreak 0x08
#define cWAStateZO 0x04
#define cWAStateER 0x02
#define cWAStateActive 0x01
#define cWAIDChanged 0x00F0
#define cWAWPChanged 0xF000
#define cErrorActive (uint8) 1
#define cTO (uint8) 2
#define cTZG (uint8) 4
#define cForcedZO (uint8) 8
#define cAL_OK (uint8) 100
#define cAL_Stored (uint8) 1
#define cAL_Unknown (uint8) 2
#define cAL_Error (uint8) 3
#define cEvNewIDs (uint8) 0
#define cEv4WPs (uint8) 1
#define cEvALFailed (uint8) 2
#define cEvHoldStore (uint8) 8
#define ucDefWACtrl (uint8) 0
#define ucDefAxDistInDm (uint8) 31
#define ucDefWheelDiamInDm (uint8) 5
#define ucDefMinRssiDistance (uint8) 7
#define ucDefLeRiMinDistance (uint8) 1
#define ucECUPosFront (uint8) 0x55
#define ucECUPosRear (uint8) 0xAA
#define ucDefMinCt4AxAnalysis (uint8) 15
#define ucDefMinCt4ER (uint8) 7
#define ucDefMinCt4HistER (uint8) 3
#define ucDefMinERMeanRssiLevel (uint8) 14
#define ucDefAL_State cAL_Stored

#define cWADefInitParam \
{ \
 ucDefWACtrl, \
 ucDefAxDistInDm, \
 ucDefWheelDiamInDm, \
 ucDefMinRssiDistance, \
 ucDefLeRiMinDistance, \
 ucECUPosRear, \
 ucDefMinCt4AxAnalysis, \
 ucDefMinCt4ER, \
 ucDefMinCt4HistER, \
 ucDefMinERMeanRssiLevel, \
 ucDefAL_State \
}

#define cWAHistIDSetDefInit {(unsigned long) 0,(unsigned long) 0,(unsigned long) 0,(unsigned long) 0}
#define cWAHistWPSetDefInit {(uint8) 8,(uint8) 8,(uint8) 8,(uint8) 8}
#define cSumABSig (uint8) 4
#define cABSStickError (uint16) 0xFFFF
#define RealOutput
#define FPA
#define NoError (uint8) 0
#define SensorMissin (uint8) 1
#define NoLearnSensor (uint8) 2
#define BadSpeed (uint8) 1
#define TooFewPalTels (uint8) 2
#define AmbigWP (uint8) 3
#define RivalSensors (uint8) 4
#define ABSignalMissin (uint8) 5
#define AssegnazioneCostretto (uint8) 6
#define cNoLearn (uint8) 1
#define cSpeciaLearn (uint8) 2
#define cCompleteLearn (uint8) 3
#define Autolearn_Learning (uint8) 1
#define Autolearn_OK (uint8) 2
#define Timeout_3_Sensors (uint8) 3
#define Timeout_2_Sensors (uint8) 4
#define Timeout_1_Sensor (uint8) 5
#define Timeout_No_Sensors (uint8) 6

extern uint8 WAInit(WAParNCfgType *);
extern uint16 ushLearnID(tRFTelType  *);
extern void WATimer1sec(uint16 ushVSpeedInKmh);
extern uint8* pucGetLearnError(void);
extern uint8* pucGetLocatError(void);
extern uint16 ushGetDriveTimeInSec(void);
extern uint8 ucGetColOfID(unsigned long *);
extern uint8 ucGetWPOfCol(uint8);
extern uint8 ucGetColOfWP(uint8);
extern unsigned long ulGetID(uint8 ucIx);
extern uint8 ucSetID(unsigned long *pt2ID, uint8 *pt2Pos, uint8 ucSum);
extern uint8 bCheckHistIDReception(void);
extern uint8 ucSetAutolocationOveride(uint8 ucPalOverideFlag);
extern uint8 ucSet4HistIDs(unsigned long *pt2ID, uint8 *pt2Pos);
extern uint8 ucSet1HistID(unsigned long *pt2ID, uint8 *pt2Pos, uint8 ucIdx);
extern void RdWAPara( WAParameter *);
extern void WrWAPara( WAParameter *);
extern void ChangeWAPara(void);
uint8 ucCheckAutolocationOverideCondition();
uint8 ucReadAutolocationOverideFlag(void);
extern uint8* GETpucStartAdrWP(void);
extern unsigned long ulGetZOMID(uint8  ucIdx);
extern uint8 ucGetZOMPosOfID(unsigned long *pt2ID);
extern uint8 ucGetZomStatus(uint8  ucIdx);
extern uint8 ucGetZomToothTelCtCorrLearnBit(uint8  ucIdx);
extern uint8 ucGetZomToothTelCtCorrNoLearnBit(uint8  ucIdx);
extern uint8 ucGetZomToothTelCtrNoCorr(uint8  ucIdx);
extern uint8 ucGetZomToothTelCtNoLearnMode(uint8  ucIdx);
extern uint8 ucGetZomToothTelCt(uint8  ucIdx);
extern uint8 ucGetZomTelCtLearnBit(uint8  ucIdx);
extern uint8 ucGetZomDeltaMin(uint8  ucIdx);
extern uint8 *ucGetZomAbsComp(uint8  ucIdx);
extern uint8 ucGetZomLqi(uint8 ucIdx);
extern uint16 *ushGetZomAbsSums(uint8  ucIdx);
extern uint8 ucGetZOMPalFrameCounter(uint8 ucIx);
extern uint8 ucGetZomResetAbsRefFlag(uint8 ucIx);
extern void PUTtWAparam(uint8 x, uint8 i);
extern uint8 GETtWAparam(uint8 i);
extern uint8 GETucWAHistID(uint8 i);
extern void PUTucWAHistID(uint8 x, uint8 i);
extern uint8 GETucWAHistWP(uint8 i);
extern void PUTucWAHistWP(uint8 x, uint8 i);
extern void SetWaData2NvmFlag(void);
extern void SortBiggest1st(uint8 *ptVal, uint8 *ptIx, uint8 ucMax);
extern uint8 ui8GetALState(void);
extern uint8 ucGetLearnMode (void);
extern uint8 ucHistInConsist(void);

#ifdef FPA
extern void RebuildABSRef(uint8 ucWP);
extern void ReNewABSRef(void);
extern void PutABSErrorActive(void);
#endif

extern uint8 ui8GetDAGAutoLearnState(void);
extern void ClearPWP(void);
extern void Check4PWP(void);
extern uint8 USEui8PWPofHistCol(uint8 ui8HistCol);
extern void PUTaucPWPofHistCol(uint8 ui8HistCol, uint8 ui8Val);
extern uint8 ui8CheckNWrPWP(uint8 ui8HistCol, uint8 ui8WP);
extern uint8 GETui8PWPofHistCol(uint8 ui8HistCol);
extern uint8 Getui8ColPWPActive(void);
extern uint8* GETpucStartAdrWPorPWP(void);
extern uint16 GETushWAState(void);
extern uint8 WAInitByDiag(WAParNCfgType *);
extern void PUTucWAHistSensorState(uint8 ui8Val);
extern uint8 GETucWAHistSensorState(void);
uint8 ui8PWPresent(void);

#ifdef FD_CONTROLS_FALLBACK
extern  uint8 ui8GetPPWP(uint8* p2P, uint8* p2PWP, uint8 ui8MinRefPF, uint8 ui8MinRefPR);
extern void Wr4PWP2NVM(uint8* p24PWP);
#endif

#ifdef WAModulTest
void TESTPutDriveTimeInSec(uint16 ushTimeInSec);
void SetALState(uint8 ui8State);

#endif
