#pragma once

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

#define RB_DATA_LEN (uint8) 24
#define RB_RS_BUF_LEN (uint8) 6

enum eModiRE{
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
#define cG35BeruLTeLen (uint8) 13
#define cG35BeruMedTeLen (uint8) 11
#define cG35BeruSTeLen (uint8) 9
#define cG35AKdefTeLen (uint8) 10
#define cBeruTel (uint8) 0
#define cAKTel (uint8) 1
#define cBiPhaseRaw (uint8) 2
#define cManchesterRaw (uint8) 3
#define cAK35Multi (uint8) 4
#define cTelGen (uint8) 1
#define cREG2Sim (uint8) 4
#define cREG3LkwSim (uint8) 0x10
#define cREG3onlySim  (uint8) 0x20
#define cREG35Sim (uint8) 0x40
#define cHFNoise (uint8) 0x80
#define cFsel433 (uint8) 0x01
#define cFsel315 (uint8) 0x02
#define cFSK (uint8) 0x40
#define cCWHi (uint8) 0x20
#define cCWLo (uint8) 0x10
#define cTransRadStren (uint8) 0x0C
#define cTransRadLo (uint8) 0
#define cTransRadMed (uint8) 0x04
#define cTransRadHi (uint8) 0x08
#define cTrandRadOverDose (uint8) 0x0C
#define cFsel433 (uint8) 0x01
#define cFsel315 (uint8) 0x02
#define cRSSI_STRONG (uint8) 100
#define cRSSI_MED (uint8) 60
#define cRSSI_LOW (uint8) 26
#define cMAXANZ_BURST_BYTES (uint8) 8

enum eBefehl{
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

struct BeruLType{
   uint16 ushPreamble;
   uint8 ucCmdId;
   uint32 ulID;
   uint8 ucP;
   uint8 ucT;
   uint8 ucRBL;
   uint8 ucStatus;
   uint8 ucSpin;
};

struct BeruMedType{
   uint16 ushPreamble;
   uint8 ucCmdId;
   uint32 ulID;
   uint8 ucP;
   uint8 ucT;
   uint8 ucSpin;
};

struct BeruSType{
   uint16 ushPreamble;
   uint8 ucCmdId;
   uint32 ulID;
   uint8 ucSpin;
};

struct AKdefType{
   uint16 ushPreamble;
   uint8 ucCmdId;
   uint32 ulID;
   uint8 ucP;
   uint8 ucT;
};

union SendBufType{
   struct BeruLType tBeruL;
   struct BeruMedType tBeruMed;
   struct BeruSType tBeruS;
   struct AKdefType tAKdef;
   uint8 ucByte[20];
};

extern union SendBufType uSendBuf[cANZAHL_RAEDER];

struct FreeRFTelType{
   uint8 ucCode;
   uint8 ucRepeat;
   uint8 ucTimeDist;
   uint8 ucTeLen;
   uint8 ucCoRec;
   uint8 ucRSAnt[7];
   uint8 ucTelByte[20];
};

typedef union{
   struct FreeRFTelType Tel;
   uint8 ucRawByte[sizeof (struct FreeRFTelType)];
}tFreeRFTelType;

extern tFreeRFTelType tFRF;

extern uint8 ucTSSSendBuffer    [cANZAHL_RAEDER][20];

struct ReceiverType{
   uint8 ucPar;
   uint8 ucOpMod;
   uint8 ucSensType;
   uint8 ucETU;
   uint32 ulFilterID;
   uint8 ucAntSense;
};

#define cExtRecON (uint8) 0x20

typedef union{
   struct ReceiverType ParDat ;
   uint8 ucRawByte[sizeof (struct ReceiverType)] ;
}tReceiverType;

extern tReceiverType tRec;

struct LFCfgtype{
   uint8 ucLen;
   uint16 ushWkUpID;
   uint8 aucDat2Send[12];
   uint8 ucRep;
   uint8 ucSendCyle;
   uint8 OpMode;
};

typedef union{
   struct LFCfgtype Dat;
   uint8 ucByte[sizeof(struct LFCfgtype)];
}tLFCfgType;
extern tLFCfgType tLFCfg;

typedef struct{
   uint32 ulTime;
   uint8 ucNoise;
   uint8 aucTel[RB_DATA_LEN + RB_RS_BUF_LEN];
}tRecRFTelData;

typedef union{
   tRecRFTelData AK35Data;
   uint8 ucByteAccess[(uint8) sizeof(tRecRFTelData)];
}tRecRFTelDecl;

volatile tRecRFTelDecl tRecRFTel;

struct tTrigselStatesDecl{
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

struct tREControlDataDecl{
   uint8 bLFCode0Received       : 1;
   uint8 bLFCode2Received       : 1;
   uint8 bLFCode3Received       : 1;
   uint8 bLFCode4Received       : 1;
   uint8 bLFCode5Received       : 1;
   uint8 bLFCode6Received       : 1;
   uint8 bLFCode7Received       : 1;
   uint8 bTransmissionReqired   : 1;
   uint8 bLFCode12Received      : 1;
   uint8 bDataAvailable         : 1;
   uint8 bDataChanged           : 1;
   uint8 bModeChanged           : 1;
   uint8 bTxTimerElapsed        : 1;
   uint8 bGoToSleepTimerElapsed : 1;
   uint8 bModeTCResponseSent    : 1;
   uint8 bSleepTimerToggled     : 1;
   uint8 bTimer_ta              : 1;
   uint8 bTimer_tm              : 1;
   uint8 bData_a                : 1;
   uint8 bTimerMode23           : 1;
   uint8 bTimer_tr              : 1;
   uint8 bData_M4               : 1;
   uint8 bData_r                : 1;
   uint8 bData_m;

   enum eModiRE  ucREState;
   enum eModiRE  ucLastREState;
   enum eModiRE  ucLastLastREState;

   uint16 ushAktuTelSendInterval;
   uint16 ushAktuInterval_ta;
   uint16 ushAktuInterval_tm;
   uint16 ushAktuInterval_tr;
   uint16 ushCurrent_tw;
   uint8 ucM4TelCt;
   uint8 ucM4DelCt;
   uint8 ucTelType;
};

extern struct tREControlDataDecl tREControlData[cANZAHL_RAEDER];
