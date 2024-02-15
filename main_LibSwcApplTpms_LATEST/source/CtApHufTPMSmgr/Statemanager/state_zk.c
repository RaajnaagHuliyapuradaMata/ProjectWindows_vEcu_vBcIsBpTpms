/************************************************************************************************************
 * (c) BERU Electronics GmbH      Abteilung BES2     2008
 ************************************************************************************************************/
/************************************************************************************************************
 * Project:       Reifendruckkontrolle TSS (TSS = tyre safety system)
 *
 * $Archive: /BMW/G3kompakt/Sw/SC4/template_can/application/source/tssappl/statemanager/state_zk.c $
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
 * $Log: /BMW/G3kompakt/Sw/SC4/template_can/application/source/tssappl/statemanager/state_zk.c $
 * 
 * 4     13.03.09 17:11 Rapp
 * Funktion SetCalNotAckZK() hinzugefügt (OIL #361)
 *
 * 3     26.09.08 14:19 Peter
 * interface function 4 setting "pos changed bits" with WP as parameter
 *
 * 2     27.06.08 10:04 Rapp
 * alle Bitfelder bei der initialisierung zurücksetzen
 *
 * 1     17.06.08 10:43 Rapp
 * Integration "Statemanager"
 *
 ************************************************************************************************************/



/************************************************************************************************************
 *                                             include
 ************************************************************************************************************/
#include "state_zk.h"
//#include "statemanagerX.h"
//#include "calX.h"
#include "state_zkX.h"



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

/************************************************************************************************************
 *                                            implementation
 ************************************************************************************************************/



/*!**********************************************************************************************************
 *\Function           void InitZK( void )
 *
 *\Typ                public
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Purpose            initialisation of this module
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
void InitZK( void )
{
  ClearBitZustandskennungZK( cZK_ALLE_BITS );

  SetCalNotAckZK();           // CalNotAck in ZK spiegeln
} /* void InitZK( void ) */



/*!**********************************************************************************************************
 *\Function           void SetBitZustandskennungZK( uint16 ushBitMask )
 *
 *\Typ                public
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Purpose            Setzt Bit in Zustandskennung anhand übergebener Bitmaske.
 *                    Setzen mehrerer Bits möglich, durch Übergabe "verODERter" Bitmasken.
 *                    z.B. setBitZustandskennung(cBIT1 | cBIT2 | cBIT3);
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
void SetBitZustandskennungZK( uint16 ushBitMask )
{
   ushZustandskennung |= ushBitMask;
} /* void SetBitZustandskennungZK( uint16 ushBitMask ) */



/*!**********************************************************************************************************
 *\Function           void ClearBitZustandskennungZK( uint16 ushBitMask )
 *
 *\Typ                public
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Purpose            Löscht Bit in Zustandskennung anhand übergebener Bitmaske.
 *                    Löschen mehrerer Bits möglich, durch Übergabe "verODERter" Bitmasken.
 *                    z.B. clearBitZustandskennung(cBIT1 | cBIT2 | cBIT3);
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
void ClearBitZustandskennungZK( uint16 ushBitMask )
{
   ushZustandskennung &= ~ushBitMask;
} /* void ClearBitZustandskennungZK( uint16 ushBitMask ) */



/*!**********************************************************************************************************
 *\Function           boolean bGetBitZustandskennungZK( uint16 ushBitMask )
 *                    uint16 ushGetZustandskennungZK( uint16 ushBitMask )
 *
 *\Typ                public
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Purpose            Liefert Bitzustand des anhand der übergebenen Bitmaske selektierten Bit
 *                    in Zustandskennung.
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
boolean bGetBitZustandskennungZK( uint16 ushBitMask )
{
   return (boolean) ((ushZustandskennung & ushBitMask) != 0 );
} /* boolean bGetBitZustandskennungZK( uint16 ushBitMask ) */



uint16 ushGetZustandskennungZK( uint16 ushBitMask )
{
   return (ushZustandskennung & ushBitMask);
} /* uint16 ushGetZustandskennungZK( uint16 ushBitMask ) */

/*!**********************************************************************************************************
 *\Function           s.b.
 *
 *
 *\Typ                public
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Purpose            set WP changed bits in ZK
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\SW_Requirements    none
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Parameter          WheelPosition (0,1,2,3 = FL .. RR)
 *
 *\Input              none
 *
 *\Output             none
 *
 *\Return             none
 *
 ************************************************************************************************************/

void SetChangedBit4WP( uint8 ucWP)
{

  switch (ucWP)
  {
    case (uint8) 0:
    {
      ushZustandskennung |= cPOS_CHANGED_VL;
      break;
    }
    case (uint8) 1:
    {
      ushZustandskennung |= cPOS_CHANGED_VR;
      break;
    }
    case (uint8) 2:
    {
      ushZustandskennung |= cPOS_CHANGED_HL;
      break;
    }
    case (uint8) 3:
    {
      ushZustandskennung |= cPOS_CHANGED_HR;
      break;
    }
    default:
    {
      ushZustandskennung |= (cPOS_CHANGED_VL | cPOS_CHANGED_VR | cPOS_CHANGED_HL| cPOS_CHANGED_HR);
      break;
    }
  }

}



/*!**********************************************************************************************************
 *\Function           SetCalNotAckZK
 *
 *
 *\Typ                public
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Purpose            set CalNotAck Bits in ZK
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
void SetCalNotAckZK( void )
{
#ifdef cal_plausi_axes_invalid_110606 /* [0] */
  if( GETbCalVaInvalidCAL() == TRUE )
  {
    SetBitZustandskennungZK( cCAL_P_VA_INVALID );
  }else{
    ClearBitZustandskennungZK( cCAL_P_VA_INVALID );
  }

  if( GETbCalHaInvalidCAL() == TRUE )
  {
    SetBitZustandskennungZK( cCAL_P_HA_INVALID );
  }else{
    ClearBitZustandskennungZK( cCAL_P_HA_INVALID );
  }
#endif /* #ifdef cal_plausi_axes_invalid_110606 */ /* [0] */

  if( GETbCalPminInvalidCAL() == TRUE )
  {
    SetBitZustandskennungZK( cCAL_P_MIN_INVALID );
  }else{
    ClearBitZustandskennungZK( cCAL_P_MIN_INVALID );
  }

#ifdef cal_EvCalTimeout_110606 /* [0] */
  if( GETbCalTioCAL() == TRUE )
  {
    SetBitZustandskennungZK( cCAL_TIO );
  }else{
    ClearBitZustandskennungZK( cCAL_TIO );
  }
#endif /* #ifdef cal_EvCalTimeout_110606 [0] */
}

