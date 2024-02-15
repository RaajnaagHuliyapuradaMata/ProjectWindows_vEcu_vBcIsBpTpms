/************************************************************************************************************
 * (c) Beru Electronics GmbH      Abteilung BES     2006
 ************************************************************************************************************/
/************************************************************************************************************
 * Project:       Reifendruckkontrolle TSS (TSS = tyre safety system)
 *
 * $Archive: /BMW/G3kompakt/Sw/SC4/template_can/application/source/tssappl/intface/tss_stdx.h $
 *
 * File Status:   compiled           - (under construction, compiled etc.)
 *
 ************************************************************************************************************/
/************************************************************************************************************
 * Author:        Uwe Rapp           Beru Electronics GmbH (BES)
 *
 * Intials:       ur
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
 *
 ************************************************************************************************************/
/************************************************************************************************************
 * Modul Modification
 * ==================
 *
 * changes in 2006
 *
 * $Log: /BMW/G3kompakt/Sw/SC4/template_can/application/source/tssappl/intface/tss_stdx.h $
 * 
 * 22    8.12.08 15:58 Rapp
 * cRadPosUndef = 8 (vorher 4)
 *
 * 21    23.10.08 9:37 Braunm
 * Neues Define: cInvalidSpinDir
 *
 * 20    17.06.08 10:05 Rapp
 * Integration "Statemanager"
 *
 * 18    15.06.07 17:16 Rapp
 * Konstanten zum Setzen der Frequenzvariante korrigiert
 *
 * 17    5.06.07 18:35 Rapp
 * Defines Frequenzvariante aus SCIx.h nach tss_stdx.h verschoben
 *
 * 16    4.05.07 12:39 Rapp
 * Definition der Dummy-ID hinzugefügt
 *
 * 15    2.01.07 16:52 Rapp
 * Das anziehen der SC6-spezifischen Header-Datei "Std_Types.h" wurde aus
 * allen Modulen entfernt und statt dessen in die BERU-spez. Header-Datei
 * "tss_stdx.h" eingefügt. Damit läßt sich an einer zentralen Stelle die
 * Anpassung an SC6 vornehmen und die Module lassen sich auch bei OEMs
 * ohne SC6 verwenden.
 *
 * 12    12.10.06 14:46 Rapp
 * Standard-Rückgabewerte für Funktionen definiert
 *
 * 11    26.09.06 10:47 Rapp
 * Struktur tLong hinzugefügt
 *
 * 10    1.08.06 15:07 Rapp
 * Korrektur an Ersatzwertbehandlung und initialisierung der
 * Fahrzeugzustände
 *
 * 9     29.07.06 12:41 Rapp
 * Umweltdaten (Fehlerspeicher) um den Eintrag Systemzeit erweitert und
 * den Datentyp der Variablen Kilometerstand von uint16 auf uint32
 * geändert
 *
 * 8     27.07.06 10:35 Rapp
 * - InitFillValueCAL() initialisiert jetzt alle Wertepaare
 * - Vergleichswerte für Druckunterschied jetz Konstante (vorher
 * EEPROM-Parameter)
 *
 * 7     24.07.06 13:51 Rapp
 * Fahrzeugsignale in FZZ-Variable spiegeln
 *
 * 6     22.07.06 11:05 Rapp
 * Initialisierung (bei Kl.15 ein/aus etc.)
 *
 * 5     21.07.06 16:23 Rapp
 * Grundinitialisierung EEPROM hinzugefügt
 *
 * 4     18.07.06 16:57 Rapp
 * Integration Modul "SgDiag"
 *
 * 3     13.07.06 13:09 Rapp
 * Integration Modul "ProcDat"
 *
 * 2     4.07.06 17:38 Rapp
 *
 * 1     27.06.06 17:11 Rapp
 *
 ************************************************************************************************************/
#ifndef _tss_stdX_H /* [0] */
#define _tss_stdX_H



/************************************************************************************************************
 *                                             include
 ************************************************************************************************************/
#include "Std_Types.h"        /* Provision of Standard Types                                                */



/************************************************************************************************************
 *                                              macro
 ************************************************************************************************************/
#define cAnzAnt       ( (uint8)  1 )      /* max. Anzahl von unterstützten Antennen im System  */
#define cAnzRad       ( (uint8)  4 )      /* max. Anzahl von unterstützten Rädern im System    */
#define cAnzAchse     ( (uint8)  2 )      /* max. Anzahl von unterstützten Achsen im System    */

#define cRadPosVL     ( (uint8) 0 )       /* Radposition vorne links   */
#define cRadPosVR     ( (uint8) 1 )       /* Radposition vorne rechts  */
#define cRadPosHL     ( (uint8) 2 )       /* Radposition hinten links  */
#define cRadPosHR     ( (uint8) 3 )       /* Radposition hinten rechts */
#define cRadPosUkw		( (uint8) 4 )       /* Radposition Unknow */
#define cRadPosFR     ( (uint8) 5 )       /* Fremdrad                  */
#define cRadPosUndef  ( (uint8) 8 )       /* Radposition undefiniert   */

#define ctFillFront   ( (uint8) 0 )       /* average tire temp at the end of filling detection front   */
#define ctFillRear    ( (uint8) 1 )       /* average tire temp at the end of filling detection rear   */
#define ctRefFront    ( (uint8) 2 )       /* reference temp for temp compensation = tFillFront with Kweight   */
#define ctRefRear     ( (uint8) 3 )       /* reference temp for temp compensation = tFillRear with Kweight   */


#define cLTS30Days  	( (uint8) 3 )       /* CRS_1211_130_245 Long Term Stationary =3  --> longer than 30days  */

#define cZOMPos0      ( (uint8) 0 )       /* ID spezifische ZOM POS0    */
#define cZOMPos1      ( (uint8) 1 )       /* ID spezifische ZOM POS1    */
#define cZOMPos2      ( (uint8) 2 )       /* ID spezifische ZOM POS2    */
#define cZOMPos3      ( (uint8) 3 )       /* ID spezifische ZOM POS3    */

#define ucPalTempNormFACTORc (unsigned char) 50 /* RE PAL Temperatur Normierungs Faktor  0x02=-50°C ... 0xEF=187°C */
#define ucPalTempNormFACTOR4Calc (unsigned char) 50 /* RE PAL Temperatur Normierungs Faktor  0x02=-50°C ... 0xEF=187°C */
#define ucPalTempNormLIMITCalc (unsigned char) 125 /* RE PAL Systemtemperatur Überlauf Grenzwert (-127°C ... +125°C */
#define ucPalTempNorm4AM (unsigned char) 85 /* RE PAL Temperatur Normierungs Faktor  0x02=-50°C ... 0xEF=187°C */
//CRS_1211_130_268 #define TirePressureDiffAbsRel  ( (uint8) 40 )  /*  difference factor for absolut 2 relativ peressure */
//CRS_1211_130_268 #define TirePressure1900mbar		( (uint8) 76 )  /*  default value for Pmin*/
#define ucPalTempNormOFFSETc (unsigned char) 2 /* CRS_1211_130_200 RE PAL Temperatur Normierungs Offset  0x02=-50°C ... 0xEF=187°C */
#define cDP_STABI				( (uint8) 4 )    /* 100mbar */
#define cDP_MANUAL			( (uint8) 8 )    /* 200mbar */
#define cDP_AUTO				( (uint8) 4 )    /* 100mbar */
#define cDP_LR					( (uint8) 83)    /* 17% threshold 4 pressure difference (100%=greaterP)  left 2 right */
#define cDP_Abs					( (uint8) 60 )   /* CRS_1211_130_074 1500mbar maximal absolute differnce pressure between max and min pressure CRS_1211_131_066 */
#define cDP_FILL				( (uint8) 8 )    /* 200mbar */
#define cP_GRAD					( (uint8) 8 )    /* 200mbar Pressure gradient for fast pressure loss warning */
#define cM_MAX					( (uint16) 540 ) /* 540 sec Timeout for missing wheel sensor / The maximal value of the Mute-Counter */
#define cV_MAX_PAL			( (uint8) 150 )  /* Maximum speed for PAL autolocation */
#define cV_MIN					( (uint8) 20 )   /* Minimum vehicle speed for Wheel transmission */

#define cDP_FILL_FL			( (uint8) 0x10 )   /* Bit 4 AFD DP_FILL Front Left */
#define cDP_FILL_FR			( (uint8) 0x20 )   /* Bit 4 AFD DP_FILL Front Right*/
#define cDP_FILL_RL			( (uint8) 0x40 )   /* Bit 4 AFD DP_FILL Rear Left */
#define cDP_FILL_RR			( (uint8) 0x80 )   /* Bit 4 AFD DP_FILL Rear Right*/

#define cFD_Pmin_FL			( (uint8) 0x01 )   /* Bit 4 AFD+MFD  DP_FILL Front Left */
#define cFD_Pmin_FR			( (uint8) 0x02 )   /* Bit 4 AFD+MFD  DP_FILL Front Right*/
#define cFD_Pmin_RL			( (uint8) 0x04 )   /* Bit 4 AFD+MFD  DP_FILL Rear Left */
#define cFD_Pmin_RR			( (uint8) 0x08 )   /* Bit 4 AFD+MFD  DP_FILL Rear Right*/
#define cFD_Pmin_UK			( (uint8) 0xF0 )   /* Bit 4 AFD+MFD  DP_FILL Pos UnKnow*/



#define cTfillLimitH		( (uint8) 60 )   /* CRS_1211_130_219 60°C */

/**
 ************************************************************************************************************
 ** Frequenzvariante
 **/
#define FREQUENCY_433MHZ  ( (uint8) 0x00 )  /* Frequenzvariante 433 MHz */
#define FREQUENCY_868MHZ  ( (uint8) 0x01 )  /* Frequenzvariante 868 MHz */
#define FREQUENCY_315MHZ  ( (uint8) 0x02 )  /* Frequenzvariante 315 MHz */



/**
 ************************************************************************************************************
 ** Ungueltigkeitswerte
 **/
#define cInvalidREpressure     ( (uint8) 0xff )
#define cInvalidREtemperature  ( (sint8) 0x7f )
#define cInvalidRElifeTime     ( (uint8) 0x00 )
#define cInvalidREstate        ( (uint8) 0x00 )
#define cInvalidRSSIsum        ( (uint8) 0x00 )
#define cInvalidSpinDir        ( (uint8) 0xFF )



/**
 ************************************************************************************************************
 ** Standard-Rückgabewerte von Funktionen
 **/
#define cRetError    ( (uint8) 0x00 )
#define cRetOk       ( (uint8) 0x01 )


/**
 ************************************************************************************************************
 ** FD Standard-Prüfwerte 
 **/


#define cNewIdInHistoryColumn0 ( (uint16) 0x0010)
#define cNewIdInHistoryColumn1 ( (uint16) 0x0020)
#define cNewIdInHistoryColumn2 ( (uint16) 0x0040)
#define cNewIdInHistoryColumn3 ( (uint16) 0x0080)


/************************************************************************************************************
 *                                             typedef
 ************************************************************************************************************/
typedef struct                 /* WORD */
{
  uint8 hi;                    /* Hi-Byte */
  uint8 lo;                    /* Lo-Byte */
} tWord;



typedef union                 /* DWORD */
{
  uint32 ulLongAccess;        /* 1x Long */
  uint16 ushWordAccess[2];    /* 2x Word */
  uint8  ucByteAccess[4];     /* 4x Byte */
} tLong;



#endif /* #ifdef _tss_stdX_H [0] */


