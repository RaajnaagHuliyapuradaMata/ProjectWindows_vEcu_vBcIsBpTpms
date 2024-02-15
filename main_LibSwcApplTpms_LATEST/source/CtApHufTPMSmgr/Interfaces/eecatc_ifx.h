/************************************************************************************************************
 * (c) Beru Electronics GmbH      Abteilung BES     2006, 2007
 ************************************************************************************************************/
/************************************************************************************************************
 * Project:       Reifendruckkontrolle TSS (TSS = tyre safety system)
 *
 * $Archive: /BMW/G3kompakt/Sw/SC4/template_can/application/source/tssappl/intface/eecatc_ifx.h $
 *
 * File Status:   compiled           - (under construction, compiled etc.)
 *
 ************************************************************************************************************/
/************************************************************************************************************
 * Author:
 *
 * Initials     Name                           Company
 * --------     --------------------------     --------------------------------------------------------------
 * ur           Uwe Rapp                       Beru Electronics GmbH (BES)
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
 * Declaration of interface functions to and global data of the eeprom category C
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
 * $Log: /BMW/G3kompakt/Sw/SC4/template_can/application/source/tssappl/intface/eecatc_ifx.h $
 * 
 * 46    23.10.09 14:00 Rapp
 * Reservebytes in CatC2 hinzugefügt (Gelegenheit wegen HW-Bruch günstig) 
 *
 * 45    17.03.09 14:15 Rapp
 * Schalter "DATENFLASH_OPTIMIERUNG" ausgeputzt (OIL #326)
 *
 * 44    26.02.09 15:52 Peter
 * ushResetCnt von CatC5 nach CatC2 verschoben - CatC2 jetzt voll
 *
 * 43    14.11.08 10:37 Rapp
 * Übergabeparameter bei allen NVM-Initialisierungsfunktionen (siehe OIL
 * #47)
 *
 * 42    13.10.08 16:10 Braunm
 * Alle Rom-Daten nach Romdata_If.c und RomData_IfX.h verschoben
 *
 * 41    13.10.08 14:03 Braunm
 * Reserved Bytes für Allignement in CatC5 angepasst
 *
 * 40    13.10.08 10:55 Peter
 * ...
 *
 * 39    13.10.08 10:46 Peter
 * USWalgo's EEPROM  consumption reduced
 *
 * 38    13.10.08 10:23 Rapp
 * stuff-bytes for alignment added
 *
 * 37    9.10.08 15:17 Braunm
 * Optimierung Datenflash
 *
 * 35    8.10.08 9:48 Rapp
 * EEPROM-Interfacefunktionen umbenannt
 *
 * 34    6.10.08 9:42 Braunm
 * Deklarationen von PUTtWAparam und GETtWAparam angepasst
 *
 * 33    19.09.08 16:15 Rapp
 * typedef struct mit Namen versehen (wegen Fehlermeldung Ristan)
 *
 * 32    12.06.08 17:38 Peter
 * walloc EE-categories and access functions defined
 *
 * 31    11.06.08 17:12 Dederer
 * Aufgeraeumt
 *
 * 29    23.01.08 15:41 Rapp
 * MISRA-C 2004 Korrekturen durchgeführt
 *
 * 28    13.06.07 11:54 Dederer
 * Neues Konzept Statistik zur Bewertung Uebertragungsstrecke umgesetzt
 *
 * 27    21.05.07 18:22 Rapp
 * BERU EEPROM-Handler durch NVM aus SC ersetzt
 *
 * 26    14.05.07 15:39 Viereckel
 *
 * 25    4.05.07 12:32 Rapp
 * extern void EventforCAT_C( void ); in X-Header verschoben und
 * auskommentierte TODO-Zeilen entfernt
 *
 * 24    19.03.07 8:59 Dederer
 * Varaible und Makros fuer Status sekundaerer Fehlerspeicher
 *
 * 23    2.01.07 16:52 Rapp
 * Das anziehen der SC6-spezifischen Header-Datei "Std_Types.h" wurde aus
 * allen Modulen entfernt und statt dessen in die BERU-spez. Header-Datei
 * "tss_stdx.h" eingefügt. Damit läßt sich an einer zentralen Stelle die
 * Anpassung an SC6 vornehmen und die Module lassen sich auch bei OEMs
 * ohne SC6 verwenden.
 *
 * 22    19.12.06 15:16 Rapp
 * Komponente ErrMem entfernt und dafür Komponente DEM integriert
 *
 * 21    15.12.06 16:19 Rapp
 * Umstellung Fehlerspeichermanager (von ErrMem auf DEM)
 *
 * 20    11.12.06 16:17 Rapp
 * Umstellung auf SC6.7.x
 *
 * 17    13.10.06 17:07 Dederer
 * Variabel ucNoLinSlaveFlags in Block5 definiert (automatische
 * Triggersender-Typerkennung)
 *
 * 16    11.10.06 15:59 Rapp
 * Verwaltung der Statistikzähler (HF-Telegramme der RE) hinzugefügt
 *
 * 15    2.10.06 11:22 Peter
 * Freischlatung und Zugriff auf Antennenstromdiagnoseparameter
 *
 * 14    28.09.06 15:53 Rapp
 * Zugriff über ucByteAccess[] über alle Bytes der Struktur sichergestellt
 *
 * 13    10.08.06 10:14 Rapp
 * TODO (ur) bearbeitet
 *
 * 12    27.07.06 12:23 Rapp
 * ungenutzte EEPROM-Variablen und Funktionen auskommentiert
 *
 * 11    21.07.06 16:23 Rapp
 * Grundinitialisierung EEPROM hinzugefügt
 *
 * 10    19.07.06 17:34 Peter
 * walloc & procdat variables made accessible
 *
 * 9     14.07.06 13:45 Peter
 * array decalration of USWalgo ParameterByte
 *
 * 8     14.07.06 12:49 Rapp
 * falsches "extern" entfernt
 *
 * 7     14.07.06 11:19 Peter
 * USWalgo integration
 *
 * 6     14.07.06 11:10 Rapp
 * Integration Modul "ProcDat"
 *
 * 5     11.07.06 12:18 Rapp
 * Integration Modul "Eeprom"
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
#ifndef _eecatc_ifX_H /* [0] */
#define _eecatc_ifX_H



/************************************************************************************************************
 *                                             include
 ************************************************************************************************************/
#include "tss_stdx.h"         /* TSS specific defines                                                       */
//#include "eeprom_CFG.h"       /* Configuration-Header of eeprom module                                      */

//#include "WallocX.h"

/************************************************************************************************************
 *                                             macro
 ************************************************************************************************************/



/************************************************************************************************************
 *                                            typedef
 ************************************************************************************************************/
/*
 * Allg. Bitfeld KAT C
 */
struct tBitfeldKATC             // Bitfeld im EEPROM mit 8 Bits
{
    boolean b7;                       // Bit 7
    boolean b6;                       // Bit 6
    boolean b5;                       // Bit 5
    boolean b4;                       // Bit 4
    boolean b3;                       // Bit 3
    boolean b2;                       // Bit 2
    boolean b1;                       // Bit 1
    boolean b0;                       // Bit 0
    boolean b15;                      // nicht benutzen !!
    boolean b14;                      // nicht benutzen !!
    boolean b13;                      // nicht benutzen !!
    boolean b12;                      // nicht benutzen !!
    boolean b11;                      // nicht benutzen !!
    boolean b10;                      // nicht benutzen !!
    boolean b9;                       // nicht benutzen !!
    boolean b8;                       // nicht benutzen !!
};



/*
* mirrored RAM data for EEPROM category C
* =======================================
*/
// Block 2 (15 Byte) ohne pruefsummenbyte
typedef struct typedef_struct_tMirroredRamCatC2Decl
{
  uint16 ushGutEmpfCnt[5];         /* Anzahl gut empfangene Telegramme */
  uint16 ushMissedCnt[5];          /* Anzahl nicht empfangene Telegramme */

  uint16 ushResetCnt;              /* wird nach jedem Klemme 30 Reset inkrementiert */

#if (BERU_BAUREIHE_BMW_PL4_ENABLE == ON)
  uint8 ucReserved[8];             /* reserved bytes (Verwendung ohne HW-Bruch möglich */
#endif

  /* --- end of bloc --- */
} tMirroredRamCatC2Decl;



typedef struct typedef_struct_tMirroredRamCatC5Decl
{
  uint8 ucWAParaByte[sizeof(WAParameter)];
  /* Belegung für USWAlgo lite V4: aus Dokument "modultestwarn.txt" entnommen */
  uint8 ucId1e;
  uint8 ucId2e[22];     /* SW_900220 C6 LL DB */
  uint8 ucId3e[1];         /* SW_10310 SW_100 bmw SW_900220 C6 LL DB */
  uint8 ucId4e;
  uint8 ucId5e[2];      /* SW_10310 */
  uint8 ucId6e[8];     /* SW_10310 SW_100 bmw SW_900220 C6 LL DB */


  uint8 ucReserved[8];    /* reserved bytes (stuff-bytes for alignment) */
  /* --- end of bloc --- */
} tMirroredRamCatC5Decl;



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
extern void InitEECATC2( void );

extern void InitEECATC5( void );

extern void PUTushMissedCntEE( uint16 , uint8 );
extern uint16 GETushMissedCntEE( uint8 );

extern void PUTushGutEmpfCntEE( uint16 , uint8 );
extern uint16 GETushGutEmpfCntEE( uint8 );

extern void PUTucFolgeAusfallCntEE( uint8 , uint8 );
extern uint8 GETucFolgeAusfallCntEE( uint8 );

extern uint8 GETucCalRequestEE( void );
extern void PUTucCalRequestEE( uint8 );

extern uint8 GETucCalNotAckEE( void );
extern void PUTucCalNotAckEE( uint8 );

extern uint8 GETucId1e( void );
extern void PUTucId1e( uint8 );
extern uint8 GETucId2e( uint8 );
extern void PUTucId2e( uint8, uint8 );
extern uint8 GETucId3e( uint8 );
extern void PUTucId3e( uint8, uint8 );
extern uint8 GETucId4e( void );
extern void PUTucId4e( uint8 );
extern uint8 GETucId5e( uint8 );
extern void PUTucId5e( uint8, uint8 );
extern uint8 GETucId6e( uint8);
extern void PUTucId6e( uint8, uint8 );

extern void PUTtWAparam(uint8 , uint8 ); /* ( value, index ) */
extern uint8 GETtWAparam(uint8 ); /* (index) */


#endif /* #ifdef _eecatc_ifX_H [0] */
