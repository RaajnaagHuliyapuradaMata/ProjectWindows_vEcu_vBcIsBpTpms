/*
 *(c) Huf Electronics GmbH     BEE1     08/2012
 *================================================================================================
 *
 *$Archive: /LIB/WAF/work/walloc.h $
 *
 *file status:   under construction
 *
 *------------------------------------------------------------------------------------------------
 *
 *author:        Peter Brand                Huf Electronics GmbH
 *
 *intials:       pb
 *
 *
 *
 *Modul Description
 *
 *
 *Global description: 
 *Purpose: 
 *contains objects of the so called us warnalgorithm as described in the specification ..\produktgruppe\tec\spec\nhtsa\pfl_us01.doc
 *
 *
 *Modul Modification
 *
 *
 *
 * $Log: /LIB/WAF/work/walloc.h $
 * 
 * 2     21.08.12 17:52 Peter
 * new module structure (FPA and AEC, CA seperated)
 * 
 * 1     17.08.12 17:27 Peter
 * 
 * 1     10.08.12 10:09 Peter
 * 
*/
/*
macro
*/
#define cInitialState (unsigned char) 0     /* constants for tZOM[x].ucStatus */
#define cNoAxis (unsigned char) 0xCF
#define cFrontAxis (unsigned char) 0x10
#define cOtherAxis (unsigned char) 0x20
#define cBackAxis (unsigned char) 0x20
#define cNoSpin (unsigned char) 0x3F
#define cRightSpin (unsigned char) 0x40
#define cLeftSpin (unsigned char) 0x80

#define cFL (unsigned char) 0 // index 2 access wheel position specific way stretch information N timestamp
#define cFR (unsigned char) 1
#define cRL (unsigned char) 2
#define cRR (unsigned char) 3
#define cTI (unsigned char) 4

#define cZOMStatHistER (unsigned char) 0x10
#define cZOMStatER (unsigned char) 0x20
#define cZOMStatWPDec (unsigned char) 0x40

/* 
typedefs
*/

struct ZOMSlot
{
  unsigned long ulID;           /* identifier of system sensor electronic (s.e.) */

  unsigned char ucStatus;       /* status of s.e. identification :
                                MSB X 1 -> n.c.
                                    X 1 -> WP identification possible
                                    X 1 -> ER
                                    X 1 -> history ER

                                    X 1 -> wheel pos rear right; combination  0 means no w.p.
                                    X 1 -> wheel pos rear left;               0
                                    X 1 -> wheel pos front right;             0
                                LSB X 1 -> wheel pos front left;              0 */

  unsigned char ucProbeCt;      /* amount of tel received events of this s.e. */
  unsigned char ucLeftCt;       /* amount of tel received events of this s.e. in left spinning mode */
  unsigned char ucRightCt;      /* amount of tel received events of this s.e. in right spinning mode */

#ifdef CONCEPT4
  unsigned char ucFCt;          /* FrontAxisCounter */
  unsigned short ushLECt;       /* LastEdgeCount */
  unsigned short ushSECt;       /* SumEdgeCtunt */
  unsigned char ucStarTiHi;
  unsigned short ushStarTi;
  unsigned short ushLogTime;
#endif
#ifdef AEC
  unsigned char ucXPEvCt;       /* free running tx counter (60 = MaxVal) */
  unsigned char ucZPEvCt;       /* free running ct'er 4 prevented peak events */
  unsigned char ucSpeed;
  unsigned short ushPeakLogT;
  unsigned short ushBurstStarTime;
  unsigned char ucBCt;
  unsigned short ushXPSum;    // no more just for statistics
#endif
#ifdef FPA
  unsigned char ucFrameCounter;         // Frame counter of PAL telegramme
  unsigned char ucResetABSRefFlag;      // Flag is set when a reset of the reference point is needed after a rollback or a backward drive
  unsigned char ucABSRef[4];			// ABS sensor's freerunning tick info at very 1st tel reception at all 4 wheel pos ( = index)
  unsigned short ushMVdN[4];			// dN's mean value (index is pos R)
  unsigned short ushPosCompVal[4];		// indicator for constant sending position
  unsigned short ushMVdN2[4];			// 2nd dN2's mean value (index is pos R)
  unsigned short ushPosCompVal2[4];		// 2nd indicator for constant sending position
#ifdef Test_LOG_ENABLE
  unsigned char ucABSComp[4];			// ABS sensor's tick after linearization (value between 0 and 96)
  unsigned char  ucDeltaMin;			// Distance between first and second minimum
  unsigned short ushRelCmpVal[4];		// indicator for constant sending position,  this is the one currently used within the algo      
  unsigned char ucToothTelCtCorrLearnBit;		// Number of received telegramms with valid PAL Value
  unsigned char ucToothTelCtCorrNoLearnBit;		// Number of received telegramms with valid PAL Value
  unsigned char ucToothTelCtNoCorr;		// Number of received telegramms with no correlation (PAL = 1 / 255)
  unsigned char ucToothTelCtNoLearnMode;		// Number of received telegramms out of learn window  (PAL = 0 )
  unsigned short ushABSRefOffset[4];    // Abs Offset after overflow
  unsigned short ucTelCtLearnBit; // Number or received telegramm with learn bit set (only Pal and akastd35 are considered)
  unsigned short ushLqi; // learn quality indicator DAG
#endif
  unsigned char ucToothTelCt;  
#if(1)
  unsigned short ushMVdN3[4];			// 2nd dN2's mean value (index is pos R)
  unsigned short ushPosCompVal3[4];		// 2nd indicator for constant sending position
  unsigned short ushMVdN4[4];			// 2nd dN2's mean value (index is pos R)
  unsigned short ushPosCompVal4[4];		// 2nd indicator for constant sending position
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