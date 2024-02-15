/**************************************************************************************************
 *(c) Beru Electronics GmbH     BEE1     01/2004
 *================================================================================================
 *
 *$Archive: /LIB/WAF/work/Walloc_IF.h $
 *
 *file name:     WAeeiface.h
 *
 *file status:   under construction
 *
 *------------------------------------------------------------------------------------------------
 *
 *author:        Peter Brand                Beru Electronics GmbH
 *
 *intials:       pb
 *
 *Modul Description
 *
 *Global description:
 *Purpose:
 *headerfile for interface module for tss basic component eeprom
 *
 *Modul Modification
 *changes in 2004
 *
 *$Log: /LIB/WAF/work/Walloc_IF.h $
 * 
 * 24    21.08.12 17:52 Peter
 * new module structure (FPA and AEC, CA seperated)
 * 
 * 23    29.06.12 15:00 Peter
 * decl 4 new ABS-counters-access function for 180° delayed FixPoint Huf
 * telegrams 
 * 
 * 22    24.05.12 16:52 Peter
 * IAT
 * walloc prepared 4 Conti tels
 * 
 * 21    7.02.12 15:08 Peter
 * ABS signal overflow protection not coupled to RF tel reception 
 * must now be detected actively at ABS signal reception (CAN cylce)
 * 
 * 20    27.01.12 15:58 Rapp
 * Ausputzen ...
 *
 * 19    23.01.12 18:30 Peter
 *
 * 18    19.01.12 18:55 Rapp
 * ABS-Linearisierung
 *
 * 17    17.01.12 13:55 Peter
 * 1st runable common Peak and FixPos allocation
 *
 * 16    11.01.12 19:07 Peter
 * backup only
 *
 * 15    1.12.10 11:35 Peter
 * support FW
 *
 * 14    17.11.10 15:55 Peter
 * replace waystretch by ABStick
 *
 * 13    17.11.10 12:00 Peter
 * simulation and TSS basic structure repaired
 *
 * 12    18.10.10 16:03 Schoenbeck
 * 1) Zählen der RE EdgCnt nur bei bestimmter Güte
 * 2) Histmem wieder aktiviert damit Kombianzeige wieder aktiv
 * 3) ZOM von 8 auf 6 reduziert wegen RAM Knappheit
 *
 * 11    12.10.10 16:33 Schoenbeck
 * erste Version mit Abrolllängenkriterium
 * Achtung histmem wurde wegen RAM-Knappheit deaktiviert!
 *
 * 10    16.09.10 17:53 Peter
 * refactored
 * optimized active sync of edge count sum
 * optimzed delta generation
 *
 * 9     27.08.10 16:57 Peter
 * Concept III/1 implemented
 *
 * 8     29.07.10 15:02 Peter
 * version with 1st concept (dT)
 *
 * 7     21.07.10 18:09 Peter
 * tel TO implemented
 *
 * 6     21.07.10 16:17 Peter
 * 1st WAF implementation with no WAF core
 *
 * 4     12.06.08 17:38 Peter
 * new module structure supported
 *
 * 2     28.02.06 13:26 Peter
 * access constants for wheel position information in eeprom added
 *
 * 1     9.01.04 17:23 Peter
 * nur zur Sicherung / backup
 *
 */

#ifdef WAEEIFACE_H

#else
/**************************************************************************************************
 *Declaration
 */

/**************************************************************************************************
 *Include
 */
#include "Compiler_Cfg.h"
#include "cd_decoder_x.h"
#include "abs_linX.h"
/**************************************************************************************************
 *macro
 */
#define WAEEIFACE_H

#define cWAParameter 8
#define cHistorySet1 9
#define cHistoryWPSet1 12

typedef tPreBuf tRFTelType;


#define cMaxTeLen sizeof(tRFTelType)
/**************************************************************************************************
 *data
 */
/**************************************************************************************************
 *Prototypes
 */
extern void GetWADataEE(unsigned char, unsigned char *, unsigned char);
extern void PutWADataEE(unsigned char, unsigned char *, unsigned char);

extern void WAStatusChangedEvent(unsigned short);
extern unsigned short ushGetABSingleTick(unsigned char ucIx);
extern unsigned char ucGetABSTick(unsigned short * );

extern unsigned char ucGetSpeed(void);
extern unsigned char ucNoWheelSensorMounted(void);

extern void SetWaData2NvmFlag(void);

extern unsigned char bGetABSSignalDTCActive(void);

extern unsigned char ucDAG_LQIParameter(void);

/*************************************************************
Macros
*/
#endif
