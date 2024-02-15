/***************************************************************************************************
*(c) Beru Electronics GmbH     BEE1     05/2003
*================================================================================================
*
*  $Archive: /LIB/WAF/work/WallocX.h $
*
*   file status:   under construction
*
*    ------------------------------------------------------------------------------------------------
*
*   author:        Peter Brand                Beru Electronics GmbH
*
*   intials:       pb
*
*
*   Modul Description
*
*   Global description:
*   headerfile for wheel position allocation based on left/right spinning information sw
*   (contains all external functions, data structures, constants and data to access the wheel allocation algo)
*   :
*
*
*Modul Modification
*
*last modification:
*$Log: /LIB/WAF/work/WallocX.h $
 * 
 * 79    7.09.12 16:54 Peter
 * FPA only version
 * 
 * 78    21.08.12 17:52 Peter
 * new module structure (FPA and AEC, CA seperated)
 * 
 * 77    10.08.12 10:10 Peter
 * new test module structure
 * 
 * 76    27.07.12 11:48 Peter
 * new table for IAT and new sensor SW XXX???
 * 
 * 75    15.05.12 14:59 Peter
 * ReNewABSRef decl
 * 
 * 74    15.05.12 11:06 Rapp
 * rename AÉC to AEC
 *
 * 73    14.05.12 13:11 Peter
 *
 * 72    14.05.12 13:09 Peter
 * AÉC removed
 *
 * 71    11.05.12 7:52 Peter
 * BP b4 2nd MV generation
 *
 * 70    3.05.12 13:39 Peter
 *
 * 69    2.05.12 16:14 Peter
 * process 4 ABS signal
 * no forced allocation of 4th ambigous ID
 *
 * 68    7.02.12 15:08 Peter
 * ABS signal overflow protection not coupled to RF tel reception
 * must now be detected actively at ABS signal reception (CAN cylce)
 *
 * 67    23.01.12 11:09 Peter
 *
 * 66    20.01.12 17:47 Peter
 * CA integrated and tested
 *
 * 65    17.01.12 13:55 Peter
 * 1st runable common Peak and FixPos allocation
 *
 * 64    12.01.12 16:16 Peter
 * test switch off
 *
 * 63    11.01.12 19:07 Peter
 * backup only
 *
 * 62    12.12.11 9:52 Peter
 * refactored
 *
 * 61    9.12.11 14:04 Peter
 * VorneMehrWegEffekt reimpleneted (no decision but runnable)
 * SWE ( PRallMax=50 and dt=2sec)
 *
 * 60    7.09.11 9:58 Peter
 * testrun with limited amaount of peak tels
 *
 * 59    7.07.11 14:40 Peter
 * optimzation 4 hyper sensible sensor
 *
 * 58    21.03.11 15:23 Peter
 * ACM implementation
 *
 * 57    17.02.11 8:52 Peter
 * timeout timer resolution set from 1 to 3 seconds, preload value = 100
 * (300sec)
 *
 * 56    8.02.11 13:26 Peter
 * SpeedLimit 80km/h active
 * Axle and wheel diameter parameter
 * default config 3,1m AxleDist 0,5m wheel diameter
 *
 * 55    7.01.11 10:08 Peter
 * modultest deactivated
 *
 * 54    5.01.11 8:45 Peter
 * BP version before tidiing
 *
 * 53    13.12.10 11:33 Peter
 * peak statistic
 *
 * 52    1.12.10 11:35 Peter
 *
 * 51    22.11.10 13:58 Peter
 * save ABS tick values with very 1st AKdef tel
 *
 * 50    18.11.10 17:29 Peter
 * voerhand corrected edge count delta information to WA algo
 *
 * 49    17.11.10 12:08 Peter
 * modultest deactivated
 *
 * 48    17.11.10 12:00 Peter
 * simulation and TSS basic structure repaired
 *
 * 47    18.10.10 16:03 Schoenbeck
 * 1) Zählen der RE EdgCnt nur bei bestimmter Güte
 * 2) Histmem wieder aktiviert damit Kombianzeige wieder aktiv
 * 3) ZOM von 8 auf 6 reduziert wegen RAM Knappheit
 *
 * 46    12.10.10 16:33 Schoenbeck
 * erste Version mit Abrolllängenkriterium
 * Achtung histmem wurde wegen RAM-Knappheit deaktiviert!
 *
 * 45    16.09.10 17:53 Peter
 * refactored
 * optimized active sync of edge count sum
 * optimzed delta generation
 *
 * 44    10.09.10 13:19 Peter
 *
 * 43    8.09.10 14:38 Peter
 * finalize WA NOT YET tested
 *
 * 42    3.09.10 14:00 Peter
 * test
 *
 * 40    27.08.10 16:57 Peter
 * Concept III/1 implemented
 *
 * 39    29.07.10 15:02 Peter
 * version with 1st concept (dT)
 *
 * 38    27.07.10 10:47 Peter
 * 1te Version lauffähig
 *
 * 37    21.07.10 16:17 Peter
 * 1st WAF implementation with no WAF core
 *
 * 35    13.03.09 17:50 Peter
 * new macro for accessing M4 info
 *
 * 34    10.03.09 16:58 Peter
 * new switches 4 module testing
 *
 * 33    6.02.09 15:48 Peter
 * Minimum RSSI distance between mean axis values redurced from 10 to 7
 *
 * 32    5.12.08 16:06 Peter
 * interface prepared 4 M4 importation
 *
 * 30    28.11.08 17:36 Rapp
 * Parameter korrigiert (siehe OIL#220):
 * - ucDefMinERMeanRssiLevel = 14
 * - ucDefMinCt4ER = 9
 *
 * 29    13.10.08 12:02 Peter
 * interface function to manipulate WAmode temporarily
 *
 * 28    6.10.08 9:49 Braunm
 * Verschachtelter Kommentar entfernt
 *
 * 27    17.07.08 13:47 Peter
 * WA Parameters now changable
 *
 * 26    18.06.08 10:24 Peter
 * enhanced WA interface supports reutn of the WP array start adr now
 *
 * 25    12.06.08 17:38 Peter
 * new module structure supported
 *
 * 24    11.06.08 15:27 Peter
 * adaptation to new maodule structure
 *
 * 22    8.01.08 17:27 Peter
 * Init has return value if history wheel allocation is present or not
 *
 * 21    22.08.07 13:38 Peter
 * comment for spinning direction corrected
 *
 * 20    3.07.06 10:05 Peter
 * new test function declaration
 * new macros for drive direction info acces
 * documenation update
 *
 * 19    17.05.06 13:35 Hanke
 * Schalter "pb_Debug4MB_010404" für Herrn Baltisberger aktiviert,
 * hierdurch stehen die Variablen "ucRightRSDistDG" und "ucLeftRSDistDG"
 * zur Verfügung.
 *
 * 18    1.03.06 15:25 Peter
 * array of wheel positions for external use removed
 *
 * 17    1.03.06 11:59 Peter
 *
 * 16    28.02.06 13:36 Peter
 * modultest deactivated
 *
 * 15    28.02.06 13:28 Peter
 * column oriented access to history
 *
 * 14    22.02.06 17:31 Peter
 * new Testfunction declarations
 * WATO -> ucWATO
 *
 * 13    19.01.06 9:14 Hanke
 *
 * 12    16.11.05 11:47 Peter
 * no debug option for mark braun anymore
 *
 * 11    22.06.05 11:52 Peter
 * update documentation
 *
 * 10    27.12.04 16:46 Peter
 * module test deactivated
 *
 * 9     27.12.04 16:28 Peter
 * status adapted to new status contet
 * old :   0x10 -> leftspinning and 0x20 -> rightspinning
 * new:  0x20 -> leftspinning and 0x08 -> rightspinning
 *
 * 8     2.04.04 9:52 Peter
 * Modultest deactivated
 * misra conformance switched off
 *
 * 7     2.04.04 9:51 Peter
 * pb_Debug4MB_010404 insertion of a debug variable set for marc braun to
 * be removed asap
 *
 * 6     13.02.04 14:57 Peter
 * ulGetZOMID gets public
 *
 * 5     11.02.04 18:27 Peter
 * new axis detection implemented to (req.id 70-73)
 * seperate axis detection level (req.id 66)
 *
 * 4     4.02.04 15:29 Peter
 * Left- and rightspinningdircetions has been changed
 *
 * 3     30.01.04 10:28 Peter
 * Änderungen für Version XXe10002
 *
 * 2     13.01.04 14:06 Peter
 * Sicherung vor Integration (Funktionstests abgeschlossen)
 *
 * 1     9.01.04 17:23 Peter
 * nur zur Sicherung / backup
*
****************************************************************************************************/
#ifdef WallocX_H

#else /* WallocX_H */
#define WallocX_H
#include "walloc_if.h"  // for types only
/***********************************************************************************************
 *Declaration
 */

 /* constants for tZOM[x].ucStatus */
#define cNoWPos (unsigned char) 0xF0

#define cWP_RR (unsigned char) 0x08
#define cWP_RL (unsigned char) 0x04
#define cWP_FR (unsigned char) 0x02
#define cWP_FL (unsigned char) 0x01

/* wheel allocation input data */
struct InputWA
{
  unsigned long ulID;
  unsigned char ucStatus; /*bit7 0;       1;           0;       1
                            bit6 0-> fwd; 0 ->no info; 1 ->bkw; 1 -> tbd
                            bit5 left spinning
                            bit4 tbd
                            bit3 right spinning
                            bit2 0 M4 inactive; 1 M4 active
                            bit1 0      ; 0      ; 1      ; 1
                            bit0 0 -> M0; 1 -> M1; 0 -> M2; 1 M3 */
  unsigned char ucRssi;
};

typedef struct   /* parameterset of walloc */
{
  unsigned char ucWACtrl; /* working mode of wheel allocation def.= 0 = learning allocation,
                            1 = fixed */
  unsigned char AL_State;  /* for it is not very easy in modern autosar system to provide new NVM variables even though running on almost omnipotential controllers we have to misuse an old parameter variable */
} WAParameter;


/*typedef unsigned long tHistoryID;*/
typedef struct
{
    unsigned char ucWACfg;  // 1 = No Learn, 2 = Learn Spéciale, 3 = Complete Learn
} WAParNCfgType;


/***********************************************************************************************
 *Include
 */

/***********************************************************************************************
 *Macros
 */
#define cSumWE  16
#define cMaxLR  4

#define cHiStateTZG (unsigned char) 0x04
#define cHiStateZG (unsigned char) 0x02
#define cHiStateER (unsigned char) 0x01

#define cWheelPos_FL  0x00	/* WP consts 4 use in history */
#define cWheelPos_FR  0x01
#define cWheelPos_RL  0x02
#define cWheelPos_RR  0x03

#define cIDStateSpinning 0x0C /* constants for status of hf-telegramm */
#define cIDStateSpinLeft 0x08
#define cIDStateSpinRight 0x04
#define cRLTelValid 0x80

#define ucBkwdc (unsigned char) 0x40        /* 4 vehicle motion state information passed over in RLtel's CRCR8 */
#define ucNoDriveInfoc (unsigned char) 0x80

#define cIDStateDrvBack 0x40
#define cIDStateNoDrvInfo 0x80
#define cIDStateM4 0x04

#define cWAChange (unsigned char) 0xF0
#define cWAStateChange_FL (unsigned char) 0x80
#define cWAStateChange_FR (unsigned char) 0x40
#define cWAStateChange_RL (unsigned char) 0x20
#define cWAStateChange_RR (unsigned char) 0x10
#define cWAStateBreak 0x08/* return value of ucLearnID interpretation */
#define cWAStateZO 0x04
#define cWAStateER 0x02
#define cWAStateActive 0x01

#define cWAIDChanged 0x00F0
#define cWAWPChanged 0xF000

// macros 4 WAStateHi access
#define cErrorActive (unsigned char) 1
#define cTO (unsigned char) 2
#define cTZG (unsigned char) 4  // at least one and no more than 3 WPs could be assigned
#define cForcedZO (unsigned char) 8

// macros for DAG's autolocation status variable
#define cAL_OK (unsigned char) 100
#define cAL_Stored (unsigned char) 1
#define cAL_Unknown (unsigned char) 2
#define cAL_Error (unsigned char) 3
// autolacation state's events
#define cEvNewIDs (unsigned char) 0
#define cEv4WPs (unsigned char) 1
#define cEvALFailed (unsigned char) 2
#define cEvHoldStore (unsigned char) 8 /*CRS_1211_090_001*/ 

/* WA Parametr configuration */
  #define ucDefWACtrl (unsigned char) 0 //ucWACtrlCyclic;//0 /* learning mode(unsigned char) default */
  #define ucDefAxDistInDm (unsigned char) 31
  #define ucDefWheelDiamInDm (unsigned char) 5
  #define ucDefMinRssiDistance (unsigned char) 7
  #define ucDefLeRiMinDistance (unsigned char) 1

  #define ucECUPosFront (unsigned char) 0x55  /* Parameter (default) constants */
  #define ucECUPosRear (unsigned char) 0xAA

  #define ucDefMinCt4AxAnalysis (unsigned char) 15
  #define ucDefMinCt4ER (unsigned char) 7 // otherwise AÉC overtakes ER
  #define ucDefMinCt4HistER (unsigned char) 3
  #define ucDefMinERMeanRssiLevel (unsigned char) 14 // 15;  2008-11-28 ur - OIL#220
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

#define cSumABSig (unsigned char) 4 // available ABS signals (FL,FR, RL = 3 ; and RR is still missing)
#define cABSStickError (unsigned short) 0xFFFF

//#define pb_ModulTest_050104 /* attend all test cases and generate modultestfile */
#define RealOutput  // generate detailed output telegram by telegram for real data simulation, while OFF only summary is printed
//#define pb_Statistic
//#define pb_FullStatOut  // generates detailed statistic data instead of WA algo simulation

//#define AEC // includes CA as well (allocation eperonner par le cahot)
//#define CA  // ClassicalAllocation; undefine 4 switch OFF CA, which is part of the AEC
#define FPA // fix point allocation ( continental's wheel allocation )

// WAError codes:
// learn/autolocate error codes (used 4 locate and learn error variables of a history slot)
#define NoError (unsigned char) 0 

#define SensorMissin (unsigned char) 1  // not 3 telegams received
#define NoLearnSensor (unsigned char) 2 // not 3 telegams w/ learn bit received

#define BadSpeed (unsigned char) 1      // > 50% of location time w/ speed > 120km/h
#define TooFewPalTels (unsigned char) 2 // < 14 valid PAL telegrams received
#define AmbigWP (unsigned char) 3       // WP is not clear (diff. 2 next deviation minimum < 5%)
#define RivalSensors (unsigned char) 4  // 2 sensors claim same WP, ( at least one other sensor has same error )
#define ABSignalMissin (unsigned char) 5// during location phase at least one time ABS data was not available
#define AssegnazioneCostretto (unsigned char) 6  // sensor was stoically set to historic WP

// modi di autolocatione
#define cNoLearn (unsigned char) 1
#define cSpeciaLearn (unsigned char) 2
#define cCompleteLearn (unsigned char) 3

// modi di DAG's auto learn (ER-Erkennung)
#define Autolearn_Learning (unsigned char) 1  // default after init
#define Autolearn_OK (unsigned char) 2        // 4 sensors learned actively (saved to history)
#define Timeout_3_Sensors (unsigned char) 3   // 3 sensors learned actively (saved to history), 1 is missing
#define Timeout_2_Sensors (unsigned char) 4   // 2 sensors learned actively (saved to history), 2 are missing
#define Timeout_1_Sensor (unsigned char) 5    // 1 sensors learned actively (saved to history), 3 are missing
#define Timeout_No_Sensors (unsigned char) 6  // 0 sensors learned actively (saved to history), 4 are missing

//#define FD_CONTROLS_FALLBACK

/***********************************************************************************************
 *Prototypes
 */
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
#endif //FPA
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

#endif /* WallocX_H */
