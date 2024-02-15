/***************************************************************************************************
(c) Beru Electronics GmbH     BEE1     01/2003
================================================================================================

$Archive: /VAG/MQB/SW/S12XS/SP/application/source/tssappl/WARN/global.h $


file status:   under construction

------------------------------------------------------------------------------------------------

author:        Peter Brand                Beru Electronics GmbH

intials:       pb


Modul Description

Global description:
prototypes, consts, data used by MORE the 1 submodule of  uswarnmodul and cannot be allocated to a
specific submodul.
Only uswarnmodul internal use!!



Modul Modification

changes in 2003

12.01.2003 pb - 1st established
30.05.2003 pb - adapted to new header structure
$Log: /VAG/MQB/SW/S12XS/SP/application/source/tssappl/WARN/global.h $
 * 
 * 27    29.07.11 17:09 Dederer
 * Anpassung an Erweiterung ECE-R64
 *
 * 26    28.07.11 11:53 Peter
 * Pwarm (ECExxx) Implementierung
 *
 * 25    13.10.08 17:28 Peter
 * module test switch deactivated
 *
 * 24    9.10.08 18:23 Peter
 * adatpted to 4 IDs and 4 wheel positions
 *
 * 23    2.07.07 15:48 Peter
 * modultest deactivated
 *
 * 22    2.07.07 10:04 Peter
 * refactoring USWarn
 *
 * 17    30.12.04 11:04 Peter
 *
 * 18    30.12.04 10:57 Peter
 * supplementary display warning type implemented SW_90 .. SW_150 bmw
 *
 * 17    19.08.04 14:37 Peter
 * Modultestschalter deaktiviert
 *
 * 16    19.08.04 14:35 Peter
 * MISRA conformance enhanced and uswarn reconfigured for better metrics
 *
 * 14    15.07.04 17:22 Peter
 * Modultestschalter und QAC-schalter deaktiviert
 *
 * 13    14.07.04 16:52 Peter
 * documentation update
 *
 * 11    11.11.03 10:55 Peter
 * Anpassung an MISRA Subset gem. HIS V1.0
 *
 * 9     30.07.03 16:26 Peter
 * neue KOnstante für WarnBits im EEPROM eingefügt
 *
 * 8     16.06.03 10:23 Peter
 * Dokumentation

***************************************************************************************************/
#ifndef GLOBAL_H

#define GLOBAL_H
/*
Declaration
*/
/*
Include
*/
#include "Std_Types.h"        /* Provision of Standard Types*/                               
/*************************************************************
Macros
*/
/* test switches */

/*#define pb_TestCtrl_110203        // activate  test routine of ctrl module */
//#define pb_ModulTest_02062003  /* all inclusive module test */

#if defined(pb_ModulTest_02062003) || defined(TestUSCSc) || defined(pb_TestCtrl_110203) || defined (pb_TestEeIface_200103)
#define pb_EeIfaceOnPc_200103       /* simulate eeprom by pc-RAM */
#endif


/* tss specific stuff */
#define ucMaxPosc 4  /* sum of possible wheel position */
#define ucSumWEc  (unsigned char) 4  /* sum of managed system w.e.s */


/******************* macros for eeprom access *******************/
#define ucCbIdTMc (unsigned short) 5 /* tss code byte for display */
#define ucWarnTypeArrayIdWNc (unsigned short) 6 /* id of warntype array to be safed in eeprom */

/**********************************************************************/
#define ucIxWnCfgc 1    /* TODO: remove parameter settings to warn- and msg-module */
#define ucIxGlobWrnLvl 0    /* to conceal the warning types (PMin..Soft) */

/*
Data
*/


/*************************************************************
Prototypes
*/

extern const unsigned char ucBitNoc[ucSumWEc];


extern uint8 bGETucCalRequestState( uint8 ucBitMask );
extern void ClearBitCalRequestState( uint8 ucBitMask );
extern void ClearCalRequestStateAtMFDfinish( void );


extern uint8 GETucPrefFront(void);/* NewNVMdata */
extern uint8 GETucPrefRear(void);/* NewNVMdata */
extern void PUTucPrefFront(uint8 x);/* NewNVMdata */
extern void PUTucPrefRear(uint8 x);/* NewNVMdata */


extern sint8 GETscTref(void);
extern void PUTucIdCalPressure(uint8 x, uint8 i);/*Init ID spezifisch for first calibration*/
extern void PUTscIdCalTemperatur(sint8 x, uint8 i);/*Init ID spezifisch for first calibration*/
extern void PUTscTref(sint8 x);/*Init ID spezifisch for first calibration*/


extern uint8 * pui8GetLastM1Pressure(void);
extern uint8 ui8GetPMIN_F(void);
extern uint8 ui8GetPMIN_R(void);

extern void UpdateWarnOut(const uint8 * p2WPs);
#endif

/*
Implementation
*/
