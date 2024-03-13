

#define cInitialState (uint8) 0
#define cNoAxis (uint8) 0xCF
#define cFrontAxis (uint8) 0x10
#define cOtherAxis (uint8) 0x20
#define cBackAxis (uint8) 0x20
#define cNoSpin (uint8) 0x3F
#define cRightSpin (uint8) 0x40
#define cLeftSpin (uint8) 0x80

#define cFL (uint8) 0
#define cFR (uint8) 1
#define cRL (uint8) 2
#define cRR (uint8) 3
#define cTI (uint8) 4

#define cZOMStatHistER (uint8) 0x10
#define cZOMStatER (uint8) 0x20
#define cZOMStatWPDec (uint8) 0x40

struct ZOMSlot
{
  uint32 ulID;

  uint8 ucStatus;

  uint8 ucProbeCt;
  uint8 ucLeftCt;
  uint8 ucRightCt;

#ifdef CONCEPT4
  uint8 ucFCt;
  uint16 ushLECt;
  uint16 ushSECt;
  uint8 ucStarTiHi;
  uint16 ushStarTi;
  uint16 ushLogTime;
#endif
#ifdef AEC
  uint8 ucXPEvCt;
  uint8 ucZPEvCt;
  uint8 ucSpeed;
  uint16 ushPeakLogT;
  uint16 ushBurstStarTime;
  uint8 ucBCt;
  uint16 ushXPSum;
 #endif
#ifdef FPA
  uint8 ucFrameCounter;
   uint8 ucResetABSRefFlag;
   uint8 ucABSRef[4];
   uint16 ushMVdN[4];
   uint16 ushPosCompVal[4];
   uint16 ushMVdN2[4];
   uint16 ushPosCompVal2[4];
 #ifdef Test_LOG_ENABLE
  uint8 ucABSComp[4];
   uint8  ucDeltaMin;
   uint16 ushRelCmpVal[4];
   uint8 ucToothTelCtCorrLearnBit;
   uint8 ucToothTelCtCorrNoLearnBit;
   uint8 ucToothTelCtNoCorr;
   uint8 ucToothTelCtNoLearnMode;
   uint16 ushABSRefOffset[4];
   uint16 ucTelCtLearnBit;
   uint16 ushLqi;
 #endif
  uint8 ucToothTelCt;
#if(1)
  uint16 ushMVdN3[4];
   uint16 ushPosCompVal3[4];
   uint16 ushMVdN4[4];
   uint16 ushPosCompVal4[4];
 #endif
#endif
  uint16 ushRssiSum;
};

#ifdef WALLOC_INT
uint8 ucGetERState(void);
uint8 ucSumCtID(uint8 ucMinCt, uint16 *ushRet);
void SetZOMWP(uint8 ucIx,uint8 ucWP);
uint8 bCheckHistIDReception(void);
uint8 ucGetHistoryState(void);
uint16 ushAlignZOM(uint16 ushERSlot);
uint8 ucNrOfBitSet(uint16 ushTarget);
void PutLocatError(uint8 ucTipicoDiErrori, uint8 ucZomSlot);
uint8 ucGetLocatError(uint8 ucZomSlot);

WAParameter tWAPar;
struct ZOMSlot tZOM[cSumWE];
#else
extern uint8 ucGetERState(void);
extern uint8 ucSumCtID(uint8 ucMinCt, uint16 *ushRet);
extern void SetZOMWP(uint8 ucIx,uint8 ucWP);
extern uint16 ushAlignZOM(uint16 ushERSlot);
extern uint8 ucNrOfBitSet(uint16 ushTarget);
extern void PutLocatError(uint8 ucTipicoDiErrori, uint8 ucZomSlot);
extern uint8 ucGetLocatError(uint8 ucZomSlot);

extern WAParameter tWAPar;
extern struct ZOMSlot tZOM[cSumWE];
#endif
