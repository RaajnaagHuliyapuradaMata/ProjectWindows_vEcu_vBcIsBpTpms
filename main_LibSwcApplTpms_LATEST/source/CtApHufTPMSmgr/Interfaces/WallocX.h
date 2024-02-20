
#ifdef WallocX_H

#else
#define WallocX_H
#include "walloc_if.h"

#define cNoWPos (unsigned char) 0xF0

#define cWP_RR (unsigned char) 0x08
#define cWP_RL (unsigned char) 0x04
#define cWP_FR (unsigned char) 0x02
#define cWP_FL (unsigned char) 0x01

struct InputWA
{
  unsigned long ulID;
  unsigned char ucStatus;
  unsigned char ucRssi;
};

typedef struct
{
  unsigned char ucWACtrl;
  unsigned char AL_State;
} WAParameter;

typedef struct
{
    unsigned char ucWACfg;
 } WAParNCfgType;

#define cSumWE  16
#define cMaxLR  4

#define cHiStateTZG (unsigned char) 0x04
#define cHiStateZG (unsigned char) 0x02
#define cHiStateER (unsigned char) 0x01

#define cWheelPos_FL  0x00
#define cWheelPos_FR  0x01
#define cWheelPos_RL  0x02
#define cWheelPos_RR  0x03

#define cIDStateSpinning 0x0C
#define cIDStateSpinLeft 0x08
#define cIDStateSpinRight 0x04
#define cRLTelValid 0x80

#define ucBkwdc (unsigned char) 0x40
#define ucNoDriveInfoc (unsigned char) 0x80

#define cIDStateDrvBack 0x40
#define cIDStateNoDrvInfo 0x80
#define cIDStateM4 0x04

#define cWAChange (unsigned char) 0xF0
#define cWAStateChange_FL (unsigned char) 0x80
#define cWAStateChange_FR (unsigned char) 0x40
#define cWAStateChange_RL (unsigned char) 0x20
#define cWAStateChange_RR (unsigned char) 0x10
#define cWAStateBreak 0x08
#define cWAStateZO 0x04
#define cWAStateER 0x02
#define cWAStateActive 0x01

#define cWAIDChanged 0x00F0
#define cWAWPChanged 0xF000
 #define cErrorActive (unsigned char) 1
#define cTO (unsigned char) 2
#define cTZG (unsigned char) 4
 #define cForcedZO (unsigned char) 8
 #define cAL_OK (unsigned char) 100
#define cAL_Stored (unsigned char) 1
#define cAL_Unknown (unsigned char) 2
#define cAL_Error (unsigned char) 3
#define cEvNewIDs (unsigned char) 0
#define cEv4WPs (unsigned char) 1
#define cEvALFailed (unsigned char) 2
#define cEvHoldStore (unsigned char) 8

  #define ucDefWACtrl (unsigned char) 0
    #define ucDefAxDistInDm (unsigned char) 31
  #define ucDefWheelDiamInDm (unsigned char) 5
  #define ucDefMinRssiDistance (unsigned char) 7
  #define ucDefLeRiMinDistance (unsigned char) 1

  #define ucECUPosFront (unsigned char) 0x55
  #define ucECUPosRear (unsigned char) 0xAA

  #define ucDefMinCt4AxAnalysis (unsigned char) 15
  #define ucDefMinCt4ER (unsigned char) 7
   #define ucDefMinCt4HistER (unsigned char) 3
  #define ucDefMinERMeanRssiLevel (unsigned char) 14
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
#define cWAHistWPSetDefInit {(unsigned char) 8,(unsigned char) 8,(unsigned char) 8,(unsigned char) 8}

#define cSumABSig (unsigned char) 4
 #define cABSStickError (unsigned short) 0xFFFF
 #define RealOutput

  #define FPA

 #define NoError (unsigned char) 0

#define SensorMissin (unsigned char) 1
 #define NoLearnSensor (unsigned char) 2

#define BadSpeed (unsigned char) 1
 #define TooFewPalTels (unsigned char) 2
 #define AmbigWP (unsigned char) 3
 #define RivalSensors (unsigned char) 4
 #define ABSignalMissin (unsigned char) 5
 #define AssegnazioneCostretto (unsigned char) 6
  #define cNoLearn (unsigned char) 1
#define cSpeciaLearn (unsigned char) 2
#define cCompleteLearn (unsigned char) 3
 #define Autolearn_Learning (unsigned char) 1
 #define Autolearn_OK (unsigned char) 2
 #define Timeout_3_Sensors (unsigned char) 3
 #define Timeout_2_Sensors (unsigned char) 4
 #define Timeout_1_Sensor (unsigned char) 5
 #define Timeout_No_Sensors (unsigned char) 6

extern unsigned char WAInit(WAParNCfgType *);
extern unsigned short ushLearnID(tRFTelType  *);
extern void WATimer1sec(unsigned short ushVSpeedInKmh);
extern unsigned char * pucGetLearnError(void);
extern unsigned char * pucGetLocatError(void);
extern unsigned short ushGetDriveTimeInSec(void);

extern unsigned char ucGetColOfID(unsigned long *);
extern unsigned char ucGetWPOfCol(unsigned char);
extern unsigned char ucGetColOfWP(unsigned char);
extern unsigned long ulGetID(unsigned char ucIx);
extern unsigned char ucSetID(unsigned long *pt2ID, unsigned char *pt2Pos, unsigned char ucSum);

extern unsigned char bCheckHistIDReception(void);
extern unsigned char ucSetAutolocationOveride(unsigned char ucPalOverideFlag);
extern unsigned char ucSet4HistIDs(unsigned long *pt2ID, unsigned char *pt2Pos);
extern unsigned char ucSet1HistID(unsigned long *pt2ID, unsigned char *pt2Pos, unsigned char ucIdx);

extern void RdWAPara( WAParameter *);
extern void WrWAPara( WAParameter *);
extern void ChangeWAPara(void);
unsigned char ucCheckAutolocationOverideCondition();
unsigned char ucReadAutolocationOverideFlag(void);

extern unsigned char * GETpucStartAdrWP(void);

extern unsigned long ulGetZOMID(unsigned char  ucIdx);
extern unsigned char ucGetZOMPosOfID(unsigned long *pt2ID);
extern unsigned char ucGetZomStatus(unsigned char  ucIdx);
extern unsigned char ucGetZomToothTelCtCorrLearnBit(unsigned char  ucIdx);
extern unsigned char ucGetZomToothTelCtCorrNoLearnBit(unsigned char  ucIdx);
extern unsigned char ucGetZomToothTelCtrNoCorr(unsigned char  ucIdx);
extern unsigned char ucGetZomToothTelCtNoLearnMode(unsigned char  ucIdx);
extern unsigned char ucGetZomToothTelCt(unsigned char  ucIdx);
extern unsigned char ucGetZomTelCtLearnBit(unsigned char  ucIdx);
extern unsigned char ucGetZomDeltaMin(unsigned char  ucIdx);
extern unsigned char *ucGetZomAbsComp(unsigned char  ucIdx);
extern unsigned char ucGetZomLqi(unsigned char ucIdx);
extern unsigned short *ushGetZomAbsSums(unsigned char  ucIdx);
extern unsigned char ucGetZOMPalFrameCounter(unsigned char ucIx);
extern unsigned char ucGetZomResetAbsRefFlag(unsigned char ucIx);

extern void PUTtWAparam(unsigned char x, unsigned char i);
extern unsigned char GETtWAparam(unsigned char i);
extern unsigned char GETucWAHistID(unsigned char i);
extern void PUTucWAHistID(unsigned char x, unsigned char i);
extern unsigned char GETucWAHistWP(unsigned char i);
extern void PUTucWAHistWP(unsigned char x, unsigned char i);

extern void SetWaData2NvmFlag(void);
extern void SortBiggest1st(unsigned char *ptVal, unsigned char *ptIx, unsigned char ucMax);

extern unsigned char ui8GetALState(void);
extern unsigned char ucGetLearnMode (void);
extern unsigned char ucHistInConsist(void);
#ifdef FPA
extern void RebuildABSRef(unsigned char ucWP);
extern void ReNewABSRef(void);
extern void PutABSErrorActive(void);
#endif
 extern unsigned char ui8GetDAGAutoLearnState(void);

extern void ClearPWP(void);
extern void Check4PWP(void);
extern unsigned char USEui8PWPofHistCol(unsigned char ui8HistCol);
extern void PUTaucPWPofHistCol(unsigned char ui8HistCol, unsigned char ui8Val);
extern unsigned char ui8CheckNWrPWP(unsigned char ui8HistCol, unsigned char ui8WP);
extern unsigned char GETui8PWPofHistCol(unsigned char ui8HistCol);
extern unsigned char Getui8ColPWPActive(void);

extern unsigned char * GETpucStartAdrWPorPWP(void);
extern unsigned char GETucWPorPWPofHistCol(unsigned char ucCol);

extern unsigned short GETushWAState(void);

extern unsigned char WAInitByDiag(WAParNCfgType *);

extern void PUTucWAHistSensorState(unsigned char ui8Val);
extern unsigned char GETucWAHistSensorState(void);

unsigned char ui8PWPresent(void);
#ifdef FD_CONTROLS_FALLBACK
extern  unsigned char ui8GetPPWP(unsigned char * p2P, unsigned char * p2PWP, unsigned char ui8MinRefPF, unsigned char ui8MinRefPR);
extern void Wr4PWP2NVM(unsigned char * p24PWP);
#endif

#ifdef WAModulTest
void TESTPutDriveTimeInSec(unsigned short ushTimeInSec);
void SetALState(unsigned char ui8State);

#endif

#endif
