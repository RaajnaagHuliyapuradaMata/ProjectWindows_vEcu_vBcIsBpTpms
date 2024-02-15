/************************************************************************************************************
 * (c) Beru Electronics GmbH      Abteilung BES     2007
 ************************************************************************************************************/
/************************************************************************************************************
 * Project:       Reifendruckkontrolle TSS (TSS = tyre safety system)
 *
 * $Archive: /BMW/G3kompakt/Sw/SC6demo/template_can/application/source/tssappl/HFrec/CDDECODER/CD_Decoder_X.h $
 *
 * File Status:   compiled           - (under construction, compiled etc.)
 *
 ************************************************************************************************************/
/************************************************************************************************************
 * Author:
 *
 * Initials     Name                           Company
 * --------     --------------------------     --------------------------------------------------------------
 * pb           Peter Brand                     Beru Electronics GmbH (BES)
 *
 ************************************************************************************************************/
/************************************************************************************************************
 * Global Description
 * ==================
 *
 *
 *
 *
 *
 ************************************************************************************************************/
/************************************************************************************************************
 * Module Description
 * ==================
 *
 * Purpose:
 *
 * Headerdatei zur Verwendung des Moduls für Dekodierung von HF-Telegrammen. Beinhaltet alle externen
 * Funktionen, Datenstrukturen, Konstanten für die Verwendung des Moduls.
 *
 ************************************************************************************************************/
/************************************************************************************************************
 * Module Abbreviation:
 * ====================
 *
 *
 ************************************************************************************************************/
/************************************************************************************************************
 * Glossary
 * ========
 *
 *
 ************************************************************************************************************/
/************************************************************************************************************
 * Module Modification
 * ===================
 *
 * changes in 2007
 *
 * $Log: /BMW/G3kompakt/Sw/SC6demo/template_can/application/source/tssappl/HFrec/CDDECODER/CD_Decoder_X.h $
 * 
 * 28    2.04.14 11:22 Peter
 * support for Schrader Pal rf telegram (SELPAL 2)
 *
 * 27    2.10.13 13:55 Peter
 *
 * 26    14.11.12 10:18 Peter
 * new constant 4 data byte definitions used (13 bytes)
 *
 * 25    23.07.12 10:01 Peter
 * AK35defLF
 *
 * 24    28.06.12 16:24 Peter
 * Rotats and AK35defLMA Type added
 *
 * 23    25.05.12 8:03 Peter
 *
 * 22    23.05.12 13:40 Peter
 * PalDat removed at Conti Telegram decl
 *
 * 21    3.05.12 14:15 Peter
 * supplier code support @ AK protocol
 * conti & schrader teltype 0x80 support
 *
 * 20    19.01.12 18:53 Rapp
 * ABS-Linearisierung
 *
 * 19    12.01.12 16:18 Peter
 * new tel type FPTimes supported
 *
 * 18    22.09.11 15:27 Peter
 * G4 sensor reception enabled as seperate application in statemanager
 *
 * 17    15.06.11 14:44 Peter
 *
 * 15    26.05.11 14:27 Peter
 * UDA like step 1
 *
 * 14    6.04.11 14:10 Peter
 * sc6 demo implementations
 *
 * 22    7.03.11 15:16 Peter
 * support RawAcc reception
 *
 * 21    1.12.10 8:39 Peter
 * Peak telegramm support
 *
 * 20    29.10.10 10:36 Schoenbeck
 * TelTypeEdgeCnt für RE SW 10.12.6 angepasst:
 * RE sendet XEdge, ZEdge (Umdrehungen) und XPeak, ZPeak (Störungen 2,5g)
 *
 * 19    2.09.10 12:09 Peter
 * no more G36
 *
 * 18    2.09.10 12:05 Peter
 * beru MED telegram available now
 *
 * 17    11.08.10 8:08 Peter
 * receive and process EDgeCt telegram
 *
 * 16    27.07.10 10:47 Peter
 * 1te Version lauffähig
 *
 * 15    21.07.10 18:29 Peter
 * AK/RLplus modifications
 *
 * 11    28.04.10 10:26 Rapp
 * #define cATA5745
 *
 * 10    26.04.10 18:00 Rapp
 * #undef cATA5745
 *
 * 9     26.04.10 14:42 Peter
 * BERU MED telegram's CMD ID changed from 0x84 to 0xA0
 *
 * 8     20.04.10 16:35 Peter
 * new define for easy switch back to maxim receiver
 *
 * 7     30.03.10 17:11 Peter
 *
 * 6     24.03.10 16:22 Peter
 * rename ushLastRisingTime in ushLaRiRi
 *
 * 5     18.03.10 15:46 Peter
 * Sync phase optimized
 *
 * 6     15.10.09 15:32 Peter
 * AUTOBOT decoder integrated (but not activated)
 *
 * 5     28.07.09 11:59 Peter
 * minimum amount of syncbits increased to 4
 *
 * 4     22.07.09 10:20 Peter
 * telegram decing time out time doubled to fix HW insufficiency in the
 * beginning of the sync bytes
 *
 * 3     4.06.09 16:04 Peter
 * SHORT tel now receivable
 *
 * 2     3.06.09 13:40 Peter
 * 19.2kBaud activated
 *
 * 1     20.05.09 11:46 Peter
 * TSS G3only WU RF-tel decoder and buffer
 *
 * 7     13.02.09 10:31 Peter
 * new switch configuration for 19,2kBaud variant
 *
 * 6     15.09.08 10:18 Schubert
 * as im Namen von pb:
 * cHF_TEL_SIZE = 11
 * cHF_TEL_SIZE_G3_ADD_ON (komplett entfallen)
 * typedef prebufferData: unsigned shortushCRC_G2 entfernt, Anzahl RSSI Werte auf
 * 6
 * reduziert
 * Dokumentation 1:1 empfangspuffer Datenstruktur
 *
 * 5     28.08.08 11:56 Peter
 * get 8 bit adc RSSI values
 *
 * 4     18.07.08 7:45 Peter
 * baudrate = 9,6kBaud
 *
 * 2     12.06.08 17:37 Peter
 * variable byte length 10/13 supported
 *
 * 1     6.06.08 11:50 Peter
 * decodes sensor telegrams and provides the data in a ringbuffer
 *
 * 1     4.12.07 14:05 Schubert
 * as: Xgate Module
 *
 * 1     23.10.07 16:34 Hanke
 * Erste Version eingecheckt. Basis PL6 I350. System lernt ein.
 *
 * 1     23.04.07 17:26 Hanke
 * - Anpassungen von Elektrobit bzgl. Make-Prozess
 * - Dekodierung auf XGATE portiert
 *
 *
 ************************************************************************************************************/
#ifndef _CDDECODER_X_H /* [0] */
#define _CDDECODER_X_H
#include "Compiler_Cfg.h"

/************************************************************************************************************
 *                                             macro
 ************************************************************************************************************/
/* Prozesszustände Dekodierung */
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

/* Error-Flags */
#define cNO_ERROR_CDD            0x00
#define cSHORT_SYNCBIT_CDD       0x01            /* Bitbreite zu gering */
#define cLONG_SYNCBIT_CDD        0x02            /* Bitbreite zu groß */
#define cCORR_OVERFLOW_CDD       0x04            /* Bit-Korrektur ergab Überlauf */
#define cTO_SYREC_CDD            0x08            /* Timout während Empfang od. Sync */
#define cBAD_CRC_CDD             0x20            /* falscher CRC */
#define cMIN_SYNCBIT_CDD         0x40            /* zu wenig Sync Bit */
#define cMAX_SYNCBIT_CDD         0x80            /* zu viele Sync Bit */
#define cSHORTEL                 0x0C            /* no error but ahort tel */
#define cBITERRORINSYNC          0x03
#define cBAD_AK35_SYNC1          0x05            /* ! onliest error in AK35 sync phase with retrials ! */

// _________________________module configuration_________________START_
#define NEWDECOTTING
//#define cATA5745                        /* ATMEL receiver active with cyclic NFSK pulse concept */
// #define NFZ_ALIVE    // try receiving short alive telegramm from truck G3 sensor
//#define cAUTOCOD
#ifndef cAUTOCOD
 #define cAK35ONLY
#endif
//#define G36TELTYPE
/* Timeout-Zeit für HF-Dekodierung */

//#define cBAUD_RATE_AUTOBOT  // = 9,6 v 19,2kBaud
//#define cBAUD_RATE_9600     // is recommended for active G36TELTYPE
#define cBAUD_RATE_19200  // MrMueller's extra192variant
//#define cG2TEL            // MrMueller's extra192variant

#ifdef cBAUD_RATE_9600
#define cDECODING_TIMEOUT_CDD  0x0190            /* Timeoutzähler für Dekodierung = 400µs */
#ifdef cATA5745
#define cFASTLOAD_TIME_CDD 12 // is NFSK impulse length in usec
#else
#define cFASTLOAD_TIME_CDD 200
#endif  // cATA5745
#endif  //cBAUD_RATE_9600

#ifdef cBAUD_RATE_19200
#define cDECODING_TIMEOUT_CDD  0x0190 //0x00C8            /* Timeoutzähler für Dekodierung = 400µs */
#ifdef cATA5745
#define cFASTLOAD_TIME_CDD 12 // is NFSK impulse length in usec
#else
#define cFASTLOAD_TIME_CDD 100
#endif  // cATA5745
#endif  //cBAUD_RATE_19200

#ifdef cBAUD_RATE_AUTOBOT
#define cDECODING_TIMEOUT_CDD  0x0190            /* Timeoutzähler für Dekodierung = 400µs */
#ifdef cATA5745
#define cFASTLOAD_TIME_CDD 12 // is NFSK impulse length in usec
#else
#define cFASTLOAD_TIME_CDD 190
#endif  // cATA5745
#endif  //cBAUD_RATE_AUTOBOT

// _________________________module configuration__________________END__

// telegram parameters
#ifdef cG2TEL    // MrMueller's extra192variant
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
#define cTelTypeAKplus          0xA1        /* UKL demonstrator types */
#define cTelTypeRLplus          0xE2
#define cTelTypeEdge            0xE3
#define cTelTypeEdgeCnt         0xE5
#define cTelTypePeak            0xE6
#define cTelTypeRotatS          0xE7    // !! WARNING RotatS replaces ZPeak WARNING !!
#define cTelTypeRawAcc          0xE8

#define cTelTypeCorntiFP      0x80
#define cTelTypeSELPAL        (unsigned char) 0x03 // no learn bit set
#define cTelTypeSELPAL1       (unsigned char) 0x23 // learn bit set

#define cTelTypeG4Std           0xA5        /* according to "in Arbeit P025 540 02.. .doc"  */
#define cTelTypeG4ATDnT         0x52
#define cTelTypeG4FoodPrint     0x18
#define cTelTypeHellOfWorld     0xC3
#define cTelTypeFPTimes         0xC5

#define cSupplCodeHuf (unsigned char) 0x20
#define cSupplCodeConti (unsigned char) 0x30
#define cSupplCodeSchrader (unsigned char) 0x50
/* NEW DUAL MOD */
#define DUAL_MOD
#define cMoTypeASK (unsigned char) 0
#define cMoTypeFSK (unsigned char) 1

/* 2 RF frequencies */
#define c433 (unsigned char) 0
#define c315 (unsigned char) 1

#ifdef _M_IX86                  // Defined for x86 processors
#define cByteOffset2HiNibID 7// 6 // this only works with 1byte structure member alignment and intel byte alignment
#else
#define cByteOffset2HiNibID 3 // this only works with 1byte structure member alignment and motorola byte alignment
#endif

#define cMaxAK35DataBytes 13    // w/o sync bytes
/************************************************************************************************************
 *                                            typedef
 ************************************************************************************************************/


typedef struct                                                  // common telegram header
{
   unsigned char ucTType;
   unsigned char ucTeLen;
} PreBufHeader;

typedef struct                                                  // G3 only
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

typedef struct                                                  // G36 FORD
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
                                                                // AK35
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

typedef struct                                              // AK4 (selftalking sensor)
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
                                                             // AK35 plus
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
                                                                  // none Huf TelTypes
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

typedef struct                                                  // common telegram structure
{
  unsigned char aucHeader[sizeof(PreBufHeader)];
  unsigned char aucTelDat[cMaxAK35DataBytes];
  unsigned char aucRSMesVal[6];
  unsigned char ucAvg;
  unsigned short ushTimeStamp;
} PreBufStructure;

//____________________________________all together: G3only,G36,AK35,AK4,AK35plus_______________________________
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
	unsigned char byte[sizeof(PreBufStructure)];   // longest struct + 2
}tPreBuf;

extern void (*fpDecoder) (unsigned short);               /* pointer 2 decoding function (manchester or biphase decoder) */
extern unsigned short ushLaRiTi;
/************************************************************************************************************
 *                                    data (module global) - ROM
 ************************************************************************************************************/



/************************************************************************************************************
 *                                    data (module global) - RAM
 ************************************************************************************************************/



/************************************************************************************************************
 *                                       data (global) - ROM
 ************************************************************************************************************/
#define  cSeriesTelsOfInterest {cTelTypeAK35BeruMed, cTelTypePeak, cTelTypeRotatS , cTelTypeEdgeCnt, cTelTypeAK35def, cTelTypeAK35defLMA, cTelTypeRawAcc, cTelTypeG4Std, cTelTypeG4ATDnT, cTelTypeG4FoodPrint, cTelTypeHellOfWorld, cTelTypeFPTimes, cTelTypeCorntiFP, cTelTypeSELPAL}  // SC6demo implementation, replace by your series model types





/************************************************************************************************************
 *                                       data (global) - RAM
 ************************************************************************************************************/



/***********************************************************************************************************
 *                                 prototype (local functions - private)
 ***********************************************************************************************************/



/***********************************************************************************************************
 *                                 prototype (local functions - public)
 ***********************************************************************************************************/
extern void InitCDD(void);
extern void PreStartCDD(void);
extern void StartCDD(void);
extern void CDDecodingCDD(unsigned short);
extern void ErrorHandlerCDD(unsigned char);
extern unsigned char GetStateCDD(void);
extern unsigned char GetErrorCDD(void);

// interface DecodeMan <- CDDecoder:
extern void SetStateCDD(unsigned char);
extern void Safe1ManBit(void);
extern void Safe0ManBit(void);
extern void Safe1AK35Bit(void);
extern void Safe0AK35Bit(void);
/************************************************************************************************************
 *                               prototype (external functions - interface)
 ************************************************************************************************************/

#endif /* #ifndef _CDDECODER_X_H */ /* [0] */
