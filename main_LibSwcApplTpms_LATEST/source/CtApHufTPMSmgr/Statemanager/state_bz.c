/************************************************************************************************************
 * (c) BERU Electronics GmbH      Abteilung BES2     2008
 ************************************************************************************************************/
/************************************************************************************************************
 * Project:       Reifendruckkontrolle TSS (TSS = tyre safety system)
 *
 * $Archive: /BMW/G3kompakt/Sw/SC4/template_can/application/source/tssappl/statemanager/state_bz.c $
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
 *                         Da der Zugriff auf globale Bitstrukturen über Funktionen gekapselt ist, kann diese
 *                         Regelverletzung ohne Gefahr hingenommen werden.
 *                         Die Beseitigung dieser Regelverletzung hätte eine Erhöhung der zyklomatischen
 *                         Komplexität zur Folge.
 * MISRA-C:2004 Rule 3.1: REFERENCE - ISO-5.2.1 Character Sets
 *                        Msg(4:0288) [I] Source file '%s' has comments containing characters which are not
 *                        members of the basic source character set.
 *                        - Die Umlaute in Kommentaren sind erlaubt.
 *                        - In Variablenbezeichnungen sind keine Umlaute erlaubt.
 *                        - VSS-Steuercodes (z.B. $Archive) sind erlaubt
 *
 ************************************************************************************************************/
/************************************************************************************************************
 * Modul Modification
 * ==================
 *
 * changes in 2008
 *
 * $Log: /BMW/G3kompakt/Sw/SC4/template_can/application/source/tssappl/statemanager/state_bz.c $
 * 
 * 7     14.07.09 15:31 Rapp
 * - OIL #395: Zustandsbit der Schatten-ZOM in BZ spiegeln
 * - Korrektur bei der BZ-Grundinitialisierung durchgeführt. Das Bit
 * cER_LEARNING kann nicht aus dem Rückgabewert der WAInit() abgeleitet
 * werden, da diese Funktion nur den Zustand der ZOM-Historie zurückmeldet
 *
 * 6     11.12.08 18:51 Rapp
 * Reaktion bei ZO-Timeout korrigiert
 *
 * 5     8.12.08 16:08 Rapp
 * Status Radmanagement korrigiert (OIL#223)
 *
 * 4     5.12.08 16:06 Peter
 * OIL #236 change reset conditions for HFÜ
 *
 * 3     6.11.08 15:41 Rapp
 * In der Modulinitialisierung cWA_FINISH zurücksetzen
 *
 * 2     5.11.08 15:13 Dederer
 * Ruecksetzen aller Betriebszustandsbits bei Initialisierung des BZ
 * entfernt
 *
 * 1     17.06.08 10:43 Rapp
 * Integration "Statemanager"
 *
 ************************************************************************************************************/



/************************************************************************************************************
 *                                             include
 ************************************************************************************************************/
#include "state_bz.h"
#include "state_bzX.h"
//#include "statemanagerX.h"

//#include "calX.h"
//#include "IDOM_X.h"  // necessary for no statemanager_if.c/h is available...
//#include "errmemX.h"
#include "wallocX.h"

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



/************************************************************************************************************
 *                                       data (global) - ROM
 ************************************************************************************************************/



/************************************************************************************************************
 *                                       data (global) - RAM
 ************************************************************************************************************/



/***********************************************************************************************************
 *                                 prototype (local functions - private)
 ***********************************************************************************************************/



/***********************************************************************************************************
 *                                 prototype (local functions - public)
 ***********************************************************************************************************/



/************************************************************************************************************
 *                               prototype (external functions - interface)
 ************************************************************************************************************/
extern boolean GETbCalPminInvalidCAL( void );
extern boolean GETbCalReqCAL( void );
extern boolean GETbCalNotAck4PlausiCheckMFA( void );
extern void CheckDTCInactiveERR(void);
extern void InitIDOM(void);
extern uint8 ucGetHistoryState(void); // TODO @@GL: declare this function in WallocX.c
/************************************************************************************************************
 *                                            implementation
 ************************************************************************************************************/



/*!**********************************************************************************************************
 *\Function           void InitBZ( void )
 *
 *\Typ                public
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Purpose            initialisation routine of bz variable
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
void InitBZ( void )
{
  uint8 ucWAState;

  /*
   * Bit: cCAL_REQUEST
   */
  if( GETbCalReqCAL() == TRUE )
  {
    SetBitBetriebszustandBZ(cCAL_REQUEST);
    // for this is the single point a starting calibration is recognized in the statemanger and all tpms application modules must be controlled via the statemanager
    InitIDOM();
  }

  /*
   * Bit: cCAL_NOT_ACK 
   */
  //CRS_1211_130_299 if( GETbCalNotAck4PlausiCheckMFA() == TRUE )	/*CRS_1211_130_272*/
  //{
	//	SetBitBetriebszustandBZ( cCAL_MFD_PLAUSI_ERROR ); /* "Reifendruck korrigieren" Meldung!*/
  //}

  /*
   * Bit: cDTC_INACTIVE
   */
  (void) CheckDTCInactiveERR();

  /*
   * Aus dem BZ werden die unten aufgelisteten Bits gelöscht:
   * Bit: cER_FINISH
   * Bit: cTO_MUCH_RE
   * Bit: cER_LEARNING
   * Bit: cEIGENRAD
   * Bit: cZUGEORDNET
   * Bit: cWA_FINISH
   * Bit: cHIST_PRELOAD
   * Bit: cZO_FINISH
   * Bit: cZO_TIMEOUT
   */
  ClearBitBetriebszustandBZ( cER_FINISH | cAL_RUNNING | cEIGENRAD | cZUGEORDNET | cHIST_PRELOAD | cZO_FINISH | cZO_TIMEOUT | cZO_ERROR | cTEILZUGEORDNET | cZO_Fallback2Hist);

  /*
   * Zustand Radmanagement (Historienspeicher) in BZ spiegeln
   */
 
  ucWAState =  ucGetHistoryState();
  if( (ucWAState & cHiStateZG) == cHiStateZG )
  {
    SetBitBetriebszustandBZ( cEIGENRAD | cZUGEORDNET | cHIST_PRELOAD );
  }
  else if( (ucWAState & cHiStateER) == cHiStateER )
  {
    SetBitBetriebszustandBZ( cEIGENRAD | cHIST_PRELOAD );
  }
} /* void InitBZ( void ) */



/*!**********************************************************************************************************
 *\Function           void SetBitBetriebszustandBZ( uint16 ushBitMask )
 *
 *\Typ                public
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Purpose            Setzt Bit in Betriebszustand anhand übergebener Bitmaske.
 *                    Setzen mehrerer Bits möglich, durch Übergabe "verODERter" Bitmasken.
 *                    z.B. setBitBetriebszustand(cBIT1 | cBIT2 | cBIT3);
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
void SetBitBetriebszustandBZ( uint16 ushBitMask )
{
   ushBetriebszustand |= ushBitMask;
} /* void SetBitBetriebszustandBZ( uint16 ushBitMask ) */



/*!**********************************************************************************************************
 *\Function           void ClearBitBetriebszustandBZ( uint16 ushBitMask )
 *
 *\Typ                public
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Purpose            Löscht Bit in Betriebszustand anhand übergebener Bitmaske.
 *                    Löschen mehrerer Bits möglich, durch Übergabe "verODERter" Bitmasken.
 *                    z.B. clearBitBetriebszustand(cBIT1 | cBIT2 | cBIT3);
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\SW_Requirements    none
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Parameter          usBitMask - Bitmaske zu löschender Bits
 *
 *\Input              none
 *
 *\Output             none
 *
 *\Return             none
 *
 ************************************************************************************************************/
void ClearBitBetriebszustandBZ( uint16 ushBitMask )
{
   ushBetriebszustand &= ~ushBitMask;
} /* void ClearBitBetriebszustandBZ( uint16 ushBitMask ) */



/*!**********************************************************************************************************
 *\Function           boolean bGetBitBetriebszustandBZ( uint16 ushBitMask )
 *                    uint16 ushGetBetriebszustandBZ( uint16 ushBitMask )
 *
 *\Typ                public
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Purpose            Liefert Bitzustand des anhand der übergebenen Bitmaske selektierten Bit
 *                    in Betriebszustand.
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
boolean bGetBitBetriebszustandBZ( uint16 ushBitMask )
{
   return (boolean) ((ushBetriebszustand & ushBitMask) != 0 );
} /* boolean bGetBitBetriebszustandBZ( uint16 ushBitMask ) */



uint16 ushGetBetriebszustandBZ( uint16 ushBitMask )
{
   return (ushBetriebszustand & ushBitMask);
} /* uint16 ushGetBetriebszustandBZ( uint16 ushBitMask ) */

uint8 ucGetBetriebszustandHByte(void)
{
return ((uint8) (ushBetriebszustand >>8));
} /* uint16 ushGetBetriebszustandBZ( uint16 ushBitMask ) */


uint8 ucGetBetriebszustandLByte(void)
{
return (( uint8) (ushBetriebszustand & 0x00FF ));
} /* uint16 ushGetBetriebszustandBZ( uint16 ushBitMask ) */



