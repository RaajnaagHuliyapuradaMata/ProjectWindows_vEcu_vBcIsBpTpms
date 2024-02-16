/***************************************************************************************************
*(c) Beru Electronics GmbH     BEE1     05/2003
*================================================================================================
*
*  $Archive: /LIB/AUTOSAR/SWC/HufTPMSwnh/wnh/USWarnX.h $
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
*   headerfile for usw arning algorithm component sw (contains all external functions, data structures,
*   constants and data to access the us warn algo)
*   :
*
*
*Modul Modification
*
*last modification:
*$Log: /LIB/AUTOSAR/SWC/HufTPMSwnh/wnh/USWarnX.h $
 * 
 * 67    3.09.12 10:41 Rapp
 * 
 * 64    23.09.11 15:09 Dederer
 * Makros fuer Zugriff auf PEce Warnflag definiert
 *
 * 63    11.08.11 15:00 Dederer
 *
 * 62    28.07.11 11:57 Peter
 *
 * 61    28.07.11 11:53 Peter
 * Pwarm (ECExxx) Implementierung
 *
 * 60    4.01.10 10:43 Peter
 * new constants for ucGetWarnTypec
 *
 * 59    2.11.09 14:22 Dederer
 * Korrektur Makro GETbFTXX(Pos)
 *
 * 58    30.10.09 18:01 Dederer
 * Warntyp FT konfiguriert
 *
 * 57    16.03.09 11:30 Dederer
 * additional macros for access to wheel pos specific warnbits defined
 *
 * 56    14.04.08 11:57 Peter
 * Timing resolution for SW warning timer changed from 10sec to 20sec
 * Timer constant all moved to warntype.h (because of model series
 * dependency)
 *
 * 55    2.07.07 10:04 Peter
 * refactoring USWarn
 *
 * 54    12.01.07 17:13 Peter
 * external access to FlatTyre warning bits via macro
 *
 * 53    14.07.06 9:54 Peter
 * FT warntype replaces dPVT warntype
 *
 * 52    10.11.05 14:29 Peter
 * documentation
 *
 * 51    9.11.05 9:11 Peter
 * light version with low resource usage based on V2.3
 *
 * 49    25.10.05 14:19 Peter
 * Warntype TSK ( < SW_40320 VAG311 >) and VW negative reset hysteresis (
 * < SW_40350 VAG311 >) integrated
 *
 * 48    2.08.05 15:30 Peter
 * service for reading temperature compensated FILL pressure according to
 * the service for reading out rated pressure
 *
 * 47    9.03.05 13:21 Peter
 * unnecessarry comment character removed
 *
 * 46    2.03.05 16:24 Peter
 * fill pressure based warning types added
 *
 * 45    1.02.05 17:22 Peter
 * Documentation
 *
 * 44    30.12.04 10:57 Peter
 * supplementary display warning type implemented SW_90 .. SW_150 bmw
 *
 * 43    17.12.04 17:56 Peter
 * documentation update
 *
 * 42    3.12.04 11:02 Peter
 * extra charge on warnlevels of non isochorerated warning types, namely
 * PMin and PFactor.
 * For BMW adaptions.
 *
 * 41    9.09.04 15:26 Peter
 * warntype constant declaration remvod to uswarnx as ordinary defines
 *
 * 40    19.08.04 14:35 Peter
 * MISRA conformance enhanced and uswarn reconfigured for better metrics
 *
 * 38    16.07.04 9:06 Rapp
 * definition of array aushWheelPosWarn[] removed
 *
 * 37    14.07.04 16:52 Peter
 * documentation update
 *
 * 36    21.06.04 15:09 Peter
 * Backup
 *
 * 35    20.02.04 16:13 Peter
 * Diagnosedienst zum Auslesen von PSoll/Tsoll ergänzt
*
* 34    11.11.03 10:55 Peter
* Anpassung an MISRA Subset gem. HIS V1.0
*
* 33    23.10.03 16:43 Peter
* Herstellerspezifische Parametrierfunktionen für MAC und C6LowLine
* entfernt (Verwendung der allgemeinen Parametrierfunktion)
*
* 32    15.10.03 17:46 Peter
* Konstante zum Diagnosdienst ucGetHWFreakBitsc zum Auslesen der
* Freakfilteraktivität eingefügt
*
* 31    9.10.03 17:14 Peter
* Reset Funktion für den Modultest eingeführt
*
* 30    30.09.03 16:14 Peter
* Änderungen aus released bezüglich der Parametrisierungsfunktionen
* nachgezogen
*
* 26    30.09.03 10:49 Wagner
* nicht benutzte Funktion entfernt.
* ucUSWAlgoParaB6
* ucUSWAlgoParaD3
*
* 25    11.09.03 15:33 Peter
* Version 1.1 aus Work
* -Änderung aus Sommererprobung Nardo03 nach Protokoll v.23.08.
* v.Hr.Kessler und Ergänzungen aus d. mail v. 26.08. v. Hr.Brand.
* -Parametrierfunktion wurde allgemeingültig ausgeführt mit Zeiger auf
* Konstantenfeld in der BR
*
* 29    9.09.03 16:18 Peter
* Deklaration für allgemeine Parametrierfunktion
*
* 28    3.09.03 14:36 Peter
* Makros
*
* 27    2.09.03 15:24 Peter
* defines zum Ansprechen der einzelnen Warnbits i.d.WarnVectoren in
* Konstanten überführt
* Macros zum Ansprechen der positionsbezogenen Warnbits und Tankstopbits
* überführt
*
* 26    1.09.03 17:05 Peter
* Konstante für unbekannte Radposition von 5 auf 8 geändert
*
* 25    28.08.03 12:12 Peter
* neuer Warntyp Tankstop implementiert aber noch nicht getestet
*
* 23    22.08.03 14:55 Wagner
* 22.08.2003 mw - UsWarnAlgo mit Hilfe der Schalter :pb_USWarn_260103
* freigegeben/hmy_VariantLoLine_300403/BAUREIHE_C6
*                 in der Baureihe C6_LowLine integriert.
*
*
* 22    1.08.03 15:15 Peter
* Inline Doku auf Stand gebracht
*
* 21    30.07.03 11:12 Peter
* fehler bei prototypen deklaration beseitigt
*
* 20    30.07.03 11:11 Peter
* Prorotyp für Initialisierungsfunktion hinzugefügt
*
* 19    30.07.03 10:52 Peter
* Konstante für neuen Diagnoseservice des AusgabeModuls eingeführt (laden
* von komplettem Warnvectorfeld)
*
* 18    24.07.03 10:31 Peter
* KOnstanten für weiter Diagnosedienste hinzugefügt
* Makros für HW-RR entfernt
*
* 17    22.07.03 10:57 Peter
* Dokumantation update
* Konstanten für neue Diagnosedienste eingefügt
* B6 Parametrierfunktionsdeklaration
*
* 16    16.07.03 12:03 Peter
* Parameter XTra Loard eingeführt mit allen Konsequenzen
*
* 15    14.07.03 16:40 Peter
* Parametrierfunktion für MAC eingeführt
*
* 14    11.07.03 12:11 Peter
* Parametrierfunktion für Audi D3 erstellt
*
* 13    10.07.03 12:08 Peter
* Diagnosedienst für TSSMsgManagerTM() eingefügt (ucClearWarnOfIdc)
*
* 12    10.07.03 9:29 Peter
* 2 weiter DiagDienste hinzugefügt (Auslesen PSoll bei übergebener Temp,
* Auslesen Mindestsolldruck)
*
* 11    4.07.03 17:17 Peter
* Dokumentation
*
* 10    4.07.03 13:20 Peter
* Zugriff auf positionsunspezifisches WW-Bit ermöglicht
*
* 9     2.07.03 15:44 Peter
* Konstante für neuen Diagnose dienst zur Berechnung einer Isochoren
* eingefügt (ucGetIsoc)
*
* 8     26.06.03 17:06 Peter
* ID spezifische Reset Möglichkeit für Warninfo geschaffen
*
* 7     25.06.03 11:26 Peter
* alte Makros zum Zugriff auf Warninformation in ushWarnOutTM (jetzt -
* früher Warnstatus1 und teilw. Warnstatus2) werden jetzt unterstützt
*
* 6     16.06.03 10:19 Peter
* Dokumentation
*
*  changes in 2003
*
*    30.05.2003 pb - 1st established
****************************************************************************************************/
#include "Platform_Types.h"

#ifndef USWarnX_H

#define USWarnX_H
/*
Declaration
*/
/*
Include
*/

/*************************************************************
Macros
*/

// !!! WARNING : the following index definitions must be in accordance with : cAllWT_function !!!! WARNING
/* not changeable WT indexs [0..7] */
#define ucPMinIxc (unsigned char) 0		/* index of warntypes , bits indexed by id */
#define ucDHWIxc (unsigned char) 3
#define ucSoftTIxc (unsigned char) 4

/* variable WT indexes [0..7] */
#define ucEcEIxc (unsigned char) 1
#define ucSFactorIxc (unsigned char) 2

#define ucAllDAGWarningBits (unsigned char) 0x1F  //PMin, EcE, DHW, SFactor
#define cDAG_PMin_WN (uint8) 1
#define cDAG_Hard_WN (uint8) 2
#define cDAG_FPL_WN  (uint8) 8
#define cDAG_Soft_WN (uint8) 4

#define ushGSFc 1024 /* stretchfactor for miso calculations */
/*************************************************************
Prototypes
*/

/************************************************************************************************************
** function:   ChangeWNParaSubSet
**
** ---------------------------------------------------------------------------------------------------------
**
** purpose: start warn- and tssmsg-manager to read or write new parameter set to or from tPSSA
**
**
**
** ---------------------------------------------------------------------------------------------------------
**
** input:
**
** input (global): tPSSA
**
** output (global): tPSSA
**
** output:
**
************************************************************************************************************/

/************************************************************************************************************
** changes in 2003
**
** 22.05.2003 pb - established
************************************************************************************************************/
typedef struct {
 uint16 ui16_V1;          // default = 100
 uint16 ui16_V2;          // default = 150
 uint16 ui16_V3;          // default = 180
 sint8 i8_T0;           // default =  70
 sint8 i8_T1;           // default =  75
 sint8 i8_T2;           // default =  80
 uint16 ui16_HC_MAX;    // default = 600
 uint8 ui8_TempWarnEnable;   // 0 = temperatur/speed warning disabled   default = 1 (enabled)
} TempWarnParaType;

typedef struct {
    uint8 ui8_P_MIN_F;      // default = 1900/25 mBar
    uint8 ui8_P_MIN_R;      // default = 1900/25 mBar
    uint8 ui8_P_MIN_TIRE;   // default = 1500/25 mBar
    uint16 ui16_T_SOFT;   // softwarning time delay IN SECONDS !!  default = 8 x 60 = 480
    uint8 ui8_PERCENT_SOFT; // default = 14
    uint16 ui16_T_HARD;   // hardwarning time delay IN SECONDS !!   default = 4 x 60 = 240
    uint8 ui8_PERCENT_HARD; // default = 20
    uint16 ui16_CONSTANT_DELAY; // TBD
} PWarnParaType;







/***************************************************************************************************
 *Function WarnManagerWN(..)
 *
 *Description
 *Purpose:
 *management of warning algorithm including the calibration of the warning data in the eeprom section
 *takes place here.
 *There are 3 main functions of the warningalgorithm:
 *initialize/reinitialize the warning levels triggered by POR/Kl15 or
 *diagfunctions to configure the warning algorithm and readout data
 *compare an actual datatelegram to the warning levels and generat an adequate output
 *
 *-----------------------------------------------------------------------------------------------
 *
 *  input:
 *    ucAction = action to be done (constants see below)
 *    ptData = pointer to datafield (unsigned char) to be processed as well as returned
 *
 *  output:
 *  see below at sections "return = "
 *
 *detailed:
 *ucAction = ucPorInitc (initialize USWarnAlgo after POR or KL15Change, CountryCode information
 *           is only accepteed if the USWarnAlgo is not yet initialized)
 *ptData = points to single byte which contains ucCountryCode (ucUSCodec, ucEuroSCodec)
 *return = ucWarnStateWN -> MSB	X X X X  X X X X LSB
 *                  									 	 | | | |_ 1 = initialized ; 0 = not initialized
 *										                   | | |___ x = not used
 *								                       |_|_____ 00 = EuroCode ; 01 = ucUSCodec
 *
 *
 *ucAction = ucComparec (generate WarnVector dependent on input data)
 *ptData: to
 *1st	unsigned char ucId;			 0..ucSumWEc
 *		unsigned char ucP;			 0..255, pressure value in ucPResInMBarc
 *		signed char scTWE;			 -40..80, temperature WE in centigrade
 *		unsigned char ucLifeTime;	 remaining lifeTime in months
 *		unsigned char ucState;		 1 normal sendmode of  WE, 2 fast with pressure loss
 *		unsigned char ushVehicleSpeed;   0..65535 speed in km/h
 *		signed char scTa;		 -40..80 outside temperature in centigrade
 *last	unsigned char ucKLState;	 bit0 = kl15, bit1 = kl61
 *return = warnvector =
*    X X X X  X X X X  LSB according to ucId (s.a.)
*    | | | |  | | | |_	PMin Warning
*    | | | |  | | |___	PFactor
*    | | | |  | |_____	DHW
*    | | | |  |_______	FT
*    | | | |__________	HardT
*    | | |____________  HardVT
*    | |______________	SoftT
*    |________________  TS (tankstop)
 *
 *ucAction = ucDiagServicec ( execute diagnostic service to change or read parameter values)
 *ptData: to
 *1st		ucCfgPSollMinc (diag sevrice set single minimal rated value for id X)
 *		IdX [0..ucSumWEc] index of id
 *last	PSoll / ucPResInMBarc
 *return =  write with succes -> ucWarnStateWN
 *		  ERROR -> 0
 *
 *ptData: to
 *1st		ucCfgReInitSinglec (diag sevrice set single soll value for id X)
 *		IdX [0..ucSumWEc] index of id
 *		PSoll / ucPResInMBarc
 *last	Cal Temperature in Centigrade (signed char)
 *return =  write with succes -> ucWarnStateWN
 *		  ERROR -> 0
 *
 *ptData: to
 *1st		ucCfgPMinc (diagservice set new PMin value)
 *		PMIn / ucPResInMBarc (0 means def)
 *		filter reload value in counts (0 means def)
 *last	Hysteresis to PSoll / ucPResInMBarc (0 means def)
 *return =  write with succes -> ucWarnStateWN
 *		  ERROR -> 0
 *
 *ptData: to
 *1st		ucCfgCtryCodec	(diagservice to configure country code)
 *last	ucCountryCode (ucUSCodec, ucEuroCodec)
 *return =  write with succes -> ucWarnStateWN
 *		  ERROR -> 0
 *
 *ptData: to
 *1st		ucResetWarnVectorc	(diagservice to reset the warning information of one or all ids)
 *last	0,1,..,ucSumWEc (reset warninformation (= Warnbits in vectors, filters) for all ids)
 *return =  reset with succes -> ucWarnStateWN
 *		  ERROR -> 0
 *
 *ptData: to
 *1st     ucGetPSollAtTempc (calculate rated pressure value at temperatur X)
 *        Temp (-40..120, -128 -> service returns PSoll wihtout temperature dependency)
 *last    Id (0,1,..(ucSumWEc-1))
 *return = 0x00 (iO)
 *         0xFF  (ERROR)
 *         indirect : *ptData PSollAtTempX / ucPResInMBarc (abs.)
 *
 *ptData: to
 *1st     ucGetPSollMinc (return absolute minmum rated pressure value)
 *last    Id (0,1,..(ucSumWEc-1))
 *return = 0x00 (iO)
 *         0xFF  (ERROR)
 *         indirect : *ptData PSollMin / ucPResInMBarc (abs.)
 *
 *ptData: to
 *1st/last ucGetWarnVectorsc
 *return: 0 (iO)
 *indirect:   ptData     = &WarnVector of id 0  ( SW_10070 )
 *            ptData + 2 = &WarnVector of id 1
 *            ptData + 4 = &WarnVector of id 2
 *            ptData + 6 = &WarnVector of id 3
 *            ptData + 8 = &WarnVector of id 4
 *
 *ptData: to
 *1st/last ucGetHWFreakBitsc
 *return: *ptData:
 *b0 = 1 freak filter id 0 (= zompos0) of hardwarningtype is active / 0 = inactive = LSB
 *b1 = 1 freak filter id 1 (= zompos1) of hardwarningtype is active / 0 = inactive
 *b2 = 1 freak filter id 2 (= zompos2) of hardwarningtype is active / 0 = inactive
 *b3 = 1 freak filter id 3 (= zompos3) of hardwarningtype is active / 0 = inactive
 *
 *b4 = 1 freak filter id 4 (= zompos4) of hardwarningtype is active / 0 = inactive
 *b5 = not used allways 0
 *b6 = not used allways 0
 *b7 = not used allways 0                                                           = MSB
 *=> range = 0..0x1F
 *
 *ptData: to
 *1st     ucGetPTSollc (return absolute  rated pressure & temperature value)
 *last    Id (0,1,..(ucSumWEc-1))
 *return: 0 (i.O) v 0xff (bad ID)
 *        *ptData:   Psoll
 *        *ptData+1: Tsoll
 *ptData: to
 *1st		ucCfgSDcc (diagservice to configure dislpay warning type SD)	SW_80
 *		  difference to rated pressure (0 means default)
 *last  filter reload value in counts (0 means def)
 *return =  write with succes -> ucWarnStateWN
 *					ERROR -> 0
 *ptData: to
 *1st		ucPutPTFillc (diag sevrice set single soll value for id X)     comment: SW_900140 C6 LL DB
 *		  IdX [0..ucSumWEc] index of id
 *		  PFill / ucPResInMBarc
 *last	Fill Temperature in Centigrade (signed char)
 *return =  write with succes -> ucWarnStateWN (>0)
 *		  ERROR -> 0
 *ptData: to
 *1st     ucGetPTFillc (return absolute  rated pressure & temperature value)  comment: SW_900140 C6 LL DB
 *last    Id (0,1,..(ucSumWEc-1))
 *return: 0 (i.O) v 0xff (bad ID)
 *        *ptData:   Psoll
 *        *ptData+1: Tsoll
 ******************************************************************************************************/
extern unsigned char ucWarnManagerWN(unsigned char ucAction, unsigned char *ptData);


struct HFTel
{
	unsigned char ucId;			  /* 0..ucSumWEc 0 */
    unsigned char ucP;			  /* 0..255, pressure value in ucPResInMBarc 1 */
    signed char scTWE;			  /* -40..80, temperature WE in centigrade 2 */
    unsigned char ucLifeTime;	/* remaining lifeTime in months 3 */
    unsigned char ucState;		/* 1 normal sendmode of  WE, 2 fast with pressure loss 4 */
    unsigned short ushVehicleSpeed;/* 0..65535 speed in 1 km/h 5 */
    signed char scTa;			    /* -40..80 outside temperature in centigrade 7 */
    unsigned char ucKLState;	/* bit0 = kl15, bit1 = kl61 8 */
};


/***************************************************************************************************
*Function ucTSSMsgManagerTM(..)
*
*Description
*Purpose:
*converts the detailed warning information of the uswarn modul to a uswarnalgorithm specification
* conform output.
*The ucTSSMsgMangerTM has to be initialized after POR an KL15 change. The filter parameter of the
*output module can changed by so called diagnsotic services. For position specific warning types
*also the wheel position information is required (can be loaded or cleared by diag. serv. or the
*module collects the position information from the actual warning data (see below)).
*
*
*-----------------------------------------------------------------------------------------------
*input:
*ucAction = action to be done
*ptData = pointer to data to be processed
*
*detailed:
*
*ucAction = ucPorInitc (initialize USWarnAlgoOutput after POR or KL15Change, all warning incl.
*             position information will be cleared !)
*ptData = points to array of 3 bytes which contain outputfilterconfiguration (see below)
*         (only processed if module is not yet init.)
*         according to the tPSSA ConfigBytes:
*  Byte[1] MSB - 0 - SollDruck tankstop (warning type TS) active
*                0 - SollDruck DPisoww (warning type ST) active
*                0 - SollDruck DPisovhi (warning type HTV) active
*                0 - SollDruck DPiso (warning type HT) active
*
*                0 - FlatTire (warning type FT) active
*                0 - DHW (warning type DHW) active
*                0 - Solldruck - X% (PFactor)
*          LSB - 0 - tbd
*  Byte[0] MSB - X - tbd
*                1 - minimum limit PMin warning = 1,6Bar X'tra Loard
*                1 - spare tyre warning only PMin
*                1 - spare tyre warning as running tyres
*
*                1 - activate spare tyre warning i.g.
*                1 - reset condition isochore rated
*                1 - country code EU
*          LSB - 1 - country code US
*
*  if the 2 bytes (Byte[0] und Byte[1]) are 0 -> default configuration gets chosen automatically
*  default: Byte[1] = 0x00
*           Byte[0] = 0x28
*
*
*return = ucTSSMsg StateTM -> MSB	X X X X  X X X X LSB
*				                      						     | |_ 1 = initialized ; 0 = not initialized
*										                           |___ x = not used
*_____________________________________________________________________________________________________
*ucAction = ucTssMsgOutc (generate new warning output based at the warninfo of uswarn)
*ptData: points to
*1.byte unsigned char ucId;			 0..ucSumWEc, 0xFF = no id specific information
*	      unsigned char ucPos;			 0..4 = FL..ST, 5 = wheel position unknown
*	      unsigned char ucSystemState;	 tbd KL15, DTC inactive, bit15 = 1 -> display warnings wheel pos spec.
*last   unsigned char ushWarning;
*   X X X X  X X X X  LSB according to ucId (s.a.)
*   | | | |  | | | |_	PMin Warning
*   | | | |  | | |___	PFactor
*   | | | |  | |_____	DHW
*   | | | |  |_______	FT
*   | | | |__________	HardT
*   | | |____________  HardVT
*   | |______________	SoftT
*   |________________  TS (tankstop)
*return:
*update of global variable  ushWarnOutTM
*_____________________________________________________________________________________________________
*ucAction = ucDiagServicec
*ptData: point to
*1st byte = ucGetWarnVectorc (= const.) read detailed warninformation (return value) of a specific id
*last       ucId = 0..4 = FL..ST, 5 = wheel position unknown
*return:
*bit coded warning:
*   X X X X  X X X X  LSB according to ucId (s.a.)
*   | | | |  | | | |_	PMin Warning
*   | | | |  | | |___	PFactor
*   | | | |  | |_____	DHW
*   | | | |  |_______	FT
*   | | | |__________	HardT
*   | | |____________  HardVT
*   | |______________	SoftT
*   |________________  TSB (tankstop)
*
*ptData points to
*1st byte = ucNewPositionsc (write set of new WPs to the function)
*           ucWPID0 = WP for id 0 (0..ucSumWEc, ucSumWEc>= means WP unknown)
*           ucWPID1 = WP for id 1 (0..ucSumWEc, ucSumWEc>= means WP unknown)
*           ucWPID2 = WP for id 2 (0..ucSumWEc, ucSumWEc>= means WP unknown)
*           ucWPID3 = WP for id 3 (0..ucSumWEc, ucSumWEc>= means WP unknown)
*last       ucWPID4 = WP for id 4 (0..ucSumWEc, ucSumWEc>= means WP unknown)
*return:
*0x00 OK - new WP table written
*0xFF ERROR
*_____________________________________________________________________________________________________
*ptData points to
*1st byte = ucClearPosc (set all WP  to unknown)
*return:
*0x00 OK
*_____________________________________________________________________________________________________

*1st byte = ucDeActivateIdc
*           0 -> deactivate Filter, 1-> activate Filter
*           id  (0,1..ucSumWEc, ucSumWEc clear complete ushWarnOutTM)
*last       wheel position specific display (== 0x80) or none wheel specific display (<> 0x80)
*return:
*0x00 OK - id activeted or deactivated
*
*1st/last byte = ucGetWarnVectorsIdc
*return = 0 O.K.
*indirect:   *ptData       = WV_ID0
*            *(ptData + 1) = WV_ID1
*            *(ptData + 2) = WV_ID2
*            *(ptData + 3) = WV_ID3
*            *(ptData + 4) = WV_ID4
*
*1st byte = ucPutWarnVectorSetc
*           *(ptData + 1) = WV_ID0
*           *(ptData + 2) = WV_ID1
*           *(ptData + 3) = WV_ID2
*           *(ptData + 4) = WV_ID3
*           *(ptData + 5) = WV_ID4
*
*return = 0 O.K.
*
***/

extern unsigned char ucTSSMsgManagerTM(unsigned char ucAction, unsigned char *ptData);
struct TssMsg
{
  unsigned char ucId;				    /* 0..ucSumWEc, 0xFF = no id specific information */
  unsigned char ucPos;			    /* 0..4 = FL..ST, 8 = wheel position unknown */
  unsigned char ucSystemState;	/* bit7=1 wheelpos active; bit1 = KL61; bit0 = KL15 */
  unsigned char ucWarning;    /* please, take documentation of this from that section below */
};
/*bit coded warning in ucWarning:
*      X X X X  X X X X  LSB according to ucId (s.a.)
* 	   | | | |  | | | |_	PMin Warning
* 	   | | | |  | | |___	PFactor
* 	   | | | |  | |_____	DHW
* 	   | | | |  |_______	FT
* 	   | | | |__________	HardT
* 	   | | |____________  HardVT
* 	   | |______________	SoftT
*      |________________  TS (tankstop)
*/

/************************************************************************************************************
** function:   TimerWT()
**
** ---------------------------------------------------------------------------------------------------------
**
** purpose: time management of uswarnmodul
** (softwarning timefilters  scan )
** needs to be called cyclic at task level !
** CYCLE TIME NEEDS TO BE DEFINED IN USWARNX:H BY ushCallFreqInMSWTcCycle (100..1000ms)
** ---------------------------------------------------------------------------------------------------------
**
** input: ucAction = ucCountc = const -> cyclic call
**        ucAction = ucIniTimec = const -> initialization after POR
**
** input (global):
**
** output (global): ucTime1sec = divider to scale one second
**
** output:
**
************************************************************************************************************/
//extern void TimerWT( unsigned char ucAction );
extern void TimerWTinit(void);


/************************************************************************************************************
** function:   InitUSWAlgo
**
** ---------------------------------------------------------------------------------------------------------
**
** purpose: initialization of uswarningalgorithm including reload of eeprom data (config & warnbit stuff)
**
** ---------------------------------------------------------------------------------------------------------
**
** input:
**
** input (global):
**
** output (global):
**
** output:
**
**
************************************************************************************************************/

/************************************************************************************************************
** changes in 2003
**
** 30.07.2003 pb - established
************************************************************************************************************/
extern void InitUSWAlgo(const unsigned char *);

/*************************************************************
defines
*/
/* tss specific stuff */

#define ucWPFLc (unsigned char) 0	/* wheel position front left */
#define ucWPFRc (unsigned char) 1	/* wheel position front right */
#define ucWPRLc (unsigned char) 2	/* wheel position rear left */
#define ucWPRRc (unsigned char) 3	/* wheel position rear right */
#define ucWPSTc (unsigned char) 4	/* wheel position spare tire */
#define ucWPUNc (unsigned char) 8	/* wheel position unknown */


/****************************** states of modules ****************************/
/********** common states **********/
#define ucPorInitc 1		/* types of tss basic sub component initialization */
#define cKl15Init 2
#define cSingleIdInit 3	    /* id specific parts of subcomponent get initialized */
#define ucDiagServicec 4    /* execute diagnosis service in warnmanager */
#define ucPorInitUSc 5      /* as ucPorInitc but use of US specific default values than europe values */
/******** states of warn  ********/
#define ucComparec 5		/* generate warning based on actual telegram data (id) */
/* sub states of warn: dignosis services */
#define ucCfgCtryCodec  1	/* configure country code */
#define ucResetWarnVectorc 14   /* clear warning info for a specific id or for all id */
#define ucCfgPSollMinAtIdc 15   /* config new id specific mimimum rated value pair */
#define ucGetIsoc 16        /* calculate isochore P/T */
#define ucGetPSollAtTempc 17/* calculate rated pressure value at temperature */
#define ucGetPSollMinc 18   /* return minimum rated pressure value */
#define ucGetWarnVectorsc 19/* return internal WarnVectorArray id specific order */
#define ucCfgPFactorc  24   /* config pfactor warning type */
#define ucCfgDHWc 25        /* config dynamic hard warning */
#define ucCfgFTc  26      /* config temperatur dependent low speed warning */
//#define ucCfgHTc 27         /* config conventional hard warning type */
#define ucCfgEcEc 27         /* config conventional EcE warning type */
#define ucCfgHTVc 28        /* config temperatur dependent high speed warning */
#define ucCfgSTc  29        /* config temperatur dependent soft warning */
#define ucCfgTSc 30
#define ucGetWarnTypec 31   /* get ID/bit indexed active warning of a specific warntype: buf[0]=ucDiagServicec, */
                            /*  buf[1]=ucGetWarnTypec, buf[2]=WarnType (e.g. 7 for TSB), buf[3]=return value */
/******* states of tssmsg ********/
#define ucTssMsgOutc 6		/* transform all warnings to a system conform warning for one id */
/* sub states of tssmsg */
/* no longer supp.  #define ucGetWarnVectorc 1	*/ /* diagservice to get detailed wpspec. warninfo */
#define ucNewPositionsc	2	/* diagservice write down new position table */
#define ucClearPosc 3       /* diagservice clear all wp info and wp specific warnings */
/* no longer supp.  #define ucDeActivateIdFilterc 7  */ /* id specific warning can be switched on/off in ushWarnOutTM */
#define ucPutWarnVectorSetc 9   /* load a complete warnvector set into the output module */
/******* states of uswtime ********/
#define ucCountc (unsigned char) 7
#define ucIniTimec (unsigned char) 8



/*
Data
*/

/************************************************************************************************************/
/* wheel position specific warnbits for Mr. Kessler  :
 *aushWheelPosWarn[0..5] = aushWheelPosWarn[FL..ST,unspecific] =
 *
*      X X X X  X X X X  LSB according to ucId (s.a.)
* 	   | | | |  | | | |_	PMin Warning
* 	   | | | |  | | |___	PFactor
* 	   | | | |  | |_____	DHW
* 	   | | | |  |_______	FT
* 	   | | | |__________	HardT
* 	   | | |____________  HardVT
* 	   | |______________	SoftT
*      |________________  TS (tankstop)
 */
//unsigned short aushWheelPosWarn[ucMaxPosc + 1];/* +1 for undefined wheel position ( SW_10060 )*/

extern unsigned char aucWheelPosWarn[];

//@@GL new function to access the comple warning vector
#define GETaucWheelPosWarn(Pos) (aucWheelPosWarn[Pos])

extern uint8 ui8GetHardWrnOfWP(uint8 ui8WP);
extern uint8 ui8GetSoftWrnOfWP(uint8 ui8WP);
// TODO: macros 4 access 2 OEM warnings @@GL use this and remove comment
#define GETbWrnPMin_FL() ( (aucWheelPosWarn[ucWPFLc] & ((unsigned char) (1<<ucPMinIxc)) ) == ((unsigned char) (1<<ucPMinIxc))  )  // DAG's PMin warning
#define GETbWrnPMin_FR() ( (aucWheelPosWarn[ucWPFRc] & ((unsigned char) (1<<ucPMinIxc)) ) == ((unsigned char) (1<<ucPMinIxc))  )  
#define GETbWrnPMin_RL() ( (aucWheelPosWarn[ucWPRLc] & ((unsigned char) (1<<ucPMinIxc)) ) == ((unsigned char) (1<<ucPMinIxc))  )  
#define GETbWrnPMin_RR() ( (aucWheelPosWarn[ucWPRRc] & ((unsigned char) (1<<ucPMinIxc)) ) == ((unsigned char) (1<<ucPMinIxc))  )  
#define GETbWrnPMin_UK() ( (aucWheelPosWarn[4] & ((unsigned char) (1<<ucPMinIxc)) ) == ((unsigned char) (1<<ucPMinIxc))  )  
#define GETbWrnPMin_WP(Pos) ( (aucWheelPosWarn[Pos] & ((unsigned char) (1<<ucPMinIxc)) ) == ((unsigned char) (1<<ucPMinIxc))  )

#define GETbWrnHard_WP(Pos) ( (uint8) 1 == ui8GetHardWrnOfWP(Pos)  )
#define GETbWrnHard_FL() ( GETbWrnHard_WP(ucWPFLc) )  // DAG's Hard warning 
#define GETbWrnHard_FR() ( GETbWrnHard_WP(ucWPFRc) )
#define GETbWrnHard_RL() ( GETbWrnHard_WP(ucWPRLc) )
#define GETbWrnHard_RR() ( GETbWrnHard_WP(ucWPRRc) )
#define GETbWrnHard_UK() ( GETbWrnHard_WP(4) )

#define GETbWrnSoft_WP(Pos) ( (uint8) 1 == ui8GetSoftWrnOfWP(Pos)  )
#define GETbWrnSoft_FL()  ( GETbWrnSoft_WP(ucWPFLc) ) // DAG's Soft warning
#define GETbWrnSoft_FR()  ( GETbWrnSoft_WP(ucWPFRc) )
#define GETbWrnSoft_RL()  ( GETbWrnSoft_WP(ucWPRLc) )
#define GETbWrnSoft_RR()  ( GETbWrnSoft_WP(ucWPRRc) )
#define GETbWrnSoft_UK()  ( GETbWrnSoft_WP(4) )

#define GETbWrnFastLoss_FL() ( (aucWheelPosWarn[ucWPFLc] & ((unsigned char) (1<<ucDHWIxc)) ) == ((unsigned char) (1<<ucDHWIxc))  )  // DAG's Fast pressure loss warning
#define GETbWrnFastLoss_FR() ( (aucWheelPosWarn[ucWPFRc] & ((unsigned char) (1<<ucDHWIxc)) ) == ((unsigned char) (1<<ucDHWIxc))  )  
#define GETbWrnFastLoss_RL() ( (aucWheelPosWarn[ucWPRLc] & ((unsigned char) (1<<ucDHWIxc)) ) == ((unsigned char) (1<<ucDHWIxc))  )  
#define GETbWrnFastLoss_RR() ( (aucWheelPosWarn[ucWPRRc] & ((unsigned char) (1<<ucDHWIxc)) ) == ((unsigned char) (1<<ucDHWIxc))  )  
#define GETbWrnFastLoss_UK() ( (aucWheelPosWarn[4] & ((unsigned char) (1<<ucDHWIxc)) ) == ((unsigned char) (1<<ucDHWIxc))  )  
#define GETbWrnFastLoss_WP(Pos) ( (aucWheelPosWarn[Pos] & ((unsigned char) (1<<ucDHWIxc)) ) == ((unsigned char) (1<<ucDHWIxc))  )

#define GETbWrnPreSoft_FL() ( (aucWheelPosWarn[ucWPFLc] & ((unsigned char) (1<<ucSoftTIxc)) ) == ((unsigned char) (1<<ucSoftTIxc))  )  // DAG's pre soft warning (soft-threshold + 10 kPa)
#define GETbWrnPreSoft_FR() ( (aucWheelPosWarn[ucWPFRc] & ((unsigned char) (1<<ucSoftTIxc)) ) == ((unsigned char) (1<<ucSoftTIxc))  )  
#define GETbWrnPreSoft_RL() ( (aucWheelPosWarn[ucWPRLc] & ((unsigned char) (1<<ucSoftTIxc)) ) == ((unsigned char) (1<<ucSoftTIxc))  )  
#define GETbWrnPreSoft_RR() ( (aucWheelPosWarn[ucWPRRc] & ((unsigned char) (1<<ucSoftTIxc)) ) == ((unsigned char) (1<<ucSoftTIxc))  )  
#define GETbWrnPreSoft_UK() ( (aucWheelPosWarn[4] & ((unsigned char) (1<<ucSoftTIxc)) ) == ((unsigned char) (1<<ucSoftTIxc))  )  
#define GETbWrnPreSoft_WP(Pos) ( (aucWheelPosWarn[Pos] & ((unsigned char) (1<<ucSoftTIxc)) ) == ((unsigned char) (1<<ucSoftTIxc))  )

/************************************************************************************************************
* global output of ushWarnOutTM
*
*MSB
*X   -   not used
*X   -   not used
*X   -   not used
*X   -   not used
*
*X   -   WW No Pos
*X   -   WW spare tyre
*X   -   WW rear right
*X   -   WW rear left
*
*
*X   -   WW front right
*X   -   WW front left
*X   -   (HW spare tyre - not used)
*X   -   HW rear right
*
*X   -   HW rear left
*X   -   HW front right
*X   -   HW front left
*X   -   HW no wheel position
*LSB
*/
extern unsigned short ushWarnOutTM;


/* macros for accessing the global ushWarnOutTM output variable by transmit -modul */
/* the naming convention is dependent to former tss systems */


#define GETushWarnstatus1WN()  ( ushWarnOutTM )
#define GETucLoWarnstatus1WN() ( (unsigned char) ushWarnOutTM )
#define GETucHiWarnstatus1WN() ( (unsigned char) (ushWarnOutTM >> 8) )

/************************************************************************************************************/


//TODO: @@GL use this for "7 Temperature Warning" and remove comment, if active add this:
//7.3 Temperature Warning Message Memory
//A separate message memory shall store the last 5 temperature warning events.
//Environment data : Odometer, time, tire pressures, tire temperatures, T_ambient, Temp_WarnDisp_Rq, Tire_Temp_Stat_XY
//A new entry shall be stored when TPM_Temp_WarnDisp_Rq increases.
extern uint8 ui8OvrHeatWrnIsActive(void);     // returns 0 = no méssage, 1 = over eat , 2 = reduce speed

extern uint8 ui8GetOvrHeatId(uint8 * pui8ZPos); // returns amount of OverHeatWarning affected zom IDs [0..4], writes affected IDs to pui8ZPos [0..3] low nibble and warn colour to high nibble

// uint8 ui8GetTempColeurWP(const uint8 ui8WP) and uint8 ui8GetTempColeurWP_xx(void)
// purpose: returns: last received sensor's temperature color according to 7.2 CAN-Signals for Temperature Warning
//                   0xFF if wheel position is not available
//          [parameter: ui8WP = 0,1..3 = FL,FR..RR, 4 unspecific wheel position returns max temperature's colour ]
extern uint8 ui8GetTempColeurWP(const uint8 ui8WP);
extern uint8 ui8GetTempColeurWP_FL(void);
extern uint8 ui8GetTempColeurWP_FR(void);
extern uint8 ui8GetTempColeurWP_RL(void);
extern uint8 ui8GetTempColeurWP_RR(void);
extern uint8 ui8GetTempColeurWP_UK(void);
extern uint16 ui16GetSofTimerInSec(void);
extern uint16 ui16GetHarTimerInSec(void);
extern uint16 ui16GetFilterSpeedInKmh(void);
extern uint16 ui16GetOvrHeatCt(void);
extern uint16 ui16GetCombVSpeed(uint16 ui16CurVehSpeed);



extern uint8 ui8GetPRelComp2Tref(sint8 i8Tcur, uint8 ui8Ix); // returns relative pressure value compensated to Tref
extern sint8 i8GetTref(uint8 ui8Ix); // returns rated temperature 
extern uint8 ui8GetPRefRel(uint8 ui8Ix); // returns relative rated pressure value at Tref
extern uint8 ui8HarTimerActive(void);  // returns DAG's HardWarningTimer activity BitX[0..3] = 1 -> Timer of ID in HistColX is active
extern uint8 ui8SofTimerActive(void);  // returns DAG's SoftWarningTimer activity BitX[0..3] = 1 -> Timer of ID in HistColX is active

extern uint8 ui8CalActive(void);  // used interface 4 WarnHandler normally located in USWarnIf......... returns > 0 if calibration is running
extern uint8 ui8MfdCalActive(void);  // used interface 4 WarnHandler normally located in USWarnIf......... returns > 0 if only MFD calibration is running
extern uint8 ui8NoHoldOff(void);  // used interface 4 WarnHandler normally located in USWarnIf......... returns > 1 if hold_off = 0
extern uint8 ui8KL15OFF(void);    // used interface 4 WarnHandler normally located in USWarnIf......... returns > 0 if clamp15 is OFF

#define cNORMAL (unsigned char) 0
#define cSOFT_WARNING (unsigned char) 1
#define cHARD_WARNING (unsigned char) 2
#define cFAST_DEFLATION (unsigned char) 3

extern unsigned char GetucTPM_WarnDisp_Rq(void); // returns DAG's TPM_WarnDisp_Rq
extern void TimerWTinit(void);
extern void KL15OffWarnInit(const unsigned char *ptWPos);
extern void UpdateGlobWrnLvlNWarnDisp(void);

extern unsigned short ushMIso(unsigned char ucP, signed char scT);

extern uint8 ui8GenPWP(uint8 * p2PWP);

extern uint16 ui16GetSpeedCtInSec(void);

extern void DelWarnOfId(uint8 ui8HistColOfID);

extern uint8 ui8GetWarntypeOfHistCol(uint8 ui8WnType, uint8 ui8HistCol);
extern void ResetM1Pressure(unsigned char i);
extern void GETDAGWrnLvlOfIdCol(uint8 ui8ColOfId, uint8 * p2WrnLvls);
extern uint8 ui8GETDAGClrWrnThresOfIdCol(uint8 ui8ColOfId);
extern uint8 NewPositionsUSWIF( const uint8 * );
#endif  /* USWarnX_H */
