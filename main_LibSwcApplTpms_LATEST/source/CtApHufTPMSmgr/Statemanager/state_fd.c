/************************************************************************************************************
 * (c) Huf Huelsbeck und Fuerst GmbH Co. KG   Abteilung PDSTPS    2016
 ************************************************************************************************************/
/************************************************************************************************************
 * Project:       Reifendruckkontrolle TSS (TSS = tyre safety system)
 *
 * $Archive: /BMW/G3kompakt/Sw/SC4/template_can/application/source/tssappl/statemanager/state_fd.c $
 *
 * File Status:   compiled           - (under construction, compiled etc.)
 *
 ************************************************************************************************************/
/************************************************************************************************************
 * Author:
 *
 * Initials     Name                           Company
 * --------     --------------------------     --------------------------------------------------------------
 * as           Andreas Schubert               Huf Huelsbeck und Fuerst GmbH Co. KG
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
 *
 ************************************************************************************************************/
/************************************************************************************************************
 * Modul Modification
 * ==================
 *
 * changes in 2016
 *
 * $Log: /_TSS/DAG/MFA2/Target/SWC/Source/CtApHufTPMSmgr/Statemanager/state_fd.c $
 * 
 *
 * 1     25.04.16 Schubert
 * creation  "Statemanager"
 *
 ************************************************************************************************************/



/************************************************************************************************************
 *                                             include
 ************************************************************************************************************/
#include "state_fd.h"
//#include "state_fdX.h"

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

#define cFD_LEFT_RIGHT_DIFFERENCE		((uint8) 0x01)
#define cFD_ABSOLUTE_PRESSURE_DIFF 	((uint8) 0x03)		// DP_ABS 1,5bar absolute differenz 

/************************************************************************************************************
 *                                       data (global) - RAM
 ************************************************************************************************************/



/***********************************************************************************************************
 *                                 prototype (local functions - private)
 ***********************************************************************************************************/
void SetBitFillingDetectionStateFD( uint8 ); /* not used */
void ClearBitFillingDetectionStateFD( uint8 ); /* not used */
boolean bGetBitFillingDetectionStateFD( uint8 );
uint8 Get_FD_STATUS( void );
void SetState2FillingDetectionStateFD( uint8 );
void ClearFillingDetectionStateFD(void);
uint8 Get_FD_ABORT_REASON( void );
void SetBitAbortReasonFD( uint8 );
void ClearBitAbortReasonFD( uint8 );
void SetState2AbortReasonFD( uint8 );
void ClearAbortReasonFD( void );
uint8 Get_FD_PLAUSIBILITY_FAILURE( void );
uint8 GetFD_PlausiFailure( void );
void SetState2PlausiFailureFD( uint8 );
void ClearPlausiFailureLeftRightAbsFD( void );


void ClearPlausiFailureFD(void);

void  SetIdCol0New4FD( uint8 );
uint8 GetIdCol0New4FD( void );
void  SetIdCol1New4FD( uint8 );
uint8 GetIdCol1New4FD( void );
void  SetIdCol2New4FD( uint8 );
uint8 GetIdCol2New4FD( void );
void  SetIdCol3New4FD( uint8 );
uint8 GetIdCol3New4FD( void );

uint8 GetNewIdColX4FD( uint8 );
uint8 ChkNewIdColX4FD( void ); /*CRS_1211_130_373*/
void ClearNewIdColXMem4FD( uint8 );


/***********************************************************************************************************
 *                                 prototype (local functions - public)
 ***********************************************************************************************************/



/************************************************************************************************************
 *                               prototype (external functions - interface)
 ************************************************************************************************************/

/************************************************************************************************************
 *                                            implementation
 ************************************************************************************************************/


/*!**********************************************************************************************************
 *\Function           void SetBitFillingDetectionStateFD( uint8 ucBitMask )
 *
 *\Typ                public
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Purpose            Setzt Bit in FillingDetectionStateFD anhand übergebener Bitmaske.
 *
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\SW_Requirements    none
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Parameter          ucBitMask - Bitmaske zu setzender Bits
 *
 *\Input              none
 *
 *\Output             none
 *
 *\Return             none
 *
 ************************************************************************************************************/
void SetBitFillingDetectionStateFD( uint8 ucBitMask )
{
   ucFD_Status |= ucBitMask;
} /* void SetBitFillingDetectionStateFD( uint16 ushBitMask ) */



/*!**********************************************************************************************************
 *\Function          void ClearBitFillingDetectionStateFD( uint8 ucBitMask )
 *
 *\Typ                public
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Purpose            Löscht Bit in FillingDetectionStateFD anhand übergebener Bitmaske.
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
void ClearBitFillingDetectionStateFD( uint8 ucBitMask )
{
   ucFD_Status &= ~ucBitMask;
} /* void ClearBitFillingDetectionStateFD( uint16 ushBitMask ) */



/*!**********************************************************************************************************
 *\Function           boolean bGetBitFillingDetectionStateFD( uint8 ucBitMask )
 *                    
 *
 *\Typ                public
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Purpose            Liefert Bitzustand des anhand der übergebenen Bitmaske selektierten Bit
 *                    in FillingDetectionState.
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
boolean bGetBitFillingDetectionStateFD( uint8 ucBitMask )
{
   return (boolean) ((ucFD_Status & ucBitMask) != 0 );
} /* boolean bGetBitFillingDetectionStateFD( uint16 ushBitMask ) */


uint8 Get_FD_STATUS(void )
{
   return ucFD_Status;
} /* uint8 Get_FD_STATUS( void ) */



/*!**********************************************************************************************************
 *\Function           void SetState2FillingDetectionStateFD( uint8 ucState )
 *                    
 *
 *\Typ                public
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Purpose            Liefert Bitzustand des anhand der übergebenen Bitmaske selektierten Bit
 *                    in FillingDetectionState.
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
 *\Return             none
 *                    
 *
 ************************************************************************************************************/
void SetState2FillingDetectionStateFD( uint8 ucState )
{
   ucFD_Status = ucState;
} /* void SetState2FillingDetectionStateFD( uint8 ucState ) */

/*!**********************************************************************************************************
 *\Function           void ClearFillingDetectionReasonFD()
 *                    
 *
 *\Typ                public
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Purpose            Liefert Bitzustand des anhand der übergebenen Bitmaske selektierten Bit
 *                    in FillingDetectionState.
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\SW_Requirements    none
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Parameter          non
 *
 *\Input              none
 *
 *\Output             none
 *
 *\Return             none
 *                    
 *
 ************************************************************************************************************/
void ClearFillingDetectionStateFD(void)
{
   ucFD_Status = FALSE;
} /* void ClearFillingDetectionReasonFD() */


/*!**********************************************************************************************************
 *\Function           uint8 Get_FD_ABORT_REASON( void )
 *
 *\Typ                public
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Purpose            ALLe Funktionen für AbortReasonFD 
 *										MFD and AFD Abort
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\SW_Requirements    none
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Parameter          ucBitMask - Bitmaske zu setzender Bits
 *
 *\Input              none
 *
 *\Output             none
 *
 *\Return             none
 *
 ************************************************************************************************************/
uint8 Get_FD_ABORT_REASON( void )
{
   return ucFD_AbortReason;
} /* uint8 Get_FD_ABORT_REASON( void ) */


void SetBitAbortReasonFD( uint8 ucBitMask )
{
   ucFD_AbortReason |= ucBitMask;
} /* void SetBitAbortReasonFD( uint8 uchBitMask ) */

void ClearBitAbortReasonFD( uint8 ucBitMask )
{
   ucFD_AbortReason &= ~ucBitMask;
} /* void SetBitAbortReasonFD( uint8 uchBitMask ) */


void SetState2AbortReasonFD( uint8 ucState )
{
   ucFD_AbortReason = ucState;
} /* void SetBitAbortReasonFD( uint8 ucState ) */


void ClearAbortReasonFD()
{
   ucFD_AbortReason =FALSE;
} /* void ClearAbortReasonFD() */


/*!**********************************************************************************************************
 *\Function           vuint8 Get_FD_PLAUSIBILITY_FAILURE(void )
 *
 *\Typ                public
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Purpose            ALLe Funktionen für ucFD_PlausiFailure 
 *										MFD and AFD Failure
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\SW_Requirements    none
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Parameter          ucBitMask - Bitmaske zu setzender Bits
 *
 *\Input              none
 *
 *\Output             none
 *
 *\Return             none
 *
 ************************************************************************************************************/
uint8 Get_FD_PLAUSIBILITY_FAILURE(void )
{
   return ucFD_PlausiFailure;
} /* uint8 GetFD_PlausiFailure( void ) */

void SetState2PlausiFailureFD( uint8 ucState )
{
   ucFD_PlausiFailure = ucState;
} /* void SetBitAbortReasonFD( uint16 ushBitMask ) */


void ClearPlausiFailureLeftRightAbsFD( void )
{
  ucFD_PlausiFailure &= ~cFD_ABSOLUTE_PRESSURE_DIFF;
	ucFD_PlausiFailure &= ~cFD_LEFT_RIGHT_DIFFERENCE;
} /* void SetBitAbortReasonFD( uint16 ushBitMask ) */



void ClearPlausiFailureFD(void)
{
   ucFD_PlausiFailure =FALSE;
} /* void ClearAbortReasonFD() */



/*!**********************************************************************************************************
 *\Function           void SetIdCol0New4FD( uint8  )
 *
 *\Typ                public
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Purpose            Setzt MerkerBit für FD da neue Column ID ZOM und die Vergleichsdrücke gespeichert werden müssen.
 *
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\SW_Requirements    none
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Parameter          non
 *
 *\Input              none
 *
 *\Output             none
 *
 *\Return             none
 *
 ************************************************************************************************************/
void SetIdCol0New4FD( uint8 ucCol )
{
   ucIdCol0New4FD = ucCol;
} /* void SetIdCol0New4FD( void ) */

uint8 GetIdCol0New4FD( void )
{
   return ucIdCol0New4FD;
} /* void GetIdCol0New4FD( void ) */

void SetIdCol1New4FD( uint8 ucCol )
{
   ucIdCol1New4FD = ucCol;
} /* void SetIdCol1New4FD( void ) */

uint8 GetIdCol1New4FD( void )
{
   return ucIdCol1New4FD;
} /* void GetIdCol1New4FD( void ) */

void SetIdCol2New4FD( uint8 ucCol )
{
   ucIdCol2New4FD =ucCol;
} /* void SetIdCol2New4FD( void ) */

uint8 GetIdCol2New4FD( void )
{
   return ucIdCol2New4FD;
} /* void GetIdCol2New4FD( void ) */

void SetIdCol3New4FD( uint8 ucCol )
{
   ucIdCol3New4FD = ucCol;
} /* void SetIdCol3New4FD( void ) */

uint8 GetIdCol3New4FD( void )
{
   return ucIdCol3New4FD;
} /* void GetIdCol3New4FD( void ) */



uint8 GetNewIdColX4FD( uint8 ucCol )
{
   
uint8 ucReturnValue=FALSE;
  switch (ucCol)
	{
		case cZOMPos0: 
					ucReturnValue = ucIdCol0New4FD;
		break;
		case cZOMPos1: 
					ucReturnValue = ucIdCol1New4FD;
		break;
		case cZOMPos2: 
					ucReturnValue = ucIdCol2New4FD;
		break;
		case cZOMPos3: 
  				ucReturnValue = ucIdCol3New4FD;	
		break;
		}


return ucReturnValue;
} /* uint8 GetNewIdColX4FD( uint8 ) */


uint8 ChkNewIdColX4FD( void )	/*CRS_1211_130_373*/
{
uint8 ucReturnValue=FALSE;
	if((ucIdCol0New4FD == TRUE) || (ucIdCol1New4FD == TRUE) || (ucIdCol2New4FD == TRUE) || (ucIdCol3New4FD == TRUE))
	{
		ucReturnValue=TRUE;
	}

return ucReturnValue;
} /* uint8 ChkNewIdColX4FD( void ) */





void ClearNewIdColXMem4FD( uint8 ucCol )
{
   
  switch (ucCol)
	{
		case cZOMPos0: 
					ucIdCol0New4FD=FALSE;
		break;
		case cZOMPos1: 
					ucIdCol1New4FD=FALSE;
		break;
		case cZOMPos2: 
					ucIdCol2New4FD=FALSE;
		break;
		case cZOMPos3: 
  				ucIdCol3New4FD=FALSE;	
		break;
		}

} /* void ClearNewIdColXMem4FD( uint8 ) */