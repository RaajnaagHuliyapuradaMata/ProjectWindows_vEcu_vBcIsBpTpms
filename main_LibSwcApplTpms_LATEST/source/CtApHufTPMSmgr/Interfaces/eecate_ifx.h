/************************************************************************************************************
 * (c) Beru Electronics GmbH      Abteilung BES2     2006, 2007, 2009
 ************************************************************************************************************/
/************************************************************************************************************
 * Project:       Reifendruckkontrolle TSS (TSS = tyre safety system)
 *
 * $Archive: /BMW/G3kompakt/Sw/SC6XS/template_can/application/source/tssappl/intface/eecate_ifx.h $
 *
 * File Status:   compiled           - (under construction, compiled etc.)
 *
 ************************************************************************************************************/
/************************************************************************************************************
 * Author:
 *
 * Initials     Name                           Company
 * --------     --------------------------     --------------------------------------------------------------
 * ur           Uwe Rapp                       Beru Electronics GmbH (BES2)
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
 *
 ************************************************************************************************************/
/************************************************************************************************************
 * Modul Description
 * =================
 *
 * Purpose:
 *
 * Declaration of interface functions to and global data of the eeprom category E
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
 *
 ************************************************************************************************************/
/************************************************************************************************************
 * Modul Modification
 * ==================
 *
 * changes in 2006
 *
 * $Log: /BMW/G3kompakt/Sw/SC6XS/template_can/application/source/tssappl/intface/eecate_ifx.h $
 * 
 * 35    26.05.10 17:41 Rapp
 * - OIL_LC #522: Anzeige "Resetting TPMS" so kurz als möglich aber
 * mindestens für 10 Sekunden
 *
 * 34    12.03.10 15:50 Rapp
 * OIL_LC #440: Tankstopp-Funktion integriert
 *
 * 33    23.10.09 14:01 Rapp
 * Reservebytes in CatE hinzugefügt (Gelegenheit wegen HW-Bruch günstig)
 *
 * 32    21.10.09 12:11 Rapp
 * OIL#418: Versenden der Applikationsbotschaften AVL_P_TYR und AVL_T_TYR
 * auf dem Fahrzeugbus
 *
 * 31    23.09.09 14:50 Rapp
 * Anzeige "Resetting TPM" nur einmal innerhalb einer Lernphase im Kombi
 * und MMI anzeigen (OIL #395, #464)
 *
 * 30    17.03.09 14:15 Rapp
 * Schalter "DATENFLASH_OPTIMIERUNG" ausgeputzt (OIL #326)
 *
 * 29    14.11.08 10:37 Rapp
 * Übergabeparameter bei allen NVM-Initialisierungsfunktionen (siehe OIL
 * #47)
 *
 * 28    13.10.08 10:23 Rapp
 * stuff-bytes for alignment added
 *
 * 27    9.10.08 15:17 Braunm
 * Optimierung Datenflash
 *
 * 25    8.10.08 9:48 Rapp
 * EEPROM-Interfacefunktionen umbenannt
 *
 * 24    19.09.08 16:15 Rapp
 * typedef struct mit Namen versehen (wegen Fehlermeldung Ristan)
 *
 * 23    12.06.08 17:38 Peter
 * walloc EE-categories and access functions defined
 *
 * 21    26.05.08 14:05 Dederer
 * Zusammenfgefuehrt mit Version aus F03
 *
 * 23    29.04.08 8:37 Rapp
 * #include "ReceiveX.h" von X-Heade rin C-Modul verschoben
 *
 * 22    25.04.08 9:09 Rapp
 * Neu_BMW311::pl6:CR_000033 (Umsetzung Warnkonzept F03)
 *
 * 20    23.01.08 9:29 Rapp
 * Einheiten für Druck- und Temperatur- Anzeige umschaltbar
 * (Neu_BMW311::pl6:SW_62000)
 *
 * 19    21.05.07 18:22 Rapp
 * BERU EEPROM-Handler durch NVM aus SC ersetzt
 *
 * 18    4.05.07 12:33 Rapp
 * extern void EventforCAT_E( void ); in X-Header verschoben
 *
 * 17    11.01.07 14:41 Rapp
 * Funktion "Vergessener Reset" hinzugefügt
 *
 * 14    2.10.06 18:09 Rapp
 * ushResetCnt hinzugefügt
 *
 * 13    28.09.06 15:53 Rapp
 * Zugriff über ucByteAccess[] über alle Bytes der Struktur sichergestellt
 *
 * 12    26.09.06 10:49 Rapp
 * alle Basis-Include-Dateien für EEPROM-Handler in eeprx.h zusammengefaßt
 *
 * 11    10.08.06 10:14 Rapp
 * TODO (ur) bearbeitet
 *
 * 10    27.07.06 13:42 Rapp
 * ungenutzte EEPROM-Variablen auskommentiert
 *
 * 9     27.07.06 10:35 Rapp
 * - InitFillValueCAL() initialisiert jetzt alle Wertepaare
 * - Vergleichswerte für Druckunterschied jetz Konstante (vorher
 * EEPROM-Parameter)
 *
 * 8     20.07.06 16:57 Peter
 * address acces to Radposition
 *
 * 7     20.07.06 12:05 Peter
 * read address to history id
 *
 * 6     20.07.06 11:00 Peter
 * address acces to ulId
 *
 * 5     19.07.06 17:34 Peter
 * walloc & procdat variables made accessible
 *
 * 4     11.07.06 9:49 Hanke
 *
 * 3     10.07.06 18:08 Hanke
 *
 * 2     10.07.06 10:38 Hanke
 *
 * 1     6.07.06 16:29 Rapp
 * Modul "Calibr" integriert
 *
 ************************************************************************************************************/
#ifndef _eecate_ifX_H /* [0] */
#define _eecate_ifX_H



/************************************************************************************************************
 *                                             include
 ************************************************************************************************************/
#include "tss_stdx.h"         /* TSS specific defines                                                       */
//#include "eeprom_CFG.h"       /* Configuration-Header of eeprom module                                      */

//#include "calX.h"
//#include "wallocx.h"



/************************************************************************************************************
 *                                             macro
 ************************************************************************************************************/



/************************************************************************************************************
 *                                            typedef
 ************************************************************************************************************/
typedef struct typedef_struct_tCalDataPair
{
  uint8 ucPressure;
  sint8 scTemperature;
} tCalDataPair;



/*
 * mirrored RAM data for EEPROM category E
 * =======================================
 */
typedef struct typedef_struct_tMirroredRamCatEDecl
{
  tCalDataPair tFillValueCAL[5];     /* Befüllwerte (Druck und Temperatur */
  tCalDataPair tRatedValueCAL[2][5]; /* zu überwachender Solldruck ID-spez. und Radhausspez. */

  uint8 ucForgottenReset;            /* Merker für Funktion "Vergessener Reset" */

  uint8 ucWAHistIDSet[cMaxLR * sizeof(uint32)];  /* working values 4 walloc */
  uint8 ucWAHistWPSet[cMaxLR];

  uint8  ucCalRequestCAL;      /* Kalibrieranforderung im E²PROM */
  uint8  ucCalNotAckCAL;       /* Grund der abgewiesenen Kalibrierung im E²PROM */
  uint8  ucFolgeAusfallCnt[5];     /* Anzahl Folgeausfälle */

  uint8  ucResettingTpms;      /* Anzeige "Resetting RDC" nur einmal innerhalb einer Lernphase im Kombi     */
                               /* anzeigen (OIL_LC #395, #464, #522)                                        */

#if (BERU_BAUREIHE_BMW_PL4_ENABLE == ON)
  uint8 ucReserved[10];        /* reserved bytes (stuff-bytes for alignment) -                              *//* OIL_LC #440 */
                               /* Verwendung ohne HW-Bruch möglich                                          */
#endif

#if (BERU_BAUREIHE_BMW_PL6_ENABLE == ON)
  uint8 ucPresUnit;            /* Einheit Luftdruck                              - Neu_BMW311::pl6:SW_62000 */
  uint8 ucTempUnit;            /* Einheit Temperatur                             - Neu_BMW311::pl6:SW_62000 */

                               /* reserved bytes (stuff-bytes for alignment) - keine Reserve mehr vorhanden *//* OIL_LC #440 */
#endif

  uint8 ucHistWarningStateBAK; /* Historischer Warnstatus für Anzeige (MMI und Kombi)                       *//* OIL_LC #440 */
} tMirroredRamCatEDecl;



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



/************************************************************************************************************
 *                                       data (global) - EEPROM
 ************************************************************************************************************/



/************************************************************************************************************
 *                                     prototype (public function)
 ************************************************************************************************************/
extern void InitEECATE( void );

extern uint8 GETucFillValuePressureEE( uint8 );
extern void PUTucFillValuePressureEE( uint8 , uint8 );

extern sint8 GETscFillValueTemperatureEE( uint8 );
extern void PUTscFillValueTemperatureEE( sint8 , uint8 );

extern uint8 GETucRatedValuePressureEE( uint8 , uint8 );
extern void PUTucRatedValuePressureEE( uint8 , uint8 , uint8 );

extern sint8 GETscRatedValueTemperatureEE( uint8 , uint8 );
extern void PUTscRatedValueTemperatureEE( sint8 , uint8 , uint8 );

extern void INCushResetCntEE( void );

extern uint8 GETucForgottenResetEE( void );
extern void PUTucForgottenResetEE( uint8 );

#if (BERU_BAUREIHE_BMW_PL6_ENABLE == ON)
extern uint8 GETucPresUnitEE( void );        /*                                  - Neu_BMW311::pl6:SW_62000 */
extern void PUTucPresUnitEE( uint8 );        /*                                  - Neu_BMW311::pl6:SW_62000 */

extern uint8 GETucTempUnitEE( void );        /*                                  - Neu_BMW311::pl6:SW_62000 */
extern void PUTucTempUnitEE( uint8 );        /*                                  - Neu_BMW311::pl6:SW_62000 */
#endif /* #if (BERU_BAUREIHE_BMW_PL6_ENABLE == ON) */

extern uint8 GETucFillValuePressureCALe(uint8 );
extern sint8 GETscFillValueTemperatureCALe(uint8 );
extern uint8 GETucRatedValuePressureCALe(uint8,uint8);
extern sint8 GETscRatedValueTemperatureCALe(uint8,uint8);

extern uint8 GETucResettingTpmsEE( void );
extern void PUTucResettingTpmsEE( uint8 );

/********************************** walloc eeprom variable access functions *********************************/
extern uint8 GETucWAHistID(uint8);
extern void PUTucWAHistID(uint8, uint8);
extern uint8 GETucWAHistWP(uint8);
extern void PUTucWAHistWP(uint8, uint8);
/*******************************END walloc eeprom variable access functions *********************************/

extern uint8 GETucHistWarningStateBAKe( void );
extern void PUTucHistWarningStateBAKe( uint8 );
#endif /* #ifdef _eecate_ifX_H [0] */
