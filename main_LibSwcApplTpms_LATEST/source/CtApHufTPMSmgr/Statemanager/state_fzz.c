/************************************************************************************************************
 * (c) BERU Electronics GmbH      Abteilung BES2     2008
 ************************************************************************************************************/
/************************************************************************************************************
 * Project:       Reifendruckkontrolle TSS (TSS = tyre safety system)
 *
 * $Archive: /BMW/G3kompakt/Sw/SC6demo/template_can/application/source/tssappl/statemanager/state_fzz.c $
 *
 * File Status:   compiled           - (under construction, compiled etc.)
 *
 ************************************************************************************************************/
/************************************************************************************************************
 * Author:
 *
 * Initials     Name                           Company
 * --------     --------------------------     --------------------------------------------------------------
 * ur           Uwe Rapp                       BERU Electronics GmbH (BES2)
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
 * Modul Description
 * =================
 *
 * Purpose:
 *
 *
 *
 ************************************************************************************************************/
/************************************************************************************************************
 * Modul Abbreviation:
 * ===================
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
 * MISRA-C 2004 Regelverletzungen
 * ==============================
 *
 * MISRA-C:2004 Rule 12.4: Msg(4:3415) The right hand operand of '&&' or '||' has side effects.
 *                         Da der Zugriff auf globale Bitstrukturen �ber Funktionen gekapselt ist, kann diese
 *                         Regelverletzung ohne Gefahr hingenommen werden.
 *                         Die Beseitigung dieser Regelverletzung h�tte eine Erh�hung der zyklomatischen
 *                         Komplexit�t zur Folge.
 * MISRA-C:2004 Rule 3.1: REFERENCE - ISO-5.2.1 Character Sets
 *                        Msg(4:0288) [I] Source file '%s' has comments containing characters which are not
 *                        members of the basic source character set.
 *                        - Die Umlaute in Kommentaren sind erlaubt.
 *                        - In Variablenbezeichnungen sind keine Umlaute erlaubt.
 *                        - VSS-Steuercodes (z.B. $Archive) sind erlaubt
 *
 ************************************************************************************************************/



/************************************************************************************************************
 *                                             include
 ************************************************************************************************************/
#include "state_fzz.h"
#include "internal_clockX.h"
#include "Rte_CtApHufTPMSmgr.h"
#include "WallocX.h"
#include "state_fzzX.h"
//#include "state_fdX.h"
#include "SupplyBattery.h"
#include "state_bzX.h"
#include "USWarnX.H"
#include "HMI_handlerX.h"
//#include "tel_statisticX.h"
#include "SensorLoBat.h"
#include "filling_detectionX.h"
#include "DEM.h"
#include "EcuM_Generated_Types.h"
//#include "CtApHufTPMSdia.h"


 /*
#include "statemanagerX.h"
#include "receiveX.h"
#include "ecustateX.h"
#include "sgdiagX.h"
#include "procdatX.h"
#include "bandmodex.h"
#include "wallocX.h"
 */

/************************************************************************************************************
 *                                             macro
 ************************************************************************************************************/

 
/************************************************************************************************************
 *                                            typedef
 ************************************************************************************************************/



/************************************************************************************************************
 *                                    data (Modulglobal) - ROM
 ************************************************************************************************************/



/************************************************************************************************************
 *                                    data (Modulglobal) - RAM
 ************************************************************************************************************/
extern uint8	bAwakeIgnOn; // awake reason


/************************************************************************************************************
 *                                       data (global) - ROM
 ************************************************************************************************************/
#define cMIN_TIME_SNA_ERROR   ((uint8) 60) //minimum time needed to confirmed a signal not available error
#define cMIN_TIME_AFTER_IGN_START ((uint8) 10) //minimum time needed after ignition start
#define cMIN_TIME_AFTER_ENG_START ((uint8) 10) //minimum time needed after engine start

/************************************************************************************************************
 *                                       data (global) - RAM
 ************************************************************************************************************/



/***********************************************************************************************************
 *                                 prototype (local functions - private)
 ***********************************************************************************************************/
static uint16 ushVehicleSpeed = 0;
static sint8 scOutdoorTemperature = 0;
static uint8 ucEcuStopCntr = 0;
static uint8 ucFzzCurrentLearnMode = cCompleteLearn; 
static uint8 ucFzzPreviousParkingState = 1;

static uint8 ucTimeSinceLastKL15On = 0;
static uint8 ucTimeSinceLastEngStart = cMIN_TIME_AFTER_ENG_START; //counter is reset only after detecting engine start

static uint8 ucTimeSnaWhlplsFL = 0; // counter for wheel pulse counter signal not available  in sec
static uint8 ucTimeSnaWhlplsFR = 0; // counter for wheel pulse counter signal not available in sec
static uint8 ucTimeSnaWhlplsRL = 0; // counter for wheel pulse counter signal not available in sec
static uint8 ucTimeSnaWhlplsRR = 0; // counter for wheel pulse counter signal not available in sec
static uint8 ucTimeSnaTractSystem = 0;  // counter for traction system signal not available in sec
static uint8 ucTimeSnavehSpeed = 0; // counter for vehicle speed signal not available in sec
static uint8 ucTimeSnaAirTempOut = 0; // counter for outside air temperature not available in sec
static uint8 ucTimeSnaIcA3TpmActiv = 0; // counter for IC_A3_TPM_Activ signal not available in sec

static uint8 ucIgnOnStartProc = 0;

/***********************************************************************************************************
 *                                 prototype (local functions - public)
 ***********************************************************************************************************/
void InitAfterKl15OffSM(void);
void InitWATCF(void);
void InitAfterKl15OnSM(void);
void InitFDAfterKl15On(void);
void InitFDAfterKl15OffSM(void);
void UpdateFzzCurrentLearnMode(void);
uint8 ucGetFzzCurrentLearnMode(void);

void ClearFzzSignalUnplausibleState(uint16 ushBitMask);
static void  UpdateFzzAllSignalDTCSetCond(void);
static void UpdateFzzAllSignalImplausibleCntr(void);
void SetFzzSignalImplauState(uint16 ucBitMask);
void InitFzzCanSignalMonitoring(void);
static boolean bFzzSignalFailureMonitoringActiv(void);
static boolean bGetFzzSignalTimeOutState(uint16 ushBitMask);

void SetFzzState4MM(uint8 state);
uint8 GetFzzState4MM(void);

void SetGlobWarnState4MM(uint8 state);
uint8 GetGlobWarnState4MM(void);
/************************************************************************************************************
 *                               prototype (external functions - interface)
 ************************************************************************************************************/
extern void InitTxBusMsg(void);
extern FUNC(Std_ReturnType, ECUM_API_CODE) EcuM_GetState(P2VAR(EcuM_StateType, AUTOMATIC, ECUM_APPL_DATA) state);
extern void UpdateSensorStateAtClamp15Off(void); /*tel_statistic*/
extern void InitTelStatInfoAtModeChange(void);/*tel_statistic*/
extern void UpdateHMICurrentTireStat4MM(void);
/************************************************************************************************************
 *                                            implementation
 ************************************************************************************************************/



/*!**********************************************************************************************************
 *\Function           void InitFZZ( void )
 *
 *\Typ                public
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Purpose            initialisation of vehicle state
 *
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\SW_Requirements    none
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Parameter          none
 *
 *\Input              none
 *
 *\Output             none
 *
 *\Return             none
 *
 ************************************************************************************************************/
void InitFZZ( void )
{
  ClearBitFahrzeugzustandFZZ( cFZZ_ALLE_BITS );

 ushVehicleSpeed=0;
 scOutdoorTemperature=0;
 ucEcuStopCntr=0;
 ucFzzCurrentLearnMode = cCompleteLearn; // init with complete learn
 ucFzzPreviousParkingState = 1;

  InitFzzCanSignalMonitoring();
} /* void InitFZZ( void ) */





/*!**********************************************************************************************************
 *\Function           void SetBitFahrzeugzustandFZZ( uint16 ushBitMask )
 *
 *\Typ                public
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Purpose            Setzt Bit in Fahrzeugzustand anhand �bergebener Bitmaske.
 *                    Setzen mehrerer Bits m�glich, durch �bergabe "verODERter" Bitmasken.
 *                    z.B. setBitFahrzeugzustand(cBIT1 | cBIT2 | cBIT3);
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\SW_Requirements    none
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Parameter          usBitMask - Bitmaske zu setzender Bits
 *
 *\Input              none
 *
 *\Output             none
 *
 *\Return             none
 *
 ************************************************************************************************************/
void SetBitFahrzeugzustandFZZ( uint16 ushBitMask )
{
   ushFahrzeugzustand |= ushBitMask;
} /* void SetBitFahrzeugzustandFZZ( uint16 ushBitMask ) */



/*!**********************************************************************************************************
 *\Function           void ClearBitFahrzeugzustandFZZ( uint16 ushBitMask )
 *
 *\Typ                public
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Purpose            L�scht Bit in Fahrzeugzustand anhand �bergebener Bitmaske.
 *                    L�schen mehrerer Bits m�glich, durch �bergabe "verODERter" Bitmasken.
 *                    z.B. clearBitFahrzeugzustand(cBIT1 | cBIT2 | cBIT3);
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\SW_Requirements    none
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Parameter          usBitMask - Bitmaske zu l�schender Bits
 *
 *\Input              none
 *
 *\Output             none
 *
 *\Return             none
 *
 ************************************************************************************************************/
void ClearBitFahrzeugzustandFZZ( uint16 ushBitMask )
{
   ushFahrzeugzustand &= ~ushBitMask;
} /* void ClearBitFahrzeugzustandFZZ( uint16 ushBitMask ) */



/*!**********************************************************************************************************
 *\Function           boolean bGetBitFahrzeugzustandFZZ( uint16 ushBitMask )
 *                    uint16 ushGetFahrzeugzustandFZZ( uint16 ushBitMask )
 *
 *\Typ                public
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Purpose            Liefert Bitzustand des anhand der �bergebenen Bitmaske selektierten Bit
 *                    in Fahrzeugzustand.
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\SW_Requirements    none
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Parameter          usBitMask - Bitmaske zur Bitselektion
 *
 *\Input              none
 *
 *\Output             none
 *
 *\Return             1 = Bit gesetzt
 *                    0 = Bit nicht gesetzt
 *
 ************************************************************************************************************/
boolean bGetBitFahrzeugzustandFZZ( uint16 ushBitMask )
{
   return (boolean) ((ushFahrzeugzustand & ushBitMask) != 0 );
} /* boolean bGetBitFahrzeugzustandFZZ( uint16 ushBitMask ) */



uint16 ushGetFahrzeugzustandFZZ( uint16 ushBitMask )
{
   return (ushFahrzeugzustand & ushBitMask);
} /* uint16 ushGetFahrzeugzustandFZZ( uint16 ushBitMask ) */



/*!**********************************************************************************************************
 *\Function           void EvTerminal15OnFZZ( void )
 *
 *\Typ                public
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Purpose            Auf dem Fahrzeugbus wurde Klemme 15 ein �bertragen
 *
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\SW_Requirements    none
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Parameter          none
 *
 *\Input              none
 *
 *\Output             none
 *
 *\Return             none
 *
 ************************************************************************************************************/
void EvTerminal15OnFZZ( void )
{
  if( bGetBitFahrzeugzustandFZZ( cKL_15_EIN ) == FALSE )  /* Mehrfachaufrufe vermeiden */
  {
    SetBitFahrzeugzustandFZZ( cKL_15_EIN );

    InitWATCF();
    InitAfterKl15OnSM();
		InitFDAfterKl15On(); /*CRS_1211_130_221*/
		Rte_Call_UR_ComMUser_HMI_RequestComMode(COMM_FULL_COMMUNICATION); /*CRS_1211_010_010*/
    //ucTimeSinceLastKL15On = 0; // re init counter
   
  }
} /* void EvTerminal15OnFZZ( void ) */



/*!**********************************************************************************************************
 *\Function           void EvTerminal15OffFZZ( void )
 *
 *\Typ                public
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Purpose            Auf dem Fahrzeugbus wurde Klemme 15 aus �bertragen
 *
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\SW_Requirements    none
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Parameter          none
 *
 *\Input              none
 *
 *\Output             none
 *
 *\Return             none
 *
 ************************************************************************************************************/
void EvTerminal15OffFZZ( void )
{
  if( bGetBitFahrzeugzustandFZZ( cKL_15_EIN ) == TRUE )  /* Mehrfachaufrufe vermeiden */
  {
    ClearBitFahrzeugzustandFZZ( cKL_15_EIN );

    InitFDAfterKl15OffSM();	/*CRS_1211_130_222*/
    InitAfterKl15OffSM();
		ClearBitBetriebszustandBZ(cCAL_AFD_PLAUSI_ERROR | cCAL_MFD_PLAUSI_ERROR);/*CRS_1211_130_097 calibration: second reset condition 5.5.5 */
		//ClearBitBetriebszustandBZ(cCAL_AFD_PLAUSI_ERROR);/*CRS_1211_130_324 AFD: second reset condition 5.5.5 */
		//CRS_1211_130_221 Kein R�cksetzen! MUSS �ber einen LKlemmenzykus gehalten werden!!!!!!!!!ClearBitBetriebszustandBZ(cCAL_REQUEST);
    //CRS_1211_130_249 PUTucCalRequestState2Nvm(); /* CRS_1211_130_170 CalRequestState into Nvm*/
		//CRS_1211_130_249 PUTucCalNotAckState2Nvm(); /*CRS_1211_130_240*/

  }
  //ucTimeSinceLastKL15On = 0; // re init counter
} /* void EvTerminal15OffFZZ( void ) */



/*!**********************************************************************************************************
 *\Function           void EvVehicleRollingFZZ( void )
 *
 *\Typ                public
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Purpose            Geschwindigkeitsschwelle zur Erkennung "Fahrzeug f�hrt" �berschritten
 *
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\SW_Requirements    none
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Parameter          none
 *
 *\Input              none
 *
 *\Output             none
 *
 *\Return             none
 *
 ************************************************************************************************************/
void EvVehicleRollingFZZ( void )
{
  if( bGetBitFahrzeugzustandFZZ( cFAHRZEUG_FAEHRT ) == FALSE )  /* Mehrfachaufrufe vermeiden */
  {
    SetBitFahrzeugzustandFZZ( cFAHRZEUG_FAEHRT );
  }
} /* void EvVehicleRollingFZZ( void ) */
/*!**********************************************************************************************************
 *\Function           void EvVehicleSpeed4CalFZZ( void )
 *
 *\Typ                public
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Purpose            Erkennung der Geschwindigkeitsschwelle v>20kmh als Vorbedingung f�r das Einsammeln der RE Dr�cke
 *                    bei Manuelle Kalibrierung
 *
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\SW_Requirements     CRS_1211_130_065
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Parameter          none
 *
 *\Input              none
 *
 *\Output             none
 *
 *\Return             none
 *
 ************************************************************************************************************/
void EvVehicleSpeed4CalFZZ( void )
{
  if( bGetBitFahrzeugzustandFZZ( cKFZFAEHRT_20KMH ) == FALSE )  /* Mehrfachaufrufe vermeiden */
  {
    SetBitFahrzeugzustandFZZ( cKFZFAEHRT_20KMH );
  }
} /* void EvVehicleSpeed4CalFZZ( void ) */



/*!**********************************************************************************************************
 *\Function           void EvVehicleStandsStillFZZ( void )
 *
 *\Typ                public
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Purpose            Geschwindigkeitsschwelle zur Erkennung "Fahrzeug f�hrt" unterschritten
 *
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\SW_Requirements    none
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Parameter          none
 *
 *\Input              none
 *
 *\Output             none
 *
 *\Return             none
 *
 ************************************************************************************************************/
void EvVehicleStandsStillFZZ( void )
{
  if( bGetBitFahrzeugzustandFZZ( cFAHRZEUG_FAEHRT ) == TRUE )  /* Mehrfachaufrufe vermeiden */
  {
    ClearBitFahrzeugzustandFZZ( cFAHRZEUG_FAEHRT );
    ucEcuStopCntr++;
  }
} /* void EvVehicleStandsStillFZZ( void ) */

/*!**********************************************************************************************************
 *\Function           void EvVehicleNoSpeed4CalFZZ( void )
 *
 *\Typ                public
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Purpose            Erkennung der Geschwindigkeitsschwelle v<17kmh als Vorbedingung f�r das 
 *\                   NICHT-Einsammeln der RE Dr�cke bei Manuelle Kalibrierung
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\SW_Requirements    CRS_1211_130_065
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Parameter          none
 *
 *\Input              none
 *
 *\Output             none
 *
 *\Return             none
 *
 ************************************************************************************************************/
void EvVehicleNoSpeed4CalFZZ( void )
{
  if( bGetBitFahrzeugzustandFZZ( cKFZFAEHRT_20KMH ) == TRUE )  /* Mehrfachaufrufe vermeiden */
  {
    ClearBitFahrzeugzustandFZZ( cKFZFAEHRT_20KMH );

  }
} /* void EvVehicleNoSpeed4CalFZZ( void ) */

/*!**********************************************************************************************************
 *\Function           void EvReDiagActiveFZZ( void )
 *
 *\Typ                public
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Purpose            Geschwindigkeitsschwelle zur Freischaltung der RE-Diagnose �berschritten
 *
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\SW_Requirements    none
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Parameter          none
 *
 *\Input              none
 *
 *\Output             none
 *
 *\Return             none
 *
 ************************************************************************************************************/
void EvReDiagActiveFZZ( void )
{
  if( bGetBitFahrzeugzustandFZZ( cRS_VTHRES ) == FALSE )  /* Mehrfachaufrufe vermeiden */
  {
    SetBitFahrzeugzustandFZZ( cRS_VTHRES );
    //ControlWATO( cWATO_RESTART_ALARM, 0 );
  }
} /* void EvReDiagActiveFZZ( void ) */



/*!**********************************************************************************************************
 *\Function           void EvReDiagInactiveFZZ( void )
 *
 *\Typ                public
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Purpose            Geschwindigkeitsschwelle zur Freischaltung der RE-Diagnose unterschritten
 *
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\SW_Requirements    none
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Parameter          none
 *
 *\Input              none
 *
 *\Output             none
 *
 *\Return             none
 *
 ************************************************************************************************************/
void EvReDiagInactiveFZZ( void )
{
  if( bGetBitFahrzeugzustandFZZ( cRS_VTHRES ) == TRUE )  /* Mehrfachaufrufe vermeiden */
  {
    ClearBitFahrzeugzustandFZZ( cRS_VTHRES );
    //ControlWATO( cWATO_BREAK_ALARM, 0 );
  }
} /* void EvReDiagInactiveFZZ( void ) */



/*!**********************************************************************************************************
 *\Function           void EvEngineRunningFZZ( void )
 *
 *\Typ                public
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Purpose            Motor wurde gestartet
 *
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\SW_Requirements    none
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Parameter          none
 *
 *\Input              none
 *
 *\Output             none
 *
 *\Return             none
 *
 ************************************************************************************************************/
void EvEngineRunningFZZ( void )
{
  if( bGetBitFahrzeugzustandFZZ( cENG_STARTING ) == TRUE )  /* Mehrfachaufrufe vermeiden */
  {
    ucTimeSinceLastEngStart = 0; //init counter
  }
  SetBitFahrzeugzustandFZZ( cENG_RUNNING );
  ClearBitFahrzeugzustandFZZ( cENG_STARTING );
} /* void EvEngineRunningFZZ( void ) */



/*!**********************************************************************************************************
 *\Function           void EvEngineStopedFZZ( void )
 *
 *\Typ                public
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Purpose            Motor angehalten
 *
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\SW_Requirements    none
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Parameter          none
 *
 *\Input              none
 *
 *\Output             none
 *
 *\Return             none
 *
 ************************************************************************************************************/
void EvEngineStopedFZZ( void )
{

  if( bGetBitFahrzeugzustandFZZ( cENG_STARTING ) == TRUE )  /* Mehrfachaufrufe vermeiden */
  {
    ucTimeSinceLastEngStart = 0; //init counter
  }
  ClearBitFahrzeugzustandFZZ( cENG_STARTING );
  ClearBitFahrzeugzustandFZZ( cENG_RUNNING );


} /* void EvEngineStopedFZZ( void ) */

/*!**********************************************************************************************************
 *\Function           void EvEngineStartingFZZ( void )
 *
 *\Typ                public
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Purpose            Enginge stating
 *
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\SW_Requirements    none
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Parameter          none
 *
 *\Input              none
 *
 *\Output             none
 *
 *\Return             none
 *
 ************************************************************************************************************/
void EvEngineStartingFZZ(void)
{
   ucTimeSinceLastEngStart = 0; //init counter
   ClearBitFahrzeugzustandFZZ(cENG_RUNNING);
   SetBitFahrzeugzustandFZZ( cENG_STARTING);
}

/*!**********************************************************************************************************
 *\Function           void EvDriveDirectionForwardFZZ( void )
 *
 *\Typ                public
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Purpose            Vorw�rtsfahrt
 *
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\SW_Requirements    none
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Parameter          none
 *
 *\Input              none
 *
 *\Output             none
 *
 *\Return             none
 *
 ************************************************************************************************************/
void EvDriveDirectionForwardFZZ( void )
{
  ClearBitFahrzeugzustandFZZ( cRUECKWAERTSFAHRT );
} /* void EvDriveDirectionForwardFZZ( void ) */



/*!**********************************************************************************************************
 *\Function           void EvDriveDirectionBackwardFZZ( void )
 *
 *\Typ                public
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Purpose            R�ckw�rtsfahrt
 *
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\SW_Requirements    none
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Parameter          none
 *
 *\Input              none
 *
 *\Output             none
 *
 *\Return             none
 *
 ************************************************************************************************************/
void EvDriveDirectionBackwardFZZ( void )
{
  SetBitFahrzeugzustandFZZ( cRUECKWAERTSFAHRT );
#ifdef FPA
  ReNewABSRef();
#endif
} /* void EvDriveDirectionBackwardFZZ( void ) */


/*!**********************************************************************************************************
 *\Function           void EvKl30DiagNoUnterSpgFZZ( void )
 *
 *\Typ                public
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Purpose            Klemm30 Bordnetzspannungs Diagnose: Spannung  i.O. Keine Unterspannung
 *\                   
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\SW_Requirements    CRS_1211_050_004
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Parameter          none
 *
 *\Input              none
 *
 *\Output             none
 *
 *\Return             none
 *
 ************************************************************************************************************/
void EvKl30DiagNoUnterSpgFZZ( void )
{
  if( bGetBitFahrzeugzustandFZZ( cKL30_UNTERSPG ) == TRUE )  /* Mehrfachaufrufe vermeiden */
  {
    ClearBitFahrzeugzustandFZZ( cKL30_UNTERSPG );
  }
} /* void EvKl30DiagNoUnterSpgFZZ( void ) */


/*!**********************************************************************************************************
 *\Function           void EvKl30DiagUnterSpgFZZ( void )
 *
 *\Typ                public
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Purpose            Klemm30 Bordnetzspannungs Diagnose: Erkennung von Unterspannung  
 *\                   
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\SW_Requirements    CRS_1211_050_004
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Parameter          none
 *
 *\Input              none
 *
 *\Output             none
 *
 *\Return             none
 *
 ************************************************************************************************************/
void EvKl30DiagUnterSpgFZZ( void )
{
  if( bGetBitFahrzeugzustandFZZ( cKL30_UNTERSPG ) == FALSE )  /* Mehrfachaufrufe vermeiden */
  {
		SetBitFahrzeugzustandFZZ( cKL30_UNTERSPG );
  }
} /* void EvKl30DiagUnterSpgFZZ( void ) */

/*!**********************************************************************************************************
 *\Function           void EvKl30DiagUnterSpgFZZ( void )
 *
 *\Typ                public
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Purpose            Klemm30 Bordnetzspannungs Diagnose: war in der Vergangenheit Unterspannung gesetzt!  
 *\                   
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\SW_Requirements    CRS_1211_050_004
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Parameter          none
 *
 *\Input              none
 *
 *\Output             none
 *
 *\Return             none
 *
 ************************************************************************************************************/
uint8 GetEvKl30DiagUnterSpgFZZ( void )
{
  if( bGetBitFahrzeugzustandFZZ( cKL30_UNTERSPG ) == TRUE )  /* */
  {
		return ( TRUE );
  }
	else
	{
		return ( FALSE );
	}
} /* uint8 GetEvKl30DiagUnterSpgFZZ( void ) */


/*!**********************************************************************************************************
 *\Function           void EvKl30DiagNoUeberSpgFZZ( void )
 *
 *\Typ                public
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Purpose            Klemm30 Bordnetzspannungs Diagnose: Spannung  i.O.
 *\                   
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\SW_Requirements    CRS_1211_050_004
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Parameter          none
 *
 *\Input              none
 *
 *\Output             none
 *
 *\Return             none
 *
 ************************************************************************************************************/
void EvKl30DiagNoUeberSpgFZZ( void )
{
  if( bGetBitFahrzeugzustandFZZ( cKL30_UEBERSPG ) == TRUE )  /* Mehrfachaufrufe vermeiden */
  {
    ClearBitFahrzeugzustandFZZ( cKL30_UEBERSPG );
  }
} /* void EvKl30DiagNoUeberSpgFZZ( void ) */


/*!**********************************************************************************************************
 *\Function           void EvKl30DiagUeberSpgFZZ( void )
 *
 *\Typ                public
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Purpose            Klemm30 Bordnetzspannungs Diagnose: Erkennung von �erspannung  
 *\                   
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\SW_Requirements    CRS_1211_050_004
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Parameter          none
 *
 *\Input              none
 *
 *\Output             none
 *
 *\Return             none
 *
 ************************************************************************************************************/
void EvKl30DiagUeberSpgFZZ( void )
{
  if( bGetBitFahrzeugzustandFZZ( cKL30_UEBERSPG ) == FALSE )  /* Mehrfachaufrufe vermeiden */
  {
		SetBitFahrzeugzustandFZZ( cKL30_UEBERSPG );
  }
} /* void EvKl30DiagUnterSpgFZZ( void ) */

/*!**********************************************************************************************************
 *\Function           uint8 GetEvKl30DiagUeberSpgFZZ( void )
 *
 *\Typ                public
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Purpose            Klemm30 Bordnetzspannungs Diagnose: war in der Vergangenheit �erspannung gesetzt!  
 *\                   
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\SW_Requirements    CRS_1211_050_045
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Parameter          none
 *
 *\Input              none
 *
 *\Output             none
 *
 *\Return             none
 *
 ************************************************************************************************************/
uint8 GetEvKl30DiagUeberSpgFZZ( void )
{
  if( bGetBitFahrzeugzustandFZZ( cKL30_UEBERSPG ) == TRUE )  /* Mehrfachaufrufe vermeiden */
  {
		return( TRUE );
  }
	else
	{
		return( FALSE );
	}
} /* uint8 GetEvKl30DiagUnterSpgFZZ( void ) */


/*!**********************************************************************************************************
 *\Function           void EvTPMS433MhzFZZ( void )
 *
 *\Typ                public
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Purpose            TPMS ATMEL receiver init 2 433Mhz frequency, because without 1Kohm to GND (Port10_9)  
 *\                   
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\SW_Requirements    CRS_1211_150_100
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Parameter          none
 *
 *\Input              none
 *
 *\Output             none
 *
 *\Return             none
 *
 ************************************************************************************************************/
void EvTPMS433MhzFZZ( void )
{
  if( bGetBitFahrzeugzustandFZZ( cTPMS433Mhz ) == FALSE )  /* Mehrfachaufrufe vermeiden */
  {
		SetBitFahrzeugzustandFZZ( cTPMS433Mhz );
  }

  if( bGetBitFahrzeugzustandFZZ( cTPMS315Mhz ) == TRUE )  /* Mehrfachaufrufe vermeiden */
  {
    ClearBitFahrzeugzustandFZZ( cTPMS315Mhz );
  }


} /* void EvTPMS433MhzFZZ( void ) */




/*!**********************************************************************************************************
 *\Function           void EvTPMS315MhzFZZ( void )
 *
 *\Typ                public
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Purpose            TPMS ATMEL receiver init 2 315Mhz frequency, because 1Kohm to GND (Port10_9)  
 *\                   
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\SW_Requirements    CRS_1211_150_100
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Parameter          none
 *
 *\Input              none
 *
 *\Output             none
 *
 *\Return             none
 *
 ************************************************************************************************************/
void EvTPMS315MhzFZZ( void )
{
  if( bGetBitFahrzeugzustandFZZ( cTPMS315Mhz ) == FALSE )  /* Mehrfachaufrufe vermeiden */
  {
		SetBitFahrzeugzustandFZZ( cTPMS315Mhz );
  }

  if( bGetBitFahrzeugzustandFZZ( cTPMS433Mhz ) == TRUE )  /* Mehrfachaufrufe vermeiden */
  {
    ClearBitFahrzeugzustandFZZ( cTPMS433Mhz );
  }


} /* void EvTPMS315MhzFZZ( void ) */



/*!**********************************************************************************************************
 *\Function           uint32 GETulKilometersFZZ( void )
 *
 *\Typ                public
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Purpose            Kilometerstand abrufen
 *
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\SW_Requirements    none
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Parameter          none
 *
 *\Input              none
 *
 *\Output             none
 *
 *\Return             none
 *
 ************************************************************************************************************/
uint32 GETulKilometersFZZ( void )
{
  uint32 ulKilometers=0;

  /*if( ReceiveMileageKM( &ulKilometers ) != RECEIVE_RET_OK )
  {
    ulKilometers = 0xffffffff;
  }*/
  //@@ ToDo: GL implement odometer
  return ulKilometers;
} /* uint32 GETulKilometersFZZ( void ) */



/*!**********************************************************************************************************
 *\Function           sint8 GETscOutdoorTemperatureFZZ( void )
 *
 *\Typ                public
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Purpose            Au�entemperatur abrufen
 *
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\SW_Requirements    none
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Parameter          none
 *
 *\Input              none
 *
 *\Output             none
 *
 *\Return             none
 *
 ************************************************************************************************************/
sint8 GETscOutdoorTemperatureFZZ( void )
{
  return scOutdoorTemperature;
} /* sint8 GETscOutdoorTemperatureFZZ( void ) */



/*!**********************************************************************************************************
 *\Function           uint16 GETushSpeedFZZ( void )
 *
 *\Typ                public
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Purpose            Geschwindigkeit abrufen
 *
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\SW_Requirements    none
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Parameter          none
 *
 *\Input              none
 *
 *\Output             none
 *
 *\Return             none
 *
 ************************************************************************************************************/
uint16 GETushSpeedFZZ( void )
{

  return ushVehicleSpeed;
} /* uint16 GETushSpeedFZZ( void ) */


void SendEnvData2VehStateMgr(uint8* data)
{
  DT_tEnvData* tEnvData = (DT_tEnvData*)data;
	ushVehicleSpeed = tEnvData->ushVehSpeed;
	scOutdoorTemperature = (sint8)tEnvData->ucTempOut;

	if (tEnvData->ucKlState == TRUE){
		EvTerminal15OnFZZ();
	}else{

	   EvTerminal15OffFZZ();
	}

  if( ucIgnOnStartProc==0)
  {
    ucTimeSinceLastKL15On = 0;
  }
  ucIgnOnStartProc = tEnvData->ucIgnOnStartProc;
	
  if (ushVehicleSpeed > 5)
	{    
		EvVehicleRollingFZZ();
    if (ushVehicleSpeed > cV_MIN)
		{
			EvVehicleSpeed4CalFZZ();
    }
		else 
		{
			EvVehicleNoSpeed4CalFZZ();	/*CRS_1211_130_086*/
		}
	}
  else
  { 
	  if (ushVehicleSpeed < 2)
		{
			EvVehicleStandsStillFZZ();
		}
		EvVehicleNoSpeed4CalFZZ();	/*CRS_1211_130_160 vehicle speed fast change immediately */
	}

  if(tEnvData->ucEngStat == cEngStat_STOPPED)
  {
    EvEngineStopedFZZ();
  }
  else if (tEnvData->ucEngStat == cEngStat_STARTING)
  {
    EvEngineStartingFZZ();
  }
  else if(tEnvData->ucEngStat == cEngStat_RUNNING)
  {
    EvEngineRunningFZZ();
  }

}


void InitAfterKl15OffSM(void){

  //else
  //{

	 //bOldIgnState = FALSE;
	
	 /* set the corespnding BSWM state --> disable transmission*/
	 //SetClamp15State(Off);
	 //Com_IpduGroupStop(Com_PduGrp_TxMess_TPM_HMI);
     //Com_IpduGroupStop(Com_PduGrp_TxNorm_TPM_HMI);
     //Nm_DisableCommunication(0);
	//ClearPlausiFailureFD(); /*KeinL�schen!CRS_1211_130_329 CRS_1211_130_191*/
	//ClearAbortReasonFD(); /*KeinL�schen!CRS_1211_130_329 CRS_1211_130_191*/
	//ClearFillingDetectionStateFD(); /*KeinL�schen!CRS_1211_130_329 CRS_1211_130_191*/
	SetFzzState4MM(FALSE);		/*CRS_1211_130_377*/
	KL15OffWarnInit(GETpucStartAdrWPorPWP ());
	InitHMIAfterKL15Off(); // Init HMI signals after KL15 Off
  UpdateSensorStateAtClamp15Off();

}

    
void InitWATCF(void){
	
}
 
void InitAfterKl15OnSM(void){

  //InitBZ();
    
  InitHMIAfterKL15On(); // Init HMI signals after KL15 On

  InitSensorLoBat (); 

  KL15OffWarnInit(GETpucStartAdrWPorPWP ());
	SetFzzState4MM(TRUE);		/*CRS_1211_130_377*/
	SetGlobWarnState4MM(GETushWarnstatus1WN());		/*CRS_1211_050_047*/
	UpdateHMICurrentTireStat4MM();

}

/************************************************************************************************//**
 *
 * \brief  Init Filling Detection after KL15 switch ON CRS_1211_130_221
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] none
 * \param [out] none
 *
 * \return	non
 *
 *------------------------------------------------------------------------------------------------
 */

void InitFDAfterKl15On(void)
{
	if((bGETucCalRequestState(cCAL_MANUAL_ACTIV) == TRUE) && (bGetBitBetriebszustandBZ(cCAL_REQUEST) == FALSE) && (bGETucCalRequestState(cCAL_AUTO_ENABLE2) == TRUE) )/* KL15 switch OFF BUT MFD is activ! */
	{
		//SetBitBetriebszustandBZ(cCAL_REQUEST);
		//ClearBitCalRequestState(cCAL_AUTO_ENABLE2);/* 07.10.2016 AFDII wird bei Parkingtime>= 1140 gestartet*/
		FillingDetectionMFD(FALSE);	/* CRS_1211_130_312 KEIN Ansteuern der Laompe mit 6= RESTART --> FALSE!  derCRS_1211_130_221*/
	}
	else
	{
		if((bGETucCalRequestState(cCAL_AUTO_ACTIV) == TRUE) && (bGETucCalRequestState(cCAL_AUTO_ENABLE3) == TRUE))/* KL15 switch OFF BUT AFD is activ! */
		{
			ClearBitCalRequestState(cCAL_AUTO_ENABLE3);/*CRS_1211_130_223*/
			FillingDetectionAFDIII(TRUE); /*CRS_1211_130_223* 1=ucDpTxTriggerc*/
		}
		else
		{
			if((GETucPfillFront() == 0) && (GETucPfillRear() == 0 ) &&  (bGETucCalNotAckState(cCAL_FBM_ACTIV_NAK) == FALSE))
			{
				SetBitCalRequestState2Ram(cCAL_AUTO_ENABLE2);		/* after flashen, auch Soft Reset! ABER nicht im FBM CRS_1211_130_344 !*/ 
			}
		}
	}
	if((GETucPfillFront() == 0) && (GETucPfillRear() == 0 ))
  {
		PUTucPfillFront(InvalidValue_c08_kPa_0_632d5_2d5);/*6,38bar CRS_1211_130_270*/
		PUTucPfillRear(InvalidValue_c08_kPa_0_632d5_2d5);/*6,38bar CRS_1211_130_270*/
		PUTscTfill(127); /*c08_degC_m50_204_1_UpperLimit= -1�C ????CRS_1211_130_270*/
	}
}

/************************************************************************************************//**
 *
 * \brief  Init Filling Detection after KL15 switch OFF CRS_1211_130_222
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] none
 * \param [out] none
 *
 * \return	non
 *
 *------------------------------------------------------------------------------------------------
 */
void InitFDAfterKl15OffSM(void)
{
	ClearBitFahrzeugzustandFZZ(cKFZPARKING_START_AFD);/* CRS_1211_130_170 */		
	
		/*AFD 3 activ?  hold AFD 3 */
		if((	bGETucCalRequestState(cCAL_AUTO_ENABLE3) ==	FALSE)  &&  (bGETucCalNotAckState(cCAL_FBM_ACTIV_NAK) == FALSE)) /* AFDII NICHT im FBM CRS_1211_130_344 */
		{
			SetBitCalRequestState2Ram(cCAL_AUTO_ENABLE2);		/* CRS_1211_130_1704 AFD start reason 2: Ignition-start and 19min parking time*/ 
			//CRS_1211_130_249 PUTucCalRequestState2Nvm(); /* CRS_1211_130_243 CalRequestState into Nvm if Kl15off and softreset*/				
		}
	
	//ClearBitCalRequestState(cCAL_AUTO_FINISH);	

}

/************************************************************************************************//**
 *
 * \brief  return ECU Stop Counter
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] none
 * \param [out] none
 *
 * \return	Total Number of CAr Stops
 *
 *------------------------------------------------------------------------------------------------
 */
uint8 ucGetEcuStopCntr(void)
{

  return ucEcuStopCntr;

}

/************************************************************************************************//**
 *
 * \brief  update current autolearn mode
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] none
 * \param [out] none
 *
 * 
 *
 *------------------------------------------------------------------------------------------------
 */
void UpdateFzzCurrentLearnMode(void)
{
  WAParNCfgType ucParkingState; 

  /* reset wheel allocation algo */
  // 1 -- No Learn
  // 2 -- Special Learn
  // 3 -- Complete Learn
  ucParkingState.ucWACfg = (uint8)ucGetCurrentECUParkingState(); 
  if ((ucFzzPreviousParkingState == 1) && (ucParkingState.ucWACfg == 2) && (bGetBitBetriebszustandBZ(cZO_FINISH) ||  bGetBitBetriebszustandBZ(cZO_ERROR))) // move to special leran only if complete learn has successfullly ended before
  {
    InitBZ();
    InitTelStatInfoAtModeChange();
    WAInit(&ucParkingState);
  }else if((ucFzzPreviousParkingState == 2) && (ucParkingState.ucWACfg == 3))
  {
    InitBZ();
    //InitTelStatInfo();
    InitTelStatInfoAtModeChange();
    WAInit(&ucParkingState);
    //InitTxBusMsg();
  }
  ucFzzPreviousParkingState = ucParkingState.ucWACfg;
  //---------------------------------------
  if ( bGetBitBetriebszustandBZ(cZO_FINISH) ||  bGetBitBetriebszustandBZ(cZO_ERROR)) // autolocation is over yet
  {
    ucFzzCurrentLearnMode = cNoLearn;
  }
  else // autolocation is running
  {
    ucFzzCurrentLearnMode = ucGetLearnMode(); //learn mode from walloc module
  }
}

/************************************************************************************************//**
 *
 * \brief  return Autolearn current learn  mode
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] none
 * \param [out] none
 *
 * \return	Tcurrent autolearn mode
 *
 *------------------------------------------------------------------------------------------------
 */
uint8 ucGetFzzCurrentLearnMode(void)
{
  return ucFzzCurrentLearnMode;
}



/************************************************************************************************//**
 *
 * \brief  set Can Bus Off sTate
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] ucState
 * \param [out] ucEcuBusOffState
 *
 * \return	void
 *
 *------------------------------------------------------------------------------------------------
 */
void UpdateFzzDTcEnableCond(void)
{
  EcuM_StateType  EcuM_State;            /* EcuM RUN mode state */

  /* check EcuM state */
  (void)EcuM_GetState(&EcuM_State);
  if( EcuM_State == ECUM_STATE_APP_RUN )
  {
    UpdateFzzAllSignalImplausibleCntr();
    UpdateFzzAllSignalDTCSetCond();

    //---------enable / disable DTCs according to pre defined conditions---------------------------------------
    if(bGetFzzSignalTimeOutState(cFZZ_CANSM_BUSOFF_Network))
    {
      //Dem_SetEnableCondition( DEM_SL_POWER_DISTRIBUTION, TRUE);
      Dem_SetEnableCondition( DEM_SL_NETWORK_COMM_WITH_CLAMP15, FALSE);
      Dem_SetEnableCondition( DEM_SL_NETWORK_COMM_NO_CLAMP15, FALSE);
    }
    else
    {
      if(!bGetBitFahrzeugzustandFZZ( cKL_15_EIN ))
      {
			  Dem_SetEnableCondition( DEM_SL_POWER_DISTRIBUTION, FALSE); /* CRS_1211_050_015*/
        //Dem_SetEnableCondition( DEM_SL_POWER_DISTRIBUTION, TRUE);
        Dem_SetEnableCondition( DEM_SL_NETWORK_COMM_WITH_CLAMP15, FALSE);
        Dem_SetEnableCondition( DEM_SL_NETWORK_COMM_NO_CLAMP15, TRUE);
      }
      else
      {
			  Dem_SetEnableCondition( DEM_SL_POWER_DISTRIBUTION, TRUE);   /* CRS_1211_050_015*/   
			  //Dem_SetEnableCondition( DEM_SL_POWER_DISTRIBUTION, FALSE);
        Dem_SetEnableCondition( DEM_SL_NETWORK_COMM_WITH_CLAMP15, TRUE);
        Dem_SetEnableCondition( DEM_SL_NETWORK_COMM_NO_CLAMP15, FALSE);
      }
    }
    UpdateFzzAllSignalDTCSetCond();
  }
}


/************************************************************************************************//**
 *
 * \brief  init signal monitoring counters
 *
 *-----------------------------------------------------------------------------------------------
 *
 * \param [out] ucEcuCanBusOffState
 * \param [out] ucTimeSinceLastKL15On
 * \param [out] ucTimeSinceLastEngStart
 * \param [out] ucTimeSnaWhlplsFL
 * \param [out] ucTimeSnaWhlplsFR
 * \param [out] ucTimeSnaWhlplsRL
 * \param [out] ucTimeSnaWhlplsRR
 * \param [out] ucTimeSnavehSpeed
 * \param [out] ucTimeSnaAirTempOut
 * \param [out] ucTimeSnaIcA3TpmActiv
 * \param [out] ucTimeSnaTractSystem
 *
 * \return	none
 *
*------------------------------------------------------------------------------------------------
 */
void InitFzzCanSignalMonitoring(void)
{
  ucTimeSinceLastKL15On = 0; // counter since last ignition start in sec
  ucTimeSinceLastEngStart = cMIN_TIME_AFTER_ENG_START; // counter since last engine start in sec, counter is reset only after detecting engine start

  ucTimeSnaWhlplsFL = 0; // counter for wheel pulse counter signal not available
  ucTimeSnaWhlplsFR = 0; // counter for wheel pulse counter signal not available
  ucTimeSnaWhlplsRL = 0; // counter for wheel pulse counter signal not available
  ucTimeSnaWhlplsRR = 0; // counter for wheel pulse counter signal not available
  ucTimeSnaTractSystem = 0;  // counter for traction system signal not available
  ucTimeSnavehSpeed = 0; // counter for vehicle speed signal not available
  ucTimeSnaAirTempOut = 0; // counter for outside air temperature not available
  ucTimeSnaIcA3TpmActiv = 0; // counter for IC_A3_TPM_Activ signal not available

  ushFzzCanSignalImplauState = 0xFFFF;
  ushFzzCanSignalTimeOutState = 0xFFFF; //default
}


/************************************************************************************************//**
 *
 * \brief  sets signal state to implausible
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] ushBitMask Signal mask
 * \param [out] ushFzzCanSignalImplauState Signal implausibilty state variable
 *
 * \return  none
 *
*------------------------------------------------------------------------------------------------
 */
void SetFzzSignalImplauState(uint16 ushBitMask)
{
    ushFzzCanSignalImplauState |= ushBitMask;

}

/************************************************************************************************//**
 *
 * \brief  gets current implausibilty state of signals
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] ushBitMask Siganls mask
 * \param [in] ushFzzCanSignalImplauState Signal implausibilty state variable
 *
 * \return	TRUE: signals currently implausible, FALSE; signals currently plausible
 *
*------------------------------------------------------------------------------------------------
 */
boolean bGetFzzCanSignalImplausibleState(uint16 ushBitMask)
{
  return (boolean) ((ushBitMask & ushFzzCanSignalImplauState)!= 0);
}

/************************************************************************************************//**
 *
 * \brief  updates DTC enable conditions variable and counters i 1s cycle
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] none
 * \param [inout] ucTimeSnaWhlplsFL
 * \param [inout] ucTimeSnaWhlplsFR
 * \param [inout] ucTimeSnaWhlplsRL
 * \param [inout] ucTimeSnaWhlplsRR
 * \param [inout] ucTimeSnavehSpeed
 * \param [inout] ucTimeSnaAirTempOut
 * \param [inout] ucTimeSnaIcA3TpmActiv
 * \param [inout] ucTimeSnaTractSystem
 *
 * \return	none
 *
*------------------------------------------------------------------------------------------------
 */
static void UpdateFzzAllSignalDTCSetCond(void)
{
// Funtion is called in 1s cycle
  if( (ucTimeSnaWhlplsFL==cMIN_TIME_SNA_ERROR) && (ushVehicleSpeed>5) && bGetBitFahrzeugzustandFZZ( cKL_15_EIN ) && !bGetFzzSignalTimeOutState(cFZZ_WHLPLS_CNT_TIMEOUT))
  {
    Dem_SetEventStatus( Dem_DTC_0xd41208, DEM_EVENT_STATUS_FAILED); //set DTC
  }
  else
  {
    //Dem_SetEventStatus( Dem_DTC_0xd41208, DEM_EVENT_STATUS_PASSED); //set DTC
  }
  //-----------------------wheel sensor FR ----------------------------------------/
  if( (ucTimeSnaWhlplsFR==cMIN_TIME_SNA_ERROR) && (ushVehicleSpeed>5) && bGetBitFahrzeugzustandFZZ( cKL_15_EIN ) && !bGetFzzSignalTimeOutState(cFZZ_WHLPLS_CNT_TIMEOUT))
  {
    Dem_SetEventStatus( Dem_DTC_0xd41308, DEM_EVENT_STATUS_FAILED);     //set DTC code 
  }else
  {
    //Dem_SetEventStatus( Dem_DTC_0xd41308, DEM_EVENT_STATUS_PASSED);     //set DTC code 
  }
  //-----------------------wheel sensor RL ----------------------------------------/
  if( (ucTimeSnaWhlplsRL==cMIN_TIME_SNA_ERROR) && (ushVehicleSpeed>5) && bGetBitFahrzeugzustandFZZ( cKL_15_EIN ) && !bGetFzzSignalTimeOutState(cFZZ_WHLPLS_CNT_TIMEOUT))
  {
      Dem_SetEventStatus( Dem_DTC_0xd41008, DEM_EVENT_STATUS_FAILED);     //set DTC code 

  }else
  {
    //Dem_SetEventStatus( Dem_DTC_0xd41008, DEM_EVENT_STATUS_PASSED);     //set DTC code 

  }
  //-----------------------wheel sensor RR ----------------------------------------/
  if( (ucTimeSnaWhlplsRR==cMIN_TIME_SNA_ERROR) && (ushVehicleSpeed>5) && bGetBitFahrzeugzustandFZZ( cKL_15_EIN ) && !bGetFzzSignalTimeOutState(cFZZ_WHLPLS_CNT_TIMEOUT))
  {
    Dem_SetEventStatus( Dem_DTC_0xd41108, DEM_EVENT_STATUS_FAILED);     //set DTC code 
  }else
  { 
    //Dem_SetEventStatus( Dem_DTC_0xd41108, DEM_EVENT_STATUS_PASSED);     //set DTC code 
  }
  //-----------------------Instrument cluster----------------------------------------/
  if( ((ucTimeSnavehSpeed==cMIN_TIME_SNA_ERROR) || (ucTimeSnaAirTempOut==cMIN_TIME_SNA_ERROR) || (ucTimeSnaIcA3TpmActiv==cMIN_TIME_SNA_ERROR)) && bFzzSignalFailureMonitoringActiv() && (!bGetFzzSignalTimeOutState(cFZZ_CANSM_BUSOFF_Network)) )
  {
    Dem_SetEventStatus( Dem_DTC_0xc42308, DEM_EVENT_STATUS_FAILED);     //set DTC code
  }
  else
  {
    //Dem_SetEventStatus( Dem_DTC_0xc42308, DEM_EVENT_STATUS_PASSED);     //set DTC code
  }
  
  //-----------------------Traction System ----------------------------------------/
  if( (ucTimeSnaTractSystem==cMIN_TIME_SNA_ERROR) && bFzzSignalFailureMonitoringActiv() && (!bGetFzzSignalTimeOutState(cFZZ_CANSM_BUSOFF_Network)) && !bGetFzzSignalTimeOutState(cFZZ_WHLPLS_CNT_TIMEOUT))
  {
      Dem_SetEventStatus( Dem_DTC_0xc41608, DEM_EVENT_STATUS_FAILED);     //set DTC code 
  }
  else
  {
    //Dem_SetEventStatus( Dem_DTC_0xc41608, DEM_EVENT_STATUS_PASSED);     //set DTC code 
  }
  //-----------------------------time out traction system-------------------------------/
  if (bGetFzzSignalTimeOutState(cFZZ_WHLPLS_CNT_TIMEOUT) && bFzzSignalFailureMonitoringActiv())
  {
    Dem_SetEventStatus( Dem_DTC_0xc12287, DEM_EVENT_STATUS_FAILED);     //set DTC code
  }
  else
  {
    //Dem_SetEventStatus( Dem_DTC_0xc12287, DEM_EVENT_STATUS_PASSED);     //set DTC code
  }
  // ---------------------------time out ignition--------------------------------------/
  if (bGetFzzSignalTimeOutState(cFZZ_IGN_VEH_STAT_TIMEOUT))
  {
    Dem_SetEventStatus( Dem_DTC_0xc16887, DEM_EVENT_STATUS_FAILED);     //set DTC code
  }
  else
  {
    //Dem_SetEventStatus( Dem_DTC_0xc16887, DEM_EVENT_STATUS_PASSED);     //set DTC code
  }

   // ---------------------------time out cFZZ_PN14_STAT_TIMEOUT--------------------------------------/
  if(bGetFzzSignalTimeOutState(cFZZ_PN14_STAT_TIMEOUT) && bFzzSignalFailureMonitoringActiv())
  {
    Dem_SetEventStatus( Dem_DTC_0xc14187, DEM_EVENT_STATUS_FAILED);     //set DTC code 
  }
  else
  {
    //Dem_SetEventStatus( Dem_DTC_0xc14187, DEM_EVENT_STATUS_PASSED);     //set DTC code 
  }

  // time out Basic info
  if( (bGetFzzSignalTimeOutState(cFZZ_IC_BASIC_INFO_TIMEOUT) || bGetFzzSignalTimeOutState(cFZZ_IC_DATE_TIME_TIMEOUT) || bGetFzzSignalTimeOutState(cFZZ_IC_SETTINGS_TIMEOUT))&& bFzzSignalFailureMonitoringActiv())
  {
    Dem_SetEventStatus( Dem_DTC_0xc15587, DEM_EVENT_STATUS_FAILED);     //set DTC code 
  }
  else
  {
    //Dem_SetEventStatus( Dem_DTC_0xc15587, DEM_EVENT_STATUS_PASSED);     //set DTC code 
  }

    // time out 
  if( ( bGetFzzSignalTimeOutState(cFZZ_ENG_CTRL_TIMEOUT) )&& bFzzSignalFailureMonitoringActiv())
  {
    Dem_SetEventStatus( Dem_DTC_0xc10087, DEM_EVENT_STATUS_FAILED);     //set DTC code 
  }
  else
  {
    //Dem_SetEventStatus( Dem_DTC_0xc10087, DEM_EVENT_STATUS_PASSED);     //set DTC code 
  }

  if(bGetFzzSignalTimeOutState(cFZZ_CANSM_BUSOFF_Network))
  {
    Dem_SetEventStatus( Dem_CANSM_E_BUSOFF_Network_0, DEM_EVENT_STATUS_FAILED);     //set DTC code 
  }
  else
  {
    Dem_SetEventStatus( Dem_CANSM_E_BUSOFF_Network_0, DEM_EVENT_STATUS_PASSED);     //set DTC code 
  }
}

/************************************************************************************************//**
 *
 * \brief  updates DTC Implausible counters in 1s cycle
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] none
 * \param [inout] ucTimeSinceLastKL15On
 * \param [inout] ucTimeSinceLastEngStart
 * \param [inout] ucTimeSnaWhlplsFL
 * \param [inout] ucTimeSnaWhlplsFR
 * \param [inout] ucTimeSnaWhlplsRL
 * \param [inout] ucTimeSnaWhlplsRR
 * \param [inout] ucTimeSnavehSpeed
 * \param [inout] ucTimeSnaAirTempOut
 * \param [inout] ucTimeSnaIcA3TpmActiv
 * \param [inout] ucTimeSnaTractSystem
 *
 * \return	none
 *
*------------------------------------------------------------------------------------------------
 */
static void UpdateFzzAllSignalImplausibleCntr(void)
{
  //10secs after last Ignition_ON, CAN Bus active, CAN physically connected, 10 secs after last engine start
  if( (ucIgnOnStartProc == 1) && (ucTimeSinceLastKL15On < cMIN_TIME_AFTER_IGN_START) )
  {
    ucTimeSinceLastKL15On++;
  }

  if( (bGetBitFahrzeugzustandFZZ( cENG_STARTING ) == FALSE) && (ucTimeSinceLastEngStart<cMIN_TIME_AFTER_ENG_START) )
  {
    ucTimeSinceLastEngStart++;
  }

  if (bFzzSignalFailureMonitoringActiv()) // check condition for monitoring signal timeoout
  {
    SetBitFahrzeugzustandFZZ(cFAILURE_MONITORING);
  }
  else
  {
    ClearBitFahrzeugzustandFZZ(cFAILURE_MONITORING);
  }
  //-----------------------wheel sensor FL ----------------------------------------/
  if( bGetFzzCanSignalImplausibleState(cFZZ_WHLPLS_FL_IMPLAU) && (ucTimeSnaWhlplsFL < cMIN_TIME_SNA_ERROR) )
  {
    ucTimeSnaWhlplsFL++;
  }
  
  //-----------------------wheel sensor FR ----------------------------------------/
  if( bGetFzzCanSignalImplausibleState(cFZZ_WHLPLS_FR_IMPLAU) && (ucTimeSnaWhlplsFR < cMIN_TIME_SNA_ERROR))
  {
    ucTimeSnaWhlplsFR++;
  }

  //-----------------------wheel sensor RL ----------------------------------------/
  if( bGetFzzCanSignalImplausibleState(cFZZ_WHLPLS_RL_IMPLAU) && (ucTimeSnaWhlplsRL < cMIN_TIME_SNA_ERROR) )
  {
    ucTimeSnaWhlplsRL++;
  }

  //-----------------------wheel sensor RR ----------------------------------------/
  if( bGetFzzCanSignalImplausibleState(cFZZ_WHLPLS_RR_IMPLAU) && (ucTimeSnaWhlplsRR < cMIN_TIME_SNA_ERROR) )
  {
    ucTimeSnaWhlplsRR++;
  }

  //-----------------------vehicle speed ----------------------------------------/
  if( bGetFzzCanSignalImplausibleState(cFZZ_VEH_SPEED_IMPLAU) && (ucTimeSnavehSpeed < cMIN_TIME_SNA_ERROR) )
  {
    ucTimeSnavehSpeed ++;
  }

  //-----------------------air temp out ----------------------------------------/
  if( bGetFzzCanSignalImplausibleState(cFZZ_AIRTEMP_OUT_IMPLAU) && (ucTimeSnaAirTempOut < cMIN_TIME_SNA_ERROR) )
  {
    ucTimeSnaAirTempOut ++;
  }

  //-----------------------TPM Actv----------------------------------------/
  if( bGetFzzCanSignalImplausibleState(cFZZ_IC_A3_TPM_ACTV_IMPLAU) && (ucTimeSnaIcA3TpmActiv < cMIN_TIME_SNA_ERROR) )
  {
    ucTimeSnaIcA3TpmActiv ++;
  }

  //-----------------------traction system ----------------------------------------/
  if( bGetFzzCanSignalImplausibleState(cFZZ_TRACTION_SYSTEM_IMPLAU) && (ucTimeSnaTractSystem < cMIN_TIME_SNA_ERROR) )
  {
    ucTimeSnaTractSystem ++;
  }

}


/************************************************************************************************//**
 *
 * \brief   reset implausibility counters
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] ushBitMask signal mask
 * \param [out] ushFzzCanSignalImplauState 
 *
 * \return	none
 *
 *------------------------------------------------------------------------------------------------
 */
void ClearFzzSignalUnplausibleCntr(uint16 ushBitMask)
{  
  
  if ( (ushBitMask & cFZZ_WHLPLS_FR_IMPLAU) > 0 )
  {
    ucTimeSnaWhlplsFR = 0; // implausible state has been cleared
  }
  if ( (ushBitMask & cFZZ_WHLPLS_FL_IMPLAU) > 0 )
  {
    ucTimeSnaWhlplsFL = 0; // implausible state has been cleared
  }
  if ( (ushBitMask & cFZZ_WHLPLS_RL_IMPLAU) > 0 )
  {
    ucTimeSnaWhlplsRL = 0; // implausible state has been cleared    
  }
  if ( (ushBitMask & cFZZ_WHLPLS_RR_IMPLAU) > 0 )
  {
    ucTimeSnaWhlplsRR = 0; // implausible state has been cleared
  }
  
  //--------------------------------------------------------------------------
  if ( (ushBitMask & cFZZ_VEH_SPEED_IMPLAU) > 0 ) 
  {
    ucTimeSnavehSpeed = 0; // implausible state has been cleared
  }
  if ( (ushBitMask & cFZZ_AIRTEMP_OUT_IMPLAU) > 0 ) 
  {
    ucTimeSnaAirTempOut = 0; // implausible state has been cleared
  }
  if ( (ushBitMask & cFZZ_IC_A3_TPM_ACTV_IMPLAU) > 0 ) 
  {
    ucTimeSnaIcA3TpmActiv = 0; // implausible state has been cleared
  }
  //-------------------------------------------------------------------------
  if ( (ushBitMask & cFZZ_TRACTION_SYSTEM_IMPLAU) > 0 )
  {
    ucTimeSnaTractSystem = 0; // implausible state has been cleared
  }
}

/************************************************************************************************//**
 *
 * \brief  clear signal implausibility flag and reset implausibility counters
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] ushBitMask signal mask
 * \param [out] ushFzzCanSignalImplauState 
 *
 * \return	none
 *
 *------------------------------------------------------------------------------------------------
 */
void ClearFzzSignalUnplausibleState(uint16 ushBitMask)
{
  ushFzzCanSignalImplauState &= ~ushBitMask;

  if (!bGetFzzCanSignalImplausibleState(cFZZ_WHLPLS_FR_IMPLAU))
  {
    ucTimeSnaWhlplsFR = 0; // implausible state has been cleared
    Dem_SetEventStatus( Dem_DTC_0xd41308, DEM_EVENT_STATUS_PASSED); //set DTC
  }
  if (!bGetFzzCanSignalImplausibleState(cFZZ_WHLPLS_FL_IMPLAU))
  {
    ucTimeSnaWhlplsFL = 0; // implausible state has been cleared
    Dem_SetEventStatus( Dem_DTC_0xd41208, DEM_EVENT_STATUS_PASSED); //set DTC
  }
  if (!bGetFzzCanSignalImplausibleState(cFZZ_WHLPLS_RL_IMPLAU))
  {
    ucTimeSnaWhlplsRL = 0; // implausible state has been cleared    
    Dem_SetEventStatus( Dem_DTC_0xd41008, DEM_EVENT_STATUS_PASSED); //set DTC
  }
  if (!bGetFzzCanSignalImplausibleState(cFZZ_WHLPLS_RR_IMPLAU))
  {
    ucTimeSnaWhlplsRR = 0; // implausible state has been cleared
    Dem_SetEventStatus( Dem_DTC_0xd41108, DEM_EVENT_STATUS_PASSED); //set DTC
  }
  
  //--------------------------------------------------------------------------
  if (!bGetFzzCanSignalImplausibleState(cFZZ_VEH_SPEED_IMPLAU) )
  {
    ucTimeSnavehSpeed = 0; // implausible state has been cleared
  }
  if (!bGetFzzCanSignalImplausibleState(cFZZ_AIRTEMP_OUT_IMPLAU) )
  {
    ucTimeSnaAirTempOut = 0; // implausible state has been cleared
  }
  if (!bGetFzzCanSignalImplausibleState(cFZZ_IC_A3_TPM_ACTV_IMPLAU) )
  {
    ucTimeSnaIcA3TpmActiv = 0; // implausible state has been cleared
  }
  if( (!bGetFzzCanSignalImplausibleState(cFZZ_VEH_SPEED_IMPLAU)) && (!bGetFzzCanSignalImplausibleState(cFZZ_AIRTEMP_OUT_IMPLAU)) && (!bGetFzzCanSignalImplausibleState(cFZZ_IC_A3_TPM_ACTV_IMPLAU)) )
  {
    Dem_SetEventStatus( Dem_DTC_0xc42308, DEM_EVENT_STATUS_PASSED); //set DTC
  }
  //-------------------------------------------------------------------------
  if (!bGetFzzCanSignalImplausibleState(cFZZ_TRACTION_SYSTEM_IMPLAU) )
  {
    ucTimeSnaTractSystem = 0; // implausible state has been cleared
    Dem_SetEventStatus( Dem_DTC_0xc41608, DEM_EVENT_STATUS_PASSED); //set DTC
  }
}

/************************************************************************************************//**
 *
 * \brief  returns signal failure monitoring state
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] ucTimeSinceLastEngStart
 * \param [in] ucTimeSinceLastKL15On
 * \param[out] none
 * \return	TRUE Signal failure monitoring active FALSE Signal failure monitoring not active
 *
 *------------------------------------------------------------------------------------------------
 */
static boolean bFzzSignalFailureMonitoringActiv(void)
{
  return ( (ucTimeSinceLastEngStart == cMIN_TIME_AFTER_ENG_START) && (ucTimeSinceLastKL15On == cMIN_TIME_AFTER_IGN_START) );
}

/************************************************************************************************//**
 *
 * \brief  clear signal timeout flag
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] ushBitMask signal mask
 * \param [out] ushFzzCanSignalImplauState 
 *
 * \return	none
 *
 *------------------------------------------------------------------------------------------------
 */
void ClearFzzSignalTimeOutState(uint16 ushBitMask)
{
  ushFzzCanSignalTimeOutState &= ~ushBitMask;

  //-----------------------------time out traction system-------------------------------/
  if (!bGetFzzSignalTimeOutState(cFZZ_WHLPLS_CNT_TIMEOUT))
  {
    Dem_SetEventStatus( Dem_DTC_0xc12287, DEM_EVENT_STATUS_PASSED);     //set DTC code
  }

  // ---------------------------time out ignition--------------------------------------/
  if (!bGetFzzSignalTimeOutState(cFZZ_IGN_VEH_STAT_TIMEOUT))
  {
    Dem_SetEventStatus( Dem_DTC_0xc16887, DEM_EVENT_STATUS_PASSED);     //set DTC code
  }

   // ---------------------------time out cFZZ_PN14_STAT_TIMEOUT--------------------------------------/
  if(!bGetFzzSignalTimeOutState(cFZZ_PN14_STAT_TIMEOUT) )
  {
    Dem_SetEventStatus( Dem_DTC_0xc14187, DEM_EVENT_STATUS_PASSED);     //set DTC code 
  }

  // time out Basic info
  if( !bGetFzzSignalTimeOutState(cFZZ_IC_BASIC_INFO_TIMEOUT) && !bGetFzzSignalTimeOutState(cFZZ_IC_DATE_TIME_TIMEOUT) && !bGetFzzSignalTimeOutState(cFZZ_IC_SETTINGS_TIMEOUT) )
  {
    Dem_SetEventStatus( Dem_DTC_0xc15587, DEM_EVENT_STATUS_PASSED);     //set DTC code 
  }

    // time out 
  if( !bGetFzzSignalTimeOutState(cFZZ_ENG_CTRL_TIMEOUT) )
  {
    Dem_SetEventStatus( Dem_DTC_0xc10087, DEM_EVENT_STATUS_PASSED);     //set DTC code 
  }

}

/************************************************************************************************//**
 *
 * \brief  sets signal state to timeout
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] ushBitMask Signal mask
 * \param [out] ushFzzCanSignalImplauState Signal implausibilty state variable
 *
 * \return  none
 *
*------------------------------------------------------------------------------------------------
 */
void SetFzzSignalTimeOutState(uint16 ushBitMask)
{
    ushFzzCanSignalTimeOutState |= ushBitMask;

}
/************************************************************************************************//**
 *
 * \brief  set fzz state 4MM Message Memory 
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] state [TRUE] or [FALSE]
 * \param [out] 
 *
 * \return  none
 *
*------------------------------------------------------------------------------------------------
 */
void SetFzzState4MM(uint8 state)
{
	ucFzzState4MessageMemory=state;
}
/************************************************************************************************//**
 *
 * \brief  set Global Warn state 4MM Message Memory 
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] state [TRUE] or [FALSE]
 * \param [out] 
 *
 * \return  none
 *
*------------------------------------------------------------------------------------------------
 */
void SetGlobWarnState4MM(uint8 state)
{
	ucGlobWarnState4MessageMemory=state;
}
/************************************************************************************************//**
 *
 * \brief  check whether DTC enable conditions flag is set
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] ushBitMask signal mask
 * \param [out] ushFzzCanSignalTimeOutState 
 *
 * \return	TRUE: signal timeout, FALSE no signal timeout
 *
 *------------------------------------------------------------------------------------------------
 */
static boolean bGetFzzSignalTimeOutState(uint16 ushBitMask)
{
   return (boolean) ((ushFzzCanSignalTimeOutState & ushBitMask) != 0 );
}

/************************************************************************************************//**
 *
  * \brief  set fzz state 4MM Message Memory 
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] state [TRUE] or [FALSE]
 * \param [out] 
 *
 * \return  none
 *
*------------------------------------------------------------------------------------------------
 */
uint8 GetFzzState4MM(void)
{
	return ucFzzState4MessageMemory;
}


/************************************************************************************************//**
 *
 * \brief  set Global Warn state 4MM Message Memory 
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] state [TRUE] or [FALSE]
 * \param [out] 
 *
 * \return  none
 *
*------------------------------------------------------------------------------------------------
 */
uint8 GetGlobWarnState4MM(void)
{
	return ucGlobWarnState4MessageMemory;
}

/************************************************************************************************//**
 *
 * \brief  check whether at least 1 wheel sensor DTC is set
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] ushBitMask signal mask
 * \param [out] ushFzzCanSignalTimeOutState 
 *
 * \return	TRUE: signal timeout, FALSE no signal timeout
 *
 *------------------------------------------------------------------------------------------------
 */
uint8  bGetABSSignalDTCActive(void)
{
  uint8 ucEventStatus0, ucEventStatus1, ucEventStatus2, ucEventStatus3, ucEventStatus4;

  Dem_GetEventStatus(Dem_DTC_0xc12287, &ucEventStatus0); // whlpls timeout
  Dem_GetEventStatus(Dem_DTC_0xd41008, &ucEventStatus1); // whlpls implausible
  Dem_GetEventStatus(Dem_DTC_0xd41108, &ucEventStatus2); // whlpls implausible
  Dem_GetEventStatus(Dem_DTC_0xd41208, &ucEventStatus3); // whlpls implausible
  Dem_GetEventStatus(Dem_DTC_0xd41208, &ucEventStatus4); // whlpls implausible
  
  if ((ucEventStatus0 == DEM_EVENT_STATUS_PASSED) && 
    (ucEventStatus1 == DEM_EVENT_STATUS_PASSED) &&
    (ucEventStatus2 == DEM_EVENT_STATUS_PASSED) &&
    (ucEventStatus3 == DEM_EVENT_STATUS_PASSED) &&
    (ucEventStatus4 == DEM_EVENT_STATUS_PASSED))
  {
    return (uint8)FALSE;
  }
  else
  {
    return (uint8)TRUE;
  }
}

/************************************************************************************************//**
 *
 * \brief  check whether at Kl30 highvoltage DTC is set
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] non
 * \param [out] DTC state 
 *
 * \return	TRUE: DTC activ, FALSE; DTC Passed
 * \CRS_1211_050_050
 *------------------------------------------------------------------------------------------------
 */
uint8  bGetKl30HighDTCActive(void)
{
  uint8 ucEventStatus0; 

	Dem_GetEventStatus(Dem_DTC_0xa10e00, &ucEventStatus0); /*0xa10e00 Kl.30 �berspannung!*/
  
  if (ucEventStatus0 == DEM_EVENT_STATUS_PASSED) 
  {
    return (uint8)FALSE;
  }
  else
  {
    return (uint8)TRUE;
  }
}

/************************************************************************************************//**
 *
 * \brief  check whether at Kl30 lowvoltage DTC is set
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] non
 * \param [out] DTC state 
 *
 * \return	TRUE: DTC activ, FALSE; DTC Passed
 * �Dem_DTC_0xa10d00 Kl30 lowvoltage CRS_1211_050_050
 *------------------------------------------------------------------------------------------------
 */
uint8  bGetKl30LowDTCActive(void)
{
  uint8 ucEventStatus0; 

  Dem_GetEventStatus(Dem_DTC_0xa10d00, &ucEventStatus0); /*0xa10d00 KL.30 Unterspannung*/
 
  if (ucEventStatus0 == DEM_EVENT_STATUS_PASSED) 
  {
    return (uint8)FALSE;
  }
  else
  {
    return (uint8)TRUE;
  }
}


/************************************************************************************************//**
 *
 * \brief  check whether at CAN message overvoltage DTC is set
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] non
 * \param [out] DTC state 
 *
 * \return	TRUE: DTC activ, FALSE; DTC Passed
 * \CRS_1211_050_050
 *------------------------------------------------------------------------------------------------
 */
uint8  bGetPN14SupbatHighDTCActive(void)
{
  uint8 ucEventStatus0; 

	Dem_GetEventStatus(Dem_DTC_0xa10b00, &ucEventStatus0); /*0xa10b00 CAN Botschaft: �berspannung */
  
  if (ucEventStatus0 == DEM_EVENT_STATUS_PASSED) 
  {
    return (uint8)FALSE;
  }
  else
  {
    return (uint8)TRUE;
  }
}

/************************************************************************************************//**
 *
 * \brief  check whether at CAN message lowvoltage DTC is set
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] non
 * \param [out] DTC state 
 *
 * \return	TRUE: DTC activ, FALSE; DTC Passed
 * \Dem_DTC_0xa10a00 cPN14_SUPBAT_HIGH CRS_1211_050_050
 *------------------------------------------------------------------------------------------------
 */
uint8  bGetPN14SupbatLowDTCActive(void)
{
  uint8 ucEventStatus0; 

  Dem_GetEventStatus(Dem_DTC_0xa10a00, &ucEventStatus0); /*0xa10a00 CAN Botschaft: Unterspannung */
 
  if (ucEventStatus0 == DEM_EVENT_STATUS_PASSED) 
  {
    return (uint8)FALSE;
  }
  else
  {
    return (uint8)TRUE;
  }
}
