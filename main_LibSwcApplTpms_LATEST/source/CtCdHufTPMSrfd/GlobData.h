

#ifndef GLOBDATA_H
#define GLOBDATA_H
   #pragma asm
  .section ".checksum_text"
  .align  4
  .globl  _HufSwVersion
   _HufSwVersion:
   .byte 'C','h','e','c','k','s','u','m'
   .word 0x0000
  .byte ' ','D','C','M',cINTEGRATION+0x30,((cAUSLIEFVERSION /10)+0x30),((cAUSLIEFVERSION %10)+0x30),((cINTERNVERSION /10)+0x30),((cINTERNVERSION %10)+0x30)
  .globl  _SoftwareVersionInformation
   _SoftwareVersionInformation:
   .byte cSWJAHR,cSWKW,cSWVERSIONINKW
   .word 0x16200110
  .word 0x07FD00
#pragma endasm

#define RB_DATA_LEN (unsigned char) 24
#define RB_RS_BUF_LEN (unsigned char) 6

enum eModiRE
{
   cMode1a     = 1,
  cMode1b     = 2,
  cMode1c     = 3,
  cMode1d     = 4,
  cMode1e     = 5,
  cModeTC     = 6,
  cParaRead   = 7,
  cMode2      = 8,
  cMode3abc   = 9,
  cM4pre      = 10,
   cM4int      = 11,
   cM4cont     = 12,
   cModeTT     = 13,
   cEv_GenFreeTel = 14,
   cLastMode   = 0xce,
  cKeineDaten = 0xff
};
 #define cSENDE_INTERVALL_M23     800
 #define cSENDE_INTERVALL_REG3_M23    1000
 #define cTw_Def 3000
 #define cM4SendInterval 2000
 #define cM4DelInterval  1000
  #define cDEFAULT_ANZAHL    32
#define cANZAHL_RAEDER     32

#define cNO_INTERVALL  0xffff
#define cALL_INTERVALL 0x1

#define cSTATUS_POS 9
 #define cDREHINFO_POS_G3ONLY 10

#define cMaxRfTelGrossLen 13
 #define cG2NeTeLen 10
 #define cG2TeLen 12
 #define cG3onlyTeLen 13
 #define cG3NfzAliveLen 7

#define cG35BeruLTeLen (unsigned char) 13
#define cG35BeruMedTeLen (unsigned char) 11
#define cG35BeruSTeLen (unsigned char) 9
#define cG35AKdefTeLen (unsigned char) 10

#define cBeruTel (unsigned char) 0
#define cAKTel (unsigned char) 1
#define cBiPhaseRaw (unsigned char) 2
#define cManchesterRaw (unsigned char) 3
#define cAK35Multi (unsigned char) 4

#define cTelGen (unsigned char) 1
 #define cREG2Sim (unsigned char) 4
#define cREG3LkwSim (unsigned char) 0x10
#define cREG3onlySim  (unsigned char) 0x20
#define cREG35Sim (unsigned char) 0x40
#define cHFNoise (unsigned char) 0x80

#define cFsel433 (unsigned char) 0x01
#define cFsel315 (unsigned char) 0x02
 #define cFSK (unsigned char) 0x40

#define cCWHi (unsigned char) 0x20
#define cCWLo (unsigned char) 0x10

#define cTransRadStren (unsigned char) 0x0C
#define cTransRadLo (unsigned char) 0
#define cTransRadMed (unsigned char) 0x04
#define cTransRadHi (unsigned char) 0x08
#define cTrandRadOverDose (unsigned char) 0x0C

#define cFsel433 (unsigned char) 0x01
#define cFsel315 (unsigned char) 0x02

#define cRSSI_STRONG (unsigned char) 100
#define cRSSI_MED (unsigned char) 60
#define cRSSI_LOW (unsigned char) 26

                 #define cMAXANZ_BURST_BYTES (unsigned char) 8

enum eBefehl
{
  eStatusRequest   = 0,
  eRE_Daten        = 1,
  eGolbaleDaten    = 2,
  eKommandoStart   = 3,
  eKommandoStop    = 4,
  eKommandoVersion = 5,
  eKommandoKalib   = 6,
  eFreeRFTel       = 7,
  eRecPar          = 8,
  eReqCurTel       = 9,
  eLFCfg           = 10,
  eKommandoUeberlauf
 };

typedef void (* fp2VoidFctVoid) (void);

struct BeruLType
{
    unsigned short ushPreamble;
    unsigned char ucCmdId;
    unsigned long ulID;
    unsigned char ucP;
    unsigned char ucT;
    unsigned char ucRBL;
    unsigned char ucStatus;
    unsigned char ucSpin;
};
struct BeruMedType
{
    unsigned short ushPreamble;
    unsigned char ucCmdId;
    unsigned long ulID;
    unsigned char ucP;
    unsigned char ucT;
    unsigned char ucSpin;
};
struct BeruSType
{
    unsigned short ushPreamble;
    unsigned char ucCmdId;
    unsigned long ulID;
    unsigned char ucSpin;
};
struct AKdefType
{
    unsigned short ushPreamble;
    unsigned char ucCmdId;
    unsigned long ulID;
    unsigned char ucP;
    unsigned char ucT;
};
union SendBufType
{
    struct BeruLType tBeruL;
    struct BeruMedType tBeruMed;
    struct BeruSType tBeruS;
    struct AKdefType tAKdef;
    unsigned char ucByte[20];
};
extern union SendBufType uSendBuf[cANZAHL_RAEDER];

 struct FreeRFTelType
{
  unsigned char ucCode;
   unsigned char ucRepeat;
  unsigned char ucTimeDist;
   unsigned char ucTeLen;
  unsigned char ucCoRec;
  unsigned char ucRSAnt[7];
   unsigned char ucTelByte[20];
};

typedef union
{
  struct FreeRFTelType Tel;
  unsigned char ucRawByte[sizeof (struct FreeRFTelType)];
}tFreeRFTelType;

extern tFreeRFTelType tFRF;

extern unsigned char ucTSSSendBuffer    [cANZAHL_RAEDER][20];
 struct ReceiverType
{
  unsigned char ucPar;
  unsigned char ucOpMod;
  unsigned char ucSensType;
  unsigned char ucETU;
   unsigned long ulFilterID;
  unsigned char ucAntSense;
};
 #define cExtRecON (unsigned char) 0x20

typedef union
{
  struct ReceiverType ParDat ;
  unsigned char ucRawByte[sizeof (struct ReceiverType)] ;
}tReceiverType;

extern tReceiverType tRec;

struct LFCfgtype
{
  unsigned char ucLen;
  unsigned short ushWkUpID;
  unsigned char aucDat2Send[12];
  unsigned char ucRep;
  unsigned char ucSendCyle;
  unsigned char OpMode;
};
typedef union
{
  struct LFCfgtype Dat;
  unsigned char ucByte[sizeof(struct LFCfgtype)];
}tLFCfgType;
extern tLFCfgType tLFCfg;

typedef struct
{
  uint32 ulTime;
  uint8 ucNoise;
  uint8 aucTel[RB_DATA_LEN + RB_RS_BUF_LEN];
}tRecRFTelData;

typedef union
{
 tRecRFTelData AK35Data;
 unsigned char ucByteAccess[(unsigned char) sizeof(tRecRFTelData)];
}tRecRFTelDecl;

volatile tRecRFTelDecl tRecRFTel;
struct tTrigselStatesDecl
{
  uint8 bSending     : 1;
  uint8 bTimeToDelay : 1;
   uint8 bKalibrating : 1;
  uint8 bReceiving   : 1;
  uint8 bExtReceiving: 1;
  uint8 reserved5    : 1;
  uint8 reserved6    : 1;
  uint8 reserved7    : 1;
};

extern struct tTrigselStatesDecl tTrigselStates;

struct tREControlDataDecl
{
  unsigned char bLFCode0Received       : 1;
  unsigned char bLFCode2Received       : 1;
  unsigned char bLFCode3Received       : 1;
  unsigned char bLFCode4Received       : 1;
  unsigned char bLFCode5Received       : 1;
  unsigned char bLFCode6Received       : 1;
  unsigned char bLFCode7Received       : 1;
  unsigned char bTransmissionReqired   : 1;

  unsigned char bLFCode12Received      : 1;
  unsigned char bDataAvailable         : 1;
  unsigned char bDataChanged           : 1;
  unsigned char bModeChanged           : 1;
  unsigned char bTxTimerElapsed        : 1;
  unsigned char bGoToSleepTimerElapsed : 1;
  unsigned char bModeTCResponseSent    : 1;
  unsigned char bSleepTimerToggled     : 1;

  unsigned char bTimer_ta              : 1;
  unsigned char bTimer_tm              : 1;
  unsigned char bData_a                : 1;
  unsigned char bTimerMode23           : 1;
  unsigned char bTimer_tr              : 1;
   unsigned char bData_M4               : 1;
   unsigned char bData_r                : 1;

  unsigned char bData_m;

  enum eModiRE  ucREState;
  enum eModiRE  ucLastREState;
  enum eModiRE  ucLastLastREState;

  unsigned short ushAktuTelSendInterval;
  unsigned short ushAktuInterval_ta;
  unsigned short ushAktuInterval_tm;
  unsigned short ushAktuInterval_tr;
   unsigned short ushCurrent_tw;

  unsigned char ucM4TelCt;
   unsigned char ucM4DelCt;

  unsigned char ucTelType;
};

extern struct tREControlDataDecl tREControlData[cANZAHL_RAEDER];

#endif
