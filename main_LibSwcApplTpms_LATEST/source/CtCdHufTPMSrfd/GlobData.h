
/*****************************************************************************
| Project Name: Renesas Starter Kit  with Atmel Receiver ATAL
|    File Name: ata_GlobData.h
|
|  Description: Header for the module GlobData.c
|
|-----------------------------------------------------------------------------
|               C O P Y R I G H T
|-----------------------------------------------------------------------------
| Copyright (c) Huf Electronics GmbH ENTS4   2015      All rights reserved.
|
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
|   as          Schubert Andreas   Huf Electronics GmbH
|
|
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date        Ver   Author  Description
| ----------  ----  ------  --------------------------------------------------
|  23.03.15    0.0    as     Creation
|
|
|
|
|
|*****************************************************************************/


#ifndef GLOBDATA_H
#define GLOBDATA_H
//#define HUF_DATA_ADDRESS                   0x07FD00u

/* Hier den Bereich für die Programm Checksum freihalten*/
//#pragma asm
//  .section ".checksum_text"
//  .word 0x07FD00 /* Address 4 huf data block example SG serial number*/
//  .word 0x0036363933 /* TEST AUSGABE TFS Change Set Nr. CS_3966 der SW Version zum Auslesen über Diagnose*/
//  .word 0x16200105 /*Datum 05.01.2016 --> 16 20 01 05 */
//  .byte 'D','M','C','2','0','0','1','3' /* Huf interne Sofware Bezeichnung*/
//#pragma endasm

/* Hier den Bereich für die Programm Checksum freihalten*/
#pragma asm
  .section ".checksum_text"
  .align  4
  .globl  _HufSwVersion
   _HufSwVersion:
	.byte 'C','h','e','c','k','s','u','m' /*0x0001 06A8*/
	.word 0x0000 /**0x0001 06B0 =Checksummen Eintrag! bei Auslieferung*/
  .byte ' ','D','C','M',cINTEGRATION+0x30,((cAUSLIEFVERSION /10)+0x30),((cAUSLIEFVERSION %10)+0x30),((cINTERNVERSION /10)+0x30),((cINTERNVERSION %10)+0x30) /* Huf interne alphanum Software Bezeichnung*/
  .globl  _SoftwareVersionInformation
   _SoftwareVersionInformation:
	.byte cSWJAHR,cSWKW,cSWVERSIONINKW /* Huf interne alpha Software Bezeichnung*/
	.word 0x16200110 /*Datum 10.01.2016 --> 16 20 01 08 */  
  //.byte '3','9','6','6'  /*TFS Change Set Nr. CS_3966 der SW Version*/
  .word 0x07FD00 /* Address 4 huf data block example SG serial number*/
#pragma endasm

//#define HUF_SOFTWARE_DATA_ADDRESS  _checksum_text
/********************/
/* Defines          */
/********************/
//#define V24_64F1L  /* V24  Port P0_3/P0_2 bzw. RS232 für Ausgabe der Empfangsdaten aktiv ACHTUNG! Port für CAN schnittstelle MFA2*/

#define RB_DATA_LEN (unsigned char) 24
#define RB_RS_BUF_LEN (unsigned char) 6

/* Betriebsmodi der Räder - Warum kein enum? */
enum eModiRE
{
  // Modi - von der Schnittstelle vorgegeben
  cMode1a     = 1,
  cMode1b     = 2,
  cMode1c     = 3,
  cMode1d     = 4,
  cMode1e     = 5,
  cModeTC     = 6,
  cParaRead   = 7,
  // restliche Modi
  cMode2      = 8,
  cMode3abc   = 9,
  cM4pre      = 10,  // RE G3
  cM4int      = 11,  // RE G3; = M4a G3NFZ
  cM4cont     = 12,  // RE G3; = M4b G3NFZ
  cModeTT     = 13,  // RE G3nfz
  cEv_GenFreeTel = 14,  // sensor GX TelGen
  cLastMode   = 0xce,
  cKeineDaten = 0xff
};

// RE wakeup time deviation and default value(s)
#define cSENDE_INTERVALL_M23     800  // 800ms Sendeintervall RE G2 in Mode 2 und 3
#define cSENDE_INTERVALL_REG3_M23    1000  // 1000ms Sendeintervall RE G3 in Mode 2 und 3
#define cTw_Def 3000 // 3second most common wakeuptime
#define cM4SendInterval 2000 // 2sec send interval 4 burst mode 4
#define cM4DelInterval  1000

// Die Pegelabschnitte aus der Zeit der Analogsignale

// Anzahl der Räder, die verarbeitet werden können
#define cDEFAULT_ANZAHL    32
#define cANZAHL_RAEDER     32


#define cNO_INTERVALL  0xffff
#define cALL_INTERVALL 0x1

#define cSTATUS_POS 9           // Die Position des Stautusbytes in der RE-Sendenachricht
#define cDREHINFO_POS_G3ONLY 10 // spin info's byte index in RE G3only telegramm

#define cMaxRfTelGrossLen 13    // (former 15) gross length of RF tel in byte (includes Sync bytes as well as CRC bytes)
#define cG2NeTeLen 10           // Nr of byte in G2 tel (inc. sync but without CRC)
#define cG2TeLen 12             // Nr of byte in G2 telegram (including syncbytes and CRC)
#define cG3onlyTeLen 13         // Nr of byte in G3 only telegram (including syncbytes and CRC)
#define cG3NfzAliveLen 7        // Nr of byte in G3NFZ alive telegramm telegram (including syncbytes and 1 byte CRC)

#define cG35BeruLTeLen (unsigned char) 13
#define cG35BeruMedTeLen (unsigned char) 11
#define cG35BeruSTeLen (unsigned char) 9
#define cG35AKdefTeLen (unsigned char) 10

#define cBeruTel (unsigned char) 0
#define cAKTel (unsigned char) 1
#define cBiPhaseRaw (unsigned char) 2
#define cManchesterRaw (unsigned char) 3
#define cAK35Multi (unsigned char) 4

#define cTelGen (unsigned char) 1 // telegram generator active
#define cREG2Sim (unsigned char) 4
#define cREG3LkwSim (unsigned char) 0x10
#define cREG3onlySim  (unsigned char) 0x20
#define cREG35Sim (unsigned char) 0x40
#define cHFNoise (unsigned char) 0x80

#define cFsel433 (unsigned char) 0x01
#define cFsel315 (unsigned char) 0x02

// constants interprates tGlobal.ucRFTransPar
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






// Folgende Zeitparameter sind im Statediagramm zur Zeit (4.3.2003) enthalten:
// Mode 1a:
//   o: tm = o * tw;
//   p: ta = p * tw;
//   q: tx = 16 * q * tw;
// Mode 1b:
//   -: tm = tw;
//   t: ta = t * tw;
//   u: tx = u * tw;
// Mode 1c:
//   -: tm = tw;
//   v: tt = v * tw;
// Mode 1d:
//   x: tm = 16 * x * tw;
//   w: ta = 16 * w * tw;
//   u: tx = 16 * x * tw;
// Mode 1e:
//   p: tm = p * tw; ta = p * tw;
// Mode TC:
//   -: ts = 1 * tx;
// Mode 2:
//   -: tm = 0,8s;
//   -: tx = 0,8s;
//   -: ts = 255 * tx;
// Mode 3:
//   -: tm = 0,8s;
//   -: tx = 0,8s;
//   -: ts = 255 * tx;
//
// Systemkonstanten:
//  tm: Meßintervall für Druck und Temperatur
//  tw: Wakeupintervall (3s d.h.[2,4s;3,6s])
//  tx: Sendeintervall
//  ta: Meßintervall Beschleunigungssensor (Rollswitch)
//  ts: Aufenthaltszeit im betreffenden Zustand

#define cMAXANZ_BURST_BYTES (unsigned char) 8

//uint8 TransCanData[8];

//uint8 ucIRQ_ATA_activ;

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
  eKommandoUeberlauf    // Als Grenze, damit die Abfrage leichter ist.
};

typedef void (* fp2VoidFctVoid) (void);

/*********************/
/* Data Declarations */
/*********************/
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
  unsigned char ucCode; // 1 = BiPhase 2 = Manchestere
  unsigned char ucRepeat;
  unsigned char ucTimeDist;   // time distcance between RF tels with same contenet (1/5msec)
  unsigned char ucTeLen;
  unsigned char ucCoRec;
  unsigned char ucRSAnt[7]; // mean RSSI value at antenna Index+1
  unsigned char ucTelByte[20];
};

typedef union
{
  struct FreeRFTelType Tel;
  unsigned char ucRawByte[sizeof (struct FreeRFTelType)];
}tFreeRFTelType;

extern tFreeRFTelType tFRF;


extern unsigned char ucTSSSendBuffer    [cANZAHL_RAEDER][20];    // exclude CRC, only AktSendBuffer includes CRC
//extern unsigned char ucRSSIBuffer       [cANZAHL_RAEDER][cMAXANZ_ANT][cMAXANZ_RSSI_PEGEL];

struct ReceiverType
{
  unsigned char ucPar;
  unsigned char ucOpMod;
  unsigned char ucSensType;
  unsigned char ucETU;  // 1/Baudraute in usec
  unsigned long ulFilterID;
  unsigned char ucAntSense;
};
// constant for ReceiverType direct access
// 4 ucOpMode:
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

/*************************************/
/* AK35 Ablage RH850 Test            */
/*************************************/
typedef struct
{
  //unsigned char ucType;
  uint32 ulTime;
  //unsigned char ucBaseRS;
  uint8 ucNoise; // average RSSI--> CR_1211_150_010-> NoiseLevel 
  uint8 aucTel[RB_DATA_LEN + RB_RS_BUF_LEN]; /* 24Bytes + 6Bytes */
}tRecRFTelData;

/* Union für Byteweisen Zugriff auf AK35ToCANbuffer Datenstruktur */
typedef union
{
 tRecRFTelData AK35Data;
 unsigned char ucByteAccess[(unsigned char) sizeof(tRecRFTelData)];
}tRecRFTelDecl;

volatile tRecRFTelDecl tRecRFTel;
// Falsch const tRecRFTelDecl tRecRFTel;


struct tTrigselStatesDecl
{
  uint8 bSending     : 1;
  uint8 bTimeToDelay : 1;     // Wird beim Start und Empfang eines Datensatzes vom PC gesetzt
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
  unsigned char bTimer_tr              : 1;  // RE G3
  unsigned char bData_M4               : 1;  // RE G3
  unsigned char bData_r                : 1;  // RE G3

  unsigned char bData_m;    // Zum Testen für den Debugger ein Byte statt ein Bit!

  enum eModiRE  ucREState;
  enum eModiRE  ucLastREState;
  enum eModiRE  ucLastLastREState;

  unsigned short ushAktuTelSendInterval;
  unsigned short ushAktuInterval_ta;
  unsigned short ushAktuInterval_tm;
  unsigned short ushAktuInterval_tr;   // RE G3
  unsigned short ushCurrent_tw;        // RE G3

  unsigned char ucM4TelCt;    // RE G3
  unsigned char ucM4DelCt; // RE G3

  unsigned char ucTelType;
};

extern struct tREControlDataDecl tREControlData[cANZAHL_RAEDER];

#endif /* GLOBDATA_H */
