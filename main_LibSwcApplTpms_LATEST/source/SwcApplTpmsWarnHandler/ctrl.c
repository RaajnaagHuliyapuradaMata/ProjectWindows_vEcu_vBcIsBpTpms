/*
(c) Beru Electronics GmbH     BEE1     02/2003
================================================================================================

$Archive: /LIB/USWarn/versions/light/ctrl.c $

file status:   under construction
------------------------------------------------------------------------------------------------

author:        Peter Brand                Beru Electronics GmbH

intials:       pb

Modul Description

Global description:
Purpose:
super module of modular tss system. Contains external interface to rf-receive module, diag-channel.
 And internal interfaces to all tss modules. Incoming external data will be filtered/prepared
 here and be distributed to the residual modules. Also inner information from one inner module to
 the next flows through the ctrl module.
 The module is realized as extended task.

Modul Modification
changes in 2003
10.02.2003 pb - 1st established
12.06.2003 pb - documentation update
$Log: /LIB/USWarn/versions/light/ctrl.c $
 * 
 * 41    4.01.10 16:57 Peter
 * support only 4 wheel positions at initialization
 * 
 * 40    9.10.08 18:23 Peter
 * adatpted to 4 IDs and 4 wheel positions
 * 
 * 39    2.07.07 10:04 Peter
 * refactoring USWarn
 *
 * 38    9.11.05 9:11 Peter
 * light version with low resource usage based on V2.3
 *
 * 35    30.12.04 10:57 Peter
 * supplementary display warning type implemented SW_90 .. SW_150 bmw
 *
 * 33    7.12.04 16:43 Peter
 * bugfix in parametrisation
 *
 * 32    3.12.04 11:02 Peter
 * extra charge on warnlevels of non isochorerated warning types, namely
 * PMin and PFactor.
 * For BMW adaptions.
 *
 * 31    19.08.04 14:35 Peter
 * MISRA conformance enhanced and uswarn reconfigured for better metrics
 *
 * 29    14.07.04 16:51 Peter
 * documentation update
 *
 * 28    21.06.04 15:09 Peter
 * Backup
 *
 * 27    11.11.03 10:55 Peter
 * Anpassung an MISRA Subset gem. HIS V1.0
 *
 * 26    23.10.03 14:53 Peter
 * Herstellerspezifische Parametrierfunktionen für MAC und C6LowLine
 * entfernt (Verwendung der allgemeinen Parametrierfunktion)
 *
 * 25    9.10.03 17:13 Peter
 * Reset Funktion für den Modultest eingeführt
 *
 * 24    30.09.03 16:14 Peter
 * Änderungen aus released bezügich der Parametrisierungsfunktionen
 * nachgezogen
 *
 * 33    30.09.03 10:49 Wagner
 * nicht benutzte Funktion entfernt.
 * ucUSWAlgoParaB6
 *
 * 32    30.09.03 10:36 Wagner
 * unnoetige Funktionen und deklarationen entfernt.
 *
 * ucUSWAlgoParaD3(..
 *
 * 31    30.09.03 10:14 Dederer
 * cd - Kleine Korrektur in allgemeiner Parametierfunktion bzgl. extraload
 *
 * 30    29.09.03 17:54 Peter
 * Xtra Loard Bit wird in Funktionsparameter für allgemeine
 * Parametrierfunktion übergeben
 *
 * 29    26.09.03 15:33 Rapp
 * Parameterueberpruefung in die Aufrufende Funktion verlagert
 *
 * 28    19.09.03 16:03 Rapp
 * ucWWFilter = 15 (für USA und RDW)
 *
 * 27    19.09.03 14:51 Rapp
 * ucUSWAlgoParaD3 modifiziert (Probleme mit Universalfunktion)
 *
 * 26    18.09.03 16:20 Rapp
 * Berechnung des Mindestwarndrucks in der universellen
 * Parametrierfunktion korrigiert
 *
 * 25    11.09.03 15:33 Peter
 * Version 1.1 aus Work
 * -Änderung aus Sommererprobung Nardo03 nach Protokoll v.23.08.
 * v.Hr.Kessler und Ergänzungen aus d. mail v. 26.08. v. Hr.Brand.
 * -Parametrierfunktion wurde allgemeingültig ausgeführt mit Zeiger auf
 * Konstantenfeld in der BR
 *
 * 23    9.09.03 16:18 Peter
 * Allgeimeine Parametrierfunktion eingeführt
 *
 * 23    6.09.03 12:54 Rapp
 * Druckdifferenz bei WW = 0,3bar, bei HW = 0,4bar (für RDW und USA)
 *
 * 22    5.09.03 14:41 Rapp
 * pressure difference to psoll for hw (HT) = 400mbar
 *
 * 21    28.08.03 15:50 Rapp
 * MAC: Parametrierbyte nach Vorgabe Zeuner, Kessler geändert
 *
 * 20    22.08.03 14:55 Wagner
 * 22.08.2003 mw - UsWarnAlgo mit Hilfe der Schalter :pb_USWarn_260103
 * freigegeben/hmy_VariantLoLine_300403/BAUREIHE_C6
 *                 in der Baureihe C6_LowLine integriert.
 *
 *
 * 19    11.08.03 11:06 Peter
 * Für Kodierung D3 wird HW-Code 7 und 8 unterstützt !
 *
 * 18    4.08.03 11:48 Peter
 * Initialisierung des Parametersatzes tPSSA bevor dieser gezielt geändert
 * wird um nicht geänderte Groessen mit default Werten zu beladen die von
 * der jungfräulichen Initialisierung stammen
 *
 * 17    30.07.03 10:53 Peter
 * Initialisierungsroutine für USWAlgo eingeführt, erforderlich für das
 * Halten der Warnbits im EEPROM
 *
 * 16    23.07.03 14:20 Peter
 * Bei Konfiguration von PMin in den Codier/Parametrierfunktionen wird für
 * die Hysterese von PMin die allgemeingültige Hysterese (300mBar bei
 * Audi) verwendet
 *
 * 15    23.07.03 10:38 Rapp
 * US-Warnmodul integriert
 *
 * 14    22.07.03 10:56 Peter
 * Parametrisierungsfunktion für B6 eingefügt muss von ur noch angepasste
 * werrn
 *
 * 13    21.07.03 10:34 Rapp
 * schreiben von Mindestsolldruck und Mindestwarndruck an MAC angepaßt
 *
 * 12    18.07.03 11:40 Rapp
 * Anpassung der Parametrierfunktion für MAC
 *
 * 11    16.07.03 14:46 Peter
 * Hysterese auf 300mBar gesetzt für AudiD3 Kodierung
 *
 * 10    16.07.03 12:03 Peter
 * Parameter XTra Loard eingeführt mit allen Konsequenzen
 *
 * 9     14.07.03 16:41 Peter
 * MAC Parametrierfunktion eingeführt
 *
 * 8     11.07.03 12:11 Peter
 * Parametrierfunktion für Audi D3 erstellt
 *
 * 7     16.06.03 10:24 Peter
 * Dokumentation
*/

/*******************************************************************************
Declaration
*/

/*******************************************************************************
Include
*/

#include "USWarnX.h"
#include "global.h"
#include "DAG_TVWarn.h"
#include "WnTypePar.h"
#include "Appl_TPMS_Dcm.h" /*CRS_1211_132_104*/
#include "wallocX.h"

/*******************************************************************************
Macros
*/

/*******************************************************************************
Data
*/

TempWarnParaType tDAG_TemPara;
PWarnParaType tDAG_PPara;

/*******************************************************************************
Implementation
*/

/*******************************************************************************
private functions
*/
static void RdDAGPara(void);
static void InitDefValPPara(void);
static void InitDefValTemPara(void);


static uint8 ui8GetDAGTempWarnPara(TempWarnParaType * ptTemPara);   // TODO: provided by AS
static uint8 ui8GetDAGPWarnPara(PWarnParaType * ptPPara);           // TODO: provided by AS
/*******************************************************************************
public functions
*/



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
 ** 10.07.2004 pb - srw adaption
 ** 22.07.2004 pb - misra conformance enhancement
 ** 28.10.2005 pb - happy shrink event
 ************************************************************************************************************/

void InitUSWAlgo(const unsigned char *ptWPos)
{
    unsigned char aucDgServ[6]={0};

    aucDgServ[0] = 0x00; /* country code by default = ucEuroCodec */
    aucDgServ[0] = ucWarnManagerWN(ucPorInitc, aucDgServ);  /* init algo of uswalgo */
    aucDgServ[0] = 0x00;
    aucDgServ[1] = 0x00;
    aucDgServ[2] = 0x00;  /* SW_10090 */
    aucDgServ[0] = ucTSSMsgManagerTM(ucPorInitc,aucDgServ);  /* init output module of uswalgo */
    TimerWTinit();                /* start timer module of uswalgo */

    UpdateWarnOut (ptWPos);

    RdDAGPara();

    IniTVWarn ();	
}

static void RdDAGPara (void) // read specific DAG pressure warn and temperature warn variant coding parameters to component's lokal RAM
{
    if ( ui8GetDAGPWarnPara (&tDAG_PPara) == (uint8) 0)
        InitDefValPPara();
    if (ui8GetDAGTempWarnPara (&tDAG_TemPara ) == (uint8) 0)
        InitDefValTemPara ();
}

static void InitDefValPPara(void)
{
    tDAG_PPara.ui16_CONSTANT_DELAY = 0;
    tDAG_PPara .ui16_T_HARD = 60 * GETucT_HardOfRam();               /*ushHWDelayInSec;     CRS_1211_132_104*/
    tDAG_PPara .ui16_T_SOFT = 60 * GETucT_SoftOfRam();               /*ushECESWDelayInSec;  CRS_1211_132_104*/
    tDAG_PPara .ui8_PERCENT_HARD = GETucPercent_HardOfRam();    /*ucEcEpcFactorc;      CRS_1211_132_104*/
    tDAG_PPara .ui8_PERCENT_SOFT = GETucPercent_SoftOfRam();    /*ucSoftFactorc;       CRS_1211_132_104*/
    tDAG_PPara .ui8_P_MIN_F = GETucPcalMinVaRelativCodOfRam();      /*CRS_1211_130_268 NEU relativer Druck ALT:(uint8) (1900 / ucPResInMBarc );CRS_1211_132_104*/
    tDAG_PPara .ui8_P_MIN_R = GETucPcalMinHaRelativCodOfRam();      /*CRS_1211_130_268 NEU relativer Druck ALT: (uint8) (1900 / ucPResInMBarc );CRS_1211_132_104*/
    tDAG_PPara .ui8_P_MIN_TIRE = GETucMinWarnThresholdOfRam();    /*CRS_1211_130_268 ucPMinECE;  NEU relativer Druck ALT: (uint8) (1500 / ucPResInMBarc) =1500/25=60d*/
}
static void InitDefValTemPara(void)
{
    tDAG_TemPara .i8_T0 = GETscT0OfRam();  /*T0_inCG;  CRS_1211_132_104*/
    tDAG_TemPara .i8_T1 = GETscT1OfRam();  /*T1_inCG;  CRS_1211_132_104*/
    tDAG_TemPara .i8_T2 = GETscT2OfRam();  /*T1_inCG;  CRS_1211_132_104*/
    tDAG_TemPara .ui16_V1 = GETushV1();    /*v1_inkmh; CRS_1211_132_104*/
    tDAG_TemPara .ui16_V2 = GETushV2();    /*v2_inkmh; CRS_1211_132_104*/
    tDAG_TemPara .ui16_V3 = GETushV3();    /*v3_inkmh; CRS_1211_132_104*/
    tDAG_TemPara .ui16_HC_MAX = GETushHCmax();                   /* HeatCtMax ;CRS_1211_132_104*/
    tDAG_TemPara.ui8_TempWarnEnable = GETucTempWarnOnOffOfRam(); /*1;  enabled CRS_1211_132_104*/
}

// TODO: remove this when function is available
static uint8 ui8GetDAGTempWarnPara(TempWarnParaType * ptTemPara)
{
    return 0;
}
static uint8 ui8GetDAGPWarnPara(PWarnParaType * ptPPara)
{
    return 0;
}

void KL15OffWarnInit(const unsigned char *ptWPos)
{
  USWPostInit();

  // LogicDokument V1.9b chapter 6.7.1 ucRet = ucTSSMsgManagerTM(ucPorInitc,&ucRet);  /* init output module of uswalgo */

  UpdateWarnOut (ptWPos );

  IniTVWarnAtKL15Off(); // OIL #1015

  UpdateGlobWrnLvlNWarnDisp();
}


uint8 ui8GetPMIN_F(void)
{
  return (tDAG_PPara .ui8_P_MIN_F );
}

uint8 ui8GetPMIN_R(void)
{
  return (tDAG_PPara .ui8_P_MIN_R );
}


// UpdateWarnOut purpose:
//  loads current warnvectors from uswalgo to tssmsg 
//  updates all output signals
void UpdateWarnOut(const unsigned char * p2WPs)
{
  unsigned char aucDgServ[6]={0};
  unsigned char i;

  aucDgServ[1] = ucGetWarnVectorsc;   /* get warnvectors from WAlgo */
  aucDgServ[0] = (unsigned char) ucWarnManagerWN(ucDiagServicec, &aucDgServ[1]);

  aucDgServ[0] = ucPutWarnVectorSetc; /* load warnvectors to output */
  aucDgServ[0] = ucTSSMsgManagerTM(ucDiagServicec,aucDgServ);

  aucDgServ[0] = ucNewPositionsc;     /* load wheel positions into output modul actualize output */
  aucDgServ[1] = *p2WPs;
  for (i = 0; i < (ucSumWEc-1); i++)  /* no spare tyre supported anymore => -1*/
  {
    aucDgServ[2+i] = p2WPs[1+i];
  }
  aucDgServ[0] = ucTSSMsgManagerTM(ucDiagServicec,aucDgServ);
}

