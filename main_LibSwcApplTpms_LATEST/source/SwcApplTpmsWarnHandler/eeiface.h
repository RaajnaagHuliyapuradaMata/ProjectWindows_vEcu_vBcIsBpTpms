/***************************************************************************************************
(c) Beru Electronics GmbH     BEE1     01/2003
================================================================================================

$Archive: /LIB/USWarn/versions/light/eeiface.h $
file name:     eeaccess.h

file status:   under construction

------------------------------------------------------------------------------------------------

author:        Peter Brand                Beru Electronics GmbH

intials:       pb


Modul Description

Global description:
headerfile for eeprom iface
Purpose:


Modul Modification

changes in 2003

19.01.2003 pb - 1st established
$Log: /LIB/USWarn/versions/light/eeiface.h $
 * 
 * 11    2.07.07 10:04 Peter
 * refactoring USWarn
 *
 * 9     2.03.05 16:02 Peter
 * function declaration for displaying eeprom usage
 *
 * 8     19.08.04 14:35 Peter
 * MISRA conformance enhanced and uswarn reconfigured for better metrics
 *
 * 6     9.10.03 17:13 Peter
 * Reset Funktion für den Modultest eingeführt
 *
 * 4     23.07.03 8:55 Peter
 * Put/GetDataEE explizit als void deklariert
***************************************************************************************************/
#ifndef EEIFACE_H
#define EEIFACE_H

/*
Declaration
*/

/*
Include
*/


/*
Prototypes
*/
extern void GetDataEE(unsigned char, unsigned char *, unsigned char);
extern void PutDataEE(unsigned char, const unsigned char *, unsigned char);

#ifndef pb_ModulTest_02062003

#else
extern void ResetEEPROM(void);
extern void PRINT_EepromUsage(void);
#endif
/*************************************************************
Macros
*/
#endif
