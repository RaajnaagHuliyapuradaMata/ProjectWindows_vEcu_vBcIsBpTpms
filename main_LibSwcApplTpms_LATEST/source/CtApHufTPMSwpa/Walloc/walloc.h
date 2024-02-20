

#define cInitialState (unsigned char) 0
#define cNoAxis (unsigned char) 0xCF
#define cFrontAxis (unsigned char) 0x10
#define cOtherAxis (unsigned char) 0x20
#define cBackAxis (unsigned char) 0x20
#define cNoSpin (unsigned char) 0x3F
#define cRightSpin (unsigned char) 0x40
#define cLeftSpin (unsigned char) 0x80

#define cFL (unsigned char) 0
 #define cFR (unsigned char) 1
#define cRL (unsigned char) 2
#define cRR (unsigned char) 3
#define cTI (unsigned char) 4

#define cZOMStatHistER (unsigned char) 0x10
#define cZOMStatER (unsigned char) 0x20
#define cZOMStatWPDec (unsigned char) 0x40

struct ZOMSlot
{
  unsigned long ulID;

  unsigned char ucStatus;

  unsigned char ucProbeCt;
  unsigned char ucLeftCt;
  unsigned char ucRightCt;

#ifdef CONCEPT4
  unsigned char ucFCt;
  unsigned short ushLECt;
  unsigned short ushSECt;
  unsigned char ucStarTiHi;
  unsigned short ushStarTi;
  unsigned short ushLogTime;
#endif
#ifdef AEC
  unsigned char ucXPEvCt;
  unsigned char ucZPEvCt;
  unsigned char ucSpeed;
  unsigned short ushPeakLogT;
  unsigned short ushBurstStarTime;
  unsigned char ucBCt;
  unsigned short ushXPSum;
 #endif
#ifdef FPA
  unsigned char ucFrameCounter;
   unsigned char ucResetABSRefFlag;
   unsigned char ucABSRef[4];
   unsigned short ushMVdN[4];
   unsigned short ushPosCompVal[4];
   unsigned short ushMVdN2[4];
   unsigned short ushPosCompVal2[4];
 #ifdef Test_LOG_ENABLE
  unsigned char ucABSComp[4];
   unsigned char  ucDeltaMin;
   unsigned short ushRelCmpVal[4];
   unsigned char ucToothTelCtCorrLearnBit;
   unsigned char ucToothTelCtCorrNoLearnBit;
   unsigned char ucToothTelCtNoCorr;
   unsigned char ucToothTelCtNoLearnMode;
   unsigned short ushABSRefOffset[4];
   unsigned short ucTelCtLearnBit;
   unsigned short ushLqi;
 #endif
  unsigned char ucToothTelCt;
#if(1)
  unsigned short ushMVdN3[4];
   unsigned short ushPosCompVal3[4];
   unsigned short ushMVdN4[4];
   unsigned short ushPosCompVal4[4];
 #endif
#endif
  unsigned short ushRssiSum;
};

#ifdef WALLOC_INT
unsigned char ucGetERState(void);
unsigned char ucSumCtID(unsigned char ucMinCt, unsigned short *ushRet);
void SetZOMWP(unsigned char ucIx,unsigned char ucWP);
unsigned char bCheckHistIDReception(void);
unsigned char ucGetHistoryState(void);
unsigned short ushAlignZOM(unsigned short ushERSlot);
unsigned char ucNrOfBitSet(unsigned short ushTarget);
void PutLocatError(unsigned char ucTipicoDiErrori, unsigned char ucZomSlot);
unsigned char ucGetLocatError(unsigned char ucZomSlot);

WAParameter tWAPar;
struct ZOMSlot tZOM[cSumWE];
#else
extern unsigned char ucGetERState(void);
extern unsigned char ucSumCtID(unsigned char ucMinCt, unsigned short *ushRet);
extern void SetZOMWP(unsigned char ucIx,unsigned char ucWP);
extern unsigned short ushAlignZOM(unsigned short ushERSlot);
extern unsigned char ucNrOfBitSet(unsigned short ushTarget);
extern void PutLocatError(unsigned char ucTipicoDiErrori, unsigned char ucZomSlot);
extern unsigned char ucGetLocatError(unsigned char ucZomSlot);

extern WAParameter tWAPar;
extern struct ZOMSlot tZOM[cSumWE];
#endif
