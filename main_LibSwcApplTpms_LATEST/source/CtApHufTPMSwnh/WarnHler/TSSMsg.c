/*
(c) Beru Electronics GmbH     BEE1     01/2003
================================================================================================

$Archive: /LIB/USWarn/versions/light/TSSMsg.c $

file name:     TSSMsg.c

file status:   under construction

------------------------------------------------------------------------------------------------

author:        Peter Brand                Beru Electronics GmbH

intials:       pb


Modul Description

Global description:
Purpose:

Modul Modification

changes in 2003
30.01.2003 pb - 1st established
$Log: /LIB/USWarn/versions/light/TSSMsg.c $
 * 
 * 41    29.07.11 10:21 Peter
 * oarameters for adjusting soft and hard warning output moved from TSSMsg
 * to wntypepar.h
 * 
 * 40    20.03.09 14:52 Peter
 * bugfix: wheel postion unspecific warnings will now be preloaded AND
 * DISPLAYED correctly after POR 
 *
 * 39    2.07.07 10:04 Peter
 * refactoring USWarn
 *
 * 38    14.08.06 17:05 Peter
 * config byte 3 condition removed
 *
 * 37    9.11.05 9:11 Peter
 * light version with low resource usage based on V2.3
 *
 * 35    25.10.05 14:16 Peter
 * HW Mask expanded for TSK Warntype < SW_40320 VAG311 >
 *
 * 34    2.03.05 16:04 Peter
 * 3 more hard warning type added to the HW mask
 *
 * 33    30.12.04 10:57 Peter
 * supplementary display warning type implemented SW_90 .. SW_150 bmw
 *
 * 32    17.12.04 17:56 Peter
 * MISRA conformance enhanced
 *
 * 31    9.09.04 10:41 Peter
 * Filter function of parabytes fixed (byte order independent now)
 *
 * 30    19.08.04 14:35 Peter
 * MISRA conformance enhanced and uswarn reconfigured for better metrics
 *
 * 28    14.07.04 16:52 Peter
 * documentation update
 *
 * 27    28.06.04 14:58 Peter
 * Sicherung 1ter Stand mit abgeschlossenen Modultests TC_10000-TC10050
 *
 * 26    21.06.04 15:09 Peter
 * Backup
 *
 * 25    5.12.03 16:13 Peter
 * Fehler aus Misrabereinigung beseitigt
 *
 * 24    1.12.03 16:54 Peter
 * Dienst ucGetWarnVectorsIdc zum Auslesen der Warnvectoren blendet jetzt
 * die Filter für "Reaktion nach Panne" bewußt aus
 *
 * 23    11.11.03 10:55 Peter
 * Anpassung an MISRA Subset gem. HIS V1.0
 *
 * 22    9.10.03 17:14 Peter
 * Reset Funktion für den Modultest eingeführt
 *
 * 21    1.10.03 18:08 Peter
 * Beim Runterladen neuer Radpositionen wird bei Übergabe unbekannter
 * Radpositionen jetzt ushWarnOutTM neu gebildet (positionsunspezifische
 * Warnung)
 *
 * 18    11.09.03 15:33 Peter
 * Version 1.1 aus Work
 * -Änderung aus Sommererprobung Nardo03 nach Protokoll v.23.08.
 * v.Hr.Kessler und Ergänzungen aus d. mail v. 26.08. v. Hr.Brand.
 * -Parametrierfunktion wurde allgemeingültig ausgeführt mit Zeiger auf
 * Konstantenfeld in der BR
 *
 * 20    3.09.03 14:35 Peter
 * Nur noch die Temperaturbezogene Weiche führt zu  einer Weichen Warnung
 * in ushWarnOutTM
 *
 * 19    1.09.03 17:09 Peter
 * Feld für Radpositionsbezogene Warnvektoren um 1 erweitert für
 * radpositionsunspezifische Warnungen
 * Filterung nur zu ushWarnOutTM hin nicht mehr in den Vectorarrays
 * Filterung über seperate Funktion
 * Anpassung der Diagnosedienste an obige Änderungen
 * (ganz schön viel geändert)
 *
 * 17    1.08.03 12:00 Peter
 * Maßnahmen für Misra Konformitätseinhaltung nach QAC
 *
 * 16    30.07.03 17:52 Peter
 * Korrektur beim service zum runterladen neuer positionen
 *
 * 15    30.07.03 17:38 Peter
 * Korrektur beim service zum runterladen neuer positionen
 *
 * 14    30.07.03 10:54 Peter
 * Neuen Diagnosedients zum reinladen des kompletten Warnvectorfeldes
 * realisiert
 *
 * 13    24.07.03 10:30 Peter
 * id bezogene ein/ausblendmöglichkeit als diag. dienst geschaffen
 *
 * 12    22.07.03 11:30 Peter
 * Beschreibung für DiagService ucDeActivateIdc eingefügt (Service selbst
 * muss noch realisisert werden)
 *
 * 11    10.07.03 12:08 Peter
 * Diagnosedienst für TSSMsgManagerTM() eingefügt (ucClearWarnOfIdc)
 *
 * 10    9.07.03 17:13 Peter
 * Korrektur bei Positionsausgabe
 *
 * 9     9.07.03 16:52 Peter
 * An den TSSMsgManager wird zur Ausgabegenerierung die Information ob mit
 * oder ohne Radposition übergeben. Bisher hat sich der Manager diese
 * Informationen aus den Radpositionsinfos selbst gebastelt.
 *
 * 8     4.07.03 13:21 Peter
 * postionsunspezifische WW wird jetzt unterstützt
 *
 * 7     27.06.03 15:21 Peter
 * Konstanten für Bits in ushWarnOutTM (globale Ausgabe Variable d.
 * Warnmoduls ) werden extern
 *
 * 6     16.06.03 10:20 Peter
 * Dokumentation

*/

/*
Declaration
*/
/*
Include
*/
#include "USWarnX.h"
#include "global.h"
#include "tssmsg.h"
#include "eeiface.h"
#include "WnTypePar.h"
#include "USWTime.h"
#include "uswarn_Ifx.h"

#ifndef pb_TestTssMsg_300103

#else
#include <stdio.h>
#endif
/*
Prototypes
*/

static void TSSMsgOut(const unsigned char *ptData);
static unsigned char ucTSSMsgService(unsigned char * pucData);
static void TSSMsgInit(void);
static void GenTPM_WarnDisp_Rq(void);
static void GenDAGlobalWarningLevel(void);
static void IdWarn2WP(const uint8 * p2WP);
/*******************************************************************************
Macros
*/



/*******************************************************************************
Data
*/
/* const */



/* variable */



static unsigned char ucGlobalWarnStatus;
/* "kodierbyte für anzeige: */
    /*
    aucWnValidTM[ucIxWnCfgc] =
    MSB
        X -> not used
        X -> not used
        X -> sparetyre warning only PMin
        X -> sparetyre warning as all tyres

        X -> no sparetyre warning at all (1 = no warning for sparetyre)
        X -> not used (reserved for isochore rated reset conditions in warnmanager)
        X -> not used (reserved for  ctry code in warnmanager )
        X -> not used (reserved for  ctry code in warnmanager )
    LSB
    aucWnValidTM[ucIxMsCfgc] =
    MSB
        X -> Solldruck - 100mBar (TS) 1 = disabled
        X -> Solldruck - DPwwiso (ST) 1 = disabled
        X -> Solldruck - DPisovhi (HTV) 1 = disabled
        X -> Solldruck - DPiso (HT) 1 = disabled

        X -> FT 1 = disabled
        X -> DHW 1 = disabled
        X -> Solldruck - x% (PFactor) 1 = disabled
        X -> not used (non maskable)
    LSB

    */



/* global output of ushWarnOutTM */
    /*
    MSB
    X   -   not used
    X   -   not used
    X   -   not used
    X   -   not used

    X
    X   -   WW spare tyre
    X   -   WW rear right
    X   -   WW rear left


    X   -   WW front right
    X   -   WW front left
    X   -   (HW spare tyre - not used)
    X   -   HW rear right

    X   -   HW rear left
    X   -   HW front right
    X   -   HW front left
    X   -   HW no wheel position
    LSB
    */
unsigned short ushWarnOutTM;


/* wheel position specific warnbits for Mr. Kessler  :
 *aushWheelPosWarn[0..5] = aushWheelPosWarn[FL..ST,unspecific] =
 *
*    X X X X  X X X X  LSB according to ucId (s.a.)
*    | | | |  | | | |_	PMin Warning
*    | | | |  | | |___	PFactor
*    | | | |  | |_____	DHW
*    | | | |  |_______	FT
*    | | | |__________	HardT
*    | | |____________  HardVT
*    | |______________	SoftT
*    |________________  TS (tankstop)
 */
unsigned char aucWheelPosWarn[ucMaxPosc + 1];/* +1 for undefined wheel position ( SW_10060 )*/




static unsigned char aucWarnAtPosTM[ucMaxPosc + 1];/* +1 for undefined wheel position ( SW_10060 )*/

static unsigned char ucTPM_WarnDisp_Rq = cNORMAL;

/*******************************************************************************
Implementation
*/
/*******************************************************************************
private functions
*/
static unsigned char ucAnyHWActive(void)
{
  if (((aucWarnAtPosTM[ucSumWEc] & (1<<ucPMinIxc)) > 0) || (((aucWarnAtPosTM[ucSumWEc] & (1<<ucEcEIxc)) > 0) && (ui8HWTimerExpired() > (uint8) 0)) )
    return ((unsigned char) 1);
  else
    return ((unsigned char) 0);
}

static unsigned char ucAnySWActive(void)
{
  if (((aucWarnAtPosTM[ucSumWEc] & (1<<ucSFactorIxc)) > 0) && (ui8SWTimerExpired () > (uint8) 0))
    return ((unsigned char) 1);
  else
    return ((unsigned char) 0);
}


static void TSSMsgOut(const unsigned char *ptData)
{
  union TssMsgAccess
  {
    struct TssMsg tTssMsg;
    unsigned char ucByte[sizeof(struct TssMsg)];
  }tTMD;	/* TssMessageData */
	unsigned char i;

	for (i=0; i < (unsigned char) sizeof(struct TssMsg) ;i++)	/* copy message data to lokal */
	{
		tTMD.ucByte[i] = ptData[i];
	}
	if (tTMD.tTssMsg.ucId < ucSumWEc)
	{
		aucWarnAtPosTM[tTMD.tTssMsg.ucId] = tTMD.tTssMsg.ucWarning; /* SW_10090 */
		IdWarn2WP (GETpui82SysWP());
 	}
}
static unsigned char ucTSSMsgService(unsigned char * pucData)
{
	unsigned char i, ucRet = 0;	/* no error return value */

	switch (*pucData)
	{
	case (unsigned short) ucNewPositionsc:		/* get a set of new wheel positions */
		{
				IdWarn2WP (GETpui82SysWP());// Warnings2Msg(&tMsg);  /*  and generate new output data */
				ucRet = 0;
    }
		break;

	case (unsigned short) ucPutWarnVectorSetc:
		{
			pucData++;   /* set pointer to 1st warnvector (id0) */
			for (i=0;i<ucSumWEc;i++)
			{
				aucWarnAtPosTM[i] = pucData[i];
			}
		}
		break;
	default:
		ucRet = 0xff;	/* error bad diag function parameter (ucData) */
		break;
	}
	return ( ucRet );
}

static void TSSMsgInit(void)
{
  unsigned char i;

  GetDataEE(ucCbIdTMc,&ucGlobalWarnStatus , 1);
  for ( i = 0; i < (ucSumWEc + 1);i++)		/* clear warn data */
  {
    aucWarnAtPosTM[i] = 0;
    aucWheelPosWarn[i] = 0;  /* SW_10060 */
  }
  
  if (cFAST_DEFLATION == ucGlobalWarnStatus)
  {
    ucGlobalWarnStatus = cHARD_WARNING;
    PutDataEE(ucCbIdTMc, &ucGlobalWarnStatus , 1);
  }
  ushWarnOutTM = ucGlobalWarnStatus;

  ucTPM_WarnDisp_Rq = cNORMAL;
}
/*******************************************************************************
*public functions
*
***************************************************************************************************
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
*ptData = points to array of 2 bytes which contain outputfilterconfiguration (see below)
*         (only processed if module is not yet init.)
*         according to the tPSSA ConfigBytes:
*  Byte[1] MSB - 0 - SollDruck tankstop (warning type TS) active
*                0 - SollDruck DPisoww (warning type ST) active
*                0 - SollDruck DPisovhi (warning type HTV) active
*                0 - SollDruck DPiso (warning type HT) active
*
*                0 - SollDruck DPisovlo (warning type dPVT) active
*                0 - DHW (warning type DHW) active
*                0 - Solldruck - X% (PFactor)
*          LSB - 0 - tbd
*  Byte[0] MSB - X - tbd
*                X - tbd
*                1 - spare tyre warning only PMin
*                1 - spare tyre warning as running tyres
*
*                1 - activate spare tyre warning i.g.
*                1 - tbd
*                1 - tbd
*          LSB - 1 - tbd
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
*      X X X X  X X X X  LSB according to ucId (s.a.)
* 	   | | | |  | | | |_	PMin Warning
* 	   | | | |  | | |___	PFactor
* 	   | | | |  | |_____	DHW
* 	   | | | |  |_______	dPVT
* 	   | | | |__________	HardT
* 	   | | |____________  HardVT
* 	   | |______________	SoftT
*      |________________  TS (tankstop)
*return:
*update of global variable  ushWarnOutTM
*_____________________________________________________________________________________________________
*ucAction = ucDiagServicec
*ptData: point to
*1st byte = ucGetWarnVectorc (= const.) read detailed warninformation (return value) of a specific id
*last       ucId = 0..4 = FL..ST, 5 = wheel position unknown
*return:
*bit coded warning:
*      X X X X  X X X X  LSB according to ucId (s.a.)
* 	   | | | |  | | | |_	PMin Warning
* 	   | | | |  | | |___	PFactor
* 	   | | | |  | |_____	DHW
* 	   | | | |  |_______	dPVT
* 	   | | | |__________	HardT
* 	   | | |____________  HardVT
* 	   | |______________	SoftT
*      |________________  TS (tankstop)
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
*ptData points to
*tPSSA with .ucAccess = ucRdWnValidTMc (read output configuration data to tPSSA)
*return (direct) = 0
*_____________________________________________________________________________________________________
*ptData points to
*tPSSA with .ucAccess = ucWrWnValidTMc (write tPSSA data to internal configuration variables & safe)
*return (direct) = 0
*_____________________________________________________________________________________________________
*1st byte = ucClearWarnOfIdc
*last       id  (0,1..ucSumWEc, ucSumWEc clear complete ushWarnOutTM)
*return:
*0x00 OK - new WP table written
*0xFF ERROR
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
**------------------------------------------------------------------------------------------------
**
**revision history
*
*changes in 2003
*
*30.01.2003 pb - 1st established
*12.06.2003 pb - documentation update
*09.07.2003 pb - no self detection for posspecific/unspecific diplay of warnings, information is now
*                 in function parameter "TssMsg.ucSystemState"
*10.07.2003 pb - clear service integrated
*30.07.2003 pb - ucPutWarnVectorSetc initgrated (new service)
*01.08.2003 pb - misra conformance
*01.10.2003 pb - support unknown wheel positions in diag service "ucNewPositionsc"
*01.12.2003 pb - deactivate "Reaktion nach Panne "-filter for diag service ucGetWarnVectorsIdc
*05.12.2003 pb - bracket bug from misra conformation removed
*10.07.2004 pb - speed related warning and 16 bit warnvector adaption ( SW_10090 )
*23.07.2004 pb - misra conformance enhancement
*27.10.2005 pb - happy shrink event
*****************************************************************************************************/

unsigned char ucTSSMsgManagerTM(unsigned char ucAction, unsigned char *ptData)
{
	unsigned char ucRet = 0;  /* initialize for misra */

  switch( ucAction )
  {
		case (unsigned short) ucPorInitc:
      {
        TSSMsgInit();
      }
      break;
    case (unsigned short) ucTssMsgOutc :
      /* prepare tss message to can/ddp output module */
      TSSMsgOut(ptData);
      break;
    case (unsigned short) ucDiagServicec:
      /* configure output */
      ucRet = ucTSSMsgService(ptData);
			break;
    default:
      ucRet = 0xff;       /* error bad function parameter (ucAction) */
      break;
  }
  return(ucRet);
}


static void GenTPM_WarnDisp_Rq(void)
{
  if (ui8KL15OFFnXsec() > 0)    // W.Kiesewetters wish we fullfill with this: 2sec after KL15 was switched 
  {                             //  off, we temporarily set WDR = NoWalni. This is a singular event. 
    ucTPM_WarnDisp_Rq = cNORMAL;//  Singular to 1 KL15off cycle.
  }
  
  switch (ucTPM_WarnDisp_Rq)
  {
  case cNORMAL:
    if (cFAST_DEFLATION == ushWarnOutTM)
      ucTPM_WarnDisp_Rq = cFAST_DEFLATION;
    else if ((cHARD_WARNING == ushWarnOutTM) && (ui8NoHoldOff () > (uint8) 0) )
      ucTPM_WarnDisp_Rq = cHARD_WARNING;
    else if ((cSOFT_WARNING == ushWarnOutTM) && (ui8NoHoldOff () > (uint8) 0) )
      ucTPM_WarnDisp_Rq = cSOFT_WARNING;
    break;

  case cSOFT_WARNING:
    if (cFAST_DEFLATION == ushWarnOutTM)
      ucTPM_WarnDisp_Rq = cFAST_DEFLATION;
    else if (cHARD_WARNING == ushWarnOutTM)
      ucTPM_WarnDisp_Rq = cHARD_WARNING;
    else if (cNORMAL == ushWarnOutTM )
      ucTPM_WarnDisp_Rq = cNORMAL;
    break;

  case cHARD_WARNING:
    if (cFAST_DEFLATION == ushWarnOutTM)
      ucTPM_WarnDisp_Rq = cFAST_DEFLATION;
    else if (cNORMAL == ushWarnOutTM )
      ucTPM_WarnDisp_Rq = cNORMAL;
    break;

  case cFAST_DEFLATION :
    if (cNORMAL == ushWarnOutTM ) 
      ucTPM_WarnDisp_Rq = cNORMAL;
    
    break;

  default:
    ucTPM_WarnDisp_Rq = cNORMAL;
    break;
  }
}

static void GenDAGlobalWarningLevel(void)
{
  ushWarnOutTM = (unsigned short) ucGlobalWarnStatus;
  switch (ucGlobalWarnStatus)
  {
  case cNORMAL:
    if ((aucWarnAtPosTM[ucSumWEc] & (1<<ucDHWIxc)) > 0)
      ucGlobalWarnStatus = cFAST_DEFLATION;
    else if ((ucAnyHWActive () > 0) && (ui8CalActive () == 0))
      ucGlobalWarnStatus = cHARD_WARNING;
    else if ((ucAnySWActive () > 0) && (ui8CalActive () == 0))
      ucGlobalWarnStatus = cSOFT_WARNING;
    break;
  
  case cSOFT_WARNING:
    if ((aucWarnAtPosTM[ucSumWEc] & (1<<ucDHWIxc)) > 0)
      ucGlobalWarnStatus = cFAST_DEFLATION;
    else if ((ucAnyHWActive () > 0) ) // && (ui8CalActive () == 0)) --> calibration active condition no longer valid in TPMS Logic PAL2 V1.4.docx
      ucGlobalWarnStatus = cHARD_WARNING;
    else if (((aucWarnAtPosTM[ucSumWEc] & ucAllDAGWarningBits) == (unsigned char) 0) || ((ui8MfdCalActive () == 1))) /*|| -> CRS_1211_090_002 MFD only*/
      ucGlobalWarnStatus = cNORMAL;
    break;

  case cHARD_WARNING:
    if (((aucWarnAtPosTM[ucSumWEc] & (1<<ucDHWIxc)) > 0) && (ui8KL15OFF () == 0))
      ucGlobalWarnStatus = cFAST_DEFLATION;
	else if (ui8MfdCalActive () == 1) /*CRS_1211_090_002 MFD only*/
			ucGlobalWarnStatus = cNORMAL; 
    else if ((aucWarnAtPosTM[ucSumWEc] & ((1<<ucPMinIxc)|(1<<ucEcEIxc))) == ((unsigned char) 0))
      ucGlobalWarnStatus = cSOFT_WARNING;
    break;
  
  case cFAST_DEFLATION :
    if (ui8KL15OFF () > 0)
      ucGlobalWarnStatus = cHARD_WARNING;
    else if (((aucWarnAtPosTM[ucSumWEc] & ucAllDAGWarningBits) == (unsigned char) 0) || ((ui8MfdCalActive () == 1))) /*|| -> CRS_1211_090_002 MFD only*/
      ucGlobalWarnStatus = cNORMAL;
    break;
  
  default:
    ucGlobalWarnStatus = cNORMAL;
    break;
    }
  if (((unsigned char) ushWarnOutTM) !=  ucGlobalWarnStatus)
  {
    PutDataEE(ucCbIdTMc, &ucGlobalWarnStatus , 1);
    ushWarnOutTM = (unsigned short) ucGlobalWarnStatus;
  }
}

unsigned char GetucTPM_WarnDisp_Rq(void)
{
  return (ucTPM_WarnDisp_Rq);
}

void UpdateGlobWrnLvlNWarnDisp(void)
{
  GenDAGlobalWarningLevel ();
  UpdateDAGsOldOff();
  GenTPM_WarnDisp_Rq ();
}

uint8 ui8GetHardWrnOfWP(uint8 ui8WP)  // returns 1 if pressure is below hardwarning level and hard warning timer is expired, else 0 is returned
{
  if (sizeof(aucWheelPosWarn) > ui8WP)
    return( (( (aucWheelPosWarn[ui8WP] & ((unsigned char) (1<<ucEcEIxc)) ) == ((unsigned char) (1<<ucEcEIxc))  ) && (ui8HWTimerExpired() > (uint8) 0)) ? (uint8)1:(uint8)0);
  
  return ( (uint8) 0);
}

uint8 ui8GetSoftWrnOfWP(uint8 ui8WP)  // returns 1 if pressure is below softwarning level and soft warning timer is expired, else 0 is returned
{
  if (sizeof(aucWheelPosWarn) > ui8WP)
    return( ( (aucWheelPosWarn[ui8WP] & ((unsigned char) (1<<ucSFactorIxc)) ) == ((unsigned char) (1<<ucSFactorIxc)) && (ui8SWTimerExpired() > (uint8) 0)) ? (uint8)1:(uint8)0);
  
  return ( (uint8) 0);
}

// ui8GetWarntypeOfHistCol purpose:
// returns 0xff if ui8WnType [cDAG_PMin_WN,cDAG_Hard_WN,cDAG_FPL_WN,cDAG_Soft_WN] of ui8HistCol[0,1,2,3] is active, otherwise 0
uint8 ui8GetWarntypeOfHistCol(uint8 ui8WnType, uint8 ui8HistCol)
{
  if (((uint8) 4) > ui8HistCol )
  {
    ui8WnType &= ucAllDAGWarningBits;
    if (ui8WnType == (aucWarnAtPosTM[ui8HistCol ] & ui8WnType ))
    {
      return ((uint8) 0xFF);
    }
    else
    {
      return ((uint8) 0);
    }
  }
  else
  {
    return ((uint8) 0);
  }
}


// IdWarn2WP purpose:
// generates WP and WP independet warnings out of ID / history column [0..4] dependend warnings
// WP dep. and WP undep. may coexist
static void IdWarn2WP(const uint8 * p2WP)
{
  uint8 i, ui8UnusedWP;

  ui8UnusedWP = (uint8) 0x0F; // all 4 WPs unused by default
  aucWheelPosWarn[ucSumWEc] = (uint8) 0;
  aucWarnAtPosTM[ucSumWEc] = (uint8) 0;

  for (i=0;i<ucSumWEc;i++)  // generate WPdep and UKWP walnings
  {
    switch(p2WP[i])
    {
    case (unsigned short) ucWPFLc:
      aucWheelPosWarn[ucWPFLc] = aucWarnAtPosTM[i];
      ui8UnusedWP &= ((uint8) ~1);  // this one is used
      break;
    case (unsigned short) ucWPFRc:
      aucWheelPosWarn[ucWPFRc] = aucWarnAtPosTM[i];
      ui8UnusedWP &= ((uint8) ~2);  // this one is used
      break;
    case (unsigned short) ucWPRLc:
      aucWheelPosWarn[ucWPRLc] = aucWarnAtPosTM[i];
      ui8UnusedWP &= ((uint8) ~4);  // this one is used
      break;
    case (unsigned short) ucWPRRc:
      aucWheelPosWarn[ucWPRRc] = aucWarnAtPosTM[i];
      ui8UnusedWP &= ((uint8) ~8);  // this one is used
      break;
    default:
      aucWheelPosWarn[ucSumWEc] |= aucWarnAtPosTM[i];
      break;
    }
    aucWarnAtPosTM[ucSumWEc] |= aucWarnAtPosTM[i];
  }

  for (i=0;i<ucSumWEc;i++)  // clear WP walings of unused WPs
  {
    if ((uint8) 0 < (ui8UnusedWP & ((uint8) (1<<i))))
    {
      aucWheelPosWarn[i] = (uint8) 0;
    }
  }

  UpdateGlobWrnLvlNWarnDisp();
}


// NewPositionsUSWIF purpose:
// loads 4 new WPs [0(=FL),1,2,3(=RR),4(=UK)] into warn message
// all pressure warning display values will be updated then 
uint8 NewPositionsUSWIF( const uint8 *pucRadPos )
{
  uint8 i, ucResult, aucDiagService[5];

  aucDiagService[0] = ucNewPositionsc;

  for( i = 0; i < ucSumWEc; i++ )
  {
    aucDiagService[i + 1] = pucRadPos[i];
  }

  if ( ucTSSMsgManagerTM( ucDiagServicec, aucDiagService ) == 0x00 )
  {
    ucResult = 0;     /* everything went fine */
  }else{
    ucResult = 0xff;  /* error case */
  }

  return( ucResult );
}