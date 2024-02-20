

#ifndef _CDDECODER_X_H
#define _CDDECODER_X_H
#include "Compiler_Cfg.h"

#define cRESET_CDD     0x00
#define cPRESTART_CDD  0x01
#define cFSYNC_CDD     0x02
#define cSYNC_CDD      0x03
#define cREC_CDD       0x04
#define cPreSync (unsigned char) 0x05
#define cStart   (unsigned char) 0
#define cMeasure (unsigned char) 1
#define cConfirmManchestere (unsigned char) 2
#define cConfirmBiphase (unsigned char) 3

#define cNO_ERROR_CDD            0x00
#define cSHORT_SYNCBIT_CDD       0x01
#define cLONG_SYNCBIT_CDD        0x02
#define cCORR_OVERFLOW_CDD       0x04
#define cTO_SYREC_CDD            0x08
#define cBAD_CRC_CDD             0x20
#define cMIN_SYNCBIT_CDD         0x40
#define cMAX_SYNCBIT_CDD         0x80
#define cSHORTEL                 0x0C
#define cBITERRORINSYNC          0x03
#define cBAD_AK35_SYNC1          0x05
#define NEWDECOTTING
#ifndef cAUTOCOD
#define cAK35ONLY
#endif
#define cBAUD_RATE_19200
 #ifdef cBAUD_RATE_9600
#define cDECODING_TIMEOUT_CDD  0x0190
#ifdef cATA5745
#define cFASTLOAD_TIME_CDD 12
 #else
#define cFASTLOAD_TIME_CDD 200
#endif
 #endif

#ifdef cBAUD_RATE_19200
#define cDECODING_TIMEOUT_CDD  0x0190
 #ifdef cATA5745
#define cFASTLOAD_TIME_CDD 12
 #else
#define cFASTLOAD_TIME_CDD 100
#endif
 #endif

#ifdef cBAUD_RATE_AUTOBOT
#define cDECODING_TIMEOUT_CDD  0x0190
#ifdef cATA5745
#define cFASTLOAD_TIME_CDD 12
 #else
#define cFASTLOAD_TIME_CDD 190
#endif
 #endif
   #ifdef cG2TEL
 #define cHF_TEL_SIZE            (unsigned char) 10    /* Länge des empfangenen HF-DATENtelegramms in Bytes */
#else
#define cHF_TEL_SIZE            (unsigned char) 11    /* Länge des empfangenen HF-DATENtelegramms in Bytes */
#endif

#define cHF_TEL_SIZE_G2         (unsigned char) 10    /* Länge des G2-DATENtelegramms */
#define cHF_TEL_SIZE_SHORT      (unsigned char) 5     /* alive length */
#define cNUM_RSSI_VALS_SHORT    (unsigned char) 2     /* nr of RSSI values during short telegram */

/* telegram types */
#define cTelTypeAK35BeruL       (unsigned char) 0x88
#define cTelTypeAK35BeruS       0xC1
#define cTelTypeAK35def         0
#define cTelTypeAK35defLF       1
#define cTelTypeAK35defLMA      0x20
#define cTelTypeBeruG36         0x81
#define cTelTypeBeruG36SWVer    0xC2
#define cTelTypeBeruG3only      0x82
#define cTelTypeBeruNfzAlive    0x83
#define cTelTypeAK35BeruMed     0xA0        /* according to AK35 sensor specification's SW implementation Rev Nr. 7.2 */
#define cTelTypeAKplus          0xA1
#define cTelTypeRLplus          0xE2
#define cTelTypeEdge            0xE3
#define cTelTypeEdgeCnt         0xE5
#define cTelTypePeak            0xE6
#define cTelTypeRotatS          0xE7
 #define cTelTypeRawAcc          0xE8

#define cTelTypeCorntiFP      0x80
#define cTelTypeSELPAL        (unsigned char) 0x03
 #define cTelTypeSELPAL1       (unsigned char) 0x23

#define cTelTypeG4Std           0xA5
#define cTelTypeG4ATDnT         0x52
#define cTelTypeG4FoodPrint     0x18
#define cTelTypeHellOfWorld     0xC3
#define cTelTypeFPTimes         0xC5

#define cSupplCodeHuf (unsigned char) 0x20
#define cSupplCodeConti (unsigned char) 0x30
#define cSupplCodeSchrader (unsigned char) 0x50

#define DUAL_MOD
#define cMoTypeASK (unsigned char) 0
#define cMoTypeFSK (unsigned char) 1

#define c433 (unsigned char) 0
#define c315 (unsigned char) 1

#ifdef _M_IX86
 #define cByteOffset2HiNibID 7
  #else
#define cByteOffset2HiNibID 3
 #endif

#define cMaxAK35DataBytes 13

typedef struct
{
   unsigned char ucTType;
   unsigned char ucTeLen;
} PreBufHeader;

typedef struct
{
   unsigned char ucHeader[sizeof(PreBufHeader)];
   unsigned long ulID;
   unsigned char ucPressure;
   unsigned char ucTemperature;
   unsigned char ucRemainingLifeTime;
   unsigned char ucState;
   unsigned char ucSpinDir;
   unsigned short ushCRC_G3;
} PreBufG3only;

typedef struct
{
   unsigned char ucHeader[sizeof(PreBufHeader)];
   unsigned long ulID;
   unsigned char ucPressure;
   unsigned char ucTemperature;
   unsigned char ucState;
   unsigned char ucCheckSum;
} PreBufG36;
typedef struct
{
   unsigned char ucHeader[sizeof(PreBufHeader)];
   unsigned long ulID;
   unsigned char ucSWRev;
   unsigned char ucCheckSum;
} PreBufG36SWRev;

typedef struct
{
   unsigned char ucHeader[sizeof(PreBufHeader)];
   unsigned char ucCmdID;
   unsigned long ulID;
   unsigned char ucPressure;
   unsigned char ucTemperature;
   unsigned char ucCRC8;
} PreBufAK35def;
typedef struct
{
   unsigned char ucHeader[sizeof(PreBufHeader)];
   unsigned char ucCmdID;
   unsigned long ulID;
   unsigned char ucSpinDir;
   unsigned char ucCRC8;
} PreBufAK35BeruShort;
typedef struct
{
   unsigned char ucHeader[sizeof(PreBufHeader)];
   unsigned char ucCmdID;
   unsigned long ulID;
   unsigned char ucPressure;
   unsigned char ucTemperature;
   unsigned char ucRemainingLifeTime;
   unsigned char ucState;
   unsigned char ucSpinDir;
   unsigned char ucCRC8;
} PreBufAK35BeruLong;
typedef struct
{
   unsigned char ucHeader[sizeof(PreBufHeader)];
   unsigned char ucCmdID;
   unsigned long ulID;
   unsigned char ucPressure;
   unsigned char ucTemperature;
   unsigned char ucSpinDir;
   unsigned char ucCRC8;
} PreBufAK35BeruMed;

typedef struct
{
   unsigned char ucHeader[sizeof(PreBufHeader)];
   unsigned char ucCmdID;
   unsigned long ulID;
   unsigned char ucTireMSB;
   unsigned char ucTire4;
   unsigned char ucTire3;
   unsigned char ucTire2;
   unsigned char ucTire1;
   unsigned char ucTireLSB;
   unsigned char ucCRC8;
} PreBufG4ATDnT;
typedef struct
{
   unsigned char ucHeader[sizeof(PreBufHeader)];
   unsigned char ucCmdID;
   unsigned long ulID;
   unsigned char ucP;
   unsigned char ucT;
   unsigned char ucFoodPrint;
   unsigned char ucCRC8;
} PreBufG4FoodPrint;
typedef struct
{
   unsigned char ucHeader[sizeof(PreBufHeader)];
   unsigned char ucCmdID;
   unsigned long ulID;
   unsigned short ushdT0;
   unsigned short ushdT1;
   unsigned short ushdT2;
   unsigned short ushdT3;
   unsigned char ucCRC8;
} PreBufFPTimes;
typedef struct
{
   unsigned char ucHeader[sizeof(PreBufHeader)];
   unsigned char ucCmdID;
   unsigned long ulID;
   unsigned char ucP;
   unsigned char ucT;
   unsigned char ucTelSentnEnergy;
   unsigned char ucCRC8;
} PreBufG4Std;
typedef struct
{
   unsigned char ucHeader[sizeof(PreBufHeader)];
   unsigned char ucCmdID;
   unsigned long ulID;
   unsigned char ucSWVer;
   unsigned char ucSWVar;
   unsigned char ucTelSentnEnergy;
   unsigned char ucFirmRev;
   unsigned char ucCRC8;
} PreBufHellOfWorld;

typedef struct
{
   unsigned char ucHeader[sizeof(PreBufHeader)];
   unsigned char ucCmdID;
   unsigned long ulID;
   unsigned char ucP;
   unsigned char ucT;
   unsigned char ucFrameID;
   unsigned char ucCRC8;
} PreBufAKplus;
typedef struct
{
   unsigned char ucHeader[sizeof(PreBufHeader)];
   unsigned char ucCmdID;
   unsigned long ulID;
   unsigned char ucSpin;
   unsigned char ucXEdgCt;
   unsigned char ucZEdgCt;
   unsigned char ucSCtTotal;
   unsigned char ucXSCtEn;
   unsigned char ucZSCtEn;
   unsigned char ucFrameID;
   unsigned char ucCRC8;
} PreBufRLplus;
typedef struct
{
   unsigned char ucHeader[sizeof(PreBufHeader)];
   unsigned char ucCmdID;
   unsigned long ulID;
   unsigned char ucEdge;
   unsigned char ucCRC8;
} PreBufEdge;
typedef struct
{
   unsigned char ucHeader[sizeof(PreBufHeader)];
   unsigned char ucCmdID;
   unsigned long ulID;
   unsigned char ucSpin;
   unsigned short ushXEdgeCt;
   unsigned char ucXPeakCt;
   unsigned short ushZEdgeCt;
   unsigned char ucZPeakCt;
   unsigned char ucCRC8;
} PreBufEdgeCnt;

typedef struct
{
   unsigned char ucHeader[sizeof(PreBufHeader)];
   unsigned char ucCmdID;
   unsigned long ulID;
   unsigned char ucXPeak;
   unsigned char ucPEvCt;
   unsigned char ucCRC8;
} PreBufPeak;

typedef struct
{
   unsigned char ucHeader[sizeof(PreBufHeader)];
   unsigned char ucCmdID;
   unsigned long ulID;
   unsigned char ucZPeak;
   unsigned char ucZPEvCt;
   unsigned char ucCRC8;
} PreBufZPeak;

typedef struct
{
   unsigned char ucHeader[sizeof(PreBufHeader)];
   unsigned char ucCmdID;
   unsigned long ulID;
   unsigned char ucXAcc;
   unsigned char ucZAcc;
   unsigned char ucCRC8;
} PreBufRawAcc;

typedef struct
{
   unsigned char ucHeader[sizeof(PreBufHeader)];
   unsigned char ucCmdID;
   unsigned long ulID;
   unsigned char ucSnRH;
   unsigned char ucRL;
   unsigned char ucCRC8;
} PreBufRotatS;

typedef struct
{
   unsigned char ucHeader[sizeof(PreBufHeader)];
   unsigned char ucCmdID;
   unsigned long ulID;
   unsigned char ucP;
   unsigned char ucT;
   unsigned char ucPAL;
   unsigned short ushStatusField;
   unsigned char ucCRC8;
} PreBufSchraderFP;

typedef struct
{
   unsigned char ucHeader[sizeof(PreBufHeader)];
   unsigned char ucCmdID;
   unsigned long ulID;
   unsigned char ucP;
   unsigned char ucT;
   unsigned char ucBat;
   unsigned char ucAcc;
   unsigned char ucModeNCode;
   unsigned char ucCRC8;
} PreBufContiFP;

typedef struct
{
  unsigned char aucHeader[sizeof(PreBufHeader)];
  unsigned char aucTelDat[cMaxAK35DataBytes];
  unsigned char aucRSMesVal[6];
  unsigned char ucAvg;
  unsigned short ushTimeStamp;
} PreBufStructure;

typedef union prebuffer
{
  PreBufHeader Header;
  PreBufStructure Struc;
  PreBufAK35def AK35def;
  PreBufAK35BeruShort AK35BeruS;
  PreBufAK35BeruLong AK35BeruL;
  PreBufAK35BeruMed AK35BeruMed;
  PreBufG36 G36;
  PreBufG36SWRev G36SWRev;
  PreBufG4ATDnT G4ATDnT;
  PreBufG4FoodPrint G4FoodPrint;
  PreBufG4Std G4Std;
  PreBufAKplus AKplus;
  PreBufRLplus RLplus;
  PreBufEdge   Edge;
  PreBufEdgeCnt EdgeCnt;
  PreBufPeak Peak;
  PreBufZPeak ZPeak;
  PreBufRawAcc RawAcc;
  PreBufHellOfWorld HellOfWorld;
  PreBufFPTimes FPTimes;
  PreBufSchraderFP SchraderFP;
  PreBufContiFP ContiFP;
  PreBufRotatS RotatS;

  PreBufG3only G3only;
   unsigned char byte[sizeof(PreBufStructure)];
 }tPreBuf;

extern void (*fpDecoder) (unsigned short);
extern unsigned short ushLaRiTi;

#define  cSeriesTelsOfInterest {cTelTypeAK35BeruMed, cTelTypePeak, cTelTypeRotatS , cTelTypeEdgeCnt, cTelTypeAK35def, cTelTypeAK35defLMA, cTelTypeRawAcc, cTelTypeG4Std, cTelTypeG4ATDnT, cTelTypeG4FoodPrint, cTelTypeHellOfWorld, cTelTypeFPTimes, cTelTypeCorntiFP, cTelTypeSELPAL}

extern void InitCDD(void);
extern void PreStartCDD(void);
extern void StartCDD(void);
extern void CDDecodingCDD(unsigned short);
extern void ErrorHandlerCDD(unsigned char);
extern unsigned char GetStateCDD(void);
extern unsigned char GetErrorCDD(void);
 extern void SetStateCDD(unsigned char);
extern void Safe1ManBit(void);
extern void Safe0ManBit(void);
extern void Safe1AK35Bit(void);
extern void Safe0AK35Bit(void);

#endif
