/*
*(c) Beru Electronics GmbH     BEE1     11/2002
*================================================================================================
*
* $Archive: /LIB/USWarn/versions/light/USWarn.c $
*
* file status:   under construction
*
*------------------------------------------------------------------------------------------------
*
*author:        Peter Brand                Beru Electronics GmbH
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
* changes in 2002
* 21.11.2002 pb - 1st established
*
* changes in 2003 :
* $Log: /LIB/USWarn/versions/light/USWarn.c $
 * 
 * 82    29.07.11 13:41 Peter
 * fix:
 * 
 * 81    29.07.11 13:28 Peter
 * fix: write Pwarm to EEPROM
 * 
 * 80    29.07.11 10:21 Peter
 * oarameters for adjusting soft and hard warning output moved from TSSMsg
 * to wntypepar.h
 * 
 * 79    28.07.11 11:53 Peter
 * Pwarm (ECExxx) Implementierung
 * 
 * 78    26.07.11 11:32 Peter
 * USWarn diag service ucGetPTSollc reimplemented
 * 
 * 77    4.01.10 16:58 Peter
 * test outut optimized for BMW use
 * 
 * 76    4.01.10 10:42 Peter
 * new diag service ucGetWarnTypec
 * 
 * 75    16.03.09 11:28 Dederer
 * const ucMaxWarnTypeWNc removed (define in WnTypePar.h)
 *
 * 74    9.10.08 18:23 Peter
 * adatpted to 4 IDs and 4 wheel positions
 *
 * 73    14.04.08 11:59 Peter
 * only module test functions enhanced
 *
 * 72    14.03.08 9:53 Rapp
 * Neu_bmw311::pl6:CR_000030
 *
 * 71    2.07.07 10:04 Peter
 * refactoring USWarn
 *
 * 70    2.04.07 16:01 Peter
 * clear freakfilter not only if the warnbits are set active but also when
 * the warningtyp condition does not last any longer (reset of a warning)
 *
 * 69    12.01.07 15:55 Peter
 * freak activity testcase revised
 *
 * 68    12.01.07 15:38 Peter
 * service of uswalgo supports external information of freak activity
 *
 * 67    12.01.07 11:19 Peter
 * freakfilter array for the warningtypes
 * freakfilter in setwarnbit
 * bugfix in clearwarntypebit
 *
 * 66    19.10.06 11:29 Peter
 * full version's bugfix at isochore calculation (1/2006) added
 *
 * 65    14.07.06 13:22 Peter
 * exclude every OS dependency
 *
 * 64    14.07.06 9:56 Peter
 * FT warntype replaces dPVT warntype
 *
 * 63    11.11.05 8:17 Peter
 * bugfix dPVT
 *
 * 62    9.11.05 9:11 Peter
 * light version with low resource usage based on V2.3
 *
 * 60    25.10.05 14:17 Peter
 * Warntype TSK ( < SW_40320 VAG311 >) and VW negative reset hysteresis (
 * < SW_40350 VAG311 >) integrated
 *
 * 59    4.08.05 11:58 Peter
 * check rated minimum values versus hard coded absolute rated minimum
 * values NOT ANYMORE versus hard coded absolute PMin !
 *
 * 58    2.08.05 15:30 Peter
 * service for reading temperature compensated FILL pressure according to
 * the service for reading out rated pressure
 *
 * 57    25.07.05 16:57 Peter
 * detect no freakfilter activities of hollow softwarnings
 *
 * 56    6.07.05 18:40 Peter
 * CheckFreakFilterActivity increased to Activity caused by FillPressure
 * based warning types
 * inclusive corresponding unittest function
 *
 * 55    6.04.05 13:31 Peter
 * schedule call reduces runtime of warntype initialization (important for
 * target)
 *
 * 54    2.03.05 16:07 Peter
 * fill pressure based warning types added
 *
 * 53    18.01.05 11:27 Peter
 * pfactor warning gets now calculated with absolute pressure value at all
 * codings (US and RDW) because of buggy behavior at pressure values below
 * 0 (relative)
 *
 * 52    30.12.04 10:57 Peter
 * supplementary display warning type implemented SW_90 .. SW_150 bmw
 *
 * 51    3.12.04 11:02 Peter
 * extra charge on warnlevels of non isochorerated warning types, namely
 * PMin and PFactor.
 * For BMW adaptions.
 *
 * 50    9.09.04 15:26 Peter
 * warntype constant declaration remvod to uswarnx as ordinary defines
 *
 * 49    19.08.04 14:35 Peter
 * MISRA conformance enhanced and uswarn reconfigured for better metrics
 *
 * 47    14.07.04 16:52 Peter
 * documentation update
 *
 * 46    28.06.04 14:58 Peter
 * Sicherung 1ter Stand mit abgeschlossenen Modultests TC_10000-TC10050
 *
 * 45    21.06.04 15:09 Peter
 * Backup
 *
 * 44    20.02.04 16:12 Peter
 * Diagnosedienst zum Auslesen von PSoll/Tsoll ergänzt
*
* 43    8.12.03 17:16 Peter
* Ausgaben für Modultest geändert
*
* 42    2.12.03 13:47 Peter
* Sichern der Warnbits nur bei Warnbitmodifikation
* (Clear/SetWarnBit..)nicht generell bei allen Bit-Modifikationen
* (Set/ClearX8Bit..)
*
* 41    2.12.03 11:13 Peter
* Bugfix in Dienst zur Information über FreakFilterAkivität
*
* 40    11.11.03 10:55 Peter
* Anpassung an MISRA Subset gem. HIS V1.0
*
* 39    15.10.03 17:56 Peter
* Unterstützung des neuen DiagService ucGetHWFreakBitsc zum Feststellen
* der WarnFilteraktivität für HWs
* Bugfix beim Initialisieren der Filterwerte für PFactor
*
* 38    9.10.03 17:14 Peter
* Reset Funktion für den Modultest eingeführt
* Bei Initialisiertem System werden Warnungen nicht mehr autom gelöscht
* sondern nur die Filter nachgeladen
*
* 37    30.09.03 16:15 Peter
* Änderungen aus released ( Löschen der Warnbits bei
* Mindestsolldruckvorgabe wird nicht mehr durchgeführt)
*
* 33    29.09.03 17:53 Peter
* keine Löschung der Warnbits nach mindestsolldruckvorgabe (erst bei
* erneutem Empfang)
*
* 32    11.09.03 15:33 Peter
* Version 1.1 aus Work
* -Änderung aus Sommererprobung Nardo03 nach Protokoll v.23.08.
* v.Hr.Kessler und Ergänzungen aus d. mail v. 26.08. v. Hr.Brand.
* -Parametrierfunktion wurde allgemeingültig ausgeführt mit Zeiger auf
* Konstantenfeld in der BR
*
* 36    5.09.03 10:06 Peter
* MISRA-Konformitätsanpassungen
* Diagnosedienst ucGetPSollAtTempc zum Solldrucklesen auf
* temperaturunabhängiges lesen erweitert
* Xtra-Loard Parameter werden bei gesetztem Bit Xtra-Loard grundsätzlich
* immer gschriebn
*
* 35    3.09.03 14:36 Peter
* Schwelle für HTV-Warntyp vom 500mBar auf 400mBar geändert
*
* 34    2.09.03 15:22 Peter
* defines zum Ansprechen der einzelnen Warnbits i.d.WarnVectoren in
* Konstanten überführt
*
* 33    1.09.03 17:06 Peter
* Testfunktion an neue Warngrenze Tankstop angepasst
*
* 32    28.08.03 12:12 Peter
* neuer Warntyp Tankstop implementiert aber noch nicht getestet
*
* 30    27.08.03 10:34 Peter
* Für den Modultest werden div. Funktionen nicht statisch sondern auch
* als extern deklariert.
*
* 29    25.08.03 13:54 Peter
* das isochoren bewertete Rücksetzen von Warnungen erfolgt nur noch dann,
* wenn der Istdruck >= NICHTISOCHORENBEWERTETEM  SOLLDRUCK ist !
*
* 28    1.08.03 12:00 Peter
* Maßnahmen für Misra Konformitätseinhaltung nach QAC
*
* 27    31.07.03 9:10 Peter
* Bei MindestSollDruckVorgabe wird nur noch dann PSOll dem
* MindestSollDruck angepasst wenn der aktuelle PSollWert unter dem
* MindestSollDruck liegt
*
* 26    30.07.03 15:31 Peter
* Bei gesetzem Warnbit, wird dieses in der WarnBitSetz-Routine nicht
* erneut gesetzt, wenn es gesetzt werden soll.
*
* 25    30.07.03 10:55 Peter
* Speichern der WarnBits im EEPROM wirkt sich bei Initialisierung, Setzen
* und Löschen der Bits aus
*
* 24    22.07.03 11:30 Peter
* Reset Bedingungen für weiche Warnungen angepasst
*
* 23    18.07.03 11:53 Peter
* Korrektur bei Diagnosedienst zum Solldrückeauslesen bei vorgegebener
* Temperatur
*
* 22    16.07.03 14:47 Peter
* Die Hysterese eines Warntyps ist nun nicht mehr von der Länderkodierung
* abhängig.
*
* 21    16.07.03 12:07 Peter
* Parameter XTra Loard eingeführt mit allen Konsequenzen
*
* 20    15.07.03 11:36 Peter
* Rücksetzbedingungen bei Harten Warnungen außer DHW und nicht
* aktivierter Isochorenrücksetzbewertung modifiziert (Unterscheidung: Tre
* < Ta +25 K)
*
* 19    10.07.03 13:40 Peter
* Diagnosedienste zum auslesen des MindestSollDruck(ID) und zur Ausgabe
* des Solldrucks als f(T) eingeführt
*
* 18    7.07.03 16:35 Peter
* Bei Berechnung der Isochoren mit ushMIso() werden die Parameter P=0 und
* T=0x7F herausgefiltert dh. die Isochore wird dann mit 0 zurückgegeben
*
* 17    2.07.03 18:32 Peter
* ucWarnManagerWN unterstützt jetzt den Diagnosedienst zur Berechnung
* einer Isochoren (mit Faktor 1024) ucGetIsoc
*
* 16    1.07.03 17:23 Peter
* Korrektur aus Strukturoptimierung
*
* 15    1.07.03 17:10 Peter
* Strukturoptimierung: an Warnfunktionen werden Pointer auf ein
* einheitliches Warndatenfeld übergeben
*
* 14    1.07.03 14:51 Peter
* Filter für WarnBits werden in den Bitsetz und -rücksetzfunktion
* angesprochen nicht mehr in der Warnfunktion selbst
*
* 13    1.07.03 10:18 Peter
* Konvertierung der warntypspezifischen Get/Set/Clear-Bit-Funktion in 3
* allgemeine Funktionen zum Lesen/Setzen und Löschen warn und id
* spezifoscher Warnbits
*
* 12    27.06.03 15:19 Peter
* Korrektur bei tempoeraturabhängiger weicher Warnung
*
* 11    26.06.03 17:06 Peter
* ID spezifische Reset Möglichkeit für Warninfo geschaffen
*
* 10    18.06.03 10:40 Peter
* Ausgaberoutinen für Modultest angepasst
*   Trennung aller Parameter durch ;
*   Zeilenweise Ausgabe aller Parameter und Cal-Werte
* Präzision bei Druchberechnungen auf von +1x25mBar auf +-1/2x25mBar
* geändert
*
* 9     13.06.03 15:38 Peter
* doku + bugfixes
*
* 8     11.06.03 15:27 Peter
* Rangecheck implementiert
* Schlüsselwörter aktiviert

*/
/**************************************************************************************************
* Declaration
*/
/*
* Include
*/

#include "USWarnX.h"
#include "global.h"
#include "uswarn.h"

#include "eeiface.h"
#include "USWTime.h"
#include "WnTypePar.h"
#include "DAG_TVWarn.h"
#include "uswarn_Ifx.h"
#include "WallocX.h"

#ifndef pb_ModulTest_02062003

#else
#include <stdio.h>
#endif
/**************************************************************************************************
*Prototypes
*/
static unsigned char bGetX8BitWM(const unsigned char *, unsigned char);
static void ClearX8BitWM(unsigned char *, unsigned char );
static void SetX8BitWM(unsigned char *, unsigned char );

static void InitWN(unsigned char ucInit, unsigned char ucIdX  );

static unsigned char ucUSWDiagService( unsigned char *ptData);
static unsigned char ucGenWNVector(const unsigned char *ptData);

static void ConvDAG_FPL2HW(void);

static uint8 ui8GenAllPWP(uint8 * p2PWP);
static uint8 ui8GetWrnLvlDHW(void);
static uint8 ui8GetWrnLvlSoft(void);
static uint8 ui8GetWrnLvlHard(void);
static uint8 ui8GetWrnLvlPMin(void);
static uint8 ui8GetResetLvlSoft(void);

/**************************************************************************************************
*Data
*/
const unsigned char ucBitNoc[ucSumWEc] =
{
  1, 2, 4, 8	//, 16
};

/*************************************************************
WarnManager
*/


/* ucWarnStateWN constants */
#define cMaiden 0x00
#define cInitialized  0x01
#define cInitSingleId 0x03
/* 0x02 reserved */
/* 0x03 reserved */


/******************************************
******
* warnbits - filters and corresponding constants
*/

static unsigned char aucWarnBitsWN[5];           /* warntype/bit array ( SW_10060 SW_140 )  ( SW_900110 C6 LL db )*/


/************************************************
* structure of warning data
*/



/**********************************************************************************/
/* TEST DATA */


struct Cmp
{
 	unsigned char ucPMin;
	unsigned char ucDAGHard;
  unsigned char ucDAGSoft;
  unsigned char ucDAGDHW;
  unsigned char ucDAGResetSoft;
};

static union U
{
	struct Cmp tWrnLvl;
	unsigned char ucByte[(unsigned char) sizeof(struct Cmp)];
} tU;


#define cNoWrnLvl (uint8) 0xFF
static uint8 ui8DAGWrnLvl[4][5] ={{cNoWrnLvl,cNoWrnLvl,cNoWrnLvl,cNoWrnLvl,cNoWrnLvl},{cNoWrnLvl,cNoWrnLvl,cNoWrnLvl,cNoWrnLvl,cNoWrnLvl},{cNoWrnLvl,cNoWrnLvl,cNoWrnLvl,cNoWrnLvl,cNoWrnLvl},{cNoWrnLvl,cNoWrnLvl,cNoWrnLvl,cNoWrnLvl,cNoWrnLvl}}; // [0..3][PMin,FPL,HW,SW,ResetSW]
static void UpdateDAGWrnLvl(uint8 uiColOfId);

/**************************************************************************************************
 * Implementation
 */

/**************************************************************************************************
 *functions
 */
/**************************************************************************************************
 * private
 */



 /************************************************************************************************************
 ** function:   SetWarnBitWN()
 **
 ** ---------------------------------------------------------------------------------------------------------
 **
 ** purpose: set a single warnbit in the warn bit array indexed by id and warning type
 ** ---------------------------------------------------------------------------------------------------------
 **
 ** input: ucIdX = index of id [0,1,...,ucSumWEc-1]
 **        ucWarnTypeIx = ushPMinc...ucSoftc
 **
 ** input (global):
 **
 ** output (global):
 **
 ** output:
 **
 ************************************************************************************************************/


unsigned char ucSetWarnBitWN(unsigned char ucIdX, unsigned char ucWarnTypeIx)
{
  if ((ucWarnTypeIx < ucMaxWarnTypeWNc) && (ucIdX < ucSumWEc))
  {
    if  (ucWarnTypeIx == ucSFactorIxc)
    { 
      (void) ucStartFilterSTWT( tDAG_PPara .ui16_T_SOFT  );
    }
    else if (ucWarnTypeIx == ucEcEIxc)
    { 
      (void) ucStartFilterHDWT(  tDAG_PPara.ui16_T_HARD );
    }

    if (bGetX8BitWM(&aucWarnBitsWN[ucWarnTypeIx], ucIdX) == 0)
    {
      SetX8BitWM(&aucWarnBitsWN[ucWarnTypeIx], ucIdX);
      PutDataEE(ucWarnTypeArrayIdWNc, aucWarnBitsWN, ucMaxWarnTypeWNc);
    }
    return((unsigned char) 1);
  }
  else
  {
    return((unsigned char) 0xff);
  }
}


/************************************************************************************************************
 ** function:   ClearWarnBitWN()
 **
 ** ---------------------------------------------------------------------------------------------------------
 **
 ** purpose: clear a single warnbit in the warn bit array indexed by id and warning type
 ** ---------------------------------------------------------------------------------------------------------
 **
 ** input: ucIdX = index of id [0,1,...,ucSumWEc-1]
 **        ucWarnTypeIx = ushPMinc...ucSoftc
 **
 ** input (global):
 **
 ** output (global):
 **
 ** output:
 **
 ************************************************************************************************************/

/************************************************************************************************************
 ** changes in 2003
 **
 ** 01.07.2003 pb - established
 ** 27.08.2003 pb - reset new filter of tankstop (ucTSIxc)
 ** 02.04.2007 pb - reset also frikbits < SW_30530 bmw pl6 db >
 ************************************************************************************************************/

void ClearWarnBitWN(unsigned char ucIdX, unsigned char ucWarnTypeIx)
{
  if ((ucWarnTypeIx < ucMaxWarnTypeWNc) && (ucIdX < ucSumWEc))
  {
    ClearX8BitWM(&aucWarnBitsWN[ucWarnTypeIx], ucIdX);

    if ((ucSFactorIxc == ucWarnTypeIx) && ((uint8) 0 == aucWarnBitsWN[ucSFactorIxc]))
      StopFilterSTWT ();
    else if ((ucEcEIxc == ucWarnTypeIx) && ((uint8) 0 == aucWarnBitsWN[ucEcEIxc]))
      StopFilterHDWT ();

    PutDataEE(ucWarnTypeArrayIdWNc, aucWarnBitsWN, ucMaxWarnTypeWNc);
  }
  return;
}



/************************************************************************************************************
 ** function:   GetWarnBitWN()
 **
 ** ---------------------------------------------------------------------------------------------------------
 **
 ** purpose: read a single warnbit in the warn bit array indexed by id(=bit index) and warning type (=array index)
 ** ---------------------------------------------------------------------------------------------------------
 **
 ** input: ucIdX = index of id [0,1,...,ucSumWEc-1]
 **        ucWarnTypeIx = ushPMinc...ucSoftc
 **
 ** input (global):
 **
 ** output (global):
 **
 ** output:
 **
 ************************************************************************************************************/

/************************************************************************************************************
 ** changes in 2003
 **
 ** 01.07.2003 pb - established
 ************************************************************************************************************/

unsigned char  ucGetWarnBitWN(unsigned char ucIdX, unsigned char ucWarnTypeIx)
{
  if ((ucWarnTypeIx < ucMaxWarnTypeWNc) && (ucIdX < ucSumWEc))
  {
    return(bGetX8BitWM(&aucWarnBitsWN[ucWarnTypeIx], ucIdX));
  }
  else
  {
    return((unsigned char) 0xff);   /* ERROR */
  }
}

unsigned char ucGetWarnType(unsigned char ucWarnTypeIx)     // returns complete warntype 
{
  if ((ucWarnTypeIx < ucMaxWarnTypeWNc) )
  {
    return(aucWarnBitsWN[ucWarnTypeIx]);
  }
  else
  {
    return((unsigned char) 0);   /* ERROR */
  }
}


/*
general 8bit handling
*/
/*
Description
*/
/*
Purpose:                       generation of pmin concerning the us warningalgorithem spec
-----------------------------------------------------------------------------------------------
Input:                         ucP

Output:                        1 warning type = active
                               0 warning type = inactive
------------------------------------------------------------------------------------------------
*/
/*
revision history
*/
/*
changes in 2002
*/
/*
21.11.2002 pb - 1st established
*/
static unsigned char bGetX8BitWM(const unsigned char *ptByte, unsigned char ucBitNo)
{
  if ((*ptByte & ucBitNoc[ucBitNo]) == ucBitNoc[ucBitNo])
  {
    return(1);
  }
  else
  {
    return(0);
  }
}
/*
Description
*/
/*
Purpose:                       generation of pmin concerning the us warningalgorithem spec
-----------------------------------------------------------------------------------------------Input:                         ucP

Output:                        1 warning type = active
                               0 warning type = inactive
------------------------------------------------------------------------------------------------
*/
/*
revision history
*/
/*
changes in 2002
*/
/*
21.11.2002 pb - 1st established
01.07.2003 pb - 1st review results put into action
30.07.2003 pb - safe warnbits in eeprom after modification
02.12.2003 pb - safe warnbits in eeprom after modification removed to clearwarnbit-function
*/
static void ClearX8BitWM(unsigned char *ptByte, unsigned char ucBitNo)
{
  if ((*ptByte & ucBitNoc[ucBitNo]) > 0)
  {
    *ptByte &= (unsigned char) ~ucBitNoc[ucBitNo];
  }
}
/*
Description
*/
/*
Purpose:                       generation of pmin concerning the us warningalgorithem spec
-----------------------------------------------------------------------------------------------
Input:                         ucP

Output:                        1 warning type = active
                               0 warning type = inactive
------------------------------------------------------------------------------------------------
*/
/*
revision history
*/
/*
changes in 2002
*/
/*
21.11.2002 pb - 1st established
01.07.2003 pb - 1st review results put into action
30.07.2003 pb - safe warnbits in eeprom after modification
01.08.2003 pb - misra conformance
30.07.2003 pb - safe warnbits in eeprom after modification removed to setwarnbit function

*/
static void SetX8BitWM(unsigned char *ptByte, unsigned char ucBitNo)
{
  if ( (*ptByte & ucBitNoc[ucBitNo]) == 0)
  {
    *ptByte |= ucBitNoc[ucBitNo];
  }
}



/*****************************************************************************
ucPfT

Function ucPfT(..)

Description

Purpose:                       generates a temperature independet relative pressure value
-----------------------------------------------------------------------------------------------
Input:                         m accessory to pressure value an overhanded temperature

Output:                        relative pressure value at desired temperature [ushTabs] = K

*/
unsigned char ucPfT(unsigned short ushM, unsigned short ushTabs)
{
  unsigned long ulHelp;
  unsigned short ushHelp;

  ulHelp = (unsigned long)   ushM * 10;
  ulHelp *=  ushTabs;
  ulHelp /= ushGSFc;
  ulHelp += 5;
  ushHelp = (unsigned short) (ulHelp / 10);
  
  ushHelp = (ushHelp > Getui8AtmosphericP()) ? (ushHelp - Getui8AtmosphericP()):ushHelp;
  
  if (ushHelp > 0x00FF) /*(BMW_EcE: CR_3478.050.0353)*/
  {
    ushHelp = 0x00FF;
  }
  
  return((unsigned char) ushHelp);
}
/*****************************************************************************
ushMIso

Function ushMIso(..)

Description

Purpose:                       generates a temperature independet pressure value
-----------------------------------------------------------------------------------------------
Input:                         m accessory to pressure value an overhanded temperature

Output:                        pressure value at 20 degree centigrade

revision history

changes in 2003

23.01.2003 pb - 1st established
17.06.2003 pb - precision changed from + 1 LSB to +-1/2 LSB as follows:
                ((dividend * 10 / divisor) + 5) / 10 = round(int result)
07.07.2003 pb - range check ucP and scT
25.01.2006 pb - range check reduced to ucP
*/

unsigned short ushMIso(unsigned char ucP, signed char scT)
{
  unsigned long ulHelp;
  unsigned short ushHelp;
  if (ucP == 0)
  {
    ushHelp = 0;
  }
  else
  {
    ulHelp = (unsigned long) ushGSFc *10;
    ulHelp *=  ucP;
    ushHelp = (unsigned short) scT + ush273Kelvinc;
    ulHelp = ulHelp / ((unsigned long) ushHelp);
    ulHelp += 5;
    ushHelp = (unsigned short) (ulHelp/10);
  }
  return( ushHelp );
}

// ui16MIsoRel purpose:
// returns quotient of Pabs/T 
// parameter [ui8Prel] = relative pressure in 25mBar range 0..fe 
// parameter [scT] = -50..127 °C
uint16 ui16MIsoRel(unsigned char ucPrel, signed char scT)
{
  unsigned long ulHelp;
  unsigned short ushHelp;
  uint16 pAbs = ucPrel + Getui8AtmosphericP ();

  if (0 == pAbs )
  {
    ushHelp = 0;
  }
  else
  {
    ulHelp = (unsigned long) ushGSFc *10;
    ulHelp *=  pAbs ;
    ushHelp = (unsigned short) scT + ush273Kelvinc;
    ulHelp = ulHelp / ((unsigned long) ushHelp);
    ulHelp += 5;
    ushHelp = (unsigned short) (ulHelp/10);
  }
  return( ushHelp );
}

/***************************************************************************************************
*Function InitWN(..)
*
*Description
*Purpose:
*support different initialization modes:
* 1. complete initialization of module global variables with const. default values (all ids)
*     all warnings get cleared
* 2. initialize initialized module means only reload filter variables (all ids)
* 3. initialize single id with default values and clear warnings of this id
* 4. deactivate filter means setting freakfilter to 1
*-----------------------------------------------------------------------------------------------
*input:
* ucInit: type of initialization (cMaiden,cInitialized,cInitSingleId,cDeactivateFilter)
* ucIdX: 0,1,2,...,ucSumWEc (id to initialize, ucSumWEc means all ids)
*
*output:
* indirect: global variables
*------------------------------------------------------------------------------------------------
*
*revision history
*
*changes in 2002
*
*21.11.2002 pb - 1st established
*06.06.2003 pb - cDeactivateFilter-case (unsigned short) added
*08.10.2003 pb - reload only filters if system is in initialized state (do not clear warnings
*                 further)
*05.08.2004 pb - refactoring (reduce interface width of config function set)
*28.12.2004 pb - include new configuration function ConfigSD
*27.10.2005 pb - happy shrink event
****************************************************************************************************/
static void InitWN(unsigned char ucInit, unsigned char ucIdX  )
{
  unsigned char i,j;

  switch (ucInit)
  {
  case (unsigned short) cMaiden:
    {
      /* very 1st initialization - no eeprom data exists yet */
      for ( i = 0; i < ucMaxWarnTypeWNc; i++)
      {
        for (j=0;j<ucSumWEc;j++)
        {
          ClearWarnBitWN(j, i);

          if (i == ucDHWIxc)
          {
            ResetM1Pressure(j);
          }
        }
      }
    }
    break;
  case (unsigned short) cInitialized:
    {
    }
    break;
  case (unsigned short) cInitSingleId:
    {
      if (ucIdX <= ucSumWEc)
      {
        if (ucIdX == ucSumWEc)
        {
          for ( i = 0; i < ucMaxWarnTypeWNc; i++)
          {
            for (j=0;j<ucSumWEc;j++)
            {
              ClearWarnBitWN(j, i);

              if (i == ucDHWIxc)
              {
                ResetM1Pressure(j);
              }
            }
          }
        }
        else
        {
          for ( i = 0; i < ucMaxWarnTypeWNc ; i++)
          {
            ClearWarnBitWN(ucIdX, i);

            if (i == ucDHWIxc)
            {
              ResetM1Pressure(ucIdX);
            }
          }
        }
      }
      else
      {
        /* ERROR bad index */
      }
    }
    break;
  default:
    break;
  }

}


/***************************************************************************************************
 *Function ucUSWDiagService(..)
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
 *    ptData = pointer to datafield (unsigned char) to be processed as well as returned
 *
 *  output: 0       well done everything
 *          0xffff  everything went wrong (again)
 *
 * 01.03.2005 pb - service for loading fill pressure and temperature
 */

static unsigned char ucUSWDiagService( unsigned char *ptData)
{
  unsigned char i,k,ucRet;

  ucRet = 0;
  switch (*ptData)
  {
  case (unsigned short) ucResetWarnVectorc:
    {
      ptData++;   /* set pointer to index */
      InitWN(cInitSingleId, *ptData);
      ucRet = 0;
    }
    break;
  case (unsigned short) ucGetWarnVectorsc:
    { /* SW_10070 */
      for (k = 0; k < ucSumWEc; k++)
      {
        ptData[k] = 0;
        for (i = 0; i < ucMaxWarnTypeWNc; i++)
        {
          ptData[k] |= (unsigned char) (ucGetWarnBitWN(k,i) << i);
        }
      }
      ucRet = 0;
    }
    break;
  case (unsigned short) ucGetWarnTypec:
    { /* << SW_410037 PL7 DB >> */
      ptData[2] = aucWarnBitsWN[ptData[1]];
      ucRet = 0;
    }
    break;
  default:
    break;
  }
  return (ucRet);
}

static unsigned char ucGenWNVector(const unsigned char *ptData)
{
    unsigned char (*const fpt2WnType[]) (struct LocalWarnDat *, unsigned char) = cAllWT_function;

    struct LocalWarnDat tLWD;
    unsigned char i, ucRet = 0;

    tLWD.tHFD.tHF.ucId = 0; /* default for MISRA */
    tLWD.ucCurWarnLevel = cNoWrnLvl ;
    tLWD.ucResetLvl = cNoWrnLvl ;
    for (i=0;i<(unsigned char) sizeof(struct HFTelIntern);i++)	/* copy hfdata */
    {
        tLWD.tHFD.ucByte[i] = *ptData;
        ptData++;
    }

    if (tLWD.tHFD.tHF.ucId < ucSumWEc)
    {
        PuT(tLWD.tHFD .tHF .ucId , tLWD.tHFD .tHF .scTWE ); // refer to : DAG's 7 Temperature Warning
        
        GetRatValOfId(tLWD.tHFD.tHF.ucId, (struct SollDat *) &tLWD.tSD);
        tLWD.PRefMin = Getui8PrefMinOfId (tLWD.tHFD.tHF.ucId);
   
        for (i = 0; i < ucMaxWarnTypeWNc;i++)
        {
            if ( fpt2WnType[i](&tLWD,(uint8) 0) > 0)  /* do all warning types  SW_10080 */
            {
                ucRet |= (unsigned char) (0x01<<i);
            }
            else
            {
                ucRet &= (unsigned char) ~(0x01<<i);
            }

            tU.ucByte[i] = tLWD.ucCurWarnLevel;	/* ucCurWarnLevel is return value from fct call above */

            if ( bSoftFactor == fpt2WnType[i] )
              tU.tWrnLvl .ucDAGResetSoft = tLWD.ucResetLvl ;
        }

        UpdateDAGWrnLvl(tLWD.tHFD.tHF.ucId);
    }
    return (ucRet);
}

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
*  MSB   X X X X  X X X X  LSB according to ucId (s.a.)
*        | | | |  | | | |_	PMin Warning
*        | | | |  | | |___	PFactor
*        | | | |  | |_____	DHW
*        | | | |  |_______	FT
*        | | | |__________	HardT
*        | | |____________  HardVT
*        | |______________	SoftT
*        |________________  TS (tankstop)
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
 *  ptData: to
 *1st		ucCfgSTc (diagservice to configure softwarning ST)
 *		scTmax in centigrade (0 means def)
 *		ucThres / ucPResInMBarc (0 means def)
 *		Hysteresis to PSoll / ucPResInMBarc (0 means def)
 *		filter reload value in counts (0 means def)
 *return =  write with succes -> ucWarnStateWN
 *		  ERROR -> 0
 *
 *ptData: to
 *1st		ucCfgFTc (diagservice to configure dPVT spec chapt. 3.1.4)
 *		filter reload value in counts (0 means def)
 *		ucSpeedMax / km/h (0 means def)
 *		Hysteresis to PSoll / ucPResInMBarc (0 means def)
 *		ucThres / ucPResInMBarc (0 means def)
 *		ucMaxThres / ucPResInMBarc (0 means def = 200mbar def.)
 *return =  write with succes -> ucWarnStateWN
 *		  ERROR -> 0
 *
 *ptData: to
 *1st		ucCfgPFactorc (diagservice PFactor)
 *		filter reload value in counts (0 means def)
 *		Hysteresis to PSoll / ucPResInMBarc (0 means def)
 *		ucfactor / % (0 means def)
 *return =  write with succes -> ucWarnStateWN
 *		  ERROR -> 0
 *
 *ptData: to
 *1st		ucCfgHTc (diagservice HT )
 *		scDrop in centigrade (0 means def)
 *		ucMDropLowByte
 *		ucMDropHighByte	(0 means def)
 *		ucThres / ucPResInMBarc (0 means def)
 *		Hysteresis to PSoll / ucPResInMBarc (0 means def)
 *		ucThres / ucPResInMBarc (0 means def)
 *last	filter reload value in counts (0 means def)
 *return =  write with succes -> ucWarnStateWN
 *		  ERROR -> 0
 *
 *ptData: to
 *1st		ucCfgHTVc (diagservice HTV )
 *		scDrop in centigrade (0 means def)
 *		ucMDropLowByte
 *		ucMDropHighByte	(0 means def)
 *		ucThres / ucPResInMBarc (0 means def)
 *		Hysteresis to PSoll / ucPResInMBarc (0 means def)
 *		ucSpeedMax / km/h for HVT (0 means def)
 *		ucThres / ucPResInMBarc (0 means def)
 *last	filter reload value in counts (0 means def)
 *return =  write with succes -> ucWarnStateWN
 *		  ERROR -> 0
 *
 *ptData: to
 *1st		ucCfgDHWc (diagservice dhw)
 *		ucThres / ucPResInMBarc (minimum difference pM1-pM2) (0 means def)
 *last	filter reload value in counts (0 means def)
 *return =  write with succes -> ucWarnStateWN
 *		  ERROR -> 0
 *
 *ptData: to
 *1st		ucCfgTSc (diagservice to configure tankstopwarning TS)
 *		filter reload value in counts (0 means def)
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
 *1st     ucGetIsoc (calculate qutient of P * / T)
 *        P
 *last    T
 *return = 0x00 (iO)
 *         0xFF  (ERROR)
 *         indirect : *ptData IsochoreLow
 *                    ptData[1] IsochoreHigh
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
 *            ptData + 1 = &WarnVector of id 1
 *            ptData + 2 = &WarnVector of id 2
 *            ptData + 3 = &WarnVector of id 3
 *            ptData + 4 = &WarnVector of id 4
 *
 *ptData: to
 *1st     ucGetPTSollc (return absolute  rated pressure & temperature value)
 *last    Id (0,1,..(ucSumWEc-1))
 *return: 0 (i.O) v 0xff (bad ID)
 *        *ptData:   Psoll
 *        *ptData+1: Tsoll
 *
 *ptData: to
 *1st     ucGetPwarmc (return absolute  rated pressure & temperature value)
 *last    Id (0,1,..(ucSumWEc-1))
 *return: 0 (i.O) v 0xff (bad ID)
 *        *ptData:   Pwarm
 *
 *ptData: to
 *1st     PutPwarm (set absolute rated pressure 4 Pwarm warning type)
 *2nd     Pwarn (abs. pressure value)
 *last    Id (0,1,..(ucSumWEc-1))
 *return: 0 (i.O) v 0xff (bad ID)
 *       
 *****************************************************************************************************/

unsigned char ucWarnManagerWN(unsigned char ucAction, unsigned char *ptData)
{
  unsigned char ucRet;

  switch( ucAction )
  {
  case (unsigned short) ucPorInitc:
    {
      InitWN((unsigned char) cInitialized, (unsigned char) 0xFF);
      GetDataEE(ucWarnTypeArrayIdWNc, aucWarnBitsWN, ucMaxWarnTypeWNc);
      ConvDAG_FPL2HW ();
      ucRet = (unsigned char) 0;
    }
    break;
  case (unsigned short) ucComparec :
    /*execute all warning functions - save results to warnbitfields - generate warn output */
    ucRet = ucGenWNVector(ptData);
    break;
  case (unsigned short) ucDiagServicec:
    /* execute diverse diagnosis services */
    ucRet = ucUSWDiagService(ptData);
    break;
  default:
    ucRet = 0xFF;   /* error bad function parameter */
    break;
  }
  return(ucRet);
}

 static uint8 ui8GetWrnLvlDHW(void)   // returns warning level of fast pressure loss warning, values are updated after each reception
 {
     return tU.tWrnLvl .ucDAGDHW ;
 }
 static uint8 ui8GetWrnLvlSoft(void)   // returns warning level of soft warning, values are updated after each reception
 {
     return tU.tWrnLvl .ucDAGSoft  ;
 }
 static uint8 ui8GetWrnLvlHard(void)   // returns warning level of hard warning, values are updated after each reception
 {
     return tU.tWrnLvl .ucDAGHard  ;
 }
 static uint8 ui8GetWrnLvlPMin(void)   // returns warning level of PMin warning, values are updated after each reception
 {
     return tU.tWrnLvl .ucPMin ;
 }
 static uint8 ui8GetResetLvlSoft(void)   // returns reset level of DAG's soft warning, values are updated after each reception
 {
     return tU.tWrnLvl .ucDAGResetSoft ;
 }
 static void ConvDAG_FPL2HW(void)  // converts any DHW to a Hardwarning and resets DHW, see: TPMS Logic  PAL2 V1.3 - 6.5 Wheel Status - Ignition OFF  --> HARD_WARNING
 {
   uint8 i;
   aucWarnBitsWN [ucEcEIxc] |= aucWarnBitsWN [ucDHWIxc];  // convert
   aucWarnBitsWN [ucPMinIxc] |= aucWarnBitsWN [ucDHWIxc]; 
   
   for ( i = (uint8) 0; i < 4; i++) // reset reference point at active DHWs/FPLs 
   {
     if ((aucWarnBitsWN[ucDHWIxc] & ((uint8) (1<<i))) > (uint8) 0)
     {
       ResetM1Pressure (i);
     }
   }
   
   aucWarnBitsWN [ucDHWIxc] = 0;  // finally reset FPL itself
 }


 uint8 ui8GetPRelComp2Tref(sint8 i8Tcur, uint8 ui8Ix) // returns relative reated pressure value compensated to Tcur[-127..127°C] for HistCol ui8Ix[0..3]
 {
    uint8 ui8Pcomp;
    struct SollDat tRatVal;

    GetRatValOfId (ui8Ix, &tRatVal);

    tRatVal.ushMSoll  = ui16MIsoRel (tRatVal.ucPSoll , tRatVal.scTSoll);
    ui8Pcomp = ucPfT(tRatVal.ushMSoll,(uint16) i8Tcur + ush273Kelvinc);

    return (ui8Pcomp);
 }

 sint8 i8GetTref(uint8 ui8Ix) // returns rated temperature 
 {
   struct SollDat tRatVal;

   GetRatValOfId (ui8Ix, &tRatVal);
   
   return( tRatVal .scTSoll );
 }

 uint8 ui8GetPRefRel(uint8 ui8Ix) // returns relative rated pressure value at Tref
 {
   struct SollDat tRatVal;

   GetRatValOfId (ui8Ix, &tRatVal);
   
   return( tRatVal.ucPSoll );
 }


 void USWPostInit(void) // converts basic FASTPressure warnings to HardWarnings incl. SWTimer
 {
     ConvDAG_FPL2HW ();
     
     //ResetWWTimeFilters4ActiveHW();
     PutDataEE(ucWarnTypeArrayIdWNc, aucWarnBitsWN, ucMaxWarnTypeWNc);
 }

// FALL BACK PWP IMPLEMENTATION START ___________________________________________________________________________

 
 // GenPWP purpose:
 // generates 4 provisional wheel positions based on minimum rated axle pressure and writes result to p2PWP[0..3]
 // result is HistoryIndex organized
 // if historic WP is present this one is overtaken also as PWP
 // returns > 0 if succeeded
 uint8 ui8GenPWP(uint8 * p2PWP)
 {
   uint8 i, ui8PWP[4];

   if ( cMaxLR == ui8GenAllPWP (ui8PWP) ) // 4 PWPs ?
   {
     for ( i = 0; i < cMaxLR ; i++)
     {
       p2PWP[i] = ui8PWP[i];
     }
     return (1);
   }
   else
   {
     return (0);
   }
 }

  // ui8GenAllPWP purpose:
 // makes 4 provisional wheel position based on M1-pressure values. 
 // writes result (4x PWP [0,1,2,3]) to p2PWP[0,1,2,3]
 // aborts if not all 4 pressure values are present
 static uint8 ui8GenAllPWP(uint8 * p2PWP)
 {
   uint8 i,j, ui8PoSeq[4],ui8SortedCol[cMaxLR], ui8WPinUse = (uint8) 0, ui8PWPCt = (uint8) 0, ui8AlloCol = (uint8) 0;

   for ( i = 0; i < cMaxLR ; i++ )  // all pressure values are available.. ?
   {
     if ( *(pui8GetLastM1Pressure() + i) < (uint8 ) 1 )
     {
       return (0);
     }
   }

   for ( i = 0; i < cMaxLR ; i++ )
   {
     if (ucGetWPOfCol (i) < cMaxLR)  // history WP already present ?
     {
       p2PWP[i] = ucGetWPOfCol (i);
       ui8WPinUse |= ((uint8) (1<<ucGetWPOfCol (i))); // this WP[0,1,2,3] is already allocated
       ui8AlloCol |= ((uint8) (1 << i));  // this col i [0,1,2,3] is already allocated
       ui8PWPCt++;
     }
   }

   if (cMaxLR > ui8PWPCt)
   {
     SortBiggest1st (pui8GetLastM1Pressure(),ui8SortedCol,cMaxLR);

     if (ui8GetPMIN_F () <= ui8GetPMIN_R() )
     {
       ui8PoSeq[0] = (uint8) 2; // sequence comes from DAG logic doc see table at chap 4.3.7
       ui8PoSeq[1] = (uint8) 3;
       ui8PoSeq[2] = (uint8) 1;
       ui8PoSeq[3] = (uint8) 0;
     }
     else
     {
       ui8PoSeq[0] = (uint8) 0;
       ui8PoSeq[1] = (uint8) 1;
       ui8PoSeq[2] = (uint8) 3; // sequence comes from DAG logic doc see table at chap 4.3.7
       ui8PoSeq[3] = (uint8) 2;
     }

     for ( i = 0; i < cMaxLR ; i++)
     {
       if ((ui8AlloCol & ((uint8) 1<<ui8SortedCol [i])) > 0) // already allocated ?
         continue;
       else
       {
         for (j = 0; j < cMaxLR ; j++)  // find unsued WP
         {
           if ((uint8) 0 == (ui8WPinUse & (1<<ui8PoSeq[j])))
           {
             ui8WPinUse |= ((uint8) (1<<ui8PoSeq[j]));  // now this WP is in use
             ui8PWPCt++;
             p2PWP [ui8SortedCol [i]] = ui8PoSeq[j];
             break;
           }
         }
       }
     }
   }
   return (ui8PWPCt );
 }

 // FALL BACK PWP IMPLEMENTATION END___________________________________________________________________________

 // DelWarnOfId purpose:
 // deletes all warningvectors of a specific ID in history
 // updates GolbalWarnStatus, WarnDisp_Rq and output warnings (used for wheelstatus)
 // ui8HistColOfID contains history column, if > 3 all warnins will be deleted
 void DelWarnOfId(uint8 ui8HistColOfID)
 {
   uint8 i, aucDiagService[2];

   aucDiagService[0] = ucResetWarnVectorc;

   if ( ui8HistColOfID < (uint8) 4)
   {
     aucDiagService[1] = ui8HistColOfID;
     (void) ucWarnManagerWN( ucDiagServicec, aucDiagService );
   }
   else
   {
     for ( i = 0; i < 4; i++)
     {
       aucDiagService[1] = i;
       (void) ucWarnManagerWN( ucDiagServicec, aucDiagService );
     }
   }

   UpdateWarnOut ((const unsigned char*) GETpucStartAdrWPorPWP ());
 }


 // GETDAGWrnLvlOfIdCol purpose:
 // writes PMin,FPL,HW,SW-WarnLevel to p2WrnLvls[0..3] of ID w/ HistCol ui8ColOfId[0..3]
 void GETDAGWrnLvlOfIdCol(uint8 ui8ColOfId, uint8 * p2WrnLvls)
 {
   if ( cMaxLR > ui8ColOfId )
   {
     p2WrnLvls[0] = ui8DAGWrnLvl [ui8ColOfId ][0];
     p2WrnLvls[1] = ui8DAGWrnLvl [ui8ColOfId ][1];
     p2WrnLvls[2] = ui8DAGWrnLvl [ui8ColOfId ][2];
     p2WrnLvls[3] = ui8DAGWrnLvl [ui8ColOfId ][3];
   }
   else
   {
     p2WrnLvls[0] = cNoWrnLvl ;
     p2WrnLvls[1] = cNoWrnLvl ;
     p2WrnLvls[2] = cNoWrnLvl ;
     p2WrnLvls[3] = cNoWrnLvl ;
   }
 }

 static void UpdateDAGWrnLvl (uint8 ui8ColOfId)
 {
   if (cMaxLR > ui8ColOfId)
   {
      ui8DAGWrnLvl [ui8ColOfId ][0]  = ui8GetWrnLvlPMin();
      ui8DAGWrnLvl [ui8ColOfId ][1]  = ui8GetWrnLvlDHW();
      ui8DAGWrnLvl [ui8ColOfId ][2]  = ui8GetWrnLvlHard();
      ui8DAGWrnLvl [ui8ColOfId ][3]  = ui8GetWrnLvlSoft();
      ui8DAGWrnLvl [ui8ColOfId ][4]  = ui8GetResetLvlSoft ();
   }
 }

 uint8 ui8GETDAGClrWrnThresOfIdCol(uint8 ui8ColOfId)
 {
   return (ui8DAGWrnLvl [ui8ColOfId ][4]);
 }
