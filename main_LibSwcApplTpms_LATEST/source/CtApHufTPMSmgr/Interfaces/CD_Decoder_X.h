

#ifndef _CDDECODER_X_H
#define _CDDECODER_X_H
#include "Compiler_Cfg.h"

#define cRESET_CDD     0x00
#define cPRESTART_CDD  0x01
#define cFSYNC_CDD     0x02
#define cSYNC_CDD      0x03
#define cREC_CDD       0x04
#define cPreSync (uint8) 0x05
#define cStart   (uint8) 0
#define cMeasure (uint8) 1
#define cConfirmManchestere (uint8) 2
#define cConfirmBiphase (uint8) 3

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
 #define cHF_TEL_SIZE            (uint8) 10    /* Länge des empfangenen HF-DATENtelegramms in Bytes */
#else
#define cHF_TEL_SIZE            (uint8) 11    /* Länge des empfangenen HF-DATENtelegramms in Bytes */
#endif

#define cHF_TEL_SIZE_G2         (uint8) 10    /* Länge des G2-DATENtelegramms */
#define cHF_TEL_SIZE_SHORT      (uint8) 5     /* alive length */
#define cNUM_RSSI_VALS_SHORT    (uint8) 2     /* nr of RSSI values during short telegram */

/* telegram types */
#define cTelTypeAK35BeruL       (uint8) 0x88
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
#define cTelTypeSELPAL        (uint8) 0x03
 #define cTelTypeSELPAL1       (uint8) 0x23

#define cTelTypeG4Std           0xA5
#define cTelTypeG4ATDnT         0x52
#define cTelTypeG4FoodPrint     0x18
#define cTelTypeHellOfWorld     0xC3
#define cTelTypeFPTimes         0xC5

#define cSupplCodeHuf (uint8) 0x20
#define cSupplCodeConti (uint8) 0x30
#define cSupplCodeSchrader (uint8) 0x50

#define DUAL_MOD
#define cMoTypeASK (uint8) 0
#define cMoTypeFSK (uint8) 1

#define c433 (uint8) 0
#define c315 (uint8) 1

#ifdef _M_IX86
 #define cByteOffset2HiNibID 7
  #else
#define cByteOffset2HiNibID 3
 #endif

#define cMaxAK35DataBytes 13

typedef struct
{
   uint8 ucTType;
   uint8 ucTeLen;
} PreBufHeader;

typedef struct
{
   uint8 ucHeader[sizeof(PreBufHeader)];
   unsigned long ulID;
   uint8 ucPressure;
   uint8 ucTemperature;
   uint8 ucRemainingLifeTime;
   uint8 ucState;
   uint8 ucSpinDir;
   uint16 ushCRC_G3;
} PreBufG3only;

typedef struct
{
   uint8 ucHeader[sizeof(PreBufHeader)];
   unsigned long ulID;
   uint8 ucPressure;
   uint8 ucTemperature;
   uint8 ucState;
   uint8 ucCheckSum;
} PreBufG36;
typedef struct
{
   uint8 ucHeader[sizeof(PreBufHeader)];
   unsigned long ulID;
   uint8 ucSWRev;
   uint8 ucCheckSum;
} PreBufG36SWRev;

typedef struct
{
   uint8 ucHeader[sizeof(PreBufHeader)];
   uint8 ucCmdID;
   unsigned long ulID;
   uint8 ucPressure;
   uint8 ucTemperature;
   uint8 ucCRC8;
} PreBufAK35def;
typedef struct
{
   uint8 ucHeader[sizeof(PreBufHeader)];
   uint8 ucCmdID;
   unsigned long ulID;
   uint8 ucSpinDir;
   uint8 ucCRC8;
} PreBufAK35BeruShort;
typedef struct
{
   uint8 ucHeader[sizeof(PreBufHeader)];
   uint8 ucCmdID;
   unsigned long ulID;
   uint8 ucPressure;
   uint8 ucTemperature;
   uint8 ucRemainingLifeTime;
   uint8 ucState;
   uint8 ucSpinDir;
   uint8 ucCRC8;
} PreBufAK35BeruLong;
typedef struct
{
   uint8 ucHeader[sizeof(PreBufHeader)];
   uint8 ucCmdID;
   unsigned long ulID;
   uint8 ucPressure;
   uint8 ucTemperature;
   uint8 ucSpinDir;
   uint8 ucCRC8;
} PreBufAK35BeruMed;

typedef struct
{
   uint8 ucHeader[sizeof(PreBufHeader)];
   uint8 ucCmdID;
   unsigned long ulID;
   uint8 ucTireMSB;
   uint8 ucTire4;
   uint8 ucTire3;
   uint8 ucTire2;
   uint8 ucTire1;
   uint8 ucTireLSB;
   uint8 ucCRC8;
} PreBufG4ATDnT;
typedef struct
{
   uint8 ucHeader[sizeof(PreBufHeader)];
   uint8 ucCmdID;
   unsigned long ulID;
   uint8 ucP;
   uint8 ucT;
   uint8 ucFoodPrint;
   uint8 ucCRC8;
} PreBufG4FoodPrint;
typedef struct
{
   uint8 ucHeader[sizeof(PreBufHeader)];
   uint8 ucCmdID;
   unsigned long ulID;
   uint16 ushdT0;
   uint16 ushdT1;
   uint16 ushdT2;
   uint16 ushdT3;
   uint8 ucCRC8;
} PreBufFPTimes;
typedef struct
{
   uint8 ucHeader[sizeof(PreBufHeader)];
   uint8 ucCmdID;
   unsigned long ulID;
   uint8 ucP;
   uint8 ucT;
   uint8 ucTelSentnEnergy;
   uint8 ucCRC8;
} PreBufG4Std;
typedef struct
{
   uint8 ucHeader[sizeof(PreBufHeader)];
   uint8 ucCmdID;
   unsigned long ulID;
   uint8 ucSWVer;
   uint8 ucSWVar;
   uint8 ucTelSentnEnergy;
   uint8 ucFirmRev;
   uint8 ucCRC8;
} PreBufHellOfWorld;

typedef struct
{
   uint8 ucHeader[sizeof(PreBufHeader)];
   uint8 ucCmdID;
   unsigned long ulID;
   uint8 ucP;
   uint8 ucT;
   uint8 ucFrameID;
   uint8 ucCRC8;
} PreBufAKplus;
typedef struct
{
   uint8 ucHeader[sizeof(PreBufHeader)];
   uint8 ucCmdID;
   unsigned long ulID;
   uint8 ucSpin;
   uint8 ucXEdgCt;
   uint8 ucZEdgCt;
   uint8 ucSCtTotal;
   uint8 ucXSCtEn;
   uint8 ucZSCtEn;
   uint8 ucFrameID;
   uint8 ucCRC8;
} PreBufRLplus;
typedef struct
{
   uint8 ucHeader[sizeof(PreBufHeader)];
   uint8 ucCmdID;
   unsigned long ulID;
   uint8 ucEdge;
   uint8 ucCRC8;
} PreBufEdge;
typedef struct
{
   uint8 ucHeader[sizeof(PreBufHeader)];
   uint8 ucCmdID;
   unsigned long ulID;
   uint8 ucSpin;
   uint16 ushXEdgeCt;
   uint8 ucXPeakCt;
   uint16 ushZEdgeCt;
   uint8 ucZPeakCt;
   uint8 ucCRC8;
} PreBufEdgeCnt;

typedef struct
{
   uint8 ucHeader[sizeof(PreBufHeader)];
   uint8 ucCmdID;
   unsigned long ulID;
   uint8 ucXPeak;
   uint8 ucPEvCt;
   uint8 ucCRC8;
} PreBufPeak;

typedef struct
{
   uint8 ucHeader[sizeof(PreBufHeader)];
   uint8 ucCmdID;
   unsigned long ulID;
   uint8 ucZPeak;
   uint8 ucZPEvCt;
   uint8 ucCRC8;
} PreBufZPeak;

typedef struct
{
   uint8 ucHeader[sizeof(PreBufHeader)];
   uint8 ucCmdID;
   unsigned long ulID;
   uint8 ucXAcc;
   uint8 ucZAcc;
   uint8 ucCRC8;
} PreBufRawAcc;

typedef struct
{
   uint8 ucHeader[sizeof(PreBufHeader)];
   uint8 ucCmdID;
   unsigned long ulID;
   uint8 ucSnRH;
   uint8 ucRL;
   uint8 ucCRC8;
} PreBufRotatS;

typedef struct
{
   uint8 ucHeader[sizeof(PreBufHeader)];
   uint8 ucCmdID;
   unsigned long ulID;
   uint8 ucP;
   uint8 ucT;
   uint8 ucPAL;
   uint16 ushStatusField;
   uint8 ucCRC8;
} PreBufSchraderFP;

typedef struct
{
   uint8 ucHeader[sizeof(PreBufHeader)];
   uint8 ucCmdID;
   unsigned long ulID;
   uint8 ucP;
   uint8 ucT;
   uint8 ucBat;
   uint8 ucAcc;
   uint8 ucModeNCode;
   uint8 ucCRC8;
} PreBufContiFP;

typedef struct
{
  uint8 aucHeader[sizeof(PreBufHeader)];
  uint8 aucTelDat[cMaxAK35DataBytes];
  uint8 aucRSMesVal[6];
  uint8 ucAvg;
  uint16 ushTimeStamp;
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
   uint8 byte[sizeof(PreBufStructure)];
 }tPreBuf;

extern void (*fpDecoder) (uint16);
extern uint16 ushLaRiTi;

#define  cSeriesTelsOfInterest {cTelTypeAK35BeruMed, cTelTypePeak, cTelTypeRotatS , cTelTypeEdgeCnt, cTelTypeAK35def, cTelTypeAK35defLMA, cTelTypeRawAcc, cTelTypeG4Std, cTelTypeG4ATDnT, cTelTypeG4FoodPrint, cTelTypeHellOfWorld, cTelTypeFPTimes, cTelTypeCorntiFP, cTelTypeSELPAL}

extern void InitCDD(void);
extern void PreStartCDD(void);
extern void StartCDD(void);
extern void CDDecodingCDD(uint16);
extern void ErrorHandlerCDD(uint8);
extern uint8 GetStateCDD(void);
extern uint8 GetErrorCDD(void);
 extern void SetStateCDD(uint8);
extern void Safe1ManBit(void);
extern void Safe0ManBit(void);
extern void Safe1AK35Bit(void);
extern void Safe0AK35Bit(void);

#endif
